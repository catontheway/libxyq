#pragma once
#include "_objinc.h"

class cObjWas : public cObjWasFather
{
public:
	int GetNowFrame(){ return now_frame; }
	int GetWidth(){ return m_pFile->GetWidth(); };
	int GetCenter();
	vector<int> m_oldmask;
	//图片上次的中心坐标
	int m_xold = 0;
	int m_yold = 0;
	int GetDataID(){ return GetFrameIndex(m_pFile->m_Picture.Spr.GetMaxFrame(), now_frame, m_pFile->m_Picture.Spr.GetDirectionNum(), m_direction); }
	RECT m_PreShowRect;
	void operator=(cObjWas& file);

	cObjWas();
	void Set(cWasFile* p);
	bool ShowOnScreen(uchar* pPic, RECT& rect)
	{
		if (!m_NeedShow)return true;
		if (!m_pFile)return false;
		CSprite& spr = m_pFile->m_Picture.Spr;
		if (!spr.m_bLoad)return true;
		spr.m_pOwner = this;
		spr.ShowOnScreen(pPic, rect);
		return true;
	}
	bool Show(uchar* pPic, RECT& rect, cMyMap* pMap)
	{
		if (!m_NeedShow)return true;
		if (!m_pFile)return false;
		CSprite& spr = m_pFile->m_Picture.Spr;
		if (!spr.m_bLoad)return true;
		spr.m_pOwner = this;
		return spr.Show(pPic, rect, pMap);
	}
	bool m_NeedShow;

	bool m_bStatic;

	//如果帧数改变,返回true否则返回false
	bool isFrameChange2Next();
	RECT GetPicRange();
	cWasFile* m_pFile;
};