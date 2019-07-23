#pragma once
#include "_inc.h"
#define MAX_OBJ_NUM		70


class CGameState
{
public:
	CGameState(){ isInit = 0; };
	virtual ~CGameState(){};
	virtual BOOL Init(void* pData=0) = 0;
	virtual BOOL Frame(void* pData=0) = 0;
	virtual BOOL Free() = 0;
	BOOL isInit;
};

struct sFightList
{
	
	int m_FriendListid = -1;//用来记录是不是玩家的好友,从而更新好友状态
	BOOL Swap(sFightList& fightlist);

	//用于记录角色战斗前的位置
	int  xOldPos;
	int  yOldPos;
	int    m_oldDirection;
	int m_WorkType;
	BOOL Free();
	//召唤兽死亡时击飞效果
	BOOL InitFly();
	BOOL m_bFlyInit;
	int  m_DiePoint;
	BOOL DieFly();

	int  m_rotateRate;
	BOOL Rotate(int rotaterate = 3);
	//让一个角色等待  ,比如说,转换攻击目标时要停几秒,否则看起来很怪
	int m_SleepTime;
	BOOL Sleep(int Time, BOOL bStatic = TRUE);
	//受到的伤害
	cWfileP m_Damage[5]; //五位,也就是最大能显示99999的伤害
	int   m_DamageTime[5];
	int m_DamageNum;   //伤害有几位
	BOOL ShowDamage(CMainState* p);
	BOOL SetDamageRect(int Num); //设置每个字的位置 两个参数分别是 第几个字和总字数
	//
	BOOL m_bSufferFullSkill;//该角色是否被全体法术打

	sFightSkillSelect m_SkillSelect;
	sFightSkillSelect m_SkillPreSelect;
	int               m_ItemSelectID;
	int               m_autoItemSelectID;
	sFightOffset* GetFightOffset();
	int           m_SkillIDEx;//当不使用法术时被使用

	cObj* m_pData=0;

	BOOL NextTarget(cFightState* pFightState,int skillid);
	int  targetID = -1;
	int  m_NowTargetID;
	int  m_NowBeAtkowner = -1;
	vector<int>  targetlist;
	int  m_MaxTargetNum; //最多攻击目标
	int  m_NowTarget;//当前目标在目标列表中的位置
	struct sWork
	{
		int type=-1;
		int stage=-1;
	};
	int GetNowWorkType(){ if (!m_work.size())return -1;  return m_work[m_work.size() - 1].type; }
	int GetNowWorkStage(){ if (!m_work.size())return -1; return m_work[m_work.size() - 1].stage; }
	void SetWork(int type);
	void SetWorkFront(int type);
	vector<sWork>  m_work;  //角色的工作
	sWork* GetWork(){return &m_work[m_work.size() - 1];}

	BOOL   isLive=FALSE;  //角色是否存在 ,比如角色在被击飞的时候,已经死了,但它还存在
	BOOL m_bPrePareFight=FALSE;
	
	int    m_sufferDirection=1;
	
	BOOL SetMagiSufferID(DWORD MagicID, int MagicPos, CWFile* pFile, BOOL up = 1);
	BOOL ShowOnScreen(cCanvas5* pCanvas);
	sFightList();
	~sFightList();
	void RestTarget();
	void operator=(sFightList& flist);
	void SetDie(BOOL bDie){ m_bDie = bDie; }
	BOOL CheckDie(){ return m_bDie; }
#if ccc_date
	int _speedOfBattle = -1;
	int _myTurn = 0;
#endif
private:
	BOOL   m_bDie = FALSE;  //角色是否活着
};



class cFightState :public CGameState
{
private:
	void FriendCure();
	void EndFight(BOOL bFriendCure=TRUE);
public:
	cFightState();
	void EscapeFight();
	void SuccessFight();
	void FalseFight();
	void DieEffect(int type);//飞到地府,并损失一定经验钱



	void ClearState(int id);//去除所有BUFF
	BOOL AddState(int userID, sBuff buf);//增加一个BUFF
	BOOL ReMoveStateID(int id, int userID);//去除一个ID为userID的 BUFF
	BOOL ReMoveSealState(int userID);//解封
	BOOL ReMovePoisionState(int userID);//解毒
	BOOL ReMoveBuffState(int userID);//解增益BUFF
	BOOL ReMoveDeBuffState(int userID);//解负面BUFF
	BOOL ReMoveState(eBuffType Type, int userID);
	
