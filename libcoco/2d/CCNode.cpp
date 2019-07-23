#include "CCNode.h"

#include <algorithm>
#include <string>
#include <regex>

#include "../base/CCDirector.h"
#include "../base/CCScheduler.h"
#include "CCActionManager.h"
#include "CCScene.h"
#include "CCComponentContainer.h"
#include "CCComponent.h"
#include "../math/TransformUtils.h"


NS_CC_BEGIN

// FIXME:: Yes, nodes might have a sort problem once every 30 days if the game runs at 60 FPS and each frame sprites are reordered.
// unsigned int Node::s_globalOrderOfArrival = 0;
// MARK: Constructor, Destructor, Init


static const float _rotationX(0.0f);
static const float _rotationY(0.0f);
static const float _rotationZ_X(0.0f);
static const float _rotationZ_Y(0.0f);
static const float _scaleX(1.0f);
static const float _scaleY(1.0f);
static const float _scaleZ(1.0f);
static const float _positionZ(0.0f);
static const bool _usingNormalizedPosition(false);
static const bool _normalizedPositionDirty(false);
static const float _skewX(0.0f);
static const float _skewY(0.0f);
static const Quaternion _rotationQuat;

Node::Node()
: _contentSize(Size::ZERO)
, _contentSizeDirty(true)
, _transformDirty(true)
, _inverseDirty(true)
, _additionalTransform(nullptr)
, _additionalTransformDirty(false)
, _transformUpdated(true)
// children (lazy allocs)
// lazy alloc
, _localZOrderAndArrival(0)
, _localZOrder(0)
, _globalZOrder(0)
, _parent(nullptr)
// "whole screen" objects. like Scenes and Layers, should set _ignoreAnchorPointForPosition to true
, _tag(Node::INVALID_TAG)
, _name("")
, _hashOfName(0)
// userData is always inited as nil
, _userData(nullptr)
, _userObject(nullptr)
//, _glProgramState(nullptr)
, _running(false)
, _visible(true)
, _ignoreAnchorPointForPosition(false)
, _reorderChildDirty(false)

, _componentContainer(nullptr)
, _realOpacity(255)
, _realColor(Color3B::WHITE)
{
    // set default scheduler and actionManager
    _director = Director::getInstance();
    _actionManager = _director->getActionManager();
    _actionManager->retain();
    _scheduler = _director->getScheduler();
    _scheduler->retain();

    _transform = _inverse = Mat4::IDENTITY;
}

