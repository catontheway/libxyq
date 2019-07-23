#include "_global.h"


bool cTaskFB::Process(int stage)
{

	switch (m_FBID)
	{
	case 0:ProcessWj(stage); break;
	case 1:ProcessSL(stage); break;
	case 2:ProcessCC(stage); break;
	case 3:ProcessSM(stage); break;
	case 4:ProcessSJ(stage); break;
	}
	return true;
}



bool cTaskFB::Start(int id)
{
	m_FBID = id;
	m_TextList.clear();
	ifstream File;
	ostringstream oss;
//	oss << g_pathData << "副本//" << id << ".txt";
	File.open(oss.str());
	if (!File)ERRBOX;
	int num;
	File >> num;
	if (num)
	{
		m_TextList.resize(num);
		getline(File, m_TextList[0]);
		for (int i = 0; i < num; i++)
		{
			getline(File, m_TextList[i]);
		}
	}
	File.close();
	m_List.clear();
	m_List2.clear();
	return true;
}


void cTaskFB::Load(ifstream& File)
{//放在地图读取后
	m_List.clear();
	m_List2.clear();
	File >> m_FBID;
	if (-1 == m_FBID)return;
	File >> m_Stage;
	File >> m_Stage2;
	File >> m_HuanShu;
	Start(m_FBID);
	int npc2num;
	File >> npc2num;
	m_List.resize(npc2num);
	for (int i = 0; i < npc2num; i++)
		m_List[i].Load(File);

	File >> npc2num;
	m_List2.resize(npc2num);
	for (int i = 0; i < npc2num; i++)
	{
		m_List2[i].Load(File);
	}
	bool havetrigger;
	File >> havetrigger;
	if (havetrigger)
	{
		int type;
		File >> type;
		m_pEnd = g_pMainState->FindTaskByID(type);
		File >> m_Ret;
	}
}

void cTaskFB::Save(ofstream& File)
{
	File << "\n";
	File << m_FBID << " ";
	if (-1 == m_FBID)return;
	File << m_Stage << " ";
	File << m_Stage2 << " ";
	File << m_HuanShu << " ";
	File << m_List.size() << " ";
	for (int i = 0; i < m_List.size(); i++)
	{
		m_List[i].Save(File);
	}
	File << m_List2.size() << " ";
	for (int i = 0; i < m_List2.size(); i++)
	{
		m_List2[i].Save(File);
	}
	if (m_pEnd)
	{
		File << 1 << " ";
		File << m_pEnd->m_type << " ";
		File << m_Ret << " ";
	}
	else
	{
		File << 0 << " ";
	}
}


void cTaskFB::RemoveNpc(sNpc* p, bool bRemoveList)
{
	cObj* po = g_pMainState->FindObjByNpc(p);
	RemoveNpc(po, bRemoveList);
}


