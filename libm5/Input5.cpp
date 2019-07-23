#include "Global.h"
cInput5::cInput5()
{
}

cInput5::~cInput5()
{
	Shutdown();
}
BOOL cInput5::Shutdown()
{
	return TRUE;
}
BOOL cInput5::Init()
{
	Shutdown();
	return TRUE;
}
cInputDevice5::cInputDevice5()
{

	// Clear the device variables
	Clear();
}

cInputDevice5::~cInputDevice5()
{
	// Free a prior install
	Free();
}
BOOL cInputDevice5::Free()
{

	// Clear the data  
	Clear();

	return TRUE;
}

BOOL cInputDevice5::Clear()
{
	return TRUE;
}
BOOL cInputDevice5::Create(cInput5 *Input, InputDevices Type, BOOL Windowed)
{

	// Free a prior device
	Free();

	// Clear the device information
	Clear();

	// Return a success
	return TRUE;
}


static auto input = cInput::getInstance();
long cInputDevice5::GetXPos()
{
	return input->getMouse().x;
}

BOOL cInputDevice5::SetXPos(long XPos)
{
//	m_XPos = XPos;
	return TRUE;
}

long cInputDevice5::GetYPos()
{
	return input->getMouse().y;
//	return m_YPos;
}

BOOL cInputDevice5::SetYPos(long YPos)
{
//	m_YPos = YPos;
	return TRUE;
}

long cInputDevice5::GetXDelta()
{
	return input->getMouseDelta().x;
}

long cInputDevice5::GetYDelta()
{
	return input->getMouseDelta().y;
}

BOOL cInputDevice5::GetKeyState(BYTE Num, bool lock /* = true */)
{
	return input->isKdown(Num, lock);
}


BOOL cInputDevice5::GetPureKeyState(BYTE Num)
{
	return ((/*m_State[Num] & */0x80) ? TRUE : FALSE);
}

BOOL cInputDevice5::GetButtonState(BYTE Num)
{
	if (Num == MOUSE_LBUTTON)
	{
		return input->isLdown(false);
	}
	else if (Num == MOUSE_RBUTTON)
	{
		return input->isRup(false);
	}

	return FALSE;
}

BOOL cInputDevice5::GetPureButtonState(BYTE Num)
{
	if (Num == MOUSE_LBUTTON)
	{
		return input->isLkeep();
	}
	return FALSE;
}


BOOL cInputDevice5::Acquire(BOOL Active)
{
// 	if (m_pDIDevice == NULL)
// 		return FALSE;
// 
// 	if (Active == TRUE)
// 		m_pDIDevice->Acquire();
// 	else
// 		m_pDIDevice->Unacquire();

	return TRUE;
}

BOOL cInputDevice5::Read()
{
	return TRUE;
}

void cInputDevice5::SetLock(BYTE Num)
{
	if (Num == MOUSE_LBUTTON)
	{
		input->lockLdown();
	}
	else if (Num == MOUSE_RBUTTON)
	{
		input->lockRup();
	}
//	 m_Locks[Num] = TRUE;
}

void cInputDevice5::UnSetLock(BYTE Num)
{
	input->unlockLdown();
}
