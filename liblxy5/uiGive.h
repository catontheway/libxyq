#pragma once
#include "_uiinc.h"


class  cInterfaceGive :public cInterfaceFather
{
public:
	void AddItem(int select);
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	void ReCoverOnce();//收到的货不是我需要的,退还
	bool CheckRB();
	void OnOff(bool NeedShow);
	bool Init();
	bool Move(int x, int y);
	bool m_bInit = false;
	void SetTarget(cObj* pTarget);
	cObj* GetTarget();
	sItem2 m_ItemGive[3];
	cInterfaceNumShuRu m_NumItem[3];
	int    m_ItemGiveOwner[3];
	cObj* m_pTarget;
private:

	cInterfaceNumShuRu m_NumShuru;
	cWasFile m_SelectMark;
	cWasFile m_MouseOnMark;
	int m_ItemSelect;
	void UpDate();

	//cWasFile m_Back;
	cWasFile m_Button;
	cText  m_tButton;

	int m_ItemNum[20];
	cWasFile m_ItemHead[20];
	cText m_tItemHead[20];
	cWasFile m_ItemGiveHead[3];


	cText m_tXIanJin;
	RECT m_Rect;
};

