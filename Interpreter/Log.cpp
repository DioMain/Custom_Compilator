#include "stdafx.h"

using namespace std;

namespace Log {
	Logging::Logging(wchar_t* path) {
		stream = new ofstream(path);

		if (!stream->is_open()) throw ERROR_THROW(112);
	}

	void Logging::WriteLine(char* str ...) {
		if (stream == nullptr || !stream->is_open()) return;

		char* nowstr = nullptr;

		int n = 0;
		do
		{
			nowstr = *(&str + n);

			*stream << nowstr;

			n++;

		} while (strlen(nowstr) != 0);
	}
	void Logging::WriteLine(wchar_t* str ...) {
		if (stream == nullptr || !stream->is_open()) return;

		char* nowstr = nullptr;

		int n = 0;
		do
		{
			size_t len = wcslen(*(&str + n)) + 1;
			nowstr = new char[len];

			wcstombs_s(0, nowstr, len, *(&str + n), len - 1);	// Переобразование wchar_t в char

			*stream << nowstr;

			n++;

		} while (strlen(nowstr) != 0);
	}

	void Logging::WriteHeader() {
		if (stream == nullptr || !stream->is_open()) return;

		time_t rltime = time(0);		// Получение текучщей даты и времени

		tm* fdtm = new tm();			// Выделение пямяти под форматированное время

		localtime_s(fdtm, &rltime);		// Преобразование в форматированное время

		char* buf = new char[200];		// Буффер

		strftime(buf, 200, " Дата создания протокола: %c", fdtm);	// Заполнение буффера текущем временем

		*stream << "<------------------ Протокол ------------------>" << endl;
		*stream << buf << endl;
	}

	void Logging::WriteParm(Parm::ParmAnalyzer parm) {
		if (stream == nullptr || !stream->is_open()) return;

		char* nowstr = new char[PARM_MAX_SIZE];

		*stream << "<------------- Входные параметры -------------->" << endl;

		wcstombs_s(0, nowstr, PARM_MAX_SIZE, parm.InPath, PARM_MAX_SIZE);
		*stream << " -in: " << nowstr << endl;

		wcstombs_s(0, nowstr, PARM_MAX_SIZE, parm.OutPath, PARM_MAX_SIZE);
		*stream << " -out: " << nowstr << endl;

		wcstombs_s(0, nowstr, PARM_MAX_SIZE, parm.LogPath, PARM_MAX_SIZE);
		*stream << " -log: " << nowstr << endl;
	}

	void Logging::WriteIn(In::InFile in) {
		if (stream == nullptr || !stream->is_open()) return;

		*stream << "<-------------- Исходные данные --------------->" << endl;

		*stream << " Кол-во символов: " << in.SizeOfCode << endl;
		*stream << " Кол-во строк: " << in.LinesCount << endl;
		*stream << " Проигнорировано: " << in.IgnoreCount << endl;
	}

	void Logging::WriteError(Error::ErrorBase* error) {
		if (stream == nullptr || !stream->is_open()) return;

		*stream << endl;

		*stream << "<------------- Информация об ошибке -------------->" << endl;

		*stream << error->ToString() << endl;
	}

	void Logging::Close() {
		if (stream != nullptr && stream->is_open()) stream->close();
	}
}