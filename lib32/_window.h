#pragma once
#include <windows.h>
#include "_inc.h"


////////////////////////////////////////////////////////////////////////// 弹框
#define ccc_msgbox(...) MessageBoxA(nullptr, toString(__VA_ARGS__).c_str(), __FUNCTION__, MB_OK);
#define ccc_box(_one_) MessageBoxA(nullptr, cc::toString(_one_).c_str(), __FUNCTION__, MB_OK);


////////////////////////////////////////////////////////////////////////// CRTDBG
inline void ccc_crtdbg(const char *file, int line)
{
#if defined(_DEBUG)
#include <crtdbg.h>
	_CrtDbgReport(_CRT_WARN, file, line, nullptr, "");
#endif
}

////////////////////////////////////////////////////////////////////////// 定位输出
#define ccc_log(...)\
do{\
ccc_crtdbg(__FILE__, __LINE__);\
std::string _str_ =  "★★点击定位★★    ";\
_str_ += toString(__VA_ARGS__) + "\n";\
OutputDebugStringA(_str_.c_str());\
}while(0)



////////////////////////////////////////////////////////////////////////// asert
#define asert(_cond_, ...)\
if(!(_cond_))\
{\
	ccc_msgbox(__VA_ARGS__);\
	DebugBreak();\
}