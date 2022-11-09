#pragma once

namespace Data {
	class Rule
	{
	public:
		std::string ruleName; // Нужет для точного поиска правила и отладки

		std::vector<LexemType> chain;

		std::string initspace;

		virtual void Action() { }
	};
}