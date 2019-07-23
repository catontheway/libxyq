#pragma once
#include "_taskinc.h"

struct sTaskMapObj :public sTaskFather
{
	sNpc m_Npc;
	void operator=(sTaskMapObj& data)
	{
		m_Npc = data.m_Npc;
		m_pTask = data.m_pTask;
		m_Stage = data.m_Stage;
	}
	void operator=(sFriendList& data);
	void Save(ofstream& File);
	void Load(ifstream& File);
};

