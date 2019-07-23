#include "_global.h"


bool cPCHead::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_TMouseOnLine.SetColor(RGB(255, 255, 255));

	m_TeamFace.resize(5);
	m_TeamBack.resize(5);
	m_TeamPetFace.resize(5);

	m_PetFaceBack.Load(0x203CE1F7);
	m_PetFaceBack.SetStatic(true);
	for (int i = 0; i < 5; i++)
	{
		m_TeamBack[i].Load(0x2178F38B);
		m_TeamBack[i].SetStatic(true);
		m_TeamBack[i].m_NeedShow = false;
		m_bPetHeadMode[i] = false;
	}
	MoveTeamHead(0);



	m_CharacterHead.Load(42282575);
	m_CharacterHead.SetStatic(true);
	m_PetHead.Load(1762476724);
	m_PetHead.SetStatic(true);
	m_PCFace.SetX(g_640 - m_CharacterHead.GetWidth() + 2);
	m_PCFace.SetStatic(true);
	m_PCFace.m_Picture.SetY(3);
	m_PetFace.SetStatic(true);
	m_PetFace.m_NeedShow = false;
	m_CharacterHead.SetX(g_640 - m_CharacterHead.GetWidth());
	m_CharacterHead.SetY(0);
	m_PetHead.SetX(g_640 - m_PetHead.GetWidth() - m_CharacterHead.GetWidth());
	m_PetHead.SetY(0);
	m_PetFace.SetX(m_PetHead.GetX() + 3);
	m_PetFace.SetY(3);
	m_PetFaceBack.SetX(m_PetHead.GetX());
	m_PetFaceBack.SetY(0);



	//各种血条
	m_Heart.Load(780622062);
	m_HeartHurt.Load(0x008C2611);

	m_HPlinep.resize(2);
	m_HeartHurtp.resize(2);
	m_MPlinep.resize(2);
	m_EXPlinep.resize(2);

	int offset = m_CharacterHead.GetHeight() / 4;
	int linex = g_640 - m_HeartHurt.GetWidth() - 6;  //血条的x位置
	int linex2 = m_PetFaceBack.GetX() + 50 - 1;       //召唤兽的血条的x位置
	for (int i = 0; i < 2; i++)
	{
		m_HeartHurtp[i].m_bStatic = true;
		m_HPlinep[i].m_bStatic = true;
		m_MPlinep[i].m_bStatic = true;
		m_EXPlinep[i].m_bStatic = true;
	}
	m_HeartHurtp[0].Set(&m_HeartHurt);
	m_HeartHurtp[0].m_x = linex;
	m_HeartHurtp[0].m_y = 3;
	m_HeartHurtp[1].Set(&m_HeartHurt);
	m_HeartHurtp[1].m_x = linex2;
	m_HeartHurtp[1].m_y = 3;


	m_HPline.Load(0xAAD44583);
	m_HPlinep[0].Set(&m_HPline);
	m_HPlinep[0].m_x = linex;
	m_HPlinep[0].m_y = 3;
	m_HPlinep[1].Set(&m_HPline);
	m_HPlinep[1].m_x = linex2;
	m_HPlinep[1].m_y = 3;


	m_MPline.Load(0xCE4D3C2D);
	m_MPlinep[0].Set(&m_MPline);
	m_MPlinep[0].m_x = linex;
	m_MPlinep[0].m_y = offset * 1 + 2;
	m_MPlinep[1].Set(&m_MPline);
	m_MPlinep[1].m_x = linex2;
	m_MPlinep[1].m_y = offset * 1 + 2;


	m_EXPline.Load(0x7B3C08E4);
	for (int i = 0; i < 2; i++)
	{
		m_EXPlinep[i].m_bStatic = true;
		m_EXPlinep[i].Set(&m_EXPline);
	}
	m_EXPlinep[0].m_x = linex;
	m_EXPlinep[0].m_y = offset * 3 + 4;
	m_EXPlinep[1].m_x = linex2;
	m_EXPlinep[1].m_y = offset * 2 + 3;

	m_CPline.Load(0xBAF8009F);
	m_CPline.SetX(linex);
	m_CPline.SetY((offset)* 2 + 3);
	m_CPline.SetStatic(true);

	m_EmptyLine.Load(0x2E8758EE);
	m_EmptyLinep.resize(7);
	for (int i = 0; i < 7; i++)
	{
		m_EmptyLinep[i].Set(&m_EmptyLine);
		m_EmptyLinep[i].m_bStatic = true;
	}
	int wid2 = g_640 - m_EmptyLine.GetWidth();
	for (int i = 0; i < 4; i++)
	{
		m_EmptyLinep[i].m_x = wid2;
		m_EmptyLinep[i].m_y = i*offset;
	}
	for (int i = 4; i < 7; i++)
	{
		m_EmptyLinep[i].m_x = wid2 - m_Heart.GetWidth() - 50 + 1;
		m_EmptyLinep[i].m_y = (i - 4)*offset;
	}

	return true;
}

