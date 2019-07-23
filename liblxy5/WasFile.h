#pragma once
#include "_objinc.h"

class cWasFile
{
public:
	//void Save(string name);
	uchar *lp = 0;
	INT m_lpSize = 0;
	int m_PosType = 1;
	RECT m_PreShowRect;


	void SetShine(bool needshow){/*if(needshow!=m_Picture.m_bShine)*/ m_bMove = true; m_Picture.m_bShine = needshow; }
	int GetCenter(){ return GetX() + (GetWidth() >> 1); }
	int GetX(){ return m_Picture.GetX(); }
	int GetY(){ return m_Picture.GetY(); }
	void SetXY(int x, int y){ m_Picture.SetXY(x, y); m_bMove = true; }
	void SetX(int x){ if (m_Picture.GetX() != x)m_bMove = true;  m_Picture.SetX(x); }
	void SetY(int y){ if (m_Picture.GetY() != y)m_bMove = true; m_Picture.SetY(y); }
	int GetWidth(){ return m_Picture.GetWidth(); }
	int GetHeight(){ return m_Picture.GetHeight(); }
	int GetShowWidth(){ return m_Picture.GetShowWidth(); }
	void SetShowWidth(int k){ m_Picture.SetShowWidth(k); }
	int GetShowHeight(){ return m_Picture.GetShowHeight(); }
	void SetShowHeight(int k){ m_Picture.SetShowHeight(k); }
	int GetDirectionNum(){ return m_Picture.Spr.GetDirectionNum(); }
	void SetxOffset(int xOff){ m_Picture.SetxOffset(xOff); }
	void SetyOffset(int yOff){ m_Picture.SetyOffset(yOff); }
	void SetxOffset2(int xOff2){ m_Picture.SetxOffset2(xOff2); }
	void SetyOffset2(int yOff2){ m_Picture.SetyOffset2(yOff2); }
	int  GetxOffset(){ return m_Picture.m_xOffset; };
	int  GetyOffset(){ return m_Picture.m_yOffset; };
	int  GetxOffset2(){ return m_Picture.m_xOffset2; };
	int  GetyOffset2(){ return m_Picture.m_yOffset2; };
	bool m_bMove;
	ulong m_NowID = 0;

	bool m_isStatic;
	cWasFile();
	~cWasFile();
	void GetPicRange(RECT& rect);//得到图片的范围
	RECT GetPicRange();//得到图片的范围
	bool isSelectOn(int x, int y);
	void SetStatic(bool bIsStatic){ m_isStatic = bIsStatic; }
	bool m_NeedShow = true;

	int m_Type;
	bool LoadBMP(string path);
	bool LoadMap(ulong uid);
	bool Load(ulong uid, sChangeColorData* pChangeColorData = 0, string str = "");
	void LoadWav(ulong uid, int position = 0, bool bPlay = true);
	void PlayWav();
	bool GetFileP(ulong uid, ifstream*& f, const function<void(const uchar *data18)> &cb = nullptr);
	bool GetFileP(ulong uid, CWdf* wdfs[], int size, ifstream*& f, const function<void(const uchar *data18)> &cb = nullptr);
	bool Show(uchar* Pic, RECT& rect, cMyMap* pMap)
	{
		if (!m_NeedShow)return true;
		return m_Picture.Show(Pic, rect, pMap);
	}

	void ShowOnScreen(uchar* Pic, RECT& rect){ m_Picture.ShowOnScreen(Pic, rect); };
	//狼: 上一帧,打击用？...然而并没有被用到
	void SubFrame(){ m_Picture.m_StepUpdate = 0; (m_Picture.GetFrame() > 0) ? (m_Picture.SetFrame帧(m_Picture.GetFrame() - 1)) : m_Picture.SetFrame帧(0); }
	void SetFrame(int frame);
	int  GetNowFrame(){ return m_Picture.GetFrame(); }
	int  GetMaxFrame(){ return m_Picture.Spr.GetMaxFrame(); }
	bool GetWillNextFrame();
	bool Free();
	bool CloseWDF();
	static	bool Open(const char* FileName);
	static bool OpenMap(const char* filename);
	static const int c64 = 64, c8 = 8;
	static CWdf* m_pWdf[c64];
	static CWdf* m_pWdfMap[c8];

	CPicture m_Picture;
	cMyWav m_Wav;
	//bool m_bStatic;
	bool NextFrame();
	bool m_bCircle = true;
	bool PreFrame();
	void SetDirection(int dir);
	bool m_ShowOnce = false;//只显示一次
private:
	////文件类型定义
	//struct ExsDate
	//{
	//	ushort  hdw;  //头两个字节
	//	ulong sst;  //第七个字节开始的四个字节
	//	ulong nst;  //第九个字节开始的四个字节
	//	ulong dss;  //倒数六个字节开始的四个字节
	//	ushort sss;	//第五个字节开始的二个字节
	//	uchar dsg[3];//倒数三个字节
	//};
	//int setfiletype(ExsDate esdate);

	int  m_Direction;
	ulong m_Offset;
public:
	ulong m_Size;
};