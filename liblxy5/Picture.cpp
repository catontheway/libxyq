#include "_global.h"

CPicture::CPicture(void)
{
	Spr.m_pOwner = this;
}

CPicture::~CPicture(void)
{
	Free();
}
// ‘ÿ»Î ˝æ›
void CPicture::Load(void* pdate, int size, int type, sChangeColorData* pChangeColorData)
{
	Spr.Load(pdate, size, type, pChangeColorData);
	now_frame = 0;
	m_StepUpdate = 0;
	m_bMove = true;
	m_Width = Spr.GetWidth();
	m_Height = Spr.GetHeight();
	return;

}





void CPicture::Free()
{
	Spr.FreeDatelp();
	m_Height = 0;
	m_Width = 0;
};