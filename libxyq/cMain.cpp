#include "cMain.h"
#include "../libutil/cCursor.h"
#include "../libutil/cGame.h"
#include "../libutil/cMouse.h"
#include "../libutil/cSprite.h"
#include "../libui/uiManager.h"

static cSprite* spriteCursor = nullptr;
static bool s_cursor = false;
void cCursor::setCursor(eCursor e)
{
	_cursor = e;
	if (!s_cursor)
	{
		static std::map<eCursor, ulong> s_cursorMap =
		{
			{ eCursor::Give, 0xCF1D211E },
			{ eCursor::Normal, 0x535C1994 },
			{ eCursor::Forbig, 0x1733E33B },
			{ eCursor::Atk, 0x1FBC5273 },
			{ eCursor::Magic, 0xB48A9B3D },
			{ eCursor::Team, 406701913 },
			{ eCursor::Hand, 0x5A055B13 },
			{ eCursor::Trade, 0xB87E0F0C },
			{ eCursor::Guard, 0xB352AE45 },
			{ eCursor::Grab, 0xC5750B15 },
			{ eCursor::No, 0xFC03AFF1 },
		};
		spriteCursor->load(s_cursorMap.at(e));
	}
	auto ui = ccu::getManager();
	if (ui != nullptr)
	{
		ui->setVisible(!(e == eCursor::Atk || e == eCursor::Give || e == eCursor::Trade || e == eCursor::Team));
	}
}



static auto app = cApp::getInstance();
static auto input = cInput::getInstance();
static cMain* s_mainApp = nullptr;
LRESULT CALLBACK proc(HWND hWnd, unsigned int uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		if (s_mainApp != nullptr)
		{
			s_mainApp->close();
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYUP:
		if (wParam == VK_RETURN && input->isAlt())
		{
			static bool s_isfull = false;
			app->setScreen(s_isfull = !s_isfull);
		}
		break;
	case WM_MOVE:
		if (hWnd == app->getHwnd())
		{
			app->resize();
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int cMain::uMain(HINSTANCE hInstance, cMain* mainApp, int fps /* = 60 */, int w /* = 0 */, int h /* = 0 */, int cw /* = 0 */, bool cursor /* = false */)
{
	s_cursor = cursor;
	auto class_proc = app->initClass(hInstance, "ÀÇ±¦×îË§");
	class_proc.lpfnWndProc = proc;
	if (!RegisterClass(&class_proc))
	{
		return 0;
	}
	s_mainApp = mainApp;
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	if (w == 0 && h == 0)
	{
		w = sw - 32;
		h = sh - 96;
	}
	app->setSize(sw, sh, w, h, cw);
	if (!app->init(hInstance, class_proc.lpszClassName))
	{
		return 0;
	}
	cGame::getInstance()->setwh(w, h);

	app->start();

	float inv = 1.0f / fps;
	auto loop = cLoop::getInstance();
	loop->init(inv);

	auto windsoul = cWindSoul::getInstance();
	windsoul->create(app->getHwnd(), app->getChildHwnd(), w, h, cw);

	auto director = Director::getInstance();
	director->setWinSize(Size(w, h));
	director->setProjection(Director::Projection::_2D);
	director->setAnimationInterval(inv);

	input->init(app->getHwnd(), hInstance);

	auto mouse = cMouse::getInstance();

	auto stepper = cStepper::getInstance();
	auto walker = cStepper::getWalk();

	walker->setSpeed(1.6f);

	auto draw = cDraw::getInstance();

	float delta = inv;
	float deltaTitle = 0;

	mainApp->setTitle(nullptr, app->getChildHwnd());

	spriteCursor = cSprite::create();
	spriteCursor->retain();
	cCursor::getInstance()->setCursor(eCursor::Normal);
	Vec2 vMouse;
	Scene* runningScene = mainApp->runScene();
	director->runWithScene(runningScene);
	while (true)
	{
		if (loop->peek())
		{
			if (loop->isBreak())
			{
				break;
			}
			continue;
		}
		if (!loop->loop())
		{
			continue;
		}
		if ((deltaTitle += delta) > 1)
		{
			deltaTitle -= 1;
			mainApp->setTitle(app->getHwnd(), nullptr);
		}
		input->update();
		if (input->isAlt() && input->isKdown(DIK_RETURN))
		{
			app->switchScreen();
		}
		vMouse = input->getMouse();
		if (vMouse.x < 0 || vMouse.x > w || vMouse.y < 0 || vMouse.y > h)
		{
			if (ShowCursor(true) > 1) ShowCursor(false);
		}
		else
		{
			if (ShowCursor(cursor) < -1)ShowCursor(!(cursor));
		}
		stepper->step(delta);
		walker->step(delta);
		runningScene = director->getRunningScene();
		if (runningScene != nullptr)
		{
			mouse->step(delta, runningScene);
		}

		draw->clear();
		mainApp->beforeMainLoop();
		director->mainLoop();
		mainApp->afterMainLoop();
		//////////////////////////////////////////////////////////////////////////
		if (walker->isStepd())
		{
			if (spriteCursor->cSpriteCache::step())
			{
				spriteCursor->setFrame(0);
			}
		}
		spriteCursor->setPosition(vMouse);
		spriteCursor->visit();
		//////////////////////////////////////////////////////////////////////////
		draw->render();

		windsoul->clear();
		windsoul->blit();
		delta = director->getDeltaTime();
	}

	return 0;
}


void cMain::close()
{

}

void cMain::setTitle(HWND hwnd, HWND child)
{
}

cocos2d::Scene* cMain::runScene()
{
	return Scene::create();
}


void cMain::beforeMainLoop()
{

}

void cMain::afterMainLoop()
{

}