bool cPCHead::Show(cCanvas* pCanvas)
{
	if (!g_pCharacter)return false;
	if (g_pCharacter->m_PcData.m_NumofBB)
	{
		pCanvas->Add(&m_PetHead, 1, 1);

		pCanvas->Add(&m_PetFaceBack, 1);
		pCanvas->Add(&m_PetFace, 1, 1);
	}
	pCanvas->Add(&m_CharacterHead, 1, 1);
	pCanvas->Add(&m_PCFace, 1, 1);


	if (m_TeamBack[1].m_NeedShow)
	{
		for (int i = 0; i < 5; i++)//显示队友头像
		{
			if (m_TeamBack[i].m_NeedShow)
			{
				pCanvas->Add(&m_TeamBack[i], 1);
			}
			else break;
		}
		for (int i = 0; i < 5; i++)//显示队友头像
		{
			if (m_TeamBack[i].m_NeedShow)
			{
				if (m_bPetHeadMode[i])
					pCanvas->Add(&m_TeamPetFace[i], 1, 1);
				else
					pCanvas->Add(&m_TeamFace[i], 1, 1);
			}
			else break;
		}
	}

	//显示HP
	if (g_pCharacter->m_PcData.m_HP < g_pCharacter->m_PcData.HPMax.GetData())
	{
		pCanvas->Add(&m_EmptyLinep[0], 1);
		pCanvas->Add(&m_HeartHurtp[0], 1);
		pCanvas->Add(&m_HPlinep[0], 1);
	}
	//显示MP
	if (g_pCharacter->m_PcData.m_MP < g_pCharacter->m_PcData.MPMax.GetData())
	{
		pCanvas->Add(&m_EmptyLinep[1], 1);
		pCanvas->Add(&m_MPlinep[0], 1);
	}
	//显示CP
	if (g_pCharacter->m_PcData.m_CP < 150)
	{
		pCanvas->Add(&m_EmptyLinep[2], 1);
		pCanvas->Add(&m_CPline, 1);
	}
	//显示经验 
	if (g_pCharacter->m_PcData.m_EXP < GetCharacterExp(g_pCharacter->m_PcData.m_Lv + 1)/*g_pCharacter->m_PcData.m_ExpTotal*/)
	{
		pCanvas->Add(&m_EmptyLinep[3], 1);
		pCanvas->Add(&m_EXPlinep[0], 1);
	}
	//下面是召唤兽的血条

	if (m_pPet)
	{
		//显示HP
		if (m_pPet->m_PetData.m_HP < m_pPet->m_PetData.HPMax.GetData())
		{
			pCanvas->Add(&m_EmptyLinep[4], 1);
			pCanvas->Add(&m_HeartHurtp[1], 1);
			pCanvas->Add(&m_HPlinep[1], 1);
		}
		//显示MP
		if (m_pPet->m_PetData.m_MP < m_pPet->m_PetData.MPMax.GetData())
		{
			pCanvas->Add(&m_EmptyLinep[5], 1);
			pCanvas->Add(&m_MPlinep[1], 1);
		}
		//显示经验 
		if (m_pPet->m_PetData.m_EXP < GetPetExp(m_pPet->m_PetData.m_Lv + 1)/*m_pPet->m_PetData.m_ExpTotal*/)
		{
			pCanvas->Add(&m_EmptyLinep[6], 1);
			pCanvas->Add(&m_EXPlinep[1], 1);
		}
	}
	if (-1 != m_MouseOnPre)pCanvas->Add(&m_TMouseOnLine);
	return true;
}

