#pragma once
#include "_objinc.h"

class CPicture :public cObjWasFather
{
public:
	//图片上次的中心坐标
	int m_xold = 0;
	int m_yold = 0;
	int getFrameIdx(){ return GetFrameIndex(Spr.GetMaxFrame(), now_frame, Spr.GetDirectionNum(), m_direction); }
	//DATEHEARD* GetDataID2(){ Spr.m_pDataOffsetList[GetDataID()] };
	CPicture(void);
	~CPicture(void);
	// 载入数据
	void Load(void* pdate, int size, int type, sChangeColorData* pChangeColorData = 0);
	void Free();
	CSprite Spr;

	bool Show(uchar* Pic, RECT& rect, cMyMap* pMap)
	{
		if (!Spr.m_bLoad)return true;
		Spr.m_pOwner = this;
		return Spr.Show(Pic, rect, pMap);
	}
	void ShowOnScreen(uchar* pPic, RECT& rect)
	{
		if (!Spr.m_bLoad)return;
		Spr.m_pOwner = this;
		Spr.ShowOnScreen(pPic, rect);
	}

};

