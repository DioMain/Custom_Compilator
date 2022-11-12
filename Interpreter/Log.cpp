#include "stdafx.h"

using namespace std;

namespace Log {
	Logging::Logging(wchar_t* path) {
		stream = new ofstream(path);

		if (!stream->is_open()) throw ERROR_THROW(112);
	}

	void Logging::WriteLine(const char* str ...) {
		if (stream == nullptr || !stream->is_open()) return;

		char* nowstr = nullptr;

		int n = 0;
		do
		{
			nowstr = (char*)(*(&str + n));

			*stream << nowstr;

			n++;

		} while (strlen(nowstr) != 0);
	}
	void Logging::WriteLine(const wchar_t* str ...) {
		if (stream == nullptr || !stream->is_open()) return;

		char* nowstr = nullptr;

		int n = 0;
		do
		{
			size_t len = wcslen(*(&str + n)) + 1;
			nowstr = new char[len];

			wcstombs_s(0, nowstr, len, *(&str + n), len - 1);	// Переобразование wchar_t в char

			*stream << nowstr;

			n++;

		} while (strlen(nowstr) != 0);
	}

	void Logging::WriteHeader() {
		if (stream == nullptr || !stream->is_open()) return;

		time_t rltime = time(0);		// Получение текучщей даты и времени

		tm* fdtm = new tm();			// Выделение пямяти под форматированное время

		localtime_s(fdtm, &rltime);		// Преобразование в форматированное время

		char* buf = new char[200];		// Буффер

		strftime(buf, 200, " Дата создания протокола: %c", fdtm);	// Заполнение буффера текущем временем

		*stream << "<------------------ Протокол ------------------>" << endl;
		*stream << buf << endl;
	}

	void Logging::WriteParm(Parm::ParmAnalyzer parm) {
		if (stream == nullptr || !stream->is_open()) return;

		char* nowstr = new char[PARM_MAX_SIZE];

		*stream << "<------------- Входные параметры -------------->" << endl;

		wcstombs_s(0, nowstr, PARM_MAX_SIZE, parm.InPath, PARM_MAX_SIZE);
		*stream << " -in: " << nowstr << endl;

		wcstombs_s(0, nowstr, PARM_MAX_SIZE, parm.OutPath, PARM_MAX_SIZE);
		*stream << " -out: " << nowstr << endl;

		wcstombs_s(0, nowstr, PARM_MAX_SIZE, parm.LogPath, PARM_MAX_SIZE);
		*stream << " -log: " << nowstr << endl;
	}

	void Logging::WriteLexemAnalysisResult(Collections::LexemsTable table, 
										Collections::LiteralsColletion lits) {
		if (stream == nullptr || !stream->is_open()) return;

		*stream << endl;

		*stream << "--------------------------------------------------------" << endl;
		*stream << "			Таблица лексем | Table of lexems" << endl;
		*stream << "<------------[ТИП|ЦЕПОЧКА|ПРОСТРАНСТВО ИМЁН]----------->" << endl;
		*stream << "--------------------------------------------------------" << endl;

		for (size_t i = 0; i < table.GetLinesCount(); i++)
		{
			*stream << "|" << i << "| ";
			for (size_t j = 0; j < table.GetLineSize(i); j++)
			{
				*stream << "[" << (int)table.Get(i, j).type
					<< "|" << table.Get(i, j).chain
					<< "|" << table.Get(i, j).space << "] " ;
			}
			*stream << endl ;
		}
		

		*stream << "--------------------------------------------------------" << endl;
		*stream << "		   Список литералов | Literals list" << endl;
		*stream << "#----Данные---------------------------------------------" << endl;
		*stream << "--------------------------------------------------------" << endl;

		for (int i = 0; i < lits.GetSize(); i++)
		{
			*stream << "|" << i << "| " << lits[i].data << endl;
		}
	}

	void Logging::WriteSyntaxAnalysisResult(Collections::RuleColletion resultRules, 
										Collections::IndefierColletion indefiers, 
										Collections::DefaultLexems defLexems) {

		if (stream == nullptr || !stream->is_open()) return;

		*stream << endl;

		*stream << "----------------------------------------------------------------" << endl;
		*stream << "			       Список правил | Rule list" << endl;
		*stream << "<----------------[ИМЯ|ПРОСТРАНСТВО ИМЁН|ЦЕПОЧКА]--------------->" << endl;
		*stream << "----------------------------------------------------------------" << endl;

		for (size_t i = 0; i < resultRules.GetSize(); i++)
		{
			*stream << "|" << i << "| " << left;
			*stream << setw(16) << resultRules[i].ruleName << left << " | "
				<< setw(16) << resultRules[i].initspace  << left << " | [";
			
			for (size_t j = 0; j < resultRules[i].fullChain.size(); j++)
			{
				switch (resultRules[i].fullChain[j])
				{
				case Data::LexemType::Expression:
					*stream << setw(2) << "EX" << left;
					break;
				case Data::LexemType::Indefier:
					*stream << setw(2) << "ID" << left;
					break;
				case Data::LexemType::LogicExpression:
					*stream << setw(2) << "LG" << left;
					break;
				case Data::LexemType::VarType:
					*stream << setw(2) << "VT" << left;
					break;
				default:
					*stream << setw(1) << defLexems.GetDataByType(resultRules[i].fullChain[j]).chain[0] << left;
					break;
				}

				if (j + 1 != resultRules[i].fullChain.size())
					*stream << '|';
			}

			*stream << ']' << endl;
		}

		*stream << endl;

		*stream << "-----------------------------------------------------------------" << endl;
		*stream << "			Список индификаторов | Indefiers list" << endl;
		*stream << "<-[ИМЯ|ТИП|ПРОСТРАНСTВО ИМЁН|ФУНКЦИЯ?|КОЛ-ВО ПАРАМ.|ИНФОРМАЦИЯ]->" << endl;
		*stream << "-----------------------------------------------------------------" << endl;

		for (size_t i = 0; i < indefiers.GetSize(); i++)
		{
			*stream << "|" << i << "| ";
			*stream << setw(12) << left << indefiers[i].name << " | "
				<< setw(1) << left << (int)indefiers[i].type  << " | "
				<< setw(12) << left << indefiers[i].initspace << " | "
				<< setw(5) << left << (indefiers[i].isFunc ? "TRUE" : "FALSE")  << " | ";

			if (indefiers[i].isFunc) *stream << setw(3) << left << indefiers[i].paramsCount << " | ";
			else *stream << setw(3) << left << "$$$" << " | ";

			*stream << setw(20) << left << (indefiers[i].data.size() != 0 ? indefiers[i].data : "$");

			*stream << endl;
		}
	}

	void Logging::WriteIn(In::InFile in) {
		if (stream == nullptr || !stream->is_open()) return;

		*stream << "<-------------- Исходные данные --------------->" << endl;

		*stream << " Кол-во символов: " << in.SizeOfCode << endl;
		*stream << " Кол-во строк: " << in.LinesCount << endl;
		*stream << " Проигнорировано: " << in.IgnoreCount << endl;
	}

	void Logging::WriteError(Error::ErrorBase* error) {
		if (stream == nullptr || !stream->is_open()) return;

		*stream << endl;

		*stream << "<------------- Информация об ошибке -------------->" << endl;

		*stream << error->ToString() << endl;
	}

	void Logging::Close() {
		if (stream != nullptr && stream->is_open()) stream->close();
	}
}