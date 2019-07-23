#pragma once
#include "_objinc.h"

class cWasFile;
class cObjWasFather
{
public:
	int	m_x = 0;
	int	m_y = 0;
	int	m_xOffset = 0;
	int	m_yOffset = 0;
	int	m_xOffset2 = 0;
	int	m_yOffset2 = 0;
	int	m_ShowHeight = 0;
	int	m_ShowWidth = 0;
	int	m_direction = 1;
	int	m_bTwinkle = 0;
	int m_FrameGap = 10;
	int	m_StepUpdate = 0;
	int	now_frame = 0;
	int	m_bShadow = 0;
	int	m_bShine = 0;
	int m_Width = 0;
	int m_Height = 0;
	void SetFrame帧(int frame)
	{
		if (now_frame != frame)m_bMove = true;
		now_frame = frame;
	}
	int  GetFrame(){ return now_frame; }


	int GetShowWidth(){ if (m_ShowWidth) return m_ShowWidth; else return m_Width; }
	void SetShowWidth(int k);
	int GetShowHeight(){ if (m_ShowHeight)return m_ShowHeight; else return m_Height; }
	void SetShowHeight(int k);

	void SetxOffset(int xOff);
	void SetyOffset(int yOff);
	void SetxOffset2(int xOff2);
	void SetyOffset2(int yOff2);
	int  GetxOffset(){ return m_xOffset; };
	int  GetyOffset(){ return m_yOffset; };
	int  GetxOffset2(){ return m_xOffset2; };
	int  GetyOffset2(){ return m_yOffset2; };

	int GetHeight(){ return m_Height; }
	int GetWidth(){ return m_Width; }
	void SetHeight(int h){ m_Height = h; }
	void SetWidth(int w){ m_Width = w; }

	int GetX(){ return m_x; }
	int GetY(){ return m_y; }
	void SetXY(int x, int y){ m_x = x; m_y = y; }
	void SetX(int x){ m_x = x; }
	void SetY(int y){ m_y = y; }


	void Init(cObjWasFather* pObj, int alpha = 100); //创建一个和pObj一样大的图片,之前的图片会被释放掉
	void Reset(cObjWasFather* pObj, int alpha = 100);
	void Reset2(cWasFile* pic);
	void Draw(cObjWasFather* pObj, int xpos = -1, int ypos = -1, int alpha = 100);  //在图片上画新的图
	void GetRect(RECT& rect1);
	uchar* m_pData = 0;
	uchar* m_pAlpha = 0;
	bool m_NeedShow = true;
	bool m_bMove = false;
	RECT m_PreShowRect;
	~cObjWasFather();
	// 更换数据new长度比较
	int m_OldDataSize = 0;
};