#include "_global.h"


bool cAccelator::ProcessInput()
{
	if (m_Describe.m_NeedShow)//g_pMainState->InterfaceSetShow(&m_Describe, false);
		m_Describe.OnOff(false);

	if (m_Mode == 0)
	{
		if (_show8 == 1)
		{
			m_redrawrect.left = m_Accelatorbackp[0].m_x;
			m_redrawrect.top = m_Accelatorbackp[0].m_y;
			m_redrawrect.right = m_Accelatorbackp[0].m_x + m_Accelatorback.GetWidth();
			m_redrawrect.bottom = m_Accelatorbackp[0].m_y + m_Accelatorback.GetHeight();
		}
		if (isOn(g_xMouse, g_yMouse, m_redrawrect))
		{
			m_Select = (g_xMouse - m_redrawrect.left) / m_Accelatorback.GetWidth();
			if (CheckL())return true;
			if (m_AccelatorSkillid[m_Select] > -1)
			{
				g_pMainState->m_SkillManager.SetMengPaiSkill(m_Describe, m_AccelatorSkillid[m_Select]);
				if (0 == m_Describe.m_NeedShow)//g_pMainState->InterfaceSetShow(&m_Describe, true);
					m_Describe.OnOff(true);
			}
			if (CheckRB())return true;
		}
	}
	else
	{
		ResetButton();
		g_pMainState->SetMouseOnMap(false);
		m_SkillSelect = -1;

		if (!isOn(g_xMouse, g_yMouse, m_MagicBack.m_PreShowRect))
		{
			return true;
		}
		if (CheckOn(&m_Cancel, 100))return true;


		int i = 0;
		for (; i < m_NumofSkill; i++)
		{
			if (isOn(g_xMouse, g_yMouse, m_SkillHead[i].m_PreShowRect))
			{
				m_Select = 14;
				m_SkillSelect = m_pSkillShow[i]->m_Id;
				g_pMainState->m_SkillManager.SetMengPaiSkill(m_Describe, m_SkillSelect);
				if (0 == m_Describe.m_NeedShow)g_pMainState->InterfaceSetShow(&m_Describe, true);
				if (CheckL())return true;
				break;
			}
		}
		m_Select = 15;
		if (CheckRB())return true;
	}
	return true;
}

bool cAccelator::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;

	if (_show8 == 1)
	{

	}
	else
	{
		for (int i = 0; i < _show8; i++)
		{
			pCanvas->Add(&m_Accelatorbackp[i], 1);
			pCanvas->Add(&m_AccelatorSkill[i], 1);
			pCanvas->Add(&m_tAccelatorSkill[i]);
		}
	}
	if (m_Mode)
	{
		pCanvas->Add(&m_MagicBack, 1);
		pCanvas->Add(&m_TitleT);
		pCanvas->Add(&m_Cancel, 1);
		for (int i = 0; i < m_NumofSkill; i++)
			pCanvas->Add(&m_SkillHead[i], 1);
	}

	return true;
}

bool cAccelator::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Describe.Init();
	//快捷键背景
	m_Accelatorback.Load(76806695);
	ostringstream oss;

	if (_show8 == 1)
	{
		m_Accelatorbackp[0].Set(&m_Accelatorback);
	}
	else
	{
		for (int i = 0; i < _show8; i++)
		{
			m_Accelatorbackp[i].Set(&m_Accelatorback);
// 			m_Accelatorbackp[i].SetXY(g_640 - 300 + i*m_Accelatorback.GetWidth(), g_480 - 60);
// 			m_AccelatorSkill[i].SetXY(g_640 - 300 + 4 + i*m_Accelatorback.GetWidth(), g_480 - 60 + 4);
			oss.str("");
			oss << "F";
			oss << i + 1;
			m_tAccelatorSkill[i].m_hFont = g_pMainState->m_hFont[5];
			m_tAccelatorSkill[i].SetColor(RGB(255, 255, 255));
			m_tAccelatorSkill[i].SetStyle(2);
			m_tAccelatorSkill[i].SetString(oss.str());
//			m_tAccelatorSkill[i].SetXY(g_640 - 300 + 10 + i*m_Accelatorback.GetWidth(), g_480 - 75);
		}
	}


