#include "stdafx.h"

using namespace std;
using namespace Collections;
using namespace LexemAnalysis;

namespace Data {
	void VarLexem::Action() 
	{
		vector<char> end;
		end.push_back(' ');
		end.push_back('=');
		end.push_back(';');
		end.push_back('(');

		lexemAnalyzer->ReadLiteral(LiteralType::Indefier, end);
	}
	void LiteralLexem::Action()
	{
		lexemAnalyzer->literals->Add(litData);
	}

	void SpaceInLex::Action()
	{
		if (lexemAnalyzer->NAMESPACE)
			lexemAnalyzer->PrepareNamespace(lexemAnalyzer->literals->GetLast().data);
		else if (lexemAnalyzer->IF && lexemAnalyzer->ELSE)
			lexemAnalyzer->PrepareNamespace("ELIF");
		else if (lexemAnalyzer->IF)
			lexemAnalyzer->PrepareNamespace("IF");
		else if (lexemAnalyzer->ELSE)
			lexemAnalyzer->PrepareNamespace("ELSE");

		lexemAnalyzer->OpenNamespace();

		lexemAnalyzer->PrepareNamespace("UNDEFINE");

		lexemAnalyzer->namespaceCounter++;

		lexemAnalyzer->NAMESPACE = false;

		lexemAnalyzer->lexTable->NextLine();

		lexemAnalyzer->IF = false;
		lexemAnalyzer->ELSE = false;
	}
	void SpaceOutLex::Action()
	{
		lexemAnalyzer->CloseNamespace();

		lexemAnalyzer->lexTable->NextLine();
	}

	void ParamsInLex::Action()
	{
		if (lexemAnalyzer->IF) {
			lexemAnalyzer->ReadLiteral(LiteralType::LogicExpression, ')');
		}
		else {
			vector<char> end;
			end.push_back(')');
			end.push_back(',');

			lexemAnalyzer->ReadLiteral(LiteralType::Expression, end);

			lexemAnalyzer->PARAMS = true;
			lexemAnalyzer->PARAM_READ = true;

			lexemAnalyzer->PrepareNamespace("FUNC." + lexemAnalyzer->literals->GetLastPointer()->data);
		}
	}
	void ParamsOutLex::Action()
	{
		lexemAnalyzer->PARAMS = false;
	}

	void EqualsLex::Action()
	{
		lexemAnalyzer->ReadLiteral(LiteralType::Expression, ';');

		lexemAnalyzer->NEED_LITERAL = true;
	}
	
	void AndLex::Action()
	{
		if (lexemAnalyzer->PARAMS) {
			vector<char> end;
			end.push_back(')');
			end.push_back(',');

			lexemAnalyzer->ReadLiteral(LiteralType::Indefier, end);

			lexemAnalyzer->PARAM_READ = true;
		}
	}

	void RuleEndLex::Action()
	{
		lexemAnalyzer->lexTable->NextLine();

		lexemAnalyzer->IF = false;
		lexemAnalyzer->ELSE = false;
	}

	void MainLex::Action()
	{
		lexemAnalyzer->PrepareNamespace("MAIN");
	}

	void ReturnLex::Action()
	{
		lexemAnalyzer->ReadLiteral(LiteralType::Expression, ';');
	}

	void NamespaceLex::Action()
	{
		vector<char> end;
		end.push_back(' ');
		end.push_back('{');

		lexemAnalyzer->ReadLiteral(LiteralType::Indefier, end);

		lexemAnalyzer->NAMESPACE = true;
		lexemAnalyzer->NEED_LITERAL = true;

		lexemAnalyzer->PrepareNamespace("UNDEFINE");
	}

	void CommentLex::Action()
	{
		lexemAnalyzer->COMMENT = true;

		lexemAnalyzer->lexTable->NextLine();
	}

	void IfLex::Action()
	{
		lexemAnalyzer->IF = true;
	}
	void ElseLex::Action()
	{
		lexemAnalyzer->ELSE = true;
	}
}