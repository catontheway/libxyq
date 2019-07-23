#pragma once
#include "_taskinc.h"


class cTaskFB :public cTaskFather
{
public:
	void SetMusicFB();
	void EndFB();
	void ClearNpc();
	void GetItem(int type, int id, bool needtag = true, int num = 1);
	void AddTriggerDialog(int id, int ret);

	cTaskFB(){ m_type = 50; }
	void AddNpc();
	void UpdateJob(string context, int time = -1, int falret = 1002, string title = "");
	void AddTriggerDialog(string path, int id, int ret);

	bool Start(int id);
	void RemoveNpc(cObj*& p, bool bRemoveList = true);
	void RemoveNpc(sNpc* p, bool bRemoveList = true);
	void Save(ofstream& File);
	void Load(ifstream& File);
	void StageSetSameNpc(vector<int> modid, string mapname, int ret, int num, string name = "");
	void StageSetSameNpc(int modid, string mapname, int ret, int num, string name = "");
	void StageSetSameNpc2(vector<int> modid, string mapname, int ret, int num, string name = "");
	void StageSetSameNpc2(int modid, string mapname, int ret, int num, string name = "");
	sTaskMapObj* FindNpcByObj(cObj* p);
	vector<string> m_TextList;
	void SetTask(cTaskFather* p, int ret);
	vector<sTaskMapObj>  m_List;
	vector<sTaskMapObj>  m_List2;


	virtual void Init(){  };
	virtual bool Process(int stage);
	void ProcessWj(int stage);
	void ProcessSL(int stage);
	void ProcessCC(int stage);
	void ProcessSM(int stage);
	void ProcessSJ(int stage);


private:
	cTaskFather* m_pEnd = 0;
	int m_Ret = -1;

	int m_Stage = -1;
	int m_Stage2 = -1;
	int m_FBID = -1;
	cObj* m_NowNpc = 0;
};


