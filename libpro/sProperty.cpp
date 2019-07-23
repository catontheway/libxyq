#include "sProperty.h"
#include "ccp.h"

sProperty::sProperty(bool pet)
{
	reset(pet);
}

sProperty::sProperty()
{
	reset(true);
}


void sProperty::reset(bool pet)
{
	equips.resize((ispet = pet) ? cEquip::c3 : cEquip::c6);
	fuzhus.resize(ccp::fz3);
	std::fill(fuzhus.begin(), fuzhus.end(), 0);
}

bool sProperty::isSki(eSki e)
{
	for (const auto& ski : skis)
	{
		if (ski.getSki() == e)
		{
			return true;
		}
	}
	return false;
}


bool sProperty::lvup(bool onlyCheck)
{
	return ccp::lvup(*this, onlyCheck);
}


bool sProperty::lvdown(bool onlyCheck)
{
	return ccp::lvdown(*this, onlyCheck);
}



bool sProperty::load(eMod e, bool rename, bool iszz, bool skill)
{
	if (!txtMod::isPet(e))
	{
		return false;
	}
	mod.setMod(e);
	mod.setJinjie(0);
	if (rename)
	{
		name = txtPet::getInstance()->getTables().at(e).name;
	}
	const auto& pzz = txtZz::getInstance()->getTables().at(e);
	if (iszz)
	{
		zz = pzz;
	}
	if (skill)
	{
		skis.resize(pzz.skills.size());
		forv(pzz.skills, k)
		{
			skis.at(k).setData(pzz.skills.at(k));
		}
	}
	return true;
}


txtZz::eAp sProperty::getAp() const
{
	if (txtMod::isPet(mod.emod))
	{
		return txtZz::getInstance()->getTables().at(mod.emod).ap;
	}
	return txtZz::eAp::Rand;
}

int sProperty::getTakeLv() const
{
	if (txtMod::isPet(mod.emod))
	{
		return txtZz::getInstance()->getTables().at(mod.emod).takelv;
	}
	return lv;
}


void sProperty::applyWeapon()
{
	if (ispet)
	{
		return;
	}
	const auto& it = equips.at(2);
	if (!it.isValid())
	{
		mod.setWeapon(it.getType(), sMod::c_1);
		return;
	}
	mod.setWeapon(it.getType(), it.getId());
}

void sProperty::save()const
{
	mod.save(ispet);
	sStream& sav = *cSave::getSave();
	forr(fuzhus, k)
	{
		sav << fuzhus.at(k) << s_space;
	}
	sav << (int)menpai << s_space << name << s_space << lv << s_space << hp << s_space << hp2 << s_space << mp << s_space << ap << s_space;
	zz.save();
	point.save();
	sav << skis.size();
	forr(skis, k)
	{
		sav << (int)skis[k].getSki() << s_space;
	}
	forr(equips, k)
	{
		equips[k].save();
	}
	// О­бщ
	sav << exp.union64 << s_space;
	zz.save();
}


void sProperty::load()
{
	mod.load(ispet);
	sStream& sav = *cSave::getLoad();
	forr(fuzhus, k)
	{
		sav >> fuzhus.at(k);
	}
	int e;
	sav >> e >> name >> lv >> hp >> hp2 >> mp >> ap;
	menpai = (eMenpai)e;
	zz.load();
	point.load();
	sav >> e;
	skis.resize(e);
	forr(skis, k)
	{
		sav >> e;
		skis[k].setData((eSki)e);
	}
	forr(equips, k)
	{
		equips[k].load();
	}
	sav >> exp.union64;
	zz.load();
}