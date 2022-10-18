#include "stdafx.h"

using namespace std;

namespace Parsing {
	void CodeAnalyzer::Invoke()
	{
		char letter;
		string lexem;

		bool LEX_END = false,
			COM_END = false,
			CODE_END = false,
			LINE_END = false,
			POLAND = false;

		int index = 0,
			letI = 0,
			lineI = 0;

		while (true)
		{
			letter = code[index];

			if (letter == PARSING_CODE_END) CODE_END = true;
			if (letter == PARSING_COM_END) COM_END = true;
			if (letter == PARSING_LEX_END) LEX_END = true;
			if (letter == PARSING_LINE_END) LINE_END = true;

			if (CODE_END) break;

			// Some calculate	

			if (!LINE_END) letI++;
			else {
				letI = 0;
				lineI++;
			}

			index++;

			COM_END = false;
			LEX_END = false;
			LINE_END = false;
		}
	}

	Lexem CodeAnalyzer::CreateLexem(string lexString)
	{
		return Lexem();
	}

	Lexem CodeAnalyzer::CreateVar(string indefier)
	{
		return Lexem();
	}

	Lexem CodeAnalyzer::CreateLiteral(string literal)
	{
		return Lexem();
	}
}


