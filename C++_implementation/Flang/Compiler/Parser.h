#pragma once

#include "Nodes.h"
#include "Tokens.h"
#include <string>
#include <vector>


class Parser {
private:
	std::vector<Tokens::IToken*> input;
	size_t pos;
	size_t inputLength;



public:
	Parser(std::vector<Tokens::IToken*> input);

	std::vector<Nodes::FunctionDefinitionNode*>* parse();

	// TODO: сделать приватными после окончания тестирования
	std::vector<Tokens::IToken*>* getFunctionContent(const std::vector<Tokens::IToken*>& tokens, size_t start);
	std::vector<std::vector<Tokens::IToken*>*>* groupArguments(const std::vector<Tokens::IToken*>& content);
	Nodes::ExpressionNode* makeExpression(const std::vector<Tokens::IToken*>& content);
	Nodes::BodyNode* makeBody(const std::vector<Tokens::IToken*>& content);
	Nodes::INode* parseFunc(const std::vector<std::vector<Tokens::IToken*>*>& content);
	std::vector<std::vector<Tokens::IToken*>*>* groupFunctionsGlobal(const std::vector<Tokens::IToken*>& tokens);
};

