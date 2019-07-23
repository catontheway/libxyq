#include "_global.h"

static const int _20 = 25;

bool cCanvas::Init()
{
	if (m_bInit)return true;
	m_bInit = true;

//	m_CanvasCube.resize( = g_640 * g_480 / 32 / 32);

	for (int i = 0; i < m_CanvasCube.size(); i++)
	{
		sCanvasCube& cube = m_CanvasCube[i];
		cube.m_Data.m_x = (i % _20) << 5;
		cube.m_Data.m_y = (i / _20) << 5;
		cube.m_Data.m_Width = 32;
		cube.m_Data.m_Height = 32;

		
		cube.m_Rect.left = cube.m_Data.m_x;
		cube.m_Rect.top = cube.m_Data.m_y;
		cube.m_Rect.right = cube.m_Data.m_x + cube.m_Data.m_Width;
		cube.m_Rect.bottom = cube.m_Data.m_y + cube.m_Data.m_Height;


		cube.PicNumOfPreFrame = -1;
		cube.PicNumOfCurrFrame = 0;
		cube.NeedReDraw = true;
		cube.m_Data.m_pData = new uchar[2048];
		cube.m_bCover已覆盖数据 = false;
	}
	
	return true;
}

bool cCanvas::Add(cWasFile* pPic, int showmode, bool bCover )
{
	if (!pPic->m_NeedShow)return true;
	if (!pPic->m_NowID)return true;
	bool bChange = pPic->NextFrame();
	if (!pPic->m_NeedShow)return true;
	bool bMove = pPic->m_bMove;

	RECT& picRect = pPic->m_PreShowRect;
	if (bChange || bMove) //如果图像发生改变,把之前的设为无效
	{
		if (pPic->m_PreShowRect.right>0)
			SetRedraw(picRect);
	}
	pPic->GetPicRange(picRect);
	int xstart;
	int ystart;
	int xend;
	int yend;

	if (0 == showmode)
	{	
		int xof = g_pMainState->m_Map.m_pMap->GetXCenter() - g_half320;
		int yof = g_pMainState->m_Map.m_pMap->GetYCenter() - g_half240;
		picRect.left = picRect.left - xof;
		picRect.top = picRect.top - yof;
		picRect.right = picRect.right - xof;
		picRect.bottom = picRect.bottom - yof;
	}
	if (picRect.left>= g_640)return false;
	if (picRect.top >= g_480)return false;
	if (picRect.right < 0)return false;
	if (picRect.bottom < 0)return false;
	

	xstart = picRect.left>>5;
	ystart = picRect.top >>5;
	xend = picRect.right >>5;
	yend = picRect.bottom>>5;

	
	if (xstart < 0)xstart = 0;
	if (ystart < 0)ystart = 0;
	int myWide = (g_640 / 32);
	if (xend >= myWide)xend = myWide - 1;
	if (yend >= g_480 / 32)yend = g_480 / 32 - 1;

	
	int index2 = xstart + ystart * myWide;
	int index=index2;
	if (bCover)
	{
		for (int j = ystart; j <= yend; j++)
		{

			for (int i = xstart; i <= xend; i++)
			{
				if (i == xstart || i == xend || j == ystart || j == yend)
				{
					m_CanvasCube[index].Add(pPic, showmode, bMove, 0, bChange);
				}
				else
				{
					if (1 == m_CanvasCube[index].NeedReDraw)
						m_CanvasCube[index].NeedReDraw = false;
					m_CanvasCube[index].Add(pPic, showmode, bMove, 1, bChange);
				}
				index += 1;
			}
			index2 += myWide;
			index = index2;
		}
	}
	else
	for (int j = ystart; j <= yend; j++)
	{
		for (int i = xstart; i <= xend; i++)
		{
			m_CanvasCube[index].Add(pPic, showmode, bMove, bCover, bChange);
			index += 1;
		}
		index2 += myWide;
		index = index2;
	}
	pPic->m_bMove = false;
	return true;
}

