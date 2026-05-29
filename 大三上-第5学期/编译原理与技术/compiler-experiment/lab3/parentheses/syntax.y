%{
    #include"lex.yy.c"
    void yyerror(const char *s);
    int result;
%}

%token LP RP LB RB LC RC

%%
StringList
    : /* empty */
    | StringList String
    ;

String
    : LP StringList RP
    | LB StringList RB
    | LC StringList RC
    ;
%%
 
void yyerror(const char *s){
    result = 0;
}

int validParentheses(char *expr){
    result = 1;
    yy_scan_string(expr);
    yyparse();
    return result;
}
