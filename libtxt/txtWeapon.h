#pragma once
#include "_txtinc.h"
#include "eIcon.h"
#include "eMod.h"
#include "txtAction.h"

ccc_txt_class_begin(txtWeapon);

txtWeapon();

typedef std::array<txtAction::sAction, 11> sAct11;
struct sWeapon
{
	eMod master;
	int masterIdx;
	sAct11 actions;
	sAct11 actionMaps;
};
typedef std::array<sWeapon, 2> sWeapon2;
typedef std::map<eMod, std::vector<eIcon>> sWeaponLists;

const sWeaponLists& getWeaponLists(){ return _weaponsList; }

int getMasterIndex(eMod master, eIcon wtype, int wid);
const txtAction::sAction& getAction(eMod master, eIcon wtype, int wid);
const txtAction::sAction& getActionMap(eMod master, eIcon wtype, int wid);
private:
	void initTable(eIcon icon, eMod m1, int i1, eMod m2, int i2);
	void initTable(eIcon icon, eMod m1);
	void insert1(const ulong& stand, const ulong&  walk, const ulong&  fight, const ulong&  go, const ulong&  atk, const ulong&  atk2, const ulong&  magic, const ulong&  def, const ulong&  suffer, const ulong&  dead, const ulong&  back);
	void insert2(const ulong& stand, const ulong&  walk, const ulong&  fight, const ulong&  go, const ulong&  atk, const ulong&  atk2, const ulong&  magic, const ulong&  def, const ulong&  suffer, const ulong&  dead, const ulong&  back);
	sAct11* _actions1;
	sAct11* _actions2;
	sAct11* _actionsMap1;
	sAct11* _actionsMap2;
	int _idx;

	sWeaponLists _weaponsList;
ccc_txt_class_end(eIcon, sWeapon2);