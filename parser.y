%{
    #include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include "ast.h"
    
    #define YYDEBUG 1
    
    extern int yylex();
    void yyerror(char* s) {
        fprintf(stderr, "%s\n", s);
    }
    
    AST* term = NULL;
%}

%union {
    int number;
    AST* node;
}

%type<node> E T F program
%token<number> NUM 

%left PLUS MINUS MUL DIV
%token LP RP
//%token GREAT LESS EQ NEQ GEQ LEQ

%start program
%%
program     : E {
                $$ = $1;
                term = AST_NEW(AST_MAIN, $$);
            }
            | {}
;

E   : E PLUS T {$$ = AST_NEW(AST_ADD, $1, $3);} 
    | E MINUS T {$$ = AST_NEW(AST_SUB, $1, $3);}
    | T {$$ = $1;}
;

T   : T MUL F {$$ = AST_NEW(AST_MUL, $1, $3);}
    | T DIV F {$$ = AST_NEW(AST_IDIV, $1, $3);}
    | F {$$ = $1;}
;

F   : LP E RP {$$ = $2;}
    | NUM {$$ = AST_NEW(AST_NUMBER, $1);}
;

%%

int main(int argc, char* argv[]) {
    FILE* asm_file = fopen(argv[1], "w");
    yydebug = 0;
    
    yyparse();
    ast_print(term);
    ast_asm_print(term, asm_file);
    putchar('\n');

    return 0;
}
