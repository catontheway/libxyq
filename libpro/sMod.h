#pragma once
#include "sDye.h"

struct sMod
{
	static const int c_1;
	enum class eRole { weapon, zq, xr, card };
	// 主模型
	eMod emod = eMod::eModNone;
	// 类型
	eRole erole = eRole::weapon;
	// 染色
	sDye dyeRole, dyeWeapon,  dyeZq, dyeZs;
	std::vector<sDye> dyePets;

	// 武器
	eIcon eweapon;
	int weaponId = c_1;
	int weaponMasterIdx = 0;
	// 坐骑
	eZuoqi ezq = eZuoqi::eZuoqiNone;
	// 装饰
	int zsid = c_1;
	// 祥瑞
	int xrid = c_1;
	// 角色姿势
	int xridx = 0;
	// 变身模型
	eMod ecard = eMod::eModNone;
	// 进阶
	int jdx = 0;
	// 渡劫/化圣头像
	int dujie = 0;

	bool setRole(eRole e);
	void setMod(eMod e);
	bool setWeapon(eIcon e, int wid);
	bool setWeapon(int wlv);
	void setWeaponUnsnatch();
	bool setZuoqi(eZuoqi e);
	bool setZs(int zs);
	bool setXr(int idx);
	bool setXr();
	bool setCard(eMod e);
	bool setJinjie(int jdx);
	bool setJinjie();
	bool setDujie(int dj);

	typedef std::map<eAct, sSps> sActs;
	void apply(sActs& sps, bool fight, eIterType iter) const;
	void apply(txtAction::sAction& heads, bool fight) const;

	sSps get(eAct e) const ;

	void save(bool pet) const;
	void load(bool pet);
};