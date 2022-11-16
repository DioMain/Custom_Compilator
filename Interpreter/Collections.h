#pragma once

namespace Collections {
	class DefaultLexems {
	public:

		DefaultLexems();

		Data::BasicLexem* ParsingChain(std::string chain);

		Data::LexemData GetDataByChain(std::string chain);
		Data::LexemData GetDataByType(Data::LexemType type);

	private:

		std::vector<Data::BasicLexem*> lexems;
	};

	class DefaultRules {
	public:

		DefaultRules();

		Data::Rule* ParsingChain(std::vector<Data::LexemData> chain);

		Data::Rule GetByName(std::string name);

	private:

		std::vector<Data::Rule*> rules;

	};

	template <typename T>
	class Collection {
	public:

		Collection() : container(std::vector<T*>()) { }

		virtual void Add(T element) {
			container.push_back(new T(element));
		}
		virtual void AddAt(T element, int index) {
			container.insert(container.begin() + index, new T(element));
		}
		
		virtual void Remove(T element) {
			if (!IsExist(element)) return;

			RemoveAt(GetIndex(element));
		}
		virtual void RemoveAt(int index) {
			container.erase(container.begin() + index);
		}

		T& Get(int index) {
			return *container[index];
		}
		T& GetLast() {
			return *container[container.size() - 1];
		}
		T* GetPointer(int index) {
			return container[index];
		}
		T* GetLastPointer() {
			return container[container.size() - 1];
		}

		int GetSize() {
			return container.size();
		}
		bool IsEmpty() {
			return container.empty();
		}

		virtual bool IsExist(T element) = 0;
		virtual int GetIndex(T element) = 0;

		T& operator[](int index) {
			return *container[index];
		}

	protected:

		std::vector<T*> container;
	};

	class LexemsTable {
	public:

		std::vector<std::vector<Data::LexemData>> table;

		LexemsTable() : table(std::vector<std::vector<Data::LexemData>>()) { NextLine(); }

		void Add(Data::LexemData element);
		void NextLine();

		int GetLineSize(int line);
		int GetLinesCount();

		Data::LexemData& GetLast();

		Data::LexemData& Get(int line, int col);
	};

	class LexemsColletion : public Collection<Data::LexemData> {
	public:
		bool IsExist(Data::LexemData element) override;

		int GetIndex(Data::LexemData element) override;
	};
	class LiteralsColletion : public Collection<Data::LiteralData> {
	public:
		bool IsExist(Data::LiteralData element) override;

		int GetIndex(Data::LiteralData element) override;
	};

	class IndefierColletion : public Collection<Data::IndefierData> {
	public:
		bool IsExist(Data::IndefierData element) override;
		bool IsExist(std::string name);

		int GetIndex(Data::IndefierData element) override;

		Data::IndefierData& GetByName(std::string ind);
	};
	class RuleColletion : public Collection<Data::Rule> {
	public:
		bool IsExist(Data::Rule element) override;

		int GetIndex(Data::Rule element) override;
	};
}