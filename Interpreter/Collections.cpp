#include "stdafx.h"

using namespace std;

namespace Collections {
	DefaultLexems::DefaultLexems()
	{
		lexems.push_back(new Data::VoidLex());
		lexems.push_back(new Data::IntegerLex());
		lexems.push_back(new Data::StringLex());
		lexems.push_back(new Data::CharLex());
		lexems.push_back(new Data::BooleanLex());

		lexems.push_back(new Data::AndLex());
		lexems.push_back(new Data::EqualsLex());

		lexems.push_back(new Data::ParamsInLex());
		lexems.push_back(new Data::ParamsOutLex());
		lexems.push_back(new Data::SpaceInLex());
		lexems.push_back(new Data::SpaceOutLex());

		lexems.push_back(new Data::MainLex());
		lexems.push_back(new Data::ReturnLex());
		lexems.push_back(new Data::NamespaceLex());

		lexems.push_back(new Data::RuleEndLex());

		lexems.push_back(new Data::CommentLex());

		lexems.push_back(new Data::IfLex());
		lexems.push_back(new Data::ElseLex());
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
		rules.push_back(new Data::VarDeclareAndInitRule());
		rules.push_back(new Data::VarAssignRule());
		rules.push_back(new Data::VarDeclareRule());
		rules.push_back(new Data::OpenSpaceRule());
		rules.push_back(new Data::CloseSpaceRule());
		rules.push_back(new Data::NamespaceDeclareRule());
		rules.push_back(new Data::FuncDeclareRule());
		rules.push_back(new Data::FuncDecNonParamsRule());
		rules.push_back(new Data::FuncUseRule());
		rules.push_back(new Data::MainDeclareRule());
		rules.push_back(new Data::ReturnRule());
		rules.push_back(new Data::IfRule());
		rules.push_back(new Data::ElseIfRule());
		rules.push_back(new Data::ElseRule());
		rules.push_back(new Data::CommentRule());
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

		// Debag
		bool debag = true;		// d

		string deChain0 = "$";	// d
		string deChain1 = "$";	// d

		if (debag)
			for (size_t i = 0; i < chain.size(); i++)
				deChain0.insert(deChain0.end() - 1, chain[i].chain[0]); // d

		if (debag)
			cout << setw(25) << left << "RYLE FIND" << setw(30) << left << deChain0 << setw(20) << left << deChain1 << endl; // d

		for (size_t i = 0; i < chain.size(); i++)
		{
			if (chain[i].type == Data::LexemType::ParamsIn) { 
				params = true; 
				haveParams = true; 
				intermediate->commonChain.push_back(chain[i].type);
				if (debag) {
					deChain1.insert(deChain1.end() - 1, chain[i].chain[0]); // d
					deChain0.erase(deChain0.begin()); // d
				}
				
				continue; 
			}
			else if (chain[i].type == Data::LexemType::ParamsOut) {
				if (HaveVarInit && OtherExpression) {
					intermediate->commonChain.push_back(Data::LexemType::AnyParams);
					if (debag) {
						deChain1.insert(deChain1.end() - 1, 'A'); // d
						deChain1.insert(deChain1.end() - 1, 'P'); // d

						deChain0.erase(deChain0.begin());	// d
					}
				}
				else if (HaveVarInit) {
					intermediate->commonChain.push_back(Data::LexemType::VarInitParams);

					if (debag) {
						deChain1.insert(deChain1.end() - 1, 'V'); // d
						deChain1.insert(deChain1.end() - 1, 'I'); // d
						deChain1.insert(deChain1.end() - 1, 'P'); // d

						deChain0.erase(deChain0.begin()); // d
						deChain0.erase(deChain0.begin()); // d
					}
				}
				else if (OtherExpression) {
					intermediate->commonChain.push_back(Data::LexemType::ExpressionParams);

					if (debag) {
						deChain1.insert(deChain1.end() - 1, 'E'); // d
						deChain1.insert(deChain1.end() - 1, 'P'); // d

						deChain0.erase(deChain0.begin()); // d
					}
				}					
				else {
					intermediate->commonChain.push_back(Data::LexemType::NoneParams);

					if (debag) {
						deChain1.insert(deChain1.end() - 1, 'N'); // d
						deChain1.insert(deChain1.end() - 1, 'P'); // d

						deChain0.erase(deChain0.begin());	// d
					}
				}


				params = false;
			}				

			if (params) {
				if (chain[i].type == Data::LexemType::And) { 					
					continue; 
				}

				if (chain[i].type == Data::LexemType::VarType && chain[i + 1].type == Data::LexemType::Indefier) {
					intermediate->paramsChain.push_back(Data::LexemType::VarInitParams);
					HaveVarInit = true;
					i++;
				}
				else {
					intermediate->paramsChain.push_back(Data::LexemType::VarInitParams);
					OtherExpression = true;
				}

				if (debag) deChain0.erase(deChain0.begin());	// d
			}
			else { 
				intermediate->commonChain.push_back(chain[i].type); 

				if (debag) {
					deChain1.insert(deChain1.end() - 1, chain[i].chain[0]); // d
					deChain0.erase(deChain0.begin());		// d
				}
			}

			if (debag) cout << setw(25) << left << "" << setw(30) << left << deChain0 << setw(20) << left << deChain1 << endl; // d
		}

		for (size_t i = 0; i < intermediate->commonChain.size(); i++)
		{
			for (size_t j = 0; j < availableRules.size(); j++)
			{
				if (intermediate->commonChain.size() != availableRules[j]->commonChain.size() || 
					intermediate->commonChain[i] != availableRules[j]->commonChain[i]) {

					availableRules.erase(availableRules.begin() + j);
					j--;
				}
			}
		}

		if (availableRules.size() < 1)
			return new Data::NoneRule();	

		result = availableRules.front();

		if (debag) cout << setw(25) << left << "RULE IS FIND" << setw(30) << left << "-------" << setw(20) << left << "-------" << endl; // ds

		if (debag) cout << setw(25) << left << result->name << setw(30) << left << deChain1 << setw(20) << left << "$" << endl; // d	

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
			if (rules[i]->name == name) rule = *rules[i];
		}
		
