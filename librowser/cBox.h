#pragma once
#include "../libwas/_inc.h"

#include "../libutil/cCursor.h"
#include "../libutil/cDesc.h"
#include "../libutil/cLabel.h"
#include "../libutil/cMouse.h"
#include "../libutil/cNode.h"
#include "../libutil/cReader.h"
#include "../libutil/cSp.h"
#include "../libutil/cSprite.h"


class cBox : public cNode
{
public:
	~cBox();
	CREATE_FUNC(cBox)

protected:
	virtual bool init();

public:
	void setColor(const s565& color);
	void setColor(uchar r, uchar g, uchar b);

protected:
	virtual void draw(cCanvas* canvas, const uint32_t& flags);

	s565 _color;
};