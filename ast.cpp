#include "ast.hpp"
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <string>
#include <map>
#include <vector>
#include <utility>

const int VAR_STEP = 4;

NumNode::NumNode(int _num) { num = _num; };

VarNode::VarNode(std::string _var_name) { var_name = _var_name; };

BinaryNode::BinaryNode(Tag _tag, ASTNode* _left, ASTNode* _right) {
    tag = _tag;
    left = _left;
    right = _right;
};

MainNode::MainNode(ASTNode* _next) {
    next = _next;
};

AssignNode::AssignNode(std::string _var_name, ASTNode* _assign_val, ASTNode* _next) {
    var_name = _var_name;
    assign_val = _assign_val;
    next = _next;
};

PrintNode::PrintNode(ASTNode* _print_val, ASTNode* _next) {
    print_val = _print_val;
    next = _next;
};

IfElseNode::IfElseNode(std::vector<std::pair<ASTNode*, ASTNode*>> _conds, ASTNode* _next) {
    conds = _conds;
    next = _next;
};

void traverse_tree(size_t lvl, ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp, int* var_counter) {
    auto* num_node = dynamic_cast<NumNode*>(ptr);
    auto* var_node = dynamic_cast<VarNode*>(ptr);
    auto* bin_op_node = dynamic_cast<BinaryNode*>(ptr);
    auto* main_node = dynamic_cast<MainNode*>(ptr);
    auto* assign_node = dynamic_cast<AssignNode*>(ptr);
    auto* print_node = dynamic_cast<PrintNode*>(ptr);
    auto* if_else_node = dynamic_cast<IfElseNode*>(ptr);
    
    if (num_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        std::cout << "#NUM: " << num_node->num << std::endl;
    }
    else if (var_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        std::cout << "#VAR: " << var_node->var_name << std::endl;
    }
    else if (bin_op_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        
        switch (bin_op_node->tag) {
            case _ADD_ : {
                std::cout << "#ADD: " << std::endl;
                break;
            }
            case _SUB_ : {
                std::cout << "#SUB: " << std::endl;
                break;
            }
            case _MUL_ : {
                std::cout << "#MUL: " << std::endl;
                break;
            }
            case _DIV_ : {
                std::cout << "#DIV: " << std::endl;
                break;
            }
            case _SHL_ : {
                std::cout << "#SHL: " << std::endl;
                break;
            }
            case _SHR_ : {
                std::cout << "#SHR: " << std::endl;
                break;
            }
            case _AND_ : {
                std::cout << "#AND: " << std::endl;
                break;
            }
            case _OR_ : {
                std::cout << "#OR: " << std::endl;
                break;
            }
            case _NOT_ : {
                std::cout << "#NOT: " << std::endl;
                break;
            }
            case _LESS_ : {
                std::cout << "#LESS: " << std::endl;
                break;
            }
            case _GREAT_ : {
                std::cout << "#GREAT: " << std::endl;
                break;
            }
            case _EQ_ : {
                std::cout << "#EQ: " << std::endl;
                break;
            }
            case _NEQ_ : {
                std::cout << "#NEQ: " << std::endl;
                break;
            }
            case _LEQ_ : {
                std::cout << "#LEQ: " << std::endl;
                break;
            }
            case _GEQ_ : {
                std::cout << "#GEQ: " << std::endl;
                break;
            }
            
            default: break;
        }
        traverse_tree(lvl + 1, bin_op_node->left, mp, var_counter);
        traverse_tree(lvl + 1, bin_op_node->right, mp, var_counter);
    }
    else if (main_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        std::cout << "#MAIN: " << std::endl;
        traverse_tree(lvl, main_node->next, mp, var_counter);
    }
    else if (assign_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        
        int tmp = expr_eval(assign_node->assign_val, mp);
        auto it = mp.find(assign_node->var_name);
        if (it != mp.end()) {
            mp[assign_node->var_name].first = tmp;
        }
        else {
            mp[assign_node->var_name] = {tmp, *var_counter};
            *var_counter += VAR_STEP;
        }
        std::cout << "#ASSIGN: " << assign_node->var_name << " " << mp[assign_node->var_name].first << std::endl;
        traverse_tree(lvl, assign_node->next, mp, var_counter);
    }
    else if (print_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        int print_value = expr_eval(print_node->print_val, mp);
        std::cout << "#PRINT: " << print_value << std::endl;
        traverse_tree(lvl, print_node->next, mp, var_counter);
    }
    else if (if_else_node) {
        for (size_t i = 0; i < lvl; ++i) {
            std::cout << "\t";
        }
        int n = if_else_node->conds.size();
        bool found_true = false;
        int i;
        for (i = 1; i < n; ++i) {
            if (expr_eval(if_else_node->conds[i].first, mp)) {
                found_true = true;
                break;
            }
        }
        
        if (found_true) {
            traverse_tree(lvl + 1, if_else_node->conds[i].second, mp, var_counter);
        }
        else {
            traverse_tree(lvl + 1, if_else_node->conds[0].second, mp, var_counter);
        }
        
        traverse_tree(lvl, if_else_node->next, mp, var_counter);
    }
};

