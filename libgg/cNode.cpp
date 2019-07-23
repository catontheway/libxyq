#include "cNode.h"

cAutoReleasePool* cAutoReleasePool::getInstance()
{
	static cAutoReleasePool* s_autoReleasePool = nullptr;
	if(s_autoReleasePool == nullptr)
	{
		s_autoReleasePool = new cAutoReleasePool();
	}
	return s_autoReleasePool;
}



void cAutoReleasePool::addNode(cNode* node)
{
	_nodes.push_back(node);
}

void cAutoReleasePool::clear()
{
	std::vector<cNode*> releasings;
	releasings.swap(_nodes);
	for (const auto &node : releasings)
	{
		node->release();
	}
}

////////////////////////////////////////////////////////////////////////// s888
s888::s888()
{
	r = g = b = 0xFF;
}

s888::s888(uchar _r, uchar _g, uchar _b):r(_r), g(_g), b(_b)
{

}

const s888 s888::WHITE  (255, 255, 255);
const s888 s888::YELLOW (255, 255,   0);
const s888 s888::GREEN  (  0, 255,   0);
const s888 s888::BLUE   (  0,   0, 255);
const s888 s888::RED    (255,   0,   0);
const s888 s888::MAGENTA(255,   0, 255);
const s888 s888::BLACK  (  0,   0,   0);
const s888 s888::ORANGE (255, 127,   0);
const s888 s888::GRAY   (166, 166, 166);

////////////////////////////////////////////////////////////////////////// cNode
static cNode* s_nodeSnatch = nullptr;

cNode::cNode() : gge::ggeRenderNode(), _isSnatch(false), _isTransformed(false), _isRender(false), _isScheduled(false),_realColor(s888::WHITE),_realOpacity(0xFF),_snatchFunc(nullptr)
{
	setTag(INVALID_TAG);
}

cNode::~cNode()
{

}

bool cNode::init()
{
	return true;
}

void cNode::retain()
{
	AddRef();
}

void cNode::release()
{
	Release();
}

void cNode::getReferenceCount()
{
	GetRefCount();
}

void cNode::autorelease()
{
	cAutoReleasePool::getInstance()->addNode(this);
}

//////////////////////////////////////////////////////////////////////////

void cNode::OnUpdate(float dt, const gge::ggeMatrix4 &parentTransform, bool bUpdateTransform)
{
	gge::ggeRenderNode::OnUpdate(dt,parentTransform, bUpdateTransform);
	if(bUpdateTransform)//层次不触发
	{
		_isTransformed = true;
		gge::ggeRenderNode* node;
		for(int i = GetChildCount() - 1; i >= 0; --i)
		{
			node = GetChild(i);
			node->SetPositionX(node->GetPositionX());
		}
	}
	if(_isScheduled)
	{
		update(dt);
	}
}

void cNode::OnRender(const gge::ggeMatrix4 &parentTransform)
{
	gge::ggeRenderNode::OnRender(parentTransform);
	if(_isRender)
	{
//		static gge::ggeVector _v1, _v2, _v3, _v4, _vAp;
		//层次不触发
		if(_isTransformed)
		{
			_isTransformed = false;
			_v1.x = _v3.x = -_anchorPointInPoints.x;
			_v1.y = _v2.y = -_anchorPointInPoints.y;
			_v2.x = _v4.x = _contentSize.width - _anchorPointInPoints.x;
			_v3.y = _v4.y = _contentSize.height - _anchorPointInPoints.y;
			_vAp.x = _vAp.y = 0;
			ConvertToWorldPosition(_v1);
			ConvertToWorldPosition(_v2);
			ConvertToWorldPosition(_v3);
			ConvertToWorldPosition(_v4);
			ConvertToWorldPosition(_vAp);
			onTransform(_v1.x, _v1.y, _v2.x, _v2.y, _v3.x, _v3.y, _v4.x, _v4.y, _vAp.x, _vAp.y);
		}
		onRender(_v1.x, _v1.y, _v2.x, _v2.y, _v3.x, _v3.y, _v4.x, _v4.y, _vAp.x, _vAp.y);
	}
}


void cNode::setRender(bool render)
{
	_isRender = render;
}



