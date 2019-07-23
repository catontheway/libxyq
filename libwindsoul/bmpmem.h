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

		Description:		位图内存管理头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/9/15
		Modify Time:		2001/9/8

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_BMPMEM_H
#define _WINDSOUL_BMPMEM_H

#include <windows.h>
#include <ddraw.h>
#include "windsoul.h"

#define MAXOBJECTSTRUCTSIZE 40

struct WBmpData : public memory<WBmpData> {
//	int times;								// 引用次数
	union {
		HBITMAP hBmp;						// 位图句柄
		HGLOBAL hMem;						// 内存句柄
		LPDIRECTDRAWSURFACE lpDS;			// DirectDraw Surface
		void *lpMem;						// 内存指针
	};
	void (*destroy)(DWORD ptr);				// 释放函数
public:
//	WBmpData() : times(0) {}
	~WBmpData() { destroy((DWORD)lpMem); }
	static void destroy_lpMem(DWORD ptr);	// 释放 lpMem
	static void destroy_hBmp(DWORD ptr);	// 释放 hBmp
};

/*
inline WBmpData::~WBmpData() 
{
//	if (!lpMem) return;
// 在释放 BMP MemPage 的时候, 所有的 times 都是 0, 这里不会运行
	if (--times==0) {
		destroy((DWORD)lpMem);
//		MEMORY::bmp_data.free(this);
	}
//	lpMem=0;
}
*/

#endif