#pragma once
#include "_txtinc.h"
#include "eAct.h"

class txtAction
{
public:
	typedef std::map<eAct, ulong> sAction;
//	_stand_, _walk_, _fight_, _go_, _atk_, _atk2_, _magic_, _def_, _suffer_, _dead_, _back_
	static void insert(sAction& act, const ulong& stand, const ulong&  walk, const ulong&  fight, const ulong&  go, const ulong&  atk, const ulong&  atk2, const ulong&  magic, const ulong&  def, const ulong&  suffer, const ulong&  dead, const ulong&  back, bool check0 = false);

	static void insert(sAction& act, const ulong&  fight, const ulong&  go, const ulong&  atk, const ulong&  atk2, const ulong&  magic, const ulong&  def, const ulong&  suffer, const ulong&  dead, const ulong&  back, bool check0 = false);

	static void insert(sAction& act, const ulong& stand, const ulong&  walk);

	static void insert(sAction& act, const ulong& small, const ulong&  big, const ulong&  dialog);

//	_atk_, _atk2_, _suffer_, _magic_, _def_, _dead_
	static void insert(sAction& act, const ulong&  atk, const ulong&  atk2, const ulong&  suffer, const ulong&  magic, const ulong&  def, const ulong&  dead);

	static const std::vector<ulong>& getWeaponTigerDies();
};