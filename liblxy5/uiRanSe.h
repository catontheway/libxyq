#pragma once
#include "_global.h"


class cInterfaceRanSe :public cInterfaceFather
{
public:
	bool CheckRB();
	void UpdateColor();
	bool CheckL();
	void OnOff(bool NeedShow);
	bool Init();
	bool Show(cCanvas* pCanvas);
	bool Move(int x, int y);
	void SetMode(int mode, int Characterid);//sFriendList* plist=0);//0 ½ÇÉ«È¾É«  1×øÆïÈ¾É«  2 ×øÆï×°ÊÎÈ¾É« 3 ÕÙ»½ÊÞÈ¾É«
	void SetPet(int part, int fightpetid);
	bool ProcessInput();
	int m_Mode;
	//cWasFile m_Back;
	cText m_Title;
	cText m_tBuy;
	cWasFile m_btBuy;
	cText m_Cost;
	cWasFile m_Target;
	cWasFile m_btSelect[4];
	cText  m_tSelect[4];
	ulong  m_ColorID;
	int m_NowPart = 0;
	sChangeColorData m_ChangeColorData;
	int _characterid;
	int _fightPetid;
	cWasFile _wasMode, _wasLeft, _wasRight;
	bool _isRandMode = false;
private:
	cWasFile m_NextPage;
	cObj m_Obj;
	sFriendList* m_plist = 0;
	bool m_bInit = false;
};

