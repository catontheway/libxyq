#pragma once
#include "_uiinc.h"

class cCursor
{
public:
	int SelectObj(int UserID, int Type, cObj*& pObj);
	int m_FollowTime = 0;
	bool   m_FollowMode;
	ulong   m_Give;
	ulong   m_Normal;
	ulong   m_Forbid;
	ulong   m_Trade;
	ulong   m_Hande;
	ulong   m_Attack;
	ulong   m_Magic;
	ulong   m_Team;
	ulong   m_Guard;
	ulong   m_Grab;
	ulong   m_No;
	cWasFile  m_Data;
	cWasFile  m_Click;
	vector<cObjWas>  m_Clickp;
	cCursor();
	void Set(ulong  Type)
	{
		if (m_Data.m_NowID == Type)return;
		m_Data.Load(Type);
	}
	bool Init();
	bool Process();
	bool CheckRB();
	bool Show(long x, long y);
private:

};
