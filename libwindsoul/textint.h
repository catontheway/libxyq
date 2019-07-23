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

		Description:		风魂ASCII处理内部头文件
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/23
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_TEXT_INTERNAL_H
#define _WINDSOUL_TEXT_INTERNAL_H

struct WTextStruct : public WObjStruct, memory<WTextStruct> {
	const char *string;						// 字符串
	WPixel color;							// 额外数据
	unsigned width;							// 宽度

	WTextStruct(const char *s);
	WTextStruct() {}
	WTextStruct(const WTextStruct& text) { string=text.string,color=text.color,width=text.width; }
	using memory<WTextStruct>::operator new;
	using memory<WTextStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WTextStruct& operator=(const WTextStruct&);
};
 
class WText : public WObject {
public:
	WText(const char *s);
	~WText() { delete GetTextStruct(); }

	int GetW() const { return GetTextStruct()->width; }
	int GetH() const { return 12; }
//	void Unlock();										// 解锁引用数据区
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WTextStruct *GetTextStruct() const { return reinterpret_cast<WTextStruct *>(objdata); }	// 获取数据结构
};

#endif
