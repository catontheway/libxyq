#pragma once
#include <windows.h>
#include "../libcc/_coco.h"

class cMain
{
public:
	static int uMain(HINSTANCE hInstance, cMain* mainApp, int fps = 60, int w = 0, int h = 0, int cw = 0, bool cursor = false);

	virtual void close();

	virtual void setTitle(HWND hwnd, HWND child);

	virtual Scene* runScene();

	virtual void beforeMainLoop();

	virtual void afterMainLoop();
};