/**
 * lexer.l - Core-ML 词法分析器（Flex）
 * 用于 HM 多态类型推导系统
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/types.h"
#include "../include/ast.h"
#include "parser.tab.h"

extern int yylineno;
%}

%option noyywrap
%option yylineno

DIGIT       [0-9]
ALPHA       [a-zA-Z_]
ALPHANUM    [a-zA-Z0-9_]

%%

[ \t\n\r]+              { /* 跳过空白 */ }
"//".*                  { /* 跳过单行注释 */ }
"(*"([^*]|"*"+[^*)])*"*"+")" { /* 跳过多行注释 */ }

"let"                   { return LET; }
"in"                    { return IN; }
"fun"                   { return FUN; }
"fn"                    { return FUN; }
"true"                  { yylval.bval = 1; return BOOL_CONST; }
"false"                 { yylval.bval = 0; return BOOL_CONST; }
"if"                    { return IF; }
"then"                  { return THEN; }
"else"                  { return ELSE; }

"λ"|"\\"                { return LAMBDA_SYM; }
"->"                    { return ARROW; }
"=>"                    { return DARROW; }
"="                     { return EQ; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
","                     { return COMMA; }
"."                     { return DOT; }

{DIGIT}+                { 
                          yylval.ival = atoi(yytext); 
                          return INT_CONST; 
                        }

{ALPHA}{ALPHANUM}*      { 
                          yylval.sval = strdup(yytext); 
                          return IDENT; 
                        }

.                       { 
                          fprintf(stderr, "Line %d: Unknown character '%s'\n", 
                                  yylineno, yytext); 
                        }

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}

