#include "_global.h"


bool cEndState::Init(void* pData /*= 0*/)
{
	if (m_bInit)return true;
	m_bInit = true;
	// 	string path = g_strMyDataPath;
	// 	path += "数据\\开始界面\\end.BMP";
	// 	m_Back.LoadBMP(path);
	m_Title.SetColor(RGB(255, 0, 0));
	m_Title.SetXCenter(g_half320);
	m_Title.SetY(200);
	m_Title.m_hFont = g_pMainState->m_hFont[2];
	m_Context.SetColor(RGB(255, 255, 255));
	m_Context.SetXCenter(g_half320);
	return true;
}

void cEndState::Set(string title, string context)
{
	Init();
	for (int i = 0; i < 10; i++)
	{
		g_pMainState->FreeFightList(i);
	}
	g_pMainState->m_Canvas.m_NeedShowMap = false;
	g_pMainState->ResetAll();

	g_pMainState->m_Canvas.SetRedrawAll();
	m_Title.SetString(title);
	m_Context.SetString(context);
	m_Title.UpdateXCenter();

	m_Context.SetY(m_Title.GetY() + m_Title.m_Height + 5);
	m_Context.UpdateXCenter();
}

bool cEndState::Frame(void* pData /*= 0*/)
{
	//	g_pMainState->m_Canvas.Add(&m_Back, 1, 1);
	g_pMainState->m_Canvas.Add(&m_Title);
	g_pMainState->m_Canvas.Add(&m_Context);
	g_pMainState->UpDateInput();
	if (CheckL())return true;
	g_pMainState->m_Cursor.Show(g_xMouse, g_yMouse);
	g_pMainState->m_Canvas.Show();
	return true;
}

bool cEndState::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	g_pMainState->m_pMenuState->Init();

	for (int i = 0; i < 300; i++)
	{
		g_pMainState->m_Canvas.m_CanvasCube[i].PicNumOfPreFrame = -1;

	}

	g_StateType = STATE_MENU;
	return true;
}




