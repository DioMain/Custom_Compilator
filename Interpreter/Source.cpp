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
		cout << "<========= Обрабока входных параметров ========>" << endl;
		parm.Invoke();

		log = Logging(parm.LogPath);

		log.WriteHeader();
		log.WriteParm(parm);

		cout << "<======= Проверка текста на доступность =======>" << endl;
		log.WriteLine("\n<======= Проверка текста на доступность =======>\n", "");
		in = InFile(parm.InPath);

		in.Invoke();
		in.Close();

		log.WriteIn(in);

		cout << "<========= Проверка текста завершена! =========>" << endl << endl;
		log.WriteLine("\n<========= Проверка текста завершена! =========>", "");

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

		//log.WriteLine("\n\n<===== Результат лексического анализатора =====>\n", "");
		//log.WriteData(*container);

		cout << "Завершено без ошибок!" << endl;
	}
	catch (LineError err)
	{
		log.WriteError(&err);

		cout << "Работа завершина с ошибками!" << endl;
		cout << err.ToString() << endl;
	}
	catch (ErrorBase err)
	{
		log.WriteError(&err);

		cout << "Работа завершина с ошибками!" << endl;
		cout << err.ToString() << endl;
	}

	log.Close();
}