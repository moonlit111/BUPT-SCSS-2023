/**
 * infer.c - Algorithm W 类型推导实现
 * Hindley-Milner 多态类型推导的核心算法
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/type_utils.h"
#include "../include/env.h"
#include "../include/subst.h"
#include "../include/unify.h"
#include "../include/infer.h"

/*=============================================================
 * 泛化（Generalize）
 * generalize(Γ, τ) = ∀α1...αn. τ
 * 其中 {α1...αn} = ftv(τ) - ftv(Γ)
 *=============================================================*/
Scheme* generalize(Env env, Type *t) {
    TVarSet type_ftv = ftv_type(t);
    TVarSet env_ftv = ftv_env(env);
    TVarSet free_vars = tvarset_diff(type_ftv, env_ftv);

    return make_poly_scheme(free_vars.count, free_vars.vars, t);
}

/*=============================================================
 * 实例化（Instantiate）
 * instantiate(∀α1...αn. τ) = [α1 := β1, ..., αn := βn]τ
 *=============================================================*/
Type* instantiate(Scheme *scheme) {
    if (scheme == NULL) return NULL;

    if (scheme->quantifier_count == 0) {
        return copy_type(scheme->body);
    }

    // 为每个量化变量创建新鲜类型变量
    Subst s = { .count = scheme->quantifier_count };
    for (int i = 0; i < scheme->quantifier_count; i++) {
        s.vars[i] = scheme->quantifiers[i];
        s.types[i] = fresh_type_var();
    }

    return apply_subst_type(&s, scheme->body);
}

/*=============================================================
 * Algorithm W 返回结果的辅助函数
 *=============================================================*/
static WResult make_w_success(Subst s, Type *t) {
    WResult r = {
        .subst = s,
        .type = t,
        .success = true,
        .error_msg = NULL
    };
    return r;
}

static WResult make_w_error(const char *msg) {
    WResult r = {
        .subst = subst_empty(),
        .type = NULL,
        .success = false,
        .error_msg = strdup(msg)
    };
    return r;
}

/*=============================================================
 * Algorithm W - HM 多态类型推导的核心算法
 *=============================================================*/
