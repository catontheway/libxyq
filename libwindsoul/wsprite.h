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

		Description:		RLE Sprite 头文件
 		Original Author:	云风
		Authors:
		Create Time:		2001/6/1
		Modify Time:		2001/11/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_SPRITE_H
#define _WINDSOUL_SPRITE_H

#include "wsaddon.h"

#define _ERR_RLESPRITE 'r'
#define WS_RLESPRTIEFILEERR MAKE_ERR(_ERR_RLESPRITE,'FLE')
#define BLIT_ALTERNATE		0x1
#define BLIT_PALETTE		0x5
#define BLIT_EDGE			0x6
 
typedef WPixel* WPalette;
  
struct WSpriteStruct;  

class WINDSOULADD_API WSprite : public WObject {
public: 
	WSprite() {}
	WSprite(WPalette pal,void *data) { Create(pal,data); }
	WSprite(const WSprite& sprite);
	~WSprite();
  
	void Create(const WPalette pal, void *data);   
	
	int GetW() const;
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;	// 获得 Draw 函数指针
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WSpriteStruct *GetSpriteStruct() const { return reinterpret_cast<WSpriteStruct *>(objdata); }	// 获取数据结构
	void SetUserData(DWORD userdata) const;	// 设置用户数据
	bool IsCover(int x,int y) const;		// 判断是否遮挡
	bool IsCover(WPoint p) const { return IsCover(p.x,p.y); }
	const WSprite& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
	const WSprite& operator()(WPalette addpal) const { SetUserData((DWORD)addpal); return *this; }
	WSERR Load(const char *filename,int *size=0);	// 读文件

	void *Zoom(int w,int h,int bSpecialPal) const;
};

class WINDSOULADD_API WSpritePak {
	void *m_Data;   
	int m_Direction;
	int m_Width;
	int m_Height;
	int m_Kx;
	int m_Ky;
	WPalette m_Pal;
	mutable WPalette m_AddPal;
	DWORD m_Size;
protected:
	int m_Frame;
	WSprite *m_Spt;
public:
	enum { GreyPal=0, RedPal=1, GreenPal=2, BluePal=3, YellowPal=4, BlackPal=5 };
	WSpritePak() : m_Spt(0),m_AddPal(0),m_Size(0) {}
	virtual ~WSpritePak() { Destroy(); }
	WSERR Destroy();								// 销毁
	bool IsValid() const { return (m_Spt!=0); }		// 判断是否有效
 	const WSprite* operator[](int dir) const { ASSERT(IsValid()); return m_Spt+dir*m_Frame; }
	WSERR Load(const char *filename,int skip=0,int size=0);	// 读文件
	void InitAdditionalPal() const;					// 初始化附加 Pal
	int GetDirection() const { return m_Direction; }// 读方向数
	int GetFrame() const { return m_Frame; }		// 读帧数
	int GetWidth() const { return m_Width; }		// 读宽度
	int GetHeight() const { return m_Height; }		// 读高度
	int GetX() const { return m_Kx; }				// 读X
	int GetY() const { return m_Ky; }				// 读Y
	DWORD GetSize() const { return m_Size; }
	const WPalette LightPal(int level) const;		// 返回亮度 Pal
	const WPalette ColorPal(int color) const;		// 返回彩色 Pal
private:
	virtual void ReadAdditional(void *header) {}		// 读附加信息
};
 
class WINDSOULADD_API WSpriteAni : public WSpritePak {
	int *m_Delay;
	mutable int m_CurrentFrame;
	mutable int m_DelayFrame;
public:
	struct Pair {
		short current;
		short delay;
	};
	WSpriteAni();
	~WSpriteAni();
	void Set(int frame=0);
	void Set(Pair &pair,int frame=0) const;
	int TotalFrame() const;
	const WSprite& NextFrame(bool *change=0) const;
	const WSprite& CurrentFrame() const {
		return m_Spt[m_CurrentFrame];
	}
	const WSprite& NextFrame(Pair &pair,bool *change=0) const;
private:
	void ReadAdditional(void *header);
};

#endif 