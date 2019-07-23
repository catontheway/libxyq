#include "_global.h"



void cInterfaceJiNeng::Set(ulong ID)
{
	if (m_Data.m_NowID == ID)return;
	m_Data.Load(ID);
	if (ID == m_ZhuJiNeng)//主技能
	{
		cCharacter* pC = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
		cMengPai* pMengPai = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(pC->m_PcData.m_MengPaiID);
		if (pMengPai)
			for (int i = 0; i < 7; i++)
			{
			m_ZhuJiNengHead[i].Load(pMengPai->m_MainSkill[i].m_BigHead);
			}

	}
}

bool cInterfaceJiNeng::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	m_bUpdateJiNeng = false;
	//背景
	pCanvas->Add(&m_Data, 1, true);
	pCanvas->Add(&m_Cancel, 1);
	//按钮
	pCanvas->Add(&m_SmB, 1);
	pCanvas->Add(&m_FuZhuB, 1);
	pCanvas->Add(&m_XiuLianB, 1);

	for (int i = 0; i < 3; i++)
		pCanvas->Add(&m_BText[i]);

	if (m_Data.m_NowID == m_ZhuJiNeng)
	{
		ostringstream oss;

		for (int i = 0; i < 7; i++)
		{
			pCanvas->Add(&m_ZhuJiNengHead[i], 1);
			pCanvas->Add(&m_ZhuJiNengLv[i]);
		}
//		if (m_JiNengHead > 0)
		{
			for (int i = 0; i < m_JiNengHeadNum; i++)
			{
				pCanvas->Add(&m_JiNengHead[i], 1);
			}

			for (int i = 0; i < m_NumMiaoShu; i++)
				pCanvas->Add(&m_MiaoShu[i]);

			for (int i = 0; i < 6; i++)
			{
				if (m_SpecialSkill[i].m_NowID)
					pCanvas->Add(&m_SpecialSkill[i], 1);
			}
		}
	}
	else if (m_Data.m_NowID == m_XiuLian)
	{
		if (m_JiNengSelect > -1)
		{
			pCanvas->Add(&m_SelectBackXiuLian, 1);

		}
		for (int i = 0; i < 8; i++)
			pCanvas->Add(&m_TXiuLian[i]);

	}
	else if (m_Data.m_NowID == m_FuZhuJiNeng)
	{
//		if (m_JiNengHead > 0)
		{
			for (int i = 0; i < m_JiNengHeadNum; i++)
			{
				pCanvas->Add(&m_JiNengHead[i], 1);
			}
		}
		if (m_JiNengSelect > -1)
		{
			pCanvas->Add(&m_MiaoShu[0]);
			pCanvas->Add(&m_MiaoShu[1]);
		}
		for (int i = 0; i < m_JiNengHeadNum; i++)
		{
			pCanvas->Add(&m_FuZhuJiNengLv[i]);
		}
	}
	return true;
}

cInterfaceJiNeng::cInterfaceJiNeng()
{
	m_JiNengSelect = -1;
	m_SkillSelect = -1;
}

