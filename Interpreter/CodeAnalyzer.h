#pragma once

#define PARSING_LEX_END  ' '
#define PARSING_LINE_END '\n'
#define PARSING_COM_END  ';'
#define PARSING_CODE_END '\0'

namespace Parsing {
	class CodeAnalyzer
	{
	public:

		CodeAnalyzer() : data(nullptr), code(nullptr) { }

		CodeAnalyzer(char* code, DataContainer* data) : code(code), data(data) { }

		void Invoke();

	private:

		Lexem CreateLexem(std::string lexString);

		Lexem CreateVar(std::string indefier);

		Lexem CreateLiteral(std::string literal);

		char* code;

		DataContainer* data;

	};
}