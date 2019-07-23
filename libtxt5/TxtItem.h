#pragma once
#include "_txtinc.h"

namespace ctt
{
	enum class eItem
	{
		剑剑j,
		刀刀d,
		枪枪q,
		锤子c,
		斧钺f,
		扇子s,
		爪子z,
		棒槌b,
		飘带p,
		鞭子b,
		环圈h,
		双剑s,
		宝珠b,
		弓弩g,
		法杖f,
		头盔t,
		发钗f,
		铠甲k,
		布裙b,
		项链x,
		腰带y,
		鞋子x,
		药品y,
		烹饪p,
		法宝f,
		暗器a,
		卡片k,
		道具d,
		叠加d,
		宝石b,
		花卉h,
		坐饰z,
		护腕h,
		项圈x,
		护甲h,
		一家y,
		二家e,
		三家s,
		四家s,
		乐器y,
		兽决s,
		符石f,
		巨剑j,
		灯笼d,
		伞伞s,
	};


	struct sItem
	{
		eItem e;
		int id;
		ulong small;
		ulong big;
		std::string name;
		std::string desc;
	};

	const sItem& getItem(const eItem& e, int id);


	const vector<ctt::sItem>& getItems();


	inline vector<ulong> getWdfFromTxtItems()
	{
		auto is = getItems();
		set<ulong> us;
		for (const auto& i : is)
		{
			us.insert(i.small);
			us.insert(i.big);
		}
		us.erase(0);
		return vector<ulong>(us.begin(), us.end());
	}
}