bool cPCHead::ProcessInput()
{
	if (!g_pMainState->GetLockMouse())return true;
	m_MouseOn = -1;
	if (g_yMouse < 50)
		if (g_xMouse > m_PetHead.GetX())
			if (g_xMouse < g_640 && g_yMouse>0)
			{
		g_pMainState->SetMouseOnMap(false);
		int wOld = 640;
		if (g_xMouse > g_640 - 70) // 570
		{
			m_MouseOn = (g_yMouse/* - g_480 + 480*/) / 12;
		}
		else
			//		if (g_xMouse > 457 && g_xMouse < 520  && g_yMouse < 36)
			if (g_xMouse > g_640 - 183 && g_xMouse < g_640 - 120 && g_yMouse < 36)
			{
			m_MouseOn = (g_yMouse/* - g_480 + 480*/) / 12 + 4;
			}

//		if (g_StateType != STATE_FIGHT)//战斗时不处理鼠标按键消息
		{
			g_pMainState->m_Cursor.m_FollowMode = false;
			if (g_xMouse > g_640 - 116) // 524
			{
				m_Select = 11;
				if (CheckL())return true;
				if (g_xMouse > g_640 - 55) // 585
				{
					if (g_yMouse < 11)
					{
						m_Select = 13;
						if (CheckRB())return true;
					}
					else
						if (g_yMouse < 23)
						{
						m_Select = 14;
						if (CheckRB())return true;
						}
				}
			}
			else
				if (g_pCharacter->m_PcData.m_NumofBB)
				{
				if (g_xMouse > m_PetHead.GetX() && g_yMouse < 40)
				{
					m_Select = 12;
					if (CheckL())return true;
					if (g_xMouse > g_640 - 176) // 464
					{
						if (g_yMouse < 11)
						{
							m_Select = 15;
							if (CheckRB())return true;
						}
						else
							if (g_yMouse < 26)
							{
							m_Select = 16;
							if (CheckRB())return true;
							}
					}
				}
				}
		}
			}

	if (m_TeamBack[0].m_NeedShow)
	{
		for (int i = 0; i < 5; i++)
		{
			if (m_TeamBack[i].m_NeedShow)
			{
				if (isOn(g_xMouse, g_yMouse, m_TeamBack[i].m_PreShowRect))
				{
					g_pMainState->SetMouseOnMap(false);
					m_Select = i;
					if (CheckRB())return true;
					if (CheckL())return true;

				}
			}
			else
				break;
		}
	}
	if (m_MouseOn != m_MouseOnPre)
	{
		if (m_MouseOn > 3)if (!m_pPet)return true;//如果角色没有召唤兽
		m_MouseOnPre = m_MouseOn;
		g_pMainState->m_Canvas.SetRedraw(m_TMouseOnLine.m_PreShowRect);
		ostringstream oss;
		switch (m_MouseOn)
		{
		case 0:
			if (1)
			{
				oss << "HP ";
				oss << g_pCharacter->m_PcData.m_HP;
				oss << "/";
				oss << g_pCharacter->m_PcData.m_HP2;
				oss << "/";
				oss << g_pCharacter->m_PcData.HPMax.GetData();
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 15, 50);

			}
			break;
		case 1:
			if (1)
			{
				oss << "MP ";
				oss << g_pCharacter->m_PcData.m_MP;
				oss << "/";
				oss << g_pCharacter->m_PcData.MPMax.GetData();
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 15, 50);

			}
			break;
		case 2:
			if (1)
			{
				oss << "CP ";
				oss << g_pCharacter->m_PcData.m_CP;
				oss << "/150";
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 15, 50);

			}
			break;
		case 3:
			if (1)
			{
				oss << "EXP ";
				oss << g_pCharacter->m_PcData.m_EXP;
				oss << "/";
				oss << GetCharacterExp(g_pCharacter->m_PcData.m_Lv + 1);//g_pCharacter->m_PcData.m_ExpTotal;
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 15, 50);
			}
			break;
		case 4:
			if (1)
			{
				oss << "HP ";
				oss << m_pPet->m_PetData.m_HP;
				oss << "/";
				oss << m_pPet->m_PetData.m_HP2;
				oss << "/";
				oss << m_pPet->m_PetData.HPMax.GetData();
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 80, 50);
			}
			break;
		case 5:
			if (1)
			{
				oss << "MP ";
				oss << m_pPet->m_PetData.m_MP;
				oss << "/";
				oss << m_pPet->m_PetData.MPMax.GetData();
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 80, 50);
			}
			break;
		case 6:
			if (1)
			{
				oss << "EXP ";
				oss << m_pPet->m_PetData.m_EXP;
				oss << "/";
				oss << GetPetExp(m_pPet->m_PetData.m_Lv + 1); //m_pPet->m_PetData.m_ExpTotal;
				SIZE size1;
				m_TMouseOnLine.SetString(oss.str());
				GetTextExtentPointA(g_DC, m_TMouseOnLine.GetString().c_str(), m_TMouseOnLine.GetString().size(), &size1);
				m_TMouseOnLine.SetXY(g_640 - size1.cx - 80, 50);
			}
			break;
		default:
			g_pMainState->m_Canvas.SetRedraw(m_TMouseOnLine.m_PreShowRect);
			break;
		}
	}
	return true;
}

