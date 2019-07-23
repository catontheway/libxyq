#pragma once
class cBmp5
{
public:
	cBmp5(){ }
	~cBmp5();
	BOOL Load(CHAR* name);
	bool Load(int mapid);
	// 笛卡尔
	BOOL isOk20(int x20, int y20);
	// 非笛卡尔
	BOOL isOk(int x, int y);
	BOOL Free();
	int GetHeight(){ return m_Height; }
	int GetWidth(){ return m_Width; }
	string oldmap = "";
	int oldid = 0;
	int m_Width;
	int m_Height;


	sMapCache _cache;
	int _ow;
};


class cMap
{
public:
	static int toMapid(const std::string& mapname, std::ifstream& ifile);
	static const char* toMap(const std::string& filename);
	void CountMaskList();//计算屏幕中的mask
	void xMove(int x);
	void yMove(int y);
	int m_MapID = -1;
	int m_AddSpeed = 24;
	int m_xPreSpeed = 0;
	int m_yPreSpeed = 0;
	//锁定地图
	int m_LockMap = 0;
	BOOL m_ReturnMap;
	int m_xLock;
	int m_yLock;

	BOOL SetCenter(float xHero, float yHero);
	BOOL Follow(cObj* pObj);

	BOOL m_bMove;  //画面是否移动

	BOOL Load(CHAR* FullPath, int mapid);
	BOOL Show(BYTE* pPic, RECT rect);
	BOOL  MoveMap();
	
	cMap();
	~cMap();

	//地图块数
	int   m_NumBlock;
	int   m_HeightNum;
	int   m_WidthNum;
	//地图大小
	int   m_Width;
	int	  m_Height;

	//记录地图中心的位置
	float m_xCenter;
	float m_yCenter;
	//当前中心图块
	int m_xCenterNum = -1;
	int m_yCenterNum = -1;
	int m_xCenterOffset;
	int m_yCenterOffset;
	//
	int GetXCenter(){ return (int)m_xCenter; }
	int GetYCenter(){ return (int)m_yCenter; }
	void Free();

public:
	sMapCache _cache;
	cocos2d::Vec2 _vMap;
	void showMask();

	// 瞬移
	bool _isTeleporting = false;
};

class CMainState;
struct sRangeTr
{
	string m_name="";
	int m_x;
	int m_y;
	int m_range;
	BOOL Check(int x, int y);
};
struct sTransmit:public sRangeTr
{
	//目的地名字
	string name; 
	//目的地坐标
	int m_xTarget;
	int m_yTarget;
};
struct sTriggerRange:public sRangeTr
{
	cTaskFather* m_p = 0;
	int m_ret;
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Set(string name,int x, int y, int range, cTaskFather* p, int ret);
};
struct sNpc;
class cMyMap
{
public:	
	void CheckChuanSong();
	//寻找某张地图上的随机空位
	cBmp5 m_BmpTest;
	void AutoGetPos(int& xout, int& yout, string mapname="");
	//该场景的物品等级和几率
	int m_Weaponlv;
	int m_WeaponRate;

	void AddNpcSmall(string name, int id, int x, int y, int direction, cTaskFather* p = 0, string scriptname = "无", int stage = 0, BOOL NeedFind = TRUE);

	void ShadowNpc(string name, BOOL NeedShow, BOOL NeedFind = TRUE);
	void RemoveNpc(string name,BOOL NeedFind=TRUE);
private:
	void RemoveNpc(int id, BOOL NeedFind);
public:
	void RemoveNpc(int xPos, int yPos, string name , BOOL NeedFind);
	void RemoveNpc(cObj* pObj,BOOL Needfind);
	void RemoveAllNpc();
	int  m_MapNumber=-1;
	int   m_MapType; //场景类型 
	int   m_NumOfEmemyType;
	int   m_EnemyLv;
	int   m_EnemyList[10];
	string m_MapName;
	CWFile m_SmallMap;
	float  m_bili;
	//CWFile m_Transmit;
	cMyMap();
	~cMyMap();
	BOOL CheckAlong(int xPos, int yPos, int xTarget, int yTarget);
	BOOL Free();
	BOOL LoadMap(long x,long y,const CHAR* Name,BOOL bFly=TRUE);
	BOOL Show(BYTE* pPic, RECT rect){return m_pMap->Show(pPic, rect);}
	
	cMap* m_pMap;
	cBmp5* m_pBmp;
	vector<cObj*>  m_pNpc;
	vector<CWFile*> m_pJianZhu;
	vector<DWORD> m_JianZhuID;
	void AddJiaJu(sJiaJu* jiaju);
	void RemoveJiaJu(sJiaJu* jiaju);
	BOOL Init();
	int m_numberOfNpc;
	sTransmit* m_pTransmit;
	int m_numberOfTransmit;
	int m_numofJianZhu;
	void SetLock(string mapname = "");
	void SetLock(BOOL b);
	void Save(ofstream& File);
	void LoadMap(ifstream& File);
	void AddTriggerRange(sTriggerRange& data);

	void AddNpc(sMapObjTrigger* data, BOOL needfind = FALSE);
	void AddNpc(sNpc* npc, cTaskFather* p = 0, string scriptname = "无", int stage = 0, BOOL NeedFind = TRUE);
	
private:
	void AddNpc(string name, int id, int x, int y, int direction, cTaskFather* p = 0, string scriptname = "无",
		int stage = 0, BOOL NeedFind = TRUE, int weapontype = -1, int weaponid = -1, sChangeColorData2* ranse = 0, int positionID = 0);

	vector<string> m_LockList;
	BOOL m_bInit = FALSE;
	BOOL m_bLock = FALSE;//禁止转换地图
	vector<sTriggerRange> m_RangeTriggerList;

public:
	bool _isAddNormalNpc;
};

