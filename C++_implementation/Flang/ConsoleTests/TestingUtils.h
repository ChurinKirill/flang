#pragma once

#include <Tokens.h>
#include <typeinfo>
#include <iostream>

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


template<typename T>
bool expect_eq(T el1, T el2) {
    if (el1 == el2) {
        std::cout << "\tComparison: " << el1 << " " << el2 << " success\n";
        return true;
    }
    std::cout << "\tComparison: " << el1 << " " << el2 << " failure\n";
    return false;
}

bool expect_true(bool statement, std::string statementMessage) {
    if (statement) {
        std::cout << "\t" << statementMessage << " result is TRUE\n";
        return true;
    }
    std::cout << "\t" << statementMessage << " result is FALSE\n";
    return false;
}
