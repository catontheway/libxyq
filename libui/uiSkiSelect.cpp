#include "uiSkiSelect.h"

bool uiSkiSelect::init()
{
	if (!uiPad::init(cSp::c0, true))
	{
		return false;
	}
	this->addChild(_grids = uiGrids::create());

	_grids->onClick = [&](bool left)
	{
		if (!left)
		{
			doClose();
		}
	};
	_grids->onGrid = [&](int index, int count, bool left)
	{
		doClose();
		if (onSelect != nullptr)
		{
			onSelect(index, _skis[index], left);
		}
	};
	return true;
}



void uiSkiSelect::load(const sSkis& skis)
{
	ulong uid;
	_skis = skis;
	int size = skis.size();
	if (size <= 6)
	{
		uid = 0x2FD95E30;
	}
	else if (size > 6 && size <= 10)
	{
		uid = 0x69823EE5;
	}
	else if (size > 10 && size <= 14)
	{
		uid = 0x0A8B7D87;
	}
	else if (size > 14 && size <= 20)
	{
		uid = 0x32F119A5;
	}
	else
	{
		uid = 0x4226BD41;
	}
	uiPad::load(uid);
	resetButtonTitlePosition();
	int x = 29, ix = 88, y = 33, iy = 42, inv = 2;
	if (size <= 6)
	{
		x = 35, ix = 61, iy = 59;
	}
	else if (size > 14 && size <= 20)
	{
		y = 28;
	}
	else if (size > 20)
	{
		x = 25, ix = 50, y = 27, inv = 3;
	}
	_grids->clear();
	_grids->setPosition(x, y);
	forv(skis, k)
	{
		auto g = uiGrid::create(skis[k]);
		g->setPosition(ix * (k % inv), iy * (k / inv));
		_grids->load(g);
	}
	_grids->load();
}
