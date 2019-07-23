#include "_global.h"
static const int c_bufRemainingTimesOnce = -0xFF;

void cSkillManager::EffectSkill(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (TargetID == -1)return;
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	cPropertyData* pTargetData;
	cPropertyData* pUserData;
	sBuff buf;
	buf.remainingTimes = c_bufRemainingTimesOnce;

	pTarget->GetPropertyData(pTargetData);
	pUser->GetPropertyData(pUserData);
	int userlv = pUserData->m_Lv;
	int targetlv = pTargetData->m_Lv;
	int dam = 0;
	auto getRemianTime = [&]()
	{
		int t = Skilllv/* + pUserData->m_XiuLian.GetMag()*/ + 15 - targetlv;
		t = t / 5;
		t = min(t, 7);
		return t;
	};
	auto getRemianTimeSelf = [&]()
	{
		int t = Skilllv/* + pUserData->m_XiuLian.GetMag()*/ + 25 - targetlv;
		t = t / 5;
		t = min(t, 9);
		return t;
	};

	int targetNum = g_pMainState->m_FightWorkList[UserID].m_MaxTargetNum;
//	int targetNow = pUserList->m_NowTarget;// g_pMainState->m_FightWorkList[UserID].m_NowTarget;
	int targetMax = 1;
	if (sSkillID < 1000 || sSkillID >= 2000)
	{
		targetMax = g_pMainState->m_SkillManager.GetSkill(sSkillID)->m_TargetNum;
	}
	Skilllv += pUserData->m_XiuLian.GetMag();
	int damPT = (Skilllv * 4 + 80) * 13 / 10 * (23 - targetNum) / 20;
	if (pUserList->m_NowTargetIdx == 0)
	{
		damPT += Skilllv / 2;
	}

	int dam2 = 0;
	switch (sSkillID)
	{
	case 0://横扫千军
	{
		int damageup;
		switch (pUserList->m_NowTargetIdx)
		{
		case 0:
			damageup = -15;
			break;
		case 1:// 攻击者攻击-目标防御 120%的伤害
			damageup = 0;
			break;
		case 2:// 攻击者攻击-目标防御  并有10%的波动  150%的伤害
			damageup = 15;
			break;
		default:
			damageup = 30;
			break;
		}
		CountphysicalDamage(dam, UserID, TargetID, damageup);
	}
		break;
	case 1: // 后发
		SetDateBuffUp(TargetID, UserID, sSkillID, buf, Skilllv);
		buf.remainingTimes = c_bufRemainingTimesOnce;
		break;
	case 1010: // 后发
	{
		pUserData->DmgAdd.d1 += Skilllv * 3 / 2;
		CountphysicalDamage(dam, UserID, TargetID, 155);
		pUserData->DmgAdd.d1 -= Skilllv * 3 / 2;
		pUser->ReMoveStateID(1);
	}
		break;
	case 7: // 破斧
	{
		CountphysicalDamage(dam, UserID, TargetID, -0xFFFF);
	}
		break;
	case 1017:// 破斧
		CountphysicalDamage(dam, UserID, TargetID, 45);
		break;
	case 8://安神诀
		buf.remainingTimes = getRemianTime();
		break;
	case 4://杀气诀
		buf.remainingTimes = getRemianTime();
		break;
	case 11://五雷咒
	case 28://落雷符
	{
		pUserData->Ghost.d2 += 50;
		int dadd = pUserData->Def.GetData() >> 4;
		pUserData->Mana.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 20/*20 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 5,eMWX雷*/);
		pUserData->Ghost.d2 -= 50;
		pUserData->Mana.AddDataOriginal(-dadd);
	}
		break;
	case 13: // 兵解符
	{
		m_pFightState->m_pFightWorkList[UserID]->isExist = false;
		if (UserID == g_pMainState->m_HeroID)
			m_pFightState->m_bEscape = true;
	}
		break;
	case 6: //反间计
		buf.remainingTimes = getRemianTime() / 2 + 1;
		break;
	case 14://催眠符
	case 15://失心符
	case 16://落魄
	case 17://失忆
	case 18://追魂
	case 19://离魂
	case 20://失魂
	case 21://定身
	case 26:
	case 27:
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
// 		buf.remainingTimes = 2;
// 		buf.remainingTimes += (Skilllv - targetlv) / 10;
		buf.remainingTimes = getRemianTime();
		break;
	case 22://归元咒
		dam = Skilllv * 5 / 2 + 128;
		CorrectCureHP(dam, UserID, UserID);//治疗修正
//		SetDamage(-dam, TargetID);
		break;
	case 23://凝神术
//		SetDamage(20, TargetID);
		CorrectCureMP(dam = Skilllv * 2, UserID, UserID);//治疗修正
//		AddMp(TargetID, dam = Skilllv * 2);
		break;
// 	case 26://分身术
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
// 	case 27://碎甲符
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
	case 31://唧唧歪歪

	{
		int dadd = pUserData->Def.GetData() >> 4;
		pUserData->Mana.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 20/*15 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4*/);
		pUserData->Mana.AddDataOriginal(-dadd);
		if (pUserList->m_NowTargetIdx == 0 && pUserData->m_HP > 5)
		{
			dadd = -5;
			AddHp(UserID, -5);
			SetDamage(5, UserID);
		}
	}
		break;
 	case 33:  //金刚护法
