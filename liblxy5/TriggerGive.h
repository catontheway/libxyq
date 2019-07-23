#pragma once
#include "_taskinc.h"

class cTriggerGive
{
public:
	void Clear(){ m_List.clear(); }
	struct sTriggerGive
	{
		string m_name;
		int m_itemid;
		int m_itemtype;
		cTaskFather* m_ptask;
		int m_ret;
		void Set(string name, int itemid, int itemtype, cTaskFather* ptask, int ret)
		{
			m_name = name;
			m_itemid = itemid;
			m_itemtype = itemtype;
			m_ptask = ptask;
			m_ret = ret;
		}
		void Save(ofstream& File);

		void Load(ifstream& File);

	};
	void AddTask(string name, int itemid, int itemtype, cTaskFather* ptask, int ret, bool bHuChi = true);
	void ReMove(cTaskFather* ptask);
	void ReMove(int id);
	bool Process(string name, int id, int type);
	void Save(ofstream& File);
	void Load(ifstream& File);
	vector<sTriggerGive> m_List;
};

