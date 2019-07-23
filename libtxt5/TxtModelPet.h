#pragma once
#include "TxtModelRole.h"

namespace ctt
{
	struct sPet
	{
		ulong small;
		ulong big;
		ulong dialog;
		ulong small2;
		ulong big2;
		ulong dialog2;
		eModel e;
		std::string name;
		sSound sound1;
		sSound sound2;
		struct sPoint
		{
			int offx;
			int atk1;
			int atk2;
			int atk3;
			int atk4;
			int magic;
		};
		sPoint point1;
		sPoint point2;
		std::vector<std::vector<int>> parts;
		struct sColorAct
		{
			ulong color;
			sAction action;
		};
		std::vector<sColorAct> actions;

	};


	const vector<sPet>& getPets();


	inline vector<ulong> getWdfFromTxtModelPetWithoutSounds()
	{
		auto pets = getPets();
		set<ulong> us;
		for (const auto& p : pets)
		{
			if (p.e == eModel::”ÒÕ√yt)
			{
				continue;
			}
			us.insert(p.small);
			us.insert(p.big);
			us.insert(p.dialog);
			us.insert(p.small2);
			us.insert(p.big2);
			us.insert(p.dialog2);

// 			us.insert(p.sound1.atk);
// 			us.insert(p.sound1.atk2);
// 			us.insert(p.sound1.atkd);
// 			us.insert(p.sound1.magic);
// 			us.insert(p.sound1.def);
// 			us.insert(p.sound1.dead);
// 			
// 			us.insert(p.sound2.atk);
// 			us.insert(p.sound2.atk2);
// 			us.insert(p.sound2.atkd);
// 			us.insert(p.sound2.magic);
// 			us.insert(p.sound2.def);
// 			us.insert(p.sound2.dead);

			if (p.e == eModel::Úø”»cy)
			{
				us.insert(p.actions[1].action.stand);
				us.insert(p.actions[1].action.walk);
				us.insert(p.actions[1].action.await);
				us.insert(p.actions[1].action.go);
				us.insert(p.actions[1].action.atk);
				us.insert(p.actions[1].action.atk2);
				us.insert(p.actions[1].action.maigc);
				us.insert(p.actions[1].action.def);
				us.insert(p.actions[1].action.atkd);
				us.insert(p.actions[1].action.dead);
				us.insert(p.actions[1].action.back);
			}
			else
			{
				for (const auto& a : p.actions)
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
				}
			}


		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}


	inline vector<ulong> getWdfFromTxtModelPetSounds()
	{
		auto pets = getPets();
		set<ulong> us;
		for (const auto& p : pets)
		{
			if (p.e == eModel::”ÒÕ√yt)
			{
				continue;
			}

			us.insert(p.sound1.atk);
			us.insert(p.sound1.atk2);
			us.insert(p.sound1.atkd);
			us.insert(p.sound1.magic);
			us.insert(p.sound1.def);
			us.insert(p.sound1.dead);

			us.insert(p.sound2.atk);
			us.insert(p.sound2.atk2);
			us.insert(p.sound2.atkd);
			us.insert(p.sound2.magic);
			us.insert(p.sound2.def);
			us.insert(p.sound2.dead);
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}


