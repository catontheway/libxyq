#pragma once
#include "_uiinc.h"

struct sFriendList
{
	int getIDinTeam();
	bool CheckInTeam();
	//bool m_bOnLine;
	int m_traderLV = 0;
	int m_Feeling = 0;//好感度
	string m_Name;//名字
	string m_dataFileName;//所处文件的名字
	int  m_stronglv;//角色的强度会改变
	int  m_modeid;
	bool m_bDuJie = 0;//是否渡劫
	//武器造型
	int m_weapontype = -1;
	int m_weaponid = -1;
	cJinJieNum m_JinJieNum;
	sZiZhi m_zizhi;//资质
	//染色
	sChangeColorData2 m_Ranse;
	//钱
	int  m_money;
	//坐骑
	bool  m_bOnZuoQi = 0;
	int   m_ZuoQiID = -1;
	sChangeColorData m_ZuoQiRanse;
	int   m_bZhuangShi = 0;
	int   m_ZhuangShiID = -1;
	sChangeColorData m_ZhuangShiRanse;

	int  m_FightBB = -1;//首发召唤兽
	vector<sShangPinPet>  m_BBList;
	//vector<int>  m_PetSkillList;
	void Save(ofstream& File);
	void Load(ifstream& File);
	ulong GetFriendHead();
	ulong GetDialogHead();
};

// 好友定制
class cInterfaceFriendQiangHua :public cInterfaceFather
{
public:
	void Set(sFriendList& list);
	void Update();
	bool Init();
	bool CheckRB();
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	virtual void OnOff(bool NeedShow);
	bool Move(int xPos, int yPos);
	void Change(int id);
private:
	bool m_bUpdateTeam;
	int m_Mode = 0;
	sFriendList* m_pData;
	cObjWas m_Buttonp[12];
	cText m_Name;
	cText m_Money;
	cText m_title;
	bool m_bInit = false;
	//cWasFile m_Back;

	cText m_Text[12];
};