	void SetFightBufDown(int i);
	BOOL m_bEscape=FALSE;//逃跑标志
	void SetDie(int ID);//检测一个对象是否死亡,并作出动作(飞掉,或倒下)

	int m_turn;  //等待接收命令,战斗
	int m_nowturnid;//当前在行动的ID
	int _turn = 0;
	BOOL SortBySpeed();

	
	//这个线程负责加载法术图片,这样法术显示就不会卡了0_0!
	CWFile* m_pFileToLoad[5];
	DWORD   m_IDtoLoad[5];

	BOOL   m_ThreadSleep=TRUE;
	HANDLE m_hThread;
	
	int m_HiddenWeaponsUseNum=0;
	CWFile m_HiddenWeapons;
	cWfileP m_HiddenWeaponsp[10];
	int   m_HiddenWeaponsTargetID[10];
	BOOL HiddenWeaponsFly();
	BOOL HiddenWeaponsMove(int id,int yoffset=0);
	int   m_ShowTurnType[30];
	void*  m_pShowTurn[30];
	int   m_ShowTurnUseNum;

	static unsigned int WINAPI ThreadProc(
		_In_  LPVOID lpParameter
		);

	cFullMagic m_FullSkill;

	cInterfaceFight m_FightMenu;
	cText5 m_Frame;  //测试用
	BOOL Suffer(int ID);
	float m_Sufferspd = 4;
	void Sort();
	
	BOOL MagicSuffer(int ID);
	BOOL SetWork(int ID,int Type);
	BOOL SetMagicSuffer(int ID, int direction);//把一个对象设置成被法术打状态
	BOOL SwitchMagicSuffer(int ID);  //把一个单位从受法术状态转成被打状态
	BOOL SwitchMagicSufferAvoid(int ID);  //把一个单位从受法术状态转成被回避状态
	BOOL SetSuffer(int ID, int direction,int userid);//把一个对象设置成被打状态
	

	BOOL SetAvoid(int ID, int direction);
	void SetTarget(int ID,int Target);
	int CheckTarget(int ID, int target, int skillid);//检测目标是否可以攻击
	BOOL DoWork();
	BOOL isInRect(long x, long y, CWFile* pPic, cMyMap* pMap);
	BOOL Init(void* pData=0);
	BOOL Frame(void* pData=0);

	BOOL GetSelect(long x, long y);
	BOOL Free();
	BOOL ProcessInput();
	int  AutoSelect(BOOL Enemy);//随机选择一个对象,如果Enemy为1 则选择敌方,如果为0,则选择我方.  如果无法选到对象,则返回-1(不可能出现这种情况吧?)
	BOOL FallDown(int ID);//角色死亡
//	BOOL Catch(int ID);
	BOOL Avoid(int ID);
	BOOL ApproachProtect(int ID, int TargetID);
	BOOL Guard(int ID, int xTarget, int yTarget);
	BOOL Counter(int ID);
	void SetCounter(int ID,int TargetID);
	BOOL SetDefend(int ID, int direction,int userid);
	BOOL Defend(int ID);
	BOOL Approach(int ID,int TargetID,BOOL gap=FALSE);  //如果移动到了范围内,返回TRUE 
	BOOL ReturnApproach(int ID, float Speed = 20.0f);  //如果移动到了范围内,返回TRUE
	int WorkAttack(int userID);//如果目标不在攻击范围内,会先调用Approach接近 代表一次物理攻击的开始到攻击判定,使用完此函数,需要用WaitPosEnd等待动作结束
	BOOL WaitPosEnd(int userID);//此函数仅仅是等待动作完成而已.
	vector<sFightList*>  m_pList;
	int   m_SpeedListPos[20];
	int m_xPosList[20];
	int m_yPosList[20];
	cText5	m_MiaoShu;
	
	void CheckPetExp();
	BOOL PrePareToFight(int i);
	BOOL BackFromFight(int i);
private:
	

};
const int c_InterfaceShowNum = 3;  //最多同时显示几个界面,多了看起来烦........
const int c_GlobalButtonNum = 256;
class cAI;
class cEndState;
class cMenuState;

