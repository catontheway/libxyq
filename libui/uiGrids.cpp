#include "uiGrids.h"
#include "uiManager.h"


uiGrid* uiGrid::create(ulong uid, ulong ucross /*= cSp::c0*/, ulong uselect /*= cSp::c0*/)
{
	return create(cSprite::create(uid), cSprite::create(ucross), cSprite::create(uselect));
}

uiGrid* uiGrid::create(const sItem& item)
{
	ulong uid = item.isValid() ? item.getIcon()->small : cSp::c0;
	auto g = create(uid, ccu::uItemCross, ccu::uItemSelect);
	g->setContentSize(c50, c50);
	g->setCrossPosition(1, -2);
	g->setSelectPosition(1, -2);
	if (item.isEquip() || item.getType() == eIcon::坐饰z)
	{
		g->addChild(cSprite::create(ccu::uEquipBack), -1, cTagEquipBack);
		g->showEquipBack(false);
	}
	else
	{
		g->setString(item.getCount());
	}
	g->_uid = uid;
	item.toDesc(g->_descs);
	g->_price = item.getPrice();
	return g;
}

uiGrid* uiGrid::create(const sSki& ski, bool big /* = true */)
{
	ulong uid = ski.isValid() ? (big ? ski.getIcon()->big : ski.getIcon()->small) : cSp::c0;
	cSprite* sprite = cSprite::create(uid);
	int w, h;
	if (uid == cSp::c0)
	{
		if (big)
		{
			w = c40, h = c40;
		}
		else
		{
			w = c24, h = c24;
		}
	}
	else
	{
		w = sprite->getContentSize().width;
		h = sprite->getContentSize().height;
	}
	cSprite* spriteCross = cSprite::create(ccu::uItemCross);
	cSprite* spriteSelect = cSprite::create(ccu::uItemSelect);
	spriteCross->set9(true);
	spriteCross->setContentSize(w + 4, h + 4);
	spriteSelect->set9(true);
	spriteSelect->setContentSize(w + 4, h + 4);
	auto g = create(sprite, spriteCross, spriteSelect);
	g->setContentSize(w, h);
	if (big)
	{
		g->setCrossPosition(3, 0);
		g->setSelectPosition(2, -1);
	}
	else
	{
		g->setCrossPosition(5, 2);
		g->setSelectPosition(4, 1);
	}

	g->_uid = uid;
	ski.toDescs(g->_descs);
	return g;
}

uiGrid* uiGrid::create(ulong uhead, int lv, const std::string& name)
{
	auto g = create(uhead, name);
// 	cSprite* spriteHead = cSprite::create(uhead);
// 	cSprite* spriteCross = cSprite::create(ccu::uPetSelect);
// 	spriteCross->setFrame(2);
// 	cSprite* spriteSelect = cSprite::create(ccu::uPetSelect);
// 	spriteSelect->setFrame(1);

	cLabel* labelLv = cLabel::create(cc::toString(lv), eFont::smal);
	labelLv->setColor(s565::YELLOW);
	labelLv->setBack(true);

	cLabel* labelFight = cLabel::create("战", eFont::smal);
	labelFight->setTag(cTagPetFight);
	labelFight->setColor(s565::RED);
	labelFight->setBack(true);
	labelFight->setVisible(false);

// 	cLabel* labelName = cLabel::create(name);
// 	labelName->setColor(s565::BLACK);
// 
// 	Node* node = Node::create();
// 	node->setContentSize(cPetw, cPeth);
// 
// 	auto g = create(node, spriteCross, spriteSelect);
// 
// 	if (uhead != cSp::INVALID_UID)
// 	{
// 		spriteHead->setClip(spriteHead->getContentSize().width / 2 - cPeth / 2, spriteHead->getContentSize().height / 2 - cPeth / 2);
// 	}
// 	spriteHead->setContentSize(cPetw, cPeth);
// 	g->addChild(spriteHead);
// 
// 	labelName->setPosition(cPetw + 2, cPeth / 2 - labelName->getContentSize().height / 2);
// 	g->addChild(labelName);

	labelLv->setPosition(cPetw - labelLv->getContentSize().width, cPeth - labelLv->getContentSize().height - 3);
	g->addChild(labelLv);

	labelFight->setPosition(cPetw - labelFight->getContentSize().width, 3);
	labelFight->setTag(0);
	g->addChild(labelFight);

// 	g->setCrossPosition(cPetw - spriteCross->getContentSize().width, cPeth / 2 - spriteCross->getContentSize().height / 2);
// 	g->setSelectPosition(cPetw - spriteSelect->getContentSize().width, cPeth / 2 - spriteSelect->getContentSize().height / 2);
// 	g->_uid = uhead;
	return g;
}

