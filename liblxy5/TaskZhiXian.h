#pragma once
#include "_taskinc.h"

class cTaskZhiXian :public cTaskJuQing
{
public:
	void GetBaoXiangID(int type, int& id, int& index);
	cTaskZhiXian(){ m_type = 2008; m_AutoPath = "支线"; }
	virtual bool Process(int stage);
	bool Process0(int stage);
	bool Process1(int stage);//各种对白
	bool Process2(int stage);
	bool Process3(int stage);//各种宝箱
	bool Process4(int stage);
	bool Process6(int stage);//支线2
	//1015 西梁/女儿村
	void ProcessSelect(int stage);
private:
	cObj* m_pObj = 0;
	/*



	bool Process5(int stage);

	bool Process7(int stage);
	bool Process8(int stage);
	bool Process9(int stage);
	bool Process10(int stage);*/
};
class cTaskZhiXian2 :public cTaskJuQing
{
public:
	cTaskZhiXian2(){ m_type = 2009; m_AutoPath = "剧情2"; }
	virtual bool Process(int stage);
};



class cTaskZhiXian3 :public cTaskJuQing
{
public:
	cTaskZhiXian3(){ m_type = 2010; m_AutoPath = "剧情3"; }
	virtual bool Process(int stage);
	void Init2();
	bool LoadTeam(int id, string path, bool bEnemy);
	bool m_bPK = false;
	~cTaskZhiXian3();
private:

	bool m_bInit2;
	cObj* m_pFighter[10];
	cObj* m_PreFighter[10];
	bool m_islive[10];
	eFormation m_eOurFormation;
	int m_prehard = 100;
};

