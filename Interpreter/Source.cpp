#include "stdafx.h"

using namespace std;

using namespace Error;
using namespace Parm;
using namespace Log;
using namespace In;
using namespace LexemAnalysis;
using namespace Collections;
using namespace Data;

int _tmain(int argc, TCHAR* argv[]) {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ParmAnalyzer parm(argv, argc);
	Logging log;
	InFile in;

	DefaultLexems* defLex;

	LexemsTable* lexTable;
	LiteralsColletion* rawLit;

	LexemAnalysis::LexemAnalyser lexAnalyzer;

	try
	{
		cout << "<========= �������� ������� ���������� ========>" << endl;
		parm.Invoke();

		log = Logging(parm.LogPath);

		log.WriteHeader();
		log.WriteParm(parm);

		cout << "<======= �������� ������ �� ����������� =======>" << endl;
		log.WriteLine("\n<======= �������� ������ �� ����������� =======>\n", "");
		in = InFile(parm.InPath);

		in.Invoke();
		in.Close();

		log.WriteIn(in);

		cout << "<========= �������� ������ ���������! =========>" << endl;
		log.WriteLine("\n<========= �������� ������ ���������! =========>", "");

		defLex = new DefaultLexems();
		lexTable = new LexemsTable();
		rawLit = new LiteralsColletion();

		lexAnalyzer = LexemAnalyser(in.Code, defLex, lexTable, rawLit);

		lexAnalyzer.Invoke();

		cout << "<======== ����������� ������ ��������! ========>" << endl << endl;
		log.WriteLine("\n<======== ����������� ������ ��������! ========>", "");

		log.WriteLexemAnalysisResult(*lexTable, *rawLit);

		cout << "��������� ��� ������!" << endl;
	}
	catch (LineError err)
	{
		log.WriteError(&err);

		cout << "������ ��������� � ��������!" << endl;
		cout << err.ToString() << endl;
	}
	catch (ErrorBase err)
	{
		log.WriteError(&err);

		cout << "������ ��������� � ��������!" << endl;
		cout << err.ToString() << endl;
	}

	log.Close();
}