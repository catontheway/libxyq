#pragma once
#include "_taskinc.h"

class cTriggerDialog
{
public:
	cTriggerDialog();
	void AddSelect(
		cTaskFather* p,
		string text,
		string name,
		int cancelret,
		string select0, int ret0,
		string select1, int ret1,
		string select2 = "", int ret2 = -1,
		string select3 = "", int ret3 = -1);
	void AddSelect(cTaskFather* p, string text, int ret0);
	bool AddTask(string path, int id, cTaskFather* ptask, int stage);
	bool AddTask(cTaskFather* ptask, const vector<sTalkList>& dialogList, int stage = 0, int mode = 1);
	bool AddTaskFB(string path, int id, cTaskFather* ptask, int stage);

	bool Process(int id = 0, bool skip = false);

	void Save(ofstream& File);
	void Load(ifstream& File);
	int m_Mode;
	struct sDialogTrigger :public sTaskFather
	{
		int m_Mode;
		void Save(ofstream& File);
		void Load(ifstream& File);
		vector<sTalkList> m_DialogList; //代表一句话
		int m_Nowtext;
		bool Process(bool skip = false);
		bool AddTaskOriginal(int mode, cTaskFather* ptask, int stage, ifstream& File);
		void Reset()
		{
			m_pTask = 0;
			m_DialogList.clear();
			m_Nowtext = -1;
		}
	};
	vector<sDialogTrigger> m_datalist;

private:
	void ReMove();
	void ReMove(int id);

};