void cPCHead::SetPetHead(ulong head)
{
	if (!head)
	{
		m_PetFace.m_NeedShow = false;
		return;
	}
	m_PetFace.Load(head);
	m_PetFace.m_NeedShow = true;
}

bool cPCHead::UpDateHead()
{
	if (!g_pCharacter)
	{
		return true;
	}
	ulong head = g_pCharacter->GetID(POS_SMALLHEAD);
	m_PCFace.Load(head);

	for (int i = 0; i < 5; i++)
	{
		const auto& list = g_pMainState->m_FightWorkList[g_pMainState->m_InterfaceTeam.GetTeamTurn(i)];
		if (list.isExist && list.m_pObj && list.m_pObj->getPropertyData() && !list.m_pObj->getPropertyData()->_isOurTeamTemp)
		{
			m_TeamFace[i].Load(g_pMainState->m_InterfaceTeam.GetSmallHead(i));
			m_TeamBack[i].m_NeedShow = true;
			m_TeamFace[i].m_bMove = true;

			m_TeamPetFace[i].Load(g_pMainState->m_InterfaceTeam.GetPetHead(i));
			m_TeamPetFace[i].m_bMove = true;
		}
		else
		{
			if (m_TeamFace[i].m_NowID)
			{
				g_pMainState->m_Canvas.SetRedraw(m_TeamFace[i].m_PreShowRect);
			}
			m_TeamFace[i].Free();
			m_TeamBack[i].m_NeedShow = false;
		}

	}
	if (1 == g_pMainState->GetLiveNum(0, 10))
		m_TeamBack[0].m_NeedShow = false;
	return true;
}

bool cPCHead::SetPcID(int id /*= 2*/)
{
	if (!g_pCharacter)return false;
	g_pCharacter = (cCharacter*)g_pMainState->m_FightWorkList[id].m_pObj->m_pIndex;
	if (g_pCharacter->m_PcData.m_FightPetID > -1)
		m_pPet = (cPet*)g_pCharacter->m_PcData.m_pPets[g_pCharacter->m_PcData.m_FightPetID];
	else m_pPet = 0;
	UpdatePet();
	UpdateDate();
	UpDateHead();
	return true;
}

