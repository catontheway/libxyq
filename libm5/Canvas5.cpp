#include "global.h"
// #include <psapi.h>
// #pragma comment(lib,"psapi")   

BOOL sCanvas::Add(CWFile* p, int OnScreen, BOOL bMove, BOOL bCover, BOOL bChange)
{
	CheckNum(bCover);
	sCube c;
	c.pPic = p;
	c.type = 0;
	c.screen = OnScreen;
	_cubes.push_back(c);
	if (NeedReDraw)
		return TRUE;
	if (bChange || bMove)
	{
		NeedReDraw = TRUE;
	}
	return TRUE;
}

BOOL sCanvas::Add(cWfileP* p, int OnScreen, BOOL bMove, BOOL bCover, BOOL bChange)
{
	CheckNum(bCover);
	sCube c;
	c.pPic = p;
	c.type = 3;
	c.screen = OnScreen;
	_cubes.push_back(c);
	if (NeedReDraw)return TRUE;
	if (bChange || bMove)
	{
		NeedReDraw = TRUE;
	}
	return TRUE;
}

BOOL sCanvas::Add(cText5* p, BOOL bMove)
{
	CheckNum(0);
	sCube c;
	c.pPic = p;
	c.type = 2;
	c.screen = p->m_bShowOnScreen;
	_cubes.push_back(c);

	if (!NeedReDraw)
	{
		//是否移动
		if (bMove)
			NeedReDraw = TRUE;
	}
	return TRUE;
}

BOOL sCanvas::Add(cObjFather* p, int OnScreen, BOOL bMove, BOOL bCover)
{
	CheckNum(bCover);
	sCube c;
	c.pPic = p;
	c.type = 4;
	c.screen = OnScreen;
	_cubes.push_back(c);
	//是否移动
	if (bMove)
		NeedReDraw = TRUE;
	return TRUE;
}

BOOL sCanvas::CheckNum(BOOL bCover)
{
	return TRUE;
}

void sCanvas::show(sCube& cube, bool onMap, bool text)
{
	switch (cube.type)
	{
	case 0:
		if (text)
		{
			break;
		}
		if (1)
		{

// 			static HANDLE hand = GetCurrentProcess();
// 			static PROCESS_MEMORY_COUNTERS pmc = { 0 }, pmc2 = { 0 };
// 			GetProcessMemoryInfo(hand, &pmc, sizeof(pmc));

			CWFile* p = (CWFile*)cube.pPic;
			if (cube.screen)
			{
				if (onMap)
				{
					break;
				}
				p->ShowOnScreen(m_Data.m_pData, m_Rect);


			}
			else
			{
				if (!onMap)
				{
					break;
				}

				p->Show(m_Data.m_pData, m_Rect, &g_pMainState->m_Map);

			}

// 			GetProcessMemoryInfo(hand, &pmc2, sizeof(pmc2));
// 			if (pmc2.WorkingSetSize > pmc.WorkingSetSize)
// 			{
// 				ccc_log("%u", pmc2.WorkingSetSize - pmc.WorkingSetSize);
// 			}

		}
		break;
	case 2:
		if (!text)
		{
			break;
		}
		if (1)
		{
// 			static HANDLE hand = GetCurrentProcess();
// 			static PROCESS_MEMORY_COUNTERS pmc = { 0 }, pmc2 = { 0 };
// 			GetProcessMemoryInfo(hand, &pmc, sizeof(pmc));

			cText5* p = (cText5*)cube.pPic;
			if (p->m_bShowOnScreen)
			{
				if (onMap)
				{
					break;
				}
			}
			else
			{
				if (!onMap)
				{
					break;
				}
			}
			p->DrawAlphaEx(m_Data.m_pData, m_Rect, g_pMainState->m_Map.m_pMap);

// 			GetProcessMemoryInfo(hand, &pmc2, sizeof(pmc2));
// 			if (pmc2.WorkingSetSize > pmc.WorkingSetSize)
// 			{
// 				ccc_log("%u", pmc2.WorkingSetSize - pmc.WorkingSetSize);
// 			}
		}
		break;
	case 3:
		if (text)
		{
			break;
		}
		if (1)
		{

			cWfileP* p = (cWfileP*)cube.pPic;

			if (cube.screen)
			{
				if (onMap)
				{
					break;
				}

// 				static HANDLE hand = GetCurrentProcess();
// 				static PROCESS_MEMORY_COUNTERS pmc = { 0 }, pmc2 = { 0 };
// 				GetProcessMemoryInfo(hand, &pmc, sizeof(pmc));


				p->ShowOnScreen(m_Data.m_pData, m_Rect);

// 				GetProcessMemoryInfo(hand, &pmc2, sizeof(pmc2));
// 				if (pmc2.WorkingSetSize > pmc.WorkingSetSize)
// 				{
// 					ccc_log("%u", pmc2.WorkingSetSize - pmc.WorkingSetSize);
// 				}
			}
			else
			{
				if (!onMap)
				{
					break;
				}
				p->Show(m_Data.m_pData, m_Rect, &g_pMainState->m_Map);
			}

		}
		break;
	case 4:
		if (text)
		{
			break;
		}
		if (1)
		{
			cObjFather* p = (cObjFather*)cube.pPic;
			if (cube.screen)
			{
				if (onMap)
				{
					break;
				}
				m_Data.Draw(p);
			}
			else
			{
				if (!onMap)
				{
					break;
				}
				int xpos = p->m_x - g_pMainState->m_Map.m_pMap->GetXCenter() + g_320;
				int ypos = p->m_y - g_pMainState->m_Map.m_pMap->GetYCenter() + g_240;
				m_Data.Draw(p, xpos, ypos);
			}
		}
		break;
	}
}



