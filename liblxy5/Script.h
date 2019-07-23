#pragma  once
#include "_asert.h"

#define SENTRYTYPE_NULL   0
#define SENTRYTYPE_STRING 1
#define SENTRYTYPE_INT    2
#define SENTRYTYPE_FLOAT  3
#define SENTRYTYPE_BOOL   4

class sActionTemplate
{
public:
	string Name;
	int NumOfEntryUnoin;
	int* pEntryUnoinsType;
	sActionTemplate()
	{
		NumOfEntryUnoin = 0;
		pEntryUnoinsType = 0;
	}
	void Free()
	{
		if (pEntryUnoinsType)
		{
			delete[] pEntryUnoinsType;
			pEntryUnoinsType = 0;
			NumOfEntryUnoin = 0;
		}
	}
	
};
class sEntryUnion
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
	int NumOfEntryUnion;
	sEntryUnion* pEntryUnoins;
	sAction()
	{
		NumOfEntryUnion = 0;
		pEntryUnoins = 0;
	}
	void Free()
	{
		if (pEntryUnoins)
		{
			delete[] pEntryUnoins;
			pEntryUnoins = 0;
		}
		NumOfEntryUnion = 0;
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
	bool LoadActionTemplate(string Path);
	vector<sActionTemplate> m_ActionTemplateList;
	list<sAction> m_ActionList;
	bool LoadScript(string name);
	void Free();
private:

};

