#include "uiAccelator.h"
#include "uiManager.h"
#include "uiSkiSelect.h"


static Size s_size = Size::ZERO;
static const int s_inv = 4;
bool uiAccelator::init()
{
	if (!cNode::init())
	{
		return false;
	}
	this->setSnatchNode(true);
	int c12 = 12;
	this->setContentSize(c8 * c32, c32 + c12);
	this->setDragType(eMouseDrag::Both);

	for (int k = 0; k < c8; ++k)
	{
		cSprite* sprite = cSprite::create(76806695);
		this->addChild(sprite);
		sprite->setPosition(k * c32, c12);

		cLabel* label = cLabel::create("F" + cc::toString(k + 1), eFont::smal);
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		label->setPosition(k * c32 + c32 / 2, c12);
		label->setBack(true);
		this->addChild(label);
	}

	this->addChild(_grids = uiGrids::create(c8, 1, c32, c32));
	_grids->setPositionY(c12);

	_grids->onGrid = [this](int index, int count, bool left)
	{
		if (left && onAccelator != nullptr)
		{
			_grids->clearSelect();
			onAccelator(index);
		}
		else if (!left && _skis[index].isValid() && onClear != nullptr)
		{
			onClear(index);
			load(index, sSki());
		}
	};
	setVisible(false);
	return true;
}

void uiAccelator::load(const sSkis& acces)
{
	_skis = acces;
	_grids->clear();
	forv(acces, k)
	{
		auto g = uiGrid::create(acces[k], false);
		_grids->load(g);
	}
	_grids->load();
}

void uiAccelator::load(int idx, const sSki& acc)
{
	_skis.at(idx) = acc;
	_grids->getGrid(idx)->load(acc, false);
}


void uiAccelator::load(sRole& role)
{
	load(role.acces);
	onClear = [this, &role](int idx)
	{
		role.acces.at(idx).setData(eSki::eSkiNone);
	};
	
	onAccelator = [this, &role](int idx)
	{
		if (!sTeam::getInstance()->isFighting())
		{
			if (role.menpai == eMenpai::None)
			{
				ccu::getManager()->toast("无门派技能");
				return;
			}
			auto skiSele = ccu::getManager()->getSkiSelect();
			if (skiSele->switchVisible())
			{
				sSkis skis;
				ccp::addSki(skis, role.menpai, true);
				skiSele->load(skis);
				skiSele->onSelect = [this, &role, idx](int, const sSki& ski, bool left)
				{
					if (left)
					{
						role.acces.at(idx) = ski;
						load(idx, ski);
					}
				};
			}
			return;
		}
	};
}
