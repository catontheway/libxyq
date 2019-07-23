#include "uiState.h"
#include "uiManager.h"
#include "uiSkill.h"

bool uiState::init()
{
	if (!uiPad::init(0xA16FD45C, true))
	{
		return false;
	}

	int x1 = 53, x2 = 149;
	if (!uiProperty::init(this, x2, 254, 203, 23))
	{
		return false;
	}

	setAilgn(eAilgn::Right);

	// 称谓
	this->addChild(_labelAppellation = cLabel::create());
	_labelAppellation->setColor(s565::BLACK);

	// 帮派
	this->addChild(_labelBangpai = cLabel::create());
	_labelBangpai->setColor(s565::BLACK);

	// 门派
	this->addChild(_labelMenpai = cLabel::create("门派"));
	_labelMenpai->setColor(s565::BLACK);

	// 升级
	this->addChild(_buttonLvup = cButton::create4("升级"));
	_buttonLvup->setPosition(178, 397);
	_buttonLvup->onClick = [this]()
	{
		if (sTeam::getInstance()->isFighting())
		{
			return;
		}
		if(_role.lv >= ccp::lv175)
		{
			ccu::getManager()->toast("已达等级上限");
		}
		if (!_role.lvup(true))
		{
			ccu::getManager()->toast("经验不足");
		}
		if (onLvup != nullptr)
		{
			onLvup();
		}
	};

	// 人物技能
	this->addChild(_buttonSkill = cButton::create4("技能"));
	_buttonSkill->setPosition(178, 422);
	_buttonSkill->onClick = [this]()
	{
		if (onSki != nullptr)
		{
			onSki();
		}
	};

	std::vector<cLabel*> labels = 
	{
		_labelLv,
		_labelAppellation,
		_labelBangpai,
		_labelMenpai,
		_labelHp,
		_labelMp,
		_labelAp,
		_labelHit,
		_labelAtk,
		_labelDef,
		_labelSpeed,
		_labelEvade,
		_labelMana
	};

	int y = 32;
	_labelName->setPosition(137, y);
	forv(labels, k)
	{
		labels[k]->setPosition(x1, y);
		y += 23;
		if (k == 3)
		{
			y += 8;
		}
		else if (k == 6)
		{
			y += 52;
		}
	}

	
	_labelExp->setPosition(83, 400);
	_labelExpMax->setPosition(83, 425);

	_labelRemian->setPositionX(x2 - 12);
	_buttonSure->setPosition(203, 367);
	return true;
}

void uiState::load(sRole& role)
{
	_role = role;
	uiProperty::load(role);
	_labelMenpai->setString(ccp::getMenpaiName(role.menpai));
	onSki = [&role]()
	{
		auto uiski = ccu::getManager()->getSkill();
		if (uiski->switchVisible())
		{
			uiski->load(role);
		}
	};
	onLvup = [this, &role]
	{
		role.lvup(false);
		load(role);
	};
}