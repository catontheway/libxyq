#include "_global.h"



void cTriggerGive::ReMove(cTaskFather* ptask)
{
	for (int i = 0; i < m_List.size(); i++)
	{
		if (m_List[i].m_ptask->m_type == ptask->m_type)
		{
			m_List.erase(m_List.begin() + i);
			return ReMove(ptask);
		}
	}
}

void cTriggerGive::ReMove(int id)
{
	m_List.erase(m_List.begin() + id);
}

void cTriggerGive::AddTask(string name, int itemid, int itemtype, cTaskFather* ptask, int ret, bool bHuChi)
{
	if (bHuChi)ReMove(ptask);
	sTriggerGive data;
	data.Set(name, itemid, itemtype, ptask, ret);
	m_List.push_back(data);
}

bool cTriggerGive::Process(string name, int id, int type)
{
	int num = m_List.size();
	if (!num)return false;
	for (int i = 0; i < num; i++)
	{
		if (m_List[i].m_name == name)
			if (m_List[i].m_itemtype == type)
				if (m_List[i].m_itemid == id)
				{
			cTaskFather* p = m_List[i].m_ptask;
			int stage = m_List[i].m_ret;
			ReMove(i);
			p->Process(stage);
			return true;
				}
	}
	return false;
}

void cTriggerGive::Save(ofstream& File)
{
	File << "\n";
	File << m_List.size() << " ";
	for (int i = 0; i < m_List.size(); i++)
		m_List[i].Save(File);
	File << "\n";
}
void cTriggerGive::Load(ifstream& File)
{
	int num;
	File >> num;
	m_List.resize(num);
	for (int i = 0; i < num; i++)
		m_List[i].Load(File);
}
void cTriggerGive::sTriggerGive::Save(ofstream& File)
{
	File << " ";
	if (m_name == "")
	{
		ERRBOX;
	}
	else
		File << m_name << " ";
	File << m_itemid << " ";
	File << m_itemtype << " ";
	File << m_ptask->m_type << " ";
	File << m_ret << " ";
}
void cTriggerGive::sTriggerGive::Load(ifstream& File)
{
	File >> m_name;
	File >> m_itemid;
	File >> m_itemtype;
	int id;
	File >> id;
	m_ptask = g_pMainState->FindTaskByID(id);
	File >> m_ret;
}
