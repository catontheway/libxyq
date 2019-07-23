#include "_global.h"


cCursor::cCursor()
{
	m_Give = 0xCF1D211E;
	m_Normal = 0x535C1994; // 0x7596D42B;// 
	m_Forbid = 0x1733E33B;
	m_Attack = 0x1FBC5273;
	m_Magic = 0xB48A9B3D;
	m_Team = 406701913;
	m_Hande = 0x5A055B13;
	m_Trade = 0xB87E0F0C;
	m_Guard = 0xB352AE45;
	m_Grab = 0xC5750B15;
	m_No = 0xFC03AFF1;

	ccm::get()->pushWdf(string("光标") + "给予", 0xCF1D211E);
	ccm::get()->pushWdf(string("光标") + "普通", 0x535C1994);
	ccm::get()->pushWdf(string("光标") + "forbid", 0x1733E33B);
	ccm::get()->pushWdf(string("光标") + "攻击", 0x1FBC5273);
	ccm::get()->pushWdf(string("光标") + "施法", 0xB48A9B3D);
	ccm::get()->pushWdf(string("光标") + "组队", 406701913);
	ccm::get()->pushWdf(string("光标") + "hande", 0x5A055B13);
	ccm::get()->pushWdf(string("光标") + "交易", 0xB87E0F0C);
	ccm::get()->pushWdf(string("光标") + "guard", 0xB352AE45);
	ccm::get()->pushWdf(string("光标") + "grab", 0xC5750B15);
	ccm::get()->pushWdf(string("光标") + "No", 0xFC03AFF1);
}

bool cCursor::Init()
{
	m_FollowMode = false;
	m_Click.Load(0x0D98AC0A);
	ccm::get()->pushWdf(string("光标") + "鼠标", 0x0D98AC0A);
	m_Clickp.resize(10);
	for (int i = 0; i < 10; i++)
	{
		m_Clickp[i].Set(&m_Click);
		m_Clickp[i].m_NeedShow = false;
		m_Clickp[i].m_FrameGap = 5;
	}
	Set(m_Normal);
	return true;
}

bool cCursor::Show(long x, long y)
{
	cCanvas* pCanvas = &g_pMainState->m_Canvas;
	for (int i = 0; i < 10; i++)
	{
		if (m_Clickp[i].m_NeedShow)
		{
			pCanvas->Add(&m_Clickp[i], 0, true);
			if (m_Click.GetMaxFrame() == m_Clickp[i].GetFrame() + 1)
				m_Clickp[i].m_NeedShow = false;
		}
	}
	if (g_pMainState->Mouse.GetXDelta() != 0)
	{
		m_Data.SetX(x);
	}
	if (g_pMainState->Mouse.GetYDelta() != 0)
	{
		m_Data.SetY(y);
	}
	//if (m_Data.m_bMove)pCanvas->SetRedraw(m_Data.m_PreShowRect);
	pCanvas->Add(&m_Data, 1);
	return true;
}
int cCursor::SelectObj(int UserID, int Type, cObj*& pObj)
{
	int i = -1;
	int kk = 0;
	switch (Type)
	{
	case 0:   //对自己使用
	case 2:
	case 5:
//		return UserID;
	case 1:  //对已方使用
	case 3:
	case 6:
	case 9:
		if (UserID < 10)
		{
			kk = 0;
		}
		else kk = 10;
		break;
	case 4:  //对敌方使用
		if (UserID < 10)
		{
			kk = 10;
		}
		else kk = 0;
		break;
	default:
		ERRBOX(Type);
		return -1;
	}
	for (i = kk; i < 10 + kk; i++)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			if (g_pMainState->m_FightWorkList[i].m_pObj->isPointOn(g_xMouse, g_yMouse))
			{
				if (Type == 9)
				{
					if (i == UserID)
					{
						continue;
					}
				}

				if (pObj)//把上一个取消高亮
				{
					pObj->m_TrueName.SetColor(RGB(0, 255, 0));
					pObj->SetShine(false);
				}
				pObj = g_pMainState->m_FightWorkList[i].m_pObj;
				pObj->m_TrueName.SetColor(RGB(255, 0, 0));
				pObj->SetShine(true);
				break;
			}
		}
	}
	if (i == 10 + kk)//如果没有选中任何对象,取消之前的高亮
	{
		if (pObj)
		{
			pObj->m_TrueName.SetColor(RGB(0, 255, 0));
			pObj->SetShine(false);
			pObj = 0;
		}
	}
	else
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
			pObj->m_TrueName.SetColor(RGB(0, 255, 0));
			pObj->SetShine(false);
			pObj = 0;
			return i;
		}
	}
	return -1;
}

