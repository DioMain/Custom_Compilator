#pragma once

#define LEXEM_ANALYSER_ENDL '\n'
#define LEXEM_ANALYSER_CODEEND '\0'
#define LEXEM_ANALYSER_SPACE ' '
#define LEXEM_ANALYSER_STR '\"'
#define LEXEM_ANALYSER_CHAR '\''

namespace LexemAnalysis {
	enum class LiteralType
	{
		None, Indefier, Expression, LogicExpression
	};

	class LexemAnalyser {
	public:

		// ФЛАГИ АНАЛИЗАТОРА / ANALYSATOR FLAGS
		bool ENDL = false,			// Конец строки	/ End line
			CODE_END = false,		// Конец кода		/ Code end
			EXP_EMPTY = false,		// Вырожение пустое	/ Expression is empty
			SPACE = false,			// Пробел	/ Space
			SPECIAL = false,		// Специальный символ	/ Special symbol
			STRING_EXP = false,		// Строковое вырожение	/ String expression
			PARAMS = false,			// Идёт работа с параметрами	/ Now work with params
			NAMESPACE = false,		// Идёт работа с прост. имён	/ Now work with namespace
			LITERAL = false,		// Вырожение есть литерал	/ Expression is literal
			NEED_LITERAL = false,	// Анализатору нужен литерал	/ The analyzer needs literal
			CONST_READ = false,		// Режим постоянного считывания	/ Constant reads mode
			PARAM_READ = false,		// Указание что считывается параметр	/ Param reads pointer
			READ_STOP = false,		// Считывание прекратилось	/ Reading is end
			COMMENT = false,		// Режим комментария	/ Comment mode
			IF = false,				// Идёт работа с условием (ЕСЛИ)	/ Now work with condition (IF)
			ELSE = false;			// Идёт работа с условием (ИНАЧЕ)	/ Now work with condition (ELSE)

		int line = 0,				// Считываемая строка	/ Current string
			col = 0,				// Считываемый символ в строке	/ Current symbol index in string
			index = 0;				// Индекс считываемого символа	/ Current symbol index

		char letter = ' ';				// Считываемый символ	/ Current symbol
		std::string expression;			// Выражение	/ Expression
		Data::BasicLexem* currentLexem;	// Лексема	/ Lexem

		std::string namespaceBuffer;	// Буффер пространсва имён	/ Namespace buffer

		LiteralType litType = LiteralType::None;	// Какой литерал считывается	/ Wait is literal reads

		std::vector<char> constReadEndSybols;		// Список символов до которых идёт считывание литерала	/ List of symbols to complete reading a literal

		int namespaceCounter = 0;			// Счётчик пространств имён	/ Namespace counter

		std::vector<std::string> namespaces;		// Список пространсв имён	/ List of namespaces

		Collections::DefaultLexems* lexDef;			// Указатель на список стандартных лексем	/ Ptr to list of default lexems
		Collections::LexemsTable* lexTable;			// Указатель на таблицу лексем				/ Ptr to lexem table
		Collections::LiteralsColletion* literals;	// Указатель на список литералов			/ Ptr to list of literal

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

		bool LiteralReadEnd();

		void ParsingParam(std::string param);

		bool IsSpecialSymbol(char symbol);

	private:

		char* code;

	};
}