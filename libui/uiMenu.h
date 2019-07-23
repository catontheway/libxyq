#pragma once
#include "_inc.h"

class uiMenu : public cNode
{
public:
	CREATE_FUNC(uiMenu);
	bool init();

	void setBattle(bool battle);

	void update(float delta);
protected:
	cButton* _buttonAtk;
	cButton* _buttonPack;
	cButton* _buttonGive;
	cButton* _buttonTrade;
	cButton* _buttonTeam;
	cButton* _buttonPet;
	cButton* _buttonJob;
	cButton* _buttonBp;
	cButton* _buttonAcce;
	cButton* _buttonMsg;
	cButton* _buttonSys;

public:
	enum class eOperator { W, E, T, O, P, Q, C, F, S };
	std::function<void(eOperator)> onOperate = nullptr;
};