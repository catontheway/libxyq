#pragma once
//这里放技能相关代码
#include "_global.h"

class cFightState;
class cSkillManager
{
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
public:
//	bool SetPetSkill1(cPropertyData* pPetDate, int ID, int lv = 1);
	void SetMengPaiSkill(cDescribe& describe, int id);

	bool CheckGodLivePercent(int& dam, int target,int userid);//神佑修正
//	void lvUpFuZhuSkill(int targetID, int FuZhuSkillID, int lv);
//	void lvUpMainSkill(cPcData& pcDate, int lv, int ID, bool isHero = false);
//
//	bool SetMainSkill(int targetID,int MainSkillID);
//
//	void SetSpecialSkill2(int targetID, int SkillID,  int Setup);//安装特效
//	void SetSpecialSkill2(cPropertyData* pPetdata, int SkillID, int Setup);//安装特效
//	int  SetPetSkill(cPropertyData* pTarget,int PetSkillID,int Pos=12);
//	bool ReMoveMainSkill(int targetID, int MainSkillID);
	bool CheckHit(cPropertyData* pUserData, cPropertyData *pTargetData, int offset = 0);//检测物理攻击是否命中
	bool CheckCRI(cPropertyData* pUserData, cPropertyData *pTargetData, int offset = 0);//检测



	bool SetDateBuffUp(int userID, int targetID, int stateid, sBuff& buf, int skilllv = 0);  // 给目标加一个BUFF
	bool SetDateBuffDown(list<sBuff>::iterator& sbuf);//int targetID, int stateid); //给目标去掉一个BUFF  用于那些能改变角色属性的BUFF
	bool CheckFightState(int FightListID);  //使BUFF发挥效果 ,  比如普渡众生,每回合开始要加血
	bool CheckFightStateOnLine催眠(int FightListID,int& dam);//当角色受到攻击时,BUFF的影响
	//bool CheckFightStateApproach(int FightListID);//当角色将要攻击时的BUFF的影响;
//	int GetLiveNum(bool our);//得到活着的敌人的数量
	int GetTargetID(int UserID, int TargetID, int Num); //得到离UserID第Num近的活着的对象ID
//	bool isIDLive(int ID, int& Num);//检测一个对象是否可以选中 ,后面那个Num参数如果不是0,则永远返回0
//	bool SetIndexPos(int UserID, int Index, bool bToAll, ulong DataID);  //给指定对象设置被法术打状态
	cMengPaiManager m_MengPaiManager;
	bool Init();
	bool Use(sFightSkillSelect SkillSelect, int UserID, bool isPut = false);
	bool UseNormal(int skillID);
	sSkill* GetPetSkill(int ID){ return &m_PetSkillList[ID]; }
	sSkill* GetFuZhuSkill(int ID){ return &m_FuZhuSkillList[ID]; }
	sSkill* GetSkill(int ID);
	sSkill* GetMengPaiSkill(int ID){ return &m_MengPaiManager.m_SkillList[ID]; }
	sSkill* GetSpecialSkill(int ID){return &m_SpecialSkill[ID];}
	sSkill* GetSpecialSkill2(int ID){ return &m_SpecialSkill2[ID]; }
	array<sSkill, c_NumPetSkill> m_PetSkillList;
	array<sSkill, c_NumFuZhu> m_FuZhuSkillList;
	vector<sSkill>    m_SpecialSkill;//特技
	vector<sSkill>    m_SpecialSkill2;//特效
	bool UseSwitchMap(int Skilllv, int sSkillID, int UserID, int TargetID);//各种回门派法术
	bool Use1后发(int Skilllv, int sSkillID, int UserID, int TargetID); //后发制人
//	bool Use7破釜沉舟(int Skilllv, int sSkillID, int UserID, int TargetID); //破釜沉舟
	bool Use26(int Skilllv, int sSkillID, int UserID, int TargetID); //分身术
	
	bool Use71法术驱动物理(int Skilllv, int sSkillID, int UserID, int TargetID); //天雷斩 烟雨剑法
	bool Use80龙卷飞沙(int Skilllv, int sSkillID, int UserID, int TargetID); //龙卷雨击
	bool Use84龙吟(int Skilllv, int sSkillID, int UserID, int TargetID);//龙呤
	bool Use1000平砍(int Skilllv, int sSkillID, int UserID, int TargetID); //普通攻击
//	bool Use1002防御(int Skilllv, int sSkillID, int UserID, int TargetID); //防御
	bool Use1003物品(int Skilllv, int sSkillID, int UserID, int TargetID); //使用道具
	bool Use1004召唤(int Skilllv, int sSkillID, int UserID, int TargetID); //召唤
	bool Use1005暗器(int Skilllv, int sSkillID, int UserID, int TargetID); //使用暗器
	bool Use61暗器(int Skilllv, int sSkillID, int UserID, int TargetID); //使用暗器
	bool Use默认技能(int Skilllv, int sSkillID, int UserID, int TargetID);//  比较简单的法术
	bool Use2105(int Skilllv, int sSkillID, int UserID, int TargetID);//  比较简单的法术
	bool Use1006(int Skilllv, int sSkillID, int UserID, int TargetID); //逃跑
	bool Use107巨岩破泰山天罗地网(int Skilllv, int sSkillID, int UserID, int TargetID); //巨岩破...........
	int CheckMagicHit(int Skilllv, int sSkillID, int UserID, int TargetID);
	//1017 //破釜
		//case 1050:  //满天花雨
		//case 1095://力劈

