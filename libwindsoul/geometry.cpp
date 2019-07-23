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

		Description:		风魂++ 几何函数
 		Original Author:	云风
		Authors:
		Create Time:		2001/1/17
		Modify Time:		2001/10/19

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include "windsoul.h"
#include "wsgeo.h"
#include "geoint.h"

WObjStruct* WLine::Duplicate(WObjectHeap* heap) const
{
	return new(heap)WLineStruct(*GetLineStruct());
}

WObjStruct* WBox::Duplicate(WObjectHeap* heap) const
{
	return new(heap)WBoxStruct(*GetBoxStruct());
}

#define new debug_new

 ///   直线
///////////////////////////////

WLine::~WLine()
{ 
	delete GetLineStruct(); 
}

int WLine::GetW() const 
{ 
	WLineStruct *data=GetLineStruct();
	return data->x+1; 
}

int WLine::GetH() const
{ 
	WLineStruct *data=GetLineStruct();
	return ABS(data->y)+1; 
}

void WLine::SetUserData(DWORD userdata) const
{
	WLineStruct *data=GetLineStruct();
	data->userdata=userdata;
}

WLine::WLine(int x,int y,WPixel color)
{
	WLineStruct *data;
	data=new WLineStruct(x,y,color);
	SetData(data);
}

WLine& WLine::Color(WPixel color)
{
	GetLineStruct()->color=color;
	return *this;
}

WLine& WLine::Size(int x,int y)
{
	WLineStruct *line=GetLineStruct();
	if (x>=0) line->kx=0,line->x=x,line->positive=true;
	else line->kx=-x,line->x=-x,line->positive=false;
	if (y>=0) line->ky=0,line->y=y;
	else line->ky=-y,line->y=-y,line->positive=!line->positive;
	return *this;
}

bool WLine::Affect(int x,int y) const
{
	WLineStruct *line=GetLineStruct();
	if (line->x==0 || line->y==0) return true;
	int x1=x,x2=x1+line->x,y1=y,y2=y1+line->y;
//	int dx = x2-x1;
//	int dy = y2-y1;
	if (line->positive) {
		int left=(y2-y1)*(-x1)/(x2-x1)+y1;
		int right=(y2-y1)*(WCANVASBLOCKW-x1)/(x2-x1)+y1;
		if ((left<WCANVASBLOCKH && right<0) || (left>=WCANVASBLOCKH && right>=0)) return false;
	}
	else {
		int left=(y2-y1)*(-x2)/(x1-x2)+y1;
		int right=(y2-y1)*(WCANVASBLOCKW-x2)/(x1-x2)+y1;
		if ((left>=0 && right>=WCANVASBLOCKH) || (left<0 && right<WCANVASBLOCKH)) return false;
	}
	return true;
}

