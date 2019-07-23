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

		Description:		风魂++ DDraw Surface
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/27
		Modify Time:		2002/4/15

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_SURFACE_H
#define _WINDSOUL_SURFACE_H

#include "wscanvas.h"

struct WSurfaceData;

class WINDSOUL_API WSurface {
protected:
	HWND m_hWnd;
	WSurfaceData *data;					// Surface 的结构
	WCanvas *Canvas;
	WSERR CreateSurface();				// 创建 Surface
	WSERR RestoreSurface();				// 切换任务时恢复 Surface
	void Refresh();						// 刷新
public:
	WSurface();
	~WSurface();
	void Release();						// 释放 DirectDraw
	WSERR RestoreDesktop();				// 恢复桌面分辨率
	WSERR SetDisplay(int w,int h);		// 设置分辨率
	WSERR Create(HWND hWnd,WCanvas& canvas);// 创建显存 Surface
	WSERR Blit2Screen(int x=0,int y=0);		// 传输到屏幕
};

#endif