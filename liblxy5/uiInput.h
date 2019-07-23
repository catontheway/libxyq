#pragma once
#include "_uiinc.h"

class cInterfaceNumShuRu
{
public:
	int CountPos(int pos);
	int CountCaretPos(int xMouse, int yMouse);
	void SetCaretPos(int pos);
	void UpdateCaret();
	bool Process();
	void Show(cCanvas* pCanvas);
	INT64 m_num = 0;
	void Init(RECT rect);
	void SetMaxNum(INT64 num){ m_MaxNum = num; }
	cText m_tNum;

	void UpdateNum();
	void SetActive(bool bActive);
	void ShuRu(int num);
	void Erase(int pos);
	void Reset();
	void SetNum(INT64 num);
	void SetHuChi(cInterfaceNumShuRu* huchi){ m_HuChiList.push_back(huchi); }
private:
	vector<cInterfaceNumShuRu*>  m_HuChiList;
	void Init2();
	INT64 m_MaxNum = 0;
	bool m_bActive = false;
	int m_time = 0;
	bool m_bInit = false;
	cWasFile m_Caret;
	vector<int>  m_numlist;
	int  m_numlong = 0;
	int m_caretpos = -1;
	RECT m_rect;
	bool m_bEraseMode = false;
	bool m_bInEraseMode = false;
	int m_EraseStart;
	int m_EraseEnd;
};
