#pragma once

namespace Lexem {
	enum class LexemType {
		Void, VarType, Indefier, Expression, LogicExpression, Equals, RuleEnd, ParamsIn, ParamsOut,
		SpaceIn, SpaceOut, Namespace, And, Main, Comment, Return, If, Else
	};

	struct LexemData {
		LexemType type;

		std::string chain;
		std::string space;

		LexemData(std::string chain, LexemType type) : chain(chain), type(type) { }
	};

	class BasicLexem {
	public:
		LexemData data;

		BasicLexem(std::string chain, LexemType type) : data(LexemData(chain, type)) { }

		virtual void Action() = 0;
	};
}