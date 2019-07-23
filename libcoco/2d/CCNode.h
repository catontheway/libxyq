#ifndef __CCNODE_H__
#define __CCNODE_H__

#include <cstdint>
#include "../base/ccMacros.h"
#include "../base/CCVector.h"
#include "../base/ccTypes.h"
#include "../math/CCAffineTransform.h"
#include "../math/CCMath.h"

NS_CC_BEGIN

class Action;
class Scheduler;
class ActionManager;
class Component;
class ComponentContainer;
class Scene;
class Director;

class CC_DLL Node : public Ref
{
public:
    /** Default tag used for all the nodes */
    static const int INVALID_TAG = -1;

    enum {
        FLAGS_TRANSFORM_DIRTY = (1 << 0),
        FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),
        FLAGS_RENDER_AS_3D = (1 << 3),

        FLAGS_DIRTY_MASK = (FLAGS_TRANSFORM_DIRTY | FLAGS_CONTENT_SIZE_DIRTY),
    };

    static Node * create();

 
    virtual void setLocalZOrder(int localZOrder);

    virtual void _setLocalZOrder(int z);

    /** !!! ONLY FOR INTERNAL USE
    * Sets the arrival order when this node has a same ZOrder with other children.
    *
    * A node which called addChild subsequently will take a larger arrival order,
    * If two children have the same Z order, the child with larger arrival order will be drawn later.
    *
    * @warning This method is used internally for localZOrder sorting, don't change this manually
    *
    * @param orderOfArrival   The arrival order.
    */
    void updateOrderOfArrival();


    virtual int getLocalZOrder() const { return _localZOrder; }

    virtual void setGlobalZOrder(float globalZOrder);

    virtual float getGlobalZOrder() const { return _globalZOrder; }

    virtual void setPosition(const Vec2 &position);

    virtual const Vec2& getPosition() const;

    virtual void setPosition(float x, float y);

    virtual void getPosition(float* x, float* y) const;

    virtual void  setPositionX(float x);
 
    virtual float getPositionX(void) const;

    virtual void  setPositionY(float y);

    virtual float getPositionY(void) const;

    virtual void setAnchorPoint(const Vec2& anchorPoint);
 
    virtual const Vec2& getAnchorPoint() const;

    virtual const Vec2& getAnchorPointInPoints() const;

	virtual void setContentSize(const Size& contentSize);
	virtual void setContentSize(float w, float h){ setContentSize(Size(w, h)); }
 
    virtual const Size& getContentSize() const;

    virtual void setVisible(bool visible);
 
    virtual bool isVisible() const;

    virtual void setIgnoreAnchorPointForPosition(bool ignore);

    virtual bool isIgnoreAnchorPointForPosition() const;

    virtual void addChild(Node * child);

    virtual void addChild(Node * child, int localZOrder);
 
     virtual void addChild(Node* child, int localZOrder, int tag);

    virtual void addChild(Node* child, int localZOrder, const std::string &name);
 
    virtual Node * getChildByTag(int tag) const;
 
    template <typename T>
    T getChildByTag(int tag) const { return static_cast<T>(getChildByTag(tag)); }

    virtual Node* getChildByName(const std::string& name) const;
 
    template <typename T>
    T getChildByName(const std::string& name) const { return static_cast<T>(getChildByName(name)); }

    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
 
    virtual ssize_t getChildrenCount() const;

    virtual void setParent(Node* parent);

    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }

    virtual void removeFromParent();
 
    virtual void removeFromParentAndCleanup(bool cleanup);

    virtual void removeChild(Node* child, bool cleanup = true);

     virtual void removeChildByTag(int tag, bool cleanup = true);
  
    virtual void removeChildByName(const std::string &name, bool cleanup = true);

    virtual void removeAllChildren();

    virtual void removeAllChildrenWithCleanup(bool cleanup);

    virtual void reorderChild(Node * child, int localZOrder);

    /**
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame.
     */
    virtual void sortAllChildren();

    /**
    * Sorts helper function
    *
    */
    template<typename _T> inline
    static void sortNodes(cocos2d::Vector<_T*>& nodes)
    {
        static_assert(std::is_base_of<Node, _T>::value, "Node::sortNodes: Only accept derived of Node!");
#if CC_64BITS
        std::sort(std::begin(nodes), std::end(nodes), [](_T* n1, _T* n2) {
            return (n1->_localZOrderAndArrival < n2->_localZOrderAndArrival);
        });
#else
        std::stable_sort(std::begin(nodes), std::end(nodes), [](_T* n1, _T* n2) {
			////////////////////////////////////////////////////////////////////////// ÀÇ±¦
			if (n1->_localZOrder == n2->_localZOrder)
			{
				return n1->_globalOrderOfArrival < n2->_globalOrderOfArrival;
			}
			////////////////////////////////////////////////////////////////////////// ÀÇ±¦
            return n1->_localZOrder < n2->_localZOrder;
        });
#endif
    }

     virtual int getTag() const;

     virtual void setTag(int tag);
 
    virtual const std::string& getName() const;
 
    virtual void setName(const std::string& name);

 
    virtual void* getUserData() { return _userData; }
 
    virtual const void* getUserData() const { return _userData; }

    virtual void setUserData(void *userData);


    virtual Ref* getUserObject() { return _userObject; }
  
    virtual const Ref* getUserObject() const { return _userObject; }

    virtual void setUserObject(Ref *userObject);


    /**
     * Returns whether or not the node is "running".
     *
     * If the node is running it will accept event callbacks like onEnter(), onExit(), update().
     *
     * @return Whether or not the node is running.
     */
    virtual bool isRunning() const;

	virtual void onEnter();

	virtual void onExit();
    /**
     * Stops all running actions and schedulers
     */
    virtual void cleanup();

    /**
     * Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     * 
     * @param renderer A given renderer.
     * @param transform A transform matrix.
     * @param flags Renderer flag.
     */

    virtual void draw(const Mat4& transform, const uint32_t& flags);
    virtual void draw() final;

    /**
     * Visits this node's children and draw them recursively.
     *
     * @param renderer A given renderer.
     * @param parentTransform A transform matrix.
     * @param parentFlags Renderer flag.
     */
	virtual void visit(const Mat4& parentTransform, const uint32_t& parentFlags);
    virtual void visit() final;


    virtual Scene* getScene() const;

    virtual Rect getBoundingBox() const;

 
    virtual void setActionManager(ActionManager* actionManager);

    virtual ActionManager* getActionManager() { return _actionManager; }
    virtual const ActionManager* getActionManager() const { return _actionManager; }

    virtual Action* runAction(Action* action);

    void stopAllActions();

    void stopAction(Action* action);

    void stopActionByTag(int tag);
    
    void stopAllActionsByTag(int tag);

    void stopActionsByFlags(unsigned int flags);

    Action* getActionByTag(int tag);

    ssize_t getNumberOfRunningActions() const;

    ssize_t getNumberOfRunningActionsByTag(int tag) const;

    virtual void setScheduler(Scheduler* scheduler);

    virtual Scheduler* getScheduler() { return _scheduler; }
    virtual const Scheduler* getScheduler() const { return _scheduler; }


    bool isScheduled(SEL_SCHEDULE selector);

    bool isScheduled(const std::string &key);

    void scheduleUpdate(void);

    void scheduleUpdateWithPriority(int priority);

    void unscheduleUpdate(void);

    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    void schedule(SEL_SCHEDULE selector, float interval);

    void scheduleOnce(SEL_SCHEDULE selector, float delay);

    void scheduleOnce(const std::function<void(float)>& callback, float delay, const std::string &key);

    void schedule(SEL_SCHEDULE selector);

    void schedule(const std::function<void(float)>& callback, const std::string &key);

    void schedule(const std::function<void(float)>& callback, float interval, const std::string &key);

    void schedule(const std::function<void(float)>& callback, float interval, unsigned int repeat, float delay, const std::string &key);

    void unschedule(SEL_SCHEDULE selector);

    void unschedule(const std::string &key);

    /**
     * Unschedule all scheduled selectors and lambda functions: custom selectors, and the 'update' selector and lambda functions.
     * Actions are not affected by this method.
     * @lua NA
     */
    void unscheduleAllCallbacks();

