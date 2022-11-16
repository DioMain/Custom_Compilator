#pragma once

namespace Data {
	class NoneRule : public Rule {
	public:
		NoneRule() : Rule("None",
			{ LexemType::None }) { }
	};

	class VarDeclareRule : public Rule {
	public:

		VarDeclareRule() : Rule("VarDeclare", 
			{ LexemType::VarType, LexemType::Indefier, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class VarDeclareAndInitRule : public Rule {
	public:

		VarDeclareAndInitRule() : Rule("VarDeclareAndInit", 
			{ LexemType::VarType, LexemType::Indefier, LexemType::Equals, LexemType::Expression, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class VarAssignRule : public Rule {
	public:

		VarAssignRule() : Rule("VarAssign", 
			{ LexemType::Indefier, LexemType::Equals, LexemType::Expression, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class NamespaceDeclareRule : public Rule {
	public:

		NamespaceDeclareRule() : Rule("DeclareNamespace",
			{ LexemType::Namespace, LexemType::Indefier, LexemType::SpaceIn }) { }

		void Action() override;
	};

	class OpenSpaceRule : public Rule {
	public:

		OpenSpaceRule() : Rule("OpenSpace",
			{ LexemType::SpaceIn }) { }

		void Action() override;
	};
	class CloseSpaceRule : public Rule {
	public:

		CloseSpaceRule() : Rule("CloseSpace",
			{ LexemType::SpaceOut }) { }

		void Action() override;
	};

	class FuncDeclareRule : public Rule {
	public:

		FuncDeclareRule() : Rule("FuncDeclare",
			{ LexemType::VarType, LexemType::Indefier, LexemType::ParamsIn, LexemType::VarInitParams, LexemType::ParamsOut, LexemType::SpaceIn }) { }

		void Action() override;
	};
	class FuncUseRule : public Rule {
	public:

		FuncUseRule() : Rule("FuncUse",
			{ LexemType::Indefier, LexemType::ParamsIn, LexemType::ExpressionParams, LexemType::ParamsOut, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class MainDeclareRule : public Rule {
	public:

		MainDeclareRule() : Rule("MainDeclare",
			{ LexemType::Main, LexemType::SpaceIn }) { }

		void Action() override;
	};

	class ReturnRule : public Rule {
	public:

		ReturnRule() : Rule("Return",
			{ LexemType::Return, LexemType::Expression, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class IfRule : public Rule {
	public:
		IfRule() : Rule("If",
			{ LexemType::If, LexemType::ParamsIn, LexemType::ExpressionParams, LexemType::ParamsOut, LexemType::SpaceIn }) { }

		void Action() override;
	};
	class ElseIfRule : public Rule {
	public:
		ElseIfRule() : Rule("ElseIf",
			{ LexemType::Else, LexemType::If, LexemType::ParamsIn, LexemType::ExpressionParams, LexemType::ParamsOut, LexemType::SpaceIn }) { }

		void Action() override;
	};
	class ElseRule : public Rule {
	public:
		ElseRule() : Rule("Else",
			{ LexemType::Else, LexemType::SpaceIn }) { }

		void Action() override;
	};
}