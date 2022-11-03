#include "stdafx.h"

using namespace std;

LegecyLexemAnalyzer::VarType GetVarTypeByName(string typeName)
{
	if (typeName == "int")
		return LegecyLexemAnalyzer::VarType::Integer;
	else if (typeName == "string")
		return LegecyLexemAnalyzer::VarType::String;
	else if (typeName == "char")
		return LegecyLexemAnalyzer::VarType::Char;
	else if (typeName == "bool")
		return LegecyLexemAnalyzer::VarType::Bool;
	else
		return LegecyLexemAnalyzer::VarType::Void;
}
