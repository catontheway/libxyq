#pragma once
#include "uiRank.h"


class uiFoot : public uiRank
{
public:
	CREATE_FUNC(uiFoot);
	bool init();
};


class uiFoot2 : public uiRank
{
public:
	CREATE_FUNC(uiFoot2);
	bool init();
};


class uiXiangRui: public uiRank
{
public:
	CREATE_FUNC(uiXiangRui);
	bool init();
};


class uiLeaderTop : public uiRank
{
public:
	CREATE_FUNC(uiLeaderTop);
	bool init();
};