#pragma once
#include "_txtinc.h"

namespace ctt
{
	struct sShop
	{
		int type;
		int id;
		int price;
	};

	const map<int, vector<sShop>>& getShops();
}


