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

		Description:		Tips 类
 		Original Author:	云风
		Authors:
		Create Time:		2001/11/13
		Modify Time:		2001/11/28

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
  
#ifndef _WINDSOUL_TIPS_H_
#define _WINDSOUL_TIPS_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"

struct WTipsStruct;
class WFont;
class WString;

class WINDSOULADD_API WTips : public WObject {
public:
	WTips() {}
	WTips(WFont &font, const char *str) { Create(font,str); }
	~WTips() { Destroy(); };
	 
	void Create(WFont &font, const char *str);
	void Destroy();
	int GetW() const;    
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WTipsStruct *GetTipsStruct() const { return reinterpret_cast<WTipsStruct *>(objdata); }	// 获取数据结构
	void SetUserData(DWORD userdata) const;				// 设置用户数据
	void SetColor(WPixel color);						// 设置颜色
	const WTips& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
};          

#endif