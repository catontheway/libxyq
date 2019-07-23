#pragma once
#include "_global.h"

const int  c_PetNumber = 200; // 183;
class cPetManager
{
public:
	bool Init();
	void Init(int i, ifstream &File);
	void  GetLimitList(int lv, vector<int>& idlist, int stronglv);
	sPetData* GetPetData(int ID){ if (ID < c_PetNumber)return &m_PetList[ID]; return nullptr; }
	array<sPetData, c_PetNumber> m_PetList;
private:
	bool m_bInit = false;
};