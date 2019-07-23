#pragma once
#include "_stateinc.h"

class cMenuState :public CGameState
{
public:
	cObjWas* m_pPre = 0;
	bool CheckL();
	virtual bool Init(void* pData = 0);
	virtual bool Frame(void* pData = 0);
	void Show(cCanvas* pCanvas);
	virtual bool Free(){ return true; }
	vector<cObjWas> m_Button;
	vector<cText> m_tButton;
	static unsigned int WINAPI ThreadProc(
		_In_  LPVOID lpParameter
		);
private:
	int m_bMode = 0;
	HANDLE m_hThread = 0;
	int m_Sleeptime;
	int m_Select;
	int m_ID = 0;
	cWasFile m_Back;
	bool m_bInit = false;
	void Move(int x, int y);
	int m_xPos;
	int m_yPos;
};