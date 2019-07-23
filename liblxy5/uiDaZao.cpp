#include "_global.h"



bool cInterfaceDaZao::Init()
{
	if (m_bInit)return true;
	m_Back.Load(0xABB7D0DB);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Button.Set(&g_pMainState->m_Button2);
	m_Button.m_bStatic = true;
	m_tButton.SetString("镶嵌");
	m_tButton.SetColor(RGB(255, 255, 255));

	vector<string> strs = { "头盔", "项链", "武器", "衣甲", "腰带", "鞋子" };
	forr(m_Buttons, i)
	{
		m_Buttons[i].Set(&g_pMainState->m_Button2);
		m_Buttons[i].m_bStatic = true;
		m_tButtons[i].SetString(strs[i]);
		m_tButtons[i].SetColor(RGB(255, 255, 255));
	}

	m_tMoneyHave.SetColor(0);
	m_tMoneyNeed.SetColor(0);
	m_Head[0].m_NeedShow = false;
	m_Head[1].m_NeedShow = false;
	m_SelectMarks[0].Load(0x10921CA7);
	m_SelectMarks[1].Load(0x10921CA7);
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}

bool cInterfaceDaZao::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(x, y);
	m_tMoneyNeed.SetXY(x + 207, y + 37);
	m_tMoneyHave.SetXY(x + 207, y + 100);
	m_Cancel.SetXY(x + 270, y + 3);
	m_Head[0].SetXY(x + 17, y + 58 + 3);
	m_Head[1].SetXY(x + 74, y + 58 + 3);
	m_Button.SetXY(x + m_Back.GetWidth() / 2 - m_Button.GetWidth() / 2, y + 356);
	m_tButton.SetY(m_Button.GetY() + 3);
	m_tButton.SetXCenter(m_Button.GetCenter());
	m_tButton.UpdateXCenter();

	forv(m_Buttons, i)
	{
		m_Buttons[i].SetXY(x + 10 + i * 45, y + 356);
		m_tButtons[i].SetY(m_Buttons[i].GetY() + 3);
		m_tButtons[i].SetXCenter(m_Buttons[i].GetCenter());
		m_tButtons[i].UpdateXCenter();
	}
//	g_pMainState->m_ItemSelect.Move(x + 16, y + 134);
// 	if (m_NeedShow)
// 		g_pMainState->m_ItemSelect.Move(x, y);
	return true;
}

bool cInterfaceDaZao::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_tMoneyHave);
	pCanvas->Add(&m_tMoneyNeed);
	for (int i = 0; i < 2; i++)
	{
		pCanvas->Add(&m_Head[i], 1);
		pCanvas->Add(&m_SelectMarks[i], 1);
	}
	g_pMainState->m_ItemSelect.Show(pCanvas);
	pCanvas->Add(&m_Button, 1);
	pCanvas->Add(&m_tButton);
	forv(m_Buttons, i)
	{
		pCanvas->Add(&m_Buttons[i], 1);
		pCanvas->Add(&m_tButtons[i]);
	}
	return true;
}

void cInterfaceDaZao::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_NeedShow)
	{
		Init();
		g_pMainState->m_ItemSelect.Update();
		g_pMainState->m_ItemSelect.Move(m_xPos + 18, m_yPos + 132);
		m_Item[0] = -1;
		m_Item[1] = -1;
		m_tMoneyNeed.SetString(0);
//		m_MoneyNeed = 0;
		m_tMoneyHave.SetString(g_pCharacter->m_PcData.m_Money[0]);
		m_SelectMarks[0].m_NeedShow = false;
		m_SelectMarks[1].m_NeedShow = false;

		if (m_MoneyNeed)
		{
			forv(m_Buttons, i)
			{
				m_Buttons[i].m_NeedShow = true;
				m_tButtons[i].m_NeedShow = true;
			}
			m_Button.m_NeedShow = false;
			m_tButton.m_NeedShow = false;
		}
		else
		{
			forv(m_Buttons, i)
			{
				m_Buttons[i].m_NeedShow = false;
				m_tButtons[i].m_NeedShow = false;
			}
			m_Button.m_NeedShow = true;
			m_tButton.m_NeedShow = true;
		}
	}
	else
	{
		g_pMainState->m_ItemSelect.m_Describe.OnOff(false);
		cct::autoSave();
	}


}

