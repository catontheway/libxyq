#pragma once
#include "expEasy.h"

class expNpc : public expEasy
{
public:
	CREATE_FUNC(expNpc);

protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};

