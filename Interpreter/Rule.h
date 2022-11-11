#pragma once

namespace Data {
	enum class ExpOperator
	{
		Plus, Minus, Division, Multi, InBrack, OutBrack, VarInd, FuncInd, QuoteOne, QuoteTwo, String,
		LAnd, LOr, LNot, LEqual, LNotEqual, LMore, LLess, LEqMore, LEqLess
	};

	struct ExpressionData
	{
		std::string expression;

		std::string traslatedExp;

		std::vector<ExpOperator> chain;
		std::vector<ExpressionData*> exps;
	};

	class Rule
	{
	public:
		std::string ruleName; // Нужет для точного поиска правила и отладки

		std::vector<LexemType> chain;
		std::vector<ExpressionData*> exps;

		std::string initspace;

		SyntaxAnalysis::SyntaxAnalysator* analysator;

		Rule() : ruleName("null"), chain(std::vector<LexemType>()), initspace(""), analysator(nullptr) { }
		Rule(std::string ruleName, std::vector<LexemType> chain, std::string initspace = "") 
			: ruleName(ruleName), chain(chain), initspace(initspace), analysator(nullptr) { }

		virtual void Action() { }
	};
}