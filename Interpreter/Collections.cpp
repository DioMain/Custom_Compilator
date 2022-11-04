#include "stdafx.h"

namespace Collections {
	DefaultLexems::DefaultLexems()
	{
		lexems.push_back(new Data::Void());
		lexems.push_back(new Data::Integer());
		lexems.push_back(new Data::SString());
		lexems.push_back(new Data::Char());
		lexems.push_back(new Data::Boolean());

		lexems.push_back(new Data::And());
		lexems.push_back(new Data::Equals());

		lexems.push_back(new Data::ParamsIn());
		lexems.push_back(new Data::ParamsOut());
		lexems.push_back(new Data::SpaceIn());
		lexems.push_back(new Data::SpaceOut());

		lexems.push_back(new Data::Main());
		lexems.push_back(new Data::Return());
		lexems.push_back(new Data::Namespace());

		lexems.push_back(new Data::RuleEnd());

		lexems.push_back(new Data::Comment());

		lexems.push_back(new Data::If());
		lexems.push_back(new Data::Else());
	}
	Data::BasicLexem* DefaultLexems::ParsingChain(std::string chain)
	{
		std::vector<Data::BasicLexem*> availableLexems = lexems;

		for (int i = 0; i < chain.size(); i++)
		{
			for (int j = 0; j < availableLexems.size(); j++)
			{
				if (chain[i] != availableLexems[j]->data.chain[i]) {
					availableLexems.erase(availableLexems.begin() + j);
					j--;
				}
			}
		}

		if (availableLexems.size() != 1 || availableLexems[0]->data.chain.size() != chain.size())
			return new Data::NoneLexem(); // Здесь должна бать ошибка

		return availableLexems.front();
	}

	bool LexemsColletion::IsExist(Data::LexemData element) {
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.chain == container[i].chain
				&& element.space == container[i].space
				&& element.type == container[i].type)
				return true;
		}

		return false;
	}
	int LexemsColletion::GetIndex(Data::LexemData element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.chain == container[i].chain
				&& element.space == container[i].space
				&& element.type == container[i].type)
				index = i;
		}

		return index;
	}

	bool LiteralsColletion::IsExist(Data::LiteralData element)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i].data)
				return true;
		}

		return false;
	}
	int LiteralsColletion::GetIndex(Data::LiteralData element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i].data)
				index = i;
		}

		return index;
	}

	void LexemsTable::Add(Data::LexemData element)
	{
		table[table.size() - 1].push_back(element);
	}
	void LexemsTable::NextLine()
	{
		table.push_back(std::vector<Data::LexemData>());
	}
	int LexemsTable::GetLineSize(int line)
	{
		return table[line].size();
	}
	int LexemsTable::GetLinesCount()
	{
		return table.size();
	}
	Data::LexemData LexemsTable::Get(int line, int col)
	{
		return table[line][col];
	}
}