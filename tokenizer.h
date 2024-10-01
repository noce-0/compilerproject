#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <fstream>

#include "Token.h"

class Tokenizer {

public:
	Tokenizer() = default;
	~Tokenizer() = default;
	Tokenizer(Token const&) = delete;
	Token& operator=(Token const&) = delete;

	std::vector<Token> operator()(std::ifstream& inputFile) {
		std::vector<Token> inputTokens;
		tokenizeInputFile(inputFile, inputTokens);
		return inputTokens;
	}

private:
	void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens);

};

#endif
