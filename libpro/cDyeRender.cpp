#include "cDyeRender.h"
#include "cEquip.h"


cDyeRender* cDyeRender::getInstance()
{
	static cDyeRender* s_colorRender = new cDyeRender();
	return s_colorRender;
}


bool cDyeRender::load(eMod epet, int jdx, const std::vector<sDye>& dyes)
{
	if (!txtMod::isPet(epet))
	{
		return false;
	}
	const auto& pet = txtPet::getInstance()->getTables().at(epet);
	const auto& acts = pet.actionMaps;
	if (pet.jinjies.empty())
	{
		_spDyes.resize(pet.actionMaps.size());
		forv(pet.actionMaps, k)
		{
			auto& sp = _spDyes.at(k);
			sp.cid = pet.colors.at(k);
			sp.uid = acts.at(k).at(eAct::Stand);
			sp.dye = dyes.at(k);
		}
	}
	else
	{
		const auto& jjs = pet.jinjies.at(jdx % pet.jinjies.size());
		_spDyes.resize(jjs.size());
		forv(jjs, k)
		{
			auto& sp = _spDyes.at(k);
			sp.cid = pet.colors.at(jjs.at(k));
			sp.uid = acts.at(jjs.at(k)).at(eAct::Stand);
			sp.dye = dyes.at(k);
		}
	}
	load(true);
	return true;
}

bool cDyeRender::load(eMod erole, int idx, const sDye& dye)
{
	if (!txtMod::isRole(erole))
	{
		return false;
	}
	const auto& r = txtRole::getInstance()->getTables().at(erole);
	_spDyes.resize(1);
	auto& sp = _spDyes.at(0);
	sp.cid = r.color;
	sp.dye = dye;
	sp.uid = r.actionMaps.at(idx % r.actionMaps.size()).at(eAct::Stand);
	load(true);
	return true;
}

bool cDyeRender::load(eMod erole, eIcon eweapon, int weaponid, const sDye& dye)
{
	if (!txtMod::isRole(erole) || !cEquip::isWeapon(eweapon))
	{
		return false;
	}
	const auto& ws = txtWeapon::getInstance()->getTables().at(eweapon);
	const auto& w2 = ws.at((ws.at(0).master == erole) ? 0 : 1);
	_spDyes.resize(1);
	auto& sp = _spDyes.at(0);
	sp.cid = 0;
	sp.dye = dye;
	sp.uid = w2.actionMaps.at(txtIcon::getWeaponIdxById(weaponid)).at(eAct::Stand);
	load(true);
	return true;
}

bool cDyeRender::load(eZuoqi ezq, const sDye& dye)
{
	const auto& zq = txtZuoqi::getInstance()->getTables().at(ezq);
	_spDyes.resize(1);
	auto& sp = _spDyes.at(0);
	sp.cid = zq.color;
	sp.dye = dye;
	sp.uid = zq.stand;
	load(true);
	return true;
}

bool cDyeRender::load(int zsid, const sDye& dye)
{
	if (zsid < 0)
	{
		return false;
	}
	const auto& zss = txtZuoqi::getInstance()->getZhuangshis();
	if (zsid >= zss.size())
	{
		return false;
	}
	const auto& zs = zss.at(zsid);
	_spDyes.resize(1);
	auto& sp = _spDyes.at(0);
	sp.cid = zs.color;
	sp.dye = dye;
	sp.uid = zs.stand;
	load(true);
	return true;
}

void cDyeRender::load(bool part0 /* = false */)
{
	if (part0)
	{
		cDye::toSections(_sections, _spDyes.at(_partIdx = 0).cid);
	}
	if (onLoad == nullptr)
	{
		return;
	}
	const auto& sp = _spDyes.at(_partIdx);
	_spMatrixs.uid = sp.uid;
	cDye::toMatrixs(_spMatrixs.matrixs, _sections, sp.dye);

	std::vector<sShow> shows;
	forv (_sections, k)
	{
		sShow show;
		show.total = _sections.at(k).matrix9s.size();
		const cDye::sIdxs& idxs = _spDyes.at(_partIdx).dye;
		show.idx = idxs.at(k) + 1;
		shows.push_back(show);
	}
	onLoad(_spMatrixs, shows);
}


bool cDyeRender::swtichPart()
{
	int size = _spDyes.size();
	if (size <= 1)
	{
		return false;
	}
	if (++_partIdx >= size)
	{
		_partIdx = 0;
	}
	cDye::toSections(_sections, _spDyes.at(_partIdx).cid);
	load();
	return true;
}


bool cDyeRender::resetPart()
{
	auto& dye = _spDyes.at(_partIdx).dye;
	dye.resetZero();
	load();
	return true;
}



bool cDyeRender::addMatrix(int sectionIdx)
{
	if (sectionIdx < 0 || sectionIdx >= _sections.size())
	{
		return false;
	}
	cDye::sIdxs& idxs = _spDyes.at(_partIdx).dye;
	int& count = idxs.at(sectionIdx);
	if (++count >= _sections.at(sectionIdx).matrix9s.size())
	{
		count = 0;
	}
	load();
	return true;
}

bool cDyeRender::randMatrix(int sectionIdx)
{
	if (sectionIdx < 0 || sectionIdx >= _sections.size())
	{
		return false;
	}
	cDye::resetMatrix(_spMatrixs.matrixs.at(sectionIdx).matrix, true);
	return true;
}


void cDyeRender::apply()
{
	if (onApply == nullptr)
	{
		return;
	}
	std::vector<sDye> dyes;
	forv(_spDyes, k)
	{
		dyes.push_back(_spDyes.at(k).dye);
	}
	onApply(dyes);
}