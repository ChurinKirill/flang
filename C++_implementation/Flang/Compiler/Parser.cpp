#include "pch.h"
#include "Utils.h"
#include <typeinfo>

using namespace std;

vector<Tokens::IToken*>* Parser::getFunctionContent(const vector<Tokens::IToken*>& tokens, size_t start) {
	size_t len = tokens.size();


	Tokens::IToken* current = tokens[start];
	size_t level = 1;
	size_t i = start;
	while (true) {
		if (typeid(*current) == typeid(Tokens::LBr))
			level++;
		else if (typeid(*current) == typeid(Tokens::RBr))
			level--;

		if (level == 0 || i == len)
			break;
		i++;
		current = tokens[i];
	}

	auto resStart = tokens.begin() + start;
	auto resEnd = tokens.begin() + i; 

	vector<Tokens::IToken*>* result = new vector<Tokens::IToken*>(i - start);

	copy(resStart, resEnd, result->begin());

	return result;
}

vector<vector<Tokens::IToken*>*>* Parser::groupArguments(const vector<Tokens::IToken*>& content) {
	size_t len = content.size();
	size_t i = 0;
	size_t level = 0;
	vector<vector<Tokens::IToken*>*>* result = new vector<vector<Tokens::IToken*>*>();

	while (i < len) {
		vector<Tokens::IToken*>* group = new vector<Tokens::IToken*>();
		Tokens::IToken* current = content[i];
		while (true) {
			if (level == 0 && typeid(*current) == typeid(Tokens::Comma))
				break;

			if (typeid(*current) == typeid(Tokens::LBr))
				level++;
			else if (typeid(*current) == typeid(Tokens::RBr))
				level--;

			group->push_back(current);
			i++;
			if (i == len)
				break;
			current = content[i];
		}
		i++;
		result->push_back(group);
		if (i >= len)
			break;

		current = content[i];
	}

	return result;
}

// TODO: !!! очищать векторы, создаваемые в getFunctionContent() и в groupArguments() в конструкциях типа groupArguments(getFunctionContent())

Nodes::ExpressionNode* Parser::makeExpression(const vector<Tokens::IToken*>& content) {
	Nodes::ExpressionNode* res = new Nodes::ExpressionNode();

	if (content.size() == 1) {
		if (typeid(content.at(0)) == typeid(Tokens::Identifier)) {
			auto t = dynamic_cast<Tokens::Identifier*>(content.at(0));
			Nodes::IdentifierNode* node = new Nodes::IdentifierNode(t->value);
			res->content = node;
		}
		else if (typeid(content.at(0)) == typeid(Tokens::ConstValue)) {
			auto t = dynamic_cast<Tokens::ConstValue*>(content.at(0));
			Nodes::ConstNode* node = new Nodes::ConstNode(t->value);
			res->content = node;
		}
	}
	else {
		Nodes::INode* node = parseFunc(*groupArguments(*getFunctionContent(content, 1)));
		res->content = node;
	}

	return res;
}

Nodes::BodyNode* Parser::makeBody(const vector<Tokens::IToken*>& content) {
	// temporary vector
	vector<vector<Tokens::IToken*>*>* grouped_content = groupArguments(*getFunctionContent(content, 1));

	vector<Nodes::ExpressionNode*>* body = new vector<Nodes::ExpressionNode*>();

	for (vector<Tokens::IToken*>* el : *grouped_content) {
		Nodes::ExpressionNode* expr = new Nodes::ExpressionNode();

		if (typeid(el->at(0)) == typeid(Tokens::LBr)) {
			Nodes::INode* node = parseFunc(*groupArguments(*getFunctionContent(*el, 1)));
			expr->content = node;
		}
		else if (typeid(el->at(0)) == typeid(Tokens::Keyword)) {
			auto keyword = dynamic_cast<Tokens::IKeyword*>(el->at(0));
			if (typeid(keyword) == typeid(Tokens::Return)) {
				Nodes::ExpressionNode* retExpr = new Nodes::ExpressionNode();

				if (typeid(el->at(1)) == typeid(Tokens::LBr)) {
					Nodes::INode* node = parseFunc(*groupArguments(*getFunctionContent(*el, 2)));
					retExpr->content = node;
				}
				else if (typeid(el->at(1)) == typeid(Tokens::Identifier)) {
					auto t = dynamic_cast<Tokens::Identifier*>(el->at(1));
					Nodes::IdentifierNode* node = new Nodes::IdentifierNode(t->value);
					retExpr->content = node;
				}
				else if (typeid(el->at(1)) == typeid(Tokens::ConstValue)) {
					auto t = dynamic_cast<Tokens::ConstValue*>(el->at(1));
					Nodes::ConstNode* node = new Nodes::ConstNode(t->value);
					retExpr->content = node;
				}
				Nodes::ReturnNode* node = new Nodes::ReturnNode(retExpr);
				expr->content = node;
			}
		}
		body->push_back(expr);
	}
	// clearing temporary vector
	Utils::clearVector2D(*grouped_content);

	// result
	Nodes::BodyNode* result = new Nodes::BodyNode(body);
	return result;
}

