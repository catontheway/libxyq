#pragma once

class cTrigger
{
public:
	BOOL AddTask(cTaskFather* ptask,int stage);
	void ReMove(cTaskFather* pTask);
	void ReMove(int id);
	BOOL Process();
	BOOL ProcessReMove();
	void Clear(){ m_TaskList.clear(); }
	vector<sTaskFather> m_TaskList;
private:	
};

class cTriggerGive
{
public:
	void Clear(){ m_List.clear(); }
	struct sTriggerGive
	{
		string m_name; 
		int m_itemid; 
		int m_itemtype;
		cTaskFather* m_ptask;
		int m_ret;
		void Set(string name, int itemid, int itemtype, cTaskFather* ptask, int ret)
		{
			m_name=name;
			m_itemid=itemid;
			m_itemtype=	itemtype;
			m_ptask=ptask;
			m_ret=ret;
		}
		void Save(ofstream& File);
		
		void Load(ifstream& File);
	
	};
	void AddTask(string name, int itemid, int itemtype, cTaskFather* ptask, int ret, BOOL bHuChi = TRUE);
	void ReMove(cTaskFather* ptask);
	void ReMove(int id);
	BOOL Process(string name, int id, int type);
	void Save(ofstream& File);
	void Load(ifstream& File);
	vector<sTriggerGive> m_List;
};
struct sTalkList //代表一句话
{
	string context;
	string name;
	void Save(ofstream& File)
	{
		File << "text\n";
		File << name << "\n";
		File << context << "\n";
	}
	void Load(ifstream& File)
	{
		string dustbin;
		getline(File,dustbin);
		getline(File, name);
		getline(File, context);
	}
};
class cTriggerTime
{
public:
	void Add(cTaskFather* task, int stage, int h = -1, int d = -1, int m = -1, int y = -1, int y2 = 0, int m2 = 0, int d2 = 0, int h2 = 0);
	void Remove(cTaskFather* task);
	void Process();
	void Save(ofstream& File);
	void Load(ifstream& File);
	struct sTimeTrigger :public sTaskFather
	{

		void Set(int y, int m, int d, int h, cTaskFather* task, int stage,
		int h2 = 0, int d2 = 0, int m2 = 0, int y2 = 0)
		{
			m_h = h;
			m_d = d;
			m_m = m;
			m_y = y;
			m_h2 = h2;
			m_d2 = d2;
			m_m2 = m2;
			m_y2 = y2;
			m_Stage = stage;
			m_pTask = task;
		}
		int m_h;
		int m_d;
		int m_m;
		int m_y;

		int m_h2;
		int m_d2;
		int m_m2;
		int m_y2;
	};
private:
	vector<sTimeTrigger>  m_list;
};


class cDialogTrigger
{
public:
	cDialogTrigger();
	void AddSelect(
		cTaskFather* p,
		string text,
		string name,
		int cancelret,
		string select0, int ret0,
		string select1, int ret1,
		string select2="", int ret2=-1,
		string select3="", int ret3=-1);
	BOOL AddTask(string path,int id,cTaskFather* ptask, int stage);
	BOOL AddTaskFB(string path, int id, cTaskFather* ptask, int stage);

	BOOL Process(int id=0,BOOL skip=FALSE);

	void Save(ofstream& File);
	void Load(ifstream& File);
	int m_Mode;
	struct sDialogTrigger :public sTaskFather
	{
		int m_Mode;
		void Save(ofstream& File);
		void Load(ifstream& File);
		vector<sTalkList> m_DialogList; //代表一句话
		int m_Nowtext;
		BOOL Process(BOOL skip = FALSE);
		BOOL AddTaskOriginal(int mode,cTaskFather* ptask, int stage, ifstream& File);
		void Reset()
		{
			m_pTask = 0;
			m_DialogList.clear();
			m_Nowtext = -1;
		}
	};
	vector<sDialogTrigger> m_datalist;
	
private:
	void ReMove();
	void ReMove(int id);

};
class cLvTrigger
{
public:
	BOOL AddTask(cTaskFather* ptask, int stage,int lv);
	BOOL Process();
	void ReMove(int id);
	void ReMove(cTaskFather* pTask);
	struct sLvTrigger :public sTaskFather
	{
		int lv;
	};
	void Clear(){ m_datalist.clear(); }
	void Save(ofstream& File);
	void Load(ifstream& File);