// 	m_redrawrect.left = m_Accelatorbackp[0].m_x;
// 	m_redrawrect.top = m_Accelatorbackp[0].m_y;
// 	m_redrawrect.right = m_Accelatorbackp[7].m_x + m_Accelatorback.GetWidth();
// 	m_redrawrect.bottom = m_Accelatorbackp[0].m_y + m_Accelatorback.GetHeight();
	m_TitleT.SetString("法术");
	m_TitleT.SetColor(RGB(255, 255, 255));
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	return true;
}



bool cAccelator::init2()
{
	if (!_c)
	{
		for (int i = 0; i < _show8; i++)
		{
			m_AccelatorSkillid[i] =-1;
			m_AccelatorSkill[i].Load(0);
		}
		return true;
	}
	int y = g_480 - 65;
	if (g_StateType == STATE_FIGHT)
	{
		y = g_480 - 32;
	}

	for (int i = 0; i < _show8; i++)
	{
		int x = g_640 - 288 + i * m_Accelatorback.GetWidth();
		m_Accelatorbackp[i].SetXY(x, y);
		m_AccelatorSkill[i].SetXY(x + 4, y + 4);
		m_tAccelatorSkill[i].SetXY(x + 11, y - 10);

		m_AccelatorSkillid[i] = _c->m_PcData.m_Accelarate[i];
		m_AccelatorSkill[i].Load(g_pMainState->m_SkillManager.GetMengPaiSkill(m_AccelatorSkillid[i])->m_SmallHead);
	}
	m_redrawrect.left = m_Accelatorbackp[0].m_x;
	m_redrawrect.top = m_Accelatorbackp[0].m_y;
	m_redrawrect.right = m_Accelatorbackp[7].m_x + m_Accelatorback.GetWidth();
	m_redrawrect.bottom = m_Accelatorbackp[0].m_y + m_Accelatorback.GetHeight();
	return true;
}


void cAccelator::OnOff(bool NeedShow)
{
	if (m_NeedShow == NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_NeedShow)
	{
		Init();
		init2();
	}
	m_Describe.OnOff(false);
	g_pMainState->m_Canvas.SetRedraw(m_redrawrect);
}

void cAccelator::MoveMagicBack(int x, int y)
{

	m_xPos = x;
	m_yPos = y;
	m_MagicBack.m_x = x;
	m_MagicBack.m_y = y;
	if (m_NumofSkill < 11)
	{
		//设置技能位置
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 30 + 88 * (i % 2), m_MagicBack.m_y + 33 + 42 * (i / 2));
		}
	}
	else if (m_NumofSkill < 15)
	{
		//设置技能位置
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 30 + 88 * (i % 2), m_MagicBack.m_y + 33 + 42 * (i / 2));
		}
	}
	else if (m_NumofSkill < 21)
	{
		//设置技能位置
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 30 + 88 * (i % 2), m_MagicBack.m_y + 30 + 42 * (i / 2));
		}
	}
	else //30
	{
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 25 + 50 * (i % 3), m_MagicBack.m_y + 27 + 42 * (i / 3));
		}
	}
	if (m_MagicBack.m_pFile)
	{
		m_Cancel.m_x = m_MagicBack.m_x + m_MagicBack.m_pFile->GetWidth() - 20;
	}
	m_Cancel.m_y = m_MagicBack.m_y + 5;
	int xc = x + m_MagicBack.m_Width / 2;
	m_TitleT.SetY(y + 3);
	m_TitleT.SetXCenter(xc);
	m_TitleT.UpdateXCenter();
}

