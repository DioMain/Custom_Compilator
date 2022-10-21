
template <typename T>
bool ExistElementInVector(std::vector<T> vec, T el) {
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == T) return true;
	}

	return false;
}

Parsing::VarType GetVarTypeByName(std::string typeName);