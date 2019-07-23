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

		Description:		风魂 Windows 字体支持
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/12
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_FONT_INTERNAL_H
#define _WINDSOUL_FONT_INTERNAL_H

#include "windsoul.h"

struct WFontData {
	int w;									// 宽度
	int h;									// 高度
	int width;								// 字宽
	int kx;									// X 偏移
	int ky;									// Y 偏移
	int size;								// 长度
	BYTE *data;								// 实际数据
};
      
struct WCharStruct : public WObjStruct, memory<WCharStruct> {
	int w;									// 宽度
	int h;									// 高度
	BYTE *data;								// 第一扫描行指针
	WPixel color;							// 颜色
	short int width;						// 字宽(含字间距)

	WCharStruct() {}
	WCharStruct(const WCharStruct& c) {w=c.w,h=c.h,data=c.data,color=c.color;}
 	WCharStruct& operator=(const WCharStruct& c);	//无此函数
	using memory<WCharStruct>::operator new;
	using memory<WCharStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
};    
   
#endif