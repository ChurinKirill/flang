#pragma once
#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include "DataTypes.h"

namespace Tokens
{
	struct IToken {
		virtual ~IToken() = default;
	};
	struct IKeyword {
		virtual ~IKeyword() = default;
	};


	struct Defn : IKeyword {};
	struct Return : IKeyword {};
	struct If : IKeyword {};
	struct While : IKeyword {};
	//struct Body : IKeyword {};
	//struct Args : IKeyword {};


	struct Identifier : IToken {
		std::string value;

		Identifier(std::string value) {
			this->value = value;
		}
	};
	struct ConstValue : IToken {
		std::string value;

		ConstValue(std::string value) {
			this->value = value;
		}
	};
	struct Keyword : IToken {
		IKeyword* value;

		Keyword(IKeyword* value) {
			this->value = value;
		}
	};
	struct DataType : IToken {
		DataTypes::IDataType* value;

		DataType(DataTypes::IDataType* value) {
			this->value = value;
		}
	};
	struct LBr : IToken {};
	struct RBr : IToken {};
	struct Comma : IToken {};
	struct Colon : IToken {};

	/*struct Plus : IToken {};
	struct Minus : IToken {};
	struct Multiply : IToken {};
	struct Divide : IToken {};
	struct Equal : IToken {};
	struct Print : IToken {};*/


}
#endif // !TOKENS_H