#pragma once

namespace Data {
	class Rule;

	enum class ExpressionElementType
	{
		None, Const, Func, Var, Plus, Minus, Division, Multi, InBrack, OutBrack, QuoteOne, QuoteTwo, String,
		LAnd, LOr, LNot, LEqual, LNotEqual, LMore, LLess, LEqMore, LEqLess, And
	};

	struct ExpressionNode
	{
		std::vector<ExpressionNode*> subExpressions;

		std::vector<std::string> elementsData;
		std::vector<ExpressionElementType> elementChain;
		std::vector<VarType> typeChain;

		Rule* selfRule;

		VarType returnType;
	};

	class Rule
	{
	public:
		std::string name; // ����� ��� ������� ������ ������� � �������
			
		std::vector<ExpressionNode*> expressionsRoot;

		std::vector<LexemType> fullChain;
		std::vector<LexemType> commonChain;		
		std::vector<LexemType> paramsChain;

		VarType retTypeBuffer;

		std::string initspace;

		SyntaxAnalysis::SyntaxAnalysator* analysator;

		Rule() : name("null"), commonChain(std::vector<LexemType>()), initspace(""), retTypeBuffer(VarType::Void), analysator(nullptr) { }
		Rule(std::string ruleName, std::vector<LexemType> chain, std::string initspace = "") 
			: name(ruleName), commonChain(chain), initspace(initspace), retTypeBuffer(VarType::Void), analysator(nullptr) { }

		virtual void Action() { }

		// ��������������� ������ (����� ��� ���������� ������) / Auxiliary methods (Needed to shorten the entry)

		int GetCurLitIndex();
		LiteralData& GetLit(int index);
		void AddLitIndex();

		IndefierData* GetLastIndefier();
		IndefierData* GetIndefier(int index);
		IndefierData* GetIndefierByName(std::string name);
		bool IndefierIsExist(std::string name);
		void AddNewIndefier(IndefierData ind);

		LexemData& GetLexemFromChain(int index);
	};
}