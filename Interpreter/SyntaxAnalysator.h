#pragma once

namespace SyntaxAnalysis {
	class SyntaxAnalysator
	{
	public:

		bool SOME_FLAG = false;

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

	private:

		Collections::LexemsTable* table;
	};
}