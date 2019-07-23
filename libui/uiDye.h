#pragma once
#include "uiPad.h"

// 调色板 染色
class uiDye : public uiPad
{
public:
	CREATE_FUNC(uiDye);
	virtual bool init();
	void doBind();
protected:
	bool _randModel = false;

	// 显示的精灵
	cSprite* _sprite = nullptr;
	// 切换 正常/随机 模式
	cButton* _buttonMod = nullptr;
	// 部位
	cButton* _buttonPart = nullptr;
	// 分段
	std::array<cButton*, 4> _button4s;
	// 左转
	cButton* _buttonLeft = nullptr;
	// 右转
	cButton* _buttonRight = nullptr;
	// 重置调色板
	cButton* _buttonZero = nullptr;
	// 确定
	cButton* _bottonOk = nullptr;
};
