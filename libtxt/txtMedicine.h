#pragma once
#include "_txtinc.h"
#include "eIcon.h"


class txtMedicine
{
public:
	ccc_txt_instance_h(txtMedicine);

	struct sEffect
	{
		int lv, hp, hp2, mp;
		bool isAll;
	};

	const sEffect& getEffect(int id){ return effects.at(id); }
	int getPoisionId(){ return _posionId; }
	int getSealId(){ return _sealId; }
	int getRelifeId(){ return _relifeId; }
	int getRelifeId2(){ return _relifeId2; }
private:
	friend class txtIcon;
	std::map<int, sEffect> effects;
	int _posionId = -1;
	int _sealId = -1;
	int _relifeId = -1;
	int _relifeId2 = -1;
};




class txtCook
{
public:
	ccc_txt_instance_h(txtCook);

	struct sEffect
	{
		int hp, hp2, mp, ap;
		bool isNormal;
	};

	const sEffect& getEffect(int id){ return effects.at(id); }
private:
	friend class txtIcon;
	std::map<int, sEffect> effects;
};