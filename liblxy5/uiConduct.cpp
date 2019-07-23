#include "_global.h"



bool cInterfaceConduct::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;

	m_Title.SetColor(RGB(255, 255, 255));
	m_Title.SetString("指挥");
	m_Back.Load(0x1DF7B97D);//0xFBEC073F // 0xCC7BC6C6);
	m_Back.SetStatic(true);
	m_Buttonp.resize(3/*7*/);
	m_tButtonp.resize(3/*7*/);
	for (int i = 0; i < 3/*7*/; i++)
	{
		m_Buttonp[i].Set(&g_pMainState->m_Button2);
		m_Buttonp[i].m_bStatic = true;
		m_tButtonp[i].SetColor(RGB(255, 255, 255));
		m_tButtonp[i].SetString(i == 0 ? "清空" : (i == 1 ? "集火" : "封印"));// "指定目标"
	}
//	m_tButtonp[6].SetString("防御");
// 	m_tName.resize(7);
// 	for (int i = 0; i < 7; i++)
// 	{
// 		m_tName[i].SetColor(RGB(0, 200, 0));
// 	}
// 	m_tName[5].SetString("全体");
// 	m_tName[6].SetString("全体");
// 
// 	m_tTargetName.resize(5);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		m_tTargetName[i].SetColor(RGB(255, 0, 0));
// 	}

	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}

bool cInterfaceConduct::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(x, y);
	m_Title.SetXCenter(m_Back.GetX() + 80/*100*/);
	m_Title.SetY(m_yPos + 4);
	m_Title.UpdateXCenter();
// 	for (int i = 0; i < m_tName.size(); i++)
// 	{
// 		if (i < 5)
// 		{
// 			m_tName[i].SetXY(m_xPos + 15, m_yPos + 26 + (i + 2) * 30);
// 			m_Buttonp[i].SetXY(m_xPos + 68, m_yPos + 24 + (i + 2) * 30);
// 		}
// 		else
// 		{
// 			m_tName[i].SetXY(m_xPos + 15, m_yPos + 26 + (i - 5) * 30);
// 			m_Buttonp[i].SetXY(m_xPos + 68, m_yPos + 24 + (i - 5) * 30);
// 		}
// 
// 
// 		m_tButtonp[i].SetXCenter(m_Buttonp[i].GetX() + m_Buttonp[i].GetShowWidth() / 2);
// 		m_tButtonp[i].SetY(m_Buttonp[i].GetY() + 3);
// 		m_tButtonp[i].UpdateXCenter();
// 	}

	forv (m_Buttonp, i)
	{
		m_Buttonp[i].SetXY(m_Back.GetCenter() - m_Buttonp[i].m_Width / 2, y + 40 + i * 25);

		m_tButtonp[i].SetXCenter(m_Buttonp[i].GetCenter());
		m_tButtonp[i].SetY(m_Buttonp[i].GetY() + 3);
		m_tButtonp[i].UpdateXCenter();
	}
// 	for (int i = 0; i < m_tTargetName.size(); i++)
// 	{
// 		m_tTargetName[i].SetXY(130 + m_tName[i + 2].GetX(), m_tName[i].GetY());
// 	}
	m_Cancel.SetXY(m_Back.GetX() + m_Back.GetWidth() - 20, m_Back.GetY() + 3);
	return true;
}

void cInterfaceConduct::OnOff(bool NeedShow)
{
	if (NeedShow)
	{
		Init();
// 		m_FighterNum = 0;
// 		for (int i = 0; i < 5; i++)
// 		{
// 			if (!g_pMainState->m_FightWorkList[i].isExist)continue;
// 			m_FighterNum += 1;
// 			m_tName[i].SetString(g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString());
// 			int wt = g_pMainState->m_FightWorkList[i].m_WorkType;
// 			if (-1 == g_pMainState->m_AI.m_FightTarget[i] && wt != -2)
// 				m_Buttonp[i].SetFrame帧(0);
// 			else
// 				m_Buttonp[i].SetFrame帧(1);
// 		}
// 		if (m_FighterNum == 1)return;
// 		m_Buttonp[5].SetFrame帧(0);
// 		m_Buttonp[6].SetFrame帧(0);
// 		m_Mode = -1;
// 		Move(m_xPos, m_yPos);
	}
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);

}

bool cInterfaceConduct::Show(cCanvas* pCanvas)
{
	if (m_Mode>-1)return true;
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_Title);
// 	if (m_FighterNum > 1)
// 	{
// 		for (int i = 0; i <7; i++)
// 		{
// 			pCanvas->Add(&m_tName[i]);
// 			pCanvas->Add(&m_Buttonp[i], 1);
// 			pCanvas->Add(&m_tButtonp[i]);
// 			if (i<5)
// 				if (m_Buttonp[i].GetFrame() == 1)
// 				{
// 				pCanvas->Add(&m_tTargetName[i]);
// 				}
// 		}
// 	}

	forv(m_Buttonp, i)
	{
		pCanvas->Add(&m_Buttonp[i], 1);
		pCanvas->Add(&m_tButtonp[i]);
	}
	
	return true;
}

