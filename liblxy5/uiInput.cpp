#include "_global.h"

bool cInterfaceNumShuRu::Process()
{
	if (!m_bActive)
	{
		if (isOn(g_xMouse, g_yMouse, m_rect))
			if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
			{
			g_pMainState->SetMouseOnMap(true);
			g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
			SetCaretPos(CountCaretPos(g_xMouse, g_yMouse));
			m_bActive = true;
			return true;
			}
		return false;
	}

	if (m_bEraseMode)
	{
		g_pMainState->SetMouseOnMap(false);
		if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			m_bEraseMode = false;
		}
		else
		{
			int endpos = CountCaretPos(g_xMouse, g_yMouse);
			if (endpos != m_EraseEnd)
			{
				m_bInEraseMode = true;
				m_EraseEnd = endpos;
				m_tNum.SetTransparentColor(CountPos(m_EraseStart), CountPos(m_EraseEnd), RGB(0, 0, 150));
			}
			m_tNum.SetBackColor(0);
		}
		return true;
	}
	if (m_caretpos < 10)
	{
		if (g_pMainState->Keyboard.GetKeyState(DIK_LEFT))
		{
			g_pMainState->Keyboard.SetLock(DIK_LEFT);
			SetCaretPos(m_caretpos - 1);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_RIGHT))
		{
			g_pMainState->Keyboard.SetLock(DIK_RIGHT);
			SetCaretPos(m_caretpos + 1);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_0))
		{
			g_pMainState->Keyboard.SetLock(DIK_0);
			if (m_caretpos == 0 && (!m_bInEraseMode))return true;
			ShuRu(0);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD0))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD0);
			ShuRu(0);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_1))
		{

			g_pMainState->Keyboard.SetLock(DIK_1);
			ShuRu(1);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD1))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD1);
			ShuRu(1);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_2))
		{
			g_pMainState->Keyboard.SetLock(DIK_2);
			ShuRu(2);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD2))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD2);
			ShuRu(2);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_3))
		{
			g_pMainState->Keyboard.SetLock(DIK_3);
			ShuRu(3);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD3))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD3);
			ShuRu(3);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_4))
		{
			g_pMainState->Keyboard.SetLock(DIK_4);
			ShuRu(4);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD4))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD4);
			ShuRu(4);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_5))
		{
			g_pMainState->Keyboard.SetLock(DIK_5);
			ShuRu(5);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD5))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD5);
			ShuRu(5);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_6))
		{
			g_pMainState->Keyboard.SetLock(DIK_6);
			ShuRu(6);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD6))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD6);
			ShuRu(6);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_7))
		{
			g_pMainState->Keyboard.SetLock(DIK_7);
			ShuRu(7);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD7))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD7);
			ShuRu(7);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_8))
		{
			g_pMainState->Keyboard.SetLock(DIK_8);
			ShuRu(8);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD8))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD8);
			ShuRu(8);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_9))
		{
			g_pMainState->Keyboard.SetLock(DIK_9);
			ShuRu(9);
			return true;
		}
		if (g_pMainState->Keyboard.GetKeyState(DIK_NUMPAD9))
		{

			g_pMainState->Keyboard.SetLock(DIK_NUMPAD9);
			ShuRu(9);
			return true;
		}
	}
	if (g_pMainState->Keyboard.GetKeyState(DIK_BACK))
	{
		g_pMainState->Keyboard.SetLock(DIK_BACK);
		if (m_bInEraseMode)
		{
			if (m_EraseStart > m_EraseEnd)swap(m_EraseEnd, m_EraseStart);
			//	int num = m_EraseEnd - m_EraseStart;
			for (int i = m_EraseEnd; i > m_EraseStart; i--)
			{
				Erase(i);
			}
			m_bInEraseMode = false;
		}
		else
			Erase(m_caretpos);
		return true;
	}
	if (isOn(g_xMouse, g_yMouse, m_rect))
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			g_pMainState->SetMouseOnMap(false);
			if (m_num > 0)
			{
				m_bEraseMode = true;
				if (m_bInEraseMode)
				{
					m_tNum.UnTransparentColor(CountPos(m_EraseStart), CountPos(m_EraseEnd), RGB(0, 0, 255));
					m_bInEraseMode = false;
				}
				m_EraseStart = CountCaretPos(g_xMouse, g_yMouse);
				SetCaretPos(m_EraseStart);
				m_EraseEnd = m_EraseStart;
			}
			return true;
		}
	}
	else //鼠标在范围外点击, 取消激活状态
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			m_bActive = false;
			if (m_bInEraseMode)
			{
				m_tNum.UnTransparentColor(CountPos(m_EraseStart), CountPos(m_EraseEnd), RGB(0, 0, 255));
				m_EraseStart = -1;
				m_EraseEnd = -1;
			}
		}
		return false;
	}
	return false;
}

void cInterfaceNumShuRu::Init(RECT rect)
{
	m_rect.left = rect.left;
	m_rect.right = rect.right;
	m_rect.top = rect.top;
	m_rect.bottom = rect.bottom;
	m_tNum.SetXY(m_rect.left, m_rect.top);
	SetCaretPos(0);
	if (!m_bInit)Init2();
}

