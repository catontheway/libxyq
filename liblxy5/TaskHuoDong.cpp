#include "_global.h"

bool cTaskHuoDong::Process(int stage)
{
	if (m_HuoDongID == -1)return true;
	switch (m_HuoDongID)
	{
	case 门派闯关:
		Processmp(stage);
		break;
	case 科举:
		break;
	default:
		ERRBOX;
		break;
	}
	return true;
}

bool cTaskHuoDong::Processmp(int stage)
{
	switch (stage)
	{
	case -1://活动时间到
		break;
	case 0:
	{
		Init();
		for (int i = 0; i < c_MenPaiNumber; i++)
		{
			AddTriggerObjMap(&m_List[i]);
		}
		m_HuanShu = g_GlobalValues[21];
//		UpdateJob("去长安107,200参加12门派");

		if (!m_Idlist.size())
		{
			m_Idlist.resize(c_MenPaiNumber);
			for (int i = 0; i < c_MenPaiNumber; i++)
			{
				m_Idlist[i] = i;
			}
		}
//		int id =  rand() % m_Idlist.size();
//		m_Stage = m_Idlist[id];
//		m_Idlist.erase(m_Idlist.begin() + id);
		m_Stage = m_HuanShu;
		string text = GetText();
		if (!m_NowNpc && g_pHeroObj)
		{
			g_pHeroObj->Talk(text);
		}
		else
		{
			m_NowNpc->Talk(text);
		}

		UpdateJob("#R" + g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(m_Stage)->m_Name + "#R\n", m_HuanShu);
	}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	{
		if (stage != m_Stage + 1)
		{
			return true;
		}
		m_NowNpc = g_pMainState->m_pNowSelect;
		ReadytoFightmp(m_List[m_Stage], (eMengPai)m_MengPaiId[m_Stage]);
		AddTriggerFightSuccess(18);
	}
		break;
	case 16:

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		m_NowNpc->Talk("要领取任务吗?", this, 17, "确定", "取消");
	}
		break;
	case 17:
	{
		if (0 != g_pMainState->m_Dialog.m_retSelect)
		{
			return true;
		}
		if (m_Stage >= 0)
		{
			return true;
		}
	}
	case -17:
	{//更新任务
		if (m_Idlist.empty())
		{
			m_Idlist.resize(c_MenPaiNumber);
			for (int i = 0; i < c_MenPaiNumber; i++)
				m_Idlist[i] = i;
		}

// 		int id = rand() % m_Idlist.size();
// 		m_Stage = m_Idlist[id];
// 		m_Idlist.erase(m_Idlist.begin() + id);
		m_Stage = m_HuanShu;
		string text = GetText();
		m_NowNpc->Talk(text);
//		UpdateJob(text, m_HuanShu);
		UpdateJob("#R" + g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(m_Stage)->m_Name + "#R\n", m_HuanShu);
	}
		break;
	case 18:
	{
	//	SetJiangLi(8 * 4, true, 30, 0, 100, 100);
		g_pMainState->awardklv(233 + m_HuanShu * 5, 72 + m_HuanShu * 2);
		g_pMainState->award125(25 + m_HuanShu, 150);

		if ((g_GlobalValues[21] = ++m_HuanShu) >= c_MenPaiNumber)
		{
			g_GlobalValues[21] = m_HuanShu = 0;
			RemoveTriggerObjMap();
			g_pMainState->m_Job.ReMoveJob(this);
			m_HuoDongID = -1;
			g_pMainState->m_Tags.Add("门派闯关结束");
			return true;
		}

		if (m_pTask)
		{
			if (m_HuanShu == m_TriggerHuanShu)
			{
				cTaskFather* p = m_pTask;
				m_pTask = 0;
			//	RemoveTriggerObjMap();
			//	g_pMainState->m_Job.ReMoveJob(this);
			//	m_HuoDongID = -1;
				p->Process(m_TaskRet);
				return true;
			}
		}

		Process(-17);
	}
		break;
	}
	return true;
}



std::string cTaskHuoDong::GetText()
{
	ostringstream oss;
	cMengPai* pmp = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(m_Stage);
	oss << "下一关为#R";
	oss << pmp->m_Name;
	oss << "#R";
	return oss.str();
}

void cTaskHuoDong::Start(eHuoDong id)
{
	m_HuoDongID = id;
	Init();
	Process(0);
}

struct sModexy{ int x, y; };
static vector<sModexy> s_xys =
{
	{ 140, 58 }, //DT
	{ 32, 19 }, //HS
	{ 65, 62 }, //NE
	{ 120, 38 }, //FC
	{ 112, 85 }, //ST
	{ 40, 26 }, //MW
	{ 146, 34 }, //PS
	{ 102, 17 }, //DF
	{ 72, 38 }, //LG
	{ 40, 43 }, //WZ
	{ 70, 21 }, //PT
	{ 193, 36 }, //TG

	{ 33, 86 }, //LB
	{ 80, 118 }, //WD
	{ 52, 27 }, //SM
};

