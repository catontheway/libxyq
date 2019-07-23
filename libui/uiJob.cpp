#include "uiJob.h"

static const int s_lockWidth = 128;
bool uiJob::init()
{
	if (!cNode::init())
	{
		return false;
	}

	this->addChild(_btnEx = cButton::create(ccu::uDesc, "-"));
	this->addChild(_btnLeft = cButton::create(ccu::uDesc, "->"));
	_btnEx->setClip(32, 32);
	_btnEx->setContentSize(cLabel::create("->")->getContentSize() + Size(4, 4));
	_btnEx->setAilgn(eAilgn::Mid);
	_btnLeft->setClip(32, 32);
	_btnLeft->setContentSize(_btnEx->getContentSize());
	_btnLeft->setAilgn(eAilgn::Mid);
// 	this->setContentSize(_btnUp->getContentSize().width + _btnLeft->getContentSize().width + 1,
// 		std::max(_btnUp->getContentSize().height, _btnLeft->getContentSize().height));

//	_btnEx->setPositionY(0);
	_btnEx->onClick = [this]()
	{
		_isShow = !_isShow;
		updateList();
	};

//	_btnLeft->setPositionY(0);
	_btnLeft->onClick = [this]()
	{
		_isLeft = !_isLeft;
		updateList();
	};

	_isShow = false;
	updateList();
	return true;
}

bool uiJob::add(const std::string& title, const std::string& text)
{
	forr(_buttonTitles, k)
	{
		if (_buttonTitles[k]->getString() == title)
		{
			_buttonTitles[k]->setTag(1);
			_texts[k]->setString(text);
			_isShow = true;
			updateList();
			return true;
		}
	}

	cButton* button = cButton::create(ccu::uDesc, title, eFont::chat);
	button->setClip(32, 32);
	button->setContentSize(s_lockWidth, cLabel::create("บวบว")->getContentSize().height + 2);
	button->setAilgn(eAilgn::Left);
	button->setTag(1);
	button->onClick = [this, button]()
	{
		button->setTag(!button->getTag());
		updateList();
	};

	cText* t = cText::create(eFont::smal, s_lockWidth);
	t->setString(text);
	t->setLabelBack(true);
	t->setPositionX(3);

	this->addChild(button);
	this->addChild(t);
	_buttonTitles.push_back(button);
	_texts.push_back(t);
	_isShow = true;
	updateList();
	return true;
}


bool uiJob::remove(const std::string& title)
{
	forr(_buttonTitles, k)
	{
		if (_buttonTitles[k]->getString() == title)
		{
			_buttonTitles[k]->removeFromParent();
			_texts[k]->removeFromParent();
			_texts.erase(_texts.begin() + k);
			_buttonTitles.erase(_buttonTitles.begin() + k);
			return true;
		}
	}
	return false;
}


void uiJob::updateList()
{
	this->setPositionX(_isLeft ? 0 : cc::vsSize().width - s_lockWidth);
	this->setPositionY(108);

	_btnEx->setString(_isShow ? "-" : "+");
	_btnLeft->setVisible(_isShow);
	if (!_isShow)
	{
		if (_isLeft)
		{
			_btnEx->setPositionX(0);
		}
		else
		{
			_btnEx->setPositionX(s_lockWidth - _btnEx->getContentSize().width);
		}
		forr(_buttonTitles, k)
		{
			_buttonTitles[k]->setVisible(false);
			_texts[k]->setVisible(false);
		}
		return;
	}

	if (_isLeft)
	{
		_btnLeft->setString("->");
		_btnLeft->setPositionX(0);
		_btnEx->setPositionX(_btnLeft->getContentSize().width + 1);
	}
	else
	{
		_btnLeft->setString("<-");
		_btnLeft->setPositionX(s_lockWidth - _btnLeft->getContentSize().width);
		_btnEx->setPositionX(_btnLeft->getPositionX() - 1 - _btnEx->getContentSize().width);
	}

	forr(_buttonTitles, k)
	{
		_buttonTitles[k]->setVisible(true);
		_texts[k]->setVisible(_buttonTitles[k]->getTag() != 0);
	}

	int y = _btnEx->getContentSize().height + 1;
	Node* node;
	forv(_buttonTitles, k)
	{
		node = _buttonTitles[k];
		node->setPositionX(0);
		node->setPositionY(y);
		y += node->getContentSize().height + 1;
		if (_texts[k]->isVisible())
		{
			node = _texts[k];
			node->setPositionY(y);
			y += node->getContentSize().height;
		}
	}
}