WSERR _stdcall _draw_line_solid(WBmpStruct *bmp,const WLineStruct *line)
{
	int x1=bmp->kx-line->kx,x2=x1+line->x,y1=bmp->ky-line->ky,y2=y1+line->y;
	int dx = x2-x1;
	int dy = y2-y1;
	int i1, i2;
	int dd;
	WPixel *pixel,color;
	if (line->positive) {
		if (dx >= dy) {
			/* (x1 <= x2) && (y1 <= y2) && (dx >= dy) */
			i1 = 2 * dy;
			dd = i1 -  dx;
			i2 = dd -  dx;
			if (x2<0 || y1>=bmp->h) return WS_OK;
			if (x2>bmp->w) x2=bmp->w;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x1;

			while (x1 < x2) {
				if (x1>=0 && y1>=0)
					*pixel=color;
					
				if (dd >= 0) {
					if (++y1>=bmp->h) return WS_OK;
					pixel=(WPixel*)((DWORD)pixel+bmp->pitch);
					dd += i2;
				}
				else         
					dd += i1; 
					
				x1 ++;
				++pixel;
			 }
		 }
		 else {
			/* (x1 <= x2) && (y1 <= y2) && (dx < dy) */
			i1 = 2 * dx;
			dd = i1 -  dy;
			i2 = dd -  dy;
			if (y2<0 || x1>=bmp->w) return WS_OK;
			if (y2>bmp->h) y2=bmp->h;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x1;

			while (y1 < y2) {
				if (x1>=0 && y1>=0)
					*pixel=color;
					
				if (dd >= 0) {
					if (++x1>=bmp->w) return WS_OK;
					++pixel;
					dd += i2;
				}
				else         
					dd += i1; 
					
				y1 ++;
				pixel=(WPixel*)((DWORD)pixel+bmp->pitch);
			 }
		 }
	}
	else {
		if (dx >= dy) {
			i1 = 2 * dy;
			dd = i1 -  dx;
			i2 = dd -  dx;
			if (x2<0 || y2<0) return WS_OK;
			if (x2>bmp->w) x2=bmp->w;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y2)+x1;

			while (x1 < x2) {
				if (x1>=0 && y2<bmp->h)
					*pixel=color;
					
				if (dd >= 0) {
					if (--y2<0) return WS_OK;
					pixel=(WPixel*)((DWORD)pixel-bmp->pitch);
					dd += i2;
				}
				else         
					dd += i1; 
					
				x1 ++;
				++pixel;
			 }
		 }
		 else {
			i1 = 2 * dx;
			dd = i1 -  dy;
			i2 = dd -  dy;
			if (y1>=bmp->h || x1>=bmp->w) return WS_OK;
			if (y1<0) y1=0;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y2)+x1;

			while (y2 > y1) {
				if (x1>=0 && y2<bmp->h)
					*pixel=color;
					
				if (dd >= 0) {
					if (++x1>=bmp->w) return WS_OK;
					++pixel;
					dd += i2;
				}
				else         
					dd += i1; 
					
				y2 --;
				pixel=(WPixel*)((DWORD)pixel-bmp->pitch);
			 }
		 }
	}
	return WS_OK;
}

WSERR _stdcall _draw_hline_solid(WBmpStruct *bmp,const WLineStruct *line)
{
	int y=bmp->ky-line->ky;
	int x1,x2;
	WPixel *pixel,color;
	if (y<0 || y>=bmp->h) return WS_OK;
	color=line->color;
	x1=bmp->kx-line->kx,x2=x1+line->x;
	if (x1<0) x1=0;
	if (x2>=bmp->w) x2=bmp->w;
	pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y)+x1;
	for (;x1<x2;x1++,++pixel)
		*pixel=color;
	return WS_OK;
}

WSERR _stdcall _draw_vline_solid(WBmpStruct *bmp,const WLineStruct *line)
{
	int x=bmp->kx-line->kx;
	int y1,y2;
	WPixel *pixel,color;
	if (x<0 || x>=bmp->w) return WS_OK;
	color=line->color;
	y1=bmp->ky-line->ky,y2=y1+line->y;
	if (y1<0) y1=0;
	if (y2>=bmp->h) y2=bmp->h;
	pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x;
	for (;y1<y2;y1++,pixel=(WPixel*)((DWORD)pixel+bmp->pitch))
		*pixel=color;
	return WS_OK;
}

