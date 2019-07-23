#pragma once
#include "uiPad.h"

// 属性界面(人物和宝宝共有的)
class uiProperty
{
public:
	uiProperty();

protected:
	virtual bool init(Node* parent, int px, int py, int px2, int iy);

public:
	virtual void load(const sProperty& pro);

	// 载入(更新)
	virtual void load();

	virtual void updatePoint();
protected:
	sProperty _pro;
	sPropertys _pros;
	bool _isPointed = false;
	sPoint _pointShow;
	std::array<int*, 5> _points;

	// 按钮 加减点
	std::array<cButton*, 5> _buttonAdds;
	std::array<cButton*, 5> _buttonSubs;
	// 按钮 确定加点
	cButton* _buttonSure = nullptr;

	// 等级
	cLabel* _labelLv = nullptr;
	// 名字
	cLabel* _labelName = nullptr;
	// 气血
	cLabel* _labelHp = nullptr;
	// 魔法
	cLabel* _labelMp = nullptr;
	// 愤怒
	cLabel* _labelAp = nullptr;

	// 命中
	cLabel* _labelHit = nullptr;
	// 攻击
	cLabel* _labelAtk = nullptr;
	// 防御
	cLabel* _labelDef = nullptr;
	// 速度
	cLabel* _labelSpeed = nullptr;
	// 灵力
	cLabel* _labelMana = nullptr;
	// 躲避 
	cLabel* _labelEvade = nullptr;

	// 属性点 体质
	cLabel* _labelBody = nullptr;
	// 属性点 魔力
	cLabel* _labelMag = nullptr;
	// 属性点 力量
	cLabel* _labelStr = nullptr;
	// 属性点 耐力
	cLabel* _labelDex = nullptr;
	// 属性点 敏捷
	cLabel* _labelAgi = nullptr;
	// 属性点 剩余
	cLabel* _labelRemian = nullptr;

	// 经验
	cLabel* _labelExp = nullptr;
	cLabel* _labelExpMax = nullptr;

public:
	// 宝宝选择索引
	std::function<void(int, const sPoint&)> onPoint;
};