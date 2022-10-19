#pragma once

#define PARSING_UNDEF_LEXEM_NAME "$$$"

namespace Parsing {
	enum class LexemType {
		Void, Error, Var, VarType, Indefier, Literal, Poland, Equals, CommandEnd
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

		Literal() : data() { }
	};

	struct Var
	{
		VarType type;

		std::string name;

		int literalIndex;

		Var() : type(VarType::Void), name(), literalIndex(-1) { }
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

		void Init();

	private:

	};
}