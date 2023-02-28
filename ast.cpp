#include "ast.hpp"
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <type_traits>
#include <string>
#include <map>
#include <vector>
#include <utility>

/* NOTE 
 * most of the utilities work
 * 
 * FIXME 
 * fix counting with main_counter
 * 
 * 
 */

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

IfElseNode::IfElseNode(int _if_num, std::vector<std::pair<ASTNode*, ASTNode*>> _conds, std::vector<int> _cond_num, ASTNode* _next) {
    if_num = _if_num;
    conds = _conds;
    cond_num = _cond_num;
    next = _next;
};

WhileNode::WhileNode(int _while_num, ASTNode* _cond, ASTNode* _stmts, ASTNode* _next) {
    while_num = _while_num;
    cond = _cond; 
    stmts = _stmts; 
    next = _next;
};

void traverse_tree(ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp, int* var_counter, 
    int* loop_counter, int* if_counter, int* cond_counter) {
    auto* num_node = dynamic_cast<NumNode*>(ptr);
    auto* var_node = dynamic_cast<VarNode*>(ptr);
    auto* bin_op_node = dynamic_cast<BinaryNode*>(ptr);
    auto* main_node = dynamic_cast<MainNode*>(ptr);
    auto* assign_node = dynamic_cast<AssignNode*>(ptr);
    auto* print_node = dynamic_cast<PrintNode*>(ptr);
    auto* if_else_node = dynamic_cast<IfElseNode*>(ptr);
    auto* while_node = dynamic_cast<WhileNode*>(ptr);
    
    if (num_node) { return; }
    else if (var_node) { return; }
    else if (bin_op_node) {
        traverse_tree(bin_op_node->left, mp, var_counter, loop_counter, if_counter, cond_counter);
        traverse_tree(bin_op_node->right, mp, var_counter, loop_counter, if_counter, cond_counter);
    }
    else if (main_node) {
        traverse_tree(main_node->next, mp, var_counter, loop_counter, if_counter, cond_counter);
    }
    else if (assign_node) {
        int tmp = expr_eval(assign_node->assign_val, mp);
        auto it = mp.find(assign_node->var_name);
        if (it != mp.end()) {
            mp[assign_node->var_name].first = tmp;
        }
        else {
            mp[assign_node->var_name] = {tmp, *var_counter};
            *var_counter += VAR_STEP;
        }
        traverse_tree(assign_node->next, mp, var_counter, loop_counter, if_counter, cond_counter);
    }
    else if (print_node) {
        traverse_tree(print_node->next, mp, var_counter, loop_counter, if_counter, cond_counter);
    }
    else if (if_else_node) {
        int n = if_else_node->conds.size();
        
        if (n == 1) {
            if_else_node->if_num = *if_counter;
            if_else_node->cond_num.push_back(*cond_counter);
            
            *if_counter += 1;
            *cond_counter += 1;
            
            std::cout << "#IF-ELSE:" << if_else_node->if_num << std::endl;
            std::cout << "#CONDS: ";
            for (int i : if_else_node->cond_num) {
                std::cout << "<cond," << i << ">, ";
            }
            std::cout << std::endl;
            
            traverse_tree(if_else_node->conds[0].first, mp, var_counter, loop_counter, if_counter, cond_counter);
            traverse_tree(if_else_node->conds[0].second, mp, var_counter, loop_counter, if_counter, cond_counter);
            traverse_tree(if_else_node->next, mp, var_counter, loop_counter, if_counter, cond_counter);
        }
        else {
            if_else_node->if_num = *if_counter;
            for (int i = 1; i < n; ++i) {
                if_else_node->cond_num.push_back(*cond_counter + i - 1);
                traverse_tree(if_else_node->conds[i].first, mp, var_counter, loop_counter, if_counter, cond_counter);
            }
            if_else_node->cond_num.push_back(*cond_counter + n - 1);
            *cond_counter += n;
            
            for (int i = 1; i < n; ++i) {
                *if_counter += 1;
                traverse_tree(if_else_node->conds[i].second, mp, var_counter, loop_counter, if_counter, cond_counter);
            }
            traverse_tree(if_else_node->conds[0].second, mp, var_counter, loop_counter, if_counter, cond_counter);
            
            std::cout << "#IF-ELSE:" << if_else_node->if_num << std::endl;
            std::cout << "#CONDS: ";
            for (int i : if_else_node->cond_num) {
                std::cout << "<cond," << i << ">, ";
            }
            std::cout << std::endl;
            
            traverse_tree(if_else_node->next, mp, var_counter, loop_counter, if_counter, cond_counter);
        }
    }
    else if (while_node) {
        while_node->while_num = *loop_counter;
        *loop_counter += 1;    
            
        std::cout << "#LOOP: " << while_node->while_num << std::endl;
        
        traverse_tree(while_node->cond, mp, var_counter, loop_counter, if_counter, cond_counter);
        traverse_tree(while_node->stmts, mp, var_counter, loop_counter, if_counter, cond_counter);
        traverse_tree(while_node->next, mp, var_counter, loop_counter, if_counter, cond_counter);
    }
    else { return; }
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
            case _NEG_ : {
                result = -expr_eval(bin_op_node->right, mp);
                break;
            }
            default: break;
        }
    }
    
    return result;
};

