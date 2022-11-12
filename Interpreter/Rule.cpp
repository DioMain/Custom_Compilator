#include "stdafx.h"

namespace Data {
	Expression* Data::ExpressionData::ParsingExpression(std::string expression, Rule* rule)
	{

		return nullptr;
	}

	int Rule::GetCurLitIndex()
	{
		return analysator->litIndex;
	}
	LiteralData& Rule::GetLit(int index)
	{
		return analysator->lits->Get(index);
	}
	void Rule::AddLitIndex()
	{
		analysator->litIndex++;
	}

	IndefierData& Rule::GetLastIndefier()
	{
		return analysator->idefiers->GetLast();
	}
	IndefierData& Rule::GetIndefier(int index)
	{
		return analysator->idefiers->Get(index);
	}
	IndefierData& Rule::GetIndefierByName(std::string name)
	{
		return analysator->idefiers->GetByName(name);
	}
	bool Rule::IndefierIsExist(std::string name)
	{
		return analysator->idefiers->IsExist(name);
	}
	void Rule::AddNewIndefier(IndefierData ind) {
		analysator->idefiers->Add(ind);
	}

	LexemData& Rule::GetLexemFromChain(int index)
	{
		return analysator->currentLexemChain[index];
	}
}
