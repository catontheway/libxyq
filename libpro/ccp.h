#pragma once
#include "cEquip.h"
#include "sPropertyInfo.h"
#include "sAttribute.h"
#include "sProperty.h"
#include "sRole.h"

namespace ccp
{
	struct sTz { eSki ski; int rate = 0, lvGap; };
}
struct sPropertys
{
	sPropertyInfo info;
	sAttribute attr;
	sPoint point;
	ccp::sTz taozhuang;
	seSkis specials;
};
// 属性计算
namespace ccp
{
	static const int cFF = 0xFF;
	// 面板属性 
	void apply(sAttribute& attr, int skilv);
	void apply(sAttribute& attr, int fzlv, int fzIdx);
	void apply(sAttribute& attr, const sPoint& point);
	void apply(sAttribute& attr, const sPoint& point, const sZz& zz, int lv);
	// 内置属性
	std::string apply(sPropertyInfo& info, int3& speed, eMenpai menpai, int rlv = -1);
	void apply(sPropertyInfo& info, const sXl& xl);
	void apply(sPropertyInfo& info, int3& speed, int fabao);
	// 装备
	void apply(sPropertyInfo& info, sAttribute& attr, sPoint& point, const cEquip::sPropertys& pros);
	void apply(sPropertyInfo& info, sAttribute& attr, sPoint& point, sTz& taozhuang, seSkis& specials, const sItems& equips);
	// 被动技能
	void apply(sPropertyInfo& info, sAttribute& attr, eSki ski, int lv);
	void apply(sPropertyInfo& info, sAttribute& attr, const sPoint& point, const seSkis& skis, int lv);
	// 主属性
	void apply(sPropertys& pros, const sProperty* pro);
	void apply(sPropertys& pros, const sProperty& pro);
	// 酒肆
	void fillHpMp(sProperty& pro);
	// 升级
	bool lvup(sProperty& pro, bool onlyCheck);
	// 降级
	bool lvdown(sProperty& pro, bool onlyCheck);
	bool lvdown(sRole& role);
	// 门派技能
	bool addSki(sSkis& skis, eMenpai e, bool normal);
	// 添加技能(重复的技能会被覆盖)
	bool addSki(sSkis& skis, sSki ski, int idx = -1);
	// 装备总伤害
	int getEquipsAtk(const sItems& equips);

	std::string getMenpaiName(eMenpai menpai);

	bool useItem(const sItem& item, sRole& role);
	bool useItem(const sItem& item, sProperty& pet);
};