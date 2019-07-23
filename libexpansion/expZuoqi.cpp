#include "expZuoqi.h"

const auto& zuoqis = txtZuoqi::getInstance()->getTables();
const auto& roles = txtRole::getInstance()->getTables();
const auto& zhuangshis = txtZuoqi::getInstance()->getZhuangshis();
bool expZuoqi::init(bool iswm /* = false */)
{
	if (!expEasy::init())
	{
		return false;
	}
	_iswm = iswm;
	std::map<int, std::string> texts;
	for (const auto& z : zuoqis)
	{
		const auto& zq = z.second;
		texts.clear();
		if (!_iswm)
		{
			for (const auto& mst : zq.masters)
			{
				texts.insert(std::make_pair((int)mst.first, roles.at(mst.first).name));
			}
		}
		initButton(zq.name, texts/*, (++k) == zuoqis.size()*/);
	}
	initButton();

	return expEasy::init(initDrag((int)eZuoqi::eZuoqi0));                                                                                                                                                                                                                                                                                                                                                                               
}


static const auto& icon = txtIcon::getInstance()->getTables().at(eIcon::×øÊÎz);
cNode* expZuoqi::initDrag(int tag, int tag2 /* = cTagNone */)
{
	std::vector<sSps> sps1(4), sps2(4);
	std::vector<int> zsids = { sMod::c_1, tag * 3, tag * 3 + 1, tag * 3 + 2 };
	std::vector<std::string> names;
	names.push_back("");
	sSp sp;
	if (tag2 == cTagNone)
	{
		const auto& zuoqi = zuoqis.at((eZuoqi)tag);
		forv(sps1, k)
		{
			sp.uid = zuoqi.stand;
			sps1.at(k).push_back(sp);
			if (k > 0)
			{
				const auto& zs = zhuangshis.at(zsids.at(k));
				names.push_back(zs.name);
				sp.uid = zs.stand;
				sps1.at(k).push_back(sp);
			}
			sp.uid = zuoqi.walk;
			sps2.at(k).push_back(sp);
			if (k > 0)
			{
				const auto& zs = zhuangshis.at(zsids.at(k));
				sp.uid = zs.walk;
				sps2.at(k).push_back(sp);
			}
		}
	}
	else
	{
		sMod mod;
		mod.setMod((eMod)tag2);
		mod.setZuoqi((eZuoqi)tag);
		mod.setRole(sMod::eRole::zq);
		forv(sps1, k)
		{
			if (k > 0)
			{
				const auto& zs = zhuangshis.at(zsids.at(k));
				names.push_back(zs.name);
			}
			mod.setZs(zsids.at(k));
			sps1.at(k) = mod.get(eAct::Stand);
			sps2.at(k) = mod.get(eAct::Walk);
		}
	}

	cNode* node = cNode::create();
	cNode* node2;
	cLabel* label;
	cSprite* sprite;
	int y = 0;
	expRank r(_wButBtn);
	if (_iswm)
	{
		cWdfs::getInstance()->pushReader(eIterType::wm);
	}
	forv(sps1, k)
	{
		node->addChild(label = cLabel::create(names[k]));
		label->setPosition(80, y);
		y += label->getContentSize().height + c10;
		node->addChild(node2 = cNode::create());
		node2->setPosition(0, y);
		r.init(_wButBtn);
		node2->addChild(sprite = cSprite::create(sps1.at(k)));
		sprite->play();
		r.iters({ sprite });
		node2->addChild(sprite = cSprite::create(sps2.at(k)));
		sprite->play();
		r.iters({ sprite });
		r.iters();
		node2->setContentSize(r.getSize());
		y += node2->getContentSize().height + c10;
	}
	if (_iswm)
	{
		cWdfs::getInstance()->popReader();
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;

#if 0
	std::vector<std::vector<cSprite*>> sprite1s(4);
	std::vector<std::vector<cSprite*>> sprite2s(4);
	std::vector<std::string> names;
	cSprite* sprite;
	cNode* node = cNode::create();
	names.push_back("");
	if (_iswm)
	{
		cWdfs::getInstance()->pushReader(eIterType::wm);
	}
	for (int k = 0; k < 4; ++k)
	{
		node->addChild(sprite = cSprite::create(zuoqi.stand));
		sprite1s.at(k).push_back(sprite);

		node->addChild(sprite = cSprite::create(zuoqi.walk));
		sprite2s.at(k).push_back(sprite);
	}
	for (int k = 0; k < 3; ++k)
	{
		const auto& zhuangshi = zhuangshis.at(tag * 3 + k);
		node->addChild(sprite = cSprite::create(zhuangshi.stand));
		sprite1s.at(k + 1).push_back(sprite);

		node->addChild(sprite = cSprite::create(zhuangshi.walk));
		sprite2s.at(k + 1).push_back(sprite);
		names.push_back(icon.at(tag * 3 + k).name);
	}
	if (tag2 != cTagNone)
	{
		const auto& master = zuoqi.masters.at((eMod)tag2);
		node->addChild(sprite = cSprite::create(master.stand));
		sprite1s.at(0).push_back(sprite);
		node->addChild(sprite = cSprite::create(master.walk));
		sprite2s.at(0).push_back(sprite);
		for (int k = 0; k < 3; ++k)
		{
			const auto& master2 = zhuangshis.at(tag * 3 + k).masters.at((eMod)tag2);
			node->addChild(sprite = cSprite::create(master2.stand));
			sprite1s.at(k + 1).push_back(sprite);
			node->addChild(sprite = cSprite::create(master2.walk));
			sprite2s.at(k + 1).push_back(sprite);

			node->addChild(sprite = cSprite::create(master.stand));
			sprite1s.at(k + 1).push_back(sprite);
			node->addChild(sprite = cSprite::create(master.walk));
			sprite2s.at(k + 1).push_back(sprite);
		}
	}
	if (_iswm)
	{
		cWdfs::getInstance()->popReader();
	}
	cNode* node2;
	cLabel* label;
	expRank r;
	int y = 0;
	r.init(_wButBtn);
	forv(sprite1s, k)
	{
		node->addChild(label = cLabel::create(names[k]));
		label->setPosition(80, y);
		y += label->getContentSize().height + c10;
		node->addChild(node2 = cNode::create());
		node2->setPosition(0, y);
		r.init(_wButBtn);
		r.iters(sprite1s[k]);
		r.iters(sprite2s[k], true);
		node2->setContentSize(r.getSize());
		y += node2->getContentSize().height + c10;
		forv(sprite1s[k], i)
		{
			sprite1s[k][i]->setParent(node2);
			sprite2s[k][i]->setParent(node2);
			sprite1s[k][i]->play();
			sprite2s[k][i]->play();
		}
	}
	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;
#endif
}