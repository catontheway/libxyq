
#include "Script.h"
#include <fstream>
using namespace std;
BOOL cScript::LoadActionTemplate(string Path)
{
	ifstream file;
	file.open(Path);
	if (!file)return FALSE;
	while (TRUE)
	{
		sActionTemplate Action1;
		Action1.Name = "";
		//读取一条行为模板  
		
			getline(file, Action1.Name);
			if (Action1.Name.size()<2)
				getline(file, Action1.Name);
			if (Action1.Name.size() < 2)
			{
				file.close();
				return TRUE;
			}
		

		for (UINT i = 0; i < Action1.Name.length(); i++)
		{
			if (Action1.Name[i] == '~')
			{
				Action1.NumOfEntry += 1;
			}
		}
		Action1.pEntryType = new int[Action1.NumOfEntry];
		string text;
		for (int i = 0; i < Action1.NumOfEntry; i++)
		{
			file >> text;
			if (!text.compare("STRING"))
			{
				Action1.pEntryType[i] = SENTRYTYPE_STRING;
			}
			else
			if (!text.compare("INT"))
			{
				Action1.pEntryType[i] = SENTRYTYPE_INT;
			}
			else
			if (!text.compare("FLOAT"))
			{
				Action1.pEntryType[i] = SENTRYTYPE_FLOAT;
			}
			else
			if (!text.compare("BOOL"))
			{
				Action1.pEntryType[i] = SENTRYTYPE_BOOL;
			}

		}
		m_ActionTemplateList.push_back(Action1);
	}
	return TRUE;
}

void cScript::Add(sAction& Action)
{
	m_ActionList.push_back(Action);
}

void cScript::Insert(sAction& Action, int Pos)
{
	if (m_ActionList.size() < (UINT)Pos)
	{
		return;
	}
	list<sAction>::iterator it;
	it = GetIterator(Pos);
	m_ActionList.insert(it, Action);
}

void cScript::Up(int Pos)
{
	if (m_ActionList.size()-1 < (UINT)Pos)
	{
		return;
	}
	list<sAction>::iterator it;
	list<sAction>::iterator it2;
	it = GetIterator(Pos);
	it2 = GetIterator(Pos - 1);
	swap(*it2, *it);
}

void cScript::Down(int Pos)
{
	Up(Pos+1);
}

list<sAction>::iterator cScript::GetIterator(int Pos)
{
	list<sAction>::iterator it;
	it = m_ActionList.begin();
	for (int i = 0; i < Pos; i++)
	{
		it++;
	}
	return it;
}

void cScript::Delete(int Pos)
{
	list<sAction>::iterator it;
	it=GetIterator(Pos);
	m_ActionList.erase(it);
}

BOOL cScript::LoadScript(string name)
{
	// TODO:  在此添加控件通知处理程序代码
	ifstream  File;
	File.open(name);
	if (!File)return FALSE;
	m_ActionList.clear();
	while (true)
	{
		sAction  Action;
		File >> Action.ID;
		if (File.eof())
		{
			return TRUE;
		}
		File >> Action.NumOfEntry;
		Action.pEntry = new sEntry[Action.NumOfEntry];
		for (int k = 0; k < Action.NumOfEntry; k++)
		{
			File >> Action.pEntry[k].Type;
			switch (Action.pEntry[k].Type)
			{
			case SENTRYTYPE_INT:
				File >> Action.pEntry[k].intData;
				break;
			case SENTRYTYPE_FLOAT:
				File >> Action.pEntry[k].floatData;
				break;
			case SENTRYTYPE_BOOL:
				File >> Action.pEntry[k].intData;
				break;
			case SENTRYTYPE_STRING:
				File >> Action.pEntry[k].stringData;
				break;
			default:
				MessageBoxA(0, "未知类型", "读取", MB_OK);
				break;
			}
		}
		m_ActionList.push_back(Action);
	}
	return TRUE;
}

void cScript::Free()
{
	list<sAction>::iterator it = m_ActionList.begin();
	for (UINT i = 0; i < m_ActionList.size(); i++)
	{
		it->Free();
		it++;
	}
	list<sAction>  dustbin;
	m_ActionList.swap(dustbin);

	
	for (UINT i = 0; i < m_ActionTemplateList.size(); i++)
	{
		m_ActionTemplateList[i].Free();
	}
	vector<sActionTemplate> dustbin2;
	m_ActionTemplateList.swap(dustbin2);
}
