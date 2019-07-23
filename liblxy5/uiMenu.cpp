#include "_global.h"


bool cMenu::Init()
{
//	if (m_bInit)
	m_Text.SetColor(RGB(255, 255, 255));
	m_NeedShow = true;
	m_gap = 30;
	m_Select = 0;
	m_BangPai.Load(3277532867);  //4069888541
	ccm::get()->pushWdf("按钮帮派", 3277532867);

	m_SkillAccelater.Load(3144573054);//3443219224
	ccm::get()->pushWdf("按钮F8", 3144573054);
	m_Trade.Load(0xCAB0B8B4);//0x9874B9B8
	ccm::get()->pushWdf("按钮交易", 0xCAB0B8B4);
	m_job.Load(0xA15292B2);//0x8F499AA3
	ccm::get()->pushWdf("按钮任务", 0xA15292B2);

	m_Give.Load(2119033822);//0x216FE0F8
	ccm::get()->pushWdf("按钮给予", 2119033822);
	m_back.Load(0x3D1FA249);
	ccm::get()->pushWdf("首界面背景", 0x3D1FA249);
	m_Attack.Load(1807500026);//886189649    
	ccm::get()->pushWdf("按钮攻击", 1807500026);
	m_Pet.Load(250440769);//0xD5D51AD0  410697672
	ccm::get()->pushWdf("按钮宠物", 250440769);
	////////////////////////////////////////////////////////////////////////// WDF
	m_Item.Load(240383749);// 240383749 //0x78DDA320
	ccm::get()->pushWdf("按钮包裹", 240383749);
	m_Info.Load(2088395993);//0xD5DF5927
	ccm::get()->pushWdf("按钮好友", 2088395993);
	m_Info.m_Picture.m_FrameGap = 4;
	m_System.Load(0x5116F7DF);//0x414977BD
	ccm::get()->pushWdf("按钮系统", 0x5116F7DF);
	m_Team.Load(222208523);//0x3B9F2278
	ccm::get()->pushWdf("按钮队伍", 222208523);
	m_BangPai.m_isStatic = true;
	m_SkillAccelater.m_isStatic = true;
	m_Trade.m_isStatic = true;
	m_job.m_isStatic = true;
	m_Give.m_isStatic = true;
	m_back.m_isStatic = true;
	m_Attack.m_isStatic = true;
	m_Attack.m_isStatic = true;
	m_Item.m_isStatic = true;
	m_Info.m_isStatic = true;
	m_System.m_isStatic = true;
	m_Team.m_isStatic = true;
	m_Pet.m_isStatic = true;

	// 	Move(660 - m_back.m_Picture.m_Width,
	// 		480 - m_back.m_Picture.m_Height);
	Move(g_640 + 20 - m_back.m_Picture.m_Width,
		g_480 - m_back.m_Picture.m_Height);
	return true;
}

bool cMenu::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	if (g_StateType == STATE_FIGHT)
	{
		pCanvas->Add(&m_System, 1);
		return true;
	}
	pCanvas->Add(&m_back, 1);
	pCanvas->Add(&m_Item, 1);
	pCanvas->Add(&m_Give, 1);
	pCanvas->Add(&m_Trade, 1);
	pCanvas->Add(&m_Team, 1);
	pCanvas->Add(&m_Pet, 1);
	pCanvas->Add(&m_job, 1);
	pCanvas->Add(&m_BangPai, 1);
	pCanvas->Add(&m_SkillAccelater, 1);
	pCanvas->Add(&m_Info, 1);
	pCanvas->Add(&m_System, 1);
	pCanvas->Add(&m_Attack, 1);
	if (m_SelectPre > -1)
		pCanvas->Add(&m_Text);
	return true;
}

void cMenu::Select(int x)
{
	m_Select = (x - g_640 + 325) / 30 + 1;
	if (g_StateType == STATE_FIGHT)
	{
		if (m_Select != 11)
		{
			return;
		}
	}
	if (m_SelectPre != m_Select)
	{
		m_SelectPre = m_Select;
		if (m_NowSelectPic)
		{
			m_NowSelectPic->SetY(g_480 - 35);
			m_NowSelectPic = 0;
		}
	}
	switch (m_Select)
	{
	case 1:
		m_Text.SetString("光标");
		m_NowSelectPic = &m_Attack;
		break;
	case 2:
		m_Text.SetString("物品E");
		m_NowSelectPic = &m_Item;
		break;
	case 3:
		m_Text.SetString("给予G");
		m_NowSelectPic = &m_Give;
		break;
	case 4:
		m_Text.SetString("交易X");
		m_NowSelectPic = &m_Trade;
		break;
	case 5:
		m_Text.SetString("队伍T");
		m_NowSelectPic = &m_Team;
		break;
	case 6:
		m_Text.SetString("炼妖P");
		m_NowSelectPic = &m_Pet;
		break;
	case 7:
		m_Text.SetString("任务Q");
		m_NowSelectPic = &m_job;
		break;
	case 8:
		m_Text.SetString("技能B");
		m_NowSelectPic = &m_BangPai;
		break;
	case 9:
		m_Text.SetString("快捷C");
		m_NowSelectPic = &m_SkillAccelater;
		break;
	case 10:
		m_Text.SetString("说明F");
		m_NowSelectPic = &m_Info;
		break;
	case 11:
		m_Text.SetString("系统S");
		m_NowSelectPic = &m_System;
		break;
	default:
		break;
	}
	if (m_NowSelectPic)
	{
		m_NowSelectPic->SetY(g_480 - 45);

		//	int x1 = m_xPos + (m_Select - 1)*m_gap;
		if (m_Select > 0 && m_Select < 12)
		{
			m_Text.SetXY((m_Select - 1) * m_gap + m_xPos - 20, g_480 - 25 - 30);
		}
	}
}