// 
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
// 		break;
	case 34:  //韦陀护法  
	case 35:  //金刚护体
	case 36:  //一苇渡江

	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTime();
		break;
	}
	case 37:     //我佛慈悲
		if (Resurgence(TargetID))
		{
			dam2 = dam = Skilllv * 12 + 256;
			CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
		}
//		AddHpHurt(TargetID, (Skilllv * 12 + 256));
//		dam2 = dam = Skilllv * 12 + 256;
//		CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
		break;
	case 38:     //推拿
		dam = Skilllv * 12;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正

		break;
// 	case 39:    //活血
// 		dam = Skilllv * 12;
// 		CorrectCureHP(dam, UserID, TargetID);//治疗修正
// 
// 		break;
	case 40:    //推气过宫
		dam = Skilllv * 8;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 41:    //妙手回春
		AddHpHurt(TargetID, (Skilllv * 8));
		break;
	case 42:    //救死扶伤
		dam = Skilllv * 7 + 64;
		dam += dam * (targetMax - targetNum) / (targetMax * 5 + 1);
//		AddHpHurt(TargetID, dam);
		dam2 = dam;
		CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
		break;
	case 39:
	case 43://解毒
		pTarget->ReMoveState(eBuffType毒);
		dam2 = dam = Skilllv * 10 + 192;
//		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
		break;
	case 45://舍身
// 		AddHpHurt(TargetID, 100, (1 << 14));
		pUserData->Def.AddDataAddPercent(-5);
		pUserData->Mana.AddDataAddPercent(-3);
// 		dam = -AddHp(TargetID, 100, 0xFFFFFF);
		CorrectCureHP(dam = 99999, UserID, TargetID);
// 		SetDamage(dam, TargetID);
		break;
	case 46:    //佛法无边
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		buf.remainingTimes = getRemianTime();
// 	}
// 		break;
	case 49:    //楚楚可怜
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
		buf.remainingTimes = getRemianTime();
		break;
	case 50: return;
	case 1050:
		CountphysicalDamage(dam, UserID, TargetID/*, 30*/);
		// 15 失心符
		if ((rand() % 100) < CheckMagicHit(Skilllv, 15, UserID, TargetID))
		{
			buf.remainingTimes = 2 + rand() % 4;
			SetDateBuffUp(UserID, TargetID, 50, buf, Skilllv);
			buf.remainingTimes = c_bufRemainingTimesOnce;
		}
		break;

	case 54:    //似玉生香
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
// 		break;
	case 59:    //一笑倾城
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
// 		break;
	case 62:    //天神护法
// 	{
// 		buf.remainingTimes = 5;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 66:	//宁心
		pUser->ReMoveState(eBuffType负面);
		break;
	case 67:    //镇妖 
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
// 		break;
	case 68:    //错乱
	case 69:    //百万神兵
// 	{
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 	}
		buf.remainingTimes = getRemianTime();
		break;
	case 71://天雷斩
	{
		int dadd = pUserData->Def.GetData() >> 4;
		pUserData->Atk.AddDataOriginal(dadd);
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->Atk.AddDataOriginal(-dadd);
		if (sSkillID == 71)
		{
			if (pUserList->m_NowTargetIdx == 0)
			{
				pUserData->Def.AddDataAddPercent(-1);
			}
			pTargetData->Mana.AddDataAddPercent(-1);
		}
	}
		break;
	case 72://五雷轰顶
	{
// 		int rate = (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag())/**2*/;
// 		int offset = Skilllv - pTargetData->m_Lv;
// 		rate = 70 + rate + offset;
// 		if (rand() % 100 < rate)

		// 失心符
		if ((rand() % 100) < CheckMagicHit(Skilllv, 15, UserID, TargetID))
		{
			dam = pTargetData->m_HP / 4;
		}
		else
		{
			dam = pTargetData->m_HP / 20;
		}
		if (dam > (pUserData->m_Lv * 50))
		{
			dam = pUserData->m_Lv * 50;
		}
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
	}
		break;
	case 74://雷霆万钧
	{
		int dadd = pUserData->Def.GetData() >> 4;
		pUserData->Mana.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 25/*20 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 8,eMWX雷*/);
		pUserData->Mana.AddDataOriginal(-dadd);
	}
		break;
	case 77: //解封
	{
		m_pFightState->ReMoveSealState(TargetID);
	}
		break;
	case 78: // 清心
	{
		pTarget->ReMoveState(eBuffType毒);
		break;
	}
	case 79://龙腾
		CountMagicDamage(dam, UserID, TargetID, 25/*40 + Skilllv / 5, eMWX水*/);
		break;
	case 80://龙卷雨击
		CountMagicDamage(dam, UserID, TargetID, 20/*25 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4,eMWX雷水*/);
		break;
	case 81://逆鳞
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 87://神龙摆尾
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 84: //龙呤
		dam = Skilllv + 10;
		CountMagic2Damage固定(dam, UserID, TargetID/*, eMWX水*/);
		AddMp(TargetID, -dam);
		break;
	case 88://二龙
		CountMagicDamage(dam, UserID, TargetID, 30/*30 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4,eMWX水*/);
		break;
	case 89://日月乾坤
	{
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTime();
	}
		break;
	case 90: //炼气化神
	{
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		dam = Skilllv;
		CorrectCureMP(dam, UserID, TargetID);
		buf.damage = dam;
//		SetDamage(30, UserID);
	}
		break;
	case 91://生命之泉
	{
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		dam = Skilllv * 5 / 2 + 64;
		buf.damage = dam;
		CorrectCureHP(dam, UserID, TargetID); //治疗修正
		
	}
		break;
	case 94:   //三花聚顶
		dam = (Skilllv * 5 + 128);
		CorrectCureMP(dam, UserID, TargetID);
