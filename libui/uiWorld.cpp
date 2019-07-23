#include "uiWorld.h"

// 地图显示状态
enum  eMap
{
	eMapWorld,
	eMapEast,
	eMapWest,
	eMapSouth,
	eMapNorth,
};

static std::map<eMap, ulong> s_mapuids = 
{
	{ eMapWorld, 0x93E77F54 },
	{ eMapEast, 0x26E89B1F },
	{ eMapWest, 0x11A18FBF },
	{ eMapSouth, 0x0B19A5DC },
	{ eMapNorth, 0xE9EC7A25 },
};
bool uiWorld::init()
{
	if (!uiPad::init(s_mapuids.at(eMapWorld), true))
	{
		return false;
	}
//	setDragType(uiEvent::eDrag::None);
//	setCloseRup(false);
	addChild(_nodeWorld = Node::create());
	cButton* button;
	// 按钮是正序遍历,所以小的先放比较好
#define ccc_create_button(_node_, _uid_, _name_, _x_, _y_, _tx_, _ty_)\
{\
	button = cButton::create(_uid_);\
	button->setSnatchPixel(true);\
	_node_->addChild(button);\
	button->setDesc(_name_);\
	button->setPosition(_x_, _y_);\
	button->onClick = [this]()\
	{\
		this->setVisible(false);\
		if(!sTeam::getInstance()->isFighting() && onSelect != nullptr)\
		{\
			onSelect(_name_, _tx_, _ty_);\
		}\
	};\
}
	// 蟠桃
	ccc_create_button(_nodeWorld, 0xF8A67A7A, "蟠桃园", 199, 0, 132, 25);
	// 天宫
	ccc_create_button(_nodeWorld, 0x5ABFF907, "天宫", 166, 23, 203, 33);
	// 月宫
	ccc_create_button(_nodeWorld, 0xF63C410E, "月宫", 75, 4, 98, 60);
	// 龙宫
	ccc_create_button(_nodeWorld, 0xCE11152D, "龙宫", 388, 376, 91, 46);
	// 北俱芦洲
	cButton* buttonNorth = cButton::create(0xEA1F50E2);
	buttonNorth->setDesc("北俱芦洲");
	_nodeWorld->addChild(buttonNorth);
	buttonNorth->setPosition(271, 10);
	buttonNorth->onClick = [this]()
	{
		doHide();
		_nodeNorth->setVisible(true);
		uiPad::load(s_mapuids.at(eMapNorth));
	};
	// 东胜神洲
	cButton* buttonEast = cButton::create(0xCC1742A6);
	buttonEast->setDesc("东胜神洲");
	_nodeWorld->addChild(buttonEast);
	buttonEast->setPosition(499, 160);
	buttonEast->onClick = [this]()
	{
		doHide();
		uiPad::load(s_mapuids.at(eMapEast));
		_nodeEast->setVisible(true);
	};
	// 西牛贺洲
	cButton* buttonWest = cButton::create(0x0AF24A29);
	buttonWest->setDesc("西牛贺洲");
	_nodeWorld->addChild(buttonWest);
	buttonWest->setPosition(0, 58);
	buttonWest->onClick = [this]()
	{
		doHide();
		uiPad::load(s_mapuids.at(eMapWest));
		_nodeWest->setVisible(true);
	};
	// 南部瞻洲
	cButton* buttonSouth = cButton::create(0x7FFAB47A);
	buttonSouth->setDesc("南部瞻洲");
	_nodeWorld->addChild(buttonSouth);
	buttonSouth->setPosition(85, 104);
	buttonSouth->onClick = [this]()
	{
		doHide();
		uiPad::load(s_mapuids.at(eMapSouth));
		_nodeSouth->setVisible(true);
	};

	addChild(_nodeEast = Node::create());
	addChild(_nodeWest = Node::create());
	addChild(_nodeNorth = Node::create());
	addChild(_nodeSouth= Node::create());
	doHide();
	_nodeWorld->setVisible(true);

	// 花果山
	ccc_create_button(_nodeEast, 0x6B27F57F, "花果山", 263, 11, 35, 98);
	// 女儿村
	ccc_create_button(_nodeEast, 0x6BF13E64, "女儿村", 212, 162, 69, 63);
	// 傲来
	ccc_create_button(_nodeEast, 0xCCB7A7C3, "傲来国", 343, 273, 127, 92);
	// 蓬莱
	ccc_create_button(_nodeEast, 0xA9BC7D93, "蓬莱仙岛", 149, 313, 83, 34);
	// 女娲神迹
	ccc_create_button(_nodeNorth, 0xEDEEF9AF, "女娲神迹", 161, 20, 51, 38);
	// 龙窟
	ccc_create_button(_nodeNorth, 0xA0B51368, "龙窟一层", 52, 167, 148, 15);
	// 凤巢
	ccc_create_button(_nodeNorth, 0x13659C02, "凤巢一层", 327, 145, 64, 59);
	// 宝象国
	ccc_create_button(_nodeWest, 0x0D906C8D, "宝象国", 488, 274, 115, 72);
	ccc_create_button(_nodeWest, 0x6A154DDE, "方寸山", 542, 8, 126, 42);
	ccc_create_button(_nodeWest, 0x637B3C48, "长寿村", 414, 117, 107, 58);
	ccc_create_button(_nodeWest, 0x63566DA9, "比丘国", 329, 101, 58, 79);
	ccc_create_button(_nodeWest, 0xE329AD6A, "西梁女国", 457, 200, 84, 62);
	ccc_create_button(_nodeWest, 0x048DA00D, "麒麟山", 387, 317, 31, 117);
	ccc_create_button(_nodeWest, 0x689EB676, "朱紫国", 469, 330, 12, 7);


	ccc_create_button(_nodeSouth, 0xE0C66A6F, "大唐官府", 450, 102, 99, 35);
	ccc_create_button(_nodeSouth, 0x9C992236, "阴曹地府", 331, 34, 44, 54);
	ccc_create_button(_nodeSouth, 0xFF1D4A14, "大唐境外", 105, 230, 394, 56);
	button->setDesc("高老庄");
	ccc_create_button(_nodeSouth, 0x6EA52AE1, "大唐国境", 295, 130, 41, 36);
	button->setDesc("洪州");
	ccc_create_button(_nodeSouth, 0x47FE6497, "化生寺", 477, 158, 35, 20);
	ccc_create_button(_nodeSouth, 0x6AB41A9A, "建邺城", 468, 232, 266, 33);
	ccc_create_button(_nodeSouth, 0x991B588D, "大唐国境", 350, 113, 204, 234);
	button->setDesc("江州");
	ccc_create_button(_nodeSouth, 0xAD1DC28A, "龙宫", 469, 374, 91, 46);
	ccc_create_button(_nodeSouth, 0x150B5122, "魔王寨", 191, 94, 39, 24);
	ccc_create_button(_nodeSouth, 0x301A4FE7, "盘丝岭", 213, 194, 179, 120);
	ccc_create_button(_nodeSouth, 0xEC9EBCA8, "普陀山", 333, 410, 69, 18);
	ccc_create_button(_nodeSouth, 0xBF78C1EF, "狮驼岭", 4, 185, 114, 83);
	ccc_create_button(_nodeSouth, 0x5B96A2DD, "无名鬼城", 273, 18, 46, 25);
	ccc_create_button(_nodeSouth, 0xCA26DE5D, "五庄观", 232, 271, 43, 38);
	ccc_create_button(_nodeSouth, 0xEA60ABA4, "小西天", 50, 69, 37, 208);
	ccc_create_button(_nodeSouth, 0xF617F5A9, "墨家村", 155, 17, 42, 155);

	ccc_create_button(_nodeSouth, 0x71DF41E1, "长安城", 368, 141, 200, 160);

#undef ccc_create_button
	return true;
}

void uiWorld::doClose()
{
	if (_nodeWorld->isVisible())
	{
		uiPad::doClose();
	}
	else
	{
		doHide();
		uiPad::load(s_mapuids.at(eMapWorld));
		_nodeWorld->setVisible(true);
	}
}

void uiWorld::doHide()
{
	_nodeEast->setVisible(false);
	_nodeWest->setVisible(false);
	_nodeNorth->setVisible(false);
	_nodeSouth->setVisible(false);
	_nodeWorld->setVisible(false);
}
