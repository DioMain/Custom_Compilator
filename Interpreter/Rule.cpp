#include "stdafx.h"

namespace Data {

	// Вспомогательные методы (Нужны для сокращения записи) / Auxiliary methods (Needed to shorten the entry)

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

	IndefierData* Rule::GetLastIndefier()
	{
		return analysator->idefiers->GetLastPointer();
	}
	IndefierData* Rule::GetIndefier(int index)
	{
		return analysator->idefiers->GetPointer(index);
	}
	IndefierData* Rule::GetIndefierByName(std::string name)
	{
		return &analysator->idefiers->GetByName(name);
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
