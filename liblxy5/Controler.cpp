#include "Controler.h"


void sControler::Save(ofstream& File)
{
	File << g_strSpace;
	File << m_CanGrab << g_strSpace; //是否由玩家控制
	File << m_bFly << g_strSpace;//是否会被击飞
	File << m_bDelete << g_strSpace; //战斗后是否删除
	File << m_bBB << g_strSpace;//是否是某人的召唤兽;
	File << m_HaveBB << g_strSpace;//是否有BB
}

void sControler::Load(ifstream& File)
{
	File >> m_CanGrab; //是否由玩家控制
	File >> m_bFly;//是否会被击飞
	File >> m_bDelete; //战斗后是否删除
	File >> m_bBB;//是否是某人的召唤兽;
	File >> m_HaveBB;//是否有BB
}