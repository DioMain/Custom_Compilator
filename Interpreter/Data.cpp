#include "stdafx.h"

using namespace std;

namespace Parsing {
	void DataContainer::Init() {
		BasicLexems.push_back(Lexem(LexemType::VarType, "число"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "строка"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "символ"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "пусто"));

		BasicLexems.push_back(Lexem(LexemType::Indefier, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::Equals, "="));

		BasicLexems.push_back(Lexem(LexemType::Expression, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::RuleEnd, ";"));

		BasicLexems.push_back(Lexem(LexemType::ParamsIn, "("));
		BasicLexems.push_back(Lexem(LexemType::ParamsOut, ")"));

		BasicLexems.push_back(Lexem(LexemType::SpaceIn, "{"));
		BasicLexems.push_back(Lexem(LexemType::SpaceOut, "}"));

		BasicLexems.push_back(Lexem(LexemType::Namespace, "пространство"));

		BasicLexems.push_back(Lexem(LexemType::And, ","));

		BasicLexems.push_back(Lexem(LexemType::Main, "Вход"));
		BasicLexems.push_back(Lexem(LexemType::Return, "вернуть"));
		BasicLexems.push_back(Lexem(LexemType::IgnoreMain, "ИгнорироватьВход"));

		BasicLexems.push_back(Lexem(LexemType::If, "Если"));
		BasicLexems.push_back(Lexem(LexemType::Else, "Иначе"));

		BasicLexems.push_back(Lexem(LexemType::LogicExpression, PARSING_UNDEF_LEXEM_NAME));

		//BasicLexems.push_back(Lexem(LexemType::LogicAnd, "&&"));
		//BasicLexems.push_back(Lexem(LexemType::LogicAnd, "И"));

		//BasicLexems.push_back(Lexem(LexemType::LogicOr, "Если"));
		//BasicLexems.push_back(Lexem(LexemType::LogicOr, "Если"));
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

		if (availableLexems.size() != 1 || availableLexems[0].name.size() != name.size())
			return Lexem(LexemType::Void, "void");

		return availableLexems.front();
	}
}