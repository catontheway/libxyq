#pragma once
#include "_taskinc.h"


class cTaskBaotu :public cTaskFather
{
public:
	void Init();
	bool Process(int stage);
	vector<string> m_Firstname;
	vector<string> m_Secondname;

	string AutoMakeName();
	vector<string> m_MapNameList;
	sNpc m_Robber;
	void Save(ofstream& File)
	{
		m_Robber.Save(File);
	}
	void Load(ifstream& File)
	{
		m_Robber.Load(File);
	}

	cTaskBaotu(){ Init(); }
};