Node * Node::create()
{
    Node * ret = new (std::nothrow) Node();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

Node::~Node()
{
    CCLOGINFO( "deallocing Node: %p - tag: %i", this, _tag );
    
    CC_SAFE_RELEASE_NULL(_userObject);
    

    for (auto& child : _children)
    {
        child->_parent = nullptr;
    }
    removeAllComponents();
    CC_SAFE_DELETE(_componentContainer);
    stopAllActions();
    unscheduleAllCallbacks();
    CC_SAFE_RELEASE_NULL(_actionManager);
    CC_SAFE_RELEASE_NULL(_scheduler);
 
    CCASSERT(!_running, "Node still marked as running on node destruction! Was base class onExit() called in derived class onExit() implementations?");

    delete[] _additionalTransform;
}

bool Node::init()
{
    return true;
}

void Node::cleanup()
{
    this->stopAllActions();
    // timers
    this->unscheduleAllCallbacks();
    
    for( const auto &child: _children)
        child->cleanup();
}

void Node::setLocalZOrder(int z)
{
    if (getLocalZOrder() == z)
        return;
    
    _setLocalZOrder(z);
    if (_parent)
    {
        _parent->reorderChild(this, z);
    }
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually
void Node::_setLocalZOrder(int z)
{
    _localZOrderAndArrival = (static_cast<std::int64_t>(z) << 32) | (_localZOrderAndArrival & 0xffffffff);
    _localZOrder = z;
}

void Node::updateOrderOfArrival()
{
	static unsigned int s_globalOrderOfArrival = 0;
    _localZOrderAndArrival = (_localZOrderAndArrival & 0xffffffff00000000) | (++s_globalOrderOfArrival);
	////////////////////////////////////////////////////////////////////////// ÀÇ±¦
	_globalOrderOfArrival = s_globalOrderOfArrival;
	////////////////////////////////////////////////////////////////////////// ÀÇ±¦
}

void Node::setGlobalZOrder(float globalZOrder)
{
    if (_globalZOrder != globalZOrder)
    {
        _globalZOrder = globalZOrder;
//        _eventDispatcher->setDirtyForNode(this);
    }
}


/// position getter
const Vec2& Node::getPosition() const
{
    return _position;
}

/// position setter
void Node::setPosition(const Vec2& position)
{
    setPosition(position.x, position.y);
}

void Node::getPosition(float* x, float* y) const
{
    *x = _position.x;
    *y = _position.y;
}

void Node::setPosition(float x, float y)
{
    if (_position.x == x && _position.y == y)
        return;
    
    _position.x = x;
    _position.y = y;
    
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

float Node::getPositionX() const
{
    return _position.x;
}

void Node::setPositionX(float x)
{
    setPosition(x, _position.y);
}

float Node::getPositionY() const
{
    return  _position.y;
}

void Node::setPositionY(float y)
{
    setPosition(_position.x, y);
}


ssize_t Node::getChildrenCount() const
{
    return _children.size();
}

/// isVisible getter
bool Node::isVisible() const
{
    return _visible;
}

/// isVisible setter
void Node::setVisible(bool visible)
{
    if(visible != _visible)
    {
        _visible = visible;
        if(_visible)
            _transformUpdated = _transformDirty = _inverseDirty = true;
    }
}

const Vec2& Node::getAnchorPointInPoints() const
{
    return _anchorPointInPoints;
}

/// anchorPoint getter
const Vec2& Node::getAnchorPoint() const
{
    return _anchorPoint;
}

void Node::setAnchorPoint(const Vec2& point)
{
    if (! point.equals(_anchorPoint))
    {
        _anchorPoint = point;
        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
        _transformUpdated = _transformDirty = _inverseDirty = true;
    }
}

/// contentSize getter
const Size& Node::getContentSize() const
{
    return _contentSize;
}

void Node::setContentSize(const Size & size)
{
    if (! size.equals(_contentSize))
    {
        _contentSize = size;

        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
        _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
    }
}

// isRunning getter
bool Node::isRunning() const
{
    return _running;
}


void Node::onEnter()
{
	if (_componentContainer && !_componentContainer->isEmpty())
	{
		_componentContainer->onEnter();
	}
	for (const auto &child : _children)
	{
		child->onEnter();
	}

	this->resume();

	_running = true;

}

void Node::onExit()
{
	if (_componentContainer && !_componentContainer->isEmpty())
	{
		_componentContainer->onExit();
	}
	this->pause();

	_running = false;

	for (const auto &child : _children)
	{
		child->onExit();
	}
}



/// parent setter
void Node::setParent(Node * parent)
{
    _parent = parent;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

/// isRelativeAnchorPoint getter
bool Node::isIgnoreAnchorPointForPosition() const
{
    return _ignoreAnchorPointForPosition;
}

/// isRelativeAnchorPoint setter
void Node::setIgnoreAnchorPointForPosition(bool newValue)
{
    if (newValue != _ignoreAnchorPointForPosition) 
    {
        _ignoreAnchorPointForPosition = newValue;
        _transformUpdated = _transformDirty = _inverseDirty = true;
    }
}

/// tag getter
int Node::getTag() const
{
    return _tag;
}

/// tag setter
void Node::setTag(int tag)
{
    _tag = tag ;
}

const std::string& Node::getName() const
{
    return _name;
}

void Node::setName(const std::string& name)
{
    _name = name;
    std::hash<std::string> h;
    _hashOfName = h(name);
}

/// userData setter
void Node::setUserData(void *userData)
{
    _userData = userData;
}

void Node::setUserObject(Ref* userObject)
{
    CC_SAFE_RETAIN(userObject);
    CC_SAFE_RELEASE(_userObject);
    _userObject = userObject;
}


Scene* Node::getScene() const
{
    if (!_parent)
        return nullptr;
    
    auto sceneNode = _parent;
    while (sceneNode->_parent)
    {
        sceneNode = sceneNode->_parent;
    }

    return dynamic_cast<Scene*>(sceneNode);
}

Rect Node::getBoundingBox() const
{
    Rect rect(0, 0, _contentSize.width, _contentSize.height);
    return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

// MARK: Children logic

// lazy allocs
void Node::childrenAlloc()
{
    _children.reserve(4);
}

Node* Node::getChildByTag(int tag) const
{
    CCASSERT(tag != Node::INVALID_TAG, "Invalid tag");

    for (const auto child : _children)
    {
        if(child && child->_tag == tag)
            return child;
    }
    return nullptr;
}

Node* Node::getChildByName(const std::string& name) const
{
    CCASSERT(!name.empty(), "Invalid name");
    
    std::hash<std::string> h;
    size_t hash = h(name);
    
    for (const auto& child : _children)
    {
        // Different strings may have the same hash code, but can use it to compare first for speed
        if(child->_hashOfName == hash && child->_name.compare(name) == 0)
            return child;
    }
    return nullptr;
}


void Node::addChild(Node *child, int localZOrder, int tag)
{    
    CCASSERT( child != nullptr, "Argument must be non-nil");
    CCASSERT( child->_parent == nullptr, "child already added. It can't be added again");

    addChildHelper(child, localZOrder, tag, "", true);
}

void Node::addChild(Node* child, int localZOrder, const std::string &name)
{
    CCASSERT(child != nullptr, "Argument must be non-nil");
    CCASSERT(child->_parent == nullptr, "child already added. It can't be added again");
    
    addChildHelper(child, localZOrder, INVALID_TAG, name, false);
}

void Node::addChildHelper(Node* child, int localZOrder, int tag, const std::string &name, bool setTag)
{
    auto assertNotSelfChild
        ( [ this, child ]() -> bool
          {
              for ( Node* parent( getParent() ); parent != nullptr;
                    parent = parent->getParent() )
                  if ( parent == child )
                      return false;
              
              return true;
          } );
    (void)assertNotSelfChild;
    
    CCASSERT( assertNotSelfChild(),
              "A node cannot be the child of his own children" );
    
    if (_children.empty())
    {
        this->childrenAlloc();
    }
    
    this->insertChild(child, localZOrder);
    
    if (setTag)
        child->setTag(tag);
    else
        child->setName(name);
    
    child->setParent(this);

    child->updateOrderOfArrival();

    if( _running )
    {
        child->onEnter();
    }
}

void Node::addChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    this->addChild(child, zOrder, child->_name);
}

void Node::addChild(Node *child)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    this->addChild(child, child->getLocalZOrder(), child->_name);
}

void Node::removeFromParent()
{
    this->removeFromParentAndCleanup(true);
}

void Node::removeFromParentAndCleanup(bool cleanup)
{
    if (_parent != nullptr)
    {
        _parent->removeChild(this,cleanup);
    } 
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void Node::removeChild(Node* child, bool cleanup /* = true */)
{
    // explicit nil handling
    if (_children.empty())
    {
        return;
    }

    ssize_t index = _children.getIndex(child);
    if( index != CC_INVALID_INDEX )
        this->detachChild( child, index, cleanup );
}

void Node::removeChildByTag(int tag, bool cleanup/* = true */)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");

    Node *child = this->getChildByTag(tag);

    if (child == nullptr)
    {
        CCLOG("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeChild(child, cleanup);
    }
}

void Node::removeChildByName(const std::string &name, bool cleanup)
{
    CCASSERT(!name.empty(), "Invalid name");
    
    Node *child = this->getChildByName(name);
    
    if (child == nullptr)
    {
        CCLOG("cocos2d: removeChildByName(name = %s): child not found!", name.c_str());
    }
    else
    {
        this->removeChild(child, cleanup);
    }
}

void Node::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}

void Node::removeAllChildrenWithCleanup(bool cleanup)
{
    // not using detachChild improves speed here
    for (const auto& child : _children)
    {
        if(_running)
        {
            child->onExit();
        }
        if (cleanup)
        {
            child->cleanup();
        }
        child->setParent(nullptr);
    }
    
    _children.clear();
}

void Node::detachChild(Node *child, ssize_t childIndex, bool doCleanup)
{
    if (_running)
    {
        child->onExit();
    }
    // If you don't do cleanup, the child's actions will not get removed and the
    // its scheduledSelectors_ dict will not get released!
    if (doCleanup)
    {
        child->cleanup();
    }
    
    child->setParent(nullptr);

    _children.erase(childIndex);
}


// helper used by reorderChild & add
void Node::insertChild(Node* child, int z)
{
    _transformUpdated = true;
    _reorderChildDirty = true;
    _children.pushBack(child);
    child->_setLocalZOrder(z);
}

void Node::reorderChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Child must be non-nil");
    _reorderChildDirty = true;
    child->updateOrderOfArrival();
    child->_setLocalZOrder(zOrder);
}

void Node::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        sortNodes(_children);
        _reorderChildDirty = false;
    }
}

