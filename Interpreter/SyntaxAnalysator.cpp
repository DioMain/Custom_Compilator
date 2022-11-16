#include "stdafx.h"

using namespace std;
using namespace Data;
using namespace Collections;

namespace SyntaxAnalysis {
	void SyntaxAnalysator::Invoke()
	{
		bool debag = true;	// d

		if (debag) cout << setw(25) << left << "Сообщение" << setw(30) << left << "Цепочка" << setw(20) << left << "Стек" << endl; // DEBAG

		namespaces.push_back("GLOBAL.0");

		while (true)
		{
			currentLexemChain = table->table[line];

			if (currentLexemChain[0].type == LexemType::CodeEnd) break;

			currentRule = defRules->ParsingChain(currentLexemChain);

			if (SAVE_NAMESPACE) {
				namespaces.push_back(currentLexemChain[0].space);

				SAVE_NAMESPACE = false;
			}

			if (currentRule->name == "None")
				throw ERROR_THROW_IN(200, currentLexemChain[0].line, 0);

			currentRule->analysator = this;

			currentRule->Action();

			rules->Add(Rule(*currentRule));

			currentRule->expressionsRoot.clear();
			currentRule->fullChain.clear();
			currentRule->paramsChain.clear();

			line++;

			if (debag)
				cout << setw(25) << left << "RES STATE"		// DEBAG
					<< setw(30) << left << "------------------------------" 
					<< setw(20) << left << "--------------------" << endl; // DEBAG
		}

		if (!MAIN)
			throw ERROR_THROW(201, currentLexemChain[0].line);
	}

