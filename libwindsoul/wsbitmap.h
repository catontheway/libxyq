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
		Create Time:		2000/12/9
		Modify Time:		2001/11/21

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_BITMAP_H
#define _WINDSOUL_BITMAP_H

#include "wshelper.h"

 ///	Blit 样式
/////////////////////////

#define BLIT_NORMAL	0
#define BLIT_COPY	0
#define BLIT_ADDITIVE	0x1
#define BLIT_SUBTRACT	0x2
#define BLIT_TRANS		0x3
#define BLIT_MASK		0x4
#define BLIT_BACK		0x5

 ///	WPixel 像素
/////////////////////////

#pragma pack (push)
#pragma pack (1)

struct WPixel {
	union {
		WORD color;								// 16bit 高彩
		struct {
			WORD blue:5;						// 5bit 兰色
			WORD green:6;						// 6bit 绿色
			WORD red:5;							// 5bit 红色
		};
		struct
		{
			BYTE l;
			BYTE h;
		};
	};
	WPixel() {}
	WPixel(DWORD c) {color=(WORD)((c>>8&0xf800)|(c>>5&0x7e0)|(c>>3&0x1f));}
	WPixel(int r,int g,int b) : red(r>>3),green(g>>2),blue(b>>3) {}
	operator DWORD() const {return (color<<5&0x7fc00)|(color<<8&0xf80000)|((color<<3|(color&7))&0x3ff);}
	// 狼宝加
// 	void operator =(WORD color)
// 	{
// 		blue = color & 0x1f;
// 		green = (color >> 5 & 0x1f) << 1;
// 		if (green)green += 1;
// 		red = color >> 10 & 0x1f;
// 	}
// 	void operator =(DWORD color1)
// 	{
// 		red = color1 >> 3 & 0x1f;
// 		green = (color1 >> 11 & 0x1f) << 1;
// 		if (green)green += 1;
// 		blue = color1 >> 19 & 0x1f;
// 	}
};

#pragma pack (pop)

 ///	WBitmap 位图
/////////////////////////

struct WBmpStruct;
struct WObjStruct;
class WObjectHeap;

typedef DWORD (_stdcall *BLIT_FUNC)(DWORD,DWORD);

struct WINDSOUL_API WObjStruct {
	int kx;									// 中心点 x
	int ky;									// 中心点 y
	void *operator new(unsigned size,WObjectHeap *heap);		// 从指定堆分配(不单个释放)
	void operator delete(void *,WObjectHeap *) {};
};

struct WBmpData;

struct WINDSOUL_API WBmpStruct : public WObjStruct {
	int w;									// 宽度
	int h;									// 高度
	int pitch;								// 行宽字节
	void *ptr;								// 第一扫描行指针
	WBmpData *mem;							// 数据内存块指针
	DWORD userdata;							// 额外数据

	WBmpStruct() {}
	WBmpStruct (const WBmpStruct&);
	~WBmpStruct();
	void *operator new(unsigned size) { return ::operator new(size); }
	void operator delete(void *p) { ::operator delete(p); };
#if defined(_DEBUG) && !defined(_DISABLE_WINDSOUL_NEW)
	void *operator new(unsigned size,const char *file,unsigned line) { return ::operator new(size,file,line); }
	void operator delete(void *p,const char *file,unsigned line) { ::operator delete(p,file,line); };
#endif
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
	void operator delete(void *,WObjectHeap *) {};
	WBmpStruct& operator=(const WBmpStruct& bmp);
	void Empty() { w=h=0,ptr=0,mem=0; }		// 清空结构
};

class WObject;

class WINDSOUL_API memory<WObject>::manager;
template class WINDSOUL_API memory<WObject>;

