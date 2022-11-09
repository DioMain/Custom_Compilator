#pragma once

namespace Data {
	struct Func
	{
		VarType retType;
		
		std::string initspace;

		std::vector<Var*> params;
	};
}