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

		Description:		风魂 Addon 头文件
 		Original Author:	云风
		Authors:
		Create Time:		2001/6/12
		Modify Time:		2001/10/11

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_ADDON_H_
#define _WINDSOUL_ADDON_H_

// #ifdef _BCB
//     #ifndef _LIB
//         #pragma comment (lib,"wppadd16.lib")
//     #endif        
//     #define WINDSOULADD_API
// #else
// 
// #if defined(WINDSOULADD_STATICLIB) || defined(_LIB) || defined(_API) || defined(WINDSOULADD_NODLL)
// 	#define WINDSOULADD_API
// 	#if !defined(_LIB) && !defined(_API) && !defined(WINDSOULADD_NODLL)
// 		#ifdef _DEBUG
// 	   		#pragma comment (lib,"wsaddonsd.lib")
// 		#else
// 	   		#pragma comment (lib,"wsaddons.lib")
//   		#endif
// 	#endif
// #elif defined(ADDON_EXPORTS)
// 	#define WINDSOULADD_API __declspec(dllexport)
// #else
// 	#define WINDSOULADD_API __declspec(dllimport)
//     #ifdef _DEBUG
// 	   	#pragma comment (lib,"wsaddond.lib")
//     #else
// 	   	#pragma comment (lib,"wsaddon.lib")
//   	#endif
// #endif
// 
// #endif

#define WINDSOULADD_API

#endif