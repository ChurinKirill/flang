#pragma once
#ifndef DATATYPES_H
#define DATATYPES_H

namespace DataTypes {
	struct IDataType {};

	struct Int : IDataType {};
	struct Float : IDataType {};
	struct Str : IDataType {};
	struct Bool : IDataType {};
	struct Void : IDataType {};
}

#endif // !_DATATYPES_H_
