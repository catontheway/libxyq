#pragma once
#include "_inc.h"
#include <dsound.h>
#include <process.h>
#include <time.h>

extern LPDIRECTSOUND8 g_pDirectSound;
//路径
//extern string g_pathData;
//extern string g_pathWdf;
//extern string g_pathCommon;
//extern string g_pathMap;
//extern string g_pathSceneTxt;
//extern string gpathExpand;
//extern string g_pathOther;
//extern string g_pathPK;
//extern string g_pathNewBaby;
//extern string g_pathFriend;
extern string g_pathSave;
//extern string g_pathMusic;

extern const int g_640;
extern const int g_480;
extern const int g_half320;
extern const int g_half240;

extern const int g_fntSize;
extern int g_xMouse;
extern int g_yMouse;

extern int g_StateType;
extern const int g_FPS;
extern int g_iFPS;

extern array<int, 128> g_GlobalValues;
extern bool g_isChangeMoney;
extern bool g_isChangeExp;

extern CMainState* g_pMainState;
extern cCharacter* g_pCharacter;
extern cObj* g_pHeroObj;



//临界区
//extern  CRITICAL_SECTION g_cs;
//extern HANDLE g_hMutex;
//位图头
extern BITMAPINFO * g_pBmpinfo;
//内存DC
extern HDC g_ShowDC;
extern HDC g_DC;
extern HDC g_DC2;
extern HBITMAP g_MemBitmap;
//extern HBITMAP g_MemBitmap2;
extern HBRUSH  g_redbrush;
extern HBRUSH  g_blackbrush;
extern HBRUSH  g_whitebrush;
extern HBRUSH  g_bluebrush;
extern HPEN  g_WhitePen;
extern HPEN  g_BWhitePen;
extern bool g_bFillScreen;
extern int nScreenWidth;
extern int nScreenHeight;
extern void SetFullScreen2(bool bFill);

//窗口句柄
extern WNDCLASSEX g_wcex;
extern HWND  g_hWnd;
extern HINSTANCE g_hInst;
//脚本
extern cScript* g_pScriptParent;
extern cScript* g_pFirst;







