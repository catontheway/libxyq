#include "uiItem.h"
#include "uiManager.h"

bool uiItem::init()
{
	if (!uiPad::init(2198359531, true))
	{
		return false;
	}
	// 0x323E2BCD 法宝
//	this->addChild(cSprite::create(1261107812));
	

	this->addChild(_nodeRole = cSprite::create(0x4B2AFA64));
	_nodeRole->setPosition(-1, 24);
	this->addChild(_nodePet = cSprite::create(0x9B1DB10D));
	_nodePet->setPosition(0, 24);
	this->addChild(_nodeZuoqi = cSprite::create(0xA7CE2F61));
	_nodeZuoqi->setPosition(_nodePet->getPosition());


	////////////////////////////////////////////////////////////////////////// role
	_nodeRole->addChild(_spriteHead = cSprite::create());
	_spriteHead->setPosition(38, 2);
	_nodeRole->addChild(_buttonZuoqi = cButton::create2("祥瑞"));
	_buttonZuoqi->onClick = [this]()
	{
		if (_pickupGrid != nullptr)
		{
			return;
		}
		doHide();
		_eArea = eArea::zq;
		_nodeZuoqi->setVisible(true);
	};
	_buttonZuoqi->setPosition(9, 125);
	_nodeRole->addChild(_labelMoney = cLabel::create("0"));
	_labelMoney->setColor(s565::BLACK);
	_labelMoney->setPosition(65, 151);
	_nodeRole->addChild(_gridequip6s = uiGrids::create());
	_gridequip6s->setPosition(201, 4);
	_gridequip6s->onGrid = [this](int select, int count, int left)
	{
		doGrid(_eGrid = eGrid::role, left, select, _role.equips[select]);
	};


	////////////////////////////////////////////////////////////////////////// pet
	Size size = uiGrid::create(cSp::c0 , 0, "")->getContentSize();
	_nodePet->addChild(_gridpets = uiGrids::create(1, 3, size.width, size.height + 2));
	_gridpets->setPosition(175, 27);
	_gridpets->onGrid = [this](int select, int count, int left)
	{
		if (left)
		{
			// _petSelect = select;
			forv(_bodies, k)
			{
				_bodies[k]->setVisible(false);
			}
			_bodies[select]->setVisible(true);
			const auto& p = _role.pets.at(select);
			const auto& es = p.equips;
			forv(es, k)
			{
				_gridequip3s->getGrid(k)->load(es[k]);
			}
			_gridequip3s->setVisible(true);

			sPropertys pros;
			ccp::apply(pros, p);
			_labelHp->setString(toString("%d/%d", p.hp, (int)pros.attr.hpMax)); 
			_labelMp->setString(toString("%d/%d", p.mp, (int)pros.attr.mpMax));
		}
	};
	_nodePet->addChild(_gridequip3s = uiGrids::create());
	_gridequip3s->setPosition(13, 124);
	////////////////////////////////////////////////////////////////////////// 控制可见
	_gridequip3s->setVisible(false);
	//////////////////////////////////////////////////////////////////////////
	for (int k = 0; k < cEquip::c3; ++k)
	{
		uiGrid* g = uiGrid::create(sItem());
		g->setPosition(k * 52, 0);
		_gridequip3s->load(g);
	}
	_gridequip3s->load();
	_gridequip3s->onGrid = [this](int select, int count, int left)
	{
		int pselect = _gridpets->getSelect();
		if (pselect >= 0)
		{
			doGrid(_eGrid = eGrid::pet, left, select, _role.pets[pselect].equips[select]);
		}
	};

	cButton* btnUp = cButton::create(ccu::uUp);
	_nodePet->addChild(btnUp);
	btnUp->setPosition(286, 18);
	btnUp->onClick = [this]()
	{
		_gridpets->subPage();
	};
	cButton* btnDown = cButton::create(ccu::uDown);
	_nodePet->addChild(btnDown);
	btnDown->setPosition(btnUp->getPositionX(), 100);
	btnDown->onClick = [this]()
	{
		_gridpets->addPage();
	};

	_nodePet->addChild(_labelHp = cLabel::create("0/0"));
	_labelHp->setColor(s565::BLACK);
	_labelHp->setPosition(208, 128);
	_nodePet->addChild(_labelMp = cLabel::create("0/0"));
	_labelMp->setColor(s565::BLACK);
	_labelMp->setPosition(208, 150);

	////////////////////////////////////////////////////////////////////////// other

	this->addChild(_grids = uiGrids::create(uiGrids::c5, uiGrids::c4, uiGrid::c50, uiGrid::c50));
	_grids->setPosition(29, 200);
	_grids->onGrid = [this](int select, int count, int left)
	{
		doGrid(_eGrid = eGrid::item, left, select, _items[select]);
	};

	this->addChild(_gridfabaos = uiGrids::create(uiGrids::c5, uiGrids::c4, uiGrid::c50, uiGrid::c50));
	_gridfabaos->setPosition(_grids->getPosition());
	_gridfabaos->setVisible(false);
	_gridfabaos->onGrid = [this](int select, int count, int left)
	{
		doGrid(_eGrid = eGrid::fabao, left, select, _role.fabaos[select]);
	};

	_nodeRole->addChild(_buttonRole = cButton::create(0x94989763));
	_buttonRole->setPosition(10, 4);
	_buttonRole->onClick = [this]()
	{
		if (_pickupGrid != nullptr)
		{
			return;
		}
		doHide();
		_eArea = eArea::pet;
		_nodePet->setVisible(true);
		_buttonRoleOnZuoqi->setVisible(false);
		_buttonPetOnZuoqi->setVisible(true);
	};
	_nodePet->addChild(_buttonPet = cButton::create(0xB5531AC0));
	_buttonPet->setPosition(_buttonRole->getPosition());
	_buttonPet->onClick = [this]()
	{
		if (_pickupGrid != nullptr)
		{
			return;
		}
		doHide();
		_eArea = eArea::role;
		_nodeRole->setVisible(true);
		_buttonRoleOnZuoqi->setVisible(true);
		_buttonPetOnZuoqi->setVisible(false);
	};

	cSprite* spiriteShadow = cSprite::create(ccu::uShadow);
	_vShadow.x = 97;
	_vShadow.y = 102;
	spiriteShadow->setPosition(_vShadow);
	_nodePet->addChild(spiriteShadow);

	////////////////////////////////////////////////////////////////////////// zuoqi
	_nodeZuoqi->addChild(_buttonRoleOnZuoqi = cButton::create(0xB5531AC0));
	_buttonRoleOnZuoqi->setPosition(_buttonRole->getPosition());
	_buttonRoleOnZuoqi->onClick = _buttonPet->onClick;

	_nodeZuoqi->addChild(_buttonPetOnZuoqi = cButton::create(0x94989763));
	_buttonPetOnZuoqi->setPosition(_buttonRole->getPosition());
	_buttonPetOnZuoqi->onClick = _buttonRole->onClick;

	_nodeZuoqi->addChild(_gridzhuangshis = uiGrids::create(1, 1, uiGrid::c50, uiGrid::c50));
	_gridzhuangshis->setPosition(186, 108);
	_gridzhuangshis->onGrid = [this](int select, int count, int left)
	{
		doGrid(_eGrid = eGrid::zq, left, select, _itemZs.at(0));
	};
	_nodeZuoqi->addChild(_gridzqs = uiGrids::create(1, 2));
	_gridzqs->setPosition(188, 36);
	for (int k = 0, y = 0; k < 2; ++k)
	{
		cNode* node = cNode::create();
		cLabel* lable = cLabel::create(k == 0 ? "坐骑" : "祥瑞");
		lable->setColor(s565::BLACK);
		node->addChild(lable);
		node->setLocalZOrder(1);
		cSprite* spriteCross = cSprite::create(ccu::uPetSelect);
		spriteCross->setFrame(2);
		spriteCross->setClip(0, 0);
		cSprite* spriteSelect = cSprite::create(ccu::uPetSelect);
		spriteSelect->setFrame(1);
		spriteSelect->setClip(0, 0);
		node->setContentSize(spriteCross->getContentSize());
		lable->setPosition(node->getContentSize() / 2 - lable->getContentSize() / 2);
 		node->setPositionY(y);
 		y += node->getContentSize().height + 10;
		_gridzqs->load(uiGrid::create(node, spriteCross, spriteSelect));
	}
	_gridzqs->load();


	_nodeZuoqi->addChild(spiriteShadow = cSprite::create(ccu::uShadow));
	spiriteShadow->setPosition(107, 135);
	_nodeZuoqi->addChild(_bodyZuoqi = cSprite::create());
	_bodyZuoqi->setPosition(spiriteShadow->getPosition());
	_bodyZuoqi->setVisible(false);
	_bodyZuoqi->play();
	_nodeZuoqi->addChild(_bodyXiangrui = cSprite::create());
	_bodyXiangrui->setPosition(spiriteShadow->getPosition());
	_bodyXiangrui->setVisible(false);
	_bodyXiangrui->play();
	_nodeZuoqi->addChild(_labelRiding = cLabel::create("乘骑中", eFont::smal));
	_labelRiding->setPosition(130, 10);
	_labelRiding->setColor(s565::RED);
	_labelRiding->setBack(true);
	_labelRiding->setVisible(false);
	_nodeZuoqi->addChild(_buttonRide = cButton::create2());
	_buttonRide->setPosition(250, 120);
	_buttonRide->setVisible(false);
	_gridzqs->onGrid = [this](int select, int count, bool left)
	{
		if (left)
		{
			_bodyZuoqi->setVisible(select == 0);
			_gridzhuangshis->setVisible(_bodyZuoqi->isVisible());
			_bodyXiangrui->setVisible(!_bodyZuoqi->isVisible());
			_buttonRide->setVisible((select == 0) ? (_role.mod.ezq != eZuoqi::eZuoqiNone) : (_role.mod.xrid >= 0));
			_labelRiding->setVisible(_buttonRide->isVisible() && (select == 0 ? (_role.mod.erole == sMod::eRole::zq) : (_role.mod.erole == sMod::eRole::xr)));
			_buttonRide->setString(_labelRiding->isVisible() ? "下车" : "上车");
		}
	};


	//////////////////////////////////////////////////////////////////////////
	this->addChild(_buttonPacks[0] = cButton::create(0x63CC8A23));
	this->addChild(_buttonPacks[1] = cButton::create(0x00D13BBF));
	this->addChild(_buttonPacks[2] = cButton::create(0x00D13BBF));
	this->addChild(_buttonFabao = cButton::create2("法宝"));
	this->addChild(_buttonUse = cButton::create2("使用"));
	_buttonUse->setDesc("长按切换操作模式");
	_buttonUse->onEvent = [](bool left, bool up, int keeptimes)
	{
		if (left && keeptimes == 1)
		{
			auto game = cGame::getInstance();
			if (game->isPhone())
			{
				game->setPhone(false);
				ccu::getManager()->toast("鼠标模式");
			}
			else
			{
				game->setPhone(true);
				ccu::getManager()->toast("触控模式");
			}
		}
	};
	this->addChild(_buttonDelete = cButton::create2("丢弃"));
	_buttonDelete->setDesc("捡起物品,然后点我");

	std::vector<cButton*> buttons = { _buttonPacks[0], _buttonPacks[1], _buttonPacks[2], _buttonFabao, _buttonUse, _buttonDelete };
	cButton* button;
	forv(buttons, k)
	{
		button = buttons[k];
		button->setTag(k);
		button->setPosition(10 + k * 50, 416);
		button->onClick = [this, button]()
		{
			int k = button->getTag();
			bool isBattle = sTeam::getInstance()->isFighting();
			if (k <= 3)
			{
				bool isfb = k == 3;
				if (!isfb && _pickupGrid != nullptr && _ePick != eGrid::fabao  && !isBattle)
				{
					// 卸装
					int index = getEmpty(_items, k);
					if (index < 0)
					{
						ccu::getManager()->toast("格子已满");
					}
					else
					{
						// 交换
						doSwap(_ePick, _pickupIndex, index);
					}
					return;
				}
				_grids->setVisible(!isfb);
				_gridfabaos->setVisible(isfb);
				if (isfb)
				{
					_eItem = eItem::fabao;
				}
				else
				{
					_eItem = eItem::item;
					_grids->load(k);
				}
				_spriteSelect->setPosition(button->getPosition() + Vec2(8, 24));
				return;
			}
			if (isBattle)
			{
				return;
			}
			bool isPhone = cGame::getInstance()->isPhone();
			if (k == 4)
			{
				// 手机使用
				if (!isPhone)
				{
					return;
				}
				if (_eItem == eItem::fabao)
				{
					return;
				}
				auto pitem = getItem(_eGrid);
				if (pitem == nullptr || !pitem->isValid())
				{
					return;
				}
				doUse(getGrids(_eGrid)->getSelect(), *pitem, isBattle);
			}
			else if (k == 5)
			{
				// 删除
				auto e = isPhone ? _eGrid : _ePick;
				if (e == eGrid::none)
				{
					return;
				}
				sItem* pitem = nullptr;
				if (isPhone)
				{
					pitem = getItem(e);
				}
				else
				{
					pitem = &getItems(e).at(_pickupIndex);
				}
				if (pitem == nullptr)
				{
					return;
				}
				bool isWeapon = cEquip::isWeapon(pitem->getType());
				*pitem = sItem();
				if (_eGrid ==  eGrid::zq)
				{
					_role.mod.zsid = sMod::c_1;
					loadZuoqi(_role.mod);
				}
				else if (isWeapon)
				{
					_role.applyWeapon();
				}
				doApply(e == eGrid::item);
				if (isPhone)
				{
					getGrid(e)->load(*pitem);
				}
				else
				{
					_pickupGrid->load(*pitem);
				}
				resetPickup(false);
			}

		};
	}

	this->addChild(_spriteSelect = cSprite::create(ccu::uItemSelect));
	_spriteSelect->setClip(2, _spriteSelect->getContentSize().height - 4);
	_spriteSelect->setContentSize(31, 4);

	this->addChild(_spritePickup = cSprite::create(), INT_MAX);

	doHide();
	_buttonPet->onClick();
	_buttonPacks[0]->onClick();
	setAilgn(eAilgn::Left);
	scheduleUpdate();
	return true; 
}


