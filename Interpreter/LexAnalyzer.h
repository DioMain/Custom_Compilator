#pragma once

#define PARSING_LEX_END  ' '
#define PARSING_LINE_END '\n'
#define PARSING_COM_END  ';'
#define PARSING_CODE_END '\0'
#define PARSING_STRING '\"'

#define PARSING_LITERA_LEXEM(id) Parsing::Lexem(Parsing::LexemType::Expression, PARSING_UNDEF_LEXEM_NAME, Parsing::LinkType::Literal, id)

namespace Parsing {
	class LexAnalyzer
	{
	public:

		LexAnalyzer() : data(nullptr), code(nullptr), varTypeBuffer(VarType::Void) { }

		LexAnalyzer(char* code, DataContainer* data) : code(code), data(data), varTypeBuffer(VarType::Void) { }

		void Invoke();

	private:

		DataContainer* data;

		int index = 0,
			letI = 0,
			lineI = 0;

		char* code;

		std::string dataBuffer;
		std::string indefierBuffer;
		std::string FuncBuffer;
		std::string namespaceBuffer;
		VarType varTypeBuffer;

		std::vector<std::string> namespaces;

		ParamType ParamParsing(std::string param);

		bool IsHaveEqualLiteral(std::string exp);

		void SetDefaultNamespaceBuffer(std::string spacename);

		bool IsReactiveSymbol(char letter);
	};
}