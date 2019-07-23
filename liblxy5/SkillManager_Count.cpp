#include "_global.h"


void cSkillManager::count炎护(int& dam, int TargetID)
{
	cPropertyData*  pTargetData;
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	pTarget->GetPropertyData(pTargetData);

	if (!pTarget->CheckHaveState(201))
	{
		return;
	}
	int mp = min(pTargetData->m_MP, dam / 2);
	dam -= mp;
	AddMp(TargetID, -mp);
	if (pTargetData->m_MP < 1)
	{
		pTarget->ReMoveStateID(201);
	}
}


bool  cSkillManager::CountMagicDamage(int& dam, int UserID, int TargetID, int Damageup, eMagicWuXing wuxing, int& userData)
{
	cPropertyData*  pUserData;
	cPropertyData*  pTargetData;
	cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	pUser->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);

	if (pTargetData->m_FightData.m_WallNum > 0)
	{//大地之墙
		pTargetData->m_FightData.m_WallNum -= 1;
		dam = 0;
		return true;
	}
	int hit = 100 + pUserData->HitRateOfMagic.d1 - pTargetData->HitRateOfMagic.d2;
	if (rand() % 100 >= hit)//法术回避
	{
		dam = 0;
		return true;
	}
	bool is雾杀 = (Damageup == 10086);
	bool is血雨 = (Damageup == 10087);
	if (is雾杀)
	{
		Damageup = 35;
	}
	else if (is血雨)
	{
		Damageup = 20;
	}
	int wakanUser = pUserData->Mana.GetData();    //自身灵力
	int  wakanTarget = pTargetData->Mana.GetData(); //目标灵力
	//	wakanTarget -= pUserData->m_Lv<<1;
	// 盾气
	int turn = m_pFightState->m_pFightWorkList[TargetID]->_myTurn;
	if (pTargetData->isHadPetSkill(75) && turn < 5) // 灵能激发
	{
		wakanTarget += (5 - turn) * pTargetData->m_Lv / 5;
	}

	int& atknum = pTargetData->m_FightData.SufferNum;
	////////////////////////////////////////////////////////////////////////// 呵呵哒 又来越被打越无法术格挡
	int pierce = pUserData->Pierce刺穿OfMagic.d1 + atknum/* * 3*/;
//	if (pierce)
	{
		if (pierce > 100)pierce = 100;
		wakanTarget -= (wakanTarget* pierce) / 100; //无视灵力
	}
// 	int DamageAddPercent = pUserData->DmgPercentOfMagic.d1; //自身法术攻击修炼
// 	int DamageDefPercent = pTargetData->DmgPercentOfMagic.d2;   //目标法术防御修炼
// 	if (DamageDefPercent > 9900)
// 	{
// 		DamageDefPercent = DamageAddPercent + DamageDefPercent - 9900;
// 	}
//	dam = (wakanUser)-(wakanTarget)/*+pUserData->m_Lv*/;

	int 装备伤害分量 = pUserData->m_Lv;
	if (pUser->m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter *pc = (cCharacter*)pUser->m_pIndex;
		装备伤害分量 = pc->m_PcData.getEquipAtk() / 4;
	}
	int skillLv = pUser->GetSkillLv(0);
	if (!skillLv)
	{
		skillLv = pUserData->m_Lv;
	}
	int targetNum = g_pMainState->m_FightWorkList[UserID].m_MaxTargetNum;
	if (targetNum < 1) targetNum = 1;

	dam = (skillLv * Damageup + wakanUser * 10 - wakanTarget * 10 + 装备伤害分量 * 10) * (21 - targetNum) / 200;

// 	if (pUserData->isHadPetSkill(103))
// 	{
// 		// 拥有须弥真言,+魔力*0.4的伤害力
// 		dam += pUserData->PointMag * 2 / 5;
// 	}
	Damageup = 0;
	int xiuliancha = 0;// pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag();
