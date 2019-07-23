#include "_global.h"



void cFangWu::GoIn()
{
	switch (m_GuiMo)
	{
	case 0:
		g_pMainState->m_Map.LoadMap(13, 8, (char*)GetMapName().c_str());
		break;
	case 1:
	case 3:
		g_pMainState->m_Map.LoadMap(18, 12, (char*)GetMapName().c_str());
		break;
	case 2:
		g_pMainState->m_Map.LoadMap(26, 18, (char*)GetMapName().c_str());
		break;
	case 4:
		g_pMainState->m_Map.LoadMap(49, 11, (char*)GetMapName().c_str());
		break;
	default:return;
	}
	for (int i = 0; i < m_JiaJu.size(); i++)
	{
		g_pMainState->m_Map.AddJiaJu(&m_JiaJu[i]);
	}
	g_pMainState->m_Map.AddNpc(&m_GuanJia, 0, "管家");
	for (int i = 0; i < g_pMainState->m_FangWu.m_List.size(); i++)
	{
		g_pMainState->m_Map.AddNpc(&g_pMainState->m_FangWu.m_List[i], &g_pMainState->m_TaskNormal, "无", 9);
	}
	g_pMainState->FindObj();
}

std::string cFangWu::GetMapName()
{
	string out;
	if (m_DiBan.GetNum() == 0)
	{
		switch (m_GuiMo)
		{
		case 0:	out = "普通民宅0"; break;
		case 1:	out = "高级华宅0"; break;
		case 2: out = "顶级豪宅0"; break;
		case 3:	out = "高级华宅10"; break;
		case 4: out = "顶级豪宅10"; break;
		}
	}
	else
		switch (m_DiBan.GetType())
	{
		case 35://1级家具
			switch (m_GuiMo)
			{
			case 0:	out = "普通民宅1"; break;
			case 1:	out = "高级华宅1"; break;
			case 2: out = "顶级豪宅1"; break;
			case 3:	out = "高级华宅11"; break;
			case 4: out = "顶级豪宅11"; break;
			}
			break;
		case 36://2级家具
			switch (m_GuiMo)
			{
			case 0:	out = "普通民宅2"; break;
			case 1:	out = "高级华宅2"; break;
			case 2: out = "顶级豪宅2"; break;
			case 3:	out = "高级华宅12"; break;
			case 4: out = "顶级豪宅12"; break;
			}
			break;
		case 37://3级家具
			switch (m_GuiMo)
			{
			case 0:	out = "普通民宅3"; break;
			case 1:	out = "高级华宅3"; break;
			case 2: out = "顶级豪宅3"; break;
			case 3:	out = "高级华宅13"; break;
			case 4: out = "顶级豪宅13"; break;
			}
			break;
		case 38://4级家具
			switch (m_DiBan.GetID())
			{
			case 19://兔
				switch (m_GuiMo)
				{
				case 0:	out = "普通民宅5"; break;
				case 1:	out = "高级华宅5"; break;
				case 2: out = "顶级豪宅5"; break;
				case 3:	out = "高级华宅15"; break;
				case 4: out = "顶级豪宅15"; break;
				}
				break;
			case 18://海蓝
				switch (m_GuiMo)
				{
				case 0:	out = "普通民宅4"; break;
				case 1:	out = "高级华宅4"; break;
				case 2: out = "顶级豪宅4"; break;
				case 3:	out = "高级华宅14"; break;
				case 4: out = "顶级豪宅14"; break;
				}
				break;

			}

	}
	return out;
}

bool cFangWu::AddJiaJu(sJiaJu& jiaju)
{
	if (m_JiaJu.size() < (m_GuiMo + 1) * 5)
	{
		m_JiaJu.push_back(jiaju);
		m_HuanJinDu += jiaju.m_JiaJu.GetType() - 34;
		if (m_HuanJinDu > 100)m_HuanJinDu = 100;


		CheckHuanJin();
		return true;
	}
	else
	{
		g_pMainState->m_Tags.Add("家具已满");
	}
	return false;
}

int cFangWu::GetHuanJin()
{// 环境度 100 +40+ 55 + 60= 255
	int huanjing;
	if (m_DiBan.GetNum())
		huanjing = m_HuanJinDu + m_List.size() * 5 + (m_GuiMo + 1) * 11 + (m_DiBan.GetType() - 34) * 15;
	else
		huanjing = m_HuanJinDu + m_List.size() * 5 + (m_GuiMo + 1) * 11;
	if (huanjing < 0)huanjing = 0;
	return huanjing;
}



