#pragma once

#define PARSING_LEX_END  ' '
#define PARSING_LINE_END '\n'
#define PARSING_COM_END  ';'
#define PARSING_CODE_END '\0'
#define PARSING_STRING '\"'

#define PARSING_LITERA_LEXEM(id) Parsing::Lexem(Parsing::LexemType::Literal, PARSING_UNDEF_LEXEM_NAME, Parsing::LinkType::Literal, id)

namespace Parsing {
	class LexAnalyzer
	{
	public:

		LexAnalyzer() : data(nullptr), code(nullptr) { }

		LexAnalyzer(char* code, DataContainer* data) : code(code), data(data) { }

		void Invoke();

	private:

		std::string ExpressionConvert(std::string exp);

		void LexSwitch(Lexem lex);

		Lexem CreateVar(std::string indefier);

		Lexem CreateLiteral();

		Var* CurVar = nullptr;

		std::string databuffer;

		bool LEX_END = false,
			COM_END = false,
			CODE_END = false,
			LINE_END = false,
			ISRIGHT_EXP = false,
			LITERAL = false,
			EXPRESSION = false,
			INDEFIER = false;

		int index = 0,
			letI = 0,
			lineI = 0;

		char* code;

		DataContainer* data;

	};
}