#include "_global.h"

typedef uchar* lpBYTE;
CSprite::CSprite(void)
	: m_MaxDirection(0)
	, m_Frame(0)
	, m_Width(0)
	, m_Height(0)
	, lpAlpha(NULL)
	, lpDate(NULL)
	, pitch(NULL)
	, m_kx(0)
	, m_ky(0)
	, flp(NULL)
	, fstr(NULL)
	, fsize(0)
{
}


CSprite::~CSprite(void)
{

	FreeDatelp();


}


bool CSprite::Load(void* lp, long size, int type, sChangeColorData* pChangeColorData)
{
	FreeDatelp();

#if 0
	if (1)
	{
		WasReader was;
		static cpp::sPointer pter;
		pter.ptr = (char*)lp;
		pter.size = size;
		if (!was.init(pter))
		{
			return false;
		}

		if (pChangeColorData)
		{
			static WasReader::sColor c;
			c.partCount = pChangeColorData->partnum;
			for (int i = 0; i < c.partCount; ++i)
			{
				const sChangeColorMatrix&  matrix = pChangeColorData->m_colormatrix[i];
				auto& m = c.matrixs[i];
				m.start = matrix.m_start;
				m.end = matrix.m_end;
				m.r1 = matrix.x1;
				m.r2 = matrix.x2;
				m.r3 = matrix.x3;

				m.g1 = matrix.y1;
				m.g2 = matrix.y2;
				m.g3 = matrix.y3;

				m.b1 = matrix.z1;
				m.b2 = matrix.z2;
				m.b3 = matrix.z3;
			}

			for (int i = c.partCount; i < 4; ++i)
			{
				auto& m = c.matrixs[i];
				memset(&m, 0, sizeof(WasReader::sColorMatrix));
			}

			if (!was.load(&c))
			{
				return false;
			}
		}
		else
		{
			if (!was.load(nullptr))
			{
				return false;
			}
		}

		m_MaxDirection = was.dCount;
		m_Frame = was.fCountPD;
		m_Width = was.wMax;
		m_Height = was.hMax;
		m_kx = was.kx;
		m_ky = was.ky;

		int total = m_MaxDirection * m_Frame;

		m_pDataOffsetList = new DATEHEARD[total];
		lpDate = new lpBYTE[total];
		lpAlpha = new lpBYTE[total];

		pitch = ((m_Width << 1) + 7) & 0xFFFFFFF8;
		int whd = pitch * m_Height + 7;
		int wha = m_Width * m_Height;
		for (int i = 0; i < total; ++i)
		{
			lpDate[i] = new uchar[whd];
			lpAlpha[i] = new uchar[wha];
			memset(lpAlpha[i], 0, wha);

			const auto& f = was.frames[i];
			auto& l = m_pDataOffsetList[i];
			l.Width = f.w;
			l.Height = f.h;
			l.FramX = f.x;
 			l.FramY = f.y;

			if (f.w == 0)
			{
				continue;
			}

			if (1)
			{
				if (!was.iterFrame(i))
				{
					continue;
				}


				was.isgh = true;
				for (int k = 0; k < f.h; ++k)
				{
					was.mseek(i, k);

					ushort* pD = (ushort*)&lpDate[i][k * pitch];
					uchar* pA = &lpAlpha[i][k * m_Width];

					for (int ix = 0; ix < f.w;)
					{
						if (!was.iterData(pD, pA, k, ix))
						{
							break;
						}
					}
				}

				if (was.isgh)
				{
					for (int iy = 0; iy < m_Height; iy += 2)
					{
						if (iy + 1 < m_Height)
						{
							memcpy(&lpDate[i][(iy + 1)*pitch], &lpDate[i][iy*pitch], m_Width << 1);
							memcpy(&lpAlpha[i][(iy + 1)*m_Width], &lpAlpha[i][iy*m_Width], m_Width);
						}
					}
				}
			}
			else
			{
				const auto& fd = was.getFrameData(i);
				if (fd.data && fd.alpha)
				{
					lpDate[i] = new uchar[whd];
					lpAlpha[i] = new uchar[wha];
					memset(lpAlpha[i], 0, wha);

					for (int k = 0; k < f.h; ++k)
					{
						ushort* pD = (ushort*)&lpDate[i][k * pitch];
						uchar* pA = &lpAlpha[i][k * m_Width];

						memcpy(pD, &fd.data[k * f.w], f.w * 2);
						memcpy(pA, &fd.alpha[k * f.w], f.w);
					}
					delete[] fd.data, fd.alpha;
				}
			}
		}
		m_bLoad = true;
		return true;
	}
#endif
	

	int i, j;

	bool isgh;	//是否隔行

	WASFILEHEADER head;		// 文件头信息
	WPixel Pal[256];		// 调色板
	ulong* FrameList;		// 帧偏移表


	ulong* LineList;		// 行偏移表

	mcreat(lp, size);
	//		mseek(0);
	mread(&head, sizeof(WASFILEHEADER), 1);
	if (head.wastitle != 'PS')
	{
		FreeDatelp();
		ERRBOX;
	}

	// 取调色板
	mseek(head.szHheard + 4);
	mread(Pal, 256 * sizeof(WPixel), 1);
	int iii = sizeof(WPixel);
	// 获取Sprite文件信息
	m_MaxDirection = head.nDirection;

	m_Frame = head.nFrame;

	m_Width = head.nWidth;
	m_Height = head.nHeigh;

	m_kx = head.xCenter;
	m_ky = head.yCenter;
	// 总帧
	int numoffset = m_MaxDirection*m_Frame;
	// 创建帧偏移表数组
	FrameList = new ulong[numoffset];

	m_pDataOffsetList = new DATEHEARD[numoffset];
	// 获取帧偏移表
	for (i = 0; i < numoffset; i++)
		mread(&(FrameList[i]), 4, 1);

	lpDate = new lpBYTE[numoffset];// 获取图片数据指针的指针
	lpAlpha = new lpBYTE[numoffset];// 获取alpha数据指针的指针


	// 得到最大图片的大小
	for (i = 0; i < numoffset; i++)
	{
		DATEHEARD& datehead = m_pDataOffsetList[i];		// 帧数据头
		// 获取帧数据头
		if (FrameList[i] == 0) continue;
		mseek(FrameList[i] + 4 + head.szHheard);
		mread(&datehead, sizeof(DATEHEARD), 1);
		if (datehead.Height>m_Height)m_Height = datehead.Height;
		if (datehead.Width > m_Width)m_Width = datehead.Width;
	}
	pitch = ((m_Width << 1) + 7) & 0xfffffff8;
	int sizedata = pitch*m_Height + 7;
	int sizealpha = m_Width*m_Height;
	for (i = 0; i < numoffset; i++)			// 申请内存空间
	{
		if ((lpDate[i] = new uchar[sizedata]) == 0)
		{
			ERRBOX;
		}

		if ((lpAlpha[i] = new uchar[sizealpha]) == 0)
		{
			ERRBOX;
		}
		memset(lpAlpha[i], 0, m_Width*m_Height);
	}

	//临时数据缓冲
	uchar ckdate;	//测试字节
	uchar wdate;		//待写入字节索引
	uchar walpha;	//待写入alpha值
	unsigned int ran;//重复次数

	//	int fx, fy;		// 帧点坐标
	int r, g, b;

	//染色
	if (pChangeColorData)
	{
		for (int i = 0; i < pChangeColorData->partnum; i++)
		{
			sChangeColorMatrix*  matrix = &pChangeColorData->m_colormatrix[i];

			for (int j = matrix->m_start; j < matrix->m_end; j++)
			{
				WPixel& pal = Pal[j];
				r = pal.red*matrix->x1 + pal.green*matrix->x2 + pal.blue*matrix->x3;
				g = pal.red*matrix->y1 + pal.green*matrix->y2 + pal.blue*matrix->y3;
				b = pal.red*matrix->z1 + pal.green*matrix->z2 + pal.blue*matrix->z3;
				r = r >> 8;
				g = g >> 8;
				b = b >> 8;
				if (r > 31)    r = 31;
				if (g > 63) g = 63;
				if (b > 31)	 b = 31;
				pal.red = r;
				pal.green = g;
				pal.blue = b;
			}
		}
	}


	WPixel PIX;
	PIX = RGB(255, 255, 255);


	ushort* pD;
	uchar* pA;
	//uchar* pD1;
	// 读取帧数据
	for (i = 0; i < m_MaxDirection*m_Frame; i++)
	{
		// 获取帧数据头
		if (FrameList[i] == 0) continue;
		DATEHEARD& datehead = m_pDataOffsetList[i];		// 帧数据头
		mseek(FrameList[i] + 4 + head.szHheard);
		mread(&datehead, sizeof(DATEHEARD), 1);


		// 创建行偏移表数组
		LineList = new ulong[datehead.Height];
		// 取行偏移表
		for (j = 0; j < datehead.Height; j++)
			mread(&(LineList[j]), 4, 1);

		isgh = 1;
		for (int iy = 0; iy < datehead.Height; iy++)
		{
			pD = (ushort*)&lpDate[i][iy*pitch];
			pA = &lpAlpha[i][iy*m_Width];
			mseek(4 + head.szHheard + FrameList[i] + LineList[iy]);
			for (int ix = 0; ix < datehead.Width;)
			{
				mread(&ckdate, 1, 1);
				if (ckdate == 0)					//象素行结束  
				{
					break;
				}
				else if ((ckdate & 0xC0) == 0)		// 若Bit7-8=00
				{
					if (isgh)
					{
						if (iy % 2)
							isgh = 0;
					}
					if (ckdate & 0x20)				//若Bit6=1
					{
						walpha = (ckdate & 0x1f);	//Bit1-5
						mread(&wdate, 1, 1);		//获取下一字节
						if (walpha)
						{
							*pD = Pal[wdate].color;
							*pA = (walpha << 3) - 7;
						}
						++ix;
						++pD;
						++pA;
					}
					else
					{
						ran = (ckdate & 0x1f);
						mread(&walpha, 1, 1);
						mread(&wdate, 1, 1);

						if (walpha)
						{
							walpha = (walpha << 3) - 7;


							while (ran)
							{
								if (ix < m_Width)
								{
									*pD = Pal[wdate].color;
									*pA = walpha;
								}
								++ix;
								++pD;
								++pA;
								--ran;
							}
						}

					}
				}
				else if ((ckdate & 0xC0) == 0x40)	// 若Bit7-8=01
				{
					if (isgh)
					{
						if (iy % 2)
							isgh = 0;
					}
					ran = (ckdate & 0x3f);
					walpha = 255;
					while (ran)
					{
						mread(&wdate, 1, 1);
						if (ix < m_Width)
						{
							*pD = Pal[wdate].color;
							*pA = walpha;
						}
						++ix;
						++pD;
						++pA;
						--ran;
					}
				}
				else if ((ckdate & 0xC0) == 0x80)	// 若Bit7-8=10
				{
					if (isgh)
					{
						if (iy % 2)
							isgh = 0;
					}
					ran = (ckdate & 0x3f);
					walpha = 255;
					mread(&wdate, 1, 1);


					while (ran)
					{
						if (ix < m_Width)
						{
							*pD = Pal[wdate].color;
							*pA = walpha;
						}
						++ix;
						++pD;
						++pA;
						ran--;
					}
				}
				else							// 若Bit7-8=11
				{
					ran = (ckdate & 0x3f);
					if (0 == ran)
					{
						flp -= 1;
						*flp = 0x40;
						flp += 1;
						*flp = 0x40;
						flp += 1;
						*flp = 0x40;
						flp += 1;
						//flp += 2;
						//纯属干扰
					}
					else
					{
						ix += ran;
						pD += ran;
						pA += ran;
					}
				}
			}
		}
		if (isgh)
		{
			for (int iy = 0; iy < m_Height; iy += 2)
			{
				if (iy + 1 < m_Height)
				{
					memcpy(&lpDate[i][(iy + 1)*pitch], &lpDate[i][iy*pitch], m_Width << 1);
					memcpy(&lpAlpha[i][(iy + 1)*m_Width], &lpAlpha[i][iy*m_Width], m_Width);
				}
			}
		}
		delete[] LineList;
	}

	delete[] FrameList;
	mclose();

	m_bLoad = true;
	return true;
}

