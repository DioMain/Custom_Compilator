#pragma once

namespace Data {
	class Rule;

	enum class ExpOperator
	{
		Plus, Minus, Division, Multi, InBrack, Const, OutBrack, VarInd, FuncInd, QuoteOne, QuoteTwo, String,
		LAnd, LOr, LNot, LEqual, LNotEqual, LMore, LLess, LEqMore, LEqLess
	};

	struct ExpressionData
	{
		std::string expression;

		Data::VarType retType;

		std::string traslatedExp;

		std::vector<ExpOperator> chain;
		std::vector<ExpressionData*> exps;

		static Expression* ParsingExpression(std::string expression, Rule* rule);
	};

	class Rule
	{
	public:
		std::string ruleName; // Нужет для точного поиска правила и отладки

		std::vector<LexemType> chain;		
		std::vector<ExpressionData*> exps;

		std::vector<LexemType> fullChain;
		std::vector<LexemType> paramsChain;

		std::string initspace;

		SyntaxAnalysis::SyntaxAnalysator* analysator;

		Rule() : ruleName("null"), chain(std::vector<LexemType>()), initspace(""), analysator(nullptr) { }
		Rule(std::string ruleName, std::vector<LexemType> chain, std::string initspace = "") 
			: ruleName(ruleName), chain(chain), initspace(initspace), analysator(nullptr) { }	

		virtual void Action() { }

		int GetCurLitIndex();
		LiteralData& GetLit(int index);
		void AddLitIndex();

		IndefierData& GetLastIndefier();
		IndefierData& GetIndefier(int index);
		IndefierData& GetIndefierByName(std::string name);
		bool IndefierIsExist(std::string name);
		void AddNewIndefier(IndefierData ind);

		LexemData& GetLexemFromChain(int index);
	};
}