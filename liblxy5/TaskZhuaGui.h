#pragma once
#include "_taskinc.h"


class cTaskZhuaGui :public cTaskFather, public cTriggerObj
{
public:
	void Init();
	bool Process(int stage);

	bool ReadyToFight(sNpc& npc);
	vector<string> m_Firstname;
	vector<string> m_Secondname;
	vector<string> m_Thirdname;
	string AutoMakeName();
	void AutoGetGost(sNpc& npc, string mapname);
	void GetErrPos(sNpc npc, int& xout, int& yout);
	vector<string> m_MapNameList;
	sNpc m_Ghost;
	void Save(ofstream& File);
	void Load(ifstream& File);
	//
	void SetTrigger(cTaskFather* p, int num, int stage);
	void UpdateZGJob(bool m_bTrue = false);
private:
	cTaskFather* m_pTask = 0;
	int m_RetStage;
	int m_RetNum;
};


