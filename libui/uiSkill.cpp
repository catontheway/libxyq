#include "uiSkill.h"
#include "uiManager.h"


bool uiSkill::init()
{
	if (!uiPad::init(1044547630, true))
	{
		return false;
	}

	// 存放主技能相关的节点
	this->addChild(_nodeMain = Node::create());
	this->addChild(_buttonMain = cButton::create4("师门"));
	_buttonMain->setPosition(25, 25);
	_buttonMain->onClick = [this]()
	{
		uiPad::load(1044547630);
		doHide();
		_nodeMain->setVisible(true);
	};
	// 存放辅助相关的节点
	this->addChild(_nodeFuzhu = Node::create());
	this->addChild(_buttonFuzu = cButton::create4("辅助"));
	_buttonFuzu->setPosition(130, 25);
	_buttonFuzu->onClick = [this]()
	{
		uiPad::load(1560928702);
		doHide();
		_nodeFuzhu->setVisible(true);
	};
	// 存放修炼相关的节点
	this->addChild(_nodeXl = Node::create());
	this->addChild(_buttonXl = cButton::create4("修炼"));
	_buttonXl->setPosition(235, 25);
	_buttonXl->onClick = [this]()
	{
		uiPad::load(993909921);
		doHide();
		_nodeXl->setVisible(true);
	};
	// 奇经八脉
	this->addChild(_buttonQj8m = cButton::create4("奇经八脉"));
	_buttonQj8m->setPosition(340, 25);
//	_buttonQj8m->setDesc("奇经八脉效果已整合到门派附加属性中");
	_buttonQj8m->onClick = [this]()
	{
		if (onQj8m != nullptr)
		{
			onQj8m();
		}
	};


	// 描述
	this->addChild(_textDesc = cText::create(140));
	_textDesc->setColor(s565::BLACK);
	_textDesc->setPosition(250, 65);

	// 修炼
	static std::vector<std::string> s_xlnames = { "攻击", "防御", "法术", "法防" };
	const int c4 = sXl::c4, c8 = c4 * 2, c380 = 380, c25 = 25;
	for(int k = 0; k < c8; ++k)
	{
		cNode* node = cNode::create();
		cLabel* label1 = cLabel::create(s_xlnames[k % c4] + "修炼  等级: ");
		label1->setColor(s565::BLACK);
		node->addChild(label1);
		label1->setPosition(5, c25 / 2 - label1->getContentSize().height / 2);
		cLabel* labelv = cLabel::create("20/35空白");
		labelv->setColor(s565::BLACK);
		labelv->setTag(0);
		node->addChild(labelv);
		labelv->setPosition(label1->getPositionX() + label1->getContentSize().width, label1->getPositionY());
		cLabel* labelup = cLabel::create("升级所需经验 ");
		labelup->setColor(s565::BLACK);
		node->addChild(labelup);
		labelup->setPosition(labelv->getPositionX() + labelv->getContentSize().width, labelv->getPositionY());
		cLabel* labelNeed = cLabel::create("0");
		labelNeed->setColor(s565::BLACK);
		labelNeed->setTag(1);
		node->addChild(labelNeed);
		labelNeed->setPosition(labelup->getPositionX() + labelup->getContentSize().width, labelup->getPositionY());

		node->setContentSize(c380, c25);
		node->setTag(k);
		_nodeXl->addChild(node);
		int y = (k < c4) ? 107 : 277;
		node->setPosition(36, y + (k % c4) * c25);
		node->setSnatchNode(true);
		node->onClick = [this, node]()
		{
			_spriteXLselece->setVisible(true);
			_spriteXLselece->setPosition(node->getPosition() - Vec2(8, 5));
			_xiulianSelect = node->getTag();
		};

// 		// 修炼等级
// 		button->addChild(_labelXLvs[k] = Label::create("0/0"));
// 		_labelXLvs[k]->setPosition(140, button->getContentSize().height / 2 - _labelXLvs[k]->getContentSize().height / 2);
// 		_labelXLvs[k]->setColor(Color3B::BLACK);
// 		// 修炼经验
// 		button->addChild(_labelXLExps[k] = Label::create("经验 "));
// 		_labelXLExps[k]->setPosition(220, _labelXLvs[k]->getPositionY());
// 		_labelXLExps[k]->setColor(Color3B::BLACK);
	}

	// 修炼选择
	_nodeXl->addChild(_spriteXLselece = cSprite::create(ccu::uItemSelect9));
	_spriteXLselece->set9(true);
	_spriteXLselece->setVisible(false);
	_spriteXLselece->setContentSize(c380 + 10, c25 + 8);

	// 点修模式
	_nodeXl->addChild(_buttonLearnXl = cButton::create4("点修"), false);
	_buttonLearnXl->setPosition(180, 410);
	_buttonLearnXl->onClick = [this]()
	{
		if (_xiulianSelect >= 0)
		{
			learnXL(_xiulianSelect >= sXl::c4, _xiulianSelect % sXl::c4);
		}
	};

	this->addChild(_spriteSelect = cSprite::create(ccu::uItemSelect));
	_spriteSelect->setVisible(false);

// 	this->addChildEvent(_buttonLearn500 = Button::create4("习×500"), false);
// 	_buttonLearn500->setPosition(240, 410);
// 	_nodeXl->addChild(_buttonLearn500);
// 	_buttonLearn500->onClick = [&](Button* btn)
// 	{
// 		learnXL(50);
// 	};

	_buttonMain->onClick();
//	showXLbutton(false);
	return true;
}

