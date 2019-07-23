#pragma once
#include "uiPad.h"
#include "uiGrids.h"

// 打造/镶嵌/分解
class uiDazao : public uiPad
{
public:
	CREATE_FUNC(uiDazao);
	virtual bool init();
	// 打造
	void dazao(cSprite* button);
	// 镶嵌
	void xiangqian(cSprite* button);
	// 分解
	void fenjie(cSprite* button);

	std::array<cSprite*, 2> _buttonHeads;

	uiGrids* _grids = nullptr;
};