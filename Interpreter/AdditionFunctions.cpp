#include "stdafx.h"

using namespace std;

LexemAnalyzer::VarType GetVarTypeByName(string typeName)
{
	if (typeName == "int")
		return LexemAnalyzer::VarType::Integer;
	else if (typeName == "string")
		return LexemAnalyzer::VarType::String;
	else if (typeName == "char")
		return LexemAnalyzer::VarType::Char;
	else if (typeName == "bool")
		return LexemAnalyzer::VarType::Bool;
	else
		return LexemAnalyzer::VarType::Void;
}
