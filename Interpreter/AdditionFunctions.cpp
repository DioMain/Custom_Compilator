#include "stdafx.h"

using namespace std;

Parsing::VarType GetVarTypeByName(string typeName)
{
	if (typeName == "число")
		return Parsing::VarType::Integer;
	else if (typeName == "строка")
		return Parsing::VarType::String;
	else if (typeName == "символ")
		return Parsing::VarType::Char;
	else
		return Parsing::VarType::Void;
}
