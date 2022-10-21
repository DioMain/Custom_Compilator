#pragma once

#define ERROR_MAXSIZE_MESSAGE 300	// Максимальный размер сообщения ошибки

#define ERROR_THROW_EMPTY Error::ErrorBase()
#define ERROR_THROW_C(id, message) Error::ErrorBase(id, message)
#define ERROR_THROW_IN_C(id, message, line, letter) Error::LineError(id, message, line, letter)

#define ERROR_THROW(id) Error::GetError(id)
#define ERROR_THROW_IN(id, line, letter) Error::GetError(id, line, letter)

#define ERROR_THROW_NODEF(id) ERROR_THROW(id, "Неопределённая ошибка")	// Далее идёт генерация пустых ошибок

#define ERROR_THROW_NODEF10(id) ERROR_THROW_NODEF(id + 0), ERROR_THROW_NODEF(id + 1), ERROR_THROW_NODEF(id + 2), ERROR_THROW_NODEF(id + 3), ERROR_THROW_NODEF(id + 4), \
								ERROR_THROW_NODEF(id + 5), ERROR_THROW_NODEF(id + 6), ERROR_THROW_NODEF(id + 7), ERROR_THROW_NODEF(id + 8), ERROR_THROW_NODEF(id + 9)

#define ERROR_THROW_NODEF100(id) ERROR_THROW_NODEF10(id + 0), ERROR_THROW_NODEF10(id + 10), ERROR_THROW_NODEF10(id + 20), ERROR_THROW_NODEF10(id + 30), ERROR_THROW_NODEF10(id + 40), \
								 ERROR_THROW_NODEF10(id + 50), ERROR_THROW_NODEF10(id + 60), ERROR_THROW_NODEF10(id + 70), ERROR_THROW_NODEF10(id + 80), ERROR_THROW_NODEF10(id + 90)

#define MAX_ERRORS_COUNT 1000

namespace Error {
	class ErrorBase
	{
	public:

		int id;
		std::string message;

		ErrorBase() : id(0), message("Unknown error!") { }

		ErrorBase(int id, std::string message) : id(id), message(message) { }

		virtual std::string ToString();
	};

	class LineError : public ErrorBase
	{
	public:

		int lineIndex, letterIndex;

		LineError() : ErrorBase(), lineIndex(-1), letterIndex(-1) { }

		LineError(int id, std::string message, int line, int letter) : ErrorBase(id, message), lineIndex(line), letterIndex(letter) { }

		std::string ToString() override;
	};

	class PolandError : public ErrorBase
	{
	public:

		int offset;

		PolandError() : ErrorBase(), offset(0) { }

		PolandError(int id, std::string message, int offset) : ErrorBase(id, message), offset(offset) { }

		std::string ToString() override;

	private:

	};

	ErrorBase GetError(int id);
	LineError GetError(int id, int line, int letter);
}