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

		Description:		风魂位图内部头文件
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/24
		Modify Time:		2001/11/14

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_MASK_H
#define _WINDSOUL_MASK_H

#include "wsaddon.h"
#include "wscanvas.h"
  
struct WMaskStruct;  

#define BLIT_BLUE BLIT_TRANS

class WINDSOULADD_API WMask : public WObject {
public: 
	WMask(); 
	WMask(const WBitmap &bmp, int x,int y,int w,int h) { Create(bmp,x,y,w,h); }
	WMask(const WBitmap &bmp, int x,int y,int w,int h,void *ptr) { Create(bmp,x,y,w,h,ptr); }
	~WMask();
       
	void Create(const WBitmap &bmp, int x,int y,int w,int h);
	void Create(const WBitmap &bmp, int x,int y,int w,int h,void *ptr);	// 从指定数据区创建
	
	int GetW() const;
	int GetH() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetKx() const;
	int GetKy() const;
	BLIT_FUNC DrawFunc(DWORD style) const;	// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WMaskStruct *GetMaskStruct() const { return reinterpret_cast<WMaskStruct *>(objdata); }	// 获取数据结构

	WMask& Clip(int x,int y,int w,int h);	// 相对背景图设置剪裁矩形
	WMask& Clip(const WObject &sprite,int x,int y);		// 根据精灵来设置剪裁矩形
	WMask& Clip(const WObject &sprite,WPoint p) { return Clip(sprite,p.x,p.y); }
	WMask& ClipEx(const WObject &sprite,WPoint p,int w,int h);	// 增加使用 Attach 图片(320x240) 对Mask 的修正
 	void Draw(const WMask &mask);			// 合并 Mask
	bool IsCover(int x,int y) const;		// 判断是否遮挡
	bool IsCover(WPoint p) const { return IsCover(p.x,p.y); }
	bool IsCoverEx(int x,int y) const;		// 判断是否遮挡
	bool IsCoverEx(WPoint p) const { return IsCoverEx(p.x,p.y); }
	WSERR Load(const void *maskdata,const WBitmap &);		// 从数据区读出Mask
	void DeleteBuffer();
	void DrawBorder(WBitmap &buffer);
	void DrawBorder(WCanvas &buffer) { DrawBorder(*reinterpret_cast<WBitmap*>(&buffer)); }
//	void Clear();							// 清空 Mask 数据区
//	char *ClipBox() const;     
};   
 
inline WMask& WMask::Clip(const WObject &sprite,int x,int y)
{
	ASSERT(sprite.IsValid());  
	return Clip(x-sprite.GetX(),y-sprite.GetY(),sprite.GetW(),sprite.GetH());
} 
  
inline WMask& WMask::ClipEx(const WObject &sprite,WPoint p,int ww,int hh)
{ 
	ASSERT(sprite.IsValid());
	int x=p.x-sprite.GetX();
	int y=p.y-sprite.GetY();
	int w=sprite.GetW(),h=sprite.GetH();
	if (x<0) w=MAX(0,w+x),x=0; 
	if (y<0) h=MAX(0,h+y),y=0;  
	return Clip(x,y,MIN(ww,x+w)-x,MIN(hh,y+h)-y);
}
      
#endif