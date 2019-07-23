#include "_global.h"

void cObjWasFather::SetShowWidth(int k)
{
	if (k > m_Width - m_xOffset2)
		k = m_Width - m_xOffset2;
	SetxOffset(m_Width - k);
}

void cObjWasFather::SetShowHeight(int k)
{
	if (k + m_yOffset2 > m_Height)
		k = m_Height - m_yOffset2;
	SetyOffset(m_Height - k);
}

void cObjWasFather::Init(cObjWasFather* pObj, int alpha)
{
	if (!pObj)return;
	m_x = pObj->m_x;
	m_y = pObj->m_y;
	m_Width = pObj->GetShowWidth();
	m_Height = pObj->GetShowHeight();
	m_ShowHeight = 0;
	m_ShowWidth = 0;
	m_xOffset = 0;
	m_xOffset2 = 0;
	m_yOffset = 0;
	m_yOffset2 = 0;
	int size = m_Width * m_Height;
	if (m_OldDataSize < size)
	{
		m_OldDataSize = size;
		SAFE_DELETE_ARRAY(m_pData);
		SAFE_DELETE_ARRAY(m_pAlpha);
		m_pAlpha = new uchar[size];
		m_pData = new uchar[size << 1];
	}
}

cObjWasFather::~cObjWasFather()
{
	SAFE_DELETE_ARRAY(m_pData);
	SAFE_DELETE_ARRAY(m_pAlpha);
}

void cObjWasFather::Draw(cObjWasFather* pObj, int xpos, int ypos, int alpha)
{
	static RECT rect1, rect2;
	GetRect(rect1);
	if (xpos == -1)
	{
		pObj->GetRect(rect2);
	}
	else
	{
		rect2.left = xpos;
		rect2.top = ypos;
		rect2.right = rect2.left + pObj->GetShowWidth();
		rect2.bottom = rect2.top + pObj->GetShowHeight();
	}
	static RECT nowrect;  //两张图交错部分的大小
	if (!CheckCross(rect1, rect2, nowrect))
	{
		return;
	}
	//实际区域的大小
	static int Height; Height = nowrect.bottom - nowrect.top;
	static int Width; Width = nowrect.right - nowrect.left;
	//实际区域相对图片区域的偏移
	static int xOffset1; xOffset1 = nowrect.left - rect1.left;
	static int yOffset1; yOffset1 = nowrect.top - rect1.top;
	static int xOffset2; xOffset2 = nowrect.left - rect2.left;
	static int yOffset2; yOffset2 = nowrect.top - rect2.top;
	static WPixel *pix1, *pix2;
	static int index1, index2, index11, index22, alpha1, alpha11;
	static uchar  alpha2;


	index11 = ((yOffset1 + m_yOffset2)*m_Width + (xOffset1 + m_xOffset2)) << 1;
	alpha11 = ((yOffset2 + pObj->m_yOffset2)*pObj->m_Width + (xOffset2 + pObj->m_xOffset2));
	index22 = alpha11 << 1;
	index1 = index11;
	index2 = index22;
	alpha1 = alpha11;
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			alpha2 = pObj->m_pAlpha[alpha1];
			if (alpha < 100)
			{
				alpha2 = (alpha1*alpha) / 100;
			}
			alpha1 += 1;
			if (!alpha2)
			{
				index1 += 2;
				index2 += 2;
				continue;
			}
			if (alpha2 < 255)
			{
				pix1 = (WPixel *)&m_pData[index1];
				pix2 = (WPixel *)&pObj->m_pData[index2];

				pix1->red = (pix2->red *alpha2 + pix1->red * (255 - alpha2)) >> 8;
				pix1->green = (pix2->green *alpha2 + pix1->green * (255 - alpha2)) >> 8;
				pix1->blue = (pix2->blue *alpha2 + pix1->blue * (255 - alpha2)) >> 8;

			//	pix1.l = m_pData[index1];
			//	pix1.h = m_pData[(index1)+1];
			//	pix2.l = pObj->m_pData[index2];
			//	pix2.h = pObj->m_pData[(index2)+1];
			//	pix2.red = (pix2.red *alpha2 + pix1.red * (255 - alpha2)) >> 8;
			//	pix2.green = (pix2.green *alpha2 + pix1.green * (255 - alpha2)) >> 8;
			//	pix2.blue = (pix2.blue *alpha2 + pix1.blue * (255 - alpha2)) >> 8;
			//	m_pData[index1] = pix2.l;
			//	m_pData[index1 + 1] = pix2.h;
			}
			else
			{

			//	pix2.l = pObj->m_pData[index2];
			//	pix2.h = pObj->m_pData[(index2)+1];
				m_pData[index1] = pObj->m_pData[index2]; // pix2.l;
				m_pData[index1 + 1] = pObj->m_pData[(index2)+1]; // pix2.h;
			}
			if (m_pAlpha)
			{
				static uchar alpha1 = m_pAlpha[index1];
				if (alpha1 < 255)
				{
					alpha1 += alpha2;
					if (alpha1 > 255)alpha1 = 255;
					m_pAlpha[index1 >> 1] = alpha1;
				}
			}
			index1 += 2;
			index2 += 2;

		}
		index11 += m_Width << 1;
		index22 += pObj->m_Width << 1;
		index1 = index11;
		index2 = index22;
		alpha11 += pObj->m_Width;
		alpha1 = alpha11;
	}
}

