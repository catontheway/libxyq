#include "_global.h"


bool cBangPaiJiNengXueXi::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_NeedShow = false;
	m_Back.Load(0x254E7029);

	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
// 	m_Button[0].Load(0x35A981D3);
// 	m_Button[1].Load(0x2BD1DEF7);
	m_Button[0].Load(0x86D66B9A);
	m_Button[1].Load(0x86D66B9A);

	for (int i = 0; i < 2; i++)
	{
		
		m_Button[i].SetStatic(true);
		m_tButton[i].SetColor(RGB(255, 255, 255));
	}
	m_tButton[0].SetString("学习");
	m_tButton[1].SetString("学习*10");
	m_tXueFei.SetString("100");
	for (int i = 0; i < c_NumFuZhu; i++)
	{
		m_SkillHead[i].Load(g_pMainState->m_SkillManager.m_FuZhuSkillList[i].m_BigHead);
	}
	m_SelectMark.Load(0x10921CA7);
	m_SelectMark.m_NeedShow = false;
	
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);

	return true;
}

bool cBangPaiJiNengXueXi::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(x, y);
	m_Cancel.SetXY(x + m_Back.GetWidth() - 20, y + 3);
	int xstart, ystart;
	xstart = 147 + x;
	ystart = 331  + y;

	m_tExp.SetXY(xstart, ystart);
	m_tNeedBangGong.SetXY(xstart, ystart+25);
	m_tXueFei.SetXY(xstart, ystart+50);
	m_Button[0].SetXY(xstart,ystart+75);
	m_tButton[0].SetXCenter(m_Button[0].GetCenter());
	m_tButton[0].SetY(ystart + 78);
	m_tButton[0].UpdateXCenter();

	xstart += 234;

	m_tNeedExp.SetXY(xstart, ystart);
	m_tNeedMoney.SetXY(xstart, ystart+25);
	m_tChuBei.SetXY(xstart, ystart+50);
	m_Button[1].SetXY(xstart, ystart+75);
	m_tButton[1].SetXCenter(m_Button[1].GetCenter());
	m_tButton[1].SetY(ystart + 78);
	m_tButton[1].UpdateXCenter();

	xstart =m_xPos+ 24;
	ystart =m_yPos+ 38;
	for (int i = 0; i < c_NumFuZhu; i++)
	{
		m_SkillHead[i].SetXY(xstart+ (i%7) *69,ystart+(i/7)* 80);
		m_tSkillHead[i].SetXCenter(m_SkillHead[i].GetCenter());
		m_tSkillHead[i].SetY(m_SkillHead[i].GetY()+50);
		m_tSkillHead[i].UpdateXCenter();
	}
	m_tMiaoShu.SetXY(m_xPos+30,m_yPos+207);
	m_tMiaoShu.LockWidth(440);

	if (m_SelectMark.m_NeedShow)
	{
		m_SelectMark.SetXY(m_SkillHead[m_SkillSelect].GetX() - 3, m_SkillHead[m_SkillSelect].GetY() - 5);
	}

	return true;
}

bool cBangPaiJiNengXueXi::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	for (int i = 0; i < 7; i++)//c_NumFuZhu; i++)
	{
		pCanvas->Add(&m_SkillHead[i], 1);
		pCanvas->Add(&m_tSkillHead[i]);
	}
	pCanvas->Add(&m_Cancel,1);
	pCanvas->Add(&m_tExp);
	pCanvas->Add(&m_tNeedBangGong);
	pCanvas->Add(&m_tNeedExp);
	pCanvas->Add(&m_tNeedMoney);
	pCanvas->Add(&m_tXueFei);
	pCanvas->Add(&m_tChuBei);
	pCanvas->Add(&m_tMiaoShu);
	pCanvas->Add(&m_SelectMark, 1);
	for (int i = 0; i < 2; i++)
	{
		pCanvas->Add(&m_Button[i],1);
		pCanvas->Add(&m_tButton[i]);
	}
	return true;
}

bool cBangPaiJiNengXueXi::CheckL()
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
		m_Sleeptime = 0;
		if (!Leveupskill(1))
		{
			return true;
		}
		UpDate();
		break;
	case 2:
		m_Sleeptime = 0;
		for (int i = 0; i < 10; ++i)
		{
			if (!Leveupskill(1))
			{
				break;
			}
		}
		UpDate();
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

void cBangPaiJiNengXueXi::OnOff(bool NeedShow)
{
	if (NeedShow)
	{
		Init();
		UpDate();
		SetSkillSelect(0);
	}
	else
	{
		cct::autoSave();
	}
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
	return ;
}

void cBangPaiJiNengXueXi::UpDate()
{
	ostringstream oss;
	oss << "/";
	oss << m_BangpaiSkilllv;
	string maxskilllv = oss.str();
	string text;
	for (int i = 0; i < c_NumFuZhu; i++)
	{
		ostringstream oss2;
		oss2 << g_pCharacter->m_PcData.m_FuZhuSkillLvList[i];
		text = oss2.str();
		text += maxskilllv;
		m_tSkillHead[i].SetString(text);
		m_tSkillHead[i].UpdateXCenter();
	}
	oss.str("");
	oss << g_pCharacter->m_PcData.m_EXP;
	m_tExp.SetString(oss.str());

	oss.str("");
	oss << g_pCharacter->m_PcData.m_Money[2];
	m_tChuBei.SetString(oss.str());

// 	oss.str("");
// 	oss << g_pCharacter->m_PcData.m_EXP;
// 	m_tExp.SetString(oss.str());

}

