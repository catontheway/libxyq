#include "cMain.h"
#include "cNode.h"

static cNode* s_root = nullptr;
static Vec2 s_vMouse;
cNode* cNode::getRoot()
{
	return s_root;
}

const Vec2& cNode::getMouse()
{
	return s_vMouse;
}

bool frame()
{
	s_vMouse.x = gge::Input_GetMousePosX();
	s_vMouse.y = gge::Input_GetMousePosY();
	s_root->setSnatch(s_vMouse);
	s_root->doUpdate(gge::Timer_GetDelta());
	if (gge::Graph_BeginScene())
	{
		gge::Graph_Clear(0x00101010);
		s_root->doRender();
		gge::Graph_EndScene();
	}
	cAutoReleasePool::getInstance()->clear();
	return false;
}


bool cMain::init(int w /*= 640*/, int h /*= 480*/)
{
	if (!gge::Engine_Create(GGE_VERSION))
	{
		return false;
	}
	gge::System_SetState(gge::GGE_STATE_INT::GGE_SCREENWIDTH, w);
	gge::System_SetState(gge::GGE_STATE_INT::GGE_SCREENHEIGHT, h);
	gge::System_SetState(gge::GGE_TITLE, "Galaxy2D Game Engine");
	gge::System_SetState(gge::GGE_STATE_INT::GGE_ICON, 101);
	gge::System_SetState(gge::GGE_STATE_INT::GGE_FPS, 60);
	gge::System_SetState(gge::GGE_STATE_BOOL::GGE_VSYNC, true);
	gge::System_SetState(gge::GGE_STATE_BOOL::GGE_HIDEMOUSE, false);
//	gge::System_SetState(gge::GGE_STATE_CHAR::GGE_LOGNAME, "xyq2d.log");
//	gge::System_SetState(gge::GGE_STATE_BOOL::GGE_DEBUGLOG, false);
	s_root = cNode::create();
	if (s_root == nullptr)
	{
		return false;
	}
	s_root->retain();

	if (!gge::System_Initiate())
	{
		return false;
	}

	gge::System_SetState(gge::GGE_STATE_BOOL_FUN::GGE_FRAMEFUNC, frame);
	return true;
}


void cMain::start()
{
	gge::System_Start();
	gge::Engine_Release();
}


void cMain::setExit(gge::GGE_BOOLFUN exitFunc)
{
	gge::System_SetState(gge::GGE_STATE_BOOL_FUN::GGE_EXITFUNC, exitFunc);
}

void cMain::setGain(gge::GGE_BOOLFUN gainFunc)
{
	gge::System_SetState(gge::GGE_STATE_BOOL_FUN::GGE_FOCUSLOSTFUNC, gainFunc);
}

void cMain::setLost(gge::GGE_BOOLFUN lostFunc)
{
	gge::System_SetState(gge::GGE_STATE_BOOL_FUN::GGE_FOCUSGAINFUNC, lostFunc);
}

void cMain::setMsg(gge::GGE_MSGFUN msgFunc)
{
	gge::System_SetState(gge::GGE_MESSAGEFUNC, msgFunc);
}