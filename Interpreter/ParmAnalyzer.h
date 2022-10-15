#pragma once

#define PARM_IN L"-in:"
#define PARM_OUT L"-out:"
#define PARM_LOG L"-log:"

#define PARM_MAX_SIZE 300 // Максимальный размер аргумента ключа

#define PARM_OUT_DEF_EXT L".out" // Стандартное расширение выходного файла
#define PARM_LOG_DEF_EXT L".log" // Стандартное расширение файла журнала

namespace Parm {
	class ParmAnalyzer {
	public:

		wchar_t InPath[PARM_MAX_SIZE];
		wchar_t OutPath[PARM_MAX_SIZE];
		wchar_t LogPath[PARM_MAX_SIZE];

		ParmAnalyzer(TCHAR* argv[], int argc) : _parms(argv), _count(argc) { }

		void Invoke();

	private:

		TCHAR** _parms;

		int _count;
	};
}