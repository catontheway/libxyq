#include "sZz.h"

sZz::sZz()
{
	reset();
}


void sZz::reset()
{
	atk = def = speed = evoid = hp = mag = grow100 = 0;
}


bool sZz::isValid()
{
	return atk > 0 && def > 0 && hp > 0 && mag > 0 && speed > 0 && evoid > 0 && grow100 > 0;
}


void sZz::correct()
{
	atk = std::max(0, std::min(atk, c1680));
	def = std::max(0, std::min(def, c1680));
	speed = std::max(0, std::min(speed, c1680));
	evoid = std::max(0, std::min(evoid, c1680));
	hp = std::max(0, std::min(hp, c6880));
	mag = std::max(0, std::min(mag, c3680));
	grow100 = std::max(0, std::min(grow100, c130));
}



void sZz::operator=(const txtZz::sZz& zz)
{
	atk = zz.atk;
	def = zz.def;
	hp = zz.hp;
	mag = zz.mp;
	speed = zz.speed;
	evoid = zz.evoid;
	grow100 = zz.grow;
}


#pragma pack (push)
#pragma pack (1)
union sZzSaveLoad
{
	struct
	{
		u64 vint64;
		uint vint;
	};
	struct
	{
		u64 atk : 11;
		u64 def : 11;
		u64 hp : 14;
		u64 mag : 13;
		u64 speed : 11;
		u64 temp64 : 4;
		uint evoid : 11;
		uint grow : 8;
		uint temp : 13;
	};
};
#pragma pack (pop)


void sZz::save()const
{
	sZzSaveLoad zz;
	zz.atk = atk;
	zz.def = def;
	zz.hp = hp;
	zz.mag = mag;
	zz.speed = speed;
	zz.evoid = evoid;
	zz.grow = grow100;

	sStream& sav = *cSave::getSave();
	sav << zz.vint << s_space << zz.vint64 << s_space;
}


void sZz::load()
{
	sStream& sav = *cSave::getLoad();
	sZzSaveLoad zz;
	sav >> zz.vint >> zz.vint64;

	atk = zz.atk;
	def = zz.def;
	hp = zz.hp;
	mag = zz.mag;
	speed = zz.speed;
	evoid = zz.evoid;
	grow100 = zz.grow;
}
