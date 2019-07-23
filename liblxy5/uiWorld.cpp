#include "_global.h"



bool cWorldMap::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Mode = 0;
	m_Data[eMapWorld].Load(0x93E77F54);
	m_Data[eMapSouth].Load(0x0B19A5DC);
	m_Data[eMapEast].Load(0x26E89B1F);
	m_Data[eMapNorth].Load(0xE9EC7A25);
	m_Data[eMapWest].Load(0x11A18FBF);
	m_Data[eMapFenChao].Load(0x13659C02);
	m_Data[eMapLongKu].Load(0xA0B51368);
	m_Data[eMapNvWa].Load(0xEDEEF9AF);
	m_Data[eMapAL].Load(0xCCB7A7C3);
	m_Data[eMapHGS].Load(0x6B27F57F);
	m_Data[eMapNR].Load(0x6BF13E64);
	m_Data[eMapPengLai].Load(0xA9BC7D93);
	m_Data[eMapCA].Load(0x71DF41E1);
	m_Data[eMapDT].Load(0xE0C66A6F);
	m_Data[eMapDF].Load(0x9C992236);
	m_Data[eMapGLZ].Load(0xFF1D4A14);
	m_Data[eMapHZ].Load(0x6EA52AE1);
	m_Data[eMapHS].Load(0x47FE6497);
	m_Data[eMapJY].Load(0x6AB41A9A);
	m_Data[eMapJZ].Load(0x991B588D);
	m_Data[eMapLG].Load(0xAD1DC28A);
	m_Data[eMapMW].Load(0x150B5122);
	m_Data[eMapPS].Load(0x301A4FE7);
	m_Data[eMapPT].Load(0xEC9EBCA8);
	//m_Data[eMapSML].Load(0xCAF25E94);
	m_Data[eMapST].Load(0xBF78C1EF);
	m_Data[eMapD5].Load(0x5B96A2DD);
	m_Data[eMapWZ].Load(0xCA26DE5D);

	m_Data[eMapXXT].Load(0xEA60ABA4);
	m_Data[eMapBX].Load(0x0D906C8D);
	m_Data[eMapBQ].Load(0x63566DA9);
	m_Data[eMapCS].Load(0x637B3C48);
	m_Data[eMapFC].Load(0x6A154DDE);
	m_Data[eMapZZ].Load(0x689EB676);
	m_Data[eMapXL].Load(0xE329AD6A);
	m_Data[eMapQLS].Load(0x048DA00D);
	m_Data[eMapWorldNorth].Load(0xEA1F50E2);
	m_Data[eMapWorldLG].Load(0xCE11152D);
	m_Data[eMapWorldEast].Load(0xCC1742A6);
	m_Data[eMapWorldSouth].Load(0x7FFAB47A);
	m_Data[eMapWorldWest].Load(0x0AF24A29);
	m_Data[eMapWorldTG].Load(0x5ABFF907);
	m_Data[eMapWorldYG].Load(0xF63C410E);
	m_Data[eMapWorldPTY].Load(0xF8A67A7A);
	m_Data[eMapMJC].Load(0xF617F5A9);

	//CWFile	m_LBC;		  m_LBC.Load(0xBDAEEA53);
	//CWFile	m_WDD;		  m_WDD.Load(0xBFF5620B);
	InitPos();
	return true;
}

