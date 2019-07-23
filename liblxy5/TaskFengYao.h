#pragma once
#include "_taskinc.h"


class cTaskFengYao :public cTaskFather
{
public:
	cTaskFengYao();
	virtual void Init();
	virtual bool Process(int stage);
	struct sFy{ int lv; string mapname; };
	vector<sFy> _fys;
	int _selectModeid, _selectX, _selectY;
};
