#include "_global.h"



bool cInterfaceLearnSkill::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	ostringstream oss;
	switch (m_Select)
	{
	case 0://关闭
		OnOff(false);
		break;
	case 1://学习技能
		if (1)
		{
			LearnSkill();
			m_Button[0].SetFrame帧(1);
		}
		break;
	case 2://学习技能*5
		for (int i = 0; i < 5; i++)
		{
			if (!LearnSkill())break;
		}
		m_Button[1].SetFrame帧(1);
		break;
	case 6://移动
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
	case 7://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	default:
		SetSkillSelect(m_Select - 10);
		break;
	}
	return true;
}

void cInterfaceLearnSkill::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_NeedShow)
	{
		m_Sleeptime = 0;
		Init();
		Update();
		SetSkillSelect(0);
	}
	else
	{
		cct::autoSave();
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}

bool cInterfaceLearnSkill::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	for (int i = 0; i < 2; i++)
	{
		m_SkillSelectBack[i].Load(0xF151309F);
		m_SkillSelectBack[i].SetStatic(true);
		m_SkillSelectBack[i].SetFrame(1);
		m_SkillSelectBack[i].SetxOffset(12);
		m_SkillSelectBack[i].m_NeedShow = false;
	}
	m_Back.Load(0x9ED74AA6);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	for (int i = 0; i < 2; i++)
	{
		m_Button[i].Set(&g_pMainState->m_Button4);
		m_Button[i].m_bStatic = true;
		//	m_Button[i].Load(0x35A981D3);
		//	m_Button[i].SetStatic(true);
		m_tButton[i].SetColor(RGB(255, 255, 255));
	}
	m_tButton[0].SetString("学习*1");
	m_tButton[1].SetString("学习*5");
	for (int i = 0; i < 7; i++)
	{
		;
		m_tMengPaiSkill[i].SetColor(0);
		m_tMengPaiSkillLv[i].SetColor(0);
	}
	m_tSkillSelectHead.LockWidth(140);
	m_tMiaoShu.LockWidth(140);
	Move(g_half320 - m_Back.GetWidth() / 2, 5 + 20);
	return true;
}

bool cInterfaceLearnSkill::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(m_xPos, m_yPos);
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	for (int i = 0; i < 2; i++)
		m_Button[i].SetXY(m_Back.GetCenter() - 80 + 120 * i, m_yPos + 434);
	m_Rect.left = m_xPos + 13;
	m_Rect.right = m_Rect.left + 167;
	m_Rect.top = m_yPos + 65;
	m_Rect.bottom = m_Rect.top + 252;


	int xStart = m_Rect.left + 1;
	int yStart;
	for (int i = 0; i < 7; i++)
	{
		yStart = m_Rect.top + 1 + 36 * i;
		m_MengPaiSkillHead[i].SetXY(xStart, yStart);
		m_tMengPaiSkill[i].SetXY(xStart + 32, yStart + 7);
		m_tMengPaiSkillLv[i].SetXY(xStart + 111, yStart + 7);
	}
	m_tSkillSelectHead.SetXY(m_xPos + 210, m_yPos + 75);
	m_tMiaoShu.SetXY(m_xPos + 205, m_yPos + 210);

	xStart = m_xPos + 78;
	yStart = m_yPos + 360;
	m_tHaveExp.SetXY(xStart, yStart);
	m_tHaveMoney[0].SetXY(xStart, yStart + 24);
	m_tHaveMoney[1].SetXY(xStart, yStart + 46);
	xStart = m_xPos + 288;
	m_tNeedExp.SetXY(xStart, yStart);
	m_tNeedMoney.SetXY(xStart, yStart + 24);
	m_tHaveMoney[2].SetXY(xStart, yStart + 46);

	for (int i = 0; i < 2; i++)
	{
		m_tButton[i].SetXCenter(m_Button[i].GetCenter());
		m_tButton[i].SetY(m_Button[i].GetY() + 3);
		m_tButton[i].UpdateXCenter();
	}
	return true;
}