// 	float damf = (float)dam;
// 	if (xiuliancha > 0)
// 	{
// 		for (int i = 0; i < xiuliancha; ++i)
// 		{
// 			damf = damf * 1.02f + 5;
// 		}
// 	}
// 	else
// 	{
// 		for (int i = 0; i < (-xiuliancha); ++i)
// 		{
// 			damf = damf * 0.98f - 5;
// 			if (damf < 1)
// 			{
// 				damf = 1;
// 				break;
// 			}
// 		}
// 	}
// 	dam = (int)damf;
//	Damageup += CorrectWuXing(pUserData, pTargetData, wuxing);//五行修正	
	Damageup += CountSpecial(pUserData, pTargetData/*, pTarget->GetSex()*/);//特攻修正

	dam = dam * (100 + xiuliancha * 2 + pUserData->DmgPercentOfMagic.d1 - pTargetData->DmgPercentOfMagic.d2 + Damageup) / 100;
	dam += pUserData->DmgAddOfMagic.d1 - pTargetData->DmgAddOfMagic.d2 + xiuliancha * 5;

	bool bCri = false;
	// 	bool isPc = pUser->m_IndexType == INDEXTYEP_CHARACTER;
	// 	bool isPT = ((cCharacter*)pUser->m_pIndex)->m_PCData.m_MengPaiID == eMengPai::eMP_普陀山;
	// 	if (!isPc || (isPc && isPT))
	// 	{
	// 
	// 	}

	int damOld = 0;
	if (dam < 0)
	{
		damOld = -dam;
	}
	//五行修正 --> 五行吸收
	if (dam > 0 && rand() % 100 < -CorrectWuXing(pUserData, pTargetData, wuxing))
	{
		bCri = true;
		dam = -dam;
	}

	if (!bCri && dam < 1)
	{
		dam = 1;
	}

// 	else
// 	{
// 		dam = dam * (100 - damageup) / 100;
// 	}

	m_pFightState->m_pFightWorkList[TargetID]->_magicCri = bCri = CountCriMagic(pUserData, pTargetData, dam);//法暴修正

	if (dam > 0)
	{

		if (pUserData->MagicWavePercent)
		{//法术波动
			dam += dam * (rand() % pUserData->MagicWavePercent) / 100;
		}

		if (is血雨)
		{
			dam += userData - damOld;
		}
		else if (Damageup > -1)
		{
			if (dam < 1)
			{
				dam = 1;
			}
		}
//		dam = dam * (100 + DamageAddPercent - DamageDefPercent + Damageup) / 100;
//		dam += (pUserData->m_DamageAddMagicLv.d1 - pTargetData->m_DamageAddMagicLv.d2) * skillLv/*pUserData->m_Lv*/;
		if (rand() % 100 < pUserData->ParryRateOfMaigc.d1 - pUserData->ParryRateOfMaigc.d2)
		{
			dam /= 2;
		}

		//	}
		//	else dam = 1;

		if (dam > 1)
		{
			count炎护(dam, TargetID);
		}
		if (is雾杀)
		{
			userData = max(dam, 0);
			dam = max(dam * 18 / 100, 1);
		}
		CheckFightStateOnLine催眠(TargetID, dam);
		int rate = pTargetData->StabRateOfMagic.d1 - pUserData->StabRateOfMagic.d2;
		if (rand() % 100 < rate)
		{
			rate = pTargetData->StabPercentOfMagic.d1 - pUserData->StabPercentOfMagic.d2;
			int dam2 = dam * rate / 100;
			CheckGodLivePercent(dam2, UserID, TargetID); //神佑
			AddHp(UserID, -dam2);
			SetDamage(dam2, UserID);
		}

//		if (pTargetData->m_FightData.m_bDefend)dam = dam * 4 / 5;//检测是否防御	

		//致伤
//		int rate = pUserData->m_MagDownHPHurt.d1 - pTargetData->m_MagDownHPHurt.d2;
//		if (rate > 0)AddHpHurt(TargetID, -(dam*rate) / 100);

		CheckGodLivePercent(dam, TargetID, UserID); //神佑
	}
	else
	{
		userData = -dam;
	}

//	asert(dam < 20000, "法术伤害超过2万");
	AddHp(TargetID, -dam);
	SetDamage(dam, TargetID);

	pTargetData->m_FightData.SufferNum += 1;
	return bCri;
}



