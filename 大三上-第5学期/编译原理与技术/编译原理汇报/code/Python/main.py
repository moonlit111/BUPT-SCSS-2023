#!/usr/bin/env python3
"""
main.py - HM 多态类型推导系统演示程序
Hindley-Milner Type Inference Demo

演示三个经典示例：
1. let id = λx.x in id           → 'a -> 'a
2. let const = λx.λy.x in const  → 'a -> 'b -> 'a
3. let id = λx.x in (id 5, id true) → (Int, Bool)
"""

from hm_types import reset_tvar_counter
from ast_nodes import (
    make_const_int, make_const_bool, make_var,
    make_lambda, make_app, make_let, make_pair
)
from infer import infer_type, TypeInferenceError


def print_separator(title: str):
    print()
    print("═" * 65)
    print(f"  {title}")
    print("═" * 65)


def run_inference(name: str, expr):
    """运行类型推导并打印结果"""
    print(f"\n【{name}】")
    print(f"Expression: {expr}")
    
    try:
        reset_tvar_counter()
        result_type = infer_type(expr)
        print(f"✓ Type inference succeeded!")
        print(f"  Inferred type: {result_type}")
    except TypeInferenceError as e:
        print(f"✗ Type inference failed!")
        print(f"  Error: {e}")
    print()


def main():
    print("╔" + "═" * 63 + "╗")
    print("║     Hindley-Milner 多态类型推导系统 (Algorithm W)            ║")
    print("║     Polymorphic Type Inference with SDT - Python             ║")
    print("╚" + "═" * 63 + "╝")

    # ═══════════════════════════════════════════════════════════════
    # 示例一：let id = λx.x in id
    # 期望类型：'a -> 'a
    # ═══════════════════════════════════════════════════════════════
    print_separator("示例一：恒等函数 (Identity Function)")
    print("源代码: let id = λx. x in id")
    print("期望类型: 'a -> 'a (多态恒等函数)")
    
    # 构造 AST: let id = λx.x in id
    lambda_x_x = make_lambda("x", make_var("x"))
    expr1 = make_let("id", lambda_x_x, make_var("id"))
    
    run_inference("let id = λx.x in id", expr1)

    # ═══════════════════════════════════════════════════════════════
    # 示例二：let const = λx.λy.x in const
    # 期望类型：'a -> 'b -> 'a
    # ═══════════════════════════════════════════════════════════════
    print_separator("示例二：K 组合子 (Const Function)")
    print("源代码: let const = λx. λy. x in const")
    print("期望类型: 'a -> 'b -> 'a (K combinator)")
    
    # 构造 AST: let const = λx.λy.x in const
    const_body = make_lambda("x", make_lambda("y", make_var("x")))
    expr2 = make_let("const", const_body, make_var("const"))
    
    run_inference("let const = λx.λy.x in const", expr2)

    # ═══════════════════════════════════════════════════════════════
    # 示例三：let id = λx.x in (id 5, id true)
    # 期望类型：(Int, Bool)
    # 
    # 这是多态的关键示例！
    # 单态系统会失败（Int ≠ Bool），HM 系统成功
    # ═══════════════════════════════════════════════════════════════
    print_separator("示例三：多态应用 (Polymorphic Application)")
    print("源代码: let id = λx. x in (id 5, id true)")
    print("期望类型: (Int, Bool)")
    print()
    print("注意：单态类型系统会在此失败（Int = Bool 冲突）")
    print("      HM 多态系统通过实例化避免类型污染")
    
    # 构造 AST: let id = λx.x in (id 5, id true)
    id_fun = make_lambda("x", make_var("x"))
    id_5 = make_app(make_var("id"), make_const_int(5))
    id_true = make_app(make_var("id"), make_const_bool(True))
    pair = make_pair(id_5, id_true)
    expr3 = make_let("id", id_fun, pair)
    
    run_inference("let id = λx.x in (id 5, id true)", expr3)

    # ═══════════════════════════════════════════════════════════════
    # 额外示例：嵌套 let
    # ═══════════════════════════════════════════════════════════════
    print_separator("额外示例：嵌套 let 表达式")
    print("源代码: let f = λx.x in let g = f in g 42")
    
    # 构造 AST: let f = λx.x in let g = f in g 42
    f_body = make_lambda("x", make_var("x"))
    g_use = make_app(make_var("g"), make_const_int(42))
    inner_let = make_let("g", make_var("f"), g_use)
    expr4 = make_let("f", f_body, inner_let)
    
    run_inference("let f = λx.x in let g = f in g 42", expr4)

    # ═══════════════════════════════════════════════════════════════
    # 额外示例：复合函数
    # ═══════════════════════════════════════════════════════════════
    print_separator("额外示例：函数组合")
    print("源代码: let compose = λf.λg.λx.f (g x) in compose")
    
    # 构造 AST: let compose = λf.λg.λx.f (g x) in compose
    gx = make_app(make_var("g"), make_var("x"))
    f_gx = make_app(make_var("f"), gx)
    compose_body = make_lambda("f", 
                      make_lambda("g", 
                         make_lambda("x", f_gx)))
    expr5 = make_let("compose", compose_body, make_var("compose"))
    
    run_inference("let compose = λf.λg.λx.f (g x) in compose", expr5)

    print()
    print("═" * 65)
    print("  演示完成！")
    print("═" * 65)


if __name__ == "__main__":
    main()