void cWorldMap::InitPos()
{
	int x = g_half320 - 320;
	int y = g_half240 - 240;
	m_text.SetXY(x + 100, y + 20);
	m_Data[eMapWorld].SetXY(x,y +  0);
	m_Data[eMapSouth].SetXY(x,y +  0);
	m_Data[eMapNorth].SetXY(x,y +  0);
	m_Data[eMapEast].SetXY(x, y + 0);
	m_Data[eMapWest].SetXY(x, y + 0);
	m_Data[eMapFenChao].SetXY(x + 327, y + 145);
	m_Data[eMapLongKu].SetXY(x + 52, y + 167);
	m_Data[eMapNvWa].SetXY(x + 161, y + 20);

	m_Data[eMapAL].SetXY(x + 343, y + 273);
	m_Data[eMapHGS].SetXY(x + 263, y + 11);
	m_Data[eMapNR].SetXY(x + 212, y + 162);
	m_Data[eMapPengLai].SetXY(x + 149, y + 313);


	m_Data[eMapCA].SetXY(x + 368, y + 141);
	m_Data[eMapDT].SetXY(x + 450, y + 102);
	m_Data[eMapDF].SetXY(x + 331, y + 34);
	m_Data[eMapGLZ].SetXY(x + 105,y +  230);
	m_Data[eMapHZ].SetXY(x + 295, y + 130);
	m_Data[eMapHS].SetXY(x + 477, y + 158);
	m_Data[eMapJY].SetXY(x + 468, y + 232);
	m_Data[eMapJZ].SetXY(x + 350, y + 113);
	m_Data[eMapLG].SetXY(x + 469, y + 374);
	m_Data[eMapMW].SetXY(x + 191, y + 94);
	m_Data[eMapPS].SetXY(x + 213, y + 194);
	m_Data[eMapPT].SetXY(x + 333, y + 410);
	m_Data[eMapSML].SetXY(x + 0, y + 0);
	m_Data[eMapST].SetXY(x + 4, y + 185);
	m_Data[eMapD5].SetXY(x + 273, y + 18);
	m_Data[eMapWZ].SetXY(x + 232, y + 271);
	m_Data[eMapXXT].SetXY(x + 50, y + 69);

	m_Data[eMapBX].SetXY(x + 488, y + 274);
	m_Data[eMapBQ].SetXY(x + 329, y + 101);
	m_Data[eMapCS].SetXY(x + 414, y + 117);
	m_Data[eMapFC].SetXY(x + 543, y + 8);
	m_Data[eMapZZ].SetXY(x + 469, y + 330);
	m_Data[eMapXL].SetXY(x + 457, y + 200);
	m_Data[eMapQLS].SetXY(x + 387, y + 317);
	m_Data[eMapMJC].SetXY(x + 155, y + 17);
	m_Data[eMapWorldNorth].SetXY(x + 271, y + 10);
	m_Data[eMapWorldLG].SetXY(x + 388, y + 376);
	m_Data[eMapWorldEast].SetXY(x + 499, y + 160);
	m_Data[eMapWorldSouth].SetXY(x + 85, y + 104);
	m_Data[eMapWorldWest].SetXY(x + 0, y + 58);
	m_Data[eMapWorldTG].SetXY(x + 166, y + 23);
	m_Data[eMapWorldYG].SetXY(x + 75, y + 4);
	m_Data[eMapWorldPTY].SetXY(x + 199, y + 0);
}

bool cWorldMap::ProcessInput()
{
	g_pMainState->SetMouseOnMap(false);
	ResetButton();

	switch (m_Mode)
	{
	case 0:
		ProcessInput0();
		break;
	case 1:
		ProcessInput1();
		break;
	case 2:
		ProcessInput2();
		break;
	case 3:
		ProcessInput3();
		break;
	case 4:
		ProcessInput4();
		break;
	}
	m_Select = 0;
	CheckRB();
	return true;
}

