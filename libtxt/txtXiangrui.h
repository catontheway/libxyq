#pragma once
#include "_txtinc.h"
#include "eMod.h"

ccc_txt_class_begin(txtXiangrui);

txtXiangrui();

struct sXiangrui
{
	ulong stand;
	ulong walk;
	ulong stand2;
	ulong walk2;
};

typedef std::map<eMod, std::vector<ulong>> sMasterPos;
const sMasterPos& getMasterStands() { return _masterStands; }
const sMasterPos& getMasterWalks() { return _masterWalks; }

private:
	void insert(const ulong& stand, const ulong& walk, const ulong& stand2 = 0, const ulong& walk2 = 0);

	sXiangrui _xiangrui;
	int _index;
	sMasterPos _masterStands;
	sMasterPos _masterWalks;

friend class txtZuoqi;
ccc_txt_class_end(int, sXiangrui);