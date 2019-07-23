#include "cInput.h"
#include "cInputDevice.h"

cInput::cInput() :_hwnd(nullptr), _input(nullptr), _mouse(nullptr), _keybord(nullptr)
{
}

cInput* cInput::getInstance()
{
	static cInput* s_inputInstance = new cInput();
	return s_inputInstance;
}


bool cInput::init(HWND hwnd, HINSTANCE hinst)
{
	if (hwnd == nullptr || hinst == nullptr)
	{
		return false;
	}
	if (_input == nullptr)
	{
		_input = new cInputDx();
		_input->Init(hinst);
	}
	if (_mouse == nullptr)
	{
		_mouse = new cInputDevice();
		_mouse->Create(_input, hwnd, cInputDevice::eInput::MOUSE);
	}
	if (_keybord == nullptr)
	{
		_keybord = new cInputDevice();
		_keybord->Create(_input, hwnd, cInputDevice::eInput::KEYBOARD);
	}
	_hwnd = hwnd;
	return true;
}



void cInput::update()
{
	if (_hwnd == nullptr)
	{
		return;
	}
	_isluplock = false;
	_isruplock = false;
	_iswheellock = false;

	_mouse->Acquire(true);
	_mouse->Read(_hwnd);
	_islkeep = _mouse->GetPureButtonState(cInputDevice::MOUSE_LBUTTON);
	_islup = _islkeepLast && (!_islkeep);
	_islkeepLast = _islkeep;

	static bool s_isrkeep;
	s_isrkeep = _mouse->GetPureButtonState(cInputDevice::MOUSE_RBUTTON);
	_isrup = _isrkeepLast && (!s_isrkeep);
	_isrkeepLast = s_isrkeep;

	_keybord->Acquire(true);
	_keybord->Read(_hwnd);

	_vDelta = _vCursor;
	_vCursor.x = _mouse->GetXPos();
	_vCursor.y = _mouse->GetYPos();
	_vDelta.x = _vCursor.x - _vDelta.x;
	_vDelta.y = _vCursor.x - _vDelta.y;
// 	_vDelta.x = _mouse->GetYDelta();
// 	_vDelta.y = _mouse->GetYDelta();


	_mouse->GetPureButtonState(cInputDevice::MOUSE_MBUTTON);
}


bool cInput::isLdown(bool lock /* = true */)
{
	if (_mouse->GetButtonState(cInputDevice::MOUSE_LBUTTON))
	{
		if (lock)
		{
			lockLdown();
		}
		return true;
	}
	return false;
}

void cInput::lockLdown()
{
	_mouse->SetLock(cInputDevice::MOUSE_LBUTTON);
}



void cInput::unlockLdown()
{
	_mouse->UnSetLock(cInputDevice::MOUSE_LBUTTON);
}


bool cInput::isLup(bool lock /* = true */)
{
	if (_islup)
	{
		if (_isluplock)
		{
			return false;
		}
		if (lock)
		{
			lockLup();
		}
		return true;
	}
	return false;
}

void cInput::lockLup()
{
	_isluplock = true;
}


bool cInput::isRup(bool lock /* = true */)
{
	if (_isrup)
	{
		if (_isruplock)
		{
			return false;
		}
		if (lock)
		{
			lockRup();
		}
		return true;
	}
	return false;
}

void cInput::lockRup()
{
	_isruplock = true;
}


bool cInput::isLkeep()
{
	return _islkeep;
}


bool cInput::isKdown(unsigned char key, bool lock /* = true */)
{
	if (_keybord->GetKeyState(key))
	{
		if (lock)
		{
			_keybord->SetLock(key);
		}
		return true;
	}
	return false;
}



bool cInput::isAlt()
{
	return (::GetKeyState(VK_LMENU) & 0x8000) || 
		(::GetKeyState(VK_RMENU) & 0x8000) || 
		(::GetAsyncKeyState(VK_LMENU) & 0x8000) ||
		(::GetAsyncKeyState(VK_RMENU) & 0x8000);
}


int cInput::getWheel(bool lock /* = true */)
{
	if (_iswheellock)
	{
		return 0;
	}
	if (lock)
	{
		lockWheel();
	}
	return _mouse->GetWheel();
}

void cInput::lockWheel()
{
	_iswheellock = true;
}

const Vec2& cInput::getMouse()
{
	return _vCursor;
}


const Vec2& cInput::getMouseDelta()
{
	return _vDelta;
}
