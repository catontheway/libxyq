#include "cChatManager.h"
#include "cLabel.h"
#include "../libtxt/txtEasy.h"


static const std::map<char, s565>& getSharpColors()
{
	static std::map<char, s565> s_colorMap;
	if (s_colorMap.empty())
	{
		s_colorMap.insert(std::make_pair('W', s565::WHITE));
		s_colorMap.insert(std::make_pair('Y', s565::YELLOW));
		s_colorMap.insert(std::make_pair('R', s565::RED));
		s_colorMap.insert(std::make_pair('G', s565::GREEN));
		s_colorMap.insert(std::make_pair('B', s565::BLUE));
		s_colorMap.insert(std::make_pair('M', s565::MAGENTA));
		s_colorMap.insert(std::make_pair('O', s565::ORANGE));
		s_colorMap.insert(std::make_pair('X', s565::BLACK));
	}
	return s_colorMap;
}


static int getSharpFace(const std::string& text, int k1, int& offs)
{
	int id = -1;
	int size = text.size();
	int v;
	for (int n = 0; n < 3; ++n)
	{
		if (k1 < size && (v = text[k1] - '0') >= 0 && v <= 9)
		{
			id = (n == 0) ? v : (id * 10 + v);
			offs = n + 1;
			++k1;
			continue;
		}
		break;
	}
	static auto& chats = txtEasy::getInstance()->getChats();
	if (id < 0 || id >= chats.size())
	{
		offs = 0;
		return -1;
	}
	return id;
}


static bool is7F(const std::string& text, int index) 
{
	return ((uchar)text[index]) > 0x7F;
}


//////////////////////////////////////////////////////////////////////////
cChatManager* cChatManager::getInstance()
{
	static cChatManager* s_chat = new cChatManager();
	return s_chat;
}


bool cChatManager::init(int width, cFont* fnt, const s565& firstColor /* = s565::WHITE */)
{
	_width = width;
	_fnt = fnt;
	_lines.resize(1);
	forr(_lines, k)
	{
		_lines[k].sprites.clear();
		_lines[k].chars.clear();
		_lines[k].hMax = _fnt->GetHeight();
	}
	_x = 0;
	_line = 0;
	while (!_colors.empty())
	{
		_colors.pop();
	}
	_firstColor = firstColor;
	return true;
}



bool cChatManager::iterX(int w)
{
	if (_x + w > _width)
	{
		_x = 0;
		pushLine();
		return true;
	}
	return false;
}



bool cChatManager::setSprite(cSprite* sprite, const Size& size)
{
	bool enter = iterX(size.width);
	sprite->setPositionX(_x);
	_lines[_line].sprites.push_back(sprite);
	if (_lines[_line].hMax < size.height)
	{
		_lines[_line].hMax = size.height;
	}
	_x += size.width;
	return enter;
}


void cChatManager::setChar(const std::string& text, int index, int& offs, int& len)
{
	bool isLast = index == text.size() - 1;
	if (is7F(text, index))
	{
		if (isLast)
		{
			offs = 1;
			len = 0;
			return;
		}
		if (text[index + 1] == ' ')
		{
			offs = 2;
			len = 0;
			return;
		}
		offs = 2;
		len = 2;
		return;
	}
	if (isLast)
	{
		if (text[index] == '#')
		{
			offs = 1;
			len = 0;
			return;
		}
		offs = 1;
		len = 1;
		return;
	}
	if ( is7F(text, index + 1) || text[index + 1] == '#')
	{
		offs = 1;
		len = 1;
		return;
	}
	offs = 2;
	len = 2;
}


bool cChatManager::setChar(const std::string& text, int index, int& offs)
{
	int len;
	setChar(text, index, offs, len);
	if (len < 1)
	{
		return false;
	}
	static char s_chars[3], s_char2[3];
	memset(s_chars, 0, 3);
	memset(s_char2, 0, 3);
	for (int k = 0; k < len; ++k)
	{
		s_chars[k] = text[index + k];
		s_char2[len - 1 - k] = text[index + k];
	}
	static sChar chr;
	chr.c = *(unsigned int*)s_char2;
	if (_colors.empty())
	{
		chr.color = _firstColor;
	}
	else
	{
		chr.color = _colors.top();
	}
	chr.w = _fnt->GetLength(s_chars);
	bool enter = iterX(chr.w);
	chr.x = _x;
	_x += chr.w;
	_lines[_line].chars.push_back(chr);
	return enter;
}



bool cChatManager::setLine(const std::string& text)
{
	int offs = 1;
	int size = text.size();
	bool enter = false;
	for (int k = 0;;)
	{
		if (offs == 0 || k >= size)
		{
			break;
		}
		if (text[k] == '#')
		{
			if (k + 1 < text.size())
			{
				auto& colorMap = getSharpColors();
				if (colorMap.find(text[k + 1]) != colorMap.end())
				{
					auto color = colorMap.at(text[k + 1]);
					if (_colors.empty())
					{
						_colors.push(color);
					}
					else if (color.color == _colors.top().color)
					{
						_colors.pop();
					}
					else
					{
						_colors.push(color);
					}
					k += 2;
					continue;
				}
			}
			int faceIndex = getSharpFace(text, k + 1, offs);
			if (faceIndex >= 0)
			{
				static auto& chats = txtEasy::getInstance()->getChats();
				cSprite* sprite = cSprite::create(chats.at(faceIndex));
				sprite->retain();
				if (setSprite(sprite, sprite->getContentSize()))
				{
					enter = true;
				}
				k += offs + 1;
				continue;
			}
		}
		if (setChar(text, k, offs))
		{
			enter = true;
		}
		k += offs;
	}
	return enter;
}


void cChatManager::pushLine()
{
	++_line;
	sLine line;
	line.hMax = _fnt->GetHeight();
	_lines.push_back(line);
}

void cChatManager::setString(cSprite* spriteChannel, const std::string& text)
{
	if (spriteChannel != nullptr)
	{
		if (spriteChannel->getReferenceCount() == 1)
		{
			spriteChannel->retain();
		}
		static Size s_sizeChannel = spriteChannel->getContentSize();
		setSprite(spriteChannel, s_sizeChannel);
	}

	std::vector<std::string> enters;
	cc::split(text, "\r\n", enters);
	forv(enters, k)
	{
		setLine(enters[k]);
		pushLine();
		_x = 0;
	}

	static const int hinv = 1;
	_height = hinv;
	bool unlimit = true; //_width == cWidthMax;
	int width;
	if (unlimit)
	{
		_width = 0;
	}
	cSprite* sprite;
	for (int k = 0; k < _line; ++k)
	{
		auto& line = _lines[k];
		line.y = _height += line.hMax + hinv;
		forr(line.sprites, i)
		{
			sprite = line.sprites[i];
			sprite->setPositionX(sprite->getPositionX() + sprite->getInfo()->kx);
			sprite->setPositionY(line.y - sprite->getContentSize().height + sprite->getInfo()->ky);
		}
		line.y -= _fnt->GetHeight() + hinv;

		if (unlimit)
		{
			if (!line.sprites.empty())
			{
				width = line.sprites.back()->getPositionX() + line.sprites.back()->getContentSize().width;
				if (width > _width)
				{
					_width = width;
				}
			}
			if (!line.chars.empty())
			{
				width = line.chars.back().x + line.chars.back().w;
				if (width > _width)
				{
					_width = width;
				}
			}
		}
	}
}



bool cChatManager::applyLines(std::vector<sLine>& lines)
{
	lines.clear();
	for (int k = 0; k < _line; ++k)
	{
		lines.push_back(_lines[k]);
	}
	return true;
}
