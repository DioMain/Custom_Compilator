#include "stdafx.h"

using namespace std;
using namespace Data;

namespace Data {
	void VarCreate::Action()
	{
		// Error
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data)) return;

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, var, initspace));

		AddLitIndex();
	}
	void VarCreateAndInit::Action()
	{
		// Error
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data)) return;

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, var, initspace));

		AddLitIndex();

		// Нужна проверка на тип
		GetLastIndefier().data = GetLit(GetCurLitIndex()).data;

		AddLitIndex();
	}
	void VarAssign::Action()
	{
		// Error
		if (!IndefierIsExist(GetLit(GetCurLitIndex()).data)) return;

		// Нужна проверка на тип
		GetIndefierByName(GetLit(GetCurLitIndex()).data).data = GetLit(GetCurLitIndex() + 1).data;

		AddLitIndex();
		AddLitIndex();
	}

	void CreateNamespace::Action()
	{
		AddLitIndex();
	}

	void OpenSpace::Action()
	{
	}
	void CloseSpace::Action()
	{
	}

	void FuncCreate::Action()
	{
		// Error
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data)) return;

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, var, initspace, true));

		AddLitIndex();

		GetLastIndefier().paramsCount = paramsChain.size();

		int offset = 3;
		for (size_t i = 0; i < paramsChain.size(); i++)
		{
			var = analysator->GetVarTypeByChain(GetLexemFromChain(offset).chain);

			AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, var, initspace, false));

			AddLitIndex();
		}

		//analysator->funcStack.push(&GetLastIndefier());
	}
	void FuncUse::Action()
	{
		// Error
		if (!IndefierIsExist(GetLit(GetCurLitIndex()).data)) return;

		AddLitIndex();

		analysator->litIndex += paramsChain.size();
	}

	void MainCreate::Action()
	{
	}

	void ReturnRule::Action()
	{
		//if (analysator->funcStack.empty()) return;

		//analysator->funcStack.pop();

		AddLitIndex();
	}
}