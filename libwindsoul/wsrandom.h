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

		Description:		随机数
 		Original Author:	云风
		Authors:
		Create Time:		2001/7/18
		Modify Time:		2001/10/28

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_RANDOM_H
#define _WINDSOUL_RANDOM_H

#pragma once

#include "wsaddon.h"

class WINDSOULADD_API WRandom {
	enum { Number=0x1000 };
	unsigned long *m_Buffer;
	unsigned long m_Seed;
	unsigned m_Ptr;

	void Batch();
public:
	WRandom();
	~WRandom();

	void Seed(unsigned long seed);	// 固定种子
	unsigned long Seed();					// 随机种子

	unsigned short GetWord();		// 读一个 Word
	unsigned long GetDWord();		// 读一个 DWord
};

#endif