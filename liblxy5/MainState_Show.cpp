#include "_global.h"


bool CMainState::SortShow()
{
	cObj* pObj;
	cWasFile* pFile;
	//int charpos = m_FightList[m_HeroID].m_pData->GetX();
	for (int i = 0; i < m_NumShow; i++)
	{
		switch (m_ShowTurnType[i])
		{
		case 0:
			pObj = (cObj*)m_pShowTurn[i];
			m_PosYList[i] = pObj->m_pShowData[0]->m_PreShowRect.bottom;
			break;
		case 1:

		{
			pFile = (cWasFile*)m_pShowTurn[i];
			switch (pFile->m_PosType)
			{
			case 1:
				m_PosYList[i] = pFile->m_PreShowRect.bottom;
				break;
			case 0:
				m_PosYList[i] = 0;//显示在最下方
				break;
			case 2:
				m_PosYList[i] = 480;//显示在最下方
				break;
			}
		}
			break;
		}
	}
	for (int a = 0; a < m_NumShow - 1; a++)
		for (int b = a + 1; b<m_NumShow; b++)
		{
		if (m_PosYList[a]>m_PosYList[b])//前数大于后数
		{
			swap(m_PosYList[a], m_PosYList[b]);
			swap(m_pShowTurn[a], m_pShowTurn[b]);
			swap(m_ShowTurnType[a], m_ShowTurnType[b]);
		}
		}//排序结果，当前位置Y小的在前。	
	return true;
}





