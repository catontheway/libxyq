#pragma once
#include "_inc.h"

// 时辰,左上角
class uiShichen : public cNode
{
public:
	CREATE_FUNC(uiShichen);
	virtual bool init();

	// 地图名
	void setMapName(const std::string& mapname);
	// 主角位置
	void setHeroXY(int x, int y);

	void updateShichen(float delta);

	void setBattle(bool battle);

	cSprite* getSpriteDay() { return _spriteDay; }

protected:
	// 精灵 时辰
	cSprite* _spriteShichen = nullptr;

	// 精灵 昼夜
	cSprite* _spriteDay = nullptr;
	cSprite* _spriteNight = nullptr;
	// 标签 当前地图
	cLabel* _labelMap = nullptr;

	// 标签 坐标xy
	cLabel* _labelxy = nullptr;

	// 灯笼按钮 小地图
	cButton* _buttonSmall = nullptr;

	// 灯笼按钮 大地图
	cButton* _buttonBig = nullptr;
};