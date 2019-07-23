#include "_global.h"



bool cInterfaceFB::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Back.Load(0x1A2DEAB9);//1259967470);
	ccm::get()->pushWdf("副本面板", 0x1A2DEAB9);
	m_Back.SetStatic(true);
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Title.SetColor(RGB(255, 255, 255));
	m_Title.SetString("创建副本");

	m_TButton.SetColor(RGB(255, 255, 255));
	m_TButton.SetString("创建");

	m_MouseOnBack.Load(0x8F43CE91);//0x51E340B6);
	ccm::get()->pushWdf("副本面板select", 0x8F43CE91);
	m_MouseOnBack.m_NeedShow = false;
	m_MouseOnBack.SetShowWidth(140);

	m_tFBName.resize(6);
	m_tFBName[0].SetString("乌鸡国");
	m_tFBName[1].SetString("水路大会");
	m_tFBName[2].SetString("车迟国");
	m_tFBName[3].SetString("四门绝阵");
	m_tFBName[4].SetString("四季");
	m_tFBName[5].SetString("十二门派");
	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}

bool cInterfaceFB::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);
	pCanvas->Add(&m_Button, 1);
	pCanvas->Add(&m_TButton);
	pCanvas->Add(&m_Title);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_MouseOnBack, 1);
	for (int i = 0; i < m_tFBName.size(); i++)
	{
		pCanvas->Add(&m_tFBName[i]);
	}
	return true;
}

bool cInterfaceFB::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	m_Select = -1;
	ResetButton();
	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	g_pMainState->SetMouseOnMap(false);
	if (CheckOn(&m_Cancel, 0))return true;
	if (CheckOn(&m_Button, 1))return true;
	if (isOn(g_xMouse, g_yMouse, m_Rect))
	{
		m_Select = (g_yMouse - m_Rect.top) / 20 + 10;
		m_MouseOnBack.m_NeedShow = true;
		m_MouseOnBack.SetXY(m_xPos + 16, m_tFBName[m_Select - 10].GetY() - 3);
		if (CheckL())return true;
	}
	else
	{
		m_MouseOnBack.m_NeedShow = false;
	}
	if (CheckRB())return true;
	return true;

}

bool cInterfaceFB::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.m_Picture.m_x = x;
	m_Back.m_Picture.m_y = y;
	m_Cancel.SetXY(x + m_Back.GetWidth() - 20, y + 3);
	m_Button.Load(0x79D01E0E);
	ccm::get()->pushWdf("副本面板按钮", 0x79D01E0E);
	m_Button.SetStatic(true);

	m_Title.SetXCenter(m_xPos + 77);
	m_Title.SetY(m_yPos + 3);
	m_Title.UpdateXCenter();
	m_Rect.left = x + 30;
	m_Rect.top = y + 40;
	m_Rect.bottom = m_Rect.top + m_tFBName.size() * 20;
	m_Rect.right = m_Rect.left + 115;

	for (int i = 0; i < m_tFBName.size(); i++)
	{
		m_tFBName[i].SetXY(m_Rect.left, m_Rect.top + i * 20);
	}
	m_Button.SetXY(m_xPos + m_Back.GetWidth() / 2 - m_Button.GetWidth() / 2, m_yPos + 204);
	m_TButton.SetXCenter(m_Button.GetCenter());
	m_TButton.SetY(m_Button.GetY() + 3);
	m_TButton.UpdateXCenter();

	m_Title.SetXCenter(m_xPos + 77);
	m_Title.SetY(m_yPos + 3);
	m_Title.UpdateXCenter();
	return true;
}

bool cInterfaceFB::CheckL()
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
		OnOff(false);
		break;
	case 1:
		m_Button.SetFrame(1);
		if (m_TrueSelect > -1)
		{
			if (!g_pCharacter->m_PcData.AddMoney(-50000, 0, 0, false))
			{
				g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->Talk("钱不够呢......");
				return true;
			}
			else if (m_TrueSelect <= 4)
			{
				g_pMainState->m_TaskFB.Start(m_TrueSelect);
				ostringstream oss;
				oss << "得到了副本任务,可以从#R";
				oss << g_pMainState->m_TaskFB.m_TextList[0];
				oss << "#R的#R";
				oss << g_pMainState->m_TaskFB.m_TextList[1];
				oss << "#R处进入副本";
				g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->Talk(oss.str());
				g_pMainState->m_TaskFB.Process(0);

				sJob job;
				job.m_Context = oss.str();
				job.m_pTask = &g_pMainState->m_TaskFB;
				job.m_Time = 100;
				job.m_Title = "副本";
				g_pMainState->m_Job.AddaJob(job);
			}
			else
			{
				g_pMainState->m_TaskHuoDong.Start(门派闯关);
				g_pMainState->m_TaskHuoDong.SetTrigger(&g_pMainState->m_taskSM, -1, 12);
				g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->Talk("长安 #R107,200#R 门派闯关使者");
			}
		}
		break;
	default:
		if (1)
		{
			if (m_TrueSelect == m_Select - 10)return true;
			if (m_TrueSelect > -1)
				m_tFBName[m_TrueSelect].SetColor(0);
			m_TrueSelect = m_Select - 10;
			m_tFBName[m_TrueSelect].SetColor(RGB(255, 0, 0));
		}
		break;
	}
	return false;
}

void cInterfaceFB::OnOff(bool NeedShow)
{
	if (NeedShow == m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_NeedShow)
	{
		Init();
		m_TrueSelect = -1;
	}
	else
	{
		if (m_TrueSelect > 9)
			m_tFBName[m_TrueSelect - 10].SetColor(0);
		m_MouseOnBack.m_NeedShow = false;
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}



bool cInterfaceFB::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	OnOff(false);
	return true;
}