bool cCanvas::Add(cText* pTex)
{
	int xtrue=pTex->GetX();
	int ytrue=pTex->GetY();
	if (!pTex->m_bShowOnScreen)
	{
		xtrue -= g_pMainState->m_Map.m_pMap->GetXCenter() - g_half320;
		ytrue -= g_pMainState->m_Map.m_pMap->GetYCenter() - g_half240;
	}
	if (!pTex->m_NeedShow)return true;
	if (xtrue+pTex->GetShowWidth() < 0)return false;
	if (ytrue+pTex->GetShowHeight() < 0)return false;
	if (ytrue >= g_480)return false;
	if (xtrue >= g_640)return false;
	bool bMove = pTex->m_bMove;
	if (bMove)
	{
		if (pTex->m_PreShowRect.right > 0)
			SetRedraw(pTex->m_PreShowRect);
	}
	pTex->m_PreShowRect.left = xtrue;
	pTex->m_PreShowRect.right = xtrue + pTex->GetShowWidth();
	pTex->m_PreShowRect.top = ytrue;
	pTex->m_PreShowRect.bottom = ytrue + pTex->GetShowHeight();

	int xstart = pTex->m_PreShowRect.left >>5;
	int ystart = pTex->m_PreShowRect.top >>5;
	int xend = pTex->m_PreShowRect.right >>5;
	int yend = pTex->m_PreShowRect.bottom >>5;


	if (xstart < 0)xstart = 0;
	if (ystart < 0)ystart = 0;
// 	if (xend >19)xend = 19;
// 	if (yend >14)yend = 14;
	int myWide = (g_640 / 32);
	if (xend >= myWide)xend = myWide - 1;
	if (yend >= g_480 / 32)yend = g_480 / 32 - 1;

	int index2 = xstart+ystart*myWide;
	int index = index2;
	for (int j = ystart; j <= yend; j++)
	{
		for (int i = xstart; i <= xend; i++)
		{
			m_CanvasCube[index].Add(pTex, bMove); 
			index += 1;
		}
		index2+=myWide;
		index = index2;
	}
	pTex->m_bMove = false;
	return true;
}

bool cCanvas::Add(cObjWas* p, int showmode, bool bCover/*=false*/)
{
	if (!p->m_NeedShow)return true;
	bool bChange = p->isFrameChange2Next();
	bool bMove = p->m_bMove;
	if (bChange || bMove) //如果图像发生改变,把之前的设为无效
	{
		if (p->m_PreShowRect.right > 0)
			SetRedraw(p->m_PreShowRect);
	}
	p->m_PreShowRect = p->GetPicRange();
	if (showmode == 0)
	{
		p->m_PreShowRect.left = p->m_PreShowRect.left - g_pMainState->m_Map.m_pMap->GetXCenter() + g_half320;
		p->m_PreShowRect.right = p->m_PreShowRect.right - g_pMainState->m_Map.m_pMap->GetXCenter() + g_half320;
		p->m_PreShowRect.top = p->m_PreShowRect.top - g_pMainState->m_Map.m_pMap->GetYCenter() + g_half240;
		p->m_PreShowRect.bottom = p->m_PreShowRect.bottom - g_pMainState->m_Map.m_pMap->GetYCenter() + g_half240;
	}
	if (p->m_PreShowRect.bottom<0)return false;
	if (p->m_PreShowRect.right<0)return false;
	if (p->m_PreShowRect.top >= g_480)return false;
	if (p->m_PreShowRect.left >= g_640)return false;
	if (p->m_PreShowRect.left < 0)p->m_PreShowRect.left = 0;
	if (p->m_PreShowRect.top < 0)p->m_PreShowRect.top = 0;

	int xstart = p->m_PreShowRect.left >>5;
	int ystart = p->m_PreShowRect.top >>5;
	int xend = p->m_PreShowRect.right >>5;
	int yend = p->m_PreShowRect.bottom >>5;

// 	if (xend>19)xend = 19;
// 	if (yend>14)yend = 14;
	int myWide = (g_640 / 32);
	if (xend >= myWide)xend = myWide - 1;
	if (yend >= g_480 / 32)yend = g_480 / 32 - 1;

	int index2 = xstart + ystart * myWide;
	int index = index2;
	if (bCover)
	{
		for (int j = ystart; j <= yend; j++)
		{
			for (int i = xstart; i <= xend; i++)
			{
				if (i == xstart || i == xend || j == ystart || j == yend)
					m_CanvasCube[index].Add(p, showmode, bMove, 0, bChange);
				else
				{
					if (1 == m_CanvasCube[index].NeedReDraw)
						m_CanvasCube[index].NeedReDraw = false;
					m_CanvasCube[index].Add(p, showmode, bMove, 1, bChange);
				}
				index += 1;
			}
			index2 += myWide;
			index = index2;
		}
	}
	else
	for (int j = ystart; j <= yend; j++)
	{

		for (int i = xstart; i <= xend; i++)
		{
			m_CanvasCube[index].Add(p, showmode, bMove, bCover, bChange);
			index += 1;
		}
		index2 += myWide;
		index = index2;
	}
		p->m_bMove = false;
	return true;
}

