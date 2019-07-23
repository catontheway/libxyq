#pragma once
#include "_taskinc.h"

class cTriggerTime
{
public:
	void Add(cTaskFather* task, int stage, int h = -1, int d = -1, int m = -1, int y = -1, int y2 = 0, int m2 = 0, int d2 = 0, int h2 = 0);
	void Remove(cTaskFather* task);
	void Process();
	void Save(ofstream& File);
	void Load(ifstream& File);
	struct sTimeTrigger :public sTaskFather
	{

		void Set(int y, int m, int d, int h, cTaskFather* task, int stage,
			int h2 = 0, int d2 = 0, int m2 = 0, int y2 = 0)
		{
			m_h = h;
			m_d = d;
			m_m = m;
			m_y = y;
			m_h2 = h2;
			m_d2 = d2;
			m_m2 = m2;
			m_y2 = y2;
			m_Stage = stage;
			m_pTask = task;
		}
		int m_h;
		int m_d;
		int m_m;
		int m_y;

		int m_h2;
		int m_d2;
		int m_m2;
		int m_y2;
	};
private:
	vector<sTimeTrigger>  m_list;
};

