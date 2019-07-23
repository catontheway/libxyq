#include "_global.h"


void cInterfaceJianDing::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (NeedShow)
	{
		Init();
		m_ItemSelect = -1;
		g_pMainState->m_ItemSelect.Update();
		for (int i = 0; i < 20; i++)
		{
			sItem2& item = g_pCharacter->m_PcData.m_Items[i];
			if (item.GetNum() == 0)continue;
			bool& needshow = g_pMainState->m_ItemSelect.m_ItemHead[i].m_NeedShow;
			if (item.GetType()>21)
			{
				switch (item.GetType())
				{
				case 32:
				case 33:
				case 34:
					needshow = true;
					break;
				case 29:
					if (m_Mode == 3)
					{
						needshow = true;
						break;
					}
				default:
					if (m_Mode == 2 || m_Mode == 4)
						needshow = true;
					else
					{
						needshow = false;
					}

					break;
				}
			}
			else needshow = true;
		}
		g_pMainState->m_ItemSelect.Move(m_xPos + 20, m_yPos + 35);

	}
	else
	{
		g_pMainState->m_ItemSelect.m_Describe.OnOff(false);
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}

bool cInterfaceJianDing::CheckL()
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
			sItem2& item = g_pCharacter->m_PcData.m_Items[m_NowItemSelect];
			if (item.m_Property.size())
			{
				g_pMainState->m_Tags.Add("已鉴定");
				return true;
			}
			int moneyneed = item.m_pItemData->m_Price / 10;
			if (g_pCharacter->m_PcData.AddMoney(-moneyneed, 0, 0, false))
			{
//				g_pMainState->m_ItemManage.AutoItemProperty国标(&item, g_pCharacter->m_PcData.m_Popularity);
				g_pMainState->m_ItemManage.AutoItemProperty(&item);
				ostringstream oss;
				oss << "鉴定成功,共花费";
				oss << moneyneed;
				oss << "两";
				g_pMainState->m_Tags.Add(oss.str());
			}
			else
			{
				g_pMainState->m_Tags.Add("金钱不足");
			}
		}
		break;
	case 2:
		if (1)
		{
			sItem2& item = g_pCharacter->m_PcData.m_Items[m_NowItemSelect];

			int moneyneed = 0;
			switch (m_Mode)
			{
			case 1:
				moneyneed = (item.m_Num*item.m_pItemData->m_Price) / 2;
				break;
			case 2:
				moneyneed = (item.m_Num*item.m_pItemData->m_Price) / 3;
				break;
			}
			g_pCharacter->m_PcData.m_Money[0] += moneyneed;
			item.m_Num = 0;
			g_pMainState->m_ItemSelect.m_ItemHead[m_NowItemSelect].m_NeedShow = false;
			ostringstream oss;
			oss << "得到了";
			oss << moneyneed;
			oss << "两";
			g_pMainState->m_Tags.Add(oss.str());
		}
		break;
	case 3:
	{
		sItem2& item = g_pCharacter->m_PcData.m_Items[m_NowItemSelect];
		item.m_Num -= 1;
		if (item.GetType() == 26)
			g_pMainState->m_Friend.m_friendqianghua.Change(item.GetID());
		OnOff(false);
	}
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
	case 8:
		if (1)
		{
			sItem2& item = g_pCharacter->m_PcData.m_Items[m_NowItemSelect];
			if (item.GetType() == 29)
			{
				//宝石	
				if (m_ItemSelect == -1)return true;
				sItem2& equip = g_pCharacter->m_PcData.m_Items[m_ItemSelect];
				if (0 == equip.m_Property.size())
				{
					g_pMainState->m_Tags.Add("未鉴定");
					return true;
				}
// 				int nummax = g_pMainState->m_ItemManage.GetlvByID(equip.GetType(), equip.GetID()) / 10;
// 				if (nummax > equip.m_Property[0])
// 				{
// 					if (item.m_Num > equip.m_Property[0])
// 					{
						if (!g_pMainState->m_ItemManage.XiangQian(g_pCharacter->m_PcData.m_Items[m_ItemSelect], item))
						{
							g_pMainState->m_Tags.Add("无法镶嵌");
						}
						else
						{
							g_pMainState->m_Tags.Add("镶嵌成功");
							g_pCharacter->m_PcData.m_Items[m_NowItemSelect].m_Num -= g_pCharacter->m_PcData.m_Items[m_ItemSelect].m_Property[0];
							g_pMainState->m_ItemSelect.Update();
						}
// 					}
// 					else g_pMainState->m_Tags.Add("数量不够");
// 				}
// 				else
// 				{
// 					g_pMainState->m_Tags.Add("无法再镶嵌了");
// 				}
			}
			else if (item.GetType() < 22 || item.GetType() == 32 || item.GetType() == 33 || item.GetType() == 34)
			{
				m_ItemSelect = m_NowItemSelect;
			}
		}
	}
	return true;
}