bool cCanvas::Add(cObjWasFather* pTex, int showmode, bool bCover /*= false*/)
{
	if (!pTex->m_NeedShow)return true;
	int xtrue = pTex->GetX();
	int ytrue = pTex->GetY();
	if (!showmode)
	{
		xtrue -= g_pMainState->m_Map.m_pMap->GetXCenter() - g_half320;
		ytrue -= g_pMainState->m_Map.m_pMap->GetYCenter() - g_half240;
	}
	
	if (xtrue + pTex->GetShowWidth() < 0)return false;
	if (ytrue + pTex->GetShowHeight() < 0)return false;
	if (ytrue >= g_480)return false;
	if (xtrue >= g_640)return false;
	
	pTex->m_PreShowRect.left = xtrue;
	pTex->m_PreShowRect.right = xtrue + pTex->GetShowWidth();
	pTex->m_PreShowRect.top = ytrue;
	pTex->m_PreShowRect.bottom = ytrue + pTex->GetShowHeight();

	int xstart = pTex->m_PreShowRect.left >>5;
	int ystart = pTex->m_PreShowRect.top >>5;
	int xend = pTex->m_PreShowRect.right >>5;
	int yend = pTex->m_PreShowRect.bottom>>5;

	bool bMove = pTex->m_bMove;
	if (bMove)
	{
		SetRedraw(pTex->m_PreShowRect);
	}
	if (xstart < 0)xstart = 0;
	if (ystart < 0)ystart = 0;
// 	if (xend >19)xend = 19;
// 	if (yend >14)yend = 14;
	int myWide = (g_640 / 32);
	if (xend >= myWide)xend = myWide - 1;
	if (yend >= g_480 / 32)yend = g_480 / 32 - 1;

	int index2=xstart+ystart*myWide;
	int index = index2;
	if (bCover)
	{
		for (int j = ystart; j <= yend; j++)
		for (int i = xstart; i <= xend; i++)
		{
			if (i == xstart || i == xend || j == ystart || j == yend)
				m_CanvasCube[index].Add(pTex, showmode, bMove, 0);
			else
			{
				if (1 == m_CanvasCube[index].NeedReDraw)
					m_CanvasCube[index].NeedReDraw = false;
				m_CanvasCube[index].Add(pTex, showmode, bMove, 1);
			}
			index += 1;
		}
		index2 += myWide;
		index = index2;
	}
	else
	for (int j = ystart; j <= yend; j++)
	{

		for (int i = xstart; i <= xend; i++)
		{
			m_CanvasCube[index].Add(pTex, showmode, bMove, 0);
			index += 1;
		}
		index2 += myWide;
		index = index2;
	}
	pTex->m_bMove = false;
	return true;
}