void uiItem::update(float delta)
{
	if (_spritePickup->isVisible())
	{
		_spritePickup->setPosition(_spritePickup->getParent()->convertToNodeSpace(cInput::getInstance()->getMouse()) - _spritePickup->getContentSize() / 2);
	}
}


void uiItem::doClose()
{
	if (_pickupGrid != nullptr)
	{
		return;
	}
	uiPad::doClose();
}


void uiItem::load(const sRole& role, const sItems& items, u64 money)
{
	_role = role;
	_items = items;
	txtAction::sAction hs;
	role.mod.apply(hs, false);
	_spriteHead->load(hs.at(eAct::Big));
	_labelMoney->setString(money, true);

	_gridequip6s->clear();
	forv(role.equips, k)
	{
		const auto& e = role.equips[k];
		uiGrid* g = uiGrid::create(e);
		g->setPosition((k % 2) * 54, (k / 2) * 54);
		g->showEquipBack(true);
		_gridequip6s->load(g);
	}
	_gridequip6s->load();

	int page = _grids->getPage();
	_grids->clear();
	forv(items, k)
	{
		const auto& it = items[k];
		auto g = uiGrid::create(it);
		_grids->load(g);
	}
	_grids->load();
	_grids->load(page);

	_gridfabaos->clear();
	forv(role.fabaos, k)
	{
		const auto& it = role.fabaos[k];
		auto g = uiGrid::create(it);
		_gridfabaos->load(g);
	}
	_gridfabaos->load();

	for (int k = _bodies.size(); k < role.pets.size(); ++k)
	{
		cSprite* body = cSprite::create();
		body->setPosition(_vShadow);
		body->setVisible(false);
		body->play();
		_nodePet->addChild(body);
		_bodies.push_back(body);
	}
	forv(_bodies, k)
	{
		_bodies[k]->setVisible(false);
	}
	_gridpets->clear();
	auto iter = cWdfs::getInstance()->getCurrIter();
	forv(role.pets, k)
	{
		const auto& p = role.pets[k];
		p.mod.apply(hs, false);
		auto g = uiGrid::create(hs.at(eAct::Small), p.lv, p.name);
		g->showEquipBack(true);
		_gridpets->load(g);

		_bodies.at(k)->load(p.mod.get(eAct::Stand));
	}
	_gridpets->load();

	const auto& m = _role.mod;
	sMod::sActs acts;
	loadZuoqi(m, acts, iter);
	loadXiangrui(m, acts, iter);
	_itemZs.resize(1);
	if (m.zsid >= 0)
	{
		_itemZs.at(0).setIcon(eIcon::坐饰z, m.zsid);
	}
	else
	{
		_itemZs.at(0) = sItem();
	}
	auto g = uiGrid::create(_itemZs.at(0));
	g->showEquipBack(true);
	_gridzhuangshis->clear();
	_gridzhuangshis->load(g);
	_gridzhuangshis->load();
}


