#pragma once
#include "_window.h"

class cApp
{
public:
	static cApp* getInstance();

	LRESULT CALLBACK proc(HWND hWnd, unsigned int uMsg, WPARAM wParam, LPARAM lParam);

	void setSize(int sw, int sh, int w, int h, int cw);

	static WNDCLASS initClass(HINSTANCE hInst, const char* className);

	bool init(HINSTANCE hInst, const char* className);

	bool initBmpInfo();

	void start();

	HWND getHwnd() { return _hwnd; }
	HWND getChildHwnd() { return _childhwnd; }

	BITMAPINFO* getBmpInfo() { return _bmpInfo; }

	int getChatw() { return _wincw; }

	bool setScreen(bool full);

	bool switchScreen();

	bool isWindowed() { return _isWindowed; }

	void resize();

	static HFONT createFontEasy(int size);

private:
	HINSTANCE _hinst = nullptr;
	HWND _hwnd = nullptr, _childhwnd = nullptr;
 	BITMAPINFO* _bmpInfo = nullptr;

	int _screenw, _screenh, _winw, _winh, _wincw;
	bool _isWindowed = true;

};