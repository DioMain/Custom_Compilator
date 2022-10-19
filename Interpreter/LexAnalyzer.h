#pragma once

#define PARSING_LEX_END  ' '
#define PARSING_LINE_END '\n'
#define PARSING_COM_END  ';'
#define PARSING_CODE_END '\0'
#define PARSING_STRING '\"'

namespace Parsing {
	class LexAnalyzer
	{
	public:

		LexAnalyzer() : data(nullptr), code(nullptr) { }

		LexAnalyzer(char* code, DataContainer* data) : code(code), data(data) { }

		void Invoke();

	private:

		void LexSwitch(Lexem lex);

		Lexem GetLexem(std::string lexString);

		Lexem CreateVar(std::string indefier);

		Lexem CreateLiteral(std::string literal);

		bool LEX_END = false,
			COM_END = false,
			CODE_END = false,
			LINE_END = false,
			LITERAL = false,
			EXPRESSION = false,
			INDEFIER = false;

		char* code;

		DataContainer* data;

	};
}