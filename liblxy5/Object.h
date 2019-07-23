#pragma once
#include "_objinc.h"

const int c_NumFuZhu = 4/*13*/;
struct sBuff
{
	int ID;   //BUFF的ID
	ulong MagicID;
	//int Type; 
	int remainingTimes;//剩余时间
	//buf的法术显示效果
	int bufPos;  //位置
	cWasFile data;
	bool bBuffup; //在上面还是下面
	int userID;
	int targetID;
	eBuffType EffectType;//这个BUFF的类型, 0 增异  1 异常 2 毒 3 死亡召唤  
	int damage;
	int damage2;
	int skilllv = -1;
};


// struct sItemData
// {
// 	string m_name;
// 	ulong	m_smallhead;
// };
// struct sFabaoData
// {
// 	string m_name;
// 	ulong	m_smallhead;
// };
// 
// 
// struct sSkillData
// {
// 	string m_name;
// 	ulong	m_smallhead;
// 	ulong	m_bighead;
// 	ulong	m_majic;
// 	ulong	m_defend;
// };




#define WORKTYPE_ATTACK    1    //攻击
#define WORKTYPE_MAGIC     3    //施法
#define WORKTYPE_APPROACH  4    //接近
#define WORKTYPE_DEFEND    5    //防
#define WORKTYPE_SUFFER    6    //受到物理攻击
#define WORKTYPE_RETURN    7    //返回
#define WORKTYPE_MAGICSUFFER  8  //受到魔法攻击
#define WORKTYPE_MAGICATTACK  9   //法术驱动的物理攻击
#define WORKTYPE_FLY       10     //召唤兽被击飞
#define WORKTYPE_FALLDOWN  11  //角色死亡
#define WORKTYPE_CATCH  12  // 抓捕
#define WORKTYPE_AVOID  13  // 回避
#define WORKTYPE_MAGIC2   14    //使用特殊法术 比如防御,攻击
#define WORKTYPE_ITEM     15    //用道具
#define WORKTYPE_SUMMON   16    //召唤
#define WORKTYPE_GUARD   17    //保护
#define WORKTYPE_COUNTER 18  //反击

#define INDEXTYEP_CHARACTER 100
#define INDEXTYEP_PET       101
#define INDEXTYEP_NPC       102

enum PropertyType
{
	typeAtkZZ,
	typeDefZZ,
	typeHPZZ,
	typeMagZZ,
	typeSpdZZ,
	typeAvoidZZ
};


// 
// 
// 
// struct sShangPinPet;
// 
// 
// 
// 
// class cCharacter;
// class cPCData;
//一个BB应该有的数据

// class cPetData : public cPetData, public cZZBase
// {
// public:
// 	virtual void Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip);
// 	void AddHpZZ(int num);
// 	void AddMagZZ(int num);
// 	void AddAtkZZ(int num);
// 	void AddAvoidZZ(int num);
// 	void AddSpdZZ(int num);
// 	void AddDefZZ(int num);
// 	void AddGrowing(int num);
// };
// 
// 
// class cMengPai;
// struct sSkill;

struct sFightSkillSelect
{
	int SkillLv=0;
	int SkillID=-1;
	int TargetID=-1;
};


// enum eCharacterEquip
// {
// 	eChaEquipWuqi,
// 	eChaEquipTouKui,
// 	eChaEquipYaoDai,
// 	eChaEquipXieZi,
// 	eChaEquipXiangLian,
// 	eChaEquipYiFu
// };

