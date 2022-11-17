#include "stdafx.h"

using namespace std;
using namespace Data;



namespace poland {

	void PolandNatation::TranslateRecursive(std::vector<Data::ExpressionNode*> NodeVec) {

		for (size_t i = 0; i < NodeVec.size(); i++)
		{
			if (NodeVec[i]->subExpressions.size() > 0)
				TranslateRecursive(NodeVec[i]->subExpressions);

			NodeVec[i] = Translate(NodeVec[i]);
		}
	}

	ExpressionNode* PolandNatation::Translate(ExpressionNode* node) {
		stack<EET> operatorsStack;

		vector<EET> result;
		vector<string> data;
		vector<VarType> types;

		bool OPERATOR = false,
			FIND_CLOSE = false;

		int index = 0;
		int dataIndex = 0;
		EET current;

		do
		{
			current = node->elementChain[index];

			if (current != EET::Const && current != EET::Var && current != EET::Func)
				OPERATOR = true;

			if (OPERATOR) {
				if ((operatorsStack.empty() && current == EET::OutBrack))
					throw ERROR_THROW_C(0, "Не верное вырожение");

				if (operatorsStack.empty() || current == EET::InBrack) 
					operatorsStack.push(current);
				else if (current == EET::OutBrack) {
					FIND_CLOSE = true;

					while (operatorsStack.top() != EET::InBrack)
					{
						result.push_back(operatorsStack.top());

						operatorsStack.pop();

						if (operatorsStack.empty()) {
							FIND_CLOSE = false;
							break;
						}
					}

					// Ошибка если откр. скобка не была закрыта
					if (!FIND_CLOSE) 
						throw ERROR_THROW_C(0, "Не верное вырожение");

					operatorsStack.pop();
				}
				else {
					while (GetOperatorPriority(current) <= GetOperatorPriority(operatorsStack.top()))
					{
						// Ошибка если на этом этапе встретиться откр. или закр. скобка
						if (operatorsStack.top() == EET::InBrack || operatorsStack.top() == EET::OutBrack) 
							throw ERROR_THROW_C(0, "Не верное вырожение");

						result.push_back(operatorsStack.top());

						operatorsStack.pop();

						if (operatorsStack.empty()) 
							break;
					}

					operatorsStack.push(current);
				}
			}
			else {
				result.push_back(current);
				data.push_back(node->elementsData[dataIndex]);
				types.push_back(node->typeChain[dataIndex]);

				dataIndex++;
			}

			OPERATOR = false;

			index++;

		} while (index < node->elementChain.size());

		while (!operatorsStack.empty())
		{
			// Ошибка если на этом этапе встретиться откр. или закр. скобка
			if (operatorsStack.top() == EET::InBrack || operatorsStack.top() == EET::OutBrack)
				throw ERROR_THROW_C(0, "Не верное вырожение");

			result.push_back(operatorsStack.top());

			operatorsStack.pop();
		}

		node->elementChain = result;
		node->elementsData = data;
		node->typeChain = types;

		return node;
	}

	int PolandNatation::GetOperatorPriority(ExpressionElementType element) {
		if (element == EET::Const || element == EET::Var || element == EET::Func)
			return 0;
		else if (element == EET::InBrack || element == EET::OutBrack)
			return 1;
		else if (element == EET::Plus || element == EET::Minus ||
			element == EET::LOr || element == EET::LAnd)
			return 2;
		else
			return 3;
	}

	bool PolandNatation::TryCalculate(ExpressionNode* node) {
		return true;
	}
}