#pragma once
#include "uiSee.h"

// 人物状态
class uiState : public uiPad, public uiProperty
{
public:
	CREATE_FUNC(uiState);

protected:
	virtual bool init();

public:
	// 载入(人物数据)
	void load(sRole& role);

protected:
	sRole _role;

	// 称谓
	cLabel* _labelAppellation = nullptr;
	// 门派
	cLabel* _labelMenpai = nullptr;
	// 帮派
	cLabel* _labelBangpai = nullptr;

	// 人物技能
	cButton* _buttonSkill = nullptr;

	// 升级
	cButton* _buttonLvup = nullptr;

public:
	std::function<void()> onLvup = nullptr, onSki = nullptr;
};