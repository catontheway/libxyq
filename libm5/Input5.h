#pragma once
static const uchar MOUSE_LBUTTON = 0;
static const uchar MOUSE_RBUTTON = 1;
static const uchar MOUSE_MBUTTON = 2;
enum InputDevices {
	NONE = 0,
	KEYBOARD,
	MOUSE,
};
class cInput5
{
protected:

public:
	cInput5();
	~cInput5();
	BOOL Init();
	BOOL Shutdown();
};
class cInputDevice5
{
public:

public:
	cInputDevice5();
	~cInputDevice5();

	// Generic functions - all devices
	BOOL Create(cInput5 *Input, InputDevices Type, BOOL Windowed = TRUE);
	BOOL Free();

	BOOL Clear();
	BOOL Read();
	BOOL Acquire(BOOL Active = TRUE);



	long GetXPos();
	BOOL SetXPos(long XPos);
	long GetYPos();
	BOOL SetYPos(long YPos);
	long GetXDelta();
	long GetYDelta();

	// Keyboard specific functions
	BOOL  GetKeyState(BYTE Num, bool lock = true);
	BOOL  GetPureKeyState(BYTE Num);

	// Mouse/Joystick specific functions
	BOOL  GetButtonState(BYTE Num);
	BOOL  GetPureButtonState(BYTE Num);
	void  SetLock(BYTE Num);
	void  UnSetLock(BYTE Num); // { m_Locks[Num] = FALSE; }

};