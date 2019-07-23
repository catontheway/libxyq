#include "sMod.h"
#include "cEquip.h"
#include "../libutil/cGame.h"

const int sMod::c_1 = -1;

bool sMod::setRole(sMod::eRole e)
{
	switch (e)
	{
	case sMod::eRole::weapon:
		if (!setWeapon(eweapon, weaponId))
		{
			setWeaponUnsnatch();
			return false;
		}
		break;
	case sMod::eRole::zq:
		if (!setZuoqi(ezq))
		{
			if (erole == eRole::zq)
			{
				erole = eRole::weapon;
			}
			return false;
		}
		break;
	case sMod::eRole::xr:
		if (!txtMod::isRole(emod))
		{
			if (erole == eRole::xr)
			{
				erole = eRole::weapon;
			}
			return false;
		}
		break;
	case sMod::eRole::card:
		if (!txtMod::isPet(ecard))
		{
			if (erole == eRole::card)
			{
				erole = eRole::weapon;
			}
			return false;
		}
		break;
	default:
		break;
	}
	erole = e;
	return true;
}

void sMod::setMod(eMod e)
{
	emod = e;
	if (txtMod::isNpc(e))
	{
		return;
	}
	if (txtMod::isPet(e))
	{
		setJinjie(jdx);
		return;
	}

	setRole(erole);
}

bool sMod::setWeapon(eIcon e, int wid)
{
	if (!txtMod::isRole(emod) || !cEquip::isWeapon(e))
	{
		return false;
	}
	const auto& wlist = txtWeapon::getInstance()->getWeaponLists().at(emod);
	if (!ccc_find(wlist, e))
	{
		return false;
	}
	eweapon = e;
	weaponId = wid;
	weaponMasterIdx = txtWeapon::getInstance()->getMasterIndex(emod, e, wid);
	wid = txtIcon::getWeaponIdxById(wid);
	if (e == eIcon::¹­åóg && (wid == 3 || wid == 7))
	{
		weaponMasterIdx = 2;
	}
	return true;
}

bool sMod::setWeapon(int wlv)
{
	if (!txtMod::isRole(emod))
	{
		return false;
	}
	const auto& wlist = txtWeapon::getInstance()->getWeaponLists().at(emod);
	eIcon e = wlist.at(cc::random(0U, wlist.size() - 1));
	int wd = cEquip::getId(e, wlv);
	return setWeapon(e, wd);
}


void sMod::setWeaponUnsnatch()
{
	weaponId = c_1;
}

bool sMod::setZuoqi(eZuoqi e)
{
	if (!txtMod::isRole(emod))
	{
		return false;
	}
	const auto& zq = txtZuoqi::getInstance()->getTables().at(e);
	for (const auto& m : zq.masters)
	{
		if (m.first != emod)
		{
			continue;
		}
		ezq = e;
		if (!setZs(zsid))
		{
			zsid = c_1;
		}
		return true;
	}
	return false;
}

bool sMod::setZs(int zs)
{
	if (zs / 3 == (int)ezq)
	{
		zsid = zs;
		return true;
	}
	return false;
}

bool sMod::setXr(int idx)
{
	xrid = idx;
	return true;
}

bool sMod::setXr()
{
	if (!txtMod::isRole(emod))
	{
		return false;
	}
	const auto& stands = txtZuoqi::getInstance()->getMasterStands().at(emod);
	if (++xridx >= stands.size())
	{
		xridx = 0;
	}
	return true;
}

bool sMod::setCard(eMod e)
{
	if (!txtMod::isPet(e))
	{
		return false;
	}
	ecard = e;
	return true;
}

bool sMod::setJinjie(int jdx_)
{
	const eMod& e = txtMod::isPet(emod) ? emod : ecard;
	if (!txtMod::isPet(e))
	{
		return false;
	}
	const auto& pet = txtPet::getInstance()->getTables().at(e);
	jdx = jdx_ >= pet.jinjies.size() ? 0 : jdx_;
	jdx_ = pet.jinjies.at(jdx).size();
	if (dyePets.size() < jdx_)
	{
		dyePets.resize(jdx_);
	}
	return true;
}

bool sMod::setJinjie()
{
	return setJinjie(jdx + 1);
}


