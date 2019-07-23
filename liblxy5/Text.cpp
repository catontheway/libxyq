#include "_global.h"


cText::cText()
{
	m_PreShowRect.right = -1;
	m_NeedShow = true;
}

bool cText::DrawAlphaEx(uchar* Pic, RECT& rect, cMap* pMap)
{
//	static RECT rect; rect = rect0;
	if (m_time > 0)
	{
		m_time -= 1;
		if (!m_time)
			m_NeedShow = false;
	}
	if (0 == m_Width)return true;
	static int xtrue; xtrue = m_x;
	static int ytrue; ytrue = m_y;
	////////////////////////////////////////////////////////////////////////// 呵呵哒 地图相关
	if (!m_bShowOnScreen)
	{
		xtrue -= pMap->GetXCenter() - g_half320;
		ytrue -= pMap->GetYCenter() - g_half240;
	}
	if ((xtrue + GetShowWidth()) < 0 ||
		xtrue > g_640 ||
		ytrue > g_480 ||
		ytrue + GetShowHeight() < 0)
		return true;

	static RECT picrect;  //图片本身的大小

	picrect.left = xtrue;
	picrect.top = ytrue;
	picrect.right = picrect.left + GetShowWidth();
	picrect.bottom = picrect.top + GetShowHeight();
	static RECT nowrect;  //图片真正显示的大小
	if (!CheckCross(picrect, rect, nowrect))return true;
	static string str3; str3 = m_Text;
	static WPixel *pix1, *pix2;
	static int index, index2, index11, index22, alphai, alphai2;
	//实际区域的大小
	static int Height; Height = nowrect.bottom - nowrect.top;
	static int Width; Width = nowrect.right - nowrect.left;
	//实际区域相对图片区域的偏移
	static int xOffset; xOffset = nowrect.left - picrect.left;// picrect.left;
	static int yOffset; yOffset = nowrect.top - picrect.top;// picrect.top;

	//实际区域相对目标区域的偏移
	static int xOffset3; xOffset3 = nowrect.left - rect.left;
	static int yOffset3; yOffset3 = nowrect.top - rect.top;

	uchar*&  lpSrc = m_pData;
	uchar*&  pAlpha = m_pAlpha;

	static int /*alpha, */unalpha;

	static int alphaoffy; alphaoffy = yOffset + m_yOffset2;
	static int alphaoffx; alphaoffx = xOffset + m_xOffset2;
	static int widthpic; widthpic = rect.right - rect.left;

	alphai2 = alphaoffy * m_Width + alphaoffx;
	alphai = alphai2;
	index11 = alphai2 << 1;
	index = index11;
	index22 = (yOffset3 * widthpic + xOffset3) << 1;
	index2 = index22;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			const auto& alpha = pAlpha[alphai];
			alphai += 1;
			if (!alpha)
			{
				index += 2;
				index2 += 2;
				continue;
			}

			if (alpha < 255)
			{
				pix1 = (WPixel *)&lpSrc[index];
			//	pix1.l = lpSrc[index];
			//	pix1.h = lpSrc[index + 1];
				pix2 = (WPixel *)&Pic[index2];
			//	pix2.l = Pic[index2];
			//	pix2.h = Pic[index2 + 1];

				unalpha = 255 - alpha;
				pix2->red = (pix1->red *alpha + pix2->red * unalpha) >> 8;
				pix2->green = (pix1->green *alpha + pix2->green * unalpha) >> 8;
				pix2->blue = (pix1->blue *alpha + pix2->blue * unalpha) >> 8;
			//	*(ushort*)Pic[index2] = *(ushort*)pix2;
			//	Pic[index2] = pix2.l;
			//	Pic[index2 + 1] = pix2.h;
			}
			else
			{
			//	pix1 = (WPixel *)&lpSrc[index];
			//	pix1.l = lpSrc[index];
			//	pix1.h = lpSrc[index + 1];
			//	*(ushort*)Pic[index2] = *(ushort*)pix1;
				Pic[index2] = lpSrc[index]; // pix1->l;
				Pic[index2 + 1] = lpSrc[index + 1]; // pix1->h;
			}
			index += 2;
			index2 += 2;
		}
		index11 += m_Width << 1;
		index = index11;
		index22 += widthpic << 1;
		index2 = index22;
		alphai2 += m_Width;
		alphai = alphai2;
	}
	return true;
}
void cText::UpdateData()
{
	//ulong oldcolor = 0;
	HFONT oldFont = 0;
	if (m_hFont)
	{
		oldFont = (HFONT)SelectObject(g_DC2, m_hFont);//err
	}
	SIZE size1;
	CountSize(size1);
	if (0 != m_Style)
	{
		size1.cx += 2;
		size1.cy += 2;
	}
	m_tuewidth = size1.cx;
	m_Width = size1.cx;
	m_Height = size1.cy;



	m_Width = ((m_Width * 2 + 7) & 0xfffffff8) / 2;



	RECT rect2;
	rect2.left = 0;
	rect2.top = 0;
	rect2.right = m_Width;
	rect2.bottom = m_Height;



	HBITMAP hBitmap = CreateCompatibleBitmap(g_ShowDC, m_Width, m_Height + 1);
	HBITMAP oldmap = (HBITMAP)SelectObject(g_DC2, hBitmap);
	//计算图片大小

	m_Size = m_Height*m_Width;
	if (m_Size > m_MemSize)
	{
		m_MemSize = m_Size;
		SAFE_DELETE_ARRAY(m_pData);
		SAFE_DELETE_ARRAY(m_pAlpha);
		m_pData = new uchar[m_MemSize << 1];
		m_pAlpha = new uchar[m_MemSize];
	}
	g_pBmpinfo->bmiHeader.biCompression = 0;
	g_pBmpinfo->bmiHeader.biWidth = m_Width;
	g_pBmpinfo->bmiHeader.biHeight = -m_Height;
	g_pBmpinfo->bmiHeader.biSizeImage = m_Size << 1;
	//
	WPixel pix, pix2;
	//跟据文字颜色,选择背景颜色
	pix2 = m_color;
	FillRect(g_DC2, &rect2, g_blackbrush);

	DrawTextA(
		g_DC2,
		m_Text.c_str(),
		-1,
		&rect2,
		DT_LEFT | DT_WORDBREAK
		);
	GetDIBits(g_DC2, hBitmap, 0, m_Height, m_pData, g_pBmpinfo, DIB_RGB_COLORS);
	int index;
	ushort* color, *color2;
	index = 0;
	for (int kk = 0; kk < m_Height; kk++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			color = (ushort*)&m_pData[index << 1];
			pix = *color;
			if (0 == (*color))
			{
				m_pAlpha[index] = 0;
			}
			else
				if ((*color) > 32766)
				{
				m_pAlpha[index] = 255;
				*color = pix2.color;
				}
				else
				{
					m_pAlpha[index] = (uchar)pix.red << 3;
					*color = pix2.color;
				}
			index += 1;
		}
	}
	if (m_Style) //文字的阴影
	{
		pix2 = m_BacColor;
		if (m_Size > m_MemSize2)
		{
			m_MemSize2 = m_Size;
			SAFE_DELETE_ARRAY(m_pData2);
			m_pData2 = new uchar[m_MemSize2 << 1];
		}
		FillRect(g_DC2, &rect2, g_blackbrush);

		if (m_Style == 1)
		{
			rect2.left += 1;
			rect2.top += 1;
			rect2.bottom += 1;
			rect2.right += 1;
			DrawTextA(
				g_DC2,
				m_Text.c_str(),
				-1,
				&rect2,
				DT_LEFT | DT_WORDBREAK
				);
		}
		else
		{
			//选择画笔  用来描边
			if (m_bBold)
				SelectObject(g_DC2, g_BWhitePen);
			//描边
			BeginPath(g_DC2);
			TextOutA(g_DC2, rect2.left, rect2.top, m_Text.c_str(), m_Text.size());
			EndPath(g_DC2);
			StrokePath(g_DC2);
			if (m_bBold)
				SelectObject(g_DC2, g_WhitePen);
		}
		GetDIBits(g_DC2, hBitmap, 0, m_Height, m_pData2, g_pBmpinfo, DIB_RGB_COLORS);

		int oldindex = 0;
		index = 0;
		for (int kk = 0; kk < m_Height; kk++)
		{
			for (int j = 0; j < m_Width; j++)
			{
				color = (ushort*)&m_pData2[index << 1];
				if ((*color) == 0)
				{
					index += 1;
					continue;
				}
				else
				{

					if (m_pAlpha[index])
					{
						index += 1;
						continue;
					}
					color2 = (ushort*)&m_pData[index << 1];
					*color2 = pix2.color;
					m_pAlpha[index] = 255;

				}
				index += 1;
			}
			oldindex += m_Width;
			index = oldindex;
		}
	}
	// SelectFont(g_DC2, oldFont);
	SelectObject(g_DC2, (HGDIOBJ)oldFont);
	SelectObject(g_DC2, oldmap);
	DeleteObject(hBitmap);
	if (m_xCenter)
	{
		UpdateXCenter();
	}
}



