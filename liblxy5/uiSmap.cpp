#include "_global.h"



bool cInterfaceSmallMap::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (isOn(g_xMouse, g_yMouse, g_pMainState->m_Map.m_SmallMap.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);

		if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
		{
			g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
			OnOff(false);
			return true;
		}

		if (g_pMainState->Mouse.GetXDelta() != 0 || g_pMainState->Mouse.GetYDelta() != 0)
		{
			m_MousePos.m_NeedShow = true;
			m_MousePosBack.m_NeedShow = true;
			m_MousePos.SetXY(g_xMouse - m_MousePosBack.m_Picture.m_Width / 2 + 10, g_yMouse - 15);
			m_MousePosBack.SetXY(g_xMouse - m_MousePosBack.m_Picture.m_Width / 2, g_yMouse - 20);


			int tx = (g_xMouse - g_pMainState->m_Map.m_SmallMap.m_Picture.m_x - 18);
			int ty = (g_yMouse - g_pMainState->m_Map.m_SmallMap.m_Picture.m_y - 18);
			tx = (int)(tx*g_pMainState->m_Map.m_bili);
			ty = (int)(ty*g_pMainState->m_Map.m_bili);
			ty = g_pMainState->m_Map.m_pMap->m_Height - ty;
			tx /= 20;
			ty /= 20;
			ostringstream oss;
			oss << "X:";
			oss << tx;
			oss << " Y:";
			oss << ty;
			m_MousePos.SetString(oss.str());

		}
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);


			PrePareFindPath(g_xMouse, g_yMouse);
			if (g_pMainState->m_Map._isTeleporting)
			{
				g_pMainState->m_Map.LoadMap(m_xTarget / 20, (g_pMainState->m_Map.m_pMap->m_Height - m_yTarget) / 20, g_pMainState->m_Map.m_MapName.c_str(), 0);
				return true;
			}
			g_pMainState->m_FindPt.findAstart(g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj, m_xTarget, m_yTarget);
			g_pMainState->m_Cursor.m_FollowMode = false;
		}
	}
	else
	{
		m_MousePosBack.m_NeedShow = false;
		m_MousePos.m_NeedShow = false;
	}
	return true;
}

bool cInterfaceSmallMap::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&g_pMainState->m_Map.m_SmallMap, 1, true);
	int xSmallMap = g_pMainState->m_Map.m_SmallMap.m_Picture.m_x;
	int ySmallMap = g_pMainState->m_Map.m_SmallMap.m_Picture.m_y;
	float xOff = (float)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->GetX();
	float yOff = (float)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->GetY();
	xOff /= g_pMainState->m_Map.m_bili;
	yOff /= g_pMainState->m_Map.m_bili;
	int xPC = xSmallMap + 18 + (int)xOff;
	int yPC = ySmallMap + 18 + (int)yOff;
	m_PCPoint.m_Picture.m_x = xPC;
	m_PCPoint.m_Picture.m_y = yPC;
	pCanvas->Add(&m_PCPoint, 1);
	int k = 0;
	if (g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_AstartPathIndex > -1)
		for (int i = 0; i <= g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_AstartPathIndex;)
		{
		xOff = (float)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_AstartPathVecs[i].x;
		yOff = (float)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_AstartPathVecs[i].y;
		xOff /= g_pMainState->m_Map.m_bili;
		yOff /= g_pMainState->m_Map.m_bili;
		xPC = xSmallMap + 18 + (int)xOff;
		yPC = ySmallMap + 18 + (int)yOff;
		m_PathPointp[k].m_x = xPC;
		m_PathPointp[k].m_y = yPC;
		pCanvas->Add(&m_PathPointp[k], 1);
		k += 1;
		if (g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_AstartPathIndex < 300)
			i += 10;
		else
			if (g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_AstartPathIndex < 600)
				i += 20;
			else
				i += 40;
		}


	forv(_npcs, k)
	{
		auto t = _npcs[k];
		t->t.SetXY(xSmallMap + t->x - t->t.m_Width / 2, ySmallMap + t->y);
		g_pMainState->m_Canvas.Add(&t->t);
	}

	if (m_MousePos.m_NeedShow)
	{
		g_pMainState->m_Canvas.Add(&m_MousePosBack, 1);
		g_pMainState->m_Canvas.Add(&m_MousePos);
	}
	return true;
}

bool cInterfaceSmallMap::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_MousePosBack.Load(0x354CD2EB);
	m_MousePosBack.SetStatic(1);
	m_MousePos.SetColor(RGB(0, 0, 0));
	m_MousePos.m_hFont = g_pMainState->m_hFont[5];
	m_PathPoint.Load(0xF792E03C);
	m_PathPoint.SetStatic(true);
	m_PCPoint.Load(0x146BB550);
	m_PCPoint.SetStatic(true);
	m_PCPoint.SetStatic(true);
	for (int i = 0; i < 30; i++)
	{
		m_PathPointp[i].Set(&m_PathPoint);
		m_PathPointp[i].m_bStatic = true;
	}
	return true;
}

bool cInterfaceSmallMap::PrePareFindPath(int xMouse, int yMouse)
{
	float x = (float)(xMouse - g_pMainState->m_Map.m_SmallMap.m_Picture.m_x - 18);
	float y = (float)(yMouse - g_pMainState->m_Map.m_SmallMap.m_Picture.m_y - 18);
	m_xTarget = (int)(x*g_pMainState->m_Map.m_bili);
	m_yTarget = (int)(y*g_pMainState->m_Map.m_bili);
	return true;
}

bool cInterfaceSmallMap::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
		break;
	}
	return true;
}

void cInterfaceSmallMap::OnOff(bool bShow)
{
	if (!g_pMainState)return;
	if (g_pMainState->m_Map.m_bili)
	{
		g_pMainState->InterfaceSetShow(&g_pMainState->m_InterfaceSmallMap, bShow);
		if (m_NeedShow)
		{
			Init();
			m_MousePosBack.m_NeedShow = false;
			m_MousePos.m_NeedShow = false;
		}

		g_pMainState->m_Canvas.SetRedraw(g_pMainState->m_Map.m_SmallMap.m_PreShowRect);
	}
}




void cInterfaceSmallMap::clear()
{
	forv(_npcs, k)
	{
		SAFE_DELETE(_npcs[k]);
	}
	_npcs.clear();
}

void cInterfaceSmallMap::addNpc(const std::string& name, int x, int y, ulong color)
{
	_npcs.push_back(new sText5());
	sText5* t = _npcs.back();
	t->t.m_hFont = g_pMainState->m_hFont[5];
	t->t.SetColor(color);
	t->t.SetString(name);
	t->x = 18 + x;
	t->y = 18 + y;
}


void cInterfaceSmallMap::addNpc(const sNpc* npc)
{
	const auto& m = g_pMainState->m_Map;
	addNpc(npc->m_name, npc->m_x * 20 / m.m_bili, (m.m_pMap->m_Height - npc->m_y * 20) / m.m_bili, RGB(0xFF, 0xFF, 0));
}