// MARK: draw / visit

void Node::draw()
{
    draw(_modelViewTransform, true);
}

void Node::draw(const Mat4 & transform, const uint32_t& flags)
{
}


void Node::visit()
{
    auto& parentTransform = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    visit(parentTransform, true);
}

uint32_t Node::processParentFlags(const Mat4& parentTransform, const uint32_t& parentFlags)
{
    uint32_t flags = parentFlags;
    flags |= (_transformUpdated ? FLAGS_TRANSFORM_DIRTY : 0);
    flags |= (_contentSizeDirty ? FLAGS_CONTENT_SIZE_DIRTY : 0);
    

    if(flags & FLAGS_DIRTY_MASK)
        _modelViewTransform = this->transform(parentTransform);
    
    _transformUpdated = false;
    _contentSizeDirty = false;

    return flags;
}

void Node::visit(const Mat4& parentTransform, const uint32_t& parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    bool visibleByCamera = true;

//    int i = 0;

    if(!_children.empty())
    {
        sortAllChildren();
#if 0
		// for (i = _children.size() - 1; i >= 0; --i)
		auto& it = _children.rbegin();
		for (; it != _children.rend(); ++it)
		{
			// auto node = _children.at(i);
			if (*it == nullptr)
			{
				continue;
			}
			if ((*it)->getLocalZOrder() >= 0)
			{
				(*it)->visit(_modelViewTransform, flags);
			}
			else
			{
				break;
			}
		}

		// self draw
		if (visibleByCamera)
		{
			this->draw(_modelViewTransform, flags);
		}


		// draw children zOrder < 0
		// for (; i >= 0; --i)
		for (;it != _children.rend(); ++it)
		{
			// auto node = _children.at(i);
			if ((*it) == nullptr)
			{
				continue;
			}
			(*it)->visit(_modelViewTransform, flags);
		}
#else

		Node* node;
		auto& it = _children.cbegin();
		const auto& itCend = _children.cend();
        // draw children zOrder < 0
        // for(auto size = _children.size(); i < size; ++i)
		for (;it != itCend; ++it)
        {
			node = (*it); //_children.at(i);

            if (node && node->_localZOrder < 0)
                node->visit(_modelViewTransform, flags);
            else
                break;
        }
        // self draw
		if (visibleByCamera)
		{
			this->draw(_modelViewTransform, flags);
		}

        for(/*auto it=_children.cbegin()+i, itCend = _children.cend()*/; it != itCend; ++it)
            (*it)->visit(_modelViewTransform, flags);
#endif
    }
    else if (visibleByCamera)
    {
        this->draw(_modelViewTransform, flags);
    }

    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    // FIX ME: Why need to set _orderOfArrival to 0??
    // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
    // reset for next frame
    // _orderOfArrival = 0;
}