void cTaskHuoDong::Initmp()
{
	if (m_bInit12)return;
	m_bInit12 = true;

	const auto mps = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai;
	forv(m_List, i)
	{
		m_List[i].m_pTask = this;
		m_List[i].m_Stage = i + 1;
		sNpc& n = m_List[i].m_Npc;
// 		if (i == c_MenPaiNumber)
// 		{
// 			n.m_modeid = 1084;
// 			n.m_x = 107;
// 			n.m_x = 200;
// 			n.m_mapname = "长安城";
// 			n.m_name = "门派闯关使者";
// 			n.m_direction = 3;
// 			break;
// 		}
		n.m_modeid = g_pMainState->getModelFromMp(m_MengPaiId[i] = i);
		n.m_x = s_xys[i].x;
		n.m_y = s_xys[i].y;
		n.m_mapname = mps[i].m_XunLuoMapName;
		n.m_name = mps[i].m_Name + "护法";
		n.m_direction = 2;
//		sChangeColorData2 m_Ranse;
		int typelist[2];
		GetWeaponType(n.m_modeid, typelist[0], typelist[1]);
		n.m_modeid += 2000;
		n.weapontype = typelist[rand() % 2];
		if (typelist[1] == -1)
		{
			n.weapontype = typelist[0];
		}
		n.weaponid = g_pMainState->m_ItemManage.GetIDByLv(n.weapontype, g_pMainState->getAvgLv() + 5);
	}

	m_Idlist.resize(c_MenPaiNumber);
	for (int i = 0; i < c_MenPaiNumber; i++)
	{
		m_Idlist[i] = i;
	}
	m_Stage = -1;
	return;


	ifstream File;
	ostringstream oss;
//	oss << g_pathData;
	oss << "十二门派.txt";
	File.open(oss.str());
	if (!File)ERRBOX;
	for (int i = 0; i < 13; i++)
	{
		File >> m_MengPaiId[i];
		m_List[i].m_Npc.Load(File);
		m_List[i].m_pTask = this;
		m_List[i].m_Stage = i + 1;
	}
	m_Idlist.resize(12);
	for (int i = 0; i < 12; i++)
		m_Idlist[i] = i;
	File.close();

	m_Stage = -1;
}

void cTaskHuoDong::Init()
{
	switch (m_HuoDongID)
	{
	case 门派闯关:
		Initmp();
		break;
	case 科举:
		break;
	default:
		ERRBOX;
		break;
	}
}