void uiItem::load(sRole& role)
{
	auto bag = sBags::getInstance();
	load(role, bag->items, bag->money);
	onRole = [&role](const sRole& r)
	{
		role = r;
		role.applyWeapon();
		role.doMod();
	};
	onItems = [bag](const sItems& items)
	{
		bag->items = items;
	};
}

void uiItem::loadZuoqi(const sMod& m, sMod::sActs& acts, eIterType iter)
{
	if (m.ezq != eZuoqi::eZuoqiNone)
	{
		if (m.erole == sMod::eRole::zq)
		{
			m.apply(acts, false, iter);
			_bodyZuoqi->load(acts.at(eAct::Stand));
		}
		else
		{
			const auto& zq = txtZuoqi::getInstance()->getTables().at(m.ezq);
			sSp sp;
			sp.uid = zq.stand;
			cDye::toMatrixs(sp.matrixs, zq.color, m.dyeZq);
			sSps sps{ sp };
			if (m.zsid != sMod::c_1 && m.zsid / 3 == (int)m.ezq)
			{
				const auto& zs = txtZuoqi::getInstance()->getZhuangshis().at(m.zsid);
				sp.uid = zs.stand;
				cDye::toMatrixs(sp.matrixs, zs.color, m.dyeZs);
				sps.push_back(sp);
			}
			_bodyZuoqi->load( sps );
		}
	}
}


