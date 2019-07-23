#include <tchar.h>
#include "cMain.h"
// 观光版
#define  ccc_tour 0
// 资料片
#define  ccc_expansion 0
#if ccc_tour || ccc_expansion
#include "../libui/uiManager.h"
#endif
#if ccc_tour
#include "../libtour/cMainTour.h"
#elif ccc_expansion
#include "../libexpansion/cExpansion.h"
class cMainExpansion : public cMain
{
public:
	void setTitle(HWND hwnd, HWND child)
	{
		if (hwnd != nullptr)
		{
			::SetWindowText(hwnd, "浪西游资料片v20190720");
		}
	}

	Scene* runScene()
	{
		auto scene = cExpansion::create();
		return scene;
	}
};
#else
// 体验版
#include "../libui/_ui.h"
class cMainXyq : public cMain
{
public:
	void setTitle(HWND hwnd, HWND child)
	{
		if (hwnd != nullptr)
		{
			if (child == nullptr)
			{
				::SetWindowText(hwnd, "浪西游体验版v20190720");
			}
			else
			{
				::SetWindowText(hwnd, "浪西游体验版");
			}
		}
		else if (child != nullptr)
		{
			::SetWindowText(child, "v20190720");
		}
	}

	Scene* runScene()
	{
		auto scene = Scene::create();
		auto map = cMap::create();
		cMapMask* mapMask = cMapMask::create();
		scene->addChild(mapMask);
		scene->addChild(map);
		mapMask->setMap(map);

		auto ui = uiManager::create();
		ccu::setManager(ui);
		scene->addChild(ui);

		auto smap = ccu::getManager()->getSmap();
		map->setMoveSpeed(5);
		map->onPaths = [smap](const std::vector<Vec2>& path, int x, int y)
		{
			smap->load(path);
			ccu::getManager()->getShichen()->setHeroXY(x, y);
		};
		map->onMoving = [smap](const Vec2& v)
		{
			smap->moving(v);
		};
 		map->onMusic = [](ulong music)
 		{
 			int size;
 		//	auto ptr = cWdf::getMp3()->getData(music, size);
 		//	cBass::getInstance()->play(music, ptr, size);
 		};
		smap->onClick = [map](const Vec2& v)
		{
			map->doSearch(v);
		};

		for (int k = 0; k < sTeam::c5; ++k)
		{
			cObject* obj = cObject::create();
			obj->setTag(k);
			obj->setVisible(false);
			map->getTeamLayer()->addChild(obj);
		}
		auto team = sTeam::getInstance();
		team->onObj = [map](int tag, int tagNew, bool visible)
		{
			Node* obj = map->getTeamLayer()->getChildByTag(tag);
			if (obj == nullptr)
			{
				return;
			}
			if (tagNew != tag)
			{
				obj->setTag(tagNew);
			}
			obj->setVisible(visible);
		};
		for (auto& role : team->members)
		{
			cObject* obj = (cObject*)map->getTeamLayer()->getChildByTag(role.teamIdx);
			role.onMod = [obj](const sMod& m)
			{
				obj->load(m, false);
			};
			eMod emod = (eMod)cc::random((int)eMod::eJueSe0, (int)eMod::eJueSeEnd);
			role.mod.setMod(emod);
			if (role.teamIdx == 0)
			{
				role.name = "狼宝";
				role.mod.ezq = (eZuoqi)cc::random((int)eZuoqi::eZuoqi0, (int)eZuoqi::eZuoqiEnd);
				role.mod.zsid = (int)role.mod.ezq * 3 + cc::random(0, 2);
				role.mod.xrid = cc::random(0U, txtXiangrui::getInstance()->getTables().size() - 1);

				role.lv = 129;
				role.point.reset(role.lv + sPoint::c10);
				role.point.remain = role.lv * 5;
				role.exp.add(sExp::getExp(ccp::lv175, false));
				role.skilv = role.lv;

				role.menpai = (eMenpai)cc::random((int)eMenpai::eMenpai0, (int)eMenpai::eMenpaiEnd);

				role.pets.resize(10);

				for (auto& pet : role.pets)
				{
					emod = (eMod)cc::random((int)eMod::ePet0, (int)eMod::ePet175end);
					pet.load(emod, true, true, true);
					pet.lv = std::min(role.lv + ccp::lvGapPet, ccp::lv180);
					pet.point.reset(pet.lv + sPoint::c10);
					pet.point.remain = pet.lv * 5;
					ccp::fillHpMp(pet);
				}
			}


			ccp::fillHpMp(role);
			team->add();
			role.doMod();
		}

		auto& hero = team->getLeader();
		// 		ccp::fillHpMp(hero);
		// 		hero.name = "狼宝";
		// 		hero.mod.setMod(eMod::eJueSe剑侠客);
		// 		team->add();
		// 		hero.doMod();

		auto bag = sBags::getInstance();
		bag->add(80000000);
		std::vector<eIcon> icons = { eIcon::头盔t, eIcon::发钗f, eIcon::项链x, eIcon::eWeapon0, eIcon::铠甲k, eIcon::布裙b, eIcon::腰带y, eIcon::鞋子x, eIcon::护腕h, eIcon::项圈x, eIcon::护甲h };
		icons.at(3) = (eIcon)cc::random((int)eIcon::eWeapon0, (int)eIcon::eWeaponEnd);
		for (int k = 0, size = icons.size(); k < size; ++k)
		{
			sItem it, it2;
			const auto& icon = txtIcon::getInstance()->getTables().at(icons.at(k));
			it.setIcon(icons.at(k), cc::random(0U, icon.size() - 1));
			it.setData(true, true, 100, 100);
			cEquip::setTemp(it, 100);
			eIcon e = cc::random(0, 100) < 50 ? eIcon::状态z : eIcon::追加z;
			const auto& icon2 = txtIcon::getInstance()->getTables().at(e);
			it2.setIcon(e, cc::random(0U, icon2.size() - 1));
			cEquip::setFushi(it, it2);

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
			bag->add(it);
		}

		for (int k = 0; k < 16; ++k)
		{
			sItem it;
			const auto& icons = txtIcon::getInstance()->getTables().at(eIcon::法宝f);
			it.setIcon(eIcon::法宝f, cc::random(0U, icons.size() - 1));
			bag->add(hero.fabaos, it);
		}

		ccu::getManager()->getAccelator()->load(hero);

		ccu::getManager()->getHeader(false)->load(hero);
		if (hero.isPeting())
		{
			ccu::getManager()->getHeader(true)->load(hero.getPet());
		}
		ccu::getManager()->getHeader(true)->onClick = [ui, &hero]()
		{
			if (ui->getPet()->switchVisible())
			{
				ui->getPet()->load(hero);
			}
		};
		ccu::getManager()->getHeader(false)->onClick = [ui, &hero]()
		{
			if (ui->getState()->switchVisible())
			{
				ui->getState()->load(hero);
			}
		};

		ccu::getManager()->getMenu()->onOperate = [ui, &hero](uiMenu::eOperator e)
		{
			switch (e)
			{
			case uiMenu::eOperator::W:
				if (ui->getState()->switchVisible())
				{
					ui->getState()->load(hero);
				}
				break;
			case uiMenu::eOperator::E:
				if (ui->getItem()->switchVisible())
				{
					ui->getItem()->load(hero/*, sBags::getInstance()->items, sBags::getInstance()->money*/);
				}
				break;
			case uiMenu::eOperator::T:
				break;
			case uiMenu::eOperator::O:
				if (ui->getPet()->switchVisible())
				{
					ui->getPet()->load(hero);
				}
				break;
			case uiMenu::eOperator::P:
				break;
			case uiMenu::eOperator::Q:
				break;
			case uiMenu::eOperator::C:
				ui->getAccelator()->setVisible(!ui->getAccelator()->isVisible());
				if (ui->getAccelator()->isVisible())
				{
					ui->getState()->load(hero);
				}
				break;
			case uiMenu::eOperator::F:
				break;
			case uiMenu::eOperator::S:
				break;
			}
		};

		ccu::getManager()->getWorld()->onSelect = [map](const std::string& mapname, int x, int y)
		{
			map->load(mapname);
			map->load(x, y);
		};

		// 		map->load("建邺城");
		// 		map->load(16, 6);
		map->load("大唐境外");
		map->load(190, 7);

		auto toast = "欢迎来到#R浪西游#R#1";
		ui->toast(toast, 10);
		ui->addChannel(eChannel系统, hero.name, toast);
		map->getHero()->runAction(RepeatForever::create(Sequence::create(
			DelayTime::create(4.5f),
			CallFuncN::create([toast, map](Node* node)
		{
			const auto& tops = txtEasy::getInstance()->getTops();
			((cObject*)node)->loadLeaderTop(tops.at(cc::random(3U, tops.size() - 1)));
			// ((cObject*)map->getTeamLayer()->getChildByTag(cc::random(1, 4)))->say(toast, false);
			const auto& fts = txtEasy::getInstance()->getDazzles();
			for (auto& n : map->getTeamLayer()->getChildren())
			{
				((cObject*)n)->loadFoot(fts.at(cc::random(0U, fts.size() - 1)));
			}
			const auto& ft2 = txtEasy::getInstance()->getFoots();
			((cObject*)map->getTeamLayer()->getChildByTag(4))->loadFoot2(ft2.at(cc::random(0U, ft2.size() - 1)));
		}), nullptr)));
		ui->getChannel()->setVisible(true);
		ui->addJob("浪西游", toast);
		ui->addJob("怎么逛得完", "世界那么大,到处逛逛");
		return scene;
	}
};
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	srand((uint)&hInstance);
	auto folder = cFolder::getInstance();
