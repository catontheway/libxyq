#include "_global.h"

ulong cPet::GetID(int Pos)
{
	vector<ulong> out;
	GetID(Pos, out);
	return out[0];
}
void cPet::GetID(int Pos, vector<ulong>& out)
{
	if (!m_pPetData)return;
	m_pPetData->GetID(m_PetData.m_JinJieNum.m_index, Pos, out);
}


// void cPet::AutoPetData(int modeid, int stronglv, sAddPoint* addpoint, bool m_bNeedSkill)
// {
// 	if (addpoint)
// 		m_PetData.m_AddPoint = *addpoint;
// 	else
// 	{
// 		sAddPoint addpoint2;
// 		m_PetData.m_AddPoint = addpoint2;
// 	}
// 	m_PetData.modeid = modeid;
// 	if (stronglv == -1)stronglv = g_pMainState->m_GlobalButton[0];
// 	m_PetData.m_StrongLv = stronglv;
// 	m_pPetData = g_pMainState->m_PetDataManager.GetPetData(modeid);
// 	m_PetData.AutoPetData(m_bNeedSkill);
// 
// 	m_PetData.m_Race = m_pPetData->m_Autorace;
// }



const sFightPoint* cPet::GetFightPoint()
{
	return &m_pPetData->m_FightPoint[m_PetData.m_JinJieNum.GetBJinJie()];
}

void cPet::GetRanse(array<sChangeColorData*, 4>& pChangeColor)
{

	forr (pChangeColor, i)
	{
		if (m_PetData.m_RanSe.m_ranse[i].partnum)
		{
			pChangeColor[i] = &m_PetData.m_RanSe.m_ranse[i];
		}
		else pChangeColor[i] = 0;
	}
}

void cPet::Set(sShangPinPet* pet, int stronglv)
{
// 	m_PetData.m_AddPoint = pet->m_addpoint;
// 	m_PetData.modeid = pet->m_modeid;
// 	m_PetData.m_StrongLv = stronglv;
// 	m_pPetData = g_pMainState->m_PetDataManager.GetPetData(m_PetData.modeid);
// 	m_PetData.Set(pet);
// 	int lv = g_pCharacter->m_PcData.m_Lv + cct::get()->lvGapFromRoleAndBaby;
// 	if (lv > cct::get()->maxBabyLv)
// 	{
// 		lv = cct::get()->maxBabyLv;
// 	}
// 	m_PetData.Followlv(lv, true, true, true);
// 	m_PetData.FillHpMp();
// 	m_PetData.m_RanSe = pet->m_ranse;
// 	m_PetData.m_Race = m_pPetData->m_Autorace;
}

void cPet::SetData(sPetData* date)
{
	m_pPetData = date;
//	propertyData.m_Race = m_pPetData->m_Autorace;
}

sModelAction* cPet::GetModelAction(int id)
{
	vector<int>& idlist = m_pPetData->m_ComponentTable[m_PetData.m_JinJieNum.m_index];
	if (idlist.size() <= id)return 0;
	return	&m_pPetData->m_ModelActs[idlist[id]];
}

