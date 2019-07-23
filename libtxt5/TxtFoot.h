#pragma once
#include "_txtinc.h"

namespace ctt
{
	struct sHeadTop
	{
		ulong uid;
		bool isMid;
	};
	const vector<sHeadTop>& getHeadTops();
	const vector<ulong>& getFoots();
	const vector<ulong>& getFoot2s();
	const map<ulong, ulong>& getColors();
}