bool cInterfaceConduct::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case  10:
		OnOff(false);
		break;
	case 16://移动
		if (1)
		{
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
			m_Sleeptime = 0;
		}
		return true;
	case 17://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	case 0:
		for (int i = 10; i < 20; ++i)
		{
			if (!g_pMainState->m_FightWorkList[i].isExist)
			{
				continue;
			}
			cObj* obj = g_pMainState->m_FightWorkList[i].m_pObj;
			obj->m_ConductFire.m_NeedShow = obj->m_ConductSeal.m_NeedShow = false;
		}
		return true;
	case 1:
	case 2:
		m_Mode = m_Select;
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Attack);
		return true;
	default:
		if (!m_framprep)
		{//按钮是否处于按下状态
			m_Buttonp[m_Select].SetFrame帧(0);
			switch (m_Select)
			{
			case 6://全体防御
				for (int i = 0; i < 5; i++)
				{
					if (i == g_pMainState->m_HeroID)continue;
					Def(i, false);
				}
			case 5://全体指定目标
				for (int i = 0; i < 5; i++)
				{
					if (i == g_pMainState->m_HeroID)continue;
					SetTarget(i, -1);
				}
				break;
			default:
				Def(m_Select, false);
				SetTarget(m_Select, -1);
				break;
			}
		}
		else
		{
			if (m_Select<5)
				if (!g_pMainState->m_FightWorkList[m_Select].isExist)return true;
			m_framprep->SetFrame帧(1);
			m_framprep = 0;
			switch (m_Select)
			{
			case 6://全体防御
				for (int i = 0; i < 5; i++)
				{
					if (i == g_pMainState->m_HeroID)continue;
					Def(i);
				}
				//				OnOff(false);
				break;
			default:
				m_Mode = m_Select;
				g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Attack);
				break;
			}
		}
		break;
	}
	return true;
}

bool cInterfaceConduct::ProcessInput()
{
	g_pMainState->SetMouseOnMap(false);
	if (m_Mode>-1)
	{
		m_Select = 1;
		if (CheckRB())return true;
		int select = g_pMainState->m_Cursor.SelectObj(g_pMainState->m_HeroID, 4, m_pObj);
		if (select == -1)return true;
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Normal);
		if (m_Mode == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				if (i == g_pMainState->m_HeroID)continue;
				Def(i, false);
				SetTarget(i, select);
			}
			OnOff(false);
		}
		else
		{
			SetTarget(m_Mode, select);
		}
		m_Mode = -1;
		return true;
	}
	if (m_Sleeptime > 0)
	{
		m_Sleeptime -= 1;
		return true;
	}
	if (m_bMoveMode)//移动
	{
		m_Select = 16;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}
	ResetButton();
	m_Select = -1;
	if (CheckOn(&m_Cancel, 10))return true;
	forv (m_Buttonp, i)
	{
		if (CheckOn(&m_Buttonp[i], i))return true;
	}
	m_Select = 0;
	if (CheckRB())return true;

	//准备移动
	m_Select = 17;
	CheckL();
	return true;
}

bool cInterfaceConduct::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	case 1:
		/*m_tTargetName[m_Mode].SetString("");
		m_Buttonp[m_Mode].SetFrame(0);
		g_pMainState->m_AI.m_FightTarget[m_Mode] = -1;*/
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Normal);
		m_Mode = -1;
		break;
	default:
		break;
	}

	return true;
}

void cInterfaceConduct::SetTarget(int id, int target)
{
	if (id == 1)
	{
		g_pMainState->m_FightWorkList[target].m_pObj->m_ConductFire.m_NeedShow = true;
	}
	else if (id == 2)
	{
		g_pMainState->m_FightWorkList[target].m_pObj->m_ConductSeal.m_NeedShow = true;
	}
	return;
// 	g_pMainState->m_AI.m_FightTarget[id] = target;
// 	g_pMainState->m_AI.m_FightTarget[id + 5] = target;
	if (target == -1)
	{
		m_Buttonp[id].SetFrame帧(0);
		m_tTargetName[id].SetString("");
	}
	else
	{
		m_Buttonp[id].SetFrame帧(1);
		m_tTargetName[id].SetString(g_pMainState->m_FightWorkList[target].m_pObj->m_TrueName.GetString());
	}
}

void cInterfaceConduct::Def(int id, bool bDef /*= true*/)
{
	if (!g_pMainState->m_FightWorkList[id].isExist)return;
	if (bDef)
	{
		g_pMainState->m_AI.defense(id);
		g_pMainState->m_AI.defense(id + 5);
		m_Buttonp[id].SetFrame帧(1);
		m_tTargetName[id].SetString("防御");
		// 		g_pMainState->m_AI.m_FightTarget[id] = id;
		// 		g_pMainState->m_AI.m_FightTarget[id + 5] = id+5;
	}
	else
	{
		if (g_pMainState->m_FightWorkList[id].m_WorkType == -2)
		{
			// 1002 格挡状态
			g_pMainState->m_FightWorkList[id].m_WorkType = -1;
			g_pMainState->m_FightWorkList[id].m_pObj->ReMoveStateID(1002);
			g_pMainState->m_FightWorkList[id + 5].m_WorkType = -1;
			g_pMainState->m_FightWorkList[id + 5].m_pObj->ReMoveStateID(1002);
// 			g_pMainState->m_AI.m_FightTarget[id] = -1;
// 			g_pMainState->m_AI.m_FightTarget[id + 5] = -1;
		}
	}
}

