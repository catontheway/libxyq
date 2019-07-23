#include "global.h"
#include <set>
#include <map>

#if ccc_date
static MyTest *s_myTestInstance = nullptr;
static bool  s_isEnemyAutoAtkMode;
struct sWid{ string desc; unsigned long id; };
vector<sWid> *s_wids = nullptr;
set<unsigned long> s_wdfSet;
static unsigned long *s_wdfs = nullptr;
static int s_indexOfWdf = -1;
map<unsigned long, unsigned long> s_tables;
map<unsigned long, int> s_ignores;
static int per加点front = 1;

MyTest* MyTest::getInstance()
{
	if (!s_myTestInstance)
	{
		s_myTestInstance = new MyTest();
		s_myTestInstance->putMenpaiSkills = { 0, 50, 80, 98, 131 };
		s_myTestInstance->putPetSkills = { 1, 3, 7, 15, 24, 26, 48, 52, 56, 58, 75, 82, 103 };
		s_wids = new vector<sWid>();
		s_wdfs = new unsigned long[32768];
	}
	return s_myTestInstance;
}


void MyTest::switch加点方案()
{
	if (per加点 == 10)
	{
		per加点 = (per加点front == 1) ? 100 : 1;
		per加点front = 10;
	}
	else if (per加点 == 100)
	{
		per加点 = 10;
		per加点front = 100;
	}
	else
	{
		per加点 = 10;
		per加点front = 1;
	}

	if (per加点 == 1)
	{
		g_pMainState->m_Tags.Add("普通加点");
	}
	else if (per加点 == 10)
	{
		g_pMainState->m_Tags.Add("快速加点");
	}
	else
	{
		g_pMainState->m_Tags.Add("超速加点");
	}
}


void MyTest::playerNormalize(int lv /*= 0*/)
{
	g_pMainState->m_pFightState->SuccessFight();
	return;
	g_pCharacter->m_PCData.LeveUp(-10, false, false);
	g_pCharacter->m_PCData.Followlv(lv, false, true, true);
}


void MyTest::useCard()
{
//	g_pCharacter->m_PCData.m_JinJieNum.m_PositionID = 1;
	cPCData *data = &g_pCharacter->m_PCData;
	if (data->m_Equip[2].GetNum())
	{
		g_pMainState->m_Tags.Add("请先脱下武器");
		return;
	}
	int &id = data->modeid;
	if (id == 1 || id == 3 || id == 5 || id == 7 || id == 9 || id == 12 || id == 14 || id == 15)
	{
		if (data->m_Equip[0].GetNum() || data->m_Equip[3].GetNum())
		{
			g_pMainState->m_Tags.Add("请先脱下头盔和衣服");
			return;
		}
	}
	if (++id > 14)
	{
		id = 0;
	}
	g_pCharacter->SetData(&g_pMainState->m_pCharacterDataList[id]);
//	g_pCharacter->m_PCData.FollowEuip();
//	g_pCharacter->m_PCData.FollowEquipAll();

//	g_pMainState->SetCharacter(g_pMainState->m_HeroID);
// 	if (g_pCharacter->m_PCData.m_FightPetID > -1)
// 	{
// 		int petid = g_pCharacter->m_PCData.m_FightPetID;
// 		g_pCharacter->m_PCData.m_FightPetID = -1;
// 		g_pMainState->SetFightPet(g_pMainState->m_HeroID, petid);
// 	}
	g_pMainState->m_PCHead.UpDateHead();

// 	if (rand() % 100 < 20)
// 	{
// 		g_pCharacter->UseCard(-1);
// 	}
// 	else
// 	{
// 		g_pCharacter->UseCard(s_changeModelID);
// 	}
// 
// 	if (++s_changeModelID > 162)
// 	{
// 		s_changeModelID = 27;
// 	}
// 	else if (s_changeModelID > 93)
// 	{
// 		s_changeModelID = 108;
// 	}

//	for (int i = 0; i < 4; i++)
	{
		auto &pc = g_pCharacter->m_PCData;
		int i = 0;
		sChangeColorData &rs = pc.m_RanSe.m_ranse[i];
//		rs.Read(File, mn.mode, sChangeColorData::ePc, i);
		rs.partnum = 4;
		DWORD color = g_pMainState->m_pCharacterDataList[pc.modeid].m_ColorID;
		if (color == 0)
		{
			color = 0x1657;
		}
		g_pMainState->m_ColorManage.Set(color);
		for (int k = 0; k < rs.partnum; ++k)
		{
			rs.SetColorChange(k, 0);
			g_pMainState->m_ColorManage.GetColorMatrix(
				k,
				rs.GetColorChange(k),
				rs.m_colormatrix[k]);
		}
	}

	g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->Reset();
	g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->Set(POS_STAND);
}

void MyTest::addMoney(int money)
{
	g_pCharacter->m_PCData.m_Money[0] += 1000000;
}

void MyTest::PKinit()
{
	s_isEnemyAutoAtkMode = isEnemyPKMode;
	isEnemyPKMode = true;
	return;
	g_pMainState->m_ZhiXian3.Init2();
}

struct sModeName{ int mode; string name; };
sModeName getModeFormMp(int mp)
{
	auto getName2 = [](const string &name1, const string &name2)
	{
		if (rand() % 100 < 50)
		{
			return name1;
		}
		return name2;
	};
	auto getMode2 = [](int mode1, int mode2)
	{
		if (rand() % 100 < 50)
		{
			return mode1;
		}
		return mode2;
	};

	auto getRand2 = [](int mode1, const string &name1, int mode2, const string &name2)
	{
		sModeName mn = { mode1, name1 };
		if (rand() % 100 < 50)
		{
			mn = { mode2, name2 };
		}
		return mn;
	};
	eMengPai e = (eMengPai)mp;
	sModeName mn = { 0, "猪队友" };
	switch (e)
	{
	case eMP_大唐官府:
		if (rand() % 100 < 50)
		{
			mn = { 1, "中国好少年" };
			break;
		}
		mn = { 0, getName2("桂小太郎", "酒伴何以久伴") };
		break;
	case eMP_化生寺:
		mn = { 1, getName2("情圣战天", "笑傲江湖757") };
		break;
	case eMP_女儿村:
		mn = { getMode2(2, 3), "微风筑城" };
		break;
	case eMP_方寸山:
		mn = getRand2(0, "待墨成碑", 12, "微风筑城");
		break;
	case eMP_狮驼岭:
		mn = getRand2(5, "是你的牛哥", 14, "狮驼大明王");
		break;
	case eMP_魔王寨:
		mn = { 4, "大笨猫" };
		break;
	case eMP_盘丝岭:
		mn = { getMode2(6, 7), "丫头" };
		break;
	case eMP_阴曹地府:
		mn = getRand2(4, "大笨猫", 14, "竟无言以对");
		break;
	case eMP_东海龙宫:
		mn = { 8, getName2("无聊的风车", "醉翁李") };
		break;
	case eMP_五庄观:
		mn = getRand2(8, "嘉喜", 9, "附魔帝君");
		break;
	case eMP_普陀山:
		mn = { getMode2(10, 11), "淡漠" };
		break;
	case eMP_天宫:
		mn = { 13, "小林子" };
		break;
	}
	return mn;
}

std::array<sAddPoint, 12> getPkAddpoint()
{
	ifstream File;
	File.open(g_strPKPath + "加点.txt");
	asert(bool(File), "无法读取擂台(加点.txt)");
	std::array<sAddPoint, 12> aps;
	string temp;
	forv(aps, i)
	{
		File >> aps[i].atk;
		File >> aps[i].def;
		File >> aps[i].hp;
		File >> aps[i].mp;
		File >> aps[i].spd;
		getline(File, temp);
	}
	File.close();
	return aps;
}

void learnPetSkill(cPCData &pc)
{
	int mp = pc.m_MengPaiID;
	for (auto eskill : { 0, 2, 7, 9, 17, 25, 29, 76, 81 })
	{
		pc.AddSkill(ePetSkill(eskill));
	}
	if (mp == eMP_东海龙宫 || mp == eMP_魔王寨)
	{
		pc.AddSkill(ePetSkill(47));
		pc.AddSkill(ePetSkill(59));
	}
	else if (mp == eMP_大唐官府 || mp == eMP_狮驼岭)
	{
		for (auto eskill : { 10, 23, 39, 75 })
		{
			pc.AddSkill(ePetSkill(eskill));
		}
	}
}

