#include "stdafx.h"

using namespace std;

Parsing::VarType GetVarTypeByName(string typeName)
{
	if (typeName == "integer")
		return Parsing::VarType::Integer;
	else if (typeName == "string")
		return Parsing::VarType::String;
	else if (typeName == "char")
		return Parsing::VarType::Char;
	else
		return Parsing::VarType::Void;
}
