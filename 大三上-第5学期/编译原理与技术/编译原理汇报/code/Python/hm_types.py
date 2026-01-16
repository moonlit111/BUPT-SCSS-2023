"""
hm_types.py - HM 多态类型推导系统的类型定义
Hindley-Milner Type Inference System

Python 版本实现
"""

from dataclasses import dataclass
from typing import List, Dict, Optional, Set, Tuple
from abc import ABC, abstractmethod

# ═══════════════════════════════════════════════════════════════
# 类型变量计数器
# ═══════════════════════════════════════════════════════════════
_tvar_counter = 0

def fresh_tvar() -> int:
    """生成新鲜的类型变量 ID"""
    global _tvar_counter
    _tvar_counter += 1
    return _tvar_counter

def reset_tvar_counter():
    """重置类型变量计数器"""
    global _tvar_counter
    _tvar_counter = 0

def tvar_to_name(id: int) -> str:
    """将类型变量 ID 转换为可读名称"""
    if id <= 26:
        return f"'{chr(ord('a') + id - 1)}"
    else:
        return f"'t{id}"


# ═══════════════════════════════════════════════════════════════
# 类型 (Type / Monotype τ)
# ═══════════════════════════════════════════════════════════════
class Type(ABC):
    """类型基类"""

    @abstractmethod
    def __str__(self) -> str:
        pass

    @abstractmethod
    def ftv(self) -> Set[int]:
        """返回自由类型变量集合"""
        pass

    @abstractmethod
    def apply_subst(self, subst: 'Subst') -> 'Type':
        """应用替换"""
        pass


@dataclass
class TVar(Type):
    """类型变量 α, β, ..."""
    id: int

    def __str__(self) -> str:
        return tvar_to_name(self.id)

    def ftv(self) -> Set[int]:
        return {self.id}

    def apply_subst(self, subst: 'Subst') -> Type:
        if self.id in subst.mapping:
            return subst.mapping[self.id]
        return self


@dataclass
class TInt(Type):
    """Int 类型"""
    def __str__(self) -> str:
        return "Int"

    def ftv(self) -> Set[int]:
        return set()

    def apply_subst(self, subst: 'Subst') -> Type:
        return self


@dataclass
class TBool(Type):
    """Bool 类型"""
    def __str__(self) -> str:
        return "Bool"

    def ftv(self) -> Set[int]:
        return set()

    def apply_subst(self, subst: 'Subst') -> Type:
        return self


@dataclass
class TFun(Type):
    """函数类型 τ1 -> τ2"""
    param: Type
    result: Type

    def __str__(self) -> str:
        if isinstance(self.param, TFun):
            return f"({self.param}) -> {self.result}"
        return f"{self.param} -> {self.result}"

    def ftv(self) -> Set[int]:
        return self.param.ftv() | self.result.ftv()

    def apply_subst(self, subst: 'Subst') -> Type:
        return TFun(
            self.param.apply_subst(subst),
            self.result.apply_subst(subst)
        )


@dataclass
class TPair(Type):
    """二元组类型 (τ1, τ2)"""
    fst: Type
    snd: Type

    def __str__(self) -> str:
        return f"({self.fst}, {self.snd})"

    def ftv(self) -> Set[int]:
        return self.fst.ftv() | self.snd.ftv()

    def apply_subst(self, subst: 'Subst') -> Type:
        return TPair(
            self.fst.apply_subst(subst),
            self.snd.apply_subst(subst)
        )


def fresh_type_var() -> TVar:
    """生成新鲜的类型变量"""
    return TVar(fresh_tvar())


# ═══════════════════════════════════════════════════════════════
# 多态类型方案 (Polytype / Type Scheme σ)
# σ = ∀α1...αn. τ
# ═══════════════════════════════════════════════════════════════
@dataclass
class Scheme:
    """多态类型方案"""
    quantifiers: List[int]  # 量化的类型变量
    body: Type              # 类型体

    def __str__(self) -> str:
        if not self.quantifiers:
            return str(self.body)
        qvars = " ".join(tvar_to_name(q) for q in self.quantifiers)
        return f"∀{qvars}. {self.body}"

    def ftv(self) -> Set[int]:
        """返回自由类型变量（排除被量化的变量）"""
        return self.body.ftv() - set(self.quantifiers)

    def apply_subst(self, subst: 'Subst') -> 'Scheme':
        """应用替换（不替换被量化的变量）"""
        # 过滤掉被量化的变量
        filtered = Subst({
            k: v for k, v in subst.mapping.items()
            if k not in self.quantifiers
        })
        return Scheme(self.quantifiers, self.body.apply_subst(filtered))


def mono_scheme(t: Type) -> Scheme:
    """创建单态类型方案"""
    return Scheme([], t)


# ═══════════════════════════════════════════════════════════════
# 替换 (Substitution S: TVar -> Type)
# ═══════════════════════════════════════════════════════════════
@dataclass
class Subst:
    """类型替换"""
    mapping: Dict[int, Type]

    def __str__(self) -> str:
        if not self.mapping:
            return "{}"
        items = ", ".join(
            f"{tvar_to_name(k)} := {v}"
            for k, v in self.mapping.items()
        )
        return f"{{{items}}}"

    @staticmethod
    def empty() -> 'Subst':
        """空替换"""
        return Subst({})

    @staticmethod
    def single(tvar_id: int, t: Type) -> 'Subst':
        """单一替换 [α := τ]"""
        return Subst({tvar_id: t})

    def compose(self, other: 'Subst') -> 'Subst':
        """
        组合替换: self ∘ other
        即先应用 other，再应用 self
        """
        # 对 other 中的所有类型应用 self
        new_mapping = {
            k: v.apply_subst(self)
            for k, v in other.mapping.items()
        }
        # 添加 self 中不在 other 域中的映射
        for k, v in self.mapping.items():
            if k not in new_mapping:
                new_mapping[k] = v
        return Subst(new_mapping)


# ═══════════════════════════════════════════════════════════════
# 类型环境 (Type Environment Γ)
# ═══════════════════════════════════════════════════════════════
class Env:
    """类型环境 Γ: VarName -> Scheme"""

    def __init__(self, bindings: Optional[Dict[str, Scheme]] = None):
        self._bindings: Dict[str, Scheme] = bindings.copy() if bindings else {}

    def lookup(self, name: str) -> Optional[Scheme]:
        """查找变量的类型方案"""
        return self._bindings.get(name)

    def extend(self, name: str, scheme: Scheme) -> 'Env':
        """扩展环境（返回新环境，不修改原环境）"""
        new_bindings = self._bindings.copy()
        new_bindings[name] = scheme
        return Env(new_bindings)

    def ftv(self) -> Set[int]:
        """环境中所有类型方案的自由类型变量"""
        result: Set[int] = set()
        for scheme in self._bindings.values():
            result |= scheme.ftv()
        return result

    def apply_subst(self, subst: Subst) -> 'Env':
        """将替换应用到环境中的所有类型方案"""
        new_bindings = {
            name: scheme.apply_subst(subst)
            for name, scheme in self._bindings.items()
        }
        return Env(new_bindings)

    def __str__(self) -> str:
        if not self._bindings:
            return "Γ = {}"
        items = ", ".join(f"{k}: {v}" for k, v in self._bindings.items())
        return f"Γ = {{{items}}}"

