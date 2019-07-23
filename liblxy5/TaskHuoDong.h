#pragma once
#include "_taskinc.h"


enum eHuoDong
{
	门派闯关,
	科举,
};


class cTaskHuoDong :public cTaskFather
{//12门派
public:
	void ReadytoFightmp(sTaskMapObj& list, eMengPai mp);//门派闯关战斗
	void Start(eHuoDong id);
	cTaskHuoDong(){ m_type = 35; }
	virtual void Init();
	void Initmp();
	virtual bool Process(int stage);
	bool Processmp(int stage);
	bool Processkj(int stage);
	array<sTaskMapObj, c_MenPaiNumber> m_List;
	array<int, c_MenPaiNumber> m_MengPaiId;
	cObj* m_NowNpc = 0;
	vector<int> m_Idlist;
	int m_Stage = 0;
	string GetText();
	void Save(ofstream& File);


	void Load(ifstream& File);
	int m_HuoDongID = -1;
	void SetTrigger(cTaskFather* p, int ret, int huanshu){ m_pTask = p; m_TaskRet = ret; m_TriggerHuanShu = huanshu; }
private:
	cTaskFather* m_pTask = 0;
	int m_TaskRet = -1;
	int m_TriggerHuanShu = 0;
	void UpdateJob(string text, int huanshu = -1);
	bool m_bInit12 = false;
};



