#pragma once
#include "_uiinc.h"

// Дђдь
class cInterfaceDaZao :public cInterfaceFather
{
public:
	bool Init();
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	bool CheckRB();
	virtual void OnOff(bool NeedShow);
	bool Move(int x, int y);
//private:
	bool CheckEquip(int type);
	bool m_bInit = false;
	//cWasFile m_Back;
	cText m_tMoneyNeed;
	cText m_tMoneyHave;
	cObjWas m_Head[2];
	int m_Item[2];
	cObjWas m_Button;
	cText m_tButton;
	array<cObjWas, 6> m_Buttons;
	array<cText,6> m_tButtons;
	int m_MoneyNeed;
	cWasFile m_SelectMarks[2];
};
