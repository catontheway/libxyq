#include "expRole.h"
#include "expZz.h"
static const auto& roles = txtRole::getInstance()->getTables();
static const auto& weapons = txtWeapon::getInstance();
bool expRole::init()
{
	if (!expEasy::init())
	{
		return false;
	}

	std::map<int, std::string> texts;
	for (eMod e = eMod::eJueSe0; e <= eMod::eJueSeEnd; e = (eMod)((int)e + 1))
	{
		texts.clear();
		texts.insert(std::make_pair(cHeadBody, "Í·Ïñ"));
		const auto& list = weapons->getWeaponLists().at(e);
		for (const auto& li : list)
		{
			texts.insert(std::make_pair((int)li, getIconName(li)));
			if (e >= eMod::eJueSeIter0 && e <= eMod::eJueSeIterEnd)
			{
				texts.insert(std::make_pair(((int)li) + cIter, cc::replace(getIconName(li), " ", "") + "(µü)"));
			}
			if (e >= eMod::eJueSeWm0 && e <= eMod::eJueSeWmEnd)
			{
				texts.insert(std::make_pair(((int)li) + cWm, cc::replace(getIconName(li), " ", "") + "(Î¨)"));
			}
			
		}
		initButton(roles.at(e).name, texts)->setTag((int)e);
	}
	initButton();
	return expEasy::init(initDrag((int)eMod::eJueSe0, cHeadBody));
}


cNode* expRole::initDrag(int tag, int tag2 /*= cTagNone*/)
{
	if (tag2 == cTagNone)
	{
		return cNode::create();
	}

	eMod e = (eMod)tag;
	const auto& role = roles.at(e);
	if (tag2 == cHeadBody)
	{
		cNode* node = cNode::create();
		cNode* node1 = createHeadFaceBodies(role);
		node->addChild(node1);
		cWdfs::getInstance()->pushReader(eIterType::wm);
		cNode* node2 = createHeadFaceBodies(role);
		cWdfs::getInstance()->popReader();
		node->addChild(node2);
		node2->setPositionY(node1->getContentSize().height + c10);
		node->setContentSize(std::max(node1->getContentSize().width, node2->getContentSize().height), node2->getPositionY() + node2->getContentSize().height + c10);
		return node;
	}

	bool isWm = tag2 >= cWm;
	bool isIter = !isWm && tag2 >= cIter;
	if (isWm)
	{
		tag2 -= cWm;
		cWdfs::getInstance()->pushReader(eIterType::wm);
	}
	else if (isIter)
	{
		tag2 -= cIter;
		cWdfs::getInstance()->pushReader(eIterType::iter);
	}

	eIcon eWeapon = (eIcon)tag2;
	sMod mod;
	mod.setMod(e);
	cLabel* label;
	cNode* node = cNode::create(), *nodeInner;
	std::string name;
	static std::vector<int> wids = { 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 28, };
	const auto& wNames = txtIcon::getInstance()->getTables().at(eWeapon);
	static auto& as = getActGroup(false);
	static auto& names = getActNames(false);
	int y = 0;
	for (int k = 0, wid; k < 11; ++k)
	{
		wid = wids.at(k);
		mod.setWeapon(eWeapon, wid);
		name = wNames.at(wid).name;
		if (k <= 2)
		{
			name += ", " + wNames.at(wid + 1).name + ", " + wNames.at(wid + 2).name;
		}
		node->addChild(label = cLabel::create(name));
		label->setPosition(0, y);
		y += label->getContentSize().height;
		node->addChild(nodeInner = createGroup(mod));
		nodeInner->setPosition(0, y);
		y += nodeInner->getContentSize().height + c10;
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);

	if (isIter || isWm)
	{
		cWdfs::getInstance()->popReader();
	}
	return node;

#if 0
	const auto& wAct2s = weapons->getTables().at(eWeapon);
	const txtWeapon::sWeapon& weapon = wAct2s.at((wAct2s.at(0).master == e) ? 0 : 1);
	const auto& wNames = txtIcon::getInstance()->getTables().at(eWeapon);
	cNode* node = cNode::create(), *nodeInner;
	cLabel* label;
	std::string name;
	int y = 0, idx;
	for(int k = 0; k < 11; ++k)
	{
		/*const*/ auto/*&*/ wActs = weapon.actions.at(k);
		const auto& wActMaps = weapon.actionMaps.at(k);
		idx = (eWeapon == eIcon::¹­åóg && (k == 3 || k == 7)) ? 2 : weapon.masterIdx;
		/*const*/ auto/*&*/ rActs = role.actions.at(idx);
		const auto& rActMaps = role.actionMaps.at(idx);
		if ((isIter || isWm) && e == eMod::eJueSe»¢Í·¹Ö)
		{
			if (eWeapon == eIcon::¸«îáf)
			{
				wActs.at(eAct::Dead) = txtAction::getWeaponTigerDies().at(k);
			}
			else if(eWeapon == eIcon::´¸×Óc)
			{
				const auto& w2s = weapons->getTables().at(eIcon::¸«îáf);
				idx = (w2s.at(0).master == e) ? 0 : 1;
				rActs.at(eAct::Dead) = role.actions.at(idx).at(eAct::Dead);
			}
		}
		name.clear();
		for (const auto& n : wNames)
		{
			if (txtIcon::getWeaponIdxById(n.first) == k)
			{
				name += n.second.name + " ";
			}
		}
		node->addChild(label = cLabel::create(name));
		label->setPosition(0, y);
		y += label->getContentSize().height;
		node->addChild(nodeInner = createGroup(rActs, rActMaps, wActs, wActMaps));
		nodeInner->setPosition(0, y);
		y += nodeInner->getContentSize().height + c10;
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);

	if (isIter || isWm)
	{
		cWdfs::getInstance()->popReader();
	}
	return node;
#endif
}


