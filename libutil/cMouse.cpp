#include "cMouse.h"
#include "cCursor.h"

cSnatch::~cSnatch()
{
	cMouse::getInstance()->onRemove(this);
}

void cSnatch::setEnabled(bool isEnabled)
{
	if (_isEnabled == isEnabled)
	{
		return;
	}
	_isEnabled = isEnabled;

	if (!isEnabled)
	{
		setState(eMouseState::Disabled);
	}
	else
	{
		setState(eMouseState::Normal);
	}
}



//////////////////////////////////////////////////////////////////////////
static const int s_dragThreshold = 4; // 64;
static const float s_keetThreshold = 0.7f;


bool cSnatchDrager::stepLkeep(const Vec2& vCursor, cSnatch* snatchTop, bool isMoveing)
{
	if (_snatchDraging == nullptr)
	{
		if (!isMoveing)
		{
			return false;
		}
		if (snatchTop == nullptr || !snatchTop->isEnabled())
		{
			return false;
		}
		if (snatchTop->_dragType == eMouseDrag::None)
		{
			return false;
		}
		if (vCursor.distance(_vecStartCursor) < s_dragThreshold)
		{
			return false;
		}
		_snatchDraging = snatchTop;
		_vecDrag = _snatchDraging->_snatchTarget->getPosition();
		_vecStartLocation = vCursor;
		return true;
	}

	if (!isMoveing)
	{
		return false;
	}

	Node* nodeDrag = _snatchDraging->_snatchTarget;
	static Vec2 v;
	v = nodeDrag->getParent()->convertToNodeSpace(vCursor);
	v -= nodeDrag->getParent()->convertToNodeSpace(_vecStartLocation);
	v += _vecDrag;
	//  vecCursor = nodeDrag->getPosition() + nodeDrag->getParent()->convertToNodeSpace(t->getDelta());
	switch (_snatchDraging->_dragType)
	{
	case eMouseDrag::V:
		nodeDrag->setPositionY(v.y);
		_snatchDraging->doCross(true);
		break;
	case eMouseDrag::H:
		nodeDrag->setPositionX(v.x);
		_snatchDraging->doCross(true);
		break;
	default:
		nodeDrag->setPosition(v);
		_snatchDraging->doCross(true);
		break;
	}
	return true;
}

void cSnatchListener::doState(cSnatch* snatch, eMouseState state)
{
	snatch->setState(state);
	if (snatch->onState != nullptr)
	{
		snatch->onState(/*snatch->_snatchTarget, */state);
	}
}

void cSnatchListener::doEvent(cSnatch* snatch, bool left, bool up, int keepTimes)
{
	snatch->doEvent(left, up, keepTimes);
	if (snatch->onEvent != nullptr)
	{
		snatch->onEvent(/*snatch->_snatchTarget, */left, up, keepTimes);
	}
}

void cSnatchListener::doClick(cSnatch* snatch)
{
	if (snatch->onClick != nullptr)
	{
		snatch->onClick(/*snatch->_snatchTarget*/);
	}
}