bool sMod::setDujie(int dj)
{
	if (dj < 0 || dj >= 3)
	{
		return false;
	}
	dujie = dj;
	return true;
}

void sMod::apply(sActs& sps, bool fight, eIterType iter) const 
{
	if (emod == eMod::eModNone)
	{
		std::vector<sSp> sp;
		sps.insert(std::make_pair(eAct::Stand, sp));
		sps.insert(std::make_pair(eAct::Walk, sp));
		return;
	}
	if (txtMod::isNpc(emod))
	{
		const auto& npc = txtNpc::getInstance()->getTables().at(emod);
		sps.clear();
		std::vector<sSp> sp(1);
		sp.at(0).uid = npc.stand;
		sps.insert(std::make_pair(eAct::Stand, sp));
		sp.at(0).uid = npc.walk;
		sps.insert(std::make_pair(eAct::Walk, sp));
		return;
	}
	if (txtMod::isPet(emod) || txtMod::isPet(ecard))
	{
		const auto& pet = txtPet::getInstance()->getTables().at(txtMod::isPet(emod) ? emod : ecard);
		
		std::vector<txtAction::sAction> acts;
		std::vector<ulong> cids;
		if (pet.jinjies.empty())
		{
			acts = fight ? pet.actions : pet.actionMaps;
			cids = pet.colors;
		}
		else
		{
			const auto& as = fight ? pet.actions : pet.actionMaps;
			const auto& jjs = pet.jinjies.at(jdx % pet.jinjies.size());
			forv(jjs, k)
			{
				acts.push_back(as.at(jjs.at(k)));
				cids.push_back(pet.colors.at(jjs.at(k)));
			}
		}
		sps.clear();
		std::vector<sSp> sp;
		for (const auto& a : acts.at(0))
		{
			sps.insert(std::make_pair(a.first, sp));
		}
		sSp spMatrixs;
		forv(acts, k)
		{
			const auto& act = acts.at(k);
			const auto& cid = cids.at(k);
			cDye::toMatrixs(spMatrixs.matrixs, cid, dyePets.at(k));
			for (const auto& a : act)
			{
				spMatrixs.uid = a.second;
				sps.at(a.first).push_back(spMatrixs);
			}
		}
		if (fight && sps.find(eAct::Atk2) == sps.end())
		{
			sps.insert(std::make_pair(eAct::Atk2, sps.at(eAct::Atk)));
		}
		return;
	}

	const auto& r = txtRole::getInstance()->getTables().at(emod);
	sSp spRole, spMatrixs;
	cDye::toMatrixs(spRole.matrixs, r.color, dyeRole);
	std::vector<sSp> sp;
	if (!fight && erole == eRole::zq)
	{
		const auto& zq = txtZuoqi::getInstance()->getTables().at(ezq);
		bool iszs = (zsid != c_1 && zsid / 3 == (int)ezq);
		sps.clear();
		sps.insert(std::make_pair(eAct::Stand, sp));
		sps.insert(std::make_pair(eAct::Walk, sp));
		auto& stands = sps.at(eAct::Stand);
		auto& walks = sps.at(eAct::Walk);

		cDye::toMatrixs(spMatrixs.matrixs, zq.color, dyeZq);
		spMatrixs.uid = zq.stand;
		stands.push_back(spMatrixs);
		spMatrixs.uid = zq.walk;
		walks.push_back(spMatrixs);
		if (iszs)
		{
			const auto& zs = txtZuoqi::getInstance()->getZhuangshis().at(zsid);
			cDye::toMatrixs(spMatrixs.matrixs, zs.color, dyeZs);
			spMatrixs.uid = zs.stand;
			stands.push_back(spMatrixs);
			spMatrixs.uid = zs.walk;
			sps.at(eAct::Walk).push_back(spMatrixs);
		}
		spRole.uid = zq.masters.at(emod).stand;
		stands.push_back(spRole);
		spRole.uid = zq.masters.at(emod).walk;
		walks.push_back(spRole);
		if (iszs)
		{
			const auto& zs = txtZuoqi::getInstance()->getZhuangshis().at(zsid);
			spMatrixs.uid = zs.masters.at(emod).stand;
			stands.push_back(spMatrixs);
			spMatrixs.uid = zs.masters.at(emod).walk;
			walks.push_back(spMatrixs);
		}
		return;
	}
	if (!fight && erole == eRole::xr)
	{
		const auto& xr = txtXiangrui::getInstance()->getTables().at(xrid);
		const auto& sts = txtXiangrui::getInstance()->getMasterStands().at(emod);
		const auto& was = txtXiangrui::getInstance()->getMasterWalks().at(emod);
		sps.clear();
		sps.insert(std::make_pair(eAct::Stand, sp));
		sps.insert(std::make_pair(eAct::Walk, sp));
		auto& stands = sps.at(eAct::Stand);
		auto& walks = sps.at(eAct::Walk);

		spMatrixs.uid = xr.stand;
		stands.push_back(spMatrixs);
		spMatrixs.uid = xr.walk;
		stands.push_back(spMatrixs);
		if (xr.stand2 != cSp::c0)
		{
			spMatrixs.uid = xr.stand2;
			stands.push_back(spMatrixs);
		}
		if (xr.walk2 != cSp::c0)
		{
			spMatrixs.uid = xr.walk2;
			stands.push_back(spMatrixs);
		}
		spRole.uid = sts.at(xridx % sts.size());
		stands.push_back(spRole);
		spRole.uid = was.at(xridx % was.size());
		stands.push_back(spRole);
		return;
	}

	const auto& acts = fight ? r.actions.at(weaponMasterIdx % r.actions.size()) : r.actionMaps.at(weaponMasterIdx % r.actionMaps.size());
	if (fight)
	{
		sps.clear();
		for (const auto& a : acts)
		{
			spRole.uid = a.second;
			sp.clear();
			sp.push_back(spRole);
			sps.insert(std::make_pair(a.first, sp));
		}
	}
	else
	{
		sps.clear();
		sps.insert(std::make_pair(eAct::Stand, sp));
		sps.insert(std::make_pair(eAct::Walk, sp));
		auto& stands = sps.at(eAct::Stand);
		auto& walks = sps.at(eAct::Walk);

		spRole.uid = acts.at(eAct::Stand);
		stands.push_back(spRole);
		spRole.uid = acts.at(eAct::Walk);
		walks.push_back(spRole);
	}

	if (weaponId == c_1)
	{
		if (fight)
		{
			sps.insert(std::make_pair(eAct::Atk2, sps.at(eAct::Atk)));
		}
		return;
	}

	const auto& wi = txtWeapon::getInstance();
	const auto& ws = wi->getTables().at(eweapon);
	const auto& w2 = ws.at((ws.at(0).master == emod) ? 0 : 1);
	int wdx = txtIcon::getWeaponIdxById(weaponId);
	cDye::toMatrixs(spMatrixs.matrixs, cSp::c0, dyeWeapon);
	if (!fight)
	{
		const auto& wacts = w2.actionMaps.at(wdx);
		auto& stands = sps.at(eAct::Stand);
		auto& walks = sps.at(eAct::Walk);
		
		spMatrixs.uid = wacts.at(eAct::Stand);
		stands.push_back(spMatrixs);
		spMatrixs.uid = wacts.at(eAct::Walk);
		walks.push_back(spMatrixs);
		return;
	}

	const auto& wacts = w2.actions.at(wdx);
	bool isChange = iter != eIterType::jd && emod == eMod::eJueSe»¢Í·¹Ö;
	for (const auto& a : wacts)
	{
		spMatrixs.uid = a.second;
		if (isChange && a.first == eAct::Dead)
		{
			if (eweapon == eIcon::¸«îáf)
			{
				spMatrixs.uid = txtAction::getWeaponTigerDies().at(wdx);
			}
			else if (eweapon == eIcon::´¸×Óc)
			{
				const auto& w2s = wi->getTables().at(eIcon::¸«îáf);
				int rdx = (w2s.at(0).master == emod) ? 0 : 1;
				sps.at(a.first).front().uid = r.actions.at(rdx).at(a.first);
			}
		}
		sps.at(a.first).push_back(spMatrixs);
	}
	sps.insert(std::make_pair(eAct::Atk2, sps.at(eAct::Atk)));
}

