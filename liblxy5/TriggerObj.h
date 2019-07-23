#pragma once
#include "_taskinc.h"

class cTriggerObj
{
public:
	bool AddTask(string name, string mapname, cTaskFather* ptask, int stage, bool bHuChi = true);
	bool Process(string name);
	void ReMove(int id);
	void ReMove(cTaskFather* pTask);
	struct sObjTrigger :public sTaskFather
	{
		string m_name;
		string m_mapname;
	};
	vector<sObjTrigger> m_datalist;
	void Save(ofstream& File);
	void Load(ifstream& File);
};

