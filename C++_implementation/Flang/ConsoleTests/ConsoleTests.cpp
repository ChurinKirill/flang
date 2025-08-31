// ConsoleTests.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Lexer.h>
#include <Parser.h>
#include "TestingUtils.h"

#include <sstream>
#include <typeinfo>

//#define private public // дл€ тестировани€ приватных функций

using namespace std;

void Lexer_SimpleTest() {
    cout << "Running Lexer_SimpleTest:\n";

    string in = R"(
(defn main : int,
    (
        (print, "Hello, World!"),
        return 0
    )
))";
    Lexer lexer = Lexer(in);

    vector<Tokens::IToken*> expected {
        new Tokens::LBr{},
            new Tokens::Keyword(new Tokens::Defn{}),
            new Tokens::Identifier("main"),
            new Tokens::Colon{},
            new Tokens::DataType(new DataTypes::Int{}),
            new Tokens::Comma{},
            new Tokens::LBr{},
            new Tokens::LBr{},
            new Tokens::Identifier("print"),
            new Tokens::Comma{},
            new Tokens::ConstValue("Hello, World!"),
            new Tokens::RBr{},
            new Tokens::Comma{},
            new Tokens::Keyword(new Tokens::Return{}),
            new Tokens::ConstValue("0"),
            new Tokens::RBr{},
            new Tokens::RBr{}
    };


    vector<Tokens::IToken*> out = lexer.tokenize();


    if (!expect_eq(out.size(), expected.size())) return;

    for (size_t i = 0; i < out.size(); i++) {
        stringstream msg; msg << "Comparing tokens expected[" << i << "] and out[" << i << "]:";
        if (!expect_true(compareTokens(expected[i], out[i]), msg.str())) return;
    }

    cout << "\n";

    /*clearVector(out);
    clearVector(expected);*/
}

void Parser_GetFunctionContent() {
    cout << "Running Parser_GetFunctionContent:\n";
    const vector<Tokens::IToken*> in {
        new Tokens::Keyword(new Tokens::Defn{}),
            new Tokens::Identifier("main"),
            new Tokens::Colon{},
            new Tokens::DataType(new DataTypes::Int{}),
            new Tokens::Comma{},
            new Tokens::LBr{},
            new Tokens::LBr{},
            new Tokens::Identifier("print"),
            new Tokens::Comma{},
            new Tokens::ConstValue("Hello, World!"),
            new Tokens::RBr{},
            new Tokens::Comma{},
            new Tokens::Keyword(new Tokens::Return{}),
            new Tokens::ConstValue("0"),
            new Tokens::RBr{},
            new Tokens::RBr{}
    };

    Parser parser = Parser(in);

    vector<Tokens::IToken*> expected {
        new Tokens::Keyword(new Tokens::Defn{}),
            new Tokens::Identifier("main"),
            new Tokens::Colon{},
            new Tokens::DataType(new DataTypes::Int{}),
            new Tokens::Comma{},
            new Tokens::LBr{},
            new Tokens::LBr{},
            new Tokens::Identifier("print"),
            new Tokens::Comma{},
            new Tokens::ConstValue("Hello, World!"),
            new Tokens::RBr{},
            new Tokens::Comma{},
            new Tokens::Keyword(new Tokens::Return{}),
            new Tokens::ConstValue("0"),
            new Tokens::RBr{}
    };


    vector<Tokens::IToken*>* out = parser.getFunctionContent(in, 0);

    vector<Tokens::IToken*> res = *out;

    if (!expect_eq(res.size(), expected.size())) return;

    for (size_t i = 0; i < res.size(); i++) {
        stringstream msg; msg << "Comparing tokens expected[" << i << "] and out[" << i << "]:";
        if (!expect_true(compareTokens(expected[i], res[i]), msg.str())) return;
    }

    cout << "\n";

}

