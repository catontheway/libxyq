#pragma once
#include "_txtinc.h"
#include "eModel.h"

namespace ctt
{
	struct sAction
	{
		ulong stand;
		ulong walk;
		ulong await;
		ulong go;
		ulong atk;
		ulong atk2;
		ulong maigc;
		ulong def;
		ulong atkd;
		ulong dead;
		ulong back;
	};

	struct sSound
	{
		ulong atk;
		ulong atk2;
		ulong atkd;
		ulong magic;
		ulong def;
		ulong dead;
	};


	struct sRole
	{
		struct sBody
		{
			ulong bow;
			ulong cry;
			ulong dance;
			ulong greet;
			ulong sit;
			ulong angry;
		};
		struct sActSoundPoint
		{
			sAction action;
			sSound sound;
			int offx;
			int atk;
			int magic;
		};
		struct sHead
		{
			// 好友列表里
			ulong amigo;
			ulong dialog;
			ulong small;
			ulong big;
			ulong smallHappy;
			ulong bigHappy;
			ulong smallSad;
			ulong bigSad;
			ulong smallProud;
			ulong bigProud;
		};
		eModel e;
		std::string name;
		sHead head;
		sHead head2;
		sHead head3;
		sBody body;
		std::vector<sActSoundPoint> actions;
	};


	const vector<sRole>& getRoles();


	inline vector<ulong> getWdfFromTxtModelRoleWithoutSounds()
	{
		auto rs = getRoles();
		set<ulong> us;
		for (const auto& r : rs)
		{
			us.insert(r.head.amigo);
			us.insert(r.head.dialog);
			us.insert(r.head.small);
			us.insert(r.head.big);
			us.insert(r.head.smallHappy);
			us.insert(r.head.bigHappy);
			us.insert(r.head.smallSad);
			us.insert(r.head.bigSad);
			us.insert(r.head.smallProud);
			us.insert(r.head.bigProud);

			us.insert(r.head2.amigo);
			us.insert(r.head2.dialog);
			us.insert(r.head2.small);
			us.insert(r.head2.big);
			us.insert(r.head2.smallHappy);
			us.insert(r.head2.bigHappy);
			us.insert(r.head2.smallSad);
			us.insert(r.head2.bigSad);
			us.insert(r.head2.smallProud);
			us.insert(r.head2.bigProud);

			us.insert(r.body.bow);
			us.insert(r.body.cry);
			us.insert(r.body.dance);
			us.insert(r.body.greet);
			us.insert(r.body.sit);
			us.insert(r.body.angry);

			for (const auto& a : r.actions)
			{
// 				us.insert(a.sound.atk);
// 				us.insert(a.sound.atk2);
// 				us.insert(a.sound.atkd);
// 				us.insert(a.sound.magic);
// 				us.insert(a.sound.def);
// 				us.insert(a.sound.dead);

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
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}


	inline vector<ulong> getWdfFromTxtModelRoleSounds()
	{
		auto rs = getRoles();
		set<ulong> us;
		for (const auto& r : rs)
		{
			for (const auto& a : r.actions)
			{
				us.insert(a.sound.atk);
				us.insert(a.sound.atk2);
				us.insert(a.sound.atkd);
				us.insert(a.sound.magic);
				us.insert(a.sound.def);
				us.insert(a.sound.dead);
			}

		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}