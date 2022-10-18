#include "stdafx.h"

using namespace std;

namespace poland {
	void PolandNatation::CONVERT()
	{
		stack<char> operators;

		string result;

		string checkstr;

		bool READING = true,
			OPERATOR = false,
			FIND_CLOSE = false;


		int i = 0;
		char cur;

		do
		{
			cur = str[i];

			if (cur == ' ' || IsMathOperator(cur) || cur == '\0') READING = false;

			if (IsMathOperator(cur)) OPERATOR = true;

			if (READING) checkstr += cur;
			else {
				if (checkstr.size() > 0) {
					if (!IsNumber(checkstr)) 
						throw ERROR_THROW_IN_C(5, "Не верное вырожение", 0, i);

					result += checkstr;
					result += ' ';

					checkstr.clear();
				}

				if (OPERATOR) {
					if ((operators.empty() && cur == ')')) 
						throw ERROR_THROW_IN_C(5, "Не верное вырожение", 0, i);

					if (operators.empty() || cur == '(') operators.push(cur);
					else if (cur == ')') {
						FIND_CLOSE = true;

						while (operators.top() != '(')
						{
							result += operators.top();
							result += ' ';

							operators.pop();

							if (operators.empty()) {
								FIND_CLOSE = false;
								break;
							}
						}

						if (!FIND_CLOSE) 
							throw ERROR_THROW_IN_C(5, "Не верное вырожение", 0, i);

						operators.pop();
					}
					else {
						while (GetOperatorPriority(cur) <= GetOperatorPriority(operators.top()))
						{
							if (operators.top() == '(' || operators.top() == ')') 
								throw ERROR_THROW_IN_C(5, "Не верное вырожение", 0, i);

							result += operators.top();
							result += ' ';

							operators.pop();

							if (operators.empty()) break;
						}

						operators.push(cur);
					}
				}
			}

			READING = true;
			OPERATOR = false;

			i++;
		} while (cur != '\0');

		while (!operators.empty())
		{
			if (operators.top() == '(' || operators.top() == ')') 
				throw ERROR_THROW_C(5, "Не верное вырожение");

			result += operators.top();

			if (operators.size() > 1) result += ' ';

			operators.pop();
		}

		str = result;
	}

	bool PolandNatation::IsMathOperator(char letter)
	{
		return letter == '(' || letter == ')' || letter == '+' || letter == '-' || letter == '/' || letter == '*';
	}

	bool PolandNatation::IsNumber(string str)
	{
		for (short i = 0; i < str.size(); i++)
		{
			if (!(str[i] >= 0x30 && str[i] <= 0x39)) return false;
		}

		return true;
	}

	int PolandNatation::GetOperatorPriority(char oper)
	{
		switch (oper)
		{
		case '(':
			return 1;
		case ')':
			return 1;
		case '+':
			return 2;
		case '-':
			return 2;
		case '/':
			return 3;
		case '*':
			return 3;
		default:
			return 0;
		}
	}

	int PolandNatation::CalculateResult()
	{
		strstream stream;

		stack<int> numbers;

		string check;

		int a, b, c;

		for (int i = 0; i < str.size() + 1; i++)
		{
			if (str[i] != ' ' && str[i] != '\0') check += str[i];
			else {
				if (IsNumber(check)) {
					a = 0;

					for (int j = check.size() - 1; j >= 0; j--)
					{
						a += (check[j] - 0x30) * (pow(10, j));
					}

					numbers.push(a);
				}
				else {
					if (numbers.size() < 2) 
						throw ERROR_THROW_C(5, "Не верное вырожение");

					b = numbers.top();
					numbers.pop();
					a = numbers.top();
					numbers.pop();

					switch (check[0])
					{
					case '+':
						c = a + b;
						break;
					case '-':
						c = a - b;
						break;
					case '*':
						c = a * b;
						break;
					case '/':
						c = (int)round(a / b);
						break;
					}

					numbers.push(c);
				}

				check.clear();
			}
		}

		return numbers.top();
	}
}