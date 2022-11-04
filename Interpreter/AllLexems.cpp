#include "stdafx.h"

using namespace std;
using namespace Collections;
using namespace LexemAnalysis;

namespace Data {
	void VarType::Action() 
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
			lexemAnalyzer->PrepareNamespace(lexemAnalyzer->literals->Get(lexemAnalyzer->literals->GetSize() - 1).data);

		lexemAnalyzer->OpenNamespace();

		lexemAnalyzer->PrepareNamespace("UNDEFINE");

		lexemAnalyzer->namespaceCount++;

		lexemAnalyzer->NAMESPACE = false;

		lexemAnalyzer->lexTable->NextLine();
	}
	void SpaceOut::Action()
	{
		lexemAnalyzer->CloseNamespace();

		lexemAnalyzer->lexTable->NextLine();
	}

	void ParamsIn::Action()
	{
		vector<char> end;
		end.push_back(')');
		end.push_back(',');

		lexemAnalyzer->ReadLiteral(LiteralType::Expression, end);

		lexemAnalyzer->PARAMS = true;

		lexemAnalyzer->paramsDepth++;

		if (lexemAnalyzer->paramsDepth == 1) {
			lexemAnalyzer->PrepareNamespace("FUNC." + lexemAnalyzer->literals->Get(lexemAnalyzer->literals->GetSize() - 1).data);
		}
	}
	void ParamsOut::Action()
	{
		lexemAnalyzer->paramsDepth--;

		if (lexemAnalyzer->paramsDepth == 0) 
			lexemAnalyzer->PARAMS = false;
	}

	void Equals::Action()
	{
		lexemAnalyzer->ReadLiteral(LiteralType::Expression, ';');
	}
	
	void And::Action()
	{
		if (lexemAnalyzer->PARAMS) {
			vector<char> end;
			end.push_back(')');
			end.push_back(',');

			lexemAnalyzer->ReadLiteral(LiteralType::Indefier, end);
		}
	}

	void RuleEnd::Action()
	{
		lexemAnalyzer->lexTable->NextLine();
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
	}

	void Comment::Action()
	{
	}

	void If::Action()
	{
	}
	void Else::Action()
	{
	}
}