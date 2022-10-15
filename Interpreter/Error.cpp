#include "stdafx.h"

using namespace std;

namespace Error {
	string ErrorBase::ToString()
	{
		strstream result;

		result << "ID: " << id << endl << "MESSAGE: " << message << '\0';

		return result.str();
	}

	string LineError::ToString()
	{
		string base = ErrorBase::ToString();

		strstream result;

		result << endl << "Line index: " << lineIndex << ", Letter index: " << letterIndex << '\0';

		return base + result.str();
	}
}