"""
unify.py - 类型合一（Unification）
Robinson 统一算法的 Python 实现
"""

from typing import Tuple, Optional
from hm_types import (
    Type, TVar, TInt, TBool, TFun, TPair, 
    Subst
)


class UnificationError(Exception):
    """合一失败异常"""
    pass


def occurs_check(tvar_id: int, t: Type) -> bool:
    """
    出现检查（Occurs Check）
    检查类型变量是否出现在类型 t 中
    用于防止产生无限类型，如 α = α -> β
    """
    if isinstance(t, TVar):
        return t.id == tvar_id
    elif isinstance(t, (TInt, TBool)):
        return False
    elif isinstance(t, TFun):
        return occurs_check(tvar_id, t.param) or occurs_check(tvar_id, t.result)
    elif isinstance(t, TPair):
        return occurs_check(tvar_id, t.fst) or occurs_check(tvar_id, t.snd)
    return False


def unify(t1: Type, t2: Type) -> Subst:
    """
    合一两个类型
    
    返回最一般合一子（MGU）S，使得 S(t1) = S(t2)
    如果无法合一，抛出 UnificationError
    
    合一规则：
    1. 相同类型 → 空替换
    2. 类型变量 α 与 τ → [α := τ]（需要出现检查）
    3. τ1 -> τ2 与 σ1 -> σ2 → 递归合一
    4. (τ1, τ2) 与 (σ1, σ2) → 递归合一
    5. 否则 → 失败
    """
    # 1. 相同类型
    if t1 == t2:
        return Subst.empty()
    
    # 2a. t1 是类型变量
    if isinstance(t1, TVar):
        if occurs_check(t1.id, t2):
            raise UnificationError(
                f"Occurs check failed: {t1} occurs in {t2} (infinite type)"
            )
        return Subst.single(t1.id, t2)
    
    # 2b. t2 是类型变量
    if isinstance(t2, TVar):
        if occurs_check(t2.id, t1):
            raise UnificationError(
                f"Occurs check failed: {t2} occurs in {t1} (infinite type)"
            )
        return Subst.single(t2.id, t1)
    
    # 3. 两个函数类型
    if isinstance(t1, TFun) and isinstance(t2, TFun):
        # 先合一参数类型
        s1 = unify(t1.param, t2.param)
        # 将 s1 应用到返回类型，再合一
        s2 = unify(
            t1.result.apply_subst(s1),
            t2.result.apply_subst(s1)
        )
        # 组合替换
        return s2.compose(s1)
    
    # 4. 两个二元组类型
    if isinstance(t1, TPair) and isinstance(t2, TPair):
        s1 = unify(t1.fst, t2.fst)
        s2 = unify(
            t1.snd.apply_subst(s1),
            t2.snd.apply_subst(s1)
        )
        return s2.compose(s1)
    
    # 5. 类型不匹配
    raise UnificationError(
        f"Type mismatch: cannot unify {t1} with {t2}"
    )