void MyTest::PK()
{
	for (int i = 0; i < 5; ++i)
	{
		if (!g_pMainState->m_FightList[i].isLive)
		{
			continue;
		}
		cObj *objMe = g_pMainState->m_FightList[i].m_pData;
		cPCData &pcMe = ((cCharacter*)objMe->m_pIndex)->m_PCData;
		int id = i + 10;
		g_pMainState->m_FightList[id].isLive = TRUE;
		sAddPoint addp = pcMe.m_AddPoint;
		if (i == g_pMainState->m_HeroID)
		{
			addp.Set(0, 3, 0, 1, 1);
			if (pcMe.m_MengPaiID == eMP_大唐官府 || pcMe.m_MengPaiID == eMP_狮驼岭)
			{
				addp.Set(4, 0, 0, 1, 0);
			}
			else if (pcMe.m_MengPaiID == eMP_东海龙宫 || pcMe.m_MengPaiID == eMP_魔王寨)
			{
				addp.Set(0, 0, 4, 1, 0);
			}
		}
		g_pMainState->m_FightList[id].m_pData->AutoPCData(
			pcMe.m_Name + "影子", pcMe.modeid, &addp, &pcMe.m_ZiZhi, (eMengPai)pcMe.m_MengPaiID);
		cObj *obj = g_pMainState->m_FightList[id].m_pData;
		cPCData &pc = ((cCharacter*)obj->m_pIndex)->m_PCData;
		pc.FollowlvAddPoint(pcMe.m_LV, false, true, true);

		for (int k = 0; k < pcMe.m_NumofBBSkill; ++k)
		{
			pc.AddSkill(ePetSkill(pcMe.m_pPetSkill[k]->m_Id));
		}
		learnPetSkill(pc);
		pc.m_AiLv = TRUE;
		pc.m_RanSe = pcMe.m_RanSe;
		for (int k = 0; k < pcMe.m_NumofBB; ++k)
		{
			cPetData petMe = pcMe.m_pPetDataList[k]->m_PetDataZZ;
			cPet* pet = new cPet();
			pet->AutoPetData(petMe.modeid, 0, &petMe.m_AddPoint, FALSE);
			pet->m_PetDataZZ.m_ZiZhi = petMe.m_ZiZhi;
			for (int k = 0; k < petMe.m_NumofBBSkill; ++k)
			{
				pet->m_PetDataZZ.AddSkill(ePetSkill(petMe.m_pPetSkill[k]->m_Id));
			}
			pet->SetData(g_pMainState->m_PetDataManager.GetPetData(petMe.modeid));
			pet->m_PetDataZZ.Followlv(petMe.m_LV, true, true, true);
			pet->m_PetDataZZ.m_Name = petMe.m_Name;
			pet->m_PetDataZZ.m_JinJieNum = petMe.m_JinJieNum;
			pc.GetPet(pet);

			if (0)
			{
				int i = 0;
				sChangeColorData &rs = pet->m_PetDataZZ.m_RanSe.m_ranse[i];
				//			rs.Read(File, mn.mode, sChangeColorData::ePc, i);
				rs.partnum = 4;
				DWORD color = g_pMainState->m_PetDataManager.GetPetData(pet->m_PetDataZZ.modeid)->m_PartList[i].m_ColorID;
				if (color == 0)
				{
					color = 0x1657;
				}
				g_pMainState->m_ColorManage.Set(color);
				for (int k = 0; k < rs.partnum; ++k)
				{
					rs.SetColorChange(k, rand() % 4);
					g_pMainState->m_ColorManage.GetColorMatrix(
						k,
						rs.GetColorChange(k),
						rs.m_colormatrix[k]);
				}
			}
		}
		if (pc.m_NumofBB > 0)
		{
			g_pMainState->SetFightPet(id, pcMe.m_FightPetID);
			g_pMainState->m_FightList[id + 5].m_pData->Set(POS_FIGHT_STAND);
		}

		pc.m_Controler.Set(FALSE, FALSE, FALSE, TRUE, FALSE);
	}
	g_pMainState->m_InterfaceTeam.SetFormation(g_pMainState->m_InterfaceTeam.m_eOurFormation, true);
}



void MyTest::PK(int state)
{
	int format = (state >> 24) - 1;
	state %= (1 << 24);
	vector<int>mps;
	int num = state % 16;
	mps.resize(state % 16);
	forr(mps, i)
	{
		mps[i] = (state >> ((i + 1) * 4));
		state %= (1 << ((i + 1) * 4));
	}
	auto aps = getPkAddpoint();
	for (int i = 0; i < num; ++i)
	{
		int id = i + 10;
		int mp = mps[i];
		int bbNum = 8;
		sAddPoint ap;
		if (mp >= 0 && mp < 12)
		{
			ap = aps[mp];
		}
		auto mn = getModeFormMp(mp);
		sZiZhi zz;
		int grow = 3;
		if (mp == eMP_东海龙宫)
		{
			grow = 2;
		}
		else if (mp == eMP_魔王寨 || mp == eMP_方寸山 || mp == eMP_化生寺 || mp == eMP_普陀山)
		{
			grow = 4;
		}
		zz.Set(100, 100, 100, 100, 100, 100, grow);
		g_pMainState->m_FightList[id].isLive = TRUE;
		g_pMainState->m_FightList[id].m_pData->AutoPCData(mn.name, mn.mode, &ap, &zz, (eMengPai)mp);
		cObj *obj = g_pMainState->m_FightList[id].m_pData;
		cPCData &pc = ((cCharacter*)obj->m_pIndex)->m_PCData;
		pc.FollowlvAddPoint(g_pCharacter->m_PCData.m_LV, false, true, true);
		learnPetSkill(pc);
		pc.m_AiLv = TRUE;
//		pc.FollowShoe();
//		for (int i = 0; i < 4; i++)
		if (isClassical)
		{
			int i = 0;
			sChangeColorData &rs = pc.m_RanSe.m_ranse[i];
			//			rs.Read(File, mn.mode, sChangeColorData::ePc, i);
			rs.partnum = 4;
			DWORD color = g_pMainState->m_pCharacterDataList[mn.mode].m_ColorID;
			if (color == 0)
			{
				color = 0x1657;
			}
			g_pMainState->m_ColorManage.Set(color);
			for (int k = 0; k < rs.partnum; ++k)
			{
				rs.SetColorChange(k, (k <= 2) ? (rand() % 8) : 0);
				g_pMainState->m_ColorManage.GetColorMatrix(
					k,
					rs.GetColorChange(k),
					rs.m_colormatrix[k]);
			}
		}
		for (int k = 0; k < bbNum; ++k)
		{
			bool isAtk = rand() % 100 < 35;
			sShangPinPet spet;
			spet.LoadEasy(isAtk ? 0 : 20);
			int pmode;
			while (true)
			{
				pmode = rand() % 162;
				if (pmode >= 114 && pmode <= 148)
				{
					continue;
				}
				int lv = g_pMainState->m_PetDataManager.m_PetList[pmode].m_LVLimit;
				if (lv > pc.m_LV)
				{
					continue;
				}
				if (lv > 0 && lv < pc.m_LV - 80)
				{
					continue;
				}
				if (pc.m_LV < 45 && lv == 0)
				{
					continue;
				}
				if (pc.m_LV >= 45 && lv >= 5 && lv < 45)
				{
					continue;
				}
				if (pc.m_LV >= 45 && lv == 0 && rand() % 100 < 80)
				{
					continue;
				}
				break;
			}

			cPet* pet = new cPet();
			pet->m_PetDataZZ.m_ZiZhi.Set(1600, 1600, 3000, 8000, 1600, 1600, 144);
			pet->m_PetDataZZ.m_ZiZhi.Set(pet->m_PetDataZZ.m_ZiZhi, 0, 0);
			for (auto skill : spet.m_skillid)
			{
				if (skill == ePetSkill::ePS_月光)
				{
					continue;
				}
				pet->m_PetDataZZ.AddSkill(ePetSkill(skill));
			}
			if (isAtk)
			{
				if (rand() % 100 < 35)
				{
					pet->m_PetDataZZ.AddSkill((rand() % 100 < 62) ? ePetSkill::ePS_力劈华山 : ePetSkill::ePS_善恶有报);
				}
			}
			else
			{
				pet->m_PetDataZZ.AddSkill(ePetSkill(85 + (rand() % 4) * 2));
			}
			pet->SetData(g_pMainState->m_PetDataManager.GetPetData(pmode));
			if (isAtk)
			{
				if (rand() % 100 < 50)
				{
					pet->m_PetDataZZ.m_AddPoint.Set(4, 0, 0, 1, 0);
				}
				else
				{
					pet->m_PetDataZZ.m_AddPoint.Set(3, 1, 0, 1, 0);
				}
			}
			else
			{
				if (rand() % 100 < 50)
				{
					pet->m_PetDataZZ.m_AddPoint.Set(0, 0, 4, 1, 0);
				}
				else
				{
					pet->m_PetDataZZ.m_AddPoint.Set(0, 1, 3, 1, 0);
				}
			}
			int lv = pc.m_LV + MyTest::getInstance()->lvGapFromRoleAndBaby;
			if (lv > MyTest::getInstance()->maxBabyLv)
			{
				lv = MyTest::getInstance()->maxBabyLv;
			}
			pet->m_PetDataZZ.Followlv(lv, true, true, true);
			pet->m_PetDataZZ.m_Name = g_pMainState->m_PetDataManager.GetPetData(pmode)->m_Name;
			pet->m_PetDataZZ.SetJinJie(rand() % 3 + 1);
			pc.GetPet(pet);

			if (0)
			{
				int i = 0;
				sChangeColorData &rs = pet->m_PetDataZZ.m_RanSe.m_ranse[i];
	//			rs.Read(File, mn.mode, sChangeColorData::ePc, i);
				rs.partnum = 4;
				DWORD color = g_pMainState->m_PetDataManager.GetPetData(pet->m_PetDataZZ.modeid)->m_PartList[i].m_ColorID;
				if (color == 0)
				{
					color = 0x1657;
				}
				g_pMainState->m_ColorManage.Set(color);
				for (int k = 0; k < rs.partnum; ++k)
				{
					rs.SetColorChange(k, rand() % 4);
					g_pMainState->m_ColorManage.GetColorMatrix(
						k,
						rs.GetColorChange(k),
						rs.m_colormatrix[k]);
				}
			}

		}
		if (pc.m_NumofBB > 0)
		{
			g_pMainState->SetFightPet(id, 0);
			g_pMainState->m_FightList[id + 5].m_pData->Set(POS_FIGHT_STAND);
		}

		pc.m_Controler.Set(FALSE, FALSE, FALSE, TRUE, FALSE);
	}
	g_pMainState->m_InterfaceTeam.SetFormation((eFormation)format, true);
}



