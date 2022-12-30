#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

#define AST_NEW(tag, ...) ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})

int main(int argc, char** argv) {
    FILE* asm_file = fopen(argv[1], "w");
    if (asm_file == NULL) {
        fprintf(stderr, "Can't open file...\n");
        return 1;
    }
    
    //example term = (5 + 1) * 2 / 3 + 1
    AST* term = AST_NEW(AST_MAIN,
        AST_NEW(AST_ADD, 
            AST_NEW(AST_IDIV, 
                AST_NEW(AST_MUL,
                    AST_NEW(AST_ADD, 
                        AST_NEW(AST_NUMBER, 5),
                        AST_NEW(AST_NUMBER, 1)
                    ),
                    AST_NEW(AST_NUMBER, 2)
                ),    
                AST_NEW(AST_NUMBER, 3)
            ),
            AST_NEW(AST_NUMBER, 1)
        )
    );

    ast_print(term);
    putchar('\n');
    ast_asm_print(term, asm_file);    
        
    return 0;
}
