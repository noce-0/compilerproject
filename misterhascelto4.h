#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "Tokenizer.h"
#include "Exceptions.h"

class Parser {
public:
    Parser(std::vector<Token>& InputToken);  // Costruttore che accetta il flusso di token
    void parse();  // Metodo principale per avviare il parsing

private:
    std::vector<Token>& InputToken;  // Flusso di token da analizzare
    int currentTokenIndex;       // Indice per tenere traccia del token corrente
    Token currentToken;          // Token corrente

    void advance();              // Passa al prossimo token
    bool match(int tokenTag);    // Verifica se il token corrente è del tipo atteso e avanza
    void error(const std::string& msg);  // Genera un errore di parsing

    // Metodi di parsing per ogni regola della grammatica
    void program();
    void block();
    void decls();
    void decl();
    void type();
    void basic();
    void stmts();
    void stmt();
    void loc();

    //Metodi di parsing per ogni figlio di statementb
    void ifstmt();
    void ifeslsestmt();
    void whilestmt();
    void dostmt();
    void breakstmt();
    void print();

    void expr();  // Metodi di parsing per espressioni
    void term();
    void unary();
    void factor();
    void bool_expr();
    void equality();
    void join();
    void rel();
};

#endif // PARSER_H
