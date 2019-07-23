#include "cDesc.h"
#include "cSprite.h"
#include "cLabel.h"
#include "cText.h"

//////////////////////////////////////////////////////////////////////////
void cDesc::setDesc(const std::string& desc, const s565& color /* = s565::WHITE */)
{
	_descs.clear();
	_descs.push(desc, color);
}

void cDesc::showDesc(bool show)
{
	auto sprite = ccu::getSpriteDesc();
	if (sprite == nullptr)
	{
		return;
	}
	if (show && _descs.isValid())
	{
		toSpriteDesc(sprite, _descs);
		sprite->setVisible(true);
	}
	else
	{
		sprite->setVisible(false);
	}
}


void cDesc::toSpriteDesc(cSprite* sprite, const sDescs& _descs)
{
	auto uhead = _descs.uhead;
	const auto& name = _descs.name;
	const auto& descs = _descs.descs;
	sprite->removeAllChildren();

	static int inv;
	inv = (uhead == 0) ? 5 : 20;
	static int w; w = inv;
	static int h; h = inv;
	if (uhead != cSp::c0)
	{
		cSprite* sprite2 = cSprite::create(uhead);
		sprite2->setPosition(inv, inv);

		w += sprite2->getPositionX() + sprite2->getContentSize().width;
		w = std::max(w, sprite2->getInfo()->kx);
		h += sprite2->getPositionY() + sprite2->getContentSize().height;
		sprite->addChild(sprite2);
	}

	static int wmax; wmax = 0;
	static int hmax; hmax = inv;
	cLabel* label = cLabel::create(name, eFont::big);
	label->setColor(s565::YELLOW);
	wmax = std::max(wmax, (int)label->getContentSize().width);
	label->setPosition(w, hmax);
	hmax += label->getContentSize().height + 3;
	sprite->addChild(label);
	cText* t;
	forv(descs, k)
	{
		auto& d = descs[k];
		sprite->addChild(t = cText::create(_descs.wMax));
		t->setColor(d.color);
		t->setString(d.text);
		if (wmax < t->getContentSize().width)
		{
			wmax = t->getContentSize().width;
		}
		t->setPosition(w, hmax);
		hmax += t->getContentSize().height + 3;
	}

	wmax += w + inv;
	h = std::max(h, hmax) + inv;
	sprite->setContentSize(w = wmax, h);
	wmax = cc::vsSize().width;
	hmax = cc::vsSize().height;

	if (uhead != 0)
	{
		inv = 0x10;
	}
	static Vec2 v; v = cInput::getInstance()->getMouse();
	if (uhead == cSp::c0 && name.empty())
	{
		sprite->setPosition(v + Vec2(-inv, -36));
	}
	else
	{
		sprite->setPosition(v + Vec2(30, 0));
	}

	static int x; x = sprite->getPositionX();
	static int y; y = sprite->getPositionY();
	if (x + w > wmax)
	{
		if (y + h > hmax)
		{
			sprite->setPosition(v - sprite->getContentSize() - Vec2(inv, inv));
			if (sprite->getPositionY() < 0)
			{
				sprite->setPositionY(0);
			}
		}
		else
		{
			sprite->setPositionX(v.x - sprite->getContentSize().width - inv);
		}
	}
	else
	{
		if (y + h > hmax)
		{
			sprite->setPositionY(v.y - sprite->getContentSize().height - inv);
			if (sprite->getPositionY() < 0)
			{
				sprite->setPositionY(0);
			}
		}
	}
}

