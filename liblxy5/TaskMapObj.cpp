#include "_global.h"

void sTaskMapObj::Save(ofstream& File)
{
	m_Npc.Save(File);
	if (m_pTask)
	{
		File << 1 << " ";
		File << m_Stage << " ";
		File << m_pTask->m_type << " ";
	}
	else File << 0 << " ";
}

void sTaskMapObj::Load(ifstream& File)
{
	m_Npc.Load(File);
	bool havetrigger;
	File >> havetrigger;
	if (havetrigger)
	{
		File >> m_Stage;
		int id;
		File >> id;
		m_pTask = g_pMainState->FindTaskByID(id);
	}
	else
	{
		m_pTask = 0;
	}
}

void sTaskMapObj::operator=(sFriendList& data)
{
	m_Npc.m_name = data.m_Name;
	if (data.m_modeid < 1000)
		m_Npc.m_modeid = 2000 + data.m_modeid;
	else
		m_Npc.m_modeid = data.m_modeid;
	//武器造型
	m_Npc.weapontype = data.m_weapontype;
	m_Npc.weaponid = data.m_weaponid;
	m_Npc.m_JinJieID = data.m_JinJieNum;
	//染色
	m_Npc.m_Ranse = data.m_Ranse;
	//目前就写这点吧,有需要继续
}



