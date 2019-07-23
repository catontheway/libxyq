#include "_global.h"



bool cInterfacePetSkill::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_back, 1, true);
	pCanvas->Add(&m_Cancel, 1);
	if (m_bDaShuMode)
	{
		pCanvas->Add(&m_DaShuBack, 1, 1);
		pCanvas->Add(&m_Cancel2, 1);
		pCanvas->Add(&m_DaShuText[0]);
		if (m_DaShuText[1].m_NeedShow)
			pCanvas->Add(&m_DaShuText[1]);
		for (int i = 0; i < m_DaShuNum; i++)
		{
			pCanvas->Add(&m_DaShuHead[i], 1);
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			pCanvas->Add(&m_TPetProPerty[i]);
		}
	}

	for (int i = 0; i < m_NumSkill; i++)
	{
		pCanvas->Add(&m_SkillHead[i], 1);
	}
	pCanvas->Add(&m_NextPage, 1);

	for (int i = 0; i < 6; i++)
	{
		if (m_pEquip[i])
		{
			pCanvas->Add(&m_EquipBackp[i], 1);
			pCanvas->Add(&m_EquipHead[i], 1);
		}
	}
	m_Describe.Show(pCanvas);
	return true;
}

bool cInterfacePetSkill::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_EquipBack.Load(0xA393A808);
	for (int i = 0; i < 6; i++)
	{
		m_EquipBackp[i].Set(&m_EquipBack);
	}
	for (int i = 0; i < 9; i++)
		m_TPetProPerty[i].SetColor(RGB(0, 0, 0));
	m_Describe.Init();
	m_Describe.m_NeedShow = false;
	m_SkillSelect = -1;
	m_back.Load(1338020705);
	m_back.SetStatic(true);

	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Cancel2.Set(&g_pMainState->m_Cancel);
	m_Cancel2.m_bStatic = true;


	////////////////////////////////////////////////////////////////////////// 打书 呵呵哒
	m_DaShuBack.Load(0x1D0C0B23); //0x907E024C
	m_DaShuBack.SetStatic(true);
	m_DaShuBack.SetShowWidth(180);
	m_DaShuBack.SetShowHeight(220); 
	m_bDaShuMode = false;
	m_DaShuText[0].SetColor(RGB(255, 255, 255));
	m_DaShuText[1].SetColor(RGB(255, 255, 255));
	m_DaShuText[0].m_hFont = g_pMainState->m_hFont[0];
	m_DaShuText[1].m_hFont = g_pMainState->m_hFont[0];

	for (int i = 0; i < 9; i++)
		m_TPetProPerty[i].SetXY(0, 0);
	m_NextPage.Load(0xCB50AB1D);
	m_NextPage.SetStatic(true);
	return true;
}

