#pragma once
#include "Map.h"

#define MAX_NPC_NUM	 256

struct sRangeTr
{
	string m_name = "";
	int m_x;
	int m_y;
	int m_range;
	bool Check(int x, int y);
};
struct sTransmit :public sRangeTr
{
	//目的地名字
	string name;
	//目的地坐标
	int m_xTarget;
	int m_yTarget;
};
struct sTriggerRange :public sRangeTr
{
	cTaskFather* m_p = 0;
	int m_ret;
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Set(string name, int x, int y, int range, cTaskFather* p, int ret);
};
//struct sNpc;
class cMyMap
{
public:
	void CheckChuanSong();
	//寻找某张地图上的随机空位
	cBmp m_BmpTest;
	void AutoGetPos(int& xout, int& yout, string mapname = "");
	//该场景的物品等级和几率
	int m_Weaponlv;
	int m_WeaponRate;

	void AddNpcSmall(string name, int id, int x, int y, int direction, cTaskFather* p = 0, string scriptname = "无", int stage = 0, bool NeedFind = true);

	void ShadowNpc(string name, bool NeedShow, bool NeedFind = true);
	void RemoveNpc(string name, bool NeedFind = true);
private:
	void RemoveNpc(int id, bool NeedFind);
public:
	void RemoveNpc(int xPos, int yPos, string name, bool NeedFind);
	void RemoveNpc(cObj* pObj, bool Needfind);
	void RemoveAllNpc();
	int  m_MapNumber = -1;
	int   m_MapType; //场景类型 
	int   m_NumOfEmemyType;
	int   m_EnemyLv;
	int m_EnemyNum;
	array<int, 25>   m_EnemyList;
	string m_MapName;
	cWasFile m_SmallMap;
	float  m_bili;
	//CWFile m_Transmit;
	cMyMap();
	~cMyMap();
	bool CheckAlong(int xPos, int yPos, int xTarget, int yTarget);
	bool Free();
	bool LoadMap(long x, long y, const char* Name, bool bFly = true);
	bool Show(uchar* pPic, const RECT& rect){ return m_pMap->Show(pPic, rect); }

	cMap* m_pMap;
	cBmp* m_pBmp;
	vector<cObj*>  m_pNpc;
	vector<cWasFile*> m_pJianZhu;
	vector<ulong> m_JianZhuID;
	void AddJiaJu(sJiaJu* jiaju);
	void RemoveJiaJu(sJiaJu* jiaju);
	bool Init();
	int m_numberOfNpc;
	sTransmit* m_pTransmit;
	int m_numberOfTransmit;
	int m_numofJianZhu;
	void SetLock(string mapname = "");
	void SetLock(int b);
	void Save(ofstream& File);
	void LoadMap(ifstream& File);
	void AddTriggerRange(sTriggerRange& data);

	void AddNpc(sTaskMapObj* data, bool needfind = false);
	void AddNpc(sNpc* npc, cTaskFather* p = 0, string scriptname = "无", int stage = 0, bool NeedFind = true);

//private:
	void AddNpc(string name, int id, int x, int y, int direction, cTaskFather* p = 0, string scriptname = "无",
		int stage = 0, bool NeedFind = true, int weapontype = -1, int weaponid = -1, sChangeColorData2* ranse = 0, int positionID = 0);

	vector<string> m_LockList;
	bool m_bInit = false;
	bool m_bLock = false;//禁止转换地图
	vector<sTriggerRange> m_RangeTriggerList;
	cWasFile _cwfileWav;
	bool _isTeleporting = false;


public:
	bool _isAddNormalNpc;
};

