#pragma once
#include "expEasy.h"


class expSkill : public expEasy
{
public:
	CREATE_FUNC(expSkill);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
	static void getuids(eSkill eski, std::vector<ulong>& uids);

	struct sName { std::string name; eSkill begin, end; };
	std::vector<sName> _names;
};