bool cWorldMap::Show(cCanvas* pCanvas)
{
	switch (m_Mode)
	{
	case 0:
		Show0(pCanvas);
		break;
	case 1:
		Show1(pCanvas);
		break;
	case 2:
		Show2(pCanvas);
		break;
	case 3:
		Show3(pCanvas);
		break;
	case 4:
		Show4(pCanvas);
		break;
	}
	pCanvas->Add(&m_text);
	return true;
}
//世界地图
bool cWorldMap::ProcessInput0()
{
	cWasFile* pNowSelect = 0;
	int i = 1;

	for (; i < 9; i++)
	{
		if (m_Data[i].isSelectOn(g_xMouse, g_yMouse))
		{
			pNowSelect = &m_Data[i];
			break;
		}
	}

	if (pNowSelect)
	{
		m_pShow = pNowSelect;
		m_Select = i;
		m_pShow->SetStatic(false);
		m_pShow->m_bMove = true;
		return CheckL();
	}
	if ((9 == i) && m_pShow)
	{
		m_pShow->SetFrame(0);
		m_pShow->SetStatic(true);
		m_pShow->m_bMove = true;
		m_pShow = 0;
	}

	return true;
}
//东胜神洲
bool cWorldMap::ProcessInput1()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		for (int i = 16; i < 20; i++)
		{
			if (CheckOn(&m_Data[i], i))return true;
		}
	}
	return true;
}
bool cWorldMap::ProcessInput2()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		for (int i = 38; i < 45; i++)
		{
			if (CheckOn(&m_Data[i], i))return true;
		}
	}
	return true;
}
bool cWorldMap::ProcessInput3()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		for (int i = 20; i < 38; i++)
		{
			if (CheckOn(&m_Data[i], i))return true;
		}
	}
	return true;
}
bool cWorldMap::ProcessInput4()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		for (int i = 13; i < 16; i++)
		{
			if (CheckOn(&m_Data[i], i))return true;
		}
	}
	return true;
}

bool cWorldMap::Show0(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Data[eMapWorld], 1, 1);
	if (m_pShow)
		pCanvas->Add(m_pShow, 1, 0);
	return true;
}
//东
bool cWorldMap::Show1(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Data[eMapEast], 1, 1);
	for (int i = 16; i < 20; i++)
		pCanvas->Add(&m_Data[i], 1, 0);
	return true;
}
//西
bool cWorldMap::Show2(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Data[eMapWest], 1, 1);
	for (int i = 38; i < 45; i++)
		pCanvas->Add(&m_Data[i], 1, 0);
	return true;
}
//南
bool cWorldMap::Show3(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Data[eMapSouth], 1, 1);
	for (int i = 20; i < 38; i++)
		pCanvas->Add(&m_Data[i], 1, 0);
	return true;
}
//北
bool cWorldMap::Show4(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Data[eMapNorth], 1, 1);
	for (int i = 13; i < 16; i++)
		pCanvas->Add(&m_Data[i], 1, 0);
	return true;
}

void cWorldMap::OnOff(bool bShow)
{
#ifndef TESTDEBU
	//	return;
#endif

	if (m_NeedShow == bShow)return;
	g_pMainState->InterfaceSetShow(this, bShow);

	g_pMainState->m_Canvas.SetRedrawAll();
	if (m_NeedShow)
	{
		if (!m_bInit)Init();
	}
}

