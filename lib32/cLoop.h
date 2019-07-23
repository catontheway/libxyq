#pragma once
#include <windows.h>

// Ö¡²½½ø
class cLoop
{
public:
	cLoop();
	static cLoop* getInstance();
	bool init(float inv);
	bool peek();
	bool isBreak();
	bool loop();
private:
	LARGE_INTEGER _animationInterval;
	LARGE_INTEGER freq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	LONGLONG interval;
	LONG waitMS;

	MSG msg;
};