void cSkillManager::CountphysicalDamage(int& dam, int UserID, int TargetID, int Damageup/*=0*/)
{
	cObj* pUser;
	cObj* pTarget;
	cPropertyData* UserData;
	cPropertyData* TargetData;
	pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	pUser->GetPropertyData(UserData);
	pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	pTarget->GetPropertyData(TargetData);
	//sFightData& userFightData = UserData->m_FightProperty;
	sFightData& targetFightData = TargetData->m_FightData;
	if (TargetData->m_FightData.m_WallNum > 0)
	{
		TargetData->m_FightData.m_WallNum -= 1;
		dam = 0;
		return;
	}
	int userAtk = UserData->Atk.GetData();    //自身攻击
	int SufferDef = TargetData->Def.GetData(); //目标防御
	// 盾气
	int turn = m_pFightState->m_pFightWorkList[TargetID]->_myTurn;
	if (TargetData->isHadPetSkill(78) && turn < 5)
	{
		SufferDef += (5 - turn) * TargetData->m_Lv * 2 / 5;
	}
	else if (TargetData->isHadPetSkill(77) && turn < 5)
	{
		SufferDef += (5 - turn) * TargetData->m_Lv / 5;
	}

	int& atknum = targetFightData.SufferNum;

	////////////////////////////////////////////////////////////////////////// 呵呵哒 越被打格挡越没用
	int picrcerate = UserData->Pierce刺穿.d1 - TargetData->Pierce刺穿.d2 + atknum/**3*/;
	bool is壁垒 = false;
	bool is善恶 = false;
	bool is力劈 = false;
	if (Damageup == 10086)
	{
		is力劈 = true;
		Damageup = 0;
//		picrcerate += 5;
	}
	if (Damageup == 10087)
	{
		Damageup = 0;
		picrcerate += 5;
		if (TargetData->m_FightData.m_bDefend)
		{
			is壁垒 = true;
		}
	}
	if (Damageup == 10088)
	{
		is善恶 = true;
		Damageup = 0;
//		picrcerate += 5;
	}
	if (picrcerate > 0)
	{
		SufferDef -= (SufferDef * picrcerate) / 100;//无视防御
	}

	if (is力劈)
	{
		// 力劈华山
		dam += userAtk * 3 - (SufferDef + TargetData->Atk.GetData() * 2);
	}
	else
	{
		dam += (userAtk)-(SufferDef);
	}
// 	if (dam < 1)
// 	{
// 		dam = 1;
// 	}
	//修炼和伤害修正
	int xiuliancha = 0;// UserData->m_XiuLian.GetAtk() - TargetData->m_XiuLian.GetDef();
// 	float damf = (float)dam;
// 	if (xiuliancha > 0)
// 	{
// 		for (int i = 0; i < xiuliancha; ++i)
// 		{
// 			damf = damf * 1.02f + 5;
// 		}
// 	}
// 	else
// 	{
// 		for (int i = 0; i < (-xiuliancha); ++i)
// 		{
// 			damf = damf * 0.98f - 5;
// 			if (damf < 1)
// 			{
// 				damf = 1;
// 				break;
// 			}
// 		}
// 	}
// 	dam = (int)damf;
//	Q_ASSERT(dam < 50000, "修炼后伤害超过五万");

	Damageup += CountSpecial(UserData, TargetData/*, pTarget->GetSex()*/);//特攻修正
	Damageup += UserData->DmgPercent.d1 - TargetData->DmgPercent.d2 + xiuliancha * 2;
// 	int atk2345 = UserData->ShiXueAdd; //攻击数修正
// 	if (atk2345 >= 0xffffff)
// 	{
// 		atk2345 -= 0xffffff;
// 	}
// 	// 	while (atk2345 >= 0xffff)
// 	// 	{
// 	// 		atk2345 -= 0xffff;
// 	// 	}
// 	atk2345 *= atknum;
// 	Damageup += atk2345;

//	int& userlv = UserData->m_Lv;  //自身等级
	if (Damageup < 0 && dam < 0)
	{
		dam = 1;
	}
	dam += dam * Damageup / 100;
	



	//结果修正
	dam += UserData->DmgAdd.d1 - TargetData->DmgAdd.d2 + xiuliancha * 5;
//	dam += (UserData->m_DamageAddLv.d1 - TargetData->m_DamageAddLv.d2) * userlv;


// 	if (TargetData->DmgPercent.d2 > 9900)
// 	{
// 		dam = dam * (100 + 9900 - TargetData->DmgPercent.d2) / 100;
// 	}

	//必杀修正
	CountCriDamage(UserData, TargetData, dam);

	if (!is善恶 && rand() % 100 < UserData->ParryRate.d1 - UserData->ParryRate.d2)
		dam /= 2;

	if (dam < 1)dam = 1;

	int damSE = dam;
	if (is善恶)
	{
		if (rand() % 100 < 75)
		{
			damSE *= 2;
		}
		else
		{
			damSE /= -2;
		}
	}
	else if (dam > 0 && TargetData->m_FightData.m_bDefend)
	{
		if (is壁垒)
		{
			dam *= 2;
		}
		else
		{
			dam /= 2;
		}
	}
	if (damSE > 0)
	{
		CheckFightStateOnLine催眠(TargetID, dam);
	}
	CheckPoision(UserID, TargetID);//中毒修正
	int damOld = dam;
	if (is善恶)
	{
		dam = 0;
	}
	CountProtect(dam, pUser, pTarget);//保护伤害修正
	if (is善恶)
	{
		dam = damOld;
	}
	count炎护(dam, TargetID);
	SuckBlood(dam, UserID, TargetData);//吸血
	CheckFanZheng(UserID, TargetID, dam);//反震
	//致伤
	//	Q_ASSERT(dam < 50000, "保护后超过五万");
// 	int rate = UserData->m_AtkDownHPHurt.d1 - TargetData->m_AtkDownHPHurt.d2;
// 	if (rate > 0)AddHpHurt(TargetID, -(dam*rate) / 100);
// 	//降蓝
// 	rate = UserData->m_AtkDownMP.d1 - TargetData->m_AtkDownMP.d2;
// 	if (rate > 0)AddMp(TargetID, -(dam*rate) / 100);
// 	//降攻
// 	if (TargetData->m_AtkDownAtk.d1)
// 	{
// 		if (TargetData->Atk.GetData() > 1)
// 		{
// 			rate = UserData->m_AtkDownAtk.d1 - TargetData->m_AtkDownAtk.d2;
// 			if (rate > 0)
// 			{
// 				if (TargetData->Atk.GetData() <= rate)rate = TargetData->Atk.GetData() - 1;
// 				TargetData->Atk.AddDataAdd(-rate);
// 			}
// 		}
// 	}
// 	//降防
// 	if (TargetData->m_AtkDownDef.d1)
// 	{
// 		if (TargetData->Def.GetData() > 1)
// 		{
// 			rate = UserData->m_AtkDownDef.d1 - TargetData->m_AtkDownDef.d2;
// 			if (rate > 0)
// 			{
// 				if (TargetData->Def.GetData() <= rate)rate = TargetData->Def.GetData() - 1;
// 				TargetData->Def.AddDataAdd(-rate);
// 			}
// 		}
// 	}
// 	//降命中
// 	if (TargetData->m_AtkDownHit.d1)
// 	{
// 		if (TargetData->Hit.GetData() > 1)
// 		{
// 			rate = UserData->m_AtkDownHit.d1 - TargetData->m_AtkDownHit.d2;
// 			if (rate > 0)
// 			{
// 				if (TargetData->Hit.GetData() <= rate)rate = TargetData->Hit.GetData() - 1;
// 				TargetData->Hit.AddDataAdd(-rate);
// 			}
// 		}
// 	}
// 	//降灵
// 	if (TargetData->m_AtkDownWakan.d1)
// 	{
// 		if (TargetData->Mana.GetData() > 1)
// 		{
// 			rate = UserData->m_AtkDownWakan.d1 - TargetData->m_AtkDownWakan.d2;
// 			if (rate > 0)
// 			{
// 				if (TargetData->Mana.GetData() <= rate)rate = TargetData->Mana.GetData() - 1;
// 				TargetData->Mana.AddDataAdd(-rate);
// 			}
// 		}
// 	}
// 	//降速
// 	if (TargetData->m_AtkDownSpd.d1)
// 	{
// 		if (TargetData->Speed.GetData() > 1)
// 		{
// 			rate = UserData->m_AtkDownSpd.d1 - TargetData->m_AtkDownSpd.d2;
// 			if (rate > 0)
// 			{
// 				if (TargetData->Speed.GetData() <= rate)rate = TargetData->Speed.GetData() - 1;
// 				TargetData->Speed.AddDataAdd(-rate);
// 			}
// 		}
// 	}
// 
// 	//降CP
// 	if (TargetData->m_AtkDownCP.d1)
// 	{
// 		rate = UserData->m_AtkDownCP.d1 - UserData->m_AtkDownCP.d2;
// 		if (rate > 0)UserData->m_CP -= rate;
// 		if (UserData->m_CP < 0)UserData->m_CP = 0;
// 	}

	if (is善恶)
	{
		dam = damSE;
	}
	CheckGodLivePercent(dam, TargetID, UserID); //神佑

//	asert(dam < 35555, "物理伤害超过3万");
	AddHp(TargetID, -dam);
	SetDamage(dam, TargetID);
	atknum += 1;
}