Mat4 Node::transform(const Mat4& parentTransform)
{
    return parentTransform * this->getNodeToParentTransform();
}


void Node::setActionManager(ActionManager* actionManager)
{
    if( actionManager != _actionManager )
    {
        this->stopAllActions();
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }
}

// MARK: actions

Action * Node::runAction(Action* action)
{
    CCASSERT( action != nullptr, "Argument must be non-nil");
    _actionManager->addAction(action, this, !_running);
    return action;
}

void Node::stopAllActions()
{
    _actionManager->removeAllActionsFromTarget(this);
}

void Node::stopAction(Action* action)
{
    _actionManager->removeAction(action);
}

void Node::stopActionByTag(int tag)
{
    CCASSERT( tag != Action::INVALID_TAG, "Invalid tag");
    _actionManager->removeActionByTag(tag, this);
}

void Node::stopAllActionsByTag(int tag)
{
    CCASSERT( tag != Action::INVALID_TAG, "Invalid tag");
    _actionManager->removeAllActionsByTag(tag, this);
}

void Node::stopActionsByFlags(unsigned int flags)
{
    if (flags > 0)
    {
        _actionManager->removeActionsByFlags(flags, this);
    }
}

Action * Node::getActionByTag(int tag)
{
    CCASSERT( tag != Action::INVALID_TAG, "Invalid tag");
    return _actionManager->getActionByTag(tag, this);
}

