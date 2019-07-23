#pragma once
#include "ChangeColor.h"

struct sChangeColorData
{
	void Reset()
	{
		partnum = 0;
		forr(m_colorchange, i)
		{
			m_colorchange[i] = 0;
		}
	}
	enum eRanseType
	{
		ePc,
		ePet,
		eZuoQi,
		eZhuangShi
	};
	//Ⱦɫ
	int partnum = 0;
	int GetColorChange(int id){ return m_colorchange[id]; }
	bool SetColorChange(int id, int num);
	bool AddColorChange(int id);
	array<sChangeColorMatrix, 4> m_colormatrix;
	sChangeColorData(){ Reset(); }
	void operator=(sChangeColorData& data);

	void Set(int d0, int d1, int d2, int d3);
	void Save(ofstream& File);
	void Read(ifstream& File, int modeid, eRanseType k, int partid);
//private:
	array<int, 4>  m_colorchange;
};
struct sChangeColorData2
{
	array<sChangeColorData, 4> m_ranse;
	void Read(int modeid, ifstream& File, int posid = 0);
	void Save(ofstream& File);
	void operator=(sChangeColorData2& data)
	{
		forr(m_ranse, i)
		{
			m_ranse[i] = data.m_ranse[i];
		}
	}
	void Reset()
	{
		forr(m_ranse, i)
		{
			m_ranse[i].partnum = 0;
		}
	}
};