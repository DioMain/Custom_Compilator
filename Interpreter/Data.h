#pragma once

#define PARSING_UNDEF_LEXEM_NAME "$$$"
#define PARSING_COMMAND_END_LEXEM LexemAnalyzer::Lexem(LexemAnalyzer::LexemType::RuleEnd, ";")
#define PARSING_VOID_LEXEM LexemAnalyzer::Lexem(LexemAnalyzer::LexemType::Void, "void")
#define PARSING_NAMESPACE_LEXEM LexemAnalyzer::Lexem(LexemAnalyzer::LexemType::Namespace, "namespace")

namespace LexemAnalyzer {
	enum class LexemType {
		Void, VarType, Indefier, Expression, Equals, RuleEnd, ParamsIn, ParamsOut, 
		SpaceIn, SpaceOut, Namespace, And, Main, Comment, Return, If, Else, 
		LogicExpression 
	};

	enum class VarType
	{
		Void, String, Integer, Char, Bool
	};

	enum class ParamType {
		Expression, Indefier, VarCreation
	};

	struct Literal
	{
		std::string data;

		Literal() : data("") { }
	};

	struct Lexem {
		LexemType type;

		std::string name;
		std::string locationSpace;

		Lexem() : type(LexemType::Void), name() { }

		Lexem(LexemType type, std::string name) : type(type), name(name) { }
	};

	class DataContainer
	{
	public:

		std::vector<Lexem> BasicLexems;

		std::vector<std::vector<Lexem*>> LexemsTable;
		std::vector<Literal*> RawLiterals;

		Lexem GetBasicLexem(std::string name);

		void Init();

	private:

	};
}