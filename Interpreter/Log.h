#pragma once

namespace Log {
	class Logging
	{
	public:

		bool MOREINFO = true;

		Logging() : stream(nullptr) { }
		Logging(wchar_t* path);

		// Записывает массив строк в log фаил, последняя строка должна быть пустой (char)
		void WriteLine(const char* str ...);
		// Записывает массив строк в log фаил, последняя строка должна быть пустой (wchar_t)
		void WriteLine(const wchar_t* str ...);

		// Записывает в log фаил инфармацию о протоколе
		void WriteHeader();

		// Записывает в log фаил инфармацию о входных параметрах
		void WriteParm(Parm::ParmAnalyzer parm);

		void WriteLexemAnalysisResult(Collections::LexemsTable table, 
									Collections::LiteralsColletion lits);

		void WriteSyntaxAnalysisResult(Collections::RuleColletion resultRules, 
									Collections::IndefierColletion idefiers, 
									Collections::DefaultLexems defLexems);

		// Записывает в log фаил инфармацию об входных данных
		void WriteIn(In::InFile in);

		// Записывает в log фаил инфармацию об ошибке
		void WriteError(Error::ErrorBase* error);

		// Закрывает поток log файла
		void Close();

		static std::string GetOpeartorSymbolsByType(Data::ExpressionElementType type);

	private:

		void RuleExpressionsOutPut(std::vector<Data::ExpressionNode*> exps, int deep);

		std::ofstream* stream;
	};

}