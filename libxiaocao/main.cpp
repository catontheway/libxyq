#include "_global.h"

#include<Accctrl.h>  
#include<Aclapi.h> 
#include <chrono>

#include "../libutil/cFolder.h"
#pragma comment(lib,"dsound.lib")


//string g_pathData;
// string g_pathWdf;
//string gpathExpand;
// string g_pathOther;
//string g_pathPK;
//string g_pathNewBaby;
//string g_pathFriend;
string g_pathSave;
// string g_pathMusic;
//string g_pathCommon; //脚本的路径
//string g_pathMap;  //地图的路径
//string g_MapPath2;
//string g_pathSceneTxt;
const int g_fntSize = 16;
const int g_FPS = 60;
const int g_640 = 800;
const int g_480 = 576;
const int g_half320 = 400;
const int g_half240 = 288;

array<int, 128> g_GlobalValues;

CMainState* g_pMainState;
cCharacter* g_pCharacter;
cObj* g_pHeroObj;
HBRUSH  g_redbrush;
HBRUSH  g_blackbrush;
HBRUSH  g_whitebrush;
HBRUSH  g_bluebrush;
HPEN  g_WhitePen;
HPEN  g_BWhitePen;
int g_xMouse;
int g_yMouse;
//HANDLE  g_hMutex;
//CRITICAL_SECTION g_cs;
WNDCLASSEX g_wcex;
bool g_bFillScreen;
int g_StateType;
int g_StateTypeOld;
HDC g_DC;
HDC g_DC2;
HDC g_ShowDC;
HBITMAP g_MemBitmap;
LPDIRECTSOUND8	 g_pDirectSound=0;

cScript* g_pScriptParent = 0;
cScript* g_pFirst = 0;
//long  g_NumScriptActions = 0;


BITMAPINFO * g_pBmpinfo;
HWND  g_hWnd;
HINSTANCE g_hInst;
void  Resize(long Width, long Height);

int g_iFPS = 0;

LRESULT CALLBACK  WindowProc(HWND hWnd, uint uMsg, WPARAM wParam, LPARAM lParam);
static ulong UpdateTimer = timeGetTime();
static ulong CurrentTime = 0;
int nScreenWidth;
int nScreenHeight;
//std::vector<std::string> getFileNames(const std::string& path, bool isOnlyName = true);

