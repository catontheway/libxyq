#include "_global.h"

void cTaskFB::ProcessSJ(int stage)
{
	int lv = g_pCharacter->m_PcData.m_Lv;
	switch (stage)
	{
	case 0:
	{
		Init();
		m_HuanShu = 0;
		m_Stage = 0;
		g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[0], this, 1);
		AddTriggerObjMap(m_TextList[3], 3);
		m_List.resize(1);
		//			SetNpc(m_List[0],4,m_TextList[5], m_TextList[3], 1050, 59, 47, 1);
		SetNpc(m_List[0], 4, m_TextList[5], m_TextList[3], 1050, 44, 45, 3);
		UpdateJob(m_TextList[23]);

	}
		break;
	case 1:
	{
		g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, -2, "确定", "取消");
	}
		break;
	case -2:
		if (g_pMainState->m_Dialog.m_retSelect)return;
	case 2:
		switch (m_Stage)
		{
		case 0:g_pMainState->m_Map.LoadMap(106, 11, m_TextList[3].c_str()); break;
		case 1:g_pMainState->m_Map.LoadMap(107, 12, m_TextList[7].c_str()); break;
			// 		case 2:g_pMainState->m_Map.LoadMap(69, 51, m_TextList[9].c_str()); break;
			// 		case 3:g_pMainState->m_Map.LoadMap(69, 51, m_TextList[19].c_str()); break;
		case 2:g_pMainState->m_Map.LoadMap(106, 12, m_TextList[9].c_str()); break;
		case 3:g_pMainState->m_Map.LoadMap(106, 12, m_TextList[19].c_str()); break;
		}
		break;
	case 3:AddNpc();
		break;
	case 4:
		m_NowNpc = g_pMainState->m_pNowSelect;
		g_pMainState->m_pNowSelect->Talk(m_TextList[6], this, 5, "确定", "取消");
		break;
	case 5://得到抓鬼任务
		if (!g_pMainState->m_Dialog.m_retSelect)
		{
			//..
			m_List2.resize(1);
			g_pMainState->m_TaskZhuaGui.AutoGetGost(m_List2[0].m_Npc, m_TextList[3]);
			m_List2[0].m_pTask = this;
			m_List2[0].m_Stage = 8;
			int xerr, yerr;
			g_pMainState->m_TaskZhuaGui.GetErrPos(m_List2[0].m_Npc, xerr, yerr);
			ostringstream oss;
			oss << "去#R" << m_List2[0].m_Npc.m_x/*xerr*/ << " " << m_List2[0].m_Npc.m_y/*yerr*/ << "#R附近把#R" << m_List2[0].m_Npc.m_name << "#R抓回来";
			m_NowNpc->Talk(oss.str());
			UpdateJob(oss.str());
			AddTriggerObjMap(m_TextList[3], 6);
			AddNpcOne(&m_List2[0], true);
		}
		break;
	case 6:
		AddNpc();
		break;
	case 8:
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		g_pMainState->m_TaskZhuaGui.ReadyToFight(m_List2[0].m_Npc);

		AddTriggerFightSuccess(9);
	}
		break;
	case 9:
		RemoveNpc(m_NowNpc);
		SetJiangLi(3);
		m_HuanShu += 6;// 1;
		if (m_HuanShu == 6)
		{
			m_Stage = 1;

			ProcessSJ(2);
			g_pMainState->m_TaskHuoDong.Initmp();
			vector<ePetID> modes =
			{ e程咬金, e空度禅师, e孙婆婆, e菩提祖师, e大大王, e牛魔王,
			e白晶晶, e地藏王, e东海龙王, e镇元大仙, e观音姐姐, e李靖 };
			m_List.resize(12);
			for (int i = 0; i < m_List.size(); i++)
			{
				//				m_List[i] = g_pMainState->m_TaskHuoDong.m_List[i];
				m_List[i].m_Npc.Set(g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[i].m_ShiFuName,
					m_TextList[7], modes[i], 0, 0);
				m_List[i].m_pTask = this;
				m_List[i].m_Stage = 10;
				g_pMainState->m_Map.AutoGetPos(m_List[i].m_Npc.m_x, m_List[i].m_Npc.m_y, m_TextList[7]);
			}
			AddTriggerObjMap(m_TextList[7], 6);
			ProcessSJ(6);
			g_pMainState->m_Tags.Add(m_TextList[15]);
			UpdateJob(m_TextList[15]);

			//			g_pMainState->m_pNowSelect->Talk("是否跳过十二门派闯关?", this, 10086, "是", "否");

			return;
		}
		UpdateJob(m_TextList[16]);
		break;
	case 10086:
		if (!g_pMainState->m_Dialog.m_retSelect)
		{
			ProcessSJ(-11);
		}
		break;
	case 10:
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		// 			int id = m_NowNpc->GetModeID()-2000;
		// 			sMapObjTrigger* plist= FindNpcByObj(m_NowNpc);
		// 			g_pMainState->m_TaskHuoDong.ReadytoFightmp(*plist, (eMengPai)id);


		vector<ePetID> modes =
		{ e程咬金, e空度禅师, e孙婆婆, e菩提祖师, e大大王, e牛魔王,
		e白晶晶, e地藏王, e东海龙王, e镇元大仙, e观音姐姐, e李靖 };

		auto getMPfromMode = [&](int mode)
		{
			forv(modes, i)
			{
				if (modes[i] == mode)
				{
					return eMengPai(i);
				}
			}
			return eMP_随机;
		};

		auto getNamefromMode = [&](int mode)
		{
			forv(modes, i)
			{
				if (modes[i] == mode)
				{
					return g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[i].m_ShiFuName;
				}
			}
			return string("师傅");
		};

		vector<ePetID> mode2;
		forv(modes, i)
		{
			if (modes[i] == m_NowNpc->GetModeID())
			{
				continue;
			}
			mode2.push_back(modes[i]);
		}
		std::random_shuffle(mode2.begin(), mode2.end());
		mode2.push_back((ePetID)m_NowNpc->GetModeID());

		cPropertyData* pPet;
		for (int i = 11; i >= 2; --i)
		{
			ePetID e = mode2[i];
			eMengPai mp = getMPfromMode(e);
			pPet = Add变身EnemyF(lv * 57, e, -1, mp, getNamefromMode(e));
			int lv = pPet->m_Lv;
			if (mp == eMP_女儿村 || mp == eMP_盘丝岭 || mp == eMP_五庄观 || mp == eMP_天宫)
			{
				pPet->HitRateOfSeal.d1 -= 30;
				pPet->m_Controler.Set(1);
			}
			else if (1 || mp == eMP_大唐官府 || mp == eMP_狮驼岭 || mp == eMP_东海龙宫 || mp == eMP_魔王寨)
			{
				pPet->m_Controler.Set(0);
			}
			pPet->m_XiuLian.Set(lv / 5, lv / 5, lv / 5, lv / 5);
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(11);
	}
		break;
	case 11:
	{
		SetJiangLi(8, true, 100, 30, 150);
		RemoveNpc(m_NowNpc);
		//			if (!m_List.size())
		{

			ProcessSJ(-11);
		}
	}
		break;
	case -11:
	{
		m_Stage = 2;
		ProcessSJ(2);
		g_pMainState->m_Tags.Add(m_TextList[8]);
		UpdateJob(m_TextList[8]);
		m_List.resize(1);
		string name;
		int modeid;
		if (-1 == g_pCharacter->m_PcData.m_MengPaiID)g_pCharacter->m_PcData.m_MengPaiID = 0;
		name = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PcData.m_MengPaiID)->m_ShiFuName;
		switch (g_pCharacter->m_PcData.m_MengPaiID)
		{
		case eMP_大唐官府:modeid = 139; break;
		case eMP_化生寺:modeid = 142; break;
		case eMP_女儿村:modeid = 132; break;
		case eMP_方寸山:modeid = 135; break;
		case eMP_狮驼岭:modeid = 143; break;
		case eMP_魔王寨:modeid = 133; break;
		case eMP_盘丝岭:modeid = 136; break;
		case eMP_阴曹地府:modeid = 140; break;
		case eMP_东海龙宫:modeid = 131; break;
		case eMP_五庄观:modeid = 134; break;
		case eMP_普陀山:modeid = 141; break;
		default:  modeid = 138; break;
		}
		m_HuanShu = 0;
		//int x, y;

		//				SetNpc(m_List[0], 12, name, m_TextList[9], modeid, 102, 62, 3);
		SetNpc(m_List[0], 12, name, m_TextList[9], modeid, 52, 62, 3);
		AddTriggerObjMap(m_TextList[9], 3);//&m_List[0]);
		AddNpcOne(&m_List[0]);
		m_Stage2 = 0;
	}
		break;
	case 12:
	{
		if (m_Stage2)return;
		m_NowNpc = g_pMainState->m_pNowSelect;
		m_NowNpc->Talk(m_TextList[10], this, 13, "确定", "取消");

	}
		break;
	case 13:
	{
		if (0 != g_pMainState->m_Dialog.m_retSelect)return;
		m_Stage2 = 1;
		// 			int rate = rand() % 100;
		// 			if (rate < 30)
		// 			{//要包子
		// 				m_NowNpc->Talk(m_TextList[11]);
		// 				g_pMainState->m_TriggerGive.AddTask(m_NowNpc->m_TrueName.GetString(),0,23,this, 14);
		// 				return;
		// 			}
		// 			else
		{//战斗
			int x, y;
			g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[9]);
			ostringstream oss;
			oss << m_TextList[12];
			oss << x << " " << y;
			oss << m_TextList[13];
			m_NowNpc->Talk(oss.str());
			UpdateJob(oss.str());
			m_List2.resize(1);
			SetNpc(m_List2[0], 15, m_TextList[14], m_TextList[9], rand() % 12 + 2000, x, y);
			AddNpcOne(&m_List2[0], true);
		}
	}
		break;
	case 14:
	{
		SetJiangLi(2, true, 50);
		m_Stage2 = 0;
	}
		break;
	case 15:
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		cPropertyData* pPet;
		pPet = AddPCEnemyF(lv * 250, m_NowNpc->GetModeID(), 0, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
		//			pPet->m_DamagePercent.d2 = 50;
		int enemynum = g_pMainState->AtutoGetEnemyNum() - 1;
		for (int i = 0; i < enemynum; i++)
		{
			switch (rand() % 4)
			{
			case 0:
				pPet = Add变身EnemyF(-lv * 10, e蛤蟆精);
				pPet->DmgPercent.d2 = 95;
				pPet->DmgPercentOfMagic.d2 = 95;
				break;
			case 1:
				pPet = Add变身EnemyF(-lv * 10, e蛤蟆精);
				pPet->DmgPercent.d2 = 95;
				pPet->DmgPercentOfMagic.d2 = 95;
				break;
			case 2:
				pPet = Add变身EnemyF(lv * 150, e花妖);
				pPet->DmgPercent.d2 = 80;
				break;
			case 3:
				pPet = Add变身EnemyF(lv * 150, e蝴蝶仙子);
				pPet->DmgPercent.d2 = 80;
				break;
			}
		}
		g_StateType = STATE_FIGHT;
		SetMusicFB();
		AddTriggerFightSuccess(16);
	}
		break;
	case 16:
	{
		UpdateJob(m_TextList[8]);
		RemoveNpc(m_NowNpc);
		SetJiangLi(3, true);
		m_Stage2 = 0;
		m_HuanShu += 8; // 1;
		if (8 == m_HuanShu)
		{
			m_Stage = 3;
			m_HuanShu = 0;
			AddTriggerObjMap(m_TextList[19], 3);

			g_pMainState->m_Tags.Add(m_TextList[17]);
			UpdateJob(m_TextList[18]);

			m_List2.resize(1);
			//				SetNpc(m_List2[0], 18, m_TextList[20], m_TextList[19], 1120, 63, 113);
			SetNpc(m_List2[0], 18, m_TextList[20], m_TextList[19], 1120, 45, 70);
			vector<int> modelist;
			modelist.resize(4);
			for (int i = 0; i < modelist.size(); i++)
				modelist[i] = i + 63;
			StageSetSameNpc(modelist, m_TextList[19], 17, 57/*20*/);



			AddTriggerGive(m_TextList[20], 27, 57, 20, false);
			AddTriggerGive(m_TextList[20], 27, 58, 21, false);
			ProcessSJ(2);
			m_Stage2 = 50;
		}
	}
		break;
	case 17://冬 战斗
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		Add变身EnemyF(lv * 250, (ePetID)m_NowNpc->GetModeID(), -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
		int enemynum = g_pMainState->AtutoGetEnemyNum() - 1;
		ePetID ptid;
		for (int i = 0; i < enemynum; i++)
		{
			switch (rand() % 4)
			{
			case 0:ptid = e机关兽;
			case 1:ptid = e机关鸟;
			case 2:ptid = e阴阳伞;
			default:ptid = e蛤蟆精;
			}
			Add变身EnemyF(lv * 200, ptid);
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;

		AddTriggerFightSuccess(19);
	}
		break;
	case 18:
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		ostringstream oss;
		oss << "当前进度#R";
		oss << m_HuanShu << "/" << m_Stage2;
		oss << "#R";
		g_pMainState->m_pNowSelect->Talk(oss.str());
	}
		break;
	case 19:
	{
		GetItem(27, 57 + rand() % 2, true);
		RemoveNpc(m_NowNpc);
	}
		break;
	case 20:
	case 21:
	{
		// 			if (20==stage)
		// 			m_HuanShu += 20;
		// 			else 
		m_HuanShu += 50;
		SetJiangLi(3, true);


		int mode2;
		switch (m_HuanShu / 10)
		{
		case 0:mode2 = 1120; break;
		case 1:mode2 = 1121; break;
		case 2:mode2 = 1122; break;
		case 3:mode2 = 1123; break;
		default: mode2 = 1124; break;
		}
		if (mode2 != m_List2[0].m_Npc.m_modeid)
		{
			m_List2[0].m_Npc.m_modeid = mode2;
			RemoveNpc(&m_List2[0].m_Npc, false);
			g_pMainState->m_Map.AddNpc(&m_List2[0], true);
		}
		if (m_HuanShu < 50)
		{
			AddTriggerGive(m_TextList[20], 27, 57, 20, false);
			AddTriggerGive(m_TextList[20], 27, 58, 21, false);
		}
		else
		{
			m_NowNpc = 0;
			m_NowNpc->Talk(m_TextList[21]);
			ClearNpc();
			g_pMainState->m_Map.LoadMap(20, 20, "四季奖励");
			//				StageSetSameNpc(1125, m_TextList[19],22,25);
			StageSetSameNpc(1125, "四季奖励", 22, 25);

			//				m_List.resize(25);
			//				int x, y;
			//				g_pMainState->m_Map.AutoGetPos(x, y, mapname);
			//				for (int i = 0; i < m_List.size(); i++)
			{
				//					g_pMainState->m_Map.AutoGetPos(x, y);
				//					SetNpc(m_List[i], 22, "", "冬", 1125, 63, 113);
			}
			//				if (g_pMainState->m_Map.m_MapName == mapname)
				{
					//					AddNpc();
				}

			UpdateJob(m_TextList[22]);

		}
	}
		break;
	case 22:
	{
		int rat = rand() % 100;
		if (rat < 5)
		{
			SetJiangLiItem(33, 27);
		}
		else
			if (rat < 15)
			{
			//				SetJiangLiItem(38 + rand() % 4, 27);
			}
		if (rat < 0/*25*/)
		{
			SetJiangLiItem(rand() % 17, 29);
		}
		else
		{
			if (rand() % 2)
				SetJiangLi(5, true, 100, 0, 0);
			else SetJiangLi(5 * 2, true, 0, 0);
		}
		RemoveNpc(g_pMainState->m_pNowSelect);
		if (!m_List.size())
		{
			ProcessSJ(1002);
		}
		break;
	}
	case 1002:
		EndFB();
		break;
	}
}