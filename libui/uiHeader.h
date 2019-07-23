#pragma once
#include "_inc.h"

// 头像按钮 血条 蓝条 愤怒 经验
class uiHeader : public cNode
{
public:
	static uiHeader* create(bool pet){ CREATE(uiHeader, pet); }

	bool init(bool pet);

	void load(const sProperty& pro, int hpMax, int mpMax);
	void load(ulong head);
	void load(const sProperty& pro);

protected:
	bool _isPet;

	// 头像精灵
	cSprite* _spriteHead = nullptr;
	// 血条精灵(支持裁剪)
	cSprite* _spriteHp = nullptr;
	cSprite* _spriteHp2 = nullptr;
	cSprite* _spriteMp = nullptr;
	cSprite* _spriteAp = nullptr;
	cSprite* _spriteExp = nullptr;

	Size _sizeBar;

public:
	static const int c32 = 32;
};