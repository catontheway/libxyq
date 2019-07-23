#pragma once
#include "_uiinc.h"

class cInterfaceUseJiaJu:public cInterfaceFather
{
public:
	cInterfaceUseJiaJu(){ 
		for (int i = 0; i < 6;i++)
		m_Pic[i].m_Picture.m_bShadow = 50; }
	virtual bool ProcessInput();
	virtual bool Show(cCanvas* pCanvas);
	virtual bool CheckL();
	bool CheckRB();
	virtual void OnOff(bool NeedShow);
	void SetJiaJu(sItem2* jiaju);
	void AddDirection();
private:
	sItem2* m_pJiaJu;
	cWasFile m_Pic[6];
	sJiaJu m_JiaJu;
	

};