void uiItem::loadZuoqi(const sMod& m)
{
	sMod::sActs acts;
	auto iter = cWdfs::getInstance()->getCurrIter();
	loadZuoqi(m, acts, iter);
}


void uiItem::loadXiangrui(const sMod& m, sMod::sActs& acts, eIterType iter)
{
	if (m.xrid >= 0)
	{
		if (m.erole == sMod::eRole::xr)
		{
			m.apply(acts, false, iter);
			_bodyXiangrui->load(acts.at(eAct::Stand));
		}
		else
		{
			const auto& xr = txtXiangrui::getInstance()->getTables().at(m.xrid);
			bool is2 = (xr.stand2 != cSp::c0);
			sSps sps(is2 ? 2 : 1);
			sps.at(0).uid = xr.stand;
			if (is2)
			{
				sps.at(1).uid = xr.stand2;
			}
			_bodyXiangrui->load( sps );
		}
	}
}


void uiItem::loadXiangrui(const sMod& m)
{
	sMod::sActs acts;
	auto iter = cWdfs::getInstance()->getCurrIter();
	loadXiangrui(m, acts, iter);
}


void uiItem::resetPickup(bool show)
{
	if (/*show && */_pickupGrid != nullptr)
	{
		_pickupGrid->showTarget(true);
	}
	_spritePickup->setVisible(false);
	_pickupIndex = -1;
	_pickupGrid = nullptr;
}


