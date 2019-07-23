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

		Description:		风魂位图 GDI 部分
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/13
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include "windsoul.h"

static int BMPINFO16[13]={
	sizeof(BITMAPINFOHEADER),
	0,	// 宽度
	0,	// 高度
	0x100001,BI_BITFIELDS,0,0,0,0,0,
	0xf800,0x7e0,0x1f
};

WSERR WBitmap::Blit2DC(HDC hDC,int x,int y,int offset) const
{
	WBmpStruct *data=GetBmpStruct();
	if (data==0) return WS_OK;
	BMPINFO16[1]=data->pitch>>1,BMPINFO16[2]=-data->h;
	if (SetDIBitsToDevice(hDC,x,y,data->w,data->h,offset,0,0,data->h,(LPVOID)((unsigned)(data->ptr)-offset*2),(BITMAPINFO*)&(BMPINFO16[0]),0)==0) 
		return WS_GDIBLITFAIL;
	return WS_OK;
}

WSERR WBitmap::Blit2DC(HDC hDC,int dx,int dy,int x,int y,int w,int h) const
{
	WBmpStruct *data=GetBmpStruct();
	if (data==0) return WS_OK;
	BMPINFO16[1]=data->pitch>>1,BMPINFO16[2]=-h;
	if (SetDIBitsToDevice(hDC,dx,dy,w,h,x,0,0,h,(LPVOID)((unsigned)data->ptr+data->pitch*y),(BITMAPINFO*)&(BMPINFO16[0]),0)==0) 
		return WS_GDIBLITFAIL;
	return WS_OK;
}
