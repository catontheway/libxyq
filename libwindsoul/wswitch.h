#ifndef _WINDSOUL_SWITCH_H_
#define _WINDSOUL_SWITCH_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"
#include "wscanvas.h"
#include "wszoom.h"

class WINDSOULADD_API WSwitch {
protected:
	WBitmap m_Buffer;
	WCanvas *m_pCanvas;
public:
	WSwitch() { m_pCanvas=0; }
	virtual ~WSwitch() {};
	virtual void Init()=0;
	void Create(WCanvas &canvas);
	void Create(WBitmap &bitmap);
	virtual bool Draw(WCanvas *canvas=0)=0;		// 画到 canvas 上(缺省为 Create 时的 canvas)
};

class WINDSOULADD_API WSwitchFade : public WSwitch {
	int m_Alpha;
public:
	void Init() { m_Alpha=256; }
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitch4Block : public WSwitch {
	int m_Count;
	int m_Speed;
	WBitmap m_Block[4];
public:
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitchSnow : public WSwitch {
	int m_Count;
public:
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitchString : public WSwitch {
	WBitmap *m_String;
	int *m_Speed;
	int *m_Hight;
	int m_Number;
public:
	WSwitchString();
	~WSwitchString();
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitchTransString : public WSwitch {
	WBitmap *m_String;
	int m_Speed;
	int m_Count;
public:
	WSwitchTransString();
	~WSwitchTransString();
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitchZoom : public WSwitch {
	WZoomBitmap m_Zoom;
	int m_Height;
	int m_Width;
public:
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitchBlind : public WSwitch {
	WBitmap *m_String;
	int m_Number;
	int m_Count;
public:
	WSwitchBlind();
	~WSwitchBlind();
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitch2Block : public WSwitch {
	WBitmap m_Block[2];
	int m_Count;
	int m_Speed;
public:
	void Init();
	bool Draw(WCanvas *canvas=0);
};

class WINDSOULADD_API WSwitchGrey : public WSwitch {
	int m_Count;
	int m_Speed;
public:
	void Init();
	bool Draw(WCanvas *canvas=0);
};

#endif