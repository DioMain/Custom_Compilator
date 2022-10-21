#pragma once

namespace poland {
	class PolandNatation
	{
	public:

		Error::PolandError error;

		bool failed;

		std::string ToString() { return str; }

		PolandNatation(std::string str) : str(str), error(), failed(false) { CONVERT(); }

		int CalculateResult();

		static int GetOperatorPriority(char oper);

		static bool IsNumber(std::string str);

		static bool IsMathOperator(char letter);

	private:

		std::string str;

		void CONVERT();
	};
}
