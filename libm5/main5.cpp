// #if defined(_DEBUG)
// #include "../libvld/vld.h"
// #endif
#include <time.h>
#include "global.h"

std::string g_ScriptPath, g_ScenePath, g_strMediaPath = "", g_Config;
int nScreenWidth, nScreenHeight, g_StateType, g_xMouse, g_yMouse;
static int g_StateTypeOld;
int g_FPS = 60, g_640 = 640, g_480 = 480, g_320 = 320, g_240 = 240, g_360 = 360;
CMainState* g_pMainState;
cCharacter* g_pCharacter;
cObj* g_pHeroObj;
HBRUSH  g_redbrush,  g_blackbrush,  g_whitebrush, g_bluebrush;
HPEN  g_WhitePen, g_BWhitePen;

BOOL g_bFillScreen;
HDC g_DC,  g_DC2, g_ShowDC;
HBITMAP g_MemBitmap;
LPDIRECTSOUND8	 g_pDirectSound = 0;
BITMAPINFO * g_pBmpinfo;
HWND  g_hWnd;
HINSTANCE g_hInst;
#if ccc_date
std::string g_strExpandPath, g_strPKPath, g_strNewBabyPath,g_strFriendPath, g_strSavePath, g_strCommonPath;
sAddPoint g_addPointAtk, g_addPointMag, g_addPointSpd,  g_addPointDef;
int g_fntSize = 16;
#endif
static auto app = cApp::getInstance();
void SetFullScreen(BOOL bFill) { app->switchScreen(); }

void Init()
{
	g_hWnd = app->getHwnd();
	app->initBmpInfo();
	g_pBmpinfo = app->getBmpInfo();
	//////////////////////////////////////////////////////////////////////////
	srand((unsigned int)time(0));
	//////////////////////////////////////////////////////////////////////////
	static CMainState MainState;
	static cFightState FightState;
	static cEndState EndState;
	static cMenuState MenuState;
	g_pMainState = &MainState;
	g_pMainState->m_pEndState = &EndState;
	g_pMainState->m_pMenuState = &MenuState;
	g_ShowDC = GetDC(g_hWnd);
	g_DC = CreateCompatibleDC(g_ShowDC);
	g_DC2 = CreateCompatibleDC(g_ShowDC);
	HPEN  oldpen = (HPEN)SelectObject(g_DC2, g_WhitePen);
	COLORREF oldcolor = SetTextColor(g_DC2, RGB(255, 255, 255));
	//////////////////////////////////////////////////////////////////////////
	g_WhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	g_BWhitePen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	//设置文本的混合模式
	SetBkMode(g_DC2, TRANSPARENT);
	//SetBkColor(g_DC2, RGB(8, 0, 0));
	//////////////////////////////////////////////////////////////////////////
	g_MemBitmap = CreateCompatibleBitmap(g_ShowDC, g_640, g_480);
	HBITMAP oldmap = (HBITMAP)SelectObject(g_DC, g_MemBitmap);
	//////////////////////////////////////////////////////////////////////////
	g_pMainState->m_pFightState = &FightState;
	g_pMainState->m_SkillManager.m_pFightState = &FightState;
	//////////////////////////////////////////////////////////////////////////
	int addtime = 1000 / g_FPS;
	//////////////////////////////////////////////////////////////////////////
	SetBkMode(g_DC, TRANSPARENT);//设置文本的混合模式
}

void firstMainState()
{
	g_pMainState->m_Tags.Add("空格键召唤说明书");
}

void spaceTest()
{
	g_pMainState->m_Instructions.OnOff();
// 	if (false)
// 	{
// 		g_pMainState->LockLv(175);
// 		g_pCharacter->m_PCData.LeveUp(10, FALSE);
// 		g_pCharacter->m_PCData.AddExp(1000000);
// 		g_pCharacter->AddMoney(1000000);
// 	}
	return;
	if (g_StateType == STATE_FIGHT)
	{
		g_pMainState->m_pFightState->SuccessFight();
		return;
	}
//	return;
	// 拜师
	g_pMainState->m_ZhuXian.SetChapter(7);
	g_pMainState->m_ZhuXian.Process(-26);
	return;
	// 门派闯关
	g_pMainState->m_ZhuXian.SetChapter(7);
	g_pMainState->m_ZhuXian.Process(26);
	return;
	// 神秘刺客
	g_pMainState->m_TaskFB.Start(3);
	g_pMainState->m_TaskFB.Process(-13);
	g_pMainState->m_TaskFB.Process(15);
	return;
	// 燕子大雁塔
	g_pMainState->m_ZhuXian.SetChapter(0);
	g_pMainState->m_ZhuXian.Process0(34);
}

bool firstMain = true;
bool Frame()
{
	switch (g_StateType)
	{
	case STATE_MAIN:
		g_pMainState->Frame();
		if (firstMain)
		{
			firstMain = false;
			firstMainState();
		}
		break;
	case STATE_FIGHT:
		g_pMainState->m_pFightState->Frame();
		break;
	case STATE_MENU:
		g_pMainState->m_pMenuState->Frame();
		break;
	case STATE_GAMEOVER:
		g_pMainState->m_pEndState->Frame();
		break;
// 	default:
// 		PostQuitMessage(1);
// 		break;
	}
	if (g_StateType == g_StateTypeOld)
	{
		return false;
	}
	g_StateTypeOld = g_StateType;
	return true;
}

LRESULT CALLBACK  WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		if (g_StateType == STATE_MENU)
		{
			break;
		}