void uiSkill::load(sRole& role)
{
	_nodeMain->removeAllChildren();
	_nodeFuzhu->removeAllChildren();
	_role = role;
	_xlOri = role.xl;
	_xlbbOri = role.xlbb;
	_moneyOri = sBags::getInstance()->money;
	// 主技能
	static std::vector<Vec2> s_vMians =
	{
		Vec2(105, 130),
		Vec2(105, 60),
		Vec2(105, 200),
		Vec2(45, 95),
		Vec2(45, 165),
		Vec2(165, 95),
		Vec2(165, 165),
	};
	if (role.menpai != eMenpai::None)
	{
		eIcon e = (eIcon)((int)eIcon::eMenpai0 + (int)role.menpai);
		const auto& ics = txtIcon::getInstance()->getTables().at(e);
		for(int k = 0; k < ccp::mp7; ++k)
		{
			const auto& icon = ics.at(k);
			cSprite* sprite = createSprite(icon.big, icon.name);
			_nodeMain->addChild(sprite);
			sprite->setPosition(s_vMians[k]);


			cLabel* label = cLabel::create(cc::toString(role.skilv));
			label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
			label->setColor(s565::BLACK);
			label->setPosition(sprite->getPosition() + Vec2(32, 45) - Size(label->getContentSize().width / 2, 0));
			_nodeMain->addChild(label);

		//	_nodeMain->addChild(createMain(k));
		}
		_nodeMain->addChild(createMain(0));
	}


	_nodeMain->addChild(createSpecial());

	const auto& ics = txtIcon::getInstance()->getTables().at(eIcon::技能j);
	forv(role.fuzhus, k)
	{
		const auto& icon = ics.at((int)eSki::强壮 + k);
		cSprite* sprite = createSprite(icon.big, icon.name + "\n#R" + icon.desc);
		sprite->setPosition(14 + 60 * k, 276);
		_nodeFuzhu->addChild(sprite);

		cLabel* label = cLabel::create(cc::toString(role.fuzhus.at(k)));
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
		label->setColor(s565::BLACK);
		label->setPosition(sprite->getPosition() + Vec2(32, 49) - Size(label->getContentSize().width / 2, 0));
		_nodeFuzhu->addChild(label);
	}

	for (int k = 0; k < sXl::c4 * 2; ++k)
	{
		loadXL(k);
	}

	_isLearned = false;
	onXL = [this, &role](const sXl& xl, const sXl& xlbb, u64 money)
	{
		role.xl = xl;
		role.xlbb = xlbb;
		sBags::getInstance()->add(-(int)money);
	};
}

void uiSkill::doHide()
{
	_nodeMain->setVisible(false);
	_nodeFuzhu->setVisible(false);
	_nodeXl->setVisible(false);
	_textDesc->setVisible(false);
	_spriteSelect->setVisible(false);
}

