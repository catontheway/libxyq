#pragma once
#include "_global.h"

class cTaskJiangLi :public cTaskFather
{
public:
	bool Process(int stage){ return true; }
	void Init(){}
	void AutoGetJiangLi();
	void AddLShouJue(int rate){ Add(0, 40, rate, 5); }
	void AddHShouJue(int rate){ Add(0, 40, rate, 10); }
	void Reset(){ m_List.clear(); }
	void Add(int id, int type, int rate, int ran = 1);//Ôö¼Ó½±ÀøÏî
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