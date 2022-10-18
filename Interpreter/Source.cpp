#include "stdafx.h"

using namespace std;

using namespace Error;
using namespace Parm;
using namespace Log;
using namespace In;
using namespace Parsing;
using namespace poland;

int _tmain(int argc, TCHAR* argv[]) {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ParmAnalyzer parm(argv, argc);
	Logging log;
	InFile in;
	CodeAnalyzer analyzer;

	DataContainer* container = nullptr;

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

		container = new DataContainer();

		container->Init();

		analyzer = CodeAnalyzer(in.Code, container);

		analyzer.Invoke();

		cout << in.Code << endl;

		cout << "��������� ��� ������!" << endl;

		PolandNatation pol("1+2*3+4-5");

		cout << pol.ToString() << endl;

		cout << pol.CalculateResult() << endl;
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