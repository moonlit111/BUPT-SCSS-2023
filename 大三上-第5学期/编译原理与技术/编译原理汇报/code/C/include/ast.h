/**
 * ast.h - 抽象语法树构造
 */

#ifndef HM_AST_H
#define HM_AST_H

#include "types.h"

/*=============================================================
 * AST 构造器
 *=============================================================*/

/**
 * 创建整数常量节点
 */
Expr* make_const_int(int value);

/**
 * 创建布尔常量节点
 */
Expr* make_const_bool(bool value);

/**
 * 创建变量节点
 */
Expr* make_var(const char *name);

/**
 * 创建 lambda 表达式节点
 * λparam. body
 */
Expr* make_lambda(const char *param, Expr *body);

/**
 * 创建函数应用节点
 * func arg
 */
Expr* make_app(Expr *func, Expr *arg);

/**
 * 创建 let 表达式节点
 * let name = bind_expr in body
 */
Expr* make_let(const char *name, Expr *bind_expr, Expr *body);

/**
 * 创建二元组节点
 * (fst, snd)
 */
Expr* make_pair(Expr *fst, Expr *snd);

/*=============================================================
 * AST 操作
 *=============================================================*/

/**
 * 打印 AST
 */
void print_ast(Expr *expr);

/**
 * 将 AST 转换为字符串
 */
char* ast_to_string(Expr *expr);

/**
 * 释放 AST 内存
 */
void free_ast(Expr *expr);

#endif // HM_AST_H