//必杀修正
void cSkillManager::CountCriDamage(cPropertyData* user, cPropertyData* target, int& nowdam)
{
	if (user->m_FightData.m_bCri)
		nowdam += (nowdam*((rand() % 20) + 100 + user->CriDmgPercent.d1 - target->CriDmgPercent.d2)) / 100;
}

bool cSkillManager::CountCri(cPropertyData* user, cPropertyData* target)
{
	int cri = user->CriRate.d1 - target->CriRate.d2;
	if ((rand() % 100) < cri)
	{
		user->m_FightData.m_bCri = true;
	}
	else
	{
		user->m_FightData.m_bCri = false;
	}
	return user->m_FightData.m_bCri;
}
//法暴修正
bool cSkillManager::CountCriMagic(cPropertyData* user, cPropertyData* target, int& nowdam)
{
	bool bCri = false;
	int cri = user->CriRateOfMagic.d1 - target->CriRateOfMagic.d2;
	if ((rand() % 100) < cri)
	{
		bCri = true;
		nowdam += nowdam;
	}
	return bCri;
}

bool cSkillManager::CountParry(cPropertyData* pUserData, cPropertyData* pTargetData)
{
	int Parry = pTargetData->ParryRate.d1 - pUserData->ParryRate.d2;
	////////////////////////////////////////////////////////////////////////// 呵呵哒 格挡率也扣
	Parry -= pTargetData->m_FightData.SufferNum/* * 5*/;
	return pTargetData->m_FightData.m_bDefend = rand() % 100 < Parry;
}

