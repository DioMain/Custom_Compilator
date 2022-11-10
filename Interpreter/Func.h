#pragma once

namespace Data {
	struct Func
	{
		VarType retType;
		
		std::string indefier;
		std::string initspace;

		std::vector<Var*> params;
	};
}