#include "cObject.h"
#include "uiManager.h"

bool cObjectCommen::init(Node* parent, bool ui)
{
	parent->addChild(_spriteShadow = cSprite::create(ccu::uShadow), -2);
	parent->addChild(_say = Node::create(), 1);
	parent->addChild(_nodeBody = Node::create());
	parent->addChild(_labelName = cLabel::create());
	setNameColor(s565::YELLOW);
	_labelName->setBack(true);
	parent->addChild(_labelAppellation = cLabel::create());
	setAppellationColor(s565::BLUE);
	_labelAppellation->setBack(true);

	_isui = ui;
	if (!ui)
	{
		_spriteShadow->setRender(eRender::map);
		_labelName->setRender(eRender::mapFont);
		_labelAppellation->setRender(eRender::mapFont);
	}
	return true;
}

void cObjectCommen::setDirection(int direction)
{
	_direction = direction;
	if (_body != nullptr)
	{
		_body->setDirection(direction);
	}
}


void cObjectCommen::setState(eMouseState state)
{
	_labelName->setColor(_colorName);
	switch (state)
	{
	case eMouseState::Normal:
		break;
	case eMouseState::Cross:
		_labelName->setColor(s565::RED);
		break;
	case eMouseState::Down:
		_labelName->setColor(s565::RED);
		break;
	case eMouseState::Disabled:
		break;
	default:
		break;
	}
	if (_body != nullptr)
	{
		// 下指令才开启 snatch
		_body->setBlend(state == eMouseState::Normal ? eBlend::normal : eBlend::light);
	}
}


void cObjectCommen::say(const std::string& text, bool toast)
{
	cSprite* sprite = cSprite::create(ccu::uDesc);
	sprite->set9(true);
	cText* t = cText::create(128);
	if (!_isui)
	{
		sprite->setRender(eRender::mapFont);
		t->setRender(eRender::mapFont);
	}
	t->setString(text);
	sprite->setContentSize(t->getContentSize() + Size(8, 8));
	sprite->addChild(t);
	t->setPosition(4, 4);
	_say->addChild(sprite);
	float x = -sprite->getContentSize().width / 2;
	sprite->setPosition(x, 0);
	_hSay += x = sprite->getContentSize().height;
	float dt = _hSay * 0.01f;
	sprite->runAction(MoveTo::create(dt, Vec2(sprite->getPositionX(), -_hSay)));
	sprite->runAction(Sequence::create(
		DelayTime::create(5),
		CallFuncN::create([this, x, dt](Node* sprite) 
		{
			for (auto& n : _say->getChildren())
			{
				if (n == sprite)
				{
					continue;
				}
				n->runAction(MoveBy::create(dt, Vec2(0, x)));
			}
			_hSay -= x;
		}),
		RemoveSelf::create(),
		nullptr));
	if (toast)
	{
		ccu::getManager()->addChannel(eChannel当前, _labelName->getString(), text);
	}
}



void cObjectCommen::setObjName(const std::string& name)
{
	_labelName->setString(name);
	_labelName->setColor(_colorName);
	_labelName->setPositionX(-_labelName->getContentSize().width / 2);
	_labelName->setPositionY(_labelAppellation->getString().empty() ? 18 : 36);
}


void cObjectCommen::setNameColor(const s565& color)
{
	_colorName = color;
}

void cObjectCommen::setAppellation(const std::string& appellation)
{
	_labelAppellation->setString(appellation);
	_labelAppellation->setColor(_colorAppellation);
	_labelAppellation->setPosition(-_labelAppellation->getContentSize().width / 2, 16);
	_labelAppellation->setVisible(!appellation.empty());
	_labelName->setPositionY(appellation.empty() ? 18 : 36);
}


void cObjectCommen::setAppellationColor(const s565& color)
{
	_colorAppellation = color;
}


void cObjectCommen::showName(bool show)
{
	_labelName->setVisible(show);
}


void cObjectCommen::showShadow(bool show)
{
	_spriteShadow->setVisible(show);
}

int cObjectCommen::getHeight(bool only1st)
{
	return only1st ? _h1 : _hBody;
}



void cObjectCommen::setHeight(int& h, int& h1)
{
	h = 0, h1 = 0;
	if (_body != nullptr && _body->getInfo() != nullptr)
	{
		h = h1 = _body->getInfo()->height;
	}
}


bool cObjectCommen::step()
{
	return _body != nullptr && _body->cSpriteCache::step();
}


void cObjectCommen::setFrame(int frame)
{
	if (_body != nullptr)
	{
		_body->setFrame(frame);
	}
}



void cObjectCommen::setSnatchPixel(bool isSnatchPixel)
{
	for (auto& body : _bodies)
	{
		body.second->setSnatchPixel(isSnatchPixel);
	}
}

