#pragma once
#include "cBox.h"

class uiPad : public cNode
{
public:
	uiPad();

	static uiPad* create(const std::string& name_or_path, const std::string& name_or_path2, bool isWas, bool sortByWidth);

protected:
	~uiPad();
	bool init(const std::string& name_or_path, const std::string& name_or_path2, bool isWas, bool sortByWidth);

	void initRank(cSprite* sprite, ulong uid, cSprite* sprite2);

	void update(float dt);

private:
	int _inv, _i;
	float _h;
	Vec2 _v;
protected:
	std::vector<cLabel*> _labels;
	std::vector<Node*> _nodes, _node2;
public:
	std::function<void(const std::vector<std::string>&)> onKeyEnter = nullptr;
};
