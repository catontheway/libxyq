#pragma once
#include "_objinc.h"

struct cPropertyData : sPropertyData
{
	void Reset();
	void FillHpMp();
	void SetJinJie(int num);

	bool AddSkill(int id, int idx = -1);
	bool isHadPetSkill(int SkillID);

	bool setPointAfterLv(const sAddPoint& ap, bool isRemain);

	bool lvup(int exp, bool onlyChek);
	bool lvdown(int exp, bool onlyChek);

	void apply(const sZiZhi* zz);

	void SaveCode(sOstream& File);
	void LoadCode(sIstream& File);

	void Save(ofstream& File);
	void Load(ifstream& File);

	cObj* getObj(bool checkExit = false);


	string m_Name;
//	string m_dataFileName;

	int modeid = -1;
	int m_HP = 0;
	int m_HP2 = 0;
	int m_MP = 0;
	int m_CP = 0;      //愤怒
	static const int m_CPMax = 150;
	INT64 m_EXP = 0;
//	INT64 m_ExpTotal = 0;

	//战斗属性表
	sFightData m_FightData;
	int m_IDinFightWorkList = -1;

	int  m_NumofBBSkill = 0;
	array<sSkill*, 24> m_petSkills;


	sControler m_Controler;
	cJinJieNum m_JinJieNum;//进阶
	sChangeColorData2 m_RanSe;

	array<sItem2, 6> m_Equips;

// 	int m_AiLv = 0;
// 	int m_StrongLv = 0;
// 
// 	int NightLv = 0;//等级夜战能力
// 	int AbnormalResist = 0; //精神集中
// 	//攻击降属性,被攻击提升属性
// 	// 固定伤害扣伤
// 	sInt2 m_MagDownHPHurt;
// 	sInt2 m_AtkDownHPHurt;
// 	sInt2 m_AtkDownCP; //攻击降CP
// 	sInt2 m_AtkDownMP;
// 	sInt2 m_AtkDownAtk;
// 	sInt2 m_AtkDownHit;
// 	sInt2 m_AtkDownDef;
// 	sInt2 m_AtkDownWakan;
// 	sInt2 m_AtkDownSpd;
// 	//特攻 
// 	sInt2 BoySpecial;  //男
// 	sInt2 GirlSpecial;   //女
// 	sInt2 GoldSpecial;     //神族特攻
// 	sInt2 MagSpecial;    //魔族特攻
// 	sInt2 ImmortalSpecial; //仙族特攻
// 	sInt2 MonsterSpecial;//妖怪特攻
// 	sInt2 PeopleSpecial; //人
// 	sInt2 ghostSpecial;  //鬼特攻
// 	sInt2 machineSpecial;//机械特攻
// 
// 	sInt2  m_DamageAddMagicLv;//法术伤害结果增加lv
// 	sInt2  m_DamageAddLv;  //物理伤害结果
// 	//召唤兽伤害加成
// 	sInt2  m_PetDamagePercentMagic;//法术伤害
// 	sInt2  m_PetDamagePercent;//物理伤害

	bool _isOurTeamTemp = false;
	bool _isWeakSeal = false;
};



class cPetData : public cPropertyData
{
public:
	cPetData();
	void apply();

	bool lvup(bool onlyChek = false){ return cPropertyData::lvup(GetPetExp(m_Lv + 1), onlyChek); }
	bool lvdown(bool onlyChek = false){ return cPropertyData::lvdown(GetPetExp(m_Lv), onlyChek); }

	void autoEquip(bool isStone, bool isFushi);
	bool autoData(bool point, bool skill);

	void SaveCode(sOstream& File);
	void LoadCode(sIstream& File);

	void Load(ifstream& File){ cPropertyData::Load(File); }
	void Load(int model, bool skill, bool zz);


// private:
// 	bool m_bSetupXiuLian = false;
// protected:
// 	bool _isBabyModeForLvup = true;
// public:
// 	int CountATK();//计算伤害
// 	int CountDEF();//计算防
// 	int CountHP();//计算HP
// 	int CountWakan();//计算灵力
// 	int CountMP(); //计算MP
// 	int CountSpd(); //计算速度
// 	int CountEvade(); //计算躲避率
// 	int CountHit();//计算命中率
// 
// 	void AddProPertyAtk(int num);
// 	void AddProPertyDef(int num);
// 	void AddProPertyMag(int num);
// 	void AddProPertyHp(int num);
// 	void AddProPertySpd(int num);
// 
// 	void AddHpZZ(int num);
// 	void AddMagZZ(int num);
// 	void AddAtkZZ(int num);
// 	void AddAvoidZZ(int num);
// 	void AddSpdZZ(int num);
// 	void AddDefZZ(int num);
// 	void AddGrowing(int num);
// 
// 	void ReadPet(string name, string path);
// 	void SetXLEffect(bool bSetup);
// 	void ResetAddPoint(bool isBB);
// 	void AutoGetSkill(int id);
// 	
// 	bool LeveUp(int lv, bool isBaby, bool isAdd);
// 	virtual void Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip);
// 	void lvUpFuZhuSkill(int lv, int FuZhuSkillID);
// 	
// 	void EquipExtra(vector<int>& prop, int& startid, int m_bEquip);
// 	void PetEquip(int Pos, int bequip = 1);
// 	void UnPetEquip(int Pos);
// 
// 	void Set(sShangPinPet* pet);
// 	
// 	void AutoPetData(bool m_bNeedSkill = true);
// 
// 	void Add人气(int num);
	
	//资质
	sZiZhi m_ZiZhi;

// 
// 	//加点方式
// 	sAddPoint m_AddPoint;
// 
// 
// 	std::array<int, 6> _spesialSkills;
// 	//BB技能
// 
// 
// 	//经验
// 
// 
// 
// 	//辅助技能
// 	int m_FuZhuSkillLvList[c_NumFuZhu];
// 
// 
// 
// 	int m_Popularity = 0;  //人气
// 	int m_Physical = 0;    //体力
// 	int m_PhysicalMax = 0; //体力上限
// 	int m_Energy = 0;      //活力
// 	int m_EnergyMax = 0;  //活力上限
// 	int m_Race = -1;//种族

	int _owerIdx = -1;
};