bool cInterfaceDaZao::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	ResetButton();
	m_Select = -1;

	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	if (!isInRect(g_xMouse, g_yMouse, &m_Back))return true;
	g_pMainState->SetMouseOnMap(false);
	if (CheckOn(&m_Cancel, 0))return true;
	int k = g_pMainState->m_ItemSelect.Process(g_xMouse, g_yMouse);
	if (k > -1)
	{
		m_Select = k + 10;
		if (CheckL())return true;
	}
	for (int i = 0; i < 2; i++)
	{
		if (m_Head[i].m_NeedShow)
		{
			if (CheckOn(&m_Head[i], i + 1))
			{
				return true;
			}
		}
	}
	if (m_MoneyNeed == 0 && CheckOn(&m_Button, 5))
	{
		return true;
	}
	else if (m_MoneyNeed)
	{
		forv(m_Buttons, i)
		{
			if (CheckOn(&m_Buttons[i], 10000 + i))
			{
				return true;
			}
		}
	}
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	CheckRB();
	return true;
}

bool cInterfaceDaZao::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		m_Select = -1;
		return false;
	}
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		return true;
	case 1:
	case 2:
		m_Head[m_Select - 1].m_NeedShow = false;
		m_Item[m_Select - 1] = -1;
		m_SelectMarks[m_Select - 1].m_NeedShow = false;
		if (m_MoneyNeed)
		{
			m_tMoneyNeed.SetString(0);
			m_MoneyNeed = 0;
		}
		return true;
	case 5:
	{
		if (m_Item[0] < 0/* && m_Item[1] < 0*/)
		{
			return true;
		}

		sItem2& item1 = g_pCharacter->m_PcData.m_Items[m_Item[0]];
		if (m_Item[1] < 0)
		{
			if (!cct::isEquip(&item1))
			{
				return true;
			}
			if (item1.m_Property.size() <= 12)
			{
				return true;
			}

			if (!g_pCharacter->m_PcData.AddMoney(-50000, false))
			{
				g_pMainState->m_Tags.Add("盘缠不足");
			}
			g_pMainState->m_Tags.GetMoneyAndExp(-50000);

			auto skills = cct::getSpecialSkills();
			int s = skills[rand() % skills.size()];
			if (item1.m_Property[12] >= 0)
			{
				item1.m_Property[12] = s;
			}
			else if (rand() % 100 < 20)
			{
				item1.m_Property[12] = s;
			}
			return true;
		}
		
		sItem2& item2 = g_pCharacter->m_PcData.m_Items[m_Item[1]];
		if ((cct::isEquip(&item1) || cct::isEquipBB(&item1)) && item2.GetType() == 29)
		{
			if (item1.m_Property.empty())
			{
				g_pMainState->m_Tags.Add("装备未鉴定");
				return true;
			}
			if (!g_pMainState->m_ItemManage.XiangQian(item1, item2))
			{
				g_pMainState->m_Tags.Add("镶嵌失败");
				return true;
			}
			else
			{
				g_pMainState->m_Tags.Add("镶嵌成功");
				--item2.m_Num;
				g_pMainState->m_ItemSelect.Update();

				m_Head[1].m_NeedShow = false;
				m_Item[1] = -1;
				m_SelectMarks[1].m_NeedShow = false;
			}
		}
		return true;
	}
	case 10000:
	case 10001:
	case 10002:
	case 10003:
	case 10004:
	case 10005:
	{
		if (m_Item[0] < 0 || m_Item[1] < 0)
		{
			return true;
		}
		sItem2& item1 = g_pCharacter->m_PcData.m_Items[m_Item[0]];
		sItem2& item2 = g_pCharacter->m_PcData.m_Items[m_Item[1]];
		if (item1.GetType() == 28 && item1.GetID() == 8 && item2.GetType() == 28 && item2.GetID() == 7)
		{
			if (item1.m_Property.empty() || item2.m_Property.empty())
			{
				g_pMainState->m_Tags.Add("无效书铁");
				return true;
			}
			if (item1.m_Property[0] > item2.m_Property[0])
			{
				g_pMainState->m_Tags.Add("书 > 铁");
				return true;
			}
			vector<int> types = { 15 + rand() % 2, 19, rand() % 15, 17 + rand() % 2, 20, 21 };
			int t = types[m_Select - 10000];
			int id = g_pMainState->m_ItemManage.GetIDByLv(t, item1.m_Property[0]);
			item1.m_pItemData = g_pMainState->m_ItemManage.GetItem(t, id);
		//	item1.m_pItemData->SetLv(item1.m_Property[0]);

			g_pMainState->m_ItemManage.AutoItemProperty(&item1, false);
			g_pMainState->m_Tags.Add("打造成功");
			item2.m_Num = 0;

			g_pMainState->m_ItemSelect.Update();
			for (int i = 0; i < 2; ++i)
			{
				m_Head[i].m_NeedShow = false;
				m_Item[i] = -1;
				m_SelectMarks[i].m_NeedShow = false;
			}
			cct::autoSave();
		}
		return true;
	}
