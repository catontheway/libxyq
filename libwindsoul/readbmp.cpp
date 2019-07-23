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

		Description:		读位图
 		Original Author:	云风
		Authors:
		Create Time:		2000/10/16
		Modify Time:		2001/11/21

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include "windsoul.h"

//#include "wsjpeg.h"
#define new debug_new

#pragma pack (push)
#pragma pack (2)

struct BITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    DWORD   Reserved;
    DWORD   bfOffBits;
};

struct BITMAPINFOHEADER {
	DWORD  biSize;
    long   biWidth;
    long   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    long   biXPelsPerMeter;
    long   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
};

#pragma pack (pop)

WSERR WBitmap::Load(void * bmpdata)
{
	int width,height;
	WPixel *bmppix;
	BITMAPFILEHEADER *bf=(BITMAPFILEHEADER *)bmpdata;
#ifdef _WINDSOUL_JPEG_H_
	WORD type=*(const WORD *)bmpdata;
	if (type==0xd8ff) return _load_jpeg(this,bmpdata);
#endif
	if (bf->bfType!=19778/*'MB'*/) return WS_INVALIDBMPFILE;
	BITMAPINFOHEADER *bi=(BITMAPINFOHEADER *)((DWORD)bmpdata+sizeof(BITMAPFILEHEADER));
	if (objdata==0) Create(bi->biWidth,bi->biHeight);
	WBmpStruct *data=GetBmpStruct();
	width=MIN(data->w,(int)bi->biWidth);
	height=MIN(data->h,(int)bi->biHeight);

	switch (bi->biBitCount) {
	case 8: {
		WPixel pal[256];
		int p=(bi->biWidth+3)&0xfffffffc;
		BYTE *bits=(BYTE*)((DWORD)bf+bf->bfOffBits+p*(bi->biHeight-height));
		int i,j,usrcolor=bi->biClrUsed;
		DWORD *color=(DWORD *)((DWORD)bi+bi->biSize);
		if (usrcolor==0) usrcolor=256;
		for (i=0;i<usrcolor;i++)
			pal[i]=color[i];
		bmppix=(*this)[height-1];
		for (i=0;i<height;i++,bits+=p,bmppix=(*this)[height-1-i])
			for (j=0;j<width;j++)
				bmppix[j]=pal[bits[j]];
		}
		break;
	case 16: {
		int p=((bi->biWidth*2+3)&0xfffffffc)/2;
		short *bits=(short*)((DWORD)bf+bf->bfOffBits+p*(bi->biHeight-height));
		int i,j;
		bmppix=(*this)[height-1];
		for (i=0;i<height;i++,bits+=p,bmppix=(*this)[height-1-i])
			for (j=0;j<width;j++)
				bmppix[j].color=bits[j];
		}
		break;
	case 24: {
		int p=(bi->biWidth*3+3)&0xfffffffc;
		DWORD bits=(DWORD)bf+bf->bfOffBits+p*(bi->biHeight-height);
		int i,j;
		bmppix=(*this)[height-1];
		for (i=0;i<height;i++,bits+=p,bmppix=(*this)[height-1-i])
			for (j=0;j<width;j++)
				bmppix[j]=*(DWORD*)(bits+j*3);
		}
		break;
	default:
		return WS_INVALIDBMPTYPE;
	}
	return WS_OK;
}

#include <stdio.h>

WSERR WBitmap::Save(const char *filename) const
{
	FILE * f;
	BITMAPFILEHEADER bithead;
	BITMAPINFOHEADER bitinfo;
	int headsize,linesize,i,j,s;
	DWORD color;

	linesize=(GetW()*3+3)&0xfffffffc;
	s=linesize-GetW()*3;
	if((f=fopen(filename,"wb"))==NULL) return WS_CANTOPEN;
	headsize=sizeof(bithead)+sizeof(bitinfo);
	bithead.bfType='MB';
	bithead.bfSize=headsize+linesize*GetH();
	bithead.Reserved=0;
	bithead.bfOffBits=headsize;
	fwrite(&bithead,1,sizeof(bithead),f);
	bitinfo.biSize=sizeof(bitinfo);
	bitinfo.biWidth=GetW();
	bitinfo.biHeight=GetH();
	bitinfo.biPlanes=1;
   bitinfo.biBitCount=24;
	bitinfo.biCompression=0;
	bitinfo.biSizeImage=0;
   bitinfo.biXPelsPerMeter=72;
	bitinfo.biYPelsPerMeter=72;
	bitinfo.biClrUsed=0;
   bitinfo.biClrImportant=0;
	fwrite(&bitinfo,1,sizeof(bitinfo),f);

	for(i=GetH()-1;i>=0;i--){
		for(j=0;j<GetW();j++){
			color=(DWORD)(*this)[i][j];
			fwrite(&color,1,3,f);
		}
		fwrite(&color,1,s,f);
	}
	fclose(f);
	return WS_OK;
}
