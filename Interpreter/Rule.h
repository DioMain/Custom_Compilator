#pragma once

namespace Data {
	class Rule
	{
	public:
		std::string ruleName; // ����� ��� ������� ������ ������� � �������

		std::vector<LexemType> chain;

		std::string initspace;

		virtual void Action() { }
	};
}