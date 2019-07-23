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

		Description:		风魂++ DDraw Surface支持
 		Original Author:	云风
		Authors:
		Create Time:		2000/10/27
		Modify Time:		2002/4/15

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include <ddraw.h>
#include <assert.h>
#include <string.h>
#include "windsoul.h"
#include "wsurface.h"
#include "wscanvas.h"
#include "canvasin.h"

#pragma comment (lib,"ddraw.lib")

struct WSurfaceData {
	LPDIRECTDRAW ddraw;			// ddraw 指针
	LPDIRECTDRAWCLIPPER clipper;	// 窗口裁减器
	LPDIRECTDRAWSURFACE screen;		// 屏幕 Buffer
	LPDIRECTDRAWSURFACE LeftBuffer;
	LPDIRECTDRAWSURFACE RightBuffer;
	int depth;
	bool window_mode;
	LONG window_style;
	RECT window_rect;

	WSurfaceData() {
		depth=2;
		ddraw=0;
		clipper=0;
		window_mode=true;
		screen=LeftBuffer=RightBuffer=0;
	}
	~WSurfaceData() {
		if (clipper) clipper->Release();
		if (LeftBuffer) ((LPDIRECTDRAWSURFACE)LeftBuffer)->Release();
		if (RightBuffer) ((LPDIRECTDRAWSURFACE)RightBuffer)->Release();
		if (screen) screen->Release();
		if (ddraw) {
			if (!window_mode)
				ddraw->RestoreDisplayMode();
			ddraw->Release();
		}
		LeftBuffer=RightBuffer=0;
		ddraw=0,screen=0;
	}
};

typedef void (__stdcall *_blit_func)(WBmpStruct *,void *ptr);
static _blit_func blit_surface;
static DDSURFACEDESC           ddsd;
extern "C" {
	void _stdcall _blit_surface_555(WBmpStruct *,void *ptr);
	void _stdcall _blit_surface_565(WBmpStruct *,void *ptr);
	void _stdcall _blit_surface_24(WBmpStruct *,void *ptr);
	void _stdcall _blit_surface_32(WBmpStruct *,void *ptr);
	void _stdcall _set_blit_pitch(int pitch);
}

WSurface::WSurface() 
{
	m_hWnd=0;
	Canvas=0;
	data=new WSurfaceData;
}

void WSurface::Release()
{
	delete data;
	data=new WSurfaceData;
}

WSurface::~WSurface()
{
	delete data;
}

WSERR WSurface::RestoreDesktop()
{
	WSERR err=WS_OK;
	if (data->ddraw) {
		if (!data->window_mode)
			data->ddraw->RestoreDisplayMode();
		::SetWindowLong(m_hWnd,GWL_STYLE,data->window_style);
		::MoveWindow(m_hWnd,data->window_rect.left,data->window_rect.top,
			data->window_rect.right-data->window_rect.left,
			data->window_rect.bottom-data->window_rect.top,true);
		err=CreateSurface();
		::UpdateWindow(m_hWnd);
		::ShowWindow(m_hWnd,SW_SHOWNORMAL);
		::BringWindowToTop(m_hWnd);
	}
	return err;
}

WSERR WSurface::SetDisplay(int w,int h)
{
	if (data->ddraw==0) 
		return WS_CREATEDDRAWFAIL;

	data->window_style=::GetWindowLong(m_hWnd,GWL_STYLE);
	::GetWindowRect(m_hWnd,&(data->window_rect));
	::SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP&~WS_VISIBLE);
	::MoveWindow(m_hWnd,0,0,w,h,true);
	::UpdateWindow(m_hWnd);
	::ShowWindow(m_hWnd,SW_SHOWNORMAL);
	::BringWindowToTop(m_hWnd);

	if (data->ddraw->SetDisplayMode(w,h,16)!=DD_OK) {
		return WS_CREARTSURFACEFAIL;
	}

	data->window_mode=false;
	return CreateSurface();
}

WSERR WSurface::Create(HWND hWnd,WCanvas &canvas)
{
	if (data->ddraw) return WS_CREATEDDRAWFAIL;

	if (DirectDrawCreate(NULL,&(data->ddraw),NULL)!=DD_OK) {
		return WS_CREATEDDRAWFAIL;
	}
	LPDIRECTDRAW lpDD=data->ddraw;
    lpDD->SetCooperativeLevel(hWnd,DDSCL_NORMAL);

	lpDD->CreateClipper(0,&(data->clipper),0);
	data->clipper->SetHWnd(0,hWnd);

	m_hWnd=hWnd;
	Canvas=&canvas;
	data->window_style=::GetWindowLong(m_hWnd,GWL_STYLE);
	::GetWindowRect(m_hWnd,&(data->window_rect));

	return CreateSurface();
}

