#pragma once
#include "uiPad.h"
#include "uiGrids.h"

class uiRank : public uiPad
{
public:
	static uiRank* create(int iw, int ih){ CREATE(uiRank, iw, ih) }

protected:
	virtual bool init(int iw, int ih);

public:
	void load();

	void load(int page);

	void load(int index, ulong uid, ulong uid2, bool play);

protected:
	cLabel* _labelPage = nullptr;
	cButton* _buttonLeft = nullptr;
	cButton* _buttonRight = nullptr;

	int _x, _y, _row, _cel, _iw, _ih, _wh, _page = -1, _pageMax = 1;
	std::vector<Node*> _nodes;
	std::vector<cButton*> _buttons;
	struct su2 { ulong u1 = cSp::c0, u2 = cSp::c0; };
	std::vector<su2> _uids;
public:
	// 点击购买回调(选中的索引, 选中物品的数量)
	std::function<void(int, ulong, ulong)> onSelect = nullptr;
};

