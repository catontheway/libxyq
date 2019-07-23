#pragma once
#include "_uiinc.h"

class cMenu :public cInterfaceFather
{
public:
	void OnOff(bool NeedShow){};
	cWasFile* m_NowSelectPic;
	bool Move(int x, int y);

	cText m_Text;
	int m_gap;
	int m_SelectPre;
	cWasFile m_Trade;
	cWasFile m_back;
	cWasFile m_Attack;
	cWasFile m_Team;
	cWasFile m_Pet;
	cWasFile m_Item;
	cWasFile m_SkillAccelater;
	cWasFile m_Info;
	cWasFile m_Give;
	cWasFile m_BangPai;
	cWasFile m_System;
	cWasFile m_job;
	bool Init();
	bool Show(cCanvas* pCanvas);
	void Select(int x);
	virtual bool ProcessInput();
	virtual bool CheckL();
};