void SetFullScreen2(bool bFill)
{

	if (bFill)												// 全屏模式
	{
		DEVMODE dmScreenSettings;								// 设备模式
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// 确保内存清空为零

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// DEVMODE结构的大小

		dmScreenSettings.dmPelsWidth = g_640;					// 所选屏幕宽度
		dmScreenSettings.dmPelsHeight = g_480; // g_480;					// 所选屏幕高度
		dmScreenSettings.dmBitsPerPel = 32;		// 每象素所选的色彩深度
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 尝试设置显示模式并返回结果，注:CDS_FULLSCREEN 移去了状态条
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			ERRBOX;
		}
		LONG styleValue = ::GetWindowLong(g_hWnd, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(g_hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		SetWindowPos(g_hWnd, 0, 0, 0, g_640, g_480, SWP_FRAMECHANGED);
	}
	else
	{//窗口化
		DEVMODE dmScreenSettings;								// 设备模式
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// 确保内存清空为零
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// DEVMODE结构的大小
		dmScreenSettings.dmPelsWidth = nScreenWidth;					// 所选屏幕宽度
		dmScreenSettings.dmPelsHeight = nScreenHeight;					// 所选屏幕高度
		dmScreenSettings.dmBitsPerPel = 32;		// 每象素所选的色彩深度
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		// 尝试设置显示模式并返回结果，注:CDS_FULLSCREEN 移去了状态条
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			ERRBOX;
		}

		::SetWindowLong(g_hWnd, GWL_STYLE, GetWindowLong(g_hWnd, GWL_STYLE)| WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		::SetWindowPos(g_hWnd, NULL, (nScreenWidth >> 1) - g_640 / 2, (nScreenHeight >> 1) - g_480 / 2, g_640, g_480, SWP_FRAMECHANGED);
		Resize(g_640, g_480);
	}


}

int PASCAL WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	srand((uint)&hInstance);
	auto folder = cFolder::getInstance();
	if (!folder->read(true))
	{
		return 0;
	}
	folder->apply();

	g_pathSave = "";
	ifstream ifile(g_pathSave + "存档.sav");

	if (ifile.is_open())
	{
		cct::loadGlobal(cInterfaceFriendQiangHua2::Load());
		ifile.close();
		if (g_GlobalValues[127] < 20180318)
		{
			// 认可版本
			ccc_msgbox("读档出错");
			return 0;
		}
	}
	else
	{
		forr(g_GlobalValues, i)
		{
			g_GlobalValues[i] = 0;
		}
		// 走速
		g_GlobalValues[7] = 2;
	}

	if (0)
	{
	//	ifile.open(g_pathOther + "更新.wdf");
		if (ifile.is_open())
		{
			ifile.close();
		}
		else
		{
			string path = g_pathSave;
			forr(path, i)
			{
				if (path[i] == '/')
				{
					path[i] = '\\';
				}
			}
			system(("md " + path).c_str());
			system(("move 更新.wdf " + path).c_str());
		}
	}

	cWasFile m_File;
//	m_File.Open((g_pathOther + "更新.wdf").c_str());
	const auto& wdfs = folder->getWdfs().at(g_GlobalValues[6] ? eIterType::iter : eIterType::jd).at((euiType)g_GlobalValues[5]);
	const auto& smaps = folder->getSmaps().at(eMapType::iter);
	auto root = folder->getRoot();
	m_File.Open("ui.wdf");
	m_File.Open("必杀.wdf");
	forv(wdfs, k)
	{
		m_File.Open((root + wdfs.at(k)).c_str());
	}
	m_File.Open((root + folder->getSound()).c_str());
	m_File.Open((root + folder->getMusic()).c_str());
	m_File.Open((root + folder->getColor()).c_str());
	forv(smaps, k)
	{
		m_File.OpenMap((root + smaps.at(k)).c_str());
	}

// 	if (g_GlobalValues[6])
// 	{
// 		m_File.Open((g_pathWdf + "迭代.wdf").c_str());
// 	}
// 	m_File.Open((g_pathWdf + "资源.wdf").c_str());
// 	m_File.Open((g_pathWdf + "宝宝.wdf").c_str());
// 	m_File.Open((g_pathWdf + "声音.wdf").c_str());
// 	m_File.Open((g_pathWdf + "染色.wdf").c_str());
// 	m_File.Open((g_pathWdf + "对话.wdf").c_str());
// 	m_File.Open((g_pathWdf + "新闻.wdf").c_str());
// 	int ui = g_GlobalValues[5];
// 	if (ui == 1)
// 	{
// 		m_File.Open((g_pathWdf + "uigy.wdf").c_str());
// 	}
// 	else if (ui == 2)
// 	{
// 		m_File.Open((g_pathWdf + "uisj.wdf").c_str());
// 	}
// 	else if (ui == 3)
// 	{
// 		m_File.Open((g_pathWdf + "uiyz.wdf").c_str());
// 	}
// 	m_File.Open((g_pathWdf + "uijd.wdf").c_str());
// 	m_File.OpenMap((g_pathWdf + "地图.wdf").c_str());

// 	cMyScript sc;
// 	auto names = getFileNames(g_pathCommon);
// 	for (auto name : names)
// 	{
// 		name.pop_back();
// 		name.pop_back();
// 		name.pop_back();
// 		name.pop_back();
// 		sc.LoadScript(name);
// 	}
// 	return 0;

	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//初始化我们的程序 
	g_hInst = hInstance;
	//InitializeCriticalSection(&g_cs);
//	g_hMutex=CreateMutex(0, 0, 0);
	g_bFillScreen = false;
	//初始化位图头
	g_pBmpinfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+sizeof(RGBQUAD)* 2);
	g_pBmpinfo->bmiHeader.biPlanes = 1;
	g_pBmpinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	g_pBmpinfo->bmiHeader.biCompression = 3;
	g_pBmpinfo->bmiHeader.biBitCount = 16;
	g_pBmpinfo->bmiHeader.biClrUsed = 0;
	g_pBmpinfo->bmiHeader.biClrImportant = 0;
	g_pBmpinfo->bmiHeader.biXPelsPerMeter = 0;
	g_pBmpinfo->bmiHeader.biYPelsPerMeter = 0;
	ulong colorbit = 0xf800;
	memmove(&g_pBmpinfo->bmiColors[0], &colorbit, sizeof(RGBQUAD));
	colorbit = 0x7e0;
	memmove(&g_pBmpinfo->bmiColors[1], &colorbit, sizeof(RGBQUAD));
	colorbit = 0x1f;
	memmove(&g_pBmpinfo->bmiColors[2], &colorbit, sizeof(RGBQUAD));
	////设计窗口
		g_wcex.cbClsExtra = 0;
		g_wcex.cbSize = sizeof(g_wcex);
		g_wcex.cbWndExtra = 0;
		g_wcex.hbrBackground = 0;
		g_wcex.hCursor = LoadCursor(0, IDC_ARROW);
		g_wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101/*IDI_ICON1*/));
		g_wcex.hIconSm = g_wcex.hIcon;
		g_wcex.lpszClassName = "狼宝最帅";
		g_wcex.hInstance = hInstance;
		g_wcex.lpfnWndProc = WindowProc;	
		g_wcex.lpszMenuName = 0;
		g_wcex.style = CS_CLASSDC;
		//注册窗口
		if (!RegisterClassEx(&g_wcex))return 0;

		//产生窗口
		g_hWnd = CreateWindow(
			g_wcex.lpszClassName,  //类名
			"浪西游",
			WS_CAPTION | WS_SYSMENU|WS_MINIMIZEBOX,//, //窗口的类型，有标题和菜单
			nScreenWidth / 2 - g_half320, nScreenHeight / 2 - g_half240, g_640, g_480,  //窗口的大小
			0, 0,          //父窗口的句柄  菜单的句柄
			g_hInst,   // 应用程序的句柄
			0
			);
		if (!g_hWnd)ERRBOX;
		Resize(g_640, g_480);
		//显标窗口并更新窗口
		ShowWindow(g_hWnd, SW_SHOW);
		UpdateWindow(g_hWnd);
	// 初始COM
	CoInitialize(NULL);


	CMainState* MainState;
	MainState = new CMainState;
	cFightState FightState;
	cEndState EndState;
	cMenuState MenuState;
	g_pMainState = MainState;
	MainState->m_pEndState = &EndState;
	MainState->m_pMenuState = &MenuState;
	g_ShowDC = GetDC(g_hWnd);
	g_DC = CreateCompatibleDC(g_ShowDC);
	g_DC2 = CreateCompatibleDC(g_ShowDC);
	HPEN  oldpen = (HPEN)SelectObject(g_DC2, g_WhitePen);
	COLORREF oldcolor = SetTextColor(g_DC2, RGB(255, 255, 255));



	g_WhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	g_BWhitePen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	
	//设置文本的混合模式
	SetBkMode(g_DC2, TRANSPARENT);
	//SetBkColor(g_DC2, RGB(8, 0, 0));

	g_MemBitmap = CreateCompatibleBitmap(g_ShowDC, g_640, g_480);
	HBITMAP oldmap = (HBITMAP)SelectObject(g_DC, g_MemBitmap);
	g_StateType =  STATE_MAIN; //STATE_MENU;//
	g_StateTypeOld = STATE_MENU;


	
	MainState->m_pFightState = &FightState;
	MainState->m_SkillManager.m_pFightState = &FightState;


	///////////////////////////////////////////////////////////////////////////
	/////////////// changing timer resolution
	///////////////////////////////////////////////////////////////////////////
	UINT TARGET_RESOLUTION = 1; // 1 millisecond target resolution
	TIMECAPS tc;
	UINT wTimerRes = 0;
	if (TIMERR_NOERROR == timeGetDevCaps(&tc, sizeof(TIMECAPS)))
	{
		wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
		timeBeginPeriod(wTimerRes);
	}
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	const float _inv = 1.0 / g_FPS;
	LONGLONG _QuadPart = (LONGLONG)(_inv * freq.QuadPart);
	// Main message loop:
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceCounter(&nLast);

	LONGLONG interval = 0LL;
	LONG waitMS = 0L;

