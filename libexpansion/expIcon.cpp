#include "expIcon.h"

bool expIcon::init()
{
	if (!expEasy::init())
	{
		return false;
	}

	for (eIcon e = eIcon::药品y; e <= eIcon::四家s; e = (eIcon)((int)e + 1))
	{
		initButton(getIconName(e))->setTag((int)e)/*, e == (eIcon)((int)eIcon::四家s - 1)*/;
	}
	for (eIcon e = eIcon::兽决s; e <= eIcon::卡片k; e = (eIcon)((int)e + 1))
	{
		initButton(getIconName(e))->setTag((int)e)/*, e == (eIcon)((int)eIcon::四家s - 1)*/;
	}
	initButton();

	// 	兽决s,
	// 	符石f,
	// 	追加z,
	// 	卡片k,

	return expEasy::init(initDrag((int)eIcon::药品y));
}

static const auto& icons = txtIcon::getInstance()->getTables();
const auto& jiajus = txtJiaju::getInstance()->getTables();
cNode* expIcon::initDrag(int tag, int tag2 /* = cTagNone */)
{
	eIcon e = (eIcon)tag;
	const auto& table = icons.at(e);
	int x = 0, wMin = 0;
	cSprite* sprite;
	cText* text;
	cNode* node = cNode::create();
	std::vector<cSprite*> sprites;
	for (int k = 0, size = table.size(); k < size; ++k)
	{
		const auto& icon = table.at(k);
		sprite = createSpriteWithName(icon.small, toString("%d.", k) +  icon.name);
		node->addChild(sprite);
		sprites.push_back(sprite);
		wMin = std::max(sprite->getContentSize().width, sprite->getChildren().at(0)->getContentSize().width);
		x = std::max(x, wMin);
	}
	x += c10;
	int w = _wButBtn - c10 * 2 - x;
	cNode* nodeInner, *nodejj;
	int y = 0, hMax;
	expRank r, r2;
	for (int k = 0, size = table.size(); k < size; ++k)
	{
		const auto& icon = table.at(k);
		node->addChild(nodeInner = cNode::create());
		nodeInner->addChild(sprite = cSprite::create(icon.big));
		nodeInner->addChild(text = cText::create(w - sprite->getContentSize().width));
		text->setString(icon.desc);
		r.init(w);
		r.iter(text);
		r.iter(sprite, true);

		nodeInner->setContentSize(r.getSize());
		wMin = nodeInner->getContentSize().width;
		hMax = nodeInner->getContentSize().height;
		nodeInner->setPosition(x, y);
		text->setPositionY(hMax * 2 / 3);
		sprites[k]->setPositionY(y + hMax / 2);
		hMax = std::max(sprites[k]->getContentSize().height, nodeInner->getContentSize().height);

		if ((tag >= (int)eIcon::一家y && tag <= (int)eIcon::四家s))
		{
			const auto& jj = jiajus.at(e).at(k);
			if (!jj.uids.empty())
			{
				node->addChild(nodejj = cNode::create());
				//int i = 0;
				r2.init(_wButBtn);
				for (const auto& u : jj.uids)
				{
					sprite = cSprite::create(u);
					nodejj->addChild(sprite);
					r2.iters({ sprite }/*, (++i) == jj.uids.size()*/);
				}
				r2.iters();
				nodejj->setContentSize(r2.getSize());

				if (x + wMin + nodejj->getContentSize().width < _wButBtn)
				{
					nodejj->setPosition(x + wMin + c10, y);
					hMax = std::max(hMax, (int)nodejj->getContentSize().height);
				}
				else
				{
					nodejj->setPosition(x, y + hMax + c10);
					hMax += nodejj->getContentSize().height + c10;
				}
			}

		}
		y += hMax + c10;
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;
}

bool expIconWeapon::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	for (eIcon e = eIcon::eWeapon0; e <= eIcon::eWeaponEnd; e = (eIcon)((int)e + 1))
	{
		initButton(getIconName(e))->setTag((int)e);
	}

	return expEasy::init(initDrag((int)eIcon::eWeapon0));
}



bool expIconEquip::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	for (eIcon e = eIcon::equipArmor0; e <= eIcon::equipBabyEnd; e = (eIcon)((int)e + 1))
	{
		initButton(getIconName(e))->setTag((int)e);
	}

	return expEasy::init(initDrag((int)eIcon::equipArmor0));
}




// cNode* uiIcon::initJiaju(int tag, int k)
// {
// 	if (tag < (int)eIcon::一家y || tag >(int)eIcon::四家s)
// 	{
// 		return uiEasy::initJiaju(tag, k);
// 	}
// 
// 	const auto& jj = jiajus.at((eIcon)tag).at(k);
// 	txtEasy::sTable table;
// 	int n = -1;
// 	for (const auto& u : jj.uids)
// 	{
// 		table.insert(std::make_pair(++n, u));
// 	}
// 	return uiEasy::initEasy(table);
// }
