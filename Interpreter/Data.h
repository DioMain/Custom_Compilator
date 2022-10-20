#pragma once

#define PARSING_UNDEF_LEXEM_NAME "$$$"
#define PARSING_COMMAND_END_LEXEM Parsing::Lexem(Parsing::LexemType::CommandEnd, ";")
#define PARSING_VOID_LEXEM Parsing::Lexem(Parsing::LexemType::Void, "void")
#define PARSING_VAR_LEXEM Parsing::Lexem(Parsing::LexemType::Var, "Var")

#define PARSING_VAR_UNINIT -1

namespace Parsing {
	enum class LexemType {
		Void, Declare, Var, VarType, Indefier, Literal, Poland, Equals, CommandEnd
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

		int literalIndex;

		Var() : type(VarType::Void), indefier(), literalIndex(PARSING_VAR_UNINIT) { }

		Var(std::string typeName);
	};

	struct Lexem {
		LexemType type;
		LinkType linkType;

		std::string name;

		int linkIndex;

		Lexem() : type(LexemType::Void), linkType(LinkType::Void), name(), linkIndex(-1) { }

		Lexem(LexemType type, std::string name, LinkType linkType = LinkType::Void, int linkIndex = -1)
			: type(type), linkType(linkType), name(name), linkIndex(linkIndex) { }
	};

	class DataContainer
	{
	public:

		std::vector<Lexem> BasicLexems;

		std::vector<Lexem*> Lexems;
		std::vector<Var*> Vars;
		std::vector<Literal*> Literals;

		Lexem GetBasicLexem(std::string name);

		Var* GetVar(std::string indifier);

		void Init();

	private:

	};
}