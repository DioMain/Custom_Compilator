#pragma once

namespace SyntaxAnalysis {
	class SyntaxAnalysator
	{
	public:

		bool MAIN = false,									// Флаг точки входа
			SAVE_NAMESPACE = false;							// Флаг записи пространсва имён

		int line = 0,										// Индекс цепочки лексем
			litIndex = 0;									// Индекс текущего литерала из списка литералов

		std::vector<Data::LexemData> currentLexemChain;		// цепочка лексем

		std::vector<std::string> namespaces;				// список пространств имён

		std::stack<Data::IndefierData*> funcStack;			// стек функций

		Data::Rule* currentRule = nullptr;					// текущее правило
		
		// Колекции
		Collections::DefaultRules* defRules;				// стандартные правила
		Collections::RuleColletion* rules;					// правила
		Collections::IndefierColletion* idefiers;			// индефикаторы
		Collections::LiteralsColletion* lits;				// литералы (raw literals)

		SyntaxAnalysator() 
			: table(nullptr), defRules(nullptr), rules(nullptr), idefiers(nullptr), lits(nullptr) { }

		SyntaxAnalysator(Collections::LexemsTable* table, Collections::DefaultRules* defRules, Collections::RuleColletion* rules,
			Collections::IndefierColletion* idefiers, Collections::LiteralsColletion* lits)
			: table(table), defRules(defRules), rules(rules), idefiers(idefiers), lits(lits) { }

		void Invoke();

		// Возврощает тип переменной по строковой цепочке
		Data::VarType GetVarTypeByChain(std::string chain);

		// Обрабатывает вырожение
		Data::ExpressionNode* ParsingExpression(Data::Rule* rule, std::string chain, Data::VarType ret);

		// Символ является оператором?
		bool IsOperator(char letter);
		// Символ является буквой?
		bool IsLetter(unsigned char symbol);
		// Имеется ли такое пространство имён?
		bool IsHaveThisNamespace(std::string name);

		// Возврощает тип элемента вырожения по строковой цепочке
		Data::ExpressionElementType GetExpressionElementType(std::string chain);

		// возращает строкое предстовление типа переменной
		std::string GetStringNameOfVarType(Data::VarType type);

	private:

		Collections::LexemsTable* table;				// Таблица лексем
	};
}