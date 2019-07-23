#pragma once
#include "cNode.h"

typedef gge::ggeTexture Texture2D;
class cSprite : public cNode
{
public:
	cSprite();
	~cSprite();

	static cSprite* create(Texture2D* texture){ CREATE_INIT(cSprite, setTexture, texture);}

	bool setTexture(Texture2D *texture);
	Texture2D* getTexture();

protected:
	virtual void onColor(uchar opacity, uchar r, uchar g, uchar b);

	virtual void onTransform(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y);

	virtual void onRender(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y);

	gge::ggeSprite* _sprite;
};