#pragma once
#include "cSprite.h"
#include <stack>

// 聊天文本管理
// 解析表情符号和文本颜色
// 解析后排版位置
class cChatManager
{
public:
	static cChatManager* getInstance();

	bool init(int width, cFont* fnt, const s565& firstColor = s565::WHITE);

private:
	bool iterX(int w);

	bool setSprite(cSprite* sprite, const Size& size);

	void setChar(const std::string& text, int index, int& offs, int& len);
	bool setChar(const std::string& text, int index, int& offs);

	bool setLine(const std::string& text);
	void pushLine();
public:
	// retain
	void setString(cSprite* spriteChannel, const std::string& text);

	int getWidth(){ return _width; }
	int getHeight(){ return _height; }

private:
	int _width;
	int _height;
	int _x;
	int _line;
	std::stack<s565> _colors;
	s565 _firstColor;
	cFont* _fnt;

public:
	struct sChar
	{
		unsigned int c;
		s565 color;
		int x;
		int w;
	};
	struct sLine
	{
		// retain
		std::vector<cSprite*> sprites;
		std::vector<sChar> chars;
		int hMax;
		int y;
	};
private:
	std::vector<sLine> _lines;
public:
	bool applyLines(std::vector<sLine>& lines);

	static const int cWidthMax = 0xFFFF;
};