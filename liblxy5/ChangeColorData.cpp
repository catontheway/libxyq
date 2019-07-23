#include "_global.h"


void sChangeColorData::Save(ofstream& File)
{
	File << g_strSpace;
	File << partnum << g_strSpace;
	for (int i = 0; i < partnum; i++)
	{
		File << m_colorchange[i] << g_strSpace;
	}
}

void sChangeColorData::Read(ifstream& File, int modeid, eRanseType k, int partid)
{
	File >> partnum;
	if (partid == -1)return;//表示这是毫无意义的
	ulong color = 0;
	if (!partnum)return;

	switch (k)
	{
	case sChangeColorData::ePc:
		color = g_pMainState->m_pCharacterDataList[modeid].m_ColorID;
		break;
	case sChangeColorData::ePet:
		color = g_pMainState->m_PetDataManager.GetPetData(modeid)->m_ModelActs[partid].m_ColorID;
		break;
	case sChangeColorData::eZuoQi:
		color = g_pMainState->m_ZuoQi.m_ZuoQi[modeid].m_ColorID;
		break;
	case sChangeColorData::eZhuangShi:
		color = g_pMainState->m_ItemManage.m_ZuoQiZhuangShiList[modeid].m_ColorID;
		break;
	default:
		ERRBOX; break;
	}
	if (color == 0)
	{
		color = 0x1657;
	}
	g_pMainState->m_ColorManage.Set(color);
	for (int i = 0; i < partnum; i++)
	{
		File >> m_colorchange[i];
		g_pMainState->m_ColorManage.GetColorMatrix(
			i,
			m_colorchange[i],
			m_colormatrix[i]);
	}

}

bool sChangeColorData::SetColorChange(int id, int num)
{
	if (g_pMainState->m_ColorManage.GetPartNum() <= id)return false;
	int matrixnum = g_pMainState->m_ColorManage.GetMatirxNum(id);
	if (matrixnum < 1)return false;
	if (matrixnum <= num)num = 0;
	m_colorchange[id] = num;
	g_pMainState->m_ColorManage.GetColorMatrix(id, num, m_colormatrix[id]);
	return true;
}



bool sChangeColorData::AddColorChange(int id)
{
	return SetColorChange(id, m_colorchange[id] + 1);
}

void sChangeColorData::Set(int d0, int d1, int d2, int d3)
{
	m_colorchange[0] = d0;
	m_colorchange[1] = d1;
	m_colorchange[2] = d2;
	m_colorchange[3] = d3;
}

void sChangeColorData::operator=(sChangeColorData& data)
{
	if (0 == data.partnum)
	{
		partnum = 0;
		return;
	}
	partnum = data.partnum;
	for (int i = 0; i < 4; i++)
	{
		m_colorchange[i] = data.m_colorchange[i];
		m_colormatrix[i] = data.m_colormatrix[i];
	}
}



void sChangeColorData2::Read(int modeid, ifstream& File, int posid)
{
	Reset();
	bool bhaveranse;
	File >> bhaveranse;
	if (!bhaveranse)return;
	if (modeid < 1000)//召唤兽
	{
		sPetData* pPet = g_pMainState->m_PetDataManager.GetPetData(modeid);
		vector<int>& lis = pPet->m_ComponentTable[posid];
		for (int i = 0; i < 4; i++)
		{
			if (i < lis.size())
				m_ranse[i].Read(File, modeid, sChangeColorData::ePet, lis[i]);
			else
				m_ranse[i].Read(File, modeid, sChangeColorData::ePet, -1);
		}
	}
	else if (modeid < 2000)
	{
		return;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			m_ranse[i].Read(File, modeid - 2000, sChangeColorData::ePc, i);
	}
}

void sChangeColorData2::Save(ofstream& File)
{
	bool haveranse = false;
	for (int i = 0; i < 4; i++)
	{
		if (m_ranse[i].partnum)haveranse = true;
	}
	if (haveranse)
	{
		File << g_strSpace << 1 << g_strSpace; // " 1 ";
		for (int i = 0; i < 4; i++)
			m_ranse[i].Save(File);
	}
	else
	{
		File << 0 << g_strSpace;
	}
}