//		SetDamage(30, UserID);
		break;
	case 96: // 驱尸
	{
		pTarget->ReMoveState(eBuffType毒);
	}
		break;
	case 97: //烟雨
	case 98: //缥缈式
	{
		int dadd = pUserData->Def.GetData() >> 4;
		pUserData->Atk.AddDataOriginal(dadd);
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->Atk.AddDataOriginal(-dadd);
	}
		break;
	case 102://普渡众生
	{
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();

		int d = Skilllv * 4 + 192;
		dam += d;
		dam2 += d;
		buf.damage = d;
		buf.damage2 = d;
//		AddHpHurt(TargetID, dam + Skilllv);
		CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
	}
		break;
	case 103://紧箍咒
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
		if ((rand() % 100) < CheckMagicHit(Skilllv, 15, UserID, TargetID))
		{
			buf.damage = (Skilllv * 3 + pTargetData->HPMax.GetData() / 50);
			int lvMax = max(pTargetData->m_Lv, pUserData->m_Lv);
			if (buf.damage > lvMax * 8)
			{
				buf.damage = lvMax * 8;
			}
			buf.remainingTimes = getRemianTime();
		}
		break;
	case 104://杨柳甘露
	{
//		Resurgence(TargetID);
		{
			cObj* pObj = g_pMainState->m_FightWorkList[TargetID].m_pObj;
			pObj->SetStatic(false);
			pObj->Set(POS_FIGHT_STAND);
			g_pMainState->m_FightWorkList[TargetID].SetDie(false);
			cPropertyData* pPet;
			pObj->GetPropertyData(pPet);
			if (pPet->m_HP < 1)
			{
				pPet->m_HP = 1;
			}
			AddHpHurt(1, TargetID);
			AddHp(1, TargetID);
			pObj->MoveShadow();
		}

		dam2 = dam = Skilllv * Skilllv / 144 + Skilllv * 6;
		buf.remainingTimes = getRemianTimeSelf();

		int d = Skilllv * 4 + 192;
		dam += d;
		dam2 += d;
		buf.damage = d;
		buf.damage2 = d;
		CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
	}
		break;
	case	105:// 日光华 等级×4 + 100
		dam = damPT + Skilllv / 2;
		CountMagic2Damage固定(dam, UserID, TargetID, eMWX光);
		break;
	case	106:// 靛沧海
		dam = damPT;
		CountMagic2Damage固定(dam, UserID, TargetID, eMWX水);