uiGrids* uiItem::getGrids(eGrid e)
{
	switch (e)
	{
	case eGrid::item:
		return _grids;
	case eGrid::role:
		return _gridequip6s;
	case eGrid::pet:
		return _gridequip3s;
	case eGrid::zq:
		return _gridzhuangshis;
	case eGrid::fabao:
		return _gridfabaos;
	}
	return nullptr;
}


uiGrid* uiItem::getGrid(eGrid e, int select)
{
	auto gs = getGrids(e);
	if (gs == nullptr)
	{
		return nullptr;
	}
	if (select < 0)
	{
		return nullptr;
	}
	return gs->getGrid(select);
}


uiGrid* uiItem::getGrid(eGrid e)
{
	auto gs = getGrids(e);
	if (gs == nullptr)
	{
		return nullptr;
	}
	int select = gs->getSelect();
	if (select < 0)
	{
		return nullptr;
	}
	return gs->getGrid(select);
}


sItems& uiItem::getItems(eGrid e)
{
	switch (e)
	{
	case eGrid::item:
		return _items;
	case eGrid::role:
		return _role.equips;
	case eGrid::pet:
		return _role.pets[_gridpets->getSelect()].equips;
	case eGrid::zq:
		return _itemZs;
	case eGrid::fabao:
		return _role.fabaos;
	}
}


