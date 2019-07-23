#pragma once
#include "TxtSkill.h"

enum class eMenpai
{
	None = -1,
	Dt,
	Hs,
	Ne,
	Fc,
	St,
	Mw,
	Ps,
	Df,
	Lg,
	Wz,
	Pt,
	Tg,
	Lb,
	Wd,
	Sm
};


namespace ctt
{
	// 学习技能提升的属性
	enum class ePromote
	{
		None,
		Hp,
		Mp,
		Atk,
		Hit,
		Def,
		Mana,
		Speed,
		Evade,
	};

	struct sMenpai
	{
		eMenpai e;
		std::string name;
		std::string masterName;
		std::string map;
		std::string masterMap;
		struct sMain
		{
			int id;
			ulong small;
			ulong big;
			std::string name;
			ePromote promote;
			struct sLockSkill
			{
				int lock;
				eSkill skill;
			};
			std::vector<sLockSkill> skills;
		};
		std::vector<sMain> mains;
	};


	const vector<sMenpai>& getMenpais();


	inline vector<ulong> getWdfFromTxtMenpais()
	{
		auto ms = getMenpais();
		set<ulong> us;
		for (const auto& mp : ms)
		{
			for (const auto& m : mp.mains)
			{
				us.insert(m.small);
				us.insert(m.big);
			}
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}