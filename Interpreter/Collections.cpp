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

		for (size_t i = 0; i < chain.size(); i++)
		{
			for (size_t j = 0; j < availableLexems.size(); j++)
			{
				if (chain.size() != availableLexems[j]->data.chain.size() || chain[i] != availableLexems[j]->data.chain[i]) {
					availableLexems.erase(availableLexems.begin() + j);
					j--;
				}
			}
		}

		if (availableLexems.size() < 1)
			return new Data::NoneLexem();

		return availableLexems.front();
	}
	Data::LexemData DefaultLexems::GetDataByChain(std::string chain)
	{
		Data::LexemData lexem = Data::NoneLexem().data;

		for (size_t i = 0; i < lexems.size(); i++)
		{
			if (chain == lexems[i]->data.chain) lexem = lexems[i]->data;
		}

		return lexem;
	}
	Data::LexemData DefaultLexems::GetDataByType(Data::LexemType type)
	{
		Data::LexemData lexem = Data::NoneLexem().data;

		for (size_t i = 0; i < lexems.size(); i++)
		{
			if (type == lexems[i]->data.type) lexem = lexems[i]->data;
		}

		return lexem;
	}

	DefaultRules::DefaultRules()
	{
		rules.push_back(new Data::VarCreateAndInit());
		rules.push_back(new Data::VarAssign());
		rules.push_back(new Data::VarCreate());
		rules.push_back(new Data::OpenSpace());
		rules.push_back(new Data::CloseSpace());
		rules.push_back(new Data::CreateNamespace());
		rules.push_back(new Data::FuncCreate());
		rules.push_back(new Data::FuncUse());
		rules.push_back(new Data::MainCreate());
		rules.push_back(new Data::ReturnRule());
	}
	Data::Rule* DefaultRules::ParsingChain(std::vector<Data::LexemData> chain)
	{
		std::vector<Data::Rule*> availableRules = rules;

		Data::Rule* intermediate = new Data::Rule();
		Data::Rule* result;

		for (size_t i = 0; i < chain.size(); i++) 
			intermediate->fullChain.push_back(chain[i].type);

		bool haveParams = false;
		bool params = false;
		bool HaveVarInit = false;
		bool OtherExpression = false;

		for (size_t i = 0; i < chain.size(); i++)
		{
			if (chain[i].type == Data::LexemType::ParamsIn) { 
				params = true; 
				haveParams = true; 
				intermediate->chain.push_back(chain[i].type);
				continue; 
			}
			else if (chain[i].type == Data::LexemType::ParamsOut) {
				if (HaveVarInit && OtherExpression)
					intermediate->chain.push_back(Data::LexemType::AnyParams);
				else if (HaveVarInit)
					intermediate->chain.push_back(Data::LexemType::VarInitParams);
				else
					intermediate->chain.push_back(Data::LexemType::ExpressionParams);

				params = false;
			}				

			if (params) {
				if (chain[i].type == Data::LexemType::And) continue;

				if (chain[i].type == Data::LexemType::VarType && chain[i + 1].type == Data::LexemType::Indefier) {
					intermediate->paramsChain.push_back(Data::LexemType::VarInitParams);
					HaveVarInit = true;
					i++;
				}
				else {
					intermediate->paramsChain.push_back(Data::LexemType::VarInitParams);
					OtherExpression = true;
				}
			}
			else intermediate->chain.push_back(chain[i].type);
		}

		for (size_t i = 0; i < intermediate->chain.size(); i++)
		{
			for (size_t j = 0; j < availableRules.size(); j++)
			{
				if (intermediate->chain.size() != availableRules[j]->chain.size() || intermediate->chain[i] != availableRules[j]->chain[i]) {
					availableRules.erase(availableRules.begin() + j);
					j--;
				}
			}
		}

		if (availableRules.size() < 1)
			return new Data::NoneRule();

		result = availableRules.front();

		result->initspace = chain[0].space;
		result->fullChain = intermediate->fullChain;
		result->paramsChain = intermediate->paramsChain;

		return result;
	}
	Data::Rule DefaultRules::GetByName(std::string name)
	{
		Data::Rule rule = Data::NoneRule();

		for (size_t i = 0; i < rules.size(); i++)
		{
			if (rules[i]->ruleName == name) rule = *rules[i];
		}
		
		return rule;
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

	Data::LexemData& LexemsTable::GetLast()
	{
		return Get(GetLinesCount() - 1, GetLineSize(GetLinesCount() - 1) - 1);
	}
	Data::LexemData& LexemsTable::Get(int line, int col)
	{
		return table[line][col];
	}

	bool IndefierColletion::IsExist(Data::IndefierData element)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i].data
				&& element.name == container[i].name
				&& element.initspace == container[i].initspace
				&& element.type == container[i].type
				&& element.isFunc == container[i].isFunc)
				return true;
		}

		return false;
	}
	bool IndefierColletion::IsExist(std::string name)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (name == container[i].name)
				return true;
		}

		return false;
	}
	int IndefierColletion::GetIndex(Data::IndefierData element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i].data
				&& element.name == container[i].name
				&& element.initspace == container[i].initspace
				&& element.isFunc == container[i].isFunc
				&& element.type == container[i].type)
				index = i;
		}

		return index;
	}
	Data::IndefierData& IndefierColletion::GetByName(std::string ind)
	{
		Data::IndefierData* item = nullptr;

		for (size_t i = 0; i < container.size(); i++)
			if (ind == container[i].name) item = &container[i];

		return *item;
	}

	bool RuleColletion::IsExist(Data::Rule element)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.chain == container[i].chain
				&& element.initspace == container[i].initspace
				&& element.ruleName == container[i].ruleName)
				return true;
		}

		return false;
	}
	int RuleColletion::GetIndex(Data::Rule element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.chain == container[i].chain
				&& element.initspace == container[i].initspace
				&& element.ruleName == container[i].ruleName)
				index = i;
		}

		return index;
	}
}