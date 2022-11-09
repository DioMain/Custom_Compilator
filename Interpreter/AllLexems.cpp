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
	void Literal::Action()
	{
		lexemAnalyzer->literals->Add(litData);
	}

	void SpaceIn::Action()
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
	void SpaceOut::Action()
	{
		lexemAnalyzer->CloseNamespace();

		lexemAnalyzer->lexTable->NextLine();
	}

	void ParamsIn::Action()
	{
		if (lexemAnalyzer->IF) {
			lexemAnalyzer->ReadLiteral(LiteralType::LogicEpression, ')');
		}
		else {
			vector<char> end;
			end.push_back(')');
			end.push_back(',');

			lexemAnalyzer->ReadLiteral(LiteralType::Expression, end);

			lexemAnalyzer->PARAMS = true;
			lexemAnalyzer->PARAM_READ = true;

			lexemAnalyzer->PrepareNamespace("FUNC." + lexemAnalyzer->literals->GetLast().data);
		}
	}
	void ParamsOut::Action()
	{
		lexemAnalyzer->PARAMS = false;
	}

	void Equals::Action()
	{
		lexemAnalyzer->ReadLiteral(LiteralType::Expression, ';');

		lexemAnalyzer->NEED_LITERAL = true;
	}
	
	void And::Action()
	{
		if (lexemAnalyzer->PARAMS) {
			vector<char> end;
			end.push_back(')');
			end.push_back(',');

			lexemAnalyzer->ReadLiteral(LiteralType::Indefier, end);

			lexemAnalyzer->PARAM_READ = true;
		}
	}

	void RuleEnd::Action()
	{
		lexemAnalyzer->lexTable->NextLine();

		lexemAnalyzer->IF = false;
		lexemAnalyzer->ELSE = false;
	}

	void Main::Action()
	{
		lexemAnalyzer->PrepareNamespace("MAIN");
	}

	void Return::Action()
	{
		lexemAnalyzer->ReadLiteral(LiteralType::Expression, ';');
	}

	void Namespace::Action()
	{
		vector<char> end;
		end.push_back(' ');
		end.push_back('{');

		lexemAnalyzer->ReadLiteral(LiteralType::Indefier, end);

		lexemAnalyzer->NAMESPACE = true;
		lexemAnalyzer->NEED_LITERAL = true;

		lexemAnalyzer->PrepareNamespace("UNDEFINE");
	}

	void Comment::Action()
	{
		lexemAnalyzer->COMMENT = true;

		lexemAnalyzer->lexTable->NextLine();
	}

	void If::Action()
	{
		lexemAnalyzer->IF = true;
	}
	void Else::Action()
	{
		lexemAnalyzer->ELSE = true;
	}
}