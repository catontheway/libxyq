#pragma once
#include "_txtinc.h"

class txtEasy
{
public:
	ccc_txt_instance_h(txtEasy);
	typedef std::map<int, ulong> sTable;
	const sTable& getChats();
	const sTable& getTops();
	const sTable& getTransmits();
	const sTable& getDazzles();
	const sTable& getFoots();
	//////////////////////////////////////////////////////////////////////////
	const sTable& getMagicWhat();
	const sTable& get_magic();
	const sTable& getMagic();
	const sTable& getMagicMove();
	const sTable& getMagicImpact();
	const sTable& getMagicState();
	const sTable& getMagicStateUnkown();
	const sTable& getMagicIter();
	const sTable& getMagicUnkown();
private:
	void initIdx();
	void insert(sTable& table, ulong uid);
	void insertChat(ulong uid){ insert(_tableChat, uid); }
	void insertTop(ulong uid){ insert(_tableTop, uid); }
	void insertTransmit(ulong uid){ insert(_tableTransmit, uid); }
	void insertDazzle(ulong uid){ insert(_tableDazzle, uid); }
	void insertFoot(ulong uid){ insert(_tableFoot, uid); }
	sTable _tableChat, _tableTop, _tableTransmit, _tableDazzle, _tableFoot;
	sTable _tableMagicWhat, _table_magic, _tableMagic, _tableMagicMove, _tableMagicImpact, _tableMagicState, _tableMagicStateUnkown, _tableMagicIter, _tableMagicUnkown;
	int _idx;
};