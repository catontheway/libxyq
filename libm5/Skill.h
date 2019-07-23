#pragma once
//这里放技能相关代码
#include "global.h"
struct sBuff;
class cFightState;


//代表一个技能
struct sSkill
{
	string m_Name;
	int    m_Id=0;
	string m_Text;//描述
	string m_tCost;//消耗的描述
	int    m_Cost=0;
	DWORD  m_BigHead=0;
	DWORD  m_SmallHead=0;
	int   m_SkillType=0;
	int   m_EffectType=0;
	int   m_Owner=-1; //位置
	DWORD  m_Sound=0;
	int m_NumUnCompatible=0;
	vector<int> m_UnCompatible;
	DWORD  m_MagicID=0;  //法术动画
	int  m_MagicPos=0; //动画的位置
	int  m_TargetNum=0;//目标最大数 比如龙卷最多秒7 那个这数就是7
	int  m_TargetNumOffset=0;//多少级目标数+1   比如龙卷雨击25级多一个目标
};

//struct sPetSkill
//{
//	int m_ID;
//	int m_SkillType;
//	DWORD m_BigHead;
//	DWORD m_SmallHead;
//	string m_Describe;
//	string m_Cost;
//	string m_Name;
//	int m_NumUnCompatible;
//	vector<int> m_UnCompatible;
//};


//代表一个主技能
class cZhuJiNeng
{
public:
	int m_ID; //主技能ID
	string m_Name;
	DWORD m_SmallHead;
	DWORD m_BigHead;
	string m_Text;//描述  包含什么技能
	string m_Text2;//描述2   学习效果
	//包含技能
	int   m_NumSkillInclude;
	int   m_Limit[12];
	int   m_SkillIncludeID[12];

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
	cZhuJiNeng m_MainSkill[7];//主技能
};




const int c_SkillNum = 167;
const int c_NumMengPai = 12;


class cMengPaiManager
{
public:
	BOOL  Init();
	cMengPai* GetMengPai(cCharacter* pc);
	cMengPai* GetMengPai(int ID){ if (ID < 0||ID>14)return 0;  return &m_MengPai[ID]; }
	sSkill*   GetSMSkill(int ID){ return &m_SkillList[ID];}
	cMengPai  m_MengPai[c_NumMengPai];//门派表
	sSkill m_SkillList[c_SkillNum];//师门技能表
	void lvUpMainSkill(cPCData& pcDate, int lv, int ID, bool isHero = false);
private:
	BOOL m_bInit;
};
#if ccc_m5
const int c_NumPetSkill = 103;        //召唤兽技能的数量
#else
const int c_NumPetSkill = 106;
#endif
class cSkillManager
{
public:
	
	BOOL SetPetSkill1(cPetData* pPetDate, int ID, int lv = 1);
public:
	void SetMengPaiSkill(cDescribe& describe, int id);

	BOOL CheckGodLivePercent(int& dam, int target,int userid);//神佑修正
	void lvUpFuZhuSkill(int targetID, int FuZhuSkillID, int lv);
	void lvUpMainSkill(cPCData& pcDate, int lv, int ID, bool isHero = false);

	BOOL SetMainSkill(int targetID,int MainSkillID);

	void SetSpecialSkill2(int targetID, int SkillID,  int Setup);//安装特效
	void SetSpecialSkill2(cPetData* pPetdata, int SkillID, int Setup);//安装特效
	int  SetPetSkill(cPetData* pTarget,int PetSkillID,int Pos=12);
	BOOL ReMoveMainSkill(int targetID, int MainSkillID);
	BOOL CheckHit(cPetData* pUserData, cPetData *pTargetData, int offset = 0);//检测物理攻击是否命中
	BOOL CheckCRI(cPetData* pUserData, cPetData *pTargetData, int offset = 0);//检测



