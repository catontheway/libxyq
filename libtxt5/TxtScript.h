#pragma once
#include "_txtinc.h"

namespace ctt
{
	struct sEntry
	{
		int value;
		string str;
	};
	struct sScript
	{
		int id;
		vector<sEntry> entries;
	};

	const map<string, vector<sScript>>& getScripts();
}


