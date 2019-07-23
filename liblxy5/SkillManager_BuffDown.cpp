#include "_global.h"


bool cSkillManager::SetDateBuffDown(list<sBuff>::iterator& sbuf)//int targetID, int stateid)
{
	int targetID = sbuf->targetID;
	int stateid = sbuf->ID;
	cObj* pTarget = m_pFightState->m_pFightWorkList[targetID]->m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	sFightData&  targetProperty = pTargetData->m_FightData;

	auto& TargetFightP = targetProperty;
	const sBuff& buf = *sbuf;

	switch (stateid)
	{
	case 0://横扫千军
	case 7://破釜沉舟
//		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 1: //后发制人
		pTargetData->Speed.AddDataAdd(-0xFFFF);
//		pTargetData->m_DamagePercent.d1 -= 50;
//		pTargetData->m_Pierce.d1 -= 30;
		pTargetData->CriRate.d1 -= 20;
		pTargetData->Def.AddDataAdd(-sbuf->damage);
		pTargetData->Mana.AddDataAdd(-sbuf->damage2);
		break;
	case 4:
		pTargetData->Hit.AddDataAdd(-sbuf->damage2);
		pTargetData->Atk.AddDataAdd(-sbuf->damage);
		break;
	case 6:
		pTarget->SetShakeFor抖动(false);
		targetProperty.chaos混乱反间 -= 1;
		g_pMainState->m_FightWorkList[targetID/*pTarget->m_IDInFightlist*/].m_WorkType = -1;
		TargetFightP.cannotMagic -= 1;
		TargetFightP.cannotSpesialSkill -= 1;
		TargetFightP.cannotUseItem -= 1;
		break;
	case 8://安神诀
//		pTargetData->DmgPercentOfMagic.d2 -= 30;
		pTargetData->Mana.AddDataAdd(-sbuf->damage);
		break;
	case 14://催眠符
		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 15://失心
		targetProperty.cannotMagic -= 1;
		pTargetData->Def.AddDataAddPercent(sbuf->damage);
		pTargetData->Mana.AddDataAddPercent(sbuf->damage2);
		pTargetData->Evade.AddDataAddPercent(25);
		break;
// 	case 16://落魄
// 		targetProperty.cannotMagic -= 1;
// 		targetProperty.cannotAttack -= 1;
// 		//		pTargetData->m_Wakan.AddDataAddPercent(20);
// 		pTarget->SetShakeFor抖动(false);
// 		break;
	case 17://失忆
		// 		targetProperty.cannotAttack -= 1;
		// 		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		break;
// 	case 18://追魂
// 		targetProperty.cannotAttack -= 1;
// 		pTargetData->Def.AddDataAddPercent(20);
// 		break;
// 	case 19://离魂
// 		targetProperty.cannotMagic -= 1;
// 		break;
// 	case 20://失魂   
// 		targetProperty.cannotMagic -= 1;
// 		break;
	case 21://定身 
//		targetProperty.cannotAll -= 1;
		
// 		targetProperty.cannotMagic -= 1;
// 		targetProperty.cannotSkill -= 1;
		pTargetData->Def.AddDataAddPercent(sbuf->damage);
		pTargetData->Mana.AddDataAddPercent(sbuf->damage2);
		targetProperty.cannotAttack -= 1;
		break;
	case 26:
		pTarget->SetShadow(false);
		pTargetData->HitRateOfMagic.d2 -= sbuf->damage;
		break;
	case 27: //碎甲符
		pTargetData->Def.AddDataAddPercent(sbuf->damage);
		pTargetData->Mana.AddDataAddPercent(sbuf->damage2);
		break;
	case 33://金刚护法
		pTarget->SetTwinkle(false);
		pTargetData->Atk.AddDataAdd(-sbuf->damage);
		break;
	case 34:   //韦陀护法  
		pTargetData->Hit.AddDataAdd(-sbuf->damage);
		pTargetData->Atk.AddDataAdd(-sbuf->damage2);
		break;
	case 35:  //金刚护体
		pTargetData->Def.AddDataAdd(-sbuf->damage);
		break;
	case 36:  //一苇渡江
		pTargetData->Speed.AddDataAdd(-sbuf->damage);
		break;
	case 46:    //佛法无边
		pTargetData->ComboRateOfMagic.d1 -= sbuf->damage;
		break;
	case 49:    //楚楚可怜
		// 		pTargetData->m_HitRate.d2 -= 100;
		// 		pTargetData->m_MagicHitRate.d2 -= 100;
		// 		pTargetData->m_SealRate.d2 -= 100;
		// 		pTargetData->poisonRate.d2 -= 100;
		targetProperty.cannotMagic -= 1;
		pTargetData->Hide.d1 -= 1;
		break;
	case 50: //满天花雨中毒

		break;
	case 54://似玉生香
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		break;
// 	case 59://一笑倾城
// 		targetProperty.cannotMagic -= 1;
// 		break;
	case 62://天神护体
		pTargetData->Mana.AddDataAdd(-sbuf->damage);
		pTargetData->HitRateOfMagic.d2 -= (sbuf->damage2);
		break;
	case 67:	//镇妖
//		pTargetData->m_ATK.AddDataAddPercent(30);
		targetProperty.cannotSpesialSkill -= 1;
		break;
	case 68:	//错乱
		pTargetData->Hit.AddDataAddPercent(sbuf->damage);
		targetProperty.cannotMagic -= 1;
		break;
	case 69:	//百万神兵
		targetProperty.cannotAttack -= 1;
		break;
	case 81:// 逆鳞
		pTarget->SetTwinkle(false);
		pTargetData->Atk.SetDataAdd(-sbuf->damage);
		break;
	case 87:// 神龙摆尾
		pTargetData->DmgPercent.d2 -= buf.damage;
		break;
	case 89:  //日月乾坤
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		break;
	case 90:   //炼气化神
		pTargetData->m_FightData.m_TurnMPAdd -= sbuf->damage;
		break;
	case 91:    //生命之泉
		pTargetData->m_FightData.m_TurnHPAdd -= sbuf->damage;
		break;
	case 104:
	case 102: //普渡众生
		pTargetData->m_FightData.m_TurnHPAdd -= sbuf->damage;
		pTargetData->m_FightData.m_TurnHPHurtAdd -= sbuf->damage2;
		break;
	case 103://紧箍咒
		pTargetData->m_FightData.m_TurnHPHurtAdd += sbuf->damage;
		pTargetData->m_FightData.m_TurnHPAdd += sbuf->damage;
		break;
	case 112:// 灵动九天
		pTargetData->Mana.AddDataAdd(-sbuf->damage);
		break;
	case 113:// 颠倒五行 
// 		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_SPD.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_HIT.AddDataAdd(-sbuf->damage);
		pTargetData->MagicThunder.d2 -= sbuf->damage;
		pTargetData->MagicSoil.d2 -= sbuf->damage; //土
		pTargetData->MagicFire.d2 -= sbuf->damage; //火
		pTargetData->MagicWater.d2 -= sbuf->damage; //水
		pTargetData->HitRateOfMagic.d2 -= sbuf->damage / 2;
		break;
	case 120:
// 		pTargetData->m_HitRate.d1 -= 100;
		pTargetData->HitRateOfSeal.d2 -= sbuf->damage;
// 		pTargetData->poisonRate.d1 -= 30;
		pTargetData->Hide.d2 -= sbuf->damage2;
		break;
	case 122:
		break;
	case 123://修罗隐身
	{
		pTarget->SetShadow(false);
//		pTargetData->m_HitRate.d1 -= 10;
// 		pTargetData->m_HitRate.d2 -= 100;
// 		pTargetData->m_MagicHitRate.d2 -= 100;
// 		pTargetData->m_SealRate.d2 -= 100;
// 		pTargetData->poisonRate.d2 -= 100;
		targetProperty.cannotMagic -= 1;
		pTargetData->Hide.d1 -= 1;
	}
		break;
	case 125:
		pTargetData->Atk.AddDataAdd(-sbuf->damage);
		break;
	case 126:// 黄泉之息
		pTargetData->Speed.AddDataAddPercent(sbuf->damage);
		break;
	case 129:// 锢魂术
		targetProperty.cannotLive -= 1;
		break;
	case 133://牛劲
		pTargetData->Mana.AddDataAdd(-sbuf->damage);
//		pTargetData->m_MagicHitRate.d1 -= 100;
		pTargetData->Hide.d2 -= sbuf->damage2;
		break;
	case 137://魔王回首
		pTargetData->CounterRate.d1 -= sbuf->damage;
		break;
	case 141://象形
		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 142://鹰击
	case 148://连环击
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 144:// 威慑
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSpesialSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 145:// 变身
		pTargetData->Atk.AddDataAdd(-sbuf->damage);
		break;
	case 147://定心
		pTargetData->Mana.AddDataAdd(-sbuf->damage);
		break;
	case 150://极度疯狂
		pTargetData->CounterRate.d1 -= sbuf->damage;
		break;
	case 152://天魔解体
// 		pTargetData->HPMax.AddDataAddPercent(-30);
// 		{
// 			int dam = AddHp(targetID, -5, 10000);
// 			SetDamage(-dam, targetID);
// 		}
// 		break;
	case 156://魔音摄魂
		targetProperty.cannotAddHP -= 1;
		break;
	case 159://含情脉脉
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		break;

	case 160:// 盘丝阵	
		pTargetData->Def.AddDataAdd(-sbuf->damage);
		break;
//	case 161: break;//复苏	
	case 162:  //天罗地网
		targetProperty.cannotAttack -= 1;
		break;
	case 166://幻镜术
		pTargetData->StabRateOfMagic.d1 -= sbuf->damage;    //法术反弹伤害
		pTargetData->StabPercentOfMagic.d1 -= sbuf->damage2; //法术反弹率
		break;

	case 175: // 不动如山
		pTargetData->DmgAdd.d2 -= sbuf->damage;
		pTargetData->DmgAddOfMagic.d2 -= sbuf->damage2;
		break;
	case 176: // 碎星决
		pTargetData->DmgAdd.d1 -= buf.damage;
		pTargetData->m_FightData.zhanyi -= 1;
		break;
	case 177: // 镇魂诀
		pTargetData->CriRate.d1 -= buf.damage;
		break;
	case 181: // 化骨
		pTargetData->SuckBloodRate.d1 -= buf.damage;
		pTargetData->SuckBloodPercent.d1 -= buf.damage2;
		break;
	case 182: // 夺魄令
		TargetFightP.cannotMagic -= 1;
		break;
	case 185: // 催心术
		pTargetData->Speed.AddDataAdd(buf.damage);
		break;
	case 187: // 明光宝烛
		pTargetData->DmgAdd.d2 -= buf.damage;
		break;
	case 188: // 金身舍利
		pTargetData->DmgAddOfMagic.d2 -= buf.damage2;
		break;
	case 198: // 雾杀
		break;
	case 199: // 血雨(夺魄令)
//		TargetFightP.cannotMagic -= 1;
		break;
	case 201: // 炎护 
		TargetFightP.yanhu -= 1;
		break;
	case 204: // 蜜润
		pTargetData->DmgAddOfMagic.d2 -= buf.damage2;
		break;

	case 1002:
		pTargetData->ParryRate.d1 -= buf.damage;
		break;
// 	case 1004://保护
// 		break;
// 	case 2092://惊心一剑
// 		//		pTargetData->m_ATK.AddDataAddPercent(20);
// 		break;
	case 2093://夜舞倾城
		pTargetData->Atk.AddDataAddPercent(buf.damage);   //伤害
		pTargetData->Hit.AddDataAddPercent(buf.damage);   //命中
		pTargetData->Def.AddDataAddPercent(buf.damage);   //防御
		pTargetData->Mana.AddDataAddPercent(buf.damage); //灵力
		pTargetData->Speed.AddDataAddPercent(buf.damage);   //速度
		pTargetData->Evade.AddDataAddPercent(buf.damage); //躲闪
		break;
	case 2094://死亡召唤
		pTargetData->m_FightData.cannotLive -= 1;
		break;
	case 2095: // 力劈
		pTargetData->Hit.AddDataAddPercent(-buf.damage); //命中
		break;
	case 2096: // 浮云神马
		pTargetData->Speed.AddDataAddPercent(-buf.damage);
		break;
	case 2097:// 法术防御
		pTargetData->DmgPercentOfMagic.d2 -= buf.damage;
		break;
	case 2101:// 无畏布施
		pTargetData->DmgAdd.d2 -= buf.damage;
		pTargetData->DmgAddOfMagic.d2 -= buf.damage2;
		break;
	case 1997: // 战意
		break;
	case 1998:// 无畏布施2
		pTargetData->Def.AddDataAddPercent(buf.damage);
		pTargetData->Mana.AddDataAddPercent(buf.damage2);
		break;
	case 3024://太极护法 罗汉
	case 3025:
		pTargetData->DmgPercentOfMagic.d2 -= buf.damage;
		break;
	case 3026://修罗咒
		pTargetData->StabRateOfMagic.d1 -= buf.damage;
		pTargetData->StabPercentOfMagic.d1 -= buf.damage2;
		pTargetData->StabRate.d1 -= buf.damage;
		pTargetData->StabPercent.d1 -= buf.damage2;
		break;
	case 3027://天衣无缝
		pTargetData->HitRateOfMagic.d2 -= buf.damage;
		break;
	case 3047://心如明镜
		pTargetData->DmgPercentOfMagic.d2 -= buf.damage;//法术防御加成
		pTargetData->DmgPercent.d2 -= buf.damage;//物理防御加成
		pTargetData->HitRateOfPoison.d2 -= buf.damage2;
		pTargetData->HitRateOfSeal.d2 -= buf.damage2;
		break;
	default:
		ERRBOX2(stateid);
		return false;
		break;
	}
	return true;
}
