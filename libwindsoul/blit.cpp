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

		Description:		风魂位图传输
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/13
		Modify Time:		2001/9/8

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <assert.h>
#include "windsoul.h"
#define new debug_new

extern "C" {
	WSERR _stdcall _clear16(WBmpStruct* bmp,WPixel color);
	WSERR _stdcall _blit16(WBmpStruct *,const WBmpStruct *);
	WSERR _stdcall _mask_blit16(WBmpStruct *,const WBmpStruct *);
	WSERR _stdcall _additive_blit16(WBmpStruct *,const WBmpStruct *);
	WSERR _stdcall _subtract_blit16(WBmpStruct *,const WBmpStruct *);
	WSERR _stdcall _trans_blit16(WBmpStruct *,const WBmpStruct *);
	WSERR _stdcall _mask_trans_blit16(WBmpStruct *,const WBmpStruct *);
	WSERR _stdcall _back_blit16(WBmpStruct *,const WBmpStruct *);
}

static BLIT_FUNC _blit_func[16]={
	(BLIT_FUNC)_blit16,					// BLIT_COPY
	(BLIT_FUNC)_additive_blit16,			// BLIT_ADDITIVE
	(BLIT_FUNC)_subtract_blit16,			// BLIT_SUBTRACT
	(BLIT_FUNC)_trans_blit16,				// BLIT_TRANS
	(BLIT_FUNC)_mask_blit16,				// BLIT_MASK
	(BLIT_FUNC)_back_blit16,				// BLIT_BACK
	0,
	(BLIT_FUNC)_mask_trans_blit16,			// BLIT_MASK|BLIT_TRANS
	0,0,0,0,0,0,0,0
};		

WSERR WBitmap::Draw(const WObject &bmp, DWORD style)
{
	BLIT_FUNC blit=bmp.DrawFunc(style);
	if (blit==0) return WS_UNSUPPORTBLITTYPE;
	if (GetBmpStruct()==0 || bmp.GetObjStruct()==0) return WS_OK;
	return blit((DWORD)GetBmpStruct(),(DWORD)bmp.GetObjStruct());
}

WSERR WBitmap::Clear(WPixel color)
{
	if (!objdata) return WS_OK;
	return _clear16(GetBmpStruct(),color);
}

BLIT_FUNC WBitmap::ClearFunc()
{
	return (BLIT_FUNC)_clear16;
}

BLIT_FUNC WBitmap::DrawFunc(DWORD style) const
{
	BLIT_FUNC blit=(BLIT_FUNC)_blit_func[style];
	if (blit==0) return 0;
	return blit;
}

void WBitmap::RegisterDrawFunc(BLIT_FUNC func,DWORD style)
{
	ASSERT(style>=0 && style<16);
	_blit_func[style]=func;
}