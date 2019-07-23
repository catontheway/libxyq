
#include "_global.h"



void cInterfaceFather::sChild::addChild(eType _e, ulong uid, cWasFile* file, string text, ulong tColor, int x, int y)
{
	if (!file)
	{
		file = new cWasFile;
	}
	if (uid)
	{
		file->Load(uid);
	}
	if ((e = _e) == eType::File)
	{
		file->SetStatic(true);
		ptr = file;
	}
	else if (_e == eType::Obj)
	{
		cObjWas* o = new cObjWas;
//		file->SetStatic(true);
		o->Set(file);
		o->m_bStatic = true;
		ptr = o;
	}
	void* &p = e == eType::Text ? ptr : ptr2;
	cText* t = new cText;
	t->SetString(text);
	t->SetColor(tColor);
	p = t;
	xx = x, yy = y;
}



bool cInterfaceFather::isInRect(long x, long y, cWasFile* pPic)
{
	RECT rect;
	rect.left = pPic->m_Picture.m_x;
	rect.top = pPic->m_Picture.m_y;
	if (pPic->m_Picture.m_ShowHeight == 0)
		rect.bottom = rect.top + pPic->m_Picture.m_Height;
	else  rect.bottom = rect.top + pPic->m_Picture.m_ShowHeight;
	if (pPic->m_Picture.m_ShowWidth == 0)
		rect.right = rect.left + pPic->m_Picture.m_Width;
	else  rect.right = rect.left + pPic->m_Picture.m_ShowWidth;

	return isOn(x, y, rect);
}

bool cInterfaceFather::CheckOn(cWasFile* pTarget, int id)
{
	if (!isOn(g_xMouse, g_yMouse, pTarget->m_PreShowRect))return false;
	m_Select = id;
	if (pTarget->GetNowFrame() == 0)
	{
		m_frampre = pTarget;
		m_frampre->SetFrame(2);
	}
	pTarget->m_bMove = true;
// 	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
// 	{
// 		m_bMoveMode = false;
// 		return false;
// 	}
// 	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
// 	m_Sleeptime = 3;
	CheckL();
	return true;
}

bool cInterfaceFather::CheckOn(cObjWas* pTarget, int id)
{
	if (!isOn(g_xMouse, g_yMouse, pTarget->m_PreShowRect))return false;
	m_Select = id;
	if (pTarget->GetFrame() == 0)
	{
		m_framprep = pTarget;
		m_framprep->SetFrame帧(2);
	}
	pTarget->m_bMove = true;
// 	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
// 	{
// 		m_bMoveMode = false;
// 		return false;
// 	}
// 	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
// 	m_Sleeptime = 3;
	return CheckL();
}

bool cInterfaceFather::CheckOn(cText* ptext, int id)
{
	if (isOn(g_xMouse, g_yMouse, ptext->m_PreShowRect))
	{
		m_Select = id;
// 		if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
// 		{
// 			m_bMoveMode = false;
// 			return false;
// 		}
// 		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
// 		m_Sleeptime = 3;
		return CheckL();
	}
	return false;
}

bool cInterfaceFather::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		m_bMoveMode = false;
		return false;
	}
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	return true;
}

void cInterfaceFather::ResetButton()
{
	if (m_framprep)
	{
		if (3 == m_framprep->GetFrame())return;
		m_framprep->SetFrame帧(0);
		m_framprep->m_bMove = true;
		m_framprep = 0;
	}
	else
		if (m_frampre)
		{
		if (3 == m_frampre->GetNowFrame())return;
		m_frampre->SetFrame(0);
		m_frampre->m_bMove = true;
		m_frampre = 0;
		}
}



