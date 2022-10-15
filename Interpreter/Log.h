#pragma once

namespace Log {
	class Logging
	{
	public:

		Logging() : stream(nullptr) { }
		Logging(wchar_t* path);

		// ���������� ������ ����� � log ����, ��������� ������ ������ ���� ������ (char)
		void WriteLine(char* str ...);
		// ���������� ������ ����� � log ����, ��������� ������ ������ ���� ������ (wchar_t)
		void WriteLine(wchar_t* str ...);

		// ���������� � log ���� ���������� � ���������
		void WriteHeader();

		// ���������� � log ���� ���������� � ������� ����������
		void WriteParm(Parm::ParmAnalyzer parm);

		// ���������� � log ���� ���������� �� ������� ������
		//void WriteIn(log lg, In::in inner);

		// ���������� � log ���� ���������� �� ������
		void WriteError(Error::ErrorBase error);

		// ��������� ����� log �����
		void Close();

	private:

		std::ofstream* stream;
	};

}