void cTaskFB::RemoveNpc(cObj*& p, bool bRemoveList)
{
	if (!p)return;
	if (bRemoveList)
	{
		uint i;
		for (i = 0; i < m_List.size(); i++)
		{
			if (m_List[i].m_Npc.m_x == p->GetX() / 20)
				if (m_List[i].m_Npc.m_y == (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20)
					if (m_List[i].m_Npc.m_name == p->m_TrueName.GetString())
					{
				m_List.erase(m_List.begin() + i);
				break;
					}
		}
		if (i == m_List.size())
			for (i = 0; i < m_List2.size(); i++)
			{
			if (m_List2[i].m_Npc.m_x == p->GetX() / 20)
				if (m_List2[i].m_Npc.m_y == (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20)
					if (m_List2[i].m_Npc.m_name == p->m_TrueName.GetString())
					{
				m_List2.erase(m_List2.begin() + i);
				break;
					}
			}
	}
	g_pMainState->m_Map.RemoveNpc(p, true);
	p = 0;
}



void cTaskFB::AddTriggerDialog(string path, int id, int ret)
{
	g_pMainState->m_TriggerDialog.AddTaskFB(path, id, this, ret);
}

void cTaskFB::AddNpc()
{
	for (int i = 0; i < m_List.size(); i++)
	{
		g_pMainState->m_Map.AddNpc(&m_List[i]);
	}
	for (int i = 0; i < m_List2.size(); i++)
	{
		g_pMainState->m_Map.AddNpc(&m_List2[i]);
	}
	g_pMainState->FindObj();
}

void cTaskFB::UpdateJob(string context, int time/*=-1*/, int falret /*= 1002*/, string title /*= ""*/)
{ //
	sJob job;
	if (title == "")
		title = "副本";
	job.Set(title, context, time, this, falret);
	g_pMainState->m_Job.AddaJob(job);
}



void cTaskFB::GetItem(int type, int id, bool needtag, int num)
{
	sItem2 item;
	item.m_Num = num;
	item.Set(type, id);
	g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
	if (needtag)
	{
		ostringstream oss;
		oss << item.m_pItemData->m_Name + " +1";
		g_pMainState->m_Tags.Add(oss.str());
	}
}



void cTaskFB::AddTriggerDialog(int id, int ret)
{
	ostringstream oss;
	oss << m_FBID;
	g_pMainState->m_TriggerDialog.AddTaskFB(oss.str(), id, this, ret);
}


sTaskMapObj* cTaskFB::FindNpcByObj(cObj* p)
{
	int x = p->GetX() / 20;
	int y = (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20;
	int modeid = p->GetModeID();

	for (int i = 0; i < m_List.size(); i++)
	{
		if (m_List[i].m_Npc.m_x == x)
			if (m_List[i].m_Npc.m_y == y)
				if (m_List[i].m_Npc.m_modeid == modeid)
				{
			return &m_List[i];
				}
	}
	for (int i = 0; i < m_List2.size(); i++)
	{
		if (m_List2[i].m_Npc.m_x == x)
			if (m_List2[i].m_Npc.m_y == y)
				if (m_List2[i].m_Npc.m_modeid == modeid)
				{
			return &m_List2[i];
				}
	}
	return 0;
}

void cTaskFB::ClearNpc()
{
	g_pMainState->m_TaskNormal.m_pNpc = 0;
	if (g_pMainState->m_pNowSelect)
	{
		g_pMainState->m_pNowSelect->SetShine(false);
		g_pMainState->m_pNowSelect = 0;
	}
	g_pMainState->m_Map.RemoveAllNpc();
	m_List2.clear();
	m_List.clear();
	g_pMainState->FindObj();
}
void cTaskFB::StageSetSameNpc(vector<int> modid, string mapname, int ret, int num, string name)
{
	m_List.resize(num);
	int x, y;
	g_pMainState->m_Map.AutoGetPos(x, y, mapname);
	for (int i = 0; i < m_List.size(); i++)
	{
		g_pMainState->m_Map.AutoGetPos(x, y);
		SetNpc(m_List[i], ret, name, mapname, modid[rand() % modid.size()], x, y);
	}
	if (g_pMainState->m_Map.m_MapName == mapname)
	{
		AddNpc();
	}
}

void cTaskFB::StageSetSameNpc(int modid, string mapname, int ret, int num, string name)
{
	vector<int>  mod2;
	mod2.push_back(modid);
	StageSetSameNpc(mod2, mapname, ret, num, name);
}


void cTaskFB::StageSetSameNpc2(vector<int> modid, string mapname, int ret, int num, string name)
{
	m_List2.resize(num);
	int x, y;
	g_pMainState->m_Map.AutoGetPos(x, y, mapname);
	for (int i = 0; i < m_List2.size(); i++)
	{
		g_pMainState->m_Map.AutoGetPos(x, y);
		SetNpc(m_List2[i], ret, name, mapname, modid[rand() % modid.size()], x, y);
	}
	if (g_pMainState->m_Map.m_MapName == mapname)
	{
		AddNpc();
	}
}


void cTaskFB::StageSetSameNpc2(int modid, string mapname, int ret, int num, string name)
{
	vector<int>  mod2;
	mod2.push_back(modid);
	StageSetSameNpc2(mod2, mapname, ret, num, name);
}


void cTaskFB::EndFB()
{
	g_pMainState->m_Tags.Add("副本结束了");
	g_pMainState->m_Map.LoadMap(485, 144, "长安城");
	g_pMainState->m_Job.ReMoveJob(this);
	RemoveTriggerObjMap();
	RemoveTriggerObj();
	m_List.clear();
	m_List2.clear();
	m_FBID = -1;
	if (m_pEnd)
	{
		cTaskFather* p = m_pEnd;
		m_pEnd = 0;
		p->Process(m_Ret);
	}

}

void cTaskFB::SetTask(cTaskFather* p, int ret)
{
	m_pEnd = p;
	m_Ret = ret;
}

void cTaskFB::SetMusicFB()
{
	SetMusic();
	return;
	string name;
	switch (rand() % 2)
	{
	case 0:
		name = "战斗_任务";
		break;
	default:
		name = "战斗_任务2";
		break;
	}
	SetMusic(name);
}