bool cInterfaceJiNeng::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_SelectBackXiuLian.Load(0x436592D8);
	ccm::get()->pushWdf("属性技能面板", 0x436592D8);
	m_SelectBackXiuLian.SetStatic(true);
	m_SelectBackXiuLian.m_Picture.m_bShadow = 50;
	m_SelectBackXiuLian.SetShowWidth(380);
	m_SelectBackXiuLian.SetxOffset2(10);
	m_TXiuLian.resize(8);
	m_BText.resize(3);
	for (int i = 0; i < 8; i++)
	{
		m_TXiuLian[i].SetColor(0);
		m_TXiuLian[i].m_hFont = g_pMainState->m_hFont[0];
	}
	for (int i = 0; i < 3; i++)
	{
		m_BText[i].m_hFont = g_pMainState->m_hFont[0];
		m_BText[i].SetColor(RGB(255, 255, 255));
	}
	m_BText[0].SetString("师门技能");
	m_BText[1].SetString("辅助技能");
	m_BText[2].SetString("修炼技能");

	m_XiuLian = 993909921;
	m_ZhuJiNeng = 1044547630;
	m_FuZhuJiNeng = 1560928702;

	ccm::get()->pushWdf("属性修炼面板", 993909921);
	ccm::get()->pushWdf("属性辅助面板", 1044547630);
	ccm::get()->pushWdf("属性修炼面板", 1560928702);

	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;

	m_SmB.Set(&g_pMainState->m_Button4);
	m_FuZhuB.Set(&g_pMainState->m_Button4);
	m_learnSkillB.Set(&g_pMainState->m_Button4);
	m_XiuLianB.Set(&g_pMainState->m_Button4);

	Set(m_ZhuJiNeng);

	m_learnSkillB.m_bStatic = true;
	m_FuZhuB.m_bStatic = true;
	m_SmB.m_bStatic = true;
	m_XiuLianB.m_bStatic = true;

	m_MiaoShu.resize(4);
	for (int i = 0; i < 4; i++)
	{
		m_MiaoShu[i].m_hFont = g_pMainState->m_hFont[0];
		m_MiaoShu[i].LockWidth(132);
	}

	for (int i = 0; i < 7; i++)
	{
		m_ZhuJiNengLv[i].SetColor(0);
	}
	Move(g_640 - 640, g_half240 - 240);
	MoveXiuLian(m_xPos, m_yPos);
	return true;
}

bool cInterfaceJiNeng::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (m_bMoveMode)//移动
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			g_pMainState->SetMouseOnMap(false);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
		}
		else	m_bMoveMode = false;
		return true;
	}
	ResetButton();
	m_Select = -1;
	if (!isOn(g_xMouse, g_yMouse, m_Data.m_PreShowRect))return true;

	g_pMainState->SetMouseOnMap(false);
	if (CheckOn(&m_Cancel, 0))
		return true;
	if (1 != m_SmB.GetNowFrame())
		if (CheckOn(&m_SmB, 1))return true;
	if (1 != m_FuZhuB.GetNowFrame())
		if (CheckOn(&m_FuZhuB, 2))return true;
	if (3 != m_learnSkillB.GetNowFrame())
		if (CheckOn(&m_learnSkillB, 3))return true;
	if (1 != m_XiuLianB.GetNowFrame())
		if (CheckOn(&m_XiuLianB, 4))return true;
	//如果是主技能状态
	if (m_Data.m_NowID == m_ZhuJiNeng)
	{
		int i;
		for (i = 0; i < 7; i++)
		{
			if (isOn(g_xMouse, g_yMouse, m_ZhuJiNengHead[i].m_PreShowRect))
			{
				m_dustSkillSelect = i;
				m_Select = 10;
				return CheckL();
			}
		}
		for (i = 0; i < m_JiNengHeadNum; i++)
		{
			if (isOn(g_xMouse, g_yMouse, m_JiNengHead[i].m_PreShowRect))
			{
				m_dustSkillSelect = i;
				m_Select = 11;
				return CheckL();
			}
		}
		for (i = 0; i < 6; i++)//特技
		{
			if (m_SpecialSkill[i].m_NowID)
				if (isOn(g_xMouse, g_yMouse, m_SpecialSkill[i].m_PreShowRect))
				{
				m_dustSkillSelect = i;
				m_Select = 14;
				return CheckL();
				}
		}

	}
	else
		if (m_Data.m_NowID == m_FuZhuJiNeng)
		{
		for (int i = 0; i < m_JiNengHeadNum; i++)
		{
			if (isOn(g_xMouse, g_yMouse, m_JiNengHead[i].m_PreShowRect))
			{
				m_dustSkillSelect = i;
				m_Select = 12;
				return CheckL();
			}
		}
		}
		else
			if (m_Data.m_NowID == m_XiuLian)
			{
		for (int i = 0; i < 8; i++)
		{
			if (isOn(g_xMouse, g_yMouse, m_TXiuLian[i].m_PreShowRect))
			{
				m_dustSkillSelect = i;
				m_Select = 13;
				return CheckL();
			}
		}

			}
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		m_bMoveMode = true;
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
	}
	else
		if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
		{
		OnOff(false);
		}

	return false;
}