void MyTest::PKover()
{
	isEnemyPKMode = s_isEnemyAutoAtkMode;
	for (int i = 10; i < 15; i++)
	{
		if (g_pMainState->m_FightList[i].isLive)
		{
			g_pMainState->SetFightPet(i, -1);
		}
	}
}

struct sPkTeam { string name; vector<int>mps; int format = 0; };
void MyTest::PKNpc()
{
	ifstream file;
	vector<sPkTeam> teams;
	auto readTeam = [&](int n)
	{
		file.open(g_strPKPath + toString("%d人队.txt", n));
		asert(bool(file), "无法读取擂台(%d人队.txt)", n);
		sPkTeam team;
		team.mps.resize(n);
		int num;
		file >> num;
		string strTemp;
		getline(file, strTemp);
		for (int i = 0; i < num; ++i)
		{
			file >> team.name;
			asert(team.name.size(), "擂台(%d人队.txt)队名错误");
			for (int k = 0; k < n; ++k)
			{
				file >> team.mps[k];
				asert(team.mps[k] >= 0 && team.mps[k] <= 11, "擂台(%d人队.txt)门派编号错误");
			}
			if (n == 5)
			{
				file >> team.format;
				asert(team.format >= 0 && team.format <= 10, "擂台(%d人队.txt)阵型编号错误");
			}
			teams.push_back(team);
			getline(file, strTemp);
		}
		file.close();
	};

	auto readTeamRand = [&]()
	{
		sPkTeam team;
		int n = 2 + rand() % 4;
		team.mps.resize(n);
		team.name = "酱油";
		if (n == 3)
		{
			team.name = "杂牌";
		}
		else if (n == 4)
		{
			team.name = "混搭";
		}
		else if (n == 5)
		{
			team.name = "随机";
		}

		team.name += "队";
		for (int k = 0; k < n; ++k)
		{
			team.mps[k] = rand() % 12;
		}
		if (n == 5)
		{
			team.format = 1 + rand() % 10;
		}
		teams.push_back(team);
	};

	auto getStageFormMp = [&](const sPkTeam &t)
	{
		unsigned int n = t.mps.size();
		forv(t.mps, i)
		{
			n += (t.mps[i] << (4 * (i + 1)));
		}
		return n += ((t.format + 1) << 24);
	};

	for (int i = 1; i <= 5; ++i)
	{
		readTeam(i);
	}
	for (int i = 0; i < 50; ++i)
	{
		readTeamRand();
	}
	while (teams.size() >= 60)
	{
		teams.pop_back();
	}

	cMyMap *mymap = &g_pMainState->m_Map;
	sNpc npc;
	for (const auto &t : teams)
	{
		if (mymap->m_numberOfNpc >= 59)
		{
			return;
		}

		mymap->m_pNpc[mymap->m_numberOfNpc]->m_ScriptOneType = 1010;
		mymap->m_pNpc[mymap->m_numberOfNpc]->m_ScriptOneId = getStageFormMp(t);
		int typelist[2];
		GetWeaponType(t.mps.front(), typelist[0], typelist[1]);
		int weapontype = typelist[rand() % 2];
		int	weaponid = g_pMainState->m_ItemManage.GetIDByLv(weapontype, g_pCharacter->m_PCData.m_LV);
		npc.Set(t.name, mymap->m_MapName, t.mps.front() + 2000, 0, 0);
		mymap->AutoGetPos(npc.m_x, npc.m_y, mymap->m_MapName);
		npc.weaponid = weaponid;
		npc.weapontype = weapontype;
		mymap->AddNpc(&npc, nullptr, "单");
	}
}


void MyTest::暗雷场景马上战斗()
{
	
	g_pMainState->m_TaskNormal.Process(1);
}

bool MyTest::isInBattle()
{
	return g_StateType == STATE_FIGHT;
}

void MyTest::set仙店(int lv)
{
	g_pMainState->m_GlobalButton[3] = lv;
}

bool MyTest::isAtkMode(int id)
{
	if (id >= 0 && id < 10)
	{
		return isAutoAtkMode;
	}
	
	cPetData *data = nullptr;
	g_pMainState->m_FightList[id].m_pData->GetDateP(data);
	if (!data)
	{
		asert(false, "AI战斗编号错误");
	}

	int k = data->m_XiuLian.GetAtk();
	if (isEnemyPKMode)
	{
		k = 100;
	}
	else
	{
		int i = data->m_XiuLian.GetMag();
		if (i > k)
		{
			k = i;
		}
		k = 20 + k * 3;
	}
	if (k > 95)
	{
		k = 95;
	}
	return  rand() % 100 > k;
	
	
}

bool MyTest::isSpecialOrZZ(int zz)
{
	return zz < 50;
}

int MyTest::getBabyLv()
{
	return g_pCharacter->m_PCData.m_LV + lvGapFromRoleAndBaby;
}

int MyTest::getDesbinOf头盔(int e, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10;
	if (e == eMP_大唐官府 || e == eMP_狮驼岭)
	{
		++dusbin;
	}
	return dusbin;
}

int MyTest::getDesbinOf项链(int e, int teji /* = 0 */)
{
	return (teji + 1) * 10;
}

int MyTest::getDesbinOf武器(int e, int teji /* = 0 */)
{
	return (teji + 1) * 10;
}

int MyTest::getDesbinOf铠甲(int e, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10;
	if (e == eMP_东海龙宫 || e == eMP_魔王寨)
	{
		++dusbin;
	}
	else if (e == eMP_无 || e == eMP_普陀山 || e == eMP_阴曹地府 || e == eMP_盘丝岭 || e == eMP_狮驼岭)
	{
		dusbin += 2;
	}
	return dusbin;
}

int MyTest::getDesbinOf腰带(int e, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10 + 1;
	if (e == eMP_东海龙宫 || e == eMP_魔王寨 || e == eMP_无)
	{
		--dusbin;
	}
	return dusbin;
}

