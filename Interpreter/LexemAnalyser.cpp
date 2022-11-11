#include "stdafx.h"

using namespace std;
using namespace Data;
using namespace Collections;

namespace LexemAnalysis {
	void LexemAnalyser::Invoke()
	{
		// Выстовляем глобальную облость видимости
		PrepareNamespace("GLOBAL");
		OpenNamespace();

		namespaceCounter++;
		PrepareNamespace("UNDEFINE");

		while (true)
		{
			letter = code[index];

			// Если конец строки
			if (letter == LEXEM_ANALYSER_ENDL) ENDL = true;

			// Если конец кода
			if (letter == LEXEM_ANALYSER_CODEEND) CODE_END = true;

			// Если пробел и сейчас не пост. считывание и не параметр и не коментарий
			if (letter == LEXEM_ANALYSER_SPACE && !CONST_READ && !PARAMS && !COMMENT) SPACE = true;

			// Если " или '
			if (letter == LEXEM_ANALYSER_CHAR || letter == LEXEM_ANALYSER_STR)
				STRING_EXP = !STRING_EXP;

			// Если вырожение пустое
			if (expression.size() == 0) EXP_EMPTY = true;
			else EXP_EMPTY = false;

			// Если не пост. считывание и символ (или первый сивол выражения) является специальным
			if (!CONST_READ && (IsSpecialSymbol(letter) || IsSpecialSymbol(expression[0]))) SPECIAL = true;

			// Если пост. считывание м первый сивол выражения является специальным
			if (CONST_READ && IsSpecialSymbol(expression[0])) {
				SPECIAL = true;

				LITERAL = false;
				CONST_READ = false;

				if (PARAMS) PARAM_READ = false;
			}	

			// Если выражениея не строчное и мы закончили его считывать
			if (!STRING_EXP && LiteralReadEnd()) {
				CONST_READ = false;		
				READ_STOP = true;
			}

			// Специальная проверка для комментария
			// Если длинна вырожение 2 и первый, второй символ это / 
			if (expression.size() == 2 && expression[0] == '/' && expression[1] == '/') 
				SPECIAL = true;

			// Ошибка если переход на след. строки или конец кода и при этом мы считывает литерал
			if ((ENDL || CODE_END) && CONST_READ)
				throw ERROR_THROW_IN(121, line, col);

			// Ошибка если переход на след. строки или конец кода и при этом мы считывает строчный литерал
			if ((ENDL || CODE_END) && STRING_EXP)
				throw ERROR_THROW_IN(125, line, col);

			// Обработчик параметров
			// Если сейчас параметрб, мы его считывает, а саму лексему уже нет, не комментарий
			if (PARAMS && PARAM_READ && READ_STOP && !COMMENT) {
				if (!EXP_EMPTY) ParsingParam(expression);

				PARAM_READ = false;
				LITERAL = false;
				READ_STOP = false;

				expression.clear();
			}

			// Общий обработчик (для лексем и литералов)
			// Тут слишком большое условие мне его очень лень описывать
			if ((ENDL || CODE_END || SPACE || SPECIAL || READ_STOP) && !EXP_EMPTY && !PARAM_READ && !COMMENT) {
				// Если считывался литерал
				if (LITERAL) {
					// Выбираем по его типу
					switch (litType)
					{
					case LexemAnalysis::LiteralType::None:
						throw ERROR_THROW_IN(123, line, col);
						break;
					case LexemAnalysis::LiteralType::Indefier:
						currentLexem = new Indefier(expression);
						currentLexem->data.chain = "INDEFIER";
						break;
					case LexemAnalysis::LiteralType::Expression:
						currentLexem = new Expression(expression);
						currentLexem->data.chain = "EXPRESSION";
						break;
					case LexemAnalysis::LiteralType::LogicExpression:
						currentLexem = new LogicExpression(expression);
						currentLexem->data.chain = "LOGIC_EXPRESSION";
						break;
					}

					// Убираем флаги литералов
					NEED_LITERAL = false;
					LITERAL = false;
				}
				// Иначе просто ищем нужную лексему
				else currentLexem = lexDef->ParsingChain(expression);

				// Если обязательно нужен был литерал
				if (NEED_LITERAL)
					throw ERROR_THROW_IN(120, line, col);

				// Если не был найден такая лексема, однако уже есть литерал с такими данными
				// Это нужно что бы реализовать идентификаторы 
				if (currentLexem->data.type == LexemType::None && literals->IsExist(expression)) {
					currentLexem = new Indefier(expression);
					currentLexem->data.chain = "INDEFIER";
				}
				// Если по итогу нет такого литерала
				else if (currentLexem->data.type == LexemType::None)
					throw ERROR_THROW_IN(124, line, col);

				// Заполняем лексему данными
				currentLexem->lexemAnalyzer = this;				// Устанавливаем указатель на лексический анализатор
				currentLexem->data.space = GetFrontNamespace();	// Задаём лексеме её пространство имён

				lexTable->Add(currentLexem->data);				// Заносим лексему в таблицу

				currentLexem->Action();							// Вызываем событие этой лексемы

				expression.clear();								// Очищаем вырожение
			}

			// Добавляется символ в выражение
			if (!(ENDL || CODE_END || SPACE) && !COMMENT) expression.push_back(letter);

			// Если единсвенный символ вырожения это пробел
			if (expression.size() == 1 && expression[0] == LEXEM_ANALYSER_SPACE) expression.pop_back();;

			// Если остановилось считывание литерала, при этом выражение пустое, и нам всё же литерал необходим
			if (READ_STOP && EXP_EMPTY && NEED_LITERAL)
				throw ERROR_THROW_IN(120, line, col);

			// Если нет пространств имён
			if (namespaces.empty())
				throw ERROR_THROW_IN(122, line, col);

			index++;

			if (ENDL) {
				line++;
				col = 0;
			}
			else col++;

			// Если конец строки (кода) убераем комментарий
			if ((ENDL || CODE_END) && COMMENT) {
				COMMENT = false;

				expression.clear();
			}

			// Убераем некоторые флажки
			ENDL = false;
			SPACE = false;
			SPECIAL = false;
			READ_STOP = false;

			// Если конец кода то заканчивает анализ
			if (CODE_END) break;
		}

		// Если по мимо глобальной обл. вид. есть ещё что то
		if (namespaces.size() != 1)
			throw ERROR_THROW(126);

		currentLexem = new Data::CodeEnd();

		lexTable->Add(currentLexem->data);
	}

