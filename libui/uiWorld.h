#pragma once
#include "uiPad.h"

// 世界地图
class uiWorld : public uiPad
{
public:
	CREATE_FUNC(uiWorld);
	virtual bool init();
	virtual void doClose();

protected:
	void doHide();

	// 世界
	Node* _nodeWorld = nullptr;
	// 东
	Node* _nodeEast = nullptr;

	// 西
	Node* _nodeWest = nullptr;

	// 南
	Node* _nodeSouth = nullptr;

	// 北
	Node* _nodeNorth = nullptr;

public:
	std::function<void(const std::string&, int, int)> onSelect = nullptr;
};