//    CC_DEPRECATED_ATTRIBUTE void unscheduleAllSelectors() { unscheduleAllCallbacks(); }

    /**
     * Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter.
     */
    virtual void resume(void);
    /**
     * Pauses all scheduled selectors, actions and event listeners.
     * This method is called internally by onExit.
     */
    virtual void pause(void);


    virtual void update(float delta);

    /// @} end of Scheduler and Timer

    /// @{
    /// @name Transformations

    /**
     * Calls children's updateTransform() method recursively.
     *
     * This method is moved from Sprite, so it's no longer specific to Sprite.
     * As the result, you apply SpriteBatchNode's optimization on your customed Node.
     * e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
     */
    virtual void updateTransform();

    /**
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     *
     * @return The transformation matrix.
     */
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /**
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     * Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see getNodeToWorldTransform
     *
     * @param ancestor The parent's node pointer.
     * @since v3.7
     * @return The transformation matrix.
     */
    virtual Mat4 getNodeToParentTransform(Node* ancestor) const;

    /**
     * Returns the affine transform matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     *
     * Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see getNodeToWorldAffineTransform
     *
     * @param ancestor The parent's node pointer.
     * @since v3.7
     * @return The affine transformation matrix.
     */
    virtual AffineTransform getNodeToParentAffineTransform(Node* ancestor) const;

    /** 
     * Sets the transformation matrix manually.
     *
     * @param transform A given transformation matrix.
     */
    virtual void setNodeToParentTransform(const Mat4& transform);

    /** @deprecated use getNodeToParentTransform() instead */
