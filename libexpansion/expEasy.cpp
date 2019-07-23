#include "expEasy.h"

cSprite* expEasy::createSpriteWithName(ulong uid, const std::string& text /* = "" */, eFont efont /* = eFont::Small */, const s565& color /* = s565::YELLOW */)
{
	cSprite* sprite = cSprite::create(uid);
	cLabel* label = cLabel::create(text, efont);
	label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	label->setPosition(0, sprite->getContentSize().height);
	label->setColor(color);
	label->setBack(true);
	sprite->addChild(label);
	return sprite;
}

cSprite* expEasy::createSpriteWithName(ulong uid, const std::string& text, const s565& color)
{
	return createSpriteWithName(uid, text, eFont::smal, color);
}

expEasy::expEasy() 
{
	_vsWidth = cc::vsSize().width - c10 * 2;
}


bool expEasy::init(const std::string& title /* = "" */)
{
	if (!Scene::init())
	{
		return false;
	}
	this->addChild(_nodeButtonDrag = cNode::create(), 1);
	_nodeButtonDrag->setPositionX(c10);
	this->addChild(_labelTitle = cLabel::create(title));
	_labelTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_labelTitle->setPosition(cc::vsSize().width / 2, c10);
	_btny = c10;
	_nodeButtonDrag->addChild(_button = cButton::create4("·µ»Ø"));
	_button->onClick = [=]() {Director::getInstance()->popScene();};
	_button->setPosition(0, _btny);
	_btnw = _button->getContentSize().width;
	_btnh = _button->getContentSize().height;
	_btny += _btnh + c10;
	_btnw = std::max(_btnw, _wButBtn) + c10 * 2;
	_wButBtn = cc::vsSize().width - c10 - _btnw;
	return true;
}


cButton* expEasy::initButton(const std::string& text, bool end /* = false */)
{
	return initButton(text, {}, end);
}




cButton* expEasy::initButton(const std::string& text, const std::map<int, std::string>& texts, bool end /*= false*/)
{
	cButton* button = cButton::create4(text);
	_nodeButtonDrag->addChild(button);
	// button->setTag(++_tag);
	button->setTag(++_tag);
	button->setPosition(0, _btny);
	button->onClick = [this, button, texts]()
	{
		int tag = button->getTag();
		_nodeDrag->removeFromParent();
		init(initDrag(tag, texts.empty() ? cTagNone : texts.begin()->first));

		for (auto btn : _button2s)
		{
			btn->removeFromParent();
		}
		_button2s.clear();
		if (!texts.empty())
		{
			onButton(tag, texts);
			initButton();
		}
	};
	_btny2 = _btny += (_btnh + c10);
	if (end)
	{
		initButton();
	}
	return button;
}


void expEasy::initButton()
{
	_nodeButtonDrag->setPosition(c10, c10);
	_nodeButtonDrag->setContentSize(_btnw, _btny2 + c10);
	if (_nodeButtonDrag->getContentSize().height > cc::vsSize().height)
	{
		_nodeButtonDrag->setSnatchNode(true);
		_nodeButtonDrag->setDragType(eMouseDrag::V);
		_nodeButtonDrag->setWheel(1);
		_nodeButtonDrag->onEvent = [=](bool left, bool up, int)
		{
			if (left && up)
			{
				if (_nodeButtonDrag->getPositionY() > cHead)
				{
					_nodeButtonDrag->setPositionY(cHead);
				}
				else if (_nodeButtonDrag->getPositionY() + _nodeButtonDrag->getContentSize().height + cHead < cc::vsSize().height)
				{
					_nodeButtonDrag->setPositionY(cc::vsSize().height - _nodeButtonDrag->getContentSize().height - cHead);
				}
			}
		};
// 		_nodeButtonDrag->schedule([=](float)
// 		{
// 			if (_nodeButtonDrag->getPositionY() > cHead)
// 			{
// 				_nodeButtonDrag->setPositionY(cHead);
// 			}
// 			else if (_nodeButtonDrag->getPositionY() + _nodeButtonDrag->getContentSize().height + cHead < cc::vsSize().height)
// 			{
// 				_nodeButtonDrag->setPositionY(cc::vsSize().height - _nodeButtonDrag->getContentSize().height - cHead);
// 			}
// 		}, 0.5f, "scheduler_nodeButtonDrag");
// 		if (!_isScheduled && !_isScheduledButton)
// 		{
// 			this->scheduleUpdate();
// 		}
// 		_isScheduledButton = true;
	}
	else
	{
		_nodeButtonDrag->setSnatchNode(false);
		_nodeButtonDrag->setDragType(eMouseDrag::None);
// 		if (!_isScheduled && _isScheduledButton)
// 		{
// 			this->unscheduleUpdate();
// 		}
// 		_isScheduledButton = false;
	}
// 	return;
// 	if (_nodeButtonDrag->getContentSize().height > cc::vsSize().height)
// 	{
// 		_nodeButtonDrag->setSnatchNode(true);
// 		_nodeButtonDrag->setDragType(eMouseDrag::V);
// 		this->scheduleUpdate();
// 		_isScheduledButton = true;
// 	}
}

void expEasy::onButton(int tag, const std::map<int, std::string>& texts)
{
	int by = _btny;
	cLabel* label = cLabel::create("´Î¼¶:");
	label->setPosition(0, by += _btnh + c10);
	by += label->getContentSize().height + c10;
	_nodeButtonDrag->addChild(label);
	_button2s.push_back(label);
	cButton* button;
	for (const auto& t : texts)
	{
		_nodeButtonDrag->addChild(button = cButton::create4(t.second));
		int tag2 = t.first;
		button->setTag(tag2);
		button->setPosition(0, by);
		button->onClick = [this, tag, tag2]()
		{
			_nodeDrag->removeFromParent();
			init(initDrag(tag, tag2));
		};
		by += (_btnh + c10);
		_button2s.push_back(button);
	}
	_btny2 = by + c10;
}