	ExpressionNode* SyntaxAnalysator::ParsingExpression(Rule* rule, string chain, VarType ret) {

		bool debag = true;

		if (debag)
			cout << setw(25) << left << "SAVE STATE"		// DEBAG
			<< setw(30) << left << "-------"
			<< setw(20) << left << "-------" << endl;	// DEBAG

		string deChain0 = chain + "$";	// DEBAG
		string deChain0_s = "";			// DEBAG
		string deChain1 = "$";			// DEBAG

		bool HaveLetters = false,			// Ключ наличия букв
			IsString = false,				// Ключ строки
			IsChar = false,					// Ключ символа
			String = false,					// Ключ ввода строки
			Char = false,					// Ключ ввода символа
			SingleOperator = false,			// Ключ одиночного оператора
			Func = false,					// Ключ функции
			Space = false,					// Ключ пробела
			Check = false,					// Ключ проверки
			Operator = false;				// Ключ оператора

		VarType needType = ret;				// Тип который должено вернуть вырожение

		string word;						// выделенная цепочка символов
			
		int index = 0;						// индекс в вырожении

		int symbolCounter = 0;				// Счетчик символов
		int bracketsCounter = 0;			// Счетчик скобок

		char letter = chain[index];			// текущий символ

		ExpressionNode* current = new ExpressionNode();	// текущее вершина вырожения

		current->returnType = needType;
		current->selfRule = rule;

		if (debag) {
			deChain0_s.clear(); // DEBAG
			for (size_t i = 0; i < (deChain0.size() < 29 ? deChain0.size() : 29); i++) // DEBAG
				deChain0_s.push_back(deChain0[i]); // DEBAG

			cout << setw(25) << left << ""
				<< setw(30) << left << deChain0_s
				<< setw(20) << left << deChain1 << endl; // DEBAG
		}

		while (letter != '\0')
		{
			letter = chain[index];

			if (letter == '\0') Check = true;

			if (letter == '\"' && !Operator) { String = !String; IsString = true; HaveLetters = true; }
			if (letter == '\'' && !Operator) { Char = !Char; IsChar = true; HaveLetters = true; }

			if (letter == ' ' && !Char && !String) {
				\
					Space = true;

				if (debag) deChain0.erase(deChain0.begin()); // DEBAG
			}

			if (IsLetter(letter) && !Operator)
				HaveLetters = true;

			if (IsOperator(letter) && !Char && !String && !Operator)
				Check = true;

			if (!IsOperator(letter) && Operator)
				Check = true;

			if ((String && Char) || (IsString && IsChar))
				throw ERROR_THROW_IN(211, currentLexemChain[0].line, 0);

			if ((Space || Check || SingleOperator) && !word.empty()) {

				VarType elementReturnType = VarType::Void;							// тип возрощаемый элементом
				ExpressionElementType elementType = ExpressionElementType::None;	// тип элемента
				IndefierData* ind;													// указатель на идентификатор

				if (Operator) {
					if (needType != VarType::Int && needType != VarType::Bool)
						throw ERROR_THROW(208, currentLexemChain[0].line, 0);

					elementType = GetExpressionElementType(word);

					bool IsMathOperator = (elementType == ExpressionElementType::Plus || elementType == ExpressionElementType::Minus
						|| elementType == ExpressionElementType::Multi || elementType == ExpressionElementType::Division);

					if (elementType == ExpressionElementType::InBrack || elementType == ExpressionElementType::OutBrack) {
						if (elementType == ExpressionElementType::InBrack) bracketsCounter++;
						else bracketsCounter--;
					}
					else if (needType == VarType::Int && !IsMathOperator)
						throw ERROR_THROW_IN(209, currentLexemChain[0].line, 0);
					else if (needType == VarType::Bool && IsMathOperator)
						throw ERROR_THROW_IN(210, currentLexemChain[0].line, 0);
				}
				else if (HaveLetters) {
					if (rule->IndefierIsExist(word)) {
						ind = rule->GetIndefierByName(word);

						string subWord;			// под цепочка символов

						int offset = 0,			// отступ от оригинальной цепочки
							paramsCount = 0,	// кол-во параметров под функции
							subBreackets = 0;	// кол-во под скобок

						bool subExpression = false;	// Ключ под вырожения

						char subLetter = chain[index + offset];	// текущий под символ

						switch (ind->type)
						{
							// ОБРАБОТКА ПОД ФУНКЦИЙ
						case IndefierType::Func:

							elementReturnType = ind->dataType;
							elementType = ExpressionElementType::Func;

							while (subLetter != ')' || subExpression)
							{
								subLetter = chain[index + offset];

								if (subLetter == '\0')
									throw ERROR_THROW_IN(212, currentLexemChain[0].line, 0);

								if (subLetter == ')') {
									if (subBreackets <= 0) subExpression = false;
									else subBreackets--;
								}

								if (subLetter == ',' && subExpression && subBreackets <= 0) {
									if (debag)
										for (size_t i = 0; i < subWord.size(); i++) // DEBAG
											deChain0.erase(deChain0.begin()); // DEBAG

									if (!subWord.empty()) {
										current->subExpressions.push_back(ParsingExpression(rule, subWord, ind->params[paramsCount]->dataType));
										paramsCount++;

										if (debag)
											cout << setw(25) << left << "RETURN STATE" // DEBAG
											<< setw(30) << left << "-------"
											<< setw(20) << left << "-------" << endl; // DEBAG
									}
									subWord.clear();
								}
								else if (subExpression)
									subWord.push_back(subLetter);

								if (subExpression && subLetter == '(') subBreackets++;

								if (subLetter == '(') {
									subExpression = true;
									if (debag) deChain0.erase(deChain0.begin()); // DEBAG
								}

								offset++;
							}

							if (!subWord.empty()) {
								current->subExpressions.push_back(ParsingExpression(rule, subWord, ind->params[paramsCount]->dataType));
								paramsCount++;

								if (debag)
									cout << setw(25) << left << "RETURN STATE"	// DEBAG
									<< setw(30) << left << "-------"
									<< setw(20) << left << "-------" << endl; // DEBAG
							}
							if (debag)
								for (size_t i = 0; i < subWord.size(); i++)	// DEBAG
									deChain0.erase(deChain0.begin());	// DEBAG

							if (paramsCount != ind->params.size())
								throw ERROR_THROW_IN(123, currentLexemChain[0].line, 0);

							index += offset - 1;

							Func = true;

							break;
						case IndefierType::Var:
							elementReturnType = ind->dataType;
							elementType = ExpressionElementType::Var;
							break;
						case IndefierType::Param:
							if (!rule->analysator->funcStack.empty() &&
								ind->belong == rule->analysator->funcStack.top()) {
								elementReturnType = ind->dataType;
								elementType = ExpressionElementType::Var;
							}
							else
								throw ERROR_THROW_IN(214, currentLexemChain[0].line, 0);
							break;
						default:
							throw ERROR_THROW_IN(215, currentLexemChain[0].line, 0);
						}
					}
					else if (IsString) {
						if (word[0] == '\"' && word[word.size() - 1] == '\"') {
							elementReturnType = VarType::String;
							elementType = ExpressionElementType::Const;
						}
						else
							throw ERROR_THROW_IN(216, currentLexemChain[0].line, 0);
					}
					else if (IsChar) {
						if (symbolCounter == 1 && word[0] == '\'' && word[word.size() - 1] == '\'') {
							elementReturnType = VarType::Char;
							elementType = ExpressionElementType::Const;
						}
						else
							throw ERROR_THROW_IN(217, currentLexemChain[0].line, 0);
					}
					else if (word == "true" || word == "false") {
						elementReturnType = VarType::Bool;
						elementType = ExpressionElementType::Const;
					}
				}
				else {
					elementReturnType = VarType::Int;
					elementType = ExpressionElementType::Const;
				}

				if (needType != VarType::Void && needType != elementReturnType && !Operator
					&& needType != VarType::Bool) {
					strstream str;

					str << "Не возможно присвоит " << GetStringNameOfVarType(elementReturnType)
						<< " к " << GetStringNameOfVarType(needType) << "!";

					str << '\0';

					throw ERROR_THROW_IN_C(218, str.str(), currentLexemChain[0].line, 0);
				}

				current->elementChain.push_back(elementType);

				if (!Operator) {
					current->typeChain.push_back(elementReturnType);
					current->elementsData.push_back(word);
				}

				Operator = false;
				HaveLetters = false;
				SingleOperator = false;
				IsString = false;
				IsChar = false;

				symbolCounter = 0;

				deChain1.insert(deChain1.end() - 1, Log::Logging::GetOpeartorSymbolsByType(elementType)[0]);

				if (debag) {
					for (size_t i = 0; i < word.size(); i++)	// DEBAG
						deChain0.erase(deChain0.begin());		// DEBAG

					deChain0_s.clear();
					for (size_t i = 0; i < (deChain0.size() < 29 ? deChain0.size() : 29); i++)	// DEBAG
						deChain0_s.push_back(deChain0[i]);										// DEBAG

					cout << setw(25) << left << ""				// DEBAG
						<< setw(30) << left << deChain0_s		// DEBAG
						<< setw(20) << left << deChain1 << endl; // DEBAG
				}

				word.clear();
			}

			if (!Func && !Space)
				word.push_back(letter);

			if (IsOperator(letter) && !Char && !String && !Operator) Operator = true;

			if ((letter == '+' || letter == '-' || letter == '*' || letter == '/' ||
				letter == '(' || letter == ')') && !IsString && !IsChar && !Func)
				SingleOperator = true;

			Space = false;
			Check = false;
			Func = false;

			if (Char && letter != '\'')
				symbolCounter++;

			index++;
		}

		return current;
	}

