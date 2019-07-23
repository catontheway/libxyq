#pragma once
#include "uiGrids.h"
#include "uiPad.h"

// 资质(操作类)
class uiPropertyZz
{
protected:
	// 初始化(父节点, 面板事件, 位置)
	virtual bool init(Node* parent, int px, int py, int iy, int px2, int py2);

public:
	// 载入(技能, 资质)
	virtual void load(const sProperty& pro);

	// 载入(更新)
	virtual void load(const sZz& zz);

protected:
	// 技能
	uiGrids* _grids = nullptr;

	std::vector<cSprite*> _equips;

//	int _skix, _skiy;
//	int _page = 0;

	// 技能翻页
	cButton* _buttonPage = nullptr;

	// 攻击
	cLabel* _labelAtk = nullptr;
	// 防御
	cLabel* _labelDef = nullptr;
	// 体力
	cLabel* _labelHp = nullptr;
	// 法力
	cLabel* _labelMp = nullptr;
	// 速度
	cLabel* _labelSpeed = nullptr;
	// 躲避 
	cLabel* _labelEvade = nullptr;
	// 寿命
	cLabel* _labelLife = nullptr;
	// 成长
	cLabel* _labelGrow = nullptr;
	// 五行
	cLabel* _label5xing = nullptr;
};


// 资质
class uiZz : public uiPad, public uiPropertyZz
{
public:
	class uiNotice
	{
	public:
		virtual void doNotify() { _zz = nullptr; }
	protected:
		uiZz* _zz = nullptr;
	};
	~uiZz();
	static uiZz* create(uiNotice* notice) { CREATE(uiZz, notice) }

protected:
	bool init(uiNotice* notice);

public:
	uiNotice* _notice = nullptr;
};