bool cCanvas::Show()
{
	auto& Map = g_pMainState->m_Map;
	const auto& pMap = Map.m_pMap;
// 	if (!pMap->m_bLoadReady)
// 	{
// 		return true;
// 	}
	while (!pMap->m_bLoadReady)
	{
		Sleep(1);
	}
	if (m_Time < m_CanvasCube.size())m_Time += 25;
	if (m_Time > m_CanvasCube.size())
	{
		m_Time = m_CanvasCube.size();
	}
	for (int i = 0; i < m_Time; i++)
	{
		sCanvasCube& cube = m_CanvasCube[i];
		if (!cube.NeedReDraw)
		{
			if (cube.PicNumOfPreFrame != cube.PicNumOfCurrFrame)
			{
				cube.NeedReDraw = true;
			}
			else if (cube.PreCover != cube.m_bCover已覆盖数据)
			{
				cube.NeedReDraw = true;
			}
			else
			{
				continue;
			}
		}

		////////////////////////////////////////////////////////////////////////// 呵呵哒 战斗底图
		if (g_StateType == STATE_FIGHT)
		{
			if (!g_pMainState->m_pFightState)
			{
				return true;
			}
	
			static uchar* p1; p1 = cube.m_Data.m_pData;
			static uchar* p2; p2 = &g_pMainState->m_pFightState->m_pFightBack[(((i / _20) << 5)) * (800 * 2) + ((i % _20) << 6)];
			for (int i2 = 0; i2 < 32; i2++) 
			{
				memcpy(p1, p2, 64);
				p1 += 64;
				p2 += 800 * 2;
			}
		}
		else
		{
			if (m_NeedShowMap)
			{
				if (!cube.m_bCover已覆盖数据)
				{
					Map.Show(cube.m_Data.m_pData, cube.m_Rect);
				}
				
			}
		}
		static RECT rec;
		for (int k = 0; k < cube.PicNumOfCurrFrame; k++)
		{
			rec = cube.m_Rect;
			switch (cube.PicType[k])
			{
			case 0:
				if (1)
				{
					cWasFile* p = (cWasFile*)cube.pPicList[k];
					if (cube.ShowMode[k])
					{
						p->ShowOnScreen(cube.m_Data.m_pData, rec);
					}
					else
					{
						p->Show(cube.m_Data.m_pData, rec, &Map);
					}
				}
				break;
			case 2:
				if (1)
				{
					cText* p = (cText*)cube.pPicList[k];
					p->DrawAlphaEx(cube.m_Data.m_pData, rec, pMap);
				}
				break;
			case 3:
				if (1)
				{
					cObjWas* p = (cObjWas*)cube.pPicList[k];

					switch (cube.ShowMode[k])
					{
					case 0:
						p->Show(cube.m_Data.m_pData, rec, &Map);
						break;
					case 1:
						p->ShowOnScreen(cube.m_Data.m_pData, rec);
						break;
					}
				}
				break;
			case 4:
				if (1)
				{
					cObjWasFather* p = (cObjWasFather*)cube.pPicList[k];
					switch (cube.ShowMode[k])
					{
					case 0:
						if (1)
						{
							static int xpos; xpos = p->m_x - pMap->GetXCenter() + g_half320;
							static int ypos; ypos = p->m_y - pMap->GetYCenter() + g_half240;
							cube.m_Data.Draw(p, xpos, ypos);
						}
						break;
					case 1:
						cube.m_Data.Draw(p);
						break;
					}
					
				}
				break;
			}
		}
	}
	
	SwapBuf();

	for (int i = 0; i < m_Time; i++)
	{
		m_CanvasCube[i].PicNumOfPreFrame = m_CanvasCube[i].PicNumOfCurrFrame;
		m_CanvasCube[i].PicNumOfCurrFrame = 0;
		m_CanvasCube[i].NeedReDraw = false;
		m_CanvasCube[i].PreCover = m_CanvasCube[i].m_bCover已覆盖数据;
		m_CanvasCube[i].m_bCover已覆盖数据 = false;
	}
	return true;
}

bool cCanvas::Free()
{
	for (int i = 0; i < m_CanvasCube.size(); i++)
	{
		SAFE_DELETE_ARRAY(m_CanvasCube[i].m_Data.m_pData);
	}
	DeleteObject(hPen);
	return true;
}

cCanvas::~cCanvas()
{
	Free();
}

bool cCanvas::SetRedraw(const RECT& rect)
{
	int	xstart = rect.left>>5;
	int	ystart = rect.top >>5;
	int	xend = rect.right>>5;
	int	yend = (rect.bottom)>>5;

	if (xstart < 0)xstart = 0;
	if (ystart < 0)ystart = 0;
// 	if (xend >19)xend = 19;
// 	if (yend >14)yend = 14;
	int myWide = (g_640 / 32);
	if (xend >= myWide)xend = myWide - 1;
	if (yend >= g_480 / 32)yend = g_480 / 32 - 1;
	int k;
	for (int i = xstart; i <= xend; i++)
	for (int j = ystart; j <= yend; j++)
	{
		k = i + j * myWide;
		m_CanvasCube[k].PicNumOfPreFrame = -1;
	}
	return true;
}