int MyTest::getDesbinOf鞋子(int e, bool isAtk /* = false */, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10;
	if (e == eMP_大唐官府 || e == eMP_狮驼岭 || (isAtk && (e == eMP_五庄观 || e == eMP_女儿村 || e == eMP_阴曹地府 || e == eMP_盘丝岭)))
	{
		dusbin += 1;
	}
	else if (e == eMP_东海龙宫 || e == eMP_魔王寨 || (isAtk && (e == eMP_化生寺 || e == eMP_方寸山 || eMP_天宫)))
	{
		dusbin += 2;
	}
// 	else if (e == eMP_化生寺 || e == eMP_普陀山 || e == eMP_阴曹地府 || e == eMP_无)
// 	{
// 		// 气血
// 		dusbin += 3;
// 	}
	return dusbin;
}

void MyTest::initControl()
{
//	g_pMainState->m_GlobalButton[0] = 99;
	g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(isControl);
}

void MyTest::init()
{
	if (0)
	{
		saveWdf();
		saveMyWdf();
	}
	g_pMainState->m_GlobalButton[0] = 99;

	g_pMainState->m_GlobalButton[6] = 0;
	g_pMainState->m_GlobalButton[5] = 0;
	g_pMainState->m_GlobalButton[4] = 0;

	g_pMainState->LoadCharacterData2(g_pMainState->m_HeroID, "队长");
	g_pMainState->SetCharacter(g_pMainState->m_HeroID);
	g_pCharacter->m_PCData.m_Controler.Set(0, 0);

	cPet* Pet4 = 0;
	sAddPoint p;
	p.Set(0, 0, 4, 1, 0);
	g_pMainState->MakeAPet(Pet4, e火星人, 100, 10, p);
	g_pMainState->GivePcAPet(g_pMainState->m_HeroID, Pet4);
	Pet4 = nullptr;
	p.Set(4, 0, 0, 1, 0);
	g_pMainState->MakeAPet(Pet4, e转轮王, 100, 10, p);
	g_pMainState->GivePcAPet(g_pMainState->m_HeroID, Pet4);
	Pet4 = nullptr;
// 	g_pMainState->MakeAPet野怪(Pet4, e转轮王, 100, 10, p);
// 	g_pMainState->GivePcAPet(g_pMainState->m_HeroID, Pet4);
// 	Pet4 = nullptr;
	g_pMainState->MakeAPet(Pet4, e知了王, 100, 10, p);
	g_pMainState->GivePcAPet(g_pMainState->m_HeroID, Pet4);
	



	for (int i = 42; i <= 51; ++i)
	{
		if (0 == (g_pMainState->m_GlobalButton[200] & (1 << (i - 42))))
		{
			g_pMainState->m_GlobalButton[200] |= (1 << (i - 42));
		}
	}

#if 0
	auto addAndPaopao = [&](const string &name)
	{
		g_pMainState->m_Friend.AddFriend(name);
		g_pMainState->m_ZhuXian.AutoGetPet(name/*, 0*/);
	};

	auto addAndPaopaos = [&](const vector<string> &names)
	{
		for (const auto &name : names)
		{
			addAndPaopao(name);
		}
	};


	int locklv = 5;
	int pro = 0;
	addAndPaopaos({ "篮子", "神天兵", "虎子" });

	auto expOnce = [&]()
	{
		g_pMainState->m_GlobalButton[14] += 200;
		g_pMainState->m_GlobalButton[15] += 200;
	};

	if (juQing > 0) // 玄奘前
	{
		expOnce();
		addAndPaopaos({ "燕子", "怀念", "敖白", "紫菜"});
		locklv = 25;
		pro = 1;
	}
	if (juQing > 1) // 琉璃前
	{
		addAndPaopao("清风");
		g_pMainState->m_Friend.AddFriend("傻妞");
		sShangPinPet sppet;
		sppet.Set(e超级大熊猫, 0, 100, TRUE);
		g_pMainState->m_ZhuXian.GetPet("傻妞", &sppet, 100);
		expOnce();
		locklv = 55;
		pro = 2;
	}
	if (juQing > 2)// 西凉前
	{
		addAndPaopao("小蛮");
		locklv = 65;
		pro = 8;
	}
	if (juQing > 3) // 小白龙前
	{
		locklv = 75;
		pro = 3;
	}
	if (juQing > 4) // 天蓬前
	{
		expOnce();
		sShangPinPet sppet;
		sAddPoint addpoint;
		addpoint.Set(4, 0, 0, 1, 0);
		sppet.Set(e超级神兔, &addpoint, 100, TRUE);
		g_pMainState->m_ZhuXian.GetPet("小蛮", &sppet, 100);

		g_pMainState->m_Friend.AddFriend("四季");

		addpoint.Set(0, 0, 4, 1, 0);
		sppet.Set(e超级海豚, &addpoint, 100, TRUE);
		g_pMainState->m_ZhuXian.GetPet("四季", &sppet, 100);
		locklv = 105;
		pro = 4;
	}
	if (juQing > 5) // 猴哥前
	{
		g_pMainState->m_Friend.AddFriend("冷涯傲雪");
		g_pMainState->m_ZhuXian.AutoGetPet("冷涯傲雪"/*, 2*/);

		g_pMainState->m_Friend.AddFriend("小胖牛");
		g_pMainState->m_ZhuXian.AutoGetPet("小胖牛"/*, 3*/);

//		g_pMainState->m_ZhuXian.AutoGetPet("紫菜", 4, 5);
		locklv = 125;
		pro = 5;
	}
	if (juQing > 6) // 白骨精前
	{
		expOnce();
		locklv = 135;
		pro = 6;
	}
	if (juQing > 7) // 芭蕉扇前
	{
		expOnce();
		pro = 7;
	}
	if (juQing > 8) // 门派蚩尤前
	{
		expOnce();
		locklv = 145;
	}
	if (juQing > 9) // 终章前
	{
		expOnce();
		locklv = 155;
		g_pMainState->m_Friend.AddFriend("羽灵神");
		pro = 9;
	}
	if (juQing > 10) // boss前
	{
		expOnce();
		g_pMainState->m_Friend.AddFriend("杀破狼");
		for (const auto &flist : g_pMainState->m_Friend.m_FriendList)
		{
			const string &name = flist.m_Name;
			g_pMainState->m_ZhuXian.AutoGetPet(name, rand() % 20 + 20);
			g_pMainState->m_ZhuXian.AutoGetPet(name, rand() % 20 + 20);
			for (int i = 0; i < 5; ++i)
			{
				g_pMainState->m_ZhuXian.AutoGetPet(name, rand() % 20);
			}
		}
		locklv = 175;
	}
	INT64 exp = 0;
	for (int i = MyTest::getInstance()->minRoleLv;
		i < locklv - MyTest::getInstance()->perLvup * 2;
		i += ((i % 10 == 5) ? 4 : 6))
	{
		exp += GetCharacterExp(i);
	}
#endif

	g_pCharacter->m_PCData.m_BangPaiID = 0;
	g_pCharacter->m_PCData.m_MengPaiID = -1;
	g_pCharacter->m_PCData.LeveUp(MyTest::getInstance()->minRoleLv, false, true);
//	g_pCharacter->m_PCData.FollowXiulian();
//	g_pCharacter->m_PCData.FullFuzhuBut暗器();
//	g_pCharacter->m_PCData.FollowSkill();
	g_pCharacter->m_PCData.FollowEuip();
//	g_pCharacter->m_PCData.FollowItem(true);
	g_pCharacter->m_PCData.FillHPMP();
	g_pHeroObj->Reset();
	g_pHeroObj->Set(POS_STAND);
	g_pCharacter->m_PCData.m_Money[0] = 0xffff;
	g_pCharacter->m_PCData.m_Money[1] = (1 << 24);
//	g_pCharacter->m_PCData.EXP = exp;
	g_pMainState->m_Map.LoadMap(19, 74, "桃源村", FALSE);
	g_pMainState->m_GlobalButton[2] = MyTest::getInstance()->maxRoleLv; // (locklv);
//	g_pMainState->m_Friend.Invite("篮子");
	for (const auto& fr : friendNames)
	{
		g_pMainState->m_Friend.AddFriend(fr);
	}

//  	g_pMainState->m_Friend.AddFriend("敖白");
//  	g_pMainState->m_ZhuXian.AutoGetPet("敖白");
// 	g_pCharacter->m_PCData.LeveUp(MyTest::getInstance()->maxRoleLv, false, true);
//  	g_pMainState->m_ZhuXian.SetChapter(4);
//  	g_pMainState->m_ZhuXian.Process4(10);
//    	return;

#if 0
	if (pro == 0)
	{
		g_pMainState->m_ZhuXian.SetChapter(0);
		g_pMainState->m_ZhuXian.Process0(10086);
	}
	else if (pro == 1)
	{
		g_pMainState->m_ZhuXian.SetChapter(1);
		g_pMainState->m_ZhuXian.Process1(0);
	}
	else if (pro == 2)
	{
		g_pMainState->m_ZhuXian.Process2(0);
	}
	else if (pro == 3)
	{
		g_pMainState->m_ZhuXian.Process3(0);
	}
	else if (pro == 4)
	{
		g_pMainState->m_ZhuXian.Process4(0);
	}
	else if (pro == 5)
	{
		g_pMainState->m_ZhuXian.Process5(0);
	}
	else if (pro == 6)
	{
		g_pMainState->m_ZhuXian.Process6(0);
	}
	else if (pro == 7)
	{
		if (juQing > 8)
		{
			g_pMainState->m_ZhuXian.SetChapter(7);
			g_pMainState->m_ZhuXian.Process7(26);
		}
		else
		{
			g_pMainState->m_ZhuXian.Process7(0);
		}
		
	}
	else if (pro == 8)
	{
		g_pMainState->m_ZhuXian.Process8(0);
	}
	else if (pro == 9)
	{
		if (juQing > 10)
		{
			g_pMainState->m_ZhuXian.SetChapter(9);
			g_pMainState->m_ZhuXian.Process9(6);
		}
		else
		{
			g_pMainState->m_ZhuXian.Process9(0);
		}
	}
#endif

// 	g_pMainState->m_Tags.Add("更多彩蛋(说明书.txt)", INT_MAX);
// 	g_pMainState->m_Tags.Add("更多操作(png说明图)", INT_MAX);


	if (0)
	{
#if 0
		ofstream fileOut;
		set<unsigned long> maps;
		set<unsigned long> map2s;
		set<int> mapIDs;
		for (auto name : mapNames)
		{
			g_pMainState->m_Map.RemoveAllNpc();
			g_pMainState->m_Map.LoadMap(0, 0, name.c_str());
			maps.insert(g_pMainState->m_Map.m_SmallMap.m_NowID);
			mapIDs.insert(g_pMainState->m_Map.m_MapNumber);
			for (const auto &jz : g_pMainState->m_Map.m_JianZhuID)
			{
				map2s.insert(jz);
			}
		}

		CWFile m_File;
		ifstream *fileWdf = nullptr;
		
		int i = -1;
		for (const auto &e : maps)
		{
			bool b = m_File.GetFileP(e, fileWdf, [&](unsigned char *data, int size)
			{
				fileOut.open(toString("C:/Users/wolf/Desktop/mapwas/%04d-%x-0.was", ++i, e), ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入地图was失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入地图was遗漏");
		}
//		return;
		i = -1;
		for (const auto &e : map2s)
		{
			bool b = m_File.GetFileP(e, fileWdf, [&](unsigned char *data, int size)
			{
				fileOut.open(toString("C:/Users/wolf/Desktop/map2was/%04d-%x-0.was", ++i, e), ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入建筑was失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入建筑was遗漏");
		}

		fileOut.open("C:/Users/wolf/Desktop/mapIDs.txt");
		if (!fileOut)
		{
			fileOut.close();
			asert(false, "写入建筑was失败");
			return;
		}
		fileOut << mapIDs.size() << "\n";
		for (const auto &e : mapIDs)
		{
			fileOut << e << "\n";
		}
		fileOut.close();
#endif
	}
}

void MyTest::pushWdf(const string &desc, unsigned long id)
{
	if (juQing != 10086 && juQing != 10087)
	{
		return;
	}
	s_wdfs[++s_indexOfWdf] = id;
	asert(s_indexOfWdf < 32768, "wdf索引溢出");
	return;
	s_wids->push_back({ desc, id });
}

void MyTest::pushWdf2(const string &desc, unsigned long id)
{
	pushWdf(desc, id);
}

void MyTest::saveWdf()
{
	if (juQing != 10086 && juQing != 10087)
	{
		return;
	}
	s_wdfSet.clear();
	if (juQing == 10086)
	{
		pushWdf3();
	}
	for (int i = 0; i <= s_indexOfWdf; ++i)
	{
		if (s_wdfs[i] > 552)
		{
			s_wdfSet.insert(s_wdfs[i]);
		}
	}
	string path = g_strExpandPath;
	if (juQing == 10086)
	{
		path += "全部wdf.txt";
	}
	else if (juQing == 10087)
	{
		path += "差异wdf.txt";
	}
	ofstream file(path);
	asert((bool)file, "写入%s失败", path.c_str());
	file << s_wdfSet.size() << "\n";
	for (const auto &wdf : s_wdfSet)
	{
		file << toString("%lu", wdf) << "\n";
	}
	file.close();
	ccc_msgbox("", "写入%s完毕", path.c_str());
	return;

	file << s_wids->size() << "\n";
	for (const auto &wdf : *s_wids)
	{
		file << wdf.id << "      "<< wdf.desc << "\n";
	}

	file << (s_indexOfWdf + 1) << "\n";
	for (int i = 0; i <= s_indexOfWdf; ++i)
	{
		file << s_wdfs[i] << "\n";
	}
	delete[] s_wdfs;

	file.close();
	ccc_msgbox("", "写入wdf列表成功");
}


void MyTest::pushWdf3()
{
	s_wdfSet.insert(0xCF1D211E);
	s_wdfSet.insert(0x535C1994);
	s_wdfSet.insert(0x1733E33B);
	s_wdfSet.insert(0x1FBC5273);
	s_wdfSet.insert(0xB48A9B3D);
	s_wdfSet.insert(0x5A055B13);
	s_wdfSet.insert(0xB87E0F0C);
	s_wdfSet.insert(0xB352AE45);
	s_wdfSet.insert(0xC5750B15);
	s_wdfSet.insert(0xFC03AFF1);
	s_wdfSet.insert(0x0D98AC0A);
	s_wdfSet.insert(0x9B3AF4E5);
	s_wdfSet.insert(0xA16FD45C);
	s_wdfSet.insert(0x02EF9247);
	s_wdfSet.insert(0xCAB0B8B4);//0x9874B9B8
	s_wdfSet.insert(0xA15292B2);//0x8F499AA3
	s_wdfSet.insert(2119033822);//0x216FE0F8
	s_wdfSet.insert(0x3D1FA249);
	s_wdfSet.insert(250440769);//0xD5D51AD0  410697672
	s_wdfSet.insert(240383749);// 240383749 //0x78DDA320
	s_wdfSet.insert(2088395993);//0xD5DF5927
	s_wdfSet.insert(0x5116F7DF);//0x414977BD
	s_wdfSet.insert(222208523);//0x3B9F2278
	s_wdfSet.insert(0x1DF7B97D);//  574791040);
	s_wdfSet.insert(0xF151309F);// 788193189);
	s_wdfSet.insert(0x436592D8);
	s_wdfSet.insert(0x08E2D199);
	s_wdfSet.insert(0xC013B53B);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xC47885C6);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xB15C5678);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x1A2DEAB9);//1259967470);
	s_wdfSet.insert(0x8F43CE91);//0x51E340B6);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xDE3F48B7);
	s_wdfSet.insert(0xAC307575);//走
	s_wdfSet.insert(0x9DF6DEBC); //白天	
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x2EFADFA5);
	s_wdfSet.insert(0x73D983B7);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xE87F26E1);
	s_wdfSet.insert(0x08E2D199);
	s_wdfSet.insert(0xC013B53B);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xE3AEF018);
	s_wdfSet.insert(0x2FD95E30);
	s_wdfSet.insert(0x69823EE5);
	s_wdfSet.insert(0x0A8B7D87);
	s_wdfSet.insert(0x32F119A5);
	s_wdfSet.insert(0x4226BD41);
	s_wdfSet.insert(0x1D0C0B23);
	s_wdfSet.insert(0xFBEC073F);//0xCC7BC6C6);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xB05126E8);
	s_wdfSet.insert(0x26066130);
	s_wdfSet.insert(0x354CD2EB);
	s_wdfSet.insert(0xF792E03C);
	s_wdfSet.insert(0x146BB550);
	s_wdfSet.insert(0xA393A808);
	s_wdfSet.insert(0x907E024C);
	s_wdfSet.insert(0xCB50AB1D);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x9ED74AA6);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0xDD1E6B63);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x2BD1DEF7);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xD6A27FFA);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x86785735);
	s_wdfSet.insert(0x541FA615);
	s_wdfSet.insert(0x420FF401);
	s_wdfSet.insert(0xE3AEF018);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0x536A7E15);
	s_wdfSet.insert(0x694F39D1);
	s_wdfSet.insert(0x694F39D1);
	s_wdfSet.insert(0xB05126E8);
	s_wdfSet.insert(0x26066130);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xE3AEF018);
	s_wdfSet.insert(0xABB7D0DB);
	s_wdfSet.insert(0x361FA820);
	s_wdfSet.insert(0xC0A66903);
	s_wdfSet.insert(0xD1D11294);
	s_wdfSet.insert(0xAA7DEB05);
	s_wdfSet.insert(0x21274A87);
	s_wdfSet.insert(0x9C4978D);
	s_wdfSet.insert(0xC9E2F072);
	s_wdfSet.insert(0x2ACB36B2);
	s_wdfSet.insert(0xC26BF189);
	s_wdfSet.insert(0x1AA170AE);
	s_wdfSet.insert(0x7921D3A3);
	s_wdfSet.insert(0xEA7CAB84);
	s_wdfSet.insert(0x203CE1F7);
	s_wdfSet.insert(0x2178F38B);
	s_wdfSet.insert(0x008C2611);
	s_wdfSet.insert(0xAAD44583);
	s_wdfSet.insert(0xCE4D3C2D);
	s_wdfSet.insert(0x7B3C08E4);
	s_wdfSet.insert(0xBAF8009F);
	s_wdfSet.insert(0x2E8758EE);
	s_wdfSet.insert(0x354CD2EB);
	s_wdfSet.insert(0x146BB550);
	s_wdfSet.insert(0x516749F4);
	s_wdfSet.insert(0xC5C5FE46);//长寿
	s_wdfSet.insert(0x3D561594);//建邺
	s_wdfSet.insert(0xDB61AD29);//长安
	s_wdfSet.insert(0x6BD8F1C8);//AL
	s_wdfSet.insert(0x29622DDB);//西凉女国
	s_wdfSet.insert(0x491E6B4C);//宝象
	s_wdfSet.insert(0x549B2B83);//朱紫国
	s_wdfSet.insert(0xA393A808);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x9B1DB10D);
	s_wdfSet.insert(0x9B1DB10D);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x63CC8A23);
	s_wdfSet.insert(0x00D13BBF);
	s_wdfSet.insert(0x00D13BBF);//0x18C30C41);
	s_wdfSet.insert(0x323E2BCD);
	s_wdfSet.insert(0xA7CE2F61);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0x65C5B7EE);
	s_wdfSet.insert(0xF9858C95);
	s_wdfSet.insert(0x1B1DCE56);
	s_wdfSet.insert(0x43700E25);
	s_wdfSet.insert(0xF9ADC3DA);
	s_wdfSet.insert(0xA0120D38);
	s_wdfSet.insert(0x32BE710D);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x8072710D);
	s_wdfSet.insert(0x0E43E0DF);
	s_wdfSet.insert(0xF5B8E062);
	s_wdfSet.insert(0xC540D7A7);
	s_wdfSet.insert(0x4B82870A);// 0x4B82870A; // 0x014FF746);// 0xEDCED445);// 0x436592D8);// 0xAB7B8559);
	s_wdfSet.insert(0x93E77F54);
	s_wdfSet.insert(0x0B19A5DC);
	s_wdfSet.insert(0x26E89B1F);
	s_wdfSet.insert(0xE9EC7A25);
	s_wdfSet.insert(0x11A18FBF);
	s_wdfSet.insert(0x13659C02);
	s_wdfSet.insert(0xA0B51368);
	s_wdfSet.insert(0xEDEEF9AF);
	s_wdfSet.insert(0xCCB7A7C3);
	s_wdfSet.insert(0x6B27F57F);
	s_wdfSet.insert(0x6BF13E64);
	s_wdfSet.insert(0xA9BC7D93);
	s_wdfSet.insert(0x71DF41E1);
	s_wdfSet.insert(0xE0C66A6F);
	s_wdfSet.insert(0x9C992236);
	s_wdfSet.insert(0xFF1D4A14);
	s_wdfSet.insert(0x6EA52AE1);
	s_wdfSet.insert(0x47FE6497);
	s_wdfSet.insert(0x6AB41A9A);
	s_wdfSet.insert(0x991B588D);
	s_wdfSet.insert(0xAD1DC28A);
	s_wdfSet.insert(0x150B5122);
	s_wdfSet.insert(0x301A4FE7);
	s_wdfSet.insert(0xEC9EBCA8);
	s_wdfSet.insert(0xBF78C1EF);
	s_wdfSet.insert(0x5B96A2DD);
	s_wdfSet.insert(0xCA26DE5D);
	s_wdfSet.insert(0xEA60ABA4);
	s_wdfSet.insert(0x0D906C8D);
	s_wdfSet.insert(0x63566DA9);
	s_wdfSet.insert(0x637B3C48);
	s_wdfSet.insert(0x6A154DDE);
	s_wdfSet.insert(0x689EB676);
	s_wdfSet.insert(0xE329AD6A);
	s_wdfSet.insert(0x048DA00D);
	s_wdfSet.insert(0xEA1F50E2);
	s_wdfSet.insert(0xCE11152D);
	s_wdfSet.insert(0xCC1742A6);
	s_wdfSet.insert(0x7FFAB47A);
	s_wdfSet.insert(0x0AF24A29);
	s_wdfSet.insert(0x5ABFF907);
	s_wdfSet.insert(0xF63C410E);
	s_wdfSet.insert(0xF8A67A7A);
	s_wdfSet.insert(0xF617F5A9);
	s_wdfSet.insert(0xCB50AB1D);
	s_wdfSet.insert(0x1A2DEAB9);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xF9494E3A);
	s_wdfSet.insert(0x254E7029);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x2BD1DEF7);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x77D2082D);
	s_wdfSet.insert(0x3E912705);
	s_wdfSet.insert(0x808CEB72);
	s_wdfSet.insert(0xAFE0E635);
	s_wdfSet.insert(0xAFE0E635);
	s_wdfSet.insert(0x535C1994);
	s_wdfSet.insert(0x7F4CBC8C);
	s_wdfSet.insert(0x4ADFB0ED);
	s_wdfSet.insert(0xE2BC8127);
	s_wdfSet.insert(0x1EE9406C);
	s_wdfSet.insert(0x1D3FF13C);
	s_wdfSet.insert(0x4ADFB0ED);
	s_wdfSet.insert(0xE2BC8127);
	s_wdfSet.insert(0xA19EAB31);  //龙
	s_wdfSet.insert(0xF1F26922);  //电
	s_wdfSet.insert(0xD61E2519);  //背景
	s_wdfSet.insert(0x4DB67680);
	s_wdfSet.insert(0x49CBD108);
	s_wdfSet.insert(0xA19EAB31);  //龙 
	s_wdfSet.insert(0xD61E2519);  //背景
	s_wdfSet.insert(0xD61E2519);  //背景
	s_wdfSet.insert(0xF1F26922);  //电
	s_wdfSet.insert(0x4DB67680);
	s_wdfSet.insert(0x49CBD108);
	s_wdfSet.insert(0x5EC2D5BB);
	s_wdfSet.insert(0x9FE48849);
	s_wdfSet.insert(0x63605C8D);
	s_wdfSet.insert(0x5EC2D5BB);
	s_wdfSet.insert(0x63605C8D);
	s_wdfSet.insert(0x9FE48849);
	s_wdfSet.insert(0x63605C8D);
	s_wdfSet.insert(0x9FE48849);
	s_wdfSet.insert(0xD9463A0C);
	s_wdfSet.insert(0x2A2A0663);
	s_wdfSet.insert(0x62EDD1CB);
	s_wdfSet.insert(0x8B43833D);
	s_wdfSet.insert(0x5525C5FB);
	s_wdfSet.insert(0xF184BD59);
	s_wdfSet.insert(0x72AD6DBA);
	s_wdfSet.insert(0xDBCEE32C);
	s_wdfSet.insert(0x59D77EF9);
	s_wdfSet.insert(3635978625);// 0x1E1AF8D9;
	s_wdfSet.insert(0x98753F94);
	s_wdfSet.insert(0x2F78C46E);
	s_wdfSet.insert(0xC48ABA7B);
	s_wdfSet.insert(0x313BCC79);
	s_wdfSet.insert(0x719D767F);
	s_wdfSet.insert(0xF8EE853A);
	s_wdfSet.insert(0xD8857128);
	s_wdfSet.insert(0xEFE73EB9);
	s_wdfSet.insert(0x95FF4460);
	s_wdfSet.insert(0x4DDF5690);
	s_wdfSet.insert(0x21435203);
	s_wdfSet.insert(0x839CC29A);
	s_wdfSet.insert(0x5ECEBEDD);
	s_wdfSet.insert(0x5C0073EE);
	s_wdfSet.insert(0x62EDD1CB);
	s_wdfSet.insert(0x3646A4D9);
	s_wdfSet.insert(0x58628406);
	s_wdfSet.insert(0x20FCCE94);
	s_wdfSet.insert(0x85C9AF08);
	s_wdfSet.insert(0xBBEA83F4);
	s_wdfSet.insert(0x3D3FA597);
	s_wdfSet.insert(0xAF07277F);
	s_wdfSet.insert(0x8103AFD2);//0xC4AA8E18;
	s_wdfSet.insert(0x369C6A29);
	s_wdfSet.insert(0x8F3E73D5);
	s_wdfSet.insert(0x0B788E5A);
	s_wdfSet.insert(0x19182964);
	s_wdfSet.insert(0xDEDEE983);
	s_wdfSet.insert(0xAF07277F);// 0x5CC81980;
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x8F3E73D5);
	s_wdfSet.insert(0x78246FE4);
	s_wdfSet.insert(0xBE7DDF16);
	s_wdfSet.insert(0xDF4C3BE3);
	s_wdfSet.insert(0xACA4A54A);
	s_wdfSet.insert(0x6AD55205);
	s_wdfSet.insert(0x4C117B7C);
	s_wdfSet.insert(0xA3FD9577);
	s_wdfSet.insert(0x66BEBCBA);
	s_wdfSet.insert(0x718754A2);
	s_wdfSet.insert(0x6AD55205);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x3BA4B993);
	s_wdfSet.insert(0xDBFCCCBA);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x6B59951D);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x171544B2);
	s_wdfSet.insert(0xB1822745);
	s_wdfSet.insert(0x21FAE73F);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x1D3FF13C);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0xECD0E003);//必杀
	s_wdfSet.insert(0x3622636F);
	s_wdfSet.insert(0x86D66B9A);
	s_wdfSet.insert(0xF11233BB);
	s_wdfSet.insert(0x4FD9FFF3);
	s_wdfSet.insert(0x4D0A334C);
	s_wdfSet.insert(0xA4120EA9);
	s_wdfSet.insert(0xE3B87E0F);
	s_wdfSet.insert(0x1D3FF13C);
	s_wdfSet.insert(0xECD0E003);
	s_wdfSet.insert(0xB0212A04);
	s_wdfSet.insert(0xB0212A04);


	s_wdfSet.insert(406701913);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3296232902);
	s_wdfSet.insert(3277532867);  //4069888541
	s_wdfSet.insert(3144573054);//3443219224
	s_wdfSet.insert(2119033822);//0x216FE0F8
	s_wdfSet.insert(1807500026);//886189649    
	s_wdfSet.insert(250440769);//0xD5D51AD0  410697672
	s_wdfSet.insert(240383749);// 240383749 //0x78DDA320
	s_wdfSet.insert(2088395993);//0xD5DF5927
	s_wdfSet.insert(222208523);//0x3B9F2278
	s_wdfSet.insert(700775208);
	s_wdfSet.insert(149082521);
	s_wdfSet.insert(153189907);
	s_wdfSet.insert(993909921);
	s_wdfSet.insert(1044547630);
	s_wdfSet.insert(1560928702);
	s_wdfSet.insert(1227154258);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3351166789); //站
	s_wdfSet.insert(2574487372);  //黑天
	s_wdfSet.insert(3482058907);
	s_wdfSet.insert(2208066685);
	s_wdfSet.insert(361218670);
	s_wdfSet.insert(2791494731);
	s_wdfSet.insert(73900200);
	s_wdfSet.insert(2732776514);
	s_wdfSet.insert(4021614423);
	s_wdfSet.insert(717963597);
	s_wdfSet.insert(320881121);
	s_wdfSet.insert(781132167);
	s_wdfSet.insert(949865717);
	s_wdfSet.insert(2324308397);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(1338020705);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(42282575);
	s_wdfSet.insert(1762476724);
	s_wdfSet.insert(780622062);
	s_wdfSet.insert(2198359531);
	s_wdfSet.insert(1261107812);
	s_wdfSet.insert(76806695);
	s_wdfSet.insert(406701913);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3296232902);
	s_wdfSet.insert(3277532867);  //4069888541
	s_wdfSet.insert(3144573054);//3443219224
	s_wdfSet.insert(2119033822);//0x216FE0F8
	s_wdfSet.insert(1807500026);//886189649    
	s_wdfSet.insert(250440769);//0xD5D51AD0  410697672
	s_wdfSet.insert(240383749);// 240383749 //0x78DDA320
	s_wdfSet.insert(2088395993);//0xD5DF5927
	s_wdfSet.insert(222208523);//0x3B9F2278
	s_wdfSet.insert(700775208);
	s_wdfSet.insert(149082521);
	s_wdfSet.insert(153189907);
	s_wdfSet.insert(993909921);
	s_wdfSet.insert(1044547630);
	s_wdfSet.insert(1560928702);
	s_wdfSet.insert(1227154258);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3351166789); //站
	s_wdfSet.insert(2574487372);  //黑天
	s_wdfSet.insert(3482058907);
	s_wdfSet.insert(2208066685);
	s_wdfSet.insert(361218670);
	s_wdfSet.insert(2791494731);
	s_wdfSet.insert(73900200);
	s_wdfSet.insert(2732776514);
	s_wdfSet.insert(4021614423);
	s_wdfSet.insert(717963597);
	s_wdfSet.insert(320881121);
	s_wdfSet.insert(781132167);
	s_wdfSet.insert(949865717);
	s_wdfSet.insert(2324308397);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(1338020705);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(42282575);
	s_wdfSet.insert(1762476724);
	s_wdfSet.insert(780622062);
	s_wdfSet.insert(2198359531);
	s_wdfSet.insert(1261107812);
	s_wdfSet.insert(76806695);
	s_wdfSet.insert(1084205009);
	s_wdfSet.insert(1030021222);
	s_wdfSet.insert(968268166);
	s_wdfSet.insert(3860707508);
	s_wdfSet.insert(3398426285);
	s_wdfSet.insert(3635978625);
	s_wdfSet.insert(3946646209);
	s_wdfSet.insert(3655438388);
	s_wdfSet.insert(1214058823);
	s_wdfSet.insert(2336457533);
	s_wdfSet.insert(2461182746);
	s_wdfSet.insert(916220457);
	s_wdfSet.insert(382287583);
	s_wdfSet.insert(3930943562);
	s_wdfSet.insert(3635978625);// 0x1E1AF8D9;
	s_wdfSet.insert(755485932);
	s_wdfSet.insert(35379719);
	s_wdfSet.insert(2673692967);
	s_wdfSet.insert(2194212682);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3705976162);
	s_wdfSet.insert(1382520422);
	s_wdfSet.insert(968268166);
	s_wdfSet.insert(3860707508);
	s_wdfSet.insert(3398426285);
	s_wdfSet.insert(3635978625);
	s_wdfSet.insert(3946646209);
	s_wdfSet.insert(3655438388);
	s_wdfSet.insert(1214058823);
	s_wdfSet.insert(2336457533);
	s_wdfSet.insert(2461182746);
	s_wdfSet.insert(916220457);
	s_wdfSet.insert(382287583);
	s_wdfSet.insert(3930943562);
	s_wdfSet.insert(3635978625);// 0x1E1AF8D9;
	s_wdfSet.insert(755485932);
	s_wdfSet.insert(35379719);
	s_wdfSet.insert(2673692967);
	s_wdfSet.insert(2194212682);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3705976162);
	s_wdfSet.insert(1382520422);
}

