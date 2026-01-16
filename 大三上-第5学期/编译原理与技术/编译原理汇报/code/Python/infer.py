"""
infer.py - Algorithm W 类型推导
Hindley-Milner 多态类型推导的核心算法 Python 实现
"""

from typing import Tuple, Optional
from dataclasses import dataclass

from hm_types import (
    Type, TVar, TInt, TBool, TFun, TPair,
    Scheme, Subst, Env,
    fresh_type_var, mono_scheme, reset_tvar_counter
)
from ast_nodes import (
    Expr, ConstInt, ConstBool, Var, Lambda, App, Let, Pair
)
from unify import unify, UnificationError


class TypeInferenceError(Exception):
    """类型推导失败异常"""
    pass


@dataclass
class WResult:
    """Algorithm W 的返回结果"""
    subst: Subst
    type: Type


# ═══════════════════════════════════════════════════════════════
# 泛化与实例化
# ═══════════════════════════════════════════════════════════════

def generalize(env: Env, t: Type) -> Scheme:
    """
    泛化（Generalize）

    generalize(Γ, τ) = ∀α1...αn. τ
    其中 {α1...αn} = ftv(τ) - ftv(Γ)

    将类型中不在环境中出现的自由类型变量量化
    这是 let 多态的关键操作
    """
    # 计算可以泛化的类型变量
    free_in_type = t.ftv()
    free_in_env = env.ftv()
    quantifiers = list(free_in_type - free_in_env)

    return Scheme(quantifiers, t)


def instantiate(scheme: Scheme) -> Type:
    """
    实例化（Instantiate）

    instantiate(∀α1...αn. τ) = [α1 := β1, ..., αn := βn]τ
    其中 β1...βn 是新鲜的类型变量

    每次使用多态值时，用新鲜类型变量替换量化变量
    这是多态的核心机制
    """
    if not scheme.quantifiers:
        return scheme.body

    # 为每个量化变量创建新鲜类型变量
    subst_map = {
        qvar: fresh_type_var()
        for qvar in scheme.quantifiers
    }
    subst = Subst(subst_map)

    return scheme.body.apply_subst(subst)


# ═══════════════════════════════════════════════════════════════
# Algorithm W - HM 多态类型推导的核心算法
# ═══════════════════════════════════════════════════════════════

def W(env: Env, expr: Expr) -> WResult:
    """
    Algorithm W

    W(Γ, e) = (S, τ) 其中:
      - S 是在推导过程中产生的替换
      - τ 是推导出的类型

    这是 HM 类型推导的核心算法，通过递归处理表达式，
    同时执行类型推导和约束求解（即时合一）
    """

    # ─────────────────────────────────────────────────────────
    # 常量规则 (Const)
    # W(Γ, c) = (∅, type_of(c))
    # ─────────────────────────────────────────────────────────
    if isinstance(expr, ConstInt):
        return WResult(Subst.empty(), TInt())

    if isinstance(expr, ConstBool):
        return WResult(Subst.empty(), TBool())

    # ─────────────────────────────────────────────────────────
    # 变量规则 (Var)
    # W(Γ, x) = (∅, instantiate(Γ(x)))
    # 每次使用变量时实例化其类型方案
    # ─────────────────────────────────────────────────────────
    if isinstance(expr, Var):
        scheme = env.lookup(expr.name)
        if scheme is None:
            raise TypeInferenceError(f"Unbound variable: {expr.name}")
        t = instantiate(scheme)
        return WResult(Subst.empty(), t)

    # ─────────────────────────────────────────────────────────
    # Lambda 规则 (Abs)
    # α fresh
    # W(Γ ∪ {x:α}, e) = (S, τ)
    # W(Γ, λx.e) = (S, S(α) -> τ)
    # ─────────────────────────────────────────────────────────
    if isinstance(expr, Lambda):
        alpha = fresh_type_var()
        env1 = env.extend(expr.param, mono_scheme(alpha))

        r1 = W(env1, expr.body)

        param_type = alpha.apply_subst(r1.subst)
        fun_type = TFun(param_type, r1.type)

        return WResult(r1.subst, fun_type)

    # ─────────────────────────────────────────────────────────
    # 应用规则 (App)
    # W(Γ, e1) = (S1, τ1)
    # W(S1(Γ), e2) = (S2, τ2)
    # α fresh
    # S3 = unify(S2(τ1), τ2 -> α)
    # W(Γ, e1 e2) = (S3∘S2∘S1, S3(α))
    # ─────────────────────────────────────────────────────────
    if isinstance(expr, App):
        r1 = W(env, expr.func)
        env2 = env.apply_subst(r1.subst)

        r2 = W(env2, expr.arg)

        alpha = fresh_type_var()
        func_type = r1.type.apply_subst(r2.subst)
        expected = TFun(r2.type, alpha)

        try:
            s3 = unify(func_type, expected)
        except UnificationError as e:
            raise TypeInferenceError(f"In application {expr}: {e}")

        s_final = s3.compose(r2.subst).compose(r1.subst)
        result_type = alpha.apply_subst(s3)

        return WResult(s_final, result_type)

    # ─────────────────────────────────────────────────────────
    # Let 规则 (Let) - 多态的关键！
    # W(Γ, e1) = (S1, τ1)
    # σ = generalize(S1(Γ), τ1)   // 泛化！
    # W(S1(Γ) ∪ {x:σ}, e2) = (S2, τ2)
    # W(Γ, let x = e1 in e2) = (S2∘S1, τ2)
    # ─────────────────────────────────────────────────────────
    if isinstance(expr, Let):
        # 首先推导绑定表达式 e1 的类型
        r1 = W(env, expr.bind_expr)

        # 应用替换到环境
        env1 = env.apply_subst(r1.subst)

        # **关键步骤**：泛化 τ1，得到多态类型方案 σ
        sigma = generalize(env1, r1.type)

        # 扩展环境，将 x 绑定到 σ
        env2 = env1.extend(expr.name, sigma)

        # 在扩展后的环境中推导 e2
        r2 = W(env2, expr.body)

        # 组合替换
        s_final = r2.subst.compose(r1.subst)
        return WResult(s_final, r2.type)

    # ─────────────────────────────────────────────────────────
    # 二元组规则 (Pair)
    # W(Γ, e1) = (S1, τ1)
    # W(S1(Γ), e2) = (S2, τ2)
    # W(Γ, (e1, e2)) = (S2∘S1, (S2(τ1), τ2))
    # ─────────────────────────────────────────────────────────
    if isinstance(expr, Pair):
        r1 = W(env, expr.fst)
        env2 = env.apply_subst(r1.subst)

        r2 = W(env2, expr.snd)

        fst_type = r1.type.apply_subst(r2.subst)
        pair_type = TPair(fst_type, r2.type)

        s_final = r2.subst.compose(r1.subst)
        return WResult(s_final, pair_type)

    raise TypeInferenceError(f"Unknown expression type: {type(expr)}")


# ═══════════════════════════════════════════════════════════════
# 高层接口
# ═══════════════════════════════════════════════════════════════

def infer_type(expr: Expr) -> Type:
    """
    类型推导的高层接口
    从空环境开始推导表达式的类型
    """
    reset_tvar_counter()
    result = W(Env(), expr)
    return result.type


def infer_type_with_env(env: Env, expr: Expr) -> Type:
    """带预定义环境的类型推导"""
    result = W(env, expr)
    return result.type
