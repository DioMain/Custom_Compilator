#include "stdafx.h"

using namespace std;

namespace Parsing {
	void LexAnalyzer::Invoke()
	{
		char letter;
		string expression;

		Lexem curLex;

		while (true)
		{
			letter = code[index];

			// Если код закончился
			if (letter == PARSING_CODE_END) CODE_END = true;
			// Если мы встретили ;
			if (letter == PARSING_COM_END) COM_END = true;
			// Если мы встретили пробел и при этом мы это не строковый литерал
			if (letter == PARSING_LEX_END && !EXPRESSION) LEX_END = true;
			// Если конец строки
			if (letter == PARSING_LINE_END) LINE_END = true;

			if (INDEFIER && EXPRESSION)
				throw ERROR_THROW_IN_C(600, "Indifier literal can`t be expression literal!", lineI, letI);

			if (CODE_END && EXPRESSION)
				throw ERROR_THROW_IN_C(602, "The expression literal must be closed!", lineI, letI);

			// Основной обработчик
			if (CODE_END || LEX_END || COM_END || LINE_END) {

				// Если вырожение пустое то мы его просто пропускаем
				if (expression.size() > 0) {
					// Если не литерал
					if (!LITERAL) {
						curLex = data->GetBasicLexem(expression);

						// Если есть сущ. лексема
						if (curLex.type != LexemType::Void) {
							LexSwitch(curLex);

							ISRIGHT_EXP = true;
						}

						// Если нет лексемы ищет пересенную с таким именем (пропуск если лексема была найдена)
						if (!ISRIGHT_EXP) {
							Var* fvar = data->GetVar(expression);

							if (fvar != nullptr) {
								CurVar = fvar;

								curLex = PARSING_VAR_LEXEM;

								ISRIGHT_EXP = true;
							}
						}

						// Если ничего не удалось найти
						if (!ISRIGHT_EXP)
							throw ERROR_THROW_IN_C(599, "Unknown sytax!", lineI, letI);

						data->Lexems.push_back(new Lexem(curLex));
					}
					else {
						curLex = PARSING_VOID_LEXEM;

						// Если литерал нужен был для идентификатора
						if (INDEFIER) {
							curLex = CreateVar(expression);
						}
						// Если литерал является вырожением
						else if (EXPRESSION) {
							if (CurVar == nullptr)
								throw ERROR_THROW_IN_C(600, "Unknown equals!", lineI, letI);

							poland::PolandNatation* pol = nullptr;
							strstream* sstream = nullptr;

							// Под какой тип переменной нужно это вырожение
							switch (CurVar->type)
							{
								// Если тип int
							case VarType::Integer:
								expression = ExpressionConvert(expression);

								pol = new poland::PolandNatation(expression);

								sstream = new strstream();
								*sstream << pol->CalculateResult() << '\0';

								expression.clear();
								expression += sstream->str();

								break;
								// Если тип string
							case VarType::String:
								if (expression[0] != '\"' || expression[expression.size() - 1] != '\"')
									throw ERROR_THROW_IN_C(600, "Я ещё не прилумал!", lineI, letI);
								break;
							}

							// Если у переменной до этого не было литерала, то есть не была инициализированна
							if (CurVar->literalIndex == PARSING_VAR_UNINIT) {
								curLex = CreateLiteral();

								CurVar->literalIndex = data->Literals.size() - 1;
							}
							else curLex = PARSING_LITERA_LEXEM(CurVar->literalIndex);

							data->Literals[CurVar->literalIndex]->data = expression;
						}

						// Если по итогу литерал не для чего не приходился
						if (curLex.type == LexemType::Void)
							throw ERROR_THROW_IN_C(600, "Я ещё не прилумал!", lineI, letI);

						data->Lexems.push_back(new Lexem(curLex));

						LITERAL = false;
						EXPRESSION = false;
						INDEFIER = false;
					}
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

			if (COM_END) {
				CurVar = nullptr;
				databuffer.clear();

				expression += letter;
			}

			index++;

			COM_END = false;
			LEX_END = false;
			LINE_END = false;

			ISRIGHT_EXP = false;
		}
	}

	void LexAnalyzer::LexSwitch(Lexem lex)
	{
		switch (lex.type)
		{
		case LexemType::Var:
			break;
		case LexemType::VarType:
			databuffer = lex.name;

			LITERAL = true;
			INDEFIER = true;
			break;
		case LexemType::Equals:
			if (CurVar == nullptr)
				throw ERROR_THROW_IN_C(600, "Unknown equals!", lineI, letI);

			LITERAL = true;
			EXPRESSION = true;
			break;
		}
	}

	Lexem LexAnalyzer::CreateVar(string indefier)
	{
		data->Vars.push_back(new Var(databuffer));

		Lexem lex = Lexem(LexemType::Indefier, PARSING_UNDEF_LEXEM_NAME, LinkType::Var, data->Vars.size() - 1);

		CurVar = data->Vars.back();

		CurVar->indefier = indefier;

		return lex;
	}

	Lexem LexAnalyzer::CreateLiteral()
	{
		data->Literals.push_back(new Literal());

		Lexem lex = PARSING_LITERA_LEXEM(data->Literals.size() - 1);

		return lex;
	}

	string LexAnalyzer::ExpressionConvert(string exp)
	{
		string finalExp;
		string word;

		for (short i = 0; true; i++)
		{
			if (exp[i] != ' ' && exp[i] != '\0') word += exp[i];
			else {

				Var* var = data->GetVar(word);

				if (var == nullptr || var->literalIndex == PARSING_VAR_UNINIT) finalExp += word;
				else finalExp += data->Literals[var->literalIndex]->data;

				if (exp[i] != '\0') finalExp += ' ';

				word.clear();
			}

			if (exp[i] == '\0') break;
		}

		return finalExp;
	}
}


