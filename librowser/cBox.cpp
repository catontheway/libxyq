#include "cBox.h"

cBox::~cBox()
{

}

bool cBox::init()
{
	if (!cNode::init())
	{
		return false;
	}

	setColor(s565::WHITE);
	return true;
}

void cBox::setColor(const s565& color)
{
	cNode::setColor(Color3B(color.r << 3, color.g << 2, color.b << 3));
	_color = color;
	_isDraw = true;
}


void cBox::setColor(uchar r, uchar g, uchar b)
{
	cNode::setColor(Color3B(r, g, b));
	_color.r = r >> 3;
	_color.g = g >> 2;
	_color.b = b >> 3;
	_isDraw = true;
}

void cBox::draw(cCanvas* canvas, const uint32_t& flags)
{
	cLine line(_contentSize.width, 0, *(WPixel*)&_color);
	canvas->SetPos(_wx, _wy);
	canvas->Draw(line, BLIT_NORMAL);

	cLine line2(_contentSize.width, 0, *(WPixel*)&_color);
	canvas->SetPos(_wx, _wy + _contentSize.height);
	canvas->Draw(line2, BLIT_NORMAL);

	cLine line3(0, _contentSize.height, *(WPixel*)&_color);
	canvas->SetPos(_wx, _wy);
	canvas->Draw(line3, BLIT_NORMAL);

	cLine line4(0, _contentSize.height, *(WPixel*)&_color);
	canvas->SetPos(_wx + _contentSize.width, _wy);
	canvas->Draw(line4, BLIT_NORMAL);
}
