#include "stdafx.h"

using namespace std;

using namespace Error;
using namespace Parm;
using namespace Log;
using namespace In;

int _tmain(int argc, TCHAR* argv[]) {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ParmAnalyzer parm(argv, argc);
	Logging log;
	InFile in;

	try
	{
		parm.Invoke();

		log = Logging(parm.LogPath);

		log.WriteHeader();
		log.WriteParm(parm);

		in = InFile(parm.InPath);

		in.Invoke();
		in.Close();

		log.WriteIn(in);

		cout << in.Code << endl;

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