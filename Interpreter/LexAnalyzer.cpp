#include "stdafx.h"

using namespace std;

namespace Parsing {
	void LexAnalyzer::Invoke()
	{
		char letter;
		string expression;

		Lexem current;

		int index = 0,
			letI = 0,
			lineI = 0;

		int last_var_index = -1,
			last_literal_index = -1;

		while (true)
		{
			letter = code[index];

			// Если код закончился
			if (letter == PARSING_CODE_END) CODE_END = true;
			// Если мы встретили ;
			if (letter == PARSING_COM_END) COM_END = true;
			// Если мы встретили пробел и при этом мы это не строковый литерал
			if (letter == PARSING_LEX_END) LEX_END = true;
			// Если конец строки
			if (letter == PARSING_LINE_END) LINE_END = true;
			// Если мы встретили "
			//if (letter == PARSING_STRING) STR_LITERAL = !STR_LITERAL;

			if (INDEFIER && EXPRESSION)
				throw ERROR_THROW_IN_C(600, "Indifier literal can`t be expression literal!", lineI, letI);

			//if ((COM_END || LINE_END || CODE_END) && STR_LITERAL)
			//	throw ERROR_THROW_IN_C(601, "The string literal must be closed!", lineI, letI);

			if (CODE_END && EXPRESSION)
				throw ERROR_THROW_IN_C(602, "The expression literal must be closed!", lineI, letI);

			//if (STR_LITERAL && POLAND_LITERAL)
			//	throw ERROR_THROW_IN_C(603, "Expression can`t be string!", lineI, letI);

			if (CODE_END || LEX_END || COM_END || LINE_END) {

				if (!LITERAL) {
					current = GetLexem(expression);

					if (current.type == LexemType::Error)
						throw ERROR_THROW_IN_C(599, "Unknown sytax!", lineI, letI);

					LexSwitch(current);

					data->Lexems.push_back(&current);
				}
				else {
					//string literal;

					//if (POLAND_LITERAL) {
					//	poland::PolandNatation natation = poland::PolandNatation(expression);
					//	strstream sstream;
					//	sstream << natation.CalculateResult();

					//	literal += sstream.str();

					//	POLAND_LITERAL = false;
					//}
					//else {
					//	literal += expression;
					//}

					LITERAL = false;
				}

				expression.clear();
			}
			else expression += letter;

			//

			if (CODE_END) break;

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

	void LexAnalyzer::LexSwitch(Lexem lex)
	{
		switch (lex.type)
		{
		case LexemType::Var:
			break;
		case LexemType::VarType:
			break;
		case LexemType::Equals:
			break;
		case LexemType::CommandEnd:
			break;
		}
	}

	Lexem LexAnalyzer::GetLexem(string lexString)
	{
		vector<Lexem> availableLexems = data->BasicLexems;

		for (int i = 0; i < lexString.size(); i++)
		{
			for (int j = 0; j < availableLexems.size(); j++)
			{
				if (lexString[i] != availableLexems[j].name[i]) {
					availableLexems.erase(availableLexems.begin() + j);
					j--;
				}
			}
		}

		if (availableLexems.size() != 1) return Lexem(LexemType::Error, "ERROR");

		return availableLexems.front();
	}

	Lexem LexAnalyzer::CreateVar(string indefier)
	{
		return Lexem();
	}

	Lexem LexAnalyzer::CreateLiteral(string literal)
	{
		return Lexem();
	}
}


