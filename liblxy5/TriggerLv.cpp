#include "_global.h"



bool cTriggerLv::AddTask(cTaskFather* ptask, int stage, int lv)
{
	int num = m_datalist.size();
	for (int i = 0; i < num; i++)
	{
		if (m_datalist[i].m_pTask->m_type == ptask->m_type)
		{
			m_datalist[i].lv = lv;
			m_datalist[i].m_Stage = stage;
			return true;
		}
	}
	sLvTrigger data;
	data.lv = lv;
	data.m_pTask = ptask;
	data.m_Stage = stage;
	m_datalist.push_back(data);
	return true;
}

bool cTriggerLv::Process()
{
	int num = m_datalist.size();
	int i = 0;
	for (; i < num; i++)
	{
		if (g_pCharacter->m_PcData.m_Lv >= m_datalist[i].lv)
		{
			int stage = m_datalist[i].m_Stage;
			cTaskFather* ptask = m_datalist[i].m_pTask;
			m_datalist.erase(m_datalist.begin() + i);
			ptask->Process(stage);
			break;
		}
	}
	if (i < num)
		return Process();
	return true;
}

void cTriggerLv::ReMove(int i)
{
	if (m_datalist.size())
		m_datalist.erase(m_datalist.begin() + i);
}

void cTriggerLv::ReMove(cTaskFather* pTask)
{
	for (int i = 0; i < m_datalist.size(); i++)
		if (m_datalist[i].m_pTask == pTask)ReMove(i);
}

void cTriggerLv::Save(ofstream& File)
{
	File << "\n";
	File << m_datalist.size() << " ";;
	for (int i = 0; i < m_datalist.size(); i++)
	{
		File << m_datalist[i].m_pTask->m_type << " ";
		File << m_datalist[i].m_pTask->m_HuanShu << " ";
		File << m_datalist[i].m_Stage << " ";
		File << m_datalist[i].lv << " ";
	}
	File << "\n";
}

void cTriggerLv::Load(ifstream& File)
{
	int num;
	File >> num;
	m_datalist.resize(num);
	int type;
	int huanshu;
	for (int i = 0; i < num; i++)
	{
		File >> type;
		File >> huanshu;
		File >> m_datalist[i].m_Stage;
		m_datalist[i].m_pTask = g_pMainState->FindTaskByID(type);
		m_datalist[i].m_pTask->m_HuanShu = huanshu;
		File >> m_datalist[i].lv;
	}
}


