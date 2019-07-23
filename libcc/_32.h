#pragma once

#include "../lib32/_32.h"
#if defined(_DEBUG)
#pragma comment(lib,"libwindsoul_mdd.lib")
#pragma comment(lib,"lib32_mdd.lib")
#else
#pragma comment(lib,"libwindsoul_mt.lib")
#pragma comment(lib,"lib32_mt.lib")
#endif