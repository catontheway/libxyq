#include "_global.h"


bool cTriggerMapObj::AddTask(cTaskFather* ptask, int stage, sNpc Npc, bool bHuChi)
{
	int num = m_datalist.size();
	if (bHuChi)
		for (int i = 0; i < num; i++)
		{
		if (m_datalist[i].m_pTask)
			if (m_datalist[i].m_pTask->m_type == ptask->m_type)
			{
			if (m_datalist[i].m_Npc.m_mapname == Npc.m_mapname)
			{
				m_datalist[i].m_Npc = Npc;
				m_datalist[i].m_Stage = stage;
				return false;
			}
			}
		}
	sTaskMapObj data;
	data.m_pTask = ptask;
	data.m_Stage = stage;
	data.m_Npc = Npc;
	m_datalist.push_back(data);
	return true;
}

bool cTriggerMapObj::AddTask(cTaskFather* ptask, int stage, string mapname, bool bHuChi)
{
	sNpc npc;
	npc.m_mapname = mapname;
	return AddTask(ptask, stage, npc, bHuChi);
}

void cTriggerMapObj::AddTask(sTaskMapObj& target)
{
	for (int i = 0; i < m_datalist.size(); i++)
	{
		if (m_datalist[i].m_Npc.m_x == target.m_Npc.m_x)
			if (m_datalist[i].m_Npc.m_y == target.m_Npc.m_y)
				if (m_datalist[i].m_Npc.m_name == target.m_Npc.m_name)
					if (m_datalist[i].m_Npc.m_mapname == target.m_Npc.m_mapname)
					{
			return;
					}
	}
	m_datalist.push_back(target);
	if (g_pMainState->m_Map.m_MapName == target.m_Npc.m_mapname)
	{
		g_pMainState->m_Map.AddNpc(&target, true);
	}

}

bool cTriggerMapObj::Process()
{
	int num = m_datalist.size();
	if (!num)return false;
	bool bTrigger;
	for (int i = 0; i < num; i++)
	{
		if (i < m_datalist.size())
		{
			bTrigger = false;
			if (m_datalist[i].m_Npc.m_mapname == "ÎÞ")bTrigger = true;
			if (m_datalist[i].m_Npc.m_mapname == g_pMainState->m_Map.m_MapName)bTrigger = true;
			if (bTrigger)
			{
				if (m_datalist[i].m_Npc.m_modeid > -1)
				{
					g_pMainState->m_Map.AddNpc(&m_datalist[i]);
				}
				else
				{
					m_datalist[i].m_pTask->Process(m_datalist[i].m_Stage);
				}
			}
		}
		else return true;
	}
	return true;
}

void cTriggerMapObj::ReMove(int i)
{
	if (m_datalist.size())
	{
		m_datalist.erase(m_datalist.begin() + i);
	}
}
void cTriggerMapObj::ReMove(cTaskFather* pTask, int ret)
{
	for (int i = 0; i < m_datalist.size(); i++)
		if (m_datalist[i].m_pTask == pTask)
		{
		if (ret == -1)
		{
			ReMove(i);
			return ReMove(pTask, ret);
		}
		else
		{
			if (m_datalist[i].m_Stage == ret)
			{
				ReMove(i);
				return;
			}
		}
		}
}

void cTriggerMapObj::ReMove(cTaskFather* pTask, string mapname)
{
	for (int i = 0; i < m_datalist.size(); i++)
	{
		if (m_datalist[i].m_pTask == pTask&&m_datalist[i].m_Npc.m_mapname == mapname)
		{
			ReMove(i);
			return;
		}
	}
}

void cTriggerMapObj::ReMove(cTaskFather* pTask, int x, int y)
{
	for (int i = 0; i < m_datalist.size(); i++)
	{
		if (m_datalist[i].m_pTask == pTask)
		{
			if (m_datalist[i].m_Npc.m_x == x&&m_datalist[i].m_Npc.m_y == y)
			{
				ReMove(i);
				return;
			}
		}
	}
}

void cTriggerMapObj::Save(ofstream& File)
{
	File << "\n";
	File << "µØÍ¼trigger" << " ";
	File << m_datalist.size() << " ";;
	for (int i = 0; i < m_datalist.size(); i++)
	{
		sTaskMapObj& li = m_datalist[i];
		li.Save(File);
	}
	File << "\n";
}

void cTriggerMapObj::Load(ifstream& File)
{
	m_datalist.clear();
	string dustbin;
	int num;
	File >> dustbin;
	while (dustbin != "µØÍ¼trigger")
		ERRBOX;
	File >> num;
	if (!num)return;
	m_datalist.resize(num);
	for (int i = 0; i < m_datalist.size(); i++)
	{
		sTaskMapObj& li = m_datalist[i];
		li.Load(File);
	}
}

sTaskMapObj* cTriggerMapObj::FindByName(string name)
{
	int num = m_datalist.size();
	for (int i = 0; i < num; i++)
	{
		if (0 == (m_datalist[i].m_Npc.m_name).compare(name))
		{
			return &m_datalist[i];
		}
	}
	return 0;
}