void uiSkill::showMain(int k)
{
	for (int i = 0; i < ccp::mp7; ++i)
	{
		_nodeMain->getChildByTag(i)->setVisible(false);
	}
	_nodeMain->getChildByTag(k)->setVisible(true);
}

cSprite* uiSkill::createSprite(ulong uid, const std::string& desc, const std::function<void()>& onClickEx /* = nullptr */)
{
	cSprite* sprite = cSprite::create(uid);
	sprite->setSnatchNode(true);
	sprite->onClick = [this, desc, onClickEx, sprite]()
	{
		_spriteSelect->setVisible(true);
		_spriteSelect->setPosition(sprite->getPosition() - Vec2(3, 6));
		_textDesc->setVisible(true);
		_textDesc->setString(desc);
		if (onClickEx != nullptr)
		{
			onClickEx();
		}
	};
	return sprite;
}

cocos2d::Node* uiSkill::createMain(int tag)
{
	Node* node = Node::create();
//	node->setPosition(27, 275);
	node->setTag(tag);
	// 师门技能
	sSkis skis;
	ccp::addSki(skis, _role.menpai, true);
	forv(skis, k)
	{
		const auto& e = skis.at(k).getSki();
		const auto& icon = txtIcon::getInstance()->getTables().at(eIcon::技能j).at((int)e);
		std::string desc = icon.name + "\n" + icon.desc;
		const auto& cost = txtSkill::getInstance()->getCosts().at(e).desc;
		if (!cost.empty())
		{
			desc += "\n#R消耗:#R\n#B" + cost;
		}
		cSprite* sprite = createSprite(icon.big, desc);
		sprite->setPosition(27 + (k % ccp::mp7) * 60, 275 + (k / ccp::mp7) * 50);
		node->addChild(sprite);
	}
//	node->setVisible(false);
	return node;
}


cocos2d::Node* uiSkill::createSpecial()
{
	Node* node = Node::create();
//	node->setPosition(40, 384);
	// 特技
	sPropertys pros;
	ccp::apply(pros, _role);
	forv(pros.specials, k)
	{
		const auto& e = pros.specials.at(k);
		const auto& icon = txtIcon::getInstance()->getTables().at(eIcon::技能j).at((int)e);
		std::string desc = icon.name + "\n" + icon.desc;
		const auto& cost = txtSkill::getInstance()->getCosts().at(e).desc;
		if (!cost.empty())
		{
			desc += "\n#R消耗:#R\n#B" + cost;
		}
		cSprite* sprite = createSprite(icon.big, desc);
		sprite->setPosition(40 + k * 66, 384);
		node->addChild(sprite);
	}
	return node;
}



void uiSkill::loadXL(int select)
{
	bool isbb = select >= sXl::c4;
	auto& xl = isbb ? _role.xlbb.lvs[select - sXl::c4] : _role.xl.lvs[select];
	auto node = _nodeXl->getChildByTag(select);
	cLabel* labelv = (cLabel*)node->getChildByTag(0);
	cLabel* labelNeed = (cLabel*)node->getChildByTag(1);
	labelv->setString(toString("%d/%d", xl, sXl::getLv(_role.lv)));
	labelNeed->setString(xl == sXl::c25 ? "---" : cc::toString(sXl::getExp(xl + 1)));
}


void uiSkill::learnXL(bool isbb, int select4)
{
	auto& xl = isbb ? _role.xlbb.lvs[select4] : _role.xl.lvs[select4];
	if (xl >= sXl::c25)
	{
		return;
	}
	auto need = sXl::getExp(xl + 1) * sXl::c2000;
	auto& money = sBags::getInstance()->money;
	if (money < need)
	{
		ccu::getManager()->toast("银两不足");
		return;
	}
	++xl;
	money.add(-need);
	_isLearned = true;
	loadXL(select4 + (isbb ? 1 : 0) * sXl::c4);
}

void uiSkill::showXLbutton(bool show)
{
	_buttonLearnXl->setVisible(show);
}

void uiSkill::doClose()
{
	uiPad::doClose();
	if (_isLearned && !sTeam::getInstance()->isFighting() && onXL != nullptr)
	{
		onXL(_role.xl, _role.xlbb, _moneyOri - sBags::getInstance()->money);
	}
}
