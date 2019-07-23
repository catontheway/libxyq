#pragma once
#include "_stateinc.h"

#define MAX_OBJ_NUM	256
const int c_InterfaceShowNum = 8;  //最多同时显示几个界面(用于显示窗口队列)
//const int c_GlobalButtonNum = 256;

class cAI;
class cEndState;
class cMenuState;
class CMainState :public CGameState
{
public:
	cWasFile m_FNumRed;
	cWasFile m_FNumGreen;
	void SetRanse(int i, int d0, int d1=0, int d2=0, int d3=0,  int part = 0);
	void awardItem(sItem2& item, bool m_bNeedTag = false);
	void awardItem(int type, int id, int num = 1, bool m_bNeedTag = false);
	void awardEquip(int lv);
	void award5bao();
	void awardBook(int lv);
	void awardIron(int lv);
	bool awardBookIron(int maxlv);
	// 普通高级兽决
	void awardShouJue1();
	// 稀有高级兽决
	void awardShouJue2();
	// 神兽兽决
	void awardShouJue3();
	void awardShouJue12();
	void awardShouJue23();
	void award125(int r, int maxbookironlv);
	void awardklv(int exp, int money = 0, bool onlyHero = false);
	void awardk(int exp, int money = 0, bool onlyHero = false);
	void award(int exp, int expbb = 0, int money = 0, bool onlyHero = false);

	void resetLangTime();
//	void FollowLv(int id,int lv=-1);
	void FreeFightList(int i);
	
	cTaskHuoDong m_TaskHuoDong;
	cInterfaceUseJiaJu m_UseJiaJu;
	cFangWu m_FangWu;
	void ResetAll();
	cEndState* m_pEndState;
	cMenuState* m_pMenuState;
	
	int _guaji = 0;
	int _autoGhost = 0;
	char* m_MaskList;
	cInterfaceChaKan m_ChaKan;
	TaskZhuXian m_ZhuXian;
	cTaskZhiXian m_ZhiXian;
	cTaskZhiXian2 m_ZhiXian2;
	cTaskZhiXian3 m_ZhiXian3;
	cTaskFB  m_TaskFB;
	void SetCharacter(int ID);

	// 人物模型 >= 2000
	cObj* AddEnemy(int pos = -1, bool our = false);
	cPetData* AddEnemy(int modeid, int lv, string name = "", sAddPoint* ap = nullptr, int pos = -1, bool our = false);
	cPcData* AddEnemy(int modeid, int lv, eMengPai mengpaid, string name = "", sAddPoint* addpoint = nullptr, int weaponLv = -1, int pos = -1, bool our = false);
	

// 	int AddPCEnemy(
// 		sTaskMapObj* pdata,
// 		int lv,
// 		sAddPoint* addpoint,
// 		sZiZhi* zizhi,
// 		eMengPai mengpaid,
// 		int stronglv = -1,
// 		int pos = -1,
// 		bool our = false);
// 
// 
// 	int AddPCEnemy(
// 		string name,
// 		int modeid,
// 		int lv,
// 		sAddPoint* addpoint,
// 		sZiZhi* zizhi,
// 		eMengPai mengpaid ,
// 		sItem2* pWeapon = 0,
// 		int petid = -1,
// 		int stronglv = -1,
// 		int pos =-1,
// 		bool our = false);
// 
// 
// 	int AddPCPetEnemy(
// 		ePetID modeid,
// 		int lv,
// 		sAddPoint* addpoint=0,
// 		eMengPai mengpaid = eMP_随机,
// 		string name = "",
// 		int stronglv = -1,
// 		bool bOut = false,
// 		int pos = -1);
// 
// 
// 	int AddPCPet(
// 		ePetID modeid,
// 		int lv,
// 		sAddPoint* addpoint,
// 		eMengPai mengpaid,
// 		string name = "",
// 		int stronglv = -1,
// 		bool bOur = false,
// 		int pos = -1);
// 
// 
// 	int AddPetEnemy(
// 		string name,
// 		int modeid,
// 		int lv,
// 		sAddPoint* addpoint,
// 		int stronglv=-1,
// 		int Pos = -1,
// 		bool out = false);
// 	int AddPetEnemy2(
// 		int modeid,
// 		int lv=-1,
// 		sAddPoint* addpoint=0,
// 		int stronglv=-1,
// 		int Pos = -1,
// 		bool our = false);
// 	int AddPC(
// 		string name,
// 		int modeid,
// 		int lv,
// 		sAddPoint* addpoint,
// 		sZiZhi* zizhi,
// 		eMengPai mengpaid,
// 		sItem2* pWeapon = 0,
// 		int petid = -1,
// 		int stronglv = -1,
// 		int pos = -1
// 		);

// 	int AddPet(
// 		string name,
// 		int modeid,
// 		int lv,
// 		sAddPoint* addpoint,
// 		int stronglv=-1,
// 		int Pos = -1);




