#include "expPet.h"


static const auto& pets = txtPet::getInstance()->getTables();
bool expPet::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	_names.push_back({ "特供", eMod::ePet0, (eMod)((int)eMod::ePetSs0 - 1) });
	_names.push_back({ "神兽", eMod::ePetSs0, eMod::ePetSsEnd });
	_names.push_back({ "生肖", eMod::ePetSx0, eMod::ePetSxEnd });
	_names.push_back({ "孩子", eMod::ePetBaby0, eMod::ePetBabyEnd });
	_names.push_back({ "5-15", eMod::ePet5, eMod::ePet15end });
	_names.push_back({ "25-45", eMod::ePet25, eMod::ePet45end });
	_names.push_back({ "55-75", eMod::ePet55, eMod::ePet75end });
	_names.push_back({ "85-105", eMod::ePet85, eMod::ePet105end });
	_names.push_back({ "师傅",eMod::ePetShifu0, eMod::ePetShifuEnd });
	_names.push_back({ "NPC",eMod::ePetNpc0, eMod::ePet115end });
	_names.push_back({ "125-135",eMod::ePet125, eMod::ePet135end });
	_names.push_back({ "145-165",eMod::ePet145, eMod::ePet165end });
	_names.push_back({ "175-BOSS",eMod::ePet175, eMod::e自在天魔 });

	std::map<int, std::string>texts;
	for (const auto& name : _names)
	{
		texts.clear();
		for (eMod e = name.begin; e <= name.end; e = (eMod)((int)e + 1))
		{
			texts.insert(std::make_pair((int)e, pets.at(e).name));
		}
		initButton(name.name, texts/*, name.name == _names.back().name*/);
	}
	initButton();
	return expEasy::init(initDrag(0));
}


cNode* expPet::initDrag(int tag, int tag2 /*= cTagNone*/)
{
	if (tag2 == cTagNone)
	{
		return cNode::create();
	}

	eMod e = (eMod)tag2;
	const auto& pet = pets.at(e);
	bool iswm = (e >= eMod::ePetBaby0 && e <= eMod::ePetBabyEnd) || (e >= eMod::ePet5 && e <= eMod::ePet155end);

	cNode* node = cNode::create(), *nodeInner;
	cLabel* label;
	int y = 0;
	int kk = 0;
	forv (pet.jinjies, k)
	{
		node->addChild(label = cLabel::create(toString("形态%d", ++kk)));
		label->setPosition(0, y);
		y += label->getContentSize().height;
		node->addChild(nodeInner = createGroup(e, k));
		nodeInner->setPosition(0, y);
		y += nodeInner->getContentSize().height + c10;

		if (iswm && ((_size_ <= 2 && k == 0) || (_size_ == 4 && (k == 0 || k == 1))))
		{
			node->addChild(label = cLabel::create(toString("形态%d(唯美)", ++kk)));
			label->setPosition(0, y);
			y += label->getContentSize().height;
			cWdfs::getInstance()->pushReader(eIterType::wm);
			node->addChild(nodeInner = createGroup(e, k));
			cWdfs::getInstance()->popReader();
			nodeInner->setPosition(0, y);
			y += nodeInner->getContentSize().height + c10;
		}
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;
}


cNode* expPet::createGroup(eMod e, int jdx)
{
	const auto& as = getActGroup(true);
	const auto& names = getActNames(true);

	sMod mod;
	mod.setMod(e);
	mod.setJinjie(jdx);

	expRank r(_wButBtn);
	cLabel* label;
	cSprite* sprite;
	cNode* node = cNode::create();
	forv(as, k)
	{
		node->addChild(sprite = cSprite::create(mod.get(as.at(k))));
		r.iters({ sprite });
		sprite->play();
		node->addChild(label = cLabel::create(names.at(k), eFont::smal));
		label->setColor(s565::GREEN);
		sprite->setUserData(label);
		sprite->setTag(k);
	}
	r.iters();
	forv(as, k)
	{
		sprite = (cSprite*)node->getChildByTag(k);
		((cLabel*)sprite->getUserData())->setPosition(sprite->getPosition());
	}
	node->setContentSize(r.getSize());
	return node;
#if 0


	std::vector<sMod> mods;

	cNode* node = cNode::create();
	cSprite* sprite;
	forv(jjs, k)
	{
		const auto& jj = jjs[k];
		const auto& acts = pet.actions[jj];
		const auto& actMaps = pet.actionMaps[jj];
		forv(aMaps, i)
		{
			node->addChild(sprite = cSprite::create(actMaps.at(aMaps[i])));
			sprite->play();
			spriteMaps.at(i).push_back(sprite);
		}
		forv(as, i)
		{
			const auto& it = acts.find(as[i]);
			if (it == acts.end())
			{
				continue;
			}
			node->addChild(sprite = cSprite::create(it->second));
			sprite->play();
			sprites.at(i).push_back(sprite);
		}
	}

	expRank r;
	r.init(_wButBtn);
	cLabel* label;
	forv(spriteMaps, k)
	{
		if (spriteMaps[k].empty())
		{
			continue;
		}
		r.iters(spriteMaps[k]);
	}
	forv(sprites, k)
	{
		if (sprites[k].empty())
		{
			continue;
		}
		r.iters(sprites[k]/*, k == (sprites.size() - 1)*/);
	}
	r.iters();

	forv(spriteMaps, k)
	{
		if (spriteMaps[k].empty())
		{
			continue;
		}
		node->addChild(label = cLabel::create(getActNamesForMap().at(k), eFont::smal));
		label->setColor(s565::GREEN);
		label->setPosition(spriteMaps[k].at(0)->getPosition());
	}
	forv(sprites, k)
	{
		if (sprites[k].empty())
		{
			continue;
		}
		node->addChild(label = cLabel::create(names[k], eFont::smal));
		label->setColor(s565::GREEN);
		label->setPosition(sprites[k].at(0)->getPosition());
	}

	node->setContentSize(r.getSize());
	return node;
#endif
}

