#pragma once

#define PARSING_UNDEF_LEXEM_NAME "$$$"
#define PARSING_COMMAND_END_LEXEM Parsing::Lexem(Parsing::LexemType::RuleEnd, ";")
#define PARSING_VOID_LEXEM Parsing::Lexem(Parsing::LexemType::Void, "пусто")
#define PARSING_NAMESPACE_LEXEM Parsing::Lexem(Parsing::LexemType::Namespace, "пространство")

#define PARSING_VAR_UNINIT -1

namespace Parsing {
	enum class LexemType {
		Void, VarType, Indefier, Expression, Equals, RuleEnd, ParamsIn, ParamsOut, 
		SpaceIn, SpaceOut, Namespace, And, Main, Return, IgnoreMain, If, Else, 
		LogicExpression 
	};

	enum class LinkType {
		Void, Var, Literal
	};

	enum class VarType
	{
		Void, String, Integer, Char
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
		LinkType linkType;

		std::string name;
		std::string locationSpace;

		int linkIndex;

		Lexem() : type(LexemType::Void), linkType(LinkType::Void), name(), linkIndex(-1) { }

		Lexem(LexemType type, std::string name, LinkType linkType = LinkType::Void, int linkIndex = -1)
			: type(type), linkType(linkType), name(name), linkIndex(linkIndex) { }
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