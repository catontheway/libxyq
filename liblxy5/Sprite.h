#pragma once
#include "_objinc.h"

struct sChangeColorData;
class cMap;
class cMyMap;
class CSprite
{
public:
	cObjWasFather* m_pOwner;
	int getFrameIdx(){ return GetFrameIndex(m_Frame, m_pOwner->now_frame, m_MaxDirection, m_pOwner->m_direction); }
	int GetHeight(){ return m_Height; }
	int GetWidth(){ return m_Width; }
	int GetDirectionNum(){ return m_MaxDirection; };

	DATEHEARD* m_pDataOffsetList;
	HBITMAP DIBtoDDB(ushort* data, BITMAPINFO*  pBmpInfo);
	CSprite(void);
	~CSprite(void);
	bool Load(void* lp, long size, int type, sChangeColorData* pChangeColorData = 0);
	bool LoadBMP(string path);
	int GetMaxFrame(){ return m_Frame; }

	int m_kx;				// 关键点 X
	int m_ky;				// 关键点 Y
	unsigned char** lpAlpha;	// alpha数据指针
	unsigned char** lpDate;		// 图像数据指针
	void FreeDatelp(void);
private:
	int m_Frame;			// 每方向帧数
	inline bool CountCross(int xPos, int yPos, RECT destrect, RECT& picrectout, RECT& nowrectout, int& xOffPic, int& yOffPic, int& xOffDes, int& yOffDes);
	int pitch;					// 扫描行宽度


	int m_Width;			// 宽度
	int m_Height;			// 高度
	int m_MaxDirection;		// 方向数



public:
	bool ShowOnScreen(uchar* Pic, RECT& rect);
	bool Show(uchar* Pic, RECT& rect, cMyMap* pMap);

	int  m_Bottom = -1;
	bool isInMask(int x, int y, int w, int h, int xMask, int yMask, int wMask, int hMask);
	bool CheckMask(int xStart, int yStart, int Width, int Height, int xOff2, int yOff2, cMap* pmap, int a, uchar* pPic);


	bool ShowPart(int xOffset, int yOffset, int x, int y, int Width, int Height, int direction, bool bStatic = 0);
	bool m_bLoad = false;
private:
	void mread(void* Dst, unsigned int size, unsigned int n);
	uchar* flp;
	void mcreat(void* ilp, unsigned int size);
	void mseek(long offset);
	uchar* fstr;
public:
	void mclose(void);
private:
	unsigned int fsize;
};
