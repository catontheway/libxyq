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

		Description:		风魂++ 几何函数
 		Original Author:	云风
		Authors:
		Create Time:		2001/1/17
		Modify Time:		2001/11/13

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
 
#ifndef _WINDSOUL_GEOMETRY_H
#define _WINDSOUL_GEOMETRY_H
 
#include "windsoul.h"

#define BLIT_XOR	0x4

struct WLineStruct;
struct WBoxStruct;

class WINDSOUL_API WLine : public WObject { 
	WLine(const WLine& line);							// 空函数,不能拷贝构造
	WLine& operator=(const WLine& Line);
public:
	WLine(int x=0,int y=0,WPixel color=0);
	~WLine();

	int GetW() const;
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WLineStruct *GetLineStruct() const { return reinterpret_cast<WLineStruct *>(objdata); }	// 获取数据结构
	bool Affect(int x,int y) const;						// 判断对象是否影响 Canvas 块
	WLine& Color(WPixel color);							// 换颜色
	WLine& Size(int x,int y);							// 换大小
	void SetUserData(DWORD userdata) const;				// 设置用户数据
	const WLine& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
};

class WINDSOUL_API WBox : public WObject {
	WBox(const WBox& box);								// 空函数,不能拷贝构造
	WBox& operator=(const WBox& box);
public:
	WBox(int w=0,int h=0,WPixel color=0);
	~WBox();

	int GetW() const;
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WBoxStruct *GetBoxStruct() const { return reinterpret_cast<WBoxStruct *>(objdata); }	// 获取数据结构
	WBox& Color(WPixel color);							// 换颜色
	WBox& Size(int w,int h);							// 换大小
	void SetUserData(DWORD userdata) const;				// 设置用户数据
	const WBox& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
};

inline WORD PixelAlphaBlending(DWORD x,DWORD y,int alpha)
{
	DWORD result;
    x = ((x&0xFFFF) | (x<<16)) & 0x7E0F81F;
    y = ((y&0xFFFF) | (y<<16)) & 0x7E0F81F;

    result = ((y - x) * alpha / 32 + x) & 0x7E0F81F;
    return (WORD)((result&0xFFFF) | (result>>16));
}
  
#endif