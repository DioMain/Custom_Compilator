#pragma once

namespace Data {
	class Rule
	{
	public:
		std::string ruleName; // Нужет для точного поиска правила и отладки

		std::vector<LexemType> chain;

		std::string initspace;

		SyntaxAnalysis::SyntaxAnalysator* analysator;

		Rule() : ruleName("null"), chain(std::vector<LexemType>()), initspace(""), analysator(nullptr) { }
		Rule(std::string ruleName, std::vector<LexemType> chain, std::string initspace = "") 
			: ruleName(ruleName), chain(chain), initspace(initspace), analysator(nullptr) { }

		virtual void Action() { }
	};
}