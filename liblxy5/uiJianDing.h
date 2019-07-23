#pragma once
#include "_uiinc.h"

class cInterfaceJianDing :public cInterfaceFather
{
public:
	void SetMode(int id){ m_Mode = id; }
	bool Init();
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	virtual void OnOff(bool NeedShow);
	bool Move(int xPos, int yPos);
private:
	int m_ItemSelect;
	int m_NowItemSelect;
	int m_Mode = 0;//0表示鉴定 1表示收购 2收购一切 3表示镶嵌宝石
	bool m_bInit = false;
	//cWasFile m_Back;
	cText m_tPrice;
};

