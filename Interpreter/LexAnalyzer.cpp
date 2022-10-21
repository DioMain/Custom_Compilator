#include "stdafx.h"

using namespace std;

namespace Parsing {
	void LexAnalyzer::Invoke()
	{
		char letter;
		string expression;

		namespaces.push_back("GLOBAL");
		data->LexemsStable.push_back(vector<Lexem*>());

		Lexem curLex;

		int tableStr = 0;

		bool ENDL = false,
			REACT = false,
			SPACE = false,
			CODEEND = false,
			LIT = false,
			EXP = false,
			IND = false,
			NSPACE = false,
			ENDRULE = false,
			MAYBE_FUNC = false,
			MAIN = false,
			MAIN_IGNORE = false;

		SetDefaultNamespaceBuffer("UNDEFINE");

		while (!CODEEND) {

			letter = code[index];

			// Если код закончился
			if (code[index] == PARSING_CODE_END) CODEEND = true;

			// Если мы встретили ; = ( ) { }
			if ((IsReactiveSymbol(code[index]) && !EXP)
				 || code[index] == ';') REACT = true;

			// Если мы встретили пробел и при этом мы это не строковый литерал
			if (letter == PARSING_LEX_END && !EXP) SPACE = true;

			// Если конец строки
			if (code[index] == PARSING_LINE_END) ENDL = true;

			if (IND && EXP)
				throw ERROR_THROW_IN_C(600, "Indifier literal can`t be expression literal!", lineI, letI);

			if (CODEEND && EXP)
				throw ERROR_THROW_IN_C(602, "The expression literal must be closed!", lineI, letI);

			if (namespaces.size() == 0)
				throw ERROR_THROW_IN_C(602, "Out global namespace!", lineI, letI);

			if (CODEEND || REACT || SPACE || ENDL) {

				if (!expression.empty()) {
					if (LIT) {
						curLex = PARSING_VOID_LEXEM;

						if (EXP) curLex = Lexem(LexemType::Literal, "expression");
						else if (IND) curLex = Lexem(LexemType::Indefier, "indefier");

						if (curLex.type == LexemType::Void)
							throw ERROR_THROW_IN_C(600, "Такого литерала не существует!", lineI, letI);

						if (NSPACE) {
							namespaceBuffer = expression;

							NSPACE = false;
						}

						curLex.locationSpace = namespaces.back();

						data->RawLiterals.push_back(new Literal());

						data->RawLiterals.back()->data = expression;

						data->LexemsStable[tableStr].push_back(new Lexem(curLex));

						LIT = false;
						EXP = false;
						IND = false;
					}
					else {
						curLex = data->GetBasicLexem(expression);

						if (curLex.type != LexemType::Void) {
							switch (curLex.type)
							{
							case LexemType::VarType:
								LIT = true;
								IND = true;
								break;
							case LexemType::Namespace:
								LIT = true;
								IND = true;
								NSPACE = true;
								break;
							case LexemType::Return:
								LIT = true;
								EXP = true;
								break;
							case LexemType::Main:
								namespaceBuffer = "MAIN";

								MAIN = true;
								break;
							case LexemType::IgnoreMain:
								MAIN_IGNORE = true;
								break;
							}
						}
						else if (IsHaveEqualLiteral(expression)) curLex = Lexem(LexemType::Indefier, "indefier");
						else throw ERROR_THROW_IN_C(599, "Unknown sytax!", lineI, letI);

						curLex.locationSpace = namespaces.back();

						data->LexemsStable[tableStr].push_back(new Lexem(curLex));
					}
				}

				expression.clear();
			}
			else expression += letter;

			if (REACT) {
				strstream sstream;
				sstream << letter << '\0';

				curLex = data->GetBasicLexem(sstream.str());

				switch (curLex.type)
				{
				case LexemType::RuleEnd:
					data->LexemsStable.push_back(vector<Lexem*>());
					break;
				case LexemType::SpaceIn:
					data->LexemsStable.push_back(vector<Lexem*>());

					if (MAYBE_FUNC) namespaces.push_back("Func." + dataBuffer);
					else namespaces.push_back(namespaceBuffer);

					SetDefaultNamespaceBuffer("UNDEFINE");
					break;
				case LexemType::SpaceOut:
					data->LexemsStable.push_back(vector<Lexem*>());

					if (namespaces.size() == 1)
						throw ERROR_THROW_IN_C(602, "Out global namespace!", lineI, letI);

					namespaces.erase(namespaces.begin() + namespaces.size() - 1);
					break;
				case LexemType::Equals:
					LIT = true;
					EXP = true;
					break;
				case LexemType::FuncIn:
					MAYBE_FUNC = true;

					dataBuffer = data->RawLiterals.back()->data;
					break;
				}

				curLex.locationSpace = namespaces.back();

				data->LexemsStable[tableStr].push_back(new Lexem(curLex));
			}

			if (letter == ';' || letter == '{' || letter == '}') {
				tableStr++;

				MAYBE_FUNC = false;
			}

			if (!ENDL) letI++;
			else {
				letI = 0;
				lineI++;
			}

			index++;

			SPACE = false;
			REACT = false;
			ENDL = false;
		}

		if (!MAIN && !MAIN_IGNORE) throw ERROR_THROW_C(599, "Main not found!");
	}

	bool LexAnalyzer::IsHaveEqualLiteral(std::string exp)
	{
		for (size_t i = 0; i < data->RawLiterals.size(); i++)
		{
			if (data->RawLiterals[i]->data == exp) return true;
		}

		return false;
	}

	//string LexAnalyzer::ExpressionParse(string exp)
	//{
	//	string finalExp;
	//	string word;

	//	int i = 0;
	//	do {
	//		if (exp[i] == '\0' || exp[i] == ' ' || poland::PolandNatation::IsMathOperator(exp[i])) {
	//			Var* var = data->GetVar(word);

	//			if (var == nullptr || var->literalIndex == PARSING_VAR_UNINIT) finalExp += word;
	//			else if (var->type == CurVar->type) finalExp += data->Literals[var->literalIndex]->data;
	//			else throw ERROR_THROW_IN_C(600, "Переменные разных типов", lineI, letI - (exp.size() - i));

	//			if (exp[i] != '\0') finalExp += exp[i];

	//			word.clear();
	//		}
	//		else word += exp[i];

	//		i++;

	//	} while (i < exp.size() + 1);

	//	return finalExp;
	//}

	void LexAnalyzer::SetDefaultNamespaceBuffer(string spacename)
	{
		strstream sst;
		sst << spacename << '.' << namespaces.size() << '\0';

		namespaceBuffer = sst.str();
	}

	bool LexAnalyzer::IsReactiveSymbol(char letter) {
		return letter == ';' || letter == '=' || letter == '(' || letter == ')' || letter == '{' || letter == '}' || letter == ',' || letter == '.';;
	}
}


