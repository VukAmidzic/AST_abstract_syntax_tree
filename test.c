#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

#define AST_NEW(tag, ...) ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})

int main() {
        AST *term = AST_NEW(AST_MAIN,
        AST_NEW(AST_ADD,
        AST_NEW(AST_NUMBER, 4),
        AST_NEW(AST_ADD,
            AST_NEW(AST_MUL, 
            AST_NEW(AST_NUMBER, 2), 
            AST_NEW(AST_NUMBER, 10),
            ),
            AST_NEW(AST_MUL,
            AST_NEW(AST_NUMBER, 3),
            AST_NEW(AST_ADD,
                AST_NEW(AST_NUMBER, 5),
                AST_NEW(AST_NUMBER, 1),
            ),
            ),
        ),
        ),
    );
    
    ast_print(term);
    putchar('\n');
    
    return 0;
}