cFangWu::cFangWu()
{
	m_GuiMo = -1;
	m_DiBan.m_Num = 0;
	m_GuanJia.m_modeid = 1039;
	m_GuanJia.m_name = "管家";
	m_GuanJia.Set(-1, -1);
}

void cFangWu::Init()
{
	if (m_bInit)return;
	m_bInit = true;
// 	ifstream File;
// 	string path = g_pathData;
// 	path += "镇宅兽.txt";
// 	File.open(path.c_str());
// 	int num;
// 	File >> num;
// 	m_YaHuangIDList.resize(num);
// 	string dustbin;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> m_YaHuangIDList[i];
// 		getline(File, dustbin);
// 	}
// 	File.close();

	for (int iNpc = 136; iNpc <= 142; ++iNpc)
	{
		m_YaHuangIDList.push_back(iNpc + 1000);
	}
// 	forv(g_pMainState->m_PetDataManager.m_PetList, k)
// 	{
// 		m_YaHuangIDList.push_back(k);
// 	}
}



void cFangWu::RemoveBB(cObj* yahuan)
{
	if (!yahuan)ERRBOX;
	int x, y;
	x = yahuan->GetX() / 20;
	y = (g_pMainState->m_Map.m_pMap->m_Height - yahuan->GetY()) / 20;
	for (int i = 0; i < m_List.size(); i++)
	{
		if (m_List[i].m_x == x &&m_List[i].m_y == y)
		{
			m_List.erase(m_List.begin() + i);
			CheckHuanJin();
			return;
		}
	}
}

void cFangWu::Save(ofstream& File)
{
	File << g_strEnter;
	File << m_GuiMo << g_strSpace;//规模 规模越大,能摆放的家具越多
	if (-1 == m_GuiMo)return;
	File << m_HuanJinDu << g_strSpace;//环境度
	m_DiBan.Save(File);//地板
	m_GuanJia.Save(File);//管家 
	File << m_List.size() << g_strSpace;
	for (int i = 0; i < m_List.size(); i++)
	{
		m_List[i].Save(File);
	}
	File << g_strSpace << "home" << g_strSpace;
	File << m_JiaJu.size() << g_strSpace;
	for (int i = 0; i < m_JiaJu.size(); i++)
	{
		m_JiaJu[i].Save(File);
	}

	File << m_YaHuangIDList.size() << g_strSpace;
	for (int i = 0; i < m_YaHuangIDList.size(); i++)
	{
		File << m_YaHuangIDList[i] << g_strSpace;
	}
	File << m_PreHuanJin << g_strSpace;
	File << g_strEnter;
}

void cFangWu::Load(ifstream& File)
{
	File >> m_GuiMo;//规模 规模越大,能摆放的家具越多
	if (-1 == m_GuiMo)return;
	File >> m_HuanJinDu;//环境度  决定睡眠质量
	m_DiBan.Load(File);//地板
	m_GuanJia.Load(File);//管家 
	int num;
	File >> num;
	m_List.clear();
	m_List.resize(num);
	for (int i = 0; i < m_List.size(); i++)
	{
		m_List[i].Load(File);
	}
	string tag;
	File >> tag;
	File >> num;
	m_JiaJu.resize(num);
	for (int i = 0; i < m_JiaJu.size(); i++)
	{
		m_JiaJu[i].Load(File);
	}
	File >> num;
	m_YaHuangIDList.clear();
	m_YaHuangIDList.resize(num);
	for (int i = 0; i < m_YaHuangIDList.size(); i++)
	{
		File >> m_YaHuangIDList[i];
	}
	File >> m_PreHuanJin;
}

void cFangWu::SetGuiMo(int num)
{
	if (num > 4)num = 4;
	if (m_GuiMo == num)return;
	m_GuiMo = num;
	switch (m_GuiMo)
	{
	case 0:m_GuanJia.Set(11, 9); break;
	case 1:m_GuanJia.Set(14, 14); break;
	case 2:m_GuanJia.Set(20, 21); break;
	case 3:m_GuanJia.Set(17, 13); break;
	case 4:m_GuanJia.Set(43, 12); break;
	}
	CheckHuanJin();
}

