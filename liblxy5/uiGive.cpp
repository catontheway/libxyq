#include "_global.h"


bool cInterfaceGive::Init()
{
	if (m_bInit) return true;
	m_bInit = true;
	m_SelectMark.Load(0x10921CA7);
	m_SelectMark.m_NeedShow = false;
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;

	m_Back.Load(0xD6A27FFA);
	m_Back.SetStatic(true);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Button.Load(0x35A981D3);
	m_Button.SetStatic(true);
	m_tButton.SetColor(RGB(255, 255, 255));
	m_tButton.SetString("给予");
	m_tXIanJin.SetColor(RGB(255, 255, 255));
	for (int i = 0; i < 3; i++)
		m_NumItem[i].SetMaxNum(30);
	m_NumItem[0].SetHuChi(&m_NumItem[1]);
	m_NumItem[0].SetHuChi(&m_NumItem[2]);
	m_NumItem[0].SetHuChi(&m_NumShuru);

	m_NumItem[1].SetHuChi(&m_NumItem[0]);
	m_NumItem[1].SetHuChi(&m_NumItem[2]);
	m_NumItem[1].SetHuChi(&m_NumShuru);

	m_NumItem[2].SetHuChi(&m_NumItem[1]);
	m_NumItem[2].SetHuChi(&m_NumItem[0]);
	m_NumItem[2].SetHuChi(&m_NumShuru);

	m_NumShuru.SetHuChi(&m_NumItem[1]);
	m_NumShuru.SetHuChi(&m_NumItem[2]);
	m_NumShuru.SetHuChi(&m_NumItem[0]);

	for (int i = 0; i < 20; i++)
	{
		m_tItemHead[i].SetColor(RGB(255, 255, 255));
		m_tItemHead[i].SetStyle(2);
	}
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}

bool cInterfaceGive::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(m_xPos, m_yPos);
	m_Button.SetXY(m_xPos + m_Back.GetWidth() / 2 - m_Button.GetWidth() / 2, m_yPos + 414);
	m_tButton.SetXCenter(m_Button.GetCenter());
	m_tButton.SetY(m_Button.GetY() + 3);
	m_tButton.UpdateXCenter();
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	int xstart = m_xPos + 6;
	int ystart = m_yPos + 34;
	m_Rect.left = xstart;
	m_Rect.top = ystart;
	m_Rect.right = xstart + 254;
	m_Rect.bottom = ystart + 203;

	for (int i = 0; i < 20; i++)
	{
		int xNum = i % 5;
		int yNum = i / 5;
		m_ItemHead[i].SetXY(xstart + xNum * 51, ystart + yNum * 51);
		m_tItemHead[i].SetXY(xstart + xNum * 51 + 2, ystart + yNum * 51 + 2);
	}
	xstart = m_xPos + 33;
	ystart = m_yPos + 270;
	for (int i = 0; i < 3; i++)
	{
		m_ItemGiveHead[i].SetXY(xstart + i * 80, ystart);
	}
	m_tXIanJin.SetXY(m_xPos + 42, m_yPos + 366);

	RECT rect;
	rect.left = m_xPos + 186;
	rect.right = rect.left + 70;
	rect.top = m_yPos + 365;
	rect.bottom = rect.top + 20;
	m_NumShuru.Init(rect);

	rect.top = m_yPos + 329;
	rect.bottom = rect.top + 20;
	for (int i = 0; i < 3; i++)
	{
		rect.left = m_xPos + 48 + i * 80;
		rect.right = rect.left + 22;
		m_NumItem[i].Init(rect);
	}
	return true;
}

void cInterfaceGive::OnOff(bool NeedShow)
{
	if (NeedShow == m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
	if (NeedShow)
	{
		UpDate();
		m_SelectMark.m_NeedShow = false;
		for (int i = 0; i < 3; i++)
		{
			m_NumItem[i].m_num = 0;
		}
	}
}

bool cInterfaceGive::ProcessInput()
{
	if (m_NumShuru.Process())return true;
	for (int i = 0; i < 3; i++)
		if (m_NumItem[i].Process())
		{
		if (m_NumItem[i].m_num)
		{
			if (m_NumItem[i].m_num > g_pCharacter->m_PcData.m_Items[m_ItemGiveOwner[i]].m_Num)
			{
				m_NumItem[i].SetNum(g_pCharacter->m_PcData.m_Items[m_ItemGiveOwner[i]].m_Num);
			}
		}
		return true;
		}
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	m_Select = -1;
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	g_pMainState->SetMouseOnMap(false);

	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = (g_xMouse - m_Rect.left) / 51 + ((g_yMouse - m_Rect.top) / 51) * 5;
		m_MouseOnMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY());
		m_MouseOnMark.m_NeedShow = true;
		m_Select += 10;
		if (CheckL())return true;
	}
	else m_MouseOnMark.m_NeedShow = false;
	for (int i = 0; i < 3; i++)
	{
		if (m_NumItem[i].m_num)
		{
			if (isOn(g_xMouse, g_yMouse, m_ItemGiveHead[i].m_PreShowRect))
			{
				m_Select = i + 2;
				m_MouseOnMark.SetXY(m_ItemGiveHead[i].GetX(), m_ItemGiveHead[i].GetY());
				if (CheckL())return true;
			}
		}
	}
	if (CheckOn(&m_Cancel, 0))return true;
	if (CheckOn(&m_Button, 1))return true;
	m_Select = 0;
	if (CheckRB())return true;

	m_Select = 7;
	if (CheckL())return true;

	return true;
}

