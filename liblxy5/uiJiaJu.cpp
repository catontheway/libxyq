#include "_global.h"


void cInterfaceUseJiaJu::SetJiaJu(sItem2* jiaju)
{
	m_pJiaJu = jiaju;
	m_JiaJu.m_JiaJu = *jiaju;
	switch (jiaju->m_pItemData->GetLv())
	{
	case 1:
	case 2:
		m_Pic[0].m_PosType = 0;
		break;
	case 4:
	case 5:
		for (int i = 0; i < 6;i++)
			m_Pic[i].m_PosType = 1;
		break;
	default:
		m_Pic[0].m_PosType = 1;
	}
	AddDirection();
	OnOff(true);
}

void cInterfaceUseJiaJu::AddDirection()
{
	sJiaJuData& list = g_pMainState->m_ItemManage.m_JiaJuData[m_JiaJu.m_JiaJu.GetType() - 35][m_JiaJu.m_JiaJu.GetID()];
	m_JiaJu.m_Direction += 1;
	m_JiaJu.m_Direction %= list.num;
	for (int i = 0; i < 6; i++)
	{
		m_Pic[i].m_NeedShow = false;
	}
	switch (m_JiaJu.m_JiaJu.m_pItemData->GetLv())
	{
	case 4:
		if (1)
		{
			if (m_JiaJu.m_Direction >= 2)m_JiaJu.m_Direction = 0;
			m_Pic[0].Load(list.m_data[m_JiaJu.m_Direction * 3]);
			m_Pic[1].Load(list.m_data[m_JiaJu.m_Direction * 3 + 1]);
			m_Pic[2].Load(list.m_data[m_JiaJu.m_Direction * 3 + 2]);
			for (int i = 0; i < 3; i++)
			{
				m_Pic[i].m_NeedShow = true;
			}
		}
		break;
	case 5:
		if (1)
		{
			if (m_JiaJu.m_Direction >= 2)m_JiaJu.m_Direction = 0;
			if (!m_JiaJu.m_Direction)
			{
				for (int i = 0; i < 6; i++)
				{
					m_Pic[i].Load(list.m_data[i]);
					m_Pic[i].m_NeedShow = true;
				}
			}
			else
			{
				for (int i = 0; i < 5; i++)
				{
					m_Pic[i].Load(list.m_data[6+i]);
					m_Pic[i].m_NeedShow = true;
				}
			}
		}
		break;
	default:
		m_Pic[0].Load(list.m_data[m_JiaJu.m_Direction]);
		m_Pic[0].m_NeedShow = true;
		break;
	}
}

bool cInterfaceUseJiaJu::Show(cCanvas* pCanvas)
{
	for (int i = 0; i < 6;i++)
	pCanvas->Add(&m_Pic[i], 1);
	return true;
}

bool cInterfaceUseJiaJu::ProcessInput()
{
	g_pMainState->SetMouseOnMap(false);
	if (g_pMainState->Keyboard.GetKeyState(DIK_SPACE))
	{
		g_pMainState->Keyboard.SetLock(DIK_SPACE);
		AddDirection();
	}
	for (int i = 0; i < 6; i++)
		m_Pic[i].SetXY(g_xMouse, g_yMouse);

	if (CheckL())return true;
	if (CheckRB())return true;
	return true;
}

void cInterfaceUseJiaJu::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_JiaJu.m_JiaJu.m_pItemData->GetLv() == 4)
	{
		for (int i = 0; i < 3;i++)
		g_pMainState->m_Canvas.SetRedraw(m_Pic[i].m_PreShowRect);
	}
	else
	g_pMainState->m_Canvas.SetRedraw(m_Pic[0].m_PreShowRect);
}

bool cInterfaceUseJiaJu::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);

	int xof = g_pMainState->m_Map.m_pMap->GetXCenter() - g_half320;
	int yof = g_pMainState->m_Map.m_pMap->GetYCenter() - g_half240;

	
	m_JiaJu.m_xPos = m_Pic[0].GetX() + xof;
	m_JiaJu.m_yPos = m_Pic[0].GetY() + yof;
	if (g_pMainState->m_FangWu.AddJiaJu(m_JiaJu))
	{
		m_pJiaJu->m_Num = 0;
		g_pMainState->m_Map.AddJiaJu(&m_JiaJu);
		g_pMainState->FindObj();
	}
	OnOff(false);
	return true;
}

bool cInterfaceUseJiaJu::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	OnOff(false);
	return true;
}