uiGrid* uiGrid::create(ulong uhead, const std::string& name)
{
	cSprite* spriteHead = cSprite::create(uhead);
	spriteHead->setTag(cTagHead);
	cSprite* spriteCross = cSprite::create(ccu::uPetSelect);
	spriteCross->setFrame(2);
	cSprite* spriteSelect = cSprite::create(ccu::uPetSelect);
	spriteSelect->setFrame(1);

	cLabel* labelName = cLabel::create(name);
	labelName->setColor(s565::BLACK);

	Node* node = Node::create();
	node->setContentSize(cPetw, cPeth);

	auto g = create(node, spriteCross, spriteSelect);

	if (uhead != cSp::c0)
	{
		spriteHead->setClip(spriteHead->getContentSize().width / 2 - cPeth / 2, spriteHead->getContentSize().height / 2 - cPeth / 2);
	}
	spriteHead->setContentSize(cPeth, cPeth);
	g->addChild(spriteHead);

	labelName->setPosition(cPeth + 2, cPeth / 2 - labelName->getContentSize().height / 2);
	g->addChild(labelName);

	g->setCrossPosition(cPetw - spriteCross->getContentSize().width, cPeth / 2 - spriteCross->getContentSize().height / 2);
	g->setSelectPosition(cPetw - spriteSelect->getContentSize().width, cPeth / 2 - spriteSelect->getContentSize().height / 2);
	g->_uid = uhead;
	return g;
}


bool uiGrid::load(const sItem& item)
{
	if (cEquip::isEquip(item.getType()) || item.getType() == eIcon::坐饰z)
	{
		if (getChildByTag(cTagEquipBack) == nullptr)
		{
			addChild(cSprite::create(ccu::uEquipBack), -1, cTagEquipBack);
			showEquipBack(false);
		}
	}
	else
	{
		removeChildByTag(cTagEquipBack);
		setString(item.getCount());
	}

	((cSprite*)_node)->load(_uid = (item.isValid() ? item.getIcon()->small : cSp::c0));
	item.toDesc(_descs);
	_price = item.getPrice();

	setContentSize(c50, c50);

	return true;
}



bool uiGrid::load(const sSki& ski, bool big /* = true */)
{
	ulong uid = (ski.isValid() ? (big ? ski.getIcon()->big : ski.getIcon()->small) : cSp::c0);
	((cSprite*)_node)->load(uid);
	if (_uid == cSp::c0 && uid == cSp::c0)
	{
		int w, h;
		if (big)
		{
			w = c40, h = c40;
		}
		else
		{
			w = c24, h = c24;
		}
		((cSprite*)_nodeCross)->set9(true);
		_nodeCross->setContentSize(w + 4, h + 4);
		((cSprite*)_nodeSelect)->set9(true);
		_nodeSelect->setContentSize(w + 4, h + 4);
	}
	else
	{
		if (big)
		{

		}
		else
		{
			// 快捷键
			_node->setPosition(_contentSize / 2 - _node->getContentSize() / 2);
		}
	}
	_uid = uid;
	ski.toDescs(_descs);
	return true;
}

bool uiGrid::init(Node* node, Node* nodeCross, Node* nodeSelect)
{
	if (!Node::init())
	{
		return false;
	}
	if (node != nullptr)
	{
		this->addChild(_node = node);
	}
	if (nodeCross != nullptr)
	{
		this->addChild(_nodeCross = nodeCross);
	}
	if (nodeSelect != nullptr)
	{
		this->addChild(_nodeSelect = nodeSelect);
	}

	this->addChild(_label = cLabel::create(" ", eFont::smal));

	if (_node != nullptr)
	{
		_node->setPosition(_node->getAnchorPointInPoints());
		Node::setContentSize(_node->getContentSize());
	}


	_label->setBack(true);
	showCross(false);
	showSelect(false);

	return true;
}

void uiGrid::setContentSize(const Size& contentSize)
{
	Node::setContentSize(contentSize);
	_node->setPosition(Vec2(contentSize - _node->getContentSize()) / 2 + _node->getAnchorPointInPoints());
	_label->setPosition(3, contentSize.height - 4 - _label->getContentSize().height);
}