bool cInterfaceLearnSkill::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	g_pMainState->SetMouseOnMap(false);
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;


	if (CheckOn(&m_Cancel, 0))return true;
	for (int i = 0; i < 2; i++)
		if (CheckOn(&m_Button[i], 1 + i))return true;
	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = 10 + (g_yMouse - m_Rect.top) / 36;
		int xStart = m_MengPaiSkillHead[m_Select - 10].GetX() + 2;
		int yStart = m_MengPaiSkillHead[m_Select - 10].GetY() + 3;
		m_SkillSelectBack[0].SetXY(xStart, yStart);
		m_SkillSelectBack[1].SetXY(xStart + 83, m_SkillSelectBack[0].GetY());
		m_SkillSelectBack[0].m_NeedShow = true;
		m_SkillSelectBack[1].m_NeedShow = true;
		if (CheckL())return true;
	}
	else
	{
		m_SkillSelectBack[0].m_NeedShow = false;
		m_SkillSelectBack[1].m_NeedShow = false;
	}
	//准备移动
	m_Select = 7;
	if (CheckL())return true;
	m_Select = 0;
	if (CheckRB())return true;
	return true;
}

bool cInterfaceLearnSkill::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, 1);
	for (int i = 0; i < 2; i++)
	{
		pCanvas->Add(&m_Button[i], 1);
		pCanvas->Add(&m_tButton[i]);
	}
	pCanvas->Add(&m_Cancel, 1);

	pCanvas->Add(&m_SkillSelectBack[0], 1);
	pCanvas->Add(&m_SkillSelectBack[1], 1);


	for (int i = 0; i < 7; i++)
	{
		pCanvas->Add(&m_MengPaiSkillHead[i], 1);
		pCanvas->Add(&m_tMengPaiSkill[i]);
		pCanvas->Add(&m_tMengPaiSkillLv[i]);
	}
	pCanvas->Add(&m_tSkillSelectHead);
	pCanvas->Add(&m_tMiaoShu);
	pCanvas->Add(&m_tHaveExp);
	pCanvas->Add(&m_tNeedExp);
	pCanvas->Add(&m_tNeedMoney);
	for (int i = 0; i < 3; i++)
	{
		pCanvas->Add(&m_tHaveMoney[i]);
	}


	return true;
}

void cInterfaceLearnSkill::SetSkillSelect(int select)
{
	if (select < 0)return;
	if (m_SkillSelect != select)
	{
		if (m_SkillSelect > -1)
		{
			m_tMengPaiSkill[m_SkillSelect].SetColor(0);
			m_tMengPaiSkillLv[m_SkillSelect].SetColor(0);
		}

		m_SkillSelect = select;
		m_tMengPaiSkill[m_SkillSelect].SetColor(RGB(255, 0, 0));
		m_tMengPaiSkillLv[m_SkillSelect].SetColor(RGB(255, 0, 0));

		cMengPai* pMengPai = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PcData.m_MengPaiID);
		m_tSkillSelectHead.SetString(pMengPai->m_MainSkill[select].m_Text);
		m_tMiaoShu.SetString(pMengPai->m_MainSkill[select].m_Text2);
	}
	ostringstream oss;
	oss << GetMainSkillExp(g_pCharacter->m_PcData.m_MengPaiSkillLvs[select] + 1);
	m_tNeedExp.SetString(oss.str());
	oss.str("");
	int money = GetMainSkillMoney(g_pCharacter->m_PcData.m_MengPaiSkillLvs[select] + 1);
	oss << money;
	m_tNeedMoney.SetColor(GetPriceColor((int)money));
	m_tNeedMoney.SetString(oss.str());


}

