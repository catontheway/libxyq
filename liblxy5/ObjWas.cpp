#include "_global.h"


void cObjWas::Set(cWasFile* p)
{
	m_pFile = p;
	m_StepUpdate = 0;
	now_frame = 0;
	m_StepUpdate = 0;
	m_Width = p->GetWidth();
	m_Height = p->GetHeight();
}

cObjWas::cObjWas()
{
	m_PreShowRect.right = -1;
	m_NeedShow = true;
	m_bMove = false;
	m_bStatic = false;
	m_pFile = 0;
	m_direction = 1;

}

RECT cObjWas::GetPicRange()
{
	int a = GetDataID();
	RECT rect;

 	rect.left = m_x - m_pFile->m_Picture.Spr.m_pDataOffsetList[a].FramX;
	rect.top = m_y - m_pFile->m_Picture.Spr.m_pDataOffsetList[a].FramY;
	if (0 == m_pFile->GetShowWidth())
		rect.right = m_x + m_pFile->m_Picture.m_Width;
	else
		rect.right = m_x + m_pFile->GetShowWidth();
	if (0 == m_pFile->GetShowHeight())
		rect.bottom = m_y + m_pFile->m_Picture.m_Height;
	else
		rect.bottom = m_y + m_pFile->GetShowHeight();
	return rect;
}
bool cObjWas::isFrameChange2Next()
{
	if (m_bStatic)return false;

	if (m_FrameGap <= m_StepUpdate)
	{
		m_StepUpdate = 0;
		(now_frame < (m_pFile->m_Picture.Spr.GetMaxFrame() - 1)) ? (now_frame++) : (now_frame = 0);
		return true;
	}
	else
	{
// 		if (m_pFile->_fps != g_iFPS)
// 		{
 			m_StepUpdate += 1;
// 			m_pFile->_fps = g_iFPS;
// 		}
	}
	return false;
}

void cObjWas::operator=(cObjWas& file)
{
	m_x = file.m_x;
	m_y = file.m_y;
	m_xOffset = file.GetxOffset();
	m_xOffset2 = file.GetxOffset2();
	m_yOffset = file.GetyOffset();
	m_yOffset2 = file.GetyOffset2();
	m_direction = file.m_direction;
	m_pFile = file.m_pFile;
}



int cObjWas::GetCenter()
{
	return m_x + (GetShowWidth() >> 1);
}