void cPCHead::UpdatePcHp()
{
	g_pMainState->m_Canvas.SetRedraw(m_HeartHurtp[0].GetPicRange());
	g_pMainState->m_Canvas.SetRedraw(m_HPlinep[0].GetPicRange());

	int hpmax = g_pCharacter->m_PcData.HPMax.GetData();
	int& hp2 = g_pCharacter->m_PcData.m_HP2;
	int & hp = g_pCharacter->m_PcData.m_HP;
	int percent;
	//int offset = m_CharacterHead.m_Picture.m_Height / 4;
	//HP
	if (hpmax != hp)
	{
		//伤
		if (hpmax == hp2)
			percent = 0;
		else
			percent = 100 - hp2 * 100 / hpmax;

		m_HeartHurtp[0].SetxOffset(percent*m_HeartHurt.m_Picture.m_Width / 100);

		//HP
		if (hpmax)
			percent = (hp * 100) / hpmax;
		else
			percent = 0;
		m_HPlinep[0].SetxOffset((98 - percent) / 2);
	}
	m_HPlinep[0].m_bMove = true;
	m_HeartHurtp[0].m_bMove = true;
	return;
}
void cPCHead::UpdatePcMp()
{
	g_pMainState->m_Canvas.SetRedraw(m_MPlinep[0].GetPicRange());
	int percent;
	//int offset = m_CharacterHead.m_Picture.m_Height / 4;
	//MP
	if (g_pCharacter->m_PcData.MPMax.GetData() != g_pCharacter->m_PcData.m_MP)
	{
		if (g_pCharacter->m_PcData.MPMax.GetData())
			percent = (g_pCharacter->m_PcData.m_MP * 100) / g_pCharacter->m_PcData.MPMax.GetData();
		else
			percent = 0;
		m_MPlinep[0].SetxOffset((98 - percent) / 2);
	}
	m_MPlinep[0].m_bMove = true;
	return;
}
void cPCHead::UpdatePcCp()
{
	int percent;
	//int offset = m_CharacterHead.m_Picture.m_Height / 4;

	percent = (g_pCharacter->m_PcData.m_CP * 100) / 150;
	m_CPline.SetxOffset((98 - percent) / 2);

	m_CPline.m_bMove = true;
}
void cPCHead::UpdatePcExp()
{
	int percent = 0;
	int exp = GetCharacterExp(g_pCharacter->m_PcData.m_Lv + 1);
	if (g_pCharacter->m_PcData.m_EXP < exp)
	{
		if (exp)
		{
			percent = (int)((g_pCharacter->m_PcData.m_EXP * 100) / exp/*g_pCharacter->m_PcData.m_ExpTotal*/);
		}
		else	percent = 0;
		m_EXPlinep[0].SetxOffset((98 - percent) / 2);
	}
	m_EXPlinep[0].m_bMove = true;
}
void cPCHead::UpdatePetHp()
{

	g_pMainState->m_Canvas.SetRedraw(m_HeartHurtp[1].GetPicRange());
	g_pMainState->m_Canvas.SetRedraw(m_HPlinep[1].GetPicRange());
	//	血条上显示的是出战召唤兽的血
	int percent;

	if (!m_pPet)return;
	//HP
	if (m_pPet->m_PetData.HPMax.GetData() != m_pPet->m_PetData.m_HP)
	{
		//伤
		if (m_pPet->m_PetData.HPMax.GetData() == m_pPet->m_PetData.m_HP2)
			percent = 0;
		else
			percent = 100 - m_pPet->m_PetData.m_HP2 * 100 / (m_pPet->m_PetData.HPMax.GetData());
		m_HeartHurtp[1].SetxOffset(percent*m_HeartHurt.m_Picture.m_Width / 100);
		//HP
		if (g_pCharacter->m_PcData.HPMax.GetData())
			percent = (m_pPet->m_PetData.m_HP * 100) / (m_pPet->m_PetData.HPMax.GetData());
		else
			percent = 0;
		m_HPlinep[1].SetxOffset((98 - percent) / 2);
	}
	m_HeartHurtp[1].m_bMove = true;
	m_HPlinep[1].m_bMove = true;
}
void cPCHead::UpdatePetMp()
{
	g_pMainState->m_Canvas.SetRedraw(m_MPlinep[1].GetPicRange());
	int percent;
	//int offset = m_CharacterHead.m_Picture.m_Height / 4;
	//MP
	if (!m_pPet)return;
	if (m_pPet->m_PetData.MPMax.GetData() != m_pPet->m_PetData.m_MP)
	{
		if (g_pCharacter->m_PcData.MPMax.GetData())
			percent = (m_pPet->m_PetData.m_MP * 100) / m_pPet->m_PetData.MPMax.GetData();
		else
			percent = 0;
		m_MPlinep[1].SetxOffset((98 - percent) / 2);
	}
	m_MPlinep[1].m_bMove = true;
	return;
}
void cPCHead::UpdatePetExp()
{
	if (!m_pPet)return;
	g_pMainState->m_Canvas.SetRedraw(m_EXPlinep[1].GetPicRange());
	//血条上显示的是出战召唤兽的血
	int percent = 0;
	//int offset = m_CharacterHead.m_Picture.m_Height / 4;

	//EXP
	int exp = GetPetExp(m_pPet->m_PetData.m_Lv + 1);
	if (m_pPet->m_PetData.m_EXP < exp)
	{
		if (exp)
		{
			percent = (int)((m_pPet->m_PetData.m_EXP * 100) / exp);
		}
		else	percent = 0;
		m_EXPlinep[1].SetxOffset((98 - percent) / 2);
	}
	m_EXPlinep[1].m_bMove = true;
	return;
}

