#ifndef _AST_H_
#define _AST_H_

#include <stdio.h>

typedef struct AST AST; 
 
struct AST {
    enum {
        AST_MAIN,
        AST_NUMBER,
        AST_ADD,
        AST_SUB,
        AST_MUL,
        AST_IDIV
    } tag;
    union {
        struct AST_MAIN { AST* body; } AST_MAIN;
        struct AST_NUMBER { int number; } AST_NUMBER;
        struct AST_ADD {
            AST* left;
            AST* right;
        } AST_ADD;
        struct AST_SUB {
            AST* left;
            AST* right;
        } AST_SUB;
        struct AST_MUL {
            AST* left;
            AST* right;
        } AST_MUL;
        struct AST_IDIV {
            AST* left;
            AST* right;
        } AST_IDIV;
    } data;
};    

AST* ast_new(AST ast);
void ast_asm_print(AST* ptr, FILE* asm_file);
void ast_print(AST* ptr);

#endif
