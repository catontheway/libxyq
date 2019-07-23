#include "cMapFollow.h"


cMapFollow* cMapFollow::getInstance()
{
	static cMapFollow* s_mapRender = new cMapFollow();
	return s_mapRender;
}


bool cMapFollow::setTarget(cocos2d::Node* target, cocos2d::Node* obj)
{
	_nodeTarget = target;
	_nodeObj = obj;

	if (_nodeTarget != nullptr)
	{
		_mw = _nodeTarget->getContentSize().width;
		_mh = _nodeTarget->getContentSize().height;
		_leftBoundary = _sw - _mw;
		_rightBoundary = 0;
		_topBoundary = 0;
		_bottomBoundary = _sh - _mh;

		_isSmallThenScreenw = _leftBoundary > 0;
		_isSmallThenScreenh = _bottomBoundary > 0;
		if (_rightBoundary < _leftBoundary)
		{
			// screen width is larger than world's boundary width
			//set both in the middle of the world
			_rightBoundary = _leftBoundary = (_leftBoundary + _rightBoundary) / 2;
		}
		if (_topBoundary < _bottomBoundary)
		{
			// screen width is larger than world's boundary width
			//set both in the middle of the world
			_topBoundary = _bottomBoundary = (_topBoundary + _bottomBoundary) / 2;
		}

		if ((_topBoundary == _bottomBoundary) && (_leftBoundary == _rightBoundary))
		{
			_boundaryFullyCovered = true;
		}
		else
		{
			_boundaryFullyCovered = false;
		}

		if (_isSmallThenScreenw)
		{
			_nodeTarget->setPositionX(cc::vsCenter().x - _mw / 2);
		}
		if (_isSmallThenScreenh)
		{
			_nodeTarget->setPositionY(cc::vsCenter().y - _mh / 2);
		}
	}
	return true;
}


bool cMapFollow::setSpeedMax(float speed)
{
	_speedMax = speed;
	return true;
}



void cMapFollow::onSize(int sw, int sh)
{
	_sw = sw, _sh = sh;
	setTarget(_nodeTarget, _nodeObj);
}


void cMapFollow::setPosition(const cocos2d::Vec2& vFollow)
{
	if (_nodeTarget == nullptr || _nodeObj == nullptr)
	{
		return;
	}
	_nodeTarget->setPosition(toPosition(vFollow));
}


const cocos2d::Vec2& cMapFollow::toPosition(const cocos2d::Vec2& vFollow)
{
	static cocos2d::Vec2 v;
	v.x = _sw;
	v.y = _sh;
	v = v / 2 - vFollow;
	v.x = cocos2d::clampf(v.x, _leftBoundary, _rightBoundary);
	v.y = cocos2d::clampf(v.y, _bottomBoundary, _topBoundary);
	return v;
}


void cMapFollow::correctPosition(cocos2d::Vec2& v)
{
	if (_isSmallThenScreenw)
	{
		v.x =_sw / 2 - _mw / 2;
	}
	else
	{
		v.x = std::min(0.0f, v.x);
		v.x = std::max((int)v.x, _sw - _mw);
	}
	if (_isSmallThenScreenh)
	{
		v.y = _sh / 2 - _mh / 2;
	}
	else
	{
		v.y = std::min(0.0f, v.y);
		v.y = std::max((int)v.y, _sh - _mh);
	}
}


void cMapFollow::correctPosition(Node* targrt)
{
	int _sw = cc::vsSize().width;
	int _sh = cc::vsSize().height;
	int _mw = targrt->getContentSize().width;
	int _mh = targrt->getContentSize().height;
	Vec2 v = targrt->getPosition();
	if (_sw > _mw)
	{
		v.x = _sw / 2 - _mw / 2;
	}
	else
	{
		v.x = std::min(0.0f, v.x);
		v.x = std::max((int)v.x, _sw - _mw);
	}
	if (_sh > _mh)
	{
		v.y = _sh / 2 - _mh / 2;
	}
	else
	{
		v.y = std::min(0.0f, v.y);
		v.y = std::max((int)v.y, _sh - _mh);
	}
	targrt->setPosition(v);
}

bool cMapFollow::step()
{
	if (_isSmallThenScreenw && _isSmallThenScreenh)
	{
		return true;
	}
	if (_nodeTarget == nullptr || _nodeObj == nullptr || _boundaryFullyCovered)
	{
		return false;
	}
	static cocos2d::Vec2 v;
	// whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
	v = toPosition(_nodeObj->getPosition());
	if (_nodeTarget->getPosition().distance(v) < _speedMax)
	{
		return false;
	}

	v -= _nodeTarget->getPosition();
	static float s_speed;
	s_speed = v.length() / 0x33;
	s_speed = std::max(s_speed, 1.0f);
	s_speed = std::min(s_speed, _speedMax);
	v.normalize();
	v = _nodeTarget->getPosition() + v * s_speed;
	correctPosition(v);
	_nodeTarget->setPosition(v);
	return true;
}