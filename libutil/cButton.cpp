#include "cButton.h"


void cLabelInner::setState(eMouseState state)
{
	_label->setPosition(_vLabel + ((state == eMouseState::Down) ? Vec2(1, 1) : Vec2::ZERO));
	switch (state)
	{
	case eMouseState::Cross:
		_label->setColor(s565::YELLOW);
		break;
	case eMouseState::Down:
		_label->setColor(s565::GREEN);
		break;
	case eMouseState::Disabled:
		_label->setColor(s565::GRAY);
		break;
	default:
		_label->setColor(_color);
		break;
	}
}



void cLabelInner::setColor(uchar r, uchar g, uchar b)
{
	_label->setColor(r, g, b);
	_color.r = r;
	_color.g = g;
	_color.b = b;
}

void cLabelInner::setColor(const s565& color)
{
	_label->setColor(_color = color);
}

void cLabelInner::setString(const std::string& text)
{
	_label->setString(text);
}

const std::string& cLabelInner::getString()
{
	return _label->getString();
}

void cLabelInner::setAilgn(eAilgn e, const Size& contentSize)
{
	switch (e)
	{
	case eAilgn::Left:
		_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_vLabel.x = 5;
		_vLabel.y = contentSize.height / 2;
		break;
	case eAilgn::Mid:
		_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_vLabel = contentSize / 2;
		break;
	case eAilgn::Right:
		_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		_vLabel.x = contentSize.width - 3;
		_vLabel.y = contentSize.height / 2;
		break;
	}
	_label->setPosition(_vLabel);
}



//////////////////////////////////////////////////////////////////////////
bool cButton::init(ulong uid, const std::string& text, eFont e)
{
	if (!cSprite::init(uid, nullptr))
	{
		return false;
	}
	setSnatchNode(true);
	this->addChild(_label = cLabel::create(text, e));
	setAilgn(eAilgn::Mid);
	return true;
}


void cButton::setState(eMouseState state)
{
	cSprite::setState(state);
	cLabelInner::setState(state);
	int frame = _iframe;
	switch (state)
	{
	case eMouseState::Cross:
		frame = 2;
		break;
	case eMouseState::Down:
		frame = 1;
		break;
	case eMouseState::Disabled:
		frame = 3;
		break;
	default:
		frame = 0;
		break;
	}
	cSprite::setFrame(frame);
}


void cButton::setAilgn(eAilgn e)
{
	cLabelInner::setAilgn(e, _contentSize);
}



//////////////////////////////////////////////////////////////////////////
bool cButtonClose::init()
{
	if (!cSprite::init(ccu::uClose, nullptr))
	{
		return false;
	}
	setSnatchNode(true);
	return true;
}


bool cButtonClose::isSnatched(const Vec2& v)
{
	if (_caches.at(0).uid == ccu::uClose)
	{
		return Rect(-_contentSize.width, -_contentSize.height / 2, _contentSize.width * 5 / 2, _contentSize.height * 2).containsPoint(v);
	}
	return cSprite::isSnatched(v);
}


void cButtonClose::setState(eMouseState state)
{
	cSprite::setState(state);
	int frame = _iframe;
	switch (state)
	{
	case eMouseState::Cross:
		frame = 2;
		break;
	case eMouseState::Down:
		frame = 1;
		break;
	case eMouseState::Disabled:
		frame = 3;
		break;
	default:
		frame = 0;
		break;
	}
	cSprite::setFrame(frame);
}