// 		if (m_MoneyNeed)
// 		{
// 			if (g_pCharacter->m_PcData.m_Money[0] < m_MoneyNeed)
// 			{
// 				g_pMainState->m_Tags.Add("盘缠不足");
// 				return true;
// 			}
// 			int weaponid = 0;
// 			sItem2* pItem = &g_pCharacter->m_PcData.m_Items[m_Item[weaponid]];
// 			sItem2* pItem2;
// 			if (pItem->GetType() == 41)
// 			{
// 				weaponid = 1;
// 				pItem = &g_pCharacter->m_PcData.m_Items[m_Item[weaponid]];
// 			}
// 			pItem2 = &g_pCharacter->m_PcData.m_Items[m_Item[!weaponid]];
// 			int lv = g_pMainState->m_ItemManage.GetlvByID(pItem->GetType(), pItem->GetID());
// 			vector<int>& prop = pItem->m_Property;
// 			if (0 == prop.size())
// 			{
// 				g_pMainState->m_Tags.Add("未鉴定");
// 				return true;
// 			}
// 			bool bSuccess = false;
// 			string text;
// 			if (lv < 60)
// 			{
// 				text = "60级以上的装备才能镶嵌";
// 			}
// 			else
// 				if (prop[2] == -1)
// 				{
// 				bSuccess = true;
// 				prop[2] = pItem2->GetID();
// 				}
// 				else
// 					if (prop[3] == -1)
// 					{
// 				if (lv > 89)
// 				{
// 					if (prop[2] != pItem2->GetID())
// 					{
// 						bSuccess = true;
// 						prop[3] = pItem2->GetID();
// 					}
// 					if (!bSuccess)text = "装备存在相同的符石";
// 				}
// 				else text = "90以下的装备只能镶嵌1个";
// 
// 					}
// 					else
// 						if (prop[4] == -1)
// 						{
// 				if (lv > 119)
// 				{
// 					if (prop[2] != pItem2->GetID())
// 						if (prop[3] != pItem2->GetID())
// 						{
// 						bSuccess = true;
// 						prop[4] = pItem2->GetID();
// 						}
// 					if (!bSuccess)text = "装备存在相同的符石";
// 				}
// 				else text = "120以下的装备只能镶嵌2个";
// 						}
// 						else
// 						{
// 							text = "最多打三个符石";
// 						}
// 			if (bSuccess)
// 			{
// 				g_pMainState->m_Tags.Add("镶嵌成功");
// 				g_pCharacter->m_PcData.AddMoney(-m_MoneyNeed, true);
// 				if (g_pCharacter->m_PcData.m_Items[m_Item[0]].GetType() == 41)
// 				{
// 					g_pCharacter->m_PcData.m_Items[m_Item[0]].m_Num -= 1;
// 				}
// 				else g_pCharacter->m_PcData.m_Items[m_Item[1]].m_Num -= 1;
// 				for (int i = 0; i < 2; i++)
// 				{
// 					m_Head[i].m_NeedShow = false;
// 					m_Item[i] = -1;
// 				}
// 				m_tMoneyNeed.SetString(0);
// 				m_MoneyNeed = 0;
// 			}
// 			else
// 			{
// 				g_pMainState->m_Tags.Add(text);
// 			}
//		}
//		break;
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
	{
		int head = -1;
		sItem2* item0 = &g_pCharacter->m_PcData.m_Items[m_Select - 10];
		if (cct::isEquip(item0) || cct::isEquipBB(item0) || (item0->GetType() == 28 && item0->GetID() == 8))
		{
			head = 0;
		}
		else if (item0->GetType() == 29 || (item0->GetType() == 28 && item0->GetID() == 7))
		{
			head = 1;
		}
		if (head >= 0)
		{
			m_Item[head] = m_Select - 10;
			auto& h = g_pMainState->m_ItemSelect.m_ItemHead[m_Select - 10];
			m_Head[head].Set(&h);
			m_Head[head].m_NeedShow = true;
			m_SelectMarks[head].m_NeedShow = true;
			m_SelectMarks[head].SetXY(h.GetX(), h.GetY() + 1);
		}
	}

