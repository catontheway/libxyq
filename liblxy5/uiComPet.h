#pragma once
#include "_uiinc.h"



class uiComPet : public cInterfaceFather
{
	virtual bool initShow();
	virtual bool Init();
	virtual bool Move(int x, int y);
	virtual bool Show(cCanvas* pCanvas);
	array<int, 2> _takelvs;
	array<int, 2> _idxs;
	array<cText*, 2> _tLvs;
	array<cText*, 2> _tNames;
	array<array<cWasFile*, 4>, 2> _wass;
	array<cPet, 2> _pets;
	array<cInterfacePetSkill, 2> _petSkills;
	array<bool, 2> _isBB30s;
	array<int, 2> _idx2s;
	array<cText*, 2> _tBB30s;

};

