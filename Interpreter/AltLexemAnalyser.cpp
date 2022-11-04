#include "stdafx.h"

using namespace std;
using namespace Data;
using namespace Collections;

namespace LexemAnalysis {
	void LexemAnalyser::Invoke()
	{
		PrepareNamespace("GLOBAL");
		OpenNamespace();

		namespaceCount++;
		PrepareNamespace("UNDEFINE");

		while (true)
		{
			letter = code[index];

			if (letter == LEXEM_ANALYSER_ENDL) ENDL = true;

			if (letter == LEXEM_ANALYSER_CODEEND) CODEEND = true;

			if (letter == LEXEM_ANALYSER_SPACE && !CONSTREAD && !PARAMS) SPACE = true;

			if (CONSTREAD && (letter == LEXEM_ANALYSER_CHAR || letter == LEXEM_ANALYSER_STR))
				STRINGEXP = !STRINGEXP;

			if (!STRINGEXP && IsSpecialSymbol(expression[0])) SPECIAL = true;

			if (!CONSTREAD && IsSpecialSymbol(letter)) SPECIAL = true;

			if (!STRINGEXP && CONSTREAD) {
				for (size_t i = 0; i < constReadEndSybols.size(); i++)
				{
					if (letter == constReadEndSybols[i]) {
						SPECIAL = true;

						CONSTREAD = false;
					}
				}
			}

			if ((ENDL || CODEEND || SPACE || SPECIAL) && !expression.empty()) {
				if (LITERAL) {
					switch (litType)
					{
					case LexemAnalysis::LiteralType::None:
						throw ERROR_THROW_IN_C(0, "Неизвестный литерал!", line, col);
						break;
					case LexemAnalysis::LiteralType::Indefier:
						currentLexem = new Indefier(expression);
						currentLexem->data.chain = "INDEFIER";
						break;
					case LexemAnalysis::LiteralType::Expression:
						currentLexem = new Expression(expression);
						currentLexem->data.chain = "EXPRESSION";
						break;
					case LexemAnalysis::LiteralType::LogicEpression:
						currentLexem = new LogicExpression(expression);
						currentLexem->data.chain = "LOGIC_EXPRESSION";
						break;
					}

					LITERAL = false;
				}
				else currentLexem = lexDef->ParsingChain(expression);

				if (currentLexem->data.type == LexemType::None && literals->IsExist(expression)) {
					currentLexem = new Indefier(expression);
					currentLexem->data.chain = "INDEFIER";
				}
				else if (currentLexem->data.type == LexemType::None)
					throw ERROR_THROW_IN_C(0, "Неизавестная лексема", line, col);

				currentLexem->lexemAnalyzer = this;
				currentLexem->data.space = GetFrontNamespace();

				lexTable->Add(currentLexem->data);

				currentLexem->Action();

				expression.clear();
			}

			if (!(ENDL || CODEEND || SPACE)) expression.push_back(letter);

			if (expression.size() == 1 && letter == LEXEM_ANALYSER_SPACE) expression.clear();;

			index++;

			if (ENDL) {
				line++;
				col = 1;
			}
			else col++;

			ENDL = false;
			SPACE = false;
			SPECIAL = false;

			if (CODEEND) break;
		}
	}

	void LexemAnalyser::PrepareNamespace(std::string spacename = "UNDEFINE")
	{
		strstream str;

		str << spacename << "." << namespaceCount << '\0';

		namespaceBuffer = str.str();
	}
	void LexemAnalyser::OpenNamespace()
	{
		namespaces.push_back(namespaceBuffer);
	}
	void LexemAnalyser::CloseNamespace()
	{
		namespaces.erase(namespaces.begin() + namespaces.size() - 1);
	}
	std::string LexemAnalyser::GetFrontNamespace()
	{
		return namespaces.back();
	}

	void LexemAnalyser::ReadLiteral(LiteralType type, std::vector<char> endSymbols)
	{
		constReadEndSybols = endSymbols;

		LITERAL = true;
		CONSTREAD = true;

		litType = type;
	}
	void LexemAnalyser::ReadLiteral(LiteralType type, char endSymbol)
	{
		constReadEndSybols.clear();
		constReadEndSybols.push_back(endSymbol);

		LITERAL = true;
		CONSTREAD = true;

		litType = type;
	}

	void LexemAnalyser::ParsingParam(std::string param)
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

		if (words.size() == 2) {
			BasicLexem* lex = lexDef->ParsingChain(words[0]);

			if (lex->data.type == LexemType::VarType) {
				lexTable->Add(lex->data);
				lexTable->Add(Indefier(words[1]).data);

				lexTable->Get(lexTable->GetLinesCount() - 1, lexTable->GetLineSize(lexTable->GetLinesCount() - 1) - 1).chain = "INDEFIER";

				literals->Add(words[1]);

				return;
			}
		}

		if (words.size() == 1 && literals->IsExist(words[0])) {
			lexTable->Add(Indefier(words[0]).data);

			lexTable->Get(lexTable->GetLinesCount() - 1, lexTable->GetLineSize(lexTable->GetLinesCount() - 1) - 1).chain = "INDEFIER";

			literals->Add(words[0]);
		}
		else {
			lexTable->Add(Expression(param).data);

			lexTable->Get(lexTable->GetLinesCount() - 1, lexTable->GetLineSize(lexTable->GetLinesCount() - 1) - 1).chain = "EXPRESSION";

			literals->Add(param);
		}
	}

	bool LexemAnalyser::IsSpecialSymbol(char symbol)
	{
		return symbol == '=' || symbol == '/' || symbol == '(' || symbol == ')' || symbol == ';'
			|| symbol == '{' || symbol == '}' || symbol == ',' || symbol == '.';
	}
}