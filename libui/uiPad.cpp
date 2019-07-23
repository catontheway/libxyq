#include "uiPad.h"

cSprite* uiPad::createSpriteClick(const Size& size, const std::string& text /* = "" */)
{
	cSprite* sprite = cSprite::create(0xA0120D38);
	sprite->setSnatchNode(true);
	sprite->set9(true);
	sprite->setContentSize(size);
	cLabel* label = cLabel::create(text, eFont::big);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(sprite->getContentSize() / 2);
	sprite->addChild(label);
	sprite->onState = [sprite, label](eMouseState state)
	{
		switch (state)
		{
		case eMouseState::Cross:
			label->setColor(s565::YELLOW);
			label->setPosition(sprite->getContentSize() / 2);
			break;
		case eMouseState::Down:
			label->setColor(s565::GREEN);
			label->setPosition(Vec2(1, 1) + sprite->getContentSize() / 2);
			break;
		default:
			label->setColor(s565::WHITE);
			label->setPosition(sprite->getContentSize() / 2);
			break;
		}
	};
	return sprite;
}

bool uiPad::init(ulong uid, bool close)
{
	if (!cSprite::init(uid, nullptr))
	{
		return false;
	}

	if (close)
	{
		initClose([this]()
		{
			this->doClose();
		});
	}
	setSnatchNode(true);
	setDragType(eMouseDrag::Both);
	cSprite::setCover(true);
	setCloseRup(true);
	setRemoveOnClose(false);
	setAilgn(eAilgn::Mid);
	setVisible(false);
	return true;
}


void uiPad::setTitle(const std::string& title)
{
	if (_labelTitle == nullptr)
	{
		this->addChild(_labelTitle = cLabel::create(title));
	}
	else
	{
		_labelTitle->setString(title);
	}
	resetButtonTitlePosition();
}


void uiPad::initClose(const cButton::sClick& cb)
{
	if (_btnClose == nullptr)
	{
		this->addChild(_btnClose = cButtonClose::create());
	}
	resetButtonTitlePosition();
	_btnClose->onClick = cb;
}



void uiPad::doClose()
{
	if (_isRemoveOnColse)
	{
		this->runAction(RemoveSelf::create());
	}
	else
	{
		setVisible(false);
	}
}

void uiPad::setContentSize(const Size& contentSize)
{
	cSprite::setContentSize(contentSize);
	resetButtonTitlePosition();
}

void uiPad::setVisible(bool visible)
{
	cSprite::setVisible(visible);
	if (visible)
	{
		reorder();
	}
}

void uiPad::doEvent(bool left, bool up, int keepTimes)
{
	if (_isCloseRup && !left && up && keepTimes == 0)
	{
		doClose();
	}
}

void uiPad::reorder()
{
	if (getParent() == nullptr)
	{
		return;
	}
	getParent()->reorderChild(this, getLocalZOrder());
	_isDraw = true;
}

void uiPad::resetButtonTitlePosition()
{
	if (_btnClose != nullptr)
	{
		_btnClose->setPositionX(_contentSize.width - _btnClose->getContentSize().width - cClosex);
		_btnClose->setPositionY(cClosey);
	}
	if (_labelTitle != nullptr)
	{
		_labelTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
		_labelTitle->setPositionX(_contentSize.width / 2);
		_labelTitle->setPositionY(3);
	}
}


void uiPad::setAilgn(eAilgn e)
{
	switch (e)
	{
	case eAilgn::Left:
		this->setPosition(0, cc::vsCenter().y - _contentSize.height / 2);
		break;
	case eAilgn::Mid:
		this->setPosition(cc::vsCenter() - _contentSize / 2);
		break;
	case eAilgn::Right:
		this->setPosition((cc::vsSize().width - _contentSize.width), cc::vsCenter().y - _contentSize.height / 2);
		break;
	default:
		break;
	}
}

bool uiPad::switchVisible()
{
	if (_visible)
	{
		setVisible(false);
		return false;
	}
	setVisible(true);
	return true;
}
