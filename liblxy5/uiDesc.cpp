#include "_global.h"


void cDescribe::Set(int xMouse, int yMouse, ulong BigHead, int num, string* pTex, ulong* colorlist, int yOffset)
{
	const int wid = 160;
	m_Num = num;
	//确定宽度
	m_BigHead.Load(BigHead);
	m_Back.SetShowWidth(m_BigHead.m_Picture.m_Width + wid + 3);
	//确定高度
	int a = m_BigHead.m_Picture.getFrameIdx();
	int& xOf = m_BigHead.m_Picture.Spr.m_pDataOffsetList[a].FramX;
	int& yOf = m_BigHead.m_Picture.Spr.m_pDataOffsetList[a].FramY;
	m_BigHead.SetXY(xOf, yOf);
	int xTextStart = m_BigHead.m_Picture.m_x - xOf + m_BigHead.m_Picture.m_Width + 2;;
	int h;
	int yTop = m_Back.m_y;

	for (int i = 0; i < m_Num; i++)
	{
		m_Text[i].LockWidth(wid);
		if (colorlist)
			m_Text[i].SetColor(colorlist[i]);
		else
			m_Text[i].SetColor(m_Color[i]);
		m_Text[i].SetString(pTex[i]);
		m_Text[i].SetXY(xTextStart, yTop);
		h = m_Text[i].GetShowHeight();
		yTop += h + 10;
	}
	h = yTop - (m_Back.GetY());
	if (h < m_BigHead.m_Picture.m_Height + 2)
		h = m_BigHead.m_Picture.m_Height + 2;
	m_Back.SetShowHeight(h);
	//确定位置
	if (yMouse - m_Back.GetShowHeight() < yOffset && (yMouse + m_Back.GetShowHeight() + yOffset > g_480))
	{
		//背景太大,考虑横向放置
		{
			if (xMouse < g_half320)
				xMouse += yOffset;
			else
				xMouse -= m_Back.GetShowWidth() + yOffset;
		}

	}
	else
	{
		//优先放在下方
		if (yMouse + m_Back.GetShowHeight() + yOffset > g_480)
		{
			yMouse -= m_Back.GetShowHeight() + yOffset;
			xMouse -= m_Back.GetShowWidth() / 2;
		}
		else
		{
			yMouse += yOffset;
			xMouse -= m_Back.GetShowWidth() / 2;
		}
	}

	if (yMouse < 0)yMouse = 0;
	if (xMouse < 0)xMouse = 0;
	if (yMouse + m_Back.GetShowHeight() > g_640)yMouse = g_640 - m_Back.GetShowHeight();
	if (xMouse + m_Back.GetShowWidth() > g_640)xMouse = g_640 - m_Back.GetShowWidth();
	m_Back.SetXY(xMouse, yMouse);
	m_BigHead.SetXY(m_Back.GetX() + xOf, m_Back.GetY() + yOf);
	xTextStart = m_BigHead.m_Picture.m_x - xOf + m_BigHead.m_Picture.m_Width + 2;;
	yTop = m_Back.m_y;
	for (int i = 0; i < m_Num; i++)
	{
		m_Text[i].SetXY(xTextStart, yTop);
		h = m_Text[i].GetHeight();
		yTop += h + 10;
	}

}

bool cDescribe::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1);
	pCanvas->Add(&m_BigHead, 1);
	for (int i = 0; i < m_Num; i++)
		pCanvas->Add(&m_Text[i]);
	return true;
}
cWasFile cDescribe::m_DescribeBack;
bool cDescribe::Init()
{
	if (m_bInit)return true;
	m_bInit = true;

	m_Color[10];
	m_Color[2] = RGB(250, 250, 0);
	m_Color[0] = RGB(250, 250, 0);
	m_Color[1] = RGB(220, 220, 220);
	for (int i = 3; i < 10; i++)
	{
		m_Color[i] = RGB(0, 128, 0);
	}

	if (!m_DescribeBack.m_NowID)
	{
		////////////////////////////////////////////////////////////////////////// 呵呵哒 描述图背景
		m_DescribeBack.Load(/*0x1D0C0B23*/0xB0025203);
	}
	m_Back.Set(&m_DescribeBack);

	m_Back.SetxOffset2(2);
	m_Back.SetyOffset2(2);
	m_BigHead.SetStatic(true);

	for (int i = 1; i < 10; i++)
		m_Text[i].m_hFont = g_pMainState->m_hFont[0];
	m_Text[0].m_hFont = g_pMainState->m_hFont[2];
	return true;
}

