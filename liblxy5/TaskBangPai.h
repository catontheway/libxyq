#pragma once
#include "_taskinc.h"


class cTaskBangPai :public cTaskFather
{
public:
	cTaskBangPai(){ Init(); }
	void Init();
	bool Process(int stage);
};