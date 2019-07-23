#pragma once
#include "cNode.h"

class cLayer : public cNode
{
public:
	class cNodeInner : public cNode
	{
	public:
		CREATE_FUNC(cNodeInner);
		void setRectWorld();
		virtual bool isSnatched(const Vec2& v);
		virtual void doCross(bool draging);
		
	};
	~cLayer();
	static cLayer* create(const std::function<cNodeInner*()>& innerCreater = nullptr) { CREATE(cLayer, innerCreater); }
protected:
	bool init(const std::function<cNodeInner*()>& innerCreater);
public:
	virtual void setContentSize(const Size& contentSize);
	virtual void setContentSize(float w, float h);
	virtual void setInnerSize(const Size& contentSize);
	virtual void setInnerSize(float w, float h);
	// localZOrder >= 0
	virtual void addChild(Node* child, int localZOrder, int tag);
	// localZOrder >= 0
	virtual void addChild(Node* child, int localZOrder);
	// localZOrder >= 0
	virtual void addChild(Node* child);
protected:
	void addChildInner(Node* child);
public:
	virtual void setDragType(const eMouseDrag& e);

	cNode* getInner() { return _nodeInner; }
	void setBounceable(bool isBounceable) { _isBounceable = isBounceable; }
protected:
	void doDraging();
	Vec2 trimPosition(Vec2 v, float tolerance);

//	void draw(const uint32_t& flags);
//	void update(float delta);
	cCanvas* _canvas = nullptr;
	cNodeInner* _nodeInner = nullptr;
	bool _isBounceable = true;
	bool _isScheduled = false;
};