WSERR _stdcall _draw_line_trans(WBmpStruct *bmp,const WLineStruct *line)
{
	int x1=bmp->kx-line->kx,x2=x1+line->x,y1=bmp->ky-line->ky,y2=y1+line->y;
	int dx = x2-x1;
	int dy = y2-y1;
	int i1, i2;
	int dd;
	int alpha=line->userdata>>3;
	WPixel *pixel,color;
	if (line->positive) {
		if (dx >= dy) {
			/* (x1 <= x2) && (y1 <= y2) && (dx >= dy) */
			i1 = 2 * dy;
			dd = i1 -  dx;
			i2 = dd -  dx;
			if (x2<0 || y1>=bmp->h) return WS_OK;
			if (x2>bmp->w) x2=bmp->w;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x1;

			while (x1 < x2) {
				if (x1>=0 && y1>=0)
					pixel->color=PixelAlphaBlending(pixel->color,color.color,alpha);
					
				if (dd >= 0) {
					if (++y1>=bmp->h) return WS_OK;
					pixel=(WPixel*)((DWORD)pixel+bmp->pitch);
					dd += i2;
				}
				else         
					dd += i1; 
					
				x1 ++;
				++pixel;
			 }
		 }
		 else {
			/* (x1 <= x2) && (y1 <= y2) && (dx < dy) */
			i1 = 2 * dx;
			dd = i1 -  dy;
			i2 = dd -  dy;
			if (y2<0 || x1>=bmp->w) return WS_OK;
			if (y2>bmp->h) y2=bmp->h;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x1;

			while (y1 < y2) {
				if (x1>=0 && y1>=0)
					pixel->color=PixelAlphaBlending(pixel->color,color.color,alpha);
					
				if (dd >= 0) {
					if (++x1>=bmp->w) return WS_OK;
					++pixel;
					dd += i2;
				}
				else         
					dd += i1; 
					
				y1 ++;
				pixel=(WPixel*)((DWORD)pixel+bmp->pitch);
			 }
		 }
	}
	else {
		if (dx >= dy) {
			i1 = 2 * dy;
			dd = i1 -  dx;
			i2 = dd -  dx;
			if (x2<0 || y2<0) return WS_OK;
			if (x2>bmp->w) x2=bmp->w;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y2)+x1;

			while (x1 < x2) {
				if (x1>=0 && y2<bmp->h)
					pixel->color=PixelAlphaBlending(pixel->color,color.color,alpha);
					
				if (dd >= 0) {
					if (--y2<0) return WS_OK;
					pixel=(WPixel*)((DWORD)pixel-bmp->pitch);
					dd += i2;
				}
				else         
					dd += i1; 
					
				x1 ++;
				++pixel;
			 }
		 }
		 else {
			i1 = 2 * dx;
			dd = i1 -  dy;
			i2 = dd -  dy;
			if (y1>=bmp->h || x1>=bmp->w) return WS_OK;
			if (y1<0) y1=0;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y2)+x1;

			while (y2 > y1) {
				if (x1>=0 && y2<bmp->h)
					pixel->color=PixelAlphaBlending(pixel->color,color.color,alpha);
					
				if (dd >= 0) {
					if (++x1>=bmp->w) return WS_OK;
					++pixel;
					dd += i2;
				}
				else         
					dd += i1; 
					
				y2 --;
				pixel=(WPixel*)((DWORD)pixel-bmp->pitch);
			 }
		 }
	}
	return WS_OK;
}

WSERR _stdcall _draw_hline_trans(WBmpStruct *bmp,const WLineStruct *line)
{
	int y=bmp->ky-line->ky;
	int x1,x2;
	int alpha=line->userdata>>3;
	WPixel *pixel,color;
	if (y<0 || y>=bmp->h) return WS_OK;
	color=line->color;
	x1=bmp->kx-line->kx,x2=x1+line->x;
	if (x1<0) x1=0;
	if (x2>=bmp->w) x2=bmp->w;
	pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y)+x1;
	for (;x1<x2;x1++,++pixel)
		pixel->color=PixelAlphaBlending(pixel->color,color.color,alpha);
	return WS_OK;
}

WSERR _stdcall _draw_vline_trans(WBmpStruct *bmp,const WLineStruct *line)
{
	int x=bmp->kx-line->kx;
	int y1,y2;
	int alpha=line->userdata>>3;
	WPixel *pixel,color;
	if (x<0 || x>=bmp->w) return WS_OK;
	color=line->color;
	y1=bmp->ky-line->ky,y2=y1+line->y;
	if (y1<0) y1=0;
	if (y2>=bmp->h) y2=bmp->h;
	pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x;
	for (;y1<y2;y1++,pixel=(WPixel*)((DWORD)pixel+bmp->pitch))
		pixel->color=PixelAlphaBlending(pixel->color,color.color,alpha);
	return WS_OK;
}

