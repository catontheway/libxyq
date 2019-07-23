#pragma once
#include "_global.h"

class cPet
{
public:
	sModelAction* GetModelAction(int id);
	void SetData(sPetData* date);
	sPetData* GetData(){ return m_pPetData; }

	void Set(sShangPinPet* pet, int stronglv);

	const sFightPoint* GetFightPoint();
	//	bool m_ID=0;
	cPetData  m_PetData;

	//通过等级(0-999) 和 强度(范围0-9) 计算属性 在使用这函数前必需设置加点方式
//	void AutoPetData(int modeid, int xiulian, sAddPoint* addpoint, bool m_bNeedSkill = true);
	void GetID(int Pos, vector<ulong>& out);// ulong& data1, ulong& data2, ulong& data3,ulong& data4);
	ulong GetID(int Pos);
//	void GetRanse(sChangeColorData* (&pChangeColor)[4]);
	void GetRanse(array<sChangeColorData*, 4>& pChangeColor);
private:
	sPetData*  m_pPetData = 0;

};