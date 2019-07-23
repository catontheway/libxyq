#pragma once
//画布单位
struct sCanvas  
{
	struct sCube
	{
		void* pPic = nullptr;
		// 0 CWFile  1 cObj 2 cText 3 cwfilep 4 objfather
		int type = -1;
		int screen = -1;
		bool isValid() { return pPic != nullptr && type >= 0 && screen >= 0; }
	};
	cObjFather m_Data;
	int  PrePicNum=-1;//前一帧的图片数
	int  PreCover=FALSE;//前一帧是否有覆盖
	int  NeedReDraw=TRUE;//是否需要重画
	BOOL Add(CWFile* p, int showmode, BOOL bMove, BOOL bCover, BOOL bChange);
	BOOL Add(cObjFather* p, int showmode, BOOL bMove, BOOL bCover);
	BOOL Add(cText5* p, BOOL bMove);
	BOOL Add(cWfileP* p, int showmode, BOOL bMove, BOOL bCover, BOOL bChange);
	BOOL CheckNum(BOOL bCover);
	BOOL m_bCover;
	RECT m_Rect;

	std::vector<sCube> _cubes;
	void show(sCube& cube, bool onMap, bool text);
};
//画布
class cCanvas5
{
public:
	int  m_Time=0;
	BOOL Init();
	BOOL Add(CWFile* pPic, int showmode, BOOL bCover = FALSE);
	BOOL Add(cText5* pTex);
	BOOL Add(cObjFather* pObj, int showmode, BOOL bCover = FALSE);
	BOOL Add(cWfileP* p, int showmode,  BOOL bCover=FALSE);
	BOOL Free();
	std::vector<sCanvas> _canvas;
	BOOL Show();
	void SwapBuf();
	HPEN hPen;
	//HDC m_hdc;
	~cCanvas5();
	BOOL SetRedraw(RECT rect);
	void SetRedrawAll(BOOL ball=TRUE);
	BOOL m_NeedShowMap = FALSE;
private:
	BOOL m_bInit = FALSE;
	
public:
	int _index = 0;
	void push();
};
