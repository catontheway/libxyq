#pragma once
#include "_uiinc.h"

class cDescribe :public cInterfaceFather
{
public:
	void OnOff(bool bonoff);
	void Set(int xMouse, int yMouse, ulong BigHead, int num, string* pTex, ulong* colorlist = 0, int yOffset = 25);
	bool Init();

	virtual bool ProcessInput(){ return true; }
	virtual bool CheckL();
	virtual bool Show(cCanvas* pCanvas);
	cObjWas m_Back;
	static cWasFile m_DescribeBack;
private:
	ulong m_Color[32];

	bool m_bInit = false;
	cWasFile m_BigHead;
	cText  m_Text[32];
	int m_Num;
};



// œ‘ æ√Ë ˆ?
class cItemSelect
{
public:
	vector<cWasFile> m_ItemHead;
	vector<cText>  m_tItemNum;
	vector<int> m_ItemNum;
	void Init();
	int Process(int xMouse, int yMouse);
	void Show(cCanvas* pCanvas);
	void Move(int xPos, int yPos);
	void Update(sItem2* it = nullptr);
	cDescribe m_Describe;
	void SetSelectMark(int id);
private:
	bool m_bInit = false;
	int m_Select;
	int m_xPos;
	int m_yPos;
	RECT m_Rect;
	cWasFile m_SelectMark;
	cWasFile m_MouseOnMark;
	sItem2* _it = nullptr;
};