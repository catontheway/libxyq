#include "sXl.h"
#include "_inc.h"

sXl::sXl()
{
	reset();
}


void sXl::reset()
{
	for (int k = 0; k < c4; ++k)
	{
		lvs[k] = 0;
	}
}

bool sXl::lvup(int idx)
{
	if (idx < 0 || idx >= c4)
	{
		return false;
	}
	if (lvs[idx] >= c25)
	{
		return false;
	}
	++lvs[idx];
	return true;
}


bool sXl::lvdown(int idx, bool onlyCheck)
{
	if (idx < 0 || idx >= c4)
	{
		return false;
	}
	if (lvs[idx] <= 0)
	{
		return false;
	}
	if (!onlyCheck)
	{
		--lvs[idx];
	}
	return true;
}


void sXl::set(int atk, int def, int mag, int dmag)
{
	setA(atk, mag);
	setD(def, dmag);
}

void sXl::setA(int a)
{
	setA(a, a);
}

void sXl::setA(int atk, int mag)
{
	lvs[0] = atk;
	lvs[2] = mag;
}

void sXl::setD(int d)
{
	setD(d, d);
}

void sXl::setD(int def, int dmag)
{
	lvs[1] = def;
	lvs[3] = dmag;
}

void sXl::set(int v)
{
	set(v, v);
}

void sXl::set(int a, int d)
{
	setA(a);
	setD(d);
}



#pragma pack (push)
#pragma pack (1)
union sXlSaveLoad
{
	uint v;
	struct
	{
		uint temp : 12;
		uint lv1 : 5;
		uint lv2 : 5;
		uint lv3 : 5;
		uint lv4 : 5;
	};
};
#pragma pack (pop)

void sXl::save()const
{
	sXlSaveLoad xl;
	xl.lv1 = lvs[0];
	xl.lv2 = lvs[1];
	xl.lv3 = lvs[2];
	xl.lv4 = lvs[3];
	sStream& sav = *cSave::getSave();
	sav << xl.v << s_space;
}

void sXl::load()
{
	sStream& sav = *cSave::getLoad();
	sXlSaveLoad xl;
	sav >> xl.v;
	lvs[0] = xl.lv1;
	lvs[1] = xl.lv2;
	lvs[2] = xl.lv3;
	lvs[3] = xl.lv4;
}



int sXl::getExp(int lv)
{
	if (lv == 0)
	{
		return 0;
	}
	int exp = 15;
	for (int i = 1; i < lv; ++i)
	{
		exp += (4 + i * 2) * 1;
	}
	return exp;
}


int sXl::getLv(int lv)
{
	if (lv < 25)
	{
		return 0;
	}
	lv = (lv - 20) / 5;
	if (lv > c25)
	{
		return c25;
	}
	return lv;
}