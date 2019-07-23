#pragma once
#include "cMouse.h"
#include "cDesc.h"

class cNode : public Node, public cSnatch,  public cRender, public cDesc
{
public:
	~cNode();
	CREATE_FUNC(cNode)

	virtual void setSnatchNode(bool isSnatchNode);

	virtual void setState(eMouseState state);

protected:
	virtual bool init();

public:
	virtual void setOpacity(GLubyte opacity);

	virtual void sortAllChildren();
protected:
	virtual void draw(const Mat4& transform, const uint32_t& flags);

	virtual void setRectWorld();
public:
	const Rect& getRectWorld() const;
	bool isScreen() const;

	Rect _rectWorld;
	int _wx, _wy;
};