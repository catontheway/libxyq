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

		Description:		风魂 Alpha 通道内部头文件
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/9
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_ALPHACHANNEL_INTERNAL_H
#define _WINDSOUL_ALPHACHANNEL_INTERNAL_H
 
struct WBmpData;
struct WChannelData;

struct WAlphaBmpStruct : public WBmpStruct, memory<WAlphaBmpStruct> {
	BYTE *channel;							// Alpha 通道
	void *cmem;								// Alpha 通道内存块

	WAlphaBmpStruct() {}
	WAlphaBmpStruct (const WAlphaBmpStruct&);

	~WAlphaBmpStruct();
	using memory<WAlphaBmpStruct>::operator new;
	using memory<WAlphaBmpStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WAlphaBmpStruct& operator=(const WAlphaBmpStruct& abmp);

	void Empty() { w=h=0,ptr=0,mem=0; }		// 清空结构
};

#endif