void CSprite::FreeDatelp(void)
{
	if (!m_bLoad)return;
	m_bLoad = false;
	SAFE_DELETE_ARRAY(m_pDataOffsetList);
	int i;
	if (lpAlpha)
	{
		for (i = 0; i < m_MaxDirection*m_Frame; i++)
		{
			SAFE_DELETE_ARRAY(lpAlpha[i]);
		}
		SAFE_DELETE_ARRAY(lpAlpha);

	}
	if (lpDate)
	{
		for (i = 0; i < m_MaxDirection*m_Frame; i++)
		{
			SAFE_DELETE_ARRAY(lpDate[i]);
		}
		SAFE_DELETE_ARRAY(lpDate);
	}
	m_MaxDirection = 0;
	m_Frame = 0;
	m_Height = 0;
	m_Width = 0;
	m_pOwner = 0;
}



HBITMAP CSprite::DIBtoDDB(ushort* data, BITMAPINFO*  pBmpInfo)
{


	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)pBmpInfo;
	HBITMAP hbm;
	HPALETTE Pal = 0;
	HPALETTE OldPal = 0;
	HDC dc = GetDC(g_hWnd);

	static int nColors; nColors = lpbi->biClrUsed ? lpbi->biClrUsed : 1 >> lpbi->biBitCount; //颜色表项的个数

	BITMAPINFO &bmInfo = *(LPBITMAPINFO)g_pBmpinfo;

	if (nColors <= 256 && GetDeviceCaps(dc, RASTERCAPS) & RC_PALETTE)
	{
		uint nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY)* nColors);
		LOGPALETTE *plp = (LOGPALETTE *) new uchar[nSize];
		plp->palVersion = 0x300;
		plp->palNumEntries = nColors;

		for (int i = 0; i < nColors; i++)
		{
			auto& p = plp->palPalEntry[i];
			const auto& b = bmInfo.bmiColors[i];
			p.peRed = b.rgbRed;
			p.peGreen = b.rgbGreen;
			p.peBlue = b.rgbBlue;
			p.peFlags = 0;
		}

		Pal = CreatePalette(plp);

		delete[] plp; //要及时处理

		// select and realize the palette
		OldPal = SelectPalette(dc, Pal, false);
		RealizePalette(dc);
	}


	hbm = CreateDIBitmap(
		dc, //设备上下文的句柄
		(LPBITMAPINFOHEADER)lpbi, //位图信息头指针
		(long)CBM_INIT, //初始化标志
		(void*)data,//lpDIBits, //初始化数据指针
		(LPBITMAPINFO)lpbi, //位图信息指针
		DIB_RGB_COLORS
		); //颜色数据的使用方式

	if (Pal)
	{
		SelectPalette(dc, OldPal, false);
	}

	return hbm;
}


