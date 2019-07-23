#include "cLoop.h"


cLoop::cLoop()
{
	interval = 0LL;
	waitMS = 0L;
	QueryPerformanceCounter(&nLast);
}


cLoop* cLoop::getInstance()
{
	static cLoop* s_loop = new cLoop();
	return s_loop;
}


bool cLoop::init(float inv)
{
	QueryPerformanceFrequency(&freq);
	_animationInterval.QuadPart = (LONGLONG)(inv * freq.QuadPart);

	ZeroMemory(&msg, sizeof(MSG));
	return true;
}


bool cLoop::peek()
{
	return PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE); // PM_REMOVE
}


bool cLoop::isBreak()
{
	if (!GetMessage(&msg, NULL, 0, 0)) // msg.message == WM_QUIT
	{
		return true;
	}
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return false;
}


bool cLoop::loop()
{
	QueryPerformanceCounter(&nNow);
	interval = nNow.QuadPart - nLast.QuadPart;
	if (interval >= _animationInterval.QuadPart)
	{
		nLast.QuadPart = nNow.QuadPart;
		return true;
	}
	waitMS = (_animationInterval.QuadPart - interval) * 1000LL / freq.QuadPart - 1L;
	if (waitMS > 1L)
	{
		Sleep(waitMS);
	}
	return false;
}

