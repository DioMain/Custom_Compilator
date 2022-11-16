#include "stdafx.h"

using namespace std;
using namespace Data;

namespace Data {
	void VarDeclareRule::Action()
	{
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data))
			throw ERROR_THROW_IN_C(0, "Такой идентификатор уже сущетвует!", GetLexemFromChain(0).line, 0);

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, IndefierType::Var, var, initspace));

		AddLitIndex();
	}
	void VarDeclareAndInitRule::Action()
	{
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data))
			throw ERROR_THROW_IN_C(0, "Такой идентификатор уже сущетвует!", GetLexemFromChain(0).line, 0);

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, IndefierType::Var, var, initspace));

		IndefierData* curInd = GetLastIndefier();

		AddLitIndex();

		retTypeBuffer = curInd->dataType;

		ExpressionNode* exp = analysator->ParsingExpression(this, GetLit(GetCurLitIndex()).data, nullptr);

		if (exp->subExpressions.empty() && exp->elementChain.size() == 1)
			curInd->data = exp->elementsData[0];
		else
			expressionsRoot.push_back(exp);

		AddLitIndex();
	}
	void VarAssignRule::Action()
	{
		if (!IndefierIsExist(GetLit(GetCurLitIndex()).data))
			throw ERROR_THROW_IN_C(0, "Такой идентификатор не сущетвует!", GetLexemFromChain(0).line, 0);

		IndefierData* curInd = GetIndefierByName(GetLit(GetCurLitIndex()).data);

		if (curInd->isFunc)
			throw ERROR_THROW_IN_C(0, "Этот идентификатор указывает на фунцию!", GetLexemFromChain(0).line, 0);

		AddLitIndex();

		retTypeBuffer = curInd->dataType;

		ExpressionNode* exp = analysator->ParsingExpression(this, GetLit(GetCurLitIndex()).data, nullptr);

		expressionsRoot.push_back(exp);

		AddLitIndex();
	}

	void NamespaceDeclareRule::Action()
	{
		AddLitIndex();
	}

	void OpenSpaceRule::Action()
	{
	}
	void CloseSpaceRule::Action()
	{
		if (GetLexemFromChain(0).space.substr(0, 4) == "FUNC")
			analysator->funcStack.pop();
	}

	void FuncDeclareRule::Action()
	{
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data))
			throw ERROR_THROW_IN_C(0, "Такая идентификатор уже сущетвует!", GetLexemFromChain(0).line, 0);

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, IndefierType::Func, var, initspace, true));

		IndefierData* funcInd = GetLastIndefier();

		analysator->funcStack.push(funcInd);

		AddLitIndex();

		int offset = 3;
		for (size_t i = 0; i < paramsChain.size(); i++)
		{
			var = analysator->GetVarTypeByChain(GetLexemFromChain(offset).chain);

			AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, IndefierType::Param, var, initspace, false));	

			GetLastIndefier()->belong = funcInd;

			funcInd->params.push_back(GetLastIndefier());

			offset += 3;

			AddLitIndex();
		}
	}
	void FuncDecNonParamsRule::Action()
	{
		if (IndefierIsExist(GetLit(GetCurLitIndex()).data))
			throw ERROR_THROW_IN_C(0, "Такая идентификатор уже сущетвует!", GetLexemFromChain(0).line, 0);

		VarType var = analysator->GetVarTypeByChain(GetLexemFromChain(0).chain);

		AddNewIndefier(IndefierData(GetLit(GetCurLitIndex()).data, IndefierType::Func, var, initspace, true));

		IndefierData* funcInd = GetLastIndefier();

		analysator->funcStack.push(funcInd);

		AddLitIndex();
	}
	void FuncUseRule::Action()
	{
		if (!IndefierIsExist(GetLit(GetCurLitIndex()).data)) 
			throw ERROR_THROW_IN_C(0, "Такой идентификатор не сущетвует!", GetLexemFromChain(0).line, 0);

		IndefierData* curInd = GetIndefierByName(GetLit(GetCurLitIndex()).data);

		if (!curInd->isFunc)
			throw ERROR_THROW_IN_C(0, "Этот идентификатор не указывает на фунцию!", GetLexemFromChain(0).line, 0);

		if (curInd->params.size() != paramsChain.size())
			throw ERROR_THROW_IN_C(0, "Функция не принемает столько аргументов!", GetLexemFromChain(0).line, 0);

		AddLitIndex();

		for (size_t i = 0; i < paramsChain.size(); i++)
		{
			retTypeBuffer = curInd->params[i]->dataType;

			expressionsRoot.push_back(analysator->ParsingExpression(this, GetLit(GetCurLitIndex()).data, nullptr));

			AddLitIndex();
		}
	}

	void MainDeclareRule::Action()
	{
		analysator->MAIN = true;
	}

	void ReturnRule::Action()
	{
		IndefierData* curInd = analysator->funcStack.top();

		retTypeBuffer = curInd->dataType;

		ExpressionNode* exp = analysator->ParsingExpression(this, GetLit(GetCurLitIndex()).data, nullptr);

		expressionsRoot.push_back(exp);

		AddLitIndex();
	}

	void IfRule::Action() {
		retTypeBuffer = VarType::Bool;

		ExpressionNode* exp = analysator->ParsingExpression(this, GetLit(GetCurLitIndex()).data, nullptr);

		expressionsRoot.push_back(exp);

		AddLitIndex();
	}
	void ElseIfRule::Action() {
		retTypeBuffer = VarType::Bool;

		ExpressionNode* exp = analysator->ParsingExpression(this, GetLit(GetCurLitIndex()).data, nullptr);

		expressionsRoot.push_back(exp);

		AddLitIndex();
	}
	void ElseRule::Action() {

	}
}