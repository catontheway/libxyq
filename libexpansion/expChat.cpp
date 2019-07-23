#include "expChat.h"

static const auto& txt = txtEasy::getInstance();
bool expChat::init()
{
	if (!expEasy::init("±íÇé°ü"))
	{
		return false;
	}

	const auto& chats = txt->getChats();
	int size = chats.size();
	const int w60 = 60;
	const int h80 = 80;
	const int c10 = (cc::vsSize().width - (640 - w60 * 10)) / (w60 * 10) * 10;
	cSprite* sprite;
	cLabel* label;
	cNode* node = cNode::create();
	for (int k = 0; k < size; ++k)
	{
		node->addChild(sprite = cSprite::create(chats.at(k)));
		sprite->play();
		sprite->setPosition(k % c10 * w60 + w60 / 4, (k / c10 + 1) * h80);
		node->addChild(label = cLabel::create(toString("#%d", k)));
		label->setPosition(sprite->getPosition());
		label->setColor(s565::ORANGE);
	}
	node->setContentSize(w60 * c10, (size / c10 + 1) * h80);
	node->setPositionX(c10);
	return expEasy::init(node);
}
