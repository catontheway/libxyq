#pragma once
#include "_taskinc.h"

class cTaskSM :public cTaskFather
{
public:
	void UpdateJob(string context);
	cObj* GetShiFu();
	string GetShiFuName();
	string GetShiFuMap();
	void Init();
	bool Process(int stage);
	//void AddTask(int type);
	void GetJiangLi();
	void CheckInit(int mengpaiid);
	void InitXiangFu();
	void InitShiWei();
	void Save(ofstream& File);

	void Load(ifstream& File);
	sNpc m_Npc;
	int  m_bXiangFuSuccess;
//private:
	int m_EnemyMengPai;
	sItem2 m_ShiWeiWeapon;//示威时NPC的武器
	cObj* m_pNowObj = 0;
	sNpc m_YuanJiu;
	vector<string> m_ShiWeiNameList[c_MenPaiNumber];
	vector<int>  m_ShiWeiIdList[c_MenPaiNumber];
	bool m_bInitShiWei = false;
	int m_TargetBBid = -1;

	bool m_bInitXiangFu = false;
	vector<string> m_XiangFuNameList;
	vector<string> m_XiangFuDiDianList;
	bool m_bInit[c_MenPaiNumber];
	bool m_bInit2;
	vector<string> m_NameList[c_MenPaiNumber];
	sItem2 m_ItemNeed;//记录当前师门要的东西
	string m_npcname; //记录当前师门要找的人
	string m_mapname;
	int m_SuccessNum;
	string m_enemyname;
	ulong m_enemyface;
	bool m_bHaveTask = 0;
};

