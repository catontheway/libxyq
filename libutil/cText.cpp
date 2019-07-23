#include "cText.h"

ulong cText::getuid(eChannel e)
{
	ulong uid = cSp::c0;
	switch (e)
	{
	case eChannel当前:
		uid = 0x65C5B7EE;
		break;
	case eChannel队伍:
		uid = 0xF9858C95;
		break;
	case eChannel世界:
		uid = 0x1B1DCE56;
		break;
	case eChannel系统:
		uid = 0x43700E25;
		break;
	case eChannel私聊:
		uid = 0xF9ADC3DA;
		break;
	default:
		break;
	}
	return uid;
}

bool cText::init(eFont e, int width)
{
	if (!cNode::init())
	{
		return false;
	}
	this->setContentSize(_width = width, 0);
	_fnt = cWindSoul::getInstance()->getFont(e);
	return true;
}


bool cText::isValid() const
{
	return _contentSize.width > 4 && _contentSize.height > 4;
}

void cText::setString(const std::string& text)
{
	setString(eChannelNone, "", text);
}


void cText::setString(eChannel e, const std::string& name, const std::string& text)
{
	ulong uid = getuid(e);

	auto chat = cChatManager::getInstance();
	chat->init(_width, _fnt, _color);

	cSprite* sprite = nullptr;
	if (uid != cSp::c0)
	{
		sprite = cSprite::create(uid);
		sprite->setCanvas(_eCanvas);
	}
	if (name.empty())
	{
		chat->setString(sprite, text);
	}
	else
	{
		chat->setString(sprite, "[" + name + "]" + text);
	}

	chat->applyLines(_lines);

	this->removeAllChildren();
	forr(_lines, k)
	{
		forr(_lines[k].sprites, i)
		{
			this->addChild(_lines[k].sprites[i]);
			_lines[k].sprites[i]->play();
			_lines[k].sprites[i]->setCanvas(_eCanvas);
			_lines[k].sprites[i]->release();
		}
	}
	this->setContentSize(chat->getWidth(), chat->getHeight());
}

void cText::setColor(const s565& color)
{
	cNode::setColor(Color3B(color.r << 3, color.g << 2, color.b << 3));
	_color = color;
}



void cText::setColor(uchar r, uchar g, uchar b)
{
	cNode::setColor(Color3B(r, g, b));
	_color.r = r >> 3;
	_color.g = g >> 2;
	_color.b = b >> 3;
}

void cText::draw(cCanvas* canvas, const uint32_t& flags)
{
//	_canvas->setChange(flags || _isDraw, false);
// 	if (flags || _isDraw)
// 	{
// 		_canvas->Change();
// 	}
// 	else
// 	{
// 		_canvas->UnChange();
// 	}

	forr(_lines, k)
	{
		const auto& line = _lines[k];
		int y = line.y;
		forr(_lines[k].chars, i)
		{
			const auto& c = _lines[k].chars[i];
			static cChar* s_chr = new cChar(*_fnt, c.c, *(WPixel*)&c.color);
			s_chr->Create(*_fnt, c.c, *(WPixel*)&c.color);
			canvas->SetPos(_wx + c.x, _wy + y);
			canvas->Draw(*s_chr, FONT_NOALPHA);
			
			if (_isBack)
			{
				static s565 s_back = s565::BLACK;
				s_chr->Create(*_fnt, c.c, *(WPixel*)&s_back);
				canvas->SetPos(_wx + c.x + 1, _wy + y + 1);
				canvas->Draw(*s_chr, FONT_NOALPHA);
			}
		}
	}
	if (0)
	{
		canvas->SetPos(_wx, _wy);
		canvas->SetOvlRect(_contentSize.width, _contentSize.height);
	}
}
