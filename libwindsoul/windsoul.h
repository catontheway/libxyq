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

		Description:		风魂头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/8
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_H_
#define _WINDSOUL_H_
// 
// #ifdef _BCB
//     #ifndef _LIB
//         #pragma comment (lib,"wpp16.lib")
//     #endif        
//     #define WINDSOUL_API
// #else
// 
// #if defined(WINDSOUL_STATICLIB) || defined(_LIB) || defined(_API)
// 	#define WINDSOUL_API
// 	#if !defined(_LIB) && !defined(_API)
// 		#ifdef _DEBUG
// 	   		#pragma comment (lib,"wsstaticd.lib")
// 		#else
//        		#pragma comment (lib,"wsstatic.lib")
//   		#endif
// 	#endif
// #elif defined(WINDSOUL_EXPORTS)
// 	#define WINDSOUL_API __declspec(dllexport)
// #else
// 	#define WINDSOUL_API __declspec(dllimport)
//     #ifdef _DEBUG
// 	   	#pragma comment (lib,"wsdebug.lib")
//     #else
//        	#pragma comment (lib,"windsoul.lib")
//   	#endif
// #endif
// 
// #endif

#define WINDSOUL_API

typedef unsigned long WSERR;

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef DWORD
typedef unsigned long DWORD;
#endif

// #ifndef QWORD
// typedef __int64 QWORD;
// #endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef _WINDEF_
#define HDC DWORD
#define HBITMAP DWORD
#define HINSTANCE DWORD
#define HANDLE DWORD
#define HWND DWORD
#endif

#ifndef WINAPI
#define WINAPI      __stdcall
#endif

#ifndef CALLBACK
#define CALLBACK    __stdcall
#endif

#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif

#include "wsmemory.h"

// Canvas 块的大小
#define WCANVASBLOCKW	64
#define WCANVASBLOCKH	32

#include "wserror.h"
#include "wsbitmap.h"
#include "wshelper.h"

#endif