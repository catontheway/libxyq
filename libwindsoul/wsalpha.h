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

		Description:		风魂 Alpha 通道头文件
 		Original Author:	云风
		Authors:
		Create Time:		2001/3/15
		Modify Time:		2001/12/21

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_ALPHACHANNEL_H
#define _WINDSOUL_ALPHACHANNEL_H

struct WAlphaBmpStruct;

class WINDSOUL_API WAlphaBitmap : public WBitmap {
public:
	WAlphaBitmap() {}
	WAlphaBitmap(int w,int h) { Create(w,h); }
	WAlphaBitmap(int w,int h,void *ptr) { Create(w,h,ptr); }
	WAlphaBitmap(const WAlphaBitmap& bmp) {*this=bmp;}
	WAlphaBitmap(const WAlphaBitmap& bmp,int x,int y,int width,int height) { Create(bmp,x,y,width,height); }
	~WAlphaBitmap() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WAlphaBitmap& operator=(const WAlphaBitmap& bmp);	// 复制位图(共享数据区)
	WAlphaBmpStruct *GetAlphaBmpStruct() const { return reinterpret_cast<WAlphaBmpStruct *>(objdata); }	// 获取数据结构
	WSERR Create(int w,int h);							// 创建位图
	WSERR Create(int w,int h,void *ptr);				// 从指定数据区创建位图
	WSERR Create(const WAlphaBitmap& parent,int x,int y,int width,int height);
	WBitmap* SubBitmap(int x,int y,int width,int height) const;	// 创建子图
	void Destroy();										// 销毁位图
	BYTE * ChannelLine(int y) const;					// 返回 Channel 通道指针
	const WAlphaBitmap& operator()(int userdata) const { SetUserData(userdata); return *this; }
	WAlphaBitmap operator() (int x,int y,int width,int height) const { return WAlphaBitmap(*this,x,y,width,height); }
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
	WSERR LoadTGA(const void *tgadata);					// 从数据区读出位图
	WSERR Combine(const WAlphaBitmap& bmp);				// 合并两个 Alpha 位图
	void ClearChannel(int alpha);						// 清除 Alpha Channel
	WSERR SaveTGA(const char *filename) const;
	bool IsCover(WPoint p) const;
};

#endif
