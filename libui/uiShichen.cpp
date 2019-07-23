#include "uiShichen.h"
#include "uiManager.h"
#include "uiSmap.h"
#include "uiWorld.h"

static std::vector<ulong> s_uids =
{
	0x361FA820,
	0xC0A66903,
	0xD1D11294,
	0xAA7DEB05,
	0x21274A87,
	0x9C4978D,
	0xC9E2F072,
	0x2ACB36B2,
	0xC26BF189,
	0x1AA170AE,
	0x7921D3A3,
	0xEA7CAB84,
};
bool uiShichen::init()
{
	if (!cNode::init())
	{
		return false;
	}
	// 灯笼按钮 小地图
// 	this->addChild(_buttonSmall = cButton::create(3136727389));
	// 精灵 时辰 16*41
	this->addChild(_spriteShichen = cSprite::create(s_uids[0]));
	_spriteShichen->setSnatchNode(true);
	_spriteShichen->setPosition(1, 1);
	_spriteShichen->setDesc("显示/隐藏");
	_spriteShichen->onClick = [this]()
	{
		_spriteDay->setVisible(!_spriteDay->isVisible());
	};

	int y = 2;
	// 标签 当前地图
	_labelMap = cLabel::create("好长的地图名", eFont::chat);
	_labelMap->setColor(s565::YELLOW);
	_labelMap->setBack(true);
	_labelMap->setPositionY(y);
	y += _labelMap->getContentSize().height;
	// 标签 坐标xy
	_labelxy = cLabel::create("X:0 Y:0", eFont::chat);
	_labelxy->setColor(s565::YELLOW);
	_labelxy->setBack(true);
	_labelxy->setPositionY(y);
	y += _labelxy->getContentSize().height + 2;

	// 精灵 昼夜 360*30
	this->addChild(_spriteDay = cSprite::create(0x9DF6DEBC));
	_spriteDay->setSnatchNode(true);
	_spriteDay->setClip(0, _spriteDay->getContentSize().height / 2 - y / 2);
	_spriteDay->setAutoAp(false);
	_spriteDay->setContentSize(_labelMap->getContentSize().width + 4, y);
	_spriteDay->setPositionX(_spriteShichen->getPositionX() + _spriteShichen->getContentSize().width + 2);
	_spriteDay->setPositionY(_spriteShichen->getPositionY() + _spriteShichen->getContentSize().height / 2 - y / 2);
	_spriteDay->setDesc("长按呼出世界地图");
	_spriteDay->onClick = []()
	{
		ccu::getManager()->getSmap()->switchVisible();
	};
	_spriteDay->onEvent = [](bool left, bool up, int keeptimes)
	{
		if (left && keeptimes == 1)
		{
			ccu::getManager()->getWorld()->switchVisible();
		}
	};

	_spriteDay->addChild(_spriteNight = cSprite::create(2574487372));
	_spriteNight->setClip(0, _spriteDay->getContentSize().height);
	_spriteNight->setContentSize(_spriteDay->getContentSize());
	_spriteNight->setVisible(false);

	_spriteDay->addChild(_labelMap);
	_labelMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_labelMap->setPositionX(_spriteDay->getContentSize().width / 2);
	_spriteDay->addChild(_labelxy);
	_labelxy->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_labelxy->setPositionX(_labelMap->getPositionX());
	
	this->schedule(CC_SCHEDULE_SELECTOR(uiShichen::updateShichen));
	return true;
}

void uiShichen::setMapName(const std::string& mapname)
{
	_labelMap->setString(mapname);	
}

void uiShichen::setHeroXY(int x, int y)
{
	_labelxy->setString(toString("X:%d Y:%d", x, y));
}

void uiShichen::updateShichen(float delta)
{
	static time_t s_tt;
	static tm* s_t;
	static int s_sec;
	s_tt = ::time(nullptr);
	s_t = ::localtime(&s_tt);
	s_sec = (s_t->tm_min % 30) * 60 + s_t->tm_sec;
	if ((s_sec % 150) == 0)
	{
		s_sec /= 150;
		_spriteShichen->load(s_uids[s_sec]);
		_spriteNight->setVisible(s_sec < 3 || s_sec > 8);
	}
}

void uiShichen::setBattle(bool battle)
{
	_spriteDay->setVisible(!battle);
}

