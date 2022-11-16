#include "stdafx.h"

using namespace std;

namespace Error {

	// ������ ���� ������������ ������ / Array of all exist errors
	static ErrorBase ErrorsPool[MAX_ERRORS_COUNT] = {
		ERROR_THROW_C(0, "������������ ��� ������"),
		ERROR_THROW_C(1, "��������� ����"),

		ERROR_THROW_NODEF(2), ERROR_THROW_NODEF(3), ERROR_THROW_NODEF(4), ERROR_THROW_NODEF(5),
		ERROR_THROW_NODEF(6), ERROR_THROW_NODEF(7), ERROR_THROW_NODEF(8), ERROR_THROW_NODEF(9),

		ERROR_THROW_NODEF10(10), ERROR_THROW_NODEF10(20), ERROR_THROW_NODEF10(30), ERROR_THROW_NODEF10(40), ERROR_THROW_NODEF10(50),
		ERROR_THROW_NODEF10(60), ERROR_THROW_NODEF10(70), ERROR_THROW_NODEF10(80), ERROR_THROW_NODEF10(90),

		ERROR_THROW_C(100, "�������� -IN ������ ���� �����!"),

		ERROR_THROW_NODEF(101), ERROR_THROW_NODEF(102), ERROR_THROW_NODEF(103),

		ERROR_THROW_C(104, "��������� ������ �������� ���������!"),

		ERROR_THROW_NODEF(105), ERROR_THROW_NODEF(106), ERROR_THROW_NODEF(107), ERROR_THROW_NODEF(108), ERROR_THROW_NODEF(109),

		// ������ ������� ���� / Errors of code scaner
		ERROR_THROW_C(110, "������ ��� �������� ����� [-IN]"),
		ERROR_THROW_C(111, "������������ ������ � �������� ����� [-IN]"),
		ERROR_THROW_C(112, "������ ��� �������� ����� ��������� [-log]"),
		ERROR_THROW_C(113, "������ ��� �������� ����� ���������� ���������� [-out]"),

		ERROR_THROW_NODEF(114), ERROR_THROW_NODEF(115),
		ERROR_THROW_NODEF(116), ERROR_THROW_NODEF(117), ERROR_THROW_NODEF(118), ERROR_THROW_NODEF(119),

		// ������ ������������ ����������� / Errors of lexem analysator
		ERROR_THROW_C(120, "����������� �������! [VAR IND = (EXPRESSION);] OR [NAMESPACE (INDEFIER) { }]"),
		ERROR_THROW_C(121, "������� ��������� ������ ���� ������! [VAR IND = EXPRESSION;]"),
		ERROR_THROW_C(122, "����� �� �������� ������� ���������!"),
		ERROR_THROW_C(123, "������ �������� �� ����������! [LexemType == None]"),
		ERROR_THROW_C(124, "���������� �������! [Lexem-Analysis]"),
		ERROR_THROW_C(125, "�������� ��� ���������� ������� ����� ���� ������! [\"TEXT\"] OR [\'C\']"),
		ERROR_THROW_C(126, "�� ��� ������������ ���� �������!"),

		ERROR_THROW_NODEF(127), ERROR_THROW_NODEF(128), ERROR_THROW_NODEF(129),
		
		ERROR_THROW_NODEF10(130), ERROR_THROW_NODEF10(140), ERROR_THROW_NODEF10(150),
		ERROR_THROW_NODEF10(160), ERROR_THROW_NODEF10(170), ERROR_THROW_NODEF10(180), ERROR_THROW_NODEF10(190),

		// ������ ��������������� ����������� / Errors of syntax analysator
		ERROR_THROW_C(200, "����������� �������!"),
		ERROR_THROW_C(201, "����� ����� �� ����������! [Main { }]"),
		ERROR_THROW_C(202, "������������� ��� ���������!"),
		ERROR_THROW_C(203, "������������� �� ������!"),
		ERROR_THROW_C(204, "������������� ��������� �� ������!"),
		ERROR_THROW_C(205, "������������� ��������� �� ����������!"),
		ERROR_THROW_C(206, "�������� ����������� �� ��������!"),
		ERROR_THROW_C(207, "������������� �������� � ������ ������������ ���!"),
		ERROR_THROW_C(208, "� ��������� ��������� ��� ���������! [Void, String, Char]"),
		ERROR_THROW_C(209, "� ��������� ��������� ���������� ���������! [Int]"),

		ERROR_THROW_C(210, "� ��������� ��������� �������������� ���������! [Bool]"),
		ERROR_THROW_C(211, "String �� ����� ���� ������������ � Char! [\'text\"]"),
		ERROR_THROW_C(212, "������� ������������ �� ���������!"),
		ERROR_THROW_C(213, "������� �� ��������� ������� ����������!"),
		ERROR_THROW_C(214, "�������� ������� ����������� �� ����� ��������!"),
		ERROR_THROW_C(215, "����������� ��� ��������������!"),
		ERROR_THROW_C(216, "�� ���������� ������ ������!"),
		ERROR_THROW_C(217, "�� ���������� ������ �������!"),
		ERROR_THROW_C(218, "�� �������� �������� {TYPE} � {TYPE}"),
		ERROR_THROW_NODEF(219),

		ERROR_THROW_NODEF10(220), ERROR_THROW_NODEF10(130), ERROR_THROW_NODEF10(240), ERROR_THROW_NODEF10(250),
		ERROR_THROW_NODEF10(260), ERROR_THROW_NODEF10(270), ERROR_THROW_NODEF10(280), ERROR_THROW_NODEF10(290),

		ERROR_THROW_NODEF100(300), ERROR_THROW_NODEF100(400), ERROR_THROW_NODEF100(500),
		ERROR_THROW_NODEF100(600), ERROR_THROW_NODEF100(700), ERROR_THROW_NODEF100(800), ERROR_THROW_NODEF100(900)
	};

	string ErrorBase::ToString()
	{
		strstream result;

		result << "ID: " << id << endl << "MESSAGE: " << message << '\0';

		return result.str();
	}
	string LineError::ToString()
	{
		string base = ErrorBase::ToString();

		strstream result;

		result << endl << "Line index: " << lineIndex + 1 << '\0';

		return base + result.str();
	}
	string PolandError::ToString()
	{
		string base = ErrorBase::ToString();

		strstream result;

		result << endl << "Expression offset: " << offset << '\0';

		return base + result.str();
	}

	ErrorBase GetError(int id)
	{
		if (id < 0 || id > MAX_ERRORS_COUNT - 1) throw ErrorsPool[0];

		return ErrorsPool[id];
	}
	LineError GetError(int id, int line, int letter)
	{
		if (id < 0 || id > MAX_ERRORS_COUNT - 1) throw ErrorsPool[0];

		return LineError(id, ErrorsPool[id].message, line, letter);
	}
}