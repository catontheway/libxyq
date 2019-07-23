#pragma once
#include "_uiinc.h"

class  cInterSelectFriendItem : public cInterfaceFather
{
public:
	enum eQiangHuaMode
	{
		eQH装备,
		eQH技能,
		eQH技能2,
		eQH坐骑装饰,
		eQH出战,
		eQH放生
	};

	RECT m_Rect;
	cWasFile m_MouseOnMark;

	virtual bool ProcessInput();
	virtual bool CheckL();
	bool CheckRB();
	bool Init();
	bool Set(int itemtype, int itemid, ulong headid);
	bool Move(int x, int y);
	bool Show(cCanvas* pCanvas);
	void SetMode(sFriendList* list, eQiangHuaMode mode);
	int m_ItemType[20];
	int m_ItemID[20];
	cWasFile m_ItemHead[20];
	void OnOff(bool bshow);

	void GetSelect(int& outtype, int& outid)
	{
		outid = m_ItemID[m_Select];
		outtype = m_ItemType[m_Select];
	}
private:
	sShangPinPet* m_Pet;
	cText m_TitleT;
	sFriendList* m_pdata;
	eQiangHuaMode m_Mode;
	bool m_bInit = false;
	int m_ItemNum = 0;
	//cWasFile m_Back;

};

