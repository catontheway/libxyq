#include "sRole.h"
#include "ccp.h"

sRole::sRole() : sProperty(false)
{
	acces.resize(ccp::acce8);
	fabaos.resize(sItem::c20);
}


bool sRole::lvdown(bool onlyCheck)
{
	if (!sProperty::lvdown(onlyCheck))
	{
		return false;
	}
	if (!onlyCheck)
	{
		ccp::lvdown(*this, onlyCheck);
	}
	return true;
}


void sRole::unPet()
{ 
	fight = cFight_1;
}


bool sRole::isPeting()
{ 
	return fight >= 0 && fight < pets.size();
}

const sProperty& sRole::getPet()const
{ 
	return pets.at(fight);
}

sProperty& sRole::getPet()
{
	return pets.at(fight);
}


bool sRole::setPet(int fig, bool onlyCheck)
{
	if (fig < 0 && fig >= pets.size())
	{
		return false;
	}
	const auto& p = pets.at(fig);
	if (p.lv > lv + ccp::lvGapPet || p.getTakeLv() > lv)
	{
		return false;
	}
	if (!onlyCheck)
	{
		fight = fig;
	}
	return true;
}

void sRole::doMod()
{
	if (onMod != nullptr)
	{
		onMod(mod);
	}
}


void sRole::save()const
{
	sProperty::save();
	sStream& sav = *cSave::getSave();
	sav << skilv << s_space;
	xl.save();
	xlbb.save();
	forr(acces, k)
	{
		sav << (int)acces.at(k).getSki() << s_space;
	}
	forr(fabaos, k)
	{
		fabaos.at(k).save();
	}
	sav << pets.size();
	forr(pets, k)
	{
		pets.at(k).save();
	}
	sav << fight << s_space;
}

void sRole::load()
{
	sProperty::load();
	sStream& sav = *cSave::getLoad();
	int e;
	sav >> e >> skilv;
	menpai = (eMenpai)e;
	xl.load();
	xlbb.load();
	forr(acces, k)
	{
		sav >> e;
		acces.at(k).setData((eSki)e);
	}
	forr(fabaos, k)
	{
		fabaos.at(k).load();
	}
	sav >> e;
	pets.resize(e);
	forr(pets, k)
	{
		pets.at(k).load();
	}
	sav >> fight;
}
