#include "_global.h"


bool cSkillManager::CheckFightState(int FightListID)
{
	sFightWork* pTargetList = &g_pMainState->m_FightWorkList[FightListID];
	cObj* pTarget = m_pFightState->m_pFightWorkList[FightListID]->m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	if (!pTargetList->m_pObj->m_StateList.size())return true;
	sBuff buf;
	for (list<sBuff>::iterator Iterator = pTarget->m_StateList.begin(); Iterator != pTarget->m_StateList.end();)
	{
		Iterator->remainingTimes -= 1;
		if (Iterator->remainingTimes < 0 || Iterator->ID == 1002) //1002防御
		{
			list<sBuff>::iterator it2 = Iterator;
			Iterator++;
			g_pMainState->m_SkillManager.SetDateBuffDown(it2);
			it2->data.Free();
			pTargetList->m_pObj->m_StateList.erase(it2);
			continue;
		}
		if (Iterator->ID == 1997)
		{
			int zy = pTargetData->m_FightData.zhanyi;
			if (zy == Iterator->damage)
			{
				Iterator++;
				continue;
			}
			Iterator->damage = zy;
			if (zy >= 3)
			{
				Iterator->data.Load(0xD1C3B611);
			}
			else if (zy == 2)
			{
				Iterator->data.Load(0x3D3C8D10);
			}
			else if (zy == 1)
			{
				Iterator->data.Load(0xC4FE8E3F);
			}
			else
			{
				Iterator->data.Free();
			}
			Iterator++;
			continue;
		}
		if (pTargetList->CheckDie())
		{
			Iterator++;
			continue;
		}
		switch (Iterator->ID)
		{
		case 1://后发
		{
			pTargetList->m_SkillSelect.SkillLv = pTarget->GetSkillLv(0/*1*/);
			pTargetList->m_SkillSelect.SkillID = 1010;
			pTargetList->m_SkillSelect.TargetID = Iterator->userID;
			pTargetList->targetID = Iterator->userID;
			pTargetList->m_WorkType = WORKTYPE_MAGIC;
		}
			break;
// 		case 6: //反间计
// 		{
// 			int autoSelect = g_pMainState->m_AI.find追击反间月光(FightListID, 3, true);
// 			if (-1 != autoSelect)
// 			{
// 				// 狼
// 				m_pFightState->m_pFightWorkList[FightListID]->m_work.clear();
// 				//
// 				m_pFightState->m_pFightWorkList[FightListID]->m_WorkType = WORKTYPE_ATTACK;
// 				m_pFightState->m_pFightWorkList[FightListID]->m_SkillSelect.SkillLv = 0;
// 				m_pFightState->m_pFightWorkList[FightListID]->m_SkillSelect.SkillID = 1000;
// 				m_pFightState->m_pFightWorkList[FightListID]->targetID = autoSelect;
// 				m_pFightState->m_pFightWorkList[FightListID]->m_SkillSelect.TargetID = autoSelect;
// 			}
// 		}
// 			break;
		case 50: // 毒
		case 122:// 尸腐毒
		{
			cPropertyData* petdata;
			g_pMainState->m_FightWorkList[FightListID].m_pObj->GetPropertyData(petdata);
			int dam = petdata->m_HP / 15;
			if (dam > (petdata->m_Lv) << 4)
				dam = (petdata->m_Lv) << 4;
			if (dam < petdata->m_Lv)
			{
				dam = petdata->m_Lv;
			}
// 			if (Iterator->damage)
// 				dam += (dam*Iterator->damage) / 100;
			count炎护(dam, FightListID);
			dam = -AddHp(FightListID, -dam);
			SetDamage(dam, FightListID);
			AddHpHurt(FightListID, -petdata->HPMax.GetData() / 100);
			if (petdata->m_HP < 1)
			{
				g_pMainState->m_pFightState->SetDie(FightListID);
				pTargetData->m_CP /= 2;
			}
		}
			break;
		case 103:// 紧箍咒
		case 198: //雾杀
		{
			int dam = 0;
			if (Iterator->ID == 198)
			{
				dam = Iterator->damage * (27 - Iterator->remainingTimes * 3) / 100 + 1;
			}
			else
			{
				dam = Iterator->damage;
			}
			count炎护(dam, FightListID);
			SetDamage(-AddHp(FightListID, -dam), FightListID);

			cPropertyData* petdata;
			g_pMainState->m_FightWorkList[FightListID].m_pObj->GetPropertyData(petdata);
			if (petdata->m_HP < 1)
			{
				g_pMainState->m_pFightState->SetDie(FightListID);
				pTargetData->m_CP /= 2;
			}
		}
			break;
		}
		Iterator++;
	}
	return true;
}






