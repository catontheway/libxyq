#pragma once
#include "expEasy.h"

class expZuoqi : public expEasy
{
public:
	CREATE_FUNC(expZuoqi);
	static expZuoqi* createWm() { CREATE(expZuoqi, true); }
protected:
	bool init(bool iswm = false);
	cNode* initDrag(int tag, int tag2 = cTagNone);

	bool _iswm;
};