void CSprite::mread(void* Dst, unsigned int size, unsigned int n)
{
	unsigned int ran = size*n;
	if (flp + ran - fstr > fsize)
	{
		flp = fstr + fsize;
		memset(Dst, 0, ran);
	}
	else
	{
		memcpy(Dst, flp, ran);
		flp += ran;
	}
}

void CSprite::mcreat(void* ilp, unsigned int size)
{
	flp = (uchar*)ilp;
	fstr = flp;
	fsize = size;
}

void CSprite::mseek(long offset)
{
	flp = fstr + offset;
}

void CSprite::mclose(void)
{
	flp = NULL;
	fstr = NULL;
}


bool CSprite::isInMask(int x, int y, int w, int h, int xMask, int yMask, int wMask, int hMask)
{
	if (y + h > yMask + hMask)return false;
	if (yMask > y + h)      return false;
	if (xMask > x + w)        return false;
	if (xMask + wMask < x)    return false;

	return true;
}

bool CSprite::ShowOnScreen(uchar* Pic, RECT& rect)
{
	if (!lpAlpha)return false;
	if (!lpDate) return false;
	//图像左上角相对于屏幕的位置
	int a = getFrameIdx();
	static int xScreenPos; xScreenPos = m_pOwner->m_x - m_pDataOffsetList[a].FramX;
	static int yScreenPos; yScreenPos = m_pOwner->m_y - m_pDataOffsetList[a].FramY;
	RECT  picrect;  //图片本身的大小
	RECT nowrect;  //图片真正显示的大小
	static int xOffset;
	static int yOffset;
	static int xOffset3;
	static int yOffset3;
	if (!CountCross(xScreenPos, yScreenPos, rect, picrect, nowrect,
		xOffset, yOffset, xOffset3, yOffset3))
		return false;
	//实际区域的大小
	static int Height; Height = nowrect.bottom - nowrect.top;
	static int Width; Width = nowrect.right - nowrect.left;
	//实际区域相对图片区域的偏移
	static WPixel pix1, *pix2;

	static uchar*  lpSrc; lpSrc = lpDate[a];
	static uchar*  pAlpha; pAlpha = lpAlpha[a];
	////////////////////////////////////////////////////////////////////////// 呵呵哒 又出现了
	if (!pAlpha)return false;
	//////////////////////////////////////////////////////////////////////////
	static int alpha;
	static int yof2; yof2 = yOffset + m_pOwner->m_yOffset2;
	static int xof2; xof2 = xOffset + m_pOwner->m_xOffset2;
	static int dealpha;

	static uchar* p1; p1 = &Pic[(yOffset3 << 6) + (xOffset3 << 1)];
	static uchar* p2; p2 = &lpSrc[yof2*pitch + ((xof2) << 1)];
	static uchar* pA; pA = &pAlpha[yof2*m_Width + xof2];
	int j2;
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			j2 = j << 1;
			alpha = pA[j];

			if (!alpha)continue;

			pix1 = *(WPixel *)&p2[j2];
		//	pix1.l = p2[j2];
		//	pix1.h = p2[j2 + 1];

			////半透明
			if (m_pOwner->m_bShadow)
			{
				alpha = (alpha*(100 - m_pOwner->m_bShadow)) / 100;
			}
			if (m_pOwner->m_bTwinkle) //闪烁  (金刚护法)
			{
				if (m_pOwner->now_frame % 3 == 0)
				{
					if (pix1.red > 24)
						pix1.red = 31;
					else
						pix1.red += 7;
					if (pix1.green > 49)
						pix1.green = 63;
					else
						pix1.green += 14;
					if (pix1.blue < 10)
						pix1.blue = 0;
					else
						pix1.blue -= 10;
				}
			}
			else
				if (m_pOwner->m_bShine)  //高亮  (角色被选中时会高亮)
				{
				if (pix1.red > 24)
					pix1.red = 31;
				else
					pix1.red += 7;
				if (pix1.green > 49)
					pix1.green = 63;
				else
					pix1.green += 14;
				if (pix1.blue > 24)
					pix1.blue = 31;
				else
					pix1.blue += 7;
				}
			if (alpha < 255)
			{
				pix2 = (WPixel*)&p1[j2];
			//	pix2.l = p1[j2];
			//	pix2.h = p1[j2 + 1];
				dealpha = 255 - alpha;
				pix2->red = (pix1.red *alpha + pix2->red *dealpha) >> 8;
				pix2->green = (pix1.green *alpha + pix2->green * dealpha) >> 8;
				pix2->blue = (pix1.blue *alpha + pix2->blue * dealpha) >> 8;
			//	p1[j2] = pix2.l;
			//	p1[j2 + 1] = pix2.h;
			}
			else
			{

				p1[j2] = pix1.l;
				p1[j2 + 1] = pix1.h;
			}
		}
		p1 += 64;
		p2 += pitch;
		pA += m_Width;
	}
	return true;
}

