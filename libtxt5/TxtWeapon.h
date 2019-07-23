#pragma once
#include "TxtItem.h"
#include "TxtModelRole.h"


namespace ctt
{
	struct sWeapon
	{
		eItem e;
		struct sRoleAct
		{
			eModel role;
			int actionsIndex;
			sAction action;
			eModel role2;
			int actionsIndex2;
			sAction action2;

		};

		std::vector<sRoleAct> actions;

	};


	const vector<sWeapon>& getWeapons();

	const vector<ulong>& getWeapon¸«îá»¢×ÓËÀÍös();

	inline vector<ulong> getWdfFromTxtWeapons()
	{
		auto ws = getWeapons();
		set<ulong> us;
		for (const auto& w : ws)
		{
			for (const auto& a : w.actions)
			{
				us.insert(a.action.stand);
				us.insert(a.action.walk);
				us.insert(a.action.await);
				us.insert(a.action.go);
				us.insert(a.action.atk);
				us.insert(a.action.atk2);
				us.insert(a.action.maigc);
				us.insert(a.action.def);
				us.insert(a.action.atkd);
				us.insert(a.action.dead);
				us.insert(a.action.back);

				us.insert(a.action2.stand);
				us.insert(a.action2.walk);
				us.insert(a.action2.await);
				us.insert(a.action2.go);
				us.insert(a.action2.atk);
				us.insert(a.action2.atk2);
				us.insert(a.action2.maigc);
				us.insert(a.action2.def);
				us.insert(a.action2.atkd);
				us.insert(a.action2.dead);
				us.insert(a.action2.back);
			}

		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}