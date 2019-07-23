#include "cAstar.h"
#include <windows.h>
#include <stdlib.h>


#define ccc_astar_malloc(_N_)VirtualAlloc(NULL,_N_,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE)
#define ccc_astar_free(_PTR_)VirtualFree(_PTR_,0,MEM_RELEASE)
#define ccc_astar_clear(_PTR_, _N_) SecureZeroMemory(_PTR_,_N_)

cAstar::cAstar()
{
	_map = nullptr;
}


cAstar::~cAstar()
{
	if (_map != nullptr)
	{
		if (_map->nodes != nullptr)
		{
			ccc_astar_free(_map->nodes);
		}
		ccc_astar_free(_map);
	}
}


bool cAstar::load(ccastar::ulong w, ccastar::ulong h, ccastar::uchar* _datas)
{
	if (_map == nullptr)
	{
		_map = (cAstar::sMap*)ccc_astar_malloc(sizeof(cAstar::sMap));
		if (!_map)
		{
			ccc_astar_free(_map);
			return false;
		}
		_map->nodes = nullptr;
	}
	_map->width = w;
	_map->height = h;
	_map->datas = _datas;
	_map->wh = w * h;
	
	if (_map->nodes != nullptr)
	{
		ccc_astar_free(_map->nodes);
	}
	_map->nodes = (cAstar::sNode*)ccc_astar_malloc(w * h * sizeof(cAstar::sNode));
	if (!_map->nodes)
	{
		ccc_astar_free(_map->nodes);
		_map->nodes = nullptr;
		return false;
	}
	return true;
}


static ccastar::ulong getDistance(const cAstar::sXY& v1, const cAstar::sXY& v2)
{
	ccastar::ulong  x, y;
	x = (v1.x > v2.x) ? v1.x - v2.x : v2.x - v1.x;
	y = (v1.y > v2.y) ? v1.y - v2.y : v2.y - v1.y;
	return (x + y) * 10;
}