void cObjWasFather::GetRect(RECT& rect1)
{
	rect1.left = m_x;
	rect1.right = rect1.left + GetShowWidth();
	rect1.top = m_y;
	rect1.bottom = rect1.top + GetShowHeight();
}

void cObjWasFather::Reset(cObjWasFather* pObj, int alpha /*= 100*/)
{
	int wid = GetShowWidth();
	int hei = GetShowHeight();
	int index11, index21;

	for (int i = 0; i < wid; i++)
		for (int j = 0; j < hei; j++)
		{
		index11 = i + m_xOffset2 + (j + m_yOffset2) *m_Width;
		index21 = i + pObj->m_xOffset2 + (j + m_yOffset2)*pObj->m_Width;

		if (alpha == 100)
			m_pAlpha[index11] = pObj->m_pAlpha[index11];
		else
			m_pAlpha[index11] = (pObj->m_pAlpha[index11] * alpha) / 100;

		index11 = index11 << 1;
		index21 = index21 << 1;
		m_pData[index11] = pObj->m_pData[index21];
		m_pData[index11 + 1] = pObj->m_pData[index21 + 1];



		}
}

void cObjWasFather::Reset2(cWasFile* pic)
{
	int index11, index21;
	int wid = GetShowWidth();
	int hei = GetShowHeight();
	if (!pic)
	{
		for (int i = 0; i < wid; i++)
			for (int j = 0; j < hei; j++)
			{
			index11 = i + m_xOffset2 + (j + m_yOffset2) *m_Width;
			m_pAlpha[index11] = 255;
			index11 = index11 << 1;
			m_pData[index11] = 0;
			m_pData[index11 + 1] = 0;
			}
		return;
	}
	cObjWasFather* pObj = &pic->m_Picture;

	uchar* pData = pic->m_Picture.Spr.lpDate[0];
	uchar* pAlpha = pic->m_Picture.Spr.lpAlpha[0];
	int pitch2 = ((pic->GetWidth() << 1) + 7) & 0xfffffff8;
	for (int i = 0; i < wid; i++)
		for (int j = 0; j < hei; j++)
		{
		index11 = i + m_xOffset2 + (j + m_yOffset2) *m_Width;
		index21 = i + pObj->m_xOffset2 + (j + m_yOffset2)*pObj->m_Width;
		m_pAlpha[index11] = pAlpha[index21];
		index11 = index11 << 1;
		index21 = ((i + pObj->m_xOffset2) << 1) + (j + m_yOffset2)*pitch2;
		m_pData[index11] = pData[index21];
		m_pData[index11 + 1] = pData[index21 + 1];
		}
}

void cObjWasFather::SetxOffset2(int xOff2)
{
	m_xOffset2 = xOff2;
	if (m_ShowWidth)
	{
		m_xOffset = m_Width - m_ShowWidth - m_xOffset2;
		if (m_xOffset < 0)
		{
			m_ShowWidth += m_xOffset;
			m_xOffset = 0;
		}
	}
	else
	{
		m_ShowWidth = m_Width - m_xOffset2;
	}

}
void cObjWasFather::SetyOffset2(int yOff2)
{
	m_yOffset2 = yOff2;
	if (m_ShowHeight)
	{
		m_yOffset = m_Height - m_ShowHeight - m_yOffset2;
		if (m_yOffset < 0)
		{
			m_ShowHeight += m_yOffset;
			m_yOffset = 0;
		}
	}
	else
	{
		m_ShowHeight = m_Height - m_yOffset2;
	}
}
void cObjWasFather::SetyOffset(int yOff)
{
	m_yOffset = yOff;
	m_ShowHeight = m_Height - m_yOffset;
	if (m_ShowHeight < 0)m_ShowHeight = 0;
}
void cObjWasFather::SetxOffset(int xOff)
{
	m_xOffset = xOff;
	m_ShowWidth = m_Width - m_xOffset;
	if (m_ShowWidth < 0)m_ShowWidth = 0;
}
