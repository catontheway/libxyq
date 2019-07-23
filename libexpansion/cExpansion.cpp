#include "cExpansion.h"

#include "expChat.h"
#include "expIcon.h"
#include "expMenpai.h"
#include "expNpc.h"
#include "expPet.h"
#include "expRole.h"
#include "expSkill.h"
#include "expXiangrui.h"
#include "expZuoqi.h"
#include "expZz.h"


static std::vector<std::string> s_stocks;
bool expStock::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	if (s_stocks.empty())
	{
		cWdf wdf;
		wdf.loadRoot(cFolder::getInstance()->getWd() + "stock.wdf");
		std::vector<std::string> strs;
		for (int k = 0, length = wdf.getIndexsCount(); k < length; ++k)
		{
			auto ptr = wdf.getData(wdf.getIndexs() + k);
			if (strlen(ptr) < 32)
			{
				delete ptr;
				continue;
			}
			cc::split(ptr, "N P", strs);
			delete ptr;
			for (auto s : strs)
			{
				s = cc::replace(s, "\r\n", "");
				s = cc::replace(s, "\n", "");
				s = cc::replace(s, "\t", "");
				if (s.empty())
				{
					continue;
				}
				s_stocks.push_back(s);
			}
		}
	}
	for (int k = 0; k < s_stocks.size(); k += 10)
	{
		initButton(cc::toString(k / 10));
	}
	initButton();
	return expEasy::init(initDrag(0));
}

cNode* expStock::initDrag(int tag, int tag2 /*= cTagNone*/)
{
	cNode* node = cNode::create();
	int x = _btnw + 40,y = 20, iy = 20;
	for (int k = tag * 10; k < (tag + 1) * 10 && k < s_stocks.size(); ++k)
	{
		cLabel* lable = cLabel::create(toString("%d.", k + 1));
		lable->setColor(s565::GREEN);
		lable->setPosition(x - lable->getContentSize().width, y);
		node->addChild(lable);
		cText* text = cText::create(cc::vsSize().width - x - iy);
		text->setString(s_stocks[k]);
		text->setPosition(x, y);
		node->addChild(text);
		y += text->getContentSize().height + iy;
	}
	node->setContentSize(cc::vsSize().width, y += iy);
	return node;
}

static std::vector<std::string> s_talks;
bool expTalk::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	if (s_talks.empty())
	{
		cWdf wdf;
		wdf.loadRoot(cFolder::getInstance()->getWd() + "talk.wdf");
		std::vector<std::string> strs;
		for (int k = 0, length = wdf.getIndexsCount(); k < length; ++k)
		{
			auto ptr = wdf.getData(wdf.getIndexs() + k);
			if (strlen(ptr) < 32)
			{
				delete ptr;
				continue;
			}
			cc::split(ptr, "N P", strs);
			delete ptr;
			for (auto s : strs)
			{
				s = cc::replace(s, "\r\n", "");
				s = cc::replace(s, "\n", "");
				if (s.empty())
				{
					continue;
				}
				s_talks.push_back(s);
			}
		}
	}

	for (int k = 0; k < s_talks.size(); k += 100)
	{
		initButton(cc::toString(k / 100));
	}
	initButton();
	return expEasy::init(initDrag(0));
}

cNode* expTalk::initDrag(int tag, int tag2 /*= cTagNone*/)
{
	cNode* node = cNode::create();
	int x = _btnw + 60, y = 20, iy = 20;
	for(int k = tag * 100; k < (tag + 1) * 100 && k < s_talks.size(); ++k)
	{
		cLabel* lable = cLabel::create(toString("%d.", k + 1));
		lable->setColor(s565::GREEN);
		lable->setPosition(x - lable->getContentSize().width, y);
		node->addChild(lable);
		cText* text = cText::create(cc::vsSize().width - x - iy);
		text->setString(s_talks[k]);
		text->setPosition(x, y);
		node->addChild(text);
		y += text->getContentSize().height + iy;
	}
	node->setContentSize(cc::vsSize().width, y += iy);
	return node;
}


bool cExp::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	return expEasy::init(initDrag(0));
}

cNode* cExp::initDrag(int tag, int tag2 /*= cTagNone*/)
{
	cNode* node = cNode::create();
	cLabel* lable = cLabel::create("Q群:");
	lable->setPosition(20, 20);
	node->addChild(lable);
	return node;
}



const int cExpansion::cy = 20;
const int cExpansion::cx = 20;
bool cExpansion::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_y = 20;
	_director = Director::getInstance();

	onButton("表情包", expChat::create);
	const auto& txt = txtEasy::getInstance();
	onButtonEasy("传送阵", txt->getTransmits());
	onButtonEasy("队长令牌", txt->getTops());
	onButtonEasy("足迹", txt->getDazzles());
	onButtonEasy("狼爪印", txt->getFoots());
	onRank();
	onButtonEasy("法术预留", txt->getMagicWhat());
	onButtonEasy("_magic", txt->get_magic());
	onButtonEasy("magic", txt->getMagic());
	onButtonEasy("击打", txt->getMagicImpact());
	onButtonEasy("状态", txt->getMagicState());
	onButtonEasy("未知状态", txt->getMagicStateUnkown());
	onButtonEasy("迭代", txt->getMagicIter());
	onButtonEasy("未知", txt->getMagicUnkown());
	onRank();
	onButton("物品", expIcon::create);
	onButton("武器", expIconWeapon::create);
	onButton("装备", expIconEquip::create);
	onButton("门派", expMenpai::create);
	onButton("技能", expSkill::create);
	onRank();
	onButton("宝宝资质", expZz::create);
	onButton("唯美头像", expZz::createWm);
	onButton("宝宝", expPet::create);
	onButton("角色", expRole::create);
	onRank();
	onButton("NPC", expNpc::create);
	onButton("坐骑", expZuoqi::create);
	onButton("(唯美)", expZuoqi::createWm);
	onButton("祥瑞", expXiangrui::create);
	onRank();

	onButton("对话", expTalk::create);
	onButton("三界", expStock::create);
	onButton("狼宝", cExp::create)->setDesc("版本: v20190520");
	onRank();

	return true;
}

cButton* cExpansion::onButton(const std::string& name, const std::function<Scene*()>& onScene)
{
	cButton* button = cButton::create4(name);
	_buttons.push_back(button);
	button->onClick = [this, onScene]()
	{
		if (onScene != nullptr)
		{
			_director->pushScene(onScene());
		}
	};
	return button;
}

cButton* cExpansion::onButtonEasy(const std::string& name, const txtEasy::sTable& txts)
{
	cButton* button = cButton::create4(name);
	_buttons.push_back(button);
	button->onClick = [this, name, txts]()
	{
		_director->pushScene(expEasy::createEasy(name, txts));
	};
	return button;
}

void cExpansion::onRank()
{
	_r.init(cc::vsSize().width - cx * 2);
	Node* node = Node::create();
	forv(_buttons, k)
	{
		node->addChild(_buttons[k]);
		_r.iter(_buttons[k]);
	}
	_r.iter();
	node->setContentSize(_r.getSize());
	node->setPosition(cx, _y);
	_y += node->getContentSize().height + cy;
	this->addChild(node);
	_buttons.clear();
}

