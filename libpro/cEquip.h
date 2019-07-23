#pragma once
#include "sItem.h"

class cEquip
{
public:
	typedef txtStone::sStone sProperty;
	typedef std::vector<sProperty> sPropertys;

	// 武器/防具/宝宝装备
	static bool isEquip(eIcon type);
	// 武器
	static bool isWeapon(eIcon type);
	// 防具
	static bool isArmor(eIcon type);
	// 宝宝装备
	static bool isEquipBaby(eIcon type);
	// 头盔/发钗
	static bool isHelmet(eIcon type);
	// 项链
	static bool isNeck(eIcon type);
	// 盔甲/衣裙
	static bool isClothes(eIcon type);
	// 腰带
	static bool isBelt(eIcon type);
	// 鞋子
	static bool isShoe(eIcon type);
	// 填充属性 特技特效/宝宝附加 双加 指数
	static bool fill(sItem& equip, bool effect_or_ex3, bool add2, int eMin, int eMax);

	static bool apply(const sItem& equip, sPropertys& pros);
	static bool apply(const sItem& equip, sDescs& descs);
	// 携带等级
	static int getTakeLv(const sItem& equip);
	// 装备等级
	static int getLv(const sItem& equip);
	// 取装备id(根据装备等级)
	static bool getId(eIcon type, int lv, std::vector<int>& weapons);
	// 取装备id(有可能随机)
	static int getId(eIcon type, int lv);
	// 取装备栏索引
	static int getIdx(eIcon type);
	// 取武器类型(根据角色)
	static eIcon getWeaponType(eMod master, int weaponlist_0_1);
	// 能否装备(角色, 装备类型)
	static bool isEquip(eMod master, eIcon type);
	// 置套装
	static bool setFushi(sItem& equip, const sItem& fushi);
	// 取套装
	static eSkill getTaoZhuang(const sItem& equip, bool& isZhuijia);
	// 取套装
	static eSkill getZhuijia(const sItem& equip);
	// 取特技
	static eSkill getSpecial(const sItem& equip);
	// 神佑/愤怒
	static bool isGodAngry(const sItem& equip);
	// 能否镶嵌(装备类型,宝石id)
	static bool isStone(eIcon type, int stone);
	// 镶嵌
	static bool setStone(sItem& equip, int stoneid);
	// 强化石 临时属性
	static bool setTemp(sItem& equip, int temp);

	static const int c_1 = -1, c3 = 3, c6 = 6, c160 = 160;
};