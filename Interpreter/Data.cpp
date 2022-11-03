#include "stdafx.h"

using namespace std;

namespace LegecyLexemAnalyzer {
	void DataContainer::Init() {
		BasicLexems.push_back(Lexem(LexemType::VarType, "int"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "string"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "char"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "bool"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "void"));

		BasicLexems.push_back(Lexem(LexemType::Indefier, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::Equals, "="));

		BasicLexems.push_back(Lexem(LexemType::Expression, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::RuleEnd, ";"));

		BasicLexems.push_back(Lexem(LexemType::ParamsIn, "("));
		BasicLexems.push_back(Lexem(LexemType::ParamsOut, ")"));

		BasicLexems.push_back(Lexem(LexemType::SpaceIn, "{"));
		BasicLexems.push_back(Lexem(LexemType::SpaceOut, "}"));

		BasicLexems.push_back(Lexem(LexemType::Namespace, "namespace"));

		BasicLexems.push_back(Lexem(LexemType::And, ","));

		BasicLexems.push_back(Lexem(LexemType::Main, "Main"));
		BasicLexems.push_back(Lexem(LexemType::Return, "return"));

		BasicLexems.push_back(Lexem(LexemType::If, "if"));
		BasicLexems.push_back(Lexem(LexemType::Else, "else"));

		BasicLexems.push_back(Lexem(LexemType::Comment, "//"));

		BasicLexems.push_back(Lexem(LexemType::LogicExpression, PARSING_UNDEF_LEXEM_NAME));
	}

	/// <summary>
	/// Функция выполняющая разбор имени(цепочки) и поиск нужной лексемы
	/// </summary>
	/// <param name="name"> = Имя(Цепочки) лексемы</param>
	/// <returns>Возврощает нужную лексему</returns>
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