#pragma once
#include "expEasy.h"

class expIcon : public expEasy
{
public:
	CREATE_FUNC(expIcon);
protected:
	bool init();
	cNode* initDrag(int tag, int tag2 = cTagNone);
};


class expIconWeapon : public expIcon
{
public:
	CREATE_FUNC(expIconWeapon);

protected:
	bool init();
};


class expIconEquip : public expIcon
{
public:
	CREATE_FUNC(expIconEquip);

protected:
	bool init();
};
