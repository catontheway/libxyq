#include "_global.h"



void cTriggerTime::Process()
{
	cShiCheng& sc = g_pMainState->m_InterfaceDoor.m_TimeShiCheng;
	int y = sc.year;
	int m = sc.month;
	int d = sc.day;
	int h = sc.hour;
	for (int i = 0; i<m_list.size(); i++)
	{
		sTimeTrigger& t = m_list[i];
		if (t.m_y > y)continue;;
		if (t.m_y - y > t.m_y2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		if (t.m_m > m)continue;
		if (t.m_m - m > t.m_m2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		if (t.m_d > d)continue;
		if (t.m_d - d > t.m_d2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		if (t.m_h > h)continue;
		if (t.m_h - h > t.m_d2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		cTaskFather* task = m_list[i].m_pTask;
		int stage = m_list[i].m_Stage;
		m_list.erase(m_list.begin() + i);
		task->Process(stage);
		return Process();
	}
}

void cTriggerTime::Save(ofstream& File)
{
	File << " ";
	File << m_list.size() << " ";
	for (int i = 0; i < m_list.size(); i++)
	{
		File << m_list[i].m_h << " ";
		File << m_list[i].m_d << " ";
		File << m_list[i].m_m << " ";
		File << m_list[i].m_y << " ";
		File << m_list[i].m_h2 << " ";
		File << m_list[i].m_d2 << " ";
		File << m_list[i].m_m2 << " ";
		File << m_list[i].m_y2 << " ";
	}
}

void cTriggerTime::Load(ifstream& File)
{
	int num;
	File >> num;
	m_list.resize(num);
	for (int i = 0; i < num; i++)
	{
		File >> m_list[i].m_h;
		File >> m_list[i].m_d;
		File >> m_list[i].m_m;
		File >> m_list[i].m_y;
		File >> m_list[i].m_h2;
		File >> m_list[i].m_d2;
		File >> m_list[i].m_m2;
		File >> m_list[i].m_y2;

	}
}

void cTriggerTime::Add(cTaskFather* task, int stage, int h /*= -1*/, int d /*= -1*/, int m /*= -1*/, int y /*= -1*/, int y2 /*= 0*/, int m2 /*= 0*/, int d2 /*= 0*/, int h2 /*= 0*/)
{
	cShiCheng& t = g_pMainState->m_InterfaceDoor.m_TimeShiCheng;
	if (y == -1)y = t.year;
	if (m == -1)m = t.month;
	if (d == -1)d = t.day;
	for (int i = 0; i < m_list.size(); i++)
	{
		if (m_list[i].m_pTask == task)
		{
			m_list[i].m_y = y;
			m_list[i].m_d = d;
			m_list[i].m_m = m;
			m_list[i].m_h = h;
			m_list[i].m_y2 = y2;
			m_list[i].m_d2 = d2;
			m_list[i].m_m2 = m2;
			m_list[i].m_h2 = h2;
			m_list[i].m_Stage = stage;
		}
	}
	sTimeTrigger lis;
	lis.m_y = y;
	lis.m_d = d;
	lis.m_m = m;
	lis.m_h = h;
	lis.m_y2 = y2;
	lis.m_d2 = d2;
	lis.m_m2 = m2;
	lis.m_h2 = h2;
	lis.m_Stage = stage;
	lis.m_pTask = task;
	m_list.push_back(lis);
}

void cTriggerTime::Remove(cTaskFather* task)
{
	for (int i = 0; i < m_list.size(); i++)
	{
		if (m_list[i].m_pTask == task)
		{
			m_list.erase(m_list.begin() + i);
			return;
		}
	}
}