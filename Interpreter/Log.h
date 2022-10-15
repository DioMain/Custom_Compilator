#pragma once

namespace Log {
	class Logging
	{
	public:

		Logging() : stream(nullptr) { }
		Logging(wchar_t* path);

		// Записывает массив строк в log фаил, последняя строка должна быть пустой (char)
		void WriteLine(char* str ...);
		// Записывает массив строк в log фаил, последняя строка должна быть пустой (wchar_t)
		void WriteLine(wchar_t* str ...);

		// Записывает в log фаил инфармацию о протоколе
		void WriteHeader();

		// Записывает в log фаил инфармацию о входных параметрах
		void WriteParm(Parm::ParmAnalyzer parm);

		// Записывает в log фаил инфармацию об входных данных
		//void WriteIn(log lg, In::in inner);

		// Записывает в log фаил инфармацию об ошибке
		void WriteError(Error::ErrorBase error);

		// Закрывает поток log файла
		void Close();

	private:

		std::ofstream* stream;
	};

}