bool cInterfaceJiNeng::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Data.SetXY(m_xPos, m_yPos);
	m_SmB.SetXY(m_xPos + 25, m_yPos + 30);
	m_FuZhuB.SetXY(m_xPos + 130, m_yPos + 30);
	m_XiuLianB.SetXY(m_xPos + 235, m_yPos + 30);

	m_learnSkillB.SetXY(m_xPos + 340, m_yPos + 435);
	m_Cancel.SetXY(x + 430, y + 5);
	int newpos;
	newpos = m_SmB.GetY() + 4;
	for (int i = 0; i < 3; i++)
		m_BText[i].SetY(newpos);
	for (int i = 0; i < 3; i++)
	{
		newpos = m_xPos + 63 + i * 105;
		m_BText[i].SetXCenter(newpos);
	}
	for (int i = 0; i < 3; i++)
	{
		m_BText[i].UpdateXCenter();
	}
	m_SelectBackXiuLian.SetX(x + 14);
	for (int i = 0; i < 6; i++)
	{
		m_SpecialSkill[i].SetX(x + 40 + i * 66);
		m_SpecialSkill[i].SetY(y + 384);
	}

	if (m_Data.m_NowID == m_ZhuJiNeng)
	{
		MoveMainSkill(m_xPos, m_yPos);
	}
	else
		if (m_Data.m_NowID == m_FuZhuJiNeng)
		{
		MoveFuZhuSkill(m_xPos, m_yPos);
		}
		else
			if (m_Data.m_NowID == m_XiuLian)
			{
		MoveXiuLian(m_xPos, m_yPos);
			}

	return true;
}

bool cInterfaceJiNeng::CheckL()
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
		if (1)
		{
			OnOff(false);
			m_Cancel.SetFrame帧(1);
		}
		return true;
	case 1: //SM技能
		SetMode(m_ZhuJiNeng);
		m_frampre = 0;
		break;
	case 2://辅助技能
		SetMode(m_FuZhuJiNeng);
		m_frampre = 0;
		break;
	case 3: //学习技能
		if (1)
		{

		}
		break;
	case 4: //修练技能
		SetMode(m_XiuLian);
		MoveXiuLian(m_xPos, m_yPos);
		m_frampre = 0;
		break;
	case 10: //门派主技能
		m_JiNengSelect = m_dustSkillSelect;
		m_SkillSelect = -1;
		m_MiaoShuID = 10;
		UpdateJiNeng();

		break;
	case 11:
		m_SkillSelect = m_dustSkillSelect;
		m_MiaoShuID = 11;
		UpdateJiNeng();

		break;
	case 12:
		m_JiNengSelect = m_dustSkillSelect;

		UpdateJiNeng();
		break;
	case 13:
		m_JiNengSelect = m_dustSkillSelect;
		UpdateJiNeng();
		break;
	case 14:
		m_SpeciallSkillSelect = m_dustSkillSelect;
		m_MiaoShuID = 14;
		UpdateJiNeng();

		break;
	default:
		ERRBOX;
		break;
	}
	return true;
}


