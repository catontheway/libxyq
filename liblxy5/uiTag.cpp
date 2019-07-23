#include "_global.h"



bool cTags::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Back.Load(0x4B82870A);// 0x4B82870A; // 0x014FF746);// 0xEDCED445);// 0x436592D8);// 0xAB7B8559);
	m_Back.m_Picture.m_pData = m_Back.m_Picture.Spr.lpDate[0];
	m_Back.m_Picture.m_pAlpha = m_Back.m_Picture.Spr.lpAlpha[0];

	m_TagNum = 0;
	for (int i = 0; i < 10; i++)
	{
		m_tags[i].m_Back.Init(&m_Back.m_Picture);
		m_tags[i].m_Back.m_y = _y + i * 20;
	}
	m_Text.m_hFont = 0;
	m_Text.SetColor(RGB(255, 255, 255));
	m_Text.SetXCenter(g_half320);
	return true;
}

bool cTags::Show(cCanvas* pCanvas)
{
	if (0 == m_TagNum)return true;

	for (int i = 0; i < 10; i++)
	{
		if (m_tags[i].m_time > 0)
		{
			pCanvas->Add(&m_tags[i].m_Back, 1);
			m_tags[i].m_time -= 1;
			if (m_tags[i].m_time < 1)
			{
				m_TagNum -= 1;
			}
		}
	}
	return true;
}

bool cTags::Add(string str, int time)
{
	if (m_TagNum < 10)
	{
		if (!m_Text.m_hFont)
		{
			m_Text.m_hFont = g_pMainState->m_hFont[0];
		}
		m_TagNum += 1;
		for (int i = 0; i < 10; i++)
		{
			if (m_tags[i].m_time < 1)
			{
				m_Text.SetString(str);
				m_Text.SetY(m_tags[i].m_Back.m_y + 2);
				m_Text.UpdateXCenter();
				m_tags[i].m_Back.m_x = m_Text.m_x - 5;
				m_Back.SetXY(m_tags[i].m_Back.m_x, m_tags[i].m_Back.m_y);
				m_tags[i].m_Back.SetShowWidth(m_Text.m_Width + 10);
				m_tags[i].m_Back.Reset2(0);
				m_tags[i].m_time = time;
				m_tags[i].m_Back.Draw(&m_Text);
				RECT rect;
				m_tags[i].m_Back.GetRect(rect);
				g_pMainState->m_Canvas.SetRedraw(rect);
				return true;
			}
		}
	}
	return false;
}

void cTags::Process()
{
	if (0 == m_TagNum)return;
	if (m_Sleeptime > 0)
	{
		m_Sleeptime -= 1;
	}
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		m_Sleeptime = 0;
		m_TagNum = 0;
		for (int i = 0; i < 10; i++)
		{
			m_tags[i].m_time = 0;
		}

	}
}

cTags::~cTags()
{
	m_Back.m_Picture.m_pData = 0;
	m_Back.m_Picture.m_pAlpha = 0;
}

void cTags::GetMoneyAndExp(int money, int exp /*= 0*/, int chubei, int expbb, bool needtag)
{
	ostringstream oss;
	if (0 != money)
	{
		if (money > 0)
		{
			oss << "大洋 +";
			oss << money;
		}
		else
		{
			oss << "大洋 -";
			oss << -money;
		}
//		oss << "块大洋";
		if (needtag)
			Add(oss.str());
//		g_pMainState->m_Channel.AddNewString(oss.str());
		oss.str("");
	}

	if (0 != chubei)
	{
		if (chubei > 0)
		{
			oss << "储备 +";
			oss << chubei;
		}
		else
		{
			oss << "储备 -";
			oss << -chubei;
		}
//		oss << "储备金";
		if (needtag)
			Add(oss.str());
//		g_pMainState->m_Channel.AddNewString(oss.str());
		oss.str("");
	}
	if (0 != exp)
	{
		if (exp > 0)
		{
			oss << "经验 +";
			oss << exp;
		}
		else
		{
			oss << "经验 -";
			oss << -exp;
		}
//		oss << "点经验";
		if (needtag)
			Add(oss.str());
//		g_pMainState->m_Channel.AddNewString(oss.str());
		oss.str("");
	}
	if (0 != expbb && g_pCharacter->m_PcData.m_FightPetID >= 0)
	{
		if (expbb > 0)
		{
			oss << "召唤兽经验 +";
			oss << expbb;
		}
		else
		{
			oss << "召唤兽经验 -";
			oss << -expbb;
		}
//		oss << "点经验";
		if (needtag)
			Add(oss.str());
//		g_pMainState->m_Channel.AddNewString(oss.str());
//		oss.str("");
	}
}

void cTags::GetItem(string itemname)
{
	ostringstream oss;
//	oss << "你得到了";
	oss << itemname << " +1";
	Add(oss.str());
	g_pMainState->m_Channel.AddNewString(oss.str());
}


bool cTag1::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Text.m_hFont = g_pMainState->m_hFont[5];
	m_Text.SetColor(RGB(0, 0xff, 0));
// 	m_Text.SetXY(436, 38);
// 	m_Text.SetString("游戏免费勿商用");
	return true;
}

bool cTag1::Show(cCanvas* pCanvas)
{
	return true;
// 	static int i = 0;
// 	if ((++i) < 180)
// 	{
// 		return true;
// 	}
	// 	if ((i % 30) < 15)
	// 	{
	// 		return true;
	// 	}
	m_Text.SetXY(g_xMouse - 20, g_yMouse - 12 - 10);
	const auto& m = g_pMainState->m_Map.m_pMap;
	m_Text.SetString(toString("%d, %d", (m->GetXCenter() + g_xMouse - g_half320) / 20, (m->m_Height - m->GetYCenter() - g_yMouse + g_half240) / 20));
	pCanvas->Add(&m_Text);
	return true;
}


