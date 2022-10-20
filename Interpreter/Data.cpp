#include "stdafx.h"

using namespace std;

namespace Parsing {
	void DataContainer::Init() {
		BasicLexems.push_back(Lexem(LexemType::Declare, "declare"));

		BasicLexems.push_back(Lexem(LexemType::VarType, "integer"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "string"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "char"));

		BasicLexems.push_back(Lexem(LexemType::Indefier, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::Equals, "="));

		BasicLexems.push_back(Lexem(LexemType::Literal, PARSING_UNDEF_LEXEM_NAME));
		BasicLexems.push_back(Lexem(LexemType::Poland, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::CommandEnd, ";"));
	}

	Lexem DataContainer::GetBasicLexem(std::string name)
	{
		vector<Lexem> availableLexems = BasicLexems;

		for (int i = 0; i < name.size(); i++)
		{
			for (int j = 0; j < availableLexems.size(); j++)
			{
				if (name[i] != availableLexems[j].name[i]) {
					availableLexems.erase(availableLexems.begin() + j);
					j--;
				}
			}
		}

		if (availableLexems.size() != 1) return Lexem(LexemType::Void, "void");

		return availableLexems.front();
	}
	Var* DataContainer::GetVar(std::string indifier)
	{
		vector<Var*> availableVars = Vars;

		for (int i = 0; i < indifier.size(); i++)
		{
			for (int j = 0; j < availableVars.size(); j++)
			{
				if (indifier[i] != availableVars[j]->indefier[i] ) {
					availableVars.erase(availableVars.begin() + j);
					j--;
				}
			}
		}

		if (availableVars.size() != 1) return nullptr;

		return availableVars.front();
	}

	Var::Var(std::string typeName)
	{
		indefier = "";
		literalIndex = PARSING_VAR_UNINIT;

		if (typeName == "integer")
			type = VarType::Integer;
		else if (typeName == "string")
			type = VarType::String;
		else if (typeName == "char")
			type = VarType::Char;
		else
			type = VarType::Void;
	}
}