#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

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
        case AST_SUB: {
            struct AST_ADD data = ast.data.AST_ADD;
            printf("(");
            ast_print(data.left);
            printf("-");
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
        case AST_IDIV: {
            struct AST_IDIV data = ast.data.AST_IDIV;
            printf("(");
            ast_print(data.left);
            printf("/");
            ast_print(data.right);
            printf(")");
            return;
        }
        /*case AST_CMP: {
            struct AST_CMP data = ast.data.AST_CMP;
            printf("(");
            ast_print(data.left);
            
            if (strcmp(data.type, "great") == 0) {
                printf(">");
            }
            else if (strcmp(data.type, "less") == 0) {
                printf("<");
            } 
            else if (strcmp(data.type, "eq") == 0) {
                printf("==");
            }
            else if (strcmp(data.type, "neq") == 0) {
                printf("!=");
            }
            else if (strcmp(data.type, "leq") == 0) {
                printf("<=");
            }
            else if (strcmp(data.type, "geq") == 0) {
                printf(">=");
            }
            
            ast_print(data.right);
            printf(")");
            return;
        }*/
        default: {break;}
    }
}

void ast_asm_print(AST* ptr, FILE* asm_file) {
    AST ast = *ptr;
    
    switch (ast.tag) {
        case AST_MAIN: {
            struct AST_MAIN data = ast.data.AST_MAIN;
            fprintf(asm_file, ".intel_syntax noprefix\n");
            fprintf(asm_file, ".extern printf\n");
            fprintf(asm_file, ".data\n");
            fprintf(asm_file, "     format: .asciz \"");
            fprintf(asm_file, "%c", 37); //37 is ASCII code for '%'
            fprintf(asm_file, "d\\n\"\n");
            fprintf(asm_file, ".text\n");
            fprintf(asm_file, ".global main\n");
            fprintf(asm_file, "main:\n");
            fprintf(asm_file, "     push rbx\n");
            ast_asm_print(data.body, asm_file);
            fprintf(asm_file, "     lea rdi, format\n");
            fprintf(asm_file, "     mov rsi, rax\n");           
            fprintf(asm_file, "     xor rax, rax\n"); 
            fprintf(asm_file, "     call printf\n");
            fprintf(asm_file, "     pop rbx\n");
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
        case AST_SUB: {
            struct AST_ADD data = ast.data.AST_ADD;
            ast_asm_print(data.left, asm_file);
            fprintf(asm_file, "     push rax\n");
            ast_asm_print(data.right, asm_file);
            fprintf(asm_file, "     pop rbx\n");
            fprintf(asm_file, "     sub rax, rbx\n");
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
        case AST_IDIV: {
            struct AST_IDIV data = ast.data.AST_IDIV;
            ast_asm_print(data.left, asm_file);
            fprintf(asm_file, "     push rax\n");
            ast_asm_print(data.right, asm_file);
            fprintf(asm_file, "     pop rbx\n");
            fprintf(asm_file, "     push rax\n");
            fprintf(asm_file, "     mov rax, rbx\n");
            fprintf(asm_file, "     pop rbx\n");
            fprintf(asm_file, "     xor rdx, rdx\n");
            fprintf(asm_file, "     idiv rbx\n");
            return;
        }
        //case AST_CMP: {TODO}
        default: {break;}
    }
}