//	LARGE_INTEGER freq;
//	QueryPerformanceFrequency(&freq);

	float _deltaTime;
	double _totalTime = 0;
	float _totalSec = 0;

	std::chrono::steady_clock::time_point _lastUpdate = std::chrono::steady_clock::now();

	MSG Msg;
	ZeroMemory(&Msg, sizeof(MSG));
	while (true /*!glview->windowShouldClose()*/)
	{
		if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		{
			if (Msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
			continue;
		}


		QueryPerformanceCounter(&nNow);
		interval = nNow.QuadPart - nLast.QuadPart;
		if (interval >= _QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart;

			////////////////////////////////////////////////////////////////////////// calculateDeltaTime
			auto now = std::chrono::steady_clock::now();

			// new delta time. Re-fixed issue #1277
// 			if (_nextDeltaTimeZero)
// 			{
// 				_deltaTime = 0;
// 				_nextDeltaTimeZero = false;
// 			}
// 			else
			{
				_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
				if (_deltaTime < 0)
				{
					break;
				}
#if defined(_DEBUG)
#else
				if (_deltaTime >= 300)
				{
					break;
				}
#endif
				_totalTime += _deltaTime;
				_totalSec += _deltaTime;
				if (_totalSec >= _inv)
				{
					while (_totalSec >= _inv)
					{
						_totalSec -= _inv;
					}
					++g_iFPS;

					////////////////////////////////////////////////////////////////////////// calculateDeltaTime

					//			g_iFPS= _totalTime * 60;

					////////////////////////////////////////////////////////////////////////// 浪时间
					if (g_pMainState->_langtimeLast >= 0)
					{
						g_GlobalValues[20] = ((int)_totalTime - g_pMainState->_langtimeOnce) + g_pMainState->_langtimeLast;
					}

//					timeval tv;
//					gettimeofday(&tv, 0);
//					if (_langtimeLast == 0 && g_GlobalValues[20] != 0)
//					{
//						_langtimeOnce = tv.tv_sec;
//						_langtimeLast = g_GlobalValues[20];
//					}
//					g_GlobalValues[21] = _langtimeLast + tv.tv_sec - _langtimeOnce;
//					if (g_GlobalValues[21] < 0 || abs(g_GlobalValues[20] - g_GlobalValues[21]) > 15)
//					{
//						resetLangTime();
//					}
//					else
//					{
//						g_GlobalValues[20] = g_GlobalValues[21];
//					}

					if (g_pMainState->m_InterfaceTeam.m_NeedShow)
					{
						g_pMainState->m_InterfaceTeam.m_tLangTime.SetString(toString("浪时间  %d:%02d:%02d",
							g_GlobalValues[20] / 3600, (g_GlobalValues[20] % 3600) / 60, g_GlobalValues[20] % 60));
					}

				}
				if (g_iFPS % 60 == 0)
				{
					SetWindowText(g_hWnd, "浪西游.小草终结版v20190712");
				}
				//////////////////////////////////////////////////////////////////////////  浪时间
				switch (g_StateType)
				{
				case STATE_MAIN:
					g_StateTypeOld = g_StateType;
					MainState->Frame();
					break;
				case STATE_FIGHT:
					if (g_StateTypeOld != STATE_FIGHT)
					{
						g_pMainState->m_Mp3.Load("战斗BOSS");
					}
					g_StateTypeOld = g_StateType;
					FightState.Frame();
					break;
				case STATE_FIGHT_MUSIC:
					g_StateTypeOld = g_StateType = STATE_FIGHT;
					FightState.Frame();
					break;
				case STATE_MENU:
					g_StateTypeOld = g_StateType;
					MenuState.Frame();
					break;
				case STATE_GAMEOVER:
					EndState.Frame();
					break;
				default:
					PostQuitMessage(1);
					break;
				}
			}
			_lastUpdate = now;
			
		//	director->mainLoop();
		//	glview->pollEvents();
		}
		else
		{
			// The precision of timer on Windows is set to highest (1ms) by 'timeBeginPeriod' from above code,
			// but it's still not precise enough. For example, if the precision of timer is 1ms,
			// Sleep(3) may make a sleep of 2ms or 4ms. Therefore, we subtract 1ms here to make Sleep time shorter.
			// If 'waitMS' is equal or less than 1ms, don't sleep and run into next loop to
			// boost CPU to next frame accurately.
			waitMS = (_QuadPart - interval) * 1000LL / freq.QuadPart - 1L;
			if (waitMS > 1L)
			{
				Sleep(waitMS);
			}
		}
	}

	const int addtime = 1000 / g_FPS;
	static int s_tick = 0;
	ShowCursor(false);
	SetBkMode(g_DC, TRANSPARENT); //设置文本的混合模式
//	::Lock_CurrentProcess();
// 	//消息循环
// 	MSG Msg;
// 	ZeroMemory(&Msg, sizeof(MSG));
// 	for (;;)
// 	{
// 		if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
// 		{	
// 			if (Msg.message == WM_QUIT)
// 			{
// 				break;
// 			}
// 			TranslateMessage(&Msg);
// 			DispatchMessage(&Msg);
// 		}
// 		else
// 		{
// 			if (timeGetTime() < UpdateTimer + addtime)
// 			{
// 				Sleep(1);   //让CPU休息一下 
// 				continue;
// 			}
// 			UpdateTimer = timeGetTime();
// 			CurrentTime += addtime;
// 
// 
// 			++g_iFPS;
// 			if (++s_tick >= 60)
// 			{
// 				s_tick = 0;
// 			}
// 			switch (g_StateType)
// 			{
// 			case STATE_MAIN:
// 				g_StateTypeOld = g_StateType;
// 				MainState->Frame();
// 				if (s_tick == 0)
// 				{
// 					SetWindowText(g_hWnd, L"浪西游v20180317");
// 				}
// 				break;
// 			case STATE_FIGHT:
// 				if (g_StateTypeOld != STATE_FIGHT)
// 				{
// 					g_pMainState->m_Mp3.Load("战斗BOSS");
// 				}
// 				g_StateTypeOld = g_StateType;
// 				FightState.Frame();
// 				if (s_tick == 0)
// 				{
// 					SetWindowText(g_hWnd, L"浪西游v20180317");
// 				}
// 				break;
// 			case STATE_FIGHT_MUSIC:
// 				g_StateTypeOld = g_StateType = STATE_FIGHT;
// 				FightState.Frame();
// 				break;
// 			case STATE_MENU:
// 				g_StateTypeOld = g_StateType;
// 				MenuState.Frame();
// 				break;
// 			case STATE_GAMEOVER:
// 				EndState.Frame();
// 				break;
// 			default:
// 				PostQuitMessage(1);
// 				break;
// 			}
// 		}
// 	}
	ShowCursor(true);


	
	SelectObject(g_DC2, oldpen);
	DeleteObject(g_WhitePen);
	DeleteObject(g_BWhitePen);
	SetTextColor(g_DC2, oldcolor);
	MainState->Free();
	FightState.Free();
	free(g_pBmpinfo);
	SelectObject(g_DC, oldmap);
	DeleteObject(g_MemBitmap);
	m_File.CloseWDF();
	m_File.Free();
	DeleteDC(g_DC);
	//DeleteDC(g_DC2);
	//DeleteCriticalSection(&g_cs);
	//CloseHandle(g_hMutex);
	SAFE_DELETE(MainState);
	UnregisterClass(g_wcex.lpszClassName, hInstance);
	PostQuitMessage(1);
	return 0;
}


