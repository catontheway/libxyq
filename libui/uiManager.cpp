#include "uiManager.h"
#include "cDialog.h"
#include "uiAccelator.h"
// #include "uiAddpoint.h"
#include "uiChannel.h"
// #include "uiDazao.h"
#include "uiDye.h"
// #include "uiFriend.h"
#include "uiFoot.h"
// #include "uiGrids.h"

#include "uiHeader.h"
// #include "uiInputNO.h"
#include "uiItem.h"
#include "uiJob.h"
#include "uiLearn.h"
#include "uiMenu.h"
#include "uiPet.h"
// #include "uiRank.h"
#include "uiSee.h"
#include "uiShichen.h"
#include "uiShop.h"
#include "uiSkill.h"
#include "uiSkiSelect.h"
#include "uiSmap.h"
#include "uiState.h"
#include "uiWorld.h"


static uiManager* s_ui = nullptr;
uiManager* ccu::getManager()
{
	return s_ui;
}

void ccu::setManager(uiManager* ui)
{
	s_ui = ui;
}

void ccu::hideSpriteDesc()
{
	if (s_ui == nullptr)
	{
		return;
	}
	s_ui->getDesc()->setVisible(false);
}

cSprite* ccu::getSpriteDesc()
{
	if (s_ui == nullptr)
	{
		return nullptr;
	}
	return s_ui->getDesc();
}



bool uiManager::init()
{
	if (!cNode::init())
	{
		return false;
	}

	this->setPosition(0, 0);
	this->setSnatchNode(true);



	this->addChild(_accelator = uiAccelator::create());


	int temp = 5;
 	this->addChild(_channel = uiChannel::create(eFont::chat, eCanvas::nor));
	_channel->cNode::addChild(_desc = cSprite::create(ccu::uDesc));
	_desc->set9(true);
	_desc->setContentSize(310, 120);
	_desc->setPositionX(-temp);
	_channel->setContentSize(_desc->getContentSize().width - temp, _desc->getContentSize().height);
	_channel->getInner()->setContentSize(_channel->getContentSize().width, 0);
	_channel->getInner()->updateOrderOfArrival();
	_channel->setPosition(temp, cc::vsSize().height - _channel->getContentSize().height);
	_channel->setVisible(false);


	this->addChild(_chat = uiChannel::create(eFont::chat, eCanvas::chat));
	_chat->setContentSize(cApp::getInstance()->getChatw() - temp, cc::vsSize().height - temp);
	_chat->getInner()->setContentSize(_channel->getContentSize().width, 0);
	_chat->setSnatchNode(false);
	_chat->getInner()->setSnatchNode(false);
	_chat->setPositionX(2);

// 	this->addChildEvent(_dazao = uiDazao::create());
	this->addChild(_desc = cSprite::create(ccu::uDesc), ccu::zDesc);
	_desc->set9(true);
	_desc->setVisible(false);

 	this->addChild(_dialog = cDialog::create(), ccu::zDialog);
	this->addChild(_dye = uiDye::create());

//	this->addChild(_friend = uiFriend::create());
	this->addChild(_foot = uiFoot::create());
	this->addChild(_foot2 = uiFoot2::create());

	this->addChild(_headerRole = uiHeader::create(false), ccu::zHead);
	_headerRole->setPosition(cc::vsSize().width - _headerRole->getContentSize().width, 0);

	this->addChild(_headerPet = uiHeader::create(true), ccu::zHead);
	_headerPet->setPosition(_headerRole->getPositionX() - _headerPet->getContentSize().width, 0);

	this->addChild(_item = uiItem::create());

	this->addChild(_job = uiJob::create(), ccu::zJob);

	this->addChild(_leaderTop = uiLeaderTop::create());

	this->addChild(_learnBp = uiLearn::createBangpai());
	this->addChild(_learnMp = uiLearn::createMenpai());
 
 	this->addChild(_menu = uiMenu::create(), ccu::zMenu);

	this->addChild(_pet = uiPet::create());
	this->addChild(_see = uiSee::create());

 	this->addChild(_shichen = uiShichen::create(), ccu::zShichen);
	this->addChild(_shop = uiShop::create());

	this->addChild(_skill = uiSkill::create());
	this->addChild(_skillSelect = uiSkiSelect::create());
	this->addChild(_smap = uiSmap::create());
	this->addChild(_state = uiState::create());
	this->addChild(_world = uiWorld::create());
	this->addChild(_xiangrui = uiXiangRui::create());
	this->addChild(_zz = uiZz::create(nullptr));
	////////////////////////////////////////////////////////////////////////// 
	_accelator->setPosition(cc::vsSize().width - 288, 
		cc::vsSize().height - _menu->getContentSize().height - _accelator->getContentSize().height);

	return true;
}


void uiManager::toast(const std::string& text, float second /* = 5 */)
{
	cTagManager::getInstance()->add(this, text, second);
}


void uiManager::addChannel(eChannel e, const std::string& name, const std::string& text)
{
	_channel->add(e, name, text);
	_chat->add(e, name, text);
}

void uiManager::addChannel(const std::string& text)
{
	addChannel(eChannel::eChannelNone, "", text);
}


// void uiManager::setCursor(eCursor e)
// {
// 	_cursor->setState(e);
// }
// 
// const eCursor& uiManager::getCursor()
// {
// 	return _cursor->getState();
// }
// 
void uiManager::addJob(const std::string& title, const std::string& text)
{
	_job->add(title, text);
}





void uiManager::setBattle(bool battle)
{
	if (battle)
	{
		_desc->setVisible(false);
		_menu->setBattle(battle);
		_shichen->setBattle(battle);
		_skillSelect->setVisible(false);
	}
	else
	{

	}
}