// 		for (int i = 0; i < 2; i++)
// 		{
// 			if (m_Item[i] == -1)
// 			{
// 				sItem2* item0 = &g_pCharacter->m_PcData.m_Items[m_Select - 10];
// 				if (!item0->GetNum())return true;
// 				bool  type = CheckEquip(item0->GetType());
// 				if (!type)
// 					if (item0->GetType() == 41)type = 1;
// 				if (type)
// 				{
// 					m_Item[i] = m_Select - 10;
// 					m_Head[i].Set(&g_pMainState->m_ItemSelect.m_ItemHead[m_Select - 10]);
// 					m_Head[i].m_NeedShow = true;
// 					if (m_Item[0] > -1 && m_Item[1] > -1)
// 					{
// 						sItem2* pItem0 = &g_pCharacter->m_PcData.m_Items[m_Item[0]];
// 						sItem2* pItem1 = &g_pCharacter->m_PcData.m_Items[m_Item[1]];
// 						if (pItem0->GetType() == 41)
// 						{
// 							if (CheckEquip(pItem1->GetType()))
// 							{
// 								m_MoneyNeed = g_pMainState->m_ItemManage.GetlvByID(pItem1->GetType(), pItem1->GetID());
// 								m_MoneyNeed *= 1000;
// 								if (!m_MoneyNeed)m_MoneyNeed = 1;
// 								m_tMoneyNeed.SetString(m_MoneyNeed);
// 							}
// 						}
// 						else if (pItem1->GetType() == 41)
// 						{
// 							if (CheckEquip(pItem0->GetType()))
// 							{
// 								m_MoneyNeed = g_pMainState->m_ItemManage.GetlvByID(pItem0->GetType(), pItem0->GetID());
// 								m_MoneyNeed *= 1000;
// 								if (!m_MoneyNeed)m_MoneyNeed = 1;
// 								m_tMoneyNeed.SetString(m_MoneyNeed);
// 							}
// 						}
// 					}
// 					return true;
// 				}
// 			}
// 		}
	}
	return false;
}

bool cInterfaceDaZao::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	OnOff(false);
	return true;
}

bool cInterfaceDaZao::CheckEquip(int type)
{
	if (type < 22)return true;
	if (type > 31 && type < 35)return true;
	return false;
}

