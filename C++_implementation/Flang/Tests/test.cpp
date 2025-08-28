#include "pch.h"
#include <Lexer.h>
#include <Parser.h>
#include <typeinfo>

//template<typename T>
//void clearVector(std::vector<T*>& vec) {
//    for (auto ptr : vec) {
//        if (ptr != nullptr) {
//            delete ptr;
//            ptr = nullptr;
//        }
//    }
//    vec.clear();
//}

bool compareTokens(Tokens::IToken* t1, Tokens::IToken* t2) {
    if (t1 == nullptr || t2 == nullptr)
        return false;
    if (typeid(*t1) != typeid(*t2))
        return false;

    if (typeid(*t1) == typeid(Tokens::Identifier)) {
        Tokens::Identifier* s1 = dynamic_cast<Tokens::Identifier*>(t1);
        Tokens::Identifier* s2 = dynamic_cast<Tokens::Identifier*>(t2);

        return s1->value == s2->value;
    }
    if (typeid(*t1) == typeid(Tokens::ConstValue)) {
        Tokens::ConstValue* s1 = dynamic_cast<Tokens::ConstValue*>(t1);
        Tokens::ConstValue* s2 = dynamic_cast<Tokens::ConstValue*>(t2);

        return s1->value == s2->value;
    }
    if (typeid(*t1) == typeid(Tokens::Keyword)) {
        Tokens::Keyword* s1 = dynamic_cast<Tokens::Keyword*>(t1);
        Tokens::Keyword* s2 = dynamic_cast<Tokens::Keyword*>(t2);

        return typeid(*s1->value) == typeid(*s2->value);
    }
    if (typeid(*t1) == typeid(Tokens::DataType)) {
        Tokens::DataType* s1 = dynamic_cast<Tokens::DataType*>(t1);
        Tokens::DataType* s2 = dynamic_cast<Tokens::DataType*>(t2);

        return typeid(*s1->value) == typeid(*s2->value);
    }
    return true;
};

TEST(LexerTests, SimpleTest) {
    std::string in = R"(
(fn main : int,
    (
        (print, "Hello, World!"),
        return 0
    )
))";
    Lexer lexer = Lexer(in);

    std::vector<Tokens::IToken*> expected {
        new Tokens::LBr{},
        new Tokens::Keyword(new Tokens::Fn{}),
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


    std::vector<Tokens::IToken*> out = lexer.tokenize();


    EXPECT_EQ(out.size(), expected.size());

    for (size_t i = 0; i < out.size(); i++) {
        EXPECT_TRUE(compareTokens(expected[i], out[i]));
    }

    /*clearVector(out);
    clearVector(expected);*/
}

TEST(ParserTests, GetFunctionContent) {
    const std::vector<Tokens::IToken*> in {
        new Tokens::Keyword(new Tokens::Fn{}),
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

    std::vector<Tokens::IToken*> expected {
        new Tokens::Keyword(new Tokens::Fn{}),
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


    std::vector<Tokens::IToken*>* out = parser.getFunctionContent(in, 0);

    std::vector<Tokens::IToken*> res = *out;

    EXPECT_EQ(res.size(), expected.size());

    for (size_t i = 0; i < res.size(); i++) {
        EXPECT_TRUE(compareTokens(expected[i], res[i]));
    }

    /*clearVector(in);
    clearVector(res);
    clearVector(expected);*/
}

TEST(ParserTests, GroupArguments) {
    std::vector<Tokens::IToken*> in {
        new Tokens::Keyword(new Tokens::Fn{}),
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

    std::vector<std::vector<Tokens::IToken*>*> expected;

    std::vector<Tokens::IToken*> v1 { 
        new Tokens::Keyword(new Tokens::Fn{}),
        new Tokens::Identifier("main"),
        new Tokens::Colon{},
        new Tokens::DataType(new DataTypes::Int{})
    };
    std::vector<Tokens::IToken*> v2 { 
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


    std::vector<std::vector<Tokens::IToken*>*>* out = parser.groupArguments(in);

    std::vector<std::vector<Tokens::IToken*>*> res = *out;

    EXPECT_EQ(res.size(), expected.size());

    for (size_t i = 0; i < res.size(); i++) {
        EXPECT_EQ(res[i]->size(), expected[i]->size());
        for (size_t j = 0; j < res[i]->size(); j++) {
            EXPECT_TRUE(compareTokens(res[i]->at(j), expected[i]->at(j)));
        }
    }

    /*clearVector(in);
    for (auto el : res)
        clearVector(*el);
    res.clear();
    for (auto el : expected)
        clearVector(*el);
    expected.clear();*/
}
