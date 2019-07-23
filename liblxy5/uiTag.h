#pragma once
#include "_global.h"

struct sTags
{
	cObjWasFather m_Back;
	int m_time;
};
class cTags
{
public:
	void GetMoneyAndExp(int money, int exp = 0, int chubei = 0, int expbb = 0, bool needtag = true);
	void GetItem(string itemname);
	int m_Sleeptime;
	cWasFile m_Back;
	bool Init();
	bool Add(string str, int time = 500);
	bool Show(cCanvas* pCanvas);
	void Process();
	int  m_TagNum;
	sTags m_tags[10];//最多显示5条
	cText m_Text;
	~cTags();
	int _y = 150;
private:
	bool m_bInit = false;
};


class cTag1
{
public:
	bool Init();
	bool Show(cCanvas* pCanvas);
	cText m_Text;
private:
	bool m_bInit = false;
};
