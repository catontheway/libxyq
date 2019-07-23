#pragma once
#include "_taskinc.h"



class cTaskNormal :public cTaskFather
{
public:
	void Init(){};
	cTaskNormal(){ m_type = 0; }
	bool Process(int stage);
	const string& getNews();
	cObj* m_pNpc = 0;
private:
};