bool cMenu::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (!g_pMainState->GetLockMouse())return true;

	if (m_NowSelectPic)
	{
		m_NowSelectPic->SetY(g_480 - 35);
		m_NowSelectPic = 0;
		m_SelectPre = -1;
	}
	if (g_yMouse < g_480 - 30)return true;
	if (g_xMouse < g_640 - 340)return true;

	g_pMainState->SetMouseOnMap(false);
	Select(g_xMouse);
	if (CheckL())return true;

	return true;
}

bool cMenu::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;

	if (g_GlobalValues[5] == 1 || g_GlobalValues[5] == 2)
	{
		y += 8;
	}
	m_back.SetXY(x, y);
	int y1 = g_480 - 35;// 445;
	m_Attack.SetXY(x, y1);
	m_Item.SetXY(x + 30, y1);

	m_Give.SetX(x + 60);
	m_Give.SetY(y1);
	m_Trade.SetX(x + 90);
	m_Trade.SetY(y1);
	m_Team.SetX(x + 120);
	m_Team.SetY(y1);
	m_Pet.SetX(x + 150);
	m_Pet.SetY(y1);
	m_job.SetX(x + 180);
	m_job.SetY(y1);
	m_BangPai.SetX(x + 210);
	m_BangPai.SetY(y1);
	m_SkillAccelater.SetX(x + 240);
	m_SkillAccelater.SetY(y1);
	m_Info.SetX(x + 270);
	m_Info.SetY(y1);
	m_System.SetX(x + 300);
	m_System.SetY(y1);

	return true;
}

bool cMenu::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;

	if ((g_StateType == STATE_FIGHT || g_pMainState->_autoGhost) && m_Select != 11)
	{
		return true;
	}

	switch (m_Select)
	{
	case 1:
	{
		static int x = 0;
		if (++x == 3)
		{
			x = 0;
		}
		if (x == 0)
		{
			g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Attack);
		}
		else if (x == 1)
		{
			g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Team);
		}
		else if (x == 2)
		{
			g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Grab);
		}
// 		g_pMainState->m_InterfaceSystem.Save(0);
// 		g_pMainState->m_Tags.Add("存档成功");
	}
		return true;
	case 2:
		g_pMainState->m_InterfaceItem.OnOff(!g_pMainState->m_InterfaceItem.m_NeedShow);
		return true;
	case 3:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Give);
		return true;
	case 4:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Trade);
		return true;
	case 5:
		g_pMainState->m_InterfaceTeam.OnOff(!g_pMainState->m_InterfaceTeam.m_NeedShow);
		return true;
	case 6:
		//宠物,不准备写了  EB279C62 
		//			g_pMainState->SetJiangLi(g_pCharacter->m_PcData.m_Lv * g_pCharacter->m_PcData.m_Lv * 100 + 1000, 0, 0, 0, 1);
		//			g_pCharacter->m_PCData.AddExp(g_pCharacter->m_PcData.m_Lv * g_pCharacter->m_PcData.m_Lv * 100 + 1000);
		g_pMainState->_uiComPet.OnOff();
		return true;
	case 7:
		g_pMainState->m_Job.OnOff(!g_pMainState->m_Job.m_NeedShow);
		return true;
	case 8://帮派
		//			g_pMainState->SetJiangLi(0, 0, 1000000, 0, 1);
		//			g_pCharacter->AddMoney(1000000);
		g_pMainState->m_InterfaceJiNeng.setCharator(g_pCharacter);
		g_pMainState->m_InterfaceJiNeng.OnOff(!g_pMainState->m_InterfaceJiNeng.m_NeedShow);
		return true;
	case 9://快捷键
		g_pMainState->m_Accelator.OnOff(!g_pMainState->m_Accelator.m_NeedShow);
		return true;
	case 10:
	//	g_pMainState->m_Friend.OnOff(!g_pMainState->m_Friend.m_NeedShow);
		g_pMainState->_uiDescription.OnOff();
		return true;
	case 11:
		g_pMainState->m_InterfaceSystem.OnOff(!g_pMainState->m_InterfaceSystem.m_NeedShow);
		return true;
	default:
		return false;
	}
}
