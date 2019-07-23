#include "expXiangrui.h"


const auto& xiangruis = txtXiangrui::getInstance()->getTables();
bool expXiangrui::init()
{
	if (!expEasy::init())
	{
		return false;
	}
	for (const auto& x : xiangruis)
	{
		initButton(toString("%d", x.first)/*, x.first == (xiangruis.size() - 1)*/);
	}
	initButton();

	return expEasy::init(initDrag(0));
}

static const auto& stands = txtZuoqi::getInstance()->getMasterStands();
static const auto& walks = txtZuoqi::getInstance()->getMasterWalks();
cNode* expXiangrui::initDrag(int tag, int tag2 /* = cTagNone */)
{
	const auto& xr = xiangruis.at(tag);
	std::vector<std::vector<cSprite*>> sprite1s(4);
	std::vector<std::vector<cSprite*>> sprite2s(4);
	cSprite* sprite;
	cNode* node = cNode::create();
	cNode* node2;
	expRank r;
	int y = 0;
#if 0
	bool testWdf = true;
	if (testWdf)
	{
		r.init(_wButBtn);
		auto wdfs = cWdfs::getInstance();
		r.init(_wButBtn);
		char arr[12];
		cWdf::sIndex* idxs;
		ushort d, f, w, h;
		for (const auto& wdf : wdfs->_wdfs)
		{
			break;
			idxs = wdf->_indexs;
			for (int k = 0; k < wdf->_indexsCount; ++k, ++idxs)
			{
				fseek(wdf->_file, idxs->offset, SEEK_SET);
				fread(arr, 12, 1, wdf->_file);
				f = *(ushort*)(arr + 4);
				d = *(ushort*)(arr + 6);
				w = *(ushort*)(arr + 8);
				h = *(ushort*)(arr + 10);
				if (d > 1 || f > 1)
				{
					continue;
				}
				f = std::abs(w - 40);
				d = std::abs(h - 40);
				if (d <= 2 && f <= 2)
				{
					continue;
				}
				if (d > 8 || f > 8)
				{
					continue;
				}
				node->addChild(sprite = createSpriteWithName(idxs->uid, toString("%08X", idxs->uid), s565::GREEN));
				r.iter(sprite);
			}
		}


		std::vector<ulong> uids =
		{
//			0xA56931AA, // 蚩尤中（在）
//			0xD0C8C11A, // 蚩尤小（在）
//			0xA69F6B2F, // 筋斗云小（在）
// 			0x0D637B35,
// 			0x05629052,
			0x85512FAA, // 土地小
			0xFA16B987, // 神猴小
			0x213332BC, // 神猴小
			0xADA2838B, // 上古灵符小
//			0x44829CE3, // 牛魔王小（在）
			0xDDBE8053, // 镜小
			0xD5C9E162, // 增长小
			0x736BF280, // 增长小迭
			0xAF9B8C7A, // 金铙小迭
			0xB1E73C63, // 龙马小
			0x9095F45E, // 泪小
			0xAE67D62E, // 泪小迭
			0x2DEC09F9, // 猕猴小
			0x85603ADA, // 神羊小
//			0xD5941BB1, // 占仆小（在）
// 			0x5B3E9AC6,
// 			0x575F5122,
			0x1D585652, // 天女小
// 			0x5A7B589D,
// 			0xD8933B51,
			0x767B5ADF,  // 琴小
// 			0x4A1D90BB,
// 			0x8E7EDE48,
// 			0x0C637B35,
// 			0x8EBBBD08,
// 			0xCF8279AC,
		};
// 		uids = 
// 		{
// 			0x1E714129,
// 			0x3FEEB486,
// 			0x7367031D,
// 			0xF2FC2425,
// 			0x2D8A2623,
// 			0x30B1D3BD,
// 			0x3CF9D5D1,
// 			0x4B4A766F,
// 			0x7DEC7858,
// 			0xACB4D7DD,
// 			0xAEB1CB42,
// 			0xDF77B951,
// 			0x1F996671,
// 			0x9C24F376,
// 			0xCD999F0B,
// 
// 
// 			0x2208A659, 0x1DDBB1C6, 0x6F6E119A, 0xEC47773C, 0x4CBC0CC5, 0xE74758DC,
// 			0xC9417A1A, 0x77ACF46A, 0x436E551F, 0x9953B8A3, 0x32F0DC6C
// 		};
		for (auto u : uids)
		{
			node->addChild(sprite = createSpriteWithName(u, toString("%08X", u), s565::GREEN));
			r.iter(sprite);
		}
		r.iter();
		y = r.getSize().height;

	}
	else
#endif
	{
		for (int k = 0; k < 4; ++k)
		{
			node->addChild(sprite = cSprite::create(xr.stand));
			sprite1s.at(k).push_back(sprite);
			if (xr.stand2 != 0)
			{
				node->addChild(sprite = cSprite::create(xr.stand2));
				sprite1s.at(k).push_back(sprite);
			}

			node->addChild(sprite = cSprite::create(xr.walk));
			sprite2s.at(k).push_back(sprite);
			if (xr.walk2 != 0)
			{
				node->addChild(sprite = cSprite::create(xr.walk2));
				sprite2s.at(k).push_back(sprite);
			}
		}
		std::vector<eMod> mods = { eMod::eJueSe偃无师, eMod::eJueSe桃夭夭, eMod::eJueSe鬼潇潇 };
		forv(mods, k)
		{
			node->addChild(sprite = cSprite::create(stands.at(mods[k]).at(0)));
			sprite1s.at(k + 1).push_back(sprite);

			node->addChild(sprite = cSprite::create(walks.at(mods[k]).at(0)));
			sprite2s.at(k + 1).push_back(sprite);
		}

		forv(sprite1s, k)
		{
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
	}

	node->setContentSize(_wButBtn, y);
	node->setPositionX(_btnw + c10);
	return node;
}