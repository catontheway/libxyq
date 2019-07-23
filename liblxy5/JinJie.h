#pragma once
#include "_asert.h"

class cJinJieNum
{
public:
	int m_index = 0;
	int m_JinJieNum = 0;
	bool GetBJinJie()
	{
		switch (m_index)
		{
		case 0:
		case 1:
			return 0;
		default:
			return 1;
		}
	}
	void operator=(cJinJieNum& data)
	{
		m_index = data.m_index;
		m_JinJieNum = data.m_JinJieNum;
	}
	void Save(ofstream& File)
	{
//		File << g_strSpace;
		File << m_index << g_strSpace;
		File << m_JinJieNum << g_strSpace;
	}
	void Load(ifstream& File)
	{
		File >> m_index;
		File >> m_JinJieNum;
	}
	void Reset()
	{
		m_index = 0;
		m_JinJieNum = 0;
	}
};