bool cSkillManager::CheckFightStateOnLine催眠(int FightListID, int& dam)
{
	cObj* pUser = g_pMainState->m_FightWorkList[FightListID].m_pObj;
	cPropertyData* pPetdata;
	pUser->GetPropertyData(pPetdata);
	if (pUser->CheckHaveState(14))
	{//催眠符 超过1%就被打醒
		if (dam * 100 / pPetdata->HPMax.GetData() > 0)
			pUser->ReMoveStateID(14);
	}
	return true;
}




bool cSkillManager::CheckHit(cPropertyData* pUserData, cPropertyData *pTargetData, int offset /* = 0 */)
{
// 	if (pUserData->Hide.d2 - pTargetData->Hide.d1 < 0)
// 	{
// 		return pTargetData->m_FightData.m_bHit = false;
// 	}

// 	vector<int> skillids = { 0, 7, 50, 71, 97, 98, 141, 142, 143, 148, 2092, 2093, 2094, 2098, 2099 };
// 	forr(skillids, i)
// 	{
// 		if (skillids[i] == skillid)
// 		{
// 			return pTargetData->m_FightProperty.m_bHit = true;
// 		}
// 	}

	int hit = pUserData->Hit.GetData() + 0x4F;
	int avoid = pTargetData->Evade.GetData()/* + hit*/;
	if (avoid < 1)avoid = 1;
	int hitrate = offset + pUserData->HitRate.d1 - pTargetData->HitRate.d2 + (55 * hit) / avoid;
	if (hitrate < 2)
	{
		hitrate = 2;
	}
	if (rand() % 100 < hitrate)  //几率命中
	{
		pTargetData->m_FightData.m_bHit = true;
		return  true;
	}
	pTargetData->m_FightData.m_bHit = false;
	return false;
}


bool cSkillManager::CheckCRI(cPropertyData* pUserData, cPropertyData *pTargetData, int offset /*= 0*/)
{
	int cri = pUserData->CriRate.d1;
	int uncri = pTargetData->CriRate.d2;
	int truecri = cri - uncri + offset;
	if (rand() % 101 < truecri)
		return true;
	return false;
}



void cSkillManager::CheckPoision(int UserID, int TargetID, int offs, sBuff buf)
{
	cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	cPropertyData* pUserData;
	pUser->GetPropertyData(pUserData);
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
//	if (pTargetData->m_Race == 5 || pTargetData->m_Race == 6 || pTargetData->m_Race >= 1000)return;//机械和鬼不会中毒
	if (pTargetData->Ghost.d1 > 0)
	{
		return;
	}
	int Poision = offs + pUserData->HitRateOfPoison.d1 - pTargetData->HitRateOfPoison.d2; //中毒率
	if (Poision > 100)
	{
		Poision = 100;
	}
	Poision -= pTargetData->HitRateOfPoison.d2 / 2;
	if (rand() % 100 < Poision)
	{
//		sBuff buf;
//		buf.damage = pUserData->DmgPercentOfPoison.d1 - pTargetData->DmgPercentOfPoison.d2;//中毒伤害修正
//		buf.remainingTimes = time;
		g_pMainState->m_SkillManager.SetDateBuffUp(UserID, TargetID, buf.ID, buf);
	}
}


void cSkillManager::CheckPoision(int UserID, int TargetID)
{
	sBuff buf;
	buf.remainingTimes = 8;
	buf.ID = 50;
	CheckPoision(UserID, TargetID, 0, buf);
}



int cSkillManager::CheckMagicHit(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	//法术的命中
	cObj* pUser = g_pMainState->m_FightWorkList[UserID].m_pObj;
	cObj* pTarget = g_pMainState->m_FightWorkList[TargetID].m_pObj;
	cPropertyData* pUserData;
	cPropertyData* pTargetData;
	pUser->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);
