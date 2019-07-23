#pragma once
#include "_taskinc.h"

class cTriggerMapObj
{
public:
	bool AddTask(cTaskFather* ptask, int stage, string mapname, bool bHuChi = true);
	void AddTask(sTaskMapObj& target);
	bool AddTask(cTaskFather* ptask, int stage, sNpc Npc, bool bHuChi = true);
	bool Process();
	sTaskMapObj*  FindByName(string name);
	void ReMove(int id);
	void ReMove(cTaskFather* pTask, int ret = -1);
	void ReMove(cTaskFather* pTask, string mapname);
	void ReMove(cTaskFather* pTask, int x, int y);


	vector<sTaskMapObj> m_datalist;
	void Save(ofstream& File);
	void Load(ifstream& File);
};



