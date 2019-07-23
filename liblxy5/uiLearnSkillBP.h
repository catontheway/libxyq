#pragma once
#include "_global.h"

class cBangPaiJiNengXueXi:public cInterfaceFather
{
public:
	bool Leveupskill(int lvup);
	bool Init();
	void OnOff(bool NeedShow);
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	bool CheckRB();
	bool Move(int x, int y);
	void UpDate();
	void SetSkillSelect(int select);
	//cWasFile m_Back;


	cWasFile m_SkillHead[14];
	cText m_tSkillHead[14];
	cWasFile m_Button[2];
	cText m_tButton[2];
	cText m_tExp;
	cText m_tNeedBangGong;
	cText m_tNeedExp;
	cText m_tNeedMoney;
	cText m_tXueFei;
	cText m_tChuBei;
	cText m_tMiaoShu;
	cWasFile m_SelectMark;

	int m_SkillSelect;
	
	int m_NeedExp;
	int m_NeedMoney;
	int m_NeedBangGong;

//private:
	static const int m_BangpaiSkilllv = 160;
	bool m_bInit = false;
};

