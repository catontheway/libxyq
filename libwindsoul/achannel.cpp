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

		Description:		风魂 Alpha 通道
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/9
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include "bmpmem.h"
#include "windsoul.h"
#include "achannel.h"
#include "wsalpha.h"
#include "string.h"

WObjStruct* WAlphaBitmap::Duplicate(WObjectHeap* heap) const
{
	return new(heap)WAlphaBmpStruct(*GetAlphaBmpStruct());
}

#define new debug_new

WAlphaBmpStruct::~WAlphaBmpStruct()
{
	if (cmem) {
		WFree(cmem);
		cmem=0;
	}
}

WAlphaBmpStruct& WAlphaBmpStruct::operator=(const WAlphaBmpStruct& data)
{
	kx=data.kx,ky=data.ky,
	w=data.w,h=data.h,
	pitch=data.pitch,ptr=data.ptr,
	mem=0,cmem=0,
	userdata=data.userdata,channel=data.channel;
	return *this;
}

WAlphaBmpStruct::WAlphaBmpStruct(const WAlphaBmpStruct& data)
{
//	kx=data.kx,ky=data.ky,
	w=data.w,h=data.h,
	pitch=data.pitch,ptr=data.ptr,
	mem=0,cmem=0,
	userdata=data.userdata,channel=data.channel;
}

WSERR WAlphaBitmap::Create(int w,int h,void *ptr)
{
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	if (data) {
		if (data->mem) {
			delete data->mem;
			WFree(data->cmem);
		}
	}
	else data=new WAlphaBmpStruct;
	data->w=w;
	w=(w*2+7)&0xfffffff8;
	data->ptr=ptr,
	data->channel=(BYTE *)((DWORD)ptr+w*h),
	data->pitch=w,data->kx=data->ky=0,data->h=h,
	data->mem=0,
	data->cmem=0;
	SetData(data);
	return WS_OK;
}

WSERR WAlphaBitmap::Create(int w,int h)
{
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	if (data) {
		if (data->mem) {
			delete data->mem;
			delete data->cmem;
		}
	}
	else data=new WAlphaBmpStruct;
	data->w=w;
	w=(w*2+7)&0xfffffff8;
	if ((data->ptr=WAlloc(w*h+7))==0) {
		delete data;
		return WS_CANTCREATEBITMAP;
	}
	if ((data->channel=(BYTE *)WAlloc(w*h/2+3))==0) {
		delete data;
		WFree(data->ptr);
		return WS_CANTCREATEBITMAP;
	}
	data->pitch=w,data->kx=data->ky=0,data->h=h;
	WBmpData *mem=new WBmpData;
	mem->lpMem=data->ptr,
	mem->destroy=WBmpData::destroy_lpMem,
	data->mem=mem;
	data->cmem=data->channel;
	SetData(data);
	return WS_OK;
}

void WAlphaBitmap::Destroy()
{
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	if (data) {
		delete data;
		SetData(0);
	}
}

BYTE * WAlphaBitmap::ChannelLine(int y) const
{
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	ASSERT(data->channel);
	return data->channel+y*data->pitch/2;
}

WSERR WAlphaBitmap::Create(const WAlphaBitmap& parent,int x,int y,int width,int height)
{
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	WAlphaBmpStruct *parent_data=parent.GetAlphaBmpStruct();
	if (data) delete data;
	data=new WAlphaBmpStruct;
	int xx=0,yy=0;
	if (x>=parent_data->w || y>=parent_data->h || parent_data->ptr==0) {
		data->Empty();
		SetData(data);
		return WS_OK;
	}
	if (x<0) xx=x,width+=x,x=0;
	if (y<0) yy=y,height+=y,y=0;
	if (width<=0 || height<=0) {
		data->Empty();
		SetData(data);
		return WS_OK;
	}
	int offset=y*parent_data->pitch/2+x;
	data->w=MIN(width,parent_data->w-x),
	data->h=MIN(height,parent_data->h-y),
	data->channel=parent_data->channel+offset,
	data->ptr=(void *)((DWORD)(parent_data->ptr)+offset*2),

	data->mem=0,data->cmem=0,
	data->pitch=parent_data->pitch,
	data->kx=xx,data->ky=yy;

	SetData(data);
	return WS_OK;
}

WAlphaBitmap& WAlphaBitmap::operator=(const WAlphaBitmap& bmp)
{
	// 传递
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	WAlphaBmpStruct *src=bmp.GetAlphaBmpStruct();
	if (data) delete data;
	data=new WAlphaBmpStruct;
	*data=*src;
	data->mem=src->mem;
	src->mem=0;
	SetData(data);
	return *this;
}

extern "C" {
	WSERR _stdcall _alpha_blit16(WBmpStruct* ,const WAlphaBmpStruct *);
	WSERR _stdcall _alpha_trans_blit16(WBmpStruct* ,const WAlphaBmpStruct *);
}

static BLIT_FUNC _alpha_blit_func[8]={
	(BLIT_FUNC)_alpha_blit16,				// BLIT_COPY
	0,
	0,
	(BLIT_FUNC)_alpha_trans_blit16,				// BLIT_TRANS
	(BLIT_FUNC)_alpha_blit16,
	0,
	0,
	(BLIT_FUNC)_alpha_trans_blit16
};		

BLIT_FUNC WAlphaBitmap::DrawFunc(DWORD style) const
{
	BLIT_FUNC blit=(BLIT_FUNC)_alpha_blit_func[style];
	if (blit==0) {
		return WBitmap::DrawFunc(style);
	}
	return blit;
}

WBitmap* WAlphaBitmap::SubBitmap(int x,int y,int width,int height) const
{
	return new WAlphaBitmap(*this,x,y,width,height);
}

WSERR WAlphaBitmap::Combine(const WAlphaBitmap& bmp)
{
	WAlphaBmpStruct *des_data=GetAlphaBmpStruct();
	WAlphaBmpStruct *src_data=bmp.GetAlphaBmpStruct();
	if (src_data==0 || des_data==0) return WS_NULLBITMAP;
	int from_line=des_data->ky-src_data->ky;
	int to_line=from_line+src_data->h;
	int src_line;
	if (from_line<0) src_line=-from_line,from_line=0;
	else src_line=0;
	to_line=MIN(to_line,des_data->h);
	if (from_line>=to_line) return WS_OK;

	int from_offset=des_data->kx-src_data->kx;
	int to_offset=from_offset+src_data->w;
	int src_offset;
	if (from_offset<0) src_offset=-from_offset,from_offset=0;
	else src_offset=0;
	to_offset=MIN(to_offset,des_data->w);
	if (from_offset>=to_offset) return WS_OK;

	int i,j;
	BYTE *line_src,*line_des;
	Draw(bmp,0);

	for (i=from_line;i<to_line;i++,src_line++) {
		line_des=ChannelLine(i)+from_offset;
		line_src=bmp.ChannelLine(src_line)+src_offset;
		for (j=from_offset;j<to_offset;j++) {
			*line_des=255-((255-*line_des)*(255-*line_src)+255)/256;
			++line_des,++line_src;
		}
	}

	return WS_OK;
}

void WAlphaBitmap::ClearChannel(int alpha)
{
	WAlphaBmpStruct *data=GetAlphaBmpStruct();
	BYTE *channel=data->channel;
	for (int i=0;i<data->h;i++,channel+=data->pitch/2) {
		memset(channel,alpha,data->w);
	}
}

bool WAlphaBitmap::IsCover(WPoint p) const
{
	if (!WObject::IsCover(p)) return false;
	return ChannelLine(GetY()+p.y)[GetX()+p.x]!=0;
}

