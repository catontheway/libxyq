#pragma once
#include "_inc.h"

class uiGrid : public Node, public cLabelInner, public cDesc
{
public:
	static uiGrid* create(Node* node, Node* nodeCross = nullptr, Node* nodeSelect = nullptr)
	{
		CREATE(uiGrid, node, nodeCross, nodeSelect);
	}
	static uiGrid* create(ulong uid, ulong ucross = cSp::c0, ulong uselect = cSp::c0);

	static uiGrid* create(const sItem& item);
	static uiGrid* create(const sSki& ski, bool big = true);
	static uiGrid* create(ulong uhead, int lv, const std::string& name);
	static uiGrid* create(ulong uhead, const std::string& name);

	bool load(const sItem& item);
	bool load(const sSki& ski, bool big = true);
protected:
	bool init(Node* node, Node* nodeCross, Node* nodeSelect);
public:
	virtual void setContentSize(const Size& contentSize);
	virtual void setContentSize(float w, float h) { setContentSize(Size(w, h)); }

	void setCrossPosition(float x, float y);
	void setCrossPosition(const Vec2& v) { setCrossPosition(v.x, v.y); }
	void setSelectPosition(float x, float y);
	void setSelectPosition(const Vec2& v) { setSelectPosition(v.x, v.y); }

	void setString(int number);
	void showTarget(bool show);
	void showCross(bool show);
	void showSelect(bool show);
	void switchSelect();

	void setPrice(int price) { _price = price; }
	int getPrice() { return _price; }

	void setHeadForPet(ulong uhead);
	void showEquipBack(bool visivle);
protected:
	int _price = 0;
public:
	ulong _uid = cSp::c0;
protected:
	Node* _node = nullptr;
	Node* _nodeCross = nullptr;
	Node* _nodeSelect = nullptr;

public:
	static const int c50 = 51, c40 = 40, c24 = 24, cPetw = 108, cPeth = 28, cTagPetFight = 1, cTagHead = 2, cTagEquipBack = 3;
};



class uiGrids : public cNode
{
public:
	// 行列为0: 无排列, 1页
	static uiGrids* create(int row = 0, int cel = 0, int iw = 0, int ih = 0) { CREATE(uiGrids, row, cel, iw, ih); }
protected:
	bool init(int row, int cel, int iw, int ih);

public:
	void clear();
	void reset();
	void clearSelect();
	void clearSelect(bool visible);

	void setMutex(bool isMutex) { _isMutex = isMutex; }
	void setSwitchWhenSelectSame(bool isSwitchWhenSelectSame) { _isSwitchWhenSelectSame = isSwitchWhenSelectSame; }

	void load(uiGrid* grid);
	// 逐个加载完毕后
	void load();
	// 载入第几页
	void load(int& page);
	// 前提:>=index的格子无nullptr;
	void remove(int index);

	void addPage();
	void subPage();

	int getSelect() { return _select; }
	void setSelect(int select);


	void setCount(int count) { _count = count; }
	int getCount() { return _count; }
	int getPage() { return _page; }
	int getPageMax() { return _pageMax; }
	int getIw() { return _iw; }
	int getIh() { return _ih; }

	void setGrid(int index, uiGrid* grid);
	uiGrid* getGrid(int index);

	bool isSnatched(const Vec2& v);

	void doEvent(bool left, bool up, int keepTimes);
protected:
	bool isValid(int index);

	int _row, _cel, _iw, _ih, _wh;
	bool _isMutex = true;
	bool _isSwitchWhenSelectSame = false;
	bool _isRank;
	int _cross = -1;
	int _select = -1;
	int _count = 0;
	int _page = 0;
	int _pageMax = 0;

	std::vector<uiGrid*> _grids;
public:
	// 点击物品后的回调(索引, 数量, (左/右)键) (右键不赋值select)
	std::function<void(int, int, bool)> onGrid = nullptr;
	// 点击空白
	std::function<void(bool)> onClick = nullptr;

	static const int c5 = 5, c4 = 4, c20 = c5 * c4;
};