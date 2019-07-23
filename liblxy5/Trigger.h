#pragma once
#include "_taskinc.h"

struct sTalkList //代表一句话
{
	string context;
	string name;
	void Save(ofstream& File)
	{
		File << "text\n";
		File << name << "\n";
		File << context << "\n";
	}
	void Load(ifstream& File)
	{
		string dustbin;
		getline(File, dustbin);
		getline(File, name);
		getline(File, context);
	}
};


class cTrigger
{
public:
	bool AddTask(cTaskFather* ptask,int stage);
	void ReMove(cTaskFather* pTask);
	void ReMove(int id);
	bool Process();
	bool ProcessReMove();
	void Clear(){ m_TaskList.clear(); }
	vector<sTaskFather> m_TaskList;
private:	
};


