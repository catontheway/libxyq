#include "uiShop.h"
#include "uiManager.h"
#include "uiSee.h"

bool uiShop::init()
{
	if (!uiPad::init(3929029437, true))
	{
		return false;
	}
	setTitle("商店");
	this->addChild(_grids = uiGrids::create(uiGrids::c5, uiGrids::c4, uiGrid::c50, uiGrid::c50));
//	_grids->setRememberSelectWhenPage(false);
	_grids->setPosition(10, 37);

	this->addChild(_labelPage = cLabel::create());

	cButton* btnLeft = cButton::create(ccu::uLeft);
	this->addChild(btnLeft);
	btnLeft->setPosition(8, 250);
	btnLeft->onClick = [this]()
	{
		_grids->subPage();
		loadPage();
	};


	cButton* btnRight = cButton::create(ccu::uRight);
	this->addChild(btnRight);
	btnRight->setPosition(88, btnLeft->getPositionY());
	btnRight->onClick = [this]()
	{
		_grids->addPage();
		loadPage();
	};

	_labelPage->setPositionX((btnLeft->getPositionX() + btnLeft->getContentSize().width + btnRight->getPositionX()) / 2);
	_labelPage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_labelPage->setPositionY(btnLeft->getPositionY() + 2);

	int x = 135 - 10;
	this->addChild(_labelPrice = cLabel::create());
	_labelPrice->setPosition(x, 279);

	this->addChild(_labelCount = cLabelNO::create(0, 999));
	_labelCount->setPosition(x, 302);
	_labelCount->onNO = [&](cLabelNO*)
	{
		_grids->setCount(_labelCount->getNumber());
		load();
	};

	this->addChild(_labelTotal = cLabel::create());
	_labelTotal->setPosition(x, 326);

	this->addChild(_labelMoney = cLabel::create());
	_labelMoney->setPosition(x, 350);

	_grids->onClick = [&](bool)
	{
		this->reorder();
	};
	_grids->onGrid = [&](int index, int count, bool left)
	{
		this->reorder();
		if (left)
		{
			_labelPrice->setString(_grids->getGrid(index)->getPrice(), true);
			load();
		}
		else if (_ispet &&  txtMod::isPet(_pets[index]))
		{
			sProperty pro(true);
			pro.load(_pets[index], true, true, true);
			pro.lv = pro.getTakeLv();
			ccu::getManager()->getSee()->load(pro);
		}
	};

	this->addChild(_buttonBuy = cButton::create4("购买"));
	_buttonBuy->setPosition(104, 380);

	_buttonBuy->onClick = [this]()
	{
		if (sTeam::getInstance()->isFighting())
		{
			return;
		}
		int select = _grids->getSelect();
		int count = _grids->getCount();
		if (select < 0 || count < 1)
		{
			return;
		}
		if (select / uiGrids::c20 != _grids->getPage())
		{
			ccu::getManager()->toast("选择不在本页");
			return;
		}
		if (_ispet)
		{
			if (!txtMod::isPet(_pets[select]))
			{
				return;
			}
			if (onPet == nullptr)
			{
				return;
			}
			onPet(_pets[select], count);
			// std::ostringstream ss;
			// ss << "购买: " << item.getIcon()->name << "×" << count << ",花费" << item.getPrice() * count << "银两";
			// ccu::getManager()->toast(ss.str());
			return;
		}
		const auto& item = _items[select];
		if (!item.isValid())
		{
			return;
		}
		if (_money < item.getPrice() * count)
		{
			ccu::getManager()->toast("银两不够");
			return;
		}
		auto bag = sBags::getInstance();
		sItem it(item);
		it.add(count - 1);
		if (!bag->add(it, true))
		{
			ccu::getManager()->toast("行囊满了");
			return;
		}
		select = item.getPrice() * count;
		bag->add(it);
		bag->add(-select);
		std::ostringstream ss;
		ss << "购买: " << item.getIcon()->name << "×" << count << ",花费" << select << "银两";
		ccu::getManager()->toast(ss.str());
	};
	return true;
}



void uiShop::load(const sItems& items, u64 money)
{
	_ispet = false;
	_items = items;
	_money = money;
	_grids->clear();
	forv(items, k)
	{
		const auto& item = items[k];
		if (item.isValid())
		{
			auto g = uiGrid::create(item);
			g->setContentSize(uiGrid::c50, uiGrid::c50);
			_grids->load(g);
		}
		else
		{
			_grids->load(nullptr);
		}
	}
	_grids->load();
	loadPage();
}

void uiShop::load(const std::vector<eMod>& pets, u64 money)
{
	_ispet = true;
	_pets = pets;
	_money = money;
	_grids->clear();
	forv(pets, k)
	{
		const auto& e = _pets[k];
		if (txtMod::isPet(e))
		{
			sMod mod;
			mod.setMod(e);
			txtAction::sAction acts;
			mod.apply(acts, false);
			auto g = uiGrid::create(acts.at(eAct::Big), ccu::uItemCross, ccu::uItemSelect);
			g->setContentSize(uiGrid::c50, uiGrid::c50);
			g->setDesc(txtPet::getInstance()->getTables().at(e).name);
			_grids->load(g);
		}
		else
		{
			_grids->load(nullptr);
		}
	}
	_grids->load();
	loadPage();
}

void uiShop::loadPage()
{
	_labelPage->setString(toString("%d/%d", _grids->getPage() + 1, _grids->getPageMax()));
}

void uiShop::load()
{
	_labelCount->setString(_grids->getCount());
	_labelTotal->setString(_labelPrice->getNumber() * _grids->getCount(), true);
}