sItem* uiItem::getItem(eGrid e)
{
	auto gs = getGrids(e);
	if (gs == nullptr)
	{
		return nullptr;
	}
	int select = gs->getSelect();
	if (select < 0)
	{
		return nullptr;
	}
	return &getItems(e).at(select);
}


void uiItem::clearSelects(eGrid e)
{
	std::vector<eGrid> es = { eGrid::item, eGrid::role, eGrid::pet, eGrid::zq, eGrid::fabao };
	forv(es, k)
	{
		if (es[k] == e)
		{
			continue;
		}
		getGrids(es[k])->clearSelect();
	}
}


int uiItem::getEmpty(const sItems& items, int page)
{
	for (int k = 0, k2 = page * uiGrids::c20; k < uiGrids::c20; ++k, ++k2)
	{
		if (!items[k2].isValid())
		{
			return k2;
		}
	}
	return -1;
}


void uiItem::doSwap(eGrid e, int select, int itemIndex)
{
	auto& it = getItems(e).at(select);
	auto& item = _items.at(itemIndex);
	std::swap(it, item);
	if (e == eGrid::zq)
	{
		_role.mod.zsid = it.isValid() ? it.getId() : sMod::c_1;
		loadZuoqi(_role.mod);
	}
	else if (e == eGrid::role)
	{
		if (select == 2)
		{
			it.switchWeapon(_role.mod.emod);
			// 武器造型
			_role.applyWeapon();
		}
		else
		{
			it.switchArmor(txtMod::isBoy(_role.mod.emod));
		}
	}
	auto g = getGrids(e)->getGrid(select);
	g->load(it);
	g->showEquipBack(_eItem == eItem::item && e != eGrid::item && it.isValid());
	_grids->getGrid(itemIndex)->load(item);
	resetPickup(true);
	clearSelects(eGrid::none);
	doApply(true);
	if (e != eGrid::item)
	{
		doApply(false);
	}
}