ssize_t Node::getNumberOfRunningActions() const
{
    return _actionManager->getNumberOfRunningActionsInTarget(this);
}

ssize_t Node::getNumberOfRunningActionsByTag(int tag) const
{
    return _actionManager->getNumberOfRunningActionsInTargetByTag(this, tag);
}


// MARK: Callbacks

void Node::setScheduler(Scheduler* scheduler)
{
    if( scheduler != _scheduler )
    {
        this->unscheduleAllCallbacks();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

bool Node::isScheduled(SEL_SCHEDULE selector)
{
    return _scheduler->isScheduled(selector, this);
}

bool Node::isScheduled(const std::string &key)
{
    return _scheduler->isScheduled(key, this);
}

void Node::scheduleUpdate()
{
    scheduleUpdateWithPriority(0);
}

void Node::scheduleUpdateWithPriority(int priority)
{
    _scheduler->scheduleUpdate(this, priority, !_running);
}


void Node::unscheduleUpdate()
{
    _scheduler->unscheduleUpdate(this);
}

void Node::schedule(SEL_SCHEDULE selector)
{
    this->schedule(selector, 0.0f, CC_REPEAT_FOREVER, 0.0f);
}

void Node::schedule(SEL_SCHEDULE selector, float interval)
{
    this->schedule(selector, interval, CC_REPEAT_FOREVER, 0.0f);
}

void Node::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    CCASSERT( selector, "Argument must be non-nil");
    CCASSERT( interval >=0, "Argument must be positive");

    _scheduler->schedule(selector, this, interval , repeat, delay, !_running);
}

void Node::schedule(const std::function<void(float)> &callback, const std::string &key)
{
    _scheduler->schedule(callback, this, 0, !_running, key);
}

void Node::schedule(const std::function<void(float)> &callback, float interval, const std::string &key)
{
    _scheduler->schedule(callback, this, interval, !_running, key);
}

void Node::schedule(const std::function<void(float)>& callback, float interval, unsigned int repeat, float delay, const std::string &key)
{
    _scheduler->schedule(callback, this, interval, repeat, delay, !_running, key);
}

void Node::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}

void Node::scheduleOnce(const std::function<void(float)> &callback, float delay, const std::string &key)
{
    _scheduler->schedule(callback, this, 0, 0, delay, !_running, key);
}

void Node::unschedule(SEL_SCHEDULE selector)
{
    // explicit null handling
    if (selector == nullptr)
        return;
    
    _scheduler->unschedule(selector, this);
}

void Node::unschedule(const std::string &key)
{
    _scheduler->unschedule(key, this);
}

void Node::unscheduleAllCallbacks()
{
    _scheduler->unscheduleAllForTarget(this);
}

void Node::resume()
{
    _scheduler->resumeTarget(this);
    _actionManager->resumeTarget(this);
}

void Node::pause()
{
    _scheduler->pauseTarget(this);
    _actionManager->pauseTarget(this);
}


// override me
void Node::update(float fDelta)
{
    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->visit(fDelta);
    }
}

// MARK: coordinates

AffineTransform Node::getNodeToParentAffineTransform() const
{
    AffineTransform ret;
    GLToCGAffine(getNodeToParentTransform().m, &ret);

    return ret;
}


Mat4 Node::getNodeToParentTransform(Node* ancestor) const
{
    Mat4 t(this->getNodeToParentTransform());

    for (Node *p = _parent;  p != nullptr && p != ancestor ; p = p->getParent())
    {
        t = p->getNodeToParentTransform() * t;
    }

    return t;
}

