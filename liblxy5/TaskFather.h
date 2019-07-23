#pragma once
#include "Npc.h"

#define TASK_TYPE_ZHUXIAN 1
#define TASK_TYPE_FUBEN 50

struct sShangPinPet;
struct sTaskMapObj;
struct cPropertyData;
class cOb;
class cPetData;
class cPcData;
class cTaskFather
{
public:
	cPropertyData* AddPetEnemyF(int hp, ePetID id, int lv = -1, string name = "", bool bOur = 0, int pos = -1);
	cPropertyData* Add变身EnemyF(int hp, ePetID id, int lv = -1, eMengPai mp = eMP_随机, string name = "", bool bOur = 0, int pos = -1);
	cPropertyData* AddPCEnemyF(int hp, int id, sZiZhi* zz, int lv = -1, eMengPai mp = eMP_随机, string name = "", int weapontype = -1, int weaponid = -1, bool bOur = 0, int pos = -1);

	cPetData* AddEnemy(int hp, int modeid, int lv, string name = "", sAddPoint* ap = nullptr, int pos = -1, bool our = false);
	cPcData* AddEnemy(int hp, int modeid, int lv, eMengPai mengpaid, string name = "", sAddPoint* addpoint = nullptr, int weaponLv = -1, int pos = -1, bool our = false);

	void AutoGetPet(string name, int id, int id1 = -1, int id2 = -1, int id3 = -1);
	void AutoGetPet(string name){ return AutoGetPet(name, rand() % 40); }
	void SetMusic(string name = "");
	bool CheckHeroMoney(int money, bool bTag = true);
	void DialogTalkObj(string text, cObj* p);
	void DialogTalkNObj(string text);
	void NowNpcTalk(string text);
	void UnInviteAll();//解散队伍
	void UpdateJob(string context, string title, int time, int ret);
	void UpdateJob(string context, string title);
	void SetNpc(sTaskMapObj& data, int ret, string name, string map, int modeid, int x, int y, int direction = -1);
	void AddTriggerFightTurn(int ret);

	void RemoveTriggerObj();
	void RemoveTriggerGive();
	void RemoveTriggerObjMap(int ret = -1);
	void RemoveTriggerObjMap(int x, int y);
	void RemoveTriggerObjMap2(cObj* pObj);
	void RemoveTriggerSuccess();
	void RemoveTriggerFalse();
	void RemoveTriggerEscape();
	void AddChannel(string text, string name = "", int channel = 3);
	void AddTriggerTalkList(string path, int id, int ret);
	void AddTriggerGive(string name, int type, int id, int ret, bool bHuChi = false);
	void AddTriggerFightStart(int ret);
	void AddTriggerFightSuccess(int ret);
	void AddTriggerFightFalse(int ret);
	void AddTriggerFightEscape(int ret);
	void AddTriggerLv(int ret, int lv);
//	virtual void AddTriggerDialog(string path, int id, int ret);

	void AddTriggerObjMap(string mapname, int ret, bool bHuChi = true);
	void AddTriggerObjMap(string mapname){ AddTriggerObjMap(mapname, _next, true); }
	void AddTriggerObjMap(sNpc* npc, int ret, bool bHuChi = true);
	void AddTriggerObjMap(sNpc* npc){ AddTriggerObjMap(npc, _next, true); }
	void AddTriggerObjMap(sTaskMapObj* data);

	void AddTriggerObj(sNpc* npc, int ret);
	void AddTriggerObj(sNpc* npc){ AddTriggerObj(npc, _next); }
	void AddTriggerObj(string name, string map, int ret, bool bHuChi = true);
	void AddTriggerObj(string name, string map){ AddTriggerObj(name, map, _next, true); }
	void AddTriggerObj(string name);

	void AddNpcOne(sTaskMapObj* data, bool needfind = false);

	void AddJob(string title, string text);
	void AddJob(string text){ AddJob(_jobTitle, text); }
	void setJobTitle(string title){ _jobTitle = title; }
	void readyFightAndSucces();
	void clearSay(bool onlyEnemy = true);


	virtual void AddTag(string text, int time = 500);
	void getTag(string text, int time = 500);
	void lostTag(string text, int time = 500);
	bool CheckNpc(string mapname, string npcname);//测检鼠标是否点在某NPC上
	int m_HuanShu = 0;
	bool m_bInit = false;
	virtual void Init() = 0;
	void CheckInit(){ if (!m_bInit)Init(); m_bInit = true; }
	virtual bool Process(int stage) = 0;
	int m_type;
	void SetJiangLi(int time, int needtag = false, int money = 100, int chubei = 0, int exp = 100, int expbb = 0);
	void SetJiangLi2(int exp, int money = 0, int chubei = 0, int petexp = 0, bool needtag = true);
	void SetJiangLiItem(int id, int type, int num = 1);
//	void FollowLvForTask(int id, int lv);
	void GetPet(string name, sShangPinPet* pet, int stronglv);
	void GetPet2(sShangPinPet* pet, int stronglv);



	void AddTriggerDialogList(vector<string> talklist, int ret);

	void AddTriggerDialog(string text, int ret)
	{ 
		AddTriggerDialogList({ text }, ret);
	}
	void AddTriggerDialog(string text)
	{ 
		AddTriggerDialogList({ text }, _next);
	}

	void AddTriggerDialog(string text, string text2, int ret)
	{
		AddTriggerDialogList({ text, text2 }, ret);
	}
	void AddTriggerDialog(string text, string text2)
	{
		AddTriggerDialogList({ text, text2 }, _next);
	}
	void AddTriggerDialog(string text, string text2, string text3, int ret)
	{
		AddTriggerDialogList({ text, text2, text3 }, ret);
	}
	void AddTriggerDialog(string text, string text2, string text3)
	{
		AddTriggerDialogList({ text, text2, text3 }, _next);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, int ret)
	{
		AddTriggerDialogList({ text, text2, text3, text4 }, ret);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4)
	{
		AddTriggerDialogList({ text, text2, text3, text4 }, _next);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, int ret)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5 }, ret);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5 }, _next);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, string text6, int ret)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5, text6 }, ret);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, string text6)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5, text6 }, _next);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, string text6, string text7, int ret)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5, text6, text7 }, ret);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, string text6, string text7)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5, text6, text7 }, _next);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, string text6, string text7, string text8, int ret)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5, text6, text7, text8 }, ret);
	}
	void AddTriggerDialog(string text, string text2, string text3, string text4, string text5, string text6, string text7, string text8)
	{
		AddTriggerDialogList({ text, text2, text3, text4, text5, text6, text7, text8 }, _next);
	}
protected:
	string _jobTitle;
	int _next;
};

struct sTaskFather
{
	cTaskFather* m_pTask = 0;
	int m_Stage = -1;
};