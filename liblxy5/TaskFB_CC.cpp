#include "_global.h"


void cTaskFB::ProcessCC(int stage)
{
	int lv = g_pCharacter->m_PcData.m_Lv;
	switch (stage)
	{
	case 0:
	{
		m_Stage = 0;
		AddTriggerObj(m_TextList[1], m_TextList[0], 1);
		AddTriggerObjMap(m_TextList[3], 3);
		m_List.resize(1);
		//			SetNpc(m_List[0],4,m_TextList[5], m_TextList[3], 1075,53,32,1);
		SetNpc(m_List[0], 4, m_TextList[5], m_TextList[3], /*1075*/179, 38, 28, 3);
		UpdateJob(m_TextList[22]);
	}
		break;
	case 1:
		g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, -1, "确定", "取消");
		break;
	case -1:
		if (g_pMainState->m_Dialog.m_retSelect)return;
	case 2:

	{
		if (!m_Stage)
		{
			//				g_pMainState->m_Map.LoadMap(8, 11, m_TextList[3].c_str());
			g_pMainState->m_Map.LoadMap(72, 15, m_TextList[3].c_str());
		}
		else
		{
			//				g_pMainState->m_Map.LoadMap(37, 20, m_TextList[14].c_str());
			g_pMainState->m_Map.LoadMap(113, 23, m_TextList[14].c_str());
		}
	}
		break;
	case 3:AddNpc();
		break;
	case 4:
		m_NowNpc = g_pMainState->m_pNowSelect;
		AddTriggerDialog(0, 6);
		UpdateJob("回答道士的问题,把收集到的木头交给道观(160,85)", -1, -1, "副本");
		break;
	case 6://车迟收集木头

	{
		m_Stage2 = 1;// 20;
		RemoveNpc(m_NowNpc);
		m_List2.resize(1);
		//			SetNpc(m_List2[0],8,m_TextList[4], m_TextList[3], 1119, 87, 116, 1);
		SetNpc(m_List2[0], 8, m_TextList[4], m_TextList[3], 1119, 162, 87, 1);
		//			StageSetSameNpc(1077, m_TextList[3], 9, 40, m_TextList[6]);
		StageSetSameNpc(1077, m_TextList[3], 9, 56, m_TextList[6]);
	}
		break;
	case 8:

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		int num = 0;
		for (int i = 0; i < 60; i++)
		{
			sItem2& item = g_pCharacter->m_PcData.m_Items[i];
			if (!item.m_Num)continue;
			if (item.GetID() == 56)
				if (item.GetType() == 27)
				{
				num += item.GetNum();
				item.m_Num = 0;
				}
		}
		if (num)
		{
			if (num > m_Stage2)
				num = m_Stage2;
			m_Stage2 -= num;
			for (int i = 0; i < num; i++)
			{
				SetJiangLi(1);
				if (!(rand() % 20))GetItem(27, rand() % 4 + 38, true);
			}
			if (m_Stage2)
			{
				ostringstream oss;
				oss << "还需要";
				oss << m_Stage2;
				oss << "个木头";
				m_NowNpc->Talk(oss.str());
			}
			else
			{
				g_pHeroObj->Talk(m_TextList[7]);
				UpdateJob(m_TextList[7]);
				ClearNpc();
				StageSetSameNpc(120, m_TextList[3], 12, 52, m_TextList[8]);
			}
		}
	}
		break;
	case 9://道士

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		m_NowNpc->Answer(this, 10);
	}
		break;
	case 10:

	{
		if (g_pMainState->m_Dialog.m_retSelect == g_pMainState->m_Dialog.m_Question.answer)
		{
			GetItem(27, 56);
		}
		else
		{
			m_NowNpc->Talk(g_pMainState->m_Dialog.GetTrueSelect());
		}
		//道士换地方
		int x, y;
		sTaskMapObj* pNpc = FindNpcByObj(m_NowNpc);
		g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[3]);
		m_NowNpc->SetXY(x * 20, g_pMainState->m_Map.m_pMap->m_Height - y * 20);
		if (!m_NowNpc)return;
		pNpc->m_Npc.m_x = x;
		pNpc->m_Npc.m_y = y;
		g_pMainState->FindObj();
	}
		break;
	case 12:

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		int enemynum = g_pMainState->AtutoGetEnemyNum();
		sAddPoint addpoint;
		for (int i = 0; i < enemynum; i++)
		{
			AddPetEnemyF(lv * 200, e泡泡, lv, m_TextList[8]);
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(13);
	}
		break;
	case 13:

	{
		SetJiangLi(2, 0, 200, 100);
		if (!(rand() % 10))GetItem(27, rand() % 4 + 38, true);
		RemoveNpc(m_NowNpc);
		//			if (!m_List.size())
		{
			AddTriggerDialog(1, 14);
		}
	}
		break;
	case 14:

	{
		UpdateJob(m_TextList[12]);
		m_List.resize(3);
		// 			SetNpc(m_List[0],16,m_TextList[9],m_TextList[3],51,62,99,3);
		// 			SetNpc(m_List[1],16,m_TextList[10], m_TextList[3], 51, 72, 103, 3);
		// 			SetNpc(m_List[2],16,m_TextList[11], m_TextList[3], 51, 84, 109, 3);
		m_List.resize(1);
		g_pMainState->m_Map.LoadMap(49, 74, "车迟国1");
		SetNpc(m_List[0], 24, m_TextList[9], "车迟国1", 51, 47, 44, 1);
		Process(3);
	}
		break;
	case 16:
	case 24:
	case 25:
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		Add变身EnemyF(lv * 250, e大力金刚, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
		for (int i = 0; i < 7; i++)
		{
			Add变身EnemyF(lv * 200, (ePetID)(30 + rand() % 30));
		}
		g_StateType = STATE_FIGHT;
		SetMusicFB();
		AddTriggerFightSuccess((stage == 16) ? 17 : (stage == 24 ? 26 : 27));
	}
		break;
	case 26:
	case 27:
	case 17:
		SetJiangLi(5);
		if (!(rand() % 20))
		{
			GetItem(27, 5, true);
		}
		RemoveNpc(m_NowNpc);
		// 		int x, y;
		// 		g_pMainState->m_Map.AutoGetPos(x,y,m_TextList[14]);
		if (stage == 26)
		{
			m_List.resize(1);
			g_pMainState->m_Map.LoadMap(77, 40, "车迟国2");
			SetNpc(m_List[0], 25, m_TextList[10], "车迟国2", 51, 48, 49, 1);
			AddNpc();
		}
		else if (stage == 27)
		{
			m_List.resize(1);
			g_pMainState->m_Map.LoadMap(21, 24, "车迟国3");
			SetNpc(m_List[0], 16, m_TextList[11], "车迟国3", 51, 44, 40, 1);
			AddNpc();
		}
		else if (stage == 17)
		{
			m_Stage = 1;
			AddTriggerObjMap(m_TextList[14], 3);
			m_List.resize(2);
			// 			SetNpc(m_List[0], 18, m_TextList[15], m_TextList[14], 56, 71, 36);
			// 			SetNpc(m_List[1], 19, m_TextList[16], m_TextList[14], 48, 88, 29);
			SetNpc(m_List[0], 18, m_TextList[15], m_TextList[14], 49, 46, 59, 3);
			SetNpc(m_List[1], 19, m_TextList[16], m_TextList[14], 48, 58, 64, 3);
			Process(2);
			UpdateJob(m_TextList[13]);
		}
		// 			int size = m_List.size();
		// 			if (size == 2)
		// 			{
		// 				g_pMainState->m_Map.LoadMap(77, 40, "车迟国2");
		// 				SetNpc(m_List[1], 16, m_TextList[10], "车迟国2", 51, 48, 49, 1);
		// 				AddNpc();
		// 			}
		// 			else if (size == 1)
		// 			{
		// 
		// 			}
		// 			else if (!m_List.size())
		// 			{
		// 				m_Stage = 1;
		// 				AddTriggerObjMap(m_TextList[14], 3);
		// 				//偷懒 只设计了雷打不动
		// 				m_List.resize(2);
		// //				g_pMainState->m_Map.AutoGetPos(x, y);
		// 				SetNpc(m_List[0], 18, m_TextList[15], m_TextList[14], 56, 71, 36);
		// //				g_pMainState->m_Map.AutoGetPos(x, y);
		// 				SetNpc(m_List[1], 19, m_TextList[16], m_TextList[14], 48, 88, 29);
		// 				Process(2);
		// 				UpdateJob(m_TextList[13]);
		// 			}
		break;
	case 18://你不动

	{
		m_NowNpc = g_pMainState->m_pNowSelect;

		Add变身EnemyF(lv * 280, e律法女娲, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
		sAddPoint addpoint;
		for (int i = 0; i < 9; i++)
		{
			Add变身EnemyF(lv * 200, (ePetID)(20 + rand() % 50));
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(20);
	}
		break;
	case 19://我不动

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		Add变身EnemyF(lv * 280, e净瓶女娲, lv + 9, eMP_魔王寨, m_NowNpc->m_TrueName.GetString());
		for (int i = 0; i < 4; i++)
			Add变身EnemyF(lv * 280, e净瓶女娲, -1, eMP_魔王寨);
		for (int i = 0; i < 5; i++)
			AddPetEnemyF(lv * 200, e大力金刚);
		g_StateType = STATE_FIGHT;
		SetMusicFB();
		AddTriggerFightSuccess(20);
	}
		break;
	case 20:

	{
		RemoveNpc(m_NowNpc);
		SetJiangLi(5);
		if (!m_List.size())
		{
			m_NowNpc->Talk(m_TextList[17]);
			m_List.resize(1);
			int x, y;
			g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[14]);
			//				SetNpc(m_List[0], 21, m_TextList[18],m_TextList[14],56,20,128,3);
			SetNpc(m_List[0], 21, m_TextList[18], m_TextList[14], e超级神虎, 20, 77, 3);
			Process(3);
			UpdateJob(m_TextList[17]);
		}
	}
		break;
	case 21://最终BOSS

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		Add变身EnemyF(lv * 500, e超级神虎, lv + 15, eMP_狮驼岭, "虎力大仙");
		Add变身EnemyF(lv * 300, e超级神羊, lv + 10, eMP_魔王寨, "羊力大仙");
		Add变身EnemyF(lv * 300, e超级灵鹿, lv + 10, eMP_化生寺, "鹿力大仙");
		sAddPoint addpoint;
		ePetID petid;
		for (int i = 0; i < 5; i++)
		{
			switch (rand() % 3)
			{
			case 0:petid = e炎魔神; break;
			case 1:petid = e灵鹤; break;
			default:petid = e鬼将;
				break;
			}
			Add变身EnemyF(lv * 280, petid);
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(22);
	}
		break;
	case 22:

	{
		RemoveNpc(m_NowNpc);
		SetJiangLi(10 * 5);
		//宝箱出现
		//			StageSetSameNpc(1125, m_TextList[14], 23, 20);
		g_pMainState->m_Map.LoadMap(20, 20, "车迟奖励");
		StageSetSameNpc(1125, "车迟奖励", 23, 20);

		// 			m_List.resize(20);
		// 			for (int i = 0; i < m_List.size(); i++)
		// 			{
		// 				SetNpc(m_List[i], 23, "", "九霄云外", 1125, 20, 128);
		// 			}
		// 			AddNpc();
		UpdateJob(m_TextList[21], 2);
	}
		break;
	case 23:

	{
		vector<int> rate;
		rate.resize(5);
		rate[0] = 5;
		rate[1] = /*3*/0;
		rate[2] = 25;
		rate[3] = 20;
		rate[4] = 20;
		int rat = rand() % 100;
		for (int i = 0; i < rate.size(); i++)
		{
			if (rat < rate[i])
			{
				switch (i)
				{
				case 0:
					switch (rand() % 3)
					{
					case 0:
						SetJiangLiItem(g_pMainState->m_ItemManage.m_LShouJueList[rand() % g_pMainState->m_ItemManage.m_LShouJueList.size()], 40); //兽决
						break;
					case 1:SetJiangLiItem(33, 27);
						break;
					case 2:
						SetJiangLiItem(rand() % 6 + 5, 27);
						break;
					}
					break;
				case 1:SetJiangLiItem(rand() % 17, 29); //宝石
					break;
				case 2:SetJiangLi(5, true, 100, 0, 0);//钱
					break;
				case 3:SetJiangLi(5, true, 0, 0, 100);//经验
					break;
				case 4:SetJiangLiItem(rand() % 89, 41);//符石
					break;
				}
				break;
			}
			rat -= rate[i];
		}
		RemoveNpc(g_pMainState->m_pNowSelect);
		if (!m_List.size())
		{
			//				RemoveNpc(g_pMainState->m_pNowSelect);
			ProcessCC(1002);
		}
	}
		break;
	case 1002:
		EndFB();
		break;
	}
}
