#include "cNode.h"
#include "cMouse.h"

cNode::~cNode()
{

}

void cNode::setSnatchNode(bool isSnatchNode)
{
	Node::setSnatchNode(isSnatchNode);
	_snatchTarget = isSnatchNode ? this : nullptr;
}


void cNode::setState(eMouseState state)
{
	cDesc::showDesc(state == eMouseState::Cross && _descs.isValid());
}

bool cNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}


void cNode::setOpacity(GLubyte opacity)
{
	if (_realOpacity != opacity)
	{
		_isDraw = true;
	}
	Node::setOpacity(opacity);
}


void cNode::sortAllChildren()
{
	if (_reorderChildDirty)
	{
		sortNodes(_children);
		_reorderChildDirty = false;
		_isDraw = true;
	}
}

void cNode::draw(const Mat4& transform, const uint32_t& flags)
{
	_flags = flags;
	if (_flags)
	{
		setRectWorld();
	}
	if (isScreen())
	{
		cDraw::getInstance()->push(this, flags);
	}
}

void cNode::setRectWorld()
{
	static Mat4 t;
	t = _transform;
	for (Node *p = _parent; p != nullptr; p = p->getParent())
	{
		t = p->getNodeToParentTransform() * t;
	}
	static Vec3 ret;
	t.transformPoint(Vec3::ZERO, &ret);
	_rectWorld.origin.x = _wx = ret.x;
	_rectWorld.origin.y = _wy = ret.y;
	_rectWorld.size = _contentSize;
}

const Rect& cNode::getRectWorld() const
{
	return _rectWorld;
}

bool cNode::isScreen() const
{
	return !(_wx > cc::vsSize().width || _wy > cc::vsSize().height || _rectWorld.getMaxX() < 0 || _rectWorld.getMaxY() < 0);
}