void cText::SetString(char* str)
{
	string str2 = str;
	SetString(str2);
}



void cText::SetString(string str)
{
	if (0 == str.compare(m_Text))return;
	m_bMove = true;
	m_Text = str;
	SetxOffset(0);
	SetyOffset(0);
	SetxOffset2(0);
	SetyOffset2(0);
	m_ShowWidth = 0;
	m_ShowHeight = 0;
	UpdateData();
}

void cText::SetString(string str, ulong color)
{
	m_color = color;
	m_bMove = true;
	m_Text = str;
	UpdateData();
}

void cText::SetString(int str)
{
	ostringstream oss;
	oss << str;
	SetString(oss.str());
}
void cText::SetString(INT64 str)
{
	ostringstream oss;
	oss << str;
	SetString(oss.str());
}
cText::~cText()
{
	SAFE_DELETE_ARRAY(m_pData);
	SAFE_DELETE_ARRAY(m_pData2);
	SAFE_DELETE_ARRAY(m_pAlpha);
}

void cText::CountSize(SIZE& size)
{
	if (m_MaxWidth)
	{
		GetTextExtentPoint32A(g_DC2, m_Text.c_str(), m_Text.size(), &size);


		RECT rect;
		rect.left = 0;
		rect.top = 0;
		if (size.cx <= m_MaxWidth)
			rect.right = size.cx;
		else
			rect.right = m_MaxWidth;
		rect.bottom = 300;
		size.cy = DrawTextA(g_DC2, m_Text.c_str(), -1, &rect, DT_CALCRECT | DT_LEFT | DT_WORDBREAK);//| DT_EDITCONTROL);

		if (size.cx > m_MaxWidth)
			size.cx = m_MaxWidth;
	}
	else
	{
		GetTextExtentPoint32A(g_DC2, m_Text.c_str(), m_Text.size(), &size);
	}
}

