#pragma once

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
}