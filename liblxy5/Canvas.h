#pragma once
#include "_asert.h"
//画布单位
struct sCanvasCube  
{
	static const int DEEP_20 = 20;
	int  PicNumOfPreFrame = 0;//前一帧的图片数
	int  NeedReDraw = false;//是否需要重画
	bool m_bCover已覆盖数据;
	sCanvasCube()
	{
		for (int i = 0; i < DEEP_20; i++)
		{
			pPicList[i] = 0;
			PicType[i] = 0;  //0 CWFile  1 cObj 2 cText 3 cwfilep 4 objfather
			ShowMode[i] = 0;
		}
	}

#pragma region 

//	RECT rect;//位置
//	uchar* m_ShowData;
	cObjWasFather m_Data;
	//在画布中的单位, 最多有20个.多于20个的话...再说
	void* pPicList[DEEP_20];
	int  PicType[DEEP_20];  //0 CWFile  1 cObj 2 cText 3 cwfilep 4 objfather

	int  ShowMode[DEEP_20];
	int  PicNumOfCurrFrame = 0;   //当前帧的图片数
	
	bool  PreCover=false;//前一帧是否有覆盖

	bool Add(cWasFile* p, int showmode, bool bMove, bool bCover, bool bChange);
	bool Add(cObjWasFather* p, int showmode, bool bMove, bool bCover);
	bool Add(cText* p, bool bMove);
	bool Add(cObjWas* p, int showmode, bool bMove, bool bCover, bool bChange);
	bool CheckNum(bool bCover);
	
	RECT m_Rect;

#pragma endregion 

};
//画布 单例单例
class cCanvas
{
public:
	int  m_Time=0;
	bool Init();
	bool Add(cWasFile* pPic, int showmode, bool bCover = false);
	bool Add(cText* pTex);
	bool Add(cObjWasFather* pObj, int showmode, bool bCover = false);
	bool Add(cObjWas* p, int showmode  ,  bool bCover=false);

	//HDC m_MemDC; //显示文字时用于过渡
	array<sCanvasCube, 450> m_CanvasCube/*[300]*/;
	bool Show();
	bool SetRedraw(const RECT& rect);
	void SetRedrawAll(bool ball = true);
	bool m_NeedShowMap = false;

	//HDC m_hdc;
	~cCanvas();
	
	
	
private:
	bool Free();


	void SwapBuf();
	HPEN hPen;


	bool m_bInit = false;
	
};
