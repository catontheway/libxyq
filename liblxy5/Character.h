#pragma once
#include "_objinc.h"

class cSkillManager;
class cCharacter
{
public:
	void UseCard(int id);
	void changeModel(int id);
//	int GetRace();
	void Free();
	void Talk(string str);

// 	void AutoPCData(string name,int modeid,
// 		sAddPoint* addpoint = 0,sZiZhi* zizhi = 0,
// 		eMengPai mengpaid = eMP_无,
// 		int petid = -1);

	int GetSkillLv(int id, cSkillManager* p);

	//int m_Modeid;
	bool AddMoney(int xianjin, int chubei = 0, int cunyin = 0);//增加现金,储备,存银

	//属性数据
	cPcData m_PcData;

	ulong GetID(int Pos)
	{
		vector<ulong> out;
		GetID(Pos, out);
		if (out.size())
			return out[0];
		return 0;
	}
	void GetID(int Pos, vector<ulong>& out);
//	void GetRanse(int Pos, sChangeColorData* (&pChangeColor)[4]);
	void GetRanse(int Pos, array<sChangeColorData*, 4>& pChangeColor);
	const sFightPoint* GetFightPoint();
	string GetName(){ return m_PcData.m_Name; }//得到角色名字
//	bool CanEquip(int EquipType, int EquipLv, int Pos = -1);
	void SetData(sCharacterData* data);
	sCharacterData* GetData(){ return m_pCharacterData; }
private:
	//图像数据
	sCharacterData* m_pCharacterData;
};