	//最后一个参数表示 是否消耗
//	bool Cost(int& outhp, int Skilllv, int sSkillID, int UserID, int num, bool bCost);
	bool Cost(int userid, int skill, int num, bool bCost);
	int GetSpeed(int skillid);
	void EffectSkill(int Skilllv, int sSkillID, int UserID, int TargetID);

	int AddHp(int target, int num, int percent = 0); //当percent不为0, num为百分比,改变最大值为percent*num;
	int AddMp(int target, int num, int percent = 0);
	void AddHpHurt(int target, int num, int percent = 0);
	void AddCp(int target, int num, int percent = 0);
	int m_time;
	bool Resurgence(int TargetID);
	//3000以上是特技
	sItem2* GetItem(int UserID);
	bool CoutCombo连击(cPropertyData* user, cPropertyData* target);
	bool CountCri(cPropertyData* user, cPropertyData* target);//必杀修正,返回是否必杀
	void CountCriDamage(cPropertyData* user, cPropertyData* target, int& dam);
	int CountSpecial(cPropertyData* user, cPropertyData* target/*, bool targetSex*/);//特攻修正
	bool CountCriMagic(cPropertyData* user, cPropertyData* target, int& nowdam);//法暴修正
	bool CoutComboMagic(int skillid, cPropertyData* user, int userid, cPropertyData* ptarget);
	
	void  CountphysicalDamage(int& dam, int UserID, int TargetID, int Damage加成百分比 = 0);
	void count炎护(int& dam, int TargetID);

	bool  CountMagicDamage(int& dam, int UserID, int TargetID, int Damageup, eMagicWuXing wuxing, int& userData); //计算法术伤害
	bool  CountMagicDamage(int& dam, int UserID, int TargetID, int Damageup = 0, eMagicWuXing wuxing = eMWX无)
	{
		int v;
		return CountMagicDamage(dam, UserID, TargetID, Damageup, wuxing, v);
	}
	
	void  CountMagic2Damage固定(int& dam, int UserID, int TargetID, eMagicWuXing wuxing = eMWX无);//固定伤害修正
	bool  CountParry(cPropertyData* pUserData,cPropertyData* pTargetData);//防御修正
	bool  CountProtect(int& dam, cObj* pUser, cObj* pTarget);//保护修正
	void CorrectCureHP(int& dam,int UserID,int TargetID);//治愈法术修正
	void CorrectCureHP(int& hp, int& hp2, int UserID, int TargetID);//治愈法术修正
	void CorrectCureMP(int& dam, int UserID, int TargetID);//治愈法术修正
	int  CountHPPercent(cPropertyData* ptarget, uint num, uint bili)
	{ 
		uint dam = (ptarget->HPMax.GetData() *num) / 100;
		if (dam > num*bili)dam = num*bili;
		return (int)dam;
	}
	int  CountMPPercent(cPropertyData* ptarget, uint num, uint bili)
	{
		uint dam = (ptarget->MPMax.GetData() *num) / 100;
		if (dam > num*bili)dam = num*bili;
		return (int)dam;
	}
	cFightState* m_pFightState;
	bool SetDamage(int HP, int Who); //显示掉了多少血,如果是负数,表示恢复多少血, 此函数仅仅在表面显示这些数字,因为有时候明明掉了10000血,但最多显示9999 
	bool CheckFanZheng(int UserID,int TargetID,int& dam);//反震检测
	void SuckBlood(int dam, int UserID,cPropertyData* target);
	// buf: state time damage(雾杀用到)
	void CheckPoision(int UserID, int TargetID, int offs, sBuff buf);
	void CheckPoision(int UserID, int TargetID);

	bool StageWaitReturn(int UserID, int retStage);//等待返回
	bool StageWaitFightBack(int UserID, int TargetID, int retStage);//等待对手反击
	bool StageWaitProtect(int atkid, int UserID, int retStage);//等待保护者就位
	bool StageWaitSleep(int time, int UserID, int retStage);
	// 0延迟?
	bool GetSkill需要目标被打动画(int ID);
	bool isAni画面型(int ID);
private:
	int CorrectWuXing(cPropertyData* pUser, cPropertyData* pTarget, eMagicWuXing MagicWuXing);
	bool WaitForMagicPoint(int Waiter);
	void GetDelayAnd(int skillID, int& delay, ulong& magicID);
	void GetMagicAndNum秒几(int Skilllv, int sSkillID, int UserID, int TargetID, ulong& MagicID, int& NumMax, int& MagicPos,  bool& MagicUporDown, bool&  toAll画面型);
	bool PhysicalAtkHitStage(int UserID, int targetid, int sSkillID);//返回是否命中
	bool m_bInit = false;
};