// 	if (abs(UserID - TargetID) >= 10 && pUserData->Hide.d2 - pTargetData->Hide.d1 < 0)
// 	{
// 		return false;
// 	}

	int rate = 0;
	auto func = [&]()
	{
//		if (pTargetData->m_Race >= 1000)
		if (pTargetData->Ghost.d1 > 0 ||
			pTarget->CheckHaveState(0) ||  //横扫
			pTarget->CheckHaveState(7) ||  //破斧
			pTarget->CheckHaveState(142))  //鹰击
		{
			rate -= 999;
		}
		else
		{
			if (!Skilllv)
			{
				Skilllv = pUserData->m_Lv;
			}
			// 修炼差距 1.5 * 25 = 37.5;
			// 等级差距 调整: 1 - 2.25
			int xl = cct::getCurrMaxXiulianLv(pUserData->m_Lv) + 1;
			int gap = cct::getCurrMaxXiulianLv(cct::MaxRoleLv) - xl;
			rate += (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag()) * (37.5f / xl);
			//封印法术命中
			rate += pUserData->HitRateOfSeal.d1 - pTargetData->HitRateOfSeal.d2;
			rate += (Skilllv - cct::LvGapFromRoleAndSkill - pTargetData->m_Lv) * (1 + gap * 1.0f / 20);

		//	rate -= pTargetData->HitRateOfSeal.d2 / 2;
			if (pUserData->_isWeakSeal)
			{
				rate -= 35;
			}
			rate = max(2, rate);
			rate = min(98, rate);
		}
	};
	switch (sSkillID)
	{
	case 2084:
	case 2085:
	case 2086:
	case 2087:
	case 2088:
	case 2089:
	case 2090:
	case 2091:
	case 2102: //天降灵葫
	case 2105: //月光
		
	case 28: // 落雷符
	case 31: // 唧唧歪歪
	case 61: // 雨落寒沙
	case 74: // 雷霆万钧
	case 105: //五形法术
	case 106:
	case 107:
	case 108:
	case 109:
	case 116: // 阎罗判官
	case 117:
	case 131: //魔王
	case 132:
	case 162:// 天罗地网
	case 186:// 夺命咒
	case 194:// 落叶萧萧
	case 195:// 
	case 196:// 
	case 197:// 
	case 198:// 雾杀
	case 199:// 血雨
		rate += 100;
		//法术命中率
		rate += pUserData->HitRateOfMagic.d1 - pTargetData->HitRateOfMagic.d2;
		break;
		//大唐
	case 6:
		rate += 50;
		func();
		break;
		//方寸
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 27:
		rate += 60;
		func();
		break;
		//女儿
	case 54:rate += 60; func(); break;//似玉生香
	case 59:rate += 30; func(); break;
		//天宫
	case 67:rate += 60; func(); break;
	case 68:rate += 60; func(); break;
	case 69:rate += 60; func(); break;
		//五庄
	case 89:rate += 60; func(); break;
		//地府
	case 122:
	{
		rate += 90;
//		rate += (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag()) * 2;
		//封印法术命中
		rate += /*pUserData->HitRateOfSeal.d1 - */pTargetData->HitRateOfSeal.d2;
		rate += pTargetData->HitRateOfSeal.d2 / 2;
		if (pUserData->_isWeakSeal)
		{
			rate += 35;
		}
	}
		func(); 
		break;
	case 127:rate += 90; func(); break;
	case 129:rate += 60; func(); break;
		//ST
	case 144:rate += 60; func(); break;
		//PS
	case 154:rate += 80; func(); break; // 勾魂
	case 155:rate += 80; func(); break; // 摄魄
	case 156:rate += 60; func(); break; // 魔音
	case 159:rate += 60; func(); break; // 含情
//	case 164:rate += 50; func(); break; // 姐妹
// 		if (pUserData->m_Popularity - pTargetData->m_Popularity >= 50)
// 		{
// 			rate += (pUserData->m_Popularity - pTargetData->m_Popularity) / 50;
// 		}
		break;
	case 182:rate += 60; func(); break; // 夺魄令
		// 各种回门派
	case 3:  //大唐   
	case 25: //方寸山
	case 44: //化生寺
	case 58: //女儿村
	case 70: //天宫
	case 83: //龙宫
	case 93: //五庄观
	case 110: //普陀
	case 124: //地府
	case 138: //魔王
	case 149: //狮驼
	case 163: //盘丝岭
	case 180: //凌波城
	case 192: //无底洞
	case 202: //叶隐
		rate = 30 + (Skilllv >> 1);
		break;
	default:
		return 100;
	}
	return rate;
	return (rand() % 100) < rate;
}