bool cAccelator::CheckL()
{
// 	if (_show8 == 1 && m_Mode == 0)
// 	{
// 
// 	}
// 	else
	{
		if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}



	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 14:
		if (1)
		{
			if (_show8 == 1 && _cb)
			{
				_cb(_tag, m_AccelatorSkillid[0] = m_SkillSelect);
				m_AccelatorSkill[0].Load(g_pMainState->m_SkillManager.GetMengPaiSkill(m_SkillSelect)->m_SmallHead);

			}
			else
			{
				g_pCharacter->m_PcData.m_Accelarate[m_AccelatorSelect] = m_SkillSelect;
				m_AccelatorSkillid[m_AccelatorSelect] = g_pCharacter->m_PcData.m_Accelarate[m_AccelatorSelect];
				m_AccelatorSkill[m_AccelatorSelect].Load(g_pMainState->m_SkillManager.GetMengPaiSkill(m_AccelatorSkillid[m_AccelatorSelect])->m_SmallHead);

			}

		}
	case 100:
		m_Mode = 0;
		g_pMainState->m_Canvas.SetRedraw(m_MagicBack.m_PreShowRect);
		break;
	default:
		if (1)
		{
			if (g_StateType == STATE_MAIN)
			{
				//设置快捷键
				m_Cancel.SetFrame帧(0);
				m_Mode = 1;
				m_AccelatorSelect = m_Select;
				m_NumofSkill = 0;
				const auto& ens = (_show8 == 1) ? 
					(((cPcData*)g_pMainState->m_FightWorkList[g_pMainState->m_InterfaceTeam.GetTeamTurn(_tag)].m_pObj->m_pIndex))->m_SkillEnablelist :
					g_pCharacter->m_PcData.m_SkillEnablelist;
				for (int i = 0; i < ens.size(); i++)
				{
					if (m_NumofSkill == 30)
					{
						break;
					}
					if (ens[i]->m_SkillType != 7)//是否战斗可用
					{
						m_pSkillShow[m_NumofSkill] = ens[i];
						m_NumofSkill += 1;
					}

				}
				g_pMainState->m_pFightState->m_FightMenu.Init();
				if (m_NumofSkill < 11)m_MagicBack.Set(&g_pMainState->m_pFightState->m_FightMenu.m_BackMagic10);
				else
					if (m_NumofSkill < 15)m_MagicBack.Set(&g_pMainState->m_pFightState->m_FightMenu.m_BackMagic14);
					else
						if (m_NumofSkill < 21)m_MagicBack.Set(&g_pMainState->m_pFightState->m_FightMenu.m_BackMagic20);
						else
						{
							m_MagicBack.Set(&g_pMainState->m_pFightState->m_FightMenu.m_BackMagic30);
							if (30 < m_NumofSkill)
								m_NumofSkill = 30;
						}
				//加载技能头像,并设置好位置
				for (int i = 0; i < m_NumofSkill; i++)
				{
					m_SkillHead[i].Load(m_pSkillShow[i]->m_BigHead);
				}
				MoveMagicBack(g_half320 - m_MagicBack.m_pFile->GetWidth() / 2, g_half240 - m_MagicBack.m_pFile->GetHeight() / 2);

			}
			else
			{
				sSkill* pskill = g_pMainState->m_SkillManager.m_MengPaiManager.GetSMSkill(m_AccelatorSkillid[m_Select]);

				if (pskill->m_EffectType != 0)
				{
// 					sFightWorkList& list = g_pMainState->m_FightWorkList[g_pMainState->m_pFightState->m_FightMenu.m_NowFighterID];
// 					list.m_SkillPreSelect.SkillID = pskill->m_Id;
// 					cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
// 					list.m_SkillPreSelect.SkillLv = pc->m_PcData.m_MengPaiSkillLvs[pskill->m_Owner];
					g_pMainState->m_pFightState->m_FightMenu.m_pSkillSelect = pskill;
					g_pMainState->m_pFightState->m_FightMenu.InitMagic2();
					g_pMainState->m_pFightState->m_MiaoShu.SetString(pskill->m_Name);
					g_pMainState->m_pFightState->m_MiaoShu.SetTime(0xFFFF);
					g_pMainState->m_pFightState->m_MiaoShu.UpdateXCenter();
				}
				return true;
			}
		}
		break;
	}
	return true;
}

