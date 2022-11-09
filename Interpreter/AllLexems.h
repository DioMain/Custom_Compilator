#pragma once

namespace Data {
	
	class NoneLexem : public BasicLexem {
	public:
		NoneLexem() : BasicLexem(LEXEM_CHAIN_UNDEFINE, LexemType::None) { }
	};

	// Наследуемые

	class VarLexem : public BasicLexem {
	public:
		VarLexem(std::string chain) : BasicLexem(chain, LexemType::VarType) { }

		void Action() override;
	};
	class Literal : public BasicLexem {
	public:
		LiteralData litData;

		Literal(std::string data, LexemType type) : BasicLexem(LEXEM_CHAIN_UNDEFINE, type), litData(LiteralData(data)) { }

		void Action() override;
	};

	// Переменные

	class Void : public VarLexem {
	public:
		Void() : VarLexem("void") { }
	};
	class Integer : public VarLexem {
	public:
		Integer() : VarLexem("int") { }
	};
	class SString : public VarLexem {
	public:
		SString() : VarLexem("string") { }
	};
	class Char : public VarLexem {
	public:
		Char() : VarLexem("char") { }
	};
	class Boolean : public VarLexem {
	public:
		Boolean() : VarLexem("bool") { }
	};

	// Литералы

	class Expression : public Literal {
	public:
		Expression(std::string data) : Literal(data, LexemType::Expression) { }
	};
	class LogicExpression : public Literal {
	public:
		LogicExpression(std::string data) : Literal(data, LexemType::LogicExpression) { }
	};
	class Indefier : public Literal {
	public:
		Indefier(std::string data) : Literal(data, LexemType::Indefier) { }
	};

	// Скобки

	class SpaceIn : public BasicLexem {
	public:

		SpaceIn() : BasicLexem("{", LexemType::SpaceIn) { }

		void Action() override;
	};
	class SpaceOut : public BasicLexem {
	public:

		SpaceOut() : BasicLexem("}", LexemType::SpaceOut) { }

		void Action() override;
	};

	class ParamsIn : public BasicLexem {
	public:

		ParamsIn() : BasicLexem("(", LexemType::ParamsIn) { }

		void Action() override;
	};
	class ParamsOut : public BasicLexem {
	public:

		ParamsOut() : BasicLexem(")", LexemType::ParamsOut) { }

		void Action() override;
	};

	// Другое

	class Equals : public BasicLexem {
	public:

		Equals() : BasicLexem("=", LexemType::Equals) { }

		void Action() override;
	};

	class And : public BasicLexem {
	public:

		And() : BasicLexem(",", LexemType::And) { }

		void Action() override;
	};

	class RuleEnd : public BasicLexem {
	public:

		RuleEnd() : BasicLexem(";", LexemType::RuleEnd) { }

		void Action() override;
	};

	class Main : public BasicLexem {
	public:

		Main() : BasicLexem("Main", LexemType::Main) { }

		void Action() override;
	};

	class Return : public BasicLexem {
	public:

		Return() : BasicLexem("return", LexemType::Return) { }

		void Action() override;
	};

	class Namespace : public BasicLexem {
	public:

		Namespace() : BasicLexem("namespace", LexemType::Namespace) { }

		void Action() override;
	};

	class Comment : public BasicLexem {
	public:

		Comment() : BasicLexem("//", LexemType::Comment) { }

		void Action() override;
	};

	class If : public BasicLexem {
	public:

		If() : BasicLexem("if", LexemType::If) { }

		void Action() override;
	};
	class Else : public BasicLexem {
	public:

		Else() : BasicLexem("else", LexemType::Else) { }

		void Action() override;
	};
}
