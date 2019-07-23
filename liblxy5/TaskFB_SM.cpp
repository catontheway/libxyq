#include "_global.h"

void cTaskFB::ProcessSM(int stage)
{
	int lv = g_pCharacter->m_PcData.m_Lv;
	switch (stage)
	{
	case 0:
	{
		m_Stage = 0;
		AddTriggerObj(m_TextList[1], m_TextList[0], 1);
		AddTriggerObjMap(m_TextList[3], 4);
		// 			StageSetSameNpc(2001, m_TextList[3], 5, 15,m_TextList[8]);
		// 			StageSetSameNpc2(1125, m_TextList[3], -5, 23, m_TextList[14]);
		StageSetSameNpc(2001, m_TextList[3], 5, 30, m_TextList[8]);
		StageSetSameNpc2(1125, m_TextList[3], -5, 27, m_TextList[14]);
	}
		break;
	case 1:
	{
		g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, 2, "确定", "取消");
	}
		break;
	case 2:
		if (g_pMainState->m_Dialog.m_retSelect)return;
	case 3:
		switch (m_Stage)
		{
		case 0:
			//			g_pMainState->m_Map.LoadMap(24, 31, m_TextList[3].c_str());
			g_pMainState->m_Map.LoadMap(99, 26, m_TextList[3].c_str());
			UpdateJob(m_TextList[9]);
			break;
		case 1:
			g_pMainState->m_Map.LoadMap(45, 25, m_TextList[4].c_str());
			UpdateJob(m_TextList[12]);
			break;
		case 2:
			//			g_pMainState->m_Map.LoadMap(8, 11, m_TextList[5].c_str());
			g_pMainState->m_Map.LoadMap(113, 15, m_TextList[5].c_str());
			break;
		case 3:
			g_pMainState->m_Map.LoadMap(65, 56, m_TextList[6].c_str());
			break;
		case 4:
			g_pMainState->m_Map.LoadMap(8, 11, m_TextList[7].c_str());
			break;
		}
		break;
	case 4:AddNpc(); break;
	case -5:
		RemoveNpc(g_pMainState->m_pNowSelect);
		switch (rand() % 4)
		{
		case 0:SetJiangLi(1, true, 50, 0, 0); break;
		case 1:SetJiangLi(1, true, 0, 0, 50); break;
		case 2:
		{
			g_pCharacter->m_PcData.m_HP /= 2;
			g_pCharacter->m_PcData.m_MP /= 2;
			g_pMainState->m_PCHead.UpdatePcHp();
			g_pMainState->m_PCHead.UpdatePcMp();
			AddTag(m_TextList[15]);
		}
			break;
		default://战斗
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			int enemynum = g_pMainState->AtutoGetEnemyNum();
			for (int i = 0; i < enemynum; i++)
			{
				Add变身EnemyF(lv * 200, (ePetID)(35 + rand() % 40));
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(-6);
		}
			return;
		}
		//		if (!(m_List.size()) && (!m_List2.size()))
		if (m_List.size() <= 29 && m_List2.size() <= 25)
		{
			m_Stage = 1;
			AddTriggerObjMap(m_TextList[4], 4);
			m_List2.resize(0);
			m_List.resize(1);
			SetNpc(m_List[0], 7, m_TextList[10], m_TextList[4], 1084, 48, 31);
			m_HuanShu = 1;
			ProcessSM(3);
		}
		break;
	case -6://宝箱战斗胜
	{
		RemoveNpc(m_NowNpc);
		SetJiangLi(1);
		//			if (!(m_List.size()) && (!m_List2.size()))
		if (m_List.size() <= 14 && m_List2.size() <= 20)
		{
			m_Stage = 1;
			AddTriggerObjMap(m_TextList[4], 4);
			m_List2.resize(0);
			m_List.resize(1);
			SetNpc(m_List[0], 7, m_TextList[10], m_TextList[4], 1084, 48, 31);
			m_HuanShu = 1;
			ProcessSM(3);
		}
	}
		break;
	case 5://玄武仙人
		m_NowNpc = g_pMainState->m_pNowSelect;
		m_NowNpc->Answer(this, 6);
		break;
	case 6:

	{
		if (g_pMainState->m_Dialog.m_retSelect == g_pMainState->m_Dialog.m_Question.answer)
		{
			RemoveNpc(m_NowNpc);
			SetJiangLi(2, true, 0);
		}
		else
		{
			m_NowNpc->Talk(g_pMainState->m_Dialog.GetTrueSelect());
		}
		//			if (!(m_List.size())&& (!m_List2.size()))
		if (m_List.size() <= 14 && m_List2.size() <= 20)
		{
			m_Stage = 1;
			m_Stage2 = 0;
			AddTriggerObjMap(m_TextList[4], 4);
			m_List2.resize(0);
			m_List.resize(1);
			SetNpc(m_List[0], 7, m_TextList[10], m_TextList[4], 1084, 48, 31);
			m_HuanShu = 1;
			ProcessSM(3);
		}
	}
		break;
	case 7:

	{
		if (m_Stage2 > 0)
		{
			//				g_pMainState->m_pNowSelect->Talk(m_TextList[24]); 
			//				return;
		}
		g_pMainState->m_pNowSelect->Talk(m_TextList[11]);
		m_Stage2 = 1;
		sItem2 item;
		item.m_Num = 1;
		item.Set(28, 21);
		int x, y;
		g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[4]);
		item.m_Property.resize(2);
		item.m_Property[0] = x;
		item.m_Property[1] = y;
		g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
	}
		break;
	case 8://挖宝

	{
		if (g_pMainState->m_Map.m_MapName != m_TextList[4])
		{

			return;
		}
		sItem2* pItem = g_pCharacter->m_PcData.GetItem(g_pMainState->m_InterfaceItem.m_NowSelect);
		if (abs(g_pMainState->m_InterfaceDoor.m_HeroX - pItem->m_Property[0]) < 7)
			if (abs(g_pMainState->m_InterfaceDoor.m_HeroY - pItem->m_Property[1]) < 7)
			{
			m_Stage2 = 0;
			int rat = rand() % 100;
			if (rat < 20)
			{
				SetJiangLi(2, true);
				m_HuanShu += 7;// 1;
				if (m_HuanShu > 7)
				{
					m_HuanShu = 0;
					AddTriggerObjMap(m_TextList[5], 4);
					m_Stage = 2;
					m_List.resize(8);
					int x, y;
					g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[5]);
					for (int i = 0; i < 8; i++)
					{
						g_pMainState->m_Map.AutoGetPos(x, y);
						SetNpc(m_List[i], 12, m_TextList[16 + i], m_TextList[5], 41, x, y);
					}
					UpdateJob(m_TextList[25]);
					Process(3);
					AddTag(m_TextList[25]);
				}
			}
			else
			{
				Process(9);
				UpdateJob(m_TextList[12]);
			}
			pItem->m_Num = 0;
			return;
			}
		ostringstream oss;
		oss << "地点:" << pItem->m_Property[0] << " " << pItem->m_Property[1];
		AddTag(oss.str());
	}
		break;
	case 9: //挖宝战斗

	{
		m_NowNpc = g_pMainState->m_pNowSelect;

		Add变身EnemyF(lv * 99999, e雨师, 5, eMP_随机, m_TextList[13]);
		for (int i = 0; i < 5; i++)
		{
			Add变身EnemyF(lv * 200, (ePetID)(35 + rand() % 40));
		}
		g_StateType = STATE_FIGHT;
		SetMusicFB();
		AddTriggerFightTurn(10);
		AddTriggerFightSuccess(11);
	}
		break;
	case 10:

	{
		if (!g_pMainState->m_FightWorkList[10].isExist)g_pMainState->m_pFightState->EscapeFight();
		int num = g_pMainState->GetLiveNum(10, 20);
		cAI& ai = g_pMainState->m_AI;// .m_AttackAI;
		if (1 == num)
		{
			g_pMainState->m_pFightState->SuccessFight();
		}
		else
		{
			ai.defense(10);
		}
	}
		break;
	case 11:

	{
		SetJiangLi(3, true);
		m_HuanShu += 7;// 1;
		if (m_HuanShu > 7)
		{
			m_HuanShu = 0;
			AddTriggerObjMap(m_TextList[5], 4);
			m_Stage = 2;

			int x, y;
			g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[5]);
			m_List.resize(4);
			for (int i = 0; i < 4; i++)
			{
				g_pMainState->m_Map.AutoGetPos(x, y);
				SetNpc(m_List[i], 12, m_TextList[16 + i], m_TextList[5], 41, x, y);
			}
			m_List2.resize(4);
			for (int i = 0; i < 4; i++)
			{
				g_pMainState->m_Map.AutoGetPos(x, y);
				SetNpc(m_List2[i], 12, m_TextList[20 + i], m_TextList[5], 41, x, y);
			}
			UpdateJob(m_TextList[25]);
			Process(3);
			AddTag(m_TextList[25]);
		}
	}
		break;
	case 12:

	{
		m_NowNpc = g_pMainState->m_pNowSelect;

		Add变身EnemyF(lv * 260, (ePetID)(m_NowNpc->GetModeID()), -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
		cPropertyData* Pet;
		for (int i = 0; i < 2; i++)
		{
			Pet = Add变身EnemyF(lv * 200, e星灵仙子, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			Pet->DmgAdd.d2 = 80;
			Pet->DmgAddOfMagic.d2 = 80;
		}
		for (int i = 0; i < 5; i++)
		{
			Add变身EnemyF(lv * 160, e如意仙子);
		}
		SetMusicFB();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(13);
	}
		break;
	case 13:

	{
		bool find = false;
		string name = m_NowNpc->m_TrueName.GetString();
		for (int i = 0; i < m_List.size(); i++)
		{
			if (name == m_List[i].m_Npc.m_name)
			{
				if (i == 0)
				{
					RemoveNpc(m_NowNpc);
					find = true;
					break;
				}
			}
		}
		if (!find)
			for (int i = 0; i < m_List2.size(); i++)
			{
			if (name == m_List2[i].m_Npc.m_name)
			{
				if (i == 0)
				{
					RemoveNpc(m_NowNpc);
					find = true;
					break;
				}
			}
			}
		// 			   return;
		// 			   if (!find)
		// 			   if ((!m_List.size()) && (!m_List2.size()))
		// 			   {
		// 
		// 			   }
		// 			   else return;
	}
	case -13:

	{//白虎门结束
		m_Stage = 3;
		AddTriggerObjMap(m_TextList[6], 4);
		m_List.resize(23);
		m_List2.resize(4);
		int x, y;
		g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[6]);
		for (int i = 0; i < 4; i++)
		{
			g_pMainState->m_Map.AutoGetPos(x, y);
			SetNpc(m_List2[i], 14, m_TextList[3 + i], m_TextList[6], 49, x, y);
		}
		for (int i = 0; i < 23; i++)
		{
			g_pMainState->m_Map.AutoGetPos(x, y);
			if (i == 14)//BUG 两个玄武门
				SetNpc(m_List[i], 14, m_TextList[26 + 15], m_TextList[6], 49, x, y);
			else
				SetNpc(m_List[i], 14, m_TextList[26 + i], m_TextList[6], 49, x, y);
		}
		UpdateJob(m_TextList[53]);
		g_pMainState->m_Tags.Add(m_TextList[53]);
		Process(3);
	}
		break;
	case 14:

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		Add变身EnemyF(lv * 280, (ePetID)(m_NowNpc->GetModeID()), lv + 5, eMP_随机, m_NowNpc->m_TrueName.GetString());
		cPropertyData* Pet;
		for (int i = 0; i < 2; i++)
		{
			Pet = Add变身EnemyF(lv * 250, e星灵仙子);
			Pet->DmgAdd.d2 = 30;
			Pet->DmgAddOfMagic.d2 = 30;
		}
		sAddPoint addpoint;
		for (int i = 0; i < 5; i++)
		{
			Add变身EnemyF(lv * 200, e天兵);
		}
		g_StateType = STATE_FIGHT;
		SetMusicFB();
		AddTriggerFightSuccess(15);
	}
		break;
	case 15:

	{
		RemoveNpc(m_NowNpc);
		SetJiangLi(3);
		//			if (!m_List2.size())
		{
			ClearNpc();
			m_List.resize(1);
			SetNpc(m_List[0], 16, m_TextList[50], m_TextList[6], 2000, 65, 57, 1);
			m_List[0].m_Npc.SetRanse(0, 4, 3);
			m_List[0].m_Npc.weapontype = 0;
			m_List[0].m_Npc.weaponid = 24;
			AddNpc();
			UpdateJob(m_TextList[51]);
			AddTag(m_TextList[51]);
		}
	}
		break;
	case 16://神密剑客  0 4 3 0

	{
		m_NowNpc = g_pMainState->m_pNowSelect;

		cPropertyData* Pet;
		Pet = AddPCEnemyF(lv * 300, 0, 0, lv + 5, eMP_大唐官府, m_NowNpc->m_TrueName.GetString(), m_List[0].m_Npc.weapontype, m_List[0].m_Npc.weaponid);
		Pet->m_XiuLian.AddXiuLianLv(30, eXLATK);
		Pet->m_RanSe.m_ranse[0].Set(2, 3, 3, 0);
		g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);

		for (int i = 0; i < 7; i++)
		{
			Pet = AddPCEnemyF(lv * 200, 0, 0, lv, eMP_大唐官府, "剑客影子", m_List[0].m_Npc.weapontype, m_List[0].m_Npc.weaponid);
			Pet->m_XiuLian.AddXiuLianLv(30, eXLATK);
			Pet->m_RanSe.m_ranse[0].Set(2, 3, 3, 0);
			g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
		}
		g_StateType = STATE_FIGHT;
		SetMusicFB();
		AddTriggerFightSuccess(17);
	}
		break;
	case 17://

	{
		m_Stage = 4;
		m_List[0].m_Npc.weaponid = -1;
		m_List[0].m_Npc.weapontype = -1;
		//			m_List.resize(50);
		StageSetSameNpc(1125, m_TextList[7], 18, 40, m_TextList[14]);

		// 			m_List.resize(40);
		// 			for (int i = 0; i < m_List.size(); i++)
		// 			{
		// 				SetNpc(m_List[i], 18, "宝箱", "宝库", 1125, 15, 10);
		// 			}
		// 			AddNpc();

		AddTriggerObjMap(m_TextList[7], 4);
		Process(3);
		SetJiangLi(10 * 5);
		AddTag(m_TextList[52]);
		UpdateJob(m_TextList[52]);
	}
		break;
	case 18:

	{
		m_NowNpc = g_pMainState->m_pNowSelect;
		cTaskJiangLi jiangli;
		//			jiangli.SetBaoShi(20);//宝石
		//			jiangli.Add(3,27,5,3); //66
		jiangli.Add(33, 27, 4);//彩果
		jiangli.AddHShouJue(2);//低兽决
		//			jiangli.Add(38, 27,10, 4);//强化石
		jiangli.SetExp(30, 8);
		jiangli.SetMoeny(25, 8);
		jiangli.AutoGetJiangLi();
		RemoveNpc(m_NowNpc);
		if (m_List.size() < 2)
			Process(1002);
	}
		break;
	case 1002:
		EndFB();

		break;
	}
}
