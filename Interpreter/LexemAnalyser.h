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

		// ����� ����������� / ANALYSATOR FLAGS
		bool ENDL = false,			// ����� ������	/ End line
			CODE_END = false,		// ����� ����		/ Code end
			EXP_EMPTY = false,		// ��������� ������	/ Expression is empty
			SPACE = false,			// ������	/ Space
			SPECIAL = false,		// ����������� ������	/ Special symbol
			STRING_EXP = false,		// ��������� ���������	/ String expression
			PARAMS = false,			// ��� ������ � �����������	/ Now work with params
			NAMESPACE = false,		// ��� ������ � �����. ���	/ Now work with namespace
			LITERAL = false,		// ��������� ���� �������	/ Expression is literal
			NEED_LITERAL = false,	// ����������� ����� �������	/ The analyzer needs literal
			CONST_READ = false,		// ����� ����������� ����������	/ Constant reads mode
			PARAM_READ = false,		// �������� ��� ����������� ��������	/ Param reads pointer
			READ_STOP = false,		// ���������� ������������	/ Reading is end
			COMMENT = false,		// ����� �����������	/ Comment mode
			IF = false,				// ��� ������ � �������� (����)	/ Now work with condition (IF)
			ELSE = false;			// ��� ������ � �������� (�����)	/ Now work with condition (ELSE)

		int line = 0,				// ����������� ������	/ Current string
			col = 0,				// ����������� ������ � ������	/ Current symbol index in string
			index = 0;				// ������ ������������ �������	/ Current symbol index

		char letter = ' ';				// ����������� ������	/ Current symbol
		std::string expression;			// ���������	/ Expression
		Data::BasicLexem* currentLexem;	// �������	/ Lexem

		std::string namespaceBuffer;	// ������ ����������� ���	/ Namespace buffer

		LiteralType litType = LiteralType::None;	// ����� ������� �����������	/ Wait is literal reads

		std::vector<char> constReadEndSybols;		// ������ �������� �� ������� ��� ���������� ��������	/ List of symbols to complete reading a literal

		int namespaceCounter = 0;			// ������� ����������� ���	/ Namespace counter

		std::vector<std::string> namespaces;		// ������ ���������� ���	/ List of namespaces

		Collections::DefaultLexems* lexDef;			// ��������� �� ������ ����������� ������	/ Ptr to list of default lexems
		Collections::LexemsTable* lexTable;			// ��������� �� ������� ������				/ Ptr to lexem table
		Collections::LiteralsColletion* literals;	// ��������� �� ������ ���������			/ Ptr to list of literal

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