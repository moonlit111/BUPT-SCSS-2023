/**
 * parser.y - Core-ML 语法分析器（Bison）
 * 用于 HM 多态类型推导系统
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/ast.h"

extern int yylex(void);
extern int yylineno;
extern FILE *yyin;
void yyerror(const char *s);

Expr *parsed_ast = NULL;
%}

%union {
    int ival;
    int bval;
    char *sval;
    Expr *expr;
}

%token <ival> INT_CONST
%token <bval> BOOL_CONST
%token <sval> IDENT
%token LET IN FUN LAMBDA_SYM
%token IF THEN ELSE
%token ARROW DARROW EQ
%token LPAREN RPAREN COMMA DOT

%type <expr> program expr simple_expr app_expr atom_expr

/* 运算符优先级（从低到高） */
%right IN
%right DARROW DOT
%left APP

%start program

%%

program
    : expr                      { parsed_ast = $1; }
    ;

expr
    /* let x = e1 in e2 */
    : LET IDENT EQ expr IN expr { $$ = make_let($2, $4, $6); free($2); }
    
    /* λx. e 或 \x. e */
    | LAMBDA_SYM IDENT DOT expr { $$ = make_lambda($2, $4); free($2); }
    
    /* fun x => e */
    | FUN IDENT DARROW expr     { $$ = make_lambda($2, $4); free($2); }
    
    /* if e1 then e2 else e3 (简化为函数应用) */
    | IF expr THEN expr ELSE expr { 
        /* 暂不实现 if-then-else，返回错误 */
        fprintf(stderr, "if-then-else not yet supported\n");
        $$ = $4;  
      }
    
    | app_expr                  { $$ = $1; }
    ;

app_expr
    /* 函数应用：左结合 */
    : app_expr atom_expr %prec APP  { $$ = make_app($1, $2); }
    | atom_expr                     { $$ = $1; }
    ;

atom_expr
    /* 整数常量 */
    : INT_CONST                 { $$ = make_const_int($1); }
    
    /* 布尔常量 */
    | BOOL_CONST                { $$ = make_const_bool($1); }
    
    /* 变量 */
    | IDENT                     { $$ = make_var($1); free($1); }
    
    /* 括号表达式 */
    | LPAREN expr RPAREN        { $$ = $2; }
    
    /* 二元组 (e1, e2) */
    | LPAREN expr COMMA expr RPAREN { $$ = make_pair($2, $4); }
    ;

%%

/**
 * 从字符串解析表达式
 */
Expr* parse_string(const char *input);

/**
 * 从文件解析表达式
 */
Expr* parse_file(FILE *file) {
    yyin = file;
    parsed_ast = NULL;
    if (yyparse() == 0) {
        return parsed_ast;
    }
    return NULL;
}