void Parser_GroupArgs() {
    cout << "Running Parser_GroupArgs:\n";
    vector<Tokens::IToken*> in {
        new Tokens::Keyword(new Tokens::Defn{}),
            new Tokens::Identifier("main"),
            new Tokens::Colon{},
            new Tokens::DataType(new DataTypes::Int{}),
            new Tokens::Comma{},
            new Tokens::LBr{},
            new Tokens::LBr{},
            new Tokens::Identifier("print"),
            new Tokens::Comma{},
            new Tokens::ConstValue("Hello, World!"),
            new Tokens::RBr{},
            new Tokens::Comma{},
            new Tokens::Keyword(new Tokens::Return{}),
            new Tokens::ConstValue("0"),
            new Tokens::RBr{}
    };

    Parser parser = Parser(in);

    vector<vector<Tokens::IToken*>*> expected;

    vector<Tokens::IToken*> v1 {
        new Tokens::Keyword(new Tokens::Defn{}),
            new Tokens::Identifier("main"),
            new Tokens::Colon{},
            new Tokens::DataType(new DataTypes::Int{})
    };
    vector<Tokens::IToken*> v2 {
        new Tokens::LBr{},
            new Tokens::LBr{},
            new Tokens::Identifier("print"),
            new Tokens::Comma{},
            new Tokens::ConstValue("Hello, World!"),
            new Tokens::RBr{},
            new Tokens::Comma{},
            new Tokens::Keyword(new Tokens::Return{}),
            new Tokens::ConstValue("0"),
            new Tokens::RBr{}
    };

    expected.push_back(&v1);
    expected.push_back(&v2);


    vector<vector<Tokens::IToken*>*>* out = parser.groupArguments(in);

    vector<vector<Tokens::IToken*>*> res = *out;

    if (!expect_eq(res.size(), expected.size())) return;

    for (size_t i = 0; i < res.size(); i++) {
        expect_eq(res[i]->size(), expected[i]->size());
        for (size_t j = 0; j < res[i]->size(); j++) {
            stringstream msg; msg << "Comparing tokens expected[" << i << "][" << j << "] and res[" << i << "][" << j << "]:";
            if (!expect_true(compareTokens(res[i]->at(j), expected[i]->at(j)), msg.str())) return;
        }
    }
    cout << "\n";
}

void Parser_MakeExpressionConst() {
    cout << "Running Parser_MakeExpressionConst:\n";
    vector<Tokens::IToken*>* in = new vector<Tokens::IToken*>();
    in->push_back(new Tokens::ConstValue("5"));


    Parser parser = Parser(*in);

    Nodes::ExpressionNode expected;
    expected.content = new Nodes::ConstNode("5");


    Nodes::ExpressionNode* out = parser.makeExpression(*in);


    if (!expect_true(typeid(out->content) == typeid(expected.content), "Comparing out.content and expected.content:")) return;

    auto constValOut = dynamic_cast<Nodes::ConstNode*>(out->content);
    auto constValExpected = dynamic_cast<Nodes::ConstNode*>(expected.content);
    if (!expect_eq(constValOut->value, constValExpected->value)) return;

    cout << "\n";
}

void Parser_MakeExpressionIdentifier() {
    cout << "Running Parser_MakeExpressionIdentifier:\n";

    vector<Tokens::IToken*>* in = new vector<Tokens::IToken*>();
    in->push_back(new Tokens::Identifier("my_var"));


    Parser parser = Parser(*in);

    Nodes::ExpressionNode expected;
    expected.content = new Nodes::IdentifierNode("my_var");


    Nodes::ExpressionNode* out = parser.makeExpression(*in);


    if (!expect_true(typeid(out->content) == typeid(expected.content), "Comparing out.content and expected.content:")) return;

    // пока вручную
    auto identifierOut = dynamic_cast<Nodes::IdentifierNode*>(out->content);
    auto identifierExpected = dynamic_cast<Nodes::IdentifierNode*>(expected.content);
    if (!expect_eq(identifierOut->name, identifierExpected->name)) return;

    cout << "\n";
}

void Parser_MakeExpressionFunc() {
    cout << "Running Parser_MakeExpressionFunc:\n";

    vector<Tokens::IToken*>* in = new vector<Tokens::IToken*>();
    in->push_back(new Tokens::LBr);
    in->push_back(new Tokens::Identifier("+"));
    in->push_back(new Tokens::Comma);
    in->push_back(new Tokens::Identifier("a"));
    in->push_back(new Tokens::Comma);
    in->push_back(new Tokens::ConstValue("5"));
    in->push_back(new Tokens::RBr);


    Parser parser = Parser(*in);


    Nodes::ExpressionNode expected;

    Nodes::ExpressionNode* exp1 = new Nodes::ExpressionNode();
    exp1->content = new Nodes::IdentifierNode("a");

    Nodes::ExpressionNode* exp2 = new Nodes::ExpressionNode();
    exp2->content = new Nodes::ConstNode("5");

    Nodes::FunctionInvocationNode* node = new Nodes::FunctionInvocationNode(
        "+",
        new vector<Nodes::ExpressionNode*>{
            exp1,
            exp2
        }
    );
    expected.content = node;


    Nodes::ExpressionNode* out = parser.makeExpression(*in);


    if (!expect_true(typeid(out->content) == typeid(expected.content), "Comparing out.content and expected.content:")) return;

    auto funcInvokeOut = dynamic_cast<Nodes::FunctionInvocationNode*>(out->content);
    auto funcInvokeExpected = dynamic_cast<Nodes::FunctionInvocationNode*>(expected.content);
    if (!expect_eq(funcInvokeOut->name, funcInvokeExpected->name)) return;
    if (!expect_eq(funcInvokeOut->args->size(), funcInvokeExpected->args->size())) return;
    // остальные проверки
    cout << "\n";
}

