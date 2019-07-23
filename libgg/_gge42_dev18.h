#pragma once

#include "../libgge/ggebase.h"
#include "../libgge/ggecolor.h"
#include "../libgge/ggecommon.h"
#include "../libgge/ggefont.h"
#include "../libgge/ggefw.h"
#include "../libgge/ggegamestate.h"
#include "../libgge/ggeguibutton.h"
#include "../libgge/ggeguieditbox.h"
#include "../libgge/ggeguilistbox.h"
#include "../libgge/ggeguiloader.h"
#include "../libgge/ggeguimanager.h"
#include "../libgge/ggeguirichtext.h"
#include "../libgge/ggeguislider.h"
#include "../libgge/ggeguiwindow.h"
#include "../libgge/ggejson.h"
#include "../libgge/ggemath.h"
#include "../libgge/ggematrix.h"
#include "../libgge/ggemesh.h"
#include "../libgge/ggemusic.h"
#include "../libgge/ggeparticle.h"
#include "../libgge/ggeprocess.h"
#include "../libgge/ggerefcounter.h"
#include "../libgge/ggerendernode.h"
#include "../libgge/ggeresmanager.h"
#include "../libgge/ggeribbontrail.h"
#include "../libgge/ggeshader.h"
#include "../libgge/ggesound.h"
#include "../libgge/ggesprite.h"
#include "../libgge/ggeswapchain.h"
#include "../libgge/ggetexture.h"
#include "../libgge/ggetypes.h"
#include "../libgge/ggevariant.h"
#include "../libgge/ggevideo.h"
#include "../libgge/ggexml.h"

// 节点类加了一个 friend class cScene;

enum class eKey
{
	NONE = -1,
	LBUTTON = GGEK_LBUTTON,
	RBUTTON = GGEK_RBUTTON,
	MBUTTON = GGEK_MBUTTON,

	ESCAPE = GGEK_ESCAPE,
	BACKSPACE = GGEK_BACKSPACE,
	TAB = GGEK_TAB,
	ENTER = GGEK_ENTER,
	SPACE = GGEK_SPACE,

	SHIFT = GGEK_SHIFT,
	CTRL = GGEK_CTRL,
	ALT = GGEK_ALT,

	LWIN = GGEK_LWIN,
	RWIN = GGEK_RWIN,
	APPS = GGEK_APPS,

	PAUSE = GGEK_PAUSE,
	CAPSLOCK = GGEK_CAPSLOCK,
	NUMLOCK = GGEK_NUMLOCK,
	SCROLLLOCK = GGEK_SCROLLLOCK,

	PGUP = GGEK_PGUP,
	PGDN = GGEK_PGDN,
	HOME = GGEK_HOME,
	END = GGEK_END,
	INSERT = GGEK_INSERT,
	DEL = GGEK_DELETE,

	LEFT = GGEK_LEFT,
	UP = GGEK_UP,
	RIGHT = GGEK_RIGHT,
	DOWN = GGEK_DOWN,

	K0 = GGEK_0,
	K1 = GGEK_1,
	K2 = GGEK_2,
	K3 = GGEK_3,
	K4 = GGEK_4,
	K5 = GGEK_5,
	K6 = GGEK_6,
	K7 = GGEK_7,
	K8 = GGEK_8,
	K9 = GGEK_9,

	A = GGEK_A,
	B = GGEK_B,
	C = GGEK_C,
	D = GGEK_D,
	E = GGEK_E,
	F = GGEK_F,
	G = GGEK_G,
	H = GGEK_H,
	I = GGEK_I,
	J = GGEK_J,
	K = GGEK_K,
	L = GGEK_L,
	M = GGEK_M,
	N = GGEK_N,
	O = GGEK_O,
	P = GGEK_P,
	Q = GGEK_Q,
	R = GGEK_R,
	S = GGEK_S,
	T = GGEK_T,
	U = GGEK_U,
	V = GGEK_V,
	W = GGEK_W,
	X = GGEK_X,
	Y = GGEK_Y,
	Z = GGEK_Z,

	GRAVE = GGEK_GRAVE,
	MINUS = GGEK_MINUS,
	EQUALS = GGEK_EQUALS,
	BACKSLASH = GGEK_BACKSLASH,
	LBRACKET = GGEK_LBRACKET,
	RBRACKET = GGEK_RBRACKET,
	SEMICOLON = GGEK_SEMICOLON,
	APOSTROPHE = GGEK_APOSTROPHE,
	COMMA = GGEK_COMMA,
	PERIOD = GGEK_PERIOD,
	SLASH = GGEK_SLASH,

	NUM0 = GGEK_NUMPAD0,
	NUM1 = GGEK_NUMPAD1,
	NUM2 = GGEK_NUMPAD2,
	NUM3 = GGEK_NUMPAD3,
	NUM4 = GGEK_NUMPAD4,
	NUM5 = GGEK_NUMPAD5,
	NUM6 = GGEK_NUMPAD6,
	NUM7 = GGEK_NUMPAD7,
	NUM8 = GGEK_NUMPAD8,
	NUM9 = GGEK_NUMPAD9,

	MULTIPLY = GGEK_MULTIPLY,
	DIVIDE = GGEK_DIVIDE,
	ADD = GGEK_ADD,
	SUBTRACT = GGEK_SUBTRACT,
	DECIMAL = GGEK_DECIMAL,