	vector<sLvTrigger> m_datalist;

	
};

struct sMapObjTrigger :public sTaskFather
{
	sNpc m_Npc;
	void operator=(sMapObjTrigger& data)
	{
		m_Npc = data.m_Npc;
		m_pTask = data.m_pTask;
		m_Stage = data.m_Stage;
	}
	void operator=(sFriendList& data);
	void Save(ofstream& File);
	void Load(ifstream& File);
};
class cMapObjTrigger
{
public:
	BOOL AddTask(cTaskFather* ptask, int stage, string mapname,BOOL bHuChi=TRUE);
	void AddTask(sMapObjTrigger& target);
	BOOL AddTask(cTaskFather* ptask, int stage, sNpc Npc,BOOL bHuChi=TRUE);
	BOOL Process();
	sMapObjTrigger*  FindByName(string name);
	void ReMove(int id);
	void ReMove(cTaskFather* pTask,int ret=-1);
	void ReMove(cTaskFather* pTask, string mapname);
	void ReMove(cTaskFather* pTask, int x,int y);
	
	
	vector<sMapObjTrigger> m_datalist;
	void Save(ofstream& File);
	void Load(ifstream& File);
};
class cObjTrigger
{
public:
	BOOL AddTask(string name, string mapname, cTaskFather* ptask, int stage,BOOL bHuChi=TRUE);
	BOOL Process(string name);
	void ReMove(int id);
	void ReMove(cTaskFather* pTask);
	struct sObjTrigger:public sTaskFather
	{
		string m_name;
		string m_mapname;
	};
	vector<sObjTrigger> m_datalist;
	void Save(ofstream& File);
	void Load(ifstream& File);
};
enum eHuoDong
{
	门派闯关,
	科举,
};
class cTaskHuoDong :public cTaskFather
{//12门派
public:
	void ReadytoFightmp(sMapObjTrigger& list,eMengPai mp);//门派闯关战斗
	void ReadytoFightmp(int lv, cObj* nownpc = nullptr);
	void Start(eHuoDong id);
	cTaskHuoDong(){ m_type = 35; }
	virtual void Init();
	void Initmp();
	virtual BOOL Process(int stage);
	BOOL Processmp(int stage);
	BOOL Processkj(int stage);
	sMapObjTrigger m_List[13];
	int m_MengPaiId[13];
	cObj* m_NowNpc=0;
	vector<int> m_Idlist;
	int m_Stage=0;
	string GetText();
	void Save(ofstream& File);


	void Load(ifstream& File);
	int m_HuoDongID=-1;
	void SetTrigger(cTaskFather* p, int ret, int huanshu){ m_pTask = p; m_TaskRet = ret; m_TriggerHuanShu = huanshu; }
// private:
	cTaskFather* m_pTask = 0;
	int m_TaskRet = -1;
	int m_TriggerHuanShu=0;
	void UpdateJob(string text, int huanshu=-1);
	BOOL m_bInit12=FALSE;
};
class cTaskNormal :public cTaskFather
{
public:
	void Init(){};
	cTaskNormal(){ m_type=0; }
	BOOL Process(int stage);
	cObj* m_pNpc = 0;
private:
};
class cTaskBaotu :public cTaskFather
{
public:
	void Init();
	BOOL Process(int stage);
	vector<string> m_Firstname;
	vector<string> m_Secondname;
	
	string AutoMakeName();
	vector<string> m_MapNameList;
	sNpc m_Robber;
	void Save(ofstream& File)
	{
		m_Robber.Save(File);
	}
	void Load(ifstream& File)
	{
		m_Robber.Load(File);
	}
};

class cTaskZhuaGui :public cTaskFather, public cObjTrigger
{
public:
	void Init();
	BOOL Process(int stage);