bool cInterfaceGive::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	for (int i = 0; i < 20; i++)
	{
		if (m_ItemNum[i])
		{
			pCanvas->Add(&m_ItemHead[i], 1);
			if (m_ItemNum[i]>1)
				pCanvas->Add(&m_tItemHead[i]);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_NumItem[i].m_num)
		{
			pCanvas->Add(&m_ItemGiveHead[i], 1);
			m_NumItem[i].Show(pCanvas);
		}
	}
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_Button, 1);
	pCanvas->Add(&m_tButton);
	pCanvas->Add(&m_tXIanJin);
	pCanvas->Add(&m_MouseOnMark, 1);
	pCanvas->Add(&m_SelectMark, 1);
	m_NumShuru.Show(pCanvas);

	return true;
}

void cInterfaceGive::UpDate()
{

	for (int i = 0; i < 20; i++)
	{
		sItem2& item = g_pCharacter->m_PcData.m_Items[i];
		m_ItemNum[i] = item.GetNum();
		if (m_ItemNum[i] < 1)continue;
		m_ItemHead[i].Load(item.m_pItemData->m_SmallHead);
		if (m_ItemNum[i] > 1)
		{
			ostringstream oss;
			oss << item.GetNum();
			m_tItemHead[i].SetString(oss.str());
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_ItemGive[i].GetNum() < 1)continue;
		m_ItemGiveHead[i].Load(m_ItemGive[i].m_pItemData->m_SmallHead);
	}
	ostringstream oss;
	oss << g_pCharacter->m_PcData.m_Money[0];
	m_tXIanJin.SetString(oss.str());
}

bool cInterfaceGive::CheckL()
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
		OnOff(false);
		break;
	case 1:
		m_Sleeptime = 0;
		m_Button.SetFrame(1);
		OnOff(false);
		if (m_ItemGive[0].GetNum() > 0 && m_ItemGive[0].m_pItemData &&
			g_pMainState->m_TriggerGive.Process(m_pTarget->m_TrueName.GetString(), m_ItemGive[0].GetID(),
			m_ItemGive[0].GetType()))
		{
			g_pCharacter->m_PcData.m_Items[m_ItemSelect].m_Num -= m_NumItem[0].m_num;
		}
		break;
	case 2:
	case 3:
	case 4:
		m_NumItem[m_Select - 2].Reset();
		break;
	case 6://移动
		if (1)
		{
			m_Sleeptime = 0;
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
		}
		return true;
	case 7://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	default:
		m_ItemSelect = m_Select - 10;
		m_SelectMark.SetXY(m_ItemHead[m_ItemSelect].GetX() + 3, m_ItemHead[m_ItemSelect].GetY() + 1);
		m_SelectMark.m_NeedShow = true;
		AddItem(m_ItemSelect);
		for (int i = 0; i < 3; i++)
		{
			if (m_ItemGiveOwner[i] == m_ItemSelect)
			{
				m_NumItem[i].SetActive(true);
				break;
			}
		}
		break;
	}
	return true;
}

bool cInterfaceGive::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	default:
		break;
	}
	return true;
}

void cInterfaceGive::AddItem(int select)
{
	sItem2& item = g_pCharacter->m_PcData.m_Items[select];
	if (item.GetNum() < 1)return;
	//	for (int i = 0; i < 3; i++)//单机游戏,不需要这个功能
	int i = 0;
	{
		if (1 > m_NumItem[i].m_num)
		{
			m_ItemGive[i] = item;
			m_ItemGiveOwner[i] = select;
			m_ItemGiveHead[i].Load(m_ItemGive[i].m_pItemData->m_SmallHead);
			m_NumItem[i].Reset();
			m_NumItem[i].ShuRu(1);
			return;
		}
		else
			if (m_ItemGiveOwner[i] == select)
			{
			if (m_NumItem[i].m_num)
			{
				if (m_NumItem[i].m_num > g_pCharacter->m_PcData.m_Items[m_ItemGiveOwner[i]].m_Num)
				{
					m_NumItem[i].SetNum(g_pCharacter->m_PcData.m_Items[m_ItemGiveOwner[i]].m_Num);
				}
				else if (m_NumItem[i].m_num < g_pCharacter->m_PcData.m_Items[m_ItemGiveOwner[i]].m_Num)
				{
					m_NumItem[i].SetNum(m_NumItem[i].m_num + 1);
				}
			}
			return;
			}
	}
}

void cInterfaceGive::SetTarget(cObj* pTarget)
{
	if (!m_bInit)Init();
	m_pTarget = pTarget;
	OnOff(true);
	UpDate();
}

cObj* cInterfaceGive::GetTarget()
{
	return m_pTarget;
}

void cInterfaceGive::ReCoverOnce()
{
	g_pCharacter->m_PcData.m_Items[m_ItemSelect].m_Num += m_NumItem[0].m_num;
}


