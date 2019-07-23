#include "txtAction.h"

void txtAction::insert(sAction& act, const ulong& stand, const ulong& walk, const ulong& fight, const ulong& go, const ulong& atk, const ulong& atk2, const ulong& magic, const ulong& def, const ulong& suffer, const ulong& dead, const ulong& back, bool check0 /*= false*/)
{
	if (!check0 || stand > 0)
	act.insert(std::make_pair(eAct::Stand, stand));
	if (!check0 || walk > 0)
	act.insert(std::make_pair(eAct::Walk, walk));
	if (!check0 || fight > 0)
	act.insert(std::make_pair(eAct::Fight, fight));
	if (!check0 || go > 0)
	act.insert(std::make_pair(eAct::Go, go));
	if (!check0 || atk > 0)
	act.insert(std::make_pair(eAct::Atk, atk));
	if (!check0)
	{
		act.insert(std::make_pair(eAct::Atk2, (atk2 == 0) ? atk : atk2));
	}
	else if (atk2 > 0)
	{
		act.insert(std::make_pair((atk == 0) ? eAct::Atk : eAct::Atk2, atk2));
	}
	if (!check0 || magic > 0)
	act.insert(std::make_pair(eAct::Magic, magic));
	if (!check0 || def > 0)
	act.insert(std::make_pair(eAct::Def, def));
	if (!check0 || suffer > 0)
	act.insert(std::make_pair(eAct::Suffer, suffer));
	if (!check0 || dead > 0)
	act.insert(std::make_pair(eAct::Dead, dead));
	if (!check0 || back > 0)
	act.insert(std::make_pair(eAct::Back, back));
}

void txtAction::insert(sAction& act, const ulong& fight, const ulong& go, const ulong& atk, const ulong& atk2, const ulong& magic, const ulong& def, const ulong& suffer, const ulong& dead, const ulong& back, bool check0 /*= false*/)
{
#if 0
	act.insert(std::make_pair(eAct::Fight, fight));
	act.insert(std::make_pair(eAct::Go, go));
	act.insert(std::make_pair(eAct::Atk, atk));
	act.insert(std::make_pair(eAct::Atk2, (atk2 == 0) ? atk : atk2));
	act.insert(std::make_pair(eAct::Magic, magic));
	act.insert(std::make_pair(eAct::Def, def));
	act.insert(std::make_pair(eAct::Suffer, suffer));
	act.insert(std::make_pair(eAct::Dead, dead));
	act.insert(std::make_pair(eAct::Back, back));
#else
	if (!check0 || fight > 0)
	act.insert(std::make_pair(eAct::Fight, fight));
	if (!check0 || go > 0)
	act.insert(std::make_pair(eAct::Go, go));
	if (!check0 || atk > 0)
	act.insert(std::make_pair(eAct::Atk, atk));
	if (!check0)
	{
		act.insert(std::make_pair(eAct::Atk2, (atk2 == 0) ? atk : atk2));
	}
	else if (atk2 > 0)
	{
		act.insert(std::make_pair((atk == 0) ? eAct::Atk : eAct::Atk2, atk2));
	}
	if (!check0 || magic > 0)
	act.insert(std::make_pair(eAct::Magic, magic));
	if (!check0 || def > 0)
	act.insert(std::make_pair(eAct::Def, def));
	if (!check0 || suffer > 0)
	act.insert(std::make_pair(eAct::Suffer, suffer));
	if (!check0 || dead > 0)
	act.insert(std::make_pair(eAct::Dead, dead));
	if (!check0 || back > 0)
	act.insert(std::make_pair(eAct::Back, back));
#endif
}

void txtAction::insert(sAction& act, const ulong& stand, const ulong& walk)
{
	act.insert(std::make_pair(eAct::Stand, stand));
	act.insert(std::make_pair(eAct::Walk, walk));
}


void txtAction::insert(sAction& act, const ulong& small, const ulong& big, const ulong& dialog)
{
	act.insert(std::make_pair(eAct::Small, small));
	act.insert(std::make_pair(eAct::Big, big));
	act.insert(std::make_pair(eAct::Dialog, dialog));
}



void txtAction::insert(sAction& act, const ulong& atk, const ulong& atk2, const ulong& suffer, const ulong& magic, const ulong& def, const ulong& dead)
{
	act.insert(std::make_pair(eAct::eAtk, atk));
	act.insert(std::make_pair(eAct::eAtk2, (atk2 == 0) ? atk : atk2));
	act.insert(std::make_pair(eAct::eSuffer, suffer));
	act.insert(std::make_pair(eAct::eMagic, magic));
	act.insert(std::make_pair(eAct::eDef, def));
	act.insert(std::make_pair(eAct::eDead, dead));
}

const std::vector<ulong>& txtAction::getWeaponTigerDies()
{
	static std::vector<ulong> s_tigerDie = { 0x2208A659, 0x1DDBB1C6, 0x6F6E119A, 0xEC47773C, 0x4CBC0CC5, 0xE74758DC,0xC9417A1A, 0x77ACF46A, 0x436E551F, 0x9953B8A3, 0x32F0DC6C };
	return s_tigerDie;
}

