#include "uiPad.h"
#include <fstream>

uiPad::uiPad():_inv(20), _i(0), _h(0)
{
}

uiPad* uiPad::create(const std::string& name_or_path, const std::string& name_or_path2, bool isWas, bool sortByWidth)
{
	CREATE(uiPad, name_or_path, name_or_path2, isWas, sortByWidth);
}

uiPad::~uiPad()
{
}

struct sInfo
{
	ulong uid;
	sSpInfo info;
};

static bool loadInfo(std::vector<sInfo>& infos, ulong u, bool loadinfo, char* ptr)
{
	if (*(ushort*)ptr != 0x5053)
	{
		return false;
	}
	sInfo inf;
	inf.uid = u;
#if 1
	if (loadinfo)
	{
		inf.info.load(ptr, true);
	}
#else
	inf.info.load(ptr, true);
	const auto& info = inf.info;
	// 条件筛选
#endif
	infos.push_back(inf);
	return true;
}


bool uiPad::init(const std::string& name_or_path, const std::string& name_or_path2, bool isWas, bool sortByWidth)
{
	if (!cNode::init())
	{
		return false;
	}

	char ptr[16];
	std::ifstream ifile;
	std::vector<sInfo> infos;
	if (isWas)
	{
		auto names = cc::efolder(name_or_path, true, 0);
		if (names.empty())
		{
			return false;
		}
		for (auto name : names)
		{
			ulong u = ccc_s2u(name);
			ifile.open(name_or_path + name, std::ios::binary);
			if (!ifile.is_open())
			{
				continue;
			}
			ifile.read(ptr, 16);
			ifile.close();
			if (!loadInfo(infos, u, sortByWidth, ptr))
			{
				continue;
			}
		}
	}
	else
	{
		ifile.open(name_or_path, std::ios::binary);
		if (!ifile.is_open())
		{
			return false;
		}
		cWas was;
		was.load(name_or_path);
		auto idx = was.getIndexs();
		for (auto k = 0; k < was.getIndexsCount(); ++k, ++idx)
		{
			ifile.seekg(idx->offset, std::ios::beg);
			ifile.read(ptr, 16);
			if (!loadInfo(infos, idx->uid, sortByWidth, ptr))
			{
				continue;
			}
		}
		ifile.close();
	}
	if (sortByWidth)
	{
		std::sort(infos.begin(), infos.end(), [](const sInfo& a, const sInfo& b)
		{
			if (a.info.width != b.info.width)
			{
				return a.info.width < b.info.width;
			}
			return a.info.height < b.info.height;
		});
	}
	else
	{
		std::sort(infos.begin(), infos.end(), [](const sInfo& a, const sInfo& b)
		{
			return a.uid < b.uid;
		});
	}


	std::vector<ulong> uids;
	forv(infos, k)
	{
		uids.push_back(infos.at(k).uid);
	}
	if (uids.empty())
	{
		return false;
	}

	_contentSize.width = cc::vsSize().width - _inv * 2;
	_contentSize.height = _inv;
	if (isWas)
	{
		int size;
		forv(uids, k)
		{
			ifile.open(name_or_path + ccc_u2was(uids.at(k)), std::ios::binary);
			ifile.seekg(0, std::ios::end);
			size = ifile.tellg();
			char* ptr = new char[size];
			ifile.seekg(0, std::ios::beg);
			ifile.read(ptr, size);
			ifile.close();
			cSprite* sprite = cSprite::create(ptr);
			cSprite* sprite2 = nullptr;
			if (!name_or_path2.empty())
			{
				ifile.open(name_or_path2 + ccc_u2was(uids.at(k)), std::ios::binary);
				ifile.seekg(0, std::ios::end);
				size = ifile.tellg();
				ptr = new char[size];
				ifile.seekg(0, std::ios::beg);
				ifile.read(ptr, size);
				ifile.close();
				sprite2 = cSprite::create(ptr);
			}
			initRank(sprite, uids.at(k), sprite2);
		}
	}
	else
	{
		cWas was, was2;
		was.load(name_or_path);
		if (!name_or_path2.empty())
		{
			was2.load(name_or_path2);
		}
		int size;
		forv(uids, k)
		{
			cSprite* sprite = cSprite::create(was.getData(uids.at(k), size));
			cSprite* sprite2 = nullptr;
			if (!name_or_path2.empty())
			{
				sprite2 = cSprite::create(was2.getData(uids.at(k), size));
			}
			initRank(sprite, uids.at(k), sprite2);
		}
	}

	for (auto n : _nodes)
	{
		n->setPositionY(n->getPositionY() + _h - n->getContentSize().height);
	}
	for (auto n : _node2)
	{
		n->setPositionY(n->getPositionY() + _h - n->getContentSize().height);
	}

	Size size = _contentSize;
	size.height += _inv * 3;
	_contentSize = Size::ZERO;
	setContentSize(size);
	setPositionX(_inv);
	_h = cc::vsSize().height;

	if (_contentSize.height > _h)
	{
		setSnatchNode(true);
		setDragType(eMouseDrag::V);
		setWheel(1);
	}
	scheduleUpdate();
	return true;
}


