/**
 * unify.c - 类型合一（Unification）实现
 * Robinson 统一算法
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/type_utils.h"
#include "../include/subst.h"
#include "../include/unify.h"

/**
 * 出现检查（Occurs Check）
 * 防止产生无限类型
 */
bool occurs_check(TVar tv, Type *t) {
    if (t == NULL) return false;
    
    switch (t->kind) {
        case T_VAR:
            return tvar_equal(tv, t->tvar);
        case T_INT:
        case T_BOOL:
            return false;
        case T_FUN:
        case T_PAIR:
            return occurs_check(tv, t->left) || occurs_check(tv, t->right);
    }
    return false;
}

static UnifyResult make_success(Subst s) {
    UnifyResult r = { .success = true, .subst = s, .error_msg = NULL };
    return r;
}

static UnifyResult make_error(const char *msg) {
    UnifyResult r = {
        .success = false,
        .subst = subst_empty(),
        .error_msg = strdup(msg)
    };
    return r;
}

/**
 * 合一算法核心实现
 * unify(τ1, τ2) 返回最一般合一子 S 使得 S(τ1) = S(τ2)
 */
UnifyResult unify(Type *t1, Type *t2) {
    // 两个类型相同
    if (type_equal(t1, t2)) {
        return make_success(subst_empty());
    }
    
    // t1 是类型变量
    if (t1->kind == T_VAR) {
        if (occurs_check(t1->tvar, t2)) {
            return make_error("Occurs check failed: infinite type");
        }
        return make_success(subst_single(t1->tvar, t2));
    }
    
    // t2 是类型变量
    if (t2->kind == T_VAR) {
        if (occurs_check(t2->tvar, t1)) {
            return make_error("Occurs check failed: infinite type");
        }
        return make_success(subst_single(t2->tvar, t1));
    }
    
    // 两个函数类型
    if (t1->kind == T_FUN && t2->kind == T_FUN) {
        // 先合一参数类型
        UnifyResult r1 = unify(t1->left, t2->left);
        if (!r1.success) return r1;
        
        // 将替换应用到返回类型
        Type *right1 = apply_subst_type(&r1.subst, t1->right);
        Type *right2 = apply_subst_type(&r1.subst, t2->right);
        
        // 合一返回类型
        UnifyResult r2 = unify(right1, right2);
        free_type(right1);
        free_type(right2);
        
        if (!r2.success) {
            // 清理 r1 的内存
            return r2;
        }
        
        // 组合两个替换
        Subst composed = subst_compose(r2.subst, r1.subst);
        return make_success(composed);
    }
    
    // 两个二元组类型
    if (t1->kind == T_PAIR && t2->kind == T_PAIR) {
        UnifyResult r1 = unify(t1->left, t2->left);
        if (!r1.success) return r1;
        
        Type *right1 = apply_subst_type(&r1.subst, t1->right);
        Type *right2 = apply_subst_type(&r1.subst, t2->right);
        
        UnifyResult r2 = unify(right1, right2);
        free_type(right1);
        free_type(right2);
        
        if (!r2.success) return r2;
        
        Subst composed = subst_compose(r2.subst, r1.subst);
        return make_success(composed);
    }
    
    // 类型不匹配
    char error_buf[256];
    snprintf(error_buf, sizeof(error_buf),
             "Type mismatch: cannot unify %s with %s",
             type_to_string(t1), type_to_string(t2));
    return make_error(error_buf);
}

