#include "uiMenu.h"
#include "uiManager.h"
#include "uiSmap.h"

bool uiMenu::init()
{
	if (!cNode::init())
	{
		return false;
	}

	cSprite* sprite = cSprite::create(0x3D1FA249);
	this->addChild(sprite);

	int x = 0;
// 	this->addChildSnatch(_buttonAtk = Button::create(1807500026));
// 	_buttonAtk->setDesc("攻击A");
// 	_buttonAtk->setPosition(x, y);
// 	x += _buttonAtk->getContentSize().width;
// 	_buttonAtk->onClick = [&](Button* btn)
// 	{
// 
// 	};

#define ccc_menu_init(_btn_, _uid_, _desc_)\
	this->addChild(_btn_ = cButton::create(_uid_));\
	_btn_->setDesc(_desc_);\
	_btn_->setPosition(x, 0);\
	x += _btn_->getContentSize().width + 5;\
	_btn_->onClick = [this]()

	ccc_menu_init(_buttonAtk, 1807500026, "攻击A")
	{
		cCursor::getInstance()->setCursor(eCursor::Atk);
	};

	ccc_menu_init(_buttonPack, 240383749, "包裹E")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::E);
		}
	};

	ccc_menu_init(_buttonGive, 2119033822, "给予G")
	{
		cCursor::getInstance()->setCursor(eCursor::Give);
	};

	ccc_menu_init(_buttonTrade, 0xCAB0B8B4, "交易X")
	{
		cCursor::getInstance()->setCursor(eCursor::Trade);
	};

	ccc_menu_init(_buttonTeam, 222208523, "队伍T")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::T);
		}
	};

	ccc_menu_init(_buttonPet, 250440769, "宠物P")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::P);
		}
	};

	ccc_menu_init(_buttonJob, 0xA15292B2, "任务Q")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::Q);
		}
	};

	ccc_menu_init(_buttonBp, 3277532867, "???")
	{
		cCursor::getInstance()->setCursor(eCursor::Team);
	};

	ccc_menu_init(_buttonAcce, 3144573054, "快捷C")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::C);
		}
	};

	ccc_menu_init(_buttonMsg, 2088395993, "消息F")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::F);
		}
	};

	ccc_menu_init(_buttonSys, 0x5116F7DF, "系统S")
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::S);
		}
	};


#undef ccc_menu_init

	this->setContentSize(x, _buttonSys->getContentSize().height + 3);
	sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	sprite->setPosition(_contentSize.width + 10, _contentSize.height);

	this->setPosition(cc::vsSize() - _contentSize);
	this->scheduleUpdate();
	return true;
}

void uiMenu::setBattle(bool battle)
{
	_buttonAtk->setEnabled(!battle);
	_buttonPack->setEnabled(!battle);
	_buttonGive->setEnabled(!battle);
	_buttonTrade->setEnabled(!battle);
	_buttonTeam->setEnabled(!battle);
	_buttonPet->setEnabled(!battle);
//	_buttonJob->setEnabled(!battle);
	_buttonBp->setEnabled(!battle);
//	_buttonAcce->setEnabled(!battle);
	_buttonMsg->setEnabled(!battle);
//	_buttonSys->setEnabled(!battle);
}

void uiMenu::update(float delta)
{
	if (sTeam::getInstance()->isFighting())
	{
		return;
	}
	auto input = cInput::getInstance();
	if (input->isKdown(DIK_TAB))
	{
		ccu::getManager()->getSmap()->switchVisible();
	}
	else if (input->isKdown(DIK_W))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::W);
		}
	}
	else if (input->isKdown(DIK_A))
	{
		cCursor::getInstance()->setCursor(eCursor::Atk);
	}
	else if (input->isKdown(DIK_E))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::E);
		}
	}
	else if (input->isKdown(DIK_G))
	{
		cCursor::getInstance()->setCursor(eCursor::Give);
	}
	else if (input->isKdown(DIK_X))
	{
		cCursor::getInstance()->setCursor(eCursor::Trade);
	}
	else if (input->isKdown(DIK_T))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::T);
		}
	}
	else if (input->isKdown(DIK_O))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::O);
		}
	}
	else if (input->isKdown(DIK_P))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::P);
		}
	}
	else if (input->isKdown(DIK_Q))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::Q);
		}
	}
	else if (input->isKdown(DIK_C))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::C);
		}
	}
	else if (input->isKdown(DIK_F))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::F);
		}
	}
	else if (input->isKdown(DIK_S))
	{
		if (onOperate != nullptr)
		{
			onOperate(eOperator::S);
		}
	}
}