bool cInterfaceJianDing::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	m_NowItemSelect = -1;
	m_Select = -1;
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}

	if (isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);
		m_NowItemSelect = g_pMainState->m_ItemSelect.Process(g_xMouse, g_yMouse);
		if (m_NowItemSelect > -1)
		{
			m_Select = 2;
			switch (m_Mode)
			{
			case 0:
				m_Select = 1;
			case 1:
			case 2:
				if (1)
				{
					if (!g_pCharacter->m_PcData.m_Items[m_NowItemSelect].m_pItemData)return false;
					int price = g_pCharacter->m_PcData.m_Items[m_NowItemSelect].m_pItemData->m_Price;
					ostringstream oss;
					oss << "价格";
					switch (m_Mode)
					{
					case 0:price /= 10; break;
					case 1:price /= 2; break;
					default:price /= 3; break;
					}
					oss << price;
					oss << "两";
					m_tPrice.SetString(oss.str());
					m_tPrice.UpdateXCenter();
				}
				break;
			case 3:
			{
				int ittype = g_pCharacter->m_PcData.m_Items[m_NowItemSelect].GetType();
				m_Select = 8;
				if (ittype < 22 || ittype == 32 || ittype == 33 || ittype == 34)
				{
					if (!g_pCharacter->m_PcData.m_Items[m_NowItemSelect].m_Property.size())
						return true;
					ostringstream oss;
					oss << g_pCharacter->m_PcData.m_Items[m_NowItemSelect].GetName() << "强化需要";
					oss << g_pCharacter->m_PcData.m_Items[m_NowItemSelect].m_Property[0] + 1;
					oss << "个宝石";
					m_tPrice.SetString(oss.str());
					m_tPrice.UpdateXCenter();
				}
			}
				break;
			case 4:
				m_Select = 3;
				break;
			default:ERRBOX;
			}
			if (CheckL())return true;
			return true;
		}

		if (CheckOn(&m_Cancel, 0))return true;
		//准备移动
		m_Select = 7;
		CheckL();
		if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
		{
			g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
			OnOff(false);
		}
	}
	return true;
}

bool cInterfaceJianDing::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	g_pMainState->m_ItemSelect.Show(pCanvas);
	pCanvas->Add(&m_tPrice);
	return true;
}


bool cInterfaceJianDing::Move(int xPos, int yPos)
{
	m_xPos = xPos;
	m_yPos = yPos;
	m_Back.SetXY(xPos, yPos);
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	g_pMainState->m_ItemSelect.Move(xPos + 20, yPos + 35);

	m_tPrice.SetXCenter(m_Back.GetCenter() - 10);
	m_tPrice.SetY(m_yPos + 3);
	m_tPrice.UpdateXCenter();
	return true;
}

bool cInterfaceJianDing::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Back.Load(0xE3AEF018);
	m_Back.SetStatic(true);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_tPrice.SetColor(RGB(255, 255, 255));
	g_pMainState->m_ItemSelect.Init();
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}



