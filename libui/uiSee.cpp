#include "uiSee.h"

uiSee::~uiSee()
{
}

bool uiSee::init()
{
	if (!uiPad::init(0x536A7E15, true))
	{
		return false;
	}
	if (!uiProperty::init(this, 205, 231, 0, 24))
	{
		return false;
	}
	if (!uiPropertyZz::init(this, 376, 32, 22, 265, 240))
	{
		return false;
	}

	std::vector<cLabel*> labels =
	{
//		_labelExp, // 参战等级/门派
		uiProperty::_labelHp,
		uiProperty::_labelMp,
		uiProperty::_labelAtk,
		uiProperty::_labelDef,
		uiProperty::_labelSpeed,
		uiProperty::_labelMana,
	};
	forr(labels, k)
	{
		labels[k]->setPosition(61, 231 + k * 24);
	}
//	_labelExp->setPositionX(93);
	_labelName->setPosition(120, 180);
	_labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	
	_labelLv->setPosition(218, 207);


	_labelAp->setVisible(false);
	_labelHit->setVisible(false);
	uiProperty::_labelEvade->setVisible(false);
	_labelExpMax->setVisible(false);
	forr(_buttonAdds, k)
	{
		_buttonAdds[k]->setVisible(false);
		_buttonSubs[k]->setVisible(false);
	}
	_buttonSure->setVisible(false);



	_labelLife->setPositionY(_labelLife->getPositionY() + 5);
	_labelGrow->setPositionY(_labelGrow->getPositionY() + 5);
	_label5xing->setPositionY(_label5xing->getPositionY() + 5);

	cSprite* spriteShadow = cSprite::create(ccu::uShadow);
	_vShadow.x = 120;
	_vShadow.y = 160;
	spriteShadow->setPosition(_vShadow);
	this->addChild(spriteShadow);

	this->addChild(_body = cSprite::create(true));
	_body->setPosition(_vShadow);
	_body->play();

	this->scheduleUpdate();
	return true;
}


void uiSee::load(const sProperty& pro)
{
	uiProperty::load(pro);
	uiPropertyZz::load(pro);

	_body->load(pro.mod.get(eAct::Stand));

	if (pro.ispet)
	{
		forr(_equips, k)
		{
			_equips[k]->setPosition(201, 30 + k * 60);
		}
		_labelExp->setString(pro.getTakeLv());
		_labelExp->setPosition(93, 207);
	}
	else
	{
		forv(_equips, k)
		{
			int x = (k < 3) ? -5 : 201;
			_equips[k]->setPosition(x, 30 + (k % 3) * 60);
		}

		_labelExp->setString(ccp::getMenpaiName(pro.menpai));
		_labelExp->setColor(s565::WHITE);
		_labelExp->setPosition(115 - _labelExp->getContentSize().width / 2, 30);
	}
}