LRESULT CALLBACK  WindowProc(HWND hWnd, uint uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		g_pMainState->m_InterfaceSystem2.OnOff(!g_pMainState->m_InterfaceSystem.m_NeedShow);
		return 1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void Resize(long Width, long Height)
{
	RECT WndRect, ClientRect;
	long WndWidth, WndHeight;

	GetWindowRect(g_hWnd, &WndRect);
	GetClientRect(g_hWnd, &ClientRect);

	WndWidth = (WndRect.right - (ClientRect.right - Width)) - WndRect.left;
	WndHeight = (WndRect.bottom - (ClientRect.bottom - Height)) - WndRect.top;

	MoveWindow(g_hWnd, WndRect.left, WndRect.top, WndWidth, WndHeight, true);


}


#if 0
#include <functional>
#include <sstream>
//#include "../basic/Qstring.h"
//#include "Qassert.h"


bool __enumFiles(std::string fullDir, std::string partDir, const std::function<bool(const std::string&)> &cb, std::stringstream& ss, bool &isNeedCallback, bool &isOnlyName)
{
	WIN32_FIND_DATAA data;
	std::string path = fullDir + "*";
	//这样处理后可以partDir + cFileName
	if (partDir.size() == 1 && partDir.back() == '/')
		partDir.clear();
	else if (partDir.size() > 1 && partDir.back() != '/')
		partDir += '/';

	HANDLE handle = FindFirstFileA(path.c_str(), &data);
	asert(handle != INVALID_HANDLE_VALUE, "枚举目录失败");

	do
	{
		//本目录或者上级目录
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && data.cFileName[0] == '.')
			continue;

		//目录
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string new_fullDir = fullDir + data.cFileName + "/";
			std::string new_partDir = partDir + data.cFileName + "/";
			if (__enumFiles(new_fullDir, new_partDir, cb, ss, isNeedCallback, isOnlyName))
			{
				FindClose(handle);
				return true;
			}
			continue;
		}

		if (ss.tellp())
			ss << "\n";
		ss << partDir + data.cFileName;

		//文件
		if (isNeedCallback)
		{
			if (isOnlyName)
			{
				if (cb(data.cFileName))
				{
					isNeedCallback = false;
				}
			}
			else
			{
				if (cb(partDir + data.cFileName))
				{
					isNeedCallback = false;
				}
			}
		}
	} while (FindNextFileA(handle, &data));

	FindClose(handle);

	return false;
}