bool CMainState::ProcessInterface()
{
	m_Tags.Process();
	//	m_Tag2.Process();

// 	if (Keyboard.GetKeyState(DIK_M))
// 	{
// 		Keyboard.SetLock(DIK_M);//
// 		g_pMainState->m_GlobalButton[16] = !g_pMainState->m_GlobalButton[16];
// 		if (g_pMainState->m_GlobalButton[16])
// 			g_pMainState->m_Mp3.Stop();
// 		else
// 			g_pMainState->m_Mp3.Play();
// 	}
// 	if (Keyboard.GetKeyState(DIK_N))
// 	{
// 		Keyboard.SetLock(DIK_N);//
// 		g_pMainState->m_GlobalButton[17] = !g_pMainState->m_GlobalButton[17];
// 	}

//	if (Keyboard.GetKeyState(DIK_3))
//	{
// 		Keyboard.SetLock(DIK_3);
// 		sItem2 weappon;
// 		weappon.m_Num = 1;
// 		for (int i = 0; i < 29; i++)
// 		{
// 			weappon.Set(13, i);
// 			m_ItemManage.AutoItemProperty(&weappon, 100,1);
// 			m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &weappon);
// 		}
//	}
	//if (Keyboard.GetKeyState(DIK_4))
	//{
	//	Keyboard.SetLock(DIK_4);
	//	int nextid;
	//	if (!g_pCharacter->m_PCData.m_bUseCard)
	//		nextid = 51;
	//	else
	//	{
	//		nextid = g_pCharacter->m_PCData.m_pCardPetData->GetData()->m_ID;
	//		nextid += 1;
	//		if (nextid > 217)nextid = 0;
	//	}
	//	sItem2 item2;
	//	item2.Set(26, nextid);
	//	m_ItemManage.UseItem26(&item2, m_HeroID);
	//}
	//
	////增加房屋规模
	//if (Keyboard.GetKeyState(DIK_M))
	//{
	//	Keyboard.SetLock(DIK_M);
	//	m_FangWu.SetGuiMo(m_FangWu.GetGuiMo() + 1);
	//	m_FangWu.GoIn();
	//	return true;
	//}

#ifndef TESTDEBU
	//	static int cardid = 0;

	//加钱
	//	if (Keyboard.GetKeyState(DIK_0))
	//	{
	//		Keyboard.SetLock(DIK_0);
	//		g_pCharacter->m_PCData.m_Money[0] += 1000000;
	//		return true;
	//	}
	//	//触发剧情
	// 	if (Keyboard.GetKeyState(DIK_H))
	// 	{
	// 		Keyboard.SetLock(DIK_H);
	// 	
	// 		cct::get()->PK();
	// 		return true;
	// 	}
	//强制战斗胜利
// 	if (Keyboard.GetKeyState(DIK_F12))
// 	{
// 		Keyboard.SetLock(DIK_F12);
// 		m_pFightState->EscapeFight();
// 		return true;
// 	}
	//加经验
	//	if (Keyboard.GetKeyState(DIK_9))
	//	{
	//		Keyboard.SetLock(DIK_9);
	//		g_pCharacter->m_PCData.EXP += g_pCharacter->m_PcData.m_Lv * g_pCharacter->m_PcData.m_Lv * 100 + 1000;
	//		return true;
	//	}
#endif

	if (Keyboard.GetKeyState(DIK_RETURN))// && Keyboard.GetKeyState(DIKEYBOARD_LMENU))
	{//切换全屏
		Keyboard.SetLock(DIK_RETURN);
		//m_Canvas.SetRedrawAll();
		g_bFillScreen = !g_bFillScreen;
		SetFullScreen2(g_bFillScreen);
		return true;
	}

	//C键按下
	if (Keyboard.GetKeyState(DIK_C))
	{
		Keyboard.SetLock(DIK_C);
		m_Accelator.setCharacter(g_pCharacter);
		m_Accelator.OnOff(!m_Accelator.m_NeedShow);
		return true;
	}

#if _DEBUG
	//主角标准化
	if (Keyboard.GetKeyState(DIK_ESCAPE))//
	{
		Keyboard.SetLock(DIK_ESCAPE);
//		m_pFightState->EscapeFight();
		m_pFightState->SuccessFight();
//		cct::get()->playerNormalize(g_pCharacter->m_PcData.m_Lv);
		return true;
	}
#endif

	//好友界面
	if (Keyboard.GetKeyState(DIK_F))
	{
		Keyboard.SetLock(DIK_F);
		//	m_Friend.OnOff(!m_Friend.m_NeedShow);
		_uiDescription.OnOff();
		return true;
	}

	if (Keyboard.GetKeyState(DIK_R))
	{
		Keyboard.SetLock(DIK_R);
	//	g_pMainState->m_InterfaceFB.OnOff(!g_pMainState->m_InterfaceFB.m_NeedShow);
		return true;
	}

	// 送装备
	if (Keyboard.GetKeyState(DIK_P))
	{
		Keyboard.SetLock(DIK_P);
		_uiComPet.OnOff();
		return true;
	}
	//R键按下
// 		if (Keyboard.GetKeyState(DIK_R))
// 		{
// 			Keyboard.SetLock(DIK_R);
// 			m_InterfaceFB.OnOff(!m_InterfaceFB.m_NeedShow);
// 			return true;
// 		}
	if (g_StateType == STATE_MAIN || !m_pFightState || m_pFightState->m_turn != 0)
	{
		//Q  任务
		if (Keyboard.GetKeyState(DIK_Q))
		{
			Keyboard.SetLock(DIK_Q);
			m_Job.OnOff(!m_Job.m_NeedShow);
			return true;
		}
	}
	//~  技能
	if (Keyboard.GetKeyState(DIK_B))
	{
		Keyboard.SetLock(DIK_B);
		m_InterfaceJiNeng.setCharator(g_pCharacter);
		m_InterfaceJiNeng.OnOff(!m_InterfaceJiNeng.m_NeedShow);
		return true;
	}


 	if (g_StateType == STATE_MAIN)
 	{
 		//变身
// 		if (Keyboard.GetKeyState(DIK_F10))
// 		{
// 			Keyboard.SetLock(DIK_F10);
// 			cct::get()->useCard();
// 			return true;
//			g_pCharacter->m_PCData.m_JinJieNum.m_PositionID = 1;
//			g_pCharacter->UseCard(cardid);
//			
//			m_FightList[m_HeroID].m_pData->Reset();
//			m_FightList[m_HeroID].m_pData->Set(POS_STAND);
//	
//			if (++cardid > 161)
//			{
//				cardid = 0;
//			}
//		}

		//E  道具
		if (Keyboard.GetKeyState(DIK_E))
		{
			Keyboard.SetLock(DIK_E);
			m_InterfaceItem.OnOff(!m_InterfaceItem.m_NeedShow);
			return true;
		}

		//  状态
		if (Keyboard.GetKeyState(DIK_W))
		{
			Keyboard.SetLock(DIK_W);
			m_State.SetCharacter(g_pCharacter);
			m_State.OnOff(!m_State.m_NeedShow);
			return true;
		}
		//O   宠物
		if (Keyboard.GetKeyState(DIK_O))
		{
			Keyboard.SetLock(DIK_O);
			g_pMainState->m_InterfacePet.setCharactor();
			m_InterfacePet.OnOff(!m_InterfacePet.m_NeedShow);
			return true;
		}

	}


	for (int i = c_InterfaceShowNum - 1; i >= 0; i--)
	{
		if (m_isMouseOnMap)
		{
			if (0 != m_Interface[i])
			{
				if (_autoGhost)
				{
					if (m_Interface[i] != &m_InterfaceSystem)
					{
						continue;
					}
				}
				m_Interface[i]->ProcessInput();
			}
		}
	}
	m_PCHead.ProcessInput();
	if (g_StateType == STATE_MAIN)
	{
		m_InterfaceDoor.ProcessInput();
	}
	else
	{
		m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
	}


	if (g_StateType != STATE_FIGHT)
	{
		if (Keyboard.GetKeyState(DIK_SPACE))
		{
			Keyboard.SetLock(DIK_SPACE);

// 			if (m_Map.m_MapType < 1)
// 			{
 				int r = rand() % 129;
// 				Q_LOG("%d", r);
 				m_FightWorkList[rand() % m_InterfaceTeam.getLeaveBegin()/*m_InterfaceTeam.m_LeaveBegin*/].m_pObj->saySkill(toString(" #%d", r));
// 			}
// 			else
// 			{
// 				m_TaskNormal.Process(1);
// 			}
		}
	}

	m_Menu.ProcessInput();

	return true;
}



