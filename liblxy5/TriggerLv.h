#pragma once
#include "_taskinc.h"

class cTriggerLv
{
public:
	bool AddTask(cTaskFather* ptask, int stage, int lv);
	bool Process();
	void ReMove(int id);
	void ReMove(cTaskFather* pTask);
	struct sLvTrigger :public sTaskFather
	{
		int lv;
	};
	void Clear(){ m_datalist.clear(); }
	void Save(ofstream& File);
	void Load(ifstream& File);
private:
	vector<sLvTrigger> m_datalist;
private:

};

