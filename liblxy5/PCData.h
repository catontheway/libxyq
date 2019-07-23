#pragma once
#include "_objinc.h"

class cPet;
class cPcData : public cPropertyData
{
public:
	cPcData();
	~cPcData();
	void Reset();

	bool AddMoney(int xianjin, int chubei = 0, int cunyin = 0, bool cost = true);//增加现金,储备,存银 如果小于0,是否扣除
	bool AddMoney(int xianjin, bool cost){ return AddMoney(xianjin, 0, 0, cost); }
	bool AddExp(int exp, int expbb = 0, bool bCost = true);
	
	int FindItem(int type, int id);

	void SetCard(int id);

	sItem2* GetItem(int ID);

	bool Equip(sItem2& item, int m_bEquip = 1);
	//void EquipSpecial(vector<int>& prop,int& proppos, int Pos, int m_bEquip = 1);
	bool UnEquip(int id){ if (id >= 10000)id -= 10000; return Equip(m_Equips[id], -1); }
	bool CanEquip(sItem2& item);
	bool CanEquip(int type);
	int getEquipAtk();

	void autoEquip(bool isNormal, bool isWJB = false, int mp = -1);
	void autoData(bool skill, bool xl, bool fz);
	void autoSkillEnable();


	bool RemovePet(int ID, bool deleteNow = false); //给角色减去一个BB
	bool AddPet(cPet* pPet);//给角色增加一个BB

	bool lvup(bool onlyChek = false){ return cPropertyData::lvup(GetCharacterExp(m_Lv + 1), onlyChek); }
	bool lvdown(bool onlyChek = false){ return cPropertyData::lvdown(GetCharacterExp(m_Lv), onlyChek); }
	void apply();

	void SaveCode(sOstream& File);
	void LoadCode(sIstream& File);
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Load(int model, int mp = -1);


// 	void Read(string name, string path);
// 	void Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip);
// 	void FollowlvAddPoint(int lv, bool isBabyMode, bool isEquip, bool isXiulian);
// 	void FollowSkill();
// 	void FollowXiulian();
// 	void FollowEuip(bool is穿盔甲 = true);
// 	void FollowWeapon();
// 	void FollowShoe();
// 	void FollowEquipAll();
// 	void FollowItem(bool isUnseal);
// 	void FollowBaby();
// 	void FullFuzhuBut暗器();
// 
// 
// 
// 
// 	bool AddTraderExp(int num);
// 
// 	bool CostBangGong(int num);
// 
// 
// 
// 
// 	void AutoPCData(string name, int modeid, sAddPoint* addpoint = 0, sZiZhi* zizhi = 0, eMengPai mengpaid = eMP_无, int  cardid = -1);
// 	
// 	int& GetCard();
// 	
// 
// 
// 
// 	void GetShangPinPet(int ShangPinID);
// 
// 

	
	//辅助技能
	array<int, c_NumFuZhu> m_FuZhuSkillLvList;
	//快捷键
	array<int, 8> m_Accelarate;

	sWeaponData* m_pWeaponData2 = 0;
	sCharacterActionSoundPoint* m_pCharacterData2 = 0;
	//变身
//	bool m_bUseCard = false;
	int m_CardPetID = -1;

	int m_bDuJie = 0; 
	int	m_faceMood = 0; 
public:
//	sChangeColorData2 m_CardRanSe;//有一定几率变成变异召唤兽
//	cPet*  m_pCardPetData = nullptr;
	//坐骑
	bool m_bOnZuoQi = false; //是否坐上坐骑
	int m_ZQ = -1;  //坐骑ID
	sChangeColorData m_ZuoQiRanSe;//坐骑染色
	sChangeColorData m_ZhuangShiRanSe;//装饰染色
	sZuoQi2 m_ZuoQi;


	//持有的召唤兽数
	int  m_NumofBB = 0;
	array<cPet*, 5> m_pPets;
	int m_FightPetID = -1;


	vector<sSkill*> m_SkillEnablelist;

	int  m_NumofSpecial = 0;
	std::array<int, 6>  m_SpecialSkillList;  //装备特技
	//门派
	int  m_MengPaiID = -1;
	array<int, 7>  m_MengPaiSkillLvs;
	// 门贡
//	int m_MengPaiPoint;
// 	//帮派
// 	int  m_BangPaiID = -1;
// 	int   m_BangPaiPoint = 0;

// 	//商人等级
// 	int m_traderLV = 0;
// 	INT64 m_traderExp = 0;
// 	INT64 m_traderExpMax = 0;
//
	//召唤兽修炼
	sBBXiuLian m_XiuLianBB;

	array<INT64, 3> m_Money; // 钱  存银 储备金
	array<sItem2, 80> m_Items;  // 人物道具 
	array<sItem2, 20> m_Fabaos;
//	array<sItem2, 6> m_Equips;//   人物装备

//	int m_Race = -1;//种族
};
