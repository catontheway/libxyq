#pragma once
#include "_objinc.h"

struct sItem2
{
	void SaveCode(sOstream& File);
	void LoadCode(sIstream& File);
	void Save(ofstream& File);
	void Load(ifstream& File);
	void Set(int type, int id, bool needclear = true);
	int GetType();
	int GetID();
	string GetName();
	string GetText();

	int GetNum(){ return m_Num; }
	sItem* m_pItemData = 0;
	int m_Num = 0;
	vector<int>  m_Property; // Ù–‘  
	string m_strProperty = "";
	void Reset()
	{
		m_Num = 0;
		m_Property.clear();
		m_pItemData = 0;
		m_strProperty = "";
	}
	void Swap(sItem2& item2)
	{
		swap(m_Num, item2.m_Num);
		swap(m_pItemData, item2.m_pItemData);
		m_strProperty.swap(item2.m_strProperty);
		m_Property.swap(item2.m_Property);
	}
	void operator=(sItem2& item)
	{
		m_pItemData = item.m_pItemData;
		m_Num = item.m_Num;
		m_Property.clear();
		for (uint i = 0; i < item.m_Property.size(); i++)
			m_Property.push_back(item.m_Property[i]);
		m_strProperty = item.m_strProperty;
	}
	bool operator==(sItem2& item)
	{
		if (item.GetType() == GetType())
			if (item.GetID() == GetID())
				return true;
		return false;
	}
};
