#pragma once

namespace Data {

	enum class VarType {
		Void, Int, Char, String, Bool
	};

	struct Var {
		VarType type;

		std::string indefier;
		std::string initspace;
		std::string data;
	};
}