#pragma once
#include "_uiinc.h"


class cInterfaceConduct :public cInterfaceFather
{
public:
	void PrePare();
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	virtual void OnOff(bool NeedShow);
	bool CheckRB();
	void SetID(int id);
	bool  Init();
	bool Move(int x, int y);
	void Def(int id, bool bDef = true);
	void SetTarget(int id, int target);
private:
	cObj* m_pObj = 0;
	int m_Mode = -1;
	int m_FighterNum;

	//cWasFile m_Back;//÷∏ª”ΩÁ√Ê  0xCC7BC6C6
	bool m_bInit = false;
	cText m_Title;
	int  m_IdSelect;
	vector<cObjWas> m_Buttonp;
	vector<cText> m_tButtonp;
	vector<cText> m_tName;
	vector<cText> m_tTargetName;
};