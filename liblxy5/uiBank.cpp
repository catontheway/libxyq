#include "_global.h"

bool cInterfaceYingHang::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	case 1:
		if (1)
		{

			if (m_pTrigger)
			{
				m_pTrigger->Process(m_TriggerID);
				OnOff(false);
				return true;
			}
			ostringstream oss;
			if (!m_bMode)
			{
				if (m_pFriend)
				{
					m_pFriend->m_money += m_ShuRu.m_num;
				}
				else
					g_pCharacter->m_PcData.m_Money[1] += m_ShuRu.m_num;

				g_pCharacter->m_PcData.m_Money[0] -= m_ShuRu.m_num;
				oss << "你存入了#R";
			}
			else
			{
				g_pCharacter->m_PcData.m_Money[1] -= m_ShuRu.m_num;
				g_pCharacter->m_PcData.m_Money[0] += m_ShuRu.m_num;
				oss << "你取出了#R";
			}
			oss << m_ShuRu.m_num;
			oss << "#R两";
			m_ShuRu.Reset();
			OnOff(false);
			g_pMainState->m_Dialog.Reset();
			if (m_pFriend)
			{
				g_pMainState->m_Dialog.Talk(oss.str(), m_pFriend->m_Name,
					m_pFriend->GetDialogHead());
			}
			else
			{
				g_pMainState->m_Dialog.SetObj("钱庄老板");
				g_pMainState->m_Dialog.m_pObj = 0;
				g_pMainState->m_Dialog.SetString(oss.str());
			}

			g_pMainState->m_Dialog.OnOff(true);
		}
		break;;
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
	}
	return true;
}

void cInterfaceYingHang::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
	if (NeedShow)
	{

		m_ShuRu.SetActive(false);
	}
	else  	m_pTrigger = false;
}

void cInterfaceYingHang::SetMode(
	bool mode,
	sFriendList* pFriend
	)
{//0存钱 1 取钱
	Init();
	m_pFriend = pFriend;
	m_bMode = mode;

	m_XianJin.SetString(g_pCharacter->m_PcData.m_Money[0]);
	m_XianJin.SetColor(GetPriceColor(g_pCharacter->m_PcData.m_Money[0]));

	if (pFriend)
	{
		m_CunYing.SetString(pFriend->m_money);
		m_CunYing.SetColor(GetPriceColor(pFriend->m_money));
	}
	else
	{
		m_CunYing.SetString(g_pCharacter->m_PcData.m_Money[1]);
		m_CunYing.SetColor(GetPriceColor(g_pCharacter->m_PcData.m_Money[1]));
	}
	if (!m_bMode)//存款
	{
		m_Back.Load(0x541FA615);
		m_ShuRu.SetMaxNum(g_pCharacter->m_PcData.m_Money[0]);
	}
	else //取款
	{
		m_Back.Load(0x420FF401);
		if (m_pFriend)
		{
			m_ShuRu.SetMaxNum(m_pFriend->m_money);
		}
		else
			m_ShuRu.SetMaxNum(g_pCharacter->m_PcData.m_Money[1]);
	}
	m_ShuRu.Reset();
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
}

bool cInterfaceYingHang::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(m_xPos, m_yPos);
	m_XianJin.SetXY(m_xPos + 100, m_yPos + 46);
	m_CunYing.SetXY(m_xPos + 100, m_yPos + 76);
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	m_Button.SetXY(m_xPos + m_Back.GetWidth() / 2 - m_Button.GetWidth() / 2, m_yPos + 142);
	m_tButton.SetXCenter(m_Button.GetCenter());
	m_tButton.SetY(m_Button.GetY() + 3);
	m_tButton.UpdateXCenter();
	RECT rect;
	rect.left = m_xPos + 100;
	rect.right = rect.left + 70;

	rect.top = m_yPos + 106;
	rect.bottom = rect.top + 18;
	m_ShuRu.Init(rect);
	return true;
}

bool cInterfaceYingHang::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Button.Set(&g_pMainState->m_Button4);
	m_Button.m_bStatic = true;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_tButton.SetColor(RGB(255, 255, 255));
	m_tButton.SetString("确定");
	return true;
}

bool cInterfaceYingHang::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_XianJin);
	pCanvas->Add(&m_CunYing);
	m_ShuRu.Show(pCanvas);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_Button, 1);
	pCanvas->Add(&m_tButton);
	return true;
}

bool cInterfaceYingHang::ProcessInput()
{
	g_pMainState->SetMouseOnMap(false);
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}
	if (m_ShuRu.Process())return true;
	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	if (CheckOn(&m_Cancel, 0))return true;
	if (CheckOn(&m_Button, 1))return true;

	m_Select = 7;
	if (CheckL())return true;
	m_Select = 0;
	if (CheckRB())return true;
	return true;
}

bool cInterfaceYingHang::CheckRB()
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