void sMod::apply(txtAction::sAction& heads, bool fight) const
{
	if (txtMod::isNpc(emod))
	{
		auto uid = txtNpc::getInstance()->getTables().at(emod).dialog;
		heads.erase(eAct::Dialog);
		heads.insert(std::make_pair(eAct::Dialog, uid));
		return;
	}
	bool iscard = txtMod::isPet(ecard);
	if (txtMod::isRole(emod) && !iscard)
	{
		const auto& r = txtRole::getInstance()->getTables().at(emod);
		if (fight)
		{
			heads = r.sounds.at(weaponMasterIdx % r.sounds.size());
		}
		else
		{
			heads = r.heads.at(dujie % 3);
		}
		return;
	}
	const auto& pet = txtPet::getInstance()->getTables().at(txtMod::isPet(emod) ? emod : ecard);
	int size = pet.jinjies.size();
	int idx = (size < 2) ? 0 : ((jdx < size / 2) ? 0 : 1);
	if (fight)
	{
		if (pet.sounds.empty())
		{
			heads = txtPet::getInstance()->getTables().at(eMod::eÅþÉáÍ¯×Ó).sounds.front();
		}
		else
		{
			heads = pet.sounds.at(idx % pet.sounds.size());
		}
	}
	else
	{
		if (pet.heads.empty())
		{
			heads.insert(std::make_pair(eAct::Small, cSp::c0));
			heads.insert(std::make_pair(eAct::Big, cSp::c0));
			heads.insert(std::make_pair(eAct::Dialog, cSp::c0));
		}
		else
		{
			heads = pet.heads.at(idx);
			const auto& hs = pet.heads.at(pet.heads.size() - 1 - idx);
			for (auto& it : heads)
			{
				if (it.second == cSp::c0)
				{
					it.second = hs.at(it.first);
				}
			}
			if (heads.at(eAct::Small) == cSp::c0)
			{
				heads.at(eAct::Small) = hs.at(eAct::Big);
			}
			else if (heads.at(eAct::Big) == cSp::c0)
			{
				heads.at(eAct::Big) = hs.at(eAct::Small);
			}
		}
	}
}