bool cInterfaceJiNeng::UpdateXiuLian()
{
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_pIndex;
	pc = _charactor;
	ostringstream oss;
	int lv = cct::getCurrMaxXiulianLv(pc->m_PcData.m_Lv);
	sBBXiuLian* xiulian = &pc->m_PcData.m_XiuLian;
	oss.str("");
	oss << "攻击修炼  等级:" << xiulian->GetAtk() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetAtkExp() << "/" << GetXiuLIanExp(xiulian->GetAtk() + 1);
	m_TXiuLian[0].SetString(oss.str());
	oss.str("");
	oss << "防御修炼  等级:" << xiulian->GetDef() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetDefExp() << "/" << GetXiuLIanExp(xiulian->GetDef() + 1);
	m_TXiuLian[1].SetString(oss.str());
	oss.str("");
	oss << "法术修炼  等级:" << xiulian->GetMag() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetMagExp() << "/" << GetXiuLIanExp(xiulian->GetMag() + 1);
	m_TXiuLian[2].SetString(oss.str());
	oss.str("");
	oss << "法防修炼  等级:" << xiulian->GetDMag() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetDMagExp() << "/" << GetXiuLIanExp(xiulian->GetDMag() + 1);
	m_TXiuLian[3].SetString(oss.str());
	oss.str("");
	xiulian = &pc->m_PcData.m_XiuLianBB;
	oss << "攻击修炼  等级:" << xiulian->GetAtk() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetAtkExp() << "/" << GetXiuLIanExp(xiulian->GetAtk() + 1);
	m_TXiuLian[4].SetString(oss.str());
	oss.str("");
	oss << "防御修炼  等级:" << xiulian->GetDef() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetDefExp() << "/" << GetXiuLIanExp(xiulian->GetDef() + 1);
	m_TXiuLian[5].SetString(oss.str());
	oss.str("");
	oss << "法术修炼  等级:" << xiulian->GetMag() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetMagExp() << "/" << GetXiuLIanExp(xiulian->GetMag() + 1);
	m_TXiuLian[6].SetString(oss.str());
	oss.str("");
	oss << "法防修炼  等级:" << xiulian->GetDMag() << "/" << lv << "   ";
	oss << "修炼经验" << xiulian->GetDMagExp() << "/" << GetXiuLIanExp(xiulian->GetDMag() + 1);
	m_TXiuLian[7].SetString(oss.str());
	oss.str("");

// 	for (int i = 0; i < 8; i++)
// 	{
// 		m_TXiuLian[i].UpdateXCenter();
// 	}
	if (m_JiNengSelect > -1)
		m_SelectBackXiuLian.SetY(m_TXiuLian[m_JiNengSelect].m_y - 23);
	return true;
}

void cInterfaceJiNeng::OnOff(bool NeedShow)
{
	g_pMainState->m_Canvas.SetRedraw(m_Data.m_PreShowRect);
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (NeedShow)
	{
		Init();
		UpdateJiNeng();
	}
}


bool cInterfaceJiNeng::UpdateMainSkill()
{
	cMengPai* pMengPai = 0;
	if (_charactor->m_PcData.m_MengPaiID > -1)
		pMengPai = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(_charactor->m_PcData.m_MengPaiID);
	else
	{
		g_pMainState->m_Tags.Add("未入门派");
		return true;
	}
	switch (m_MiaoShuID)
	{
	case 11:
		//师门技能
		if (m_SkillSelect >= 0)
	{
		sSkill* pSkill = m_JiNengHeadData[m_SkillSelect];
		m_MiaoShu[0].SetString(pSkill->m_Name, RGB(255, 0, 0));
		//int h = m_MiaoShu[0].GetHeight();
		m_MiaoShu[1].SetString(pSkill->m_Text, 0);
		string name2 = "消耗:";
		name2 += pSkill->m_tCost;
		m_MiaoShu[2].SetString(name2, 0);
		m_NumMiaoShu = 3;

	}
		break;
	case 10:
		//门派技能
	{
		if (m_JiNengSelect == -1)
		{
			m_NumMiaoShu = 0;
			break;
		}

		m_MiaoShu[0].SetString(pMengPai->m_MainSkill[m_JiNengSelect].m_Name, RGB(255, 0, 0));
		m_MiaoShu[1].SetString(pMengPai->m_MainSkill[m_JiNengSelect].m_Text, 0);
		m_MiaoShu[2].SetString(pMengPai->m_MainSkill[m_JiNengSelect].m_Text2, 0);
		m_NumMiaoShu = 3;

		m_JiNengHeadNum = 0;
		int num = _charactor->m_PcData.m_SkillEnablelist.size();
		for (int i = 0; i < num; i++)
		{
//			if (_charactor->m_PcData.m_SkillEnablelist[i]->m_Owner == m_JiNengSelect)
			{
				m_JiNengHeadData[m_JiNengHeadNum] = _charactor->m_PcData.m_SkillEnablelist[i];
				m_JiNengHead[m_JiNengHeadNum].Load(m_JiNengHeadData[m_JiNengHeadNum]->m_BigHead);
				m_JiNengHeadNum += 1;
			}
		}
	}
		break;
	case 14:
	{
		sSkill* pSkill = g_pMainState->m_SkillManager.GetSpecialSkill(_charactor->m_PcData.m_SpecialSkillList[m_SpeciallSkillSelect]);
		m_MiaoShu[0].SetString(pSkill->m_Name, RGB(255, 0, 0));
		m_MiaoShu[1].SetString(pSkill->m_Text, 0);
		m_NumMiaoShu = 2;
	}
		break;
	case -1:
		break;
	default:
		ERRBOX;
		break;
	}
	//更新角色等级
	ostringstream oss;
	for (int i = 0; i < 7; i++)
	{
		oss.str("");
		oss << _charactor->m_PcData.m_MengPaiSkillLvs[i];
		m_ZhuJiNengLv[i].SetString(oss.str());
		m_ZhuJiNengHead[i].Load(pMengPai->m_MainSkill[i].m_BigHead);
	}
	for (int i = 0; i < 6; i++)
	{
		int id = _charactor->m_PcData.m_SpecialSkillList[i];
		if (id > -1)
		{
			sSkill* pSkill = g_pMainState->m_SkillManager.GetSpecialSkill(id);
			m_SpecialSkill[i].Load(pSkill->m_BigHead);
		}
		else 	m_SpecialSkill[i].Free();
	}
	MoveMainSkill(m_xPos, m_yPos);
	return true;
}

