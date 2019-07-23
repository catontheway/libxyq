#pragma once
#include "_txtinc.h"
#include "eIcon.h"
#include "eMod.h"
#include "eSkill.h"

class txtIcon
{
public:
	ccc_txt_instance_h(txtIcon);
	txtIcon();
	struct sIcon
	{
		int price;
		ulong small;
		ulong big;
		std::string name;
		std::string desc;
	};
	typedef std::map<int, sIcon> sTable;

	static const int c1000 = 1000;
	// 返回 0~16
	static int getWeaponLv1ById(int id);
	// 返回 0~10
	static int getWeaponIdxById(int id);
	// 返回 0~16
	static int getNeckBeltLv1ById(int id);
private:
	void initWeapon();
	void initEquip();
	void initMedicineCook();
	void initStone();
	void initJiaju();
	void initMenpai();
	// 价格 == 技能
	void initSkill();
	void initCard();
	void init();
	
	void initIdx();
	void initTable(eIcon e);
	void insert(ulong small, ulong big, int temp, const std::string& name, const std::string&  desc);
	void insertWeapon(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc);
	void insertJiaju(eIcon e, ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc);
	void insertJiaju(eIcon e, ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc, const std::vector<ulong>& uids);
	void insertJiaju1(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc);
	void insertJiaju1(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc, const std::vector<ulong>& uids);
	void insertJiaju2(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc);
	void insertJiaju2(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc, const std::vector<ulong>& uids);
	void insertJiaju3(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc);
	void insertJiaju3(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc, const std::vector<ulong>& uids);
	void insertJiaju4(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc);
	void insertJiaju4(ulong small, ulong big, int temp, const std::string&  name, const std::string&  desc, const std::vector<ulong>& uids);
	void insertMenpai(ulong small, ulong big, const std::string&  name);
	void insertSkill(ulong small, ulong big, eSkill e, const std::string&  name, const std::string&  desc, const std::string& emtpy = "");
	void insertCard(ulong small, ulong big, eMod e);

	int _idx;
	sIcon _item;
	sTable* _table = nullptr;
	std::map<eIcon, sTable> _tables;
public:
	const std::map<eIcon, sTable>& getTables(){ return _tables; }



	static const ulong cSkiSmall = 0x73C1B59D;
	static const ulong cSkiBig = 0xADEE4E4D;
	static const ulong cHeadSmall = 0x42475124;
};