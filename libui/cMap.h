#pragma once
#include "cObject.h"

class cMap;
class cMapMask : public cNode
{
public:
	CREATE_FUNC(cMapMask);

	void setMap(cMap* map) { _map = map; }

	bool init();

	void draw(cCanvas* canvas, const uint32_t& flags);

protected:
	cMap* _map = nullptr;
};

class cMap : public cNode
{
public:
	CREATE_FUNC(cMap);
	cMap();
	~cMap();
	
	bool init();

	void clearNpcsAndTrans();
	void clearPaths();

	bool load(const std::string& mapname);
	void load(const txtMap::sTransmit& transmit);
	void load(const txtMap::sNpc& npc, bool rand, bool smap);
	void load(int mapid, eMapType e);
	void load(int x20, int y20);

	int getMapId(){ return _cache.mapid; }
	void setMusic(const std::string& music);
	ulong getMusic() const { return _music; }
	void loadMusic();

	// 小地图 笛卡尔
	Vec2 toPosition(int x20, int y20);
	void toPosition(const Vec2& vMap, int& x20, int& y20);
	// 这是小地图的笛卡尔20
	bool isObstacle(int x20, int y20);

	Node* getHero();

	Node* getNpcLayer() { return _nodeNpc; }
	Node* getTeamLayer() { return _nodeTeam; }
	Node* getTempLayer() { return _nodeTemp; }
protected:
	void draw(cCanvas* canvas, const uint32_t& flags);

	void doEvent(bool left, bool up, int keepTimes);
public:
	void doSearch(const Vec2& v);
protected:
	void update(float delta);

public:
	void setMoveSpeed(int speed);
protected:
	ulong _music = cSp::c0;
	sMapCache _cache;
	std::vector<std::vector<Node*>> _nodeNpcs;
	Node* _nodeTemp = nullptr;
	Node* _nodeNpc = nullptr;
	Node* _nodeTeam = nullptr;

	std::vector<Vec2> _paths;
	int _moveSpeed;
	bool _isMoving = false;
	int _nw, _nh;
public:
	static const int cHeroTag = 0, cTeam5 = 5;
	std::function<void(const Vec2&)> onMoving = nullptr;
	std::function<void(const std::vector<Vec2>&, int, int)> onPaths = nullptr;
	std::function<void(ulong)> onMusic = nullptr;

};