class CMainState :public CGameState
{
public:
	CWFile m_FNumRed;
	CWFile m_FNumGreen;
	void SetRanse(int i, int d0, int d1=0, int d2=0, int d3=0,  int part = 0);
	void SetJiangLiItem(sItem2& item, BOOL m_bNeedTag = FALSE);
	void SetJiangLi(INT64 exp, INT64 expbb, INT64 money, INT64 chubeimoney = 0, BOOL m_bNeedTag = FALSE);

	void FollowLv(int id,int lv=-1);
	void FreeFightList(int i);
	
	cTaskHuoDong m_TaskHuoDong;
	cInterfaceUseJiaJu m_UseJiaJu;
	cFangWu m_FangWu;
	void ResetAll();
	cEndState* m_pEndState;
	cMenuState* m_pMenuState;
	
	int  m_FightType;
	BOOL* m_MaskList;
	cInterfaceChaKan m_ChaKan;
	cTaskZhuXian m_ZhuXian;
	cTaskZhiXian m_ZhiXian;
	cTaskZhiXian2 m_ZhiXian2;
	cTaskZhiXian3 m_ZhiXian3;
	cTaskFB  m_TaskFB;
	void SetCharacter(int ID);
	int AddPCEnemy(
		sMapObjTrigger* pdata,
		int lv,
		sAddPoint* addpoint,
		sZiZhi* zizhi,
		eMengPai mengpaid,
		int stronglv = -1,
		int pos = -1,
		BOOL our = FALSE);

	int AddPCEnemy(
		string name,
		int modeid,
		int lv,
		sAddPoint* addpoint,
		sZiZhi* zizhi,
		eMengPai mengpaid ,
		sItem2* pWeapon = 0,
		int petid = -1,
		int stronglv = -1,
		int pos =-1,
		BOOL our = FALSE);
	int AddPCPetEnemy(
		ePetID modeid,
		int lv=-1,
		sAddPoint* addpoint=0,
		eMengPai mengpaid = eMP_随机,
		string name = "",
		int stronglv = -1,
		BOOL bOut = FALSE,
		int pos = -1);
	int AddPCPet(
		ePetID modeid,
		int lv,
		sAddPoint* addpoint,
		eMengPai mengpaid,
		string name = "",
		int stronglv = -1,
		BOOL bOur = FALSE,
		int pos = -1);
	int AddPetEnemy(
		string name,
		int modeid,
		int lv,
		sAddPoint* addpoint,
		int stronglv=-1,
		int Pos = -1,
		BOOL out = FALSE);
	int AddPetEnemy2(
		int modeid,
		int lv=-1,
		sAddPoint* addpoint=0,
		int stronglv=-1,
		int Pos = -1,
		BOOL our = FALSE);
	int AddPC(
		string name,
		int modeid,
		int lv,
		sAddPoint* addpoint,
		sZiZhi* zizhi,
		eMengPai mengpaid,
		sItem2* pWeapon = 0,
		int petid = -1,
		int stronglv = -1,
		int pos = -1
		);

	int AddPet(
		string name,
		int modeid,
		int lv,
		sAddPoint* addpoint,
		int stronglv=-1,
		int Pos = -1);
	cInterfaceJianDing m_InterfaceJianDing;
	cInterfaceGive m_InterfaceGive;
	cInterfaceYingHang m_YingHang;
	cInterfaceXiuLian m_LearnXiuLian;
	cBangPaiJiNengXueXi m_LearnBangPaiSkill;
	cInterfaceLearnSkill m_LearnSkill;
	cTaskSM m_taskSM;
	int GetAverageLv();//计算队伍平均等级
	cInterfaceRanSe m_InterfaceRanSe;
	cChangeColor m_ColorManage;
	cItemSelect m_ItemSelect;
	cTriggerGive m_TriggerGive;
	//cTriggerTime m_TriggerTime;
	cTrigger m_TriggerFightSuccess;
	cTrigger m_TriggerFightFalse;
	cTrigger m_TriggerFightEscape;
	cDialogTrigger m_TriggerDialog;
	cTrigger m_TriggerFightStart;
	cMapObjTrigger m_TriggerObjMap;
	cObjTrigger m_TriggerObj;
	cLvTrigger m_Triggerlv;
	cTaskNormal m_TaskNormal;
	cTaskBaotu m_TaskBaoTu;
	cTaskZhuaGui m_TaskZhuaGui;
	cTaskBangPai m_TaskBangPai;
	cTrigger  m_TriggerFightTurn;//干扰战斗
	//cText m_sFPS;
	string m_MusicName;
	cInterSelectFriendItem m_SelectFriendItem;
	cMySound  m_Mp3;
	//
	cWorldMap m_WorldMap;

	
	cTags m_Tags;
	cInterfaceTeam m_InterfaceTeam;
	
