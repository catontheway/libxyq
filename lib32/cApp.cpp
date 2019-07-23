#include "cApp.h"
#include <string>
#include <vector>
#include <objbase.h>

cApp* cApp::getInstance()
{
	static cApp* s_app = new cApp();
	return s_app;
}



LRESULT CALLBACK cApp::proc(HWND hWnd, unsigned int uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
// 	case WM_KEYUP:
// 		if (_isAlt && wParam == VK_RETURN)
// 		{
// 			switchScreen();
// 		}
// 		break;
	case WM_MOVE:
		if (hWnd == _hwnd)
		{
			resize();
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



void cApp::setSize(int sw, int sh, int w, int h, int cw)
{
	_screenw = sw;
	_screenh = sh;
	_winw = w;
	_winh = h;
	_wincw = cw;
}


WNDCLASS cApp::initClass(HINSTANCE hInst, const char* className)
{
	WNDCLASS class_proc;
	class_proc.style = CS_HREDRAW | CS_VREDRAW;
	// class_proc.lpfnWndProc = ::proc;
	class_proc.cbClsExtra = 0;
	class_proc.cbWndExtra = 0;
	class_proc.hInstance = hInst;
	class_proc.hIcon = LoadIcon(hInst,/*"WS_ICON"*/MAKEINTRESOURCE(101));
	class_proc.hCursor = NULL;
	class_proc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	class_proc.lpszMenuName = NULL;
	class_proc.lpszClassName = className;
	return class_proc;
}


bool cApp::init(HINSTANCE hInst, const char* className)
{
	_hwnd = ::CreateWindow(className, "", (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX), 0, 0, _winw, _winh, 0, 0, hInst, 0);
	if (_hwnd == nullptr)
	{
		return false;
	}
	::SetWindowLong(_hwnd, GWL_USERDATA, (unsigned long)this);



	if (_wincw > 0)
	{
		_childhwnd = ::CreateWindow(className, "", (WS_POPUP | WS_CAPTION | WS_VISIBLE | WS_CHILD), _winw, 0, _wincw, _winh, _hwnd, 0, hInst, 0);
		if (_childhwnd == nullptr)
		{
			return true;
		}
		::SetWindowLong(_childhwnd, GWL_USERDATA, (unsigned long)_childhwnd);
	}
	resize();
	return true;
}

bool cApp::initBmpInfo()
{
	_bmpInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + sizeof(RGBQUAD) * 2);
	_bmpInfo->bmiHeader.biPlanes = 1;
	_bmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_bmpInfo->bmiHeader.biCompression = 3;
	_bmpInfo->bmiHeader.biBitCount = 16;
	_bmpInfo->bmiHeader.biClrUsed = 0;
	_bmpInfo->bmiHeader.biClrImportant = 0;
	_bmpInfo->bmiHeader.biXPelsPerMeter = 0;
	_bmpInfo->bmiHeader.biYPelsPerMeter = 0;
	unsigned long colorbit = 0xf800;
	memmove(&_bmpInfo->bmiColors[0], &colorbit, sizeof(RGBQUAD));
	colorbit = 0x7e0;
	memmove(&_bmpInfo->bmiColors[1], &colorbit, sizeof(RGBQUAD));
	colorbit = 0x1f;
	memmove(&_bmpInfo->bmiColors[2], &colorbit, sizeof(RGBQUAD));
	return true;
}

void cApp::start()
{
	::ShowWindow(_hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(_hwnd);
	if (_childhwnd != nullptr)
	{
		::ShowWindow(_childhwnd, SW_SHOWDEFAULT);
		::UpdateWindow(_childhwnd);
	}

	return;
	// init COM for MP3
	CoInitialize(NULL);
}


bool cApp::setScreen(bool full)
{
	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth = full ? _winw : _screenw;
	dmScreenSettings.dmPelsHeight = full ? _winh : _screenh;
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	// 尝试设置显示模式并返回结果，注:CDS_FULLSCREEN 移去了状态条
	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return false;
	}

	if (full)
	{
		LONG styleValue = ::GetWindowLong(_hwnd, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(_hwnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		SetWindowPos(_hwnd, 0, 0, 0, _winw, _winh, SWP_FRAMECHANGED);

		if (_childhwnd != nullptr)
		{
			::ShowWindow(_childhwnd, SW_HIDE);
		}
	}
	else
	{
		::SetWindowLong(_hwnd, GWL_STYLE, GetWindowLong(_hwnd, GWL_STYLE) | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		::SetWindowPos(_hwnd, NULL, (_screenw - _winw) >> 1, (_screenh - _winh) >> 1, _winw, _winh, SWP_FRAMECHANGED);

		resize();
	}

	return true;
}



bool cApp::switchScreen()
{
	return setScreen(!(_isWindowed = !_isWindowed));
}


void cApp::resize()
{
	RECT WndRect, ClientRect;
	long WndWidth, WndHeight;

	GetWindowRect(_hwnd, &WndRect);
	GetClientRect(_hwnd, &ClientRect);

	WndWidth = (WndRect.right - (ClientRect.right - _winw)) - WndRect.left;
	WndHeight = (WndRect.bottom - (ClientRect.bottom - _winh)) - WndRect.top;

	MoveWindow(_hwnd, WndRect.left, WndRect.top, WndWidth, WndHeight, true);

	if (_childhwnd != nullptr)
	{
		::ShowWindow(_childhwnd, SW_SHOWDEFAULT);
		::UpdateWindow(_childhwnd);
		MoveWindow(_childhwnd, WndRect.left + WndWidth, WndRect.top, _wincw, WndHeight, true);
	}
}


HFONT cApp::createFontEasy(int size)
{
	return CreateFont(
		size, 0, // 高宽
		0, 0, // 显示角度 角度
		FW_NORMAL, // 字体的磅数 700粗体 
		FALSE, FALSE, FALSE, // 斜体 下划线 删除线
		GB2312_CHARSET, //GB2312_CHARSET DEFAULT_CHARSET, // 字符集
		OUT_CHARACTER_PRECIS, // OUT_CHARACTER_PRECIS OUT_DEFAULT_PRECIS,// 输出精度
		CLIP_STROKE_PRECIS, // CLIP_STROKE_PRECIS CLIP_DEFAULT_PRECIS, // 裁剪精度
		DEFAULT_QUALITY, // DEFAULT_QUALITY PROOF_QUALITY, // 逻辑字体与输出设备的实际字体之间的精度
		FF_MODERN, // DEFAULT_QUALITY FF_MODERN 字体间距
		"Arial"); // "Arial"); "仿宋"); // L"汉仪魏碑简");//L"方正粗活意简体");//L"方正彩云简体");

	return CreateFont(
		size, 0, // 高宽
		0, 0, // 显示角度 角度
		FW_NORMAL, // 字体的磅数 700粗体 
		FALSE, FALSE, FALSE, // 斜体 下划线 删除线
		DEFAULT_CHARSET, //GB2312_CHARSET DEFAULT_CHARSET, // 字符集
		OUT_DEFAULT_PRECIS, // OUT_CHARACTER_PRECIS OUT_DEFAULT_PRECIS,// 输出精度
		CLIP_DEFAULT_PRECIS, // CLIP_STROKE_PRECIS CLIP_DEFAULT_PRECIS, // 裁剪精度
		PROOF_QUALITY, // DEFAULT_QUALITY PROOF_QUALITY, // 逻辑字体与输出设备的实际字体之间的精度
		DEFAULT_QUALITY, // DEFAULT_QUALITY FF_MODERN 字体间距
		"仿宋"); // "Arial"); "仿宋"); // L"汉仪魏碑简");//L"方正粗活意简体");//L"方正彩云简体");
}