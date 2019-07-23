#include "uiChannel.h"

bool uiChannelInner::init(eFont eFnt)
{
	if (!cLayer::cNodeInner::init())
	{
		return false;
	}
	_eFont = eFnt;
	return true;
}

void uiChannelInner::setRectWorld()
{
	cNode::setRectWorld();
	int h = _parent->getContentSize().height;
	if (h > cc::vsSize().height * 0.9f)
	{
		return;
	}
	int y;
	cText* t;
	forv(_texts, k)
	{
		t = _texts[k];
		y = t->getPositionY() + _position.y;
		t->setVisible(y >= 0 && y + t->getContentSize().height <= h);
	}
}


void uiChannelInner::add(eCanvas eCanv, eChannel e, const std::string& name, const std::string& text)
{
	auto t = cText::create(_eFont, _contentSize.width);
	t->setCanvas(eCanv);
	t->setString(e, name, text);
	static const int inv = 0;
	int h = t->getContentSize().height + inv;
	t->setPosition(0, _contentSize.height + inv);
	this->setPositionY(std::min(0.0f, _parent->getContentSize().height - _contentSize.height - h));
	this->setContentSize(_contentSize.width, _contentSize.height + h);
	this->addChild(t);
	_texts.push_back(t);
}


//////////////////////////////////////////////////////////////////////////
cSprite* uiChannel::createSprite()
{
	return nullptr;
}


bool uiChannel::init(eFont eFnt, eCanvas eCanv)
{
	_eCanv = eCanv;
	_eFont = eFnt;
	return cLayer::init(nullptr);
	return cLayer::init([eFnt]()
	{
		return uiChannelInner::create(eFnt);
	});
}


void uiChannel::add(eChannel e, const std::string& name, const std::string& text)
{
	Size size = _nodeInner->getContentSize();
	auto t = cText::create(_eFont, size.width);
	t->setCanvas(_eCanv);
	t->setString(e, name, text);
	static const int inv = 0;
	int h = t->getContentSize().height + inv;
	t->setPosition(0, size.height + inv);
	_nodeInner->setPositionY(std::min(0.0f, _contentSize.height - size.height - h));
	_nodeInner->setContentSize(size.width, size.height + h);
	_nodeInner->addChild(t);
	return;
	((uiChannelInner*)getInner())->add(_eCanv, e, name, text);
}

