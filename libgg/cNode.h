#pragma once
#include "_gge42_dev18.h"
#include "../libcc/_cpp.h"
#include "../libcoco/_create.h"
#include "Geometry.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
class cNode;
class cAutoReleasePool
{
public:
	static cAutoReleasePool* getInstance();

	void addNode(cNode* node);

	void clear();

private:
	std::vector<cNode*> _nodes;
};

//////////////////////////////////////////////////////////////////////////
struct s888
{
	uchar r, g, b;
	s888();
	s888(uchar _r, uchar _g, uchar _b);

	static const s888 WHITE;
	static const s888 YELLOW;
	static const s888 BLUE;
	static const s888 GREEN;
	static const s888 RED;
	static const s888 MAGENTA;
	static const s888 BLACK;
	static const s888 ORANGE;
	static const s888 GRAY;
};



//////////////////////////////////////////////////////////////////////////
class cNode : private gge::ggeRenderNode
{
public:
	static const int INVALID_TAG = -1;
	cNode();
	virtual ~cNode();
	CREATE_FUNC(cNode);
protected:
	virtual bool init();
public:
	void retain();
	
	void release();

	void getReferenceCount();

	void autorelease();

protected:
	void OnUpdate(float dt, const gge::ggeMatrix4 &parentTransform, bool bUpdateTransform);

	void OnRender(const gge::ggeMatrix4 &parentTransform);

public:
	static cNode* getRoot();
	static const Vec2& getMouse();
	void doUpdate(float dt) { gge::ggeRenderNode::Update(dt); }
	void doRender() { gge::ggeRenderNode::Render(); }
public:
	void setRender(bool render);

	virtual void onTransform(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y);

	virtual void onRender(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y);

	void setSnatch(bool snatch);

	void setSnatch(const Vec2& vMouse);

	void setSnatch(const std::function<bool(int, int)>& func);

	bool isSnatch();

	static void getSnatch(cNode* node, std::vector<cNode*>& sortNodes);

	cNode* getSnatch(const Vec2& vMouse);

	static cNode* getSnatch();

public:
	void setLocalZOrder(int localZOrder);

	int getLocalZOrder() const;

	void updateOrderOfArrival();

	int getOrderOfArrival()const;

public:
	void setScale(float scale);

	float getScale()const;

	void setPosition(const Vec2& position);

	void setPosition(float x, float y);

	Vec2 getPosition();

	float getPositionX() const;

	float getPositionY() const;

	void setAnchorPoint(const Vec2& anchorPoint);

	const Vec2& getAnchorPoint() const;

	const Vec2& getAnchorPointInPoints() const;

	virtual void setContentSize(const Size& contentSize);

	virtual void setContentSize(float w, float h);

	const Size& getContentSize() const;

	virtual void setVisible(bool visible);

	bool isVisible() const;

	bool isVisibleRecur() const;

	void setRotation(float rotation);

	float getRotation() const;

public:
	virtual void addChild(cNode* child);
	virtual void addChild(cNode* child, int localZOrder);
	virtual void addChild(cNode* child, int localZOrder, int tag);

	cNode* getChildByTag(int tag) const;

	int getChildrenCount() const;

	void removeFromParent();

	void removeChild(cNode* child);

	void removeChildByTag(int tag);

	 void removeAllChildren();

public:
	int getTag() const;

	void setTag(int tag);

	void* getUserData();

	const void* getUserData() const;

	void setUserData(void *userData);

public:
	void scheduleUpdate(void);

    void unscheduleUpdate(void);

	virtual void update(float delta);

public:
	const Vec2& convertToNodeSpace(const Vec2& worldPoint) const;

	const Vec2& convertToWorldSpace(const Vec2& nodePoint) const;

public:
	uchar getOpacity() const;

	void setOpacity(uchar opacity);

	virtual const s888& getColor() const;

	virtual void setColor(const s888& color);

	virtual void setColor(uchar r, uchar g, uchar b);

	virtual void onColor(uchar opacity, uchar r, uchar g, uchar b);

protected:
	Vec2 _anchorPointInPoints;
	Vec2 _anchorPoint;        

	Size _contentSize;

	uchar _realOpacity;
	s888 _realColor;

protected:
	bool _isSnatch;
	bool _isTransformed;
	bool _isRender;
	bool _isScheduled;
	std::function<bool(int, int)> _snatchFunc;

	gge::ggeVector _v1, _v2, _v3, _v4, _vAp;
};