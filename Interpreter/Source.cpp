#include "stdafx.h"

using namespace std;

using namespace Error;
using namespace Parm;
using namespace Log;
using namespace In;
using namespace LexemAnalysis;
using namespace Collections;
using namespace Data;
using namespace SyntaxAnalysis;

int _tmain(int argc, TCHAR* argv[]) {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ParmAnalyzer parm(argv, argc);
	Logging log;
	InFile in;

	DefaultLexems* defLex;
	DefaultRules* defRules;

	LexemsTable* lexTable;
	LiteralsColletion* rawLit;

	RuleColletion* resultRules;
	IndefierColletion* indefiers;

	LexemAnalyser lexAnalyser;
	SyntaxAnalysator synAnalyser;

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

		cout << "<========= Проверка текста завершена! =========>" << endl;
		log.WriteLine("\n<========= Проверка текста завершена! =========>", "");

		defLex = new DefaultLexems();
		lexTable = new LexemsTable();
		rawLit = new LiteralsColletion();

		lexAnalyser = LexemAnalyser(in.Code, defLex, lexTable, rawLit);

		lexAnalyser.Invoke();

		cout << "<======== Лексический анализ завершен! ========>" << endl;
		log.WriteLine("\n<======== Лексический анализ завершен! ========>", "");

		log.WriteLexemAnalysisResult(*lexTable, *rawLit);

		defRules = new DefaultRules();
		resultRules = new RuleColletion();
		indefiers = new IndefierColletion();

		synAnalyser = SyntaxAnalysator(lexTable, defRules, resultRules, indefiers, rawLit);

		synAnalyser.Invoke();

		for (size_t i = 0; i < resultRules->GetSize(); i++)
		{
			poland::PolandNatation::TranslateRecursive(resultRules->Get(i).expressionsRoot);
		}

		cout << "<======= Синтаксический анализ завершен! =======>" << endl << endl;
		log.WriteLine("\n<======= Синтаксический анализ завершен! =======>", "");

		log.WriteSyntaxAnalysisResult(*resultRules, *indefiers, *defLex);

		cout << "Завершено без ошибок!" << endl;
	}
	catch (LineError err)
	{
		cout << endl;

		log.WriteError(&err);

		cout << "Работа завершина с ошибками!" << endl;
		cout << err.ToString() << endl;
	}
	catch (ErrorBase err)
	{
		cout << endl;

		log.WriteError(&err);

		cout << "Работа завершина с ошибками!" << endl;
		cout << err.ToString() << endl;
	}

	log.Close();
}