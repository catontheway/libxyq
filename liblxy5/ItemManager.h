#pragma once
#include "_global.h"

class cDescribe;
class ItemManager //物品管理类
{
public:
	void GetIDlistByLv(vector<int>& outlist,int type, int lv);
	int GetIDByLv(int type, int lv);//通过等级随机得到物品的ID
	int GetlvByID(int type, int id);//通过ID得到物品等级
	bool m_bAddHp=0;
	bool m_bAddMp=0;
	bool m_bAddCp=0;
	bool m_bToAll=0;
	bool AddHp(int Num, int TargetID, int Percent = 0);
	// MAxHp * Num% <= Num*Percent
	bool AddHpHurt(int Num, int TargetID, int Percent = 0);
	bool AddHp(int Num, cPropertyData* pdata, int Percent = 0);
	// MAxHp2 * Num% <= Num*Percent
	bool AddHpHurt(int Num, cPropertyData* pdata, int Percent = 0);
	bool removeBuff(int Type, int TargetID,int ReMoveAll);//除某种具体的状态   ,最后一个参数表示是否移除所有同类状态
	
	bool AddMp(int Num, int TargetID, int Percent = 0);
	bool AddCp(int Num, int TargetID, int Percent = 0);
	bool relife(int Num, int TargetID, int Percent = 0);//复活

	bool AddFunc(bool(ItemManager::*AddSomething)(int, int, int), int Num, int TargetID, int Percent = 0);
	int  m_hp;//用来记录上次使用物品加的HP
	//leveup表示升多少级
//	void  SetFabaoEffect(cPcData& data, int leveup, eFaBao ID);

	sItem* GetItem(int type, int id){ return &m_ItemList[type][id]; }
	array<vector<sItem>, 45> m_ItemList; 
	
	array<sZuoQiZhuangShi, 24> m_ZuoQiZhuangShiList;
	//sEquipData m_EquipList[7];  //装备列表
	bool Init();//加载列表

	array<vector<sJiaJuData>, 4> m_JiaJuData;

	//对兽决进行分类,方便奖励
	vector<int> m_LShouJueList;
	vector<int> m_HShouJueList;
	//
	bool UseItem22药品(sItem2* pItem,int ObjId);
	bool UseItem23烹饪(sItem2* pItem, int ObjId);
	bool UseItem24法宝(sItem2* pItem, int ObjId);
	bool UseItem26(sItem2* pCard, int ObjId);
	bool UseItem27道具(sItem2* pItem, int ObjId, int* num=0);
	bool UseItem28(sItem2* pItem, int ObjId);
	bool UseJiaJu(sItem2* pItem);
	bool UseItem(sItem2* pItem, int ObjId,int* num=0);
	
	

	bool FillProperty(int CharID, ItemProPerty type);

	int  GetCheapestItem右键加血(int CharID, ItemProPerty Type);//寻找最便宜的物品
	cWasFile m_MagicAddHP;
	cWasFile m_MagicAddMP;
	cWasFile m_MagicAddHPMP;
	vector<string> m_ItemTypeName;

	vector<sWeaponData> m_pWeaponList2[18][11];//15种武器
	sWeaponData* GetWeaponList(int charid, int weaponid, int type);
	bool SetItemDescribe(int x, int y,cDescribe& pDescribe, sItem2* pItem);
//	void AutoItemProperty(sItem2* item, cPCData* pc, int dustbin = 0);
//	void AutoFuShi(sItem2* item, int lv, eMengPai mengpaiid);
//	void AutoItemProperty(sItem2* item, cCharacter* pc = 0, int dustbin = 0); //自动给物品填充属性, 比如武器的属性
	vector<int> AutoItemPropertyWeapon(sItem2* item, bool isNormal);
	vector<int> AutoItemPropertyEquipButWeapon(sItem2* item, bool isNormal);
	vector<int> AutoItemPropertyBB(sItem2* item);
	void AutoItemProperty(sItem2* item, bool isNormalEquip = true);
//	void AutoItemProperty(sItem2* item, int Luck, int dustbin);
//	void AutoItemProperty国标(sItem2* item, int Luck);
//	void AutoItemProperty装备(vector<int>& prop,  int num, int Luck, int Offset);
	bool XiangQian(sItem2& equip, sItem2& gem);
	void SetUpQiangHua(vector<int>& prop,int protype, int num, bool isBB);
	void SetUpBaoShi(vector<int>& pro, int baoshiid, int lv, bool isBB);
	sItem2* m_pNowItem = 0;
private:
	
	int m_numtext = 0;
	array<string, 20> m_text;
	array<ulong, 20> m_Color;

	string MakePropString(vector<int>& prop, int pos);
	string getProPertyString(int prop);
	void  MakePropString2(sItem2* item);
	void  makePropStringEquip(sItem2* item);
	bool m_bInit = false;
	bool Detoxify1(int Type, int TargetID);
	bool LoadItem1(string path);  //  
	bool LoadFaBao(string path);
	bool LoadShouJue(string path);
	bool LoadWeapon(string path);
	bool LoadZuoqiZhuangShi(string path);
	bool LoadJiaJu(string path);
	void LoadJiaJuCube(ifstream& File,int type);
};
