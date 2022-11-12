#pragma once

namespace Data {
	class NoneRule : public Rule {
	public:
		NoneRule() : Rule("None",
			{ LexemType::None }) { }
	};

	class VarCreate : public Rule {
	public:

		VarCreate() : Rule("VarCreate", 
			{ LexemType::VarType, LexemType::Indefier, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class VarCreateAndInit : public Rule {
	public:

		VarCreateAndInit() : Rule("VarCreateAndInit", 
			{ LexemType::VarType, LexemType::Indefier, LexemType::Equals, LexemType::Expression, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class VarAssign : public Rule {
	public:

		VarAssign() : Rule("VarAssign", 
			{ LexemType::Indefier, LexemType::Equals, LexemType::Expression, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class CreateNamespace : public Rule {
	public:

		CreateNamespace() : Rule("CreateNamespace",
			{ LexemType::Namespace, LexemType::Indefier, LexemType::SpaceIn }) { }

		void Action() override;
	};

	class OpenSpace : public Rule {
	public:

		OpenSpace() : Rule("OpenSpace",
			{ LexemType::SpaceIn }) { }

		void Action() override;
	};
	class CloseSpace : public Rule {
	public:

		CloseSpace() : Rule("CloseSpace",
			{ LexemType::SpaceOut }) { }

		void Action() override;
	};

	class FuncCreate : public Rule {
	public:

		FuncCreate() : Rule("FuncCreate",
			{ LexemType::VarType, LexemType::Indefier, LexemType::ParamsIn, LexemType::VarInitParams, LexemType::ParamsOut, LexemType::SpaceIn }) { }

		void Action() override;
	};
	class FuncUse : public Rule {
	public:

		FuncUse() : Rule("FuncUse",
			{ LexemType::Indefier, LexemType::ParamsIn, LexemType::ExpressionParams, LexemType::ParamsOut, LexemType::RuleEnd }) { }

		void Action() override;
	};

	class MainCreate : public Rule {
	public:

		MainCreate() : Rule("MainCreate",
			{ LexemType::Main, LexemType::SpaceIn }) { }

		void Action() override;
	};

	class ReturnRule : public Rule {
	public:

		ReturnRule() : Rule("Return",
			{ LexemType::Return, LexemType::Expression, LexemType::RuleEnd }) { }

		void Action() override;
	};
}