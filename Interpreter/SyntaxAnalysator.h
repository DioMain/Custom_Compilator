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
		Collections::FuncColletion* funcs;
		Collections::VarColletion* vars;
		Collections::LiteralsColletion* lits;

		SyntaxAnalysator() : table(nullptr), defRules(nullptr), rules(nullptr), funcs(nullptr), vars(nullptr), lits(nullptr) { }

		SyntaxAnalysator(Collections::LexemsTable* table, Collections::DefaultRules* defRules, Collections::RuleColletion* rules,
			Collections::FuncColletion* funcs, Collections::VarColletion* vars, Collections::LiteralsColletion* lits)
			: table(table), defRules(defRules), rules(rules), funcs(funcs), vars(vars), lits(lits) { }

		void Invoke();

	private:

		Collections::LexemsTable* table;
	};
}