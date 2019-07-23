#pragma once
#include "_stateinc.h"

class cEndState :public CGameState
{
public:
	bool CheckL();
	virtual bool Init(void* pData = 0);
	virtual bool Frame(void* pData = 0);
	void Show(cCanvas* pCanvas);
	void Set(string title, string context);
	virtual bool Free(){ return true; }
private:
	//cWasFile m_Back;
	bool m_bInit = false;
	cText m_Title;
	cText m_Context;
};