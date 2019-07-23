#include "cTag.h"
#include "cText.h"


bool cTag::init(const std::string& text, float second)
{
	if (!cSprite::init(ccu::uDesc, nullptr))
	{
		return false;
	}
	cText* t = cText::create(std::min(cc::vsSize().width - 128, _contentSize.width - cEdge * 2));
	t->setString(text);
	int w = t->getContentSize().width + cEdge * 2;
	int h = t->getContentSize().height + cEdge / 2;
	this->set9(true);
	this->setOpacity(192);

	Size size(w, std::max(24, h));
	this->setContentSize(size);
	t->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	t->setPosition(size / 2);
	this->addChild(t);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(cTag::updateOnce), second);
	return true;
}


void cTag::updateOnce(float dt)
{
	cTagManager::getInstance()->remove(this);
}




//////////////////////////////////////////////////////////////////////////
cTagManager* cTagManager::getInstance()
{
	static cTagManager* s_tag = new cTagManager();
	return s_tag;
}

bool cTagManager::add(Node* parent, const std::string& text, float second)
{
	cTag* tag = cTag::create(text, second);
	tag->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	int x = cc::vsCenter().x;
	int y;
	if (_tags.empty())
	{
		y = cc::vsY(0.1f);
	}
	else
	{
		y = _tags.back()->getPositionY() + _tags.back()->getContentSize().height + 1;
	}
	_tags.push_back(tag);
	tag->setPosition(x, y);
	parent->addChild(tag, ccu::zTag);
	return true;
}


bool cTagManager::remove(cTag* tag)
{
	tag->removeFromParent();
	const auto& it = ccc_find_it(_tags, tag);
	if (it != _tags.end())
	{
		_tags.erase(it);
	}
	return true;
}