void cFangWu::Move(int x, int y, cObj* p)
{
	int xTarget = p->GetX() / 20;
	int yTarget = (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20;
	int targetID;
	switch (p->m_IndexType)
	{
	case INDEXTYEP_NPC:
		if (1)
		{
			cNpc* npc = (cNpc*)p->m_pIndex;
			targetID = npc->m_pNpcData->m_ModeId;
		}
		break;
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* pPet = (cPet*)p->m_pIndex;
			targetID = pPet->m_PetData.modeid;
		}
		break;
	default:
		return;
		break;
	}

	for (int i = 0; i < m_List.size(); i++)
	{
		if (xTarget == m_List[i].m_x)
			if (yTarget == m_List[i].m_y)
				if (targetID == m_List[i].m_modeid)
				{
			m_List[i].Set(x / 20, (g_pMainState->m_Map.m_pMap->m_Height - y) / 20);
			m_List[i].m_direction = GetDirection4(p->GetX(), p->GetY(), x, y);
			p->setNextTargetOnAstart(x, y);
			p->m_AstartPathIndex = -1;
			return;
				}
	}
	if (xTarget == m_GuanJia.m_x)
		if (yTarget == m_GuanJia.m_y)
			if (targetID == m_GuanJia.m_modeid)
			{
		m_GuanJia.Set(x / 20, (g_pMainState->m_Map.m_pMap->m_Height - y) / 20);
		m_GuanJia.m_direction = GetDirection4(p->GetX(), p->GetY(), x, y);
		p->setNextTargetOnAstart(x, y);
		p->m_AstartPathIndex = -1;
		return;
			}
}

void cFangWu::RemovePreJiaJu()
{
	if (g_pMainState->m_FangWu.m_JiaJu.size())
	{
		sJiaJu& item = g_pMainState->m_FangWu.m_JiaJu[g_pMainState->m_FangWu.m_JiaJu.size() - 1];
		m_HuanJinDu -= item.m_JiaJu.GetType() - 34;
		g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item.m_JiaJu);
		g_pMainState->m_Map.RemoveJiaJu(&item);
		g_pMainState->FindObj();
		g_pMainState->m_FangWu.m_JiaJu.pop_back();
		CheckHuanJin();
	}
	else g_pMainState->m_Tags.Add("现在没有家具");
}

void cFangWu::CheckHuanJin()
{
	int newhuanjin = GetHuanJin();
	if (newhuanjin == m_PreHuanJin)return;
// 	g_pCharacter->m_PcData.AddGrowing(-((m_PreHuanJin) / 25));
// 	g_pCharacter->m_PcData.AddGrowing((newhuanjin) / 25);
	m_PreHuanJin = newhuanjin;
}

void cFangWu::GetBB()
{
	int maxnum;
	switch (g_pMainState->m_FangWu.GetGuiMo())
	{
	case 1:maxnum = 4; break;
	case 2:maxnum = 8; break;
	case 3:maxnum = 12; break;
	case 4:maxnum = 16; break;
	default:
		if (1)
		{
			g_pMainState->FindObjByName("管家")->Talk("房屋规模太小,就不要买镇宅兽了");
			return;
		}
		break;
	}
	if (maxnum == g_pMainState->m_FangWu.m_List.size())
	{
		g_pMainState->FindObjByName("管家")->Talk("镇宅兽的已经够多了,就别再买了");
		return;
	}
	sNpc npc;
	g_pMainState->m_FangWu.Init();
	cObj* pobj = g_pHeroObj;
	int rate = m_YaHuangIDList.size();
// 	switch (g_pMainState->m_FangWu.GetGuiMo())
// 	{
// 	case 0:return;
// 	case 1:rate = 5; break;
// 	case 2:rate = 10; break;
// 	case 3:rate = 15; break;
// 	case 4:rate = 25; break;
// 	default:rate = g_pMainState->m_FangWu.m_YaHuangIDList.size(); break;
// 	}
	int petid = m_YaHuangIDList[rand() % rate];
	npc.Set("镇宅兽", g_pMainState->m_Map.m_MapName, petid,
		pobj->GetX() / 20, (g_pMainState->m_Map.m_pMap->m_Height - pobj->GetY()) / 20);
	g_pMainState->m_FangWu.m_List.push_back(npc);
	g_pMainState->m_Map.AddNpc(&npc, &g_pMainState->m_TaskNormal, "", 9);
	CheckHuanJin();
}