	// Подготавливет имя для нового пространства имён
	void LexemAnalyser::PrepareNamespace(std::string spacename = "UNDEFINE")
	{
		strstream str;

		str << spacename << "." << namespaceCounter << '\0';

		namespaceBuffer = str.str();
	}
	// Отрывает новое пространсво имён
	void LexemAnalyser::OpenNamespace()
	{
		namespaces.push_back(namespaceBuffer);
	}
	// Закрывает верхнее пространсво имён
	void LexemAnalyser::CloseNamespace()
	{
		namespaces.erase(namespaces.begin() + namespaces.size() - 1);
	}
	// Возврощает верхнее пространсво имён
	std::string LexemAnalyser::GetFrontNamespace()
	{
		return namespaces.back();
	}

	// Настраивает анализатор на считывание литерала до указанных символов
	void LexemAnalyser::ReadLiteral(LiteralType type, std::vector<char> endSymbols)
	{
		constReadEndSybols = endSymbols;

		LITERAL = true;
		CONST_READ = true;

		litType = type;
	}
	// Настраивает анализатор на считывание литерала до указанного символа
	void LexemAnalyser::ReadLiteral(LiteralType type, char endSymbol)
	{
		constReadEndSybols.clear();
		constReadEndSybols.push_back(endSymbol);

		LITERAL = true;
		CONST_READ = true;

		litType = type;
	}

	// Проверяет конец ли считывания литерала
	bool LexemAnalyser::LiteralReadEnd()
	{
		if (!STRING_EXP && CONST_READ) {
			for (size_t i = 0; i < constReadEndSybols.size(); i++)
			{
				if (letter == constReadEndSybols[i]) return true;
			}
		}

		return false;
	}

	// Разбирает параметр
	void LexemAnalyser::ParsingParam(std::string param)
	{
		string word;
		vector<string> words;

		// Разбивает параметр на слова
		for (size_t i = 0; i < param.size() + 1; i++)
		{
			if ((param[i] == ' ' || param[i] == '\0') && !word.empty()) {
				words.push_back(word);

				word.clear();
			}
			else if (param[i] != ' ' && param[i] != '\0') word += param[i];
		}
		
		// Если слова два
		if (words.size() == 2) {
			BasicLexem* lex = lexDef->ParsingChain(words[0]);

			// При этом первый это лексема типа переменной
			if (lex->data.type == LexemType::VarType) {
				// Тогла это объявление агрумента
				lexTable->Add(lex->data);
				lexTable->Add(Indefier(words[1]).data);

				lexTable->GetLast().chain = "INDEFIER";
				lexTable->GetLast().space = GetFrontNamespace();

				literals->Add(words[1]);

				return;
			}
		}

		// Если слово одно и при этом есть такой же литерал
		if (words.size() == 1 && literals->IsExist(words[0])) {
			// Тогда это идентификатор
			lexTable->Add(Indefier(words[0]).data);

			lexTable->GetLast().chain = "INDEFIER";
			lexTable->GetLast().space = GetFrontNamespace();

			literals->Add(words[0]);
		}
		else {
			// Иначе это просто какое-то вырожение
			lexTable->Add(Expression(param).data);

			lexTable->GetLast().chain = "EXPRESSION";
			lexTable->GetLast().space = GetFrontNamespace();

			literals->Add(param);
		}
	}

	// Проверяет входной символ на то что специальный ли он
	bool LexemAnalyser::IsSpecialSymbol(char symbol)
	{
		return symbol == '=' || symbol == '(' || symbol == ')' || symbol == ';'
			|| symbol == '{' || symbol == '}' || symbol == ',' || symbol == '.';
	}
}