	int m_HeroID;
	cCanvas5 m_Canvas;
	cZuoQi m_ZuoQi;
	int  AtutoGetEnemyNum();
	int GetPCFightNum(){ return GetLiveNum(0, 5); }

	//int  GetEnemyNum(int startid=10,int endid=20);
	int GetLiveNum(int start, int end);

	BOOL SwapFightOffset(int Original, int Target);
	BOOL ReadyToFight();
	int ReadTaskFightIndex(string name);
	cInterfaceChannel m_Channel;
	
	void LockLv(int b = 0);//设定等级上限
	int GetLockLv(){ return m_GlobalButton[2]; }
	vector<int> m_GlobalButton;
	void SaveGlobal(ofstream& File);
	void LoadGlobal(ifstream& File);
	 RECT m_FullRect;
	 HBRUSH  m_blackbrush;
	
	BOOL SetEnemy(int EnemyType, int EnemyID, int lv, int AI);
	//让指定角色得到物品  如果不是可叠加物品最后一个参数作为等级使用
	BOOL Give(int CharID, sItem2* pItem);
	CWFile m_PathPoint;
	cItem m_ItemManage;
	
	cInterfaceSmallMap m_InterfaceSmallMap; //控制显示小地图
	//从文件读取
	BOOL LoadCharacterData2(int charactID, string Path);
	BOOL LoadCharacterData2(cObj*& data, string Path);
	cObj*  m_pNowSelect;

	BOOL  FindAttackPoint(cObj* data,char* name);
	//寻找角色列表
	BOOL  FindCharacter(cObj*& data, int CharacterID);
	BOOL SetFightPet(int ID,int PetID,BOOL blimit=TRUE);

	//产生一个召唤兽(注意,返回的资源在堆中,接收者如果不用需自行删除)
	BOOL MakeAPet(cPet*& pPet, int ID, int StrongLv, int LV,sAddPoint addpoint);
#if ccc_date
	BOOL MakeAPet(cPet*& pPet, int ID, int StrongLv, int LV);
	sAddPoint getAddpointFromPet(cPetData *data, bool is1Or0Blood = false);
	sAddPoint getAddpointFromPet(const vector<sSkill*> &skills, bool is1Or0Blood = false);
#endif
	//BOOL SetUpOffset(sFightList* p);
	BOOL  GivePcAPet(int charID, cPet* pPet,BOOL setfight=TRUE);
	int CheckInTeam(string name);

	BOOL  FindNPCData(cNpc*& data, int NpcID);
	BOOL  FindData(cObj* data, int Id);
	//寻找召唤兽列表
	BOOL  FindPetData(cPet* pPet, int PetID);
	cPetManager m_PetDataManager;
	cSkillManager m_SkillManager;
	//战斗角色表
	vector<sFightList> m_FightList;

	CWFile m_Shadow;
	
	CWFile m_FaceTextBack;
	vector<cWfileP> m_FaceTextBackp;
	cAI     m_AI;
	cFriend m_Friend;
	cInterfaceDoor m_InterfaceDoor;
	cInterfaceItem m_InterfaceItem;
	cInterfaceFB   m_InterfaceFB;
	cInterfacePet  m_InterfacePet;
	cInterfaceJiNeng m_InterfaceJiNeng;
	cInterfaceJob  m_Job;
	cInterfaceSystem m_InterfaceSystem;

	cMenu   m_Menu;
	cState  m_State;
	cCursor5 m_Cursor;
	vector<HFONT> m_hFont;
	HFONT m_hOldFont;
	HFONT m_hOldFont2;
	cPCHead m_PCHead;

	cInterfaceDialog m_Dialog;
	cInterFaceBuy   m_InterFaceBuy;
	cInterFaceBuyPet   m_InterFaceBuyPet;
	cInterfaceDaZao m_Dazao;
	cInterfaceChallange m_Challange;
	cInterfaceInstructions m_Instructions;
	cInterfaceConfig m_InterFaceConfig;