	BOOL SetDateBuffUp(int userID, int targetID, int stateid, sBuff& buf, int skilllv = 0);  // 给目标加一个BUFF
	BOOL SetDateBuffDown(list<sBuff>::iterator& sbuf);//int targetID, int stateid); //给目标去掉一个BUFF  用于那些能改变角色属性的BUFF
	BOOL CheckFightState(int FightListID);  //使BUFF发挥效果 ,  比如普渡众生,每回合开始要加血
	BOOL CheckFightStateOnLine(int FightListID,int& dam);//当角色受到攻击时,BUFF的影响
	//BOOL CheckFightStateApproach(int FightListID);//当角色将要攻击时的BUFF的影响;
	int GetLiveNum(BOOL our);//得到活着的敌人的数量
	int GetTargetID(int UserID, int TargetID, int Num); //得到离UserID第Num近的活着的对象ID
	BOOL isIDLive(int ID, int& Num);//检测一个对象是否可以选中 ,后面那个Num参数如果不是0,则永远返回0
	BOOL SetIndexPos(int UserID, int Index, BOOL bToAll, DWORD DataID);  //给指定对象设置被法术打状态
	cMengPaiManager m_MengPaiManager;
	BOOL Init();
	BOOL Use(sFightSkillSelect SkillSelect, int UserID, bool isPut = false);
	BOOL UseNormal(int skillID);
	sSkill* GetPetSkill(int ID){ return &m_PetSkillList[ID]; }
	sSkill*  GetFuZhuSkill(int ID){ return &m_FuZhuSkillList[ID]; }
	sSkill*    GetSkill(int ID);
	sSkill*    GetMengPaiSkill(int ID){ return &m_MengPaiManager.m_SkillList[ID]; }
	sSkill* GetSpecialSkill(int ID){return &m_SpecialSkill[ID];}
	sSkill* GetSpecialSkill2(int ID){ return &m_SpecialSkill2[ID]; }
	sSkill m_PetSkillList[c_NumPetSkill];
	sSkill    m_FuZhuSkillList[13];
	vector<sSkill>    m_SpecialSkill;//特技
	vector<sSkill>    m_SpecialSkill2;//特效
	BOOL UseSwitchMap(int Skilllv, int sSkillID, int UserID, int TargetID);//各种回门派法术
	BOOL Use1(int Skilllv, int sSkillID, int UserID, int TargetID); //后发制人
	BOOL Use7(int Skilllv, int sSkillID, int UserID, int TargetID); //破釜沉舟
	BOOL Use26(int Skilllv, int sSkillID, int UserID, int TargetID); //分身术
	
	BOOL Use71(int Skilllv, int sSkillID, int UserID, int TargetID); //天雷斩 烟雨剑法
	BOOL Use80(int Skilllv, int sSkillID, int UserID, int TargetID); //龙卷雨击
	BOOL Use84(int Skilllv, int sSkillID, int UserID, int TargetID);//龙呤
	BOOL Use1000(int Skilllv, int sSkillID, int UserID, int TargetID); //普通攻击
	BOOL Use1002(int Skilllv, int sSkillID, int UserID, int TargetID); //防御
	BOOL Use1003(int Skilllv, int sSkillID, int UserID, int TargetID); //使用道具
	BOOL Use1004(int Skilllv, int sSkillID, int UserID, int TargetID); //召唤
	BOOL Use1005(int Skilllv, int sSkillID, int UserID, int TargetID); //使用暗器
	// 日期版专用
	BOOL Use61暗器(int Skilllv, int sSkillID, int UserID, int TargetID); //使用暗器
	BOOL Use粗劣小AI(int Skilllv, int sSkillID, int UserID, int TargetID);//  比较简单的法术
	BOOL Use2105(int Skilllv, int sSkillID, int UserID, int TargetID);

	BOOL UseSeal(int Skilllv, int sSkillID, int UserID, int TargetID);//  比较简单的法术
	BOOL Use1006(int Skilllv, int sSkillID, int UserID, int TargetID); //逃跑
	BOOL Use107(int Skilllv, int sSkillID, int UserID, int TargetID); //巨岩破...........
	BOOL CheckMagicHit(int Skilllv, int sSkillID, int UserID, int TargetID);
	//1017 //破釜
		//case 1050:  //满天花雨
		//case 1095://力劈

	//最后一个参数表示 是否消耗
	BOOL Cost(int& outhp, int Skilllv, int sSkillID, int UserID, int num, BOOL bCost);
	int GetSpeed(int skillid);
	void EffectSkill(int Skilllv, int sSkillID, int UserID, int TargetID);

