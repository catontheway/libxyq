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

		Description:		菱形地块
 		Original Author:	云风
		Authors:
		Create Time:		2001/10/14
		Modify Time:		20001/10/29

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
 
#ifndef _WINDSOUL_LOZENGE_H
#define _WINDSOUL_LOZENGE_H

#pragma once

#include "wsaddon.h"
 
struct WLozengeStruct;
        
class WINDSOULADD_API WLozenge : public WObject {
public:      
	WLozenge(WPixel color=0,int size=16);
	WLozenge(const WBitmap &father,int x,int y,int size=16);
	WLozenge(const WLozenge &);
	~WLozenge();

	const WLozenge& operator=(const WLozenge&);
	WSERR Create(WPixel color=0,int size=16);						// 创建纯色的菱形地块
	WSERR Create(const WBitmap &father,int x,int y,int size=16);	// 从一个位图中创建出菱形地块
    
	int GetW() const;
	int GetH() const;

	void SetUserData(DWORD userdata) const ;	// 设置用户数据(颜色)
	BLIT_FUNC DrawFunc(DWORD style) const;	// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WLozengeStruct *GetLozengeStruct() const { return reinterpret_cast<WLozengeStruct *>(objdata); }	// 获取数据结构
};       
 
#endif