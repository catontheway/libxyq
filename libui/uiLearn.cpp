#include "uiLearn.h"
#include "uiManager.h"

bool uiLearn::init(bool isBangpai)
{

	if (!uiPad::init(isBangpai ? 0x254E7029 : 0x9ED74AA6, true))
	{
		return false;
	}
	_skiMax = isBangpai ? sSki::c160 : sSki::c180;
//	_descs = descs;
//	_skiMax = maxskilv;
	this->addChild(_labelNeedExp = cLabel::create("0"));
	this->addChild(_labelNeedMoney = cLabel::create("0"));
	this->addChild(_labelExp = cLabel::create("0"));
	this->addChild(_labelMoney = cLabel::create("0"));
	this->addChild(_nodeLoad = Node::create());
	_nodeLoad->setTag((int)isBangpai);

	this->addChild(_textDesc = cText::create());
	_textDesc->setColor(s565::BLACK);

	if (isBangpai)
	{
		_labelNeedExp->setPosition(382, 332);
		_labelNeedMoney->setPosition(382, 356);
		_labelExp->setPosition(147, 332);
		_labelMoney->setPosition(147, 356);

		_textDesc->setPosition(30, 207);

		_spriteSelect = cSprite::create(ccu::uItemSelect);
	}
	else
	{
		_labelNeedExp->setPosition(79, 360);
		_labelNeedMoney->setPosition(79, 383);
		_labelExp->setPosition(288, 360);
		_labelMoney->setPosition(288, 383);

		_textDesc->setPosition(210, 72);

		_spriteSelect = cSprite::create(ccu::uItemSelect9);
		_spriteSelect->set9(true);
		_spriteSelect->setContentSize(190, 42);
	}

	this->addChild(_spriteSelect);
	_spriteSelect->setVisible(false);


	for (int k = 0; k < 2; ++k)
	{
		cButton* button = cButton::create4(k == 0 ? "学习" : "学习×5");
		if (isBangpai)
		{
			button->setPosition(k == 0 ? 145 : 275, 405);
		}
		else
		{
			button->setPosition(k == 0 ? 95 : 220, 434);
		}
		this->addChild(button);
		// button->setTag(k == 0 ? 1 : 5);
		int tag = k == 0 ? 1 : 5;
		button->onClick = [this, tag]()
		{
			learn(_skilvs[_select], tag);
		};
	}

	return true;
}

void uiLearn::doClose()
{
	uiPad::doClose();
	if (_isLearned && !sTeam::getInstance()->isFighting() && onLearn != nullptr)
	{
		auto skilvs = _skilvs;
		forv(skilvs, k)
		{
			skilvs[k] -= _skilvOris[k];
		}
		onLearn(skilvs, _expOri - _exp, _moneyOri - _money);
	}
}

void uiLearn::load(const sIcons& icons, const std::vector<int>& skilvs, u64 exp, u64 money)
{
	_icons = icons;	
	_expOri = _exp = exp;
	_moneyOri = _money = money;
	_skilvOris = _skilvs = skilvs;

	_nodeLoad->removeAllChildren();
	_labelLvs.clear();
	if (_nodeLoad->getTag())
	{
		forv(icons, k)
		{
			_skilvs.push_back(skilvs[k]);
			cSprite* sprite = cSprite::create(icons[k].small);
			sprite->setPosition(24 + k * 69, 38);
			sprite->setTag(k);
			_nodeLoad->addChild(sprite);
			// _sprites.push_back(sprite);
			sprite->setSnatchNode(true);
			sprite->onClick = [this, sprite]()
			{
				int skilv = _skilvs[_select = sprite->getTag()];
				updateLabel(skilv);
				_spriteSelect->setVisible(true);
				_spriteSelect->setPosition(sprite->getPosition() - Vec2(3, 6));
				_textDesc->setString(_icons[_select].desc);
			};

			cLabel* label = cLabel::create(toString("%d/%d", 0, _skiMax));
			label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
			label->setPosition(sprite->getPosition() + Vec2(18, 50));
			label->setColor(s565::BLACK);
			_nodeLoad->addChild(label);
			_labelLvs.push_back(label);
		}
	}
	else
	{
		forv(icons, k)
		{
			cNode* node = cNode::create();
			node->setPosition(15, 70 + k * 39);
			cSprite* sprite = cSprite::create(icons[k].small);

			node->setContentSize(170, 40);
			node->setTag(k);
			node->addChild(sprite);
			node->setSnatchNode(true);
			node->onClick = [this, node]()
			{
				int skilv = _skilvs[_select = node->getTag()];
				updateLabel(skilv);
				_spriteSelect->setVisible(true);
				_spriteSelect->setPosition(node->getPosition() - Vec2(10, 6));
				_textDesc->setString(_icons[_select].desc);
			};

			cLabel* label = cLabel::create(icons[k].name);
			label->setPosition(sprite->getContentSize().width + 3, sprite->getPositionY() + sprite->getContentSize().height / 2 - label->getContentSize().height / 2);
			label->setColor(s565::BLACK);
			node->addChild(label);

			cLabel *labelv = cLabel::create(toString("%d/%d", 0, _skiMax));
			labelv->setPosition(106, label->getPositionY());
			labelv->setColor(s565::BLACK);
			node->addChild(labelv);
			_labelLvs.push_back(labelv);

			_nodeLoad->addChild(node);
		}
	}

	updateLabel(_skilvs[0]);
	forv(_labelLvs, k)
	{
		updateLabel(k, _skilvs[k]);
	}
}

