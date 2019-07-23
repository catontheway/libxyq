#pragma once
#include "_uiinc.h"

//struct sSkill;
class cInterfaceJiNeng :public cInterfaceFather
{
private:

	int m_MiaoShuID = -1;
public:
	cWasFile m_SelectBackXiuLian;
	cObjWas* m_pPreMode = 0;
	void SetMode(ulong mode);
	void OnOff(bool NeedShow);
	bool CheckL();
	cWasFile m_Data;
	vector<cText> m_BText;
	array<cText, 7> m_ZhuJiNengLv;
	array<cText, c_NumFuZhu> m_FuZhuJiNengLv;
	cInterfaceJiNeng();

	ulong m_ZhuJiNeng;
	ulong m_XiuLian;
	ulong m_FuZhuJiNeng;


	cObjWas m_SmB;
	cObjWas m_FuZhuB;
	cObjWas m_learnSkillB;
	cObjWas m_XiuLianB;
	bool Init();
	bool ProcessInput();
	void Set(ulong ID);
	bool Show(cCanvas* pCanvas);
	bool Move(int x, int y);
	void MoveMainSkill(int x, int y);
	void MoveFuZhuSkill(int x, int y);
	void MoveXiuLian(int x, int y);
	array<cWasFile, 7> m_ZhuJiNengHead;
	array<cWasFile, 6> m_SpecialSkill;
	int    m_JiNengHeadNum;

	array<sSkill*, 14> m_JiNengHeadData;
	array<cWasFile, 14> m_JiNengHead;
	array<cWasFile, 6> m_TeJiHead;
	int    m_NumMiaoShu = 0;
	vector<cText>  m_MiaoShu;
	int    m_SpeciallSkillSelect;
	int    m_JiNengSelect;
	int    m_SkillSelect;
	int    m_dustSkillSelect;
	vector<cText>  m_TXiuLian;
	bool   UpdateJiNeng();
	bool   m_bUpdateJiNeng = 0;
	bool   UpdateXiuLian();
	bool   UpdateMainSkill();
	bool   UpdateFuZhuJiNeng();
	void setCharator(cCharacter *charactor){ _charactor = charactor; }
private:
	bool m_bInit = false;
	cCharacter *_charactor = nullptr;
};

