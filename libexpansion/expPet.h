#pragma once
#include "expEasy.h"

class expPet : public expEasy
{
public:
	CREATE_FUNC(expPet);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);

	cNode* createGroup(eMod e, int jdx);

	struct sName { std::string name; eMod begin, end; };
	std::vector<sName> _names;
};