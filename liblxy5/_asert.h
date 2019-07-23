#pragma once
#include "../libcc/_qcode.h"
#include "../libcc/_cpp.h"
#include "../lib32/_window.h"
#include <fstream>
#include <sstream>
#include <list>

////////////////////////////////////////////////////////////////////////// 你的
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma warning(disable:4996) 
#pragma warning(disable:4995) 
#pragma warning(disable:4018) 

#define SAFE_DELETE(p) if (p) {delete p; p = NULL;}  
#define SAFE_DELETE_ARRAY(p) if (p) {delete[] p; p = NULL;}  
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#define ERRBOX {MessageBoxA(NULL,__FUNCTION__, "ERR",MB_OK);}
#define ERRBOX2(num) {char data[20]; itoa(num,data,20); MessageBoxA(NULL,__FUNCTION__, data,MB_OK);}


////////////////////////////////////////////////////////////////////////// 我的
using namespace std;
typedef istringstream sIstream;
typedef ostringstream sOstream;
static const string g_strSpace = " ";
static const string g_strEnter = "\n";
static const string g_strNeedBattle = "\n(需战斗)";