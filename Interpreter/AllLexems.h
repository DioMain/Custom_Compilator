#pragma once

namespace Lexem {
	class VarType : public BasicLexem {
	public:
		VarType(std::string chain) : BasicLexem(chain, LexemType::VarType) { }

		void Action() override;
	};

	// All vars

	class Void : public VarType {
	public:
		Void() : VarType("void") { }
	};
	class Integer : public VarType {
	public:
		Integer() : VarType("int") { }
	};
	class SString : public VarType {
	public:
		SString() : VarType("string") { }
	};
	class Char : public VarType {
	public:
		Char() : VarType("char") { }
	};
	class Boolean : public VarType {
	public:
		Boolean() : VarType("bool") { }
	};
}
