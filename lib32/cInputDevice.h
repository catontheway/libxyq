#pragma once
#include <array>
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

class cInputDx
{
protected:
	IDirectInput8 *m_pDI;

public:
	cInputDx();
	~cInputDx();
	IDirectInput8 *GetDirectInputCOM();
	bool Init(HINSTANCE hinst);
	bool Shutdown();
};

//  ‰»Î…Ë±∏
class cInputDevice
{
public:
	enum eInput
	{
		NONE = 0,
		KEYBOARD,
		MOUSE,
	};
	
	static const unsigned char MOUSE_LBUTTON = 0;
	static const unsigned char MOUSE_RBUTTON = 1;
	static const unsigned char MOUSE_MBUTTON = 2;
	cInputDx *m_Input;

	short m_Type;
	IDirectInputDevice8 *m_pDIDevice;

	bool m_Windowed;

	std::array<char, 256> m_State;
	DIMOUSESTATE *m_MouseState;


	std::array<bool, 256> m_Locks;

	long  m_XPos, m_YPos, m_Wheel;

public:
	cInputDevice();
	~cInputDevice();

	// Generic functions - all devices
	bool Create(cInputDx *Input, HWND hwnd, short Type, bool Windowed = true);
	bool Free();

	bool Clear();
	bool Read(HWND hwnd);
	bool Acquire(bool Active = true);



	long GetXPos();
	bool SetXPos(long XPos);
	long GetYPos();
	bool SetYPos(long YPos);
	long GetXDelta();
	long GetYDelta();
	long GetWheel();

	// Keyboard specific functions
	bool  GetKeyState(unsigned char Num);
	bool  GetPureKeyState(unsigned char Num);

	// Mouse/Joystick specific functions
	bool  GetButtonState(unsigned char Num);
	bool  GetPureButtonState(unsigned char Num);
	void  SetLock(unsigned char Num);
	void  UnSetLock(unsigned char Num){ m_Locks[Num] = false; }

};