// 		if ((rand() % 100) < 10)
// 		{
// 			m_pFightState->m_pFightWorkList[TargetID]->m_WorkType = -1;
// 		}
		break;
	case	107:// 巨岩破
		dam = damPT;
		CountMagic2Damage固定(dam, UserID, TargetID, eMWX土);
		if ((rand() % 100) < 10)
		{
			AddCp(TargetID, -dam / 50);
		}
		break;
	case	108:// 苍茫树
		dam = damPT;
		CountMagic2Damage固定(dam, UserID, TargetID);
		if ((rand() % 100) < 10)
		{
			AddMp(UserID, -dam / 10);
		}
		break;
	case	109:// 地裂火
		dam = damPT;
		CountMagic2Damage固定(dam, UserID, TargetID, eMWX火);
		if ((rand() % 100) < 10)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 112://灵动
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 113://五行颠倒
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 115://自在心法
		if (pTarget->m_StateList.size())
		{
			int hp = 1;
			int hp2 = 1;
			int t = 1;
			for (list<sBuff>::iterator Iterator = pTarget->m_StateList.begin(); Iterator != pTarget->m_StateList.end();)
			{
// 				if (Iterator->ID == 102 || Iterator->ID == 91)
// 				{
// 					list<sBuff>::iterator it2 = Iterator;
// 					Iterator++;
// 					if (Iterator->ID == 91)
// 					{
// 						int hpadd = it2->damage2*it2->times;
// 						AddHpHurt(TargetID, hpadd);
// 					}
// 					dam = -it2->damage*it2->times;
// 					AddHp(TargetID, -dam);
// 					g_pMainState->m_SkillManager.SetDateBuffDown(it2);// it2->targetID, it2->ID);
// 					it2->data.Free();
// 					pTarget->m_StateList.erase(it2);
// 					break;
// 				}
// 				else 
				if (Iterator->ID == 102 || Iterator->ID == 104)
				{
					if (t < Iterator->remainingTimes)
					{
						t = Iterator->remainingTimes;
					}
					if (hp < Iterator->damage)
					{
						hp = Iterator->damage;
					}
					if (hp2 < Iterator->damage2)
					{
						hp2 = Iterator->damage2;
					}
					g_pMainState->m_SkillManager.SetDateBuffDown(Iterator);// it2->targetID, it2->ID);
					Iterator->data.Free();
					pTarget->m_StateList.erase(Iterator++);
				}
				else
				{
					++Iterator;
				}
			}
			hp *= t;
			hp2 *= t;
// 			if (hp > 0)
// 			{
// 				AddHpHurt(TargetID, hp);
// 				AddHp(TargetID, hp);
// 				SetDamage(-hp, TargetID);
// 			}
			CorrectCureHP(hp, hp2, UserID, TargetID);
		}
		break;
	case 116://阎罗令
		dam = (Skilllv * 3 / 2 + 30) * 13 / 10 * 2;
		CountMagic2Damage固定(dam, UserID, TargetID);
		AddHpHurt(TargetID, -(Skilllv * 3 / 2 + 30));
		break;
	case 117://判官令
		dam = (Skilllv * 3 + 75) * 13 / 10 * 3 / 2;
		CountMagic2Damage固定(dam, UserID, TargetID);
		AddMp(TargetID, -(Skilllv * 3 + 75));
		break;
	case 119://寡欲令
		m_pFightState->ReMoveSealState(TargetID);
	case 120://鬼眼
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 122://尸腐毒
	{
		if (pTarget->CheckHaveState(sSkillID))return;
//		if (pTargetData->m_Race == 5 || pTargetData->m_Race == 6 || pTargetData->m_Race >= 1000)return;//机械和鬼不会中毒
		if (pTargetData->Ghost.d1 > 0) return;
// 		int Poision = pUserData->poisonRate.d1 - pUserData->poisonRate .d2 + 80; //中毒率
// 		if (rand() % 100 < Poision)
		{
			sBuff buf;
			buf.damage = pUserData->DmgPercentOfPoison.d1 - pTargetData->DmgPercentOfPoison.d2;//中毒伤害修正
			buf.remainingTimes = Skilllv + pUserData->m_XiuLian.GetMag() - targetlv;
			buf.remainingTimes = buf.remainingTimes / 5;
			buf.remainingTimes = min(buf.remainingTimes, 4);

			SetDateBuffUp(UserID, TargetID, sSkillID, buf);
			buf.remainingTimes = c_bufRemainingTimesOnce;
			dam = pTargetData->m_HP / 10 + Skilllv;
			if (dam > userlv * 15)
			{
				dam = userlv * 15;
			}
			AddHp(TargetID, -dam);
			SetDamage(dam, TargetID);

			cPropertyData* pPet;
			int randstart, randend;
			if (UserID < 10)randstart = 0; else randstart = 10;
			randend = randstart + 10;
			for (int i = randstart; i < randend; i++)
			{
				sFightWork& list = g_pMainState->m_FightWorkList[i];
				if (!list.isExist)continue;
				list.m_pObj->GetPropertyData(pPet);

				if (pPet->m_HP < 1)continue;
				int d = dam + pPet->DmgAddOfCure.d2 + pUserData->DmgAddOfCure.d1;
				if (d > Skilllv * 9 / 2 + 192)
				{
					d = Skilllv * 9 / 2 + 192;
				}
				AddHp(i, d);
				SetDamage(-d, i);
			}
		}
	}
		break;
	case 123:   //修罗隐身
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		if (pUserData->Hide.d1 >= 2)
		{
			buf.remainingTimes = pUserData->Hide.d1;
			pUserData->Hide.d1 = 0;
		}
		else
		{
			buf.remainingTimes = getRemianTime();
		}
		break;
	case 125:
		if (Resurgence(TargetID))
		{
			//		AddHpHurt(TargetID, Skilllv * 10);
			dam2 = dam = Skilllv * 8 + 128;
			//		AddHp(TargetID, dam);
			CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
			buf.remainingTimes = 3;
			buf.remainingTimes += (Skilllv - targetlv) / 5;
			buf.remainingTimes = getRemianTime();
		}

		break;
	case 126: // 黄泉之息
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTime();

		dam = pUserData->Mana.GetData() - pTargetData->Mana.GetData();
		dam += pUserData->Atk.GetData() - pTargetData->Def.GetData();
		if (dam < 0)
		{
			dam = 0;
		}
		dam += Skilllv * 3 + 30;
		CountMagic2Damage固定(dam, UserID, TargetID);
		break;
	case 127:// 魂飞魄散
		pTarget->ReMoveState(eBuffType增益);
		break;
	case 129: // 锢魂术
		buf.remainingTimes = 5;
		buf.remainingTimes += (Skilllv - targetlv) / 25;
		buf.remainingTimes = getRemianTime();
		
		break;
	case 131://飞砂走石
		CountMagicDamage(dam, UserID, TargetID, 25/*25 + Skilllv / 4 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4, eMWX土*/);
		break;
	case 132:// 三昧真火
		CountMagicDamage(dam, UserID, TargetID, 30/*70 + Skilllv / 4, eMWX火*/);
		break;
	case 133:// 牛劲
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 135:// 牛妖
		
		break;
	case 136:// 法术牛妖
		break;
	case 137: // 魔王回首
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 141://象形
		CountphysicalDamage(dam, UserID, TargetID, 60);
		pUser->ReMoveStateID(145);//取消变身
		buf.remainingTimes = 1;
		SetDateBuffUp(UserID, TargetID, sSkillID, buf);
		buf.remainingTimes = c_bufRemainingTimesOnce;
		break;
	case 142://鹰击 
		CountphysicalDamage(dam, UserID, TargetID, 5);
// 		if (pUserList->m_NowTarget == 0/*pUserList->m_MaxTargetNum - 1*/)
// 		{
// 			buf.times = 1;
// 			SetDateBuffUp(UserID, UserID, sSkillID, buf);
// 		}
// 		buf.times = -999;
		break;
	case 143:// 狮搏
		CountphysicalDamage(dam, UserID, TargetID, 125);
		break;
	case 144:// 威慑
		if (pTarget->m_IndexType != INDEXTYEP_CHARACTER)
		{
			buf.remainingTimes = 5;
			buf.remainingTimes += (Skilllv - targetlv) / 25;
			buf.remainingTimes = getRemianTime();
		}

		break;
	case 145://变身
