#ifndef _WINDSOUL_ZOOM_BITMAP_H_
#define _WINDSOUL_ZOOM_BITMAP_H_

#pragma once

#include "wsaddon.h"

class WINDSOULADD_API WZoomBitmap : public WBitmap {
public:
	using WBitmap::Draw;
	void Draw(const WBitmap &bmp,int w,int h);
};

#endif