bool expEasy::initEasy(const std::string& title, const txtEasy::sTable& table)
{
	if (!init(title))
	{
		return false;
	}
	expRank rank;
	rank.init(_vsWidth, false);
	// int k = 0;
	cNode* node = cNode::create();
	std::vector<cSprite*> sprites;
	for (const auto& it : table)
	{
		cSprite* sprite = cSprite::create(it.second);
		if (sprite->isValid() && sprite->getInfo()->framesCount > 1)
		{
			sprite->play();
		}
		node->addChild(sprite);
		rank.iters({ sprite }/*, (++k) == table.size()*/);

		cLabel* label = cLabel::create(toString("%08X", it.second), eFont::smal);
		node->addChild(label);
		sprite->setUserData(label);
		sprites.push_back(sprite);
	}
	rank.iters();
	for (auto& sprite : sprites)
	{
		cLabel* label = (cLabel*)sprite->getUserData();
		label->setPosition(sprite->getPosition() - label->getContentSize() / 2);
		label->setVisible(false);
	}
	node->setContentSize(_vsWidth, rank.getSize().height);
	node->setPositionX(c10);
	return init(node);
}


bool expEasy::init(cNode* nodeDrag)
{
	nodeDrag->setPositionY(cHead);
//	this->addChild(cSprite::create(ccu::uDesc), -100);
	this->addChild(_nodeDrag = nodeDrag);
	if (nodeDrag->getContentSize().height > cc::vsSize().height)
	{
		nodeDrag->setSnatchNode(true);
		nodeDrag->setDragType(eMouseDrag::V);
		nodeDrag->setWheel(1);
		nodeDrag->onEvent = [this](bool left, bool up, int)
		{
			_button->setVisible(!(_tag == -1 && left && !up));
			if (left && up)
			{
				if (_nodeDrag->getPositionY() > cHead)
				{
					_nodeDrag->setPositionY(cHead);
				}
				else if (_nodeDrag->getPositionY() + _nodeDrag->getContentSize().height + 100 < cc::vsSize().height)
				{
					_nodeDrag->setPositionY(cc::vsSize().height - _nodeDrag->getContentSize().height - 100);
				}
			}
		};
// 		nodeDrag->schedule([=](float)
// 		{
// 			if (_nodeDrag->getPositionY() > cHead)
// 			{
// 				_nodeDrag->setPositionY(cHead);
// 			}
// 			else if (_nodeDrag->getPositionY() + _nodeDrag->getContentSize().height + 100 < cc::vsSize().height)
// 			{
// 				_nodeDrag->setPositionY(cc::vsSize().height - _nodeDrag->getContentSize().height - 100);
// 			}
// 		}, 0.5f, "scheduler_nodeDrag");


// 		if (!_isScheduled)
// 		{
// 			if (!_isScheduledButton)
// 			{
// 				this->scheduleUpdate();
// 			}
// 			_isScheduled = true;
// 		}
	}
// 	else if (_isScheduled)
// 	{
// 		if (!_isScheduledButton)
// 		{
// 			this->unscheduleUpdate();
// 		}
// 		_isScheduled = false;
// 	}
	return true;
}


void expEasy::update(float delta)
{
	auto input = cInput::getInstance();
// 	if (_isScheduled)
// 	{
// 		if (_nodeDrag->getRectWorld().containsPoint(input->getMouse()))
// 		{
// 			int wheel = input->getWheel();
// 			if (wheel != 0)
// 			{
// 				_nodeDrag->setPositionY(_nodeDrag->getPositionY() + wheel);
// 			}
// 		}
// 	}
// 	if (_isScheduledButton)
// 	{
// 		if (_nodeButtonDrag->getRectWorld().containsPoint(input->getMouse()))
// 		{
// 			int wheel = input->getWheel();
// 			if (wheel != 0)
// 			{
// 				_nodeButtonDrag->setPositionY(_nodeButtonDrag->getPositionY() + wheel);
// 			}
// 		}
// 	}
	if (!cStepper::getInstance()->isStepd())
	{
		return;
	}
	_labelTitle->setVisible(_nodeDrag->getPositionY() > cHead / 2);
	if (cInput::getInstance()->isLkeep())
	{
		if (_tag == -1 && cMouse::getInstance()->getTop() == _nodeDrag)
		{
			_button->setVisible(false);
		}
	}
	else
	{
		_button->setVisible(true);
// 		if (_isScheduled)
// 		{
// 			if (_nodeDrag->getPositionY() > cHead)
// 			{
// 				_nodeDrag->setPositionY(cHead);
// 			}
// 			else if (_nodeDrag->getPositionY() + _nodeDrag->getContentSize().height + 100 < cc::vsSize().height)
// 			{
// 				_nodeDrag->setPositionY(cc::vsSize().height - _nodeDrag->getContentSize().height - 100);
// 			}
// 		}
// 		if (_isScheduledButton)
// 		{
// 			if (_nodeButtonDrag->getPositionY() > cHead)
// 			{
// 				_nodeButtonDrag->setPositionY(cHead);
// 			}
// 			else if (_nodeButtonDrag->getPositionY() + _nodeButtonDrag->getContentSize().height + cHead < cc::vsSize().height)
// 			{
// 				_nodeButtonDrag->setPositionY(cc::vsSize().height - _nodeButtonDrag->getContentSize().height - cHead);
// 			}
// 		}
	}
}
