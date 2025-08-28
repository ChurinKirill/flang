#pragma once

#include "Tokens.h"
#include <vector>

//namespace Utils {

template<typename T>
void clearVector(std::vector<T*>& vec) {
    for (auto ptr : vec) {
        if (ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    vec.clear();
}

template<typename T>
void clearVector2D(std::vector<std::vector<T*>*>& vec) {
    for (std::vector<T*>* el : vec) {
        clearVector(*el);
        el = nullptr;
    }
    vec.clear();
}

	//bool compareTokens(Tokens::IToken* t1, Tokens::IToken* t2);
//}

