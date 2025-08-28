#pragma once

#include <string>
#include <vector>
#include "Tokens.h"

class Lexer {
private:
	std::string input;
	size_t pos;
	size_t inputLength;

	// получить следующий относительно текущей позиции токен
	Tokens::IToken* nextToken();
	// прочитать строку (между двух "")
	std::string readString();
	// прочитать число (в том числе с точкой)
	std::string readDigit();
	// прочитать слово
	std::string readWord();
	// получить нужный токен в зависимости от прочитанного слова
	Tokens::IToken* checkWord(std::string word);
	// пропустить игнорируемые символы (пробел, \n, \t)
	void skipUnreadable();

public:
	Lexer(std::string input);
	std::vector<Tokens::IToken*> tokenize();
};

