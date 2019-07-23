#include "_global.h"


void sNpc::Save(ofstream& File)
{
	File << g_strSpace;
	File << m_modeid << g_strSpace;
	if (-1 == m_modeid)
	{
		if (m_mapname.size())
		{
			File << 1 << g_strSpace;
			File << m_mapname << g_strSpace;
		}
		else File << 0 << g_strSpace;
		return;
	}
	File << m_name << g_strSpace;
	if (m_mapname == "")
	{
		File << 0 << g_strSpace;
	}
	else
	{
		File << 1 << g_strSpace;
		File << m_mapname << g_strSpace;
	}
	File << m_x << g_strSpace;
	File << m_y << g_strSpace;
	File << m_direction << g_strSpace;

	if (m_modeid >= 2000 || m_modeid < 1000)
	{//角色和召唤兽才有染色和进阶
		m_JinJieID.Save(File);
		if (m_modeid >= 2000)
		{
			File << weaponid << g_strSpace;
			File << weapontype << g_strSpace;
		}
		m_Ranse.Save(File);
	}
	File << g_strEnter;
}

void sNpc::Load(ifstream& File)
{
	File >> m_modeid;
	if (-1 == m_modeid)
	{
		int b;
		File >> b;
		if (b)File >> m_mapname;
		return;
	}
	File >> m_name;
	bool havemap;
	File >> havemap;
	if (havemap)
		File >> m_mapname;
	File >> m_x;
	File >> m_y;
	File >> m_direction;
	if (m_modeid >= 2000 || m_modeid < 1000)
	{//角色和召唤兽才有染色和进阶
		m_JinJieID.Load(File);
		if (m_modeid >= 2000)
		{
			File >> weaponid;
			File >> weapontype;
		}
		m_Ranse.Read(m_modeid, File, m_JinJieID.m_index);
	}
}

void sNpc::Set(string name, string mapname, int modeid, int x, int y, int direction /*= -1*/, int jinjie /*= 1*/)
{
	if (jinjie > 3)jinjie = 3;
	if (name == "")
	{
		if (modeid < 1000)
		{
			name = g_pMainState->m_PetDataManager.GetPetData(modeid)->m_Name;
		}
		else
			if (modeid < 2000)
			{
			name = g_pMainState->m_pNpcList[modeid - 1000].m_name;
			}
			else
			{
				name = g_pMainState->m_pCharacterDataList[modeid - 2000].m_Name;
			}
	}
	if (mapname.empty())
	{
		mapname = g_pMainState->m_Map.m_MapName;
	}
	m_name = name;
	m_mapname = mapname;
	if (direction == -1) AutoDirection4();
	else
		m_direction = direction;
	m_x = x;
	m_y = y;
	m_modeid = modeid;
	m_JinJieID.m_index = jinjie;
	m_JinJieID.m_JinJieNum = jinjie;
}

void sNpc::Reset()
{
	m_JinJieID.Reset();
	weaponid = -1;
	weapontype = -1;
}

void sNpc::SetRanse(int id0, int id1 /*= -1*/, int id2 /*= -1*/, int id3 /*= -1*/, int part)
{
	m_Ranse.m_ranse[part].Set(id0, id1, id2, id3);
	g_pMainState->m_ColorManage.Give2(&m_Ranse.m_ranse[part], m_modeid, part);
}




void cNpc::GetID(int POS_X, vector<ulong>& out)
{
	out.resize(1);
	switch (POS_X)
	{
	case POS_STAND:
		out[0] = m_pNpcData->m_stand;
		break;
	case POS_WALK:
		out[0] = m_pNpcData->m_walk;
		break;
	case POS_DIALOG:
		out[0] = m_pNpcData->m_dialog;
		break;
	}
}

