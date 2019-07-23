#include "cLabel.h"

bool cLabel::init(const std::string& text, eFont e)
{
	if (!cNode::init())
	{
		return false;
	}

	_fnt = cWindSoul::getInstance()->getFont(e);

	if (text.size())
	{
		setString(text);
	}
	return true;
}


bool cLabel::isValid() const
{
	return !_name.empty();
}

void cLabel::setColor(const s565& color)
{
	cNode::setColor(Color3B(color.r << 3, color.g << 2, color.b << 3));
	_color = color;
	_isDraw = true;
}



void cLabel::setColor(uchar r, uchar g, uchar b)
{
	cNode::setColor(Color3B(r, g, b));
	_color.r = r >> 3;
	_color.g = g >> 2;
	_color.b = b >> 3;
	_isDraw = true;
}


static const s565& setColor(const u64& _number)
{
	static s565 color;
	if (_number < 10000)
	{
		return color = s565::BLACK;
	}
	if (_number < 100000)
	{
		return color = s565::BLUE;
	}
	if (_number < 1000000)
	{
		return color = s565(0, 0x88, 0);
	}
	if (_number < 10000000)
	{
		return color = s565::RED;
	}
	return color = s565::MAGENTA;
}


void cLabel::setString(const u64& u, bool moneyColor /* = false */)
{
	_number = u;
	setString(cc::toString(u));
	if (moneyColor)
	{
		setColor(::setColor(u));
	}
}


void cLabel::setString(int i, bool moneyColor /* = false */)
{
	_number = i;
	setString(cc::toString(i));
	if (moneyColor)
	{
		setColor(::setColor(i));
	}
}



void cLabel::setString(const std::string& text)
{
	_name = text;
	cNode::setContentSize(Size(_fnt->GetLength(getString().c_str()), _fnt->GetHeight()));
	_isDraw = true;
}


const std::string& cLabel::getString()const
{
	return _name;
}



void cLabel::draw(cCanvas* canvas, const uint32_t& flags)
{
//	_canvas->setChange(flags, _isDraw && !flags);
// 	if (flags || _isDraw)
// 	{
// 		canvas->Change();
// 	}
// 	else
// 	{
// 		canvas->UnChange();
// 	}
	canvas->SetPos(_wx, _wy);
	_fnt->Draw(*canvas, _name.c_str(), *(WPixel*)&_color);
//	_canvas->Draw(_fnt, &_color, _name.c_str());
	if (_isBack)
	{
		static s565 color;
		color = _color;
		_color = s565::BLACK;
		canvas->SetPos(_wx + 1, _wy + 1);
	//	_canvas->drawFont(_fnt, &_color, _name.c_str());
		_fnt->Draw(*canvas, _name.c_str(), *(WPixel*)&_color);
		_color = color;
	}
}



//////////////////////////////////////////////////////////////////////////
bool cLabelNO::init(u64 number, u64 numberMax)
{
	if (!cLabel::init("", eFont::nor))
	{
		return false;
	}

	this->addChild(_labelCursor = cLabel::create("|"));
	_labelCursor->setColor(s565::RED);
	// _labelCursor->setBack(true);
	_labelCursor->setPositionY(1);

	_max = numberMax;
	setString(number, true);
	this->scheduleUpdate();
	setSnatchNode(true);
	return true;
}

bool cLabelNO::isSnatched(const Vec2& v)
{
	if (cLabel::isSnatched(v))
	{
		return true;
	}
	return Rect(0, 0, 128, _contentSize.height).containsPoint(v);
}

void cLabelNO::setString(u64 number, bool moneyColor /* = false */)
{
	if (number > _max)
	{
		number = _max;
	}
	_number = number;
	cLabel::setString((_number == 0) ? "" : cc::toString(_number));
	if (moneyColor)
	{
		setColor(::setColor(_number));
	}

	_labelCursor->setPositionX(_contentSize.width - 3);
}

void cLabelNO::add()
{
	setString(_number + 1);
}


void cLabelNO::update(float delta)
{
	if (!isVisible())
	{
		return;
	}
	auto snatch = cMouse::getInstance()->getDown();
	auto node = snatch == nullptr ? nullptr : dynamic_cast<Node*>((cSnatch*)snatch);
	auto parent = node == nullptr ? nullptr : node->getParent();
	if (node != _parent && parent != this && parent != _parent)
	{
		_labelCursor->setVisible(false);
		return;
	}

	static int x = 0;

	if (++x == 15)
	{
		_labelCursor->setVisible(true);
	}
	else if (x == 30)
	{
		x = 0;
		_labelCursor->setVisible(false);
	}
	static std::map<int, int> s_numberMap =
	{
		{ DIK_1, 1 },
		{ DIK_2, 2 },
		{ DIK_3, 3 },
		{ DIK_4, 4 },
		{ DIK_5, 5 },
		{ DIK_6, 6 },
		{ DIK_7, 7 },
		{ DIK_8, 8 },
		{ DIK_9, 9 },
		{ DIK_0, 0 },
		{ DIK_NUMPAD7, 7 },
		{ DIK_NUMPAD8, 8 },
		{ DIK_NUMPAD9, 9 },

		{ DIK_NUMPAD4, 4 },
		{ DIK_NUMPAD5, 5 },
		{ DIK_NUMPAD6, 6 },

		{ DIK_NUMPAD1, 1 },
		{ DIK_NUMPAD2, 2 },
		{ DIK_NUMPAD3, 3 },
		{ DIK_NUMPAD0, 0 },
	};

	if (cInput::getInstance()->isKdown(DIK_BACK))
	{
		_number /= 10;
		setString(_number);
		if (onNO != nullptr)
		{
			onNO(this);
		}
	}
	else for (const auto& k : s_numberMap)
	{
		if (!cInput::getInstance()->isKdown(k.first))
		{
			continue;
		}
		_number *= 10;
		_number += k.second;
		setString(_number);
		if (onNO != nullptr)
		{
			onNO(this);
		}
		break;
	}
}