void cBangPaiJiNengXueXi::SetSkillSelect(int select)
{
	if (select < 0)
	{
		m_SelectMark.m_NeedShow = false;
		m_SkillSelect = -1;
		return;
	}
	m_SelectMark.m_NeedShow = true;
	m_SelectMark.SetXY(m_SkillHead[select].GetX()-3, m_SkillHead[select].GetY()-5);
	m_SkillSelect = select;
	sSkill* pSkill = g_pMainState->m_SkillManager.GetFuZhuSkill(select);
	m_tMiaoShu.SetString(pSkill->m_Text);
	ostringstream oss;
	m_NeedExp = GetMainSkillExp(g_pCharacter->m_PcData.m_FuZhuSkillLvList[select] + 1);
	oss << m_NeedExp;
	m_tNeedExp.SetString(oss.str());
	oss.str("");
	m_NeedMoney = GetMainSkillMoney(g_pCharacter->m_PcData.m_FuZhuSkillLvList[select] + 1);
	oss << m_NeedMoney;
	m_tNeedMoney.SetColor(GetPriceColor((int)m_NeedMoney));
	m_tNeedMoney.SetString(oss.str());


	m_NeedBangGong = 0;// g_pCharacter->m_PCData.m_FuZhuSkillLvList[select];
	oss.str("");
	oss << g_pCharacter->m_PcData.m_Money[0];// m_NeedBangGong;
	m_tNeedBangGong.SetString(oss.str());
}

bool cBangPaiJiNengXueXi::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	ResetButton();
	m_Select = -1;
	g_pMainState->SetMouseOnMap(false);
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	for (int i = 0; i <7;i++)// c_NumFuZhu; i++)
	{
		if (isOn(g_xMouse, g_yMouse, m_SkillHead[i].m_PreShowRect))
		{
			m_Select = i + 10;
			return CheckL();
		}
	}
	for (int i = 0; i < 2;i++)
		if(CheckOn(&m_Button[i], i+1))return true;
	if(CheckOn(&m_Cancel, 0))return true;
	//准备移动
	m_Select = 7;
	if (CheckL())return true;
	m_Select = 0;
	if (CheckRB())return true;
	return true;
}
bool cBangPaiJiNengXueXi::CheckRB()
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


bool cBangPaiJiNengXueXi::Leveupskill(int lvup)
{
	if (m_SkillSelect < 0)return false;
	
	int& Skilllv = g_pCharacter->m_PcData.m_FuZhuSkillLvList[m_SkillSelect];
// 	if (maxLv <= Skilllv)
// 	{
// 		g_pMainState->m_SkillManager.lvUpFuZhuSkill(g_pMainState->m_HeroID, g_pMainState->m_SkillManager.GetFuZhuSkill(m_SkillSelect)->m_Id, 0);
// 		return false;
// 	}
	if (Skilllv >= m_BangpaiSkilllv)
	{
		g_pMainState->m_Tags.Add("已达上限");
		return false;
	}
// 	INT64 oldmoney[3]/*,oldbanggong*/;
// 	INT64 oldexp;
// 	for (int i = 0; i < 3; i++)
// 		oldmoney[i] = g_pCharacter->m_PcData.m_Money[i];
// 	oldexp = g_pCharacter->m_PcData.m_EXP;
//	oldbanggong = g_pCharacter->m_PcData.m_BangPaiPoint;

	/*if (!g_pCharacter->m_PCData.CostBangGong(m_NeedBangGong))
	{
		g_pCharacter->m_PCData.m_BangPaiPoint=oldbanggong;
		g_pMainState->m_Tags.Add("帮贡不够");
		return false;
	}*/
	if (!g_pCharacter->m_PcData.AddExp(-GetMainSkillExp(Skilllv + 1)/*m_NeedExp*/,0,false))
	{
//		g_pCharacter->m_PcData.m_BangPaiPoint = oldbanggong;
//		g_pCharacter->m_PcData.m_EXP = oldexp;
		g_pMainState->m_Tags.Add("经验不够");
		return false;
	}
	if (!g_pCharacter->m_PcData.AddMoney(-GetMainSkillMoney(Skilllv + 1)/*(int)(-m_NeedMoney)*/, 0, 0, false))
	{
//		g_pCharacter->m_PcData.m_BangPaiPoint = oldbanggong;
//		g_pCharacter->m_PcData.m_EXP = oldexp;
		g_pMainState->m_Tags.Add("盘缠不足");
		return false;
	}
	++Skilllv;// += lvup;
//	g_pMainState->m_SkillManager.lvUpFuZhuSkill(g_pMainState->m_HeroID, g_pMainState->m_SkillManager.GetFuZhuSkill(m_SkillSelect)->m_Id, lvup);
//	Skilllv += lvup;
	g_pMainState->m_State.UpDatePcDate();
	SetSkillSelect(m_SkillSelect);
	return true;
}
