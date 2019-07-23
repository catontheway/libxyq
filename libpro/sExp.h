#pragma once
#include "_inc.h"

#pragma pack (push)
#pragma pack (1)
// ¾­Ñé/½ðÇ®
union sExp
{
	u64 union64;
	struct  
	{
		u64 w : 49;
		u64 v : 15;
	};

	sExp();
	operator const u64()const
	{
		return w * 10000 + v;
	}

	bool add(int v, bool onlyCheck = false);

	static int getExp(int lv, bool pet);
};
#pragma pack(pop)

