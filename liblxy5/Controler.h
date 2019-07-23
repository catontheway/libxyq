#pragma once
#include "_asert.h"

struct sControler
{
	void Set(int bfly = 1, int bdel = 1, int bBB = 0, int bHavebb = 0, int bCanGrab = 0)
	{
		m_bBB = bBB;
		m_bDelete = bdel;
		m_HaveBB = bHavebb;
		m_bFly = bfly;
		m_CanGrab = bCanGrab;
	}
	void Save(ofstream& File);
	void Load(ifstream& File);
//	int GetOwner(){ return m_Hero; };

	int  GetFly(){ return m_bFly; }
	int GetDel(){ return m_bDelete; }
	int CheckBB(){ return m_bBB; }
	int CheckHaveBB(){ return m_HaveBB; }
	void SetHaveBB(int k){ m_HaveBB = k; }
	int CheckGrab(){ return m_CanGrab; }
private:
	int m_CanGrab = 0; //是否可以抓 一般都是不能抓的
	int m_bFly = 1;//是否会被击飞
	int m_bDelete = 1; //战斗后是否删除
	int m_bBB = 0;//是否是某人的召唤兽;
	int m_HaveBB = 0;//是否有BB
};