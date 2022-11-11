#include "stdafx.h"

using namespace std;
using namespace Data;
using namespace Collections;

namespace LexemAnalysis {
	void LexemAnalyser::Invoke()
	{
		// ���������� ���������� ������� ���������
		PrepareNamespace("GLOBAL");
		OpenNamespace();

		namespaceCounter++;
		PrepareNamespace("UNDEFINE");

		while (true)
		{
			letter = code[index];

			// ���� ����� ������
			if (letter == LEXEM_ANALYSER_ENDL) ENDL = true;

			// ���� ����� ����
			if (letter == LEXEM_ANALYSER_CODEEND) CODE_END = true;

			// ���� ������ � ������ �� ����. ���������� � �� �������� � �� ����������
			if (letter == LEXEM_ANALYSER_SPACE && !CONST_READ && !PARAMS && !COMMENT) SPACE = true;

			// ���� " ��� '
			if (letter == LEXEM_ANALYSER_CHAR || letter == LEXEM_ANALYSER_STR)
				STRING_EXP = !STRING_EXP;

			// ���� ��������� ������
			if (expression.size() == 0) EXP_EMPTY = true;
			else EXP_EMPTY = false;

			// ���� �� ����. ���������� � ������ (��� ������ ����� ���������) �������� �����������
			if (!CONST_READ && (IsSpecialSymbol(letter) || IsSpecialSymbol(expression[0]))) SPECIAL = true;

			// ���� ����. ���������� � ������ ����� ��������� �������� �����������
			if (CONST_READ && IsSpecialSymbol(expression[0])) {
				SPECIAL = true;

				LITERAL = false;
				CONST_READ = false;

				if (PARAMS) PARAM_READ = false;
			}	

			// ���� ���������� �� �������� � �� ��������� ��� ���������
			if (!STRING_EXP && LiteralReadEnd()) {
				CONST_READ = false;		
				READ_STOP = true;
			}

			// ����������� �������� ��� �����������
			// ���� ������ ��������� 2 � ������, ������ ������ ��� / 
			if (expression.size() == 2 && expression[0] == '/' && expression[1] == '/') 
				SPECIAL = true;

			// ������ ���� ������� �� ����. ������ ��� ����� ���� � ��� ���� �� ��������� �������
			if ((ENDL || CODE_END) && CONST_READ)
				throw ERROR_THROW_IN(121, line, col);

			// ������ ���� ������� �� ����. ������ ��� ����� ���� � ��� ���� �� ��������� �������� �������
			if ((ENDL || CODE_END) && STRING_EXP)
				throw ERROR_THROW_IN(125, line, col);

			// ���������� ����������
			// ���� ������ ���������, �� ��� ���������, � ���� ������� ��� ���, �� �����������
			if (PARAMS && PARAM_READ && READ_STOP && !COMMENT) {
				if (!EXP_EMPTY) ParsingParam(expression);

				PARAM_READ = false;
				LITERAL = false;
				READ_STOP = false;

				expression.clear();
			}

			// ����� ���������� (��� ������ � ���������)
			// ��� ������� ������� ������� ��� ��� ����� ���� ���������
			if ((ENDL || CODE_END || SPACE || SPECIAL || READ_STOP) && !EXP_EMPTY && !PARAM_READ && !COMMENT) {
				// ���� ���������� �������
				if (LITERAL) {
					// �������� �� ��� ����
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

					// ������� ����� ���������
					NEED_LITERAL = false;
					LITERAL = false;
				}
				// ����� ������ ���� ������ �������
				else currentLexem = lexDef->ParsingChain(expression);

				// ���� ����������� ����� ��� �������
				if (NEED_LITERAL)
					throw ERROR_THROW_IN(120, line, col);

				// ���� �� ��� ������ ����� �������, ������ ��� ���� ������� � ������ �������
				// ��� ����� ��� �� ����������� �������������� 
				if (currentLexem->data.type == LexemType::None && literals->IsExist(expression)) {
					currentLexem = new Indefier(expression);
					currentLexem->data.chain = "INDEFIER";
				}
				// ���� �� ����� ��� ������ ��������
				else if (currentLexem->data.type == LexemType::None)
					throw ERROR_THROW_IN(124, line, col);

				// ��������� ������� �������
				currentLexem->lexemAnalyzer = this;				// ������������� ��������� �� ����������� ����������
				currentLexem->data.space = GetFrontNamespace();	// ����� ������� � ������������ ���

				lexTable->Add(currentLexem->data);				// ������� ������� � �������

				currentLexem->Action();							// �������� ������� ���� �������

				expression.clear();								// ������� ���������
			}

			// ����������� ������ � ���������
			if (!(ENDL || CODE_END || SPACE) && !COMMENT) expression.push_back(letter);

			// ���� ����������� ������ ��������� ��� ������
			if (expression.size() == 1 && expression[0] == LEXEM_ANALYSER_SPACE) expression.pop_back();;

			// ���� ������������ ���������� ��������, ��� ���� ��������� ������, � ��� �� �� ������� ���������
			if (READ_STOP && EXP_EMPTY && NEED_LITERAL)
				throw ERROR_THROW_IN(120, line, col);

			// ���� ��� ����������� ���
			if (namespaces.empty())
				throw ERROR_THROW_IN(122, line, col);

			index++;

			if (ENDL) {
				line++;
				col = 0;
			}
			else col++;

			// ���� ����� ������ (����) ������� �����������
			if ((ENDL || CODE_END) && COMMENT) {
				COMMENT = false;

				expression.clear();
			}

			// ������� ��������� ������
			ENDL = false;
			SPACE = false;
			SPECIAL = false;
			READ_STOP = false;

			// ���� ����� ���� �� ����������� ������
			if (CODE_END) break;
		}

		// ���� �� ���� ���������� ���. ���. ���� ��� ��� ��
		if (namespaces.size() != 1)
			throw ERROR_THROW(126);

		currentLexem = new Data::CodeEnd();

		lexTable->Add(currentLexem->data);
	}