Nodes::INode* Parser::parseFunc(const vector<vector<Tokens::IToken*>*>& content) {
	// keywords
	if (typeid(content.at(0)->at(0)) == typeid(Tokens::Keyword)) {
		auto keyword = dynamic_cast<Tokens::Keyword*>(content.at(0)->at(0));
		// fn
		if (typeid(keyword->value) == typeid(Tokens::Fn)) {

			auto name = dynamic_cast<Tokens::Identifier*>(content.at(0)->at(1));
			auto returnType = dynamic_cast<Tokens::DataType*>(content.at(0)->at(3));

			if (content.size() == 2) {
				Nodes::BodyNode* body = makeBody(*content.at(1));

				Nodes::FunctionDefinitionNode* node = new Nodes::FunctionDefinitionNode(
					name->value,
					nullptr,
					returnType->value,
					body
				);
				return node;
			}
			// temporary vector
			vector<vector<Tokens::IToken*>*>* argTokens = groupArguments(*getFunctionContent(*content.at(1), 1));

			vector<pair<string, DataTypes::IDataType*>*>* args = new vector<pair<string, DataTypes::IDataType*>*>();

			for (auto a : *argTokens) {
				auto aName = dynamic_cast<Tokens::Identifier*>(a->at(0));
				auto dataType = dynamic_cast<Tokens::DataType*>(a->at(2));
				pair<string, DataTypes::IDataType*>* arg = new pair<string, DataTypes::IDataType*>(aName->value, dataType->value);
				args->push_back(arg);
			}

			Nodes::BodyNode* body = makeBody(*content.at(2));

			// cleaning temporary vector
			Utils::clearVector2D(*argTokens);

			// result
			Nodes::FunctionDefinitionNode* node = new Nodes::FunctionDefinitionNode(
				name->value,
				args,
				returnType->value,
				body
			);
			return node;

		}
		// if
		else if (typeid(keyword->value) == typeid(Tokens::If)) {
			Nodes::ExpressionNode* condition = new Nodes::ExpressionNode();
			if (typeid(content.at(0)->at(1)) == typeid(Tokens::LBr)) {
				Nodes::INode* node = parseFunc(*groupArguments(*getFunctionContent(*content.at(0), 2)));
				condition->content = node;
			}
			else if (typeid(content.at(0)->at(1)) == typeid(Tokens::Identifier)) {
				auto t = dynamic_cast<Tokens::Identifier*>(content.at(0)->at(1));
				Nodes::IdentifierNode* node = new Nodes::IdentifierNode(t->value);
				condition->content = node;
			}
			else if (typeid(content.at(0)->at(1)) == typeid(Tokens::ConstValue)) {
				auto t = dynamic_cast<Tokens::ConstValue*>(content.at(0)->at(1));
				Nodes::ConstNode* node = new Nodes::ConstNode(t->value);
				condition->content = node;
			}

			Nodes::BodyNode* statement = makeBody(*content.at(1));
			if (content.size() == 2) {
				Nodes::IfStatementNode* node = new Nodes::IfStatementNode(
					statement,
					nullptr,
					condition
				);
				return node;
			}
			Nodes::BodyNode* elseClause = makeBody(*content.at(2));
			Nodes::IfStatementNode* node = new Nodes::IfStatementNode(
				statement,
				elseClause,
				condition
			);
			return node;
		}
		// while
		else if (typeid(keyword->value) == typeid(Tokens::While)) {
			Nodes::ExpressionNode* condition = new Nodes::ExpressionNode();
			if (typeid(content.at(0)->at(1)) == typeid(Tokens::LBr)) {
				Nodes::INode* node = parseFunc(*groupArguments(*getFunctionContent(*content.at(0), 2)));
				condition->content = node;
			}
			else if (typeid(content.at(0)->at(1)) == typeid(Tokens::Identifier)) {
				auto t = dynamic_cast<Tokens::Identifier*>(content.at(0)->at(1));
				Nodes::IdentifierNode* node = new Nodes::IdentifierNode(t->value);
				condition->content = node;
			}
			else if (typeid(content.at(0)->at(1)) == typeid(Tokens::ConstValue)) {
				auto t = dynamic_cast<Tokens::ConstValue*>(content.at(0)->at(1));
				Nodes::ConstNode* node = new Nodes::ConstNode(t->value);
				condition->content = node;
			}
			Nodes::BodyNode* body = makeBody(*content.at(1));

			Nodes::WhileStatementNode* node = new Nodes::WhileStatementNode(
				body,
				condition
			);
			return node;
		}
	}
	// Identifier
	else if (typeid(content.at(0)->at(0)) == typeid(Tokens::Identifier)) {
		auto identifier = dynamic_cast<Tokens::Identifier*>(content.at(0)->at(0));
		// variable declaration
		if (identifier->value == "=" && content.at(1)->size() == 3) {
			auto name = dynamic_cast<Tokens::Identifier*>(content.at(1)->at(0));
			auto dataType = dynamic_cast<Tokens::DataType*>(content.at(1)->at(2));

			Nodes::ExpressionNode* expression = makeExpression(*content.at(2));

			Nodes::VariableDeclarationNode* node = new Nodes::VariableDeclarationNode(
				name->value,
				dataType->value,
				expression
			);
			return node;
		}

		// function invocation
		string name = identifier->value;
		vector<Nodes::ExpressionNode*>* args = new vector<Nodes::ExpressionNode*>();

		for (size_t i = 1; i < content.size(); i++) {
			Nodes::ExpressionNode* arg = makeExpression(*content.at(i));
			args->push_back(arg);
		}

		Nodes::FunctionInvocationNode* node = new Nodes::FunctionInvocationNode(
			name,
			args
		);
		return node;
	}
}

Parser::Parser(vector<Tokens::IToken*> input) {
	this->input = input;
	this->pos = 0;
	this->inputLength = input.size();
}