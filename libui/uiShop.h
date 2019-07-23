#pragma once
#include "uiPad.h"
#include "uiGrids.h"

class uiShop : public uiPad
{
public:
	CREATE_FUNC(uiShop);

protected:
	virtual bool init();

public:
	void load(const sItems& items, u64 money);
	void load(const std::vector<eMod>& pets, u64 money);
protected:
	void loadPage();

	void load();

	bool _ispet;
	sItems _items;
	std::vector<eMod> _pets;
	u64 _money;


	cLabel* _labelPage = nullptr;
	cLabel* _labelPrice = nullptr;
	cLabelNO* _labelCount = nullptr;
	cLabel* _labelTotal = nullptr;
	cLabel* _labelMoney = nullptr;

	uiGrids* _grids = nullptr;

	cButton* _buttonBuy = nullptr;

public:
//	std::function<void(eMod)> onRight = nullptr;
//	std::function<bool(const sItem&, int)> onBuy = nullptr;
	std::function<bool(eMod, int)> onPet = nullptr;
};