#if ccc_m5
		g_pMainState->m_InterfaceSystem.OnOff(TRUE);
#else
		g_pMainState->m_InterFaceConfig.OnOff();
#endif
		return TRUE;
// 	case WM_DESTROY:
// 		PostQuitMessage(0);
// 		break;
	case WM_MOVE:
		if (hWnd == app->getHwnd())
		{
			app->resize();
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_SPACE)
		{
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int PASCAL WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef TESTDEBU
	g_strMediaPath = "..\\..\\Media\\";
#else
	g_strMediaPath = "Media/";
	ccc_log("定位测试");
#endif
#if ccc_m5
	g_ScenePath = g_strMediaPath + "scene\\";//地图的路径
	g_ScriptPath = g_strMediaPath + "script\\1\\"; //角色脚本的路径
#else	
	std::string g_strRoot = "";
	g_strPKPath = g_strRoot + "擂台/";
	g_strMediaPath = g_strRoot + "data/";
	g_strCommonPath = g_strMediaPath + "common/";
	g_strFriendPath = g_strRoot + "队友/";
	g_strSavePath = g_strRoot + "存档/";
	g_strExpandPath = g_strRoot + "拓展/";
	g_strNewBabyPath = g_strExpandPath + "newbb/";
	g_ScenePath = g_strMediaPath + "scene/";

	g_addPointAtk.Set(5, 0, 0, 0, 0);
	g_addPointMag.Set(0, 0, 5, 0, 0);
	g_addPointDef.Set(0, 5, 0, 0, 0);
	g_addPointSpd.Set(0, 3, 0, 0, 2);
	for (auto name : cc::efolder(g_strNewBabyPath, true, 0))
	{
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		int i = atoi(name.c_str());
		if (i >= 0 && i <= 162)
		{
			MyTest::getInstance()->newBabys.insert(i);
		}
	}
	for (auto name : cc::efolder(g_strFriendPath, true, 0))
	{
		name.pop_back();
		name.pop_back();
		name.pop_back();
		name.pop_back();
		if (name == "队长")
		{
			continue;
		}
		MyTest::getInstance()->friendNames.push_back(name);
	}
#endif
	srand((uint)&hInstance);

	auto fol = cFolder::getInstance();
	if (!fol->read(true))
	{
		return 0;
	}
#if ccc_m5
	fol->setFront({ g_strMediaPath + "media.5", g_strMediaPath + "media.zq", g_strMediaPath + "shape1.wdf", g_strMediaPath + "ui.wdf" });
#else
	fol->setFront({ g_strRoot + "ui.wdf" });

#endif
	//	fol->setFrontSmap({ g_strMediaPath + "smap.5", g_strMediaPath + "smap.6" });
	fol->apply();

	auto game = cGame::getInstance();
	game->load(g_Config = "配置.txt");
	g_640 = game->getw();
	g_480 = game->geth();
	g_320 = g_640 / 2;
	g_240 = g_480 / 2;
	if (!game->isChatShown())
	{
		g_360 = 0;
	}
	auto eiter = game->getIter();
	auto eui = game->getui();
	auto emap = game->getMap();


	auto wdfs = cWdfs::getInstance();
	wdfs->setType(emap);
	wdfs->setType(eui);
	wdfs->pushReader(eiter);

#if ccc_m5
	cWdf::getColor()->loadRoot(g_strMediaPath + "shape.wd1");
#else
	cWdf::getColor()->loadRoot(g_strRoot + "shape.wd1");
#endif
	cWdf::getMp3()->loadRoot(fol->getMusic());
	cWdf::getWav()->loadRoot(fol->getSound());


	auto class_proc = app->initClass(hInstance, "狼宝最帅");
	class_proc.lpfnWndProc = WindowProc;
	if (!RegisterClass(&class_proc))
	{
		return 0;
	}
	app->setSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), g_640, g_480, g_360);
	if (!app->init(hInstance, class_proc.lpszClassName))
	{
		return 0;
	}

	app->start();

	float inv = 1.0f / g_FPS;
	auto loop = cLoop::getInstance();
	loop->init(inv);

	auto windsoul = cWindSoul::getInstance();
	auto chwnd = app->getChildHwnd();
	windsoul->create(app->getHwnd(), chwnd, g_640, g_480, g_360);
	if (chwnd != nullptr && g_360 > 0)
	{
		::SetWindowText(app->getChildHwnd(), "v20190720");
	}

	cInput::getInstance()->init(app->getHwnd(), g_hInst = hInstance);
//	getWeimei();
	Init();
#if ccc_m5
	g_pMainState->Init();
	g_StateTypeOld = g_StateType = STATE_MENU;
#else
	g_StateTypeOld = g_StateType = STATE_MAIN;
#endif
	Frame();
	int tick = 0;
	while (true)
	{
		if (loop->peek())
		{
			if (loop->isBreak())
			{
				break;
			}
			continue;
		}
		if (!loop->loop())
		{
			continue;
		}
		if ((++tick) > g_FPS)
		{
			tick = 0;
#if ccc_m5
			::SetWindowText(g_hWnd, "梦幻群侠传5");
#else
			::SetWindowText(g_hWnd, "梦幻群侠传5.日期版");
#endif
		}
		cInput::getInstance()->update();
		if (Frame())
		{
			g_pMainState->m_Canvas._canvas.clear();
			g_pMainState->m_Canvas.push();
		}
		else
		{
			windsoul->clear();
			windsoul->blit();
		}
		if (g_StateType == STATE_EXT)
		{
			break;
		}
	}
	quick_exit(0);
	return 0;
}
