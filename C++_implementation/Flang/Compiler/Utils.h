#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "Tokens.h"

namespace Utils {

	template<typename T>
	void clearVector(std::vector<T*>& vec);

	template<typename T>
	void clearVector2D(std::vector<std::vector<T*>*>& vec);

	bool compareTokens(Tokens::IToken* t1, Tokens::IToken* t2);
}



#endif // !UTILS_H