bool cDescribe::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
		break;
	}
	return true;
}

void cDescribe::OnOff(bool bonoff)
{
	if (m_NeedShow == bonoff)
	{
		if (m_NeedShow)
		{
			g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
		}
		return;
	}
	g_pMainState->InterfaceSetShow(this, bonoff);
	if (m_NeedShow)
	{
		Init();
	}
	else
	{
		for (int i = 0; i < 10; i++)
			m_Text[i].SetString("");
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}






void cItemSelect::Move(int xPos, int yPos)
{
	Init();
	m_Rect.left = xPos;
	m_Rect.top = yPos;
	m_Rect.right = m_Rect.left + 255;
	m_Rect.bottom = m_Rect.top + 204;
	int xOff, yOff;
	for (int i = 0; i < 20; i++)
	{
		xOff = xPos + (i % 5) * 51;
		yOff = yPos + (i / 5) * 51;
		m_ItemHead[i].SetXY(xOff, yOff);
		m_tItemNum[i].SetXY(xOff + 2, yOff + 2);
	}
}


int cItemSelect::Process(int xMouse, int yMouse)
{
	if (!_it)
	{
		return -1;
	}
	if (m_Describe.m_NeedShow)
		m_Describe.OnOff(false);
	if (!isOn(xMouse, yMouse, m_Rect))
	{
		m_MouseOnMark.m_NeedShow = false;
		return -1;
	}

	m_Select = (xMouse - m_Rect.left) / 51 + ((yMouse - m_Rect.top) / 51) * 5;

//	sItem2* pItem = &g_pCharacter->m_PcData.m_Items[m_Select];
	if (!m_ItemHead[m_Select].m_NeedShow)return -1;
	g_pMainState->m_ItemManage.SetItemDescribe(
		xMouse, yMouse, m_Describe, /*pItem*/&_it[m_Select]
		);

	m_MouseOnMark.m_NeedShow = true;
	m_MouseOnMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY());
	return m_Select;
}

void cItemSelect::Update(sItem2* it /* = nullptr */)
{
	Init();
	if (!it)
	{
		it = &g_pCharacter->m_PcData.m_Items[0];
	}
	_it = it;
	m_SelectMark.m_NeedShow = false;
	for (int i = 0; i < 20; i++)
	{
		m_ItemNum[i] = it/*pc->m_PcData.m_Items*/[i].GetNum();
		if (m_ItemNum[i])
		{
			m_ItemHead[i].m_NeedShow = true;
			m_ItemHead[i].Load(/*pc->m_PcData.m_Items*/it[i].m_pItemData->m_SmallHead);
			if (m_ItemNum[i]>1)
			{
				ostringstream oss;
				oss << m_ItemNum[i];
				m_tItemNum[i].SetString(oss.str());
			}
		}
		else
			m_ItemHead[i].m_NeedShow = false;
	}
}

void cItemSelect::Show(cCanvas* pCanvas)
{
	for (int i = 0; i < 20; i++)
	{
		if (m_ItemHead[i].m_NeedShow)
		{
			pCanvas->Add(&m_ItemHead[i], 1);
			if (m_ItemNum[i]>1)
				pCanvas->Add(&m_tItemNum[i]);
		}
	}
	m_Describe.Show(pCanvas);
	pCanvas->Add(&m_MouseOnMark, 1);
	pCanvas->Add(&m_SelectMark, 1);
}

void cItemSelect::Init()
{
	if (m_bInit)return;
	m_Describe.Init();
	m_bInit = true;
	m_ItemHead.resize(20);
	m_tItemNum.resize(20);
	m_ItemNum.resize(20);
	m_SelectMark.Load(0x10921CA7);
	m_SelectMark.m_NeedShow = false;
	m_MouseOnMark.Load(0x6F88F494);
	m_MouseOnMark.m_NeedShow = false;
}

void cItemSelect::SetSelectMark(int id)
{
	if (id > -1)
	{
		m_SelectMark.m_NeedShow = true;
		m_SelectMark.SetXY(m_ItemHead[m_Select].GetX(), m_ItemHead[m_Select].GetY());
	}
	else m_SelectMark.m_NeedShow = false;

}