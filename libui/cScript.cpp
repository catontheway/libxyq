#include "cScript.h"
#include "cMap.h"
#include "cDialog.h"
#include "uiManager.h"
#include "uiSee.h"
#include "../libtxt/txtMap.h"


cScript* cScript::getInstance()
{
	static cScript* s_script = new cScript();
	return s_script;
}

static void goMap(cMap* map, ulong head, const std::string& name, const std::string& talk, const std::string& mapname, int x, int y)
{
	ccu::getManager()->getDialog()->load(head, name, talk, { "确定", "取消" }, [map, mapname, x, y](int select)
	{
		if (select == 0)
		{
			map->load(mapname);
			map->load(x, y);
		}
	});
}

static void goMap(cMap* map, ulong head, const std::string& name, const std::string& mapname, int x, int y)
{
	goMap(map, head, name, std::string("前往 #Y") + mapname, mapname, x, y);
}


static void goMap(cMap* map, ulong head, const std::string& name, const std::string& mapname, const std::string& x, const std::string& y)
{
	goMap(map, head, name, mapname, std::atoi(x.c_str()), std::atoi(y.c_str()));
}



bool cScript::run(cMap* map, ulong head, const std::string& name, const std::string& script)
{
	std::vector<std::string> strs;
	cc::split(script, "_", strs);
	const std::string& str = strs.front();
	int size = strs.size();
	if (str == txtMap::_地图传送)
	{
		goMap(map, head, name, strs.at(1), strs.at(2), strs.at(3));
		return true;
	}
	if (str == txtMap::_驿站老板)
	{
		if (size == 1)
		{
			goMap(map, head, name, "长安城", 363, 30);
			return true;
		}

		if (strs[1] == "酆都")
		{
			goMap(map, head, name, "前往#Y 酆都", "大唐国境", 80, 250);
			return true;
		}
		goMap(map, head, name, strs.at(1), strs.at(2), strs.at(3));
		return true;
	}
	if (size > 1 && str == "帮派竞赛" && strs[1] == "离开场地")
	{
		goMap(map, head, name, "退出帮派竞赛", "长安城", 370, 113);
		return true;
	}
	if (size > 1 && str == "英雄大会" && strs[1] == "离开场地")
	{
		goMap(map, head, name, "退出帮英雄大会", "长安城", 116, 105);
		return true;
	}
	if (str == txtMap::_门派传送弟子)
	{
		goMap(map, head, name, "长安城", 470, 25);
		return true;
	}
	if (str == txtMap::_大唐国境土地)
	{
		ccu::getManager()->getDialog()->load(head, name, "去哪", { "凌波城", "赤水洲", "离开" }, [map](int select)
		{
			if (select == 0)
			{
				map->load("凌波城");
				map->load(14, 67);
			}
			else if (select == 1)
			{
				map->load("赤水洲");
				map->load(97, 71/*140, 17*/);
			}
		
		});
		return true;
	}
	return false;
}



void cScript::run(sRole& role, ulong head, const std::string& name)
{
	ccu::getManager()->getDialog()->load(head, name, "欢迎体验 #Y浪西游#Y#1", { "浪西游资料片", "浪西游观光版", "梦幻群侠传5", "梦幻群侠传5.日期版","浪西游.小草终结版" }, [](int select)
	{
		if (cc::random(0, 100) < 50)
		{
			sRole r;
			std::vector<int> lvs = { 69, 89, 109, 129, 159, 175 };
			eMod emod = (eMod)cc::random((int)eMod::eJueSe0, (int)eMod::eJueSeEnd);
			r.mod.setMod(emod);
			r.name = txtRole::getInstance()->getTables().at(emod).name;
			cDye::sIdxs& idxs = r.mod.dyeRole;
			forv(idxs, v)
			{
				idxs.at(v) = cc::random(0, 8);
			}
	
			r.lv = lvs.at(cc::random(0U, lvs.size() - 1));
			r.point.reset(r.lv + sPoint::c10);
			r.point.remain = r.lv * 5;
			r.skilv = r.lv;
			r.menpai = (eMenpai)cc::random((int)eMenpai::eMenpai0, (int)eMenpai::eMenpaiEnd);
			forv(r.fuzhus, k)
			{
				r.fuzhus.at(k) = sSki::c180;
			}
			std::vector<eIcon> icons = { eIcon::头盔t, eIcon::项链x, eIcon::eWeapon0, eIcon::铠甲k, eIcon::腰带y, eIcon::鞋子x};
			forv (icons, k)
			{
				eIcon e = icons.at(k);
				sItem& it = r.equips.at(cEquip::getIdx(e));
				it.add();
				const auto& icon = txtIcon::getInstance()->getTables().at(e);
				it.setIcon(icons.at(k), cEquip::getId(e, r.lv));
				it.setData(true, true, 100, 100);
				cEquip::setTemp(it, 100);

				if (k == 2)
				{
					it.switchWeapon(r.mod.emod);
					r.applyWeapon();
				}
				else
				{
					it.switchArmor(txtMod::isBoy(r.mod.emod));
				}

				std::vector<int> stones;
				const auto& icon3 = txtIcon::getInstance()->getTables().at(eIcon::宝石b);
				for (const auto& i : icon3)
				{
					if (cEquip::isStone(it.getType(), i.first))
					{
						stones.push_back(i.first);
					}
				}
				cEquip::setStone(it, stones.at(cc::random(0U, stones.size() - 1)));
			}
			ccp::fillHpMp(r);
			ccu::getManager()->getSee()->setVisible(true);
			ccu::getManager()->getSee()->load(r);
			return;
		}

		eMod emod = (eMod)cc::random((int)eMod::ePet0, (int)eMod::ePet175end);
		sProperty pet;
		pet.load(emod, true, true, true);
		pet.mod.setJinjie(cc::random(0, 3));
		int jdx = pet.mod.jdx % pet.mod.dyePets.size();
		cDye::sIdxs& idxs = pet.mod.dyePets.at(jdx);
		forv(idxs, v)
		{
			idxs.at(v) = cc::random(0, 8);
		}

		pet.lv = txtZz::getInstance()->getTables().at(emod).takelv;
		if (pet.lv <= 5)
		{
			pet.lv = 180;
		}
		pet.point.reset(pet.lv + sPoint::c10);
		pet.point.remain = pet.lv * 5;
		std::vector<eIcon> icons = { eIcon::护腕h, eIcon::项圈x, eIcon::护甲h};
		forv(icons, k)
		{
			eIcon e = icons.at(k);
			sItem& it = pet.equips.at(cEquip::getIdx(e));
			it.add();
			const auto& icon = txtIcon::getInstance()->getTables().at(e);
			it.setIcon(icons.at(k), cEquip::getId(e, pet.lv));
			it.setData(true, true, 100, 100);
			cEquip::setTemp(it, 100);

			std::vector<int> stones;
			const auto& icon3 = txtIcon::getInstance()->getTables().at(eIcon::宝石b);
			for (const auto& i : icon3)
			{
				if (cEquip::isStone(it.getType(), i.first))
				{
					stones.push_back(i.first);
				}
			}
			cEquip::setStone(it, stones.at(cc::random(0U, stones.size() - 1)));
		}
		ccp::fillHpMp(pet);
		ccu::getManager()->getSee()->setVisible(true);
		ccu::getManager()->getSee()->load(pet);
	});
}