// 		buf.remainingTimes = 5;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
	case 147://定心
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 148:// 连环击
		CountphysicalDamage(dam, UserID, TargetID, 10 - pUserData->m_FightData.AttackNum * 5);
// 		if (pUserList->m_NowTarget == 0)
// 		{
//  			buf.times = 1;
//  			SetDateBuffUp(UserID, UserID, sSkillID, buf);
//  			buf.times = -999;
// 			pUser->ReMoveStateID(145);//取消变身
// 			buf.times = 1;
// 			SetDateBuffUp(UserID, TargetID, sSkillID, buf);
// 			buf.times = -999;
// 		}
		break;
	case 150://极度疯狂
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
	case 152:
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTime();
		break;
	case 154://勾魂
	{
		dam = pTargetData->HPMax.GetData() / 20;
		dam += Skilllv * 3;
		dam = dam * (100 - pTargetData->DmgPercentOfFix.d2) / 100;
		if (dam > userlv * 12)
		{
			dam = userlv * 12;
		}
// 		AddHp(TargetID, -dam);
// 		SetDamage(dam, TargetID);
		CountMagic2Damage固定(dam, UserID, TargetID);
		CorrectCureHP(dam, UserID, UserID);//治疗修正
	}
		break;
	case 155://摄魄
// 		dam = -AddMp(TargetID, -5, userlv * 100);
// 		dam += -AddMp(TargetID, -Skilllv * 2);
		dam = pTargetData->MPMax.GetData() / 20;
		dam += Skilllv * 2;
// 		if (dam > userlv * 5)
// 		{
// 			dam = userlv * 5;
// 		}

		AddMp(TargetID, -dam);
//		dam /= 2;
		CorrectCureMP(dam, UserID, UserID);//治疗修正
		dam = 0;
		break;
	case 156://魔音摄魂
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
	case 159://含情脉脉
