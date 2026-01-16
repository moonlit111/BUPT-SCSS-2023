"""
ast_nodes.py - 表达式 AST 节点定义
Core-ML 风格的表达式抽象语法树
"""

from dataclasses import dataclass
from typing import Union
from abc import ABC, abstractmethod


class Expr(ABC):
    """表达式基类"""
    
    @abstractmethod
    def __str__(self) -> str:
        pass


@dataclass
class ConstInt(Expr):
    """整数常量"""
    value: int
    
    def __str__(self) -> str:
        return str(self.value)


@dataclass
class ConstBool(Expr):
    """布尔常量"""
    value: bool
    
    def __str__(self) -> str:
        return "true" if self.value else "false"


@dataclass
class Var(Expr):
    """变量"""
    name: str
    
    def __str__(self) -> str:
        return self.name


@dataclass
class Lambda(Expr):
    """Lambda 表达式 λx. e"""
    param: str
    body: Expr
    
    def __str__(self) -> str:
        return f"(λ{self.param}. {self.body})"


@dataclass
class App(Expr):
    """函数应用 e1 e2"""
    func: Expr
    arg: Expr
    
    def __str__(self) -> str:
        return f"({self.func} {self.arg})"


@dataclass
class Let(Expr):
    """Let 表达式 let x = e1 in e2"""
    name: str
    bind_expr: Expr
    body: Expr
    
    def __str__(self) -> str:
        return f"(let {self.name} = {self.bind_expr} in {self.body})"


@dataclass
class Pair(Expr):
    """二元组 (e1, e2)"""
    fst: Expr
    snd: Expr
    
    def __str__(self) -> str:
        return f"({self.fst}, {self.snd})"


# ═══════════════════════════════════════════════════════════════
# AST 构造辅助函数
# ═══════════════════════════════════════════════════════════════

def make_const_int(value: int) -> ConstInt:
    return ConstInt(value)

def make_const_bool(value: bool) -> ConstBool:
    return ConstBool(value)

def make_var(name: str) -> Var:
    return Var(name)

def make_lambda(param: str, body: Expr) -> Lambda:
    return Lambda(param, body)

def make_app(func: Expr, arg: Expr) -> App:
    return App(func, arg)

def make_let(name: str, bind_expr: Expr, body: Expr) -> Let:
    return Let(name, bind_expr, body)

def make_pair(fst: Expr, snd: Expr) -> Pair:
    return Pair(fst, snd)

