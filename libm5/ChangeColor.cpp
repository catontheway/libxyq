#include "global.h"
void cChangeColor::Init()
{
}

void cChangeColor::GetColorMatrix(int part, int matrixid, sChangeColorMatrix& out)
{
	if (part < m_CharacterColor.m_stagesplit.size())
	{
		if (matrixid < m_CharacterColor.m_stagesplit[part].m_ColorMatrix.size())
			out = m_CharacterColor.m_stagesplit[part].m_ColorMatrix[matrixid];
	}
}


void cChangeColor::Set(DWORD id)
{
	if (m_oldid == id)return;
	m_oldid = id;
	if (id == 0)return;
	cDye::sSections sections;
	if (!cDye::toSections(sections, id))
	{
		return;
	}
	m_CharacterColor.m_stagesplit.clear();
	forv (sections, k)
	{
		sChangeColorSplit  part;
		const auto& ss = sections.at(k);
		const auto& m9s = ss.matrix9s;
		forv (m9s, i)
		{
			sChangeColorMatrix matrix;
			auto& m = m9s.at(i);
			matrix.m_start = ss.start;
			matrix.m_end = ss.end;
			matrix.x1 = m.r1;
			matrix.x2 = m.r2;
			matrix.x3 = m.r3;
			matrix.y1 = m.g1;
			matrix.y2 = m.g2;
			matrix.y3 = m.g3;
			matrix.z1 = m.b1;
			matrix.z2 = m.b2;
			matrix.z3 = m.b3;
			part.m_ColorMatrix.push_back(matrix);
		}
		m_CharacterColor.m_stagesplit.push_back(part);
	}
}

int cChangeColor::GetPartNum()
{
	return m_CharacterColor.m_stagesplit.size();
}

int cChangeColor::GetMatirxNum(int id)
{
	return m_CharacterColor.m_stagesplit[id].m_ColorMatrix.size();
}

void cChangeColor::Give(sChangeColorData* pData)
{
	pData->partnum = GetPartNum();
	for (int i = 0; i < pData->partnum; i++)
	{
		GetColorMatrix(i, pData->GetColorChange(i) , pData->m_colormatrix[i]);
	}
}

void cChangeColor::SetCharacter(DWORD id)
{
	Set(g_pMainState->m_pCharacterDataList[id].m_ColorID);
}

void cChangeColor::SetPet(DWORD id,int part)
{
	Set(g_pMainState->m_PetDataManager.GetPetData(id)->m_PartList[part].m_ColorID);
}

void cChangeColor::Give2(sChangeColorData* pData, int modeid,int part)
{
	if (modeid < 1000)
	{
		SetPet(modeid, part);
	}
	else
	if (modeid>1999)
	{
		SetCharacter(modeid - 2000);
	}
	else
	return;
	Give(pData);
}