bool cInterfacePetSkill::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	ResetButton();
	for (int i = 0; i < 6; i++)
	{
		if (m_pEquip[i])
			if (isOn(g_xMouse, g_yMouse, m_EquipBackp[i].m_PreShowRect))
			{
			g_pMainState->m_InterfaceItem.UpDateItemDate(m_Describe, m_pEquip[i]);
			g_pMainState->SetMouseOnMap(false);
			return true;
			}
	}
	if (!isOn(g_xMouse, g_yMouse, m_back.m_PreShowRect))
	{
		if (m_Describe.m_NeedShow)
			m_Describe.OnOff(false);
		return false;
	}
	g_pMainState->SetMouseOnMap(false);
	if (CheckRB())return true;
	//记录鼠标等止的时间
	if (0 == g_pMainState->Mouse.GetXDelta() && 0 == g_pMainState->Mouse.GetYDelta())
	{
		m_ItemDataTime += 1;
	}
	else
	{
		m_ItemDataTime = 0;
		if (m_Describe.m_NeedShow)
		{
			m_Describe.m_NeedShow = false;
			g_pMainState->m_Canvas.SetRedraw(m_Describe.m_Back.m_PreShowRect);
		}
	}
	if (CheckOn(&m_Cancel, 61))return true;
	cCharacter* pC = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID/*m_FightID*/].m_pObj->m_pIndex;

	if (m_bDaShuMode)
	{
		if (isOn(g_xMouse, g_yMouse, m_DaShuBack.m_PreShowRect))
		{
			if (CheckOn(&m_Cancel2, 62))return true;

			for (int i = 0; i < m_DaShuNum; i++)
			{
				if (isOn(g_xMouse, g_yMouse, m_DaShuHead[i].m_PreShowRect))
				{
					m_DashuSkillSelect = i;

					if (m_ItemDataTime > 10)//更新技能说明
					{
						m_Describe.m_NeedShow = true;
						int skillid = pC->m_PcData.m_Items[m_DaShuItemId[m_DashuSkillSelect]].GetID();
						sSkill* pSkill = g_pMainState->m_SkillManager.GetPetSkill(skillid);
						sItem* Item = g_pMainState->m_ItemManage.GetItem(28, 0);
						string text[3];
						text[0] = Item->m_Name;
						text[1] = Item->m_Text;
						text[2] = pSkill->m_Name;
						m_Describe.Set(g_xMouse, g_yMouse, pSkill->m_BigHead, 3, text);
					}
					m_Select = 101;
					return CheckL();
				}
			}
		}
		return true;
	}

	if (CheckOn(&m_NextPage, 11))return true;

	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_SkillSelect = (g_xMouse - m_Rect.left) / 42 + ((g_yMouse - m_Rect.top) / 42) * 4;
		if (m_ItemDataTime > 10)
		{

			if (m_SkillSelect < m_NumSkill)
			{
				m_Describe.m_NeedShow = true;
				sSkill* pSkill = m_pPetData->m_petSkills[m_SkillSelect + m_SkillPage * 12];
				string text[3];
				int textnum = 2;
				text[0] = pSkill->m_Name;
				text[1] = pSkill->m_Text;
				if (pSkill->m_SkillType != 7)
				{
					textnum = 3;
					ostringstream oss;
					oss << "消耗:";
					oss << pSkill->m_tCost;
					text[2] = oss.str();
				}
				m_Describe.Set(g_xMouse, g_yMouse, pSkill->m_BigHead, textnum, text);
			}
		}
		m_Select = 100;
		return CheckL();//打书
	}



	return false;
}

