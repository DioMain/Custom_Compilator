#pragma once

namespace Data {
	enum class VarType {
		Void, Int, Char, String, Bool
	};

	enum class IndefierType {
		Var, Func, Param
	};

	struct IndefierData
	{		
		// Common data
		std::string name;
		std::string initspace;

		IndefierType type;

		// For functions
		bool isFunc;
		// For functions
		std::vector<IndefierData*> params;		

		// For params
		IndefierData* belong;

		// Inner text data
		std::string data;

		VarType dataType;

		IndefierData() : name(""), type(IndefierType::Var), dataType(VarType::Void), initspace("GLOBAL"), isFunc(false), 
			data(""), belong(nullptr) { }

		IndefierData(std::string name, IndefierType type, VarType dataType, std::string initspace, bool isFunc = false)
			: name(name), type(type), dataType(dataType), initspace(initspace), isFunc(isFunc), data(""), belong(nullptr) { }
	};
}