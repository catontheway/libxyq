#pragma once
#include "cMapReader.h"

class cMapRender
{
public:
	static cMapRender* getInstance();

	static void getScrew(int x0, int y0, int row, int cel, int bw, int bh, int& x1, int& y1, int& x2, int& y2);

	int forScrew(int x0, int y0, bool limit);

	void setMap(sMap* pMap);

	void reset();

	void onSize(float sw, float sh);

	bool step(const cocos2d::Vec2& vCenter, bool limit);

	void draw(cCanvas* canves, const cocos2d::Vec2& vPort);

	void drawMask(cCanvas* canves, const cocos2d::Vec2& vPort);

private:
	int _x320, _y240, _x1, _y1, _x2, _y2;

	int _row = 0, _cel = 0;

	int _bw, _bh;

	int _flag = -1, _mask = -1;

	bool _isLoaded;

	sMap* _pMap = nullptr;
	cBmp* _bitmap = nullptr;
	std::vector<sMapAlpha>* _alphas = nullptr;
	sMapAlpha* _alpha = nullptr;
};