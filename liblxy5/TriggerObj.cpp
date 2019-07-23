#include "_global.h"


bool cTriggerObj::Process(string name)
{
	int num = m_datalist.size();
	if (!num)return false;
	for (int i = 0; i < num; i++)
	{
		if (0 == m_datalist[i].m_mapname.compare(g_pMainState->m_Map.m_MapName))
		{
			if (0 == m_datalist[i].m_name.compare(name))
			{
				m_datalist[i].m_pTask->Process(m_datalist[i].m_Stage);
				return true;
			}
		}
	}
	return false;
}

bool cTriggerObj::AddTask(string name, string mapname, cTaskFather* ptask, int stage, bool bHuChi)
{
	if (bHuChi)
	{
		int num = m_datalist.size();
		for (int i = 0; i < num; i++)
		{
			if (m_datalist[i].m_pTask->m_type == ptask->m_type)
			{
				m_datalist[i].m_Stage = stage;
				m_datalist[i].m_name = name;
				m_datalist[i].m_mapname = mapname;
				return false;
			}
		}
	}
	sObjTrigger task;
	task.m_pTask = ptask;
	task.m_Stage = stage;
	task.m_name = name;
	task.m_mapname = mapname;
	m_datalist.push_back(task);
	return true;
}

void cTriggerObj::ReMove(int i)
{
	m_datalist.erase(m_datalist.begin() + i);
}

void cTriggerObj::ReMove(cTaskFather* pTask)
{
	for (int i = 0; i < m_datalist.size(); i++)
	{
		if (pTask->m_type == m_datalist[i].m_pTask->m_type)
		{
			ReMove(i);
			return ReMove(pTask);
		}
	}
}

void cTriggerObj::Save(ofstream& File)
{
	File << "\n";
	File << m_datalist.size() << " ";
	for (int i = 0; i < m_datalist.size(); i++)
	{
		File << m_datalist[i].m_pTask->m_type << " ";
		File << m_datalist[i].m_pTask->m_HuanShu << " ";
		File << m_datalist[i].m_Stage << "\n";
		File << m_datalist[i].m_name << "\n";
		File << m_datalist[i].m_mapname << "\n";
	}
	File << "\n";
}

void cTriggerObj::Load(ifstream& File)
{
	m_datalist.clear();
	int num;
	File >> num;
	if (!num)return;
	int type;
	int huanshu;
	m_datalist.resize(num);

	for (int i = 0; i < num; i++)
	{
		cTriggerObj::sObjTrigger& data = m_datalist[i];
		File >> type;
		File >> huanshu;
		File >> data.m_Stage;
		data.m_pTask = g_pMainState->FindTaskByID(type);
		data.m_pTask->m_HuanShu = huanshu;
		getline(File, data.m_name);
		getline(File, data.m_name);
		getline(File, data.m_mapname);
	}
}