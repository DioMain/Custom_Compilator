#include "stdafx.h"

using namespace std;

Parsing::VarType GetVarTypeByName(string typeName)
{
	if (typeName == "�����")
		return Parsing::VarType::Integer;
	else if (typeName == "������")
		return Parsing::VarType::String;
	else if (typeName == "������")
		return Parsing::VarType::Char;
	else
		return Parsing::VarType::Void;
}
