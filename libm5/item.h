#pragma once
#include "global.h"
using namespace std;
class CMainState;
struct sWeaponData2:public sPetDataPart //一种武器的一种状态
{
	int     Master;
	int     MasterPos; //持有这个武器的角色的ID
	void Read(ifstream& File)
	{
		File >> m_attack;
		m_attack2 = m_attack;
		File >> m_defend;
		File >> m_dead;
		File >> m_fstand;
		File >> m_majic;
		File >> m_return;
		File >> m_run;
		File >> m_stand;
		File >> m_suffer;
		File >> m_walk;
		File >> Master;
		File >> MasterPos;
	}
};

enum eFaBao
{
	eFaBao0曼陀罗,
	eFaBao1干将莫邪,
	eFaBao2罗汉珠,
	eFaBao3赤焰,
	eFaBao4万鬼幡,
	eFaBao5惊魂铃,
	eFaBao6混元伞,
	eFaBao7无魂傀儡,
	eFaBao8乾坤玄火塔,
	eFaBao9普渡,
	eFaBao10缩地尺,
	eFaBao11月光宝盒,
	eFaBao12红色导标旗,
	eFaBao13蓝色导标旗,
	eFaBao14白色导标旗,
	eFaBao15绿色导标旗,
	eFaBao16隐蛊,
	eFaBao17周杰伦手办,
	eFaBao18时之环,
	eFaBao19通灵宝玉,
	eFaBao20聚宝盆,
	eFaBao21碧玉葫芦,
	eFaBao22神木宝鼎,
	eFaBao23八咫镜,
	eFaBao24嗜血幡,
	eFaBao25金甲仙衣,
	eFaBao26降魔斗篷,
	eFaBao27九幽,
	eFaBao28救命毫毛,
	eFaBao29镇海珠,
	eFaBao30五火神焰印,
	eFaBao31忘情,
	eFaBao32慈悲,
	eFaBao33梦蝶,
	eFaBao15黄色导标旗
};
struct sItem //表示一个道具
{
	int m_Type;
	int m_ID;
	string m_Name;
	DWORD m_SmallHead; //头像
	DWORD m_BigHead;
	int m_Price=0;//价格
	
	string m_Text; //描述
	int m_UseType;
	void SetLv(int lv){ m_lv = lv; }
	int GetLv(){ return m_lv; }
private:
	int m_lv;
};
enum eProPerty
{
	eProPerty伤害,
	eProPerty命中,
	eProPerty防御,
	eProPerty魔法,
	eProPerty灵力,
	eProPerty速度,
	eProPerty气血,
	eProPerty力量,
	eProPerty敏捷,
	eProPerty体质,
	eProPerty魔力,
	eProPerty耐力,
	eProPerty水抗,
	eProPerty火抗,
	eProPerty土抗,
	eProPerty雷抗,
	eProPerty躲避
};

enum ItemProPerty
{
	enum_hp,
	enum_hphurt,
	enum_mp
};


class cZuoQi
{
public:
	BOOL GetZuoQi(int charID, int ZuoQiID);
	BOOL GetZuoQi(cPCData& pcData, int ZuoQiID);
	BOOL Init(string Path);
	sZuoQi m_ZuoQi[8];
	void GetShiPei(vector<int>& list,int pcData);
};
class cFightState;
class cDescribe;
struct sJiaJuData
{
	int num;
	vector<DWORD> m_data;
};
class cItem //物品管理类
{
public:
	void GetIDlistByLv(vector<int>& outlist,int type, int lv);
	int GetIDByLv(int type, int lv);//通过等级随机得到物品的ID
	int GetlvByID(int type, int id);//通过ID得到物品等级
	BOOL m_bAddHp=0;
	BOOL m_bAddMp=0;
	BOOL m_bAddCp=0;
	BOOL m_bToAll=0;
	BOOL AddHp(int Num, int TargetID, BOOL Percent = FALSE);
	BOOL AddHpHurt(int Num, int TargetID, BOOL Percent = FALSE);
	BOOL AddHp(int Num, cPetData* pdata, BOOL Percent = FALSE);
	BOOL AddHpHurt(int Num, cPetData* pdata, BOOL Percent = FALSE);
	BOOL Detoxify(int Type, int TargetID,BOOL ReMoveAll);//除某种具体的状态   ,最后一个参数表示是否移除所有同类状态
	
	BOOL AddMp(int Num, int TargetID, BOOL Percent = FALSE);
	BOOL AddCp(int Num, int TargetID, BOOL Percent = FALSE);
	BOOL Resurgence(int Num,int TargetID,BOOL Percent=FALSE);//复活

