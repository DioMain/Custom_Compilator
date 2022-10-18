#pragma once

namespace poland {
	class PolandNatation
	{
	public:

		PolandNatation(std::string str) : str(str) { CONVERT(); }

		std::string ToString() { return str; }

		int CalculateResult();

		static int GetOperatorPriority(char oper);

		static bool IsNumber(std::string str);

		static bool IsMathOperator(char letter);

	private:

		void CONVERT();

		std::string str;
	};
}