WSERR _stdcall _draw_line_xor(WBmpStruct *bmp,const WLineStruct *line)
{
	int x1=bmp->kx-line->kx,x2=x1+line->x,y1=bmp->ky-line->ky,y2=y1+line->y;
	int dx = x2-x1;
	int dy = y2-y1;
	int i1, i2;
	int dd;
	int alpha=line->userdata>>3;
	WPixel *pixel,color;
	if (line->positive) {
		if (dx >= dy) {
			/* (x1 <= x2) && (y1 <= y2) && (dx >= dy) */
			i1 = 2 * dy;
			dd = i1 -  dx;
			i2 = dd -  dx;
			if (x2<0 || y1>=bmp->h) return WS_OK;
			if (x2>bmp->w) x2=bmp->w;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x1;

			while (x1 < x2) {
				if (x1>=0 && y1>=0)
					pixel->color^=color.color;
					
				if (dd >= 0) {
					if (++y1>=bmp->h) return WS_OK;
					pixel=(WPixel*)((DWORD)pixel+bmp->pitch);
					dd += i2;
				}
				else         
					dd += i1; 
					
				x1 ++;
				++pixel;
			 }
		 }
		 else {
			/* (x1 <= x2) && (y1 <= y2) && (dx < dy) */
			i1 = 2 * dx;
			dd = i1 -  dy;
			i2 = dd -  dy;
			if (y2<0 || x1>=bmp->w) return WS_OK;
			if (y2>bmp->h) y2=bmp->h;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x1;

			while (y1 < y2) {
				if (x1>=0 && y1>=0)
					pixel->color^=color.color;
					
				if (dd >= 0) {
					if (++x1>=bmp->w) return WS_OK;
					++pixel;
					dd += i2;
				}
				else         
					dd += i1; 
					
				y1 ++;
				pixel=(WPixel*)((DWORD)pixel+bmp->pitch);
			 }
		 }
	}
	else {
		if (dx >= dy) {
			i1 = 2 * dy;
			dd = i1 -  dx;
			i2 = dd -  dx;
			if (x2<0 || y2<0) return WS_OK;
			if (x2>bmp->w) x2=bmp->w;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y2)+x1;

			while (x1 < x2) {
				if (x1>=0 && y2<bmp->h)
					pixel->color^=color.color;
					
				if (dd >= 0) {
					if (--y2<0) return WS_OK;
					pixel=(WPixel*)((DWORD)pixel-bmp->pitch);
					dd += i2;
				}
				else         
					dd += i1; 
					
				x1 ++;
				++pixel;
			 }
		 }
		 else {
			i1 = 2 * dx;
			dd = i1 -  dy;
			i2 = dd -  dy;
			if (y1>=bmp->h || x1>=bmp->w) return WS_OK;
			if (y1<0) y1=0;
			color=line->color;
			pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y2)+x1;

			while (y2 > y1) {
				if (x1>=0 && y2<bmp->h)
					pixel->color^=color.color;
					
				if (dd >= 0) {
					if (++x1>=bmp->w) return WS_OK;
					++pixel;
					dd += i2;
				}
				else         
					dd += i1; 
					
				y2 --;
				pixel=(WPixel*)((DWORD)pixel-bmp->pitch);
			 }
		 }
	}
	return WS_OK;
}

WSERR _stdcall _draw_hline_xor(WBmpStruct *bmp,const WLineStruct *line)
{
	int y=bmp->ky-line->ky;
	int x1,x2;
	int alpha=line->userdata>>3;
	WPixel *pixel,color;
	if (y<0 || y>=bmp->h) return WS_OK;
	color=line->color;
	x1=bmp->kx-line->kx,x2=x1+line->x;
	if (x1<0) x1=0;
	if (x2>=bmp->w) x2=bmp->w;
	pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y)+x1;
	for (;x1<x2;x1++,++pixel)
		pixel->color^=color.color;
	return WS_OK;
}

WSERR _stdcall _draw_vline_xor(WBmpStruct *bmp,const WLineStruct *line)
{
	int x=bmp->kx-line->kx;
	int y1,y2;
	int alpha=line->userdata>>3;
	WPixel *pixel,color;
	if (x<0 || x>=bmp->w) return WS_OK;
	color=line->color;
	y1=bmp->ky-line->ky,y2=y1+line->y;
	if (y1<0) y1=0;
	if (y2>=bmp->h) y2=bmp->h;
	pixel=(WPixel*)((DWORD)bmp->ptr+bmp->pitch*y1)+x;
	for (;y1<y2;y1++,pixel=(WPixel*)((DWORD)pixel+bmp->pitch))
		pixel->color^=color.color;
	return WS_OK;
}

