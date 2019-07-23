#pragma once
#include "expEasy.h"

class expXiangrui : public expEasy
{
public:
	CREATE_FUNC(expXiangrui);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};