	F1 = GGEK_F1,
	F2 = GGEK_F2,
	F3 = GGEK_F3,
	F4 = GGEK_F4,
	F5 = GGEK_F5,
	F6 = GGEK_F6,
	F7 = GGEK_F7,
	F8 = GGEK_F8,
	F9 = GGEK_F9,
	F10 = GGEK_F10,
	F11 = GGEK_F11,
	F12 = GGEK_F12
};

namespace gg 
{
	inline eKey getKey(){ return static_cast<eKey>(gge::Input_GetKey()); }
	inline const char* getChar(){ return gge::Input_GetChar(); }
	inline bool isKup(eKey k){ return gge::Input_IsKeyUp(static_cast<int>(k)); }
	inline bool isKdown(eKey k){ return gge::Input_IsKeyDown(static_cast<int>(k)); }
	inline bool isKkeep(eKey k){ return gge::Input_IsKeyPress(static_cast<int>(k)); }
#if 0
	inline float getX(){ return gge::Input_GetMousePosX(); }
	inline float getY(){ return gge::Input_GetMousePosY(); }
	inline int getScroll(){ return gge::Input_GetMouseWheel(); }
#endif
	inline bool isLup(){ return gge::Input_IsMouseUp(GGEK_LBUTTON); }
	inline bool isLdown(){ return gge::Input_IsMouseDown(GGEK_LBUTTON); }
	inline bool isLkeep(){ return gge::Input_IsMousePress(GGEK_LBUTTON); }

	inline bool isRup(){ return gge::Input_IsMouseUp(GGEK_RBUTTON); }
	inline bool isRdown(){ return gge::Input_IsMouseDown(GGEK_RBUTTON); }
	inline bool isRkeep(){ return gge::Input_IsMousePress(GGEK_RBUTTON); }

	inline bool isMouseOver(){ return gge::Input_IsMouseOver(); }

	inline bool isMouseMup(){ return gge::Input_IsMouseUp(GGEK_MBUTTON); }
	inline bool isMouseMdown(){ return gge::Input_IsMouseDown(GGEK_MBUTTON); }
	inline bool isMouseMkeep(){ return gge::Input_IsMousePress(GGEK_MBUTTON); }

#if 0
	inline bool isMouseUpButM(){ return isMouseLup() || isMouseRup()/* || isMouseMup()*/; }
	inline bool isMouseDownButM(){ return isMouseLdown() || isMouseRdown()/* || isMouseMdown()*/; }
	inline bool isMouseKeepButM(){ return isMouseLkeep() || isMouseRkeep()/* || isMouseMkeep()*/; }
	inline bool isMouseL(){ return isMouseLup() || isMouseLdown() || isMouseLkeep(); }
	inline bool isMouseR(){ return isMouseRup() || isMouseRdown() || isMouseRkeep(); }
	inline bool isMouseM(){ return isMouseMup() || isMouseMdown() || isMouseMkeep() || getMouseWheel(); }
	inline bool isMouseButMoveM(){ return isMouseL() || isMouseR(); }


	inline void hideMouse(bool isHide){ return gge::System_SetState(gge::GGE_STATE_BOOL::GGE_HIDEMOUSE, isHide); }
	inline bool isMouseHidden(){ return gge::System_GetState(gge::GGE_STATE_BOOL::GGE_HIDEMOUSE); }
	inline void setMouse(float x, float y){ return gge::Input_SetMousePos(x, y); }


	inline void drawLine(float x1, float y1, float x2, float y2, gge::guint32 color = 0xffffffff){ return gge::Graph_RenderLine(x1, y1, x2, y2, color); }

	inline void savePNG(const std::string &filename){ return gge::Graph_Snapshot(filename.c_str(), gge::GGE_IMAGE_FORMAT::IMAGE_PNG); }
#endif

	inline void setFullScreen(bool full){ return gge::System_SetState(gge::GGE_STATE_INT::GGE_SCREENMODE, full ? gge::SCREEN_MODE::SCREEN_FULLSCREEN : gge::SCREEN_MODE::SCREEN_WINDOWED); }
	inline bool isFullScreen(){ return gge::System_GetState(gge::GGE_STATE_INT::GGE_SCREENMODE) == gge::SCREEN_MODE::SCREEN_FULLSCREEN; }

	inline HWND getHwnd(){ return (HWND)gge::System_GetState(gge::GGE_STATE_SYS_VAL::GGE_HWND); }
	inline void setTitle(const std::string &title){ gge::System_SetState(gge::GGE_STATE_CHAR::GGE_TITLE, title.c_str()); }

#if 0
	inline void setFPS(int fps){ return gge::System_SetState(gge::GGE_STATE_INT::GGE_FPS, fps); }
	inline int getFPS(){ return gge::System_GetState(gge::GGE_STATE_INT::GGE_FPS); }

	inline gge::guint32 getMilliSec(){ return gge::Timer_GetTime(); }
	inline float getDeltaTime(){ return gge::Timer_GetDelta(); }
	inline float getFrameRate(){ return 1.0 / gge::System_GetState(gge::GGE_STATE_INT::GGE_FPS); }

	inline void randomSeed(gge::guint32 seed){ return gge::Random_Seed(seed); }
	inline int random(){ return gge::Random_Int(0, INT_MAX); }
	inline int random(int a, int b){ return gge::Random_Int(a, b); }
	inline float random(float a, float b){ return gge::Random_Float(a, b); }

	inline bool runURL(const char *url){ return gge::System_Launch(url); }

	template <typename...T>
	inline void log(const T& ...arg){ return gge::System_Log(arg); }
#endif
}