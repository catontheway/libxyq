#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

// “Ù–ß
class cWav
{
public:
	~cWav(){ free(); };
	static cWav* getInstance();
	void setHwnd(HWND hwnd);
	void load(char* pdata, int size, int pos = 0, bool bPlay = true);

private:
	void free();

	void setPosition(int num);

	int getNowPostion();

	LPDIRECTSOUNDBUFFER m_pPrimaryBuffer = nullptr;
	int m_size;
	bool bLoad = false;
	HWND _hwnd = nullptr;
};