void MyTest::saveWdf3()
{
	ofstream file("C:/Users/wolf/Desktop/wdfSet.txt");
	asert((bool)file, "写入wdf列表失败");
	file << s_wdfSet.size() << "\n";
	for (const auto &wdf : s_wdfSet)
	{
		file << wdf << "\n";
	}
	file.close();
	ccc_msgbox("", "写入wdfSet列表成功");
}

unsigned long MyTest::getUid(unsigned long id)
{
	if (isClassical)
	{
		return id;
	}
	const auto &it = s_tables.find(id);
	if (it == s_tables.end())
	{
		return id;
	}
	return it->second;
}

void MyTest::pushTable(unsigned long id, unsigned long idNew)
{
	s_tables.insert(make_pair(id, idNew));
}

int MyTest::isIgnore(unsigned long id)
{
	if (isClassical)
	{
		return 0;
	}
	if (id == 647087968)
	{
		return 2;
	}
	const auto &it = s_ignores.find(id);
	return it != s_ignores.end();
}

void MyTest::pushIgnore(unsigned long id)
{
	s_ignores.insert(make_pair(id, 1));
}

int MyTest::getJinjie(int lv)
{
	if (lv < per进阶)
	{
		return 1;
	}
	if (lv < per进阶 * 2)
	{
		return 1 + (rand() % 100 < 20) + (rand() % 100 < 5);
	}
	return 1 + (rand() % 100 < 50) + (rand() % 100 < 20);
}
static set<unsigned long> s_Zuoqi;
static set<unsigned long> s_ZuoqiHead;
static set<unsigned long> s_Home;
static set<unsigned long> s_HomeHead;
static set<unsigned long> s_Item;
static set<unsigned long> s_ItemHead;
static set<unsigned long> s_Chat;
static set<unsigned long> s_Other;
static set<unsigned long> s_Npc;
static set<unsigned long> s_NpcHead;
static set<unsigned long> s_MpSkill;
static set<unsigned long> s_MpSkillHead;
static set<unsigned long> s_MpHead;
static set<unsigned long> s_BabySkill;
static set<unsigned long> s_BabySkillHead;
static set<unsigned long> s_SpecialSkill;
static set<unsigned long> s_SpecialSkillHead;
static set<unsigned long> s_FuzhuSkillHead;
static set<unsigned long> s_BabyHead;
static set<unsigned long> s_Baby;
static set<unsigned long> s_RoleHead;
static set<unsigned long> s_Role;
static set<unsigned long> s_RoleZuoqi;
static set<unsigned long> s_Weapon;
static set<unsigned long> s_WeaponHead;
void MyTest::pushZuoqi(const string &desc, unsigned long id)
{
	s_Zuoqi.insert(id);
}

