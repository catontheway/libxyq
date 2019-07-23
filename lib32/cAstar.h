#pragma once
#include "cLink2.h"

// 参照李光版本
class cAstar
{
public:
	struct sXY { int x, y; };
	struct sNode
	{
		ccastar::uchar state;
		ccastar::ulong distance;
		ccastar::ulong distanceBegin;
		ccastar::ulong distanceEnd;
		sXY next;
	};
	struct sMap
	{
		ccastar::uchar* datas;
		sNode*	nodes;
		ccastar::ulong width;
		ccastar::ulong height;
		ccastar::ulong wh;
	};

	cAstar();
	~cAstar();
	bool load(ccastar::ulong w, ccastar::ulong h, ccastar::uchar* _datas);
	bool search(const sXY& vStart, const sXY& vEnd);
	bool next(sXY& v);

private:
	bool isOut(const sXY& v);
	sMap* _map;
public:
	static const ccastar::uchar cUnknown = 0;
	static const ccastar::uchar cWaitChecking = 1;
	static const ccastar::uchar cClose = 2;
	static const ccastar::uchar cObstacle = 1;
};