class WINDSOUL_API WObject : public memory<WObject> {
protected:
	void *objdata;
public:
	WObject() : objdata(0) {}
	virtual ~WObject() {};
	void SetData(void *p) { objdata=p; }				// 设置 data
	WObjStruct *GetObjStruct() const { return reinterpret_cast<WObjStruct *>(objdata); }	// 获取数据结构
	virtual bool IsValid() const { return (objdata!=0); }		// 判断位图是否有效
	void *GetData() const { return objdata; }			// 读 data
	WObject& SetPos(const WPoint &p) { WObjStruct *data=GetObjStruct(); data->kx=p.x,data->ky=p.y; return *this;}	// 设置关键点
	WObject& SetPos(int x,int y) { WObjStruct *data=GetObjStruct(); data->kx=x,data->ky=y; return *this;}	// 设置关键点
	WObject& AddPos(const WPoint &p) { WObjStruct *data=GetObjStruct(); data->kx+=p.x,data->ky+=p.y; return *this;}	// 设置关键点
	WObject& AddPos(int x,int y) { WObjStruct *data=GetObjStruct(); data->kx+=x,data->ky+=y; return *this;}	// 设置关键点
	int GetX() const { return GetObjStruct()->kx; }		// 获取 kx
	int GetY() const { return GetObjStruct()->ky; }		// 获取 ky
	virtual int GetW() const=0;
	virtual int GetH() const=0;
	virtual BLIT_FUNC DrawFunc(DWORD style) const=0;	// 获得 Draw 函数指针
	virtual WObjStruct *Duplicate(WObjectHeap *heap) const=0;	// 从自己拷贝构造对象
	virtual bool Affect(int, int) const { return true; }	// 判断对象是否影响 Canvas 块
	virtual void SetUserData(DWORD) const {};			// 设置用户的扩展数据
	virtual bool IsCover(WPoint p) const;				// 判断是否覆盖一个点
};

inline bool WObject::IsCover(WPoint p) const
{
	return WRect(-GetX(),-GetY(),GetW(),GetH()).IsCover(p);
}

class WINDSOUL_API WBitmap : public WObject {
public:
	WBitmap() {}
	WBitmap(int w,int h) { Create(w,h); }
	WBitmap(int w,int h,void *ptr) { Create(w,h,ptr); }
	WBitmap(const WBitmap& bmp) {*this=bmp;}
	WBitmap(const WBitmap& bmp,int x,int y,int width,int height) { Create(bmp,x,y,width,height); }
	~WBitmap() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WBitmap& operator=(const WBitmap& bmp);				// 复制位图(共享数据区)
	WBmpStruct *GetBmpStruct() const { return reinterpret_cast<WBmpStruct *>(objdata); }	// 获取数据结构
	virtual WSERR Create(int w,int h);					// 创建位图
	virtual WSERR Create(int w,int h,void *ptr);		// 给定数据区创建位图
	WSERR Create(const WBitmap& parent,int x,int y,int width,int height);
	virtual WBitmap* SubBitmap(int x,int y,int width,int height) const;	// 创建子图
	virtual void Destroy();								// 销毁位图
	WSERR Blit2DC(HDC hDC,int x,int y,int offset=0) const;	// 传送到 DC (如果有父位图 ,offset 为其在父图上的 X 偏移)
	WSERR Blit2DC(HDC hDC,int dx,int dy,int x,int y,int w,int h) const;	// BLIT 一个矩形部分到 DC
	int GetW() const;									// 取宽度
	int GetH() const;									// 取高度
	WPixel * operator[](int y) const;					// 返回一个扫描行指针
	void SetUserData(DWORD userdata) const;				// 设置用户数据
	const WBitmap& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
	WBitmap& operator()(int x,int y) { SetPos(x,y); return *this; }
	WBitmap& operator()(WPoint p) { SetPos(p); return *this; }
	WBitmap operator() (int x,int y,int width,int height) const { return WBitmap(*this,x,y,width,height); }
	virtual WSERR Draw(const WObject &bmp, DWORD style);		// 将 bmp 绘制到 this 上
	WSERR Clear(WPixel color);							// 清位图
	void Draw(const char *s,WPixel color);				// 输出 Ascii 字符串
	static BLIT_FUNC ClearFunc();						// 获得 Clear 函数指针
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
	static void RegisterDrawFunc(BLIT_FUNC,DWORD style);// 注册绘图函数
	WSERR Load(void *bmpdata);					// 从数据区读出位图
	WSERR Save(const char *filename) const;
	bool IsCover(WPoint p) const;				// 判断是否覆盖一个点
};

#endif