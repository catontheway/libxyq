#pragma once
#include "cNode.h"

class cLabel : public cNode
{
public:
	enum class eAlign
	{
		left = gge::FONT_ALIGN::TEXT_LEFT,
		center = gge::FONT_ALIGN::TEXT_CENTER,
		right = gge::FONT_ALIGN::TEXT_RIGHT
	};
	cLabel();
	virtual ~cLabel();

	static cLabel* create(const std::string& text = "", int fontSize = 16)
	{
		CREATE(cLabel, text, fontSize);
	}

protected:
	virtual bool init(const std::string& text, int fontSize);

	virtual void onColor(uchar opacity, uchar r, uchar g, uchar b);

	virtual void onRender(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y);
public:
	virtual void setString(const std::string& text);

	void setAlign(eAlign align);

protected:
	std::string _text;
	gge::ggeFont* _font;
	bool _isBack;
};