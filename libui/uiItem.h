#pragma once
#include "uiGrids.h"
#include "uiPet.h"

// 对话
class uiItem : public uiPad
{
public:
	enum class eGrid { none = -1, item, role, pet, zq, fabao };
	enum class eArea { role = (int)eGrid::role, pet = (int)eGrid::pet, zq = (int)eGrid::zq };
	enum class eItem { item = (int)eGrid::item, fabao = (int)eGrid::fabao };
	CREATE_FUNC(uiItem);

protected:
	bool init();

	void update(float delta);

	void doClose();

public:
	// 载入(人物数据)
	void load(const sRole& role, const sItems& items, u64 money);
	void load(sRole& role);

	void loadZuoqi(const sMod& m, sMod::sActs& acts, eIterType iter);
	void loadZuoqi(const sMod& m);
	void loadXiangrui(const sMod& m, sMod::sActs& acts, eIterType iter);
	void loadXiangrui(const sMod& m);
protected:
	void resetPickup(bool show);

	uiGrids* getGrids(eGrid e);
	uiGrid* getGrid(eGrid e, int select);
	uiGrid* getGrid(eGrid e);
	sItems& getItems(eGrid e);
	sItem* getItem(eGrid e);

	void clearSelects(eGrid e);

	// 当前页第一个空位
	int getEmpty(const sItems& items, int page);

	// 捡起交换
	void doSwap(eGrid e, int select, int itemIndex);

	void doGrid(eGrid e, bool left, int select, sItem& item);

	void doUse(int select, sItem& item, bool battle);

	void doHide();
	void doApply(bool item);

	sRole _role;
	sItems _items;
	sItems _itemZs;

	Node* _nodeRole = nullptr;
	Node* _nodePet = nullptr;
	Node* _nodeZuoqi = nullptr;
	// 角色
	cSprite* _spriteHead = nullptr;
	cLabel* _labelMoney = nullptr;
	
	// 宝宝
	// int _petSelect = -1;
	std::vector<cSprite*> _bodies;
	Vec2 _vShadow;
	// 坐骑
	cSprite* _bodyZuoqi = nullptr;
	cSprite* _bodyXiangrui = nullptr;
	cLabel* _labelRiding = nullptr;
	cButton* _buttonRide = nullptr;

	cButton* _buttonRole = nullptr;
	cButton* _buttonPet = nullptr;
	std::array<cButton*, sItem::c60 / uiGrids::c20> _buttonPacks;
	cButton* _buttonFabao = nullptr;
	cButton* _buttonZuoqi = nullptr;
	cButton* _buttonUse = nullptr;
	cButton* _buttonDelete = nullptr;
	cButton* _buttonRoleOnZuoqi = nullptr;
	cButton* _buttonPetOnZuoqi = nullptr;

	// 背包/行囊/法宝
	cSprite* _spriteSelect = nullptr;
	cLabel* _labelHp = nullptr;
	cLabel* _labelMp = nullptr;

	uiGrids* _gridpets = nullptr;
	uiGrids* _gridzqs = nullptr;
	uiGrids* _gridequip6s = nullptr;
	uiGrids* _gridequip3s = nullptr;
	uiGrids* _gridzhuangshis = nullptr;
	uiGrids* _grids = nullptr;
	uiGrids* _gridfabaos = nullptr;

	eItem _eItem = eItem::item;
	eItem _eItemPick = eItem::fabao;
	eArea _eArea = eArea::role;
	eGrid _ePick = eGrid::none;
	eGrid _eGrid = eGrid::none;

	int _pickupIndex = -1;
	uiGrid* _pickupGrid = nullptr;
	cSprite* _spritePickup = nullptr;
public:
	std::function<void(const sRole&)> onRole = nullptr;
	std::function<void(const sItems&)> onItems = nullptr;
};