struct sMASKRect;
bool CSprite::Show(uchar* Pic, RECT& rect, cMyMap* pMap)
{
	if (0 == lpAlpha)return false;
	cMap*& pMap2 = pMap->m_pMap;
	static int xMapCenter; xMapCenter = pMap2->GetXCenter();
	static int yMapCenter; yMapCenter = pMap2->GetYCenter();
	static int a; a = getFrameIdx();
	//图像左上角相对于屏幕的位置
	static int xScreenPos; xScreenPos = m_pOwner->m_x - m_pDataOffsetList[a].FramX - xMapCenter + g_half320;
	static int yScreenPos; yScreenPos = m_pOwner->m_y - m_pDataOffsetList[a].FramY - yMapCenter + g_half240 - m_pOwner->m_yOffset;

	static RECT  picrect;  //图片本身的大小
	static RECT nowrect;  //图片真正显示的大小
	static int xOffset;
	static int yOffset;
	static int xOffset3;
	static int yOffset3;
	if (!CountCross(xScreenPos, yScreenPos, rect, picrect, nowrect,
		xOffset, yOffset, xOffset3, yOffset3))
		return false;
	//实际区域的大小
	static int Height; Height = nowrect.bottom - nowrect.top;
	static int Width; Width = nowrect.right - nowrect.left;


	//	//检测是否在建筑后
	static bool  bCross; bCross = 0;
	static int InH;
	static int InW;
	static int  xOffmask;
	static int  yOffmask;
	static int  xOffPic;
	static int  yOffPic;

	static int xnowrectoffset, ynowrectoffset;

	static RECT rectmask; //建筑的大小
	static RECT rectcross; //图片显示区和建筑重叠的大小
	static int nummask;
	//得到相交的矩形
	if (g_StateType == STATE_MAIN)
	{
		static sMASKRect* pMaskRect;
		////////////////////////////////////////////////////////////////////////// 呵呵哒 地图相关
		memset(g_pMainState->m_MaskList, 0, sizeof(char) * 1024);
		static int i; i = 0;
		nummask = pMap2->m_MaskIDList.size();
		for (int j = 0; j < nummask; j++)
		{
			i = pMap2->m_MaskIDList[j];
			pMaskRect = &pMap2->m_pMaskRect[i];
			rectmask.left = pMaskRect->x - pMap2->GetXCenter() + g_half320;
			rectmask.top = pMaskRect->y - pMap2->GetYCenter() + g_half240;
			rectmask.right = rectmask.left + pMaskRect->w;
			rectmask.bottom = rectmask.top + pMaskRect->h;

			if (m_Bottom != -1)
			{
				if (pMaskRect->y + pMaskRect->h < m_Bottom)
					continue;
			}
			if (rectmask.left > g_640)continue;
			if (rectmask.right < 0)continue;
			if (rectmask.top > g_480)continue;
			if (rectmask.bottom < 0)continue;

			if (!CheckCross(picrect, rectmask, rectcross))continue;
			bCross = true;

			xnowrectoffset = rectcross.left - rect.left;
			ynowrectoffset = rectcross.top - rect.top;
			InH = rectcross.bottom - rectcross.top;
			InW = rectcross.right - rectcross.left;
			xOffmask = rectcross.left - rectmask.left;
			yOffmask = rectcross.top - rectmask.top;
			xOffPic = rectcross.left - picrect.left;
			yOffPic = rectcross.top - picrect.top;
			// 读mask信息

			uchar*& pMaskDataDec = pMap2->m_pMaskDataDec[i];

			int& align_width = pMap2->m_align_width[i];
			// 读mask数据
			if (0 == align_width)
			{
// 				auto m = pMap2->_reader->readMask(j, false);
// 				pMaskDataDec = (uchar*)m.masks;
// 				align_width = m.w;

				SMaskInfo maskInfo = { 0 };
				pMap2->m_File2.seekg(pMap2->m_pMaskDataOffset[i], ios::beg);
				pMap2->m_File2.read((char*)&maskInfo, sizeof(SMaskInfo));
				align_width = ((maskInfo.width >> 2) + (maskInfo.width % 4 != 0)) << 2;	// 以4对齐的宽度
				uchar* pMaskData = 0;
				pMaskData = new uchar[maskInfo.mask_size];
				pMap2->m_File2.read((char*)pMaskData, maskInfo.mask_size);
				// 解密mask数据
				pMaskDataDec = new uchar[(align_width * maskInfo.height) >> 2];		// 1个字节4个像素，故要除以4
				pMap2->DecompressMask(pMaskData, pMaskDataDec);
				SAFE_DELETE_ARRAY(pMaskData);
			}

			bool* bs = (bool*)pMaskDataDec;
 			static int mask_index;
 			uchar mask_value;
			for (int i2 = 0; i2 < InH; i2++)
			{
				for (int j2 = 0; j2 < InW; j2++)
				{
// 					if (bs[j2 * align_width + i2])
// 					{
// 						g_pMainState->m_MaskList[j2 + xnowrectoffset + ((i2 + ynowrectoffset) << 5)] = true;
// 					}
						
					mask_index = ((i2 + yOffmask) * align_width + j2 + xOffmask) << 1;		// 单位:位
					if (mask_index < 0)
					{
						ERRBOX;
					}
					mask_value = pMaskDataDec[mask_index >> 3];	// 定位到字节
					mask_value = mask_value >> (mask_index % 8);	// 定位到位
					if ((mask_value & 3) == 3)
					{
						g_pMainState->m_MaskList[j2 + xnowrectoffset + ((i2 + ynowrectoffset) << 5)] = true;
					}
				}
			}
		}
	}
	static WPixel pix1, *pix2;
	static int index, index2, index11, index22;
	static uchar*  lpSrc; lpSrc = lpDate[a];
	static uchar*  pAlpha; pAlpha = lpAlpha[a];

	static int alpha;

	static int indexx, indexy, unalpha;
	indexy = yOffset + m_pOwner->m_yOffset2;
	indexx = xOffset + m_pOwner->m_xOffset2;

	index11 = indexy*pitch + (indexx << 1);
	index = index11;
	index22 = (yOffset3 << 6) + (xOffset3 << 1);
	index2 = index22;

	static uchar* pA; pA = &pAlpha[indexy*m_Width + indexx];
	static uchar* P1; P1 = &lpSrc[indexy*pitch + (indexx << 1)];
	static uchar* P2; P2 = &Pic[(yOffset3 << 6) + (xOffset3 << 1)];
	static int j2;
	for (int i2 = 0; i2 < Height; i2++)
	{
		for (int j = 0; j < Width; j++)
		{
			j2 = j << 1;
			alpha = pA[j];
			if (!alpha)continue;

			pix1.l = P1[j2];
			pix1.h = P1[j2 + 1];

			if (m_pOwner->m_bTwinkle) //闪烁  (金刚护法)
			{
				if (m_pOwner->now_frame % 3 == 0)
				{
					if (pix1.red > 24)
						pix1.red = 31;
					else
						pix1.red += 7;
					if (pix1.green > 49)
						pix1.green = 63;
					else
						pix1.green += 14;
					if (pix1.blue < 10)
						pix1.blue = 0;
					else
						pix1.blue -= 10;
				}
			}
			else
				if (m_pOwner->m_bShine)  //高亮  (角色被选中时会高亮)
				{
				if (pix1.red > 24)
					pix1.red = 31;
				else
					pix1.red += 7;
				if (pix1.green > 49)
					pix1.green = 63;
				else
					pix1.green += 14;
				if (pix1.blue > 24)
					pix1.blue = 31;
				else
					pix1.blue += 7;
				}
			if (m_pOwner->m_bShadow)
			{
				alpha = (alpha*(100 - m_pOwner->m_bShadow)) / 100; //半透明
			}
			if (bCross)
			{
				if (g_pMainState->m_MaskList[j + xOffset3 + ((i2 + yOffset3) << 5)])
				{
					if (8 == m_MaxDirection)
					{
						alpha = alpha >> 1;
					}
					else  alpha = 0;
				}
			}
			if (alpha < 255)
			{
				pix2 = (WPixel*)&P2[j2];
			//	pix2.l = P2[j2];
			//	pix2.h = P2[j2 + 1];

				unalpha = 255 - alpha;
				pix2->red = (pix1.red *alpha + unalpha* pix2->red) >> 8;
				pix2->green = (pix1.green *alpha + unalpha*pix2->green) >> 8;
				pix2->blue = (pix1.blue *alpha + unalpha*pix2->blue) >> 8;
			//	P2[j2] = pix2.l;
			//	P2[j2 + 1] = pix2.h;
			}
			else
			{
				P2[j2] = pix1.l;
				P2[j2 + 1] = pix1.h;
			}
		}
		pA += m_Width;
		P2 += 64;
		P1 += pitch;
	}
	return true;
}



