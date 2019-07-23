#include "cLayer.h"

float s_actionDuration = .1f;

void cLayer::cNodeInner::setRectWorld()
{
	cNode::setRectWorld();
	float x, y, w, h;
	for (auto& c : _children)
	{
		if (c == nullptr)
		{
			continue;
		}
		c->getPosition(&x, &y);
		w = c->getContentSize().width;
		h = c->getContentSize().height;
		x += _position.x - c->getAnchorPointInPoints().x;
		y += _position.y - c->getAnchorPointInPoints().y;
		if (x < 0 || y < 0 || x - w > _parent->getContentSize().width || y - h > _parent->getContentSize().height)
		{
			c->setVisible(false);
		}
		else
		{
			c->setVisible(true);
		}
	}
}

bool cLayer::cNodeInner::isSnatched(const Vec2& v)
{
	return ((cNode*)_parent)->isSnatched(v + _position);
}

void cLayer::cNodeInner::doCross(bool draging)
{
	if (draging)
	{
		((cLayer*)_parent)->doDraging();

	}
}

//////////////////////////////////////////////////////////////////////////
cLayer::~cLayer()
{
	ccc_delete(_canvas);
}

bool cLayer::init(const std::function<cNodeInner * ()>& innerCreater)
{
	if (!cNode::init())
	{
		return false;
	}
	_nodeInner = (innerCreater == nullptr) ? cNodeInner::create() : innerCreater();
	cNode::addChild(_nodeInner);
	_nodeInner->setSnatchNode(true);
	_nodeInner->setWheel(1);

	this->setSnatchNode(true);
	this->setDragType(eMouseDrag::V);
	return true;
}

void cLayer::setContentSize(const Size& contentSize)
{
	cNode::setContentSize(contentSize);
	ccc_delete(_canvas);
	_canvas = new cCanvas(contentSize.width, contentSize.height);
}

void cLayer::setContentSize(float w, float h)
{
	cNode::setContentSize(w, h);
	ccc_delete(_canvas);
	_canvas = new cCanvas(w, h);
}

void cLayer::setInnerSize(const Size& contentSize)
{
	_nodeInner->setContentSize(contentSize);
}

void cLayer::setInnerSize(float w, float h)
{
	_nodeInner->setContentSize(w, h);
}

void cLayer::addChild(Node* child, int localZOrder, int tag)
{
	_nodeInner->addChild(child, localZOrder, tag);
	addChildInner(child);
}

void cLayer::addChild(Node* child, int localZOrder)
{
	_nodeInner->addChild(child, localZOrder);
	addChildInner(child);
}

void cLayer::addChild(Node* child)
{
	_nodeInner->addChild(child);
	addChildInner(child);
}

void cLayer::addChildInner(Node* child)
{
	return;
	cNode* c = dynamic_cast<cNode*>(child);
	if (c != nullptr)
	{
//		c->setCanvas(&_canvas);
	}
}


void cLayer::setDragType(const eMouseDrag& e)
{
	_nodeInner->setDragType(e);
	switch (e)
	{
	case eMouseDrag::None:
		if (_isScheduled)
		{
			unscheduleUpdate();
			_isScheduled = false;
		}
		break;
	default:
		if (!_isScheduled)
		{
			scheduleUpdate();
			_isScheduled = true;
		}
		break;
	}
}

void cLayer::doDraging()
{
	Vec2 v = trimPosition(_nodeInner->getPosition(), 0);
	if (!_isBounceable)
	{
		_nodeInner->setPosition(v);
	}
	else if (!v.equals(_nodeInner->getPosition()))
	{
		_nodeInner->stopAllActions();
		_nodeInner->runAction(MoveTo::create(s_actionDuration, v));
	}
}

cocos2d::Vec2 cLayer::trimPosition(Vec2 v, float tolerance)
{
	const float &w = _contentSize.width;
	const float &h = _contentSize.height;

	Vec2 vs = _nodeInner->getContentSize();
	float sw = vs.x;
	float sh = vs.y;
	vs += v;

	Vec2 v2 = v;
	bool f = false;
	if (v.x > tolerance)
	{
		f = true;
		v2.x = tolerance;
	}
	else if (vs.x + tolerance < w)
	{
		f = true;
		v2.x = w - sw - tolerance;
	}
	if (v.y > tolerance)
	{
		f = true;
		v2.y = tolerance;
	}
	else if (vs.y + tolerance < h)
	{
		v2.y = h - sh - tolerance;
	}
	return v2;
}


// void cLayer::draw(const uint32_t& flags)
// {
// //	cNode::_canvas->setChange(flags, _isDraw && !flags);
// 	if (flags)
// 	{
// 		cNode::_canvas->Change();
// 	}
// 	else if (_isDraw && !flags)
// 	{
// 		cNode::_canvas->SelfChange();
// 	}
// 	else
// 	{
// 		cNode::_canvas->UnChange();
// 	}
// 	cNode::_canvas->SetPos(_wx, _wy);
// 	_canvas->Clear(0);
// 	cNode::_canvas->Draw(*_canvas);
// 	cSnatch::setCover(flags);
// }
// 
// void cLayer::update(float delta)
// {
// 	auto input = cInput::getInstance();
// 	if (!_rectWorld.containsPoint(input->getMouse()))
// 	{
// 		return;
// 	}
// 	if (_wheel != 0)
// 	{
// 		int wheel = input->getWheel();
// 		if (wheel != 0)
// 		{
// 			_nodeInner->setPositionY(_nodeInner->getPositionY() + wheel * _wheel);
// 			doDraging();
// 		}
// 	}
// }