	BOOL ReadyToFight(sNpc& npc);
	vector<string> m_Firstname;
	vector<string> m_Secondname;
	vector<string> m_Thirdname;
	string AutoMakeName();
	void AutoGetGost(sNpc& npc, string mapname);
	void GetErrPos(sNpc npc,int& xout, int& yout);
	vector<string> m_MapNameList;
	sNpc m_Ghost;
	void Save(ofstream& File);
	void Load(ifstream& File);
	//
	void SetTrigger(cTaskFather* p, int num, int stage);
	void UpdateZGJob(BOOL m_bTrue=FALSE);
private:
	cTaskFather* m_pTask = 0;
	int m_RetStage;
	int m_RetNum;
};

class cTaskBangPai:public cTaskFather
{
public:
	void Init(){};
	BOOL Process(int stage);
};

class cTaskSM:public cTaskFather
{
public:
	void UpdateJob(string context);
	cObj* GetShiFu();
	string GetShiFuName();
	string GetShiFuMap();
	void Init(){ m_type = 1003; m_bInit2 = TRUE; }
	BOOL Process(int stage);
	//void AddTask(int type);
	void GetJiangLi();
	void CheckInit(int mengpaiid);
	void InitXiangFu();
	void InitShiWei();
	void Save(ofstream& File);
	
	void Load(ifstream& File);
	sNpc m_Npc;
	int  m_bXiangFuSuccess;
private:
	
	
	int m_EnemyMengPai;
	sItem2 m_ShiWeiWeapon;//示威时NPC的武器
	cObj* m_pNowObj=0;
	sNpc m_YuanJiu;
	vector<string> m_ShiWeiNameList[12];
	vector<int>  m_ShiWeiIdList[12];
	BOOL m_bInitShiWei=FALSE;
	int m_TargetBBid=-1; 

	BOOL m_bInitXiangFu = FALSE;
	vector<string> m_XiangFuNameList;
	vector<string> m_XiangFuDiDianList;
	BOOL m_bInit[12];
	BOOL m_bInit2;
	vector<string> m_NameList[12];
	sItem2 m_ItemNeed;//记录当前师门要的东西
	string m_npcname; //记录当前师门要找的人
	string m_mapname; 
	int m_SuccessNum;
	string m_enemyname; 
	DWORD m_enemyface;
	BOOL m_bHaveTask=0;
};

class cTaskFB :public cTaskFather
{
public:
	void SetMusicFB();
	void EndFB();
	void ClearNpc();
	void GetItem(int type, int id, BOOL needtag=TRUE, int num=1);
	void AddTriggerDialog(int id, int ret);
	
	cTaskFB(){ m_type = 50; }
	void AddNpc();
	void UpdateJob(string context, int time=-1, int falret = 1002, string title = "");
	void AddTriggerDialog(string path, int id, int ret);
	virtual void Init(){  };
	virtual BOOL Process(int stage);
	void ProcessWj(int stage);
	void ProcessSL(int stage);
	void ProcessCC(int stage);
	void ProcessSM(int stage);
	void ProcessSJ(int stage);
	BOOL Start(int id);
	void RemoveNpc(cObj*& p, BOOL bRemoveList = TRUE);
	void RemoveNpc(sNpc* p,BOOL bRemoveList=TRUE);
	void Save(ofstream& File);
	void Load(ifstream& File);
	void StageSetSameNpc(vector<int> modid, string mapname, int ret, int num, string name = "");
	void StageSetSameNpc(int modid, string mapname, int ret, int num, string name = "");
	void StageSetSameNpc2(vector<int> modid, string mapname, int ret, int num, string name = "");
	void StageSetSameNpc2(int modid, string mapname, int ret, int num, string name = "");
	sMapObjTrigger* FindNpcByObj(cObj* p);
	vector<string> m_TextList;
	void SetTask(cTaskFather* p, int ret);
	vector<sMapObjTrigger>  m_List;
	vector<sMapObjTrigger>  m_List2;
private:
	cTaskFather* m_pEnd=0;
	int m_Ret=-1;
	
	int m_Stage = -1;
	int m_Stage2 = -1;
	int m_FBID=-1;
	cObj* m_NowNpc=0;
};
class cTaskFriend :public cTaskFather
{
	virtual void Init(){};
	virtual BOOL Process(int stage);
};
