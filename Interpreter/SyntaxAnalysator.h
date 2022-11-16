#pragma once

namespace SyntaxAnalysis {
	class SyntaxAnalysator
	{
	public:

		bool MAIN = false;

		int line = 0, litIndex = 0;

		std::vector<Data::LexemData> currentLexemChain;

		std::vector<std::string> namespaces;

		std::stack<Data::IndefierData*> funcStack;

		Data::Rule* currentRule = nullptr;
		
		Collections::DefaultRules* defRules;
		Collections::RuleColletion* rules;
		Collections::IndefierColletion* idefiers;
		Collections::LiteralsColletion* lits;

		SyntaxAnalysator() 
			: table(nullptr), defRules(nullptr), rules(nullptr), idefiers(nullptr), lits(nullptr) { }

		SyntaxAnalysator(Collections::LexemsTable* table, Collections::DefaultRules* defRules, Collections::RuleColletion* rules,
			Collections::IndefierColletion* idefiers, Collections::LiteralsColletion* lits)
			: table(table), defRules(defRules), rules(rules), idefiers(idefiers), lits(lits) { }

		void Invoke();

		Data::VarType GetVarTypeByChain(std::string chain);

		Data::ExpressionNode* ParsingExpression(Data::Rule* rule, std::string chain, Data::ExpressionNode* lastNode);

		bool IsOperator(char letter);
		bool IsLetter(unsigned char symbol);
		Data::ExpressionElementType GetExpressionElementType(std::string chain);

		std::string GetStringNameOfVarType(Data::VarType type);

	private:

		Collections::LexemsTable* table;
	};
}