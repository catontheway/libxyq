#include "uiHeader.h"

bool uiHeader::init(bool pet)
{
	if (!cNode::init())
	{
		return false;
	}
	_isPet = pet;
	// pet 1762476724
	// role 42282575
	cSprite* spriteBack = cSprite::create(pet ? 0x203CE1F7 : 0x2178F38B);
	this->addChild(spriteBack);
	
	this->addChild(_spriteHead = cSprite::create());
	_spriteHead->setPosition(3, 3);

	std::array<cSprite*, 4> sprites;
	forr(sprites, k)
	{
		this->addChild(sprites[k] = cSprite::create(0x2E8758EE));
		sprites[k]->setPosition(spriteBack->getContentSize().width, k * sprites[k]->getContentSize().height);
	}

	this->setContentSize(spriteBack->getContentSize().width + sprites[0]->getContentSize().width, spriteBack->getContentSize().height);

	Vec2 v(12, 3);
	this->addChild(_spriteHp2 = cSprite::create(0x008C2611));
	_spriteHp2->setClip(0, 0);
	_spriteHp2->setPosition(sprites[0]->getPosition() + v);
	_sizeBar = _spriteHp2->getContentSize();
	_spriteHp2->setContentSize(_spriteHp2->getContentSize() / 2);

	this->addChild(_spriteHp = cSprite::create(0xAAD44583)); // 780622062
	_spriteHp->setClip(0, 0);
	_spriteHp->setPosition(_spriteHp2->getPosition());

	this->addChild(_spriteMp = cSprite::create(0xCE4D3C2D));
	_spriteMp->setClip(0, 0);
	_spriteMp->setPosition(sprites[1]->getPosition() + v);

	this->addChild(_spriteAp = cSprite::create(0xBAF8009F));
	_spriteAp->setClip(0, 0);
	_spriteAp->setPosition(sprites[2]->getPosition() + v);

	this->addChild(_spriteExp = cSprite::create(0x7B3C08E4));
	_spriteExp->setClip(0, 0);
	_spriteExp->setPosition(sprites[pet ? 2 : 3]->getPosition() + v);

	if (pet)
	{
		_spriteHp2->setVisible(false);
		_spriteAp->setVisible(false);
		sprites[3]->setVisible(false);
	}

	setSnatchNode(true);
	return true;
}



void uiHeader::load(const sProperty& pro, int hpMax, int mpMax)
{
	auto mod = pro.mod;
	txtAction::sAction heads;
	mod.apply(heads, false);
	load(heads.at(eAct::Small));
	if (hpMax > 0)
	{
		_spriteHp2->setContentSize(pro.hp2 * _sizeBar.width / hpMax, _sizeBar.height);
		_spriteHp->setContentSize(pro.hp * _sizeBar.width / hpMax, _sizeBar.height);
	}
	if (mpMax > 0)
	{
		_spriteMp->setContentSize(pro.mp * _sizeBar.width / mpMax, _sizeBar.height);
	}
	_spriteAp->setContentSize(pro.ap * _sizeBar.width / sAttribute::cAp150, _sizeBar.height);
	_spriteExp->setContentSize(pro.exp * _sizeBar.width / sExp::getExp(pro.lv, pro.ispet), _sizeBar.height);

	sDescs descs;
	if (pro.ispet)
	{
		descs.push(pro.name + toString(": %d¼¶", pro.lv), s565::WHITE);
	}
	descs.push(toString("ÆøÑª: %d/%d/%d", pro.hp, pro.hp2, hpMax), s565::RED);
	descs.push(toString("Ä§·¨: %d/%d", pro.mp, mpMax), s565::BLUE);
	if (!_isPet)
	{
		descs.push(toString("·ßÅ­: %d/%d", pro.ap, sAttribute::cAp150), s565::YELLOW);
	}
	setDesc(descs);
}


void uiHeader::load(ulong uhead)
{
	_spriteHead->load(uhead);
	if (_isPet)
	{
		Size size = _spriteHead->getContentSize();
		if (size.width > c32 || size.height > c32)
		{
			_spriteHead->setClip(size.width / 2 - c32 / 2, size.height / 2 - c32 / 2);
			_spriteHead->setContentSize(c32, c32);
		}
		else
		{
			_spriteHead->setClip(0, 0);
		}
	}
}


void uiHeader::load(const sProperty& pro)
{
	if (_isPet != pro.ispet)
	{
		return;
	}
	sPropertys pros;
	ccp::apply(pros, pro);
	load(pro, pros.attr.hpMax, pros.attr.mpMax);
}