//    CC_DEPRECATED_ATTRIBUTE virtual AffineTransform nodeToParentTransform() const { return getNodeToParentAffineTransform(); }

    /**
     * Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     *
     * @return The transformation matrix.
     */
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
//    CC_DEPRECATED_ATTRIBUTE virtual AffineTransform parentToNodeTransform() const { return getParentToNodeAffineTransform(); }

    /**
     * Returns the world affine transform matrix. The matrix is in Pixels.
     *
     * @return transformation matrix, in pixels.
     */
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
//    CC_DEPRECATED_ATTRIBUTE virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldAffineTransform(); }

    /**
     * Returns the inverse world affine transform matrix. The matrix is in Pixels.
     *
     * @return The transformation matrix.
     */
    virtual Mat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;

    /** @deprecated Use getWorldToNodeTransform() instead */
//    CC_DEPRECATED_ATTRIBUTE virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeAffineTransform(); }

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters

    /**
     * Converts a Vec2 to node (local) space coordinates. The result is in Points.
     *
     * @param worldPoint A given coordinate.
     * @return A point in node (local) space coordinates.
     */
    Vec2 convertToNodeSpace(const Vec2& worldPoint) const;

    /**
     * Converts a Vec2 to world space coordinates. The result is in Points.
     *
     * @param nodePoint A given coordinate.
     * @return A point in world space coordinates.
     */
    Vec2 convertToWorldSpace(const Vec2& nodePoint) const;

    /**
     * Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     *
     * @param worldPoint A given coordinate.
     * @return A point in node (local) space coordinates, anchor relative.
     */
    Vec2 convertToNodeSpaceAR(const Vec2& worldPoint) const;

    /**
     * Converts a local Vec2 to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     *
     * @param nodePoint A given coordinate.
     * @return A point in world space coordinates, anchor relative.
     */
    Vec2 convertToWorldSpaceAR(const Vec2& nodePoint) const;

    /**
     * convenience methods which take a Touch instead of Vec2.
     *
     * @param touch A given touch.
     * @return A point in world space coordinates.
     */
//    Vec2 convertTouchToNodeSpace(Touch * touch) const;

    /**
     * converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     *
     * @param touch A given touch.
     * @return A point in world space coordinates, anchor relative.
     */
//    Vec2 convertTouchToNodeSpaceAR(Touch * touch) const;

    /**
     *  Sets an additional transform matrix to the node.
     *
     *  In order to remove it, call it again with the argument `nullptr`.
     *
     * @note The additional transform will be concatenated at the end of getNodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     *
     * @param additionalTransform An additional transform matrix.
     */
    void setAdditionalTransform(const Mat4* additionalTransform);
    void setAdditionalTransform(const Mat4& additionalTransform);
    void setAdditionalTransform(const AffineTransform& additionalTransform);


    Component* getComponent(const std::string& name);
    virtual bool addComponent(Component *component);
    virtual bool removeComponent(const std::string& name);
    virtual bool removeComponent(Component *component);
    virtual void removeAllComponents();
    virtual GLubyte getOpacity() const;

    virtual void setOpacity(GLubyte opacity);

    virtual const Color3B& getColor() const;
 
    virtual void setColor(const Color3B& color);
	

