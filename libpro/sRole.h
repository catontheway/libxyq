#pragma once
#include "sProperty.h"
#include "sSki.h"

typedef std::vector<sProperty> sPets;
// 人物属性
struct sRole : public sProperty
{
	static const int cFight_1 = -1;
	// 师门技能等级
	int skilv = sSki::cGap;
	// 宝宝修
	sXl xlbb;
	// 快捷键
	sSkis acces;
	// 法宝栏
	sItems fabaos;
	// 宝宝栏
	sPets pets;
	// 参战索引
	int fight = cFight_1;
	int teamIdx;

	sRole();
	// 技能等级
	int getSkiLv() const { return skilv; }
	// 降级
	bool lvdown(bool onlyCheck);

	void unPet();
	bool isPeting();
	const sProperty& getPet() const;
	sProperty& getPet();
	bool setPet(int fight, bool onlyCheck);

	void doMod();
	std::function<void(const sMod&)> onMod = nullptr;

	void save()const;
	void load();
};