bool CSprite::CountCross(int xPos, int yPos, RECT destrect, RECT& picrectout, RECT& nowrectout, int& xOffPic, int& yOffPic, int& xOffDes, int& yOffDes)
{
	picrectout.left = (xPos > destrect.left ? xPos : destrect.left);
	picrectout.top = (yPos > destrect.top ? yPos : destrect.top);
	if (m_pOwner->m_ShowWidth)picrectout.right = xPos + m_pOwner->m_ShowWidth;
	else  picrectout.right = xPos + m_Width;
	if (m_pOwner->m_ShowHeight)picrectout.bottom = yPos + m_pOwner->m_ShowHeight;
	else  picrectout.bottom = yPos + m_Height;
	if (destrect.right < picrectout.right)picrectout.right = destrect.right;
	if (destrect.bottom < picrectout.bottom)picrectout.bottom = destrect.bottom;

	if (!CheckCross(picrectout, destrect, nowrectout))return false;
	xOffPic = nowrectout.left - xPos;
	yOffPic = nowrectout.top - yPos;
	//实际区域相对目标区域的偏移
	xOffDes = nowrectout.left - destrect.left;
	yOffDes = nowrectout.top - destrect.top;
	return true;
}



bool CSprite::LoadBMP(string path)
{
	FreeDatelp();
	m_MaxDirection = 1;
	m_Frame = 1;
	m_kx = 0;
	m_ky = 0;

	ifstream File;
	File.open(path, ios::binary);
	if (!File)
		ERRBOX;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER m_BmpInfoHead;
	int m_nBitCount;

	File.read((char*)&bmfh, sizeof(BITMAPFILEHEADER));
	File.seekg(sizeof(BITMAPFILEHEADER));
	File.read((char*)&m_BmpInfoHead, sizeof(BITMAPINFOHEADER));
	m_Width = m_BmpInfoHead.biWidth;
	m_Height = m_BmpInfoHead.biHeight;
	m_nBitCount = m_BmpInfoHead.biBitCount;


	if (m_nBitCount < 16)ERRBOX;
	pitch = ((m_Width << 1) + 7) & 0xfffffff8;
	int size = (m_Width*m_Height*m_nBitCount) >> 3;
	uchar* data = new uchar[size + m_Width];
	lpDate = new unsigned char*[m_MaxDirection*m_Frame];
	lpAlpha = new unsigned char*[m_MaxDirection*m_Frame];
	(lpDate[0]) = new uchar[pitch*m_Height + 7];
	(lpAlpha[0]) = new uchar[m_Width*m_Height];


	File.seekg(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
	File.read((char*)data, size);

	memset(lpAlpha[0], 255, m_Width*m_Height);


	m_pDataOffsetList = new DATEHEARD;
	m_pDataOffsetList->FramX = 0;
	m_pDataOffsetList->FramY = 0;
	m_pDataOffsetList->Height = m_Height;
	m_pDataOffsetList->Width = m_Width;
	WPixel pix;
	switch (m_nBitCount)
	{
	case 16:
		ERRBOX;
		break;
	case 24:
		if (1)
		{
			int index = 0;
			int index2 = (m_Height - 1)*pitch;
			for (int h = 0; h < m_Height; h++)
			{
				for (int w = 0; w < m_Width; w++)
				{
					pix.red = (data[index + 2] >> 3) & 0x1f;
					pix.green = ((data[index + 1] >> 3) & 0x1f) << 1;
					pix.blue = (data[index] >> 3) & 0x1f;
					(lpDate[0])[index2] = pix.l;
					(lpDate[0])[index2 + 1] = pix.h;
					index += 3;
					index2 += 2;
				}
				index2 -= pitch << 1;
			}
		}
		break;
	default:
		ERRBOX;
		break;
	}
	SAFE_DELETE_ARRAY(data);
	m_bLoad = true;
	return true;
}

