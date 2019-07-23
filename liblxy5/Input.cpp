#include "_global.h"
#pragma comment(lib,"dinput8.lib") 
#pragma comment(lib,"dxguid.lib")   

cInput::cInput()
{
	m_pDI = NULL;
}

cInput::~cInput()
{
	Shutdown();
}
bool cInput::Shutdown()
{
	SAFE_RELEASE(m_pDI);
	return true;
}
bool cInput::Init()
{
	Shutdown();
	DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	return true;
}
IDirectInput8 *cInput::GetDirectInputCOM()
{
	return m_pDI;
}
cInputDevice::cInputDevice()
{
	// Clear parent cInput object pointer
	m_Input = NULL;

	// Setup device to none
	m_Type = NONE;

	// Set windowed usage to true
	m_Windowed = true;

	// Clear the DirectInput interface pointer
	m_pDIDevice = NULL;

	// Point the mouse and joystick structures to the state buffer
	m_MouseState = (DIMOUSESTATE*)&m_State;

	// Clear the device variables
	Clear();
}

cInputDevice::~cInputDevice()
{
	// Free a prior install
	Free();
}
bool cInputDevice::Free()
{
	// Unacquire and release the object
	if (m_pDIDevice != NULL) {
		m_pDIDevice->Unacquire();
		SAFE_RELEASE(m_pDIDevice);
	}

	// Set to no device installed
	m_Type = NONE;

	// Clear the data  
	Clear();

	return true;
}

bool cInputDevice::Clear()
{
	short i;

	ZeroMemory(&m_State, 256);

	for (i = 0; i < 256; i++)
		m_Locks[i] = false;

	m_XPos = 0;
	m_YPos = 0;

	return true;
}
bool cInputDevice::Create(cInput *Input, short Type, bool Windowed)
{
	DIDATAFORMAT *DataFormat;


	// Free a prior device
	Free();
	m_Input = Input;
	switch (Type) {
	case KEYBOARD:
		if (FAILED(m_Input->GetDirectInputCOM()->CreateDevice(GUID_SysKeyboard, &m_pDIDevice, NULL)))
			return false;
		DataFormat = (DIDATAFORMAT*)&c_dfDIKeyboard;
		break;

	case MOUSE:
		if (FAILED(m_Input->GetDirectInputCOM()->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL)))
			return false;
		DataFormat = (DIDATAFORMAT*)&c_dfDIMouse;
		break;



	default: return false;
	}

	// Set the windowed usage
	m_Windowed = Windowed;

	// Set the data format of keyboard
	m_pDIDevice->SetDataFormat(DataFormat);


	// Set the cooperative level - Foreground & Nonexclusive
	m_pDIDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	m_pDIDevice->Acquire();


	// Set the device type
	m_Type = Type;

	// Clear the device information
	Clear();

	// Return a success
	return true;
}


long cInputDevice::GetXPos()
{
	return m_XPos;
}

bool cInputDevice::SetXPos(long XPos)
{
	m_XPos = XPos;
	return true;
}

long cInputDevice::GetYPos()
{
	return m_YPos;
}

bool cInputDevice::SetYPos(long YPos)
{
	m_YPos = YPos;
	return true;
}

long cInputDevice::GetXDelta()
{
	switch (m_Type) {
	case MOUSE:
		return m_MouseState->lX;
	default: return 0;
	}
}

long cInputDevice::GetYDelta()
{
	switch (m_Type) {
	case MOUSE:
		return m_MouseState->lY;

	default: return 0;
	}
}

bool cInputDevice::GetKeyState(uchar Num)
{
	if ((m_State[Num] & 0x80))
	{
		if (m_Locks[Num] == false)
		{
			return true;
		}
		return false;
	}
	m_Locks[Num] = false;
	return false;
}


bool cInputDevice::GetPureKeyState(uchar Num)
{
	return ((m_State[Num] & 0x80) ? true : false);
}

bool cInputDevice::GetButtonState(uchar Num)
{
	char State = 0;

	if (m_Type == MOUSE)
		State = m_MouseState->rgbButtons[Num];

	if (State & 0x80)   //是否被按下
	{
		if (m_Locks[Num] == false)  //是否已经处理过这个消息
		{
			return true;
		}
		return false;
	}
	//如果没有被按下, 重置
	m_Locks[Num] = false;
	return false;
}

bool cInputDevice::GetPureButtonState(uchar Num)
{
	char State = 0;

	if (m_Type == MOUSE)
		State = m_MouseState->rgbButtons[Num];
	if (State & 0x80)
		return true;
	return false;
}


bool cInputDevice::Acquire(bool Active)
{
	if (m_pDIDevice == NULL)
		return false;

	if (Active == true)
		m_pDIDevice->Acquire();
	else
		m_pDIDevice->Unacquire();

	return true;
}

bool cInputDevice::Read()
{
	HRESULT hr;
	long BufferSizes[2] = { 256, sizeof(DIMOUSESTATE) };

	if (m_Type < 1 || m_Type > 3)
		return false;
	for (;;) {
		// Poll
		m_pDIDevice->Poll();

		// Read in state
		if (SUCCEEDED(hr = m_pDIDevice->GetDeviceState(BufferSizes[m_Type - 1], (LPVOID)&m_State)))
			break;

		// Return on an unknown error  
		if (hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
			return false;

		// Reacquire and try again
		if (FAILED(m_pDIDevice->Acquire()))
			return false;
	}

	// Since only the mouse coordinates are relative, you'll
	// have to deal with them now
	if (m_Type == MOUSE) {
		// If windowed usage, ask windows for coordinates
		if (m_Windowed == true) {
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			m_XPos = pt.x;
			m_YPos = pt.y;
		}
		else {
			m_XPos += m_MouseState->lX;
			m_YPos += m_MouseState->lY;
		}
	}
	return true;
}

void cInputDevice::SetLock(uchar Num)
{
	 m_Locks[Num] = true;
}
