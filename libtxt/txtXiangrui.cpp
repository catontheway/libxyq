#include "txtXiangrui.h"

ccc_txt_instance_cpp(txtXiangrui);


void txtXiangrui::insert(const ulong& stand, const ulong& walk, const ulong& stand2 /*= 0*/, const ulong& walk2 /*= 0*/)
{
	_xiangrui.stand = stand;
	_xiangrui.walk = walk;
	_xiangrui.stand2 = stand2;
	_xiangrui.walk2 = walk2;
	_tables.insert(std::make_pair(_index, _xiangrui));
	++_index;
}

txtXiangrui::txtXiangrui()
{
	std::vector<ulong> uids;
	for (int e = (int)eMod::eJueSe0; e <= (int)eMod::eJueSeEnd; ++e)
	{
		_masterStands.insert(std::make_pair((eMod)e, uids));
		_masterWalks.insert(std::make_pair((eMod)e, uids));
	}

	_masterStands.at(eMod::eJueSeÙÈÎÞÊ¦).push_back(0xC8FDA195);
	_masterStands.at(eMod::eJueSeÌÒØ²Ø²).push_back(0x0C8FDA28);
	_masterStands.at(eMod::eJueSe¹íäìäì).push_back(0x094C5BFB);

	_masterWalks.at(eMod::eJueSeÙÈÎÞÊ¦).push_back(0xC8FDA428);
	_masterWalks.at(eMod::eJueSeÌÒØ²Ø²).push_back(0x0C8FDA70);
	_masterWalks.at(eMod::eJueSe¹íäìäì).push_back(0xFE2D2B18);

	_index = 0;
	//////////////////////////////////////////////////////////////////////////
	insert(0x876E0D2B, 0x6088EDAC, 0x9AF401B2, 0xC541DCEA);
	insert(0xB5DFFC71, 0xC5B4FDEF, 0xCA6F2BB0, 0x7E3ADBB8);
}


