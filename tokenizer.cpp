#include "token.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <vector>

// Funzione helper per identificare se un carattere è uno spazio
bool is_whitespace(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

// Funzione helper per verificare se un carattere è un numero
bool is_digit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

// Funzione helper per verificare se un carattere fa parte di un identificatore
bool is_identifier_char(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

// Restituisce il tag corrispondente alla parola chiave o all'operatore
int keyword_or_operator(const std::string& word) {
    static const std::unordered_map<std::string, int> keywords = {
        {"print", Token::PRINT},
        {"int", Token::INT},
        {"if", Token::IF},
        {"while", Token::WHILE},
        {"true", Token::TRUE},
        {"false", Token::FALSE},
        {"else", Token::ELSE},
        {"boolean", Token::BOOL},
    };

    auto it = keywords.find(word);
    if (it != keywords.end()) {
        return it->second;
    }
    return Token::ID;
}

// Tokenizza una stringa di input
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::istringstream iss(input);
    char c;

    while (iss >> std::noskipws >> c) {
        if (is_whitespace(c)) {
            continue;
        }

        if (is_digit(c)) {
            // Parsing di un numero
            std::string num;
            num += c;
            while (iss.peek() != EOF && is_digit(iss.peek())) {
                num += iss.get();
            }
            tokens.emplace_back(Token::NUM, num);
        } else if (std::isalpha(c)) {
            // Parsing di un identificatore o parola chiave
            std::string word;
            word += c;
            while (iss.peek() != EOF && is_identifier_char(iss.peek())) {
                word += iss.get();
            }
            tokens.emplace_back(keyword_or_operator(word), word);
        } else {
            // Parsing di singoli caratteri e operatori
            switch (c) {
                case '(': tokens.emplace_back(Token::OP, "("); break;
                case ')': tokens.emplace_back(Token::CP, ")"); break;
                case '{': tokens.emplace_back(Token::OG, "{"); break;
                case '}': tokens.emplace_back(Token::CG, "}"); break;
                case '+': tokens.emplace_back(Token::ADD, "+"); break;
                case '-': tokens.emplace_back(Token::SUB, "-"); break;
                case '*': tokens.emplace_back(Token::MUL, "*"); break;
                case '/': tokens.emplace_back(Token::DIV, "/"); break;
                case '<': tokens.emplace_back(Token::LT, "<"); break;
                case '>': tokens.emplace_back(Token::GT, ">"); break;
                case '=': 
                    if (iss.peek() == '=') {
                        iss.get();
                        tokens.emplace_back(Token::CON, "==");
                    } else {
                        tokens.emplace_back(Token::EQ, "=");
                    }
                    break;
                case '!':
                    if (iss.peek() == '=') {
                        iss.get();
                        tokens.emplace_back(Token::NOTEQ, "!=");
                    } else {
                        tokens.emplace_back(Token::NOT, "!");
                    }
                    break;
                case '&':
                    if (iss.peek() == '&') {
                        iss.get();
                        tokens.emplace_back(Token::AND, "&&");
                    }
                    break;
                case ';': tokens.emplace_back(Token::PV, ";"); break;
                case '%': tokens.emplace_back(Token::MOD, "%"); break;
                case '^': tokens.emplace_back(Token::EXP, "^"); break;
                case '[': tokens.emplace_back(Token::OQ, "["); break;
                case ']': tokens.emplace_back(Token::CQ, "]"); break;
                default:
                    std::cerr << "Unrecognized character: " << c << std::endl;
                    break;
            }
        }
    }

    return tokens;
}

// Funzione per confrontare i token
bool Token::operator==(Token other) const {
    return tag == other.tag && word == other.word;
}

// Operatore di output per stampare i token
std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << "Token(" << Token::id_word_table[t.tag] << ", \"" << t.word << "\")";
    return os;
}

// Funzione di test per il tokenizer
int main() {
    std::string input = "int x = 5; if (x > 3) { print(x); } else { x = 10; }";
    std::vector<Token> tokens = tokenize(input);

    for (const Token& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
