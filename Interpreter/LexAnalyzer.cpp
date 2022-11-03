#include "stdafx.h"

using namespace std;

namespace LegecyLexemAnalyzer {
	void LexAnalyzer::Invoke()
	{
		char letter;
		string expression;

		namespaces.push_back("GLOBAL");
		data->LexemsTable.push_back(vector<Lexem*>());

		Lexem curLex;

		int tableStr = 0;
		int paramdepth = 0;
		int logicdepth = 0;

		bool ENDL = false, 
			REACT = false,
			SPACE = false,
			CHECK = false,
			CODEEND = false,
			LITERAL = false,
			EXPRESSION = false,
			EXPRESSION_STR = false,
			EXPRESSION_LOGIC = false,
			INDEFIER = false,
			NAMESPACE = false,
			ENDRULE = false,
			PARAMS = false,
			MAIN = false,
			COMMENT = false,
			RETURN = false,
			IF = false,		
			ELSE = false;

		SetDefaultNamespaceBuffer("UNDEFINE");

		while (!CODEEND) {

			letter = code[index];

			// Если код закончился
			if (code[index] == PARSING_CODE_END) CODEEND = true;

			// Если мы встретили ; = ( ) { }7
			if (((IsReactiveSymbol(code[index]) && !EXPRESSION)
				 || code[index] == ';' || code[index] == ',')
				&& !EXPRESSION_STR && !EXPRESSION_LOGIC && !COMMENT)
				REACT = true;

			// Если логическое вырожение
			if (EXPRESSION_LOGIC) {
				if (code[index] == ')' && logicdepth == 0) REACT = true;

				if (code[index] == '(') logicdepth++;
				if (code[index] == ')') logicdepth--;
			}

			if (expression.size() == 2 && expression[0] == '/' && expression[1] == '/') CHECK = true;

			// Если мы встретили пробел и при этом мы это не строковый литерал
			if (letter == PARSING_LEX_END && !EXPRESSION && !PARAMS) SPACE = true;

			// Если конец строки
			if (code[index] == PARSING_LINE_END) ENDL = true;

			if ((EXPRESSION || PARAMS) && (letter == '\"' || letter == '\''))
				EXPRESSION_STR = !EXPRESSION_STR;

			// Если однавременно требуеться и вырожение и идентификатор
			if (INDEFIER && EXPRESSION)
				throw ERROR_THROW_IN(120, lineI, letI);

			// Если однавременно и конец кода и требуется вырожение
			if (CODEEND && EXPRESSION)
				throw ERROR_THROW_IN(121, lineI, letI);

			// Если вышли за глобальную облость видимости
			if (namespaces.size() == 0)
				throw ERROR_THROW_IN(122, lineI, letI);

			if (EXPRESSION_STR && (ENDL || CODEEND))
				throw ERROR_THROW_IN(126, lineI, letI);

			// Если конец кода, встречер реактивый символ, пробел, конец строки
			if ((CODEEND || REACT || SPACE || ENDL || CHECK) && !COMMENT) {

				// Если выражение не пустое
				if (!expression.empty()) {
					
					// Если параметр и литерал
					if (PARAMS && LITERAL) {
						// Если логическое вырожение
						if (EXPRESSION_LOGIC) {
							curLex = Lexem(LexemType::LogicExpression, "LogicExpression");
							curLex.locationSpace = namespaces.back();

							data->LexemsTable[tableStr].push_back(new Lexem(curLex));

							data->RawLiterals.push_back(new Literal());
							data->RawLiterals.back()->data = expression;
						}
						else {
							switch (ParamParsing(expression))
							{
							case ParamType::VarCreation:
								curLex = data->GetBasicLexem(dataBuffer);
								curLex.locationSpace = namespaces.back();

								data->LexemsTable[tableStr].push_back(new Lexem(curLex));

								curLex = Lexem(LexemType::Indefier, "indefier");
								curLex.locationSpace = namespaces.back();

								data->LexemsTable[tableStr].push_back(new Lexem(curLex));

								data->RawLiterals.push_back(new Literal());
								data->RawLiterals.back()->data = indefierBuffer;

								break;
							case ParamType::Indefier:
								curLex = Lexem(LexemType::Indefier, "indefier");
								curLex.locationSpace = namespaces.back();

								data->LexemsTable[tableStr].push_back(new Lexem(curLex));

								data->RawLiterals.push_back(new Literal());
								data->RawLiterals.back()->data = indefierBuffer;
								break;
							case ParamType::Expression:
								curLex = Lexem(LexemType::Expression, "Expression");
								curLex.locationSpace = namespaces.back();

								data->LexemsTable[tableStr].push_back(new Lexem(curLex));

								data->RawLiterals.push_back(new Literal());
								data->RawLiterals.back()->data = expression;
								break;
							}
						}

						EXPRESSION_LOGIC = false;
						LITERAL = false;
					}
					// Если литерал
					else if (LITERAL) {						
						curLex = PARSING_VOID_LEXEM; // Устанавливает пустую лексему

						// Если вырожение
						if (EXPRESSION) curLex = Lexem(LexemType::Expression, "expression");
						// Если идентификатор
						else if (INDEFIER) curLex = Lexem(LexemType::Indefier, "indefier");

						// Если пустая лексема
						if (curLex.type == LexemType::Void)
							throw ERROR_THROW_IN(123, lineI, letI);

						// Если переход на другое пространство имен
						if (NAMESPACE) {
							namespaceBuffer = expression;

							NAMESPACE = false;
						}

						curLex.locationSpace = namespaces.back();

						data->RawLiterals.push_back(new Literal());

						data->RawLiterals.back()->data = expression;

						if (tableStr > data->LexemsTable.size() - 1)
							throw ERROR_THROW_IN(127, lineI, letI);

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
								NAMESPACE = true;
								break;
							case LexemType::Return:
								LITERAL = true;
								EXPRESSION = true;

								RETURN = true;
								break;
							case LexemType::Main:
								namespaceBuffer = "MAIN";

								MAIN = true;
								break;
							case LexemType::If:
								IF = true;

								SetDefaultNamespaceBuffer(ELSE ? "ELIF" : "IF");
								break;
							case LexemType::Else:
								ELSE = true;

								SetDefaultNamespaceBuffer("ELSE");
								break;
							case LexemType::Comment:
								COMMENT = true;
								break;
							}

						}
						// Если существует литерал равный данному вырожению
						else if (IsHaveEqualLiteral(expression)) {
							curLex = Lexem(LexemType::Indefier, "indefier");

							data->RawLiterals.push_back(new Literal());
							data->RawLiterals.back()->data = expression;
						}
						else 
							throw ERROR_THROW_IN(124, lineI, letI);

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

					if (RETURN) {
						LITERAL = false;
						EXPRESSION = false;

						RETURN = false;
					}
					break;
				case LexemType::SpaceIn:
					data->LexemsTable.push_back(vector<Lexem*>());

					namespaces.push_back(namespaceBuffer);

					namespacesCounter++;

					if (ELSE) ELSE = false;

					SetDefaultNamespaceBuffer("UNDEFINE");
					break;
				case LexemType::SpaceOut:
					data->LexemsTable.push_back(vector<Lexem*>());

					if (namespaces.size() == 1)
						throw ERROR_THROW_IN_C(602, "Out global namespace!", lineI, letI);

					namespaces.erase(namespaces.begin() + namespaces.size() - 1);

					LITERAL = false;
					break;
				case LexemType::Equals:
					LITERAL = true;
					EXPRESSION = true;
					break;
				case LexemType::ParamsIn:
					PARAMS = true;
					LITERAL = true;

					if (IF) { 
						EXPRESSION_LOGIC = true;  
						logicdepth = 0; 
					}

					paramdepth++;

					if (!IF && !ELSE) namespaceBuffer = "Func." + data->RawLiterals.back()->data;
					break;
				case LexemType::ParamsOut:
					paramdepth--;

					if (IF) IF = false;

					if (paramdepth == 0) {
						PARAMS = false;
						LITERAL = false;
					}
					break;
				case LexemType::And:
					LITERAL = true;

					if (!PARAMS) INDEFIER = true;
					break;
				}

				curLex.locationSpace = namespaces.back();

				data->LexemsTable[tableStr].push_back(new Lexem(curLex));
			}

			// Cимволы закачивающие строку лексем
			if (!EXPRESSION_STR && !COMMENT && (letter == ';' || letter == '{' || letter == '}')) {
				tableStr++;
			}

			// Если конец строки
			if (!ENDL) letI++;
			else {
				letI = 0;
				lineI++;
			}

			index++;

			// Если единтсвенный сивлол это пробел
			if (expression.size() == 1 && expression[0] == ' ') expression.clear();

			// Если коментарий и конец строки
			if (COMMENT && ENDL) {
				data->LexemsTable.push_back(vector<Lexem*>());
				tableStr++;

				COMMENT = false;
				expression.clear();
			}

			SPACE = false;
			REACT = false;
			ENDL = false;
			CHECK = false;
		}

		// Если main не найден и при этом его не игнорируем
		if (!MAIN) throw ERROR_THROW(125);
	}

	ParamType LexAnalyzer::ParamParsing(string param)
	{
		string word;
		vector<string> words;

		for (size_t i = 0; i < param.size() + 1; i++)
		{
			if ((param[i] == ' ' || param[i] == '\0') && !word.empty()) {
				words.push_back(word);

				word.clear();
			}				
			else if (param[i] != ' ' && param[i] != '\0') word += param[i];
		}

		if (GetVarTypeByName(words[0]) != VarType::Void && words.size() == 2) {
			dataBuffer = words[0];
			indefierBuffer = words[1];

			return ParamType::VarCreation;
		}
		else if (IsHaveEqualLiteral(words[0])) {
			indefierBuffer = words[0];

			return ParamType::Indefier;
		}
		else return ParamType::Expression;
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
		sst << spacename << '.' << namespacesCounter << '\0';

		namespaceBuffer = sst.str();
	}

	bool LexAnalyzer::IsReactiveSymbol(char letter) {
		return letter == ';' || letter == '=' || letter == '(' || letter == ')' || letter == '{' || letter == '}' || letter == ',' || letter == '.';
	}
}


