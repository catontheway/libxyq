#pragma once
#include "_inc.h"

#include <dsound.h>
#include <list>

#include <stdio.h>
#include <fstream>
#include <sstream>
#include "Input5.h"
#include "MyMath.h"

#if ccc_date
#include "MyTest.h"
#endif
#include "ChangeColor.h"
#include "mysound.h"
#include "MyScript.h"
#include "A_Start.h"
#include "Object5.h"
#include "PetData.h"
#include "item.h"
#include "Skill.h"

#include "Interface.h"
#include "Interface2.h"
#include "Script.h"
#include "Map.h"
#include "AI.h"
#include "trigger.h"
#include "Canvas5.h"
#include "trigger2.h"
#include "State.h"

extern LPDIRECTSOUND8	 g_pDirectSound;

extern string g_strMediaPath;
//位图头
extern BITMAPINFO * g_pBmpinfo;
//内存DC
extern HDC g_ShowDC, g_DC, g_DC2;
extern HBITMAP g_MemBitmap; // g_MemBitmap2;
extern HBRUSH  g_redbrush, g_blackbrush, g_whitebrush, g_bluebrush;
extern HPEN  g_WhitePen, g_BWhitePen;
extern BOOL g_bFillScreen;
extern int g_xMouse, g_yMouse, g_640, g_480, g_320, g_240, g_360; // nScreenWidth, nScreenHeight
extern void SetFullScreen(BOOL bFill);
extern void firstMainState();
extern void spaceTest();
//路径
extern  string g_ScriptPath, g_ScenePath, g_Config;
extern HWND  g_hWnd;
extern HINSTANCE g_hInst;

#pragma comment(lib,"dsound.lib")
#pragma warning(disable:4995) 
#pragma warning(disable:4996) 
#pragma warning(disable:4018) 


#define SAFE_DELETE(p) if (p) {delete p; p = NULL;}  
#define SAFE_DELETE_ARRAY(p) if (p) {delete[] p; p = NULL;}  
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#define ERRBOX {MessageBoxA(NULL,__FUNCTION__, "ERR",MB_OK);}// assert(0);
#define ERRBOX2(num) {char data[20]; itoa(num,data,10); MessageBoxA(NULL,__FUNCTION__, data,MB_OK);}
//8个方向
#define DIRECTION_UP		 8
#define DIRECTION_DOWN		 2
#define DIRECTION_RIGHT		 6
#define DIRECTION_LEFT		 4
#define DIRECTION_LEFT_UP	 7
#define DIRECTION_RIGHT_UP	 9
#define DIRECTION_LEFT_DOWN  1
#define DIRECTION_RIGHT_DOWN 3

//#define OBJ_TYPE_PC       1
//#define OBJ_TYPE_NPC      2
//#define OBJ_TYPE_PET     3


#define POS_STAND    1
#define POS_WALK     2
#define POS_FIGHT_STAND 3
#define POS_RUN       4
#define POS_ATTACK       5
#define POS_MAGIC       6
#define POS_DEF       7
#define POS_SUFFER       8
#define POS_DEAD       9
#define POS_RETURN       10
#define POS_ATTACK2      11
#define POS_GREET      12
#define POS_DANCE      13
#define POS_BOW      14
#define POS_ANGRY      15
#define POS_CRY      16
#define POS_SIT      17
#define POS_BIGHEAD      18
#define POS_DIALOG      19
#define POS_SMALLHEAD    20

#define POS_SOUNDATTACK       21
#define POS_SOUNDMAGIC       22
#define POS_SOUNDDEF       23
#define POS_SOUNDSUFFER       24
#define POS_SOUNDDEAD       25
#define POS_SOUNDATTACK2      26



extern int g_StateType;
extern int g_FPS;
#define STATE_FIGHT 2
#define STATE_MAIN  1
#define STATE_EXT  3
#define STATE_MENU 4
#define STATE_GAMEOVER 5

#define MAX_NPC_NUM		128
#define WFourCC(str) ((DWORD)str[0]|(DWORD)str[1]<<8|(DWORD)str[2]<<16|(DWORD)str[3]<<24)

#define WAlloc(size) ((void*)new BYTE[(size)])
#define WFree(ptr) (delete []((BYTE*)(ptr)))
extern CMainState* g_pMainState;

extern cCharacter* g_pCharacter;
extern cObj* g_pHeroObj;

#if ccc_date
extern std::string g_strCommonPath, g_strExpandPath, g_strOtherPath, g_strPKPath, g_strNewBabyPath, g_strFriendPath, g_strSavePath;
extern sAddPoint g_addPointAtk, g_addPointMag, g_addPointSpd, g_addPointDef;
extern int g_fntSize;
#endif