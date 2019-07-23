#include "_global.h"


bool cFullMagic::SetMagicUp(int dataid, ulong id, int x, int y)
{
	m_FullSkilUP[dataid].Load(id);
	m_FullSkilUP[dataid].SetFrame(0);
	m_FullSkilUP[dataid].m_NeedShow = true;
	m_FullSkilUP[dataid].m_Picture.m_x = x;
	m_FullSkilUP[dataid].m_Picture.m_y = y;
	return true;
}

cFullMagic::cFullMagic()
{
	m_FullSkilUP.resize(3);
	for (int i = 0; i < 3; i++)
	{
		m_FullSkilUP[i].m_NeedShow = false;
		m_FullSkilUP[i].m_Picture.m_x = 0;
		m_FullSkilUP[i].m_Picture.m_y = 0;
	}
	m_SufferMagic.resize(20);
}