	BOOL AddAll(BOOL(cItem::*AddSomething)(int, int, BOOL), int Num, int TargetID, BOOL Percent = FALSE);
	int  m_hp;//用来记录上次使用物品加的HP
	//leveup表示升多少级
	void  SetFabaoEffect(cPCData& data, int leveup, eFaBao ID);

	sItem* GetItem(int type, int id){ return &m_ItemList[type][id]; }
	vector<sItem> m_ItemList[42]; 
	
	sZuoQiZhuangShi m_ZuoQiZhuangShiList[24];
	//sEquipData m_EquipList[7];  //装备列表
	BOOL Init();//加载列表

	vector<sJiaJuData> m_JiaJuData[4];

	//对兽决进行分类,方便奖励
	vector<int> m_LShouJueList;
	vector<int> m_HShouJueList;
	//
	BOOL UseItem22(sItem2* pItem,int ObjId);
	BOOL UseItem23(sItem2* pItem, int ObjId);
	BOOL UseItem24(sItem2* pItem, int ObjId);
	BOOL UseItem26(sItem2* pCard, int ObjId);
	BOOL UseItem27(sItem2* pItem, int ObjId, int* num=0);
	BOOL UseItem28(sItem2* pItem, int ObjId);
	BOOL UseJiaJu(sItem2* pItem);
	BOOL UseItem(sItem2* pItem, int ObjId,int* num=0);
	
	

	BOOL FillProperty(int CharID, ItemProPerty type);

	int  GetCheapestItem(int CharID, ItemProPerty Type);//寻找最便宜的物品
	CWFile m_MagicAddHP;
	CWFile m_MagicAddMP;
	CWFile m_MagicAddHPMP;
	vector<string> m_ItemTypeName;

	vector<sWeaponData2> m_pWeaponList2[15][11];//15种武器
	sWeaponData2* GetWeaponList(int charid, int weaponid, int type);
	BOOL SetItemDescribe(int x, int y,cDescribe& pDescribe, sItem2* pItem);
	void AutoItemProperty(sItem2* item, cPCData* pc);
	void AutoItemProperty(sItem2* item, cPCData* pc, int dustbin);
	void AutoFuShi(sItem2* item, int lv, eMengPai mengpaiid);
	void AutoItemProperty(sItem2* item,cCharacter* pc=0); //自动给物品填充属性, 比如武器的属性
	void AutoItemProperty(sItem2* item, cCharacter* pc, int dustbin);
	void AutoItemProperty(sItem2* item, int Luck, int dustbin);
	void AutoItemProperty2(vector<int>& prop,  int num, int Luck, int Offset);
#if ccc_date
	void AutoItemProperty鉴定(sItem2* item, int Luck);
#endif
	BOOL XiangQian(sItem2& equip, sItem2& gem);
	void SetUpQiangHua(vector<int>& prop,int protype, int num);
	void SetUpBaoShi(vector<int>& pro, int baoshiid, int m_bSetup=1);
	sItem2* m_pNowItem = 0;
private:
	
	string m_text[16];
	int m_numtext = 0;
	DWORD m_Color[16];

	string MakePropString(vector<int>& prop, int pos);
	void  MakePropString2(sItem2* item);
	BOOL m_bInit = FALSE;
	BOOL Detoxify1(int Type, int TargetID);
	BOOL LoadItem1(string path);  //  
	BOOL LoadFaBao(string path);
	BOOL LoadShouJue(string path);
	BOOL LoadWeapon(string path);
	BOOL LoadZuoqiZhuangShi(string path);
	BOOL LoadJiaJu(string path);
	void LoadJiaJuCube(ifstream& File,int type);
};
class cJiangLi:public cTaskFather
{
public:
	BOOL Process(int stage){ return TRUE; }
	void Init(){}
	void AutoGetJiangLi();
	void AddLShouJue(int rate){ Add(0, 40, rate, 5); }
	void AddHShouJue(int rate){ Add(0, 40, rate, 10); }
	void Reset(){ m_List.clear(); }
	void Add(int id, int type, int rate,int ran=1);//增加奖励项
	void SetBaoShi(int rate){ Add(0, 29, rate, 17); }
	void SetQiangHua(int rate);
	int m_MoenyRate;
	int m_ExpRate;
	int m_Moneytime;
	int m_Exptime;
	void SetMoeny(int rate, int time){ m_MoenyRate = rate; m_Moneytime = time; }
	void SetExp(int rate, int time){ m_ExpRate = rate; m_Exptime = time; }
	struct sJiangLiList
	{
		int m_Type;
		int m_Id;
		int m_Rate;
		int m_rand = 1;
	};
	vector<sJiangLiList> m_List;

};