/*
 "               ..;;;;,                     ;;;,    
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
       ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
      .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
     ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
     ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
    :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
 
                        Windsoul++

                by 云风 (Cloud Wu)  1999-2001
 
		http://member.netease.com/~cloudwu 
		mailto:cloudwu@263.net
 
		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.

		Description:		风魂++ 画布支持头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/10/20
		Modify Time:		2001/10/18

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_CANVAS_H
#define _WINDSOUL_CANVAS_H

//#define _RECORD_CANVAS

#include "wstimer.h"

class WCanvasBlock;
struct WCanvasInternalData;
class WCanvas;

class WINDSOUL_API memory<WCanvas>::manager;
template class WINDSOUL_API memory<WCanvas>;

class WINDSOUL_API WCanvas : WBitmap, public memory<WCanvas> {
	WTimer m_Timer;
public:
	int m_FrameTime;
protected:
	enum WCanvasChangedTag { change_null,change_full,change_self } changed;	// 改变标记
	WCanvasInternalData *data;			// 内部数据
	WCanvasBlock *block;	// 子图块
	int row;				// 行数目
	int col;				// 列数目
	int block_x;			// 起始块 X
	int block_y;			// 起始块 Y

	friend class WSurface;

	using WBitmap::operator();
public:
	using memory<WCanvas>::operator new;
	using memory<WCanvas>::operator delete;
	WCanvas(int width,int height);
	~WCanvas();
	void Update();
	void NextFrame();		// 准备下一帧
	void SkipFrame();		// 跳过下一帧
	void Reset(int f);		// 时钟复位
	void MoveTo(int x,int y);	// 移动到 p
	void MoveTo(WPoint p) { MoveTo(p.x,p.y); }
	void Move(int x,int y);	// 移动 (x,y)
	void Move(WPoint p) { Move(p.x,p.y); }
	int GetX() const;		// 获取世界坐标 X
	int GetY() const;		// 获取世界坐标 Y
	int GetW() const;		// 获得 Canvas 的可视宽度
	int GetH() const;		// 获得 Canvas 的可视高度
	WPoint GetViewPort(int x,int y) const;	// 获取视口坐标得对应世界坐标
	WPoint GetViewPort(WPoint p) const { return GetViewPort(p.x,p.y); }
	void Clear(WPixel color);												// 清除 Canvas
	void Clear();															// Canvas 信息归 0
	WSERR Draw(const WObject &bmp, DWORD style);							// 画一张图
	WSERR DrawEx(const WObject &bmp, DWORD style);							// 画一张图(检验对象是否落在 Canvas 块内)
	void Draw(const char *str, WPixel color);								// 写 ASCII String
	void Draw(WCanvas &canvas,DWORD style=BLIT_COPY);						// 输入另一个画布
	void SetOvlRect(int w,int h);											// 添加覆盖矩形
	void SetOvlRect(const WRect &rect) { operator()(rect.x,rect.y); SetOvlRect(rect.w,rect.h); }
	WCanvas& operator() (int x,int y) { return SetPos(x,y); }				// 设置关键点
	WCanvas& operator() (WPoint p) { return SetPos(p.x,p.y); }				// 设置关键点
	WCanvas& SetPos(int x,int y);											// 设置关键点
	WCanvas& SetPos(WPoint p) { return SetPos(p.x,p.y); }
	WCanvas& AddPos(int x,int y);											// 设置关键点
	WCanvas& AddPos(WPoint p) { return AddPos(p.x,p.y); }
	WCanvas& ViewPort(int x,int y);											// 设置视口关键点
	WCanvas& ViewPort(WPoint p) {return ViewPort(p.x,p.y); }				// 设置视口关键点
	WCanvas& UnChange() { changed=change_null; return *this; }	// 设置画布状态为相对上帧不变更
	WCanvas& Change() { changed=change_full; return *this; }	// 设置画布状态为相对上帧变更
	WCanvas& SelfChange() { changed=change_self; return *this; }	//  设置画布状态为相对上帧自身变更
	const WCanvas& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
	bool IsMoved() const;					// 是否移动
	bool IsChanged() const { return (changed!=change_null); }
	void Update2DC(HDC hDC,int x,int y) const;		// 重新刷新一次到 DC
	void Blit2DC(HDC hDC,int x,int y);      		// 绘制到 DC
	void BlitTo(WBitmap &bmp);						// copy 到位图
	void Blit(HDC hDC,int x,int y);					// Blit 一帧
	void SleepFrame();								// 等待到这帧时间结束
	void Laptop(bool Set=true);						// 设置笔记本模式

#ifdef _RECORD_CANVAS
	void Record(const char* path="d:/record");
#endif

	using WBitmap::SetUserData;
}; 

#endif