cNode* expRole::createFace(const txtRole::sRole& role)
{
	const auto& heads = role.heads;
	const auto& faces = role.faces;
	cNode* node = cNode::create();
	cNode* nodeBig1 = cNode::create();
	cNode* nodeBig2 = cNode::create();
	cNode* nodeBig3 = cNode::create();
	cNode* nodeSmall1 = cNode::create();
	cNode* nodeSmall2 = cNode::create();
	cNode* nodeSmall3 = cNode::create();
	node->addChild(nodeBig1);
	node->addChild(nodeBig2);
	node->addChild(nodeBig3);
	node->addChild(nodeSmall1);
	node->addChild(nodeSmall2);
	node->addChild(nodeSmall3);
	cSprite* sprite;
	expRank r;
	r.init(_wButBtn);
#define  ccc_rank_iter r.iters({sprite})
#define  ccc_rank_iter_end r.iters()
	nodeBig1->addChild(sprite = cSprite::create(heads[0].at(eAct::Big)));
	ccc_rank_iter;
	nodeBig1->addChild(sprite = cSprite::create(heads[1].at(eAct::Big)));
	ccc_rank_iter;
	nodeBig1->addChild(sprite = cSprite::create(heads[2].at(eAct::Big)));
	ccc_rank_iter;
	ccc_rank_iter_end;
	nodeBig1->setContentSize(r.getSize());

	r.init(_wButBtn);
	nodeBig2->addChild(sprite = cSprite::create(faces[0].at(eAct::HappyBig)));
	ccc_rank_iter;
	nodeBig2->addChild(sprite = cSprite::create(faces[0].at(eAct::SadBig)));
	ccc_rank_iter;
	nodeBig2->addChild(sprite = cSprite::create(faces[0].at(eAct::ProudBig)));
	ccc_rank_iter;
	ccc_rank_iter_end;
	nodeBig2->setContentSize(r.getSize());

	r.init(_wButBtn);
	nodeBig3->addChild(sprite = cSprite::create(faces[1].at(eAct::HappyBig)));
	ccc_rank_iter;
	nodeBig3->addChild(sprite = cSprite::create(faces[1].at(eAct::SadBig)));
	ccc_rank_iter;
	nodeBig3->addChild(sprite = cSprite::create(faces[1].at(eAct::ProudBig)));
	ccc_rank_iter;
	ccc_rank_iter_end;
	nodeBig3->setContentSize(r.getSize());

	r.init(_wButBtn);
	nodeSmall1->addChild(sprite = cSprite::create(faces[0].at(eAct::Amigo)));
	ccc_rank_iter;
	nodeSmall1->addChild(sprite = cSprite::create(faces[0].at(eAct::HappySmall)));
	ccc_rank_iter;
	nodeSmall1->addChild(sprite = cSprite::create(faces[0].at(eAct::SadSmall)));
	ccc_rank_iter;
	nodeSmall1->addChild(sprite = cSprite::create(faces[0].at(eAct::ProudSmall)));
	ccc_rank_iter;
	ccc_rank_iter_end;
	nodeSmall1->setContentSize(r.getSize());

	r.init(_wButBtn);
	nodeSmall2->addChild(sprite = cSprite::create(faces[1].at(eAct::Amigo)));
	ccc_rank_iter;
	nodeSmall2->addChild(sprite = cSprite::create(faces[1].at(eAct::HappySmall)));
	ccc_rank_iter;
	nodeSmall2->addChild(sprite = cSprite::create(faces[1].at(eAct::SadSmall)));
	ccc_rank_iter;
	nodeSmall2->addChild(sprite = cSprite::create(faces[1].at(eAct::ProudSmall)));
	ccc_rank_iter;
	ccc_rank_iter_end;
	nodeSmall2->setContentSize(r.getSize());

	r.init(_wButBtn);
	nodeSmall3->addChild(sprite = cSprite::create(heads[0].at(eAct::Small)));
	ccc_rank_iter;
	nodeSmall3->addChild(sprite = cSprite::create(heads[1].at(eAct::Small)));
	ccc_rank_iter;
	nodeSmall3->addChild(sprite = cSprite::create(heads[2].at(eAct::Small)));
	ccc_rank_iter;
	ccc_rank_iter_end;
	nodeSmall3->setContentSize(r.getSize());

	float w = nodeBig1->getContentSize().width;
	w = std::max(w, nodeBig2->getContentSize().width);
	w = std::max(w, nodeBig3->getContentSize().width);
	w = std::max(w, nodeSmall1->getContentSize().width);
	w = std::max(w, nodeSmall2->getContentSize().width);

	nodeBig2->setPositionY(nodeBig1->getContentSize().height + c10);
	nodeBig3->setPositionY(nodeBig2->getPositionY() + nodeBig2->getContentSize().height + c10);
	nodeSmall1->setPositionY(nodeBig3->getPositionY() + nodeBig3->getContentSize().height + c10);
	nodeSmall2->setPositionY(nodeSmall1->getPositionY() + nodeSmall1->getContentSize().height + c10);
	nodeSmall3->setPositionY(nodeSmall2->getPositionY() + nodeSmall2->getContentSize().height + c10);
	node->setContentSize(w, nodeSmall3->getPositionY() + nodeSmall3->getContentSize().height + c10);
	return node;
#undef ccc_rank_iter
#undef ccc_rank_iter_end
}

