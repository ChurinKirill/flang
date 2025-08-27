#include "pch.h"
#include "Utils.h"
#include <typeinfo>

template<typename T>
void Utils::clearVector(std::vector<T*>& vec) {
    for (auto ptr : vec) {
        if (ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    vec.clear();
}

template<typename T>
void Utils::clearVector2D(std::vector<std::vector<T*>*>& vec) {
    for (std::vector<T*>* el : vec) {
        clearVector(*el);
        el = nullptr;
    }
    vec.clear();
}

bool Utils::compareTokens(Tokens::IToken* t1, Tokens::IToken* t2) {
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
