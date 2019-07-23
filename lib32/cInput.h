#pragma once
#include <windows.h>
#include "_inc.h"

class cInputDx;
class cInputDevice;
// 输入(鼠键)
class cInput
{
public:
	cInput();
	static cInput* getInstance();

	bool init(HWND hwnd, HINSTANCE hinst);

	// 鼠标事件: 左键按下
	bool isLdown(bool lock = true);
	void lockLdown();
	void unlockLdown();
	// 鼠标事件: 左键按住
	bool isLkeep();
	bool isLup(bool lock = true);
	void lockLup();
	// 鼠标事件: 右键弹起
	bool isRup(bool lock = true);
	void lockRup();
	// 键盘事件: 键盘按下
	bool isKdown(unsigned char key, bool lock = true);
	bool isAlt();
	// 鼠标事件: 取鼠标滚轮
	int getWheel(bool lock = true);
	void lockWheel();

	// 鼠标事件: 取鼠标位置
	const Vec2& getMouse();
	// 鼠标事件: 取鼠标相对上一帧的偏移
	const Vec2& getMouseDelta();

private:
	HWND _hwnd;
	cInputDx* _input;
	cInputDevice* _mouse;
	cInputDevice* _keybord;
	bool _islup;
	bool _isluplock;
	bool _islkeep;
	bool _islkeepLast;

	bool _isrup;
	bool _isruplock;
	bool _isrkeepLast;

	bool _iswheellock;

	Vec2 _vCursor, _vDelta;
public:
	void update();
};