CC_CONSTRUCTOR_ACCESS:
    // Nodes should be created using create();
    Node();
    virtual ~Node();

    virtual bool init();

protected:
    /// lazy allocs
    void childrenAlloc(void);
    
    /// helper that reorder a child
    void insertChild(Node* child, int z);

    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(Node *child, ssize_t index, bool doCleanup);

    /// Convert cocos2d coordinates to UI windows coordinate.
    Vec2 convertToWindowSpace(const Vec2& nodePoint) const;

    Mat4 transform(const Mat4 &parentTransform);
    virtual uint32_t processParentFlags(const Mat4& parentTransform, const uint32_t& parentFlags);

private:
    void addChildHelper(Node* child, int localZOrder, int tag, const std::string &name, bool setTag);
    
protected:
    Vec2 _position;                 ///< position of the node


    Vec2 _anchorPointInPoints;      ///< anchor point in points
    Vec2 _anchorPoint;              ///< anchor point normalized (NOT in points)

    Size _contentSize;              ///< untransformed size of the node
    bool _contentSizeDirty;         ///< whether or not the contentSize is dirty

    Mat4 _modelViewTransform;       ///< ModelView transform of the Node.

    // "cache" variables are allowed to be mutable
    mutable Mat4 _transform;        ///< transform
    mutable bool _transformDirty;   ///< transform dirty flag
    mutable Mat4 _inverse;          ///< inverse transform
    mutable bool _inverseDirty;     ///< inverse transform dirty flag
    mutable Mat4* _additionalTransform; ///< two transforms needed by additional transforms
    mutable bool _additionalTransformDirty; ///< transform dirty ?
    bool _transformUpdated;         ///< Whether or not the Transform object was updated since the last frame

    std::int64_t _localZOrderAndArrival; /// cache, for 64bits compress optimize.
    int _localZOrder; /// < Local order (relative to its siblings) used to sort the node

	////////////////////////////////////////////////////////////////////////// ÀÇ±¦
private:
	bool _isSnatchNode = false;
protected:
	unsigned int _globalOrderOfArrival = 0;
public:
	void setSnatchNode(bool isSnatchNode) { _isSnatchNode = isSnatchNode; }
	bool isSnatchNode() { return _isSnatchNode; }
	virtual bool isSnatched(const Vec2& v) { return Rect(Vec2::ZERO, _contentSize).containsPoint(v); }
protected:
	////////////////////////////////////////////////////////////////////////// ÀÇ±¦
    float _globalZOrder;            ///< Global order used to sort the node

//    static unsigned int s_globalOrderOfArrival;

    Vector<Node*> _children;        ///< array of children nodes
    Node *_parent;                  ///< weak reference to parent node
    Director* _director;            //cached director pointer to improve rendering performance
    int _tag;                       ///< a tag. Can be any number you assigned just to identify this node
    
    std::string _name;              ///<a string label, an user defined string to identify this node
    size_t _hashOfName;             ///<hash value of _name, used for speed in getChildByName

    void *_userData;                ///< A user assigned void pointer, Can be point to any cpp object
    Ref *_userObject;               ///< A user assigned Object

//    GLProgramState *_glProgramState; ///< OpenGL Program State

    Scheduler *_scheduler;          ///< scheduler used to schedule timers and updates

    ActionManager *_actionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions

//    EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events

    bool _running;                  ///< is running

    bool _visible;                  ///< is this node visible

    bool _ignoreAnchorPointForPosition; ///< true if the Anchor Vec2 will be (0,0) when you position the Node, false otherwise.
                                          ///< Used by Layer and Scene.

    bool _reorderChildDirty;          ///< children order dirty flag


    ComponentContainer *_componentContainer;        ///< Dictionary of components
    // opacity controls
    GLubyte     _realOpacity;
    Color3B     _realColor;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Node);
};

NS_CC_END

#endif // __CCNODE_H__
