#pragma once
#include "_global.h"

class cZuoQi
{
public:
	bool GetZuoQi(int charID, int ZuoQiID);
	bool GetZuoQi(cPcData& pcData, int ZuoQiID);
	bool Init(string Path);
	array<sZuoQi, 145> m_ZuoQi;
	void GetShiPei(vector<int>& list, int pcData);
};