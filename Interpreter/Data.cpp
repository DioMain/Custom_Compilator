#include "stdafx.h"

using namespace std;

namespace Parsing {
	void DataContainer::Init() {
		BasicLexems.push_back(Lexem(LexemType::VarType, "�����"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "������"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "������"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "�����"));

		BasicLexems.push_back(Lexem(LexemType::Indefier, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::Equals, "="));

		BasicLexems.push_back(Lexem(LexemType::Expression, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::RuleEnd, ";"));

		BasicLexems.push_back(Lexem(LexemType::ParamsIn, "("));
		BasicLexems.push_back(Lexem(LexemType::ParamsOut, ")"));

		BasicLexems.push_back(Lexem(LexemType::SpaceIn, "{"));
		BasicLexems.push_back(Lexem(LexemType::SpaceOut, "}"));

		BasicLexems.push_back(Lexem(LexemType::Namespace, "������������"));

		BasicLexems.push_back(Lexem(LexemType::And, ","));

		BasicLexems.push_back(Lexem(LexemType::Main, "����"));
		BasicLexems.push_back(Lexem(LexemType::Return, "�������"));
		BasicLexems.push_back(Lexem(LexemType::IgnoreMain, "����������������"));

		BasicLexems.push_back(Lexem(LexemType::If, "����"));
		BasicLexems.push_back(Lexem(LexemType::Else, "�����"));

		BasicLexems.push_back(Lexem(LexemType::LogicExpression, PARSING_UNDEF_LEXEM_NAME));

		//BasicLexems.push_back(Lexem(LexemType::LogicAnd, "&&"));
		//BasicLexems.push_back(Lexem(LexemType::LogicAnd, "�"));

		//BasicLexems.push_back(Lexem(LexemType::LogicOr, "����"));
		//BasicLexems.push_back(Lexem(LexemType::LogicOr, "����"));
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