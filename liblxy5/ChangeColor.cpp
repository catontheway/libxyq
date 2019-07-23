#include "_global.h"

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


static int readIColor9(char*& ptr, int& i, int size)
{
	if (i >= size)
	{
		return -1;
	}
	int v = atoi(ptr);
	do
	{
		++ptr;
		if (++i >= size)
		{
			return v;
		}
	} while ((*ptr) >= '0' && (*ptr) <= '9');

	do
	{
		++ptr;
		if (++i >= size)
		{
			return v;
		}
	} while ((*ptr) < '0' || (*ptr) > '9');

	return v;
}

struct sColorPad9{ ushort r1, r2, r3, g1, g2, g3, b1, b2, b3; };
struct sColorPad
{
	vector<ushort> patrs;
	vector <vector<sColorPad9>> pad9s;
};

static bool readColorPal(sColorPad& c, char* ptr, int& idx, int size)
{
	int n = readIColor9(ptr, idx, size);
	c.pad9s.resize(n % 10);
	c.patrs.resize(c.pad9s.size() + 1);
	forv(c.patrs, i)
	{
		c.patrs[i] = readIColor9(ptr, idx, size);
	}

	forv(c.pad9s, k)
	{
		c.pad9s[k].resize(readIColor9(ptr, idx, size));
		forv(c.pad9s[k], i)
		{
			if (n > 1000)
			{
				readIColor9(ptr, idx, size);
			}
			auto& m = c.pad9s[k][i];
			m.r1 = readIColor9(ptr, idx, size);
			m.r2 = readIColor9(ptr, idx, size);
			m.r3 = readIColor9(ptr, idx, size);
			m.g1 = readIColor9(ptr, idx, size);
			m.g2 = readIColor9(ptr, idx, size);
			m.g3 = readIColor9(ptr, idx, size);
			m.b1 = readIColor9(ptr, idx, size);
			m.b2 = readIColor9(ptr, idx, size);
			m.b3 = readIColor9(ptr, idx, size);
			if (n > 1000)
			{
				readIColor9(ptr, idx, size);
				readIColor9(ptr, idx, size);
				readIColor9(ptr, idx, size);
				readIColor9(ptr, idx, size);
			}
			if (idx >= size)
			{
				return false;
			}
		}

	}
	return true;
}



void cChangeColor::Set(ulong id)
{
	if (m_oldid == id)return;
	m_oldid = id;
	if (id == 0)return;
	cWasFile finddata;
	ifstream* f=0;
	int plitnum;
	int split[10];
	int matrixnum;
	int matrixid[9];
	if (!finddata.GetFileP(id, f))
	{
		return;
	}
	if (id >= 0x00003000)
	{
		char* ptr = new char[finddata.m_Size];
		f->read(ptr, finddata.m_Size);
		sColorPad c;
		int idx = 0;
		readColorPal(c, ptr, idx, finddata.m_Size);
		delete[] ptr;

		plitnum = c.patrs.size() - 1;
		forv(c.patrs, k)
		{
			split[k] = c.patrs[k];
		}
		m_CharacterColor.m_stagesplit.clear();
		for (int k = 0; k < plitnum; ++k)
		{
			sChangeColorSplit  part;
			matrixnum = c.pad9s[k].size();
			for (int i = 0; i < matrixnum; ++i)
			{
				sChangeColorMatrix matrix;
				auto& m = c.pad9s[k][i];
				matrix.m_start = split[k];
				matrix.m_end = split[k + 1];
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
		return;
	}
	*f >> plitnum;
	for (int i1 = 0; i1 < plitnum + 1; i1++)
	{
		*f >> split[i1];
	}
	m_CharacterColor.m_stagesplit.clear();
	for (int i3 = 0; i3 < plitnum; i3++)
	{
		sChangeColorSplit  part;
		 *f >> matrixnum;
		for (int i1 = 0; i1 < matrixnum; i1++)//¶ÁÈ¡¾ØÕó
		{
		/*	if (i1 == 7)
				int k = 0;*/
			sChangeColorMatrix matrix;
			for (int i2 = 0; i2 < 9; i2++)
			{
				*f >> matrixid[i2];
			}
			matrix.m_start = split[i3];
			matrix.m_end = split[i3 + 1];
			matrix.x1 = matrixid[0];
			matrix.x2 = matrixid[1];
			matrix.x3 = matrixid[2];

			matrix.y1 = matrixid[3];
			matrix.y2 = matrixid[4];
			matrix.y3 = matrixid[5];

			matrix.z1 = matrixid[6];
			matrix.z2 = matrixid[7];
			matrix.z3 = matrixid[8];
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

void cChangeColor::SetCharacter(ulong id)
{
	Set(g_pMainState->m_pCharacterDataList[id].m_ColorID);
}

void cChangeColor::SetPet(ulong id,int part)
{
	Set(g_pMainState->m_PetDataManager.GetPetData(id)->m_ModelActs[part].m_ColorID);
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


