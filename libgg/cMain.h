#pragma once
#include "cNode.h"

class cMain
{
public:
	bool init(int w = 640, int h = 480);
	void start();
	void setExit(gge::GGE_BOOLFUN exitFunc);
	void setGain(gge::GGE_BOOLFUN gainFunc);
	void setLost(gge::GGE_BOOLFUN lostFunc);
	void setMsg(gge::GGE_MSGFUN msgFunc);
};