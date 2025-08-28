#pragma once

#include "DataTypes.h"
#include <vector>
#include <string>
#include <utility>

using namespace std;

namespace Nodes {
	struct INode {
		virtual ~INode() = default;
	};

	struct ExpressionNode : INode {
		INode* content;

		/*ExpressionNode(INode* content) {
			this->content = content;
		}*/
	};

	struct BodyNode : INode {
		vector<ExpressionNode*>* content;

		BodyNode(vector<ExpressionNode*>* content) {
			this->content = content;
		}
	};

	struct FunctionDefinitionNode : INode {
		string name;
		vector<pair<string, DataTypes::IDataType*>*>* args; // nullptr - args are absent
		//vector<DataTypes::IDataType*>* args;
		DataTypes::IDataType* returnType;
		BodyNode* body;

		FunctionDefinitionNode(string name, vector<pair<string, DataTypes::IDataType*>*>* args, DataTypes::IDataType* returnType, BodyNode* body) {
			this->name = name;
			this->args = args;
			this->returnType = returnType;
			this->body = body;
		}
	};

	struct FunctionInvocationNode : INode {
		string name;
		vector<ExpressionNode*>* args;

		FunctionInvocationNode(string name, vector<ExpressionNode*>* args) {
			this->name = name;
			this->args = args;
		}
	};

	struct VariableDeclarationNode : INode {
		string name;
		DataTypes::IDataType* dataType;
		ExpressionNode* value;

		VariableDeclarationNode(string name, DataTypes::IDataType* dataType, ExpressionNode* value) {
			this->name = name;
			this->dataType = dataType;
			this->value = value;
		}
	};

	struct IfStatementNode : INode {
		BodyNode* statement;
		BodyNode* elseClause; // nullptr - else clause is absent
		ExpressionNode* condition;

		IfStatementNode(BodyNode* statement, BodyNode* elseClause, ExpressionNode* condition) {
			this->statement = statement;
			this->elseClause = elseClause;
			this->condition = condition;
		}
	};

	struct WhileStatementNode : INode {
		BodyNode* body;
		ExpressionNode* condition;

		WhileStatementNode(BodyNode* body, ExpressionNode* condition) {
			this->body = body;
			this->condition = condition;
		}
	};

	struct ReturnNode : INode {
		ExpressionNode* returnValue;

		ReturnNode(ExpressionNode* returnValue) {
			this->returnValue = returnValue;
		}
	};

	struct ConstNode : INode {
		string value;

		ConstNode(string value) {
			this->value = value;
		}
	};

	struct IdentifierNode : INode {
		string name;

		IdentifierNode(string name) {
			this->name = name;
		}
	};

}

