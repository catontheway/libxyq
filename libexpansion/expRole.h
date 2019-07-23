#pragma once
#include "expEasy.h"

class expRole : public expEasy
{
public:
	CREATE_FUNC(expRole);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);

	cNode* createFace(const txtRole::sRole& role);
	cNode* createBodies(const txtAction::sAction& bodies);
	cNode* createHeadFaceBodies(const txtRole::sRole& role);
	cNode* createGroup(const txtAction::sAction& rActs, const txtAction::sAction& rActMaps, const txtAction::sAction& wActs, const txtAction::sAction& wActMaps);
	cNode* createGroup(const sMod& mod);
	const int cHeadBody = -10086, cIter = 0xFFFF + 10086, cWm = cIter + 0xFFFFF + 10010;
};