	VarType SyntaxAnalysator::GetVarTypeByChain(string chain)
	{
		VarType var;

		switch (chain[0])
		{
		case 'i':
			var = VarType::Int;
			break;
		case 's':
			var = VarType::String;
			break;
		case 'c':
			var = VarType::Char;
			break;
		case 'b':
			var = VarType::Bool;
			break;
		default:
			var = VarType::Void;
			break;
		}

		return var;
	}

	bool SyntaxAnalysator::IsOperator(char letter) {
		return letter == '+' || letter == '-' || letter == '*' || letter == '/' ||
			letter == '(' || letter == ')' || letter == '|' || letter == '&' ||
			letter == '!' || letter == '=' || letter == '<' || letter == '>' || letter == ',';
	}
	bool SyntaxAnalysator::IsLetter(unsigned char symbol) {
		return (symbol >= 0x41 && symbol <= 0x7a) || (symbol >= 0xc0 && symbol <= 0xff);
	}
	bool SyntaxAnalysator::IsHaveThisNamespace(std::string name) {
		for (string item : namespaces) {
			if (item == name)
				return true;
		}

		return false;
	}

	ExpressionElementType SyntaxAnalysator::GetExpressionElementType(string chain) {
		if (chain.size() == 1) {
			switch (chain[0])
			{
			case '+':
				return ExpressionElementType::Plus;
			case '-':
				return ExpressionElementType::Minus;
			case '*':
				return ExpressionElementType::Multi;
			case '/':
				return ExpressionElementType::Division;
			case '(':
				return ExpressionElementType::InBrack;
			case ')':
				return ExpressionElementType::OutBrack;
			case ',':
				return ExpressionElementType::And;
			case '!':
				return ExpressionElementType::LNot;
			case '<':
				return ExpressionElementType::LLess;
			case '>':
				return ExpressionElementType::LMore;
			}
		}
		else if (chain.size() == 2) {
			switch (chain[0])
			{
			case '=':
				if (chain[1] == '=')
					return ExpressionElementType::LEqual;
				else
					return ExpressionElementType::None;
			case '|':
				if (chain[1] == '|')
					return ExpressionElementType::LOr;
				else
					return ExpressionElementType::None;
			case '&':
				if (chain[1] == '&')
					return ExpressionElementType::LAnd;
				else
					return ExpressionElementType::None;
			case '<':
				if (chain[1] == '=')
					return ExpressionElementType::LEqLess;
				else
					return ExpressionElementType::None;
			case '>':
				if (chain[1] == '=')
					return ExpressionElementType::LEqMore;
				else
					return ExpressionElementType::None;
			case '!':
				if (chain[1] == '=')
					return ExpressionElementType::LNotEqual;
				else
					return ExpressionElementType::None;
			default:
				return ExpressionElementType::None;
			}
		}
		else 
			return ExpressionElementType::None;
	}

	string SyntaxAnalysator::GetStringNameOfVarType(VarType type) {
		switch (type)
		{
		case Data::VarType::Void:
			return "Void";
		case Data::VarType::Int:
			return "Int";
		case Data::VarType::Char:
			return "Char";
		case Data::VarType::String:
			return "String";
		case Data::VarType::Bool:
			return "Bool";
		default:
			return "Undefine";
		}
	}
}