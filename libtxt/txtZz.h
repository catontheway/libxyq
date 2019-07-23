#pragma once
#include "_txtinc.h"
#include "eMod.h"
#include "eSkill.h"

ccc_txt_class_begin(txtZz);

txtZz();

enum class eAp
{
	GiveMagic,
	Atk,
	Magic,
	Rand,
};

struct sZz
{
	eAp ap;
	int takelv;
	int atk;
	int def;
	int hp;
	int mp;
	int speed;
	int evoid;
	int grow;
	std::vector<eSkill> skills;
};


private:
	void init(eMod pet, int takelv, eAp ap);
	void insert(int atk, int def, int hp, int mp, int speed, int evoid, int grow);
	void insert(eSkill ski);
	void insert(eSkill ski, eSkill ski2);
	void insert(eSkill ski, eSkill ski2, eSkill ski3);
	void insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4);
	void insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4, eSkill ski5);
	void insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4, eSkill ski5, eSkill ski6);
	void insert(eSkill ski, eSkill ski2, eSkill ski3, eSkill ski4, eSkill ski5, eSkill ski6, eSkill ski7);
	void correctSkill();

	sZz* _zz;
	std::vector<eSkill>* _skills;
ccc_txt_class_end(eMod, sZz);