void cCanvas::SwapBuf()
{
	g_pBmpinfo->bmiHeader.biHeight = -32;
	g_pBmpinfo->bmiHeader.biWidth = 32;
	g_pBmpinfo->bmiHeader.biCompression = 3;
	g_pBmpinfo->bmiHeader.biSizeImage = 2048;

// 	static uchar* pdata = new uchar[g_640 * g_480 * 2];
// 	forr(m_CanvasCube, i)
// 	{
// 		const auto& d = m_CanvasCube[i].m_Data;
// 		for (int k = 0; k < 32; ++k)
// 		{
// 			memcpy(&pdata[(d.m_y + k) * g_640 * 2 + d.m_x * 2], &d.m_pData[k * 64], 64);
// 		}
// 	}
//
// 	forr(m_CanvasCube, i)
// 	{
// 		const auto& d = m_CanvasCube[i].m_Data;
// 		for (int k = 0; k < 32; ++k)
// 		{
// 			memcpy(&d.m_pData[k * 64], &pdata[(d.m_y + k) * g_640 * 2 + d.m_x * 2], 64);
// 		}
// 	}


	forr (m_CanvasCube, i)
	{
		const auto& d = m_CanvasCube[i].m_Data;
//		if (1 == m_CanvasCube[i].NeedReDraw)
		{
			//////画出来
			SetDIBitsToDevice(
				g_DC,
				d.m_x,
				d.m_y,
				32,
				32,
				0, 0,
				0,
				32,
				d.m_pData,
				g_pBmpinfo,
				DIB_RGB_COLORS
				);
		}
	}

//	SetDIBitsToDevice(g_DC, 0, 0, g_640, g_480, 0, 0, 0, g_480, pdata, g_pBmpinfo, DIB_RGB_COLORS);
	BitBlt(g_ShowDC, 0, 0, g_640, g_480, g_DC, 0, 0, SRCCOPY);
}

void cCanvas::SetRedrawAll(bool ball)
{
	if (ball)
	{
		for (int i = 0; i < m_CanvasCube.size(); i++)
		{
			m_CanvasCube[i].PicNumOfPreFrame = -1;
		}
	}
	else
		for (int i = 0; i < m_CanvasCube.size(); i++)
	{
		if (m_CanvasCube[i].m_bCover已覆盖数据)
			continue;
		m_CanvasCube[i].PicNumOfPreFrame = -1;
	}
}

bool sCanvasCube::Add(cWasFile* p, int OnScreen, bool bMove, bool bCover,bool bChange)
{
	CheckNum(bCover);
	ShowMode[PicNumOfCurrFrame] = OnScreen;
	pPicList[PicNumOfCurrFrame] = p;
	PicType[PicNumOfCurrFrame] = 0;
	PicNumOfCurrFrame += 1;
	if (NeedReDraw)return true;
	if (bChange || bMove)
	{
			NeedReDraw = true;
	}
	return true;
}
bool sCanvasCube::Add(cObjWas* p, int OnScreen, bool bMove, bool bCover,bool bChange)
{
	
	CheckNum(bCover);
	ShowMode[PicNumOfCurrFrame] = OnScreen;
	pPicList[PicNumOfCurrFrame] = p;
	PicType[PicNumOfCurrFrame] = 3;
	PicNumOfCurrFrame += 1;
	if (NeedReDraw)return true;
	if (bChange || bMove)
	{
		NeedReDraw = true;
	}
	return true;
}

bool sCanvasCube::Add(cText* p, bool bMove)
{
	CheckNum(0);
	ShowMode[PicNumOfCurrFrame] = 0;
	pPicList[PicNumOfCurrFrame] = p;
	PicType[PicNumOfCurrFrame] = 2;
	PicNumOfCurrFrame += 1;

	if (!NeedReDraw)
	{
		//是否移动
		if (bMove)
			NeedReDraw = true;
	}
	return true;
}

bool sCanvasCube::Add(cObjWasFather* p, int showmode, bool bMove, bool bCover)
{
	CheckNum(bCover);
	ShowMode[PicNumOfCurrFrame] = showmode;
	pPicList[PicNumOfCurrFrame] = p;
	PicType[PicNumOfCurrFrame] = 4;
	PicNumOfCurrFrame += 1;
	//是否移动
	if (bMove)
		NeedReDraw = true;
	return true;
}

bool sCanvasCube::CheckNum(bool bCover)
{
	if (bCover)
	{
		PicNumOfCurrFrame = 0;
		m_bCover已覆盖数据 = bCover;
		return true;
	}
	if (PicNumOfCurrFrame >= DEEP_20)
	{
		for (int i = 0; i < DEEP_20 - 1; i++)
		{
			pPicList[i] = pPicList[i + 1];
			PicType[i] = PicType[i + 1];
			ShowMode[i] = ShowMode[i+1];
		}
		PicNumOfCurrFrame = DEEP_20 - 1;
	}
	return true;
}





