#pragma once
#include "_inc.h"

enum class eMouseState { Normal, Cross, Down, Disabled };
enum class eMouseDrag { None, H, V, Both };
class cSnatch
{
protected:
	~cSnatch();
public:
	void setEnabled(bool isEnabled);
	bool isEnabled()const { return _isEnabled; }

	void setDragType(const eMouseDrag& e) { _dragType = e; }

	void setKeep2Click(bool toClick) { _isKeep2Click = toClick; }

	void setWheel(float wheel) { _wheel = wheel; }

	virtual void setState(eMouseState state) {}

	// 能拖住不会触发keep
	virtual void doEvent(bool left, bool up, int keepTimes) {}

	virtual void doCross(bool draging) {}

	virtual void reorder() {}
protected:
	bool _isEnabled = true;
	eMouseDrag _dragType = eMouseDrag::None;
	bool _isKeep2Click = false;
	float _wheel = 0;
public:
	std::function<void(eMouseState)> onState = nullptr;
	std::function<void(bool, bool, int)> onEvent = nullptr;
	typedef std::function<void()> sClick;
	sClick onClick = nullptr;

	friend class cSnatchDrager;
	friend class cSnatchListener;

	Node* _snatchTarget = nullptr;
};

class cSnatchDrager
{
public:
	bool stepLkeep(const Vec2& vCursor, cSnatch* snatchTop, bool isMoveing);

	Vec2 _vecDrag;
	Vec2 _vecStartLocation;
	Vec2 _vecStartCursor;

	cSnatch* _snatchDraging = nullptr;
};


class cSnatchListener
{
public:
	static void doState(cSnatch* snatch, eMouseState state);
	static void doEvent(cSnatch* snatch, bool left, bool up, int keepTimes);
	static void doClick(cSnatch* snatch);
	void setTop(cSnatch* top) { _snatchTop = top; }
	const cSnatch* getTop() const { return _snatchTop; }
	const cSnatch* getDown() const { return _snatchDown; }

	void step(float dt, bool lock, bool isMoving, const Vec2& _vCursor, bool isLup, bool isLdown, bool isLkeep, bool isRup);
	void step(float dt, bool lock, bool isLup, bool isLdown, bool isLkeep, bool isRup);
protected:
	cSnatchDrager _drager;
	cSnatch* _snatch = nullptr;
	cSnatch* _snatchTop = nullptr;
	cSnatch* _snatchDown = nullptr;

	float _delta;
	int _keepTimes;
	bool _isKeep = false;

};


class cMouse : public cSnatchListener
{
public:
	static cMouse* getInstance();

	void onRemove(cSnatch* node);

	void step(float dt, Node* nodeRoot);
};