static cNode* initRank(cSprite* sprite, ulong uid)
{
	cNode* node = cNode::create();
	node->addChild(sprite);
	const sSpInfo& info = *sprite->getInfo();
	node->setContentSize(info.width, info.height);
	// 框
	cBox* box = cBox::create();
	node->addChild(box);
	box->setColor(s565::GRAY);
	box->setContentSize(node->getContentSize());
	// 编号
	if (uid != cSp::c0)
	{
		cLabel* label = cLabel::create(ccc_u2s(uid), eFont::smal);
		label->setColor(s565::GREEN);
		label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		label->setTag(10086);
		node->addChild(label);
		label->setVisible(false);
		label->setPosition(0, info.height + 2);
	}
	// 方向
	if (info.directionsCount == 2 || info.directionsCount == 8)
	{
		cLabel* label = cLabel::create(cc::toString(info.directionsCount), eFont::smal);
		label->setPosition(0, info.height - label->getContentSize().height);
		node->addChild(label);
	}
	// 帧
	if (info.framesCountPerDirection > 1)
	{
		sprite->play();
		if (info.framesCountPerDirection != 4)
		{
			cLabel* label = cLabel::create(cc::toString(info.framesCountPerDirection), eFont::smal);
			label->setPosition(info.width - label->getContentSize().width, info.height - label->getContentSize().height);
			label->setColor(s565::YELLOW);
			node->addChild(label);

			// 锚点
			box = cBox::create();
			node->addChild(box);
			box->setColor(s565::RED);
			box->setPosition(sprite->getAnchorPointInPoints() - Vec2(1, 1));
			box->setContentSize(3, 3);
		}
	}
	return node;
}


void uiPad::initRank(cSprite* sprite, ulong uid, cSprite* sprite2)
{
	if (!sprite->isValid())
	{
		return;
	}

	cNode* node = ::initRank(sprite, uid);
	_labels.push_back((cLabel*)node->getChildByTag(10086));
	cNode* node2 = (sprite2 != nullptr && sprite2->isValid()) ? ::initRank(sprite2, cSp::c0) : nullptr;

	Size size = node->getContentSize();
	Size size2 = node2 == nullptr ? Size::ZERO : node2->getContentSize();
	float w = size.width + _inv + size2.width + _inv;

	if (_i > 0 && _v.x + w > _contentSize.width)
	{
		for (auto n : _nodes)
		{
			n->setPositionY(n->getPositionY() + _h - n->getContentSize().height);
		}
		for (auto n : _node2)
		{
			n->setPositionY(n->getPositionY() + _h - n->getContentSize().height);
		}
		_nodes.clear();
		_node2.clear();
		_contentSize.height += _h + _inv;
		_h = 0;
		_v.x = 0;
	}
	_h = std::max(_h, size.height);
	_h = std::max(_h, size2.height);
	node->setPosition(_v.x, _contentSize.height);
	addChild(node);
	_nodes.push_back(node);
	if (node2 != nullptr)
	{
		node2->setPosition(node->getPositionX() + size.width + _inv, _contentSize.height);
		addChild(node2);
		_node2.push_back(node2);
	}
	_v.x += w;
	node->setSnatchNode(true);
	node->onClick = [node]()
	{
		cLabel* label = (cLabel*)node->getChildByTag(10086);
		bool visible = label->isVisible();
		label->setVisible(!visible);
		if (!visible)
		{
			std::string s = "0x";
			s += label->getString() + ",";
			OutputDebugStringA(s.c_str());
		//	ccc_log(s.c_str());
		}
	};
	++_i;
}


void uiPad::update(float dt)
{
	if (isSnatchNode())
	{
		if (_position.y > _inv)
		{
			setPositionY(_inv);
		}
		if (_position.y + _contentSize.height < _h)
		{
			setPositionY(_h - _contentSize.height);
		}
	}

	auto input = cInput::getInstance();
	if (input->isKdown(DIK_TAB))
	{
		bool visible = _labels.front()->isVisible();
		for (const auto& l : _labels)
		{
			l->setVisible(!visible);
		}
		if (!visible)
		{
			int i = 0;
			for (const auto& l : _labels)
			{
				std::string s = "0x";
				s += l->getString() + ",";
				if ((++i) % 10 == 0)
				{
					s += '\n';
				}
				OutputDebugStringA(s.c_str());
			}
		}
	}
	else if (input->isKdown(DIK_SPACE))
	{
		OutputDebugStringA("0x00000000,");
	}
	else if (input->isKdown(DIK_ENTER))
	{
		ccc_log("Enter: Begin");
		std::vector<std::string> moves;
		for (const auto& l : _labels)
		{
			if (l->isVisible())
			{
				std::string s = "0x";
				s += l->getString();
				ccc_log(s.c_str());
				moves.push_back(l->getString());
			}
		}
		ccc_log("Enter: End %d", moves.size());
		if (onKeyEnter)
		{
			onKeyEnter(moves);
		}
#if 0
		if (moves.empty())
		{
			return;
		}

		for (const auto& label : _labels)
		{
			if (!label->isVisible())
			{
				continue;
			}
			SpriteBtn* spr = (SpriteBtn*)label->getUserData();
			if (!spr->isAllTexturesLoaded())
			{
				ccc_msgbox("加载未完成", "请稍等");
				return;
			}
		}

		string path;
		std::ofstream ofile;
		for (const auto& label : _labels)
		{
			if (!label->isVisible())
			{
				continue;
			}
			path = "导出图片/" + label->getString() + "/";
			ccc_md(path);
			SpriteBtn* spr = (SpriteBtn*)label->getUserData();
			ofile.open(path + "_锚点.txt");
			ofile << spr->getKx() << "\n" << spr->getKy();
			ofile.close();
			spr->savePNG(path + label->getString());
		}
#endif
	}
}
