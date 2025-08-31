#include "pch.h"
//#include <Lexer.h>
//#include <Parser.h>
//#include <typeinfo>
//
////template<typename T>
////void clearVector(std::vector<T*>& vec) {
////    for (auto ptr : vec) {
////        if (ptr != nullptr) {
////            delete ptr;
////            ptr = nullptr;
////        }
////    }
////    vec.clear();
////}
//
//bool compareTokens(Tokens::IToken* t1, Tokens::IToken* t2) {
//    if (t1 == nullptr || t2 == nullptr)
//        return false;
//    if (typeid(*t1) != typeid(*t2))
//        return false;
//
//    if (typeid(*t1) == typeid(Tokens::Identifier)) {
//        Tokens::Identifier* s1 = dynamic_cast<Tokens::Identifier*>(t1);
//        Tokens::Identifier* s2 = dynamic_cast<Tokens::Identifier*>(t2);
//
//        return s1->value == s2->value;
//    }
//    if (typeid(*t1) == typeid(Tokens::ConstValue)) {
//        Tokens::ConstValue* s1 = dynamic_cast<Tokens::ConstValue*>(t1);
//        Tokens::ConstValue* s2 = dynamic_cast<Tokens::ConstValue*>(t2);
//
//        return s1->value == s2->value;
//    }
//    if (typeid(*t1) == typeid(Tokens::Keyword)) {
//        Tokens::Keyword* s1 = dynamic_cast<Tokens::Keyword*>(t1);
//        Tokens::Keyword* s2 = dynamic_cast<Tokens::Keyword*>(t2);
//
//        return typeid(*s1->value) == typeid(*s2->value);
//    }
//    if (typeid(*t1) == typeid(Tokens::DataType)) {
//        Tokens::DataType* s1 = dynamic_cast<Tokens::DataType*>(t1);
//        Tokens::DataType* s2 = dynamic_cast<Tokens::DataType*>(t2);
//
//        return typeid(*s1->value) == typeid(*s2->value);
//    }
//    return true;
//};
//
//TEST(LexerTests, SimpleTest) {
//    std::string in = R"(
//(defn main : int,
//    (
//        (print, "Hello, World!"),
//        return 0
//    )
//))";
//    Lexer lexer = Lexer(in);
//
//    std::vector<Tokens::IToken*> expected {
//        new Tokens::LBr{},
//        new Tokens::Keyword(new Tokens::Defn{}),
//        new Tokens::Identifier("main"),
//        new Tokens::Colon{},
//        new Tokens::DataType(new DataTypes::Int{}),
//        new Tokens::Comma{},
//        new Tokens::LBr{},
//        new Tokens::LBr{},
//        new Tokens::Identifier("print"),
//        new Tokens::Comma{},
//        new Tokens::ConstValue("Hello, World!"),
//        new Tokens::RBr{},
//        new Tokens::Comma{},
//        new Tokens::Keyword(new Tokens::Return{}),
//        new Tokens::ConstValue("0"),
//        new Tokens::RBr{},
//        new Tokens::RBr{}
//    };
//
//
//    std::vector<Tokens::IToken*> out = lexer.tokenize();
//
//
//    EXPECT_EQ(out.size(), expected.size());
//
//    for (size_t i = 0; i < out.size(); i++) {
//        EXPECT_TRUE(compareTokens(expected[i], out[i]));
//    }
//
//    /*clearVector(out);
//    clearVector(expected);*/
//}
//
//TEST(ParserTests, GetFunctionContent) {
//    const std::vector<Tokens::IToken*> in {
//        new Tokens::Keyword(new Tokens::Defn{}),
//        new Tokens::Identifier("main"),
//        new Tokens::Colon{},
//        new Tokens::DataType(new DataTypes::Int{}),
//        new Tokens::Comma{},
//        new Tokens::LBr{},
//        new Tokens::LBr{},
//        new Tokens::Identifier("print"),
//        new Tokens::Comma{},
//        new Tokens::ConstValue("Hello, World!"),
//        new Tokens::RBr{},
//        new Tokens::Comma{},
//        new Tokens::Keyword(new Tokens::Return{}),
//        new Tokens::ConstValue("0"),
//        new Tokens::RBr{},
//        new Tokens::RBr{}
//    };
//
//    Parser parser = Parser(in);
//
//    std::vector<Tokens::IToken*> expected {
//        new Tokens::Keyword(new Tokens::Defn{}),
//        new Tokens::Identifier("main"),
//        new Tokens::Colon{},
//        new Tokens::DataType(new DataTypes::Int{}),
//        new Tokens::Comma{},
//        new Tokens::LBr{},
//        new Tokens::LBr{},
//        new Tokens::Identifier("print"),
//        new Tokens::Comma{},
//        new Tokens::ConstValue("Hello, World!"),
//        new Tokens::RBr{},
//        new Tokens::Comma{},
//        new Tokens::Keyword(new Tokens::Return{}),
//        new Tokens::ConstValue("0"),
//        new Tokens::RBr{}
//    };
//
//
//    std::vector<Tokens::IToken*>* out = parser.getFunctionContent(in, 0);
//
//    std::vector<Tokens::IToken*> res = *out;
//
//    EXPECT_EQ(res.size(), expected.size());
//
//    for (size_t i = 0; i < res.size(); i++) {
//        EXPECT_TRUE(compareTokens(expected[i], res[i]));
//    }
//
//}
//
//TEST(ParserTests, GroupArguments) {
//    std::vector<Tokens::IToken*> in {
//        new Tokens::Keyword(new Tokens::Defn{}),
//        new Tokens::Identifier("main"),
//        new Tokens::Colon{},
//        new Tokens::DataType(new DataTypes::Int{}),
//        new Tokens::Comma{},
//        new Tokens::LBr{},
//        new Tokens::LBr{},
//        new Tokens::Identifier("print"),
//        new Tokens::Comma{},
//        new Tokens::ConstValue("Hello, World!"),
//        new Tokens::RBr{},
//        new Tokens::Comma{},
//        new Tokens::Keyword(new Tokens::Return{}),
//        new Tokens::ConstValue("0"),
//        new Tokens::RBr{}
//    };
//
//    Parser parser = Parser(in);
//
//    std::vector<std::vector<Tokens::IToken*>*> expected;
//
//    std::vector<Tokens::IToken*> v1 { 
//        new Tokens::Keyword(new Tokens::Defn{}),
//        new Tokens::Identifier("main"),
//        new Tokens::Colon{},
//        new Tokens::DataType(new DataTypes::Int{})
//    };
//    std::vector<Tokens::IToken*> v2 { 
//        new Tokens::LBr{},
//        new Tokens::LBr{},
//        new Tokens::Identifier("print"),
//        new Tokens::Comma{},
//        new Tokens::ConstValue("Hello, World!"),
//        new Tokens::RBr{},
//        new Tokens::Comma{},
//        new Tokens::Keyword(new Tokens::Return{}),
//        new Tokens::ConstValue("0"),
//        new Tokens::RBr{}
//    };
//
//    expected.push_back(&v1);
//    expected.push_back(&v2);
//
//
//    std::vector<std::vector<Tokens::IToken*>*>* out = parser.groupArguments(in);
//
//    std::vector<std::vector<Tokens::IToken*>*> res = *out;
//
//    EXPECT_EQ(res.size(), expected.size());
//
//    for (size_t i = 0; i < res.size(); i++) {
//        EXPECT_EQ(res[i]->size(), expected[i]->size());
//        for (size_t j = 0; j < res[i]->size(); j++) {
//            EXPECT_TRUE(compareTokens(res[i]->at(j), expected[i]->at(j)));
//        }
//    }
//}
//
//TEST(ParserTests, MakeExpressionConst) {
//    std::vector<Tokens::IToken*>* in = new std::vector<Tokens::IToken*>();
//    in->push_back(new Tokens::ConstValue("5"));
//    
//
//    Parser parser = Parser(*in);
//
//    Nodes::ExpressionNode expected;
//    expected.content = new Nodes::ConstNode("5");
//
//
//    Nodes::ExpressionNode* out = parser.makeExpression(*in);
//
//
//    ASSERT_EQ(typeid(out->content), typeid(expected.content));
//
//    auto constValOut = dynamic_cast<Nodes::ConstNode*>(out->content);
//    auto constValExpected = dynamic_cast<Nodes::ConstNode*>(expected.content);
//    ASSERT_EQ(constValOut->value, constValExpected->value);
//}
//
//TEST(ParserTests, MakeExpressionIdentifier) {
//    std::vector<Tokens::IToken*>* in = new std::vector<Tokens::IToken*>();
//    in->push_back(new Tokens::Identifier("my_var"));
//
//
//    Parser parser = Parser(*in);
//
//    Nodes::ExpressionNode expected;
//    expected.content = new Nodes::IdentifierNode("my_var");
//
//
//    Nodes::ExpressionNode* out = parser.makeExpression(*in);
//
//
//    ASSERT_EQ(typeid(out->content), typeid(expected.content));
//
//    // пока вручную
//    auto identifierOut = dynamic_cast<Nodes::IdentifierNode*>(out->content);
//    auto identifierExpected = dynamic_cast<Nodes::IdentifierNode*>(expected.content);
//    ASSERT_EQ(identifierOut->name, identifierExpected->name);
//}
//
//TEST(ParserTests, MakeExpressionFunc) {
//    std::vector<Tokens::IToken*>* in = new std::vector<Tokens::IToken*>();
//    in->push_back(new Tokens::LBr);
//    in->push_back(new Tokens::Identifier("+"));
//    in->push_back(new Tokens::Comma);
//    in->push_back(new Tokens::Identifier("a"));
//    in->push_back(new Tokens::Comma);
//    in->push_back(new Tokens::ConstValue("5"));
//    in->push_back(new Tokens::RBr);
//
//
//    Parser parser = Parser(*in);
//
//
//    Nodes::ExpressionNode expected;
//
//    Nodes::ExpressionNode* exp1 = new Nodes::ExpressionNode();
//    exp1->content = new Nodes::IdentifierNode("a");
//
//    Nodes::ExpressionNode* exp2 = new Nodes::ExpressionNode();
//    exp2->content = new Nodes::ConstNode("5");
//
//    Nodes::FunctionInvocationNode* node = new Nodes::FunctionInvocationNode(
//        "+",
//        new vector<Nodes::ExpressionNode*>{
//            exp1,
//            exp2
//        }
//    );
//    expected.content = node;
//
//
//    Nodes::ExpressionNode* out = parser.makeExpression(*in);
//
//
//    ASSERT_EQ(typeid(out->content), typeid(expected.content));
//
//    auto funcInvokeOut = dynamic_cast<Nodes::FunctionInvocationNode*>(out->content);
//    auto funcInvokeExpected = dynamic_cast<Nodes::FunctionInvocationNode*>(expected.content);
//    ASSERT_EQ(funcInvokeOut->name, funcInvokeExpected->name);
//    ASSERT_EQ(funcInvokeOut->args->size(), funcInvokeExpected->args->size());
//    // остальные проверки
//}
//
////TEST(ParserTests, ParseFunc) {
////
////}
