#include "uiSmap.h"
#include "cMap.h"

bool uiSmap::init()
{
	if (!uiPad::init(cSp::c0, true))
	{
		return false;
	}
	_btnClose->setLocalZOrder(0xFFFF);
	this->addChild(_spriteSmap = cSprite::create());
	_spriteSmap->setReader(cWdfs::getInstance()->getSmap());
	this->addChild(_nodeTrans = Node::create());
	_nodeTrans->setPosition(cVec18);
	this->addChild(_nodeNpc = Node::create());
	_nodeNpc->setPosition(cVec18);
	this->addChild(_nodeNpcTemp = Node::create());
	_nodeNpcTemp->setPosition(cVec18);
	this->addChild(_nodePaths = Node::create());
	_nodePaths->setPosition(cVec18);
	this->addChild(_nodeHero = Node::create());
	_nodeHero->setPosition(cVec18);
	_nodeHero->addChild(_spriteHero = cSprite::create(0x146BB550));
//	this->addChild(_spriteCursor = SpriteEasy::create(0x354CD2EB), 1);
	return true;
}

void uiSmap::doEvent(bool left, bool up, int keepTimes)
{
	uiPad::doEvent(left, up, keepTimes);
	if (!left || !up || keepTimes != 0 || sTeam::getInstance()->isFighting())
	{
		return;
	}
	if (_spriteHero->isVisible())
	{
		if (onClick != nullptr)
		{
			static Vec2 v;
			v = cInput::getInstance()->getMouse();
			v = _nodeHero->convertToNodeSpace(v);
			onClick(v * _rate);
		}
	}
}

void uiSmap::doCross(bool draging)
{
	if (draging)
	{
		return;
	}
	static Vec2 v;
	v = cInput::getInstance()->getMouse();
	v = _nodeHero->convertToNodeSpace(v);
	v.y = _contentSize.height - cVec18.y * 2 - v.y;
	v = v * _rate / cMapReader::c20;
	_descs.clear();
	_descs.push(toString("X:%d,Y:%d", (int)v.x, (int)v.y), s565::WHITE);
	auto sprite = ccu::getSpriteDesc();
	if (sprite != nullptr)
	{
		cDesc::toSpriteDesc(sprite, _descs);
		sprite->setVisible(true);
	}
}

void uiSmap::clear()
{
	_nodeTrans->removeAllChildren();
	_nodeNpc->removeAllChildren();
	_nodeNpcTemp->removeAllChildren();
}

void uiSmap::load(ulong suid, const Size& mapSize)
{
	clear();
	_spriteSmap->load(suid);
	setContentSize(_spriteSmap->getContentSize());
	_rate = mapSize.height / (_contentSize.height - cVec18.y * 2);
	resetButtonTitlePosition();
	setAilgn(eAilgn::Mid);
}



void uiSmap::load(const std::vector<Vec2>& paths)
{
	_nodePaths->removeAllChildren();
	if (paths.empty())
	{
		return;
	}
	cSprite* sprite = cSprite::create(3136727389);
	sprite->setPosition(paths.front() / _rate);
	sprite->setAutoAp(false);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_nodePaths->addChild(sprite, 1);
	for (int k = 1, size = paths.size(); k < size; k += 8)
	{
		cSprite* sprite = cSprite::create(0xF792E03C);
		sprite->setPosition(paths[k] / _rate);
		_nodePaths->addChild(sprite);
	}
}


void uiSmap::loadTrans(const std::string& name, const Vec2& v)
{
	loadInner(_nodeTrans, name, v, s565::GREEN);
}

void uiSmap::loadNpc(const std::string& name, const Vec2& v)
{
	loadInner(_nodeNpc, name, v, s565::WHITE);
}

void uiSmap::loadNpcTemp(const std::string& name, const Vec2& v)
{
	loadInner(_nodeNpcTemp, name, v, s565::YELLOW);
}

void uiSmap::loadInner(Node* node, const std::string& name, const Vec2& v, const s565& color)
{
	cLabel* label = cLabel::create(name, eFont::smal);
	label->setPosition(v / _rate);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setColor(color);
	node->addChild(label);
}

void uiSmap::moving(const Vec2& v)
{
	if (_spriteHero->isVisible())
	{
		_spriteHero->setPosition(v / _rate);
	}
}

const cocos2d::Vec2 uiSmap::cVec18(12, 12);
