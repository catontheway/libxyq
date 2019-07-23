#pragma once
#include "_uiinc.h"

class cInterfaceLearnSkill :public cInterfaceFather
{
public:
	bool CostSkill(int needexp, int needmoney);
	array<cWasFile, 2> m_SkillSelectBack;
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	bool LearnSkill(bool cost = true);
	void OnOff(bool needshow);
	bool Move(int x, int y);
	bool Init();
	bool CheckRB();
	//cWasFile m_Back;

	array<cObjWas, 2> m_Button;
	array<cText, 2> m_tButton;

	RECT m_Rect;
	int m_SkillSelect;
	array<cWasFile,7> m_MengPaiSkillHead;
	array<cText,7> m_tMengPaiSkill;
	array<cText,7> m_tMengPaiSkillLv;
	cText m_tSkillSelectHead;
	cText m_tMiaoShu;
	cText m_tNeedExp;
	cText m_tHaveExp;
	cText m_tNeedMoney;
	array<cText,3> m_tHaveMoney;
	void Update();
	void SetSkillSelect(int select);
private:
	bool m_bInit = false;
};
