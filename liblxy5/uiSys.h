#pragma once
#include "_uiinc.h"

class cTrigger;
class cTriggerObj;
class cTriggerMapObj;
class cTriggerLv;
class cInterfaceFriendQiangHua2 :public cInterfaceFather
{
public:
	string getString(int i);
	bool ProcessInputMore();
	void onClick(int i);
	bool initShow();
//	void Update();
	bool Init();
// 	bool CheckRB();
// 	virtual bool ProcessInput();
// 	virtual bool Show(cCanvas* pCanvas);
// 	virtual bool CheckL();
// 	virtual void OnOff(bool NeedShow);
// 	bool Move(int xPos, int yPos);

	void GetSaveTitle(vector<string>& list);
	void Save(int id);
	void Load(int id);
	static sIstream Load();
//	cInterfaceFriendQiangHua2(){ m_xPos = 100; m_yPos = 100; }

private:
	array<cText*, 15> _ts;
// 	array<cObjWas, 18> m_Buttonp;
// 	cText m_title;
// 	bool m_bInit = false;
// 
// 	array<cText, 18> m_Text;

	int m_bMode = 0;
	void SavePos(ofstream& File);
	void SaveFriend(ofstream& File);
	void SaveFightList(ofstream& File);
	void SaveTrigger(ofstream& File);
	void SaveATrigger(cTrigger* trigger, ofstream& File);
	void SaveObjTrigger(cTriggerObj* trigger, ofstream& File);

	void LoadObjTrigger(cTriggerObj* trigger, ifstream& File);
	void LoadPos(ifstream& File);
	void LoadFriend(ifstream& File);
	void LoadFightList(ifstream& File);
	void LoadTrigger(ifstream& File);
	void LoadATrigger(cTrigger* trigger, ifstream& File);
};




class cInterfaceSystem :public cInterfaceFather
{
public:
	void GetSaveTitle(vector<string>& list);
	void Save(int id);
	void Load(int id);
	cObjWas m_ExtGame;
	cObjWas m_SaveGame;
	cObjWas m_LoadGame;
	cInterfaceSystem(){ m_xPos = 100; m_yPos = 100; }
	bool ProcessInput();
	bool CheckL();
	bool CheckRB();
	//cWasFile m_Back;
	cText m_tExtGame;
	cText m_tSaveGame;
	cText m_tLoadGame;
	cText m_tTitle;
	//sFaceText m_tTime;
	bool Init();
	bool Move(int x, int y);
	bool Show(cCanvas* pCanvas);
	void OnOff(bool needshow);

private:
	int m_bMode = 0;
	bool m_bInit = false;
	void SavePos(ofstream& File);
	void SaveFriend(ofstream& File);

	void SaveFightList(ofstream& File);
	void SaveTrigger(ofstream& File);
	void SaveATrigger(cTrigger* trigger, ofstream& File);
	void SaveObjTrigger(cTriggerObj* trigger, ofstream& File);
	void LoadObjTrigger(cTriggerObj* trigger, ifstream& File);




	void LoadPos(ifstream& File);

	void LoadFriend(ifstream& File);

	void LoadFightList(ifstream& File);
	void LoadTrigger(ifstream& File);
	void LoadATrigger(cTrigger* trigger, ifstream& File);

};