bool cCursor::Process()
{

	////X键按下
	//if (g_pMainState->Keyboard.GetKeyState(DIK_X))
	//{
	//	g_pMainState->Keyboard.SetLock(DIK_X);
	//	Set(m_Trade);
	//}
	//T键按下
// 	if (g_pMainState->Keyboard.GetKeyState(DIK_T))
// 	{
// 		g_pMainState->Keyboard.SetLock(DIK_T);
// 		Set(m_Team);
// 	}
//	//A键按下
// 	if (g_pMainState->Keyboard.GetKeyState(DIK_A))
// 	{
// 		g_pMainState->Keyboard.SetLock(DIK_A);
// 		if (g_pMainState->m_GlobalButton[9] != 3)
// 		{
// 			g_pMainState->m_GlobalButton[9] = 3;
// 		}
// 		else
// 		{
// 			g_pMainState->m_GlobalButton[9] = 0;
// 		}
// 	}
	if (g_pMainState->Keyboard.GetKeyState(DIK_G))
	{
		g_pMainState->Keyboard.SetLock(DIK_G);
		Set(m_Give);
		return true;
	}
	if (CheckRB())return true;
	if (!g_pMainState->GetLockMouse())return true;



	static int time = 0; //记录鼠标按下的时间

	if (g_xMouse < 0 || g_yMouse < 0)return false;
	int xWorldMouse = g_xMouse + g_pMainState->m_Map.m_pMap->GetXCenter() - g_half320;
	int yWorldMouse = g_yMouse + g_pMainState->m_Map.m_pMap->GetYCenter() - g_half240;

	if (g_pMainState->_autoGhost)
	{
		return true;
	}

	//是否点在NPC上
	cObj*  pPc2 = g_pMainState->GetObjPointAt(xWorldMouse, yWorldMouse);
	g_pMainState->m_pNowSelect = pPc2;
	if (pPc2)
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
			pPc2->SetShine(false);
			if (m_Give == m_Data.m_NowID)
			{
				Set(m_Normal);
				g_pMainState->m_InterfaceGive.SetTarget(pPc2);
				return true;
			}
			if (m_Normal == m_Data.m_NowID)
			{
				string name = g_pMainState->m_pNowSelect->m_TrueName.GetString();
				if (!g_pMainState->m_TriggerObj.Process(name))
				{
					if (name.size() && pPc2->m_TaskTrigger.m_pTask)
					{
						pPc2->m_TaskTrigger.m_pTask->Process(pPc2->m_TaskTrigger.m_Stage);
					}
					else
					{
						if (pPc2->m_bHaveScript)
						{
							pPc2->m_Script.Process(pPc2);
						}
						else if (pPc2->GetShow())
						{
							bool isFound = false;
							const auto& fs = g_pMainState->m_Friend._friends;
							forr(fs, i)
							{
								if (pPc2 == fs[i].obj)
								{
									isFound = true;
								}
							}
							if (!isFound)
							{
								// pPc2->Talk(g_pMainState->m_TaskNormal.getNews());
							}
						}
					}
				}
			}
		}
		else
		{
			pPc2->SetShine(true);
		}
		return true;
	}


	if (!pPc2)
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON) || m_FollowMode)
		{
			time = 0;

			if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
			{
				g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
				m_FollowMode = false;

				if (g_pMainState->m_Map.CheckAlong(g_pHeroObj->GetX(), g_pHeroObj->GetY(), xWorldMouse, yWorldMouse))
				{
					g_pHeroObj->m_AstartPathIndex = -1;
					g_pHeroObj->setNextTargetOnAstart(xWorldMouse, yWorldMouse);
				}
				else
				{
					g_pMainState->m_FindPt.findAstart(g_pHeroObj, xWorldMouse, yWorldMouse);
				}
			}
			else
			{
				m_FollowTime += 1;
				//鼠标点击效果
				if (m_FollowTime > 6)
				{
					m_FollowTime = 0;
					if (abs(g_pHeroObj->GetX() - xWorldMouse) > 48 || abs(g_pHeroObj->GetY() - yWorldMouse) > 36)
					{
						g_pHeroObj->m_AstartPathIndex = -1;
						g_pHeroObj->setNextTargetOnAstart(xWorldMouse, yWorldMouse);

					}
					else
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			for (int i = 0; i < 10; i++)
			{
				if (!m_Clickp[i].m_NeedShow)
				{
					m_Clickp[i].m_NeedShow = true;
					m_Clickp[i].m_x = xWorldMouse;
					m_Clickp[i].m_y = yWorldMouse;
					m_Clickp[i].SetFrame帧(0);
					m_Clickp[i].m_StepUpdate = false;
					break;
				}
			}
			return true;
		}
		else if (m_FollowMode == false)
		{
			if (g_pMainState->Mouse.GetPureButtonState(MOUSE_LBUTTON))
			{
				time += 1;
				if (time == 60)
				{
					m_FollowMode = true;
				}
				return true;
			}
		}
	}
	return true;
}

bool cCursor::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	if (m_Data.m_NowID != m_Normal)
	{
		g_pMainState->m_Canvas.SetRedrawAll();
		Set(m_Normal);
	}
	return true;
}