// 		buf.remainingTimes = 3;
// 		buf.remainingTimes += (Skilllv - targetlv) / 5;
// 		break;
	case 160:// 盘丝阵
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - targetlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 161: //复苏
		m_pFightState->ReMoveSealState(UserID);
		m_pFightState->ReMoveDeBuffState(UserID);
		m_pFightState->ReMovePoisionState(UserID);
		break;
	case 162:  //天罗地网
		dam = Skilllv * 2 + (pUserData->Atk.GetData() / 5);
		dam = dam * 5 / 3;
		CountMagic2Damage固定(dam, UserID, TargetID);
		// 59 一笑倾城
		if ((rand() % 100) < CheckMagicHit(Skilllv, 59, UserID, TargetID))
		{
			buf.remainingTimes = rand() % 3 + 1;
			buf.remainingTimes = getRemianTime();
		}
		break;
	case 164://姐妹同心
		dam = AddMp(TargetID, -10, userlv * 100);
		dam += AddMp(TargetID, Skilllv * 5);
		dam = 0;
		break;
	case 166://幻镜术
		buf.remainingTimes = 3;
		buf.remainingTimes += (Skilllv - userlv) / 5;
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 171:
	case 172:
		break;
	case 167:
	case 168:
	case 169:
	case 170:
	case 1171:
	case 1172:
	{
		int cri = 0;
		int add = 0;
		if (sSkillID <= 169)
		{
			cri += Skilllv / 10;
		}
		else if (sSkillID > 170)
		{
			add += Skilllv;
		}
		pUserData->CriRate.d1 += cri;
		pUserData->DmgAdd.d1 += add;
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->CriRate.d1 -= cri;
		pUserData->DmgAdd.d1 -= add;
// 		else if (sSkillID == 168)
// 		{
// 			--pUserData->m_FightData.zhanyi;
// 		}
// 		else if (sSkillID == 169 || sSkillID == 171)
// 		{
// 			pUserData->m_FightData.zhanyi -= 2;
// 		}
// 		else if (sSkillID == 172)
// 		{
// 			pUserData->m_FightData.zhanyi -= 3;
// 		}
	}
		break;
	case 175: // 不动如山
	case 176:
	case 177:
	case 181: // 画骨

	case 187: // 明光
	case 188: // 舍利
	case 201: // 炎护
	case 204: // 咪润
		buf.remainingTimes = getRemianTimeSelf();
		break;
	case 182:
	case 185: // 崔心术
		buf.remainingTimes = getRemianTime();
		break;
	case 186: // 夺命咒 （技能等级*3+80）*[(11-作用人数)/10]+武器伤害/4 
		dam = damPT;
		CountMagic2Damage固定(dam, UserID, TargetID);
		break;
	case 189: // 地涌金莲
		dam = Skilllv * 11 + 128;
		if (TargetID == pUserList->targetlist[0])
		{
			dam += dam / 2 + pUserData->HPMax.GetData() / 33;
		}
		dam2 = 128 + dam / 10;
		CorrectCureHP(dam, dam2, UserID, TargetID);
		break;
	case 193: // 由己渡人
		if (Resurgence(TargetID))
		{
			dam2 = dam = Skilllv * 7 + 256;
			CorrectCureHP(dam, dam2, UserID, TargetID);//治疗修正
		}

		break;
	case 194: // 落叶萧萧
		CountMagicDamage(dam, UserID, TargetID, 25);
		break;
	case 195: // 荆棘舞
		CountMagicDamage(dam, UserID, TargetID, 40);
		break;
	case 196: // 尘土刃
		CountMagicDamage(dam, UserID, TargetID, 30);
		if ((rand() % 100) < 20)
		{
			AddHpHurt(TargetID, -dam / 20);
		}
		break;
	case 197: // 冰川怒
		CountMagicDamage(dam, UserID, TargetID, 30);
		if ((rand() % 100) < 20)
		{
			AddCp(TargetID, -dam / 50);
		}
		break;
	case 198: // 雾杀 等级*等级/100+（等级+45）+灵力差
		CountMagicDamage(dam, UserID, TargetID, 10086, eMWX无, dam2);
		buf.damage = dam2;
		buf.remainingTimes = 3;
		break;
	case 199: // 血雨
		dam2 = g_pMainState->m_SkillManager.GetSkill(sSkillID)->m_Cost;
		dam2 = pUserData->HPMax.GetData() * dam2 / 100;
		CountMagicDamage(dam, UserID, TargetID, 10087, eMWX无, dam2);
		buf.remainingTimes = 1;
		SetDateBuffUp(UserID, UserID, sSkillID, buf, Skilllv);
		buf.remainingTimes = c_bufRemainingTimesOnce;
		break;
	case 200: // 星月之惠
	{
		int randstart, randend;
		if (UserID < 10)randstart = 0; else randstart = 10;
		randend = randstart + 5;
		int die = 0;
		for (int i = randstart; i < randend; i++)
		{
			sFightWork& list = g_pMainState->m_FightWorkList[i];
			if (!list.isExist)continue;
			if (list.CheckDie())
			{
				++die;
			}
		}
		dam = Skilllv * 4 + 128;
		dam += dam * die / 2;
		CorrectCureHP(dam, UserID, TargetID);
	}
		break;
	case 1001://抓捕

	{
		if (!pTargetData->m_Controler.CheckGrab())
		{
//			g_pMainState->m_Channel.AddNewString("该对象无法抓捕");
			pTarget->say("想抓我?没门!");
			return;
		}
		cCharacter* pc1 = (cCharacter*)pUser->m_pIndex;
		if (pc1->m_PcData.m_NumofBB > 7)
		{
			g_pMainState->m_Tags.Add("召唤兽已满");
			break;
		}
		// 草儿特供???
		cPet* pPet = (cPet*)pTarget->m_pIndex;
		if (pc1->m_PcData.m_Lv < pPet->GetData()->m_LvTake)//等级上限
		{
			g_pMainState->m_Tags.Add("没有达到该召唤兽的携带等级");
			break;
		}
		if ((rand() % 100) > 50)
		{

			m_pFightState->BackFromFight(TargetID);
			cPet* pPet = (cPet*)pTarget->m_pIndex;
			pc1->m_PcData.AddPet(pPet);
			pTarget->m_pIndex = 0;
			pTarget->m_IndexType = 0;
			m_pFightState->m_pFightWorkList[TargetID]->m_work.clear();
			
		}
	}
		break;


	case 1007://乾坤袋

	{
		cObj* target = g_pMainState->m_FightWorkList[TargetID].m_pObj;
// 		string targetname = target->m_TrueName.GetString();
// 		if (0 == targetname.compare(g_pMainState->m_taskSM.m_Npc.m_name))
		if (target == g_pMainState->m_taskSM.m_pNowObj)
		{
			cPropertyData* pData;
			target->GetPropertyData(pData);
//			if (pData->m_HP < (pData->HPMax.GetData()) / 2)
			{
				if (rand() % 100 > (pData->m_HP * 100 / pData->HPMax.GetData()))
				{
					dam = pData->m_HP;
					AddHp(TargetID, -dam);
					SetDamage(dam, TargetID);
					g_pMainState->m_taskSM.m_bXiangFuSuccess = true;
				}
			}

		}
	}
		break;
	case 2084:  //雷击
		CountMagicDamage(dam, UserID, TargetID, 30, eMWX雷);
		break;
	case 2085://奔雷咒
		CountMagicDamage(dam, UserID, TargetID, 20/*35 - pUserList->m_NowTarget * 5*/, eMWX雷);
		break;
	case 2086: //落岩
		CountMagicDamage(dam, UserID, TargetID, 30, eMWX土);
		if (rand() % 5 == 0)
		{
			AddCp(TargetID, -20);
		}
		break;
	case 2087: //泰山压顶
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX土);
// 		if (rand() % 10 == 0)
// 		{
// 			AddCp(TargetID, -20);
// 		}
		break;
	case 2088: //水攻
		CountMagicDamage(dam, UserID, TargetID, 30, eMWX水);