int expr_eval(ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp) {
    int result = 0;
    
    auto* num_node = dynamic_cast<NumNode*>(ptr);
    auto* var_node = dynamic_cast<VarNode*>(ptr);
    auto* bin_op_node = dynamic_cast<BinaryNode*>(ptr);
    
    if (num_node) {
        result = num_node->num;
    }
    else if (var_node) {
        auto found = mp.find(var_node->var_name);
        if (found == mp.end()) {
            std::cerr << "Variable " << "'" + var_node->var_name + "'" << " not defined!!" << std::endl;
            exit(EXIT_FAILURE);
        }
        result = (found->second).first;
    }
    else if (bin_op_node) {
        switch (bin_op_node->tag) {
            case _ADD_ : {
                result = expr_eval(bin_op_node->left, mp) + expr_eval(bin_op_node->right, mp);
                break;
            }
            case _SUB_ : {
                result = expr_eval(bin_op_node->left, mp) - expr_eval(bin_op_node->right, mp);
                break;
            }
            case _MUL_ : {
                result = expr_eval(bin_op_node->left, mp) * expr_eval(bin_op_node->right, mp);
                break;
            }
            case _DIV_ : {
                result = expr_eval(bin_op_node->left, mp) / expr_eval(bin_op_node->right, mp);
                break;
            }
            case _SHL_ : {
                result = expr_eval(bin_op_node->left, mp) << expr_eval(bin_op_node->right, mp);
                break;
            }
            case _SHR_ : {
                result = expr_eval(bin_op_node->left, mp) >> expr_eval(bin_op_node->right, mp);
                break;
            }
            case _AND_ : {
                result = expr_eval(bin_op_node->left, mp) && expr_eval(bin_op_node->right, mp);
                break;
            }
            case _OR_ : {
                result = expr_eval(bin_op_node->left, mp) || expr_eval(bin_op_node->right, mp);
                break;
            }
            case _NOT_ : {
                result = !expr_eval(bin_op_node->right, mp);
                break;
            }
            case _LESS_ : {
                result = expr_eval(bin_op_node->left, mp) < expr_eval(bin_op_node->right, mp);
                break;
            }
            case _GREAT_ : {
                result = expr_eval(bin_op_node->left, mp) > expr_eval(bin_op_node->right, mp);
                break;
            }
            case _EQ_ : {
                result = expr_eval(bin_op_node->left, mp) == expr_eval(bin_op_node->right, mp);
                break;
            }
            case _NEQ_ : {
                result = expr_eval(bin_op_node->left, mp) != expr_eval(bin_op_node->right, mp);
                break;
            }
            case _LEQ_ : {
                result = expr_eval(bin_op_node->left, mp) <= expr_eval(bin_op_node->right, mp);
                break;
            }
            case _GEQ_ : {
                result = expr_eval(bin_op_node->left, mp) >= expr_eval(bin_op_node->right, mp);
                break;
            }
            default: break;
        }
    }
    
    return result;
};

