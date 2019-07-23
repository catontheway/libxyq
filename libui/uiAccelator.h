#pragma once
#include "uiGrids.h"

// ¿ì½Ý¼ü
class uiAccelator : public cNode
{
public:
	CREATE_FUNC(uiAccelator);
protected:
	virtual bool init();
public:
	void load(const sSkis& acces);
	void load(sRole& role);

	void load(int idx, const sSki& acc);

protected:
	sSkis _skis;
	uiGrids* _grids = nullptr;

public:
	static const int c8 = ccp::acce8, c32 = 32;
	std::function<void(int)> onAccelator = nullptr, onClear = nullptr;
};