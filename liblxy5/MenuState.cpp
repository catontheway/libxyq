#include "_global.h"



bool cMenuState::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
		if (1)
		{
			m_Button[0].SetFrame帧(1);
			Show(&g_pMainState->m_Canvas);
			g_pMainState->m_Canvas.Show();
			if (!g_pMainState->m_bInit3)
			{
				g_pMainState->Init3();
			}
			g_StateType = STATE_MAIN;
			g_pMainState->isInit = true;
			g_pMainState->ResetAll();
			g_pMainState->m_ZhuXian.SetChapter(0);
			g_pMainState->m_ZhuXian.Process(0);

		}
		break;
	case 1:
		if (1)
		{
			m_Button[1].SetFrame帧(1);
			vector<string> strselect;
			g_pMainState->m_InterfaceSystem.GetSaveTitle(strselect);
			g_pMainState->m_Dialog.OnOff(false);
			g_pMainState->m_Dialog.Reset();
			g_pMainState->m_Dialog.m_bRetSelect = true;

			m_bMode = 2;
			g_pMainState->m_Dialog.SetString("选择读取位置", strselect[0], strselect[1], strselect[2], strselect[3]);

			g_pMainState->m_Dialog.OnOff(true);
			return true;
		}
		break;
	case 2:
		if (1)
		{
			g_StateType = STATE_EXT;
			return true;
		}
		break;
	}
	return true;
}





bool cMenuState::Init(void* pData /*= 0*/)
{
	if (m_bInit)return true;
	m_bInit = true;

	m_tButton.resize(3);
	m_Button.resize(3);

	g_pMainState->m_Canvas.m_NeedShowMap = false;
	g_pMainState->Init2();
	g_pMainState->UpDateInput();
	g_pMainState->m_Cursor.m_Data.SetXY(g_xMouse, g_yMouse);
	string path;
//	path = g_pathData;
	path += "数据\\开始界面\\0.BMP";
	m_Back.LoadBMP(path.c_str());

	m_tButton[0].SetString("开始游戏");
	m_tButton[1].SetString("读取进度");
	m_tButton[2].SetString("退出游戏");
	for (int i = 0; i < 3; i++)
	{
		m_Button[i].Set(&g_pMainState->m_Button4);
		m_Button[i].m_bStatic = true;
		m_tButton[i].SetColor(RGB(255, 255, 255));
	}
	Move(0, 0);



	g_pMainState->Init3();
	return true;

	////创建线程
	if (!m_hThread)
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, CREATE_SUSPENDED, NULL);
		//	m_hThread = CreateThread(0, 0, ThreadProc, this, 0, 0);
	}

	return true;
}

void cMenuState::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(x, y);
	for (int i = 0; i < 3; i++)
	{
		m_Button[i].SetXY(120 + 200 * (i)-m_Button[i].GetWidth() / 2, 400);
		m_tButton[i].SetXCenter(m_Button[i].GetCenter());
		m_tButton[i].SetY(m_Button[i].GetY() + 3);
		m_tButton[i].UpdateXCenter();
	}
}

bool cMenuState::Frame(void* pData /*= 0*/)
{
	if (!m_bInit)Init();
	g_pMainState->UpDateInput();
	if (m_pPre)
	{
		m_pPre->SetFrame帧(0);
		m_pPre = 0;
	}
	if (m_bMode == 2)
	{
		if (g_pMainState->m_Dialog.m_retSelect > -1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4)
			{
				g_pMainState->ResetAll();
				Show(&g_pMainState->m_Canvas);
				g_pMainState->m_Canvas.Show();
				if (!g_pMainState->m_bInit3)
				{
					g_pMainState->Init3();
				}
				g_pMainState->isInit = true;
				g_pMainState->m_InterfaceSystem.Load(g_pMainState->m_Dialog.m_retSelect);
			}
			m_bMode = 0;
			return true;
		}

	}

	if (g_pMainState->m_Dialog.m_NeedShow)
		g_pMainState->m_Dialog.ProcessInput();
	if (g_pMainState->Keyboard.GetKeyState(DIK_1))
	{
		g_pMainState->Keyboard.SetLock(DIK_1);
		m_ID += 1;
		m_ID %= 15;
		ostringstream oss;
//		oss << g_pathData << "数据\\开始界面\\";
		oss << m_ID;
		oss << ".BMP";
		m_Back.LoadBMP(oss.str());//0x01408ACC);
		g_pMainState->m_Canvas.SetRedrawAll();
	}
	for (int i = 0; i < 3; i++)
		if (isOn(g_xMouse, g_yMouse, m_Button[i].m_PreShowRect))
		{
		m_Select = i;
		m_Button[i].SetFrame帧(2);
		m_pPre = &m_Button[i];
		m_pPre->m_bMove = true;
		if (CheckL())return true;
		}
	Show(&g_pMainState->m_Canvas);
	g_pMainState->ShowInterface2();
	g_pMainState->m_Canvas.Show();
	return true;
}

void cMenuState::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	for (int i = 0; i < 3; i++)
	{
		pCanvas->Add(&m_Button[i], 1);
		pCanvas->Add(&m_tButton[i]);
	}
	if (g_pMainState->m_Dialog.m_NeedShow)
		g_pMainState->m_Dialog.Show(pCanvas);
}

unsigned int WINAPI cMenuState::ThreadProc(_In_ LPVOID lpParameter)
{
	cMenuState* pState = (cMenuState*)lpParameter;
	g_pMainState->Init3();
	CloseHandle(pState->m_hThread);
	ExitThread(3);
}