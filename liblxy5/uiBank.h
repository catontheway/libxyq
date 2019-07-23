#pragma once
#include "_uiinc.h"

class cInterfaceYingHang :public cInterfaceFather
{
public:
	bool Init();
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	bool CheckRB();
	void SetMode(
		bool mode,
		sFriendList* pFriend = 0
		);
	void OnOff(bool NeedShow);
	bool Move(int x, int y);
	cText m_XianJin;
	cText m_CunYing;
	cInterfaceNumShuRu m_ShuRu;
	cTaskFather* m_pTrigger;
	int m_TriggerID;
private:
	sFriendList* m_pFriend;
	bool m_bInit = false;
	bool m_bMode;
	//cWasFile m_Back;

	cObjWas m_Button;
	cText  m_tButton;
};
