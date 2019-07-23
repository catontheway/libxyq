#include "uiFoot.h"
#include "../libtxt/txtEasy.h"
#include "../libtxt/txtXiangrui.h"

static const auto& txt = txtEasy::getInstance();
static const auto& dazzles = txt->getDazzles();
bool uiFoot::init()
{
	if (!uiRank::init(190, 120))
	{
		return false;
	}
	setTitle("◊„º£");

	load(0, cSp::c0, cSp::c0, false);
	forv(dazzles, k)
	{
		load(k + 1, dazzles.at(k), cSp::c0, true);
	}
	load();

	return true;
}


//////////////////////////////////////////////////////////////////////////
static const auto& foots = txt->getFoots();
bool uiFoot2::init()
{
	if (!uiRank::init(190, 150))
	{
		return false;
	}
	setTitle("¿«◊¶”°");

	load(0, cSp::c0, cSp::c0, false);
	forv(foots, k)
	{
		load(k + 1, foots.at(k), cSp::c0, true);
	}
	load();

	return true;
}


//////////////////////////////////////////////////////////////////////////
// static const auto& xiangrui = txtZuoqi::getInstance()->getXiangruis();
static const auto& xiangrui = txtXiangrui::getInstance()->getTables();
bool uiXiangRui::init()
{
	if (!uiRank::init(200, 180))
	{
		return false;
	}
	setTitle("œÈ»");

	load(0, cSp::c0, cSp::c0, false);
	forv(xiangrui, k)
	{
		const auto& xr = xiangrui.at(k);
		load(k + 1, xr.stand, xr.stand2, true);
	}
	load();
	return true;
}

//////////////////////////////////////////////////////////////////////////
static const auto& top = txt->getTops();
bool uiLeaderTop::init()
{
	if (!uiRank::init(100, 120))
	{
		return false;
	}
	setTitle("∂”≥§¡Ó≈∆");

	load(0, cSp::c0, cSp::c0, false);
	forv(top, k)
	{
		load(k + 1,top.at(k), cSp::c0, true);
	}
	load();
	return true;
}
