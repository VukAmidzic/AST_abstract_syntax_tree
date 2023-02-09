#include <string>
#include <cstddef>
#include <cstdlib>
#include <map>
#include <vector>
#include <utility>

#ifndef AST_HPP
#define AST_HPP

enum Tag {
    _ADD_,
    _SUB_,
    _MUL_,
    _DIV_,
    _SHL_,
    _SHR_,
    _LESS_,
    _GREAT_,
    _EQ_,
    _NEQ_,
    _LEQ_,
    _GEQ_,
    _AND_,
    _OR_,
    _NOT_,
    _NEG_
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class NumNode : public ASTNode {
public:
    int num;
    NumNode(int _num);
};

class VarNode : public ASTNode {
public:
    std::string var_name;
    VarNode(std::string _var_name);
};

class BinaryNode : public ASTNode {
public: 
    Tag tag;
    ASTNode* left;
    ASTNode* right;
    BinaryNode(Tag _tag, ASTNode* _left, ASTNode* _right);
};

class MainNode : public ASTNode {
public:
    ASTNode* next;
    MainNode(ASTNode* _next);
};

class StatementNode : public ASTNode {
public: 
    virtual ~StatementNode() = default;
};

class AssignNode : public StatementNode {
public:
    std::string var_name;
    ASTNode* assign_val;
    ASTNode* next;
    AssignNode(std::string _var_name, ASTNode* _assign_val, ASTNode* _next);
};

class PrintNode : public StatementNode {
public:
    ASTNode* print_val;
    ASTNode* next;
    PrintNode(ASTNode* _print_val, ASTNode* _next);
};

class IfElseNode : public StatementNode {
public:
    std::vector<std::pair<ASTNode*, ASTNode*>> conds;
    ASTNode* next;
    IfElseNode(std::vector<std::pair<ASTNode*, ASTNode*>> _conds, ASTNode* _next);
};

void traverse_tree(size_t lvl, ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp, int* var_counter);
void print_asm(ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp);
int expr_eval(ASTNode* ptr, std::map<std::string, std::pair<int, int>>& mp);

#endif