void cInterfacePetSkill::UpdateData(cPropertyData* data, sZiZhi& zz, bool candashu)
{
	if (!data)
	{
		for (int i = 0; i < 9; i++)
			m_TPetProPerty[i].SetString("");
		m_NumSkill = 0;
		return;
	}
	if (m_pPetData == data)
	{
//		return;
	}
	m_bCanDaShu = candashu;
	m_pPetData = data;
	m_SkillPage = 1;
	NextPage();

	for (int i = 0; i < 6; i++)
	{
		if (m_pPetData->m_Equips[i].GetNum())
		{
			m_pEquip[i] = &m_pPetData->m_Equips[i];
			m_EquipHead[i].Load(g_pMainState->m_ItemManage.GetItem(m_pEquip[i]->GetType(), m_pEquip[i]->GetID())->m_SmallHead);
		}
		else m_pEquip[i] = 0;
	}

	vector<int> zzs = {
		zz.atk,
		zz.def,
		zz.hp,
		zz.mag,
		zz.speed,
		zz.avoid
	};
	bool isEmpty = false;
	ostringstream oss;
	for (int i = 0; i < 6; ++i)
	{
		oss.str("");
		int zz = zzs[i];
// 		if (cct::get()->isSpecialOrZZ(zz))
// 		{
// 			oss << g_pMainState->m_SkillManager.GetSpecialSkill(zz)->m_Name;
// 		}
// 		else
		if (zz > 0)
		{
			oss << zz;
		}
		else
		{
			isEmpty = true;
			oss.str("");
		}
		m_TPetProPerty[i].SetString(oss.str());
	}

	// 	m_TPetProPerty[0].SetString(oss.str());
	// 	oss.str("");
	// 	oss << pPetData->m_ZiZhi.m_DEFZZ;
	// 	m_TPetProPerty[1].SetString(oss.str());
	// 	oss.str("");
	// 	oss << pPetData->m_ZiZhi.m_HPZZ;
	// 	m_TPetProPerty[2].SetString(oss.str());
	// 	oss.str("");
	// 	oss << pPetData->m_ZiZhi.m_MAGZZ;
	// 	m_TPetProPerty[3].SetString(oss.str());
	// 	oss.str("");
	// 	oss << pPetData->m_ZiZhi.m_SPDZZ;
	// 	m_TPetProPerty[4].SetString(oss.str());
	// 	oss.str("");
	// 	oss << pPetData->m_ZiZhi.m_AVOIDZZ;
	// 	m_TPetProPerty[5].SetString(oss.str());
	oss.str(""); // 0xFF
	if (!isEmpty)
	{
		oss << 1000 + rand() % 9000;
	}
	m_TPetProPerty[6].SetString(oss.str());

	oss.str("");
// 	if (zz.grow < cct::get()->putMenpaiSkills.size())
// 	{
// 		int id = cct::get()->putMenpaiSkills[zz.grow];
// 		oss << g_pMainState->m_SkillManager.GetMengPaiSkill(id)->m_Name;
// 	}
// 	else
	if (zz.grow > 0)
	{
		float groving = (float)zz.grow;
		groving /= 100;
		oss << groving;
	}
	m_TPetProPerty[7].SetString(oss.str());

	oss.str(""); //缺金
	if (!isEmpty)
	{
		static vector<string> _5s = { "金", "木", "水", "火", "土" };
		oss << _5s[rand() % _5s.size()];
	}
	m_TPetProPerty[8].SetString(oss.str());
}