std::string replace(std::string str, std::string to_replace, std::string replace)
{
	std::string::size_type pos = 0;
	std::string::size_type srcLen = to_replace.size();
	std::string::size_type desLen = replace.size();
	pos = str.find(to_replace, pos);
	while ((pos != std::string::npos))
	{
		str.replace(pos, srcLen, replace);
		pos = str.find(to_replace, (pos + desLen));
	}
	return str;
}

std::vector<std::string> getFileNames(const std::string& path, bool isOnlyName)
{
	std::vector<std::string> fileNames;

	std::string fullDir = path;
	fullDir = replace(fullDir, "\\", "/");
	asert(fullDir.size(), "枚举目录失败");
	//这样处理后可以partDir + cFileName
	if (fullDir.back() != '/')
		fullDir += '/';

	std::string partDir = "";
	std::stringstream ss;
	bool isNeedCallback = true;
//	bool isOnlyName = true;
	auto func = [&fileNames](const std::string &filename)
	{
		fileNames.push_back(filename);
		return false;
	};
	__enumFiles(fullDir, partDir, func, ss, isNeedCallback, isOnlyName);
	return fileNames;
}



bool Lock_CurrentProcess()
{
	HANDLE hProcess = ::GetCurrentProcess();
	SID_IDENTIFIER_AUTHORITY sia = SECURITY_WORLD_SID_AUTHORITY;
	PSID pSid/* = new PSID*/;
	bool bSus = false;
	//	bSus = ::InitializeSid(pSid, &sia, NULL);
	bSus = ::AllocateAndInitializeSid(&sia, 1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &pSid);
	if (!bSus) goto Cleanup;
	HANDLE hToken;
	//	bSus = ::OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);
	bSus = ::OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken);
	if (!bSus) goto Cleanup;
	ulong dwReturnLength;
	bSus = ::AdjustTokenPrivileges(hProcess, true, NULL, 1024, NULL, &dwReturnLength);
	if (!bSus) goto Cleanup;
	::GetTokenInformation(hToken, TokenUser, NULL, NULL, &dwReturnLength);
	if (dwReturnLength > 0x400) goto Cleanup;
	LPVOID TokenInformation;
	TokenInformation = ::LocalAlloc(LPTR, 0x400);//这里就引用SDK的函数不引用CRT的了
	ulong dw;
	bSus = ::GetTokenInformation(hToken, TokenUser, TokenInformation, 0x400, &dw);
	if (!bSus) goto Cleanup;
	PTOKEN_USER pTokenUser = (PTOKEN_USER)TokenInformation;
	uchar Buf[0x200];
	PACL pAcl = (PACL)&Buf;
	bSus = ::InitializeAcl(pAcl, 1024, ACL_REVISION);
	if (!bSus) goto Cleanup;
	// 	bSus = ::AddAccessDeniedAce(pAcl, ACL_REVISION, 0x000000FA, pSid);
	// 	if (!bSus) goto Cleanup;
	// 	bSus = ::AddAccessAllowedAce(pAcl, ACL_REVISION, 0x00100701, pTokenUser->User.Sid);
	// 	if (!bSus) goto Cleanup;
	if (::SetSecurityInfo(hProcess, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION, NULL, NULL, pAcl, NULL) == 0)
		bSus = true;
Cleanup:
	if (hProcess != NULL)
		::CloseHandle(hProcess);
	if (pSid != NULL)
		::FreeSid(pSid);
	return bSus;
}



