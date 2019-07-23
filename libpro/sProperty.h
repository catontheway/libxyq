#pragma once
#include "sMod.h"
#include "sPoint.h"
#include "sXl.h"
#include "sItem.h"
#include "sSki.h"
#include "sZz.h"
#include "sExp.h"

// 主属性
struct sProperty
{
	// 是否宝宝
	bool ispet;
	// 模型
	sMod mod;
	// 门派
	eMenpai menpai = eMenpai::None;
	// 名字
	std::string name;
	// 辅助技能等级
	std::vector<int> fuzhus;
	// 等级
	int lv = 0;
	// 气血
	int hp;
	// 伤
	int hp2;
	// 魔法
	int mp;
	// 愤怒
	int ap = 0;
	// 属性点
	sPoint point;
	// 修炼
	sXl xl;
	// 技能
	sSkis skis;
	// 装备
	sItems equips;
	// 经验
	sExp exp;
	// 资质
	sZz zz;

	// 构造
	sProperty();
	sProperty(bool ispet);

	void reset(bool ispet);
	// 判断技能
	virtual bool isSki(eSkill e);
	// 技能等级
	virtual int getSkiLv() const { return lv; }
	// 升级
	virtual bool lvup(bool onlyCheck);
	// 降级
	virtual bool lvdown(bool onlyCheck);

	// 宝宝专用
	bool load(eMod e, bool rename, bool zz, bool skis);
	txtZz::eAp getAp() const;
	int getTakeLv() const;
	void applyWeapon();

	// 修炼不存
	virtual void save()const;
	virtual void load();
};