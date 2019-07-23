#pragma once
#include "TxtItem.h"

namespace ctt
{
	struct sJiaju
	{
		eItem type;
		int id;
		ulong small;
		ulong big;
		std::string name;
		std::string desc;
		std::vector<ulong> uids;
	};

	const vector<sJiaju>& getJiajus();


	inline vector<ulong> getWdfFromTxtJiajus()
	{
		auto js = getJiajus();
		set<ulong> us;
		for (const auto& j : js)
		{
			us.insert(j.small);
			us.insert(j.big);
			for (const auto& u : j.uids)
			{
				us.insert(u);
			}
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}