void uiGrid::setCrossPosition(float x, float y)
{
	if (_nodeCross != nullptr)
	{
		_nodeCross->setPosition(x, y);
	}
}


void uiGrid::setSelectPosition(float x, float y)
{
	if (_nodeSelect != nullptr)
	{
		_nodeSelect->setPosition(x, y);
	}
}

void uiGrid::setString(int number)
{
	if (number < 2)
	{
		_label->setString("");
	}
	else
	{
		_label->setString(number);
	}
}

void uiGrid::showTarget(bool show)
{
	if (_node == nullptr)
	{
		return;
	}
	_node->setVisible(show);
}

void uiGrid::showCross(bool show)
{
	if (_nodeCross == nullptr)
	{
		return;
	}
	_nodeCross->setVisible(show);
	showDesc(show);
}

void uiGrid::showSelect(bool show)
{
	if (_nodeSelect == nullptr)
	{
		return;
	}
	_nodeSelect->setVisible(show);
}


void uiGrid::switchSelect()
{
	if (_nodeSelect == nullptr)
	{
		return;
	}
	_nodeSelect->setVisible(_nodeSelect->isVisible());
}




void uiGrid::setHeadForPet(ulong uhead)
{
	cSprite* spriteHead = (cSprite*)getChildByTag(cTagHead);
	if (uhead != cSp::c0)
	{
		spriteHead->load(uhead);
		spriteHead->setClip(spriteHead->getContentSize().width / 2 - cPeth / 2, spriteHead->getContentSize().height / 2 - cPeth / 2);
	}
	spriteHead->setContentSize(cPeth, cPeth);
}

void uiGrid::showEquipBack(bool visivle)
{
	auto node = getChildByTag(cTagEquipBack);
	if (node != nullptr)
	{
		node->setVisible(visivle);
	}
}

//////////////////////////////////////////////////////////////////////////
bool uiGrids::init(int row, int cel, int iw, int ih)
{
	if (!cNode::init())
	{
		return false;
	}
	_row = row, _cel = cel, _wh = row * cel, _iw = iw, _ih = ih;
	_isRank = _row != 0 && _cel != 0;
	setSnatchNode(true);
	return true;
}

void uiGrids::clear()
{
	forr(_grids, k)
	{
		if (_grids[k] == nullptr)
		{
			continue;
		}
		_grids[k]->removeFromParent();
	}
	_grids.clear();
	_count = 0;
	_page = 0;
	_cross = -1;
	_select = -1;
	_pageMax = 1;
}

void uiGrids::reset()
{
	clear();
	_iw = _ih = 0;
}

void uiGrids::clearSelect()
{
	int size = _grids.size();
	for (int k = 0; k < size; ++k)
	{
		if (_grids[k] == nullptr)
		{
			continue;
		}
		_grids[k]->showCross(false);
		_grids[k]->showSelect(false);
		_grids[k]->showDesc(false);
	}
	_select = -1;
}

void uiGrids::clearSelect(bool visible)
{
	int size = _grids.size();
	for (int k = 0; k < size; ++k)
	{
		if (_grids[k] == nullptr)
		{
			continue;
		}
		_grids[k]->showCross(false);
		_grids[k]->showSelect(false);
		_grids[k]->showDesc(false);
		_grids[k]->setVisible(visible);
	}
//	_select = -1;
}


void uiGrids::load(uiGrid* grid)
{
	int k = _grids.size();
	_grids.push_back(grid);
	if (grid == nullptr)
	{
		return;
	}
	if (_iw == 0)
	{
		_iw = grid->getContentSize().width;
		_ih = grid->getContentSize().height;
	}
	else
	{
		grid->setContentSize(_iw, _ih);
	}
	this->addChild(grid);
	if (_isRank)
	{
		grid->setPosition((k % _row) * _iw, ((k % _wh) / _row) * _ih);
	}
	else
	{
		_row = std::max((float)_row, grid->getPositionX() + grid->getContentSize().width);
		_cel = std::max((float)_cel, grid->getPositionY() + grid->getContentSize().height);
	}
}


void uiGrids::load()
{
	if (_isRank)
	{
		this->setContentSize(_iw * _row, _ih * _cel);
		_pageMax = std::ceil(_grids.size() * 1.0f / _wh);
	}
	else
	{
		this->setContentSize(_row, _cel);
		_wh = _grids.size();
		_pageMax = 1;
	}

	load(_page);
}



