#pragma once
#include "_inc.h"

class cObjectCommen
{
protected:
	bool init(Node* parent, bool ui);

	void setState(eMouseState state);

public:
	void setDirection(int direction);
	int getDirection() const { return _direction; };

	void say(const std::string& text, bool toast);

	void setObjName(const std::string& name);
	void setNameColor(const s565& color);

	void setAppellation(const std::string& appellation);
	void setAppellationColor(const s565& color);

	void showName(bool show);

	void showShadow(bool show);

	int getHeight(bool only1st);

	void setSnatchPixel(bool isSnatchPixel);

	void setHeight(int& h, int& h1);

	bool step();

	void setFrame(int frame);

	virtual void setAction(eAct e, bool reframe = true);
protected:
	bool _isui;
	int _direction, _hBody = 0, _h1 = 0, _hSay = 0;
	Node* _say = nullptr;
	cLabel* _labelName = nullptr;
	cLabel* _labelAppellation = nullptr;
	s565 _colorName, _colorAppellation;
	cSprite* _spriteShadow = nullptr;

	Node* _nodeBody = nullptr;
	std::map<eAct, cSprite*> _bodies;
	cSprite* _body = nullptr;
};

class cObject : public cNode,  public cObjectCommen
{
public:
	static cObject* create(bool ui = false) { CREATE(cObject, ui); }
protected:
	~cObject();
	bool init(bool ui);

	bool isSnatched(const Vec2& v);

	void setState(eMouseState state);

public:
	void load(const sSps& stands, const sSps& walks = {});

	void load(const sMod::sActs& acts, bool onlyStand = true);

	void load(const sMod& mod, bool onlyStand = true);

	void load(ulong uid, const std::string& mapname);

	void loadFoot(ulong ufoot);

	void loadFoot2(ulong ufoot2) { _ufoot2 = ufoot2; }

	void loadLeaderTop(ulong top);

	void stand();

	void walk(const Vec2& vTo);

	void step(float delta, bool steped, bool walked);
protected:
	bool _isStand = true;
	ulong _ufoot2 = cSp::c0;
	float _deltaFoot = 0;
	cSprite* _foot = nullptr;
	cSprite* _leaderTop = nullptr;
};


