#pragma once
#include "_taskinc.h"

class cTaskJuQing :public cTaskFather
{
public:
	string SetUpPathJuQing(string str);
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Init();
	virtual bool Process(int stage){ return true; }

	void SetChapter(int chapter);
	int GetChapter(){ return m_Chapter; }



protected:
	//bool m_bInit2 = false;
	string m_AutoPath;
	vector<string> m_Textlist;
	int m_Chapter = -1;
	string m_DialogPath;
	sAddPoint m_AddPoint;
// public:
// 	sAddPoint getAddPointFromMenpai(eMengPai e);
// 	eMengPai getMenPaiFromRand();
protected:
	int AddPetEnemy(ePetID id, int lv, int name = -1, bool bOur = false, int pos = -1);
	int AddPCPetEnemy(ePetID id, int lv, eMengPai mp = eMP_随机, int name = -1, bool bOur = false, int pos = -1);
	int AddPCEnemy(int id, sZiZhi* zz, int lv, eMengPai mp, int name = -1, int weapontype = -1, int weaponid = -1, bool bOur = false, int pos = -1);

	cPropertyData* AddPetEnemy2(int hp, ePetID id, int lv, int name = -1, bool bOur = false, int pos = -1);
	cPropertyData* Add变身Enemy2(int hp, ePetID id, int lv, eMengPai mp = eMP_随机, int name = -1, bool bOur = false, int pos = -1);
	cPropertyData* AddPCEnemy2(int hp, int id, sZiZhi* zz, int lv, eMengPai mp, int name = -1, int weapontype = -1, int weaponid = -1, bool bOur = false, int pos = -1);
	sItem2* FindItem(int Type, int id);

	void AddTag(int str, int time = 500);
	void LockMap(int name = -1);
	void TalkList(int textid, int nextname, int nextmap, int jobtext, int ret, int dialogret = -1);
	void SetDialogList(int id);
	void AddRangeMap(int mapname, int x, int y, int range, int ret);
	void UpdateJob2(string text);
	void UpdateJob2(int id);
	void AddChannel2(int id);
	void Invite(string name, int fighterid = -1);
	void Un邀请(string name);
	void AddFriend(int i);
	void AddTriggerDialog2(int id, int ret = -1);
	void AddTriggerObj2(int name, int mapname, int ret, bool bHuChi = true);
	void RemoveNpc(int id, bool needfind = false);
	//	void FollowLvForTask(int id, int lv);
	void Select(int title, int name, int cancelret, int select0, int ret0, int select1, int ret1 = -1, int select2 = -1, int ret2 = -1, int select3 = -1, int ret3 = -1);
	cPropertyData* GetPetData(int id);
	int GetCharacterID(string name);
	void AddTriggerObjMap2(int name, int mapname, int modeid, int x, int y, int direction = -1, int ret = -1, int jinjie = 0);
};