cNode* expRole::createBodies(const txtAction::sAction& bodies)
{
	cNode* node = cNode::create();
	cNode* node1 = cNode::create();
	cNode* node2 = cNode::create();
	node->addChild(node1);
	node->addChild(node2);
	cSprite* sprite;
	expRank r;
	r.init(_wButBtn);
	node1->addChild(sprite = cSprite::create(bodies.at(eAct::BodyBow)));
	if (sprite->isValid())
	{
		sprite->play();
		r.iters({ sprite });
	}
	node1->addChild(sprite = cSprite::create(bodies.at(eAct::BodyCry)));
	if (sprite->isValid())
	{
		sprite->play();
		r.iters({ sprite });
	}
	node1->addChild(sprite = cSprite::create(bodies.at(eAct::BodyDance)));
	if (sprite->isValid())
	{
		sprite->play();
		r.iters({ sprite });
	}
	r.iters();
	node1->setContentSize(r.getSize());

	r.init(_wButBtn);
	node2->addChild(sprite = cSprite::create(bodies.at(eAct::BodyGreet)));
	if (sprite->isValid())
	{
		sprite->play();
		r.iters({ sprite });
	}
	node2->addChild(sprite = cSprite::create(bodies.at(eAct::BodySit)));
	if (sprite->isValid())
	{
		sprite->play();
		r.iters({ sprite });
	}
	node2->addChild(sprite = cSprite::create(bodies.at(eAct::BodyAngry)));
	if (sprite->isValid())
	{
		sprite->play();
		r.iters({ sprite });
	}
	r.iters();
	node2->setContentSize(r.getSize());

	node2->setPositionY(node1->getContentSize().height + c10);
	node->setContentSize(std::max(node1->getContentSize().width, node2->getContentSize().width), node2->getPositionY() + node2->getContentSize().height + c10);
	return node;
}