void print_asm(ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp, int* main_counter) {
    auto* num_node = dynamic_cast<NumNode*>(ptr);
    auto* var_node = dynamic_cast<VarNode*>(ptr);
    auto* bin_op_node = dynamic_cast<BinaryNode*>(ptr);
    auto* main_node = dynamic_cast<MainNode*>(ptr);
    auto* assign_node = dynamic_cast<AssignNode*>(ptr);
    auto* print_node = dynamic_cast<PrintNode*>(ptr);
    auto* if_else_node = dynamic_cast<IfElseNode*>(ptr);
    auto* while_node = dynamic_cast<WhileNode*>(ptr);
    
    if (num_node) {
        std::cout << "  mov rax, " << num_node->num << std::endl;
    }
    else if (var_node) {
        std::cout << "  mov rax, QWORD PTR [rbp-" << 2 * mp[var_node->var_name].second << "]" << std::endl;
    }
    else if (bin_op_node) {
        switch (bin_op_node->tag) {
            case _ADD_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  add rax, rbx" << std::endl;
                break;
            }
            case _SUB_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  sub rax, rbx" << std::endl;
                break;
            }
            case _MUL_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  imul rax, rbx" << std::endl;
                break;
            }
            case _DIV_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
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
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  shl rax, " << expr_eval(bin_op_node->right, mp) << std::endl;
                break;
            }
            case _SHR_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  shr rax, " << expr_eval(bin_op_node->right, mp) << std::endl;
                break;
            }
            case _AND_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  and rax, rbx" << std::endl;
                break;
            }
            case _OR_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  or rax, rbx" << std::endl;
                break;
            }
            case _NOT_ : {
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  not rax" << std::endl;
                break;
            }
            case _LESS_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_less" << std::endl;  
                break;
            }
            case _GREAT_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_great" << std::endl; 
                break;
            }
            case _EQ_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_eq" << std::endl; 
                break;
            }
            case _NEQ_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_neq" << std::endl; 
                break;
            }
            case _LEQ_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_leq" << std::endl; 
                break;
            }
            case _GEQ_ : {
                print_asm(bin_op_node->left, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  push rax" << std::endl;
                std::cout << "  pop rbx" << std::endl;
                std::cout << "  pop rax" << std::endl;
                std::cout << "  mov rdi, rax" << std::endl;
                std::cout << "  mov rsi, rbx" << std::endl;
                std::cout << "  call cmp_geq" << std::endl; 
                break;
            }
            case _NEG_ : {
                print_asm(bin_op_node->right, mp, main_counter);
                std::cout << "  mov r8, -1" << std::endl;
                std::cout << "  mul r8" << std::endl;
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
        print_asm(main_node->next, mp, main_counter);
        std::cout << "  leave" << std::endl;
        std::cout << "  ret\n" << std::endl;
    }
    else if (assign_node) {
        print_asm(assign_node->assign_val, mp, main_counter);
        std::cout << "  mov QWORD PTR [rbp-" << 2 * mp[assign_node->var_name].second << "], rax" << std::endl;
        print_asm(assign_node->next, mp, main_counter);
    }
    else if (print_node) {
        print_asm(print_node->print_val, mp, main_counter);
        std::cout << "  lea rdi, format" << std::endl;
        std::cout << "  mov rsi, rax" << std::endl;
        std::cout << "  xor rax, rax" << std::endl;
        std::cout << "  call printf" << std::endl;
        print_asm(print_node->next, mp, main_counter);
    }
    else if (if_else_node) {
        auto* next_if_else = dynamic_cast<IfElseNode*>(if_else_node->next);
        auto* next_while = dynamic_cast<WhileNode*>(if_else_node->next);
        int n = if_else_node->conds.size();
        
        if (n == 1) {
            std::cout << "if" << if_else_node->if_num << ":" << std::endl;
            print_asm(if_else_node->conds[0].first, mp, main_counter);
            std::cout << "  cmp rax, 1" << std::endl;
            std::cout << "  je cond" << if_else_node->cond_num[0] << std::endl;
            
            if (next_if_else) {
                std::cout << "  jmp if" << next_if_else->if_num << std::endl;
            }
            else if (next_while) {
                std::cout << "  jmp loop" << next_while->while_num << std::endl;
            }
            else {
                std::cout << "  jmp main" << (*main_counter) << std::endl;
            }
            
            std::cout << "cond" << if_else_node->cond_num[0] << ":" << std::endl;
            print_asm(if_else_node->conds[0].second, mp, main_counter);
                
            if (next_if_else) {
                std::cout << "  jmp if" << next_if_else->if_num << std::endl; 
            }
            else if (next_while) {
                std::cout << "  jmp loop" << next_while->while_num << std::endl;
            }
            else {
                std::cout << "  jmp main" << (*main_counter) << std::endl;
            }
            
            if (!(next_if_else || next_while)) {
                std::cout << "main" << (*main_counter) << ":" << std::endl;
                *main_counter += 1;
            }
            
            print_asm(if_else_node->next, mp, main_counter);
        }
        else {
            std::cout << "if" << if_else_node->if_num << ":" << std::endl;
            int i;
            for (i = 1; i < n; ++i) {
                print_asm(if_else_node->conds[i].first, mp, main_counter);
                std::cout << "  cmp rax, 1" << std::endl;
                std::cout << "  je cond" << if_else_node->cond_num[i-1] << std::endl;
            }
            std::cout << "  jmp cond" << if_else_node->cond_num[i-1] << std::endl;
            
            for (i = 1; i < n; ++i) {
                std::cout << "cond" << if_else_node->cond_num[i-1] << ":" << std::endl;
                print_asm(if_else_node->conds[i].second, mp, main_counter);
                
                if (next_if_else) {
                    std::cout << "  jmp if" << next_if_else->if_num << std::endl; 
                }
                else if (next_while) {
                    std::cout << "  jmp loop" << next_while->while_num << std::endl;
                }
                else {
                    std::cout << "  jmp main" << (*main_counter) << std::endl;
                }
            }
            std::cout << "cond" << if_else_node->cond_num[i-1] << ":" << std::endl;
            print_asm(if_else_node->conds[0].second, mp, main_counter);
                
            if (next_if_else) {
                std::cout << "  jmp if" << next_if_else->if_num << std::endl; 
            }
            else if (next_while) {
                std::cout << "  jmp loop" << next_while->while_num << std::endl;
            }
            else {
                std::cout << "  jmp main" << (*main_counter) << std::endl;
                std::cout << "main" << (*main_counter) << ":" << std::endl;
                *main_counter += 1;
            }
            print_asm(if_else_node->next, mp, main_counter);
        }
        
    }
    else if (while_node) {
        auto* next_while = dynamic_cast<WhileNode*>(while_node->next);
        
        std::cout << "loop" << while_node->while_num << ":" << std::endl;
        print_asm(while_node->cond, mp, main_counter);
        std::cout << "  cmp rax, 0" << std::endl;
        if (next_while) {
            std::cout << "  je loop" << next_while->while_num << std::endl;
        }
        else {
            std::cout << "  je main" << (*main_counter + 1) << std::endl;
        }
        print_asm(while_node->stmts, mp, main_counter);
        std::cout << "  jmp loop" << while_node->while_num << std::endl;
        
        if (!next_while) {
            std::cout << "main" << (*main_counter) << ":" << std::endl;
            *main_counter += 1;
        }
        print_asm(while_node->next, mp, main_counter);
    }
};
