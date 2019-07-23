#pragma once
#include "_inc.h"

class cMapFollow
{
public:
	static cMapFollow* getInstance();

	// target 被删了怎么办
	bool setTarget(cocos2d::Node* target, cocos2d::Node* obj);
	bool setSpeedMax(float speed);

	void onSize(int sw, int sh);

	cocos2d::Node* getTarget(){ return _nodeTarget; }
	cocos2d::Node* getTargetObj(){ return _nodeObj; }

	void setPosition(const cocos2d::Vec2& vFollow);
	const cocos2d::Vec2& toPosition(const cocos2d::Vec2& vFollow);
	void correctPosition(cocos2d::Vec2& vTarget);
	static void correctPosition(Node* targrt);
	// 返回: 是否动
	bool step();

	cocos2d::Node* _nodeTarget = nullptr;
	cocos2d::Node* _nodeObj = nullptr;
	
	int _sw, _sh, _mw, _mh;

	float _leftBoundary, _rightBoundary, _topBoundary, _bottomBoundary;
	bool _boundaryFullyCovered;
	bool _isSmallThenScreenw, _isSmallThenScreenh;

	float _speedMax;
};