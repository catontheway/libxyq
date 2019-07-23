#include "_global.h"

bool cTrigger::AddTask(cTaskFather* ptask, int stage)
{
	sTaskFather task;
	task.m_pTask = ptask;
	task.m_Stage = stage;
	int num = m_TaskList.size();
	for (int i = 0; i < num; i++)
	{
		if (m_TaskList[i].m_pTask->m_type == ptask->m_type)
		{
			m_TaskList[i].m_Stage = stage;
			return false;
		}
	}
	m_TaskList.push_back(task);
	return true;
}

void cTrigger::ReMove(cTaskFather* pTask)
{
	return ReMove(pTask->m_type);
}

void cTrigger::ReMove(int id)
{
	int num = m_TaskList.size();
	for (int i = 0; i < num; i++)
	{
		if (m_TaskList[i].m_pTask->m_type == id)
		{
			m_TaskList.erase(m_TaskList.begin() + i);
		}
	}
}

bool cTrigger::Process()
{
	int num = m_TaskList.size();
	if (!num) return false;
	bool b = false;
	for (int i = 0; i < num; i++)
	{
		if (m_TaskList[i].m_pTask->Process(m_TaskList[i].m_Stage))
		{
			b = true;
		}
	}
	return b;
}

bool cTrigger::ProcessReMove()
{
	int num = m_TaskList.size();
	if (!num)return false;
	cTaskFather* ptask = m_TaskList[0].m_pTask;
	int stage = m_TaskList[0].m_Stage;
	Clear();
	ptask->Process(stage);
	return true;
}



