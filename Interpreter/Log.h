#pragma once

namespace Log {
	class Logging
	{
	public:

		Logging() : stream(nullptr) { }
		Logging(wchar_t* path);

		// ���������� ������ ����� � log ����, ��������� ������ ������ ���� ������ (char)
		void WriteLine(const char* str ...);
		// ���������� ������ ����� � log ����, ��������� ������ ������ ���� ������ (wchar_t)
		void WriteLine(const wchar_t* str ...);

		// ���������� � log ���� ���������� � ���������
		void WriteHeader();

		// ���������� � log ���� ���������� � ������� ����������
		void WriteParm(Parm::ParmAnalyzer parm);

		void WriteData(Parsing::DataContainer data);

		// ���������� � log ���� ���������� �� ������� ������
		void WriteIn(In::InFile in);

		// ���������� � log ���� ���������� �� ������
		void WriteError(Error::ErrorBase* error);

		// ��������� ����� log �����
		void Close();

	private:

		std::ofstream* stream;
	};

}