bool cSkillManager::CountProtect(int& dam, cObj* pUser, cObj* pTarget)
{
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	if (pTargetData->m_FightData.m_guardID.size())
	{
		cPropertyData* pUserData;
		pUser->GetPropertyData(pUserData);

		int target2 = pTargetData->m_FightData.m_guardID[0];
		if (!g_pMainState->m_FightWorkList[target2].isExist || g_pMainState->m_FightWorkList[target2].CheckDie())
		{
		}
		else
		{
			int dam3 = dam / 20;
			int dam2 = dam3 * 15;
			dam = dam3 * 5;
			AddHp(target2, -dam2);
			SetDamage(dam2, target2);
			g_pMainState->m_FightWorkList[target2].SetWork(WORKTYPE_RETURN);
			m_pFightState->SetSuffer_state30(target2, pUser->GetDirection(), -1);
		}
		pTargetData->m_FightData.m_guardID.erase(pTargetData->m_FightData.m_guardID.begin());
		
		return true;
	}
	return false;
}




int cSkillManager::CountSpecial(cPropertyData* user, cPropertyData* target/*, bool targetSex*/)
{
	int damageup = 0;
	// 狼： 驱鬼 高级驱鬼
	if (user->Ghost.d2 > 0 && target->Ghost.d1 > 0)
	{
		damageup += user->Ghost.d2/* - target->Ghost.d1*/;
	}
// 	switch (target->m_Race % 10)
// 	{
// 	case 0:
// 		damageup = user->GoldSpecial.d1 - target->ghostSpecial.d2;     //神族特攻
// 		break;
// 	case 1:
// 		damageup = user->MagSpecial.d1 - target->MagSpecial.d2;    //魔族特攻
// 		break;
// 	case 2:
// 		damageup = user->ImmortalSpecial.d1 - target->ImmortalSpecial.d2; //仙族特攻
// 		break;
// 	case 3:
// 		damageup = user->MonsterSpecial.d1 - target->MonsterSpecial.d2;//妖怪特攻
// 		break;
// 	case 4: // 隐身楚楚感知鬼眼牛劲占用
// 		//		damageup = user->PeopleSpecial.d1 - target->PeopleSpecial.d2; //人
// 		break;
// 	case 5:	//灵体无法被特攻
// 		break;
// 	case 6:
// 		damageup = user->machineSpecial.d1 - target->machineSpecial.d2;//机械特攻
// 		break;
// 	default:
// 
// 		break;
// 	}
// 	if (target->m_Race > 11)
// 	{
// 		damageup += user->ghostSpecial.d1 - target->ghostSpecial.d2; //鬼特攻
// 	}
// 	if (targetSex)
// 	{
// 		damageup += user->BoySpecial.d1 - target->BoySpecial.d2;  //男	
// 	}
// 	else damageup += user->GirlSpecial.d1 - target->GirlSpecial.d2;//女

	return damageup;
}