	int AddHp(int target, int num, int percent = 0); //当percent不为0, num为百分比,改变最大值为percent*num;
	int AddMp(int target, int num, int percent = 0);
	void AddHpHurt(int target, int num, int percent = 0);
	void AddCp(int target, int num, int percent = 0);
	int m_time;
	void Resurgence(int TargetID);
	//3000以上是特技
	sItem2* GetItem(int UserID);
	BOOL CoutCombo(cPetData* user, cPetData* target);
	BOOL CountCri(cPetData* user, cPetData* target);//必杀修正,返回是否必杀
	void CountCriDamage(cPetData* user, cPetData* target, int& dam);
	int CountSpecial(cPetData* user, cPetData* target, BOOL targetSex);//特攻修正
	BOOL CountCriMagic(cPetData* user, cPetData* target, int& nowdam);//法暴修正
#if ccc_m5
	BOOL CoutComboMagic(cPetData* user, int userid, cPetData* ptarget);
#else
	BOOL CoutComboMagic(int skillid, cPetData* user, int userid, cPetData* ptarget);
#endif
	
	void  CountphysicalDamage(int& dam, int UserID, int TargetID, int Damageup = 0);
	enum eMagicWuXing
	{
		eMWX无,
		eMWX雷,
		eMWX火,
		eMWX水,
		eMWX土,
		eMWX雷水,
		eMWX光

	};
	BOOL  CountMagicDamage(int& dam, int UserID, int TargetID, int Damageup = 0,eMagicWuXing wuxing=eMWX无);//计算法术伤害
	void  CountMagic2Damage(int& dam, int UserID, int TargetID, eMagicWuXing wuxing = eMWX无);//固定伤害修正
	BOOL  CountParry( cPetData* pUserData,cPetData* pTargetData);//防御修正
	BOOL  CountProtect(int& dam, cObj* pUser, cObj* pTarget);//保护修正
	void CorrectCureHP(int& dam,int UserID,int TargetID);//治愈法术修正
	void CorrectCureMP(int& dam, int UserID, int TargetID);//治愈法术修正
	int  CountHPPercent(cPetData* ptarget, UINT num, UINT bili)
	{ 
		UINT dam = (ptarget->m_HPMax.GetData() *num) / 100;
		if (dam > num*bili)dam = num*bili;
		return (int)dam;
	}
	int  CountMPPercent(cPetData* ptarget, UINT num, UINT bili)
	{
		UINT dam = (ptarget->m_MPMax.GetData() *num) / 100;
		if (dam > num*bili)dam = num*bili;
		return (int)dam;
	}
	cFightState* m_pFightState;
	BOOL SetDamage(int HP, int Who); //显示掉了多少血,如果是负数,表示恢复多少血, 此函数仅仅在表面显示这些数字,因为有时候明明掉了10000血,但最多显示9999 
	BOOL CheckFanZheng(int UserID,int TargetID,int& dam);//反震检测
	void SuckBlood(int dam, int UserID,cPetData* target);
	void CheckPoision(int UserID, int TargetID);

	BOOL StageWaitReturn(int UserID, int retStage);//等待返回
	BOOL StageWaitFightBack(int UserID, int TargetID, int retStage);//等待对手反击
	BOOL StageWaitProtect(int atkid, int UserID, int retStage);//等待保护者就位
	inline	BOOL StageWaitSleep(int time, int UserID, int retStage);
	BOOL GetSkillAtk(int ID);
	BOOL GetSkillToAll(int ID);
private:
	int CorrectWuXing(cPetData* pUser, cPetData* pTarget, eMagicWuXing MagicWuXing);
	BOOL WaitForMagicPoint(int Waiter);
	void GetDelayAnd(int skillID, int& delay, DWORD& magicID);
	void GetMagicAndNum(int Skilllv, int sSkillID, int UserID, int TargetID, DWORD& MagicID, int& NumMax, int& MagicPos,  BOOL& MagicUporDown, BOOL&  toAll);
	BOOL PhysicalAtkHitStage(int UserID, int targetid, int sSkillID);//返回是否命中
	BOOL m_bInit = FALSE;
};