string get说明()
{
	string strDesc = "2017.2.21\n";
	strDesc += "游戏素材归官方梦幻西游所有\n";
	strDesc += "勿用于商业行为,否则后果自负\n";
	strDesc += "保留原版剧情,感谢子犯的(梦幻群侠传5)\n";
	strDesc += "欢迎 +梦幻群侠传5官方群 361715087\n";
	strDesc += "游戏免费,若发现贩卖行为,呃...\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "1.游戏特色:\n";
	strDesc += "部分迭代(地图/角色/NPC)\n";
	strDesc += "新增召唤兽技能 须弥真言 从天而降 月光\n";
	strDesc += "新增普通攻击追加法术\n";
	strDesc += "支持调整游戏字号大小\n";
	strDesc += "支持调整走路速度\n";
	strDesc += "支持瞬移(慎用,有可能暴毙)\n";
	strDesc += "支持显示/隐藏敌方血条\n";
	strDesc += "支持血条右键免药回血回蓝\n";
	strDesc += "支持队友的(输出模式/智能模式)\n";
	strDesc += "支持控制队长/控制全部队友\n";
	strDesc += "支持自动战斗\n";
	strDesc += "支持指挥队友急火\n";
	strDesc += "支持调整出生开始剧情进度\n";
	strDesc += "支持转换门派\n";
	strDesc += "支持转换造型\n";
	strDesc += "支持游戏初始入帮派\n";
	strDesc += "支持加减属性点\n";
	strDesc += "支持快速加点\n";
	strDesc += "支持变身卡进阶效果\n";
	strDesc += "支持召唤兽进阶选择\n";
	strDesc += "支持队友自由邀请/离队(邀请队友和宝宝的资质/加点/技能...会被重置)\n";
	strDesc += "支持游戏中调整队友的名字/特技/加点方案\n";
	strDesc += "支持擂台和帮战队伍的自定义设计(门派加点/人数/门派/阵型)\n";
	strDesc += "支持拓展新wdf/新召唤兽\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "2.门派技能调整:\n";
	strDesc += "方寸 失心符/定身符/碎甲符 降防降灵效果\n";
	strDesc += "方寸 分身术 法术躲避效果\n";
	strDesc += "方寸 落雷符 驱鬼效果\n";
	strDesc += "化生 部分技能合并,提升回血效果\n";
	strDesc += "化生 解毒附加回血效果\n";
	strDesc += "化生 佛法无边 法术连击率\n";
	strDesc += "女儿 雨落寒沙 暗器技巧影响效果\n";
	strDesc += "普陀 后期双灯\n";
	strDesc += "普陀 自在心法 结算效果\n";
	strDesc += "普陀 灵动九天 技能效果\n";
	strDesc += "普陀 颠倒五行 法术吸收率 法术躲避率\n";
	strDesc += "地府 幽冥鬼眼 感知效果 抗封效果\n";
	strDesc += "地府 尸腐毒 回血效果\n";
	strDesc += "地府 修罗隐身 技能效果\n";
	strDesc += "地府 还阳术 加攻效果\n";
	strDesc += "地府 黄泉之息 降速效果\n";
	strDesc += "地府 魂飞魄散 去除良性buff效果\n";
	strDesc += "地府 锢魂术 命中几率\n";
	strDesc += "魔王 牛劲 感知效果\n";
	strDesc += "盘丝 勾魂 摄魄 命中 技能效果\n";
	strDesc += "盘丝 幻境术 法术反弹效果\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "3.召唤兽技能调整:\n";
	strDesc += "隐身 有彩蛋\n";
	strDesc += "鬼魂术 兼容神佑 抗封 会飞出场\n";
	strDesc += "四吸收 官方\n";
	strDesc += "嗜血追击 官方\n";
	strDesc += "盾气 官方\n";
	strDesc += "风华武圣 效果调整\n";
	strDesc += "力劈华山 官方\n";
	strDesc += "剑荡四方 官方\n";
	strDesc += "善恶有报 官方\n";
	strDesc += "壁垒击破 官方\n";
	strDesc += "苍穹怒击 效果调整\n";
	strDesc += "空间真 效果调整\n";
	strDesc += "大蛇光线 效果调整\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "4.特技调整:\n";
	strDesc += "晶清诀 回血效果 移除效果\n";
	strDesc += "慈航普渡 技能效果\n";
	strDesc += "罗汉金钟 技能效果\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "5.道具调整:\n";
	strDesc += "元宵效果\n";
	strDesc += "暗器 非女儿门派使用暗器单秒\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "6.商店调整\n";
	strDesc += "高级兽决商店补全\n";
	strDesc += "召唤兽商店补全\n";
	strDesc += "法宝商店 +境外旗子+时只环\n";
	strDesc += "仙店灵铺 +特色令牌-开挂药品\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "7.副本调整:\n";
	strDesc += "+门派闯关\n";
	strDesc += "适当化简,比如答题/战斗1次过\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "8.其他调整\n";
	strDesc += "阵型全开不用吃鬼谷子\n";
	strDesc += "超级泡泡无限攻击的修复\n";
	strDesc += "哮天犬合并进阶哮天犬\n";
	strDesc += "帮派修炼会同时学习宝宝修,修炼果无冲突\n";
	strDesc += "更多彩蛋,请在游戏中体验...\n";
	strDesc += "\n";
	strDesc += "\n";
	strDesc += "9.注意事项\n";
	strDesc += "地图/NPC/商店/大部分一致,先熟悉原版攻略\n";
	strDesc += "操作方法请参考说明图\n";
	strDesc += "多存档以防暴毙...";

	return strDesc;


	ofstream fileOut;
	fileOut.open("说明书.txt");
	fileOut.write(strDesc.c_str(), strDesc.size());
	fileOut.close();


	strDesc = "2017.2.25\n";
	strDesc += "修复鼠标经过包裹藏宝图报错的问题\n";
	strDesc += "修复29~39级改名字存档错误问题\n";
	fileOut.open("更新.txt");
	fileOut.write(strDesc.c_str(), strDesc.size());
	fileOut.close();
}



