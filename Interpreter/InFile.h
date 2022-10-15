#pragma once

#define IN_MAX_LEN_TEXT 1024*1024		// ������������ ������ ��������� ���� 1 mb
#define IN_CODE_ENDL '\n'				// ������ ����� ������
#define IN_SPACE ' '					// ������ �������

// ������� �����������, �����������, ���������� � ������������ ��������
// ������� Windows-1251
// F - �����������, T - �����������, I - �������������, '{������}' - ������ �� {������}.

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
	// T - ���������� ������; F - ������������� ������; I - ������������
	enum in
	{
		T = 1024, F = 2048, I = 4096
	};

	class InFile
	{
	public:
		
		int SizeOfCode;		// ���-�� ��������
		int LinesCount;		// ���-�� �����
		int IgnoreCount;	// ���-�� ����������������� ��������

		char* Code;	//�������� ���

		InFile() : code_table(nullptr), SizeOfCode(0), LinesCount(0), IgnoreCount(0), Code(nullptr), stream(nullptr) { }

		InFile(wchar_t* path);

		void Invoke();

		void Close();
		
	private:

		std::ifstream* stream;

		int* code_table;	// �������� ��������: T, F, I	����� ��������
	};
};