void MyTest::pushZuoqiHead(const string &desc, unsigned long id)
{
	s_ZuoqiHead.insert(id);
}

void MyTest::pushHome(const string &desc, unsigned long id)
{
	s_Home.insert(id);
}

void MyTest::pushHomeHead(const string &desc, unsigned long id)
{
	s_HomeHead.insert(id);
}

void MyTest::pushItem(const string &desc, unsigned long id)
{
	s_Item.insert(id);
}

void MyTest::pushItemHead(const string &desc, unsigned long id)
{
	s_ItemHead.insert(id);
}

void MyTest::pushChat(const string &desc, unsigned long id)
{
	s_Chat.insert(id);
}

void MyTest::pushOther(const string &desc, unsigned long id)
{
	s_Other.insert(id);
}

void MyTest::pushNpc(const string &desc, unsigned long id)
{
	s_Npc.insert(id);
}

void MyTest::pushNpcHead(const string &desc, unsigned long id)
{
	s_NpcHead.insert(id);
}

void MyTest::pushMpSkill(const string &desc, unsigned long id)
{
	s_MpSkill.insert(id);
}

void MyTest::pushMpSkillHead(const string &desc, unsigned long id)
{
	s_MpSkillHead.insert(id);
}

void MyTest::pushMpHead(const string &desc, unsigned long id)
{
	s_MpHead.insert(id);
}

