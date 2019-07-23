#include "_global.h"
#include "_txt.h"



bool cInterfaceChannel::Init()
{
	for (int i = 0; i < 30; i++)
	{
		m_ContextList[i].m_ShowStyle = 2;
		m_ContextList[i].m_Name.m_hFont = g_pMainState->m_hFont[0];
		m_ContextList[i].m_Name.SetColor(RGB(0, 255, 0));
		for (int k = 0; k < 6; k++)
		{
			m_ContextList[i].m_TextLineList[k].m_line.SetColor(RGB(255, 255, 255));
			m_ContextList[i].m_TextLineList[k].m_line.m_hFont = g_pMainState->m_hFont[0];
		}
	}
	m_Channel[0].Load(0x65C5B7EE);
	m_Channel[1].Load(0xF9858C95);
	m_Channel[2].Load(0x1B1DCE56);
	m_Channel[3].Load(0x43700E25);
	m_Channel[4].Load(0xF9ADC3DA);
	ccm::get()->pushWdf("频道", 0x65C5B7EE);
	ccm::get()->pushWdf("频道", 0xF9858C95);
	ccm::get()->pushWdf("频道", 0x1B1DCE56);
	ccm::get()->pushWdf("频道", 0x43700E25);

	ccm::get()->pushWdf("频道", 0xF9ADC3DA);
// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData << "表情.txt";
// 	File.open(oss.str());
// 
// 	string dustbin;
// 	for (int i = 0; i < 120; i++)
// 	{
// 		File >> m_FaceId[i];
// 		cct::get()->pushChat(toString("表情%d", i), m_FaceId[i]);
// 		getline(File, dustbin);
// 	}
// 	File.close();

	const auto& chats = ctt::getChats();
	for (int i = 0; i < 129; i++)
	{
		m_FaceId[i] = chats[i % 120].uid;
	}

	m_HeightChannel = 120;
	m_WidthChannel = 310;
	m_NeedShow = true;
	m_Back.Load(0xB5FDF1AC); // 0xA0120D38
	for (int i = 0; i < 4; i++)
	{
		m_BackP[i].Set(&m_Back);
		m_BackP[i].m_bStatic = true;
		m_BackP[i].m_bShadow = 20;
	}
	m_BackP[0].SetxOffset(m_Back.m_Picture.m_Width - m_WidthChannel / 2);
	m_BackP[2].SetxOffset(m_BackP[0].GetxOffset());
	m_BackP[0].SetyOffset(m_Back.m_Picture.m_Height - m_HeightChannel / 2);
	m_BackP[1].SetyOffset(m_BackP[0].GetyOffset());

	m_BackP[1].SetxOffset2(m_Back.m_Picture.m_Width - m_WidthChannel / 2);
	m_BackP[3].SetxOffset2(m_BackP[1].GetxOffset2());
	m_BackP[1].SetShowWidth(m_WidthChannel / 2);
	m_BackP[3].SetShowWidth(m_BackP[1].GetShowWidth());

	m_BackP[2].SetyOffset2(m_Back.m_Picture.m_Height - m_HeightChannel / 2);
	m_BackP[2].SetShowHeight(m_HeightChannel / 2);

	m_BackP[3].SetyOffset2(m_BackP[2].GetyOffset2());
	m_BackP[3].SetShowHeight(m_BackP[2].GetShowHeight());


	TEXTMETRIC tx;
	GetTextMetrics(g_DC, &tx);
	m_HeightCube = tx.tmHeight + 3;
	m_MoveIcon.Load(0x32BE710D);
	m_MoveIcon.m_NeedShow = true;
	m_MoveIcon.m_Picture.m_x = m_xPos;
	m_MoveIcon.m_Picture.m_y = m_yPos + m_HeightChannel - 20;
	Move(0, g_480 - m_HeightChannel);
	m_ContextStart = -1;  //第1条的位置
	return true;
}

