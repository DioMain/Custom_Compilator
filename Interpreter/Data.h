#pragma once

#define PARSING_UNDEF_LEXEM_NAME "$$$"
#define PARSING_COMMAND_END_LEXEM Parsing::Lexem(Parsing::LexemType::RuleEnd, ";")
#define PARSING_VOID_LEXEM Parsing::Lexem(Parsing::LexemType::Void, "void")
#define PARSING_VAR_LEXEM Parsing::Lexem(Parsing::LexemType::Var, "Var")
#define PARSING_FUNC_LEXEM Parsing::Lexem(Parsing::LexemType::Function, "function")
#define PARSING_NAMESPACE_LEXEM Parsing::Lexem(Parsing::LexemType::Namespace, "namespace")

#define PARSING_VAR_UNINIT -1

namespace Parsing {
	enum class LexemType {
		Void, Var, VarType, Indefier, Literal, Equals, RuleEnd, Function,
		FuncIn, FuncOut, SpaceIn, SpaceOut, Namespace, And, Main, Return, IgnoreMain
	};

	enum class LinkType {
		Void, Var, Literal
	};

	enum class VarType
	{
		Void, String, Integer, Char
	};

	struct Literal
	{
		std::string data;

		Literal() : data("") { }
	};

	struct Var
	{
		VarType type;

		std::string indefier;
		std::string locationSpace;

		int literalIndex;

		Var() : type(VarType::Void), indefier(), literalIndex(PARSING_VAR_UNINIT) { }

		Var(VarType type) : type(type), indefier(), literalIndex(PARSING_VAR_UNINIT) { }
	};

	struct Func
	{
		Var retVar;

		std::vector<int> argsIndexes;

		std::string indefier;
		std::string locationSpace;

		Func() : retVar(VarType::Void), indefier() { }

		Func(VarType retType) : retVar(retType), indefier() { }
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

		std::vector<std::vector<Lexem*>> LexemsStable;
		std::vector<Literal*> RawLiterals;

		Lexem GetBasicLexem(std::string name);

		void Init();

	private:

	};
}