int main2()
{
	ifstream File;
	cWasFile m_File;
	ifstream *fileWdf = nullptr;
	ofstream fileOut;
	string strTemp;
	if (0)
	{
		for (const auto &name : getFileNames(gpathExpand))
		{
			File.open(gpathExpand + name);
			if (!File)
			{
				File.close();
				continue;
			}
			File.close();
			m_File.Open(string(gpathExpand + name).c_str());
		}
	}

	if (cct::get()->isClassical)
	{
		string path = g_pathWdf + "jd/";
		for (const auto &name : getFileNames(path))
		{
			File.open(path + name);
			if (!File)
			{
				File.close();
				continue;
			}
			File.close();
			m_File.Open(string(path + name).c_str());
		}
	}


	if (0)
	{
		set<string> pack0;
		for (auto name : getFileNames("C:/Users/wolf/Desktop/wdfpack/坐骑/"))
		{
			name = name.substr(5, name.length() - 5);
			pack0.insert(name);
		}
		for (const auto &name : getFileNames("C:/Users/wolf/Desktop/wdfpack0/坐骑/"))
		{
			if (pack0.find(name.substr(5, name.length() - 5)) == pack0.end())
			{
				asert(false, "多余%s", name.c_str());
			}
		}
	}




	if (1)
	{
		for (const auto &name : getFileNames(g_pathWdf/*, false*/))
		{
			File.open(g_pathWdf + name);
			if (!File)
			{
				File.close();
				continue;
			}
			File.close();
			m_File.Open(string(g_pathWdf + name).c_str());
		}
	}

	if (0)
	{
		for (auto name : getFileNames(g_pathNewBaby))
		{
			name.pop_back();
			name.pop_back();
			name.pop_back();
			name.pop_back();
			int i = atoi(name.c_str());
			if (i >= 0 && i <= 162)
			{
				cct::get()->newBabys.insert(i);
			}
		}
	}


	if (cct::get()->juQing == 10087)
	{
		ifstream file(gpathExpand + "全部wdf.txt");
		if (!file)
		{
			asert(bool(File), "找不到(全部wdf.txt)");
			return 0;
		}
		int num;
		file >> num;
		getline(file, strTemp);
		unsigned long uid;

		for (int i = 0; i < num; ++i)
		{
			file >> uid;
			bool isFound = false;
			for (int k = 0; k < m_File.s_wdfNum; k++)
			{
				if (m_File.m_pWdf[k] == 0)
					continue;
				if (m_File.m_pWdf[k]->SearchFile(uid))
				{
					isFound = true;
					break;
				}
			}
			if (!isFound)
			{
				cct::get()->pushWdf2(strTemp, uid);
			}
			getline(file, strTemp);
		}
		cct::get()->saveWdf();
	}

	if (cct::get()->juQing == 10088)
	{

		ifstream file(gpathExpand + "差异wdf.txt");
		if (!file)
		{
			asert(bool(File), "找不到(差异wdf.txt)");
			return 0;
		}
		int num;
		file >> num;
		getline(file, strTemp);
		vector<unsigned long> uids;
		uids.resize(num);
		for (unsigned long i = 0; i < num; ++i)
		{
			file >> uids[i];
		}
		file.close();

		for (unsigned long i = 0; i < num; ++i)
		{
			bool b = m_File.GetFileP(uids[i], fileWdf, [&](const uchar *data)
			{
				int size = 18;
				fileOut.open(gpathExpand + toString("差异%lu", uids[i]), ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入差异文件失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入差异文件失败");
		}
	}


	if (0)
	{
		fileOut.close();
		vector<unsigned long > ids =
		{ 481695805, 1324670936, 916542457, 2880121122, 916542457,
		3707768443, 2121775169, 2233389510,
		623405626, 1499046182, 247762293, 4279487352, 1953154114, 1953154114, 1735308365, 1546483919, 575768071, 3952815488, 963848079 };
		ids = { 395811073 };
		forv(ids, i)
		{
			bool b = m_File.GetFileP(ids[i], fileWdf, [&](const uchar *data)
			{
				int size = 18;
				fileOut.open(gpathExpand + toString("%04d-%x-0.was", i, ids[i]), ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入差异文件失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
		}

	}

	if (cct::get()->juQing == 10089)
	{
		ifstream file(gpathExpand + "差异wdf.txt");
		if (!file)
		{
			asert(bool(File), "找不到(差异wdf.txt)");
			return 0;
		}
		int num;
		file >> num;
		getline(file, strTemp);
		vector<unsigned long> uids;
		uids.resize(num);
		for (unsigned long i = 0; i < num; ++i)
		{
			file >> uids[i];
		}
		file.close();

		unsigned long mySize = (1 << 21);
		unsigned long  uSize = (1 << 21);
		char *myData = new char[mySize];
		char *uData = new char[uSize];

		unsigned long uNew = 0;
		const WDataFileIndex *pf = nullptr;

		vector<WDataFileIndex> tables;
		int noneNum = -1;
		for (unsigned long i = 0; i < num; ++i)
		{
			const unsigned long &u = uids[i];
			file.open(gpathExpand + toString("差异%lu", u), ios::binary);
			file.seekg(0, ios_base::end);

			mySize = (int)file.tellg();
			file.seekg(0, ios_base::beg);
			file.read(myData, mySize);
			file.close();

			uNew = 0;
			for (unsigned long iWdf = 0; iWdf < m_File.s_wdfNum; ++iWdf)
			{
				if (m_File.m_pWdf[iWdf] == 0)continue;
				for (unsigned long idx = 0; idx < m_File.m_pWdf[iWdf]->m_Number; ++idx)
				{
					pf = &m_File.m_pWdf[iWdf]->m_pIndex[idx];
					if (pf->size != mySize)
					{
						continue;
					}

					fileWdf = m_File.m_pWdf[iWdf]->GetFileHandle();
					fileWdf->seekg(pf->offset, ios_base::beg);
					fileWdf->read(uData, pf->size);

					bool isSame = true;
					for (unsigned long x = 100; x < mySize; ++x)
					{
						if (*(myData + x) != *(uData + x))
						{
							isSame = false;
							break;
						}
					}
					if (isSame)
					{
						uNew = pf->uid;
						break;
					}
				}
				if (uNew)
				{
					if (uNew != u)
					{
						tables.push_back({ u, uNew, 0, 0 });
					}
					break;
				}
			}
			if (!uNew)
			{
				fileOut.open(gpathExpand + toString("%04d-%x-0.was", ++noneNum, u), ios_base::binary);
				fileOut.write(myData, mySize);
				fileOut.close();
			}
		}

		delete[] myData;
		delete[] uData;

		fileOut.open(gpathExpand + "对应wdf.txt");
		if (!fileOut)
		{
			asert(false, "写入(对应wdf.txt)失败");
			return 0;
		}
		fileOut << tables.size() << "\n";
		for (int i = 0; i < tables.size(); ++i)
		{
			fileOut << tables[i].uid << "	" << tables[i].offset << "\n";
		}
		fileOut.close();
		Q::msgbox2("", "写入(对应wdf.txt)完毕");
	}


	if (cct::get()->juQing == 10090)
	{
		std::map<unsigned long, int> maps;
		for (unsigned long iWdf = 0; iWdf < m_File.s_wdfNum; ++iWdf)
		{
			if (m_File.m_pWdf[iWdf] == 0)continue;
			for (unsigned long idx = 0; idx < m_File.m_pWdf[iWdf]->m_Number; ++idx)
			{
				const unsigned long &uid = m_File.m_pWdf[iWdf]->m_pIndex[idx].uid;
				const auto it = maps.find(uid);
				if (it == maps.end())
				{
					maps.insert(make_pair(uid, 0));
				}
				else
				{
					++it->second;
				}
			}
		}
		std::map<unsigned long, int> map2s;
		for (const auto &u : maps)
		{
			if (u.second > 0)
			{
				map2s.insert(u);
			}
		}

		fileOut.open(gpathExpand + "重复wdf.txt");
		if (!fileOut)
		{
			asert(false, "写入(重复wdf.txt)失败");
			return 0;
		}
		fileOut << map2s.size() << "\n";
		for (const auto &u : map2s)
		{
			fileOut << u.first << "	" << u.second << "\n";
		}
		fileOut.close();
		Q::msgbox2("", "写入(重复wdf.txt)完毕");
	}

	if (0)
	{
		ifstream file(gpathExpand + "对应wdf.txt");
		if (!file)
		{
			asert(bool(File), "找不到(对应wdf.txt)");
			return 0;
		}
		int num;
		unsigned long id, idNew;
		file >> num;
		getline(file, strTemp);
		for (unsigned long i = 0; i < num; ++i)
		{
			file >> id >> idNew;
			cct::get()->pushTable(id, idNew);
			getline(file, strTemp);
		}
		file.close();
		file.open(gpathExpand + "忽略wdf.txt");
		if (!file)
		{
			asert(bool(File), "找不到(忽略wdf.txt)");
			return 0;
		}
		file >> num;
		getline(file, strTemp);
		for (unsigned long i = 0; i < num; ++i)
		{
			file >> id;
			cct::get()->pushIgnore(id);
			getline(file, strTemp);
		}
		file.close();
	}

	if (0)
	{
		for (auto name : getFileNames(g_pathSceneTxt))
		{
			name.pop_back();
			name.pop_back();
			name.pop_back();
			name.pop_back();
			cct::get()->mapNames.insert(name);
		}
	}
	if (0)
	{
		ifstream file("C:/Users/wolf/Desktop/mapIDs.txt");
		if (!file)
		{
			asert(bool(File), "找不到(mapIDs.txt)");
			return 0;
		}
		int num;
		vector<int> ids;
		file >> num;
		getline(file, strTemp);
		ids.resize(num);
		for (unsigned long i = 0; i < num; ++i)
		{
			file >> ids[i];
			getline(file, strTemp);
		}
		file.close();
		for (const auto &id : ids)
		{
			system(toString("copy D:\\xyq2\\scene\\%d.map C:\\Users\\wolf\\Desktop\\scenecopy\\%d.map", id, id).c_str());
		}
	}



	if (0)
	{
		vector<string> wdfpath;
		wdfpath.resize(33);
		for (int i = 0; i < 33; i++)
		{
			wdfpath[i] = g_pathWdf;
		}
		wdfpath[0] += "shape.wda";
		wdfpath[1] += "shape.wdb";
		wdfpath[2] += "shape.wdc";
		wdfpath[3] += "shape.wdf";
		wdfpath[4] += "shape1.wdf";
		wdfpath[5] += "shape.wd1";
		wdfpath[6] += "shape.wd2";
		wdfpath[7] += "shape.wd3";
		wdfpath[8] += "shape.wd4";
		wdfpath[9] += "shape.wd5";
		wdfpath[10] += "shape.wd6";
		wdfpath[11] += "shape.wd7";
		wdfpath[12] += "shape.wd8";
		wdfpath[13] += "shape.wd9";
		wdfpath[14] += "shape.wd11";
		wdfpath[15] += "wzife.wd1";
		wdfpath[16] += "wzife.wd2";
		wdfpath[17] += "wzife.wd3";
		wdfpath[18] += "wzife.wd4";
		wdfpath[19] += "wzife.wdf";
		wdfpath[20] += "smap.wdf";
		wdfpath[21] += "item.wdf";
		wdfpath[22] += "item.wd1";
		wdfpath[23] += "item.wd2";
		wdfpath[24] += "addon.wdf";
		wdfpath[25] += "magic.wdf";
		wdfpath[26] += "magic.wd1";
		wdfpath[27] += "magic.wd2";
		wdfpath[28] += "waddon.wdf";  //状态
		wdfpath[29] += "sound.wdf";
		wdfpath[30] += "sound1.wdf";
		wdfpath[31] += "mapani.wdf";
		wdfpath[32] += "atom.wdf";
		for (int i = 0; i < 33; i++)
			m_File.Open(wdfpath[i].c_str());

		m_File.Open(string(g_pathOther + "_1.wdf").c_str());

	}

	return 0;
}



void main3()
{


	////产生字体
	if (0)
	{
		string path;
		wstring path2;
		auto func = [&]()
		{
			StringToWString(path, path2);
			//			path2 = path;
		};
		path = g_pathData;
		path += "font\\hyh1gjm.ttf";
		func();
		AddFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\hyb1gjm.ttf";
		func();
		AddFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\hyj4gjm.ttf";
		func();
		AddFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\hksnt.ttf";
		func();
		AddFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\方正胖头鱼简体.ttf";
		func();
		AddFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
	}


	if (0)
	{
		string path;
		wstring path2;
		path = g_pathData;
		path += "font\\hyh1gjm.ttf";
		auto func = [&]()
		{
			StringToWString(path, path2);
			//			path2 = path;
		};
		func();
		RemoveFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\hyb1gjm.ttf";
		func();
		RemoveFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\hyj4gjm.ttf";
		func();
		RemoveFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\hksnt.ttf";
		func();
		RemoveFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
		path = g_pathData;
		path += "font\\方正胖头鱼简体.ttf";
		func();
		RemoveFontResourceEx(path2.c_str(), FR_PRIVATE, 0);
	}

}

#endif