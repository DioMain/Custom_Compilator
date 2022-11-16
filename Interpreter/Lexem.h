#pragma once

#define LEXEM_CHAIN_UNDEFINE "$$$"

namespace Data {
	enum class LexemType {
		// Обычные лексемы
		None, Void, VarType, Indefier, Expression, LogicExpression, Equals, RuleEnd, ParamsIn, DefLib,
		ParamsOut, SpaceIn, SpaceOut, Namespace, And, Main, Comment, Return, If, Else, CodeEnd,

		// Лексемы для правил
		AnyParams, VarInitParams, ExpressionParams
	};

	struct LexemData {
		LexemType type;

		std::string chain;
		std::string space;

		int line;

		LexemData(std::string chain, LexemType type) : chain(chain), type(type), line(0) { }
	};

	class BasicLexem {
	public:
		LexemData data;

		LexemAnalysis::LexemAnalyser* lexemAnalyzer;

		BasicLexem() : data(LexemData(LEXEM_CHAIN_UNDEFINE, LexemType::None)), lexemAnalyzer(nullptr) { }

		BasicLexem(std::string chain, LexemType type) : data(LexemData(chain, type)), lexemAnalyzer(nullptr) { }

		virtual void Action() { }
	};
}