void MyTest::pushBabySkill(const string &desc, unsigned long id)
{
	s_BabySkill.insert(id);
}

void MyTest::pushBabySkillHead(const string &desc, unsigned long id)
{
	s_BabySkillHead.insert(id);
}

void MyTest::pushSpecialSkill(const string &desc, unsigned long id)
{
	s_SpecialSkill.insert(id);
}

void MyTest::pushSpecialSkillHead(const string &desc, unsigned long id)
{
	s_SpecialSkillHead.insert(id);
}

void MyTest::pushFuzhuSkillHead(const string &desc, unsigned long id)
{
	s_FuzhuSkillHead.insert(id);
}

void MyTest::pushBabyHead(const string &desc, unsigned long id)
{
	s_BabyHead.insert(id);
}

void MyTest::pushBaby(const string &desc, unsigned long id)
{
	s_Baby.insert(id);
}

void MyTest::pushRoleHead(const string &desc, unsigned long id)
{
	s_RoleHead.insert(id);
}

void MyTest::pushRole(const string &desc, unsigned long id)
{
	s_Role.insert(id);
}


void MyTest::pushRoleZuoqi(const string &desc, unsigned long id)
{
	s_RoleZuoqi.insert(id);
}


void MyTest::pushWeapon(const string &desc, unsigned long id)
{
	s_Weapon.insert(id);
}

