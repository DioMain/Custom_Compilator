#pragma once

#define IN_MAX_LEN_TEXT 1024*1024		// Максимальный размер исходного кода 1 mb
#define IN_CODE_ENDL '\n'				// Символ конца строки
#define IN_SPACE ' '					// Символ пробела

// Таблица разрешённых, запрещённых, заменяемых и игнорируемых символов
// Таблица Windows-1251
// F - запрещённый, T - разрешённый, I - игнорирование, '{символ}' - замена на {символ}.

					//	  0      1      2	   3	  4		 5		6	   7	  8		 9		A	   B	  C		 D		E	   F

#define IN_CODE_TABLE	{\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
																																	   \
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::F, in::F, in::F, in::F, in::F, in::F, in::F, in::F,\
						in::I, in::T, in::T, in::F, in::F, in::F, in::F, in::T, in::T, in::I, in::I, in::T, in::I, in::I, in::I, in::I,\
						in::F, in::F, in::F, in::F, in::F, in::F, in::F, in::T, in::T, in::T, in::T, in::T, in::I, in::I, in::I, in::I,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T,\
						in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T, in::T \
						}

namespace In {
	// T - Допустимый символ; F - Недопоустимый символ; I - игнорировать
	enum in
	{
		T = 1024, F = 2048, I = 4096
	};

	class InFile
	{
	public:
		
		int SizeOfCode;		// Кол-во символов
		int LinesCount;		// Кол-во строк
		int IgnoreCount;	// Кол-во проигнорированных символов

		char* Code;	//Исходный код

		InFile() : code_table(nullptr), SizeOfCode(0), LinesCount(0), IgnoreCount(0), Code(nullptr), stream(nullptr) { }

		InFile(wchar_t* path);

		void Invoke();

		void Close();
		
	private:

		std::ifstream* stream;

		int* code_table;	// Табилица проверки: T, F, I	новое значение
	};
};