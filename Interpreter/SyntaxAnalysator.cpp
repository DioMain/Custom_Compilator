#include "stdafx.h"

using namespace std;
using namespace Data;
using namespace Collections;

namespace SyntaxAnalysis {
	void SyntaxAnalysator::Invoke()
	{
		while (true)
		{
			currentLexemChain = table->table[line];

			if (currentLexemChain[0].type == LexemType::CodeEnd) break;

			currentRule = defRules->ParsingChain(currentLexemChain);

			currentRule->analysator = this;

			currentRule->Action();

			rules->Add(*currentRule);

			line++;
		}
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
}