void cNode::onTransform(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y)
{

}


void cNode::onRender(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y)
{

}


void cNode::setSnatch(bool snatch)
{
	_isSnatch = snatch;
}

void cNode::setSnatch(const Vec2& vMouse)
{
	s_nodeSnatch = getSnatch(vMouse);
}


void cNode::setSnatch(const std::function<bool(int, int)>& func)
{
	_snatchFunc = func;
}

bool cNode::isSnatch()
{
	return _isSnatch;
}


void cNode::getSnatch(cNode* node, std::vector<cNode*>& sortNodes)
{
	if(!node->isVisible())
	{
		return;
	}
	cNode* child;
	std::vector<cNode*> children;
	for(int k = node->GetChildCount() - 1; k >= 0; --k)
	{
		child = (cNode*)node->GetChild(k);
		if(child->isVisible() && child->isSnatch())
		{
			children.push_back(child);
		}
	}

	std::sort(children.begin(), children.end(), [](const cNode* n1, const cNode* n2)
	{
		if(n1->getLocalZOrder() == n2->getLocalZOrder())
		{
			return n1->getOrderOfArrival() < n2->getOrderOfArrival();
		}
		return n1->getLocalZOrder() < n2->getLocalZOrder();
	});

	int k = 0;
	for(int size = children.size(); k < size; ++k)
	{
		child = children.at(k);
		if(child->getLocalZOrder() < 0)
		{
			getSnatch(child, sortNodes);
		}
		else
		{
			break;
		}
	}

	if (node->isSnatch())
	{
		sortNodes.push_back(node);
	}

	for(auto it = children.cbegin()+ k, itCend = children.cend(); it != itCend; ++it)
	{
		getSnatch(*it, sortNodes);
	}
}



cNode* cNode::getSnatch(const Vec2& vMouse)
{
	static Vec2 v;
	static cNode* node;
	std::vector<cNode*> sortNodes;
	getSnatch(this, sortNodes);
	forr(sortNodes, k)
	{
		node = sortNodes.at(k);
		v = node->convertToNodeSpace(vMouse);
		if(Rect(Vec2::ZERO, node->getContentSize()).containsPoint(v))
		{
			if(node->_snatchFunc == nullptr || node->_snatchFunc(v.x, v.y))
			{
				return node;
			}
		}
	}
	return nullptr;
}



cNode* cNode::getSnatch()
{
	return s_nodeSnatch;
}


//////////////////////////////////////////////////////////////////////////
void cNode::setLocalZOrder(int localZOrder)
{
	SetZOrder(localZOrder);
}

int cNode::getLocalZOrder() const
{
	return GetZOrder();
}

void cNode::updateOrderOfArrival()
{
	SetZOrder(GetZOrder());
}


int cNode::getOrderOfArrival()const
{
	return m_localOrder;
}

//////////////////////////////////////////////////////////////////////////
void cNode::setScale(float scale)
{
	SetScale(scale, scale);
}

float cNode::getScale() const
{
	return GetScaleX();
}

void cNode::setPosition(const Vec2& position)
{
	SetPosition(position.x, position.y);
}

void cNode::setPosition(float x, float y)
{
	SetPosition(x, y);
}

Vec2 cNode::getPosition()
{
	return Vec2(GetPositionX(), GetPositionY());
}

float cNode::getPositionX() const
{
	return GetPositionX();
}

float cNode::getPositionY() const
{
	return GetPositionY();
}

void cNode::setAnchorPoint(const Vec2& anchorPoint)
{
	_anchorPoint = anchorPoint;
	_anchorPointInPoints.x = _contentSize.width * _anchorPoint.x;
	_anchorPointInPoints.y = _contentSize.height * _anchorPoint.y;
	TransformDirty();
}

const Vec2& cNode::getAnchorPoint() const
{
	return _anchorPoint;
}

const Vec2& cNode::getAnchorPointInPoints() const
{
	return _anchorPointInPoints;
}

void cNode::setContentSize(const Size& contentSize)
{
	_contentSize = contentSize;
	_anchorPointInPoints.x = _contentSize.width * _anchorPoint.x;
	_anchorPointInPoints.y = _contentSize.height * _anchorPoint.y;
	TransformDirty();
}