AffineTransform Node::getNodeToParentAffineTransform(Node* ancestor) const
{
    AffineTransform t(this->getNodeToParentAffineTransform());

    for (Node *p = _parent; p != nullptr && p != ancestor; p = p->getParent())
        t = AffineTransformConcat(t, p->getNodeToParentAffineTransform());

    return t;
}
const Mat4& Node::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        // Translate values
        float x = _position.x;
        float y = _position.y;
        float z = _positionZ;
        
        if (_ignoreAnchorPointForPosition)
        {
            x += _anchorPointInPoints.x;
            y += _anchorPointInPoints.y;
        }
        
        bool needsSkewMatrix = ( _skewX || _skewY );

        // Build Transform Matrix = translation * rotation * scale
        Mat4 translation;
        //move to anchor point first, then rotate
        Mat4::createTranslation(x, y, z, &translation);
        
        Mat4::createRotation(_rotationQuat, &_transform);
        
        if (_rotationZ_X != _rotationZ_Y)
        {
            // Rotation values
            // Change rotation code to handle X and Y
            // If we skew with the exact same value for both x and y then we're simply just rotating
            float radiansX = -CC_DEGREES_TO_RADIANS(_rotationZ_X);
            float radiansY = -CC_DEGREES_TO_RADIANS(_rotationZ_Y);
            float cx = cosf(radiansX);
            float sx = sinf(radiansX);
            float cy = cosf(radiansY);
            float sy = sinf(radiansY);
            
            float m0 = _transform.m[0], m1 = _transform.m[1], m4 = _transform.m[4], m5 = _transform.m[5], m8 = _transform.m[8], m9 = _transform.m[9];
            _transform.m[0] = cy * m0 - sx * m1, _transform.m[4] = cy * m4 - sx * m5, _transform.m[8] = cy * m8 - sx * m9;
            _transform.m[1] = sy * m0 + cx * m1, _transform.m[5] = sy * m4 + cx * m5, _transform.m[9] = sy * m8 + cx * m9;
        }
        _transform = translation * _transform;

        if (_scaleX != 1.f)
        {
            _transform.m[0] *= _scaleX, _transform.m[1] *= _scaleX, _transform.m[2] *= _scaleX;
        }
        if (_scaleY != 1.f)
        {
            _transform.m[4] *= _scaleY, _transform.m[5] *= _scaleY, _transform.m[6] *= _scaleY;
        }
        if (_scaleZ != 1.f)
        {
            _transform.m[8] *= _scaleZ, _transform.m[9] *= _scaleZ, _transform.m[10] *= _scaleZ;
        }
        
        // FIXME:: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            float skewMatArray[16] =
            {
                1, (float)tanf(CC_DEGREES_TO_RADIANS(_skewY)), 0, 0,
                (float)tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1, 0, 0,
                0,  0,  1, 0,
                0,  0,  0, 1
            };
            Mat4 skewMatrix(skewMatArray);
            
            _transform = _transform * skewMatrix;
        }

        // adjust anchor point
        if (!_anchorPointInPoints.isZero())
        {
            // FIXME:: Argh, Mat4 needs a "translate" method.
            // FIXME:: Although this is faster than multiplying a vec4 * mat4
            _transform.m[12] += _transform.m[0] * -_anchorPointInPoints.x + _transform.m[4] * -_anchorPointInPoints.y;
            _transform.m[13] += _transform.m[1] * -_anchorPointInPoints.x + _transform.m[5] * -_anchorPointInPoints.y;
            _transform.m[14] += _transform.m[2] * -_anchorPointInPoints.x + _transform.m[6] * -_anchorPointInPoints.y;
        }
    }

    if (_additionalTransform)
    {
        // This is needed to support both Node::setNodeToParentTransform() and Node::setAdditionalTransform()
        // at the same time. The scenario is this:
        // at some point setNodeToParentTransform() is called.
        // and later setAdditionalTransform() is called every time. And since _transform
        // is being overwritten everyframe, _additionalTransform[1] is used to have a copy
        // of the last "_transform without _additionalTransform"
        if (_transformDirty)
            _additionalTransform[1] = _transform;

        if (_transformUpdated)
            _transform = _additionalTransform[1] * _additionalTransform[0];
    }

    _transformDirty = _additionalTransformDirty = false;

    return _transform;
}

void Node::setNodeToParentTransform(const Mat4& transform)
{
    _transform = transform;
    _transformDirty = false;
    _transformUpdated = true;

    if (_additionalTransform)
        // _additionalTransform[1] has a copy of lastest transform
        _additionalTransform[1] = transform;
}

void Node::setAdditionalTransform(const AffineTransform& additionalTransform)
{
    Mat4 tmp;
    CGAffineToGL(additionalTransform, tmp.m);
    setAdditionalTransform(&tmp);
}

void Node::setAdditionalTransform(const Mat4* additionalTransform)
{
    if (additionalTransform == nullptr)
    {
        delete[] _additionalTransform;
        _additionalTransform = nullptr;
    }
    else
    {
        if (!_additionalTransform) {
            _additionalTransform = new Mat4[2];

            // _additionalTransform[1] is used as a backup for _transform
            _additionalTransform[1] = _transform;
        }

        _additionalTransform[0] = *additionalTransform;
    }
    _transformUpdated = _additionalTransformDirty = _inverseDirty = true;
}

