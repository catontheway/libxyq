#ifndef _WINDSOUL_EDGE_CHAR_H_
#define _WINDSOUL_EDGE_CHAR_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"

struct WEdgeCharStruct;

class WINDSOULADD_API WEdgeChar : public WObject {
public:
	WEdgeChar() {} 
	WEdgeChar(int size,unsigned int c,WPixel color,WPixel edge) { Create(size,c,color,edge); }
	~WEdgeChar() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WEdgeCharStruct *GetEdgeCharStruct() const { return reinterpret_cast<WEdgeCharStruct *>(objdata); }	// 获取数据结构
	WSERR Create(int size,unsigned int c,WPixel color,WPixel edge);	// 创建字符
	void Destroy();										// 销毁
	int GetW() const;									// 取宽度
	int GetH() const;									// 取高度
	int GetWidth() const;								// 取字宽
	BLIT_FUNC DrawFunc(DWORD style) const;				// 获得 Draw 函数指针
};

#endif