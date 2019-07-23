#pragma once
#include "_txtinc.h"
#include "eIcon.h"

ccc_txt_class_begin(txtJiaju);

txtJiaju();
struct sJiaju
{
	int lv;
	std::vector<ulong> uids;
};

typedef std::map<int, sJiaju> sTable;

friend class txtIcon;

ccc_txt_class_end(eIcon, sTable);