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
	class LiteralLexem : public BasicLexem {
	public:
		LiteralData litData;

		LiteralLexem(std::string data, LexemType type) : BasicLexem(LEXEM_CHAIN_UNDEFINE, type), litData(LiteralData(data)) { }

		void Action() override;
	};

	// Переменные

	class VoidLex : public VarLexem {
	public:
		VoidLex() : VarLexem("void") { }
	};
	class IntegerLex : public VarLexem {
	public:
		IntegerLex() : VarLexem("int") { }
	};
	class StringLex : public VarLexem {
	public:
		StringLex() : VarLexem("string") { }
	};
	class CharLex : public VarLexem {
	public:
		CharLex() : VarLexem("char") { }
	};
	class BooleanLex : public VarLexem {
	public:
		BooleanLex() : VarLexem("bool") { }
	};

	// Литералы

	class ExpressionLex : public LiteralLexem {
	public:
		ExpressionLex(std::string data) : LiteralLexem(data, LexemType::Expression) { }
	};
	class LogicExpressionLex : public LiteralLexem {
	public:
		LogicExpressionLex(std::string data) : LiteralLexem(data, LexemType::LogicExpression) { }
	};
	class IndefierLex : public LiteralLexem {
	public:
		IndefierLex(std::string data) : LiteralLexem(data, LexemType::Indefier) { }
	};

	// Скобки

	class SpaceInLex : public BasicLexem {
	public:

		SpaceInLex() : BasicLexem("{", LexemType::SpaceIn) { }

		void Action() override;
	};
	class SpaceOutLex : public BasicLexem {
	public:

		SpaceOutLex() : BasicLexem("}", LexemType::SpaceOut) { }

		void Action() override;
	};

	class ParamsInLex : public BasicLexem {
	public:

		ParamsInLex() : BasicLexem("(", LexemType::ParamsIn) { }

		void Action() override;
	};
	class ParamsOutLex : public BasicLexem {
	public:

		ParamsOutLex() : BasicLexem(")", LexemType::ParamsOut) { }

		void Action() override;
	};

	// Другое

	class EqualsLex : public BasicLexem {
	public:

		EqualsLex() : BasicLexem("=", LexemType::Equals) { }

		void Action() override;
	};

	class AndLex : public BasicLexem {
	public:

		AndLex() : BasicLexem(",", LexemType::And) { }

		void Action() override;
	};

	class RuleEndLex : public BasicLexem {
	public:

		RuleEndLex() : BasicLexem(";", LexemType::RuleEnd) { }

		void Action() override;
	};

	class MainLex : public BasicLexem {
	public:

		MainLex() : BasicLexem("Main", LexemType::Main) { }

		void Action() override;
	};

	class ReturnLex : public BasicLexem {
	public:

		ReturnLex() : BasicLexem("return", LexemType::Return) { }

		void Action() override;
	};

	class NamespaceLex : public BasicLexem {
	public:

		NamespaceLex() : BasicLexem("namespace", LexemType::Namespace) { }

		void Action() override;
	};

	class CommentLex : public BasicLexem {
	public:

		CommentLex() : BasicLexem("//", LexemType::Comment) { }

		void Action() override;
	};

	class IfLex : public BasicLexem {
	public:

		IfLex() : BasicLexem("if", LexemType::If) { }

		void Action() override;
	};
	class ElseLex : public BasicLexem {
	public:

		ElseLex() : BasicLexem("else", LexemType::Else) { }

		void Action() override;
	};

	class CodeEndLex : public BasicLexem {
	public:
		CodeEndLex() : BasicLexem("$", LexemType::CodeEnd) { }
	};
}