bool cInterfacePetSkill::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	// 当然了,现在只有主角有背包
	cCharacter* pC = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID/*m_FightID*/].m_pObj->m_pIndex;
	switch (m_Select)
	{
	case 11:
		if (m_pPetData)
		{
			NextPage();

			m_NextPage.SetFrame(1);
			m_NextPage.m_bMove = true;
		}
		break;

	case 61:
		if (1)
		{
			OnOff(false);
			m_Cancel.SetFrame帧(0);
		}
		return true;
	case 62: //取消
		if (1)
		{
			m_bDaShuMode = false;
			g_pMainState->m_Canvas.SetRedraw(m_DaShuBack.m_PreShowRect);
			m_Cancel2.SetFrame帧(0);
		}
		return true;
	case 100://打书		
		if (m_bCanDaShu && g_StateType != STATE_FIGHT)
		{
			if (InitDaShuMode())
			{
				g_pMainState->m_Tags.Add("只扫描队长背包");
	// 			if (m_SkillSelect < m_NumSkill)
	// 			{
	// 				m_DaShuText[0].SetString("");//替换技能
	// 				m_DaShuText[1].m_NeedShow = true;
	// 				string str2 = "替换:";
	// 				str2 += m_pPetData->m_petSkills[m_SkillSelect + m_SkillPage * 12]->m_Name;
	// 				m_DaShuText[1].SetString(str2);
	// 			}
	// 			else
	// 			{
	// 				m_SkillSelect = m_NumSkill;
	// 				m_DaShuText[0].SetString("");//增加技能
	// 				m_DaShuText[1].m_NeedShow = false;
	// 			}
				m_DaShuBack.m_bMove = true;
				m_bDaShuMode = true;
			}
		}
		return true;
	case 101:
	{
		//确保角色有这本书
		int  itemnum = m_DaShuItemId[m_DashuSkillSelect];
		sItem2* pItem = &pC->m_PcData.m_Items[itemnum];
		if (pItem->GetNum())
		{
			if (40 == pItem->GetType())
			{
				//sItem* pit = pItem->m_pItemData;
				int itemid = pItem->GetID();
				int num = m_pPetData->m_NumofBBSkill;
				int idx;
				if (num < 2)
				{
					idx = -1;
				}
				else if (num < 16)
				{
					// 2+1 55.5%
					// 3+1 35.5%
					// 4+1 20.9%
					// 5+1 15.5%
					// 6+1 10.0%
					// 7+1  7.0%
					// 8+1  5.0%
					// 9+1  3.0%
					// 10+1 2.0%
					// 11+1 1.0%
					// 12+1 0.7%
					// 13+1 0.5%
					// 14+1 0.2%
					// 15+1 0.1%
					vector<int> rs = { 555, 355, 200, 155, 100, 70, 50, 30, 20, 10, 7, 5, 2, 1 };
					if (rand() % 1000 < rs[num - 2])
					{
						idx = -1;
					}
					else
					{
					   idx = rand() % num;
					}
				}
				else
				{
					idx = rand() % num;
				}

				if (!m_pPetData->AddSkill(itemid, idx/*m_SkillSelect + 12 * m_SkillPage*/))
				{
					g_pMainState->m_Tags.Add("打书失败");
					return true;
				}
// 				int pos = m_SkillSelect + 12 * m_SkillPage;
// 				int conflict = g_pMainState->m_SkillManager.SetPetSkill(m_pPetData, itemid, pos);
// 				if (-1 < conflict)
// 				{
// 					//此技能与某技能矛盾
// 					m_bDaShuMode = false;
// 					g_pMainState->m_Canvas.SetRedraw(m_DaShuBack.m_PreShowRect);
// 					ostringstream oss;
// 					oss << m_pPetData->m_petSkills[conflict]->m_Name;
// 					oss << "与此技能不能共存";
// 					g_pMainState->m_Tags.Add(oss.str());
// 					return true;
// 				}
				NextPage(false);
				/*	m_SkillHead[m_SkillSelect].Load(m_pPetData->m_pPetSkill[m_SkillSelect + 12 * m_SkillPage]->m_BigHead);
				m_SkillHead[m_SkillSelect].m_bMove = true;
				m_NumSkill = m_pPetData->m_NumofBBSkill;*/
				pItem->m_Num -= 1;

			}
		}
		m_bDaShuMode = false;
		m_back.m_bMove = true;
	}
		return true;
	}
	return true;
}

bool cInterfacePetSkill::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;

	int xstart = x + 20;
	int ystart = y + 313;
	MoveSkillHead(xstart, ystart);

	m_back.SetXY(m_xPos, m_yPos);
	m_DaShuBack.SetX(m_back.m_Picture.m_x + 15);
	m_DaShuBack.SetY(m_back.m_Picture.m_y + 85);
	m_Cancel.SetXY(m_back.GetX() + 185, m_back.GetY() + 5);
	m_Cancel2.SetXY(m_DaShuBack.GetX() + 162, m_DaShuBack.GetY() + 3);
	for (int i = 0; i < 2; i++)
	{
		m_DaShuText[i].SetXCenter(m_DaShuBack.GetX() + m_DaShuBack.GetWidth() / 2);
	}
	m_DaShuText[0].UpdateXCenter();
	m_DaShuText[0].SetY(m_DaShuBack.GetY() + 3);
	m_DaShuText[1].SetY(m_DaShuBack.GetY() + 198/* + 50*/);
	for (int i = 0; i < 5/*3*/; i++)
	{
		for (int j = 0; j < 4/*3*/; j++)
		{
			int k = i * 4/*3*/ + j;
			m_DaShuHead[k].SetX(m_DaShuBack.GetX() + 5 + j * 44);
			m_DaShuHead[k].SetY(m_DaShuBack.GetY() + 5 + i * 44);
		}
	}

	m_NextPage.m_Picture.m_x = m_xPos + 191;
	m_NextPage.m_Picture.m_y = m_yPos + 412;


	xstart = m_xPos + 128;
	for (int i = 0; i < 9; ++i)
	{
		m_TPetProPerty[i].SetXY(xstart, m_yPos + 100 + i * 23);
	}