void cInterfaceLearnSkill::Update()
{
	cCharacter* pC = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	cMengPai* pMengPai = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(pC->m_PcData.m_MengPaiID);
	for (int i = 0; i < 7; i++)
	{
		m_MengPaiSkillHead[i].Load(pMengPai->m_MainSkill[i].m_SmallHead);
		m_tMengPaiSkill[i].SetString(pMengPai->m_MainSkill[i].m_Name);

		ostringstream oss;
		oss << pC->m_PcData.m_MengPaiSkillLvs[i];
		oss << "/" << cct::MaxSkillLv;
		m_tMengPaiSkillLv[i].SetString(oss.str());
		if (m_SkillSelect == i)
		{
			m_tMengPaiSkill[i].SetColor(RGB(255, 0, 0));
			m_tMengPaiSkillLv[i].SetColor(RGB(255, 0, 0));
		}
		else
		{
			m_tMengPaiSkill[i].SetColor(0);
			m_tMengPaiSkillLv[i].SetColor(0);
		}
	}
	ostringstream oss;
	oss << pC->m_PcData.m_EXP;
	m_tHaveExp.SetString(oss.str());
	for (int i = 0; i < 3; i++)
	{
		oss.str("");
		oss << pC->m_PcData.m_Money[i];
		m_tHaveMoney[i].SetColor(GetPriceColor(pC->m_PcData.m_Money[i]));
		m_tHaveMoney[i].SetString(oss.str());
	}
}

bool cInterfaceLearnSkill::CheckRB()
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

bool cInterfaceLearnSkill::LearnSkill(bool cost)
{
// 	g_pMainState->m_Tags.Add("不用点,升级自动满技");
// 	return false;
	if (m_SkillSelect < -1 || m_SkillSelect >= g_pCharacter->m_PcData.m_MengPaiSkillLvs.size())
	{
		return false;
	}
	int& Skilllv = g_pCharacter->m_PcData.m_MengPaiSkillLvs[m_SkillSelect];
	if (Skilllv >= g_pCharacter->m_PcData.m_Lv + cct::LvGapFromRoleAndSkill)
	{
		g_pMainState->m_Tags.Add("技能已满");
		return false;
	}

	if (m_SkillSelect > 0 && Skilllv >= g_pCharacter->m_PcData.m_MengPaiSkillLvs[0])
	{
		g_pMainState->m_Tags.Add("不得超过主技能");
		return false;
	}

	if (Skilllv >= cct::MaxSkillLv)
	{
		g_pMainState->m_Tags.Add("技能已达上限");
		return false;
	}
	if (cost)
	{
		int needexp = GetMainSkillExp(Skilllv + 1);
		int needmoney = GetMainSkillMoney(Skilllv + 1);
	//	INT64 oldmoney[3];
	//	INT64 oldexp;
	//	for (int i = 0; i < 3; i++)
	//		oldmoney[i] = g_pCharacter->m_PcData.m_Money[i];
	//	oldexp = g_pCharacter->m_PcData.m_EXP;


		if (!g_pCharacter->m_PcData.AddExp(-needexp, 0, false))
		{

		//	g_pCharacter->m_PcData.m_EXP = oldexp;
			g_pMainState->m_Tags.Add("经验不足");
			return false;
		}
		if (!g_pCharacter->m_PcData.AddMoney(-needmoney,0,  0, false))
		{

		//	g_pCharacter->m_PcData.m_EXP = oldexp;
			g_pMainState->m_Tags.Add("盘缠不足");
			return false;
		}

	}
//	Skilllv += 1;
//	g_pMainState->m_SkillManager.lvUpMainSkill(g_pCharacter->m_PcData, 1, m_SkillSelect);
	if (m_SkillSelect == 0)
	{
		forr(g_pCharacter->m_PcData.m_MengPaiSkillLvs, kk)
		{
			++g_pCharacter->m_PcData.m_MengPaiSkillLvs[kk];
		}
	}
	else
	{
		++Skilllv;
	}

	g_pMainState->m_State.UpDatePcDate();
	Update();
	SetSkillSelect(m_SkillSelect);
	g_pMainState->m_PCHead.UpdatePcExp();
	return true;
}