void cNode::setContentSize(float w, float h)
{
	setContentSize(Size(w, h));
}

const Size& cNode::getContentSize() const
{
	return _contentSize;
}

void cNode::setVisible(bool visible)
{
	return SetVisible(visible);
}

bool cNode::isVisible() const
{
	return IsVisible();
}

bool cNode::isVisibleRecur() const
{
	if(GetParent() == nullptr || !IsVisible())
	{
		return false;
	}
	auto node = GetParent()->GetParent();
	do 
	{
		if (!node->IsVisible())
		{
			return false;
		}
		node = node->GetParent();
	} 
	while (true);
	return true;
}

void cNode::setRotation(float rotation)
{
	SetRotation(gge::ToRadian(rotation));
}

float cNode::getRotation() const
{
	return gge::ToDegree(GetRotation());
}

//////////////////////////////////////////////////////////////////////////
void cNode::addChild(cNode* child)
{
	AddChild(child);
}

void cNode::addChild(cNode* child, int localZOrder)
{
	child->setLocalZOrder(localZOrder);
	addChild(child);
}

void cNode::addChild(cNode* child, int localZOrder, int tag)
{
	child->setLocalZOrder(localZOrder);
	child->setTag(tag);
	addChild(child);
}

cNode* cNode::getChildByTag(int tag) const
{
	return (cNode*)FindChild(tag);
	return dynamic_cast<cNode*>(GetChild(tag));
}

int cNode::getChildrenCount() const
{
	return GetChildCount();
}

void cNode::removeFromParent()
{
	RemoveFromParent();
}

void cNode::removeChild(cNode* child)
{
	RemoveChild(child);
}

void cNode::removeChildByTag(int tag)
{
	auto node = getChildByTag(tag);
	if(node)
	{
		removeChild(node);
	}
}

void cNode::removeAllChildren()
{
	RemoveAllChild();
}

//////////////////////////////////////////////////////////////////////////
int cNode::getTag() const
{
	return GetID();
}

void cNode::setTag(int tag)
{
	SetID(tag);
}

void* cNode::getUserData()
{
	return GetUserData();
}

const void* cNode::getUserData() const
{
	return GetUserData();
}

void cNode::setUserData(void *userData)
{
	SetUserData(userData);
}


//////////////////////////////////////////////////////////////////////////
void cNode::scheduleUpdate(void)
{
	_isScheduled = true;
}

void cNode::unscheduleUpdate(void)
{
	_isScheduled = false;
}

void cNode::update(float delta)
{

}

const Vec2& cNode::convertToNodeSpace(const Vec2& worldPoint) const
{
	static Vec2 v2;
	static gge::ggeVector v;
	v.x = worldPoint.x;
	v.y = worldPoint.y;
	gge::ggeRenderNode::ConvertToNodePosition(v);
	v2.x = v.x + _anchorPointInPoints.x;
	v2.y = v.y + _anchorPointInPoints.y;
	return v2;
}

const Vec2& cNode::convertToWorldSpace(const Vec2& nodePoint) const
{
	static Vec2 v2;
	static gge::ggeVector v;
	v.x = nodePoint.x - _anchorPointInPoints.x;
	v.y = nodePoint.y - _anchorPointInPoints.y;
	gge::ggeRenderNode::ConvertToWorldPosition(v);
	v2.x = v.x;
	v2.y = v.y;
	return v2;
}

uchar cNode::getOpacity() const
{
	return _realOpacity;
}

void cNode::setOpacity(uchar opacity)
{
	_realOpacity = opacity;
}

const s888& cNode::getColor() const
{
	return _realColor;
}

void cNode::setColor(const s888& color)
{
	_realColor = color;
	onColor(_realOpacity, _realColor.r, _realColor.g, _realColor.b);
}

void cNode::setColor(uchar r, uchar g, uchar b)
{
	_realColor.r = r;
	_realColor.g = g;
	_realColor.b = b;
	onColor(_realOpacity, _realColor.r, _realColor.g, _realColor.b);
}



void cNode::onColor(uchar opacity, uchar r, uchar g, uchar b)
{

}


//////////////////////////////////////////////////////////////////////////

