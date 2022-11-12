#pragma once

namespace Data {
	enum class VarType {
		Void, Int, Char, String, Bool
	};

	struct IndefierData
	{
		VarType type;

		bool isFunc;
		int paramsCount;

		std::string name;
		std::string initspace;

		std::string data;

		IndefierData() : name(""), type(VarType::Void), initspace("GLOBAL"), isFunc(false), data(""), paramsCount(0) { }

		IndefierData(std::string name, VarType type, std::string initspace, bool isFunc = false)
			: name(name), type(type), initspace(initspace), isFunc(isFunc), data(""), paramsCount(0) { }
	};
}