void Node::setAdditionalTransform(const Mat4& additionalTransform)
{
    setAdditionalTransform(&additionalTransform);
}

AffineTransform Node::getParentToNodeAffineTransform() const
{
    AffineTransform ret;

    GLToCGAffine(getParentToNodeTransform().m,&ret);
    return ret;
}

const Mat4& Node::getParentToNodeTransform() const
{
    if ( _inverseDirty )
    {
        _inverse = getNodeToParentTransform().getInversed();
        _inverseDirty = false;
    }

    return _inverse;
}


AffineTransform Node::getNodeToWorldAffineTransform() const
{
    return this->getNodeToParentAffineTransform(nullptr);
}

Mat4 Node::getNodeToWorldTransform() const
{
    return this->getNodeToParentTransform(nullptr);
}

AffineTransform Node::getWorldToNodeAffineTransform() const
{
    return AffineTransformInvert(this->getNodeToWorldAffineTransform());
}

Mat4 Node::getWorldToNodeTransform() const
{
    return getNodeToWorldTransform().getInversed();
}


Vec2 Node::convertToNodeSpace(const Vec2& worldPoint) const
{
    Mat4 tmp = getWorldToNodeTransform();
    Vec3 vec3(worldPoint.x, worldPoint.y, 0);
    Vec3 ret;
    tmp.transformPoint(vec3,&ret);
    return Vec2(ret.x, ret.y);
}

Vec2 Node::convertToWorldSpace(const Vec2& nodePoint) const
{
    Mat4 tmp = getNodeToWorldTransform();
    Vec3 vec3(nodePoint.x, nodePoint.y, 0);
    Vec3 ret;
    tmp.transformPoint(vec3,&ret);
    return Vec2(ret.x, ret.y);

}

Vec2 Node::convertToNodeSpaceAR(const Vec2& worldPoint) const
{
    Vec2 nodePoint(convertToNodeSpace(worldPoint));
    return nodePoint - _anchorPointInPoints;
}

Vec2 Node::convertToWorldSpaceAR(const Vec2& nodePoint) const
{
    return convertToWorldSpace(nodePoint + _anchorPointInPoints);
}

Vec2 Node::convertToWindowSpace(const Vec2& nodePoint) const
{
    Vec2 worldPoint(this->convertToWorldSpace(nodePoint));
    return _director->convertToUI(worldPoint);
}
// 
// // convenience methods which take a Touch instead of Vec2
// Vec2 Node::convertTouchToNodeSpace(Touch *touch) const
// {
//     return this->convertToNodeSpace(touch->getLocation());
// }
// 
// Vec2 Node::convertTouchToNodeSpaceAR(Touch *touch) const
// {
//     Vec2 point = touch->getLocation();
//     return this->convertToNodeSpaceAR(point);
// }

void Node::updateTransform()
{
    // Recursively iterate over children
    for( const auto &child: _children)
        child->updateTransform();
}

Component* Node::getComponent(const std::string& name)
{
    if (_componentContainer)
        return _componentContainer->get(name);
    
    return nullptr;
}

bool Node::addComponent(Component *component)
{
    // lazy alloc
    if (!_componentContainer)
        _componentContainer = new (std::nothrow) ComponentContainer(this);
    
    // should enable schedule update, then all components can receive this call back
    scheduleUpdate();
    
    return _componentContainer->add(component);
}

bool Node::removeComponent(const std::string& name)
{
    if (_componentContainer)
        return _componentContainer->remove(name);
    
    return false;
}

bool Node::removeComponent(Component *component)
{
    if (_componentContainer)
    {
        return _componentContainer->remove(component);
    }
    
    return false;
}

void Node::removeAllComponents()
{
    if (_componentContainer)
        _componentContainer->removeAll();
}
// MARK: Opacity and Color

GLubyte Node::getOpacity(void) const
{
    return _realOpacity;
}

void Node::setOpacity(GLubyte opacity)
{
    _realOpacity = opacity;
}


const Color3B& Node::getColor(void) const
{
    return _realColor;
}

void Node::setColor(const Color3B& color)
{
    _realColor = color;
}

NS_CC_END
