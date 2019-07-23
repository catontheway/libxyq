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

		Description:		RichText 类
 		Original Author:	云风
		Authors:
		Create Time:		2001/11/15
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
  
#ifndef _WINDSOUL_RICHTEXT_H_
#define _WINDSOUL_RICHTEXT_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"
#include "wsstring.h"
#include "wscanvas.h"
#include "wsprite.h"

#pragma warning( disable : 4251 )

class WFont;
struct WRichTextArray;

class WINDSOULADD_API WRichText {
	WString m_Text;
	int m_MaxLines;
	int m_Lines;
	WString *m_Line;			// 每行的展开文字
	WRichTextArray &m_Array;	// 数据数组

	WPixel m_Color;
	WFont *m_Font;

	void IncreaseLines();		// 增加行数
	static WSpriteAni* s_Sprite;	// 表情动画
	static int s_SpriteNumber;
	static unsigned s_SpriteSpeed;
public:
	WRichText();
	WRichText(const WString &text);
	~WRichText();

	static void LoadSprite(const char *path,int speed=5);	// 读取路径

	void SetString(const WString &text) { m_Text=text; }
	const WString& GetString() const { return m_Text; } 
	int Format(WFont &font,int width);			// 按像素宽度格式化串, 返回行数
	int GetLines() const { return m_Lines; }	// 上次 Format 后的行数
	void SetColor(WPixel color) { m_Color=color; }	// 设置颜色
	void Draw(int n,WBitmap &buffer,DWORD style=0,int alpha=128);		// 输出字符串
	void Draw(int n,WCanvas &buffer,DWORD style=0,int alpha=128);
	int GetLength(int n) const;					// 获取第 n 行的宽度
	int GetHeight(int n) const;					// 获取第 n 行的高度
	int GetHeight() const;
	const WString & GetLine(int n) const { return m_Line[n]; }
	int GetWord(int n) const;
	static void Release();
};

#endif