WSERR WSurface::CreateSurface()
{
	if (Canvas==0) return WS_CREARTSURFACEFAIL;
	LPDIRECTDRAW lpDD=data->ddraw;
	WCanvas &canvas=*Canvas;

	memset(&ddsd,0,sizeof(ddsd));
    ddsd.dwSize=sizeof(ddsd);
    ddsd.dwFlags=DDSD_CAPS;
    ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;

	if (data->screen!=0) data->screen->Release();
	if (data->LeftBuffer!=0) data->LeftBuffer->Release();
	if (data->RightBuffer!=0) data->RightBuffer->Release();

    if (lpDD->CreateSurface(&ddsd,&(data->screen),NULL)!=DD_OK) {
		data->screen=0;
        return WS_CREARTSURFACEFAIL;
	}
	data->screen->SetClipper(data->clipper);

	DDPIXELFORMAT ddpf;

//	lpDD->GetDisplayMode(&ddsd);
	memset(&ddpf,0,sizeof(ddpf));
	ddpf.dwSize=sizeof(ddpf);
	data->screen->GetPixelFormat(&ddpf);

	data->depth=ddpf.dwRGBBitCount/8;

	switch (ddpf.dwRGBBitCount) {
	case 16:
		switch (ddpf.dwGBitMask) {
		case 0x3e0:
			blit_surface=_blit_surface_555;
			break;
		case 0x7e0:
			blit_surface=_blit_surface_565;
			break;
		default:
			data->screen->Release();
			data->screen=0;
			return WS_CREARTSURFACEFAIL;
		}
		break;
	case 24:
		blit_surface=_blit_surface_24;
		break;
	case 32:
		blit_surface=_blit_surface_32;
		break;
	default:
		data->screen->Release();
		data->screen=0;
		return WS_CREARTSURFACEFAIL;
	}

	int lback_width,rback_width,back_height;
	lback_width=WCANVASBLOCKW*(canvas.col/2);
	rback_width=WCANVASBLOCKW*(canvas.col-canvas.col/2);
	back_height=WCANVASBLOCKH*canvas.row;
	
	ddsd.dwFlags= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.dwHeight=back_height;
	ddsd.dwWidth=lback_width;

    if (lpDD->CreateSurface(&ddsd,&(data->LeftBuffer),NULL)!=DD_OK) {
		data->LeftBuffer=data->RightBuffer=0;
		return WS_CREARTSURFACEFAIL;
	}

	ddsd.dwFlags= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	ddsd.dwHeight=back_height;
	ddsd.dwWidth=rback_width;

    if (lpDD->CreateSurface(&ddsd,&(data->RightBuffer),NULL)!=DD_OK) {
		data->LeftBuffer=data->RightBuffer=0;
		return WS_CREARTSURFACEFAIL;
	}
	Refresh();
	return WS_OK;
}

void WSurface::Refresh()
{
	int i,j,s;
	LPDIRECTDRAWSURFACE left_buffer=data->LeftBuffer;
	LPDIRECTDRAWSURFACE right_buffer=data->RightBuffer;
	HRESULT hr;
	int left_col=Canvas->col/2,right_col=Canvas->col-Canvas->col/2;
	BYTE *blit_ptr;
	hr=left_buffer->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	if (hr!=DD_OK) return;
	_set_blit_pitch(ddsd.lPitch-WCANVASBLOCKW*data->depth);
	blit_ptr=(BYTE *)ddsd.lpSurface;
	for (s=0,i=0;i<Canvas->row;i++,blit_ptr+=ddsd.lPitch*WCANVASBLOCKH-left_col*WCANVASBLOCKW*data->depth,s+=right_col)
		for (j=0;j<left_col;j++,blit_ptr+=WCANVASBLOCKW*data->depth,++s) {
			blit_surface(Canvas->block[s].GetBmpStruct(),(void*)blit_ptr);
		}
	left_buffer->Unlock(&ddsd);
	left_col=Canvas->col/2,right_col=Canvas->col-Canvas->col/2;
	hr=right_buffer->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	if (hr!=DD_OK) return;
	_set_blit_pitch(ddsd.lPitch-WCANVASBLOCKW*data->depth);
	blit_ptr=(BYTE *)ddsd.lpSurface;
	for (s=left_col,i=0;i<Canvas->row;i++,blit_ptr+=ddsd.lPitch*WCANVASBLOCKH-right_col*WCANVASBLOCKW*data->depth,s+=left_col)
		for (j=0;j<right_col;j++,blit_ptr+=WCANVASBLOCKW*data->depth,++s) {
			blit_surface(Canvas->block[s].GetBmpStruct(),(void*)blit_ptr);
		}
	right_buffer->Unlock(&ddsd);
}