void uiGrids::load(int& page)
{
	int old = _page;
	if (page < 0)
	{
		page = 0;
		return;
	}

	if (page >= _pageMax)
	{
		page = _pageMax - 1;
		return;
	}
	// 物品栏切换用到
	_page = page;
	int size = _grids.size();
	clearSelect(false);

	size = std::min(size, (page + 1) * _wh);

	for (int k = page * _wh; k < size; ++k)
	{
		if (_grids[k] == nullptr)
		{
			continue;
		}
		_grids[k]->setVisible(true);
	}

	if (_select >= 0)
	{
		_grids[_select]->showSelect(true);
	}
}


void uiGrids::remove(int index)
{
	if (!isValid(index))
	{
		return;
	}
	for (int k = _grids.size() - 1; k > index; --k)
	{
		_grids[k]->setPosition(_grids[k - 1]->getPosition());
	}
	_grids[index]->removeFromParent();
	_grids.erase(_grids.begin() + index);
	if (_grids.empty())
	{
		_select = -1;
	}
	else if(_select > 0)
	{
		--_select;
	}
	int pageMax = std::ceil(_grids.size() * 1.0f / _wh);
	if (_page >= pageMax)
	{
		_page = pageMax - 1;
	}
	load();
}


void uiGrids::addPage()
{
	load(++_page);
}

void uiGrids::subPage()
{
	load(--_page);
}


void uiGrids::setSelect(int select)
{
	if (!isValid(select))
	{
		return;
	}
	_grids[_select = select]->showSelect(true);
}

void uiGrids::setGrid(int index, uiGrid* grid)
{
	if (index < 0 || index >= _grids.size())
	{
		return;
	}
	auto g = getGrid(index);
	Vec2 v = grid->getPosition();
	if (g != nullptr)
	{
		v = g->getPosition();
		g->removeFromParent();
	}
	if (grid != nullptr)
	{
		grid->setContentSize(_iw, _ih);
		grid->setPosition(v);
		this->addChild(grid);
	}
	_grids[index] = grid;
}

uiGrid* uiGrids::getGrid(int index)
{
	if (!isValid(index))
	{
		return nullptr;
	}
	return _grids[index];
}

bool uiGrids::isValid(int index)
{
	if (index < 0 || index >= _grids.size() || _grids[index] == nullptr)
	{
		return false;
	}
	return true;
}


bool uiGrids::isSnatched(const Vec2& v)
{
	if (!cNode::isSnatched(v))
	{
		return false;
	}
	int cross;
	if (_isRank)
	{
		cross = (int)v.y / _ih * _row + (int)v.x / _iw;
		cross += _page * _wh;
	}
	else
	{
		for (cross = _grids.size() - 1; cross >= 0; --cross)
		{
			// 只要一页, 不做判断也行
			if (cross / _wh != _page)
			{
				continue;
			}
			auto g = _grids[cross];
			if (g == nullptr)
			{
				continue;
			}
			if (!Rect(g->getPosition(), g->getContentSize()).containsPoint(v))
			{
				continue;
			}
			break;
		}
	}
	if (_cross != cross && isValid(_cross))
	{
		_grids[_cross]->showCross(false);
	}
	if (isValid(cross))
	{
		_grids[cross]->showCross(true);
		_grids[cross]->showDesc(true);
		_cross = cross;
		return true;
	}
	return false;
}


void uiGrids::doEvent(bool left, bool up, int keepTimes)
{
	if (!up || keepTimes > 0)
	{
		return;
	}
	if (_cross < 0 || _cross >= _grids.size())
	{
		if (onClick != nullptr)
		{
			onClick(left);
		}
		return;
	}
	if (_grids[_cross] == nullptr)
	{
		if (onClick != nullptr)
		{
			onClick(left);
		}
	}
	if (!left)
	{
		if (onGrid != nullptr)
		{
			onGrid(_cross, _count, left);
		}
		return;
	}
	if (_select == _cross)
	{
		if ((_isSwitchWhenSelectSame || !_isMutex) && _grids[_select] != nullptr)
		{
			_grids[_select]->switchSelect();
		}
		if (onGrid != nullptr)
		{
			onGrid(_cross, ++_count, left);
		}
	}
	else
	{
		if (_isMutex)
		{
			// _select 肯定有效啊
			if (_select >= 0)
			{
				_grids[_select]->showSelect(false);
			}
			if (_grids[_cross] != nullptr)
			{
				_grids[_cross]->showSelect(true);
			}
		}
		_select = _cross;
		if (onGrid != nullptr)
		{
			onGrid(_cross, _count = 1, left);
		}
	}
}

