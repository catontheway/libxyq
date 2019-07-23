#pragma once
#include "global.h"

class cMyMap;
struct Coordinate
{
	int sx;
	int sy;
	Coordinate()
	{
		sx = 0;
		sy = 0;
	}
	Coordinate(int x, int y)
	{
		sx = x;
		sy = y;
	}
};

class cFindPath
{
public:
	~cFindPath();
	BOOL InitMap();
	BOOL FindPath(cObj* pObj, int Xend, int Yend);

	void  ResetMap(sMap* pMap);
	void  Free();

public:
	sMap *_pMap = nullptr;
};