WSERR WSurface::RestoreSurface()
{
	LPDIRECTDRAWSURFACE left_buffer=data->LeftBuffer;
	LPDIRECTDRAWSURFACE right_buffer=data->RightBuffer;

	HRESULT hr=DD_OK;
	bool need_restore=false;

	if (data->screen->IsLost()) {
		hr=data->screen->Restore();
		need_restore=true;
	}
	if (hr==DD_OK && left_buffer->IsLost()) {
		hr=left_buffer->Restore();
		need_restore=true;
	}
	if (hr==DD_OK && right_buffer->IsLost()) {
		hr=right_buffer->Restore();
		need_restore=true;
	}

	if (hr!=DD_OK) {
		WSERR err=CreateSurface();
		if (err!=WS_OK) return err;
		need_restore=false;
	}

	if (need_restore) {
		Refresh();
	}
	return WS_OK;
}

WSERR WSurface::Blit2Screen(int x,int y)
{
	int i,j,s;
	Canvas->SleepFrame();
	Canvas->Update();
	if (data->LeftBuffer==0) {
		Canvas->NextFrame();
		return WS_CREARTSURFACEFAIL;
	}

	POINT point={0,0};
	::ClientToScreen(m_hWnd,&point);
	x+=point.x,y+=point.y;

	LPDIRECTDRAWSURFACE lpDDSBackLeft=data->LeftBuffer;
	LPDIRECTDRAWSURFACE lpDDSBackRight=data->RightBuffer;
	LPDIRECTDRAWSURFACE lpDDSPrimary=data->screen;

	int left_col=Canvas->col/2,right_col=Canvas->col-Canvas->col/2;
	BYTE *blit_ptr;
	bool bError;
	HRESULT hr=DD_OK;
	
	for (bError=true;bError;bError=false) {
		hr=lpDDSBackLeft->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);

		if (hr!=DD_OK) break;
		_set_blit_pitch(ddsd.lPitch-WCANVASBLOCKW*data->depth);
		blit_ptr=(BYTE *)ddsd.lpSurface;
		for (s=0,i=0;i<Canvas->row;i++,blit_ptr+=ddsd.lPitch*WCANVASBLOCKH-left_col*WCANVASBLOCKW*data->depth,s+=right_col)
			for (j=0;j<left_col;j++,blit_ptr+=WCANVASBLOCKW*data->depth,++s) {
				if (Canvas->block[s].last!=Canvas->block[s].obj || Canvas->block[s].change!=0)
					blit_surface(Canvas->block[s].GetBmpStruct(),(void*)blit_ptr);
			}

		hr=lpDDSBackLeft->Unlock(&ddsd);
		if (hr!=DD_OK) break;

		hr=lpDDSBackRight->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
		if (hr!=DD_OK) break;
		_set_blit_pitch(ddsd.lPitch-WCANVASBLOCKW*data->depth);
		blit_ptr=(BYTE *)ddsd.lpSurface;
		for (s=left_col,i=0;i<Canvas->row;i++,blit_ptr+=ddsd.lPitch*WCANVASBLOCKH-right_col*WCANVASBLOCKW*data->depth,s+=left_col)
			for (j=0;j<right_col;j++,blit_ptr+=WCANVASBLOCKW*data->depth,++s) {
				if (Canvas->block[s].last!=Canvas->block[s].obj || Canvas->block[s].change!=0)
					blit_surface(Canvas->block[s].GetBmpStruct(),(void*)blit_ptr);
			}
		hr=lpDDSBackRight->Unlock(&ddsd);
		if (hr!=DD_OK) break;

		WPoint offset_pos=Canvas->data->offset;
		int width=MIN((Canvas->col-Canvas->block_x)*WCANVASBLOCKW-offset_pos.x,Canvas->GetW());
		int height=MIN(((Canvas->row-Canvas->block_y)*WCANVASBLOCKH-offset_pos.y),Canvas->GetH());
		int split_x=Canvas->block_x*WCANVASBLOCKW+offset_pos.x;
		int split_y=Canvas->block_y*WCANVASBLOCKH+offset_pos.y;
		RECT rect;
		RECT drect;
		int skip;

		if (height>0) {
			if (width>0) {
				rect.top=split_y,rect.bottom=split_y+height;
				rect.left=split_x,rect.right=MIN(split_x+width,left_col*WCANVASBLOCKW);
				drect.left=x,drect.top=y;
				drect.right=x+rect.right-rect.left;
				drect.bottom=y+rect.bottom-rect.top;
				if (rect.left<rect.right) {
					skip=rect.right-rect.left;
//					lpDDSPrimary->BltFast(x,y,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					lpDDSPrimary->Blt(&drect,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);
				}
				else skip=0;
				rect.left=MAX(0,split_x-left_col*WCANVASBLOCKW),rect.right=split_x+width-left_col*WCANVASBLOCKW;
				if (rect.left<rect.right)
					drect.left=skip+x,drect.right=skip+x+rect.right-rect.left;
//					lpDDSPrimary->BltFast(skip+x,y,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					lpDDSPrimary->Blt(&drect,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);
				}
			if (Canvas->GetW()>width) {
				rect.top=split_y,rect.bottom=split_y+height;
				rect.left=0,rect.right=MIN(Canvas->GetW()-width,left_col*WCANVASBLOCKW);
				skip=rect.right-rect.left;

				drect.top=y,drect.left=Canvas->WBitmap::GetW()-split_x+x;
				drect.bottom=y+rect.bottom-rect.top;
				drect.right=drect.left+rect.right-rect.left;

//				lpDDSPrimary->BltFast(Canvas->WBitmap::GetW()-split_x+x,y,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
				lpDDSPrimary->Blt(&drect,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);
				if (rect.right<Canvas->GetW()-width) {
					rect.right=Canvas->GetW()-width-left_col*WCANVASBLOCKW;
					drect.left+=skip;
					drect.right=drect.left+rect.right-rect.left;
//					lpDDSPrimary->BltFast(Canvas->WBitmap::GetW()-split_x+skip+x,y,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					lpDDSPrimary->Blt(&drect,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);
				}
			}
		}
		if (Canvas->GetH()>height) {
			if (width>0) {
				rect.top=0,rect.bottom=Canvas->GetH()-height;
				rect.left=split_x,rect.right=MIN(split_x+width,left_col*WCANVASBLOCKW);
				drect.top=y+Canvas->WBitmap::GetH()-split_y;
				drect.left=x;
				drect.bottom=drect.top+rect.bottom-rect.top;
				drect.right=x+rect.right-rect.left;
				if (rect.left<rect.right) {
					skip=rect.right-rect.left;
//					lpDDSPrimary->BltFast(x,y+Canvas->WBitmap::GetH()-split_y,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					lpDDSPrimary->Blt(&drect,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);
				}
				else skip=0;
				rect.left=MAX(0,split_x-left_col*WCANVASBLOCKW),rect.right=split_x+width-left_col*WCANVASBLOCKW;
				if (rect.left<rect.right) {
					drect.left+=skip;
					drect.right=drect.left+rect.right-rect.left;
//					lpDDSPrimary->BltFast(skip+x,y+Canvas->WBitmap::GetH()-split_y,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					lpDDSPrimary->Blt(&drect,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);
				}
			}
			if (Canvas->GetW()>width) {
				rect.top=0,rect.bottom=Canvas->GetH()-height;
				rect.left=0,rect.right=MIN(Canvas->GetW()-width,left_col*WCANVASBLOCKW);
				skip=rect.right-rect.left;
				drect.left=x+Canvas->WBitmap::GetW()-split_x;
				drect.right=drect.left+rect.right-rect.left;
				drect.top=y+Canvas->WBitmap::GetH()-split_y;
				drect.bottom=drect.top+rect.bottom-rect.top;

//				lpDDSPrimary->BltFast(x+Canvas->WBitmap::GetW()-split_x,y+Canvas->WBitmap::GetH()-split_y,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
				lpDDSPrimary->Blt(&drect,lpDDSBackLeft,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);

				if (rect.right<Canvas->GetW()-width) {
					rect.right=Canvas->GetW()-width-left_col*WCANVASBLOCKW;
					drect.left+=skip;
					drect.right=drect.left+rect.right-rect.left;
//					lpDDSPrimary->BltFast(x+Canvas->WBitmap::GetW()-split_x+skip,y+Canvas->WBitmap::GetH()-split_y,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
					lpDDSPrimary->Blt(&drect,lpDDSBackRight,&rect,DDBLTFAST_NOCOLORKEY|DDBLT_WAIT,0);

				}
			}
		}
	}

	WSERR r=WS_OK;
	if (bError && hr==DDERR_SURFACELOST) {
		r=RestoreSurface();
	}
	Canvas->NextFrame();
	return r;
}
