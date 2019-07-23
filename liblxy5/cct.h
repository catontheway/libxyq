#pragma once
#include "_global.h"
namespace cct
{
	static const int MinPoint = 10;
	static const int PointRemian = 0; // 250;
	static const int MaxXL = 25;
	static const int LvFor·ÉÉý = 125;
	static const int MaxRoleLv = 175;
	static const int MaxBabyLv = 180;
	static const int MaxSkillLv = 180;
	static const int MaxStoneLv = 16;
	static const int MaxStoneWJB = 20;
	static const int LvFor¶É½Ù = 155;
	static const int LvGapFromRoleAndBaby = 10;
	static const int LvGapFromRoleAndSkill = 10;

	bool isWeapon(const sItem* item);
	bool isWeapon(const sItem2* item);
	bool isEquipButWeapon(const sItem* item);
	bool isEquipButWeapon(const sItem2* item);
	bool isEquip(const sItem* item);
	bool isEquip(const sItem2* item);
	bool isEquipBB(const sItem* item);
	bool isEquipBB(const sItem2* item);
	bool isWJB(const sItem2* item);
	vector<int> getSpecialSkills();
	int getModel(int model);
	int getMenpai(int mp);
	int getCurrMaxXiulianLv(int pclv);
	void setINT(int i, int v);
	int getINT(int i);
	void switchINT(int i);
	void setDelta(ulong magic, int& delta);
	void setMagicPos(ulong magic, int& pos);
	int getPetModel(int lvTake1 = 0, int lvTake2 = 85, bool gadIf0 = false);
	void saveGlobal(sOstream& File);
	void loadGlobal(sIstream& File);
	void autoSave();
	const vector<string>& getFields();
	const vector<string>& getCitiesButCA();
}
