#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <string>
#include <vector>

class Int;
class IdExp;
class LogicalExp;       
class Block;

//      NODE

class Node {
public:
    Node();
    virtual ~Node() = default;

    virtual int interpret() = 0;
};

//      SUBCLASSES OF NODE

class Statement : public Node {
public:
    Statement();
    virtual ~Statement() = default;

    int interpret() override = 0;
};

class Expression : public Node {
public:
    Expression();
    virtual ~Expression() = default;

    int interpret() override = 0;
};

//      SUBCLASSES OF STATEMENT

class IfStmt final : public Statement {
public:
    IfStmt(LogicalExp* c, Block* ts) : condition(c), then_stmt(ts) {};
    ~IfStmt() {};
    IfStmt& operator=(const IfStmt& other);

    int interpret() override;

private:
    LogicalExp* condition;
    Block* then_stmt;
};

class ElseStmt final : public Statement {
public:
    ElseStmt(LogicalExp* c, Block* ts, Block* es) : condition(c), then_stmt(ts), else_stmt(es) {};
    virtual ~ElseStmt() = default;
    ElseStmt& operator=(const ElseStmt& other);

    int interpret() override;

private:
    LogicalExp* condition;
    Block* then_stmt;
    Block* else_stmt;
};

class WhileStmt final : public Statement {
public:
    WhileStmt(LogicalExp* c, Block* l) : condition(c), loop(l) {};
    virtual ~WhileStmt() = default;
    WhileStmt& operator=(const WhileStmt& other);

    int interpret() override;

private:
    LogicalExp* condition;
    Block* loop;
};

class DoStmt final : public Statement {
public:
    DoStmt(LogicalExp* c, Block* dl) : condition(c), doloop(dl) {};
    virtual ~DoStmt() = default;
    DoStmt& operator=(const DoStmt& other);

    int interpret() override;

private:
    LogicalExp* condition;
    Block* doloop;
};

class SetStmt final : public Statement {
public:
    SetStmt(IdExp* id, Expression* exp, const char o) : var_id(id), value(exp), oper(o) {};
    ~SetStmt() override = default;
    int interpret() override;
private:
    IdExp* var_id;
    Expression* value;
    const char oper = '=';
};

class SetElemStmt final : public Statement {
public:
    SetElemStmt(IdExp* id, Int* p, Expression* exp, const char o, char opb, char c) : var_id(id), var_position(p), value(exp), oper(o), ob(opb), cb(c) {};
    ~SetElemStmt() override = default;
    int interpret() override;
private:
    IdExp* var_id;
    Int* var_position;
    Expression* value;
    const char oper = '=';
    const char ob = '[';
    const char cb = ']';
};

class BreakStmt final : public Statement {
public:
    int interpret() override;
};

class PrintStmt final : public Statement {
public:
    PrintStmt(LogicalExp* c) : condition(c) {};
    virtual ~PrintStmt() = default;

    int interpret() override;

private:
    LogicalExp* condition;
};

//      SUBCLASSES OF EXPRESSION

class OpExpr : public Expression {
public:
    OpExpr();
    ~OpExpr() override = default;
    int interpret() override = 0;   
};

class Constant: public Expression {
public:
    Constant();
    ~Constant() override = default;
    int interpret() override = 0;
};

class LogicalExp : public Expression {
public:
    virtual ~LogicalExp() {};
    virtual int interpret() = 0;
};

class IdExp final : public Expression {
public:
    IdExp(std::string nid) : id(nid){}
    ~IdExp() {};
    int interpret() override;
private:
    std::string id;
};

//      SUBCLASSES OF OPEXPR

class UnaryOp final : public OpExpr {
public:
    UnaryOp(const char c, int o) : ch(c), op(o) {};
    ~UnaryOp() override = default;
    int interpret() override;
private:
    const char ch = '-';
    int op;
};

class AccessOp final : public OpExpr {
public:
    AccessOp(int ind, char o, char c) : index(ind), ob(o), cb(c) {};
    ~AccessOp() override = default;
    int interpret() override;
private:
    int index;
    const char ob = '[';
    const char cb = ']';
};

class BinaryOp final : public OpExpr {
public:
    BinaryOp(int l, int r, char o) : left_op(l), right_op(o), op(o) {};
    ~BinaryOp() override = default;
    int interpret() override;
private:
    int left_op;
    int right_op;
    char op;
};

//      SUBCLASSES OF CONSTANT

class Int final : public Constant {
public:
    explicit Int(int v) : intvalue(v) {};
    ~Int() override = default;
    int interpret() override;
private:
    int intvalue;
};

class Bool final : public Constant {
public:
    explicit Bool(bool b) : boolvalue(b) {};
    ~Bool() override = default;
    int interpret() override;
private:
    bool boolvalue;
};

//      SUBCLASSES OF LOGICALEXP

class NotLog final : public LogicalExp {
public:
    explicit NotLog(Expression* l) : left(l) {};
    ~NotLog() override = default;
    int interpret() override;

private:
    Expression* left;
};

class OrLog final : public LogicalExp{
public:
    OrLog(Expression* l, Expression* r) : left(l), right(r) {};
    ~OrLog() override = default;
    int interpret() override;

private:
    Expression* left;
    Expression* right;
};

class AndLog final : public LogicalExp{
public:
    AndLog(Expression* l, Expression* r) : left(l), right(r) {};
    ~AndLog() override = default;
    int interpret() override;

private:
    Expression* left;
    Expression* right;
};

class RelLog final : public LogicalExp{
public:
    enum symbCode { GT, LT, EQ, GET, LET, CON };
    RelLog(Expression* l, Expression* r, symbCode s) :  left(l), right(r), sc(s){};
    ~RelLog() {};
    int interpret() override;

private:
    Expression* left;
    Expression* right;
    symbCode sc;
};

#endif //INTERPRETER_H