void cText::SetColor(ulong newcolor)
{
	if (m_color == newcolor)return;
	if (!m_Size)
	{
		m_color = newcolor;
		return;
	}
	m_bMove = true;
	if (m_Style && m_BacColor == m_color)
	{
		m_color = newcolor;
		UpdateData();
	}
	else
	{
		ChangeColor(m_color, newcolor);
		m_color = newcolor;
	}

}
void cText::SetBackColor(ulong color)
{
	if (m_BacColor == color)return;
	if (!m_Size)
	{
		m_BacColor = color;
		return;
	}
	m_bMove = true;
	if (m_BacColor == m_color)
	{
		UpdateData();
		m_BacColor = color;
	}
	else
	{

		ChangeColor(m_BacColor, color);
		m_BacColor = color;
	}

}
//改变颜色
void cText::ChangeColor(ulong originalcolor, ulong outcolor)
{
	int index = 0;
	WPixel color;
	WPixel original;
	original = originalcolor;
	WPixel out;
	out = outcolor;
	for (int kk = 0; kk < m_Height; kk++)
	{
		for (int j = 0; j < m_Width; j++)
		{
			if (m_pAlpha[index])
			{
				color.l = m_pData[index << 1];
				color.h = m_pData[(index << 1) + 1];
				if (color.color == original.color)
				{
					m_pData[index << 1] = out.l;
					m_pData[(index << 1) + 1] = out.h;
				}

			}
			index += 1;
		}
	}
	m_bMove = true;
}

void cText::SetTagColor(int starttag, int endtag, ulong color)
{
	int k;
	WPixel pix;
	pix = color;
	if (starttag < 0)starttag = 0;
	if (endtag < 0)endtag = m_Width;
	for (int j = 0; j < m_Height; j++)
		for (int i = starttag; i < endtag; i++)
		{
		k = i + m_Width*j;
		if (m_pAlpha[k])
		{
			k *= 2;
			m_pData[k] = pix.l;
			m_pData[k + 1] = pix.h;
		}
		}
}

void cText::SetTransparentColor(int startpos, int endpos, ulong color)
{
	if (endpos < startpos)swap(endpos, startpos);
	int k;
	WPixel pix;
	pix = color;
	if (startpos < 0)startpos = 0;
	if (endpos < 0)endpos = m_Width;
	for (int j = 0; j < m_Height; j++)
		for (int i = startpos; i < endpos; i++)
		{
		k = i + m_Width*j;
		if (!m_pAlpha[k])
		{
			m_pData[k * 2] = pix.l;
			m_pData[k * 2 + 1] = pix.h;
			m_pAlpha[k] = 255;
		}
		}

}

void cText::UnTransparentColor(int startpos, int endpos, ulong transparentcolor)
{
	if (endpos < startpos)swap(endpos, startpos);
	int k;
	WPixel pix, targetpix;
	targetpix = transparentcolor;
	if (startpos < 0)startpos = 0;
	if (endpos < 0)endpos = m_Width;
	for (int j = 0; j < m_Height; j++)
		for (int i = startpos; i < endpos; i++)
		{
		k = i + m_Width*j;
		pix.l = m_pData[k * 2];
		pix.h = m_pData[k * 2 + 1];
		if (pix.color == targetpix.color)
		{
			m_pAlpha[k] = 0;
		}
		}
}

void cText::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return;
	if (m_time > 0)
	{
		m_time -= 1;
		if (!m_time)
		{
			m_NeedShow = false;
			return;
		}
	}
	pCanvas->Add(this);
}