bool cSkillManager::CoutComboMagic(int skillid, cPropertyData* user, int userid, cPropertyData* ptarget)
{
	vector<int> skills =
	{ 
		11, 28, 31, 74, 79, 80, 88, 131, 132,
		194, 195, 196, 197,
		2084, 2085, 2086, 2087, 2088, 2089, 2090, 2091
		/*, 2101 */, 2102
	};
	bool f = false;
	for (auto id : skills)
	{
		if (id == skillid)
		{
			f = true;
			break;
		}
	}

	if (!f)
	{
		return false;
	}
	// 狼 判断 追加类型的法术不会连击
	user->m_FightData.AttackNum += 1;
	if (user->m_FightData.AttackNum < 2)
	{
		if ((rand() % 100) < (user->ComboRateOfMagic.d1 - ptarget->ComboRateOfMagic.d2))
		{
			g_pMainState->m_FightWorkList[userid].SetWorkFront(WORKTYPE_MAGIC);
			return true;
		}
	}

	return false;
}

bool cSkillManager::CoutCombo连击(cPropertyData* user, cPropertyData* target)
{
	user->m_FightData.AttackNum += 1;
	if (user->m_FightData.AttackNum < user->ComboNumUp)
	{
		if (user->m_FightData.AttackNum < user->ComboNumDown)
		{
			return true;
		}
		int rate = user->ComboRate.d1 - target->ComboRate.d2;
		if (rand() % 100 < rate)
		{
			return true;
		}
	}
	return false;
}




void cSkillManager::CountMagic2Damage固定(int& dam, int UserID, int TargetID, eMagicWuXing wuxing)
{
	//计算固定伤害
	cPropertyData*  pUserData;
	cPropertyData*  pTargetData;
	cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	pUser->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);

	if (pTargetData->m_FightData.m_WallNum > 0)
	{//大地之墙
		pTargetData->m_FightData.m_WallNum -= 1;
		dam = 0;
		return;
	}
	int hit = 100 + pUserData->HitRateOfMagic.d1 - pTargetData->HitRateOfMagic.d2;
	if (rand() % 100 >= hit)//法术回避
	{
		dam = 0;
		return;
	}

	int damageup = 0;
	//特攻修正
	damageup += CountSpecial(pUserData, pTargetData/*, pTarget->GetSex()*/);
	damageup += pUserData->DmgPercentOfFix.d1 - pTargetData->DmgPercentOfFix.d2;

	dam = (dam*(100 + damageup)) / 100;
	// 	if ((TargetID < 10) || g_pMainState->m_AI.m_bPKMode)
	// 	{//普通任务时伤害其实是2倍化的
	// 		dam= dam >>1;
	// 	}
	//	if (dam < 1)dam = 1;
	//致伤
	damageup = -CorrectWuXing(pUserData, pTargetData, wuxing);//五行修正 --> 五行吸收
	if (rand() % 100 < damageup)
	{
		dam = -dam;
	}
// 	else if (damageup > 0)
// 	{
// 		dam = dam * (100 - damageup) / 100;
// 	}
	if (dam > 0)
	{
// 		int rate = pUserData->m_MagDownHPHurt.d1 - pTargetData->m_MagDownHPHurt.d2;
// 		if (rate > 0) AddHpHurt(TargetID, -(dam * rate) / 100);

// 		if (pTargetData->StabRateOfMagic.d1)
// 		{
// 			//int rate = pTargetData->m_StabRateMagic.d1 - pUserData->m_StabRateMagic.d2;
// 			if (dam)
// 			{
// 				int rate = pTargetData->StabPercentOfMagic.d1 - pUserData->StabPercentOfMagic.d2;
// 				int dam2 = dam * rate / 100;
// 				CheckGodLivePercent(dam, UserID, TargetID); //神佑
// 				AddHp(UserID, -dam);
// 				SetDamage(dam, UserID);
// 			}
// 		}

		CheckFightStateOnLine催眠(TargetID, dam);
		CheckGodLivePercent(dam, TargetID, UserID); //神佑
	}

	AddHp(TargetID, -dam);
	SetDamage(dam, TargetID);
	pTargetData->m_FightData.SufferNum += 1;
}