void uiLearn::load(sRole& role)
{
	sIcons icons;
	bool isfz = _nodeLoad->getTag();
	if (isfz)
	{
		icons.resize(ccp::fz3);
		const auto& ics = txtIcon::getInstance()->getTables().at(eIcon::技能j);
		forv(icons, k)
		{
			icons.at(k) = ics.at((int)eSki::强壮 + k);
		}
		load(icons, role.fuzhus, role.exp, sBags::getInstance()->money);

	}
	else
	{
		icons.resize(ccp::mp7);
		eIcon e = (eIcon)((int)eIcon::eMenpai0 + (int)role.menpai);
		const auto& ics = txtIcon::getInstance()->getTables().at(e);
		forv(icons, k)
		{
			icons.at(k) = ics.at(k);
		}
		std::vector<int> skilvs(ccp::mp7);
		std::fill(skilvs.begin(), skilvs.end(), role.skilv);
		load(icons, skilvs, role.exp, sBags::getInstance()->money);
	}
	_isLearned = false;
	onLearn = [this, &role, isfz](const std::vector<int> skilvs, u64 exp, u64 money)
	{
		if (isfz)
		{
			forr(skilvs, k)
			{
				role.fuzhus.at(k) += skilvs.at(k);
			}
		}
		else
		{
			role.skilv += skilvs.at(0);
		}
		role.exp.add(-(int)exp);
		sBags::getInstance()->add(-(int)money);
	};
}


bool uiLearn::learn(int skilv, int ilv)
{
	auto ui = ccu::getManager();
	if (_select < 0)
	{
		ui->toast("无效");
		return false;
	}
	if (skilv >= _skiMax)
	{
		ui->toast("技能已满");
		return false;
	}
	if ((!_nodeLoad->getTag()) && _select > 0 && (skilv + ilv) > _skilvs[0])
	{
		ui->toast("不得超过主技能");
		return false;
	}

	u64 exp = 0, money = 0;
	int k = 0;
	for (; k < ilv && skilv + k < _skiMax; ++k)
	{
		exp += sSki::getExp(skilv + k + 1);
		money += sSki::getMoney(skilv + k + 1);
	}
	if (_exp < exp)
	{
		ui->toast("经验不足");
		return false;

	}
	if (_money < money)
	{
		ui->toast("银两不足");
		return false;
	}

	_isLearned = true;
	_exp -= exp;
	_money -= money;
	_skilvs[_select] = skilv += std::max(0, k);
	updateLabel(skilv + 1);
	updateLabel(_select, skilv);
	if (!_nodeLoad->getTag())
	{
		forv(_skilvs, k)
		{
			_skilvs[k] = skilv;
			updateLabel(k, skilv);
		}
	}
	return true;
}


void uiLearn::updateLabel(int skilv)
{
	_labelExp->setString(_exp, true);
	_labelMoney->setString(_money, true);

	_labelNeedExp->setString(sSki::getExp(skilv), true);
	_labelNeedMoney->setString(sSki::getMoney(skilv), true);
}

void uiLearn::updateLabel(int index, int skilv)
{
	_labelLvs[index]->setString(toString("%d/%d", skilv, _skiMax));
}
