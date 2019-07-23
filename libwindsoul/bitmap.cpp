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

		Description:		风魂位图类
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/14
		Modify Time:		2001/7/10

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include "bmpmem.h"
#include "assert.h"

WObjStruct* WBitmap::Duplicate(WObjectHeap* heap) const
{
	return new(heap)WBmpStruct(*GetBmpStruct());
}

#define new debug_new

WBmpStruct::~WBmpStruct()
{
	if (mem) {
		delete mem;
		mem=0;
	}
}

WBmpStruct& WBmpStruct::operator=(const WBmpStruct& data)
{
	kx=data.kx,ky=data.ky,
	w=data.w,h=data.h,
	pitch=data.pitch,ptr=data.ptr,
	mem=0,
	userdata=data.userdata;
	return *this;
}

WBmpStruct::WBmpStruct(const WBmpStruct& data)
{
//	kx=data.kx,ky=data.ky,
	w=data.w,h=data.h,
	pitch=data.pitch,ptr=data.ptr,
	mem=0,
//	mem=data.mem,
	userdata=data.userdata;
//	if (mem) ++mem->times;
}

void WBmpData::destroy_lpMem(DWORD ptr)
{
	WFree((void *)ptr);
}

WSERR WBitmap::Create(int w,int h,void *ptr)
{
	WBmpStruct *data=GetBmpStruct();
	if (data) {
		if (data->mem) delete data->mem;
	}
	else data=new WBmpStruct;
	data->w=w;
	w=(w*2+7)&0xfffffff8;
	data->pitch=w,data->kx=data->ky=0,data->h=h,
	data->ptr=ptr,data->mem=0;
	SetData(data);
	return WS_OK;
}

WSERR WBitmap::Create(int w,int h)
{
	WBmpStruct *data=GetBmpStruct();
	if (data) {
		if (data->mem) delete data->mem;
	}
	else data=new WBmpStruct;
	data->w=w;
	w=(w*2+7)&0xfffffff8;
	if ((data->ptr=WAlloc(w*h+7))==0) {
		delete data;
		return WS_CANTCREATEBITMAP;
	}
	data->pitch=w,data->kx=data->ky=0,data->h=h;
	WBmpData *mem=new WBmpData;
	mem->lpMem=data->ptr,
	mem->destroy=WBmpData::destroy_lpMem,
//	mem->times=1,
	data->mem=mem;
	SetData(data);
	return WS_OK;
}

void WBitmap::Destroy()
{
	WBmpStruct *data=GetBmpStruct();
	if (data) {
		delete data;
		SetData(0);
	}
}
/*
void WBitmap::Unlock()
{
	WBmpStruct *data=GetBmpStruct();
	if (data->mem) delete (data->mem);
}
*/
int WBitmap::GetW() const
{
	WBmpStruct *data=GetBmpStruct();
	ASSERT(data!=0);
    return data->w;
}

int WBitmap::GetH() const
{
	WBmpStruct *data=GetBmpStruct();
	ASSERT(data!=0);
	return data->h;
}

WPixel * WBitmap::operator[](int y) const
{
	WBmpStruct *data=GetBmpStruct();
	return (WPixel*)((DWORD)(data->ptr)+y*data->pitch);
}

void WBitmap::SetUserData(DWORD userdata) const
{
	WBmpStruct *data=GetBmpStruct();
	data->userdata=userdata;
}

WSERR WBitmap::Create(const WBitmap& parent,int x,int y,int width,int height)
{
	WBmpStruct *data=GetBmpStruct();
	WBmpStruct *parent_data=parent.GetBmpStruct();
	if (data) delete data;
	data=new WBmpStruct;
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
	data->w=MIN(width,parent_data->w-x),
	data->h=MIN(height,parent_data->h-y),
	data->ptr=(void *)((DWORD)(parent_data->ptr)+y*parent_data->pitch+x*2),
//	data->mem=parent_data->mem,
	data->mem=0,
	data->pitch=parent_data->pitch,
	data->userdata=parent_data->userdata,
	data->kx=xx,data->ky=yy;
//	if (data->mem) 
//		++data->mem->times;
	SetData(data);
	return WS_OK;
}

WBitmap& WBitmap::operator=(const WBitmap& bmp)
{
	// 传递
	WBmpStruct *data=GetBmpStruct();
	WBmpStruct *src=bmp.GetBmpStruct();
	if (data) delete data;
	data=new WBmpStruct;
	*data=*src;
	data->mem=src->mem;
	src->mem=0;
	SetData(data);
	return *this;
}

WBitmap* WBitmap::SubBitmap(int x,int y,int width,int height) const
{
	return new WBitmap(*this,x,y,width,height);
}

bool WBitmap::IsCover(WPoint p) const
{
	if (!WObject::IsCover(p)) return false;
	return (*this)[GetY()+p.y][GetX()+p.x].color!=0xf81f;
}

