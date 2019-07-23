#pragma once
#include "_uiinc.h"

struct sPoem
{//一首诗
	string m_title;
	string m_name;
	vector<string> m_context;
	void Read(ifstream& File)
	{
		File >> m_name;
		File >> m_title;
		int num;
		File >> num;
		m_context.resize(num);
		for (int i = 0; i < num; i++)
			File >> m_context[i];
	}
};
struct	sQuestion
{
	string title;
	vector<string> select;
	int  answer; //正确答案

	void Auto()//改变题目中选择的位置
	{
		int a = rand() % select.size();
		if (a != answer)
		{
			swap(select[answer], select[a]);
			answer = a;
		}
		a = (a + 1) % select.size();
		int b = rand() % select.size();
		if (a != b)
		{
			swap(select[a], select[b]);
		}
		if (b == answer)answer = a;
	}
};
struct sTalkList;
class cInterfaceDialog :public cInterfaceFather
{
private:
	vector<sPoem>  m_PoemList;
	void AutoGetPoem(sPoem*& out);//随机得到标题,但不能为title;
public:
	string GetTrueSelect();
	void GetQuestion(sQuestion& quest, int selectnum = 4);

	void InitQuestion();

	bool m_bInitQuestion = false;
	int m_retSelect = -1;

	void Talk(sTalkList* talk);
	void Talk(string context, string name, ulong head);
	void TalkNObj(string context);
	void TalkObj(string context, cObj* p = 0);
	sFaceText m_ContextList;
	cWasFile m_DialogBack;
	int    m_NumOfSelect;
	vector<cText>  m_SelectT;
	int    m_NowMouseOnSelect = -1;
	void Reset();
	void Reset2();
	cWasFile m_NameBack;
	void OnOff(bool bShow);

	bool Init();
	void SetObj(string name);
	void SetObj(cObj* pObj);
	void SetHead(ulong head);
	void SetPet(cPet* p);

	bool  ProcessInput();
	bool  CheckL();
	void Close();
	bool  Show(cCanvas* pCanvas);
	bool  Free();
	void  SetString(string str = "", string select1 = "", string select2 = "", string select3 = "", string select4 = "");
	void  Question();
	cObj* m_pObj;
	void SetTrigger(cTaskFather* pTask, int defaultret, int stage0 = -1, int stage1 = -1, int stage2 = -1, int stage3 = -1);
	bool m_bRetSelect = false;
	sQuestion m_Question;
private:

	cTaskFather* m_pTask = 0;
	int m_retstage[5];
	bool m_Reset = false;
	cWasFile m_Head;
	bool m_bInit = false;
};

