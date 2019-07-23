#pragma once
#include "uiPad.h"
#include "uiGrids.h"

// 面板: 技能选择
class uiSkiSelect : public uiPad
{
public:
	CREATE_FUNC(uiSkiSelect);

protected:
	bool init();

public:
	void load(const sSkis& skis);

protected:
	sSkis _skis;
	uiGrids* _grids = nullptr;
public:
	std::function<void(int, const sSki&, bool)> onSelect = nullptr;
};