void cTaskHuoDong::ReadytoFightmp(sTaskMapObj& list, eMengPai mp)
{
	// 	int enemynum =  g_pMainState->AtutoGetEnemyNum();
	// 	if (enemynum > 9)enemynum = 9;
	int lv = g_pMainState->getAvgLv();//  ->m_PcData.m_Lv;
//	sZiZhi zizhi;
//	zizhi.Set(1200 + m_HuanShu * 3, 800 + m_HuanShu * 3, 2000 + m_HuanShu * 4, 4000 + m_HuanShu * 10, 1000 + m_HuanShu * 2, 1000 + m_HuanShu * 2, 100 + (m_HuanShu >> 2));
//	cPropertyData* pPet = AddPCEnemyF(lv * 300, list.m_Npc.m_modeid, &zizhi, lv, mp, list.m_Npc.m_name, list.m_Npc.weapontype, list.m_Npc.weaponid);
	auto pPet = g_pMainState->AddEnemy(list.m_Npc.m_modeid, g_pMainState->getMaxLv(), mp, list.m_Npc.m_name);
	pPet->_isWeakSeal = false;
//	pPet->setPointAfterLv(g_pMainState->getAddpointFromMp(pPet->m_MengPaiID, true), false);
//	pPet->autoEquip(false);
//	pPet->autoData(true, true, true);
//	pPet->apply();
	int xl = cct::getCurrMaxXiulianLv(pPet->m_Lv);
	pPet->m_XiuLian.Set(xl, xl, xl, xl);
	pPet->applyXL();
	pPet->StabRate.d1 += 50;
	pPet->StabPercent.d1 += 20;
//	pPet->HitRateOfSeal.d1 = 0;
	if (g_pMainState->m_AI.isMpSeal(pPet) || g_pMainState->m_AI.isMpCure(pPet))
	{
		pPet->LiveCp = 10 + rand() % 10;
		int &n = pPet->m_NumofSpecial;
		if (n == pPet->m_SpecialSkillList.size())
		{
			--n;
		}
		pPet->m_SpecialSkillList[n++] = 13;
	}
	

	string name = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[mp].m_Name + "护卫";
	for (int i = 0; i < 2; i++)
	{
		pPet = g_pMainState->AddEnemy(cct::getPetModel(), lv, mp, name);
		xl = cct::getCurrMaxXiulianLv(pPet->m_Lv);
		pPet->m_XiuLian.Set(xl, 0, xl, 0);
		pPet->applyXL();
	}

	for (int i = 0; i < 2; i++)
	{
		int mp2 = cct::getMenpai(eMP_随机);
		cPcData* pc = nullptr;
		if (g_pMainState->m_AI.isMpMag(pPet) || g_pMainState->m_AI.isMpPhy(pPet))
		{
			do
			{
				mp2 = cct::getMenpai(eMP_随机);
				if (pc)
				{
					g_pMainState->m_FightWorkList[pc->m_IDinFightWorkList].isExist = false;
				}
				pc = g_pMainState->AddEnemy(cct::getPetModel(), lv, (eMengPai)mp2, name);
				if (g_pMainState->m_AI.isMpSeal(pc) || g_pMainState->m_AI.isMpCure(pc))
				{
					break;
				}
			} while (true);
		}
		else if (g_pMainState->m_AI.isMpSeal(pPet))
		{
			mp2 = cct::getMenpai(eMP_辅助);
		}
		if (!pc)
		{
			pc = g_pMainState->AddEnemy(cct::getPetModel(), lv, (eMengPai)mp2, name);
		}

		if (g_pMainState->m_AI.isMpCure(pc) || g_pMainState->m_AI.isMpSeal(pc))
		{
			pc->LiveCp = 10 + rand() % 10;
			int &n = pc->m_NumofSpecial;
			if (n == pc->m_SpecialSkillList.size())
			{
				--n;
			}
			pc->m_SpecialSkillList[n++] = 13;
		}
		xl = cct::getCurrMaxXiulianLv(pc->m_Lv);
		pc->m_XiuLian.Set(0, xl, 0, xl);
		pc->applyXL();
	}

	int mid;
	for (int i = 0; i < 5; i++)
	{
		cObj* obj = g_pMainState->AddEnemy();
		if (!obj)
		{
			break;
		}
		mid = cct::getPetModel(lv - 80, lv + 5, true);
		obj->AutoData(mid, "守护兽");
		cPet* pet = (cPet*)obj->m_pIndex;
		g_pMainState->AutoPet(pet, mid, lv);
		cPetData& pd = pet->m_PetData;
		if (g_pMainState->m_AI.isMagFromPoint(&pd))
		{
			xl = cct::getCurrMaxXiulianLv(pd.m_Lv) / 2;
			pd.m_XiuLian.Set(xl, 0, xl, 0);
			pd.applyXL();
		}
		pd.HPMax.SetDataAddPercent(cBangPaiJiNengXueXi::m_BangpaiSkilllv/* << 2*/);
		pd.MPMax.SetDataAddPercent(cBangPaiJiNengXueXi::m_BangpaiSkilllv);
		pd.FillHpMp();
	}
	g_StateType = STATE_FIGHT;
}

void cTaskHuoDong::UpdateJob(string text, int huanshu)
{
	sJob job;
	string title;
	switch (m_HuoDongID)
	{
	case 门派闯关:title = "门派闯关";
		break;
	case 科举:title = "科举";
		break;
	default:
		break;
	}
	job.Set(title, text, -1, this, 0);
	g_pMainState->m_Job.AddaJob(job, huanshu);
}

void cTaskHuoDong::Load(ifstream& File)
{
	File >> m_HuoDongID;
	if (m_HuoDongID == -1)return;
	m_bInit12 = false;
	Init();
	string str;
	File >> str;
	int num;
	File >> num;
	m_Idlist.resize(num);
	for (uint i = 0; i < m_Idlist.size(); i++)
		File >> m_Idlist[i];
	File >> m_Stage;
	File >> m_HuanShu;
	int k;
	File >> k;
	if (k)
	{
		File >> k;
		m_pTask = g_pMainState->FindTaskByID(k);
		File >> m_TaskRet;
		File >> m_TriggerHuanShu;
	}

}

void cTaskHuoDong::Save(ofstream& File)
{
	File << "\n";
	File << m_HuoDongID;
	if (m_HuoDongID == -1)return;
	File << " 活动 ";
	File << m_Idlist.size() << " ";
	for (uint i = 0; i < m_Idlist.size(); i++)
		File << m_Idlist[i] << " ";
	File << m_Stage << " ";
	File << m_HuanShu << " ";
	//是否有剧情
	if (m_pTask)
	{
		File << 1 << " ";
		File << m_pTask->m_type << " ";
		File << m_TaskRet << " ";
		File << m_TriggerHuanShu << " ";
	}
	else File << 0 << " ";
}