WResult W(Env env, Expr *expr) {
    if (expr == NULL) {
        return make_w_error("Null expression");
    }

    switch (expr->kind) {

        /*---------------------------------------------------------
         * 常量规则 (Const)
         * W(Γ, c) = (∅, type_of(c))
         *---------------------------------------------------------*/
        case EXPR_CONST_INT: {
            return make_w_success(subst_empty(), make_type_int());
        }

        case EXPR_CONST_BOOL: {
            return make_w_success(subst_empty(), make_type_bool());
        }

        /*---------------------------------------------------------
         * 变量规则 (Var)
         * W(Γ, x) = (∅, instantiate(Γ(x)))
         *---------------------------------------------------------*/
        case EXPR_VAR: {
            Scheme *scheme = env_lookup(env, expr->var_name);
            if (scheme == NULL) {
                char buf[128];
                snprintf(buf, sizeof(buf), "Unbound variable: %s", expr->var_name);
                return make_w_error(buf);
            }
            Type *t = instantiate(scheme);
            return make_w_success(subst_empty(), t);
        }

        /*---------------------------------------------------------
         * Lambda 规则 (Abs)
         * α fresh
         * W(Γ ∪ {x:α}, e) = (S, τ)
         * W(Γ, λx.e) = (S, S(α) -> τ)
         *---------------------------------------------------------*/
        case EXPR_LAMBDA: {
            Type *alpha = fresh_type_var();
            Scheme *mono = make_mono_scheme(alpha);
            Env env1 = env_extend(env, expr->lambda.param_name, mono);
            free_scheme(mono);

            WResult r1 = W(env1, expr->lambda.body);
            env_free_single(env1);  // 只释放新增的节点

            if (!r1.success) return r1;

            Type *param_type = apply_subst_type(&r1.subst, alpha);
            Type *fun_type = make_fun_type(param_type, r1.type);
            free_type(alpha);

            return make_w_success(r1.subst, fun_type);
        }

        /*---------------------------------------------------------
         * 应用规则 (App)
         * W(Γ, e1) = (S1, τ1)
         * W(S1(Γ), e2) = (S2, τ2)
         * α fresh
         * S3 = unify(S2(τ1), τ2 -> α)
         * W(Γ, e1 e2) = (S3∘S2∘S1, S3(α))
         *---------------------------------------------------------*/
        case EXPR_APP: {
            WResult r1 = W(env, expr->app.func);
            if (!r1.success) return r1;

            Env env2 = apply_subst_env(&r1.subst, env);
            WResult r2 = W(env2, expr->app.arg);
            env_free(env2);

            if (!r2.success) return r2;

            Type *alpha = fresh_type_var();
            Type *func_type = apply_subst_type(&r2.subst, r1.type);
            Type *expected = make_fun_type(copy_type(r2.type), copy_type(alpha));

            UnifyResult u = unify(func_type, expected);
            free_type(func_type);
            free_type(expected);

            if (!u.success) {
                free_type(alpha);
                return make_w_error(u.error_msg);
            }

            Subst s_tmp = subst_compose(u.subst, r2.subst);
            Subst s_final = subst_compose(s_tmp, r1.subst);
            Type *result_type = apply_subst_type(&u.subst, alpha);
            free_type(alpha);

            return make_w_success(s_final, result_type);
        }

        /*---------------------------------------------------------
         * Let 规则 (Let) - 多态的关键！
         * W(Γ, e1) = (S1, τ1)
         * σ = generalize(S1(Γ), τ1)   // 泛化！
         * W(S1(Γ) ∪ {x:σ}, e2) = (S2, τ2)
         * W(Γ, let x = e1 in e2) = (S2∘S1, τ2)
         *---------------------------------------------------------*/
        case EXPR_LET: {
            // 首先推导绑定表达式 e1 的类型
            WResult r1 = W(env, expr->let.bind_expr);
            if (!r1.success) return r1;

            // 应用替换到环境（创建全新的环境链）
            Env env1 = apply_subst_env(&r1.subst, env);

            // **关键步骤**：泛化 τ1，得到多态类型方案 σ
            Scheme *sigma = generalize(env1, r1.type);

            // 扩展环境，将 x 绑定到 σ（只创建一个新节点）
            Env env2 = env_extend(env1, expr->let.let_name, sigma);
            free_scheme(sigma);

            // 在扩展后的环境中推导 e2
            WResult r2 = W(env2, expr->let.let_body);

            // env2 的 next 指向 env1，所以先释放 env2 的头节点
            env_free_single(env2);
            // 然后释放 env1 整个链（它是 apply_subst_env 创建的完整副本）
            env_free(env1);

            if (!r2.success) return r2;

            // 组合替换
            Subst s_final = subst_compose(r2.subst, r1.subst);
            return make_w_success(s_final, r2.type);
        }

        /*---------------------------------------------------------
         * 二元组规则 (Pair)
         * W(Γ, e1) = (S1, τ1)
         * W(S1(Γ), e2) = (S2, τ2)
         * W(Γ, (e1, e2)) = (S2∘S1, (S2(τ1), τ2))
         *---------------------------------------------------------*/
        case EXPR_PAIR: {
            WResult r1 = W(env, expr->pair.fst);
            if (!r1.success) return r1;

            Env env2 = apply_subst_env(&r1.subst, env);
            WResult r2 = W(env2, expr->pair.snd);
            env_free(env2);

            if (!r2.success) return r2;

            Type *fst_type = apply_subst_type(&r2.subst, r1.type);
            Type *pair_type = make_pair_type(fst_type, r2.type);

            Subst s_final = subst_compose(r2.subst, r1.subst);
            return make_w_success(s_final, pair_type);
        }
    }

    return make_w_error("Unknown expression kind");
}

/*=============================================================
 * 高层接口
 *=============================================================*/
WResult infer_type(Expr *expr) {
    reset_tvar_counter();
    return W(env_empty(), expr);
}

WResult infer_type_with_env(Env env, Expr *expr) {
    return W(env, expr);
}
