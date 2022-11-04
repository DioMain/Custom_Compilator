#pragma once

#define LEXEM_ANALYSER_ENDL '\n'
#define LEXEM_ANALYSER_CODEEND '\0'
#define LEXEM_ANALYSER_SPACE ' '
#define LEXEM_ANALYSER_STR '\"'
#define LEXEM_ANALYSER_CHAR '\''

namespace LexemAnalysis {
	enum class LiteralType
	{
		None, Indefier, Expression, LogicEpression
	};

	class LexemAnalyser {
	public:

		bool ENDL = false,
			CODEEND = false,
			SPACE = false,
			SPECIAL = false,
			STRINGEXP = false,
			PARAMS = false,
			NAMESPACE = false,
			LITERAL = false,
			CONSTREAD = false;

		int line = 1, col = 1, index = 0;

		char letter = ' ';
		std::string expression;
		Data::BasicLexem* currentLexem;

		std::string dataBuffer;
		std::string namespaceBuffer;

		LiteralType litType = LiteralType::None;

		std::vector<char> constReadEndSybols;

		int namespaceCount = 0,
			paramsDepth = 0;

		std::vector<std::string> namespaces;

		Collections::DefaultLexems* lexDef;
		Collections::LexemsTable* lexTable;
		Collections::LiteralsColletion* literals;

		LexemAnalyser() : code(nullptr), lexDef(nullptr), lexTable(nullptr), literals(nullptr), currentLexem(nullptr) { }

		LexemAnalyser(char* code, Collections::DefaultLexems* lexDef, Collections::LexemsTable* lexTable, Collections::LiteralsColletion* literals)
						: code(code), lexDef(lexDef), lexTable(lexTable), literals(literals), currentLexem(nullptr) { }

		void Invoke();

		void PrepareNamespace(std::string spacename);
		void OpenNamespace();
		void CloseNamespace();
		std::string GetFrontNamespace();

		void ReadLiteral(LiteralType type, std::vector<char> endSymbols);
		void ReadLiteral(LiteralType type, char endSymbol);

		void ParsingParam(std::string param);

		bool IsSpecialSymbol(char symbol);

	private:

		char* code;

	};
}