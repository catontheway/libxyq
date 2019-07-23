#pragma once
#include "_uiinc.h"

// 查看人物和宝宝属性
class cInterfaceChaKan :public cInterfaceFather
{
public:
	bool Init();
	void Set(cObj* obj);
	void Set(sFriendList& list);
	void Set(cPropertyData* data, vector<ulong> picid, array<sChangeColorData*, 4> pranse, sZiZhi* zz);
	void Set(cCharacter* character);
	void Set(cPet* pet);
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	virtual void OnOff(bool NeedShow);
	bool Move(int xPos, int yPos);
	bool CheckRB();
	void MovePetEquip();
private:
	cText m_MengPai;

	cText m_Property[15];
	cPropertyData* m_data;
	//cWasFile m_Back;
	bool m_bInit = false;
	cInterfacePetSkill uiPetSkill;
	cWasFile m_Pic[4];
	cObjWas m_Shadow;
// 	cObj m_Obj;
// 	cObj *_obj = nullptr;
};