bool CMainState::ShowInterface()
{
	cCanvas* pCanvas = &m_Canvas;
	m_PCHead.Show(pCanvas);

	//显示菜单
	if (g_StateType == STATE_MAIN)
	{
		m_InterfaceDoor.Show(pCanvas);
		m_Menu.Show(&m_Canvas);
	}
	else if (g_StateType == STATE_FIGHT)
	{
		m_Menu.Show(&m_Canvas);
	}

	m_Channel.Show(pCanvas);
	return true;
}






bool CMainState::InterfaceSetShow(cInterfaceFather* p, bool NeedShow)
{
	if (p->m_NeedShow == NeedShow)return true; //如果已经存在 直接退出
	if (NeedShow)
	{
		for (int i = 0; i < c_InterfaceShowNum; i++)
		{
			if (m_Interface[i] == p)
			{
				p->m_NeedShow = true;
				return true;
			}
			if (m_Interface[i] == 0)
			{
				p->m_NeedShow = true;
				m_Interface[i] = p;
				return true;
			}
		}
		//如果列表已满,则把最后面的一个退出列表
		m_Interface[0]->OnOff(false);
		m_Interface[c_InterfaceShowNum - 1] = p;
		m_Interface[c_InterfaceShowNum - 1]->m_NeedShow = true;

	}
	else  //退出列表
	{
		for (int i = 0; i < c_InterfaceShowNum; i++)
		{
			if (m_Interface[i] == p)
			{
				p->m_NeedShow = false;
				int k = i;
				for (; k < c_InterfaceShowNum - 1; k++)
				{
					m_Interface[k] = m_Interface[k + 1];
				}
				m_Interface[k] = 0;
				return true;
			}
		}
		p->m_NeedShow = false;
	}
	return true;

}





bool CMainState::ShowInterface2()
{
	if (m_Cursor.m_Data.m_NowID == m_Cursor.m_Normal)
		for (int i = 0; i < c_InterfaceShowNum; i++)
		{
		if (m_Interface[i])
			m_Interface[i]->Show(&m_Canvas);
		}
	m_Tags.Show(&m_Canvas);
	m_Tag1.Show(&m_Canvas);


	if (g_xMouse < 0 || g_yMouse < 0 || g_xMouse> g_640 || g_yMouse > g_480)
	{
		if (ShowCursor(true) > 1)
			ShowCursor(false);
	}
	else
	{
		if (ShowCursor(false) < -1)
			ShowCursor(true);
		m_Cursor.Show(g_xMouse, g_yMouse);
	}
	return true;
}



void CMainState::ClearInterfaceSetShow()
{
	for (int i = 0; i < c_InterfaceShowNum; i++)
	{
		if (m_Interface[i])
		{
			m_Interface[i]->m_NeedShow = false;
			m_Interface[i] = 0;
		}
	}
}