BOOL cCanvas5::Init()
{
	if (m_bInit)return TRUE;
	push();
	m_bInit = TRUE;
	return TRUE;
}

BOOL cCanvas5::Add(CWFile* pPic, int showmode, BOOL bCover)
{
	if (!pPic->m_NeedShow)return TRUE;
	if (!pPic->m_NowID)return TRUE;
	BOOL bChange = pPic->NextFrame();
	BOOL bMove = pPic->m_bMove;

	RECT& picRect = pPic->m_PreShowRect;
	if (bChange || bMove) //如果图像发生改变,把之前的设为无效
	{
		if (pPic->m_PreShowRect.right > 0)
			SetRedraw(picRect);
	}
	pPic->GetPicRange(picRect);

	if (0 == showmode)
	{	
		int xof = g_pMainState->m_Map.m_pMap->GetXCenter() - g_320;
		int yof = g_pMainState->m_Map.m_pMap->GetYCenter() - g_240;
		picRect.left = picRect.left - xof;
		picRect.top = picRect.top - yof;
		picRect.right = picRect.right - xof;
		picRect.bottom = picRect.bottom - yof;
	}
	if (picRect.left >= g_640)return FALSE;
	if (picRect.top >= g_480)return FALSE;
	if (picRect.right < 0)return FALSE;
	if (picRect.bottom < 0)return FALSE;

	_canvas.back().Add(pPic, showmode, bMove, 0, bChange);
	pPic->m_bMove = FALSE;
	return TRUE;
}

BOOL cCanvas5::Add(cText5* pTex)
{
	if (!pTex->m_NeedShow)return TRUE;
	int xtrue=pTex->GetX();
	int ytrue=pTex->GetY();
	if (pTex->m_bShowOnScreen)
	{

	}
	else 
	{
		xtrue -= g_pMainState->m_Map.m_pMap->GetXCenter() - g_320;
		ytrue -= g_pMainState->m_Map.m_pMap->GetYCenter() - g_240;
	}
	if (xtrue + pTex->GetShowWidth() < 0)return FALSE;
	if (ytrue + pTex->GetShowHeight() < 0)return FALSE;
	if (ytrue >= g_480)return FALSE;
	if (xtrue >= g_640)return FALSE;
	BOOL bMove = pTex->m_bMove;
	if (bMove)
	{
		if (pTex->m_PreShowRect.right > 0)
			SetRedraw(pTex->m_PreShowRect);
	}
	pTex->m_PreShowRect.left = xtrue;
	pTex->m_PreShowRect.right = xtrue + pTex->GetShowWidth();
	pTex->m_PreShowRect.top = ytrue;
	pTex->m_PreShowRect.bottom = ytrue + pTex->GetShowHeight();

	_canvas.back().Add(pTex, bMove);
	pTex->m_bMove = FALSE;
	return TRUE;
}

BOOL cCanvas5::Add(cWfileP* p, int showmode, BOOL bCover/*=FALSE*/)
{
	if (!p->m_NeedShow)return TRUE;
	BOOL bChange = p->NextFrame();

	BOOL bMove = p->m_bMove;
	if (bChange || bMove) //如果图像发生改变,把之前的设为无效
	{
		if (p->m_PreShowRect.right > 0)
			SetRedraw(p->m_PreShowRect);
	}
	p->m_PreShowRect = p->GetPicRange();
	if (showmode == 0)
	{
		p->m_PreShowRect.left = p->m_PreShowRect.left - g_pMainState->m_Map.m_pMap->GetXCenter() + g_320;
		p->m_PreShowRect.right = p->m_PreShowRect.right - g_pMainState->m_Map.m_pMap->GetXCenter() + g_320;
		p->m_PreShowRect.top = p->m_PreShowRect.top - g_pMainState->m_Map.m_pMap->GetYCenter() + g_240;
		p->m_PreShowRect.bottom = p->m_PreShowRect.bottom - g_pMainState->m_Map.m_pMap->GetYCenter() + g_240;
	}
	if (p->m_PreShowRect.bottom<0)return FALSE;
	if (p->m_PreShowRect.right<0)return FALSE;
	if (p->m_PreShowRect.top >= g_480)return FALSE;
	if (p->m_PreShowRect.left >= g_640)return FALSE;
	if (p->m_PreShowRect.left < 0)p->m_PreShowRect.left = 0;
	if (p->m_PreShowRect.top < 0)p->m_PreShowRect.top = 0;

	_canvas.back().Add(p, showmode, bMove, 1, bChange);
	p->m_bMove = FALSE;
	return TRUE;
}