void uiItem::doGrid(eGrid e, bool left, int select, sItem& item)
{
	bool isPicking = _pickupGrid != nullptr;
	bool isSameItem = /*isPicking &&  */_eItemPick == _eItem;
	bool isSame = /*isPicking && */_ePick == e && _pickupIndex == select;
	bool isBattle = sTeam::getInstance()->isFighting();
	clearSelects(e);
	_buttonUse->setString((e == eGrid::item) ? "使用" : "卸下");
	if (left)
	{
		if (!isPicking)
		{
			// 捡起
			if (item.isValid() && !cGame::getInstance()->isPhone())
			{
				_ePick = e;
				_eItemPick = _eItem;
				_pickupIndex = select;
				_pickupGrid = getGrid(e);
				_pickupGrid->showTarget(false);
				_spritePickup->load(_pickupGrid->_uid);
				_spritePickup->setVisible(true);
			}
		}
		else
		{
			if (isSameItem && isSame)
			{
				// 放回
				resetPickup(true);
			}
			else
			{
				// 交换
				// 按钮也都限制切换了
				if (!isBattle && isSameItem)
				{
					if (_eItem == eItem::fabao)
					{
						auto& f1 = item;
						auto& f2 = _role.fabaos.at(_pickupIndex);
						std::swap(f1, f2);
						_gridfabaos->getGrid(select)->load(f1);
						_pickupGrid->load(f2);
						resetPickup(true);
						doApply(false);
					}
					else if (e == eGrid::item || _ePick == eGrid::item)
					{
						if (e == eGrid::item)
						{
							doSwap(_ePick, _pickupIndex, select);
						}
						else
						{
							doSwap(e, select, _pickupIndex);
						}
					}
				}
			}
		}
	}
	else
	{
		if (isPicking)
		{
			resetPickup(true);
		}
		else if(_eItem == eItem::item && item.isValid()) // 法宝不能用
		{
			if (e == eGrid::item)
			{
				doUse(select, item, isBattle);
			}
			else if (!isBattle)
			{
				// 卸装
				int index = getEmpty(_items, _grids->getPage());
				if (index < 0)
				{
					ccu::getManager()->toast("格子已满");
				}
				else
				{
					// 交换
					doSwap(e, select, index);
				}
			}
		}
	}
}


void uiItem::doUse(int select, sItem& item, bool battle)
{
	if (battle)
	{
		return;
	}
	auto type = item.getType();
	int pselect = _gridpets->getSelect();
	if (type == eIcon::坐饰z)
	{
		if (_eArea == eArea::zq && item.getId() / 3 == (int)_role.mod.ezq)
		{
			auto& itzs = _itemZs.at(0);
			if (!itzs.isValid() || itzs.getId() != item.getId())
			{
				doSwap(eGrid::zq, 0, select);
			}
		}
	}
	else if(cEquip::isEquip(type))
	{
		if (cEquip::isEquipBaby(type))
		{
			if (_eArea == eArea::pet)
			{
				if (pselect >= 0)
				{
					const auto& pet = _role.pets.at(pselect);
					if (cEquip::getTakeLv(item) > pet.lv)
					{
						ccu::getManager()->toast("等级不够");
					}
					else
					{
						doSwap(eGrid::pet, cEquip::getIdx(type), select);
					}
				}
			}
		}
		else
		{
			if (_eArea == eArea::role)
			{
				if (cEquip::getTakeLv(item) > _role.lv)
				{
					ccu::getManager()->toast("等级不够");
				}
				else
				{
					doSwap(eGrid::role, cEquip::getIdx(type), select);
				}
			}
		}
	}
	else
	{
		if (_eArea == eArea::role && ccp::useItem(item, _role) || (_eArea == eArea::pet && pselect >= 0 && ccp::useItem(item, _role.pets.at(pselect))))
		{
			if (item.isConsumables(false))
			{
				item.sub();
				_grids->getGrid(select)->load(item);
			}
			doApply(true);
			doApply(false);
		}
	}
}


void uiItem::doHide()
{
	_nodeRole->setVisible(false);
	_nodePet->setVisible(false);
	_nodeZuoqi->setVisible(false);
}


void uiItem::doApply(bool item)
{
	if (item)
	{
		if (onItems != nullptr)
		{
			onItems(_items);
		}
	}
	else
	{
		if (onRole != nullptr)
		{
			onRole(_role);
		}
	}
}
