#pragma once
#include "_uiinc.h"


class cInterfaceFB :public cInterfaceFather
{
public:
	void OnOff(bool NeedShow);
	bool CheckRB();
	bool Init();
	bool ProcessInput();
	bool Show(cCanvas* pCanvas);
	bool CheckL();
	bool Move(int x, int y);
	//void Reset();//÷ÿ÷√∏±±æ◊¥Ã¨
	vector<cText> m_tFBName;
private:
	int m_TrueSelect;
	RECT m_Rect;
	cWasFile m_MouseOnBack;
	cText m_TButton;
	cText m_Title;
	cWasFile m_Button;
	//cWasFile m_Back;
	bool m_bInit = false;
};