void print_asm(ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp) {
    auto* num_node = dynamic_cast<NumNode*>(ptr);
    auto* var_node = dynamic_cast<VarNode*>(ptr);
    auto* bin_op_node = dynamic_cast<BinaryNode*>(ptr);
    auto* main_node = dynamic_cast<MainNode*>(ptr);
    auto* assign_node = dynamic_cast<AssignNode*>(ptr);
    auto* print_node = dynamic_cast<PrintNode*>(ptr);
    auto* if_else_node = dynamic_cast<IfElseNode*>(ptr);
    
    if (num_node) {
        std::cout << "  mov rax, " << num_node->num << std::endl;
    }
    else if (var_node) {
        std::cout << "  mov rax, QWORD PTR [rbp-" << 2 * mp[var_node->var_name].second << "]" << std::endl;
    }
    else if (bin_op_node) {
        switch (bin_op_node->tag) {
            case _ADD_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  add rax, rbx" << std::endl;
                break;
            }
            case _SUB_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  sub rax, rbx" << std::endl;
                break;
            }
            case _MUL_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  imul rax, rbx" << std::endl;
                break;
            }
            case _DIV_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->left, mp);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  push rax" << std::endl;
                std::cout << "  mov rax, rbx" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  cqo" << std::endl;
                std::cout << "  xor rdx, rdx" << std::endl;
                std::cout << "  idiv rbx" << std::endl;
                break;
            }
            case _SHL_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  shl rax, " << expr_eval(bin_op_node->right, mp) << std::endl;
                break;
            }
            case _SHR_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  shr rax, " << expr_eval(bin_op_node->right, mp) << std::endl;
                break;
            }
            case _AND_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  and rax, rbx" << std::endl;
                break;
            }
            case _OR_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  or rax, rbx" << std::endl;
                break;
            }
            case _NOT_ : {
                print_asm(bin_op_node->right, mp);
                std::cout << "  not rax" << std::endl;
                break;
            }
            case _LESS_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_less" << std::endl;  
                break;
            }
            case _GREAT_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_great" << std::endl; 
                break;
            }
            case _EQ_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_eq" << std::endl; 
                break;
            }
            case _NEQ_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_neq" << std::endl; 
                break;
            }
            case _LEQ_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_leq" << std::endl; 
                break;
            }
            case _GEQ_ : {
                print_asm(bin_op_node->left, mp);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_geq" << std::endl; 
                break;
            }
            
            default: break;
        }
    }
    else if (main_node) {
        std::cout << ".intel_syntax noprefix" << std::endl;
        std::cout << ".data" << std::endl;
        std::cout << "  format: .asciz \"\%d\\n\"" << std::endl;
        std::cout << ".text\n" << std::endl;
        std::cout << ".global main" << std::endl;
        std::cout << "main:" << std::endl;
        std::cout << "  enter " << 8 * mp.size() << ", 0" << std::endl;
        print_asm(main_node->next, mp);
        std::cout << "  leave" << std::endl;
        std::cout << "  ret\n" << std::endl;
    }
    else if (assign_node) {
        print_asm(assign_node->assign_val, mp);
        std::cout << "  mov QWORD PTR [rbp-" << 2 * mp[assign_node->var_name].second << "], rax" << std::endl;
        print_asm(assign_node->next, mp);
    }
    else if (print_node) {
        print_asm(print_node->print_val, mp);
        std::cout << "  lea rdi, format" << std::endl;
        std::cout << "  mov rsi, rax" << std::endl;
        std::cout << "  xor rax, rax" << std::endl;
        std::cout << "  call printf" << std::endl;
        print_asm(print_node->next, mp);
    }
    else if (if_else_node) {
        int n = if_else_node->conds.size();
        bool found_true = false;
        int i;
        for (i = 1; i < n; ++i) {
            if (expr_eval(if_else_node->conds[i].first, mp)) {
                found_true = true;
                break;
            }
        }
        
        if (found_true) {
            print_asm(if_else_node->conds[i].second, mp);
        }
        else {
            print_asm(if_else_node->conds[0].second, mp);
        }
        
        print_asm(if_else_node->next, mp);
    }
};
