#include "uiPet.h"
#include "uiManager.h"
#include "cDialog.h"
#include "uiDye.h"

uiPet::~uiPet()
{
}

bool uiPet::init()
{
	if (!uiPad::init(1227154258/*0x79D01E0E*/, true))
	{
		return false;
	}
	if (!uiProperty::init(this, 180, 217, 230, 24))
	{
		return false;
	}

	setAilgn(eAilgn::Left);

	_buttonSure->setPosition(230, 335);
	_buttonSure->onClick = [this]()
	{
		int select = _grids->getSelect();
		if (_isPointed && select >= 0 && onPoint != nullptr)
		{
			onPoint(select, _pets[select].point);
		}
	};

	std::vector<cLabel*> labels =
	{
		_labelName,
		_labelHp,
		_labelMp,
		_labelAtk,
		_labelDef,
		_labelSpeed,
		_labelMana,
		_labelExp,
		_labelExpMax
	};
	forr(labels, k)
	{
		labels[k]->setPosition(52, 193 + k * 24);
	}
	_labelExp->setPositionX(85);
	_labelExpMax->setPositionX(85);
	_labelLv->setPosition(180, 146);

	_labelAp->setVisible(false);
	_labelHit->setVisible(false);
	_labelEvade->setVisible(false);

	this->addChild(_grids = uiGrids::create(1, 4, uiGrid::cPetw, uiGrid::cPeth));
	_grids->setPosition(12, 48);
	_grids->onGrid = [&](int select, int count, int left)
	{
		if (left)
		{
			load(select);
			loadZz(select);
		}
	};

	cButton* btnUp = cButton::create(ccu::uUp);
	this->addChild(btnUp);
	btnUp->setPosition(122, 25);
	btnUp->onClick = [this]()
	{
		_grids->subPage();
		loadPage();
	};


	cButton* btnDown = cButton::create(ccu::uDown);
	this->addChild(btnDown);
	btnDown->setPosition(btnUp->getPositionX(), 140);
	btnDown->onClick = [this]()
	{
		_grids->addPage();
		loadPage();
	};

	// 参战
	this->addChild(_buttonFight = cButton::create2("参战"));
	_buttonFight->setPosition(223, 144);
	_buttonFight->onClick = [this]()
	{
		if (sTeam::getInstance()->isFighting())
		{
			return;
		}
		int select = _grids->getSelect();
		if (select < 0)
		{
			return;
		}
		const auto& pet = _pets[select];
		if (_fightid == select)
		{
			_fightid = sRole::cFight_1;
			doFight();
			if (onOperate != nullptr)
			{
				onOperate(eOperator::fight, _fightid, pet);
			}
			return;
		}
		if (pet.lv > _lv + ccp::lvGapPet || pet.getTakeLv() > _lv)
		{
			ccu::getManager()->toast("携带等级不够");
			return;
		}
		if (onOperate != nullptr)
		{
			if (onOperate(eOperator::fight, select, pet))
			{
				_fightid = select;
				doFight();
				_buttonFight->setString(_buttonFight->getString() == "参战" ? "休息" : "参战");
			}
		}
	};
	// 改名
	this->addChild(_buttonChangeName = cButton::create4("修改名字"));
	_buttonChangeName->setPosition(198, 190);
// _buttonChangeName->setDesc("读取<改名专用.txt>第一行");
	_buttonChangeName->setVisible(false);

	// 进阶
	this->addChild(_buttonJinjie = cButton::create4("变换形态"));
	_buttonJinjie->setPosition(13, 407);
	_buttonJinjie->onClick = [this]()
	{
		int select = _grids->getSelect();
		if (select < 0)
		{
			return;
		}
		if (onOperate != nullptr)
		{
			onOperate(eOperator::jinjie, select, _pets[select]);
		}
	};

	// 放生
	this->addChild(_buttonFree = cButton::create2("放生"));
	_buttonFree->setPosition(93, 407);
	_buttonFree->onClick = [this]()
	{
		if (sTeam::getInstance()->isFighting())
		{
			return;
		}
		int select = _grids->getSelect();
		if (select < 0)
		{
			return;
		}
		const auto& pet = _pets[select];
		auto dialog = ccu::getManager()->getDialog();
		dialog->setCancel(true);
		txtAction::sAction hs;
		pet.mod.apply(hs, false);
		dialog->load(hs.at(eAct::Dialog), pet.name, 
			"是放生, 还是存入仓库, 这是个问题", 
			{ "放生", "存入仓库", "取消" }, 
			[this, &pet, select](int index)
		{
			if (index < 2 && onOperate != nullptr)
			{
				if (onOperate(index == 0 ? eOperator::free : eOperator::store, select, pet))
				{
					remove(select);
				}
			}
		});
	};

	// 染色
	this->addChild(_buttonColor = cButton::create2("染色"));
	_buttonColor->setPosition(230, 400);
	_buttonColor->onClick = [this]()
	{
		int select = _grids->getSelect();
		if (select < 0)
		{
			return;
		}
		if (onOperate != nullptr)
		{
			onOperate(eOperator::color, select, _pets[select]);
		}
	};

	// 查看技能
	this->addChild(_buttonSkill = cButton::create(0xB15C5678));
	_buttonSkill->setPosition(202, 425);
	_buttonSkill->onClick = [this]()
	{
		if (_zz->isVisible())
		{
			_zz->setVisible(false);
			return;
		}
		_zz->setVisible(true);
		_zz->setPosition(_contentSize.width, 0);
	};


	// 携带等级
	this->addChild(_labelTakelv = cLabel::create());
	_labelTakelv->setPosition(215, 170);

	// 页码
	this->addChild(_labelPage = cLabel::create());
	_labelPage->setPosition(83, 170);

	cSprite* spriteShadow = cSprite::create(ccu::uShadow);
	_vShadow.x = 208;
	_vShadow.y = 123;
	spriteShadow->setPosition(_vShadow);
	this->addChild(spriteShadow);

	this->addChild(_zz = uiZz::create(nullptr));
	_zz->setRemoveOnClose(false);
	_zz->setVisible(false);

	return true;
}


