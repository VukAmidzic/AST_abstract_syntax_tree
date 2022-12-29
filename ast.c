#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST* ast_new(AST ast) {
    AST* ptr = malloc(sizeof(AST));
    
    if (ptr) *ptr = ast;
    
    return ptr;
}

void ast_print(AST* ptr) {
    AST ast = *ptr;
    
    switch (ast.tag) {
        case AST_MAIN: {
            struct AST_MAIN data = ast.data.AST_MAIN;
            printf("main() = ");
            ast_print(data.body);
            return;
        }
        case AST_NUMBER: {
            struct AST_NUMBER data = ast.data.AST_NUMBER;
            printf("%d", data.number);
            return;
        }
        case AST_ADD: {
            struct AST_ADD data = ast.data.AST_ADD;
            printf("(");
            ast_print(data.left);
            printf("+");
            ast_print(data.right);
            printf(")");
            return;
        }
        case AST_MUL: {
            struct AST_MUL data = ast.data.AST_MUL;
            printf("(");
            ast_print(data.left);
            printf("*");
            ast_print(data.right);
            printf(")");
            return;
        }
    }
}

void ast_asm_print(AST* ptr, FILE* asm_file) {
    AST ast = *ptr;
    
    switch (ast.tag) {
        case AST_MAIN: {
            struct AST_MAIN data = ast.data.AST_MAIN;
            fprintf(asm_file, ".intel_syntax noprefix\n");
            fprintf(asm_file, ".global main\n");
            fprintf(asm_file, ".text\n");
            fprintf(asm_file, "main:\n");
            ast_asm_print(data.body, asm_file);
            fprintf(asm_file, "     ret\n");
            fprintf(asm_file, "\n");
            return;
        }
        case AST_NUMBER: {
            struct AST_NUMBER data = ast.data.AST_NUMBER;
            fprintf(asm_file, "     mov rax, %d\n", data.number);
            return;
        }
        case AST_ADD: {
            struct AST_ADD data = ast.data.AST_ADD;
            ast_asm_print(data.left, asm_file);
            fprintf(asm_file, "     push rax\n");
            ast_asm_print(data.right, asm_file);
            fprintf(asm_file, "     pop rbx\n");
            fprintf(asm_file, "     add rax, rbx\n");
            return;
        }
        case AST_MUL: {
            struct AST_MUL data = ast.data.AST_MUL;
            ast_asm_print(data.left, asm_file);
            fprintf(asm_file, "     push rax\n");
            ast_asm_print(data.right, asm_file);
            fprintf(asm_file, "     pop rbx\n");
            fprintf(asm_file, "     mul rbx\n");
            return;
        }
    }
}