// 	m_TPetProPerty[8].SetXY(xstart, m_yPos + 284);
// 	m_TPetProPerty[7].SetXY(xstart, m_yPos + 261 - 1);
// 	m_TPetProPerty[6].SetXY(xstart, m_yPos + 238);
// 	m_TPetProPerty[5].SetXY(xstart, m_yPos + 215 - 4);
// 	m_TPetProPerty[4].SetXY(xstart, m_yPos + 192 - 3);
// 	m_TPetProPerty[3].SetXY(xstart, m_yPos + 169 - 2);
// 	m_TPetProPerty[2].SetXY(xstart, m_yPos + 146 - 1);
// 	m_TPetProPerty[1].SetXY(xstart, m_yPos + 123);
// 	m_TPetProPerty[0].SetXY(xstart, m_yPos + 100 + 2);
	for (int i = 0; i < 6; i++)
	{
		m_EquipBackp[i].SetXY(m_xPos + 20 + i * 60, m_yPos + 38);
		m_EquipHead[i].SetXY(m_EquipBackp[i].GetX(), m_EquipBackp[i].GetY());
	}
	return true;
}

bool cInterfacePetSkill::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	if (m_bDaShuMode)
	{
		m_bDaShuMode = false;
		g_pMainState->m_Canvas.SetRedraw(m_DaShuBack.m_PreShowRect);
	}
	else
	{
		OnOff(false);
	}
	return true;
}

void cInterfacePetSkill::OnOff(bool NeedShow)
{
	g_pMainState->m_Canvas.SetRedraw(m_back.m_PreShowRect);
	m_NeedShow = NeedShow;
	if (!NeedShow)
	{
		m_Describe.OnOff(false);
	}
}

void cInterfacePetSkill::MoveSkillHead(int x, int y)
{
	int xi, yi;
	for (int i = 0; i < 12; i++)
	{
		xi = i % 4;
		yi = i / 4;
		m_SkillHead[i].SetXY(x + 42 * xi, y + 42 * yi);
	}
	m_Rect.left = x;
	m_Rect.right = m_Rect.left + 42 * 4;
	m_Rect.top = y;
	m_Rect.bottom = m_Rect.top + 42 * 3;
}

void cInterfacePetSkill::NextPage(bool bnext)
{
	if (bnext)
		m_SkillPage = !m_SkillPage;
	m_NumSkill = m_pPetData->m_NumofBBSkill - 12 * m_SkillPage;
	if (m_NumSkill > 12)m_NumSkill = 12;
	if (m_NumSkill < 0)m_NumSkill = 0;
	for (int i = 0; i < m_NumSkill; i++)
	{
		m_SkillHead[i].Load(m_pPetData->m_petSkills[i + 12 * m_SkillPage]->m_BigHead);
	}
}



bool cInterfacePetSkill::InitDaShuMode()
{
	if (0 == g_pMainState)return false;
	auto obj = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID/*m_FightID*/].m_pObj;
	if (INDEXTYEP_CHARACTER != obj->GetDataType())return false;

	cCharacter* p = (cCharacter*)obj->m_pIndex;
	m_DaShuNum = 0;
	sItem2* pItem = 0;
	forv (p->m_PcData.m_Items, i)//检测道具和行囊
	{
		pItem = &p->m_PcData.m_Items[i];
		if (pItem->m_Num > 0)
		{
			if (40 == pItem->GetType())
			{
				if (20/*9*/ == m_DaShuNum)
					return true;
				m_DaShuItemId[m_DaShuNum] = i;
				m_DaShuHead[m_DaShuNum].Load(g_pMainState->m_SkillManager.GetPetSkill(pItem->GetID())->m_BigHead);
				m_DaShuNum += 1;
			}
		}
	}
	if (m_DaShuNum == 0)
		return false;
	m_DaShuText[1].UpdateXCenter();
	return true;
}