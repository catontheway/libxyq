#pragma once
#include "_global.h"

class cFullMagic
{
public:
	bool SetMagicUp(int dataid, ulong id, int x, int y);
	vector<cWasFile> m_FullSkilUP;
	vector<cWasFile> m_SufferMagic;
	cFullMagic();
};