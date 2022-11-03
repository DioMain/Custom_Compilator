#pragma once

namespace AltLexemAnalyzer {
	class LexemAnalyzer {
	public:

		LexemAnalyzer() : code(nullptr), lexDef(nullptr), lexTable(nullptr), literals(nullptr) { }

		LexemAnalyzer(char* code, Collections::DefaultLexems* lexDef, Collections::LexemsTable* lexTable, Collections::LiteralsColletion* literals)
						: code(code), lexDef(lexDef), lexTable(lexTable), literals(literals) { }

		void Invoke();

	private:

		bool SOMEFLAG = false;

		Collections::DefaultLexems* lexDef;
		Collections::LexemsTable* lexTable;
		Collections::LiteralsColletion* literals;

		char* code;

	};
}