bool cWorldMap::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	cMyMap& map = g_pMainState->m_Map;

	eMap mapid = (eMap)m_Select;
	switch (mapid)
	{
	case cWorldMap::eMapWorld:
	case cWorldMap::eMapWorldEast:
	case cWorldMap::eMapWorldWest:
	case cWorldMap::eMapWorldSouth:
	case cWorldMap::eMapWorldNorth:
		g_pMainState->m_Canvas.SetRedrawAll();
		m_Mode = m_Select;
		break;
	case cWorldMap::eMapSouth:
	case cWorldMap::eMapNorth:
	case cWorldMap::eMapEast:
	case cWorldMap::eMapWest:
		g_pMainState->m_Canvas.SetRedrawAll();
		m_Mode = m_Select;
		break;
	default:
		if (1)
		{
			OnOff(false);
			bool bfly = true;
			switch (mapid)
			{
			case cWorldMap::eMapFenChao:map.LoadMap(64, 59, "凤巢一层", bfly); break;
			case cWorldMap::eMapLongKu:map.LoadMap(148, 15, "龙窟一层", bfly); break;
			case cWorldMap::eMapNvWa:map.LoadMap(51, 38, "女娲神迹", bfly); break;
			case cWorldMap::eMapAL:map.LoadMap(127, 92, "傲来国", bfly); break;
			case cWorldMap::eMapHGS:map.LoadMap(35, 98, "花果山", bfly); break;
			case cWorldMap::eMapNR:map.LoadMap(69, 63, "女儿村", bfly); break;
			case cWorldMap::eMapPengLai:map.LoadMap(83, 34, "蓬莱仙岛", bfly); break;
			case cWorldMap::eMapCA:map.LoadMap(200, 160, "长安城", bfly); break;
			case cWorldMap::eMapDT:map.LoadMap(99, 35, "大唐官府", bfly); break;
			case cWorldMap::eMapDF:map.LoadMap(44, 54, "阴曹地府", bfly); break;
			case cWorldMap::eMapGLZ:map.LoadMap(394, 56, "大唐境外", bfly); break;
			case cWorldMap::eMapHZ:map.LoadMap(41, 36, "大唐国境", bfly); break;
			case cWorldMap::eMapHS:map.LoadMap(35, 20, "化生寺", bfly); break;
			case cWorldMap::eMapJY:map.LoadMap(266, 33, "建邺城", bfly); break;
			case cWorldMap::eMapJZ:map.LoadMap(204, 234, "大唐国境"); break;
			case cWorldMap::eMapLG:map.LoadMap(91, 46, "龙宫", bfly); break;
			case cWorldMap::eMapWorldLG:map.LoadMap(91, 46, "龙宫", bfly); break;
			case cWorldMap::eMapMW:map.LoadMap(39, 24, "魔王寨", bfly); break;
			case cWorldMap::eMapPS:map.LoadMap(179, 120, "盘丝岭", bfly); break;
			case cWorldMap::eMapPT:map.LoadMap(69, 18, "普陀山", bfly); break;
			case cWorldMap::eMapSML://神木林break;
			case cWorldMap::eMapST:map.LoadMap(114, 83, "狮驼岭", bfly); break;
			case cWorldMap::eMapD5:map.LoadMap(41, 31, "无名鬼城", bfly); break;
			case cWorldMap::eMapWZ:map.LoadMap(43, 38, "五庄观", bfly); break;
			case cWorldMap::eMapXXT:map.LoadMap(37, 208, "小西天", bfly); break;
			case cWorldMap::eMapBX:map.LoadMap(115, 72, "宝象国", bfly); break;
			case cWorldMap::eMapBQ:map.LoadMap(58, 79, "比丘国", bfly); break;
			case cWorldMap::eMapCS:map.LoadMap(107, 58, "长寿村", bfly); break;
			case cWorldMap::eMapZZ:map.LoadMap(12, 7, "朱紫国", bfly); break;
			case cWorldMap::eMapXL:map.LoadMap(84, 62, "西梁女国", bfly); break;
			case cWorldMap::eMapMJC:map.LoadMap(42, 155, "墨家村", bfly); break;
			case cWorldMap::eMapQLS:map.LoadMap(31, 117, "麒麟山", bfly); break;
			case cWorldMap::eMapFC:map.LoadMap(126, 42, "方寸山", bfly); break;
			case cWorldMap::eMapWorldTG:map.LoadMap(202, 33, "天宫", bfly); break;
			case cWorldMap::eMapWorldYG:map.LoadMap(98, 60, "月宫", bfly); break;
			case cWorldMap::eMapWorldPTY:map.LoadMap(132, 35, "蟠桃园", bfly); break;
			default:ERRBOX; break;
			}
		}
	}
	return true;
}

bool cWorldMap::MoveTest(cWasFile& Target)
{
	if (isOn(g_xMouse, g_yMouse, Target.m_PreShowRect))
	{
		if (-1 != m_Prex)
		{
			ostringstream oss;
			int x = Target.GetX();
			int y = Target.GetY();
			oss << "x:" << x << "  ";
			oss << "y:" << y;
			m_text.SetString(oss.str());
			Target.SetXY(x + g_xMouse - m_Prex, y + g_yMouse - m_Prey);
		}
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		return true;
	}
	return false;
}

bool cWorldMap::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Mode)
	{
	case 0:
		OnOff(false);
		break;
	default:
		g_pMainState->m_Canvas.SetRedrawAll();
		m_Mode = 0;
		break;
	}
	return true;
}

