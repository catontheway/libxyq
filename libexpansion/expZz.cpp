#include "expZz.h"

bool expZz::init(bool iswm /* = false */)
{
	if (!expEasy::init())
	{
		return false;
	}
	_iswm = iswm;
	_names.push_back({ "特供", eMod::ePet0, (eMod)((int)eMod::ePetSs0 - 1) });
	_names.push_back({ "神兽", eMod::ePetSs0, eMod::ePetSsEnd });
	_names.push_back({ "生肖", eMod::ePetSx0, eMod::ePetSxEnd });
	_names.push_back({ "孩子", eMod::ePetBaby0, eMod::ePetBabyEnd });
	_names.push_back({ "5", eMod::ePet5, eMod::ePet5end });
	_names.push_back({ "15", eMod::ePet15, eMod::ePet15end });
	_names.push_back({ "25", eMod::ePet25, eMod::ePet25end});
	_names.push_back({ "35", eMod::ePet35, eMod::ePet35end});
	_names.push_back({ "45", eMod::ePet45, eMod::ePet45end});
	_names.push_back({ "55", eMod::ePet55, eMod::ePet55end});
	_names.push_back({ "65", eMod::ePet65, eMod::ePet65end});
	_names.push_back({ "75", eMod::ePet75, eMod::ePet75end});
	_names.push_back({ "85", eMod::ePet85, eMod::ePet85end});
	_names.push_back({ "95", eMod::ePet95, eMod::ePet95end});
	_names.push_back({ "105",eMod::ePet105, eMod::ePet105end });
	_names.push_back({ "师傅",eMod::ePetShifu0, eMod::ePetShifuEnd });
	_names.push_back({ "NPC",eMod::ePetNpc0, eMod::ePetNpcEnd });
	_names.push_back({ "活动",(eMod)((int)eMod::ePetNpcEnd + 1), eMod::ePet115end });
	_names.push_back({ "125",eMod::ePet125, eMod::ePet125end });
	_names.push_back({ "135",eMod::ePet135, eMod::ePet135end });
	_names.push_back({ "145",eMod::ePet145, eMod::ePet145end });
	_names.push_back({ "155",eMod::ePet155, eMod::ePet155end });
	_names.push_back({ "165",eMod::ePet165, eMod::ePet165end });
	_names.push_back({ "175",eMod::ePet175, eMod::ePet175end });
	for (const auto& name : _names)
	{
		initButton(name.name/*, name.name == _names.back().name*/);
	}
	initButton();
	return expEasy::init(initDrag(0));
}

cNode* expZz::createHead(const txtAction::sAction& act, const std::string& name /* = "" */)
{
	if (_iswm)
	{
		cWdfs::getInstance()->pushReader(eIterType::wm);
	}
	cNode* node = cNode::create();
	cSprite* sprite, *spriteSmall, *spriteBig;
	if (name.empty())
	{
		node->addChild(sprite = cSprite::create(act.at(eAct::Dialog)));
	}
	else
	{
		node->addChild(sprite = expEasy::createSpriteWithName(act.at(eAct::Dialog), name, eFont::nor, s565::GREEN));
	}
	int x = sprite->getContentSize().width;
	int y = sprite->getContentSize().height;
	node->addChild(spriteBig = cSprite::create(act.at(eAct::Big)));
	spriteBig->setPosition(x + 5, 0);
	int x2 = spriteBig->getContentSize().width;
	int y2 = spriteBig->getContentSize().height;
	node->addChild(spriteSmall = cSprite::create(act.at(eAct::Small)));
	spriteSmall->setPosition(x + 5, y2 += 5);
	y2 += spriteSmall->getContentSize().height;
	x += x2;
	y = std::max(y, y2);
	node->setContentSize(x, y);
	spriteBig->setPositionY(spriteBig->getPositionY() + y - y2);
	spriteSmall->setPositionY(spriteSmall->getPositionY() + y - y2);

	if (_iswm)
	{
		cWdfs::getInstance()->popReader();
	}
	return node;
}


static const auto& pets = txtPet::getInstance()->getTables();
const auto& zzs = txtZz::getInstance()->getTables();
static const auto& skills = txtIcon::getInstance()->getTables().at(eIcon::技能j);
cNode* expZz::initDrag(int tag, int tag2 /*= cTagNone*/)
{
	eMod begin = _names.at(tag).begin, end = _names.at(tag).end;

	cSprite* sprite;
	cNode* node = cNode::create(), *nodeInner, *node2, *node3;
	cText* text;
	expRank r;
	int y = 0;
	for (eMod e = begin; e <= end; e = (eMod)((int)e + 1))
	{
		const auto& pet = pets.at(e);
		node->addChild(nodeInner = cNode::create());
		if (pet.heads.empty())
		{
			cLabel* lable = cLabel::create(pet.name);
			lable->setColor(s565::GREEN);
			nodeInner->addChild(lable);
			r.init(_wButBtn);
			r.iter(lable);
		}
		else 
		{
			// node2 头像组
			nodeInner->addChild(node2 = cNode::create());
			node2->addChild(node3 = createHead(pet.heads.at(0), pet.name));
			r.init(_wButBtn);
			r.iter(node3);
			if (!_iswm && pet.heads.size() >= 2)
			{
				node2->addChild(node3 = createHead(pet.heads.at(1)));
				r.iter(node3);
			}
			r.iter();
			node2->setContentSize(r.getSize());

			r.init(_wButBtn);
			r.iter(node2);
		}

		const auto& z = zzs.at(e);
		if (!_iswm && z.takelv != 115)
		{
			nodeInner->addChild(text = cText::create());
			text->setString(toString("携带等级: %d\n攻击资质: %d\n防御资质: %d\n体力资质: %d\n法力资质: %d\n速度资质: %d\n躲避资质: %d\n成长: %0.2f",
				z.takelv, z.atk, z.def, z.hp, z.mp, z.speed, z.evoid, z.grow * 0.01f));
			r.iter(text);

			nodeInner->addChild(node2 = cNode::create());
			forv(z.skills, k)
			{
				node2->addChild(sprite = cSprite::create(skills.at((int)z.skills[k]).big));
				sprite->setPosition(k % 4 * 44, k / 4 * 44);
			}
			node2->setContentSize(176, (z.skills.size() / 4 + 1) * 44);
			r.iter(node2);

			nodeInner->addChild(node2 = cNode::create());
			forv(z.skills, k)
			{
				node2->addChild(sprite = cSprite::create(skills.at((int)z.skills[k]).small));
				sprite->setPosition(k % 4 * 32, k / 4 * 32);
			}
			node2->setContentSize(128, (z.skills.size() / 4 + 1) * 32);
			r.iter(node2);
		}

		r.iter();

		nodeInner->setContentSize(r.getSize());
		nodeInner->setPosition(0, y);
		y += nodeInner->getContentSize().height + c10;
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;
}
