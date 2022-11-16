#pragma once

namespace Log {
	class Logging
	{
	public:

		bool MOREINFO = true;

		Logging() : stream(nullptr) { }
		Logging(wchar_t* path);

		// ���������� ������ ����� � log ����, ��������� ������ ������ ���� ������ (char)
		void WriteLine(const char* str ...);
		// ���������� ������ ����� � log ����, ��������� ������ ������ ���� ������ (wchar_t)
		void WriteLine(const wchar_t* str ...);

		// ���������� � log ���� ���������� � ���������
		void WriteHeader();

		// ���������� � log ���� ���������� � ������� ����������
		void WriteParm(Parm::ParmAnalyzer parm);

		void WriteLexemAnalysisResult(Collections::LexemsTable table, 
									Collections::LiteralsColletion lits);

		void WriteSyntaxAnalysisResult(Collections::RuleColletion resultRules, 
									Collections::IndefierColletion idefiers, 
									Collections::DefaultLexems defLexems);

		// ���������� � log ���� ���������� �� ������� ������
		void WriteIn(In::InFile in);

		// ���������� � log ���� ���������� �� ������
		void WriteError(Error::ErrorBase* error);

		// ��������� ����� log �����
		void Close();

		static std::string GetOpeartorSymbolsByType(Data::ExpressionElementType type);

	private:

		void RuleExpressionsOutPut(std::vector<Data::ExpressionNode*> exps, int deep);

		std::ofstream* stream;
	};

}