int cInterfaceNumShuRu::CountCaretPos(int xMouse, int yMouse)
{
	int truex = xMouse - m_tNum.GetX();
	cText test;

	ostringstream oss;
	int prewidth = 0;
	int width;
	int widthcube;
	for (int i = 0; i < m_numlong; i++)
	{
		oss.str("");
		for (int j = 0; j < i + 1; j++)
			oss << m_numlist[j];
		test.SetString(oss.str());
		width = test.GetWidth();
		widthcube = width - prewidth;
		if (truex < widthcube)
		{
			if (truex < widthcube / 2)
				return	i;
			else
				return i + 1;
		}
		prewidth = width;
		truex -= widthcube;
	}
	return m_numlong;
}

void cInterfaceNumShuRu::Init2()
{
	for (int i = 0; i < 15; i++)
	{
		m_numlist.push_back(0);
	}

	m_Caret.Load(0x86785735);
	m_Caret.SetStatic(true);
	m_Caret.SetShowWidth(2);
	m_Caret.SetyOffset2(4);
	m_Caret.SetShowHeight(18);
	//m_Caret.SetFrame(1);
	m_bInit = true;
}

void cInterfaceNumShuRu::Show(cCanvas* pCanvas)
{
	if (m_bActive)
	{
		m_time += 1;
		m_time %= 80;
		if (m_time == 0)
			m_Caret.m_NeedShow = false;
		else
			if (m_time == 40)
				m_Caret.m_NeedShow = true;
		pCanvas->Add(&m_Caret, 1);
	}
	//m_Caret.m_NeedShow = !m_Caret.m_NeedShow;
	if (m_numlong)
		pCanvas->Add(&m_tNum);
}

void cInterfaceNumShuRu::UpdateCaret()
{
	int width = CountPos(m_caretpos);
	m_Caret.SetXY(m_rect.left + width, m_rect.top);
}

void cInterfaceNumShuRu::SetCaretPos(int pos)
{
	if (pos < 0)return;
	if (pos > m_numlong)pos = m_numlong;
	m_caretpos = pos;
	UpdateCaret();
}

void cInterfaceNumShuRu::UpdateNum()
{
	ostringstream oss;
	for (int i = 0; i < m_numlong; i++)
		oss << m_numlist[i];
	string text = oss.str();
	m_num = atoi(text.c_str());
	if (m_num > m_MaxNum)
	{
		Reset();

		SetNum(m_MaxNum);
		SetCaretPos(m_numlong);
		return;
	}
	m_tNum.SetString(text);
	ulong color = GetPriceColor(m_num);
	m_tNum.SetColor(color);
}

int cInterfaceNumShuRu::CountPos(int pos)
{
	if (!pos)return 0;
	cText test;
	ostringstream oss;
	for (int i = 0; i < pos; i++)
		oss << m_numlist[i];
	test.SetString(oss.str());
	return test.GetWidth();
}

void cInterfaceNumShuRu::ShuRu(int num)
{
	if (m_bInEraseMode)
	{
		if (m_bInEraseMode)
		{
			if (m_EraseStart > m_EraseEnd)swap(m_EraseEnd, m_EraseStart);
			//int num = m_EraseEnd - m_EraseStart;
			for (int i = m_EraseEnd; i > m_EraseStart; i--)
			{
				Erase(i);
			}
			m_bInEraseMode = false;
		}
	}
	for (int i = m_numlong - 1; i >= m_caretpos; i--)
	{
		m_numlist[i] = m_numlist[i - 1];
	}
	m_numlist[m_caretpos] = num;
	m_numlong += 1;
	SetCaretPos(m_caretpos + 1);
	UpdateNum();
}

void cInterfaceNumShuRu::Erase(int pos)
{
	if (pos <= 0)return;
	m_numlong -= 1;
	for (int i = pos - 1; i < m_numlong; i++)
	{
		m_numlist[i] = m_numlist[i + 1];
	}
	SetCaretPos(pos - 1);
	UpdateNum();
}

void cInterfaceNumShuRu::Reset()
{
	m_num = 0;
	m_numlong = 0;
	SetCaretPos(0);
}

void cInterfaceNumShuRu::SetNum(INT64 num)
{
	if (num > m_MaxNum)num = m_MaxNum;
	m_num = num;
	m_numlong = 0;
	int numlist[15];
	while (num > 0)
	{
		numlist[m_numlong] = num % 10;
		m_numlong += 1;
		num /= 10;
	}
	for (int i = 0; i < m_numlong; i++)
	{
		m_numlist[i] = numlist[m_numlong - 1 - i];
	}
	ostringstream oss;
	for (int i = 0; i < m_numlong; i++)
		oss << m_numlist[i];
	string text = oss.str();
	m_tNum.SetString(text);
	ulong color = GetPriceColor(m_num);
	m_tNum.SetColor(color);
	SetCaretPos(m_numlong);
}

void cInterfaceNumShuRu::SetActive(bool bActive)
{
	m_bActive = bActive;
	SetCaretPos(m_numlong);
	if (m_bActive)
		if (m_HuChiList.size())
		{
		for (int i = 0; i < m_HuChiList.size(); i++)
			m_HuChiList[i]->SetActive(false);
		}
}