// 		if (rand() % 15 == 0)
// 		{
// 			m_pFightState->m_pFightWorkList[TargetID]->m_WorkType = -1;
// 		}
		break;
	case 2089: //水漫金山
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX水);
// 		if (rand() % 30 == 0)
// 		{
// 			m_pFightState->m_pFightWorkList[TargetID]->m_WorkType = -1;
// 		}
		break;
	case 2090: //烈火
		CountMagicDamage(dam, UserID, TargetID, 30, eMWX火);
		if (rand() % 10 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 2091: //地狱烈火
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX火);
// 		if (rand() % 20 == 0)
// 		{
// 			AddHpHurt(TargetID, -dam / 10);
// 		}
		break;
	case 2092://惊心一剑
		CountphysicalDamage(dam, UserID, TargetID/*, -10*/);
		AddMp(TargetID, -(dam / 4 + userlv / 3));
		break;
	case 2093://夜舞倾城
		buf.remainingTimes = 3;
		dam = pUserData->PointStr * 3 / 2 + pUserData->Speed.GetData() / 3;
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
		break;
	case 2094://死亡召唤
		CountphysicalDamage(dam, UserID, TargetID);
		if (rand() % 100 < 15)
		{
			buf.remainingTimes = 10;
		}
		break;
	case 2095://力劈华山 临时加
		SetDateBuffUp(UserID, UserID, sSkillID, buf, Skilllv);

		break;
	case 1095://力劈
		CountphysicalDamage(dam, UserID, TargetID, 10086);
		break;
		
	case 2097:// 法术防御
		buf.remainingTimes = 6;
		break;
	case 2098://善恶有报
		CountphysicalDamage(dam, UserID, TargetID, 10088);
		break;
	case 2099://壁垒击破
		CountphysicalDamage(dam, UserID, TargetID, 10087);
		break;
	case 2101://无畏布施
		buf.remainingTimes = 3;
		SetDateBuffUp(UserID, UserID, 1998, buf, Skilllv);
		break;
	case 2102://天降灵葫
		CountMagicDamage(dam, UserID, TargetID, 25);
		break;
	case 2105: //月光
		pUserData->DmgPercentOfMagic.d1 -= (pUserList->_moon - 2) * 20;
//		pUserData->m_MagicCriRate.d1 -= pUserData->m_FightProperty.AttackNum * 5;
		CountMagicDamage(dam, UserID, TargetID, 30);
		pUserData->DmgPercentOfMagic.d1 += (pUserList->_moon - 2) * 20;
//		pUserData->m_MagicCriRate.d1 += pUserData->m_FightProperty.AttackNum * 5;
		break;
	case 2110: //剑荡四方
		CountphysicalDamage(dam, UserID, TargetID, -35);
		break;
	case 2111: //吸星大法
		CountMagicDamage(dam, UserID, TargetID, 50);
		if (dam > 1)
		{
			AddMp(TargetID, dam / 5);
		}
		break;
	case 3000: //气疗
	{
		dam = CountHPPercent(pTargetData, 3, userlv);
		dam += 200;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
	}
		break;
	case 3001: //心疗

	{
		dam = CountHPPercent(pTargetData, 6, userlv);
		dam += 400;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
	}
		break;
	case 3002: //命疗

	{
		dam = CountHPPercent(pTargetData, 9, userlv);
		dam += 600;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
	}
		break;
	case 3003: //凝气

	{
		dam = CountMPPercent(pTargetData, 10, userlv);
		dam += 150;
		CorrectCureMP(dam, UserID, TargetID);//治疗修正
	}
		break;
	case 3004:  //凝神

	{
		dam = CountMPPercent(pTargetData, 15, userlv);
		dam += 240;
		CorrectCureMP(dam, UserID, TargetID);//治疗修正
	}
		break;
	case 3006: //命归
		dam = CountHPPercent(pTargetData, 50, userlv * 20 / 50);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 3005:  //气归
	case 3007: //四海升平
		dam = CountHPPercent(pTargetData, 30, userlv * 12 / 30);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 3008://回魂咒
		if (Resurgence(TargetID))
		{
			dam = 150;// CountHPPercent(pTargetData, 20, userlv);
			AddHpHurt(TargetID, dam);
			CorrectCureHP(dam, UserID, TargetID);//治疗修正
		}
		break;
	case 3009: //起死回生
		if (Resurgence(TargetID))
		{
			dam = CountHPPercent(pTargetData, 50, userlv * 20 / 50);
			CorrectCureHP(dam, UserID, TargetID);//治疗修正
			AddHpHurt(TargetID, dam);
		}
		break;
	case 3010://水清
	case 3012://玉清
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		break;
	case 3011://冰清
	case 3013://晶清
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		dam = CountHPPercent(pTargetData, 15, userlv * 12 / 15);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
// 		pTarget->ReMoveState(eBuffType封印);
// 		pTarget->ReMoveState(eBuffType毒);
// 		pTarget->ReMoveState(eBuffType负面);
		break;
	case 3016://笑里藏刀
		AddCp(TargetID, -70);
		break;
	case 3017://绝幻魔音
		AddCp(TargetID, -20);
		break;
	case 3018://野兽	
		if (!(pTargetData->m_FightData.m_AtkIntensify && 2))
			pTargetData->Atk.AddDataAddPercent(10);
		break;
	case 3019://魔兽之印
		if (!(pTargetData->m_FightData.m_AtkIntensify && 1))
			pTargetData->Atk.AddDataAddPercent(5);
		break;
	case 3020://光辉
		if (!(pTargetData->m_FightData.m_DefIntensify && 2))
			pTargetData->Def.AddDataAddPercent(10);
		break;
	case 3021://圣灵
		if (!(pTargetData->m_FightData.m_DefIntensify && 1))
			pTargetData->Def.AddDataAddPercent(5);
		break;
	case 3022://流云
		if (!(pTargetData->m_FightData.m_SpdIntensify && 2))
			pTargetData->Speed.AddDataAddPercent(10);
		break;
	case 3023://啸风
		if (!(pTargetData->m_FightData.m_SpdIntensify && 1))
			pTargetData->Speed.AddDataAddPercent(5);
		break;
	case 3024://太极护法
		buf.remainingTimes = 3;
		break;
	case 3025://罗汉金钟
		buf.remainingTimes = 3;
		break;
	case 3026://修罗咒
		buf.remainingTimes = 3;
		break;
	case 3027://天衣无缝
		buf.remainingTimes = 5;
		break;
	case 3028://放下屠刀
		if (!(pTargetData->m_FightData.m_AtkIntensify && 8))
		{
			pTargetData->m_FightData.m_AtkIntensify += 8;
			pTargetData->Atk.AddDataAddPercent(-10);
		}
		break;
	case 3029://牌山压制
		if (!(pTargetData->m_FightData.m_AtkIntensify && 4))
		{
			pTargetData->m_FightData.m_AtkIntensify += 4;
			pTargetData->Atk.AddDataAddPercent(-5);
		}
		break;
	case 3030://破甲术
		if (!(pTargetData->m_FightData.m_DefIntensify && 8))
		{
			pTargetData->m_FightData.m_DefIntensify += 8;
			pTargetData->Def.AddDataAddPercent(-10);
		}
		break;
	case 3031://碎甲术
		if (!(pTargetData->m_FightData.m_DefIntensify && 4))
		{
			pTargetData->m_FightData.m_DefIntensify += 4;
			pTargetData->Def.AddDataAddPercent(-5);
		}
		break;
	case 3032://凝滞术
		if (!(pTargetData->m_FightData.m_SpdIntensify && 8))
		{
			pTargetData->m_FightData.m_SpdIntensify += 8;
			pTargetData->Speed.AddDataAddPercent(-10);
		}
		break;
	case 3033://停陷术
		if (!(pTargetData->m_FightData.m_SpdIntensify && 4))
			pTargetData->Speed.AddDataAddPercent(-5);
		break;


	case 3034://破血
		pUserData->Pierce刺穿.d1 += 5;
		CountphysicalDamage(dam, UserID, TargetID, 45);
		pUserData->Pierce刺穿.d1 -= 5;
		break;

	case 3035://弱点
		pUserData->Pierce刺穿.d1 += 45;
		CountphysicalDamage(dam, UserID, TargetID, 5);
		pUserData->Pierce刺穿.d1 -= 45;
		break;

