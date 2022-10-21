#include "stdafx.h"

using namespace std;

namespace In {
	InFile::InFile(wchar_t* path) {
		stream = new ifstream(path);

		if (!stream->is_open()) throw ERROR_THROW(110);

		code_table = new int[256] IN_CODE_TABLE;

		SizeOfCode = 0;
		LinesCount = 0;
		IgnoreCount = 0;

		Code = nullptr;
	}

	void InFile::Invoke() {
		if (stream == nullptr || !stream->is_open()) return;

		int line = 0, letter = 0;

		bool HaveSpace_Flag = false;

		string rawResult;
		unsigned char currentLetter;
		while (true)
		{
			*stream >> currentLetter >> noskipws;

			if (stream->eof()) break;

			if (currentLetter == '\t') continue;

			// Удаление лишних пробелов
			if (currentLetter == IN_SPACE) {
				if (HaveSpace_Flag) {
					IgnoreCount++;
					continue;
				}
				else HaveSpace_Flag = true;
			}
			else HaveSpace_Flag = false;

			switch (code_table[currentLetter])
			{
			// Обработка разрешенных
			case in::T:

				rawResult.push_back(currentLetter);

				SizeOfCode++;
				LinesCount += currentLetter == IN_CODE_ENDL ? 1 : 0;

				break;
			// Обработка запрещённых
			case in::F:
				throw ERROR_THROW_IN(111, line, letter);
			// Обработка игнора
			case in::I:
				IgnoreCount++;
				continue;
			// Обработка замены
			default:

				rawResult.push_back(code_table[currentLetter]);

				SizeOfCode++;

				break;
			}

			// Переход на следующую строку
			if (currentLetter == IN_CODE_ENDL) {
				letter = 0;
				line++;
			}
			else letter++;
		}

		Code = new char[SizeOfCode];

		for (int i = 0; i < SizeOfCode; i++)
			Code[i] = rawResult[i];

		Code[SizeOfCode] = '\0';
	}

	void InFile::Close() {
		if (stream != nullptr && stream->is_open()) stream->close();
	}
}