bool cPCHead::UpdatePet()
{
	g_pMainState->m_Canvas.SetRedraw(m_PetHead.m_PreShowRect);
	int id = g_pCharacter->m_PcData.m_FightPetID;
	if (0 > id || id > 7)
	{
		m_pPet = 0;
	}
	else
	{
		if (id > -1)
			m_pPet = g_pCharacter->m_PcData.m_pPets[id];
		else m_pPet = 0;
		if (!m_pPet)return true;
		SetPetHead(m_pPet->GetID(POS_SMALLHEAD));
		UpdatePetHp();
		UpdatePetMp();
		UpdatePetExp();
	}
	return true;
}

void cPCHead::MoveTeamHead(bool mode)
{
	int xstart, ystart;
	if (!mode)
	{
		xstart = 172 + g_640 - 640;
		ystart = 3;
	}
	else
	{
		xstart = g_640 - 200 /*385 + g_640 - 640*/;
		ystart = 53/*430 + g_480 - 480*/;
	}
	for (int i = 0; i < 5; i++)
	{
		m_TeamFace[i].SetX(xstart + (4 - i) * 50);
		m_TeamFace[i].SetY(ystart);

		m_TeamBack[i].SetX(m_TeamFace[i].GetX() - 2);
		m_TeamBack[i].SetY(m_TeamFace[i].GetY() - 3);


		m_TeamPetFace[i].SetX(xstart + (4 - i) * 50);
		m_TeamPetFace[i].SetY(ystart);

	}
}

