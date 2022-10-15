#include "stdafx.h"

using namespace std;

namespace Parm {
	void ParmAnalyzer::Invoke()
	{
		bool parm_0 = false, parm_1 = false, parm_2 = false;

		for (short i = 1; i < _count; i++)
		{
			// Для In
			if (wcsstr(_parms[i], PARM_IN)) {
				if (wcslen(_parms[i]) > PARM_MAX_SIZE) throw ERROR_THROW(104);

				parm_0 = true;

				wcscpy_s(InPath, _parms[i] + 4);
			}
			// Для Out
			else if (wcsstr(_parms[i], PARM_OUT)) {
				if (wcslen(_parms[i]) > PARM_MAX_SIZE) throw ERROR_THROW(104);

				parm_1 = true;

				wcscpy_s(OutPath, _parms[i] + 5);
			}
			// Для Log
			else if (wcsstr(_parms[i], PARM_LOG)) {
				if (wcslen(_parms[i]) > PARM_MAX_SIZE) throw ERROR_THROW(104);

				parm_2 = true;

				wcscpy_s(LogPath, _parms[i] + 5);
			}
		}

		// Если нет In то ошибка
		if (parm_0 == false) throw ERROR_THROW(100);

		// Если нет Out то создать по умолчанию
		if (parm_1 == false) {
			wcscpy_s(OutPath, L"Result");
			wcsncat_s(OutPath, PARM_OUT_DEF_EXT, 4);
		}
		// Если у out файла не указано расширение
		else if (!wcsstr(OutPath, L"."))
			wcsncat_s(OutPath, PARM_OUT_DEF_EXT, 4);

		// Если нет Log то создать по умолчанию
		if (parm_2 == false) {
			wcscpy_s(LogPath, L"Log");
			wcsncat_s(LogPath, PARM_LOG_DEF_EXT, 4);
		}
		// Если у log файла не указано расширение
		else if (!wcsstr(LogPath, L"."))
			wcsncat_s(LogPath, PARM_LOG_DEF_EXT, 4);
	}
}