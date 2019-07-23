#pragma once
#include "_uiinc.h"

class cInterfaceXiuLian :public cInterfaceFather
{
public:
	void CheckInit(){ if (!m_bInit)Init(); };
	void setBB(bool isBB){ _isBB = isBB; }
	bool Leveupskill(int lvup);

	bool Init();
	void OnOff(bool NeedShow);
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	bool CheckRB();
	bool Move(int x, int y);
	void UpDate();

	cWasFile m_SkillSelectBack[2];
	//cWasFile m_Back;
	cWasFile m_Button[2];
	cText m_tButton[2];
	cText m_MiaoShu;
	cText m_TXiuLian[4];
	RECT m_Rect;
	bool _isBB = false;
private:
	int m_SkillSelect;
	bool m_bInit = false;
};