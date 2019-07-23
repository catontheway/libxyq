#include "expNpc.h"


const auto& npcs = txtNpc::getInstance()->getTables();
bool expNpc::init()
{
	return expEasy::init("NPC") && expEasy::init(initDrag(0));
}

cNode* expNpc::initDrag(int tag, int tag2 /* = cTagNone */)
{
	float w;
	float head = 0;
	int y = 0;
	cSprite* sprite;
	cNode* node = cNode::create();
	for (const auto& n : npcs)
	{
		w = 0;
		const auto& npc = n.second;
		std::vector<eIterType> its = { eIterType::jd, eIterType::wm };
		forv(its, k)
		{
			cWdfs::getInstance()->pushReader(its.at(k));
			node->addChild(sprite = createSpriteWithName(npc.dialog, npc.name, eFont::nor, s565::GREEN));
			sprite->setPosition(w, y);
			w += sprite->getContentSize().width;
			head = std::max(head, sprite->getContentSize().height);
			cWdfs::getInstance()->popReader();
		}

		w += c10 * 3;
		std::vector<ulong> us = { npc.stand, npc.walk, npc.stand, npc.walk };
		std::vector<float> hs = { 0, 0, 0, 0 };
		forv(us, k)
		{
			if (k >= 2)
			{
				cWdfs::getInstance()->pushReader(eIterType::wm);
			}
			node->addChild(sprite = cSprite::create(npc.stand));
			if (sprite->isValid())
			{
				sprite->setPosition(w + sprite->getInfo()->kx, y + sprite->getInfo()->ky);
				hs[k] = sprite->getContentSize().height;
				if (head > hs[k])
				{
					sprite->setPositionY(sprite->getPositionY() + (head - hs[k]) / 2);
				}
				sprite->play();
				w += sprite->getInfo()->width + c10 * 2;
			}
			if (k >= 2)
			{
				cWdfs::getInstance()->popReader();
				if (k == 3)
				{
					std::sort(hs.begin(), hs.end(), [](int a, int b) {return a > b; });
					y += std::max(head, hs.front()) + c10;
				}
			}
		}
	}
	node->setContentSize(_vsWidth, y);
	node->setPositionX(c10);
	return node;
}