void cSnatchListener::step(float dt, bool lock, bool isMoving, const Vec2& _vCursor, bool isLup, bool isLdown, bool isLkeep, bool isRup)
{
	static auto cursor = cCursor::getInstance();
	static auto input = cInput::getInstance();
	if (cursor->getCursor() != eCursor::Normal)
	{
		if (isRup)
		{
			if (lock)
			{
				input->lockRup();
			}
			cursor->setCursor(eCursor::Normal);
			return;
		}
	}
	bool istop = (_snatchTop != nullptr) && _snatchTop->isEnabled();
	if (isRup)
	{
		if (_snatchTop != nullptr)
		{
			if (lock)
			{
				input->lockRup();
			}
			if (_snatchTop->isEnabled())
			{
 				doEvent(_snatchTop, false, true, 0);
			}
		}
	}
	else if (isLdown)
	{
		_delta = 0;
		_keepTimes = 0;
		_drager._snatchDraging = nullptr;
		if (_snatch != nullptr)
		{
			if (lock)
			{
				input->lockLdown();
			}
			if (_snatch->isEnabled())
			{
				doState(_snatch, eMouseState::Down);
				doEvent(_snatch, true, false, 0);
				_snatch->reorder();
				_snatchDown = _snatch;
				_isKeep = true;
			}
		}
	}
	else if (isLkeep)
	{
		_drager.stepLkeep(_vCursor, _snatchTop, isMoving);
	}
	else if (isLup)
	{
		_isKeep = false;
		if (istop)
		{
			doEvent(_snatchTop, true, true, 0);
		}

		bool isNoDrag = (_drager._snatchDraging == nullptr);
		if (!isNoDrag)
		{
			_drager._snatchDraging = nullptr;
			if (lock)
			{
				input->lockLup();
			}
		}
		else if (_snatchTop != nullptr)
		{
			if (lock)
			{
				input->lockLup();
			}
			if (_snatchTop->isEnabled())
			{
				doState(_snatchTop, eMouseState::Normal);
				if (isNoDrag && _keepTimes == 0)
				{
					doClick(_snatchTop);
				}
			}
		}
	}
	bool isnode = (_snatch != nullptr) && _snatch->isEnabled();
	bool isEvent = isLup || isLdown || isLkeep || isRup;
	if (_snatchTop != _snatch)
	{
		ccu::hideSpriteDesc();
		if (istop)
		{
			doState(_snatchTop, eMouseState::Normal);
		}
		if (isnode && !isEvent)
		{
			doState(_snatch, eMouseState::Cross);
		}
		_snatchTop = _snatch;
	}
	else if (!isEvent && isnode)
	{
		if (_snatch->_wheel > 0 && (_snatch->_dragType == eMouseDrag::V || _snatch->_dragType == eMouseDrag::Both))
		{
			int wheel = input->getWheel();
			if (wheel == 0)
			{
				_snatch->doCross(false);
			}
			else
			{
				_snatch->_snatchTarget->setPositionY(_snatch->_snatchTarget->getPositionY() + wheel * _snatch->_wheel);
				doEvent(_snatch, true, true, 0);
				_snatch->doCross(true);
			}
		}
		else
		{
			_snatch->doCross(false);
		}
	}
	if (_isKeep && isnode && (_delta += dt) > s_keetThreshold && (++_keepTimes) > 0)
	{
		doEvent(_snatch, true, false, _keepTimes);
		if (_snatch->_isKeep2Click)
		{
			doClick(_snatch);
		}
	}
}

void cSnatchListener::step(float dt, bool lock, bool isLup, bool isLdown, bool isLkeep, bool isRup)
{
	static auto input = cInput::getInstance();
	bool isMoving = !input->getMouseDelta().equals(Vec2::ZERO);
	static Vec2 vCursor = input->getMouse();
	if (isMoving)
	{
		vCursor = input->getMouse();
	}
	step(dt, lock, isMoving, vCursor, isLup, isLdown, isLkeep, isRup);
}


//////////////////////////////////////////////////////////////////////////
static bool isSnatched(Node* child, const Vec2& vMouse)
{
	if (child->isVisible() && child->isSnatchNode())
	{
		static Vec2 v;
		v = child->convertToNodeSpace(vMouse);
		if (child->isSnatched(v))
		{
			return true;
		}
	}
	return false;
}

static Node* getSnatch(Node* node, const Vec2& vMouse)
{
	if (!node->isVisible())
	{
		return nullptr;
	}
	
	Node* child;
	Node* n;
	auto& it = node->getChildren().rbegin();
	const auto& itCend = node->getChildren().rend();
	for (; it != itCend; ++it)
	{
		child = *it;

		if (child->getLocalZOrder() >= 0)
		{
			n = getSnatch(child, vMouse);
			if (n != nullptr)
			{
				return n;
			}
		}
		else
		{
			break;
		}
	}

	if (isSnatched(node, vMouse))
	{
		return node;
	}

	for (; it != itCend; ++it)
	{
		n = getSnatch(*it, vMouse);
		if (n != nullptr)
		{
			return n;
		}
	}
	return nullptr;
}


//////////////////////////////////////////////////////////////////////////
cMouse* cMouse::getInstance()
{
	static cMouse* s_mouse = new cMouse();
	return s_mouse;
}


void cMouse::onRemove(cSnatch* node)
{
	if (node == _snatchTop)
	{
		_snatchTop = nullptr;
	}
	if (node == _drager._snatchDraging)
	{
		_drager._snatchDraging = nullptr;
	}
	if (node == _snatchDown)
	{
		_snatchDown = nullptr;
	}
}


void cMouse::step(float dt, Node* nodeRoot)
{
	static auto input = cInput::getInstance();
	bool isMoving = !input->getMouseDelta().equals(Vec2::ZERO);
	static Vec2 vCursor = input->getMouse();
	if (isMoving)
	{
		vCursor = input->getMouse();
		_snatch = dynamic_cast<cSnatch*>(getSnatch(nodeRoot, vCursor));
	}
	cSnatchListener::step(dt, true, isMoving, vCursor, input->isLup(false), input->isLdown(false), input->isLkeep(), input->isRup(false));
}