void cObjectCommen::setAction(eAct e, bool reframe /* = true */)
{
	auto& it = _bodies.find(e);
	if (it == _bodies.end())
	{
		return;
	}
	int frame = 0;
	if (_body != nullptr)
	{
		_body->setVisible(false);
		frame = _body->getInfo()->framesCountPerDirection;
	}
	_body = it->second;
	_body->setVisible(true);
	_body->setDirection(_direction);
	if (reframe || frame >= _body->getInfo()->framesCountPerDirection)
	{
		_body->setFrame(0);
	}

	setHeight(_hBody, _h1);
	_say->setPositionY(-_hBody);
}


//////////////////////////////////////////////////////////////////////////
cObject::~cObject()
{

}
bool cObject::init(bool ui)
{
	if (!cNode::init() || !cObjectCommen::init(this, ui))
	{
		return false;
	}
	this->addChild(_foot = cSprite::create(), 1);
	this->addChild(_leaderTop = cSprite::create(), 1);

	_foot->play();
	_leaderTop->play();
	
	if (!ui)
	{
		_foot->setRender(eRender::map);
		_leaderTop->setRender(eRender::mapFont);
	}
	stand();
	return true;
}


bool cObject::isSnatched(const Vec2& v)
{
	if (_body == nullptr)
	{
		return cNode::isSnatched(v);
	}
	return _body->isSnatched(_body->convertToNodeSpace(_nodeBody->convertToWorldSpace(v)));
}


void cObject::setState(eMouseState state)
{
	cObjectCommen::setState(state);
}


void cObject::load(const sSps& stands, const sSps& walks /* = */ )
{
	cSprite* sprite = cSprite::create(stands);
	_nodeBody->addChild(sprite);
	sprite->setVisible(false);
	if (!_isui)
	{
		sprite->setRender(eRender::mapObj);
	}
	_bodies.clear();
	_bodies.insert(std::make_pair(eAct::Stand, sprite));
	if (!walks.empty())
	{
		_nodeBody->addChild(sprite = cSprite::create(walks));
		sprite->setVisible(false);
		if (!_isui)
		{
			sprite->setRender(eRender::mapObj);
		}
		_bodies.insert(std::make_pair(eAct::Walk, sprite));
	}
	stand();
	setHeight(_hBody, _h1);
}

void cObject::load(const sMod::sActs& acts, bool onlyStand /* = true */)
{
	if (onlyStand)
	{
		load(acts.at(eAct::Stand));
	}
	else
	{
		load(acts.at(eAct::Stand), acts.at(eAct::Walk));
	}
}


void cObject::load(const sMod& mod, bool onlyStand /*= true*/)
{
	sMod::sActs acts;
	mod.apply(acts, false, cWdfs::getInstance()->getCurrIter());
	load(acts, onlyStand);
}


void cObject::load(ulong uid, const std::string& mapname)
{
	sSp sp;
	sp.uid = uid;
	load({ sp });
	setObjName(mapname);
//	setAppellation("传送");
	_labelAppellation->setPositionY(0);
	_labelName->setPositionY(_labelAppellation->getContentSize().height);
	_nodeBody->setPositionY(-_hBody / 2);
}


void cObject::loadFoot(ulong ufoot)
{
	_foot->load(ufoot);
}

void cObject::loadLeaderTop(ulong top)
{
	_leaderTop->load(top);
	_leaderTop->setPositionY(-_hBody);
}

void cObject::stand()
{
	_isStand = true;
	setAction(eAct::Stand);
}

void cObject::walk(const Vec2& vTo)
{
	if (_isStand)
	{
		_isStand = false;
		setAction(eAct::Walk, false);
	}
	if (_body != nullptr)
	{
		int d;
		if (_body->getInfo()->directionsCount == 4)
		{
			d = cDirection::getDirection4(vTo - _position);
		}
		else
		{
			d = cDirection::getDirection8(_direction, vTo - _position);
		}
		setDirection(d);
	}
}



void cObject::step(float delta, bool steped, bool walked)
{
	if (!_visible)
	{
		return;
	}
	if (_isStand && steped || (!_isStand && walked))
	{
		if (cObjectCommen::step())
		{
			setFrame(0);
		}
	}

	if (!_isStand && _ufoot2 != cSp::c0 && (_deltaFoot += delta) > 0.4f)
	{
		_deltaFoot -= 0.4f;
		cSprite* sprite = cSprite::create(_ufoot2);
		if (!_isui)
		{
			sprite->setRender(eRender::mapObj);
		}
		sprite->setDirection(_direction);
		sprite->play(1, true);
		sprite->setPosition(_position);
		getParent()->getParent()->addChild(sprite);
	}
}