#pragma once
#include "uiSee.h"

// 宝宝 
class uiPet : public uiPad, public uiProperty //, public uiZz::uiNotice
{
public:
	~uiPet();
	CREATE_FUNC(uiPet);

protected:
	bool init();

public:
	void load(sRole& role);
	// 载入(宝宝组)
	void load(const sPets& pets, int lv, int fightid);
	// 刷新某个宝宝
	void load(int index, const sProperty& pro);
	// 载入(基本属性)
	void load(int index);
	// 进阶/染色用
	void load(int index, const sSps& stands, ulong uhead = cSp::c0);

	void remove(int index);

	// 载入资质(更新)
	void loadZz(int index);

	void doFight();

	void loadPage();

protected:
	int _lv, _fightid = -1;
	sPets _pets;
	std::vector<cSprite*> _bodies;
	Vec2 _vShadow;

	// 列表
	uiGrids* _grids = nullptr;

	// 参战
	cButton* _buttonFight = nullptr;
	// 查看技能
	cButton* _buttonSkill = nullptr;
	// 进阶
	cButton* _buttonJinjie = nullptr;
	// 染色
	cButton* _buttonColor = nullptr;
	// 放生
	cButton* _buttonFree = nullptr;
	// 改名
	cButton* _buttonChangeName = nullptr;

	// 携带等级
	cLabel* _labelTakelv = nullptr;
	cLabel* _labelPage = nullptr;

	// 资质
	uiZz* _zz = nullptr;
	// 仓库

	// 背包

public:
	enum class eOperator { fight, jinjie, free, store, color };
	std::function<bool(eOperator, int, const sProperty&)> onOperate = nullptr;
};