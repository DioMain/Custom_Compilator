#pragma once

namespace SyntaxAnalysis {
	class SyntaxAnalysator
	{
	public:

		bool SOME_FLAG = false;

		int litIndex = 0;

		std::vector<Data::LexemData> currentLexemChain;
		
		Collections::DefaultRules* defRules;
		Collections::RuleColletion* rules;
		Collections::IndefierColletion* idefiers;
		Collections::LiteralsColletion* lits;

		SyntaxAnalysator() : table(nullptr), defRules(nullptr), rules(nullptr), idefiers(nullptr), lits(nullptr) { }

		SyntaxAnalysator(Collections::LexemsTable* table, Collections::DefaultRules* defRules, Collections::RuleColletion* rules,
			Collections::IndefierColletion* idefiers, Collections::LiteralsColletion* lits)
			: table(table), defRules(defRules), rules(rules), idefiers(idefiers), lits(lits) { }

		void Invoke();

	private:

		Collections::LexemsTable* table;
	};
}