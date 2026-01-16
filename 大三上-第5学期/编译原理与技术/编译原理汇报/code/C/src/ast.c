/**
 * ast.c - AST 构造与操作实现
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/ast.h"

/*=============================================================
 * AST 构造器
 *=============================================================*/
Expr* make_const_int(int value) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_CONST_INT;
    e->int_val = value;
    return e;
}

Expr* make_const_bool(bool value) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_CONST_BOOL;
    e->bool_val = value;
    return e;
}

Expr* make_var(const char *name) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_VAR;
    e->var_name = strdup(name);
    return e;
}

Expr* make_lambda(const char *param, Expr *body) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_LAMBDA;
    e->lambda.param_name = strdup(param);
    e->lambda.body = body;
    return e;
}

Expr* make_app(Expr *func, Expr *arg) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_APP;
    e->app.func = func;
    e->app.arg = arg;
    return e;
}

Expr* make_let(const char *name, Expr *bind_expr, Expr *body) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_LET;
    e->let.let_name = strdup(name);
    e->let.bind_expr = bind_expr;
    e->let.let_body = body;
    return e;
}

Expr* make_pair(Expr *fst, Expr *snd) {
    Expr *e = (Expr*)malloc(sizeof(Expr));
    e->kind = EXPR_PAIR;
    e->pair.fst = fst;
    e->pair.snd = snd;
    return e;
}

/*=============================================================
 * AST 打印
 *=============================================================*/
static void print_ast_helper(Expr *expr, int indent) {
    for (int i = 0; i < indent; i++) printf("  ");

    if (expr == NULL) {
        printf("(null)\n");
        return;
    }

    switch (expr->kind) {
        case EXPR_CONST_INT:
            printf("INT(%d)\n", expr->int_val);
            break;
        case EXPR_CONST_BOOL:
            printf("BOOL(%s)\n", expr->bool_val ? "true" : "false");
            break;
        case EXPR_VAR:
            printf("VAR(%s)\n", expr->var_name);
            break;
        case EXPR_LAMBDA:
            printf("LAMBDA %s =>\n", expr->lambda.param_name);
            print_ast_helper(expr->lambda.body, indent + 1);
            break;
        case EXPR_APP:
            printf("APP\n");
            print_ast_helper(expr->app.func, indent + 1);
            print_ast_helper(expr->app.arg, indent + 1);
            break;
        case EXPR_LET:
            printf("LET %s =\n", expr->let.let_name);
            print_ast_helper(expr->let.bind_expr, indent + 1);
            for (int i = 0; i < indent; i++) printf("  ");
            printf("IN\n");
            print_ast_helper(expr->let.let_body, indent + 1);
            break;
        case EXPR_PAIR:
            printf("PAIR\n");
            print_ast_helper(expr->pair.fst, indent + 1);
            print_ast_helper(expr->pair.snd, indent + 1);
            break;
    }
}

void print_ast(Expr *expr) {
    print_ast_helper(expr, 0);
}

/*=============================================================
 * AST 转字符串
 *=============================================================*/
static void ast_to_string_helper(Expr *expr, char *buf, int *pos, int max) {
    if (expr == NULL || *pos >= max - 1) return;

    switch (expr->kind) {
        case EXPR_CONST_INT:
            *pos += snprintf(buf + *pos, max - *pos, "%d", expr->int_val);
            break;
        case EXPR_CONST_BOOL:
            *pos += snprintf(buf + *pos, max - *pos, "%s",
                           expr->bool_val ? "true" : "false");
            break;
        case EXPR_VAR:
            *pos += snprintf(buf + *pos, max - *pos, "%s", expr->var_name);
            break;
        case EXPR_LAMBDA:
            *pos += snprintf(buf + *pos, max - *pos, "(λ%s. ",
                           expr->lambda.param_name);
            ast_to_string_helper(expr->lambda.body, buf, pos, max);
            buf[(*pos)++] = ')';
            break;
        case EXPR_APP:
            buf[(*pos)++] = '(';
            ast_to_string_helper(expr->app.func, buf, pos, max);
            buf[(*pos)++] = ' ';
            ast_to_string_helper(expr->app.arg, buf, pos, max);
            buf[(*pos)++] = ')';
            break;
        case EXPR_LET:
            *pos += snprintf(buf + *pos, max - *pos, "(let %s = ",
                           expr->let.let_name);
            ast_to_string_helper(expr->let.bind_expr, buf, pos, max);
            *pos += snprintf(buf + *pos, max - *pos, " in ");
            ast_to_string_helper(expr->let.let_body, buf, pos, max);
            buf[(*pos)++] = ')';
            break;
        case EXPR_PAIR:
            buf[(*pos)++] = '(';
            ast_to_string_helper(expr->pair.fst, buf, pos, max);
            *pos += snprintf(buf + *pos, max - *pos, ", ");
            ast_to_string_helper(expr->pair.snd, buf, pos, max);
            buf[(*pos)++] = ')';
            break;
    }
}

char* ast_to_string(Expr *expr) {
    static char buf[512];
    int pos = 0;
    ast_to_string_helper(expr, buf, &pos, 512);
    buf[pos] = '\0';
    return buf;
}

/*=============================================================
 * 内存释放
 *=============================================================*/
void free_ast(Expr *expr) {
    if (expr == NULL) return;

    switch (expr->kind) {
        case EXPR_CONST_INT:
        case EXPR_CONST_BOOL:
            break;
        case EXPR_VAR:
            free(expr->var_name);
            break;
        case EXPR_LAMBDA:
            free(expr->lambda.param_name);
            free_ast(expr->lambda.body);
            break;
        case EXPR_APP:
            free_ast(expr->app.func);
            free_ast(expr->app.arg);
            break;
        case EXPR_LET:
            free(expr->let.let_name);
            free_ast(expr->let.bind_expr);
            free_ast(expr->let.let_body);
            break;
        case EXPR_PAIR:
            free_ast(expr->pair.fst);
            free_ast(expr->pair.snd);
            break;
    }
    free(expr);
}