	cInterfaceJianDing m_InterfaceJianDing;
	cInterfaceGive m_InterfaceGive;
	cInterfaceYingHang m_YingHang;
	cInterfaceXiuLian m_LearnXiuLian;
	cBangPaiJiNengXueXi m_LearnBangPaiSkill;
	cInterfaceLearnSkill m_LearnSkill;
	cTaskSM m_taskSM;
	int getAvgLv();//计算队伍平均等级
	int getMaxLv();
	int getMinLv();
	cInterfaceRanSe m_InterfaceRanSe;
	cChangeColor m_ColorManage;
	cItemSelect m_ItemSelect;
	cTriggerGive m_TriggerGive;
	//cTriggerTime m_TriggerTime;
	cTrigger m_TriggerFightSuccess;
	cTrigger m_TriggerFightFail;
	cTrigger m_TriggerFightEscape;
	cTriggerDialog m_TriggerDialog;
	cTrigger m_TriggerFightStart;
	cTriggerMapObj m_TriggerObjMap;
	cTriggerObj m_TriggerObj;
	cTriggerLv m_Triggerlv;
	cTaskNormal m_TaskNormal;
	cTaskBaotu m_TaskBaoTu;
	cTaskZhuaGui m_TaskZhuaGui;
	cTaskBangPai m_TaskBangPai;
	cTrigger  m_TriggerFightTurn;//干扰战斗
	cTaskFengYao _taskFengYao;
	//cText m_sFPS;
	string m_MusicName;
	cInterSelectFriendItem m_SelectFriendItem;
	cMySound  m_Mp3;
	//
	cWorldMap m_WorldMap;

	
	cTags m_Tags;
	cTag1 m_Tag1;
	cInterfaceTeam m_InterfaceTeam;
	
	int m_HeroID = 0;
	cCanvas m_Canvas;
	cZuoQi m_ZuoQi;
	int  AtutoGetEnemyNum(int nmin = 1, int nmax = 10);
	int GetPCFightNum(){ return GetLiveNum(0, 5); }

	//int  GetEnemyNum(int startid=10,int endid=20);
	int GetLiveNum(int start, int end);

	bool SwapFightOffset(int Original, int Target);
	bool ReadyToFight();
	int ReadTaskFightIndex(string name);
	cInterfaceChannel m_Channel;
	
	// 无效化
	void LockLv(int b = 0);//设定等级上限
	int GetLockLv上限();
// 	void SaveGlobal(sOstream& File);
// 	void LoadGlobal(sIstream& File);

	 RECT m_FullRect;
	 HBRUSH  m_blackbrush;
	
	bool SetEnemy(int EnemyType, int EnemyID, int lv, int AI);
	//让指定角色得到物品  如果不是可叠加物品最后一个参数作为等级使用
	bool Give(int CharID, sItem2* pItem);
	cWasFile m_PathPoint;
	ItemManager m_ItemManage;
	
	cInterfaceSmallMap m_InterfaceSmallMap; //控制显示小地图
	//从文件读取
	bool LoadCharacterData(int model, string name = "");
// 	bool LoadCharacterData2(int charactID, string Path);
// 	bool LoadCharacterData2(cObj*& data, string Path);
	cObj*  m_pNowSelect;
	string m_pNowSelectName;
	ulong m_pNowSelectHead;
	void setNowSelect(string name, ulong uid){ m_pNowSelectName = name; m_pNowSelectHead = uid; }
	void setNowSelect(cObj* obj){ if (obj)setNowSelect(obj->m_TrueName.GetString(), obj->GetID(POS_DIALOG)); }
	void setNowSelect(){ setNowSelect(m_pNowSelect); }
	void resetNowSelect(){ setNowSelect("", 0); }
	void dialogHead(ulong uid, string name, string text);
	void dialog(int mid, string name, string text);
	void dialog(int mid, string text);
	void dialog(string text);

	bool  FindAttackPoint(cObj* data,char* name);
	//寻找角色列表
	bool  FindCharacter(cObj*& data, int CharacterID);
	bool SetFightPet(int ID,int PetID,bool blimit=true);

	//产生一个召唤兽(注意,返回的资源在堆中,接收者如果不用需自行删除)
	bool AutoPet(cPet*& pPet, int ID, int StrongLv, int LV,sAddPoint addpoint);
	bool AutoPet(cPet*& pPet, int ID, int StrongLv, int LV);
	bool AutoPet(cPet*& pet, int modeid, int lv, bool addBlood = false);
	sAddPoint getAddpointFromPet(cPetData *data, bool is1Or0Blood = false);
	sAddPoint getAddpointFromMp(int mp, bool isAddBlood = false);
	int getModelFromMp(int mp);
//	sAddPoint getAddpointFromPet(const vector<sSkill*> &skills, bool is1Or0Blood = false);
	//bool SetUpOffset(sFightList* p);
//	bool  GivePcAPet(int charID, cPet* pPet,bool setfight=true);
	int CheckInTeam(string name);

