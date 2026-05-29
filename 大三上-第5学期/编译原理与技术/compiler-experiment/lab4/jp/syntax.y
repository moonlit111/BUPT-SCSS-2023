%{
    #include"lex.yy.c"
    void yyerror(const char*);
%}

%token LC RC LB RB COLON COMMA
%token STRING NUMBER LEADINGZERO
%token TRUE FALSE VNULL
%%

Json:
      Value
    | Value COMMA error { printf("Comma after the close, recovered"); }
    | Value RB error { printf("Extra close, recovered"); }
    ;
Value:
      Object
    | Array
    | STRING
    | NUMBER
    | TRUE
    | FALSE
    | VNULL
    ;
Object:
      LC RC
    | LC Members RC
    | Object Value error { puts("Extra value after close, recovered"); }
    | LC Values RC error { puts("Comma instead of colon, recovered");}
    | LC Member COMMA error { puts("Comma instead if closing brace, recovered");}
    ;
Members:
      Member
    | Members COMMA Member
    | Members COMMA error { puts("Extra comma, recovered"); }
    ;
Member:
      STRING COLON Value
    | STRING COLON error Value { puts("Double colon, recovered"); }
    | STRING Value error { puts("Missing colon, recovered"); }
    | STRING COLON LEADINGZERO error { puts("Numbers cannot have leading zeroes, recovered"); }
    ;
Array:
      LB RB
    | LB Values RB
    | LB Values RC error { puts("mismatch, recovered"); }
    | LB Member RB error { puts("Colon instead of comma, recovered"); }
    | LB Values error { puts("Unclosed array, recovered"); }
    ;
Values:
      Value
    | Values COMMA Value
    | Values COMMA error { puts("extra comma, recovered"); }
    | Values COMMA COMMA error { puts("double extra comma, recovered"); }
    | COMMA Values error { puts("<-- missing value, recovered"); }
    ;
%%

void yyerror(const char *s){
    printf("syntax error: ");
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    }
    else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    yyparse();
    return 0;
}