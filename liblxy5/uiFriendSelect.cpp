#include "_global.h"



bool cInterSelectFriendItem::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;
	m_Back.Load(0xE3AEF018);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_TitleT.SetString("选择物品");
	m_TitleT.SetColor(RGB(255, 255, 255));
	Move(200, 30);
	return true;
}

bool cInterSelectFriendItem::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);
	pCanvas->Add(&m_TitleT);
	for (int i = 0; i < m_ItemNum; i++)
	{
		pCanvas->Add(&m_ItemHead[i], 1);
	}
	pCanvas->Add(&m_Cancel, 1);

	if (m_Select > -1)
	{
		pCanvas->Add(&m_MouseOnMark, 1);
	}
	return true;
}

bool cInterSelectFriendItem::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}

	m_MouseOnMark.m_NeedShow = false;

	m_Select = -1;
	ResetButton();

	if (m_bMoveMode)//移动
	{
		m_Select = 106;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}

	if (!isInRect(g_xMouse, g_yMouse, &m_Back))return true;
	g_pMainState->SetMouseOnMap(false);
	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = (g_xMouse - m_Rect.left) / 51 + 5 * ((g_yMouse - m_Rect.top) / 51);
		if (m_Select < m_ItemNum)
		{
			m_MouseOnMark.m_NeedShow = true;
			m_MouseOnMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY());
			if (CheckL())return true;
		}
	}
	//取消按钮
	if (CheckOn(&m_Cancel, 100))return true;

	m_Select = 0;
	if (CheckRB())return true;
	//准备移动
	m_Select = 107;
	CheckL();
	return true;
}

bool cInterSelectFriendItem::Set(int itemtype, int itemid, ulong headid)
{
	if (m_ItemNum > 19)return false;
	m_ItemType[m_ItemNum] = itemtype;
	m_ItemID[m_ItemNum] = itemid;
	m_ItemHead[m_ItemNum].Load(headid);
	m_ItemNum += 1;
	return true;
}

bool cInterSelectFriendItem::Move(int x, int y)
{

	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(x, y);
	m_Cancel.SetXY(x + 272, y + 5);
	m_TitleT.SetXY(x + 110, y + 5);

	for (int i = 0; i < 20; i++)
	{
		int xNum = (i) % 5;
		int yNum = (i) / 5;
		m_ItemHead[i].SetXY(xNum * 51 + 20 + x, yNum * 51 + 35 + y);
	}
	m_Rect.left = 20 + x;
	m_Rect.top = 35 + y;
	m_Rect.right = m_Rect.left + 255;
	m_Rect.bottom = m_Rect.top + 204;

	return true;
}

