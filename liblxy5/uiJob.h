#pragma once
#include "_uiinc.h"

//class cTaskFather;
struct sJob  //表示一个任务
{
	cTaskFather* m_pTask = 0;
	int m_Stage = -1;
	string m_Title;
	string m_Context;
	int m_Time = 0;
	void Set(string title, string context, int time, cTaskFather* task, int Stage)
	{
		m_Stage = Stage;
		m_Time = time;
		m_Context = context;
		m_Title = title;
		m_pTask = task;
	}
	void operator=(sJob& target)
	{
		m_Stage = target.m_Stage;
		m_Context = target.m_Context;
		m_pTask = target.m_pTask;
		m_Title = target.m_Title;
		m_Time = target.m_Time;
	}
};
struct sJobCharcter
{
	string characterName;
	int xPos;
	int yPos;
	string MapName;
	int direction;
	int TeamPos;
	string taskName;
};

class cCanvas;
class cInterfaceJob :public cInterfaceFather
{
public:
	void CheckErr();
	bool CheckHaveJob(int ID);//检测是否存在某种任务
	bool CheckHaveJob(string title);//检测是否存在某种任务
	void SetSelect(int select);
	void UpDatePageTitle();
	int m_Page = 0;
	bool AddaJob(sJob& job, int huanshu = -1);
	bool AddaJob(string title, string text, int huanshu = -1);
	bool updateJob(string title, string text, int huanshu = -1);
	bool ReMoveJob(cTaskFather* p);
	void Reset(){ m_JobList.clear(); }

	cText m_TitleList[8];
	sFaceText m_Context;
	void OnOff(bool NeedShow);
	//CWFile* m_pPreButton;

	vector<cWasFile> m_Back;
	int  m_gap;
	cWasFile m_Up;
	cWasFile m_Down;
	int m_Check;
	bool Move(int x, int y);
	sJob m_List[10];
	cWasFile m_Job;
	bool Init();
	bool ProcessInput();
	bool CheckL();
	bool CheckRB();
	bool Show(cCanvas* pCanvas);
	void MoveContext(int x, int y);
	void Save(ofstream& File);
	void Load(ifstream& File);

private:
	vector<sJob> m_JobList;
	bool m_bInit = false;
};