bool cAccelator::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 15:
		if (1)
		{
			m_Mode = 0;
			g_pMainState->m_Canvas.SetRedraw(m_MagicBack.m_PreShowRect);
		}
	default:
		if (1)
		{
			if (m_AccelatorSkillid[m_Select] < 0)return true;
			sSkill* pskill = g_pMainState->m_SkillManager.m_MengPaiManager.GetSMSkill(m_AccelatorSkillid[m_Select]);
			switch (g_StateType)
			{
			case STATE_MAIN:
				if (pskill->m_EffectType == 0)
					g_pMainState->m_SkillManager.GetSkill(m_AccelatorSkillid[m_Select]);
				return true;
			case STATE_FIGHT:
				if (pskill->m_EffectType != 0)
				{
// 					sFightWorkList& list = g_pMainState->m_FightWorkList[g_pMainState->m_pFightState->m_FightMenu.m_NowFighterID];
// 					list.m_SkillPreSelect.SkillID = pskill->m_Id;
// 					cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
// 					list.m_SkillPreSelect.SkillLv = pc->m_PcData.m_MengPaiSkillLvs[pskill->m_Owner];
// 					g_pMainState->m_pFightState->m_FightMenu.InitMagic2();
					g_pMainState->m_pFightState->m_FightMenu.m_pSkillSelect = pskill;
					g_pMainState->m_pFightState->m_FightMenu.InitMagic2();
					g_pMainState->m_pFightState->m_MiaoShu.SetString(pskill->m_Name);
					g_pMainState->m_pFightState->m_MiaoShu.SetTime(0xFFFF);
					g_pMainState->m_pFightState->m_MiaoShu.UpdateXCenter();
				}
				return true;
			}
		}
		/*if (m_AccelatorSkillid[m_Select]>-1)
		return UseSkill(m_AccelatorSkillid[m_Select]);*/
		break;
	}

	return true;
}

bool cAccelator::ProcessAccelator()
{
	if (!_c)return true;
	const auto& acc = _c->m_PcData.m_Accelarate;
	for (int i = 0; i < 8; i++)
	{
		if (acc[i] > -1)
		{
			if (g_pMainState->Keyboard.GetKeyState(59 + i))
			{
				g_pMainState->Keyboard.SetLock(59 + i);
				return UseSkill(acc[i]);
			}
		}
	}


	return false;
}

bool cAccelator::UseSkill(int id)
{
	sSkill* pskill = g_pMainState->m_SkillManager.GetMengPaiSkill(id);
	if (g_StateType == STATE_MAIN)
	{
		if (pskill->m_SkillType == 0)
		{
			g_pMainState->m_SkillManager.UseNormal(id);
			return true;
		}
	}
	else
	{
		if (pskill->m_SkillType != 0)
		{
//			if (g_pMainState->m_pFightState->m_FightMenu.m_NowFighterID == g_pMainState->m_HeroID)
			{
				g_pMainState->m_pFightState->m_FightMenu.m_pSkillSelect = pskill;
				g_pMainState->m_pFightState->m_FightMenu.InitMagic2();
				g_pMainState->m_pFightState->m_MiaoShu.SetString(pskill->m_Name);
				g_pMainState->m_pFightState->m_MiaoShu.SetTime(0xFFFF);
				g_pMainState->m_pFightState->m_MiaoShu.UpdateXCenter();
			}
			return true;
		}
	}
	return false;
}


