#pragma once
#include "uiProperty.h"
#include "uiZz.h"
#include "cObject.h"

// ²é¿´
class uiSee : public uiPad, public uiProperty, public uiPropertyZz
{
public:
	~uiSee();
	CREATE_FUNC(uiSee);

protected:
	virtual bool init();

public:
	void load(const sProperty& pro);

protected:
	cSprite* _body = nullptr;
	Vec2 _vShadow;
};