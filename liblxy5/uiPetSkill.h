#pragma once
#include "_uiinc.h"

class cInterfacePetSkill :public cInterfaceFather
{
public:
	int m_ItemDataTime = 0;
	bool Move(int x, int y);
	void MoveSkillHead(int x, int y);
	void UpdateData(cPropertyData* data, sZiZhi& zz, bool candashu);
	void UpdateData(cPetData* pPetData, bool candashu)
	{
		UpdateData(pPetData, pPetData->m_ZiZhi, candashu);
	}

	void NextPage(bool bnext = true);
	bool Init();
	virtual bool ProcessInput();
	virtual bool CheckL();
	void OnOff(bool NeedShow);
	bool CheckRB();
	virtual bool Show(cCanvas* pCanvas);
	int m_FightID = 0;
	cWasFile m_back;
	cObjWas m_Cancel2;
	RECT m_Rect;
	bool m_bDaShuMode = 0;
	cObjWas m_EquipBackp[6];
	cWasFile m_EquipHead[6];

//private:
	bool m_bCanDaShu = false;
	bool m_bInit = false;
	int m_SkillSelect;

	cText m_DaShuText[2];
	int m_DashuSkillSelect;
	bool  InitDaShuMode();//如果角色的道具栏里没有技能书,返回False;
	cWasFile m_DaShuHead[20/*9*/];
	int    m_DaShuItemId[20/*9*/];//记录角色的哪里有技能书
	cPropertyData* m_pPetData;
	cText m_TPetProPerty[9];
	int m_SkillPage = 0;
	int m_NumSkill;
	cWasFile m_SkillHead[12];
	sItem2* m_pEquip[6];
	cWasFile  m_EquipBack;

	cObjWas m_SkillSelectHead;
	int m_DaShuNum;
	cWasFile m_DaShuBack;
	cWasFile m_NextPage;


	cDescribe m_Describe;
};