#if 0
	folder->init();
#else
	if (!folder->read(true))
	{
		return 0;
	}
#endif
	folder->apply();

	cWdf::getColor()->loadRoot(folder->getColor());
//	cWdf::getMp3()->loadRoot(folder->getMusic());
//	cWdf::getWav()->loadRoot(folder->getSound());
#if ccc_tour || ccc_expansion
	cWdfs::getInstance()->setType(eMapType::jd);
	cWdfs::getInstance()->setType(euiType::jd);
	cWdfs::getInstance()->pushReader(eIterType::jd);
#if ccc_tour
	return cMain::uMain(hInstance, new cMainTour());
#elif ccc_expansion
	return cMain::uMain(hInstance, new cMainExpansion(), 30);
#endif
#elif 0
	auto game = cGame::getInstance();
	game->load(cGame::cFilename);
	auto eiter = game->getIter();
	auto eui = game->getui();
	auto emap = game->getMap();

	auto wdfs = cWdfs::getInstance();
	wdfs->setType(emap);
	wdfs->setType(eui);
	wdfs->pushReader(eiter);

	return cMain::uMain(hInstance, new cMainXyq(), 60, game->getw(), game->geth(), game->isChatShown() ? 360 : 0);
#else 
	cWdfs::getInstance()->setType(eMapType::iter);
	cWdfs::getInstance()->setType(euiType::sj);
	cWdfs::getInstance()->pushReader(eIterType::iter);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	sw = std::min(1280, sw);
	sh = std::min(720, sh - 96);
	return cMain::uMain(hInstance, new cMainXyq(), 60, sw, sh);
#endif
}