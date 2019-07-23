#pragma once
#include "global.h"
#include <vector>
class cObj;
class sActionTemplate;
class CMainState;
class sAction;
using namespace std;
class cMyScript
{
public:
	int m_SleepTime;
	int m_DialogueStyle;
	int  m_NowScript;
	BOOL Process(cObj* p);
	BOOL LoadScript(string name);
	BOOL NPCSelect2(cObj* p);
	BOOL SelectNum(cObj* p, int num);
	BOOL EndScript(cObj* p);
	BOOL Case(cObj* p);
	BOOL SetPoint(cObj* p);

	BOOL Talk(cObj* p);
	BOOL TalkMySelf(cObj* p);
	BOOL SetGlobalButton(int stype,int sid,cObj* p=0);
	BOOL ChangeMap(cObj* p);
	sAction* GetAction(cObj* p);
	BOOL Default(cObj* p);
	BOOL Break(cObj* p);

	vector<sAction>    m_ActionList;
	vector<sActionTemplate>* m_pActionTemplateList;
	cMyScript();
	void Free();
private:

};