void cInterfaceJiNeng::SetMode(ulong mode)
{
	m_JiNengHeadNum = 0;
	m_JiNengSelect = -1;
	m_SkillSelect = -1;
	m_learnSkillB.SetFrame帧(3);
	m_learnSkillB.m_bMove = true;
	if (m_pPreMode)
	{
		m_pPreMode->SetFrame帧(0);
		m_pPreMode->m_bMove = true;
	}
	Set(mode);
	m_Data.m_bMove = true;
	if (mode == m_ZhuJiNeng)
	{
		m_SmB.SetFrame帧(1);
		m_pPreMode = &m_SmB;
	}
	else
		if (mode == m_FuZhuJiNeng)
		{
		m_FuZhuB.SetFrame帧(1);
		m_pPreMode = &m_FuZhuB;
		}
		else
			if (mode == m_XiuLian)
			{
		m_XiuLianB.SetFrame帧(1);
		m_pPreMode = &m_XiuLianB;
			}
	m_pPreMode->m_bMove = true;
	UpdateJiNeng();

}

bool cInterfaceJiNeng::UpdateJiNeng()
{
	if (m_bUpdateJiNeng)return true;
	if (-1 != m_JiNengSelect)
	{
		m_learnSkillB.SetFrame帧(0);
		m_learnSkillB.m_bMove = true;
	}
	if (m_Data.m_NowID == m_ZhuJiNeng)
	{
		return UpdateMainSkill();
	}
	else
		if (m_Data.m_NowID == m_FuZhuJiNeng)
		{
		return UpdateFuZhuJiNeng();
		}
		else
			if (m_Data.m_NowID == m_XiuLian)
			{
		return UpdateXiuLian();
			}

	return true;
}

bool cInterfaceJiNeng::UpdateFuZhuJiNeng()
{
	ostringstream oss;
//	cPropertyData* pUserData;
	cPcData* pUserData = &_charactor->m_PcData;
	int skillnum = c_NumFuZhu;
	for (int i = 0; i < skillnum; i++)
	{
		m_JiNengHead[i].Load(g_pMainState->m_SkillManager.m_FuZhuSkillList[i].m_BigHead);
		oss.str("");
		oss << pUserData->m_FuZhuSkillLvList[i];
		m_FuZhuJiNengLv[i].SetString(oss.str());
	}
	if (-1 != m_JiNengSelect)
	{
		sSkill*  Skill = g_pMainState->m_SkillManager.GetFuZhuSkill(m_JiNengSelect);
		m_MiaoShu[0].SetString(Skill->m_Name, RGB(255, 0, 0));
		//	int h = m_MiaoShu[0].GetHeight();
		m_MiaoShu[1].SetString(Skill->m_Text, 0);
	}
	m_JiNengHeadNum = skillnum;
	MoveFuZhuSkill(m_xPos, m_yPos);
	return true;
}


