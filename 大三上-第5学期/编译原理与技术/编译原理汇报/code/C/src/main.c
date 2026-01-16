/**
 * main.c - HM 多态类型推导系统演示程序
 * 
 * 演示三个经典示例：
 * 1. let id = λx.x in id           → 'a -> 'a
 * 2. let const = λx.λy.x in const  → 'a -> 'b -> 'a
 * 3. let id = λx.x in (id 5, id true) → (Int, Bool)
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/types.h"
#include "../include/type_utils.h"
#include "../include/env.h"
#include "../include/subst.h"
#include "../include/unify.h"
#include "../include/infer.h"
#include "../include/ast.h"

void print_separator(const char *title) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("  %s\n", title);
    printf("═══════════════════════════════════════════════════════════════\n");
}

void run_inference(const char *name, Expr *expr) {
    printf("\n【%s】\n", name);
    printf("Expression: %s\n", ast_to_string(expr));
    printf("AST:\n");
    print_ast(expr);
    
    WResult result = infer_type(expr);
    
    if (result.success) {
        printf("\n✓ Type inference succeeded!\n");
        printf("  Inferred type: ");
        print_type(result.type);
        printf("\n");
    } else {
        printf("\n✗ Type inference failed!\n");
        printf("  Error: %s\n", result.error_msg);
    }
    printf("\n");
}

int main(void) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║     Hindley-Milner 多态类型推导系统 (Algorithm W)              ║\n");
    printf("║     Polymorphic Type Inference with SDT                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");

    /*=========================================================
     * 示例一：let id = λx.x in id
     * 期望类型：'a -> 'a
     *=========================================================*/
    print_separator("示例一：恒等函数 (Identity Function)");
    printf("源代码: let id = λx. x in id\n");
    printf("期望类型: 'a -> 'a (多态恒等函数)\n");
    
    {
        // 构造 AST: let id = λx.x in id
        Expr *lambda_x_x = make_lambda("x", make_var("x"));
        Expr *expr1 = make_let("id", lambda_x_x, make_var("id"));
        
        run_inference("let id = λx.x in id", expr1);
        free_ast(expr1);
    }

    /*=========================================================
     * 示例二：let const = λx.λy.x in const
     * 期望类型：'a -> 'b -> 'a
     *=========================================================*/
    print_separator("示例二：K 组合子 (Const Function)");
    printf("源代码: let const = λx. λy. x in const\n");
    printf("期望类型: 'a -> 'b -> 'a (K combinator)\n");
    
    {
        // 构造 AST: let const = λx.λy.x in const
        Expr *const_body = make_lambda("x", 
                              make_lambda("y", 
                                  make_var("x")));
        Expr *expr2 = make_let("const", const_body, make_var("const"));
        
        run_inference("let const = λx.λy.x in const", expr2);
        free_ast(expr2);
    }

    /*=========================================================
     * 示例三：let id = λx.x in (id 5, id true)
     * 期望类型：(Int, Bool)
     * 
     * 这是多态的关键示例！
     * 单态系统会失败（Int ≠ Bool），HM 系统成功
     *=========================================================*/
    print_separator("示例三：多态应用 (Polymorphic Application)");
    printf("源代码: let id = λx. x in (id 5, id true)\n");
    printf("期望类型: (Int, Bool)\n");
    printf("\n注意：单态类型系统会在此失败（Int = Bool 冲突）\n");
    printf("      HM 多态系统通过实例化避免类型污染\n");
    
    {
        // 构造 AST: let id = λx.x in (id 5, id true)
        Expr *id_fun = make_lambda("x", make_var("x"));
        Expr *id_5 = make_app(make_var("id"), make_const_int(5));
        Expr *id_true = make_app(make_var("id"), make_const_bool(true));
        Expr *pair = make_pair(id_5, id_true);
        Expr *expr3 = make_let("id", id_fun, pair);
        
        run_inference("let id = λx.x in (id 5, id true)", expr3);
        free_ast(expr3);
    }

    /*=========================================================
     * 额外示例：嵌套 let
     *=========================================================*/
    print_separator("额外示例：嵌套 let 表达式");
    printf("源代码: let f = λx.x in let g = f in g 42\n");
    
    {
        Expr *f_body = make_lambda("x", make_var("x"));
        Expr *g_use = make_app(make_var("g"), make_const_int(42));
        Expr *inner_let = make_let("g", make_var("f"), g_use);
        Expr *expr4 = make_let("f", f_body, inner_let);
        
        run_inference("let f = λx.x in let g = f in g 42", expr4);
        free_ast(expr4);
    }

    printf("\n═══════════════════════════════════════════════════════════════\n");
    printf("  演示完成！\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    return 0;
}

