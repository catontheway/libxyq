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
 
		http://www.codingnow.com 
		mailto:cloudwu@263.net
 
		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.

		Description:		Tips 类
 		Original Author:	云风
		Authors:
		Create Time:		2001/11/13
		Modify Time:
		Comment:			这个类演示了如果扩展风魂的绘图对象,
							WTips 把 四条 WLine, 一个 WBox 和一些 WChar
							合并在一起, 做成一个对象, 方便作画.
							效果和 WIndows 的黑框浅黄色的 Tips 条一样.

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>

#include "windsoul.h"
#include "wstips.h"
#include "wsfont.h"
#include "wsgeo.h"

struct WTipsStruct : public WObjStruct, memory<WTipsStruct> {
	int w;					// 先计算好宽度
	WPixel color;
	WFont *font;
	char * text;			// 字符串
	int userdata;
	
	WTipsStruct() {}
	~WTipsStruct() { WFree(text); }
	WTipsStruct(WFont *f,const char *string);
	// 因为 Canvas 并不析构 WString, 所以直接用 byte copy 而不用 WString::operator=
//	WTipsStruct(const WTipsStruct& tips) { w=tips.w,font=tips.font,text=tips.text,userdata=tips.userdata,color=tips.color; }
	using memory<WTipsStruct>::operator new;
	using memory<WTipsStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WTipsStruct& operator=(const WTipsStruct&box);		//无此函数

};

WTipsStruct::WTipsStruct(WFont *f,const char *string)
{
	font=f;
	w=f->GetLength(string)+6;
	text=(char*)WAlloc(64);
	int i;
	for (i=0;i<64 && string[i];i++) {
		text[i]=string[i];
	}
	if (i==64) {
		WFree(text);	// 长 string
		int n;
		for (n=i;string[n];n++) ;
		text=(char*)WAlloc(n+1);
		for (i=0;i<n;i++)
			text[i]=string[i];
	}
	text[i]=0;
	color=0xffffe7;
	kx=ky=0;
}

WObjStruct* WTips::Duplicate(WObjectHeap* heap) const
{
	// 避免 WString 的 引用copy
	WTipsStruct *tips=new(heap)WTipsStruct();
	WMemCpy(tips,GetTipsStruct(),sizeof(WTipsStruct));
	return tips;
}

void WTips::Destroy()
{
	if (objdata) delete GetTipsStruct();
	objdata=0;
}

void WTips::Create(WFont &font,const char *str)
{
	if (objdata==0) {
		objdata=new WTipsStruct(&font,str);
	}
	else {
		WTipsStruct *tips=GetTipsStruct();
		delete tips;
		objdata=new WTipsStruct(&font,str);
	}
}

int WTips::GetH() const
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	return tips->font->GetHeight()+4;
}

int WTips::GetW() const
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	return tips->w;
}

void WTips::SetColor(WPixel color)
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	tips->color=color;
}

void WTips::SetUserData(DWORD userdata) const
{
	WTipsStruct *tips=GetTipsStruct();
	ASSERT(tips);
	tips->userdata=userdata;
}

static WSERR _fastcall _draw_tips(WBmpStruct *bmp,const WTipsStruct *tips,int style)
{
	WBitmap temp;
	temp.SetData(bmp);
	int kx=bmp->kx,ky=bmp->ky;
	int h=tips->font->GetHeight()+2;
	WLine hline(tips->w,0,0);
	WLine vline(0,h,0);
	WBox box(tips->w-2,h,tips->color);
	hline.SetUserData(tips->userdata);
	vline.SetUserData(tips->userdata);
	box.SetUserData(tips->userdata);

	hline.SetPos(tips->kx,tips->ky);
	vline.SetPos(tips->kx,tips->ky-1);
	box.SetPos(tips->kx-1,tips->ky-1);

	temp.Draw(hline,style);
//	上一句可以写成下面的形式, 就不需要创建临时位图 temp
//	hline.DrawFunc(style)((DWORD)bmp,(DWORD)hline.GetLineStruct());

	temp.Draw(vline,style);

	hline.SetPos(tips->kx,tips->ky-tips->font->GetHeight()-3);
	vline.SetPos(tips->kx-tips->w+1,tips->ky-1);

	temp.Draw(hline,style);
	temp.Draw(vline,style);
	temp.Draw(box,style);

	temp.AddPos(3-tips->kx,2-tips->ky);
	tips->font->Draw(temp,tips->text,0);
	temp(kx,ky);			// 恢复 bmp 的 kx,ky
	temp.SetData(0);		// 保证 temp 退出的时候结构不被释放掉
	return WS_OK;
}

static WSERR _stdcall _draw_tips_solid(WBmpStruct *bmp,const WTipsStruct *tips)
{
	return _draw_tips(bmp,tips,BLIT_NORMAL);
}


static WSERR _stdcall _draw_tips_trans(WBmpStruct *bmp,const WTipsStruct *tips)
{
	return _draw_tips(bmp,tips,BLIT_TRANS);
}


BLIT_FUNC WTips::DrawFunc(DWORD style) const
{
	if (style==BLIT_TRANS) return (BLIT_FUNC)_draw_tips_trans;
	else return (BLIT_FUNC)_draw_tips_solid;
}