void MyTest::pushWeaponHead(const string &desc, unsigned long id)
{
	s_WeaponHead.insert(id);
}

void MyTest::saveMyWdf()
{
	return;
	CWFile wdf;
	ifstream *fileWdf = nullptr;
	ofstream fileOut;


#if 0
	auto func = [&](const set<unsigned long> &sets, string folder)
	{
		if (!sets.size())
		{
			return;
		}
		system(toString("md C:\\Users\\wolf\\Desktop\\wdfpack\\%s\\", folder.c_str()).c_str());
		folder = "C:/Users/wolf/Desktop/wdfpack/" + folder + "/";
		int i = -1;
		for (const auto &e : sets)
		{
			if (e == 0)
			{
				continue;
			}
			bool b = wdf.GetFileP(e, fileWdf, [&](unsigned char *data, int size)
			{
				fileOut.open(folder + toString("%04d-%x-0.was", ++i, e),
					ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入was失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入文件遗漏");
		}
	};


	pushWdf3();
	for (const auto s : s_wdfSet)
	{
		s_Other.insert(s);
	}
	s_Other.insert(551);
	s_Other.insert(552);

	func(s_Zuoqi,"坐骑");
	func(s_ZuoqiHead, "坐骑图");
	func(s_Home, "家具");
	func(s_HomeHead, "家具图");
	func(s_Item, "道具");
	func(s_ItemHead, "道具图");
	func(s_Chat, "表情");
	func(s_Other, "其他");
	func(s_Npc, "NPC");
	func(s_NpcHead, "NPC图");
	func(s_MpSkill, "门派技能");
	func(s_MpSkillHead, "门派技能图");
	func(s_MpHead, "门派");
	func(s_BabySkill, "宝宝技能");
	func(s_BabySkillHead, "宝宝技能图");
	func(s_SpecialSkill, "特技");
	func(s_SpecialSkillHead, "特技图");
	func(s_FuzhuSkillHead, "辅助技能");
	func(s_BabyHead, "宝宝图");
	func(s_Baby, "宝宝");
	func(s_RoleHead, "角色图");
 	func(s_Role, "角色");
	func(s_RoleZuoqi, "角色坐骑");
 	func(s_Weapon, "武器");
 	func(s_WeaponHead, "武器图");

	ccc_msgbox2("", "写入was完毕"); 

#endif
}


// 染色
// 紫菜 14626 
// 敖白 006
// 虎子 355
// 怀念 024
// 篮子 626
// 冷涯 063
// 清风 004
// 杀破狼 520
// 神天兵 566
// 四季 010
// 小蛮 330
// 小胖牛 334
// 燕子 004
// 羽灵神 030

#endif