// 	case 3038://星杯圣域
// 		pTargetData->m_FightData.m_WallNum = 2;
// 		break;
// 	case 3039://命疗术EX
// 
// 	{
// 		dam = CountHPPercent(pTargetData, 50, userlv);
// 		dam += 1000;
// 		CorrectCureHP(dam, UserID, TargetID);//治疗修正
// 	}
// 		break;

	case 3040://破碎
		CountphysicalDamage(dam, UserID, TargetID, 0);
		AddMp(TargetID, -dam);
		break;	

// 	case 3043://弱点EX
// 		pUserData->Pierce刺穿.d1 += 80;
// 		CountphysicalDamage(dam, UserID, TargetID, 0);
// 		pUserData->Pierce刺穿.d1 -= 80;
// 		break;
// 
// 	case 3042://破血2
// 	case 3044://破血EX
// 		pUserData->Pierce刺穿.d1 += 5;
// 		CountphysicalDamage(dam, UserID, TargetID, 0);
// 		pUserData->Pierce刺穿.d1 -= 5;
// 		break;
// 
// 	case 3046://大地之墙
// 		pTargetData->m_FightData.m_WallNum = 1;
// 		break;
	case 3047://心如明镜
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		buf.remainingTimes = 4;
		break;
	case 3048://慈航普度
		if (TargetID == UserID)
		{
			dam2 = pUserData->HPMax.GetData() / 10 - pUserData->m_HP2;
			if (dam2 < 0)
			{
				dam = 0;
				CorrectCureHP(dam, dam2, UserID, TargetID);
			}
			pUserData->m_MP = 0;
			if (UserID == g_pMainState->m_HeroID)
			{
				g_pMainState->m_PCHead.UpdatePcMp();
			}
		}
		else if (Resurgence(TargetID))
		{
			dam = CountHPPercent(pTargetData, 100, userlv << 5);
			AddHpHurt(TargetID, 100, 0xFFFF);
			CorrectCureHP(dam, UserID, TargetID);//治疗修正
			pTarget->ReMoveState(eBuffType封印);
			pTarget->ReMoveState(eBuffType毒);
			pTarget->ReMoveState(eBuffType负面);
		}

// 		Resurgence(TargetID);
// 		dam = CountHPPercent(pTargetData, 50, userlv);
// 		CorrectCureHP(dam, UserID, TargetID);//治疗修正
// 		AddHpHurt(TargetID, dam);

		break;
// 	case 3049://迅疾如风
// 		buf.remainingTimes = 5;
// 		break;

	default:
		if (sSkillID > 1000)
		{
			ERRBOX2(sSkillID);
		}
		return;
	}
	if (buf.remainingTimes != c_bufRemainingTimesOnce)
	{
		if (buf.remainingTimes < 1)buf.remainingTimes = 1;
		if (buf.remainingTimes > 1)
		{
			if (UserID < 10 && TargetID < 10)
				buf.remainingTimes += pTargetData->BuffedTiemsAdd;
			else
				if (TargetID>9 && UserID>10)
					buf.remainingTimes += pTargetData->BuffedTiemsAdd;
		}
		SetDateBuffUp(UserID, TargetID, sSkillID, buf, Skilllv);
	}
}