	// ������������� ��� ��� ������ ������������ ���
	void LexemAnalyser::PrepareNamespace(std::string spacename = "UNDEFINE")
	{
		strstream str;

		str << spacename << "." << namespaceCounter << '\0';

		namespaceBuffer = str.str();
	}
	// �������� ����� ����������� ���
	void LexemAnalyser::OpenNamespace()
	{
		namespaces.push_back(namespaceBuffer);
	}
	// ��������� ������� ����������� ���
	void LexemAnalyser::CloseNamespace()
	{
		namespaces.erase(namespaces.begin() + namespaces.size() - 1);
	}
	// ���������� ������� ����������� ���
	std::string LexemAnalyser::GetFrontNamespace()
	{
		return namespaces.back();
	}

	// ����������� ���������� �� ���������� �������� �� ��������� ��������
	void LexemAnalyser::ReadLiteral(LiteralType type, std::vector<char> endSymbols)
	{
		constReadEndSybols = endSymbols;

		LITERAL = true;
		CONST_READ = true;

		litType = type;
	}
	// ����������� ���������� �� ���������� �������� �� ���������� �������
	void LexemAnalyser::ReadLiteral(LiteralType type, char endSymbol)
	{
		constReadEndSybols.clear();
		constReadEndSybols.push_back(endSymbol);

		LITERAL = true;
		CONST_READ = true;

		litType = type;
	}

	// ��������� ����� �� ���������� ��������
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

	// ��������� ��������
	void LexemAnalyser::ParsingParam(std::string param)
	{
		string word;
		vector<string> words;

		// ��������� �������� �� �����
		for (size_t i = 0; i < param.size() + 1; i++)
		{
			if ((param[i] == ' ' || param[i] == '\0') && !word.empty()) {
				words.push_back(word);

				word.clear();
			}
			else if (param[i] != ' ' && param[i] != '\0') word += param[i];
		}
		
		// ���� ����� ���
		if (words.size() == 2) {
			BasicLexem* lex = lexDef->ParsingChain(words[0]);

			// ��� ���� ������ ��� ������� ���� ����������
			if (lex->data.type == LexemType::VarType) {
				// ����� ��� ���������� ���������
				lexTable->Add(lex->data);
				lexTable->Add(Indefier(words[1]).data);

				lexTable->GetLast().chain = "INDEFIER";
				lexTable->GetLast().space = GetFrontNamespace();

				literals->Add(words[1]);

				return;
			}
		}

		// ���� ����� ���� � ��� ���� ���� ����� �� �������
		if (words.size() == 1 && literals->IsExist(words[0])) {
			// ����� ��� �������������
			lexTable->Add(Indefier(words[0]).data);

			lexTable->GetLast().chain = "INDEFIER";
			lexTable->GetLast().space = GetFrontNamespace();

			literals->Add(words[0]);
		}
		else {
			// ����� ��� ������ �����-�� ���������
			lexTable->Add(Expression(param).data);

			lexTable->GetLast().chain = "EXPRESSION";
			lexTable->GetLast().space = GetFrontNamespace();

			literals->Add(param);
		}
	}

	// ��������� ������� ������ �� �� ��� ����������� �� ��
	bool LexemAnalyser::IsSpecialSymbol(char symbol)
	{
		return symbol == '=' || symbol == '(' || symbol == ')' || symbol == ';'
			|| symbol == '{' || symbol == '}' || symbol == ',' || symbol == '.';
	}
}