bool cAstar::search(const sXY& vStart, const sXY& vEnd)
{
	if (isOut(vStart) || isOut(vEnd))
	{
		return false;
	}
	/* 终点开始查找 */

	ccastar::uchar* datas = _map->datas;
	ccastar::ulong width = _map->width;
	ccastar::ulong height = _map->height;
	ccastar::ulong wh = _map->wh;
	cLink2 link2(wh);

	cAstar::sNode* nodes = _map->nodes;
	ccc_astar_clear(nodes, wh * sizeof(cAstar::sNode));

	bool isFound = false;
	ccastar::ulong curIdx = width * vStart.y + vStart.x;
	ccastar::ulong nearIdx, g, distance;

	nodes[curIdx].state = cAstar::cWaitChecking;
	nodes[curIdx].distanceEnd = getDistance(vStart,vEnd);
	nodes[curIdx].distance = nodes[curIdx].distanceEnd;
	
	link2.insert((ccastar::voidp)curIdx,nodes[curIdx].distance);
	
	while (link2.getNodesCount() != 0 && isFound == false)
	{
		/* 在待检链表中取出 F(总距离) 最小的节点, 并将其选为当前点 */
		link2.setTail();
		curIdx = (ccastar::ulong)link2.getValue();
		link2.remove();
		sNode& nodeCur = nodes[curIdx];
		nodeCur/*node[curIdx]*/.state = cAstar::cClose;

		static sXY vCur;
		vCur.x = curIdx % width; //地图宽度,
		vCur.y = curIdx / width; //地图宽度

		static int s_xs[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
		static int s_ys[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
		/* 遍历当前坐标的八个相邻坐标 */
		for (int i = 0; i < 8; ++i)
		{
			static sXY vNear;
			vNear.x = vCur.x + s_xs[i];
			vNear.y = vCur.y + s_ys[i];

			if (isOut(vNear))
			{
				continue;
			}

			nearIdx = width * vNear.y + vNear.x;
			if (nearIdx + 1 >= wh || nearIdx + width >= wh || nearIdx - 1 < 0 || nearIdx - width < 0 || datas[nearIdx] == cAstar::cObstacle)
			{
				continue;
			}
			
			switch (i)
			{
			case 1:
				if (datas[nearIdx + 1] == cAstar::cObstacle || datas[nearIdx + width] == cAstar::cObstacle)
					continue;
			case 3:
				if (datas[nearIdx - 1] == cAstar::cObstacle || datas[nearIdx + width] == cAstar::cObstacle)
					continue;
			case 5:
				if (datas[nearIdx - 1] == cAstar::cObstacle || datas[nearIdx - width] == cAstar::cObstacle)
					continue;
			case 7:
				if (datas[nearIdx + 1] == cAstar::cObstacle || datas[nearIdx - width] == cAstar::cObstacle)
					continue;
				/*
			case 0:
			case 4:
				if (点阵数据[相邻索引+地图宽度] != 可通过 || 点阵数据[相邻索引-地图宽度] != 可通过)
					continue;
			case 2:
			case 6:
				if (点阵数据[相邻索引-1] != 可通过 || 点阵数据[相邻索引+1] != 可通过)
					continue;
				*/
			}

			sNode& nodeNear = nodes[nearIdx];
			/* 检查是否已到达终点 */
			if (vNear.x == vEnd.x && vNear.y == vEnd.y)
			{
				isFound = true;
				nodeNear/*node[nearIdx]*/.next = vCur;
				break;
			}
			
			g = ((i % 2) ? 14 : 10) + ::abs(datas[curIdx] - datas[nearIdx]);
			
			
			if (nodeNear/*nodes[nearIdx]*/.state == cAstar::cUnknown)
			{
				/* 放入待检链表中 */
				nodeNear/*node[nearIdx]*/.state = cAstar::cWaitChecking;
				nodeNear/*node[nearIdx]*/.distanceBegin = nodeCur/*node[curIdx]*/.distanceBegin + g;
				nodeNear/*node[nearIdx]*/.distanceEnd = getDistance(vNear,vEnd);
				nodeNear/*node[nearIdx]*/.distance = nodeNear/*node[nearIdx]*/.distanceBegin + nodeNear/*node[nearIdx]*/.distanceEnd;
				nodeNear/*node[nearIdx]*/.next = vCur;

				distance = nodeNear/*node[nearIdx]*/.distance;
				if (link2.getNodesCount() == 0)
				{
					link2.insert((ccastar::voidp)nearIdx, distance/*node[nearIdx].distance*/);
				}
				else
				{
					link2.setTail();
					while (true)
					{
						if (link2.getKey() >= distance)
						{
							link2.insert((ccastar::voidp)nearIdx, distance/*node[nearIdx].distance*/);
							break;
						}
						if (!link2.setParent())
						{
							link2.insert((ccastar::voidp)nearIdx, distance/*node[nearIdx].distance*/, cLink2::eInsert::before);
							break;
						}
					}
				}
			}
			else if (nodeNear/*node[nearIdx]*/.state == cAstar::cWaitChecking)
			{
				/* 如果将当前点设为父 G(距起点) 值是否更小 */
				if (nodeNear/*node[nearIdx]*/.distanceBegin > nodeCur/*node[curIdx]*/.distanceBegin + g)
				{
					nodeNear/*node[nearIdx]*/.next = vCur;
					nodeNear/*node[nearIdx]*/.distanceBegin = nodeCur/*node[curIdx]*/.distanceBegin + g;
					nodeNear/*node[nearIdx]*/.distance = nodeNear/*node[nearIdx]*/.distanceBegin + nodeNear/*node[nearIdx]*/.distanceEnd;
				}
			}
		}
	}

	return isFound;
}



bool cAstar::next(sXY& v)
{
	if (isOut(v))
	{
		return false;
	}
	ccastar::ulong idx = v.y * _map->width + v.x;
	v = _map->nodes[idx].next;
	return true;
}



bool cAstar::isOut(const sXY& v)
{
	return v.x < 0 || v.y < 0 || v.x >= _map->width || v.y >= _map->height;
}



#undef ccc_astar_malloc
#undef ccc_astar_free
#undef ccc_astar_clear