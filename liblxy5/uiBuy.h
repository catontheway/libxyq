#pragma once
#include "_uiinc.h"

class  cInterFaceBuy : public cInterfaceFather
{
public:

	void UpdateText();
	RECT m_Rect;
	cWasFile m_MouseOnMark;

	cWasFile m_SelectMark;
	int m_TrueSelect;
	int m_TrueSelect2;
	virtual bool ProcessInput();
	virtual bool CheckL();
	bool CheckRB();
	bool Init();
	void Open(int id);
	bool Set(sItem2& item, int rate);
	bool Move(int x, int y);
	bool Show(cCanvas* pCanvas);
	array<cText, 6> m_Text;

	vector<sItem2> m_Item;
	vector<int> m_pricerate;
	array<cWasFile, 20> m_ItemHead;
	void OnOff(bool bshow);
	cDescribe m_Describe;
	void Reset();
private:
	int m_ItemNum = 0;
	int m_page = 0;
	void AddPage();
	void SubPage();
	void Update();
	bool m_bInit = false;
	int m_PriceTotal;
	void CoutTotal();
	//cWasFile m_Back;

	cWasFile m_Button;
	cInterfaceNumShuRu m_NumBuy;

	cWasFile m_Left;
	cWasFile m_Right;
};