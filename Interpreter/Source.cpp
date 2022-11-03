#include "stdafx.h"

using namespace std;

using namespace Error;
using namespace Parm;
using namespace Log;
using namespace In;
//using namespace LegecyLexemAnalyzer;
using namespace AltLexemAnalyzer;
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

	AltLexemAnalyzer::LexemAnalyzer lexAnalyzer;

	//LexAnalyzer lex;
	//DataContainer* container = nullptr;

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

		cout << "<========= �������� ������ ���������! =========>" << endl << endl;
		log.WriteLine("\n<========= �������� ������ ���������! =========>", "");

		defLex = new DefaultLexems();
		lexTable = new LexemsTable();
		rawLit = new LiteralsColletion();

		lexAnalyzer = LexemAnalyzer(in.Code, defLex, lexTable, rawLit);

		// LEGACY CODE

		//lexAnalyzer = AltLexemAnalyzer::LexemAnalyzer(in.Code, )

		//container = new DataContainer();

		//container->Init();

		//lex = LexAnalyzer(in.Code, container);

		//lex.Invoke();

		//log.WriteLine("\n\n<===== ��������� ������������ ����������� =====>\n", "");
		//log.WriteData(*container);

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