bool cInterSelectFriendItem::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 106://移动
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
	case 107://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		m_Sleeptime = 0;
		return true;
	case 100:
		OnOff(false);
		break;
	default:
		if (1)
		{
			switch (m_Mode)
			{
			case cInterSelectFriendItem::eQH装备:
				if (1)
				{
					g_pMainState->m_SelectFriendItem.GetSelect(m_pdata->m_weapontype, m_pdata->m_weaponid);
					g_pMainState->m_Tags.Add("完成装备设定");
				}
				break;
			case cInterSelectFriendItem::eQH技能:
				/*if (1)
				{
				int skillid,dustbin;
				g_pMainState->m_SelectFriendItem.GetSelect(dustbin, skillid);
				sSkill* skill= g_pMainState->m_SkillManager.GetPetSkill(skillid);

				for (int i = 0; i < m_pdata->m_PetSkillList.size(); i++)
				{
				if (skill->m_Id == m_pdata->m_PetSkillList[i])
				{
				g_pMainState->m_Tags.Add("已经存在这个技能了");
				return true;
				}
				for (int j = 0; j < skill->m_NumUnCompatible; j++)
				{
				if (skill->m_UnCompatible[j] == m_pdata->m_PetSkillList[i])
				{
				string text;
				text = "由于不兼容,";
				text+= g_pMainState->m_SkillManager.GetPetSkill(m_pdata->m_PetSkillList[i])->m_Name;
				text += "被顶掉了";
				m_pdata->m_PetSkillList[i] = skill->m_Id;

				g_pMainState->m_Tags.Add(text);
				g_pMainState->m_ChaKan.Set(*m_pdata);
				return true;
				}
				}
				}

				m_pdata->m_PetSkillList.push_back(skillid);
				g_pMainState->m_Tags.Add("得到了新的技能");
				g_pMainState->m_ChaKan.Set(*m_pdata);
				}*/
				break;
			case cInterSelectFriendItem::eQH技能2:
				if (1)
				{
					int skillid, dustbin;
					g_pMainState->m_SelectFriendItem.GetSelect(dustbin, skillid);
					sSkill* skill = g_pMainState->m_SkillManager.GetPetSkill(skillid);

					for (int i = 0; i < m_Pet->m_skillid.size(); i++)
					{
						if (skill->m_Id == m_Pet->m_skillid[i])
						{
							g_pMainState->m_Tags.Add("已经存在这个技能了");
							return true;
						}
						for (int j = 0; j < skill->m_NumUnCompatible; j++)
						{
							if (skill->m_UnCompatible[j] == m_Pet->m_skillid[i])
							{
								string text;
								text = "由于不兼容,";
								text += g_pMainState->m_SkillManager.GetPetSkill(m_Pet->m_skillid[i])->m_Name;
								text += "被顶掉了";
								m_Pet->m_skillid[i] = skill->m_Id;

								g_pMainState->m_Tags.Add(text);
//								g_pMainState->m_ChaKan.Set(m_pdata->m_BBList[m_pdata->m_FightBB]);
								return true;
							}
						}
					}

					m_Pet->m_skillid.push_back(skillid);
					g_pMainState->m_Tags.Add("得到了新的技能");
//					g_pMainState->m_ChaKan.Set(m_pdata->m_BBList[m_pdata->m_FightBB]);
				}
				break;

			case cInterSelectFriendItem::eQH坐骑装饰:
				if (1)
				{
					int dustbin;
					m_pdata->m_bZhuangShi = true;
					m_pdata->m_ZhuangShiRanse.partnum = 0;
					g_pMainState->m_SelectFriendItem.GetSelect(dustbin, m_pdata->m_ZhuangShiID);
					g_pMainState->m_Tags.Add("完成装饰设定");
				}
				break;
			case eQH出战:
				if (1)
				{
					m_pdata->m_FightBB = m_Select;
				}
				break;
			case eQH放生:
				if (1)
				{
					string text = "放生了";
					text += m_pdata->m_BBList[m_Select].m_name;
					g_pMainState->m_Tags.Add(text);
					if (m_Select < m_pdata->m_FightBB)
						m_pdata->m_FightBB -= 1;
					else
						if (m_Select == m_pdata->m_FightBB)
						{
						m_pdata->m_FightBB = m_pdata->m_BBList.size() - 2;
						}

					for (int i = m_Select; i < m_ItemNum - 1; i++)
					{
						m_ItemID[i] = m_ItemID[i + 1];
						m_ItemHead[i].Load(m_ItemHead[i + 1].m_NowID);
					}
					m_ItemNum -= 1;
					g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
					m_pdata->m_BBList.erase(m_pdata->m_BBList.begin() + m_Select);


				}
				break;
			default:
				ERRBOX;
				break;
			}
			int teamid = m_pdata->getIDinTeam();
			if (teamid > -1)
			{
				cObj* obj = g_pMainState->m_FightWorkList[teamid].m_pObj;
				cCharacter* pc = (cCharacter*)obj->m_pIndex;
				switch (m_Mode)
				{
				case cInterSelectFriendItem::eQH装备:
					if (1)
					{
						cPcData *data = &pc->m_PcData;
						sItem2 *item = &data->m_Equips[2];
						asert(item->m_Property.size(), "武器空属性(定制)");
						item->Set(m_pdata->m_weapontype, m_pdata->m_weaponid);
//						g_pMainState->m_ItemManage.AutoItemProperty(item, data, cct::get()->getDesbinOf武器(data->m_MengPaiID));
//						g_pMainState->m_ItemManage.AutoFuShi(item, data->m_Lv, eMengPai(data->m_MengPaiID));
						g_pMainState->m_InterfaceItem.Add(59, *data, item);
						g_pMainState->m_InterfaceItem.UseItem(59, *data);
						pc->m_PcData.m_pCharacterData2 = 0;
					}
					break;
				case cInterSelectFriendItem::eQH技能:
//					g_pMainState->m_SkillManager.SetPetSkill(&pc->m_PcData, m_ItemID[m_Select]);
					break;
				case cInterSelectFriendItem::eQH技能2:
					if (1)
					{
						cPropertyData* ppetdata;
						g_pMainState->m_FightWorkList[teamid + 5].m_pObj->GetPropertyData(ppetdata);
//						g_pMainState->m_SkillManager.SetPetSkill(ppetdata, m_ItemID[m_Select]);
					}
					break;
				case cInterSelectFriendItem::eQH坐骑装饰:
					if (1)
					{
						pc->m_PcData.m_ZuoQi.m_ZhuangShi.m_Num = 1;
						pc->m_PcData.m_ZuoQi.m_ZhuangShi.Set(31, m_pdata->m_ZhuangShiID);

					}
					break;
				case eQH出战:
					if (1)
					{
						string text = m_pdata->m_BBList[m_pdata->m_FightBB].m_name;
						if (g_pMainState->SetFightPet(teamid, m_Select))// m_ItemID[m_Select]);
						{
							text += "被设定为出战召唤兽";
						}
						else
						{
							text = "失败";
						}
						g_pMainState->m_Tags.Add(text);
					}
					break;
				case eQH放生:
					if (1)
					{
						if (0 == obj->m_TrueName.GetString().compare(m_pdata->m_Name))
						{
							g_pMainState->SetFightPet(teamid, -1);//
							cCharacter* pc = (cCharacter*)obj->m_pIndex;
							pc->m_PcData.RemovePet(m_Select);
							g_pMainState->SetFightPet(teamid, m_pdata->m_FightBB);//
						}


					}
					break;
				default:
					break;
				}
				obj->m_NowPos = -1;
				obj->Set(POS_STAND);
			}
		}
		break;
	}
	return true;
}

void cInterSelectFriendItem::OnOff(bool bshow)
{
	if (m_NeedShow == bshow)return;
	g_pMainState->InterfaceSetShow(this, bshow);
	if (m_NeedShow)
	{
		Init();
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}

bool cInterSelectFriendItem::CheckRB()
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

void cInterSelectFriendItem::SetMode(sFriendList* list, eQiangHuaMode mode)
{
	m_pdata = list;
	m_Mode = mode;
	m_ItemNum = 0;
	if (mode == eQH出战 || mode == eQH放生)
	{
		for (uint i = 0; i < list->m_BBList.size(); i++)
		{
			ulong head = g_pMainState->m_PetDataManager.GetPetData(list->m_BBList[i].m_modeid)->GetID(0, POS_BIGHEAD);
			Set(-1, i, head);
		}
	}
	if (mode == eQH技能2)
	{
		m_Pet = &m_pdata->m_BBList[m_pdata->m_FightBB];
	}
}