sSps sMod::get(eAct e) const
{
	sSps sps;
	if (e == eAct::eAtk || e == eAct::eAtk2 || e == eAct::eMagic || e == eAct::eDef || e == eAct::eSuffer || e == eAct::eDead)
	{
		txtAction::sAction sounds;
		apply(sounds, true);
		sps.resize(1);
		sps.at(0).uid = sounds.at(e);
		return sps;
	}
	else if (e == eAct::Small || e == eAct::Big || e == eAct::Dialog)
	{
		txtAction::sAction heads;
		apply(heads, false);
		sps.resize(1);
		sps.at(0).uid = heads.at(e);
		return sps;
	}

	sActs acts;
	apply(acts, !(e == eAct::Stand || e == eAct::Walk), cWdfs::getInstance()->getCurrIter());
	return acts.at(e);
}


void sMod::save(bool pet) const
{
	sStream& sav = *cSave::getSave();
	sav << (int)emod << s_space;
	if (!pet)
	{
		sav << (int)erole << s_space;
		dyeRole.save();
		dyeWeapon.save();
		dyeZq.save();
		dyeZs.save();
	}
	sav << dyePets.size();
	forr(dyePets, k)
	{
		dyePets.at(k).save();
	}
	if (!pet)
	{
		sav << (int)eweapon << s_space << weaponId << s_space << weaponMasterIdx << s_space << (int)ezq << s_space << zsid << s_space << xrid << s_space << xridx << s_space << (int)ecard << s_space;
	}
	sav << jdx << s_space;
	if (!pet)
	{
		sav << dujie << s_space;
	}
}


void sMod::load(bool pet)
{
	sStream& sav = *cSave::getLoad();
	int e;
	sav >> e;
	emod = (eMod)e;
	if (!pet)
	{
		sav >> e;
		erole = (eRole)e;
		dyeRole.load();
		dyeWeapon.load();
		dyeZq.load();
		dyeZs.load();
	}
	sav >> e;
	dyePets.resize(e);
	forr(dyePets, k)
	{
		dyePets.at(k).load();
	}
	if (!pet)
	{
		sav >> e;
		eweapon = (eIcon)e;
		sav >> weaponId >> weaponMasterIdx >> e;
		ezq = (eZuoqi)e;
		sav >> zsid >> xrid >> xridx >> e;
		ecard = (eMod)e;
	}
	sav >> jdx;
	if (!pet)
	{
		sav >> dujie;
	}
}
