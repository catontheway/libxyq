#pragma once
#include "eMod.h"

class txtMod
{
public:
	// 是否宝宝模型
	static bool isPet(eMod mod);
	// 是否Npc模型
	static bool isNpc(eMod mod);
	// 是否人物模型
	static bool isRole(eMod mod);
	// 人物性别
	static bool isBoy(eMod eRole);
};