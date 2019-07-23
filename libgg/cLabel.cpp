#include "cLabel.h"

cLabel::cLabel() : _font(nullptr), _isBack(false)
{

}

cLabel::~cLabel()
{
	if (_font != nullptr)
	{
		_font->Release();
	}
}

bool cLabel::init(const std::string& text, int fontSize)
{
	if(!cNode::init())
	{
		return false;
	}
	// Arial
	_font = gge::Font_Create("simsun.ttc", fontSize, gge::FONT_CREATE_MODE::FONT_MODE_MONO);
	if(_font == nullptr)
	{
		MessageBox(nullptr, "simsun.ttc", __FUNCTION__, MB_OK);
		return false;
	}
	setRender(true);
	setString(text);
	return true;
}

void cLabel::onColor(uchar opacity, uchar r, uchar g, uchar b)
{
	if(!_isBack)
	{
		_font->SetColor(gge::Color_ARGB(opacity, r, g, b));
	}
}



void cLabel::onRender(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y)
{
	if(_isBack)
	{
		_font->SetColor(0xFF000000);
		_font->Render(x1 + 1, y1 + 1, _text.c_str());
		_font->SetColor(gge::Color_ARGB(_realOpacity, _realColor.r, _realColor.g, _realColor.b));
	}
	_font->Render(x1, y1, _text.c_str());
}


void cLabel::setString(const std::string& text)
{
	static gge::ggeFont::StringInfo info;
	_text = text;
	_font->GetStringInfo(_text.c_str(), info);
	setContentSize(info.Width, info.Height);
}

void cLabel::setAlign(eAlign align)
{
	_font->SetAlign((gge::FONT_ALIGN)align);
}
