#pragma once

namespace poland {

	static class PolandNatation
	{
	public:

		static void TranslateRecursive(std::vector<Data::ExpressionNode*> NodeVec);

		static Data::ExpressionNode* Translate(Data::ExpressionNode* node);

		static int GetOperatorPriority(Data::ExpressionElementType element);

		static bool TryCalculate(Data::ExpressionNode* node);
	};
}
