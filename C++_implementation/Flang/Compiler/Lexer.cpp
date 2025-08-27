#include "pch.h"
#include <cctype>

using namespace std;


Tokens::IToken* Lexer::nextToken() {
	skipUnreadable();
	char current = input[pos];

	switch (current)
	{
	case '\"':
	{
		pos++;
		Tokens::ConstValue* token = new Tokens::ConstValue(readString());
		pos++;
		return token;
	}

	case '(':
	{
		pos++;
		Tokens::LBr* token = new Tokens::LBr{};
		return token;
	}
	case ')':
	{
		pos++;
		Tokens::RBr* token = new Tokens::RBr{};
		return token;
	}
	case ',':
	{
		pos++;
		Tokens::Comma* token = new Tokens::Comma{};
		return token;
	}
	case ':':
	{
		pos++;
		Tokens::Colon* token = new Tokens::Colon{};
		return token;
	}
	default:
	{
		if (isdigit(current)) {
			string value = readDigit();
			Tokens::ConstValue* token = new Tokens::ConstValue(value);
			return token;
		}
		string word = readWord();
		return checkWord(word);
	}
	}
}

string Lexer::readString() {
	size_t start = pos;
	char current = input[start];
	while (pos < inputLength && current != '\"') {
		pos++;
		current = input[pos];
	}
	return input.substr(start, pos - start);
}

string Lexer::readDigit() {
	size_t start = pos;
	char current = input[start];
	while (pos < inputLength && (isdigit(current) || current == '.')) {
		pos++;
		current = input[pos];
	}
	return input.substr(start, pos - start);
}

string Lexer::readWord() {
	size_t start = pos;
	char current = input[start];
	while (pos < inputLength && isalpha(current)) {
		pos++;
		current = input[pos];
	}
	return input.substr(start, pos - start);
}

Tokens::IToken* Lexer::checkWord(string word) {
	if (word == "fn") {
		Tokens::Keyword* token = new Tokens::Keyword(new Tokens::Fn{});
		return token;
	}
	else if (word == "return") {
		Tokens::Keyword* token = new Tokens::Keyword(new Tokens::Return{});
		return token;
	}
	/*else if (word == "body") {
		Tokens::Keyword* token = new Tokens::Keyword(new Tokens::Body{});
		return token;
	}
	else if (word == "args") {
		Tokens::Keyword* token = new Tokens::Keyword(new Tokens::Args{});
		return token;
	}*/
	/*else if (word == "+") {
		Tokens::Plus* token = new Tokens::Plus{};
		return token;
	}
	else if (word == "-") {
		Tokens::Minus* token = new Tokens::Minus{};
		return token;
	}
	else if (word == "*") {
		Tokens::Multiply* token = new Tokens::Multiply{};
		return token;
	}
	else if (word == "/") {
		Tokens::Divide* token = new Tokens::Divide{};
		return token;
	}
	else if (word == "=") {
		Tokens::Equal* token = new Tokens::Equal{};
		return token;
	}
	else if (word == "print") {
		Tokens::Print* token = new Tokens::Print{};
		return token;
	}*/
	else if (word == "int") {
		Tokens::DataType* token = new Tokens::DataType(new DataTypes::Int{});
		return token;
	}
	else if (word == "float") {
		Tokens::DataType* token = new Tokens::DataType(new DataTypes::Float{});
		return token;
	}
	else if (word == "str") {
		Tokens::DataType* token = new Tokens::DataType(new DataTypes::Str{});
		return token;
	}
	else if (word == "bool") {
		Tokens::DataType* token = new Tokens::DataType(new DataTypes::Bool{});
		return token;
	}
	else if (word == "void") {
		Tokens::DataType* token = new Tokens::DataType(new DataTypes::Void{});
		return token;
	}

	else {
		Tokens::Identifier* token = new Tokens::Identifier(word);
		return token;
	}
}

void Lexer::skipUnreadable() {
	while (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '\t') {
		pos++;
	}
}

Lexer::Lexer(string input) {
	this->input = input;
	this->inputLength = input.length();
	this->pos = 0;
}

vector<Tokens::IToken*> Lexer::tokenize() {
	vector<Tokens::IToken*> result;
	while (pos < inputLength) {
		result.push_back(nextToken());
	}
	return result;
}