bool cInterfaceChannel::Show(cCanvas* pCanvas)
{
	if (g_GlobalValues[9])
	{
		return true;
	}
	for (int i = 0; i < 4; i++)
		pCanvas->Add(&m_BackP[i], 1);

	int linestart = m_ContextShowStart;
	//接下来显示文字
	for (int i = 0; i < m_ContextShowNum; i++)
	{
		m_ContextList[linestart].Show(pCanvas);
		linestart -= 1;
		if (linestart < 0)linestart = 29;
	}
	return true;
}

bool cInterfaceChannel::ProcessInput()
{
	return true;
}

bool cInterfaceChannel::AddNewString(string str, string name, int channel)
{
	if (channel < 2)//如果是当前或队伍
	{
		int i = 0;
		for (; i < 5; i++)
		{
			if (g_pMainState->m_FightWorkList[i].isExist)
			{
				if (0 == g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString().compare(name))
				{
					if (g_StateType != STATE_FIGHT)
					{
						g_pMainState->m_FightWorkList[i].m_pObj->m_ContextList.SetFaceText(str, g_pMainState->m_hFont[0], 114);
						g_pMainState->m_FightWorkList[i].m_pObj->m_ShowTime = 210;
						g_pMainState->m_FightWorkList[i].m_pObj->MoveDialog();
					}
					break;
				}
			}
		}
		if (i == 5)
		{
			for (i = 10; i < 15; i++)
			{
				if (g_pMainState->m_FightWorkList[i].isExist)
					if (0 == g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString().compare(name))
					{
						if (g_StateType != STATE_FIGHT)
						{
							g_pMainState->m_FightWorkList[i].m_pObj->m_ContextList.SetFaceText(str, g_pMainState->m_hFont[0], 114);
							g_pMainState->m_FightWorkList[i].m_pObj->m_ShowTime = 210;
							g_pMainState->m_FightWorkList[i].m_pObj->MoveDialog();
						}
					break;
					}
			}
		}
		if (i == 15)
		{
			g_pMainState->m_TriggerDialog.Process(1, true);
			return false;
		}
	}

	m_ContextStart += 1;
	if (m_ContextStart > 29)
		m_ContextStart = 0;
	if (m_ContextNum < 30)
		m_ContextNum += 1;
	m_ContextList[m_ContextStart].SetFaceText(&m_Channel[channel], name, str, g_pMainState->m_hFont[0], m_WidthChannel - 10);
	m_ContextShowStart = m_ContextStart;


	for (int i = 0; i < 4; i++)
		g_pMainState->m_Canvas.SetRedraw(m_BackP[i].m_PreShowRect);
	UpDateShow();
	return true;
}

bool cInterfaceChannel::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_BackP[0].m_x = x;
	m_BackP[0].m_y = y;
	m_BackP[1].m_x = x + m_WidthChannel / 2;
	m_BackP[1].m_y = y;
	m_BackP[2].m_x = x;
	m_BackP[2].m_y = y + m_HeightChannel / 2;
	m_BackP[3].m_x = m_BackP[1].m_x;
	m_BackP[3].m_y = m_BackP[2].m_y;
	return true;
}

bool cInterfaceChannel::CheckL()
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
		break;
	}
	return false;
}

void cInterfaceChannel::UpDateShow()
{
	if (!m_ContextNum)return;
	//const int gap = 10;
	//接下来显示文字
	int linestart = m_ContextShowStart;
	int xStart = m_xPos + 2;
	//计算窗口能容纳的对话数
	int yStart = 5;
	m_ContextShowNum = 0;
	while (true)
	{
		yStart += m_ContextList[linestart].m_Height;
		if (yStart > m_HeightChannel)
			break;
		if (m_ContextShowNum == m_ContextNum)
			break;
		linestart -= 1;
		if (linestart < 0)linestart = 29;
		m_ContextShowNum += 1;
	}
	linestart += 1;
	if (linestart > 29)linestart = 0;
	yStart = m_yPos + 5;
	//设置对话的位置
	for (int i = 0; i < m_ContextShowNum; i++)
	{
		m_ContextList[linestart].SetPos(xStart, yStart);
		yStart += m_ContextList[linestart].m_Height;
		linestart += 1;
		if (linestart > 29)linestart = 0;
	}
}