void uiPet::load(const sPets& pets, int lv, int fightid)
{
	_lv = lv;
	_pets = pets;
	for (int k = _bodies.size(); k < pets.size(); ++k)
	{
		cSprite* body = cSprite::create();
		body->setPosition(_vShadow);
		body->play();
		this->addChild(body);
		_bodies.push_back(body);
	}
	forv(_bodies, k)
	{
		_bodies[k]->setVisible(false);
	}
	_grids->clear();
	if (pets.empty())
	{
		return;
	}
	txtAction::sAction hs;
	forv(pets, k)
	{
		const auto& pet = pets[k];
		txtAction::sAction hs;
		pet.mod.apply(hs, false);
		_grids->load(uiGrid::create(hs.at(eAct::Small), pet.lv, pet.name));
		_bodies.at(k)->load(pet.mod.get(eAct::Stand));
	}
	_grids->load();
	_fightid = fightid;
	fightid = std::max(fightid, 0);
	load(fightid);
	_grids->setSelect(fightid);
	loadZz(fightid);
	doFight();
}


void uiPet::load(sRole& role)
{
	load(role.pets, role.lv, role.fight);
	onOperate = [this, &role](uiPet::eOperator e, int index, const sProperty& p)
	{
		if (index < 0)
		{
			if (e == eOperator::fight)
			{
				role.fight = index;
			}
			return true;
		}
		auto& pet = role.pets.at(index);
		txtAction::sAction hs;
		switch (e)
		{
		case eOperator::fight:
			role.fight = index;
			return true;
		case eOperator::jinjie:
		{
			pet.mod.setJinjie();
			pet.mod.apply(hs, false);
			load(index, pet.mod.get(eAct::Stand), hs.at(eAct::Small));
		}
			return true;
		case eOperator::free:
			role.pets.erase(role.pets.begin() + index);
			return true;
		case eOperator::store:
			return false;
		case eOperator::color:
		{
			auto uidye = ccu::getManager()->geDye();
			if (uidye->switchVisible())
			{
				uidye->doBind();
				auto cdye = cDyeRender::getInstance();
				cdye->load(pet.mod.emod, pet.mod.jdx, pet.mod.dyePets);
				cdye->onApply = [this, index, &pet](const std::vector<sDye>& dyes)
				{
					pet.mod.dyePets = dyes;
					load(index, pet.mod.get(eAct::Stand));
				};
			}
		}
			return true;
		}
		return false;
	};
}


void uiPet::load(int index, const sProperty& pro)
{
	if (index >= 0 && index < _pets.size())
	{
		_pets[index] = pro;
		if (index == _grids->getSelect())
		{
			load(index);
		}
	}
}


void uiPet::load(int index)
{
	const sProperty& pet = _pets[index];
	uiProperty::load(pet);
	forv(_bodies, k)
	{
		_bodies[k]->setVisible(false);
	}
	_bodies[index]->setVisible(true);

	// 名字
	_labelTakelv->setString(pet.getTakeLv());
	_buttonFight->setString(index == _fightid ? "休息" : "参战");
	loadPage();
}


void uiPet::load(int index, const sSps& stands, ulong uhead /* = cSp::INVALID_UID */)
{
	_bodies[index]->load(stands);
	if (uhead != cSp::c0)
	{
		_grids->getGrid(index)->setHeadForPet(uhead);
	}
}


void uiPet::remove(int select)
{
	if (_pets.size() == 1)
	{
		_fightid = -1;
		if (onOperate != nullptr)
		{
			onOperate(eOperator::fight, _fightid, _pets[0]);
		}
	}
	_pets.erase(_pets.begin() + select);
	if (!_pets.empty())
	{
		if (_fightid == select)
		{
			_fightid = -1;
			if (onOperate != nullptr)
			{
				onOperate(eOperator::fight, _fightid, _pets[0]);
			}
		}
		else if (_fightid > select)
		{
			if (onOperate != nullptr)
			{
				if (onOperate(eOperator::fight, _fightid - 1, _pets[0]))
				{
					--_fightid;
				}
			}
		}
	}
	_bodies[select]->removeFromParent();
	_bodies.erase(_bodies.begin() + select);
	_grids->remove(select);
	select = _grids->getSelect();
	if (select >= 0)
	{
		load(select);
		loadZz(select);
	}
	doFight();
	loadPage();
}


void uiPet::loadZz(int index)
{
	_zz->uiPropertyZz::load(_pets[index]);
}


void uiPet::doFight()
{
	forv(_pets, k)
	{
		_grids->getGrid(k)->getChildByTag(0)->setVisible(false);
	}
	if (_fightid >= 0)
	{
		_grids->getGrid(_fightid)->getChildByTag(0)->setVisible(true);
	}
}


void uiPet::loadPage()
{
	_labelPage->setString(toString("%d/%d页", _grids->getPage() + 1, _grids->getPageMax()));
}
