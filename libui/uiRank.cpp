#include "uiRank.h"

bool uiRank::init(int iw, int ih)
{
	if (!uiPad::init(ccu::uPad, true))
	{
		return false;
	}
	_iw = iw, _ih = ih, _row = 1, _cel = 1;
	const int c64 = 88, c9 = 24;
	iw = _contentSize.width * 2 - c9;
	ih = _contentSize.height * 2 - c9;
	for (;; ++_row)
	{
		_x = _iw * _row;
		if (_x > iw || _x > cc::vsSize().width)
		{
			break;
		}
	}
	for (;; ++_cel)
	{
		_y = _ih * _cel + c64;
		if (_y > ih || _y > cc::vsSize().height)
		{
			break;
		}
	}
	_row = std::max(1, _row - 1);
	_cel = std::max(1, _cel - 1);
	_wh = _row * _cel;
	_x = _iw * _row;
	_y = _ih * _cel + c64;
	iw = std::min(_x, (int)cc::vsSize().width - 32);
	ih = std::min(_y, (int)cc::vsSize().height - 32);
	_x = (iw - _x) / 2;
	_y = _ih - 20;
	
	if (iw > _contentSize.width)
	{
		cSprite* sprite = cSprite::create(ccu::uPad);
		sprite->setClip(c9, 0);
		sprite->setContentSize(_contentSize.width - c9, ih);
		sprite->setPosition(iw - _contentSize.width + c9, 0);
		sprite->setCover(true);
		this->addChild(sprite);
	}
	if (ih > _contentSize.height)
	{
		cSprite* sprite = cSprite::create(ccu::uPad);
		sprite->setClip(0, _contentSize.height * 2 - ih - c9);
		sprite->setContentSize(iw, _contentSize.height);
		sprite->setPosition(0, _contentSize.height - c9);
		sprite->setCover(true);
		this->addChild(sprite);
	}
	if (iw > _contentSize.width && ih > _contentSize.height)
	{
		cSprite* sprite = cSprite::create(ccu::uPad);
		sprite->setClip(_contentSize.width * 2 - iw - c9, _contentSize.height * 2 - ih - c9);
		sprite->setPosition(_contentSize.width - c9, _contentSize.height - c9);
		sprite->setCover(true);
		this->addChild(sprite);
	}
	set9(true, c9, c9);
	setContentSize(iw, ih);

	this->addChild(_labelPage = cLabel::create(" "));
	_labelPage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_labelPage->setPosition(_contentSize.width / 2, _contentSize.height - 32);


	cButton* btnLeft = cButton::create2("<--");
	this->addChild(btnLeft);
	btnLeft->setPosition(_contentSize.width / 2 - 64 - btnLeft->getContentSize().width, _labelPage->getPositionY());
	btnLeft->onClick = [this]()
	{
		load(_page - 1);
	};


	cButton* btnRight = cButton::create2("-->");
	this->addChild(btnRight);
	btnRight->setPosition(_contentSize.width / 2 + 64, _labelPage->getPositionY());
	btnRight->onClick = [this]()
	{
		load(_page + 1);
	};

	_labelPage->setPositionY(_labelPage->getPositionY() + btnRight->getContentSize().height - _labelPage->getContentSize().height);

	setAilgn(eAilgn::Mid);
	return true;
}


void uiRank::load()
{
	_pageMax = std::ceil(_nodes.size() * 1.0f / _wh);
	load(0);
}


void uiRank::load(int page)
{
	if (_page == page)
	{
		return;
	}
	if (page < 0)
	{
		_page = 0;
		return;
	}

	if (page >= _pageMax)
	{
		_page = _pageMax - 1;
		return;
	}
	_page = page;

	int size = _nodes.size();
	for (int k = 0; k < size; ++k)
	{
		if (_nodes[k] == nullptr)
		{
			continue;
		}
		_nodes[k]->setVisible(false);
		_buttons[k]->setVisible(false);
	}

	size = std::min(size, (page + 1) * _wh);

	for (int k = page * _wh; k < size; ++k)
	{
		if (_nodes[k] == nullptr)
		{
			continue;
		}
		_nodes[k]->setVisible(true);
		_buttons[k]->setVisible(true);
	}
	_labelPage->setString(toString("%d/%d", _page + 1, _pageMax));
}


void uiRank::load(int index, ulong uid, ulong uid2, bool play)
{
	cSprite* sprite = cSprite::create(uid);
	if (play)
	{
		sprite->play();
	}
	sprite->setPositionX(_x + (index % _row) * _iw + _iw / 2);
	sprite->setPositionY(_y + ((index % _wh) / _row) * _ih);
	if (uid2 != cSp::c0)
	{
		cSprite* sprite2 = cSprite::create(uid2);
		if (play)
		{
			sprite2->play();
		}
		Node* node = Node::create();
		node->setPosition(sprite->getPosition());
		sprite->setPosition(Vec2::ZERO);
		sprite2->setPosition(sprite->getPosition());
		node->addChild(sprite);
		node->addChild(sprite2);
		this->addChild(node);
		_nodes.push_back(node);
		//////////////////////////////////////////////////////////////////////////
		sprite = (cSprite*)node;
	}
	else
	{
		this->addChild(sprite);
		_nodes.push_back(sprite);
	}


	cButton* button = cButton::create2(cc::toString(index));
	// button->setTag(index);
	button->onClick = [this, index]()
	{
		if (onSelect != nullptr)
		{
			onSelect(index- 1, _uids[index].u1, _uids[index].u2);
		}
	};
	button->setPosition(sprite->getPositionX() - button->getContentSize().width / 2, sprite->getPositionY() + 32);
	this->addChild(button);
	_buttons.push_back(button);
	_uids.push_back({ uid, uid2 });
}
