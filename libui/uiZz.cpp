#include "uiZz.h"

static const int c_4 = 4, c_12 = c_4 * 3;
bool uiPropertyZz::init(Node* parent, int px, int py, int iy, int px2, int py2)
{
#define ccc_label_create(_label_, _y_)\
parent->addChild(_label_ = cLabel::create("0xFFFF"));\
	_label_->setColor(s565::BLACK);\
	_label_->setPosition(px, py + _y_ * iy);
	// 攻击
	ccc_label_create(_labelAtk, 0);
	// 防御
	ccc_label_create(_labelDef, 1);
	// 体力
	ccc_label_create(_labelHp, 2);
	// 法力
	ccc_label_create(_labelMp, 3);
	// 速度
	ccc_label_create(_labelSpeed, 4);
	// 躲避 
	ccc_label_create(_labelEvade, 5);
	// 寿命
	ccc_label_create(_labelLife, 6);
	// 成长
	ccc_label_create(_labelGrow, 7);
	// 五行
	ccc_label_create(_label5xing, 8);
#undef ccc_label_create


	parent->addChild(_grids = uiGrids::create(4, 3, 42, 42));
	_grids->setPosition(px2, py2);
	_grids->onGrid = [this](int select, int count, bool left)
	{
		if (!left || sTeam::getInstance()->isFighting())
		{
			return;
		}
	};

// 	_skix = px2;
// 	_skiy = py2;

	// 技能翻页
	parent->addChild(_buttonPage = cButton::create(ccu::uSkiNextPage));
	_buttonPage->setPosition(px2 + 172, py2 + 95);
	_buttonPage->onClick = [this]()
	{
		int page = _grids->getPage();
		if (++page >= _grids->getPageMax())
		{
			page = 0;
		}
		_grids->load(page);
	};
	return true;
}

void uiPropertyZz::load(const sProperty& pro)
{
	_buttonPage->setVisible(pro.skis.size() >= 12);
	_grids->clear();
	forv(pro.skis, k)
	{
		auto g = uiGrid::create(pro.skis[k]);
		_grids->load(g);
	}
	_grids->load();

	forv(_equips, k)
	{
		_equips[k]->removeFromParent();
	}
	_equips.clear();
	forv(pro.equips, k)
	{
		const auto& e = pro.equips[k];
		cSprite* sprite = cSprite::create(e.isValid() ? e.getIcon()->small : cSp::c0);
		sprite->setSnatchNode(true);
		_grids->getParent()->addChild(sprite);
		sprite->setPosition(21 + 60 * k, 38);
		if (k == 2)
		{
			sprite->setPositionX(sprite->getPositionX() - 1);
		}
		sprite->setAutoAp(false);
		sprite->setAnchorPoint(Vec2::ZERO);
		cSprite* spriteEquipBack = cSprite::create(ccu::uEquipBack);
		spriteEquipBack->setLocalZOrder(-1);
		spriteEquipBack->setVisible(pro.equips[k].isValid());
		sprite->addChild(spriteEquipBack);
		sDescs descs;
		e.toDesc(descs);
		sprite->setDesc(descs);
		_equips.push_back(sprite);
	}
	load(pro.zz);
}

void uiPropertyZz::load(const sZz& _zz)
{
	// 攻击
	_labelAtk->setVisible(_zz.atk > 0);
	// 防御
	_labelDef->setVisible(_zz.def > 0);
	// 体力
	_labelHp->setVisible(_zz.hp > 0);
	// 法力
	_labelMp->setVisible(_zz.mag > 0);
	// 速度
	_labelSpeed->setVisible(_zz.speed > 0);
	// 躲避 
	_labelEvade->setVisible(_zz.evoid > 0);
	// 寿命
	_labelLife->setVisible(_zz.atk > 0);
	// 成长
	_labelGrow->setVisible(_zz.grow100 > 0);
	// 五行
	_label5xing->setVisible(_zz.atk > 0);

	if (_labelAtk->isVisible())
	{
		// 攻击
		_labelAtk->setString(_zz.atk);
		// 防御
		_labelDef->setString(_zz.def);
		// 体力
		_labelHp->setString(_zz.hp);
		// 法力
		_labelMp->setString(_zz.mag);
		// 速度
		_labelSpeed->setString(_zz.speed);
		// 躲避 
		_labelEvade->setString(_zz.evoid);
		// 寿命
		_labelLife->setString(cc::random(1000, 9999));
		// 成长
		_labelGrow->setString(toString("%0.2f", _zz.grow100 * 0.01f));
		// 五行
		static std::vector<std::string> s_12xings = { "金", "木", "水", "火", "土" };
		_label5xing->setString(s_12xings.at(cc::random(0, (int)s_12xings.size() - 1)));
	}

// 	_button->setVisible(_buttons.size() > c_12);
// 
// 	int size = _buttons.size();
// 	for (int k = 0; k < size; ++k)
// 	{
// 		_buttons[k]->setVisible(false);
// 	}
// 
// 	size = std::min(size, (_page + 1) * c_12);
// 
// 	for (int k = _page * c_12; k < size; ++k)
// 	{
// 		_buttons[k]->setVisible(true);
// 	}
}



uiZz::~uiZz()
{
	if (_notice != nullptr)
	{
		_notice->doNotify();
	}
}

//////////////////////////////////////////////////////////////////////////
bool uiZz::init(uiNotice* notice)
{
	if (!uiPad::init(1338020705, true))
	{
		return false;
	}
	if (!uiPropertyZz::init(this, 128, 100, 23, 20, 313))
	{
		return false;
	}
	_notice = notice;
	return true;
}
