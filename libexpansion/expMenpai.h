#pragma once
#include "expEasy.h"

class expMenpai : public expEasy
{
public:
	CREATE_FUNC(expMenpai);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};