void cInterfaceJiNeng::MoveMainSkill(int x, int y)
{
	m_ZhuJiNengHead[0].SetX(m_xPos + 105);
	m_ZhuJiNengHead[0].SetY(m_yPos + 130);

	m_ZhuJiNengHead[1].SetX(m_xPos + 105);
	m_ZhuJiNengHead[1].SetY(m_yPos + 60);

	m_ZhuJiNengHead[2].SetX(m_xPos + 105);
	m_ZhuJiNengHead[2].SetY(m_yPos + 200);

	m_ZhuJiNengHead[3].SetX(m_xPos + 45);
	m_ZhuJiNengHead[3].SetY(m_yPos + 95);

	m_ZhuJiNengHead[4].SetX(m_xPos + 45);
	m_ZhuJiNengHead[4].SetY(m_yPos + 165);

	m_ZhuJiNengHead[5].SetX(m_xPos + 165);
	m_ZhuJiNengHead[5].SetY(m_yPos + 95);

	m_ZhuJiNengHead[6].SetX(m_xPos + 165);
	m_ZhuJiNengHead[6].SetY(m_yPos + 165);

	for (int i = 0; i < 7; i++)
	{
		m_ZhuJiNengLv[i].SetY(m_ZhuJiNengHead[i].GetY() + 47);
		m_ZhuJiNengLv[i].SetXCenter(m_ZhuJiNengHead[i].GetX() + 20);
		m_ZhuJiNengLv[i].UpdateXCenter();
	}
	int h = m_yPos + 65;
	for (int i = 0; i < m_NumMiaoShu; i++)
	{
		m_MiaoShu[i].SetXY(m_xPos + 250, h);
		h += m_MiaoShu[i].GetHeight();
	}
	int i2;
	int i3;
	for (int i = 0; i < m_JiNengHeadNum; i++)
	{
		i2 = i % 7;
		i3 = i / 7;
		m_JiNengHead[i].m_Picture.m_x = m_xPos + 27 + 60 * i2;
		m_JiNengHead[i].m_Picture.m_y = m_yPos + 275 + 50 * i3;
	}

}

void cInterfaceJiNeng::MoveFuZhuSkill(int x, int y)
{
	ostringstream oss;
	//cPetData* pUserData=&g_pCharacter->m_PCData;
	int x1, y1;
	for (int i = 0; i < c_NumFuZhu; i++)
	{
		int i2 = i % 7;
		int i3 = i / 7;
		x1 = m_xPos + 14 + 60 * i2;
		y1 = m_yPos + 276 + 74 * i3;
		m_JiNengHead[i].m_Picture.SetXY(x1, y1);
		m_FuZhuJiNengLv[i].SetXCenter(x1 + 20);
		m_FuZhuJiNengLv[i].SetY(y1 + 50);
		m_FuZhuJiNengLv[i].UpdateXCenter();
	}
	if (-1 != m_JiNengSelect)
	{
		m_MiaoShu[0].SetXY(m_xPos + 250, m_yPos + 65);
		int h = m_MiaoShu[0].GetHeight();
		m_MiaoShu[1].SetXY(m_xPos + 250, m_yPos + 66 + h);
	}
}
void cInterfaceJiNeng::MoveXiuLian(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		m_TXiuLian[i].SetX(x + 55);
//		m_TXiuLian[i].SetXCenter(x + 225);
//		m_TXiuLian[i].UpdateXCenter();
	}
	for (int i = 0; i < 4; i++)
	{
		m_TXiuLian[i].SetY(m_yPos + 115 + 22 * i);
		m_TXiuLian[i + 4].SetY(m_yPos + 285 + 22 * i);
	}
	if (m_JiNengSelect > -1)
		m_SelectBackXiuLian.SetY(m_TXiuLian[m_JiNengSelect].m_y - 23);
}


