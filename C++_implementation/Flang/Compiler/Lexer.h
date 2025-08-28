#pragma once

#include <string>
#include <vector>
#include "Tokens.h"

class Lexer {
private:
	std::string input;
	size_t pos;
	size_t inputLength;

	// �������� ��������� ������������ ������� ������� �����
	Tokens::IToken* nextToken();
	// ��������� ������ (����� ���� "")
	std::string readString();
	// ��������� ����� (� ��� ����� � ������)
	std::string readDigit();
	// ��������� �����
	std::string readWord();
	// �������� ������ ����� � ����������� �� ������������ �����
	Tokens::IToken* checkWord(std::string word);
	// ���������� ������������ ������� (������, \n, \t)
	void skipUnreadable();

public:
	Lexer(std::string input);
	std::vector<Tokens::IToken*> tokenize();
};

