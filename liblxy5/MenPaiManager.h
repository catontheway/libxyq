#pragma once
#include "_global.h"


//代表一个主技能
class cZhuJiNeng
{
public:
	int m_ID; //主技能ID
	string m_Name;
	ulong m_SmallHead;
	ulong m_BigHead;
	string m_Text;//描述  包含什么技能
	string m_Text2;//描述2   学习效果
	//包含技能
	int m_NumSkillInclude;
	// 原本12
	array<int, 14> m_Limit技能解锁;
	array<int, 14> m_SkillIncludeID;

};
//代表一个门派
class cMengPai
{
public:
	int m_ID;
	string m_Name;			//门派的名字
	string m_ShiFuName;    //门派师父的名字
	string m_ShiFuMap; //门派师父所在地图
	string m_XunLuoMapName;//师门巡逻的地点
	array<cZhuJiNeng, 7> m_MainSkill;//主技能
};



const int c_SkillNum = 206;

class cMengPaiManager
{
public:
	bool  Init();
	cMengPai* GetMengPai(cCharacter* pc);
	cMengPai* GetMengPai(int ID){ if (ID < 0 || ID >= c_NumofCharacter)return nullptr;  return &m_MengPai[ID]; }
	sSkill*   GetSMSkill(int ID){ return &m_SkillList[ID]; }
	cMengPai  m_MengPai[c_MenPaiNumber];//门派表
	sSkill m_SkillList[c_SkillNum];//师门技能表
//	void lvUpMainSkill(cPcData& pcDate, int lv, int ID, bool isHero = false);
private:
	bool m_bInit;
};