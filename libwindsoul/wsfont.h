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

		Description:		风魂 Windows 字体支持
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/12
		Modify Time:		2001/11/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_FONT_H
#define _WINDSOUL_FONT_H
 
#ifndef _WINDOWS_
#error Include windows.h first!
#endif

#include "wsbitmap.h"

#define FONT_ALPHA		0
#define FONT_NOALPHA	1

struct WFontData; 
struct WCharStruct;
class WCanvas;

 ///	字体
/////////////////////////

class WINDSOUL_API WFont {
	int m_CacheSize;
	int m_CacheNum;

	struct Data {
		unsigned int c;
		int freq;
		unsigned short id;
	} *m_Data;
	WFontData *m_FontData;

	HDC m_FontDC;
	HBITMAP m_FontBmp;
	WORD *m_Buffer;
	int m_Ascent;
	int m_Height;
	int m_Locked;
	int m_Freq;
	int m_Alpha;
	int m_MaxWidth;
private: 
	int SearchChar(unsigned int c) const;	// 在 Cache 里搜索一个字符
	void ExpandCacheSize(int newsize);		// 扩展 CacheSize
public:
	WFont() : m_CacheSize(0), m_Height(0) {}
	WFont(HFONT font,int alpha=16, int cachesize=128) : m_CacheSize(0) { Create(font,alpha,cachesize); }
	~WFont() { Destroy(); }

	WSERR Create(HFONT,int alpha=16,int cachesize=128);	// 从 HFONT 中创建字体
	void Destroy();									// 销毁字体
	WFontData *GetChar(unsigned int c);				// 获取一个字的数据(内部使用)
	int GetHeight() const { return m_Height; }		// 获取字体高度
 
	void Lock() { m_Locked=m_Freq+1; }				// Lock Cache Buffer (不可删减)
	void Unlock() { m_Locked=0; }					// Unlock Cache Buffer
	DWORD BestStyle() const { return (m_Alpha==0)?FONT_NOALPHA:FONT_ALPHA; }
   
	DWORD GetLength(const char *str);
	void Draw(WBitmap &buffer,const char *str,WPixel color, DWORD style=FONT_ALPHA);		// 输出字符串
	void Draw(WCanvas &buffer,const char *str,WPixel color, DWORD style=FONT_ALPHA)	{
		Draw(*reinterpret_cast<WBitmap*>(&buffer),str,color,style);
	}
};   
         
 ///	字符对象 
/////////////////////////
  
class WINDSOUL_API WChar : public WObject {
public:
	WChar() {} 
	WChar(WFont &font,unsigned int c,WPixel color) { Create(font,c,color); }
	~WChar() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WCharStruct *GetCharStruct() const { return reinterpret_cast<WCharStruct *>(objdata); }	// 获取数据结构
	WSERR Create(WFont &,unsigned int c,WPixel color);	// 创建字符
	void Destroy();										// 销毁
	int GetW() const;									// 取宽度
	int GetH() const;									// 取高度
	int GetWidth() const;								// 取字宽
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
};
 
#endif