bool cSkillManager::CheckFanZheng(int UserID, int TargetID, int& dam)
{
	cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	cPropertyData* pUserData;
	cPropertyData* pTargetData;
	pUser->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);
	if (rand() % 100 < pTargetData->StabRate.d1 - pUserData->StabRate.d2)
	{
		//计算反震伤害
		int dam3 = (dam *(pTargetData->StabPercent.d1 - pUserData->StabPercent.d2)) / 100;
		if (dam3 < 1)dam3 = 1;
		AddHp(UserID, -dam3);
		SetDamage(dam3, UserID);
		m_pFightState->SetSuffer_state30(UserID, pTarget->GetDirection(), UserID);
		return true;
	}
	return false;
}




bool cSkillManager::CheckGodLivePercent(int& dam, int target, int userid)
{
	cPropertyData* pTargetData;
	cPropertyData* pUserData;
	cObj* pObj = m_pFightState->m_pFightWorkList[target]->m_pObj;
	pObj->GetPropertyData(pTargetData);
	pObj = m_pFightState->m_pFightWorkList[userid]->m_pObj;
	pObj->GetPropertyData(pUserData);
	if (pTargetData->m_HP - dam < 1)
	{
		int godlive = pTargetData->RelifeRate.d1 - pUserData->RelifeRate.d2;
		if (rand() % 100 < godlive)
		{
			dam += pTargetData->HPMax.GetData() * pTargetData->RelifePercent.d1;
			if (dam > pTargetData->HPMax.GetData())
			{
				dam = pTargetData->HPMax.GetData();
			}
			dam = -dam;
			////////////////////////////////////////////////////////////////////////// 呵呵哒 神佑几率也下降
			pTargetData->RelifeRate.d1 -= pTargetData->RelifeRate.d1 / 50;// 5;
			return true;
		}
	}
	return false;
}




void cSkillManager::SuckBlood(int dam, int UserID, cPropertyData* target)
{
//	if (target->m_Race == 6 || target->m_Race == 5 || target->m_Race >= 1000)return;//鬼和机械不会被吸血
	if (target->Ghost.d1 > 0)
	{
		return;
	}
	cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	cPropertyData* pUserData;
	pUser->GetPropertyData(pUserData);
	
	if (rand() % 100 < (pUserData->SuckBloodRate.d1 - target->SuckBloodRate.d2))
	{
		int suckrate = pUserData->SuckBloodPercent.d1 - target->SuckBloodPercent.d2;
		int suckblooddam = (dam*suckrate) / 100;
		if (!suckblooddam)return;
		suckblooddam = min(suckblooddam, pUserData->m_HP2 - pUserData->m_HP);
		SetDamage(-suckblooddam, UserID);
		AddHp(UserID, suckblooddam);
	}
}





int cSkillManager::CorrectWuXing(cPropertyData* pUserData, cPropertyData* pTargetData, eMagicWuXing wuxing)
{
	//五行伤害修正
	int offwx = 0;
	switch (wuxing)
	{
	case cSkillManager::eMWX无:
		break;
	case cSkillManager::eMWX雷:
		offwx = pUserData->MagicThunder.d1 - pTargetData->MagicThunder.d2;
		break;
	case cSkillManager::eMWX火:
		offwx = pUserData->MagicFire.d1 - pTargetData->MagicFire.d2;
		break;
	case cSkillManager::eMWX水:
		offwx = pUserData->MagicWater.d1 - pTargetData->MagicWater.d2;
		break;
	case cSkillManager::eMWX土:
		offwx = pUserData->MagicSoil.d1 - pTargetData->MagicSoil.d2;
		break;
	case cSkillManager::eMWX雷水:
		offwx = (pUserData->MagicThunder.d1 - pTargetData->MagicThunder.d2/* / 2*/);
		offwx += (pUserData->MagicWater.d1 - pTargetData->MagicWater.d2/* / 2*/);
		break;
	case cSkillManager::eMWX光:
		offwx = pUserData->MagicThunder.d1 - pTargetData->MagicThunder.d2/* / 3*/;
		offwx += pUserData->MagicWater.d1 - pTargetData->MagicWater.d2/* / 3*/;
		offwx += pUserData->MagicFire.d1 - pTargetData->MagicFire.d2/* / 3*/;
		offwx += pUserData->MagicSoil.d1 - pTargetData->MagicSoil.d2/* / 3*/;
		break;
	default:
		break;
	}
	return offwx;
}




