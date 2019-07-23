#include "expMenpai.h"

bool expMenpai::init()
{
	return expEasy::init("ÃÅÅÉ¼¼ÄÜ") && expEasy::init(initDrag(0));
}

static const auto& icons = txtIcon::getInstance()->getTables();
cNode* expMenpai::initDrag(int tag, int tag2 /* = cTagNone */)
{
	std::map<eIcon, std::string> names;
	for (eIcon e = eIcon::eMenpai0; e <= eIcon::eMenpaiEnd; e = (eIcon)((int)e + 1))
	{
		names.insert(std::make_pair(e, getIconName(e)));
	}

	int e = 10, x = 0, y = c10, wSprite = 75, hSprite = 0, hSpriteSmall = 0, hLabel = 0, wMax = 0;
	cLabel* label;
	cSprite* sprite;
	cNode* node = cNode::create();
	for (const auto& name : names)
	{
		node->addChild(label = cLabel::create(name.second));
		label->setPosition(0, y);
		if (hLabel == 0)
		{
			hLabel = label->getContentSize().height;
		}
		y += hLabel + 5;
		x = 0;
		const auto &skills = icons.at(name.first);
		for (const auto& ski : skills)
		{
			node->addChild(sprite = createSpriteWithName(ski.second.big, ski.second.name, s565::GREEN));
			if (hSprite == 0)
			{
				hSprite = sprite->getContentSize().height;
			}
			sprite->setPosition(wSprite * x, y);
			if (wMax < wSprite * (++x))
			{
				wMax = wSprite * x;
			}
		}
		y += hSprite + 5;
		x = 0;
		for (const auto& ski : skills)
		{
			node->addChild(sprite = cSprite::create(ski.second.small));
			if (hSpriteSmall == 0)
			{
				hSpriteSmall = sprite->getContentSize().height;
			}
			sprite->setPosition(wSprite * x, y);
			++x;
		}
		y += hSpriteSmall + e + 20;
	}
	node->setContentSize(wMax, y + hSprite + e);
	node->setPositionX(_btnw + c10 + (_wButBtn - wMax) / 2);
	return node;
}
