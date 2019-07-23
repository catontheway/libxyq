#pragma once
#include "_global.h"

class cObj;
class sActionTemplate;
class CMainState;
class sAction;
class cMyScript
{
public:
	int m_SleepTime;
	int m_DialogueStyle;
	int  m_NowScript;
	bool Process(cObj* p);
	bool LoadScript(string name);
	bool NPCSelect2(cObj* p);
	bool SelectNum(cObj* p, int num);
	bool EndScript(cObj* p);
	bool Case(cObj* p);
	bool SetPoint(cObj* p);

	bool Talk(cObj* p);
	bool TalkMySelf(cObj* p);
	bool SetGlobalButton(int stype,int sid,cObj* p=0);
	bool ChangeMap(cObj* p);
	sAction* GetAction(cObj* p);
	bool Default(cObj* p);
	bool Break(cObj* p);

	vector<sAction>  m_ActionList;
//	vector<sActionTemplate>* m_pActionTemplateList;
	cMyScript();
	void Free();
private:

};

