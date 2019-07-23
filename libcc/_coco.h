#pragma once

#include "../libcoco/_coco.h"
#include "../libcoco/_create.h"
#if defined(_DEBUG)
#pragma comment(lib,"libcoco_mdd.lib")
#else
#pragma comment(lib,"libcoco_mt.lib")
#endif