	bool  FindNPCData(cNpc*& data, int NpcID);
	bool  FindData(cObj* data, int Id);
	//寻找召唤兽列表
	bool  FindPetData(cPet* pPet, int PetID);
	cPetManager m_PetDataManager;
	cSkillManager m_SkillManager;
	//战斗角色表
	vector<sFightWork> m_FightWorkList;
//	array<sFightWork, 2> m_FightWorkTemps;

	cWasFile m_Shadow;
	
	cWasFile m_FaceTextBack;
	vector<cObjWas> m_FaceTextBackp;
	cAI     m_AI;
	cFriend m_Friend;
	cInterfaceDoor m_InterfaceDoor;
	cInterfaceItem m_InterfaceItem;
	cInterfaceFB   m_InterfaceFB;
	cInterfacePet  m_InterfacePet;
	cInterfaceJiNeng m_InterfaceJiNeng;
	cInterfaceJob  m_Job;
	cInterfaceSystem m_InterfaceSystem2;
	cInterfaceFriendQiangHua2 m_InterfaceSystem;
	uiXiangRui _uiXiangRui;
	uiHeadTop _uiHeadTop;
	uiFoot _uiFoot;
	uiFoot2 _uiFoot2;
	uiAnimalSign _uiAnimalSign;
	uiComPet _uiComPet;
	uiCangKu _uiCangKu;
	uiChangeCharacter _uiChangeCharacter;
	uiDesc _uiDescription;
	uiSign _uiSign;

	cWasFile _wasHeadTop;
	int _wasHeadHigh = 20;
	int _langtimeOnce = 0;
	int _langtimeLast = -1;
// 	struct sWasDirection{ cWasFile was; int direction; };
// 	list<sWasDirection> _wasFoots;

	cMenu   m_Menu;
	cState  m_State;
	cCursor m_Cursor;
	vector<HFONT> m_hFont;
	HFONT m_hOldFont;
	HFONT m_hOldFont2;
	cPCHead m_PCHead;




	cInterfaceDialog m_Dialog;
	cInterFaceBuy   m_InterFaceBuy;
//	cInterFaceBuyPet   m_InterFaceBuyPet;
	uiBuyPet m_InterFaceBuyPet;
	cInterfaceDaZao m_Dazao;
	bool MoveObj();
	cFindPath m_FindPt;
	cObj* GetObjPointAt(long x, long y);
	cScript m_ScriptTemplate;

	cObj* FindObjByName(string Name);
	cObj* FindObjByNpc(sNpc* pNpc);
	cAccelator m_Accelator;


	bool ProcessInput();
	bool ProcessInterface();

	cInterfaceFather* m_Interface[c_InterfaceShowNum];
	bool InterfaceSetShow(cInterfaceFather* p,bool NeedShow);
	void ClearInterfaceSetShow();
	cInput Input;
	cInputDevice Mouse;
	cInputDevice Keyboard;
	bool FindObj();
	bool SortShow();

	//让队友跟随主角
	bool TeamFollow();

	void UpDateInput();
	CMainState();
	cObj*  m_pObj[MAX_OBJ_NUM];
	int m_ObjNumber;
	~CMainState();
	bool SetWork(int ID,int Target,int Pos);
	bool Init(void* pData=0);
	void Init2();
	void Init3();
	void initGame();
	
	HFONT EasyCreateFont(int h, string name, int weight=400);
	cTaskFather* FindTaskByID(int ID);
	int FindPetWeapon(string name);
	bool Frame(void* pData=0);
	bool ShowInterface();
	bool ShowInterface2();
	bool Free();
	cMyMap m_Map;
	

	vector<sNpcData> m_pNpcList;


	void LoadList();
	bool LoadWeaponList(string Path);
	int  ReadInt(char*& point);
	bool  ReadName(char*& point, char*& pName);
	ulong Readulong(char*& point);

	array<sCharacterData, 18> m_pCharacterDataList;
	
	cFightState* m_pFightState=0;
	void SetMouseOnMap(bool lock);
	bool GetLockMouse(){ return m_isMouseOnMap; }
	bool m_bInit3 = false;

	//全局变量
	cWasFile m_Cancel;
	cWasFile m_HpLine;
	cWasFile m_HpEmptyLine;
	cWasFile m_Button4;//四字按钮
	cWasFile m_Button2;
	void ShowObj();
	struct sDialogList
	{
		string name;
		ulong  idlist;
	};
	void SetDialogList(string name, ulong id);
	void SetDialogListPet(string name, ePetID petid,bool bJinJie=false);
	void SetDialogListNpc(string name, int npcid);
	void SetDialogListPC(string name, int pcid);
	void SetDialogList(cObj* pObj);
	void ClearDialogList(){ m_DialogList.clear(); }
	vector<sDialogList>  m_DialogList;//头像列表,用于对话时没出现的角色的头像


private:
	bool m_bInit2=false;
	bool m_LoadList = false;
	bool m_isMouseOnMap;
	
	int m_NumShow = 0;
	int   m_ShowTurnType[MAX_OBJ_NUM];
	void*  m_pShowTurn[MAX_OBJ_NUM];
	int m_PosYList[MAX_OBJ_NUM];
};


