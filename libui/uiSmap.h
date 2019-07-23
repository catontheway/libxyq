#pragma once
#include "uiPad.h"

// 小地图
class uiSmap : public uiPad
{
public:
	CREATE_FUNC(uiSmap);
	bool init();
	// 事件
	void doEvent(bool left, bool up, int keepTimes);

	void doCross(bool draging);

	void clear();

	// 载入
	void load(ulong suid, const Size& mapSize);

	void load(const std::vector<Vec2>& paths);

	void loadTrans(const std::string& name, const Vec2& v);
	void loadNpc(const std::string& name, const Vec2& v);
	void loadNpcTemp(const std::string& name, const Vec2& v);
	void loadInner(Node* node, const std::string& name, const Vec2& v, const s565& color);

	cSprite* getSpriteHero() { return _spriteHero; }
	void moving(const Vec2& v);
protected:

	float _rate;

	cSprite* _spriteSmap = nullptr;
	cSprite* _spriteHero = nullptr;

	Node* _nodeHero = nullptr;
	Node* _nodePaths = nullptr;
	Node* _nodeNpc = nullptr;
	Node* _nodeTrans = nullptr;
	Node* _nodeNpcTemp = nullptr;

public:
	static const Vec2 cVec18;
	// 点击(小地图坐标,注意是节点坐标)
	std::function<void(const Vec2&)> onClick = nullptr;
};