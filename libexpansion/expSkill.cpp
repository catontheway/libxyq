#include "expSkill.h"

//////////////////////////////////////////////////////////////////////////
bool expSkill::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	_names.push_back({ "被动技能", eSkill::eSkied0, eSkill::eSkiedEnd });
	_names.push_back({ "宝宝技能", (eSkill)((int)eSkill::eSkiedEnd + 1), eSkill::ePetSkiEnd });
	_names.push_back({ "特技", eSkill::eSpecial0, eSkill::eSpecialEnd });
	_names.push_back({ "大唐官府", eSkill::eDt0, eSkill::eDtEnd });
	_names.push_back({ "方寸山", eSkill::eFc0, eSkill::eFcEnd });
	_names.push_back({ "化生寺", eSkill::eHs0, eSkill::eHsEnd });
	_names.push_back({ "女儿村", eSkill::eNe0, eSkill::eNeEnd });
	_names.push_back({ "天宫", eSkill::eTg0, eSkill::eTgEnd });
	_names.push_back({ "东海龙宫", eSkill::eLg0, eSkill::eLgEnd });
	_names.push_back({ "五庄观", eSkill::eWz0, eSkill::eWzEnd });
	_names.push_back({ "普陀山", eSkill::ePt0, eSkill::ePtEnd });
	_names.push_back({ "阴曹地府", eSkill::eDf0, eSkill::eDfEnd });
	_names.push_back({ "魔王寨", eSkill::eMw0, eSkill::eMwEnd });
	_names.push_back({ "狮驼岭", eSkill::eSt0, eSkill::eStEnd });
	_names.push_back({ "盘丝洞", eSkill::ePs0, eSkill::ePsEnd });
	_names.push_back({ "凌波城", eSkill::eLb0, eSkill::eLbEnd });
	_names.push_back({ "无底洞", eSkill::eWd0, eSkill::eWdEnd });
	_names.push_back({ "神木林", eSkill::eSm0, eSkill::eSmEnd });
	_names.push_back({ "辅助技能", eSkill::eFuzhu0, eSkill::eFuzhuEnd });
	for (const auto& name : _names)
	{
		initButton(name.name/*, name.name == _names.back().name*/);
	}
	initButton();
	return expEasy::init(initDrag(0));
}

static const auto& icons = txtIcon::getInstance()->getTables();
const auto& skills = txtSkill::getInstance()->getTables();
const auto& costs = txtSkill::getInstance()->getCosts();
const auto& acts = txtSkill::getInstance()->getActs();
const auto& hits = txtSkill::getInstance()->getHits();
const auto& states = txtSkill::getInstance()->getStateExs();
cNode* expSkill::initDrag(int tag, int tag2 /* = cTagNone */)
{
	eSkill begin = _names.at(tag).begin, end = _names.at(tag).end;
	const auto& skis = icons.at(eIcon::技能j);
	int x = 0, y = 0, wSprite = 0, hSprite = 0, wText = 0, wMax = 0, hMax = 0, k = 0;
	cLabel* label;
	cSprite* sprite;
	cText* text = nullptr;
	cNode* node = cNode::create();
	cNode* nodeInner;
	std::vector<ulong> uids;
	expRank r;
	for (eSkill eski = begin; eski <= end; eski = (eSkill)((int)eski + 1))
	{
		const auto& it = skis.find((int)eski);
		if (it == skis.end())
		{
			continue;
		}
		const auto &ski = it->second;
		node->addChild(sprite = createSpriteWithName(ski.big, ski.name));
		if (hSprite == 0)
		{
			wSprite = sprite->getContentSize().width;
			hSprite = sprite->getContentSize().height;
			wText = _wButBtn - c10 * 3 - wSprite * 2;
			x = wSprite * 2 + c10;
		}
		sprite->setPosition(0, y);

		if (ski.small != ski.big)
		{
			node->addChild(sprite = cSprite::create(ski.small));
			sprite->setPosition(wSprite + 5, y);
		}

		node->addChild(text = cText::create(wText));
		text->setString("#Y" + ski.desc);
		text->setPosition(x, y);
		hMax = text->getContentSize().height;
		if (wMax < x + text->getContentSize().width)
		{
			wMax = x + text->getContentSize().width;
		}

		const auto& it2 = costs.find(eski);
		if (it2 != costs.end())
		{
			node->addChild(label = cLabel::create("消耗: " + it2->second.desc, eFont::smal));
			label->setPosition(x, y + (hMax += 5));
			label->setColor(s565::RED);
			hMax += text->getContentSize().height;

		}
		getuids(eski, uids);
		node->addChild(nodeInner = cNode::create());
		r.init(_wButBtn - x);
		for (const auto& u : uids)
		{
			nodeInner->addChild(sprite = cSprite::create(u));
			if (sprite->isValid())
			{
				sprite->play();
			}
			r.iters({ sprite }/*, (++k) == uids.size()*/);
			sprite->setTag(u);
		}
		r.iters();
		for (const auto& u : uids)
		{
			nodeInner->addChild(label = cLabel::create(toString("%08X", u), eFont::smal));
			label->setColor(s565::YELLOW);
			label->setPosition(nodeInner->getChildByTag(u)->getPosition() - label->getContentSize() / 2);
			label->setVisible(false);
		}
		nodeInner->setContentSize(r.getSize());
		nodeInner->setPosition(x, y + hMax);
		y += std::max(hMax + (int)nodeInner->getContentSize().height, hSprite) + c10;
		if (wMax > nodeInner->getContentSize().width)
		{
			wMax = nodeInner->getContentSize().width;
		}
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;
}

void expSkill::getuids(eSkill eski, std::vector<ulong>& uids)
{
	uids.clear();
	const auto& it3 = skills.find(eski);
	if (it3 != skills.end())
	{
		uids.push_back(it3->second.act);
		uids.push_back(it3->second.state);
	}
	const auto& it4 = acts.find(eski);
	if (it4 != acts.end())
	{
		for (const auto& u : it4->second)
		{
			uids.push_back(u);
		}
	}
	const auto& it5 = hits.find(eski);
	if (it5 != hits.end())
	{
		for (const auto& u : it5->second)
		{
			uids.push_back(u);
		}
	}
	const auto& it6 = states.find(eski);
	if (it6 != states.end())
	{
		uids.push_back(it6->second);
	}
}