bool cPCHead::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);

	if (m_Select >= 13 && m_Select <= 16 && g_StateType == STATE_FIGHT)
	{
		return true;
	}
	switch (m_Select)
	{
	case 13:
		// 		g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID, enum_hphurt);
		// 		g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID, enum_hp);
		g_pCharacter->m_PcData.m_HP2 = g_pCharacter->m_PcData.HPMax.GetData();
		g_pCharacter->m_PcData.m_HP = g_pCharacter->m_PcData.HPMax.GetData();
		g_pHeroObj->m_Wav.Free();
		g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
		break;
	case 14:
		//		g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID, enum_mp);
		g_pCharacter->m_PcData.m_MP = g_pCharacter->m_PcData.MPMax.GetData();
		g_pHeroObj->m_Wav.Free();
		g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
		break;
	case 15:
		// 		g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID+5, enum_hphurt);
		// 		g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID+5, enum_hp);
		if (g_pCharacter->m_PcData.m_FightPetID >= 0)
		{
			cPropertyData &pet = g_pCharacter->m_PcData.m_pPets[g_pCharacter->m_PcData.m_FightPetID]->m_PetData;
			pet.m_HP2 = pet.HPMax.GetData();
			pet.m_HP = pet.HPMax.GetData();
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
		}
		break;
	case 16:
		//		g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID+5, enum_mp);
		if (g_pCharacter->m_PcData.m_FightPetID >= 0)
		{
			cPropertyData &pet = g_pCharacter->m_PcData.m_pPets[g_pCharacter->m_PcData.m_FightPetID]->m_PetData;
			pet.m_MP = pet.MPMax.GetData();
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
		}
		break;
	default:
		if (1)
		{
			m_bPetHeadMode[m_Select] = !m_bPetHeadMode[m_Select];
			g_pMainState->m_Canvas.SetRedraw(m_TeamBack[m_Select].m_PreShowRect);
		}
		break;
	}
	return true;
}


bool cPCHead::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	switch (m_Select)
	{
	case 11:
		g_pMainState->m_State.SetCharacter(g_pCharacter);
		g_pMainState->m_State.OnOff(!g_pMainState->m_State.m_NeedShow);
		break;
	case 12:
		g_pMainState->m_InterfacePet.setCharactor();
		g_pMainState->m_InterfacePet.OnOff(!g_pMainState->m_InterfacePet.m_NeedShow);
		break;
	case 13:
		if (1)
		{
			g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID, enum_hphurt);
			g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID, enum_hp);
		}
		break;
	case 14:
		if (1)
		{
			g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID, enum_mp);
		}
		break;
	case 15:
		if (1)
		{
			g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID + 5, enum_hphurt);
			g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID + 5, enum_hp);
		}
		break;
	case 16:
		if (1)
		{
			g_pMainState->m_ItemManage.FillProperty(g_pMainState->m_HeroID + 5, enum_mp);
		}
		break;

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		if (1)
		{

			if (m_bPetHeadMode[m_Select])
			{
				int teamselect = g_pMainState->m_InterfaceTeam.GetTeamTurn(m_Select);
//				if (!g_pMainState->m_FightWorkList[teamselect + 5].isExist)return true;
//				g_pMainState->m_ChaKan.Set(g_pMainState->m_FightList[teamselect + 5].m_pData);
//				g_pMainState->m_State.SetFight((cCharacter*)g_pMainState->m_FightList[teamselect + 5].m_pData->m_pIndex);
				g_pMainState->m_InterfacePet.setCharactor(teamselect);
				g_pMainState->m_InterfacePet.OnOff(!g_pMainState->m_InterfacePet.m_NeedShow);
			}
			else
			{
				int teamselect = g_pMainState->m_InterfaceTeam.GetTeamTurn(m_Select);
				if (!g_pMainState->m_FightWorkList[teamselect].isExist)
				{ 
					return true; 
				}
//				g_pMainState->m_ChaKan.Set(g_pMainState->m_FightList[teamselect].m_pData);
				g_pMainState->m_State.SetCharacter((cCharacter*)g_pMainState->m_FightWorkList[teamselect].m_pObj->m_pIndex);
				g_pMainState->m_State.OnOff(!g_pMainState->m_State.m_NeedShow);
			}
		}
		//		g_pMainState->m_ChaKan.OnOff(true);

	}
	return true;
}

void cPCHead::UpdateDate()
{
	UpdatePcHp();
	UpdatePcMp();
	UpdatePcCp();
	UpdatePcExp();
}