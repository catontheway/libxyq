#include "global.h"

BOOL cFindPath::FindPath(cObj* pObj, int Xend, int Yend)
{
	if (_pMap == nullptr)
	{
		return FALSE;
	}

	vector<cocos2d::Vec2> paths;
	_pMap->search(cocos2d::Vec2(pObj->GetX(), pObj->GetY()), cocos2d::Vec2(Xend, Yend), paths);
	if (paths.empty())
	{
		return FALSE;
	}
	pObj->m_Path.clear();//清空
	pObj->m_time = -1;
	forv(paths, k)
	{
		pObj->m_Path.push_back(Coordinate(paths[k].x, paths[k].y));
		pObj->m_time += 1;
	}
	pObj->m_time -= 1;
	if (pObj->m_time < 0)return FALSE;
	pObj->SetTarget(pObj->m_Path[pObj->m_time].sx, pObj->m_Path[pObj->m_time].sy);
	pObj->m_time -= 1;
	return TRUE;
}
//我准备在cMyMap中调用它
void cFindPath::ResetMap(sMap* pMap)
{
	Free();
	_pMap = pMap;
}

void cFindPath::Free()
{
}

BOOL cFindPath::InitMap()
{
	return TRUE;
}

cFindPath::~cFindPath()
{
	Free();
}