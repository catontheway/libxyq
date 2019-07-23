#pragma once
#include "_inc.h"
#include <vector>
#include <string>
class cMyMap;
class CWFile;


class cInterfaceFather
{
public:
	int m_Sleeptime = 0;
	virtual void init() {}
	virtual void initShow() { }
	virtual BOOL ProcessInput();
	virtual bool ProcessInputMore() { return false; }
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	virtual void OnOff(BOOL NeedShow);
	void OnOff() { OnOff(!m_NeedShow); }
	virtual BOOL CheckRB() { return false; }
	virtual void move(int x, int y);
	virtual CWFile* getBack() { return &m_Back; }
	void setAlignLeft();
	void setAlignCenter();
	void setAlignRight();
	BOOL m_NeedShow=FALSE;
	int m_xPos=0;
	int m_yPos=0;
	int  m_Prex=0;
	int  m_Prey=0;
	BOOL m_bMoveMode=FALSE;
	BOOL m_bMove=FALSE;
	BOOL isInRect(long x, long y, CWFile* pPic);
	cWfileP m_Cancel;
	
	BOOL CheckOn(CWFile* pTarget, int id);
	BOOL CheckOn(cWfileP* pTarget, int id);
	BOOL CheckOn(cText5* ptext, int id);
	
	int m_Select=-1;
	int m_SelectPre=-1;
	CWFile* m_frampre=0;
	cWfileP* m_framprep=0;
	void ResetButton();

	struct sChild
	{
		enum class eType { File, Obj, Text };
		void addChild(eType _e, ulong uid, CWFile* file, string text, ulong tColor, int x, int y);

		sChild(ulong uid, string text, ulong tColor, int x, int y)
		{
			addChild(eType::File, uid, nullptr, text, tColor, x, y);
		}

