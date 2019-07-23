#pragma once
#include "_objinc.h"

struct sNpc
{
	cJinJieNum m_JinJieID;
	int weaponid = -1;
	int weapontype = -1;
	sChangeColorData2 m_Ranse;
	int m_modeid = -1;
	string m_name;
	string m_mapname = "";//Ëù´¦Î»ÖÃ
	int m_x;
	int m_y;
	int  m_direction;
	void Reset();
	void SetRanse(int id0, int id1 = 0, int id2 = 0, int id3 = 0, int part = 0);
	void AutoDirection4(){ m_direction = Direction8To4(rand() % 10); }
	void operator =(sNpc& data)
	{
		m_x = data.m_x;
		m_y = data.m_y;
		m_name = data.m_name;
		m_mapname = data.m_mapname;
		m_modeid = data.m_modeid;
		m_direction = data.m_direction;

		weapontype = data.weapontype;
		weaponid = data.weaponid;
		m_JinJieID = data.m_JinJieID;

	}
	void Set(int x1, int y1){ m_x = x1; m_y = y1; }
	void Set(string name, string mapname, int modeid, int x, int y, int direction = -1, int jinjie = 1);

	void Save(ofstream& File);
	void Load(ifstream& File);
};


struct sNpcData
{
	int  m_ModeId;
	string  m_name;
	ulong	m_stand;
	ulong	m_walk;
	ulong	m_dialog;
};

class cNpc
{
public:
	sNpcData* m_pNpcData;
	void GetID(int POS_X, vector<ulong>& out);
private:

};
