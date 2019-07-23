#pragma once

//代表一个技能
struct sSkill
{
	string m_Name;
	int    m_Id = 0;
	string m_Text;//描述
	string m_tCost;//消耗的描述
	string m_tCostHpMp;
	int    m_Cost = 0;
	ulong  m_BigHead = 0;
	ulong  m_SmallHead = 0;
	int   m_SkillType = 0;
	int   m_EffectType = 0;
	int   m_Owner = -1; //位置
	ulong m_State = 0;
	ulong  m_Sound = 0;
	int m_NumUnCompatible = 0;
	vector<int> m_UnCompatible;
	ulong  m_MagicID = 0;  //法术动画
	int  m_MagicPos = 0; //动画的位置
	int  m_TargetNum = 0;//目标最大数 比如龙卷最多秒7 那个这数就是7
	int  m_TargetNumOffset = 0;//多少级目标数+1   比如龙卷雨击25级多一个目标
};

//struct sPetSkill
//{
//	int m_ID;
//	int m_SkillType;
//	ulong m_BigHead;
//	ulong m_SmallHead;
//	string m_Describe;
//	string m_Cost;
//	string m_Name;
//	int m_NumUnCompatible;
//	vector<int> m_UnCompatible;
//};


const int c_NumPetSkill = 112;        //召唤兽技能的数量
