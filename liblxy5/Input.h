#pragma once
#include "_asert.h"
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

#define MOUSE_LBUTTON          0
#define MOUSE_RBUTTON          1
#define MOUSE_MBUTTON          2
enum InputDevices {
	NONE = 0,
	KEYBOARD,
	MOUSE,
};
class cInput
{
protected:

	IDirectInput8 *m_pDI;

public:
	cInput();
	~cInput();
	IDirectInput8 *GetDirectInputCOM();
	bool Init();
	bool Shutdown();
};
class cInputDevice
{
public:
	cInput               *m_Input;

	short                 m_Type;
	IDirectInputDevice8  *m_pDIDevice;

	bool                  m_Windowed;

	array<char, 256>                  m_State;
	DIMOUSESTATE         *m_MouseState;


	array<bool,256>                 m_Locks;

	long                  m_XPos, m_YPos;



public:
	cInputDevice();
	~cInputDevice();

	IDirectInputDevice8 *DeviceCOM();

	// Generic functions - all devices
	bool Create(cInput *Input, short Type, bool Windowed = true);
	bool Free();

	bool Clear();
	bool Read();
	bool Acquire(bool Active = true);



	long GetXPos();
	bool SetXPos(long XPos);
	long GetYPos();
	bool SetYPos(long YPos);
	long GetXDelta();
	long GetYDelta();

	// Keyboard specific functions
	bool  GetKeyState(uchar Num);
	bool  GetPureKeyState(uchar Num);

	// Mouse/Joystick specific functions
	bool  GetButtonState(uchar Num);
	bool  GetPureButtonState(uchar Num);
	void  SetLock(uchar Num);
	void  UnSetLock(uchar Num){ m_Locks[Num] = false; }

};