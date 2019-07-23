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

		Description:		风魂辅助类
 		Original Author:	云风
		Authors:
		Create Time:		2000/12/8
		Modify Time:		2001/10/10

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_HELPER_H
#define _WINDSOUL_HELPER_H

#pragma warning (disable: 4786 )
#pragma warning (disable: 4660 )

 ///	常用运算模板
/////////////////////////

template<class T> inline T MIN (T i, T j) { return ((i < j) ? i : j); }
template<class T> inline T MAX (T i, T j) { return ((i > j) ? i : j); }
template<class T> inline T MOD (T i, T j) { return (i<0)?(j-1)-((-i-1)%j):i%j; }
template<class T> inline T DIV (T i, T j) { return (i<0)?-((-i-1)/j)-1:i/j; }
template<class T> inline T ABS (T i) { return (i>0)?i:-i; }
template<class T> inline void SWAP(T &x, T &y) { T t; t=x,x=y,y=t; }

#ifdef _BCB
#define _C(c) (((c)<<8|(c)>>8)&0xffff)
#else
#define _C(c) (c)
#endif

 ///	WPoint 点类
/////////////////////////

template <class T>
struct WPointEx { 
    T x; 
    T y; 
	WPointEx() {}
	WPointEx(T x,T y) :x(x),y(y) {}
	WPointEx(const WPointEx &p) { x=p.x,y=p.y; }
	WPointEx operator+(const WPointEx &p) const { return WPointEx(x+p.x,y+p.y); }
	WPointEx operator-(const WPointEx &p) const { return WPointEx(x-p.x,y-p.y); }
	bool operator==(const WPointEx &p) const { return (x==p.x && y==p.y); }
	bool operator!=(const WPointEx &p) const { return (x!=p.x || y!=p.y); }
	WPointEx& operator+=(const WPointEx &p) { x+=p.x,y+=p.y; return *this; }
	WPointEx& operator-=(const WPointEx &p) { x-=p.x,y-=p.y; return *this; }
	WPointEx& operator=(const WPointEx &p) { x=p.x,y=p.y; return *this; }
	bool IsLeft(const WPointEx &p) const { return x<p.x; }							// 是否在点的左边
	bool IsRight(const WPointEx &p) const { return x>p.x; }							// 是否在点的右边
	bool IsUp(const WPointEx &p) const { return y<p.y; }								// 是否在点的上边
	bool IsDown(const WPointEx &p) const { return y>p.y; }							// 是否在点的下边
};

typedef WPointEx<int> WPoint;

 ///	WRect 矩形类
/////////////////////////

struct WRect {
	int x;
	int y;
	int w;
	int h;
	WRect() {}
	WRect(int x,int y,int w,int h) : x(x),y(y),w(w),h(h) {}
	WRect(WPoint &p,int w,int h) : x(p.x),y(p.y),w(w),h(h) {}
	bool IsIn(const WRect &rect) const;										// 是否在另一个矩形区域里
	bool IsOut(const WRect &rect) const;									// 是否在另一个矩形区域外
	WRect HorRect(const WRect &rect) const;									// 产生水平相交部分区域
	WRect VerRect(const WRect &rect) const;									// 产生垂直相交部分区域
	WRect& operator+=(const WPoint &p) { x+=p.x,y+=p.y; return *this;}
	WRect& operator-=(const WPoint &p) { x-=p.x,y-=p.y; return *this;}
	WRect operator+(const WPoint &p) const { return WRect(x+p.x,y+p.y,w,h); }
	WRect operator-(const WPoint &p) const { return WRect(x-p.x,y-p.y,w,h); }
	bool IsCover(const WPoint &p) const { return (x<=p.x && x+w>p.x && y<=p.y && y+h>p.y); }
};

inline bool WRect::IsIn(const WRect &rect) const
{
	return !(x<rect.x || y<rect.y || x>=rect.x+rect.w || y>=rect.y+rect.h ||
		x+w>rect.x+rect.w || y+h>rect.y+rect.h);
}

inline bool WRect::IsOut(const WRect &rect) const
{
	return (x>=rect.x+rect.w || x+w<=rect.x || y>=rect.y+rect.h || y+h<=rect.y);
}

inline WRect WRect::HorRect(const WRect &rect) const
{
	int left,width,top,height;
	left=MIN(x,rect.x);
	width=MAX(x+w,rect.x+rect.w)-left;
	top=MAX(y,rect.y);
	height=MIN(y+h,rect.y+rect.h)-top;
	return WRect(left,top,width,height);
}

inline WRect WRect::VerRect(const WRect &rect) const
{
	int left,width,top,height;
	left=MAX(x,rect.x);
	width=MIN(x+w,rect.x+rect.w)-left;
	top=MIN(y,rect.y);
	height=MAX(y+h,rect.y+rect.h)-top;
	return WRect(left,top,width,height);
}

 ///	内存分配
/////////////////////////

#define WAlloc(size) ((void*)new BYTE[(size)])
#define WFree(ptr) (delete []((BYTE*)(ptr)))

inline void WMemCpy(void *dest, const void *src, unsigned count)
{
	unsigned i;
	BYTE *d=(BYTE *)dest;
	const BYTE *s=(const BYTE *)src;
	for (i=0;i<count;i++,++d,++s)
		*d=*s;
}

 ///	字符串
/////////////////////////

DWORD WINDSOUL_API _stdcall WString2ID(const char* string);

#ifndef _BCB
__int64 WINDSOUL_API _stdcall WString2LID(const char* string);
#endif

#define WFourCC(str) ((DWORD)str[0]|(DWORD)str[1]<<8|(DWORD)str[2]<<16|(DWORD)str[3]<<24)

#endif