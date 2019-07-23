#include "_global.h"


void cTaskFB::ProcessSL(int stage)
{
	switch (stage)
	{
	case 0:

	{
		m_Stage = 0;
		g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[0], this, 1);
		g_pMainState->m_TriggerObjMap.AddTask(this, 2, m_TextList[2]);
		m_List.resize(2);
		//			SetNpc(m_List[0],3,m_TextList[3], m_TextList[2],1117,35,37,3);
		//			SetNpc(m_List[1],6, m_TextList[4], m_TextList[2], 1118, 93, 80, 1);
		SetNpc(m_List[0], 3, m_TextList[3], m_TextList[2], 1117, 77, 26, 3);
		SetNpc(m_List[1], 6, m_TextList[4], m_TextList[2], 1118, 124, 43, 1);
		UpdateJob(m_TextList[26]);
	}
		break;
	case 1:g_pMainState->m_pNowSelect->Talk(m_TextList[5], this, -1, "确定", "取消");
		break;
	case -1:
		if (!g_pMainState->m_Dialog.m_retSelect)
		{
			UpdateJob(m_TextList[8], 120);
			//			g_pMainState->m_Map.LoadMap(16, 14, m_TextList[2].c_str());
			g_pMainState->m_Map.LoadMap(56, 16, m_TextList[2].c_str());
		}
		break;
	case 2:
	{
		if (!m_List.size())return;
		if (m_Stage == 3)
			AddNpcOne(&m_List[1]);
		AddNpcOne(&m_List[0], true);
	}
		break;
	case 3:
		m_NowNpc = g_pMainState->m_pNowSelect;
		g_pMainState->m_pNowSelect->Talk(m_TextList[13], this, -3, "确定", "取消");
		break;
	case -3:
		switch (m_Stage)
		{
		case 0://送信

		{
			m_NowNpc->Talk(m_TextList[7]);
			g_pMainState->m_TriggerObjMap.AddTask(this, 4, m_TextList[9]);
			UpdateJob(m_TextList[7]);
			m_Stage = 2;

		}
			break;
		case 1: //收集木材

		{
			m_NowNpc->Talk(m_TextList[6]);
			g_pMainState->m_TriggerObj.AddTask(m_TextList[4], m_TextList[2], this, 6);
			UpdateJob(m_TextList[6]);
			m_Stage = 3;
			AddNpcOne(&m_List[1]);

		}
			break;
		default:
			break;
		}
		break;
	case 4://设置NPC

	{
		cMyMap* p = &g_pMainState->m_Map;
		int num = p->m_numberOfNpc;
		//			num = 1;
		for (int i = 0; i < num; i++)
		{
			p->m_pNpc[i]->m_TaskTrigger.m_pTask = this;
			p->m_pNpc[i]->m_TaskTrigger.m_Stage = 5;
		}
	}
		break;
	case 5://回收NPC

	{
		g_pMainState->m_pNowSelect->Talk(m_TextList[10]);
		g_pMainState->m_Dialog.m_pObj = 0;
		g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect, true);
		if (g_pMainState->m_Map.m_numberOfNpc < 15)
		{
			g_pMainState->m_Map.RemoveAllNpc();
			UpdateJob(m_TextList[8]);
			SetJiangLi(10, true);
			g_pMainState->m_TriggerObjMap.ReMove(this, m_TextList[9]);
			g_pHeroObj->Talk(m_TextList[14]);
			m_Stage = 1;

			g_pMainState->m_TriggerObjMap.AddTask(this, 2, m_TextList[2]);

			m_HuanShu = 0;
		}
	}
		break;
	case 6:
	{
		if (3 != m_Stage)return;
		int lv = g_pCharacter->m_PcData.m_Lv;
		m_NowNpc = g_pMainState->m_pNowSelect;
		// 			int select = rand() % 10;
		// 			if (select == 0)
		// 			{
		// 				Process(7);
		// 			}
		// 			else
		{
			g_pMainState->m_Tags.Add(m_TextList[11]);
			for (int i = 0; i < 8; i++)
			{
				Add变身EnemyF(lv * 200, (ePetID)(20 + rand() % 10), -1, eMP_随机, m_TextList[12]);
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(7);
		}
	}
		break;
	case 7://桃树奖励
	{
		SetJiangLi(2);
		m_HuanShu += 1;
		if (m_HuanShu/* == 5*/)
		{
			RemoveNpc(m_NowNpc);
			m_NowNpc = g_pMainState->FindObjByName(m_TextList[3]);
			RemoveNpc(m_NowNpc);
			g_pMainState->m_TriggerObj.ReMove(this);
			AddTriggerDialog(0, 8);

			return;
		}
		UpdateJob(m_TextList[8], 120);
		m_Stage = 1;
	}
		break;
	case 8:
	{
		sTaskMapObj npc;
		//			SetNpc(npc,9,m_TextList[15], m_TextList[2], 139, 49, 28,1);
		SetNpc(npc, 9, m_TextList[15], m_TextList[2], 139, 89, 20, 1);
		UpdateJob(m_TextList[20]);
		g_pMainState->m_TriggerObjMap.AddTask(npc);
		AddNpcOne(&npc, false);
	}
		break;
	case 9:
		m_NowNpc = g_pMainState->m_pNowSelect;
		AddTriggerDialog(1, 10); break;
	case 10:
	{
		g_pMainState->m_Map.RemoveAllNpc();
		m_List.resize(2);
		// 			SetNpc(m_List[0],12,m_TextList[17], m_TextList[2], 56, 116, 83, 1);//虎翼
		// 			SetNpc(m_List[1],13,m_TextList[18], m_TextList[2], 49, 122, 80, 1);//蛇
		SetNpc(m_List[0], 12, m_TextList[17], m_TextList[2], 56, 119, 44, 1);//虎翼
		SetNpc(m_List[1], 13, m_TextList[18], m_TextList[2], 49, 126, 41, 1);//蛇
		AddTriggerObjMap(m_TextList[2], 11);
		//			g_pMainState->m_Map.RemoveNpc(m_NowNpc,true);
		g_pMainState->FindObj();
		UpdateJob(m_TextList[16]);
		Process(11);
	}
		break;
	case 11:AddNpc(); break;
	case 12:
	case 13:
	{
		int lv = g_pCharacter->m_PcData.m_Lv;
		m_NowNpc = g_pMainState->m_pNowSelect;
		//	sNpc* pNpc = (sNpc*)m_NowNpc->m_pIndex;
		if (stage == 12)
		{
			Add变身EnemyF(lv * 250, (ePetID)m_List[0].m_Npc.m_modeid, lv + 5, eMP_随机, m_TextList[17]);
		}
		else
		{
			Add变身EnemyF(lv * 250, (ePetID)m_List[m_List.size() - 1].m_Npc.m_modeid, lv + 5, eMP_随机, m_TextList[18]);
		}
		for (int i = 0; i < 7; i++)
		{
			Add变身EnemyF(lv * 200, (ePetID)(30 + rand() % 40), -1, eMP_随机, m_TextList[19]);
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(14);
	}
		break;
	case 14:
	{
		SetJiangLi(4, 1);
		RemoveNpc(m_NowNpc);
		if (!m_List.size())
		{
			m_List.resize(1);
			//				SetNpc( m_List[0],15,m_TextList[21], m_TextList[2], 1066, 120, 81, 1);
			SetNpc(m_List[0], 15, m_TextList[21], m_TextList[2], 1066, 138, 60, 1);
			AddTriggerObjMap(&m_List[0]);
			AddNpc();
		}
	}
		break;
	case 15:
		g_pMainState->m_pNowSelect->Talk(m_TextList[22], this, 16, "确定", "取消");
		break;
	case 16:
	{
		g_pMainState->m_Map.RemoveAllNpc();
		g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[22], this, 18);
		//			g_pMainState->m_Map.LoadMap(54, 4, m_TextList[23].c_str());
		g_pMainState->m_Map.LoadMap(96, 8, m_TextList[23].c_str());
		AddTriggerObjMap(m_TextList[23], 11);

		//			m_List.resize(20);
		// 			cObj obj;
		// 			obj.SetXY(28 * 20, g_pMainState->m_Map.m_pMap->m_Height - 14 * 20);
		// 			g_pMainState->m_FindPt.findAstart(&obj, 20 * 20, g_pMainState->m_Map.m_pMap->m_Height - 81 * 20);
		// 			int timenum = obj.m_AstartPathIndex / m_List.size();
		// 			for (int i = 0; i < m_List.size(); i++)
		// 			{
		// 				SetNpc(m_List[i],22,m_TextList[19], m_TextList[23], rand() % 40, obj.m_AstartPathVecs[obj.m_AstartPathIndex].x / 20, (g_pMainState->m_Map.m_pMap->m_Height - obj.m_AstartPathVecs[obj.m_AstartPathIndex].y) / 20);
		// 				obj.m_AstartPathIndex -= timenum;
		// 			}
		m_List2.resize(1);
		for (int i = 0; i < m_List2.size(); i++)
		{
			//				SetNpc(m_List2[i],21,m_TextList[24], m_TextList[23], 121, 43, 78, 1);
			SetNpc(m_List2[i], 21, m_TextList[24], m_TextList[23], 121, 122, 87, 1);
		}
		//			Process(11);
		AddNpc();

		vector<int> modeid;
		for (int i = 0; i < 57; i++)
			modeid.push_back(rand() % 40);
		StageSetSameNpc(modeid, m_TextList[23], 22, modeid.size(), m_TextList[19]);
	}
		break;
	case 18:g_pMainState->m_pNowSelect->Talk(m_TextList[5], this, 19, "确定", "取消");
		break;
		// 	case 19:
		// 		g_pMainState->m_Map.LoadMap(16, 14, m_TextList[2].c_str());
		// 		break;
	case 22: //小妖战斗

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		int lv = g_pCharacter->m_PcData.m_Lv;
		Add变身EnemyF(lv * 200, (ePetID)(m_NowNpc->GetModeID()));
		for (int i = 0; i < 7; i++)
		{
			Add变身EnemyF(lv * 180, (ePetID)(m_NowNpc->GetModeID()));
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(20);
	}
		break;
	case 20://小妖奖励

	{
		SetJiangLi(2);
		RemoveNpc(m_NowNpc);
	}
		break;
	case 21://大王战斗

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		int lv = g_pCharacter->m_PcData.m_Lv;
		Add变身EnemyF(lv * 300, (ePetID)m_NowNpc->GetModeID(), lv + 5, eMP_随机, m_NowNpc->m_TrueName.GetString());
		for (int i = 0; i < 9; i++)
		{
			Add变身EnemyF(lv * 280, (ePetID)(20 + rand() % 40));
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;

		AddTriggerFightSuccess(24);
	}
		break;
	case 24://
	{
		g_pMainState->m_Map.RemoveAllNpc();
		g_pMainState->m_Map.LoadMap(20, 20, "水路奖励");
		m_List.resize(20);
		StageSetSameNpc(1125, "水路奖励", 25, m_List.size(), "宝箱");
	}
		break;
	case 25:
	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		cTaskJiangLi jiangli;
		jiangli.Add(33, 27, 4);//彩果
		jiangli.AddHShouJue(2);//低兽决
		jiangli.SetExp(30, 8);
		jiangli.SetMoeny(25, 8);
		jiangli.AutoGetJiangLi();
		RemoveNpc(m_NowNpc);
		if (!m_List.size())
		{
			Process(23);
		}
	}
		break;
	case 23://BOSS奖励 

	{
		SetJiangLi(10/* * 5*/, true);
		RemoveNpc(m_NowNpc);
		g_pMainState->m_Channel.AddNewString(m_TextList[25]);
		g_pMainState->m_Tags.Add(m_TextList[25]);
	}
	case 1002:
		EndFB();
		break;
	default:
		break;
	}
}

