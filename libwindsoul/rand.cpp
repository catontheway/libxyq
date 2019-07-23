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
				
		http://www.codingnow.com 
		mailto:cloudwu@263.net
 
		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.

		Description:		随机数
 		Original Author:	云风
		Authors:
		Create Time:		2001/7/18
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include "wsrandom.h"

#define GENIUS_NUMBER 0x19790205

WRandom::WRandom()
{
	int s;
	m_Buffer=new unsigned long[Number];
	m_Ptr=Number*2;
	__asm {
		_asm _emit 0x0f _asm _emit 0x31
		mov s,eax
	}
	m_Seed=s;
}

WRandom::~WRandom()
{
	delete[] m_Buffer;
}

unsigned long WRandom::Seed()
{
	int s;
	__asm {
		_asm _emit 0x0f _asm _emit 0x31
		mov s,eax
	}
	Seed(s);
	return s;
}

void WRandom::Seed(unsigned long s)
{
	m_Seed=s^GENIUS_NUMBER;
	Batch();
}

void WRandom::Batch()
{
	__asm {
		cld
		mov edi,[ecx]WRandom.m_Buffer
		mov eax,[ecx]WRandom.m_Seed
		mov ecx,0x1000		;//WRandom::Number
		mov esi,0xE7BD2160

		ALIGN 4
_loop_circle1:
		push ecx
		mov ecx,32
_loop_circle2:
		mov ebx,eax
		shl eax,1
		and ebx,esi;	//select the bit for xor
		mov edx,ebx
		bswap ebx
		xor bx,dx
		xor bh,bl;		// because P only judge one byte
						;// so must XOR to judge the p of whole word 
		jp _next;		//jp equals the xor 
		inc eax
_next:
		dec ecx
		jnz _loop_circle2
		pop ecx
		stosd
		dec ecx
		jnz _loop_circle1
		mov ecx,this
		mov [ecx]WRandom.m_Seed,eax
	}
}

unsigned short WRandom::GetWord()
{
	if (m_Ptr>=Number*2) {
		Batch();
		m_Ptr=0;
	}
	return *((unsigned short *)m_Buffer+m_Ptr++);
}

unsigned long WRandom::GetDWord()
{
	if (m_Ptr>=Number*2-1) {
		Batch();
		m_Ptr=0;
	}
	m_Ptr+=2;
	return *(unsigned long*)((unsigned short *)m_Buffer+m_Ptr-2);
}