BOOL cCanvas5::Add(cObjFather* pTex, int showmode, BOOL bCover /*= FALSE*/)
{
	if (!pTex->m_NeedShow)return TRUE;

	int xtrue = pTex->GetX();
	int ytrue = pTex->GetY();
	if (!showmode)
	{
		xtrue -= g_pMainState->m_Map.m_pMap->GetXCenter() - g_320;
		ytrue -= g_pMainState->m_Map.m_pMap->GetYCenter() - g_240;
	}
	
	if (xtrue + pTex->GetShowWidth() < 0)return FALSE;
	if (ytrue + pTex->GetShowHeight() < 0)return FALSE;
	if (ytrue >= g_480)return FALSE;
	if (xtrue >= g_640)return FALSE;
	
	pTex->m_PreShowRect.left = xtrue;
	pTex->m_PreShowRect.right = xtrue + pTex->GetShowWidth();
	pTex->m_PreShowRect.top = ytrue;
	pTex->m_PreShowRect.bottom = ytrue + pTex->GetShowHeight();

	_canvas.back().Add(pTex, showmode, pTex->m_bMove, 1);
	pTex->m_bMove = FALSE;
	return TRUE;
}

BOOL cCanvas5::Show()
{

	for (auto& it = _canvas.rbegin(); it != _canvas.rend(); ++it)
	{
		for (auto& it2 = it->_cubes.rbegin(); it2 != it->_cubes.rend(); ++it2)
		{
			it->show(*it2, false, it2->type == 2);
		}
		for (auto& it2 = it->_cubes.rbegin(); it2 != it->_cubes.rend(); ++it2)
		{
			it->show(*it2, false, it2->type != 2);
		}
	}


	if (m_NeedShowMap && g_StateType == STATE_MAIN)
	{
		if (!_canvas.back().m_bCover)
		{
			g_pMainState->m_Map.m_pMap->showMask();
		}
	}

	for (auto& it = _canvas.rbegin(); it != _canvas.rend(); ++it)
	{
		for (auto& it2 = it->_cubes.rbegin(); it2 != it->_cubes.rend(); ++it2)
		{
			it->show(*it2, true, true);
		}
	}
	for (auto& it = _canvas.begin(); it != _canvas.end(); ++it)
	{
		for (auto& it2 = it->_cubes.rbegin(); it2 != it->_cubes.rend(); ++it2)
		{
			it->show(*it2, true, false);
		}
	}


	if (g_StateType == STATE_FIGHT)
	{
		if (!g_pMainState->m_pFightState)
		{
			return TRUE;
		}
		static CWFile* s_wdfFight = nullptr;
		if (s_wdfFight == nullptr)
		{
			s_wdfFight = new CWFile();
			s_wdfFight->Load(0x5E41A0E6);
			s_wdfFight->SetXY((g_640 - s_wdfFight->GetWidth()) / 2, (g_480 - s_wdfFight->GetHeight()) / 2);
		}
		s_wdfFight->ShowOnScreen(nullptr, _canvas.back().m_Rect);
		g_pMainState->m_Map.m_pMap->Show(nullptr, _canvas.back().m_Rect);
	}
	else
	{
		if (m_NeedShowMap)
		{
			if (!_canvas.back().m_bCover)
			{
				g_pMainState->m_Map.Show(nullptr, _canvas.back().m_Rect);
			}
		}
	}


	_canvas.clear();
	push();
	return TRUE;
}

BOOL cCanvas5::Free()
{
	DeleteObject(hPen);
	return TRUE;
}

cCanvas5::~cCanvas5()
{
	Free();
}

BOOL cCanvas5::SetRedraw(RECT rect)
{
	forv(_canvas, k)
	{
		_canvas[k].PrePicNum = -1;
	}
	return TRUE;
}

void cCanvas5::SwapBuf()
{

}

void cCanvas5::SetRedrawAll(BOOL ball)
{
	forv(_canvas, k)
	{
		_canvas[k].PrePicNum = -1;
	}
}


void cCanvas5::push()
{
	_canvas.push_back(sCanvas());
}