BLIT_FUNC WLine::DrawFunc(DWORD style) const
{
	WLineStruct *data=GetLineStruct();
	switch (style) {
	case BLIT_TRANS:
		if (data->y==0) {
			return (BLIT_FUNC)_draw_hline_trans;
		}
		if (data->x==0) {
			return (BLIT_FUNC)_draw_vline_trans;
		}
		return (BLIT_FUNC)_draw_line_trans;
	case BLIT_XOR:
		if (data->y==0) {
			return (BLIT_FUNC)_draw_hline_xor;
		}
		if (data->x==0) {
			return (BLIT_FUNC)_draw_vline_xor;
		}
		return (BLIT_FUNC)_draw_line_xor;
	default:
		if (data->y==0) {
			return (BLIT_FUNC)_draw_hline_solid;
		}
		if (data->x==0) {
			return (BLIT_FUNC)_draw_vline_solid;
		}
		return (BLIT_FUNC)_draw_line_solid;
	}
}

 ///   实心的矩形
///////////////////////////////

extern "C" {
	WSERR _stdcall _box16(WBmpStruct* bmp,const WBoxStruct *);
	WSERR _stdcall _trans_box16(WBmpStruct *,const WBoxStruct *);
	WSERR _stdcall _grey_box16(WBmpStruct *,const WBoxStruct *);
}

static BLIT_FUNC _box_func[6]={
	(BLIT_FUNC)_box16,						// BLIT_COPY
	0,0,
	(BLIT_FUNC)_trans_box16,				// BLIT_TRANS
	0,
	(BLIT_FUNC)_grey_box16,					// BLIT_BACK
};		

WBox::~WBox()
{ 
	delete GetBoxStruct(); 
}

int WBox::GetW() const 
{ 
	WBoxStruct *data=GetBoxStruct();
	return data->w; 
}

int WBox::GetH() const
{ 
	WBoxStruct *data=GetBoxStruct();
	return data->h; 
}

void WBox::SetUserData(DWORD userdata) const
{
	WBoxStruct *data=GetBoxStruct();
	data->userdata=userdata;
}

WBox::WBox(int w,int h,WPixel color)
{
	WBoxStruct *data;
	data=new WBoxStruct(w,h,color);
	SetData(data);
}

WBox& WBox::Color(WPixel color)
{
	GetBoxStruct()->color=color;
	return *this;
}

WBox& WBox::Size(int w,int h)
{
	WBoxStruct *box=GetBoxStruct();
	box->w=w;
	box->h=h;
	return *this;
}

BLIT_FUNC WBox::DrawFunc(DWORD style) const
{
	ASSERT(style<6);
	BLIT_FUNC blit=(BLIT_FUNC)_box_func[style];
	if (blit==0) return 0;
	return blit;
}

WSERR _stdcall _grey_box16(WBmpStruct *bmp,const WBoxStruct *box)
{
	int x=bmp->kx-box->kx;
	int y=bmp->ky-box->ky;
	int w=box->w,h=box->h;
	if (x<0) w+=x,x=0;
	if (y<0) h+=y,y=0;
	if (x+w>bmp->w) w=bmp->w-x;
	if (y+h>bmp->h) h=bmp->h-y;
	if (w<=0 || h<=0) return WS_OK;

	DWORD pitch=bmp->pitch/2-w;
	WPixel *p=(WPixel *)((DWORD)(bmp->ptr)+bmp->pitch*y+x*2);
	for (int i=0;i<h;i++) {
		for (int j=0;j<w;j++,++p) {
			int bw=(p->red*38+p->green*37+p->blue*16)>>7;
			p->color=bw<<11|bw<<6|bw;
		}
		p+=pitch;
	}

	return WS_OK;
}
