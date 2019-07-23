#pragma once
#include "_uiinc.h"

class cState :public cInterfaceFather
{
public:

	void OnOff(bool NeedShow);
	array<cText, 9> m_TPetDate;
	array<cText, 32> m_TPcFnt; //27 门派  28 帮派 29称谓 30降级 31加点速度
	array<cObjWas, 11> _btns;
	array<cText, 11> _tBtns;
	cWasFile m_LeveUp;
	cText m_Text;
	cObjWas m_ButtonLvDown;   //升级
	cObjWas m_ButtonLvUp;   //升级
	cObjWas m_PointSpeed;
	cObjWas m_ButtonSkill;  //技能
	int m_SkillPage;//如果技能数超过12个,需要翻页
	array<cWasFile, 12> m_SkillHead;
	int m_SkillSelect;
	cObjWas m_SkillHeadSelect;
	////查看资质

	array<cText, 2> m_TSkillHeadSelectDate;
	cObjWas m_SeeZZ;

	cInterfacePetSkill m_PetSkill;
	bool UpDatePcDate();
	void UpdateAddPointB();
	void UpdateProPerty();
	void UpDateHp();
	void UpDateMp();
	void UpDateCp();
	vector<cObjWas> m_Addp;
	vector<cObjWas> m_Subp;
	cWasFile m_Add;
	cWasFile m_Sub;

	cWasFile* m_pShow;
	bool Init();
	bool ProcessInput();
	bool CheckL();
	bool CheckRB();
	bool SetCharacter(cCharacter* pc);
	cPcData* m_pPCData;
	bool Show(cCanvas* pCanvas);
	bool Move(int x, int y);
	int m_NowFighter;
	cWasFile m_State;
	void switchAddPoint();
	bool CheckAddPoint(){ return m_bAddPoint; }

private:
	bool m_bAddPoint;
	bool m_isNeedLvupOfFriend = false;
	bool m_bInit = false;
	vector<int> _pointTemps;
	cCharacter *_cC = nullptr;
};

