#include "stdafx.h"

using namespace std;

namespace Parsing {
	void LexAnalyzer::Invoke()
	{
		char letter;
		string expression;

		namespaces.push_back("GLOBAL");
		data->LexemsTable.push_back(vector<Lexem*>());

		Lexem curLex;

		int tableStr = 0;

		bool ENDL = false, 
			REACT = false,
			SPACE = false,
			CODEEND = false,
			LITERAL = false,
			EXPRESSION = false,
			EXPRESSION_STR = false,
			INDEFIER = false,
			NSPACE = false,
			ENDRULE = false,
			PARAMS = false,
			MAIN = false,
			MAIN_IGNORE = false;

		SetDefaultNamespaceBuffer("UNDEFINE");

		while (!CODEEND) {

			letter = code[index];

			// Если код закончился
			if (code[index] == PARSING_CODE_END) CODEEND = true;

			// Если мы встретили ; = ( ) { }
			if ((IsReactiveSymbol(code[index]) && !EXPRESSION)
				 || code[index] == ';') REACT = true;

			// Если мы встретили пробел и при этом мы это не строковый литерал
			if (letter == PARSING_LEX_END && !EXPRESSION) SPACE = true;

			//if (EXPRESSION && letter == '\"') 
			//	EXPRESSION_STR = !EXPRESSION_STR;

			// Если конец строки
			if (code[index] == PARSING_LINE_END) ENDL = true;


			// Если однавременно требуеться и вырожение и идентификатор
			if (INDEFIER && EXPRESSION)
				throw ERROR_THROW_IN(120, lineI, letI);

			// Если однавременно и конец кода и требуется вырожение
			if (CODEEND && EXPRESSION)
				throw ERROR_THROW_IN(121, lineI, letI);

			// Если вышли за глобальную облость видимости
			if (namespaces.size() == 0)
				throw ERROR_THROW_IN(122, lineI, letI);

			// Если конец кода, встречер реактивый символ, пробел, конец строки
			if (CODEEND || REACT || SPACE || ENDL) {

				// Если выражение не пустое
				if (!expression.empty()) {
					// Если литерал
					if (LITERAL) {						
						curLex = PARSING_VOID_LEXEM; // Устанавливает пустую лексему

						// Если вырожение
						if (EXPRESSION) curLex = Lexem(LexemType::Literal, "expression");
						// Если идентификатор
						else if (INDEFIER) curLex = Lexem(LexemType::Indefier, "indefier");

						// Если пустая лексема
						if (curLex.type == LexemType::Void)
							throw ERROR_THROW_IN(123, lineI, letI);

						// Если переход на другое пространство имен
						if (NSPACE) {
							namespaceBuffer = expression;

							NSPACE = false;
						}

						curLex.locationSpace = namespaces.back();

						data->RawLiterals.push_back(new Literal());

						data->RawLiterals.back()->data = expression;

						data->LexemsTable[tableStr].push_back(new Lexem(curLex));

						LITERAL = false;
						EXPRESSION = false;
						INDEFIER = false;
					}
					else {
						curLex = data->GetBasicLexem(expression);

						// Если не пустая лексема
						if (curLex.type != LexemType::Void) {
							// Выбор по типу лексемы
							switch (curLex.type)
							{
							case LexemType::VarType:
								LITERAL = true;
								INDEFIER = true;
								break;
							case LexemType::Namespace:
								LITERAL = true;
								INDEFIER = true;
								NSPACE = true;
								break;
							case LexemType::Return:
								LITERAL = true;
								EXPRESSION = true;
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
						// Если существует литерал равный данному вырожению
						else if (IsHaveEqualLiteral(expression)) curLex = Lexem(LexemType::Indefier, "indefier");
						else throw ERROR_THROW_IN(124, lineI, letI);

						curLex.locationSpace = namespaces.back();

						data->LexemsTable[tableStr].push_back(new Lexem(curLex));
					}
				}

				expression.clear();
			}
			else expression += letter;

			// Если реактивный символ
			if (REACT) {
				strstream sstream;
				sstream << letter << '\0';

				curLex = data->GetBasicLexem(sstream.str());

				// Выбор по типу лексемы
				switch (curLex.type)
				{
				case LexemType::RuleEnd:
					data->LexemsTable.push_back(vector<Lexem*>());
					break;
				case LexemType::SpaceIn:
					data->LexemsTable.push_back(vector<Lexem*>());

					if (PARAMS) namespaces.push_back("Func." + dataBuffer);
					else namespaces.push_back(namespaceBuffer);

					SetDefaultNamespaceBuffer("UNDEFINE");
					break;
				case LexemType::SpaceOut:
					data->LexemsTable.push_back(vector<Lexem*>());

					if (namespaces.size() == 1)
						throw ERROR_THROW_IN_C(602, "Out global namespace!", lineI, letI);

					namespaces.erase(namespaces.begin() + namespaces.size() - 1);
					break;
				case LexemType::Equals:
					LITERAL = true;
					EXPRESSION = true;
					break;
				case LexemType::ParamsIn:
					PARAMS = true;

					dataBuffer = data->RawLiterals.back()->data;
					break;
				case LexemType::ParamsOut:
					PARAMS = false;
					break;
				}

				curLex.locationSpace = namespaces.back();

				data->LexemsTable[tableStr].push_back(new Lexem(curLex));
			}

			// Если данный символ закачивает строку лексем
			if (letter == ';' || letter == '{' || letter == '}') {
				tableStr++;
			}

			// Если конец строки
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

		// Если main не найден и при этом его не игнорируем
		if (!MAIN && !MAIN_IGNORE) throw ERROR_THROW(125);
	}

	void LexAnalyzer::ParamParsing(std::string param)
	{

	}

	bool LexAnalyzer::IsHaveEqualLiteral(std::string exp)
	{
		for (size_t i = 0; i < data->RawLiterals.size(); i++)
		{
			if (data->RawLiterals[i]->data == exp) return true;
		}

		return false;
	}

	void LexAnalyzer::SetDefaultNamespaceBuffer(string spacename)
	{
		strstream sst;
		sst << spacename << '.' << namespaces.size() << '\0';

		namespaceBuffer = sst.str();
	}

	bool LexAnalyzer::IsReactiveSymbol(char letter) {
		return letter == ';' || letter == '=' || letter == '(' || letter == ')' || letter == '{' || letter == '}' || letter == ',' || letter == '.';
	}
}


