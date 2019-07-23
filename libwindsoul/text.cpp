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

		Description:		文字输出(简单ASCII)
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/20
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include "windsoul.h"
#include <string.h>
//#include "wsstring.h"
#include "bmpmem.h"
#include "textint.h"

WObjStruct* WText::Duplicate(WObjectHeap* heap) const
{
	return new(heap)WTextStruct(*GetTextStruct());
}

#ifndef _DISABLE_WINDSOUL_NEW
	#define new debug_new
#endif

extern "C" void _stdcall _draw_ascii(WBmpStruct *bmp,char c);

WTextStruct::WTextStruct(const char *s)
{
	string=s;
	width=strlen(s)*7;
}

static WSERR _draw_str(WBmpStruct *bmp,const char *s)
{
	int i;
	int x=bmp->kx,y=bmp->ky;
	for (i=0;s[i];i++,bmp->kx+=7) {
		if (s[i]<33) continue;
		_draw_ascii(bmp,s[i]);
	}
	bmp->kx=x,bmp->ky=y;
	return WS_OK;
}

void WBitmap::Draw(const char *s,WPixel color)
{
	SetUserData(color.color);
	_draw_str(GetBmpStruct(),s);
}

/*
WTextStruct& WTextStruct::operator=(const WTextStruct& data)
{
	kx=data.kx,ky=data.ky,
	color=data.color;
	string=data.string;
	return *this;
}
*/
WText::WText(const char *s)
{
	WTextStruct *data;
	data=new WTextStruct(s);
//	WString tmp=data->string;
	data->kx=data->ky=0;
	SetData(data);
}

/*
void WText::Unlock()
{
	WTextStruct *data=GetTextStruct();
	data->string.Empty();
}
*/
WSERR _stdcall _draw_text(WBmpStruct *bmp,const WTextStruct *text)
{
	int i;
	const char *s=text->string;
	bmp->userdata=text->color.color;
	bmp->kx-=text->kx,bmp->ky-=text->ky;
	for (i=0;s[i];i++,bmp->kx+=7) {
		if (s[i]<33) continue;
		_draw_ascii(bmp,s[i]);
	}
	bmp->kx-=i*7-text->kx;
	bmp->ky+=text->ky;
	return WS_OK;
}

BLIT_FUNC WText::DrawFunc(DWORD style) const
{
	return (BLIT_FUNC)_draw_text;
}




