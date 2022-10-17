#include "stdafx.h"

using namespace std;

namespace Parsing {
	void DataContainer::Init() {
		BasicLexems.push_back(Lexem(LexemType::Var, "declare"));

		BasicLexems.push_back(Lexem(LexemType::VarType, "integer"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "string"));
		BasicLexems.push_back(Lexem(LexemType::VarType, "char"));

		BasicLexems.push_back(Lexem(LexemType::Indefier, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::Equals, "="));

		BasicLexems.push_back(Lexem(LexemType::Literal, PARSING_UNDEF_LEXEM_NAME));

		BasicLexems.push_back(Lexem(LexemType::CommandEnd, ";"));
	}
}