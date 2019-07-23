#pragma once
#include "cChatManager.h"
#include "cLabel.h"

enum eChannel
{
	eChannelNone = -1,
	eChannel当前,
	eChannel队伍,
	eChannel世界,
	eChannel系统,
	eChannel私聊
};

class cText : public cNode
{
public:
	static ulong getuid(eChannel e);
	static cText* create(eFont e, int width = cChatManager::cWidthMax){ CREATE(cText, e, width); }
	static cText* create(int width = cChatManager::cWidthMax) { CREATE(cText, eFont::nor, width); }
protected:
	virtual bool init(eFont e, int width);

public:
	bool isValid() const;
	// #0~#119 表情
	// #W #Y #R #G #B #M #O 颜色
	void setString(const std::string& text);
	void setString(eChannel e, const std::string& name, const std::string& text);

	void setColor(const s565& color);
	void setColor(uchar r, uchar g, uchar b);

	// 字体阴影
	void setLabelBack(bool back){ _isBack = back; }

protected:
	void draw(cCanvas* canvas, const uint32_t& flags);

	cFont* _fnt;
	bool _isBack = false;
	int _width;

	std::vector<cChatManager::sLine> _lines;
	s565 _color;
};