cNode* expRole::createHeadFaceBodies(const txtRole::sRole& role)
{
	cNode* node = cNode::create();
	cNode* nodeDialog = cNode::create();
	cSprite* sprite;
	node->addChild(nodeDialog);
	expRank r;
	r.init(_wButBtn);
	forv(role.heads, k)
	{
		nodeDialog->addChild(sprite = cSprite::create(role.heads[k].at(eAct::Dialog)));
		r.iter(sprite);
	}
	r.iter();
	nodeDialog->setContentSize(r.getSize());

	r.init(_wButBtn);
	r.iter(nodeDialog);
	cNode* nodeFace = createFace(role);
	node->addChild(nodeFace);
	r.iter(nodeFace);
	// ×ÊÔ´Î´ÊÕÂ¼
// 	cNode* nodeBodies = createBodies(role.bodies);
// 	node->addChild(nodeBodies);
// 	r.iter(nodeBodies);
	r.iter();
	node->setContentSize(r.getSize());
	node->setPositionX(_btnw + c10);
	return node;
}

cNode* expRole::createGroup(const txtAction::sAction& rActs, const txtAction::sAction& rActMaps, const txtAction::sAction& wActs, const txtAction::sAction& wActMaps)
{
	const auto& aMaps = getActGroup/*ForMap*/(false);
	const auto& as = getActGroup(false);
	const auto& names = getActNames(false);
	std::vector<std::vector<cSprite*>> sprites(as.size()), spriteMaps(aMaps.size());

	cNode* node = cNode::create();
	cSprite* sprite;
	forv(aMaps, i)
	{
		node->addChild(sprite = cSprite::create(rActMaps.at(aMaps[i])));
		sprite->play();
		spriteMaps.at(i).push_back(sprite);

		node->addChild(sprite = cSprite::create(wActMaps.at(aMaps[i])));
		sprite->play();
		spriteMaps.at(i).push_back(sprite);
	}
	forv(as, i)
	{
		if (as[i] == eAct::Atk2)
		{
			continue;
		}
		node->addChild(sprite = cSprite::create(rActs.at(as[i])));
		sprite->play();
		sprites.at(i).push_back(sprite);

		node->addChild(sprite = cSprite::create(wActs.at(as[i])));
		sprite->play();
		sprites.at(i).push_back(sprite);
	}

	expRank r;
	r.init(_wButBtn);
	cLabel* label;
	forv(spriteMaps, k)
	{
		r.iters(spriteMaps[k]);
	}
	forv(sprites, k)
	{
		r.iters(sprites[k]/*, k == (sprites.size() - 1)*/);
	}
	r.iters();

	forv(spriteMaps, k)
	{
		node->addChild(label = cLabel::create((k == 0) ? "Õ¾" : "×ß", eFont::smal));
		label->setColor(s565::GREEN);
		label->setPosition(spriteMaps[k].at(0)->getPosition());
	}
	forv(sprites, k)
	{
		if (as[k] == eAct::Atk2)
		{
			continue;
		}
		node->addChild(label = cLabel::create(names[k], eFont::smal));
		label->setColor(s565::GREEN);
		label->setPosition(sprites[k].at(0)->getPosition());
	}

	node->setContentSize(r.getSize());
	return node;
}

cNode* expRole::createGroup(const sMod& mod)
{
	const auto& as = getActGroup(false);
	const auto& names = getActNames(false);

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
}