	BOOL MoveObj();
	cFindPath m_FindPt;
	cObj* GetPointAt(long x, long y);
	cScript m_ScriptTemplate;

	cObj* FindObjByName(string Name);
	cObj* FindObjByNpc(sNpc* pNpc);
	cAccelator m_Accelator;


	BOOL ProcessInput();
	BOOL ProcessInterface();

	cInterfaceFather* m_Interface[c_InterfaceShowNum];
	BOOL InterfaceSetShow(cInterfaceFather* p,BOOL NeedShow);
	void ClearInterfaceSetShow();
	cInput5    Input;
	cInputDevice5 Mouse;
	cInputDevice5 Keyboard;
	BOOL FindObj();
	BOOL Sort();

	//让队友跟随主角
	BOOL TeamFollow();

	inline void UpDateInput();
	CMainState();
	cObj*  m_pObj[MAX_OBJ_NUM];
	int m_ObjNumber;
	~CMainState();
	BOOL SetWork(int ID,int Target,int Pos);
	BOOL Init(void* pData=0);
	void Init2();
	void Init3();
	
	HFONT EasyCreateFont(int h, string name, int weight=400);
	cTaskFather* FindTaskByID(int ID);
	int FindPetWeapon(string name);
	BOOL Frame(void* pData=0);
	BOOL ShowInterface();
	BOOL ShowInterface2();
	BOOL Free();
	cMyMap m_Map;
	

	vector<sNpcData> m_pNpcList;

	
	long m_EquipNumber;

	
	int  m_AttackPointNumber;
	void LoadList();
	BOOL LoadWeaponList(string Path);
	int  ReadInt(char*& point);
	BOOL  ReadName(char*& point, char*& pName);
	DWORD ReadDWORD(char*& point);

	vector<sCharacterData> m_pCharacterDataList;
	
	cFightState* m_pFightState=0;
	void SetMouseOnMap(BOOL lock);
	BOOL GetLockMouse(){ return m_isMouseOnMap; }
	BOOL m_bInit3 = FALSE;

	//全局变量
	CWFile m_Cancel;
	CWFile m_HpLine;
	CWFile m_HpEmptyLine;
	CWFile m_Button4;//四字按钮
	CWFile m_Button2;
	void ShowObj();
	struct sDialogList
	{
		string name;
		DWORD  idlist;
	};
	void SetDialogList(string name, DWORD id);
	void SetDialogListPet(string name, ePetID petid,BOOL bJinJie=FALSE);
	void SetDialogListNpc(string name, int npcid);
	void SetDialogListPC(string name, int pcid);
	void SetDialogList(cObj* pObj);
	void ClearDialogList(){ m_DialogList.clear(); }
	vector<sDialogList>  m_DialogList;//头像列表,用于对话时没出现的角色的头像
private:
	BOOL m_bInit2=FALSE;
	BOOL m_LoadList = FALSE;
	BOOL m_isMouseOnMap;
	
	int m_NumShow=0;
	int   m_ShowTurnType[70];
	void*  m_pShowTurn[70];
	int m_PosYList[70];
public:
	// 主线剧情 挑战模式
	int _challengeChapterStorage = -1;
};

class cMenuState:public CGameState
{
public:
	cWfileP* m_pPre=0;
	BOOL CheckL();
	virtual BOOL Init(void* pData = 0) ;
	virtual BOOL Frame(void* pData = 0);
	void Show(cCanvas5* pCanvas);
	virtual BOOL Free(){ return TRUE; }
	vector<cWfileP> m_Button;
	vector<cText5> m_tButton;
	static unsigned int WINAPI ThreadProc(
		_In_  LPVOID lpParameter
		);
private:
	int m_bMode=0;
	HANDLE m_hThread=0;
	int m_Sleeptime;
	int m_Select;
	int m_ID=0;
	CWFile m_Back;
	BOOL m_bInit = FALSE;
	void Move(int x, int y);
	int m_xPos;
	int m_yPos;
};
class cEndState :public CGameState
{
public:
	BOOL CheckL();
	virtual BOOL Init(void* pData = 0);
	virtual BOOL Frame(void* pData = 0);
	void Show(cCanvas5* pCanvas);
	void Set(string title, string context);
	virtual BOOL Free(){ return TRUE; }
private:
	CWFile m_Back;
	BOOL m_bInit = FALSE;
	cText5 m_Title;
	cText5 m_Context;


};