		sChild(ulong uid, string text, int x, int y)
		{
			addChild(eType::File, uid, nullptr, text, RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		sChild(ulong uid, int x, int y)
		{
			addChild(eType::File, uid, nullptr, "", RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		sChild(CWFile* file, string text, ulong tColor, int x, int y)
		{
			addChild(eType::Obj, 0, file, text, tColor, x, y);
		}

		sChild(CWFile* file, string text, int x, int y)
		{
			addChild(eType::Obj, 0, file, text, RGB(0xFF, 0xFF, 0xFF), x, y);
		}

		sChild(CWFile* file, int x, int y)
		{
			addChild(eType::Obj, 0, file, "", RGB(0xFF, 0xFF, 0xFF), x, y);
		}


		sChild(string text, ulong tColor, int x, int y)
		{
			addChild(eType::Text, 0, nullptr, text, tColor, x, y);
		}

		sChild(string text, int x, int y)
		{
			addChild(eType::Text, 0, nullptr, text, RGB(0xFF, 0xFF, 0xFF), x, y);
		}


		int xx, yy;
		eType e;
		void* ptr = nullptr;
		void* ptr2 = nullptr;
		function<void()> onClick = nullptr;
		function<void(const sChild* c)> onFrame = nullptr;
		operator ulong() { return (ulong)ptr; }
		int tag = -1;
		bool checkon = true;
		bool visible = true;
	};

	void addChild(sChild c)
	{
		_children.push_back(c);
	}

	vector<sChild> _children;
	bool _isInit = false;
	bool _isRclose = true;
	int _backw = 0;
	CWFile m_Back;
};


class cInterfaceNumShuRu
{
public:
	int CountPos(int pos);
	int CountCaretPos(int xMouse, int yMouse);
	void SetCaretPos(int pos);
	void UpdateCaret();
	BOOL Process();
	void Show(cCanvas5* pCanvas);
	int m_num=0;
	void Init(RECT rect);
	void SetMaxNum(int num){ m_MaxNum = num; }
	cText5 m_tNum;
	
	void UpdateNum();
	void SetActive(BOOL bActive);
	void ShuRu(int num);
	void Erase(int pos);
	void Reset();
	void SetNum(int num);
	void SetHuChi(cInterfaceNumShuRu* huchi){ m_HuChiList.push_back(huchi); }
private:
	vector<cInterfaceNumShuRu*>  m_HuChiList;
	void Init2();
	int m_MaxNum=0;
	BOOL m_bActive = FALSE;
	int m_time=0;
	BOOL m_bInit = FALSE;
	CWFile m_Caret;
	vector<int>  m_numlist;
	int  m_numlong=0;
	int m_caretpos = -1;
	RECT m_rect;
	BOOL m_bEraseMode = FALSE;
	BOOL m_bInEraseMode = FALSE;
	int m_EraseStart;
	int m_EraseEnd;
};

class cDescribe :public cInterfaceFather
{
public:
	void OnOff(BOOL bonoff);
	void Set(int xMouse, int yMouse, DWORD BigHead, int num, string* pTex,DWORD* colorlist=0, int yOffset = 25);
	void Init();

	virtual BOOL ProcessInput(){ return TRUE; }
	virtual BOOL CheckL();
	virtual BOOL Show(cCanvas5* pCanvas);
	cSprite9 m_Back;
	static CWFile m_DescribeBack;
// private:
	DWORD m_Color[16];
	
	BOOL m_bInit=FALSE;
	CWFile m_BigHead;
	cText5  m_Text[16];
	int m_Num;
};
class cItemSelect
{
public:
	vector<CWFile> m_ItemHead;
	vector<cText5>  m_tItemNum;
	vector<int> m_ItemNum;
	void Init();
	int Process(int xMouse,int yMouse);
	void Show(cCanvas5* pCanvas);
	void Move(int xPos, int yPos);
	void Update(cCharacter* pc=0);
	cDescribe m_Describe;
	void SetSelectMark(int id);
private:
	BOOL m_bInit=FALSE;
	int m_Select;
	int m_xPos;
	int m_yPos;
	RECT m_Rect;
	CWFile m_SelectMark;
	CWFile m_MouseOnMark;
	
};
class  cInterFaceBuy: public cInterfaceFather
{
public:
	
	void UpdateText();
	RECT m_Rect;
	CWFile m_MouseOnMark;
	
	CWFile m_SelectMark;
	int m_TrueSelect;
	int m_TrueSelect2;
	virtual BOOL ProcessInput();
	virtual BOOL CheckL();
	BOOL CheckRB();
	BOOL Init();
	void Open(int id);
	BOOL Set(sItem2& item,int rate);
	BOOL Move(int x, int y);
	BOOL Show(cCanvas5* pCanvas);
	cText5 m_Text[6];
	
	vector<sItem2> m_Item;
	vector<int> m_pricerate;
	CWFile m_ItemHead[20];
	void OnOff(BOOL bshow);
	cDescribe m_Describe;
	void Reset();
private:
	int m_ItemNum = 0;
	int m_page = 0;
	void AddPage();
	void SubPage();
	void Update();
	BOOL m_bInit=FALSE;
	int m_PriceTotal;
	void CoutTotal();
	CWFile m_Back;
	
	CWFile m_Button;
	cInterfaceNumShuRu m_NumBuy;

	CWFile m_Left;
	CWFile m_Right;
};
struct sFriendList;

struct sShangPinPet
{
	int m_modeid;
	string m_name;
	vector<int>  m_skillid;
	int m_price;
	sAddPoint m_addpoint; //加点
	sZiZhi m_zizhi;//资质
	sChangeColorData2 m_ranse;
	void operator=(sShangPinPet pet)
	{
		m_modeid=pet.m_modeid;
		m_name=pet.m_name;
		m_skillid.swap(pet.m_skillid);
		m_price=pet.m_price;
		m_addpoint=pet.m_addpoint; //加点
		m_zizhi=pet.m_zizhi;//资质
		m_ranse=pet.m_ranse;
	}
	void Set(int modeid, sAddPoint* addpoint = 0, int stronglv=100, BOOL needskill = FALSE);
	void AddSkill(int id);
	void Save(ofstream& File);
	void Read(ifstream& File);//从商店读取简化的召唤兽
	void Load(ifstream& File,int positon);//从存档读取
	void LoadEasy(int id,int strong = -1);
};


class  cInterFaceBuyPet : public cInterfaceFather
{
public:
	
	void UpdateText();
	RECT m_Rect;
	CWFile m_MouseOnMark;

	CWFile m_SelectMark;
	int m_TrueSelect=-1;

	virtual BOOL ProcessInput();
	virtual BOOL CheckL();
	BOOL CheckRB();
	BOOL Init();
	BOOL Set(sShangPinPet& item, int rate);
	BOOL Move(int x, int y);
	BOOL Show(cCanvas5* pCanvas);
	cText5 m_Text[6];
	int m_ItemNum = 0;
	sShangPinPet m_Item[20];
	int m_pricerate[20];
	CWFile m_ItemHead[20];
	void OnOff(BOOL bshow);
	void Init2(sFriendList* plist, UINT page1, UINT page2);
	void Init3();
	void AddPage();
	void SubPage();
	void UpDateTeam(string name,int stronglv,int lv=-1);
	sShangPinPet& GetPet3(int id);
private:
	CWFile m_Left;
	CWFile m_Right;
	vector<sShangPinPet> m_ShangPinList[17];
	vector<sShangPinPet> m_ShangPinList3;
	BOOL m_bInit3=FALSE;
	int m_page=0;
	int m_page2=0;//比如0级召唤兽,如果数量超过20,则m_page2可以有两页
	sFriendList* m_plist=0;
	BOOL m_bInit = FALSE;
	int m_PriceTotal;
	void CoutTotal();
	CWFile m_Back;
	
	CWFile m_Button;
	cInterfaceNumShuRu m_NumBuy;
};
enum eFightMenu
{
	FMENU_NORMAL,  //普通
	FMENU_MAGIC2,   //法术目标选择
	FMENU_ITEM,  //物品选择
	FMENU_GRAB,   //抓
	FMENU_ITEM2,  //物品目标选择
	FMENU_MAGIC, //法术目标
	FMENU_PET,   //召唤
	FMENU_PROTECT, //保护
	FMENU_SPECIAL,  //特技
//	FMENU_CONDUCT,   //指挥
//	FMENU_FABAO,  //法宝
	FMENU_SPECIAL2
};
class cInterfaceConduct :public cInterfaceFather
{
public:
	void PrePare();
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	virtual void OnOff(BOOL NeedShow);
	BOOL CheckRB();
	void SetID(int id);
	void  Init();
	void Move(int x, int y);
	void Def(int id, BOOL bDef = TRUE);
	void SetTarget(int id,int target);
private:
	cObj* m_pObj = 0;
	int m_Mode=-1;
	int m_FighterNum;

	CWFile m_Back;//指挥界面  0xCC7BC6C6
	BOOL m_bInit = FALSE;
	cText5 m_Title;
	int  m_IdSelect;
	vector<cWfileP> m_Buttonp;
	vector<cText5> m_tButtonp;
	vector<cText5> m_tName;
	vector<cText5> m_tTargetName;
};


class cInterfaceFight:public cInterfaceFather
{
public:
	cInterfaceFight();
	void SetTeamControl(BOOL bC);
	cInterfaceConduct m_InterfaceConduct;
	void OnOff(BOOL NeedShow);
	RECT m_ItemRect;
	cDescribe m_Describe;
	void InitPet();
	void ShowPet();
	void MovePet(int x, int y);

	CWFile m_Button;
	cText5 m_PetName[8];
	cText5 m_PetProPerty[6];
	cText5 m_Text;
	CWFile	m_UpB;
	CWFile	m_DownB;
	int  m_PetPage;
	int m_PetIDSelect;
	int m_TruePetIDSelect;
	CWFile m_PetBack;
	CWFile m_ItemDataBack;
	CWFile m_BackMagic6;//法术界面  0x2FD95E30
	CWFile m_BackMagic10;//法术界面 0x69823EE5
	CWFile m_BackMagic14;//法术界面  0A8B7D87
	CWFile m_BackMagic20;//法术界面  0x32F119A5
	CWFile m_BackMagic30;// 0x4226BD41
	CWFile m_BackPet; // 0xE87F26E1
	CWFile m_BackItem;//  0xE3AEF018
	BOOL AddTurn();
	BOOL CheckTurn(int ID);
	
	BOOL UpdateMenu();
	void SwitchMode(eFightMenu eFightMenu);
	void SelectMode(eFightMenu eFightMenu);
	BOOL Move(int x, int y);
	void MoveMagicBack(int x,int y);
	void MoveMenu(int x, int y);
	void MoveItem(int x,int y);
	int  m_NumofButtonShow;  //需要显示的按钮数


	CWFile m_Magic;
	CWFile m_Stunt;  //特技
	CWFile m_Conduct; //指挥
	CWFile m_Item;
	CWFile m_Defend;
	CWFile m_Guard;
	CWFile m_Summon; //召唤
//	CWFile m_Auto;
	CWFile m_Catch; //抓
	CWFile m_Fabao;
	CWFile m_Escape;  
	eFightMenu    m_MenuMode;
	void   InitItem(int offset);
	//BOOL   SetSpecialMode(BOOL b);
	CWFile m_ItemSelectFrame;
	int    m_NumofSkill;
//	CWFile m_ItemHead[20];

	sSkill* m_pSkillShow[30];
	
	sSkill* m_pSkillSelect=0;
	CWFile m_SkillHead[30];

	BOOL   InitMagic2();
	BOOL   InitMagic();
	BOOL   InitSpecial();
	void   MoveSpecial(int x, int y);
	void   ShowSpecial(cCanvas5* pCanvas);
	BOOL   ProcessSpecial();
	BOOL   ProcessSpecial2();
	BOOL  ProcessGrab();
	BOOL  ProcessItem2();
	
	BOOL  ProcessProtect();
	BOOL ProcessPet();
	cText5  m_TitleT;
	cText5  m_SkillPreSelectT;
	cWfileP m_MagicBack;
	int    m_SpecialNum=0;
	int	   m_SpecialID[6];
	CWFile m_SpecialHead[6];
	int    m_SpecialSelect;

	virtual BOOL ProcessInput();
	BOOL ProcessMenu();
	//物品
	CWFile m_PetSelectBack[2];
	CWFile m_ItemBack;
	
	int  m_ItemSelect;
	
	void Init();
	BOOL m_bInit=FALSE;
	BOOL SetNowFight(int fight);
	BOOL Show(cCanvas5* pCanvas);
	BOOL   m_ItemCanUse[20];


	int  m_NowFighterID;
	int  m_PreFighterID;

	
	cFightState* m_pFightState;
	BOOL CheckL();
	//移动
	int m_xMenuPos;
	int m_yMenuPos;
	BOOL m_MoveBack = FALSE;
	int m_OldxMouse;
	int m_OldyMouse;
	void SetControl(int id, BOOL cancontrol){ m_bCanControl[id] = cancontrol; }
	BOOL CheckControl(int id);
	// 日期版专用
	int _timeWaiting = 0;
private:
	BOOL m_bCanControl[20];
	cObj* m_pObjSelect=0;
	//int SelectObj(int Userid,int type);
	inline  BOOL ProcessItem();
	inline  BOOL ProcessNormal();
	inline  BOOL ProcessMagic2();
	inline  BOOL ProcessMagic();
	
#if ccc_date
	BOOL RunA();
public:
	BOOL RunQ();
private:
#endif
	inline	BOOL CheckA();
	inline	BOOL CheckQ();
	inline	BOOL CheckD();
	inline	BOOL CheckT();
	inline	BOOL CheckG();
	inline	BOOL CheckW();
	inline	BOOL CheckX();
	inline	BOOL CheckS();
	inline	BOOL CheckE();
	inline	BOOL CheckV();

	inline	BOOL CheckRButton();
	inline	void Def();
	inline	void Guard();
	inline	void ShowMenu(cCanvas5* pCanvas);
	inline	void ShowItem(cCanvas5* pCanvas);
	inline	void ShowMagic(cCanvas5* pCanvas);
};
struct sTalkList;

struct sPoem
{//一首诗
	string m_title;
	string m_name;
	vector<string> m_context;
	void Read(ifstream& File)
	{
		File >> m_name;
		File >> m_title;
		int num;
		File >> num;
		m_context.resize(num);
		for (int i = 0; i < num; i++)
			File >> m_context[i];
	}
};
struct	sQuestion
{
	string title;
	vector<string> select;
	int  answer; //正确答案

	void Auto()//改变题目中选择的位置
	{
		int a = rand() % select.size();
		if (a != answer)
		{
			swap(select[answer], select[a]);
			answer = a;
		}
		a = (a + 1) % select.size();
		int b = rand() % select.size();
		if (a != b)
		{
			swap(select[a], select[b]);
		}
		if (b == answer)answer = a;
	}
};
class cInterfaceDialog :public cInterfaceFather
{
private:
	vector<sPoem>  m_PoemList;
	void AutoGetPoem(sPoem*& out);//随机得到标题,但不能为title;
public:
	string GetTrueSelect();
	void GetQuestion(sQuestion& quest, int selectnum = 4);
	
	void InitQuestion();

	BOOL m_bInitQuestion = FALSE;
	int m_retSelect=-1;

	void Talk(sTalkList* talk);
	void Talk(string context ,string name,DWORD head);
	void TalkNObj(string context);
	void TalkObj(string context,cObj* p=0);
	sFaceText m_ContextList;
	CWFile m_DialogBack;
	int    m_NumOfSelect;
	vector<cText5>  m_SelectT;
	int    m_NowMouseOnSelect=-1;
	void Reset();
	void Reset2();
	CWFile m_NameBack;
	void OnOff(BOOL bShow);
	
	void Init();
	void SetObj(string name);
	void SetObj(cObj* pObj);
	void SetHead(DWORD head);
	void SetPet(cPet* p);
	
	BOOL  ProcessInput();
	BOOL  CheckL();
	void Close();
	BOOL  Show(cCanvas5* pCanvas);
	BOOL  Free();
	void  SetString(string str="", string select1="", string select2="", string select3="",string select4="");
	void  Question();
	cObj* m_pObj;
	void SetTrigger(cTaskFather* pTask,int defaultret ,int stage0=-1, int stage1=-1, int stage2=-1, int stage3=-1);
	BOOL m_bRetSelect = FALSE;
	sQuestion m_Question ;
private:
	
	cTaskFather* m_pTask = 0;
	int m_retstage[5];
	BOOL m_Reset=FALSE;
	CWFile m_Head;
	BOOL m_bInit = FALSE;
};


struct sFriendList
{
	int GetTeamID();
	BOOL CheckInTeam();
	//BOOL m_bOnLine;
	int m_traderLV=0;
	int m_Feeling=0;//好感度
	string m_Name;//名字
	string m_dataFileName;//所处文件的名字
	int  m_stronglv;//角色的强度会改变
	int  m_modeid;
	BOOL m_bDuJie=0;//是否渡劫
	//武器造型
	int m_weapontype=-1;
	int m_weaponid=-1;
	cJinJieNum m_JinJieNum;
	sZiZhi m_zizhi;//资质
	//染色
	sChangeColorData2 m_Ranse;
	//钱
	int  m_money;
	//坐骑
	BOOL  m_bOnZuoQi=0;
	int   m_ZuoQiID=-1;
	sChangeColorData m_ZuoQiRanse;
	int   m_bZhuangShi=0;
	int   m_ZhuangShiID=-1;
	sChangeColorData m_ZhuangShiRanse;

	int  m_FightBB=-1;//首发召唤兽
	vector<sShangPinPet>  m_BBList;
	//vector<int>  m_PetSkillList;
	void Save(ofstream& File);
	void Load(ifstream& File);
	DWORD GetFriendHead();
	DWORD GetDialogHead();

	bool isFound(const std::string& file_or_name);
};
class cInterfaceFriendQiangHua :public cInterfaceFather
{
public:
	void Set(sFriendList& list);
	void Update();
	void Init();
	BOOL CheckRB();
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	virtual void OnOff(BOOL NeedShow);
	void Move(int xPos, int yPos);
	void Change(int id);
private:
	BOOL m_bUpdateTeam;
	int m_Mode=0;
	sFriendList* m_pData;
	cWfileP m_Buttonp[12];
	cText5 m_Name;
	cText5 m_Money;
	cText5 m_title;
	BOOL m_bInit = FALSE;
	CWFile m_Back;
	
	cText5 m_Text[12];
};
class cFriend:public cInterfaceFather
{
public:
	cInterfaceFriendQiangHua m_friendqianghua;
	static const int m_MaxNameNum = 8;
	static const int _hInv = 28;
	static const int _yStart = 100;
	cText5 m_ButtonText[4];
	cWfileP m_Buttonp[4];
	
	CWFile m_PetSelectBack[2];
	int  m_TrueFriendSelect=-1;

	cText5 m_NameList[m_MaxNameNum];//
	CWFile m_NameListHead[m_MaxNameNum];
	BOOL UpdateList(int page=-1);
	CWFile m_Back;
	BOOL Move(int x, int y);
	BOOL Init();
	struct sMessageList
	{
		string	messagePath;
		int id;
		cTaskFather* p;
		int taskid;
		void Save(ofstream& File);
		void Load(ifstream& File);
	};
	void AddMeesage(string path, int id, cTaskFather* ptask, int taskid);
	vector<sMessageList> m_MessageList;

	BOOL ProcessInput();
	BOOL CheckL();
	void JuanZeng(int num);
	void UnJuanZeng(int num);
	BOOL CheckRB();
	BOOL Show(cCanvas5* pCanvas);
	
	void OnOff(BOOL NeedShow);
	
	BOOL Invite(string datafilename, int fighterid = -1);
	BOOL UnInvite(string datafilename);
	BOOL UnInvite(int id);
	vector<sFriendList> m_FriendList;
	void Save(ofstream& File);
	void Load(ifstream&File);
	BOOL AddFriend(string datafilename);
	int FindFriend(string datafilename);
	sFriendList* FindFriend2(string datafilename){ return &m_FriendList[FindFriend(datafilename)]; }
	void ReMove(string name);
	void AddDay();
private:
	void operator=(cFriend& list){}
	BOOL Invite(int id, int fighterid = -1);//邀请   返回是否邀请成功
	RECT m_Rect;
	BOOL m_bInit = FALSE;
	int m_nowPage=0;
	int m_NameNum=0;
};


struct sNpc;
class cInterfaceSmallMap:public cInterfaceFather
{
public:
	cInterfaceSmallMap(){ m_NeedShow = FALSE; }
	void Init();
	BOOL ProcessInput();
	BOOL CheckL();
	CWFile m_PathPoint;
	cWfileP m_PathPointp[30];
	CWFile m_PCPoint;
	BOOL Show(cCanvas5* pCanvas);
	int m_xTarget;
	int m_yTarget;
	void OnOff(BOOL bShow);
	cText5 m_MousePos;
	CWFile m_MousePosBack;
private:
	
	BOOL m_bInit = FALSE;
	BOOL PrePareFindPath(int xMouse, int yMouse);

public:
	void clear();
	void addNpc(const std::string& name, int x, int y, ulong color);
	void addNpc(const sNpc* npc);
	struct sText5{ cText5 t; int x, y; };
	std::vector<sText5*> _npcs;
};
class cShiCheng
{
public:
	void Save(ofstream& File);
	void Load(ifstream& File);

	DWORD  m_23_1;  //子
	DWORD  m_1_3;   //丑
	DWORD  m_3_5;   //寅
	DWORD  m_5_7;   //卯
	DWORD  m_7_9;   //辰
	DWORD  m_9_11;  //巳  
	DWORD  m_11_13;  //午
	DWORD  m_13_15;  //未
	DWORD  m_15_17; //申
	DWORD  m_17_19; //酉
	DWORD  m_19_21;  //戌
	DWORD  m_21_23;  //亥

	CWFile m_Data;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int s;
	int ss;
	int m_fps;
	int m_week; //星期
	cShiCheng()
	{
		m_23_1 = 0x361FA820;
		m_1_3 = 0xC0A66903;
		m_3_5 = 0xD1D11294;
		m_5_7 = 0xAA7DEB05;
		m_7_9 = 0x21274A87;
		m_9_11 = 0x9C4978D;
		m_11_13 = 0xC9E2F072;
		m_13_15 = 0x2ACB36B2;
		m_15_17 = 0xC26BF189;
		m_17_19 = 0x1AA170AE;
		m_19_21 = 0x7921D3A3;
		m_21_23 = 0xEA7CAB84;
		m_Data.SetX(0);
		m_Data.SetY(25);
		m_Data.SetStatic(TRUE);
	}
	void SetFPS(int fps){ fps = m_fps; }
	void UpdateTime(); //前进一毫秒
	void AddMinute(int add);
	void AddHour(int num=1);
	void AddDay();
	void AddMonth();
	void AddYear();
	void Init(int fps, int y, int m, int d,int h, int mi, int secend, int millisecond = 0)
	{
		m_fps = fps;
		year = y;
		month = m;
		day = d;
		hour = h;
		minute = mi;
		s = secend;
		ss = millisecond;
		CountDay();
		UpdateShiCheng(hour);
	}
	void CountDay();
	void UpdateShiCheng(int h);
	BOOL CheckWhite(){ return m_bWhite; }
private:
	BOOL m_bWhite;
};

class cInterfaceDoor:public cInterfaceFather
{
public:
	int m_SaveNum=0;
	void OnOff(BOOL NeedShow){};
	cText5 m_CharacterPos;
	char   m_MapNameBuf[50];
	cText5  m_MapName; 
	BOOL  m_MapNameNeedShow;//是否显示地图的名字
	cShiCheng m_TimeShiCheng;//时辰
	CWFile m_SmallMap;
	int    m_time;  
	CWFile m_Back;
	CWFile m_Door;
	CWFile m_WorldmapGlim; //灯笼
	CWFile m_Glim;
	CWFile m_MapGlim;
	int   m_GlimSelect;
	CWFile m_SmallPeople[2];
	BOOL ProcessInput();
	void UpdatePos(cObj* pObj);
	BOOL CheckL();
	void Init();
	BOOL Show(cCanvas5* pCanvas);
	void SetName(string name);
	cInterfaceDoor(){ m_time = 0; }
	int m_xoldHeroPos;
	int m_yoldHeroPos;
	int wid = 70;
	BOOL m_bRunMode=0;
	void SetTrigger(cTaskFather* pFather=0,int stage=-1,int least=1024);
	void CheckFight();
	int m_AvoidFight = 0;
	void SetWhite(BOOL b);
	BOOL CheckWhite(){ return m_bWhite; }
	int m_HeroX;
	int m_HeroY;
	void Save(ofstream& File);
	void Load(ifstream& File);
	void SetHalf(BOOL bTrue = -1);
	cTaskFather* m_pTask;
	int m_stage;
private:
	BOOL m_bHalf = FALSE;
	BOOL m_bWhite=2;
	BOOL m_bInit = FALSE;

	int m_timeleast;  //两次遇怪的最低时间间隔
	int  m_rate;//遇怪率
	int m_nowtimeleast=200;
	

};

class cInterfaceFB:public cInterfaceFather
{
public:
	void OnOff(BOOL NeedShow);
	BOOL CheckRB();
	void Init();
	BOOL ProcessInput();
	BOOL Show(cCanvas5* pCanvas);
	BOOL CheckL();
	BOOL Move(int x, int y);
	//void Reset();//重置副本状态
	vector<cText5> m_tFBName;
private:
	int m_TrueSelect;
	RECT m_Rect;
	CWFile m_MouseOnBack;
	cText5 m_TButton;
	cText5 m_Title;
	CWFile m_Button;
	CWFile m_Back;
	BOOL m_bInit = FALSE;
};
class cInterfacePetSkill :public cInterfaceFather
{
public:
	int m_ItemDataTime = 0;
	void Move(int x, int y);
	void MoveSkillHead(int x,int y);
	void UpdateData(cPetData* pPetData, BOOL candashu);
	void NextPage(BOOL bnext=TRUE);
	void Init();
	virtual BOOL ProcessInput();
	virtual BOOL CheckL();
	void OnOff(BOOL NeedShow);
	BOOL CheckRB();
	virtual BOOL Show(cCanvas5* pCanvas);
	int m_FightID = 0;
	CWFile m_back;
	cWfileP m_Cancel2;
	RECT m_Rect;
	BOOL m_bDaShuMode = 0;
	cWfileP m_EquipBackp[3];
	CWFile m_EquipHead[3];
	
private:
	BOOL m_bCanDaShu=FALSE;
	BOOL m_bInit=FALSE;
	int m_SkillSelect;

	cText5 m_DaShuText[2];
	int m_DashuSkillSelect;
	BOOL  InitDaShuMode();//如果角色的道具栏里没有技能书,返回False;
	CWFile m_DaShuHead[9];
	int    m_DaShuItemId[9];//记录角色的哪里有技能书
	cPetData* m_pPetData;
	cText5 m_TPetProPerty[9];
	int m_SkillPage = 0;
	int m_NumSkill;
	CWFile m_SkillHead[12];
	sItem2* m_pEquip[3];
	CWFile  m_EquipBack;

	cWfileP m_SkillSelectHead;
	int m_DaShuNum;
	CWFile m_DaShuBack;
	CWFile m_NextPage;
	
	
	cDescribe m_Describe;
};

class cInterfaceChaKan :public cInterfaceFather
{
public:
	void Init();
	void Set(cObj* data);
	void Set(sFriendList& list);
	void Set(sShangPinPet& list);
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	virtual void OnOff(BOOL NeedShow);
	void Move(int xPos, int yPos);
	BOOL CheckRB();
	void MovePetEquip();
private:
	cText5 m_MengPai;

	cText5 m_Property[15];
	cPetData* m_data;
	CWFile m_Back;
	BOOL m_bInit = FALSE;
	cInterfacePetSkill m_PetSkill;
	CWFile m_Pic[4];
	cWfileP m_Shadow;
	cObj m_Obj;
	// 日期版专用
	cObj *_obj = nullptr;
};

class cInterfacePet:public cInterfaceFather
{
public:
	void AddExp(cPetData* pPetSelect, INT64 num);
	cInterfacePetSkill m_PetSkill;
	void OnOff(BOOL NeedShow);
	//CWFile* m_frampre;
	//cWfileP* m_framprep;


	BOOL   Move(int x, int y);//移动界面
	CWFile m_UpB;
	CWFile m_DownB;
	//CWFile m_ItemDataBack;
	
	CWFile m_SetAttackB;
	CWFile m_AddPoint[5];
	CWFile m_SubPoint[5];
	CWFile m_XunYang;
	CWFile m_ChaKanZiZhi;
	CWFile m_FreePet;//放生
	cWfileP m_SetAddPoint;//设置加点
	BOOL  m_bAddPoint=FALSE;
	void   FreePet();
	BOOL   m_FreePetMode;
	//CWFile m_DaShu;
	int m_SkillPage;//如果技能数超过12个,需要翻页
	int m_PetPage=0;//如果BB数超过4个,需要页
	
	CWFile m_back;
	
	CWFile m_PetSelectBack[2];
	// 日期版专用
	cWfileP _btnJJ;
	
	cText5 m_TPetName[4];
	void Init();

	BOOL MovePetProPerty();
	BOOL CheckL();
	BOOL ProcessFreePet();
	BOOL ProcessInput();
	BOOL UpdateDescript(CWFile* pHead,sPetSkill* pPet,int xMouse,int yMouse);
	BOOL Show(cCanvas5* pCanvas);
	BOOL SetPage(int page);
	void UpdateList(int page);
	//BOOL InitPage();
	void UpDateExp();
	void UpDateByLvUp();  
	int m_TrueSelect;
	

	int m_ItemDataTime;
	
	cText5 m_TSkillSelectData[2];
	//CWFile* m_PetPic[4]; //一个召唤兽可能由4个部分组成,另外还有个阴
	cObj m_PetObj;
	//cWfileP m_Shadow;
	int m_PetSelectID=0;
	
	cText5 m_TPetProPerty[25];
	~cInterfacePet();
	BOOL Free();
	void UpdatePointButton();
	void UpdateProPerty();
	// 日期版专用
	cInterfacePet();
	void setCharactor(int id = -1);
	void setPointTemps();
private:
	
	BOOL m_bInit=FALSE;
	cObj  m_FreePetObj;
	BOOL SelectPet(int id);
	/*BOOL CheckOn(CWFile* pTarget, int id);
	BOOL CheckOn(cWfileP* pTarget, int id);*/
	/*int m_xMouse;
	int m_yMouse;*/
	// 日期版专用
	cCharacter *_charactor = nullptr;
	int _heroID;
	vector<int> _pointTemps;

};
class cInterfaceJiNeng:public cInterfaceFather
{
private:
	
	int m_MiaoShuID=-1;
public:
	CWFile m_SelectBackXiuLian;
	cWfileP* m_pPreMode=0;
	void SetMode(DWORD mode);
	void OnOff(BOOL NeedShow);
	BOOL CheckL();
	CWFile m_Data;
	vector<cText5> m_BText;
	cText5 m_ZhuJiNengLv[7];
	cText5 m_FuZhuJiNengLv[14];
	cInterfaceJiNeng();
	
	DWORD m_ZhuJiNeng;
	DWORD m_XiuLian;
	DWORD m_FuZhuJiNeng;

	
	cWfileP m_SmB;
	cWfileP m_FuZhuB;
	cWfileP m_learnSkillB;
	cWfileP m_XiuLianB;
	void Init();
	BOOL ProcessInput();
	void Set(DWORD ID);
	BOOL Show(cCanvas5* pCanvas);
	BOOL Move(int x,int y);
	void MoveMainSkill(int x,int y);
	void MoveFuZhuSkill(int x, int y);
	void MoveXiuLian(int x, int y);
	CWFile m_ZhuJiNengHead[7];
	CWFile m_SpecialSkill[6];
	int    m_JiNengHeadNum;

	sSkill* m_JiNengHeadData[14];
	CWFile m_JiNengHead[14];
	CWFile m_TeJiHead[6];
	int    m_NumMiaoShu=0;
	vector<cText5>  m_MiaoShu;
	int    m_SpeciallSkillSelect;
	int    m_JiNengSelect;
	int    m_SkillSelect;
	int    m_dustSkillSelect;
	vector<cText5>  m_TXiuLian;
	BOOL   UpdateJiNeng();
	BOOL   m_bUpdateJiNeng=0;
	BOOL   UpdateXiuLian();
	BOOL   UpdateMainSkill();
	BOOL   UpdateFuZhuJiNeng();
	// 日期版专用
	void setCharator(cCharacter *charactor){ _charactor = charactor; }
private:
	BOOL m_bInit = FALSE;
	// 日期吧专用
	cCharacter *_charactor = nullptr;
};


class cTaskFather;
struct sJob  //表示一个任务
{
	cTaskFather* m_pTask=0;
	int m_Stage=-1;
	string m_Title;
	string m_Context;
	int m_Time=0;
	void Set(string title, string context, int time, cTaskFather* task, int Stage)
	{
		m_Stage = Stage;
		m_Time = time;
		m_Context = context;
		m_Title = title;
		m_pTask = task;
	}
	void operator=(sJob& target)
	{
		m_Stage = target.m_Stage;
		m_Context = target.m_Context;
		m_pTask = target.m_pTask;
		m_Title = target.m_Title;
		m_Time = target.m_Time;
	}
};
struct sJobCharcter
{
	string characterName;
	int xPos;
	int yPos;
	string MapName;
	int direction;
	int TeamPos;
	string taskName;
};

class cCanvas5;
class cInterfaceJob:public cInterfaceFather
{
public:
	void CheckErr();
	BOOL CheckHaveJob(int ID);//检测是否存在某种任务
	void SetSelect(int select);
	void UpDatePageTitle();
	int m_Page = 0;
	BOOL AddaJob(sJob& job,int huanshu=-1);
	BOOL ReMoveJob(cTaskFather* p);
	void Reset(){ m_JobList.clear(); }
	
	cText5 m_TitleList[8];
	sFaceText m_Context;
	void OnOff(BOOL NeedShow);
	//CWFile* m_pPreButton;
	
	vector<CWFile> m_Back;
	int  m_gap;
	CWFile m_Up;
	CWFile m_Down;
	int m_Check;
	BOOL Move(int x, int y);
	sJob m_List[10];
	CWFile m_Job;
	void Init();
	BOOL ProcessInput();
	BOOL CheckL();
	BOOL CheckRB();
	BOOL Show(cCanvas5* pCanvas);
	void MoveContext(int x, int y);
	void Save(ofstream& File);
	void Load(ifstream& File);
	
private:
	vector<sJob> m_JobList;
	BOOL m_bInit=FALSE;
};


class cTrigger;
class cObjTrigger;
class cMapObjTrigger;
class cLvTrigger;
class cInterfaceSystem:public cInterfaceFather
{
public:
	void GetSaveTitle(vector<string>& list);
	void Save(int id);
	void Load(int id);
	cWfileP m_ExtGame;
	cWfileP m_SaveGame;
	cWfileP m_LoadGame;
	cInterfaceSystem(){ m_xPos = 100; m_yPos = 100; }
	BOOL ProcessInput();
	bool showSaveLoad(bool sav);
	bool processSaveLoad(bool sav);
	BOOL CheckL();
	BOOL CheckRB();
	CWFile m_Back;
	cText5 m_tExtGame;
	cText5 m_tSaveGame;
	cText5 m_tLoadGame;
	cText5 m_tTitle;
	//sFaceText m_tTime;
	void Init();
	BOOL Move(int x, int y);
    BOOL Show(cCanvas5* pCanvas);
	void OnOff(BOOL needshow);

private:
	int m_bMode=0;
	BOOL m_bInit=FALSE;
	void SavePos(ofstream& File);
	void SaveFriend(ofstream& File);

	void SaveFightList(ofstream& File);
	void SaveTrigger(ofstream& File);
	void SaveATrigger(cTrigger* trigger, ofstream& File);
	void SaveObjTrigger(cObjTrigger* trigger, ofstream& File);
	void LoadObjTrigger(cObjTrigger* trigger, ifstream& File);




	void LoadPos(ifstream& File);
	
	void LoadFriend(ifstream& File);
	
	void LoadFightList(ifstream& File);
	void LoadTrigger(ifstream& File);
	void LoadATrigger(cTrigger* trigger, ifstream& File);
	
};
class cMenu:public cInterfaceFather
{
public:
	void OnOff(BOOL NeedShow){};
	CWFile* m_NowSelectPic;
	BOOL Move(int x, int y);
	
	cText5 m_Text;
	int m_gap;
	int m_SelectPre;
	CWFile m_Trade;
	CWFile m_back;
	CWFile m_Attack;
	CWFile m_Team;
	CWFile m_Pet;
	CWFile m_Item;
	CWFile m_SkillAccelater;
	CWFile m_Info;
	CWFile m_Give;
	CWFile m_BangPai;
	CWFile m_System;
	CWFile m_job;
	void Init();
	BOOL Show(cCanvas5* pCanvas);
	void Select(int x);
	virtual BOOL ProcessInput();
	virtual BOOL CheckL();
};
class cCursor5
{
public:
	int SelectObj(int UserID, int Type, cObj*& pObj);
	int m_FollowTime=0;
	BOOL   m_FollowMode;
	DWORD   m_Give;
	DWORD   m_Normal;
	DWORD   m_Forbid;
	DWORD   m_Trade;
	DWORD   m_Hande;
	DWORD   m_Attack;
	DWORD   m_Magic;
	DWORD   m_Team;
	DWORD   m_Guard;
	DWORD   m_Grab;
	DWORD   m_No;
	CWFile  m_Data;
	CWFile  m_Click;
	vector<cWfileP>  m_Clickp;
	cCursor5();
	void Set(DWORD  Type)
	{
		if (m_Data.m_NowID == Type)return;
		m_Data.Load(Type); 
	}
	BOOL Init();
	BOOL Process();
	BOOL CheckRB();
	BOOL Show(long x, long y);
private:

};

class cState :public cInterfaceFather
{
public:

	void OnOff(BOOL NeedShow);
	cText5 m_TPetDate[9];
	vector<cText5> m_TPcDate; //27 门派  28 帮派

	CWFile m_LeveUp;
	cText5 m_Text;
	cWfileP m_ButtonLvUp;   //升级
	cWfileP m_ButtonSkill;  //技能
	int m_SkillPage;//如果技能数超过12个,需要翻页
	CWFile m_SkillHead[12];
	int m_SkillSelect;
	cWfileP m_SkillHeadSelect;
	////查看资质

	cText5 m_TSkillHeadSelectDate[2];
	cWfileP m_SeeZZ; 

	cInterfacePetSkill m_PetSkill;
	BOOL UpDatePcDate();
	void UpdateAddPointB();
	void UpdateProPerty();
	void UpDateHp();
	void UpDateMp();
	void UpDateCp();
	vector<cWfileP> m_Addp;
	vector<cWfileP> m_Subp;
	CWFile m_Add;
	
	CWFile m_Sub;
	CWFile* m_pShow;
	BOOL Init();
	BOOL ProcessInput();
	BOOL CheckL();
	BOOL CheckRB();
	BOOL SetFight(cCharacter* pc);
	cPCData* m_pPCData;
	BOOL Show(cCanvas5* pCanvas);
	BOOL Move(int x, int y);
	int m_NowFighter;
	CWFile m_State;
	void SetAddPoint();
	BOOL CheckAddPoint(){ return m_bAddPoint; }
private:
	BOOL m_bAddPoint;
	BOOL m_bNeedLVUP=FALSE;
	BOOL m_bInit = FALSE;
	// 日期版专用
	vector<int> _pointTemps;
	cCharacter *_cC = nullptr;

};
class cInterfaceLearnSkill :public cInterfaceFather
{
public:
	BOOL CostSkill(INT64 needexp, INT64 needmoney);
	CWFile m_SkillSelectBack[2];
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	BOOL LearnSkill(BOOL cost=TRUE);
	void OnOff(BOOL needshow);
	void Move(int x, int y);
	void Init();
	BOOL CheckRB();
	CWFile m_Back;
	
	cWfileP m_Button[2];
	cText5 m_tButton[2];

	RECT m_Rect;
	int m_SkillSelect;
	CWFile m_MengPaiSkillHead[7];
	cText5 m_tMengPaiSkill[7];
	cText5 m_tMengPaiSkillLv[7];
	cText5 m_tSkillSelectHead;
	cText5 m_tMiaoShu;
	cText5 m_tNeedExp;
	cText5 m_tHaveExp;
	cText5 m_tNeedMoney;
	cText5 m_tHaveMoney[3];
	void Update();
	void SetSkillSelect(int select);
private:
	BOOL m_bInit = FALSE;
};
class cInterfaceXiuLian:public cInterfaceFather
{
public:
	void CheckInit(){ if (!m_bInit)Init(); };
	BOOL Leveupskill(int lvup);

	void Init();
	void OnOff(BOOL NeedShow);
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	BOOL CheckRB();
	void Move(int x, int y);
	void UpDate();
	
	CWFile m_SkillSelectBack[2];
	CWFile m_Back;
	CWFile m_Button[2];
	cText5 m_tButton[2];
	cText5 m_MiaoShu;
	cText5 m_TXiuLian[4];
	RECT m_Rect;
	
private:
	int m_SkillSelect;
	BOOL m_bInit=FALSE;
};
class  cInterfaceGive:public cInterfaceFather
{
public:
	void AddItem(int select);
	virtual BOOL ProcessInput() ;
	virtual BOOL Show(cCanvas5* pCanvas) ;
	virtual BOOL CheckL() ;
	void ReCoverOnce();//收到的货不是我需要的,退还
	BOOL CheckRB();
	void OnOff(BOOL NeedShow);
	void Init();
	void Move(int x, int y);
	BOOL m_bInit = FALSE;
	void SetTarget(cObj* pTarget);
	cObj* GetTarget();
	sItem2 m_ItemGive[3];
	cInterfaceNumShuRu m_NumItem[3];
	int    m_ItemGiveOwner[3];
	cObj* m_pTarget;
private:
	
	cInterfaceNumShuRu m_NumShuru;
	CWFile m_SelectMark;
	CWFile m_MouseOnMark;
	int m_ItemSelect;
	void UpDate();

	CWFile m_Back;
	CWFile m_Button;
	cText5  m_tButton;
	
	int m_ItemNum[20];
	CWFile m_ItemHead[20];
	cText5 m_tItemHead[20];
	CWFile m_ItemGiveHead[3];
	
	
	cText5 m_tXIanJin;
	RECT m_Rect;
};

class cInterfaceYingHang :public cInterfaceFather
{
public:
	void Init();
	virtual BOOL ProcessInput() ;
	virtual BOOL Show(cCanvas5* pCanvas) ;
	virtual BOOL CheckL() ;
	BOOL CheckRB();
	void SetMode(
		BOOL mode,
		sFriendList* pFriend = 0
		);
	void OnOff(BOOL NeedShow);
	void Move(int x, int y);
	cText5 m_XianJin;
	cText5 m_CunYing;
	cInterfaceNumShuRu m_ShuRu;
	cTaskFather* m_pTrigger;
	int m_TriggerID;
private:
	sFriendList* m_pFriend;
	BOOL m_bInit=FALSE;
	BOOL m_bMode;
	CWFile m_Back;

	cWfileP m_Button;
	cText5  m_tButton;
};

class cInterfaceJianDing :public cInterfaceFather
{
public:
	void SetMode(int id){ m_Mode = id; }
	void Init();
	virtual BOOL ProcessInput() ;
	virtual BOOL Show(cCanvas5* pCanvas) ;
	virtual BOOL CheckL() ;
	virtual void OnOff(BOOL NeedShow) ;
	void Move(int xPos, int yPos);
private:
	int m_ItemSelect;
	int m_NowItemSelect;
	BOOL m_Mode=0;//0表示鉴定 1表示收购 2收购一切 3表示镶嵌宝石
	BOOL m_bInit=FALSE;
	CWFile m_Back;
	cText5 m_tPrice;
};




class  cInterSelectFriendItem : public cInterfaceFather
{
public:
	enum eQiangHuaMode
	{
		eQH装备,
		eQH技能,
		eQH技能2,
		eQH坐骑装饰,
		eQH出战,
		eQH放生
	};

	RECT m_Rect;
	CWFile m_MouseOnMark;
	
	virtual BOOL ProcessInput();
	virtual BOOL CheckL();
	BOOL CheckRB();
	BOOL Init();
	BOOL Set(int itemtype, int itemid,DWORD headid);
	BOOL Move(int x, int y);
	BOOL Show(cCanvas5* pCanvas);
	void SetMode(sFriendList* list, eQiangHuaMode mode);
	int m_ItemType[20];
	int m_ItemID[20];
	CWFile m_ItemHead[20];
	void OnOff(BOOL bshow);

	void GetSelect(int& outtype, int& outid)
	{
		outid = m_ItemID[m_Select];
		outtype = m_ItemType[m_Select];
	}
private:
	sShangPinPet* m_Pet;
	cText5 m_TitleT;
	sFriendList* m_pdata;
	eQiangHuaMode m_Mode;
	BOOL m_bInit = FALSE;
	int m_ItemNum=0;
	CWFile m_Back;

};
class cInterfaceUseJiaJu:public cInterfaceFather
{
public:
	cInterfaceUseJiaJu(){ 
		for (int i = 0; i < 6;i++)
		m_Pic[i].m_Picture.m_bShadow = 50; }
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	BOOL CheckRB();
	virtual void OnOff(BOOL NeedShow);
	void SetJiaJu(sItem2* jiaju);
	void AddDirection();
private:
	sItem2* m_pJiaJu;
	CWFile m_Pic[6];
	sJiaJu m_JiaJu;
	

};
class cInterfaceDaZao:public cInterfaceFather
{
public:
	void Init();
	virtual BOOL ProcessInput();
	virtual BOOL Show(cCanvas5* pCanvas);
	virtual BOOL CheckL();
	BOOL CheckRB();
	virtual void OnOff(BOOL NeedShow);
	void Move(int x, int y);
private:
	BOOL CheckEquip(int type);
	BOOL m_bInit = FALSE;
	CWFile m_Back;
	cText5 m_tMoneyNeed;
	cText5 m_tMoneyHave;
	cWfileP m_Head[2];
	int m_Item[2];
	cWfileP m_Button;
	cText5 m_tButton;
	int m_MoneyNeed;
};
