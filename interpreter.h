#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <string>
#include <vector>

/---------- AST DIDDY ----------/
class Node {
public:
    Node();
    virtual ~Node() = default;

    virtual int interpret() = 0;
};

class Statement : public Node {
public:
    Statement();
    virtual ~Statement() = default;

    virtual int interpret() = 0;
};

class Expression : public Node {
public:
    Expression();
    virtual ~Expression() = default;

    virtual int interpret() = 0;
};

/---------- SUBCLASSES OF STATEMENT ----------/
class IfStmt : public Statement {
public:
    IfStmt(Logical* c, Block* ts) : condition(c), then_stmt(ts) {};
    ~IfStmt() {};
    IfStmt& operator=(const IfStmt& other);

    int interpret() override;

private:
    Logical* condition;
    Block* then_stmt;
};

class ElseStmt : public Statement {
public:
    ElseStmt(Logical* c, Block* ts, Block* es) : condition(c), then_stmt(ts), else_stmt(es) {};
    virtual ~ElseStmt() = default;
    ElseStmt& operator=(const ElseStmt& other);

    int interpret() override;

private:
    Logical* condition;
    Block* then_stmt;
    Block* else_stmt;
};

class WhileStmt : public Statement {
public:
    WhileStmt(Logical* c, Block* l) : condition(c), loop(l) {};
    virtual ~WhileStmt() = default;
    WhileStmt& operator=(const WhileStmt& other);

    int interpret() override;

private:
    Logical* condition;
    Block* loop;
};

class DoStmt : public Statement {
public:
    DoStmt(Logical* c, Block* dl) : condition(c), loop(dl) {};
    virtual ~DoStmt() = default;
    DoStmt& operator=(const DoStmt& other);

    int interpret() override;

private:
    Logical* condition;
    Block* doloop;
};

class BreakStmt : public Statement {
public:
    int interpret() override;

};

class PrintStmt : public Statement {
public:
    PrintStmt(Logical* c) : condition(c) {};
    virtual ~PrintStmt() = default;

    int interpret() override;

private:
    Logical* condition;
};

/---------- BLOCK ----------/
class Block : public Statement {
public:
    Block();
    ~Block() = default;

    int interpret() override;   // perché foglia

private:
    IfStmt* ifblock;
    ElseStmt* elseblock;
    WhileStmt* whileblock;
    DoStmt* doblock;
    PrintStmt* printblock;
    BreakStmt* breakblock;
};

class OpExpr : public Expression {
    public:
        OpExpr();
        ~OpExpr() override = default;
        virtual int interpret() = 0;    // perché padre
};

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
        AccessOp(int ind, char o, char c) : index(ind), op(o), cb(c) {};
        ~AccessOp() override = default;
        int interpret() override;
    private:
        int index;
        const char op = '[';
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

class CostantExp : public Expression{
public:
    virtual ~Costant() {};
    virtual int interpret() = 0;
};

//---------- SUBCLASSES OF COSTANT ----------//

class IntConst : public CostantExp{
public:
    IntConst(int v) : valore(v) {};
    ~IntConst() {};
    int interpret() override;

private:
    int valore;
};

class BooleanConst : public CostantExp{
public:
    BooleanConst(int b) : binario(b) {};
    ~PrintStmt() {};
    int interpret() override;

private:
    int binario;
};

class LogicalExp : public Expression {
public:
    virtual ~Logical() {};
    virtual int interpret() = 0;
};

//---------- SUBCLASSES OF LOGICAL ----------//

class NotLog : public LogicalExp {
public:
    NotLog(Expression* l) : left(l) {};
    ~Notlog() {};
    int interpret() override;

private:
    Expression* left;
};

class OrLog : public LogicalExp{
public:
    OrLog(Expression* l, Expression* r) : left(l), right(r) {};
    ~OrLog() {};
    int interpret() override;

private:
    Expression* left;
    Expression* right
};

class AndLog : public LogicalExp{
public:
    AndLog(Expression* l, Expression* r) : left(l), right(r) {};
    ~AndLog() {};
    int interpret() override;

private:
    Expression* left;
    Expression* right
};

class RelLog : public LogicalExp{
public:
    enum symbCode { GT, LT, EQ, GET, LET, CON };
    RelLog(Expression* l, Expression* r, RelLog::symbCode smc) :  left(l), right(r), sc(smc){};
    ~RelLog() {};
    int interpret() override;

private:
    Expression* left;
    Expression* right;
    RelLog::symbCode sc;
};

class IdExp final : public Expression {
public:
    IdExp(std::string nid) : id(nid){}
    ~IdExp() {};
    int interpreter() override;
private:
    std::string id;
};

#endif //INTERPRETER_H
