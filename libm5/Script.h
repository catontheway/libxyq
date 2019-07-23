#pragma  once
#include <string>
#include <vector>
#include <list>
#include <windows.h>
using namespace std;
#define SENTRYTYPE_NULL   0
#define SENTRYTYPE_STRING 1
#define SENTRYTYPE_INT    2
#define SENTRYTYPE_FLOAT  3
#define SENTRYTYPE_BOOL   4

class sActionTemplate
{
public:
	string Name;
	int NumOfEntry;
	int* pEntryType;
	sActionTemplate()
	{
		NumOfEntry = 0;
		pEntryType = 0;
	}
	void Free()
	{
		if (pEntryType)
		{
			delete[] pEntryType;
			pEntryType = 0;
			NumOfEntry = 0;
		}
	}
	
};
class sEntry
{
public:
	int Type; //1 string 2 int
	float floatData;
	int   intData;
	string stringData;

};
class sAction
{
public:
	int ID;
	int NumOfEntry;
	sEntry* pEntry;
	sAction()
	{
		NumOfEntry = 0;
		pEntry = 0;
	}
	void Free()
	{
		if (pEntry)
		{
			delete[] pEntry;
			pEntry = 0;
		}
		NumOfEntry = 0;
	}
};
class cScript
{
public:
	void Add(sAction& Action);
	void Insert(sAction& Action,int Pos);
	void Up(int Pos);
	void Down(int Pos);
	void Delete(int Pos);
	list<sAction>::iterator GetIterator(int Pos);
	BOOL LoadActionTemplate(string Path);
	vector<sActionTemplate> m_ActionTemplateList;
	list<sAction>         m_ActionList;
	BOOL LoadScript(string name);
	void Free();
private:

};

