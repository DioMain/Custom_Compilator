#include "stdafx.h"

using namespace std;

namespace Error {

	// Массив всех сущетсвующих ошибок / Array of all exist errors
	static ErrorBase ErrorsPool[MAX_ERRORS_COUNT] = {
		ERROR_THROW_C(0, "Недопустимый код ошибки"),
		ERROR_THROW_C(1, "Системный збой"),

		ERROR_THROW_NODEF(2), ERROR_THROW_NODEF(3), ERROR_THROW_NODEF(4), ERROR_THROW_NODEF(5),
		ERROR_THROW_NODEF(6), ERROR_THROW_NODEF(7), ERROR_THROW_NODEF(8), ERROR_THROW_NODEF(9),

		ERROR_THROW_NODEF10(10), ERROR_THROW_NODEF10(20), ERROR_THROW_NODEF10(30), ERROR_THROW_NODEF10(40), ERROR_THROW_NODEF10(50),
		ERROR_THROW_NODEF10(60), ERROR_THROW_NODEF10(70), ERROR_THROW_NODEF10(80), ERROR_THROW_NODEF10(90),

		ERROR_THROW_C(100, "Параметр -IN должен быть задан!"),

		ERROR_THROW_NODEF(101), ERROR_THROW_NODEF(102), ERROR_THROW_NODEF(103),

		ERROR_THROW_C(104, "Превышена длинна входного пораметра!"),

		ERROR_THROW_NODEF(105), ERROR_THROW_NODEF(106), ERROR_THROW_NODEF(107), ERROR_THROW_NODEF(108), ERROR_THROW_NODEF(109),

		// Ошибки сканера кода / Errors of code scaner
		ERROR_THROW_C(110, "Ошибка при открытии файла [-IN]"),
		ERROR_THROW_C(111, "Недопустимый символ в исходном файле [-IN]"),
		ERROR_THROW_C(112, "Ошибка при создании файла протакола [-log]"),
		ERROR_THROW_C(113, "Ошибка при создании файла результата трансляции [-out]"),

		ERROR_THROW_NODEF(114), ERROR_THROW_NODEF(115),
		ERROR_THROW_NODEF(116), ERROR_THROW_NODEF(117), ERROR_THROW_NODEF(118), ERROR_THROW_NODEF(119),

		// Ошибки лексического анализатора / Errors of lexem analysator
		ERROR_THROW_C(120, "Треболволся литерал! [VAR IND = (EXPRESSION);] OR [NAMESPACE (INDEFIER) { }]"),
		ERROR_THROW_C(121, "Литерал вырожения должен быть закрыт! [VAR IND = EXPRESSION;]"),
		ERROR_THROW_C(122, "Выход за глобалую область видимости!"),
		ERROR_THROW_C(123, "Такого литерала не существует! [LexemType == None]"),
		ERROR_THROW_C(124, "Неизвесное лексема! [Lexem-Analysis]"),
		ERROR_THROW_C(125, "Строчный или символьный литерал дожен быть закрыт! [\"TEXT\"] OR [\'C\']"),
		ERROR_THROW_C(126, "Не все пространства имен закрыты!"),

		ERROR_THROW_NODEF(127), ERROR_THROW_NODEF(128), ERROR_THROW_NODEF(129),
		
		ERROR_THROW_NODEF10(130), ERROR_THROW_NODEF10(140), ERROR_THROW_NODEF10(150),
		ERROR_THROW_NODEF10(160), ERROR_THROW_NODEF10(170), ERROR_THROW_NODEF10(180), ERROR_THROW_NODEF10(190),

		// Ошибки синтаксического анализатора / Errors of syntax analysator
		ERROR_THROW_C(200, "Неизвестное правило!"),
		ERROR_THROW_C(201, "Точка входа не обнаружена! [Main { }]"),
		ERROR_THROW_C(202, "Идентификатор уже сущетвует!"),
		ERROR_THROW_C(203, "Идентификатор не найден!"),
		ERROR_THROW_C(204, "Идентификатор указывает на фунцию!"),
		ERROR_THROW_C(205, "Идентификатор указывает на переменную!"),
		ERROR_THROW_C(206, "Параметр использован за функцией!"),
		ERROR_THROW_C(207, "Идентификатор объявлен в другом пространстве имён!"),
		ERROR_THROW_C(208, "В вырожении заперщены все операторы! [Void, String, Char]"),
		ERROR_THROW_C(209, "В вырожении заперщены логические операторы! [Int]"),

		ERROR_THROW_C(210, "В вырожении заперщены арифметические операторы! [Bool]"),
		ERROR_THROW_C(211, "String не может быть однавременно и Char! [\'text\"]"),
		ERROR_THROW_C(212, "Функция использована не правильно!"),
		ERROR_THROW_C(213, "Функция не принемает столько аргументов!"),
		ERROR_THROW_C(214, "Параметр функции использован за самой функцией!"),
		ERROR_THROW_C(215, "Неизвестный тип идентификатора!"),
		ERROR_THROW_C(216, "Не правильный формат строки!"),
		ERROR_THROW_C(217, "Не правильный формат символа!"),
		ERROR_THROW_C(218, "Не возможно присвоит {TYPE} к {TYPE}"),
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