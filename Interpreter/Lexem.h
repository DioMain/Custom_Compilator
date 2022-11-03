#pragma once

#define LEXEM_CHAIN_UNDEFINE "$$$"

namespace Data {
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

		AltLexemAnalyzer::LexemAnalyzer* lexemAnalyzer;

		BasicLexem(std::string chain, LexemType type) : data(LexemData(chain, type)), lexemAnalyzer(nullptr) { }

		virtual void Action()  { }
	};
}