void Parser_ParseFunc() {
    cout << "Running Parser_ParseFunc:\n";

    string in = R"(
(defn main : int,
    (
        (print, "Hello, World!"),
        return 0
    )
))";
    Lexer lexer = Lexer(in);

    vector<Tokens::IToken*> tokens = lexer.tokenize();

    vector<Nodes::ExpressionNode*>* bodyContent = new vector<Nodes::ExpressionNode*>{
        new Nodes::ExpressionNode(new Nodes::FunctionInvocationNode(
            "print",
            new vector<Nodes::ExpressionNode*> { new Nodes::ExpressionNode(new Nodes::ConstNode("Hello, World!")) }
        )),
        new Nodes::ExpressionNode(new Nodes::ReturnNode(new Nodes::ExpressionNode(new Nodes::ConstNode("0"))))
    };

    Nodes::BodyNode* body = new Nodes::BodyNode(bodyContent);

    Nodes::FunctionDefinitionNode* expected = new Nodes::FunctionDefinitionNode(
        "main",
        nullptr,
        new DataTypes::Int(),
        body
    );

    Parser parser = Parser(tokens);

    Nodes::INode* out = parser.parseFunc(*parser.groupArguments(*parser.getFunctionContent(tokens, 1)));

    if (!expect_true(typeid(*out) == typeid(*expected), "Comparing types of out and expected:")) return;

    auto outNode = dynamic_cast<Nodes::FunctionDefinitionNode*>(out);
    if (!expect_eq(outNode->name, expected->name) || !expect_true(typeid(*outNode->returnType) == typeid(*expected->returnType), "Compairing returnTypes:")) return;
    if (outNode->args != nullptr) {
        cout << "In this test args must be nullptr!";
        return;
    }
    // остальные проверки
    cout << "\n";
}

void Parser_GroupFunctionsGlobal() {
    cout << "Running ParserGroupFunctionsGlobal:\n";
    string in = R"(
(defn my_func : void,
    (
        (print, "Hello from my_func!")
    )
)

(defn main : int,
    (
        (print, "Hello, World!"),
        return 0
    )
))";

    Lexer lexer = Lexer(in);

    vector<Tokens::IToken*> tokens = lexer.tokenize();

    Parser parser = Parser(tokens);

    vector<vector<Tokens::IToken*>*>* out = parser.groupFunctionsGlobal(tokens);

    if (!expect_eq(out->size(), (size_t)2)) return;
    if (!expect_eq(out->at(0)->size(), (size_t)14)) return;
    if (!expect_eq(out->at(1)->size(), (size_t)17)) return;

    cout << "\n";

}

void Parser_Parse() {
    cout << "Running ParserGroupFunctionsGlobal:\n";

    string in = R"(
(defn my_func : void,
    (
        (print, "Hello from my_func!")
    )
)

(defn main : int,
    (
        (print, "Hello, World!"),
        return 0
    )
))";

    Lexer lexer = Lexer(in);

    vector<Tokens::IToken*> tokens = lexer.tokenize();

    Parser parser = Parser(tokens);

    vector<Nodes::FunctionDefinitionNode*>* out = parser.parse();

    if (!expect_eq(out->size(), (size_t)2)) return;

}




int main()
{
    Lexer_SimpleTest();
    Parser_GetFunctionContent();
    Parser_GroupArgs();
    Parser_MakeExpressionConst();
    Parser_MakeExpressionIdentifier();
    Parser_MakeExpressionFunc();
    Parser_ParseFunc();
    Parser_GroupFunctionsGlobal();
    Parser_Parse();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
