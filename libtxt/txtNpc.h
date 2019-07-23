#pragma once
#include "_txtinc.h"
#include "eMod.h"

ccc_txt_class_begin(txtNpc);

txtNpc();
struct sNpc
{
	ulong stand, walk, dialog;
	std::string name;
};

ccc_txt_class_end(eMod, sNpc);