bool cInterfaceFather::Move(int x, int y)
{
	m_xPos = x, m_yPos = y;
	m_Back.SetXY(m_xPos, m_yPos);
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
//	Move(m_xPos, m_yPos);
	forr(_children, i)
	{
		const auto& c = _children[i];

		switch (c.e)
		{
		case sChild::eType::File:
		{
			cWasFile* f = (cWasFile*)c.ptr;
			cText* t = (cText*)c.ptr2;
			f->SetXY(c.xx + m_xPos, c.yy + m_yPos);
			if (!t->GetString().empty())
			{
				t->SetY(f->GetY() + f->GetShowHeight() / 2 - t->GetShowHeight() / 2 + 1);
				t->SetXCenter(f->GetX() + f->GetShowWidth() / 2);
				t->UpdateXCenter();
			}
		}
			break;
		case sChild::eType::Obj:
		{
			cObjWas* f = (cObjWas*)c.ptr;
			cText* t = (cText*)c.ptr2;
			f->SetXY(c.xx + m_xPos, c.yy + m_yPos);
			if (!t->GetString().empty())
			{
				t->SetY(f->GetY() + f->GetShowHeight() / 2 - t->GetShowHeight() / 2 + 1);
				t->SetXCenter(f->GetX() + f->GetShowWidth() / 2);
				t->UpdateXCenter();
			}
		}
			break;
		case sChild::eType::Text:
			((cText*)c.ptr)->SetXY(c.xx + m_xPos, c.yy + m_yPos);
			break;
		}
	}
	return true;
}



bool cInterfaceFather::ProcessInput()
{
// 	if (!isInRect(g_xMouse, g_yMouse, &m_Back))
// 	{
// 		return true;
// 	}

	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}

	g_pMainState->SetMouseOnMap(false);
	m_Select = -1;
	ResetButton();


	if (m_bMoveMode)//移动
	{
		g_pMainState->SetMouseOnMap(false);

		if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			m_bMoveMode = false;
			return true;
		}

// 		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
// 		m_Sleeptime = 3;
		if (m_frampre)
			m_frampre->SetFrame(1);

		m_Sleeptime = 0;
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		int xDel = g_xMouse - m_Prex;
		int yDel = g_yMouse - m_Prey;
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		if (xDel != 0 || yDel != 0)
		{
			Move(m_xPos + xDel, m_yPos + yDel);
		}
		return true;
	}

	if (ProcessInputMore())
	{
		return true;
	}

	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	g_pMainState->SetMouseOnMap(false);

	//取消按钮
	if (CheckOn(&m_Cancel, INT_MAX))
	{
		OnOff(false);
		return true;
	}


	forr(_children, i)
	{
		auto& c = _children[i];
		if (c.onFrame)
		{
			c.onFrame(&c);
		}
		switch (c.e)
		{
		case sChild::eType::File:
			if (c.checkon && CheckOn((cWasFile*)c.ptr, INT_MAX))
			{
				if (c.onClick)
				{
					c.onClick(&c);
				}
				return true;
			}
		case sChild::eType::Obj:
			if (c.checkon && CheckOn((cObjWas*)c.ptr, INT_MAX))
			{
				if (c.onClick)
				{
					c.onClick(&c);
				}
				return true;
			}
		}
	}


	if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
		if (_isRclose)
		{
			OnOff(false);
			return true;
		}
		else if (CheckRB())
		{
			return true;
		}
	}
	//准备移动
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		m_bMoveMode = false;
		return true;
	}
	g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
	m_Prex = g_xMouse;
	m_Prey = g_yMouse;
	m_bMoveMode = true;
	m_Sleeptime = 0;
	return true;
}

bool cInterfaceFather::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	if (m_Back.m_NowID)
	{
		pCanvas->Add(&m_Back, 1/*, true*/);
	}
	if (m_Cancel.m_pFile)
	{
		pCanvas->Add(&m_Cancel, 1/*, true*/);
	}
	forv(_children, i)
	{
		auto& c = _children[i];
		switch (c.e)
		{
		case sChild::eType::File:
			pCanvas->Add((cWasFile*)c.ptr, 1/*, true*/);
			pCanvas->Add((cText*)c.ptr2, 1/*, true*/);
			break;
		case sChild::eType::Obj:
			pCanvas->Add((cObjWas*)c.ptr, 1/*, true*/);
			pCanvas->Add((cText*)c.ptr2, 1/*, true*/);
			break;
		case sChild::eType::Text:
			pCanvas->Add((cText*)c.ptr/*, true*/);
			break;
		}
	}
	return true;
}


void cInterfaceFather::OnOff(bool NeedShow)
{
	if (NeedShow == m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (NeedShow)
	{
		if (!_isInit)
		{
			_isInit = true;
			m_Cancel.Set(&g_pMainState->m_Cancel);
			m_Cancel.m_bStatic = (true);
			Init();
		}
		initShow();
	}
	else
	{
		g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
	}
}