		return rule;
	}

	bool LexemsColletion::IsExist(Data::LexemData element) {
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.chain == container[i]->chain
				&& element.space == container[i]->space
				&& element.type == container[i]->type)
				return true;
		}

		return false;
	}
	int LexemsColletion::GetIndex(Data::LexemData element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.chain == container[i]->chain
				&& element.space == container[i]->space
				&& element.type == container[i]->type)
				index = i;
		}

		return index;
	}

	bool LiteralsColletion::IsExist(Data::LiteralData element)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i]->data)
				return true;
		}

		return false;
	}
	int LiteralsColletion::GetIndex(Data::LiteralData element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i]->data)
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
			if (element.data == container[i]->data
				&& element.name == container[i]->name
				&& element.initspace == container[i]->initspace
				&& element.dataType == container[i]->dataType
				&& element.isFunc == container[i]->isFunc)
				return true;
		}

		return false;
	}
	bool IndefierColletion::IsExist(std::string name)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (name == container[i]->name)
				return true;
		}

		return false;
	}
	int IndefierColletion::GetIndex(Data::IndefierData element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.data == container[i]->data
				&& element.name == container[i]->name
				&& element.initspace == container[i]->initspace
				&& element.isFunc == container[i]->isFunc
				&& element.dataType == container[i]->dataType)
				index = i;
		}

		return index;
	}
	Data::IndefierData& IndefierColletion::GetByName(std::string ind)
	{
		Data::IndefierData* item = nullptr;

		for (size_t i = 0; i < container.size(); i++)
			if (ind == container[i]->name) item = container[i];

		return *item;
	}

	bool RuleColletion::IsExist(Data::Rule element)
	{
		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.commonChain == container[i]->commonChain
				&& element.initspace == container[i]->initspace
				&& element.name == container[i]->name)
				return true;
		}

		return false;
	}
	int RuleColletion::GetIndex(Data::Rule element)
	{
		int index = -1;

		for (size_t i = 0; i < container.size(); i++)
		{
			if (element.commonChain == container[i]->commonChain
				&& element.initspace == container[i]->initspace
				&& element.name == container[i]->name)
				index = i;
		}

		return index;
	}
}