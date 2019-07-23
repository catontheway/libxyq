#include "_global.h"


int cSkillManager::AddHp(int target, int num, int percent)
{
	cPropertyData* pData;
	cObj* pObj = g_pMainState->m_FightWorkList[target].m_pObj;
	pObj->GetPropertyData(pData);
	int& hp = pData->m_HP;
	if (0 == hp)return 0;
	int& hphurt = pData->m_HP2;
	int hpadd = num;
	int hpmax = pData->HPMax.GetData();
	if (percent)
	{
		hpadd *= hpmax;
		if (abs(hpadd) > abs(percent*num))hpadd = percent*num;
		hpadd /= 100;
	}
	hp += hpadd;
	if (hp > hphurt)hp = hphurt;
	else if (hp < 0)hp = 0;


	if (target == g_pMainState->m_HeroID)
	{
		g_pMainState->m_PCHead.UpdatePcHp();
	}
	else
		if (target == g_pMainState->m_HeroID + 5)
		{
		g_pMainState->m_PCHead.UpdatePetHp();
		}
	if (g_StateType == STATE_MAIN)return hpadd;

	if (hpadd < 0)
	{
		int cpadd = hpadd * (-50) / hpmax;
		if (pData->m_HP < 1)
		{
			g_pMainState->m_FightWorkList[target].SetDie(true);
			cpadd = -pData->m_CP / 2;
		}
		pData->m_CP += cpadd;
		if (pData->m_CP > pData->m_CPMax)pData->m_CP = pData->m_CPMax;
		if (target == g_pMainState->m_HeroID)
		{
			g_pMainState->m_PCHead.UpdatePcCp();
		}
	}

	pObj->UpdateHpLine();
	return hpadd;
}


int cSkillManager::AddMp(int target, int num, int percent)
{
	cPropertyData* pData;
	cObj* pObj = g_pMainState->m_FightWorkList[target].m_pObj;
	pObj->GetPropertyData(pData);
	int& mp = pData->m_MP;
	int  mpmax = pData->MPMax.GetData();
	int mpadd = num;
	if (percent)
	{
		mpadd *= mpmax;
		if (abs(mpadd) > abs(percent*num))mpadd = percent*num;
		mpadd /= 100;
	}
	mp += mpadd;
	if (mp > mpmax)mp = mpmax;
	else if (mp < 0)mp = 0;

	if (target == g_pMainState->m_HeroID)
	{
		g_pMainState->m_PCHead.UpdatePcMp();
	}
	else
		if (target == g_pMainState->m_HeroID + 5)
		{
		g_pMainState->m_PCHead.UpdatePetMp();
		}
	return mpadd;
}

void cSkillManager::AddHpHurt(int target, int num, int percent)
{
	cPropertyData* pData;
	cObj* pObj = g_pMainState->m_FightWorkList[target].m_pObj;
	pObj->GetPropertyData(pData);
	int& hp = pData->m_HP;
	if (0 == hp)return;
	int hphurt = pData->m_HP2;
	int hpmax = pData->HPMax.GetData();
	int dam = num;
	if (percent)
	{
		dam *= hpmax;
		if (abs(dam) > abs(num*percent))dam = num*percent;
		dam /= 100;
	}
	hphurt += dam;
	if (hphurt > hpmax)hphurt = hpmax;
	else if (hphurt < 0)hphurt = 0;
	pData->m_HP2 = hphurt;
	if (target == g_pMainState->m_HeroID)
	{
		g_pMainState->m_PCHead.UpdatePcHp();
	}
	else
		if (target == g_pMainState->m_HeroID + 5)
		{
		g_pMainState->m_PCHead.UpdatePetHp();
		}
}

void cSkillManager::AddCp(int target, int num, int percent)
{
	cPropertyData* pData;
	cObj* pObj = g_pMainState->m_FightWorkList[target].m_pObj;
	pObj->GetPropertyData(pData);
	int& cp = pData->m_CP;
	int dam = num;
	if (percent)
	{
		cp *= cPcData::m_CPMax;
		cp /= 100;
	}
	cp += dam;
	if (cp > cPcData::m_CPMax)cp = cPcData::m_CPMax;
	else if (cp < 0)cp = 0;

	if (target == g_pMainState->m_HeroID)
	{
		g_pMainState->m_PCHead.UpdatePcCp();
	}
}
//¸´»î
bool cSkillManager::Resurgence(int TargetID)
{
	return g_pMainState->m_ItemManage.relife(1, TargetID);
}





void cSkillManager::CorrectCureHP(int& dam, int UserID, int TargetID)
{
	int hp2 = 0;
	CorrectCureHP(dam, hp2, UserID, TargetID);
	return;
	cPropertyData* pUser;
	cPropertyData* pTarget;
	g_pMainState->m_FightWorkList[UserID].m_pObj->GetPropertyData(pUser);
	g_pMainState->m_FightWorkList[TargetID].m_pObj->GetPropertyData(pTarget);
	dam += (dam* (pUser->DmgPercentOfCure.d1 + pTarget->DmgPercentOfCure.d2)) / 100;
	int crirate = pUser->CriRateOfCure.d1 + pUser->CriRateOfCure.d2;
	if (rand() % 100 < crirate)
	{
		dam = dam * 2;
	}
	dam += pUser->DmgAddOfCure.d1 + pUser->DmgAddOfCure.d2;
	AddHp(TargetID, dam);
	SetDamage(-dam, TargetID);
}


void cSkillManager::CorrectCureHP(int& hp, int& hp2, int UserID, int TargetID)
{
	cPropertyData* pUser;
	cPropertyData* pTarget;
	g_pMainState->m_FightWorkList[UserID].m_pObj->GetPropertyData(pUser);
	g_pMainState->m_FightWorkList[TargetID].m_pObj->GetPropertyData(pTarget);
	hp += (hp* (pUser->DmgPercentOfCure.d1 + pTarget->DmgPercentOfCure.d2)) / 100;
	hp2 += (hp2* (pUser->DmgPercentOfCure.d1 + pTarget->DmgPercentOfCure.d2)) / 100;
	int crirate = pUser->CriRateOfCure.d1 + pUser->CriRateOfCure.d2;
	if (rand() % 100 < crirate)
	{
		hp *= 2;
		hp2 *= 2;
	}
	hp += pUser->DmgAddOfCure.d1 + pUser->DmgAddOfCure.d2;
	hp2 += pUser->DmgAddOfCure.d1 + pUser->DmgAddOfCure.d2;
	AddHpHurt(TargetID, hp2);
	int hpOld = pTarget->m_HP;
	AddHp(TargetID, hp);
	SetDamage(hpOld - pTarget->m_HP, TargetID);
}


void cSkillManager::CorrectCureMP(int& dam, int UserID, int TargetID)
{
	cPropertyData* pUser;
	cPropertyData* pTarget;
	g_pMainState->m_FightWorkList[UserID].m_pObj->GetPropertyData(pUser);
	g_pMainState->m_FightWorkList[TargetID].m_pObj->GetPropertyData(pTarget);
	dam += (dam* (pUser->DmgPercentOfCure.d1 + pTarget->DmgPercentOfCure.d2)) / 100;
	AddMp(TargetID, dam);
//	SetDamage(-dam, TargetID);
}
