#pragma once
#include "_txtinc.h"
#include "eMod.h"
#include "txtAction.h"

ccc_txt_class_begin(txtRole);
txtRole();

struct sPoint{ int offx, atk, magic; };

struct sRole
{
	ulong color;
	std::string name;
	std::array<txtAction::sAction, 3> heads;
	std::array<txtAction::sAction, 2> faces;
	txtAction::sAction bodies;
	std::vector<txtAction::sAction> actionMaps;
	std::vector<txtAction::sAction> actions;
	std::vector<txtAction::sAction> sounds;
	std::vector<sPoint> points;
};

ccc_txt_class_end(eMod, sRole);