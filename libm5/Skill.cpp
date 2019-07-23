#include "global.h"
#if ccc_date

BOOL cSkillManager::SetDateBuffUp(int userID, int targetID, int stateid, sBuff& buf, int skilllv)
{
	if (g_StateType != STATE_FIGHT)return TRUE;
	if (buf.times < 1)buf.times = 1;
	int MagicPos = 0;
	DWORD MagicID = 0; //BUFF 的ID
	BOOL MagicUpOrDown = FALSE; //设置BUFF 在人物显示后显示
//	int  magicType = 1; //默认法术类型 封印
	cObj* pTarget = m_pFightState->m_pList[targetID]->m_pData;
	cPetData* pTargetData;
	pTarget->GetDateP(pTargetData);
	sFightData& TargetFightP = pTargetData->m_FightProperty;
	//eBuffType EffectType = eBuffType封印;


	for (list<sBuff>::iterator it = pTarget->m_StateList.begin(); it != pTarget->m_StateList.end(); it++)
	{
		if (it->ID == stateid)
		{
			it->times = buf.times;
			return TRUE;
		}
	}
	switch (stateid)
	{
	case 0: //横扫千军
	case 7: //破釜沉舟
		MagicID = 0xD9463A0C;
		//		TargetFightP.cannotAll += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicPos = -10;
		break;
	case 1://后发制人
		MagicID = 0x2A2A0663;
		pTargetData->m_SPD.AddDataOriginal(80000);
		//		pTargetData->m_Pierce.d1 += 30;
		pTargetData->m_CriRate.d1 += 20;
		//		pTargetData->m_DamagePercent.d1 += 50;
		pTargetData->m_DEF.AddDataOriginal(buf.damage = skilllv * 3);
		pTargetData->m_Wakan.AddDataOriginal(buf.damage2 = skilllv * 2);
		MagicPos = -10;
		break;
	case 4://杀气诀
		MagicUpOrDown = TRUE;
		MagicID = 0x62EDD1CB;
		buf.damage = skilllv;
		pTargetData->m_HIT.AddDataOriginal(buf.damage * 3);
		pTargetData->m_ATK.AddDataOriginal(buf.damage);
		break;
	case 6://反间计
		pTarget->SetShakeFor抖动(TRUE);
		TargetFightP.chaos += 1;
		break;
	case 8://安神诀
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		MagicID = 3860707508;
		pTargetData->m_DamageAddPercentMagic.d2 += 30;
		break;
	case 14://催眠
		MagicPos = -10;
		TargetFightP.cannotAll += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 3398426285;
		break;
	case 15://失心
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		pTargetData->m_Evade.AddDataAddPercent(-20);
		MagicID = 3635978625;
		break;
	case 16://落魄
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotAttack += 1;
		//		pTargetData->m_Wakan.AddDataAddPercent(-20);
		pTarget->SetShakeFor抖动(TRUE);
		//		MagicID = 0x8B43833D;
		break;
	case 17://失忆
		MagicPos = -10;
		// 		TargetFightP.cannotAttack += 1;
		// 		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		MagicID = 3946646209;
		break;
	case 18://追魂
		MagicPos = -10;
		pTargetData->m_DEF.AddDataAddPercent(-20);
		TargetFightP.cannotAttack += 1;
		MagicID = 3655438388;
		break;
	case 19://离魂
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		MagicID = 1214058823;
		break;
	case 20://失魂   
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		MagicID = 2336457533;
		break;
	case 21://定身 
		MagicPos = -10;
		//		TargetFightP.cannotAll += 1;
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		TargetFightP.cannotAttack += 1;
		// 		TargetFightP.cannotMagic += 1;
		// 		TargetFightP.cannotSkill += 1;
		MagicID = 2461182746;
		break;
	case 26:
		pTarget->SetShadow(50);
		pTargetData->m_MagicHitRate.d2 += buf.damage = skilllv / 8;
		break;
	case 27: //碎甲符
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		MagicID = 0x5525C5FB;
		MagicUpOrDown = TRUE;
		MagicPos = 10;
		break;
	case 33://金刚护法
		pTarget->SetTwinkle(TRUE);
		buf.damage = skilllv * 3 / 2;
		pTargetData->m_ATK.AddDataAdd(buf.damage);
		break;
	case 34: //韦陀护法  
		pTargetData->m_HIT.AddDataAdd(buf.damage = skilllv * 3);
		MagicID = 0xF184BD59;
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		break;
	case 35:  //金刚护体
		pTargetData->m_DEF.AddDataAdd(buf.damage = skilllv * 3 / 2);
		MagicID = 916220457;
		MagicUpOrDown = TRUE;
		break;
	case 36://一苇渡江
		MagicID = 382287583;
		MagicPos = -10;
		pTargetData->m_SPD.AddDataAddPercent(buf.damage = skilllv / 3);
		break;
	case 46:    //佛法无边
		pTargetData->m_MagicComboRate.d1 += 30;
		MagicID = 3930943562;
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		break;
	case 49:    //楚楚可怜
		MagicID = 0x72AD6DBA;
		MagicPos = -10;
		MagicUpOrDown = TRUE;
		// 		pTargetData->m_HitRate.d2 += 100;
		// 		pTargetData->m_MagicHitRate.d2 += 100;
		// 		pTargetData->m_SealRate.d2 += 100;
		// 		pTargetData->poisonRate.d2 += 100;
		TargetFightP.cannotMagic += 1;
		pTargetData->PeopleSpecial.d2 += 100;
		break;
	case 50: //满天花雨中毒
		MagicID = 0xDBCEE32C;
		MagicPos = -10;
		MagicUpOrDown = 1;
		break;
	case 54://似玉生香
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		MagicID = 0x59D77EF9;
		MagicPos = -10;
		break;
	case 59://一笑倾城
		TargetFightP.cannotMagic += 1;
		MagicID = 3635978625;// 0x1E1AF8D9;
		MagicPos = -10;
		break;
	case 63://天神护法
		break;
	case 67:	//镇妖
//		pTargetData->m_ATK.AddDataAddPercent(-30);
		TargetFightP.cannotSkill += 1;
		MagicID = 0x98753F94;
		MagicPos = -10;
		break;
	case 68:	//错乱
		pTargetData->m_HIT.AddDataAddPercent(-20);
		TargetFightP.cannotMagic += 1;
		MagicID = 0x2F78C46E;
		MagicUpOrDown = TRUE;
		MagicPos = -10;
		break;
	case 69:	//百万神兵
		TargetFightP.cannotAttack += 1;
		MagicID = 0xC48ABA7B;
		MagicPos = -10;
		break;
	case 81:// 逆鳞
		pTarget->SetTwinkle(TRUE);
		buf.damage = skilllv;
		pTargetData->m_ATK.SetDataAdd(buf.damage);
		break;
	case 89:  //日月乾坤
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		MagicID = 0x313BCC79;
		MagicUpOrDown = 1;
		MagicPos = -10;
		break;
	case 90:   //炼气化神
		MagicID = 0x719D767F;
		MagicUpOrDown = 1;
		MagicPos = 10;
		//		buf.damage = skilllv;
		pTargetData->m_FightProperty.m_TurnMPAdd += buf.damage;
		AddMp(targetID, buf.damage);
		break;
	case 91:    //生命之泉
		MagicID = 0xF8EE853A;
		MagicUpOrDown = 1;
		MagicPos = 10;
		//		buf.damage = skilllv * 2 + 120;
		pTargetData->m_FightProperty.m_TurnHPAdd += buf.damage;
		AddHp(targetID, buf.damage);
		buf.damage2 = buf.damage;
		break;
	case 102: //普渡众生
		MagicID = 0xD8857128;
		MagicUpOrDown = 1;
		MagicPos = 10;
		buf.damage = skilllv * 4 + 50;
		buf.damage2 = buf.damage;
		pTargetData->m_FightProperty.m_TurnHPAdd += buf.damage;
		pTargetData->m_FightProperty.m_TurnHPHurtAdd += buf.damage2;
		break;
	case 103:// 紧箍咒
		MagicID = 0xEFE73EB9;
		MagicUpOrDown = 1;
		MagicPos = 10;
		pTargetData->m_FightProperty.m_TurnHPHurtAdd -= buf.damage = skilllv * 2;
		break;
	case 112:// 灵动九天
		MagicID = 0x95FF4460;
		MagicUpOrDown = 1;
		MagicPos = 0;
		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 113:// 颠倒五行
		MagicID = 0x4DDF5690;
		MagicUpOrDown = 1;
		MagicPos = 0;
		// 		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv);
		// 		pTargetData->m_ATK.AddDataAdd(buf.damage);
		// 		pTargetData->m_DEF.AddDataAdd(buf.damage);
		// 		pTargetData->m_SPD.AddDataAdd(buf.damage);
		// 		pTargetData->m_HIT.AddDataAdd(buf.damage);
		buf.damage = skilllv / 5 + 10;
		pTargetData->m_MagicThunder.d2 += buf.damage;
		pTargetData->m_MagicSoil.d2 += buf.damage; //土
		pTargetData->m_MagicFire.d2 += buf.damage; //火
		pTargetData->m_MagicWater.d2 += buf.damage; //水
		pTargetData->m_MagicHitRate.d2 += buf.damage / 2;
		break;
	case 120://幽冥鬼眼
		MagicID = 0x21435203;
		// 		pTargetData->m_HitRate.d1 += 100;
		pTargetData->m_SealRate.d2 += buf.damage = skilllv / 10;
		// 		pTargetData->poisonRate.d1 += 30;
		pTargetData->PeopleSpecial.d1 += 100;
		MagicUpOrDown = 1;
		MagicPos = 0;
		break;
	case 122:// 尸腐毒
		MagicID = 0x839CC29A;
		MagicUpOrDown = 1;
		MagicPos = -10;

		break;
	case 123://修罗隐身

	{
		pTarget->SetShadow(50);
		pTargetData->PeopleSpecial.d2 += 100;
		//			pTargetData->m_HitRate.d1 += 10;
		// 			pTargetData->m_HitRate.d2 += 100;
		// 			pTargetData->m_MagicHitRate.d2 += 100;
		// 			pTargetData->m_SealRate.d2 += 100;
		// 			pTargetData->poisonRate.d2 += 100;
		TargetFightP.cannotMagic += 1;
	}
	break;
	case 125:
		pTargetData->m_ATK.AddDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 126:// 黄泉之息
		MagicID = 0x5ECEBEDD;
		pTargetData->m_SPD.AddDataAddPercent(-20);
		MagicUpOrDown = 1;
		MagicPos = -10;
		break;
	case 129:// 锢魂术
		MagicID = 0x5C0073EE;
		MagicUpOrDown = 1;
		MagicPos = 1;
		pTargetData->m_FightProperty.cannotLive += 1;
		break;
	case 133://牛劲
		MagicID = 0x62EDD1CB;
		buf.damage = skilllv;
		MagicUpOrDown = 1;
		pTargetData->m_Wakan.AddDataAdd(buf.damage);
		//		pTargetData->m_MagicHitRate.d1 += 100;
		pTargetData->PeopleSpecial.d1 += 100;
		break;
	case 141://象形
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 0x3646A4D9;
		MagicPos = -10;
		break;
	case 148://连环击
	case 142://鹰击
		stateid = 142;
		//		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 0x58628406;
		MagicPos = -10;
		break;
	case 144:// 威慑
		MagicID = 0x20FCCE94;
		MagicPos = -10;
		pTargetData->m_ATK.AddDataAddPercent(-20);
		pTargetData->m_DEF.AddDataAddPercent(-10);
		pTargetData->m_Wakan.AddDataAddPercent(-10);
		break;
	case 145:// 变身
		MagicID = 0x85C9AF08;
		pTargetData->m_ATK.AddDataAdd(buf.damage = skilllv);
		MagicUpOrDown = 1;
		break;
	case 147://定心术
		MagicID = 755485932;
		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv * 3 / 2);
		MagicUpOrDown = 1;
		break;
	case 150://极度疯狂
		MagicID = 0xBBEA83F4;
		pTargetData->m_CounterRate.d1 += 100;
		MagicUpOrDown = 1;
		break;
	case 152://天魔解体
		MagicID = 0x3D3FA597;
		pTargetData->m_HPMax.AddDataAddPercent(30);

		{
			int dam = AddHp(targetID, 5, 10000);
			SetDamage(-dam, targetID);
		}
		MagicUpOrDown = 1;
		break;
	case 156://魔音摄魂
		MagicID = 0xAF07277F;
		MagicPos = -10;
		TargetFightP.cannotAddHP += 1;
		break;
	case 159://含情脉脉
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		MagicID = 0x8103AFD2;//0xC4AA8E18;
		MagicPos = -10;
		break;
	case 160:// 盘丝阵
		buf.damage = skilllv * 2;
		pTargetData->m_DEF.AddDataAdd(buf.damage);
		MagicID = 0x369C6A29;
		MagicUpOrDown = TRUE;
		break;
	case 161: break;//复苏	
	case 162:  //天罗地网
		MagicPos = -10;
		MagicID = 0x8F3E73D5;
		TargetFightP.cannotAttack += 1;
		break;
	case 164:break;//姐妹同心	
	case 166://幻镜术
		MagicID = 0x0B788E5A;
		MagicUpOrDown = TRUE;
		MagicPos = -10;
		pTargetData->m_StabRateMagic.d1 += 50;    //法术反弹伤害
		pTargetData->m_StabDamageRateMagic.d1 += 50; //法术反弹率
		break;
	case 1002: //1回合的格挡 BUFF
		pTargetData->m_ParryRate.d1 += 1000;
		break;
	case 1004://保护
		break;
	case 2092://惊心一剑
//		pTargetData->m_ATK.AddDataAddPercent(-20);
		break;
	case 2093://夜舞倾城
		pTargetData->m_ATK.AddDataAddPercent(-10);   //伤害
		pTargetData->m_HIT.AddDataAddPercent(-10);   //命中
		pTargetData->m_DEF.AddDataAddPercent(-10);   //防御
		pTargetData->m_Wakan.AddDataAddPercent(-10); //灵力
		pTargetData->m_SPD.AddDataAddPercent(-10);   //速度
		pTargetData->m_Evade.AddDataAddPercent(-10); //躲闪
		break;
	case 2094://死亡召唤
		MagicID = 0x19182964;
		MagicPos = -10;
		pTargetData->m_FightProperty.cannotLive += 1;
		break;
	case 2095:
		pTargetData->m_HIT.AddDataAddPercent(200);   //命中
		break;
	case 2097:// 法术防御
		MagicID = 0xDEDEE983;
		MagicUpOrDown = TRUE;
		pTargetData->m_DamageAddPercentMagic.d2 += 65;
		break;
	case 3024://太极护法 
	case 3025://罗汉
		MagicPos = -10;
		MagicID = 0xAF07277F;// 0x5CC81980;
		pTargetData->m_DamageAddPercentMagic.d2 += 50;
		break;
	case 3026://修罗咒
		pTargetData->m_StabRateMagic.d1 += 100;
		pTargetData->m_StabDamageRateMagic.d1 += 30;
		break;
	case 3027://天衣无缝
		pTargetData->m_MagicHitRate.d2 += 50;
		break;
	case 3047://心如明镜
		pTargetData->m_DamageAddPercentMagic.d2 += 50;//法术防御加成
		pTargetData->m_DamagePercent.d2 += 50;//物理防御加成
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		pTarget->ReMoveState(eBuffType其它);
		break;
	default:
		ERRBOX2(stateid);
		return TRUE;
	}
	sSkill* pskill = g_pMainState->m_SkillManager.GetSkill(stateid);
	if (pskill)
	{
		buf.EffectType = (eBuffType)pskill->m_EffectType;
	}
	else buf.EffectType = eBuffType其它;
	buf.skilllv = skilllv;
	buf.userID = userID;
	buf.targetID = targetID;
	buf.MagicID = MagicID;
	buf.bufPos = MagicPos;
	buf.bBuffup = MagicUpOrDown;
	buf.ID = stateid; //设置BUFF  ID
	m_pFightState->AddState(targetID, buf);
	return TRUE;
}

BOOL cSkillManager::SetDateBuffDown(list<sBuff>::iterator& sbuf)//int targetID, int stateid)
{
	int targetID = sbuf->targetID;
	int stateid = sbuf->ID;
	cObj* pTarget = m_pFightState->m_pList[targetID]->m_pData;
	cPetData* pTargetData;
	pTarget->GetDateP(pTargetData);
	sFightData&  targetProperty = pTargetData->m_FightProperty;


	switch (stateid)
	{
	case 0://横扫千军
	case 7://破釜沉舟
//		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 1: //后发制人
		pTargetData->m_SPD.AddDataOriginal(-80000);
		//		pTargetData->m_DamagePercent.d1 -= 50;
		//		pTargetData->m_Pierce.d1 -= 30;
		pTargetData->m_CriRate.d1 -= 20;
		pTargetData->m_DEF.AddDataOriginal(-sbuf->damage);
		pTargetData->m_Wakan.AddDataOriginal(-sbuf->damage2);
		break;
	case 4:
		pTargetData->m_HIT.AddDataOriginal(-sbuf->damage * 3);
		pTargetData->m_ATK.AddDataOriginal(-sbuf->damage);
		break;
	case 6:
		pTarget->SetShakeFor抖动(FALSE);
		targetProperty.chaos -= 1;
		g_pMainState->m_FightList[pTarget->m_IDInFightlist].m_WorkType = -1;
		break;
	case 8://安神诀
		pTargetData->m_DamageAddPercentMagic.d2 -= 30;
		break;
	case 14://催眠符
		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 15://失心
		targetProperty.cannotMagic -= 1;
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		pTargetData->m_Evade.AddDataAddPercent(20);
		break;
	case 16://落魄
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotAttack -= 1;
		//		pTargetData->m_Wakan.AddDataAddPercent(20);
		pTarget->SetShakeFor抖动(FALSE);
		break;
	case 17://失忆
// 		targetProperty.cannotAttack -= 1;
// 		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		break;
	case 18://追魂
		targetProperty.cannotAttack -= 1;
		pTargetData->m_DEF.AddDataAddPercent(20);
		break;
	case 19://离魂
		targetProperty.cannotMagic -= 1;
		break;
	case 20://失魂   
		targetProperty.cannotMagic -= 1;
		break;
	case 21://定身 
//		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		// 		targetProperty.cannotMagic -= 1;
		// 		targetProperty.cannotSkill -= 1;
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		break;
	case 26:
		pTarget->SetShadow(FALSE);
		pTargetData->m_MagicHitRate.d2 -= sbuf->damage;
		break;
	case 27: //碎甲符
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		break;
	case 33://金刚护法
		pTarget->SetTwinkle(FALSE);
		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
		break;
	case 34:   //韦陀护法  
		pTargetData->m_HIT.AddDataAdd(-sbuf->damage);
		break;
	case 35:  //金刚护体
		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
		break;
	case 36:  //一苇渡江
		pTargetData->m_SPD.AddDataAdd(-sbuf->damage);
		break;
	case 46:    //佛法无边
		pTargetData->m_MagicComboRate.d1 -= 30;
		break;
	case 49:    //楚楚可怜
// 		pTargetData->m_HitRate.d2 -= 100;
// 		pTargetData->m_MagicHitRate.d2 -= 100;
// 		pTargetData->m_SealRate.d2 -= 100;
// 		pTargetData->poisonRate.d2 -= 100;
		targetProperty.cannotMagic -= 1;
		pTargetData->PeopleSpecial.d2 -= 100;
		break;
	case 50: //满天花雨中毒

		break;
	case 141://象形
		targetProperty.cannotAll -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		break;
	case 54://似玉生香
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		break;
	case 59://一笑倾城
		targetProperty.cannotMagic -= 1;
		break;
	case 63://天神护法

		break;
	case 67:	//镇妖
//		pTargetData->m_ATK.AddDataAddPercent(30);
		targetProperty.cannotSkill -= 1;
		break;
	case 68:	//错乱
		pTargetData->m_HIT.AddDataAddPercent(20);
		targetProperty.cannotMagic -= 1;
		break;
	case 69:	//百万神兵
		targetProperty.cannotAttack -= 1;
		break;
	case 81:// 逆鳞
		pTarget->SetTwinkle(FALSE);
		pTargetData->m_ATK.SetDataAdd(-sbuf->damage);
		break;
	case 89:  //日月乾坤
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotSkill -= 1;
		break;
	case 90:   //炼气化神
		pTargetData->m_FightProperty.m_TurnMPAdd -= sbuf->damage;
		break;
	case 91:    //生命之泉
		pTargetData->m_FightProperty.m_TurnHPAdd -= sbuf->damage;
		break;
	case 102: //普渡众生
		pTargetData->m_FightProperty.m_TurnHPAdd -= sbuf->damage;
		pTargetData->m_FightProperty.m_TurnHPHurtAdd -= sbuf->damage2;
		break;
	case 103://紧箍咒
		pTargetData->m_FightProperty.m_TurnHPHurtAdd += sbuf->damage;
		break;
	case 112:// 灵动九天
		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
		break;
	case 113:// 颠倒五行 
// 		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_SPD.AddDataAdd(-sbuf->damage);
// 		pTargetData->m_HIT.AddDataAdd(-sbuf->damage);
		pTargetData->m_MagicThunder.d2 -= sbuf->damage;
		pTargetData->m_MagicSoil.d2 -= sbuf->damage; //土
		pTargetData->m_MagicFire.d2 -= sbuf->damage; //火
		pTargetData->m_MagicWater.d2 -= sbuf->damage; //水
		pTargetData->m_MagicHitRate.d2 -= sbuf->damage / 2;
		break;
	case 120:
		// 		pTargetData->m_HitRate.d1 -= 100;
		pTargetData->m_SealRate.d2 -= sbuf->damage;
		// 		pTargetData->poisonRate.d1 -= 30;
		pTargetData->PeopleSpecial.d1 -= 100;
		break;
	case 122:
		break;
	case 123://修罗隐身

	{
		pTarget->SetShadow(FALSE);
		//			pTargetData->m_HitRate.d1 -= 10;
		// 			pTargetData->m_HitRate.d2 -= 100;
		// 			pTargetData->m_MagicHitRate.d2 -= 100;
		// 			pTargetData->m_SealRate.d2 -= 100;
		// 			pTargetData->poisonRate.d2 -= 100;
		targetProperty.cannotMagic -= 1;
		pTargetData->PeopleSpecial.d2 -= 100;
	}
	break;
	case 125:
		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
		break;
	case 126:// 黄泉之息
		pTargetData->m_SPD.AddDataAddPercent(20);
		break;
	case 129:// 锢魂术
		targetProperty.cannotLive -= 1;
		break;
	case 133://牛劲
		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
		//		pTargetData->m_MagicHitRate.d1 -= 100;
		pTargetData->PeopleSpecial.d1 -= 100;
		break;
	case 142://鹰击
		targetProperty.cannotMagic -= 1;
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotSkill -= 1;
		targetProperty.cannotUseItem -= 1;
		break;
	case 144:// 威慑
		pTargetData->m_ATK.AddDataAddPercent(20);
		pTargetData->m_DEF.AddDataAddPercent(10);
		pTargetData->m_Wakan.AddDataAddPercent(10);
		break;
	case 145:// 变身
		pTargetData->m_ATK.AddDataAdd(-sbuf->damage);
		break;
	case 147://定心
		pTargetData->m_Wakan.AddDataAdd(-sbuf->damage);
		break;
	case 150://极度疯狂
		pTargetData->m_CounterRate.d1 -= 100;
		break;
	case 152://天魔解体
		pTargetData->m_HPMax.AddDataAddPercent(-30);

		{
			int dam = AddHp(targetID, -5, 10000);
			SetDamage(-dam, targetID);
		}
		break;
	case 156://魔音摄魂
		pTargetData->m_FightProperty.cannotAddHP -= 1;
		break;
	case 159://含情脉脉
		targetProperty.cannotAttack -= 1;
		targetProperty.cannotMagic -= 1;
		break;

	case 160:// 盘丝阵	
		pTargetData->m_DEF.AddDataAdd(-sbuf->damage);
		break;

	case 162:  //天罗地网
		targetProperty.cannotAttack -= 1;
		break;
	case 166://幻镜术
		pTargetData->m_StabRateMagic.d1 -= 50;    //法术反弹伤害
		pTargetData->m_StabDamageRateMagic.d1 -= 50; //法术反弹率
		break;
	case 1002:
		pTargetData->m_ParryRate.d1 -= 1000;
		break;
	case 1004:
		break;
	case 2092://惊心一剑
//		pTargetData->m_ATK.AddDataAddPercent(20);
		break;
	case 2093://夜舞倾城
		pTargetData->m_ATK.AddDataAddPercent(10);   //伤害
		pTargetData->m_HIT.AddDataAddPercent(10);   //命中
		pTargetData->m_DEF.AddDataAddPercent(10);   //防御
		pTargetData->m_Wakan.AddDataAddPercent(10); //灵力
		pTargetData->m_SPD.AddDataAddPercent(10);   //速度
		pTargetData->m_Evade.AddDataAddPercent(10); //躲闪
		break;
	case 2094://死亡召唤
		pTargetData->m_FightProperty.cannotLive -= 1;
		break;
	case 2095:
		pTargetData->m_HIT.AddDataAddPercent(-200); //躲闪
		break;
	case 2097:// 法术防御
		pTargetData->m_DamageAddPercentMagic.d2 -= 65;
		break;
	case 3024://太极护法 罗汉
	case 3025:
		pTargetData->m_DamageAddPercentMagic.d2 -= 50;
		break;
	case 3026://修罗咒
		pTargetData->m_StabRateMagic.d1 -= 100;
		pTargetData->m_StabDamageRateMagic.d1 -= 30;
		break;
	case 3027://天衣无缝
		pTargetData->m_MagicHitRate.d2 -= 50;
		break;
	case 3047://心如明镜
		pTargetData->m_DamageAddPercentMagic.d2 -= 50;//法术防御加成
		pTargetData->m_DamagePercent.d2 -= 50;//物理防御加成
		break;
	default:
		ERRBOX2(stateid);
		return FALSE;
		break;
	}
	return TRUE;
}





BOOL cSkillManager::Use61暗器(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (!Skilllv)
	{
		Skilllv = g_pMainState->m_FightList[UserID].m_pData->GetSkillLv(0);
	}
	sFightList* pUserList = m_pFightState->m_pList[UserID];
	cObj* pUser = pUserList->m_pData;
	cPetData* pPet;
	pUser->GetDateP(pPet);
	int lv = pPet->m_LV;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		if (pUser->m_IndexType == INDEXTYEP_PET)
		{
			pUserList->m_work.pop_back();
			stage = -1;
			g_pMainState->m_Channel.AddNewString("宠物无法使用暗器");
			return TRUE;
		}
		// 		sItem2* pItem = GetItem(UserID);
		// 		if (pItem->GetNum() < 1)
		// 		{
		// 			pUserList->m_work.pop_back();
		// 			stage = -1;
		// 			g_pMainState->m_Channel.AddNewString("没有道具");
		// 			return TRUE;
		// 		}
		// 		if (lv / 15 < pItem->GetID())
		// 		{
		// 			pUserList->m_work.pop_back();
		// 			stage = -1;
		// 			g_pMainState->m_Channel.AddNewString("角色等级太低,无法使用");
		// 			return TRUE;
		// 		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage += 1;
	}
	return TRUE;
	case 1:

	{

		if (WaitForMagicPoint(UserID))
		{
			stage += 1;
			sItem2* pItem = GetItem(UserID);

			DWORD dateid = 0;
			int num = 0;
			switch (Skilllv / 20)
			{
			case 0://飞刀
				dateid = 0x44BE65A3;
				num = 1;
				break;
			case 1://飞蝗石
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 2://铁蒺藜
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 3://无影神针
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 4://孔雀翎
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 5://含沙射影
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 6://回龙摄魂标
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 7://寸阴若梦
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 8://魔睛子
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 9://顺逆神针
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			default:
				dateid = 0x44BE65A3;
				break;
				//				return FALSE;
			}
			num = Skilllv / 25 + 1;
			if (num > 7)
			{
				num = 7;
			}

			m_pFightState->m_HiddenWeapons.Load(dateid);
			int i = 0;
			for (; i < num; i++)
			{
				m_pFightState->m_HiddenWeaponsTargetID[i] = g_pMainState->m_AI.GetNear(UserID, TargetID, i, TRUE + 2);
				if (-1 == m_pFightState->m_HiddenWeaponsTargetID[i])
					break;
				m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = TRUE;
				m_pFightState->m_HiddenWeaponsp[i].m_x = pUser->GetX();
				m_pFightState->m_HiddenWeaponsp[i].m_y = pUser->GetY() - 30;
			}
			m_pFightState->m_HiddenWeaponsUseNum = i;
		}
	}
	return TRUE;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			stage += 1;
		}
	case 3:

	{
		int targetid;
		sItem2* pItem = GetItem(UserID);
		for (int i = 0; i < 10; i++)
		{
			if (TRUE == m_pFightState->m_HiddenWeaponsp[i].m_NeedShow)
			{
				if (m_pFightState->HiddenWeaponsMove(i))
				{
					targetid = m_pFightState->m_HiddenWeaponsTargetID[i];
					m_pFightState->m_HiddenWeaponsUseNum -= 1;
					m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = FALSE;
					if (!g_pMainState->m_FightList[targetid].isLive)continue;
					cPetData* pTargetData;
					g_pMainState->m_FightList[targetid].m_pData->GetDateP(pTargetData);
					int damageup = pPet->m_HiddenWeaponDamagePercent.d1 - pTargetData->m_HiddenWeaponDamagePercent.d2;
					if (rand() % 100 >= 100 + pPet->m_HitRate.d1 - pTargetData->m_HitRate.d2)
					{
						m_pFightState->SetAvoid(targetid, pUser->GetDirection());
					}
					else
					{
						int dam, damh;
						switch (Skilllv / 20)
						{
						case 0://飞刀
							dam = 100;
							damh = 10;
							break;
						case 1://飞蝗石
							dam = 120;
							damh = 20;
							break;
						case 2://铁蒺藜
							dam = 200;
							damh = 50;
							break;
						case 3://无影神针
							dam = 300;
							damh = 80;
							break;
						case 4://孔雀翎
							dam = 400;
							damh = 100;
							break;
						case 5://含沙射影
							dam = 500;
							damh = 150;
							break;
						case 6://回龙摄魂标
							dam = 800;
							damh = 200;
							break;
						case 7://寸阴若梦
							dam = 1000;
							damh = 250;
							break;
						case 8://魔睛子
							dam = 1500;
							damh = 300;
							break;
						default://顺逆神针
							dam = 2000;
							damh = 400;
							break;
						}


						damh = dam = (Skilllv / 20 + 1) * 30;
						dam = (Skilllv * 2 + dam + 50);
						dam = dam * (100 + damageup) / 100;

						if (dam > 0)
						{
							CheckPoision(UserID, targetid);//中毒修正
							if ((TargetID < 10) || g_pMainState->m_AI.m_AttackAI.m_bPKMode)
							{//普通任务时伤害其实是2倍化的
								// 									dam = dam >> 1;
								// 									damh = damh >> 1;
							}
							m_pFightState->SetSuffer(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction, UserID);
							AddHp(targetid, -dam);
							AddHpHurt(targetid, -damh);
							SetDamage(dam, targetid);
						}
						else
							m_pFightState->SetAvoid(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction);
					}
				}
			}
		}
		if (0 == m_pFightState->m_HiddenWeaponsUseNum)
		{
			if (3 == stage)
			{
				pUserList->m_work.pop_back();
				stage = -1;
			}
		}
	}
	break;
	}
	return TRUE;
}





BOOL cSkillManager::SetPetSkill1(cPetData* pPetDate, int ID, int lv)
{
	switch (ID)
	{
	case 0://反击
		pPetDate->m_CounterRate.d1 += lv * 30;
		break;
	case 1://高级反击
		pPetDate->m_CounterRate.d1 += lv * 45;
		break;
	case 2://反震
		pPetDate->m_StabRate.d1 += lv * 30;
		pPetDate->m_StabDamageRate.d1 += lv * 30;
		break;
	case 3://高级反震
		pPetDate->m_StabRate.d1 += lv * 30;
		pPetDate->m_StabDamageRate.d1 += lv * 50;
		break;
	case 4://吸血
		pPetDate->m_SuckBloodRate.d1 += lv * 20;
		break;
	case 5://高级吸血
		pPetDate->m_SuckBloodRate.d1 += lv * 35;
		break;
	case 6://连击
		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 7://高级连击
		pPetDate->m_Combo.d1 += lv * 30;
		break;
	case 8://飞行
		pPetDate->m_HitRate.d1 += lv * 10;
		pPetDate->m_HitRate.d2 += lv * 10;
		pPetDate->m_HiddenWeaponDamagePercent.d2 -= lv * 50;
		break;
	case 9://高级飞行
		pPetDate->m_HitRate.d1 += lv * 20;
		pPetDate->m_HitRate.d2 += lv * 20;
		pPetDate->m_HiddenWeaponDamagePercent.d2 -= lv * 20;
		break;
	case 10://夜战
//		pPetDate->m_Spurting.d2 += 20;
		pPetDate->m_DamagePercent.d1 += lv * 5;
		//		pPetDate->nightLv += lv *10;
		break;
	case 11://高级夜战
//		pPetDate->m_Spurting.d2 += 30;
		pPetDate->m_DamagePercent.d1 += lv * 10;
		//		pPetDate->nightLv += lv * 20;
		break;
	case 12://隐身
// 		pPetDate->m_HitRate.d2 += lv*15;
// 		pPetDate->m_MagicHitRate.d2 += lv * 15;
// 		pPetDate->m_SealRate.d2 += lv * 15;
// 		pPetDate->poisonRate.d2 += lv * 15;
		pPetDate->m_StartMagic.d1 = lv > 0 ? 123 : 0;
		break;
	case 13://高级隐身
// 		pPetDate->m_HitRate.d2 += lv * 25;
// 		pPetDate->m_MagicHitRate.d2 += lv * 25;
// 		pPetDate->m_SealRate.d2 += lv * 25;
// 		pPetDate->poisonRate.d2 += lv * 25;
		pPetDate->m_StartMagic.d1 = lv > 0 ? 123 : 0;
		break;
	case 14://感知
// 		pPetDate->m_HitRate.d1 += lv * 35;
// 		pPetDate->m_MagicHitRate.d1 += lv * 35;
// 		pPetDate->poisonRate.d1 += lv * 35;
		pPetDate->PeopleSpecial.d1 += 100;
		break;
	case 15://高级感知
		pPetDate->m_HitRate.d1 += lv * 25;
		// 		pPetDate->m_MagicHitRate.d1 += lv * 65;
		// 		pPetDate->poisonRate.d1 += lv * 65;
		pPetDate->PeopleSpecial.d1 += 100;
		break;
	case 16://再生
		pPetDate->m_LiveHpLv += lv * 10;
		break;
	case 17://高级再生
		pPetDate->m_LiveHpLv += lv * 20;
		break;
	case 18://冥思
		pPetDate->m_LiveMpLv += lv * 5;
		break;
	case 19://高级冥思
		pPetDate->m_LiveMpLv += lv * 10;
		break;
	case 20://慧根
		pPetDate->mpsavepercent += lv * 25;
		break;
	case 21://高级慧根
		pPetDate->mpsavepercent += lv * 50;
		break;
	case 22://不幸
//		pPetDate->m_CriRate.d2   -= lv*10;
		pPetDate->m_CriRate.d2 -= lv * 10;
		break;
	case 23://必杀
		pPetDate->m_CriRate.d1 += lv * 10;
		break;
	case 24://高级必杀
		pPetDate->m_CriRate.d1 += lv * 20;
		break;
	case 25://幸运
		pPetDate->m_CriRate.d2 += lv * 60;
		//		pPetDate->m_MagicCriRate.d2 -= lv * 60;
		break;
	case 26://高级幸运
		pPetDate->m_CriRate.d2 += lv * 200;
		//		pPetDate->m_MagicCriRate.d2 -= lv * 20;
		break;
	case 27://神迹
		pPetDate->restoreRate += lv * 60;
		break;
	case 28://高级神迹
		pPetDate->restoreRate += lv * 200;
		break;
	case 29://招架
		pPetDate->m_ParryRate.d1 += lv * 10;
		break;
	case 30://高级招架
		pPetDate->m_ParryRate.d1 += lv * 20;
		break;
	case 31://永恒
		pPetDate->buffAdd += lv * 1;
		break;
	case 32://高级永恒
		pPetDate->buffAdd += lv * 2;
		break;
	case 33://敏捷
		pPetDate->m_SPD.AddDataAddPercent(lv * 10);
		break;
	case 34://高级敏捷
		pPetDate->m_SPD.AddDataAddPercent(lv * 20);
		break;
	case 35://强力
		pPetDate->m_ATK.AddDataAddPercent(lv * 5);
		break;
	case 36://高级强力
		pPetDate->m_ATK.AddDataAddPercent(lv * 10);
		break;
	case 37://防御
		pPetDate->m_DEF.AddDataAddPercent(lv * 5);
		break;
	case 38://高级防御
		pPetDate->m_DEF.AddDataAddPercent(lv * 10);
		break;
	case 39://偷袭  
		pPetDate->m_StabRate.d2 += lv * 50;//反震免疫率
		pPetDate->m_CounterRate.d2 += lv * 50;//反击免疫率
		pPetDate->m_ParryRate.d2 += lv * 50;//反格档
		break;
	case 40://高级偷袭
		pPetDate->m_StabRate.d2 += lv * 100;//反震免疫率
		pPetDate->m_CounterRate.d2 += lv * 100;
		pPetDate->m_ParryRate.d2 += lv * 100;
		break;
	case 41://毒
		pPetDate->poisonRate.d1 += lv * 10;
		break;
	case 42://高级毒
		pPetDate->poisonRate.d1 += lv * 20;
		break;
	case 43://驱鬼
		pPetDate->ghostSpecial.d1 += lv * 50;
		break;
	case 44://高级驱鬼
		pPetDate->ghostSpecial.d1 += lv * 100;
		break;
	case 45://鬼魂术
//		pPetDate->m_DamagePercent.d2 += lv*20;
		pPetDate->m_race += lv * 1020;
		// 		if (lv > 0)
		// 		{
		// 			pPetDate->m_race += 1020;
		// 		}
		// 		else
		// 		{
		// 			pPetDate->m_race -= 1020;
		// 		}
		break;
	case 46://高级鬼魂术
		pPetDate->m_race += lv * 1020;
		//		pPetDate->m_DamagePercent.d2 += lv*30;
		// 		if (lv > 0)
		// 		{
		// 			pPetDate->m_race += 1020;
		// 		}
		// 		else
		// 		{
		// 			pPetDate->m_race -= 1020;
		// 		}
		break;
	case 47://魔之心
		pPetDate->m_DamageAddPercentMagic.d1 += lv * 10;
		break;
	case 48://高级魔之心
		pPetDate->m_DamageAddPercentMagic.d1 += lv * 20;
		break;
	case 49://神佑
		pPetDate->GoldLivePercent.d1 += lv * 20;
		break;
	case 50://高级神佑
		pPetDate->GoldLivePercent.d1 += lv * 35;
		break;
	case 51://精神集中
		pPetDate->m_SealRate.d2 += lv * 10;
		break;
	case 52://高级精神集中
		pPetDate->m_SealRate.d2 += lv * 20;
		break;
	case 53://否定信仰
		pPetDate->GoldLivePercent.d2 += lv * 20;
		break;
	case 54://高级否定信仰
		pPetDate->GoldLivePercent.d2 += lv * 30;
		break;
	case 55://法术连击
		pPetDate->m_MagicComboRate.d1 += lv * 20;
		break;
	case 56://高级法术连击
		pPetDate->m_MagicComboRate.d1 += lv * 30;
		break;
	case 57://法术暴击
		pPetDate->m_MagicCriRate.d1 += lv * 10;
		break;
	case 58://高级法术暴击
		pPetDate->m_MagicCriRate.d1 += lv * 15;
		break;
	case 59://法术波动
		pPetDate->magicWavePercent += lv * 20;
		break;
	case 60://高级法术波动
		pPetDate->magicWavePercent += lv * 35;
		break;
	case 61://迟钝
//		pPetDate->m_DEF.AddDataAddPercent(lv * 20);
		pPetDate->m_SPD.AddDataAddPercent(-lv * 50);
		//		pPetDate->m_HitRate.d2 -= lv * 20;
		//		pPetDate->m_ParryRate.d1 -= lv * 40;
		break;
	case 62://弱点火
		pPetDate->m_MagicFire.d2 -= lv * 30; //火	
		break;
	case 63://弱点水
		pPetDate->m_MagicWater.d2 -= lv * 30;  //水
		break;
	case 64://弱点土
		pPetDate->m_MagicSoil.d2 -= lv * 30; //土
		break;
	case 65://弱点雷
		pPetDate->m_MagicThunder.d2 -= lv * 30;//雷
		break;
	case 66://雷属性吸收
		pPetDate->m_MagicThunder.d2 += lv * 20;//雷
		break;
	case 67://高级雷属性吸收
		pPetDate->m_MagicThunder.d2 += lv * 30;//雷
		break;
	case 68://土属性吸收
		pPetDate->m_MagicSoil.d2 += lv * 20; //土
		break;
	case 69://高级土属性吸收
		pPetDate->m_MagicSoil.d2 += lv * 30; //土
		break;
	case 70://火属性吸收
		pPetDate->m_MagicFire.d2 += lv * 20; //火
		break;
	case 71://高级火属性吸收
		pPetDate->m_MagicFire.d2 += lv * 30; //火
		break;
	case 72://水属性吸收
		pPetDate->m_MagicWater.d2 += lv * 20;  //水
		break;
	case 73://高级水属性吸收
		pPetDate->m_MagicWater.d2 += lv * 30;  //水
		break;
	case 74://移花接木 
		pPetDate->m_HiddenWeaponDamagePercent.d2 += lv * 95;
		break;
	case 75://风刃
		pPetDate->m_Spurting.d1 += lv * 15;
		break;
	case 76://嗜血追击
		pPetDate->ShiXueAdd += lv * 5;
		break;
	case 77://龙鳞防御(盾气)
//		pPetDate->m_DamageAddMagicLv.d2 += lv * 2;//法术伤害结果
// 		pPetDate->m_DamageAddLv.d2	+= lv * 2;  //物理伤害结果
// 		pPetDate->m_DamageAddPercentMagic2.d2 += 10;
// 		pPetDate->m_MagicWater.d2 += lv*20;  //水
		break;
	case 78://龙鳞守护(高级盾气)
//		pPetDate->m_DamageAddMagicLv.d2 += lv * 3;//法术伤害结果
// 		pPetDate->m_DamageAddLv.d2 += lv * 3;  //物理伤害结果
// 		pPetDate->m_DamageAddPercentMagic2.d2 += 15;
// 		pPetDate->m_MagicWater.d2 += lv * 30;  //水
		break;
	case 79://法术抵抗
		pPetDate->m_DamageAddPercentMagic.d2 += lv * 15;
		break;
	case 80://高级法术抵抗
		pPetDate->m_DamageAddPercentMagic.d2 += lv * 25;
		break;
	case 81://直死(合纵，小风华)
//		pPetDate->m_Pierce.d1 += 20;//无视防御率
//		pPetDate->m_PierceMagic.d1+=30; //无视灵力率
		pPetDate->comboNumUp += lv * 1;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 82://风华武圣
		pPetDate->comboNumUp += lv * 3;
		//		pPetDate->m_Combo.d1 += lv * 15;
		break;
	case 83://法术反弹
		pPetDate->m_StabRateMagic.d1 += lv * 35;//法术反震率
		pPetDate->m_StabDamageRateMagic.d1 += lv * 30;//法术反震伤害率
		break;
	}
	return TRUE;
}



BOOL  cSkillManager::CountMagicDamage(int& dam, int UserID, int TargetID, int Damageup, eMagicWuXing wuxing)//计算法术伤害
{
	cPetData*  pUserData;
	cPetData*  pTargetData;
	cObj* pUser = m_pFightState->m_pList[UserID]->m_pData;
	cObj* pTarget = m_pFightState->m_pList[TargetID]->m_pData;
	pUser->GetDateP(pUserData);
	pTarget->GetDateP(pTargetData);

	if (pTargetData->m_FightProperty.m_WallNum > 0)
	{//大地之墙
		pTargetData->m_FightProperty.m_WallNum -= 1;
		dam = 0;
		return TRUE;
	}
	int hit = 100 + pUserData->m_MagicHitRate.d1 - pTargetData->m_MagicHitRate.d2;
	if (rand() % 100 >= hit)//法术回避
	{
		dam = 0;
		return TRUE;
	}

	int wakanUser = pUserData->m_Wakan.GetData();    //自身灵力
	int  wakanTarget = pTargetData->m_Wakan.GetData(); //目标灵力
//	wakanTarget -= pUserData->m_LV<<1;
	// 盾气
	int turn = m_pFightState->m_pList[TargetID]->_myTurn;
	if (pTargetData->CheckHavePetSkill(78) && turn < 5)
	{
		wakanTarget += (5 - turn) * pTargetData->m_LV * 2 / 5;
	}
	else if (pTargetData->CheckHavePetSkill(77) && turn < 5)
	{
		wakanTarget += (10 - turn) * pTargetData->m_LV / 5;
	}
	int& atknum = pTargetData->m_FightProperty.SufferNum;
	////////////////////////////////////////////////////////////////////////// 呵呵哒 又来越被打越无法术格挡
	int pierce = pUserData->m_PierceMagic.d1 + atknum/* * 3*/;
	if (pierce)
	{
		if (pierce > 100)pierce = 100;
		wakanTarget -= (wakanTarget* pierce) / 100; //无视灵力
	}
	int DamageAddPercent = pUserData->m_DamageAddPercentMagic.d1; //自身法术攻击修炼
	int DamageDefPercent = pTargetData->m_DamageAddPercentMagic.d2;   //目标法术防御修炼
	if (DamageDefPercent > 9900)
	{
		DamageDefPercent = DamageAddPercent + DamageDefPercent - 9900;
	}
	dam = (wakanUser)-(wakanTarget)+pUserData->m_LV;

	int 装备伤害分量 = pUserData->m_LV;
	if (pUser->m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter *pc = (cCharacter*)pUser->m_pIndex;
		装备伤害分量 = pc->m_PCData.getEquipAtk() / 5;
	}
	int skillLv = pUser->GetSkillLv(0);
	if (!skillLv)
	{
		skillLv = pUserData->m_LV;
	}
	int targetNum = g_pMainState->m_FightList[UserID].m_MaxTargetNum;
	if (targetNum < 1) targetNum = 1;
	dam = (skillLv * Damageup + wakanUser * 10 - wakanTarget * 10 + 装备伤害分量 * 10) * (21 - targetNum) / 200;
	if (dam < 1)
	{
		dam = 1;
	}
	if (pUserData->CheckHavePetSkill(103))
	{
		// 拥有须弥真言,+魔力*0.4的伤害力
		dam += pUserData->m_ProPertyMag * 2 / 5;
	}
	Damageup = 0;
	int xiuliancha = pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag();
	float damf = (float)dam;
	if (xiuliancha > 0)
	{
		for (int i = 0; i < xiuliancha; ++i)
		{
			damf = damf * 1.02f + 5;
		}
	}
	else
	{
		for (int i = 0; i < (-xiuliancha); ++i)
		{
			damf = damf * 0.98f - 5;
			if (damf < 1)
			{
				damf = 1;
				break;
			}
		}
	}
	dam = (int)damf;
	BOOL bCri = FALSE;
	// 	bool isPc = pUser->m_IndexType == INDEXTYEP_CHARACTER;
	// 	bool isPT = ((cCharacter*)pUser->m_pIndex)->m_PCData.m_MengPaiID == eMengPai::eMP_普陀山;
	// 	if (!isPc || (isPc && isPT))
	// 	{
	// 
	// 	}
	int damageup = -CorrectWuXing(pUserData, pTargetData, wuxing);//五行修正 --> 五行吸收
	if (rand() % 100 < damageup)
	{
		dam = -dam;
	}
	else
	{
		dam = dam * (100 - damageup) / 100;
	}
	if (dam > 1)
	{
		//		Damageup += CorrectWuXing(pUserData, pTargetData, wuxing);//五行修正	
		Damageup += CountSpecial(pUserData, pTargetData, pTarget->GetSex());//特攻修正
		bCri = CountCriMagic(pUserData, pTargetData, dam);//法暴修正

		if (pUserData->magicWavePercent)
		{//法术波动
			dam = dam * (100 + (rand() % pUserData->magicWavePercent) - (rand() % (pUserData->magicWavePercent / 2))) / 100;
		}
		dam = dam * (100 + DamageAddPercent - DamageDefPercent + Damageup) / 100;
		dam += (pUserData->m_DamageAddMagicLv.d1 - pTargetData->m_DamageAddMagicLv.d2) * skillLv/*pUserData->m_LV*/;
		if (rand() % 100 < pUserData->m_XiangMoRate.d1 - pUserData->m_XiangMoRate.d2)dam /= 2;
		if (Damageup > -1)if (dam < 1)dam = 1;
		//	}
		//	else dam = 1;
		CheckFightStateOnLine(TargetID, dam);
		if (pTargetData->m_StabRateMagic.d1)
		{
			//int rate= pTargetData->m_StabRateMagic.d1 - pUserData->m_StabRateMagic.d2;
			if (rand() % 100 < dam)
			{
				int rate = pTargetData->m_StabDamageRateMagic.d1 - pUserData->m_StabDamageRateMagic.d2;
				int dam2 = dam * rate / 100;
				CheckGodLivePercent(dam2, UserID, TargetID); //神佑
				AddHp(UserID, -dam2);
				SetDamage(dam2, UserID);
			}
		}

		if (pTargetData->m_FightProperty.m_bDefend)dam = dam * 4 / 5;//检测是否防御	

		//致伤
		int rate = pUserData->m_MagDownHPHurt.d1 - pTargetData->m_MagDownHPHurt.d2;
		if (rate > 0)AddHpHurt(TargetID, -(dam*rate) / 100);

		CheckGodLivePercent(dam, TargetID, UserID); //神佑
	}
//	asert(dam < 20000, "法术伤害超过2万");
	AddHp(TargetID, -dam);
	SetDamage(dam, TargetID);
	pTargetData->m_FightProperty.SufferNum += 1;
	return bCri;
}
void cSkillManager::CountphysicalDamage(int& dam, int UserID, int TargetID, int Damageup/*=0*/)
{
	cObj* pUser;
	cObj* pTarget;
	cPetData* UserData;
	cPetData* TargetData;
	pUser = m_pFightState->m_pList[UserID]->m_pData;
	pUser->GetDateP(UserData);
	pTarget = m_pFightState->m_pList[TargetID]->m_pData;
	pTarget->GetDateP(TargetData);
	//sFightData& userFightData = UserData->m_FightProperty;
	sFightData& targetFightData = TargetData->m_FightProperty;
	if (TargetData->m_FightProperty.m_WallNum > 0)
	{
		TargetData->m_FightProperty.m_WallNum -= 1;
		dam = 0;
		return;
	}
	int userAtk = UserData->m_ATK.GetData();    //自身攻击
	int SufferDef = TargetData->m_DEF.GetData(); //目标防御
	// 盾气
	int turn = m_pFightState->m_pList[TargetID]->_myTurn;
	if (TargetData->CheckHavePetSkill(78) && turn < 5)
	{
		SufferDef += (5 - turn) * TargetData->m_LV * 2 / 5;
	}
	else if (TargetData->CheckHavePetSkill(77) && turn < 5)
	{
		SufferDef += (10 - turn) * TargetData->m_LV / 5;
	}

	int& atknum = targetFightData.SufferNum;

	////////////////////////////////////////////////////////////////////////// 呵呵哒 越被打格挡越没用
	int picrcerate = UserData->m_Pierce.d1 - TargetData->m_Pierce.d2 + atknum/**3*/;
	bool is壁垒 = false;
	bool is善恶 = false;
	bool is力劈 = false;
	if (Damageup == 10086)
	{
		is力劈 = true;
		Damageup = 0;
		picrcerate += 5;
	}
	if (Damageup == 10087)
	{
		Damageup = 0;
		picrcerate += 10;
		if (TargetData->m_FightProperty.m_bDefend)
		{
			is壁垒 = true;
		}
	}
	if (Damageup == 10088)
	{
		is善恶 = true;
		Damageup = 0;
		picrcerate += 5;
	}
	if (picrcerate > 0)
	{
		SufferDef -= (SufferDef * picrcerate) / 100;//无视防御
	}

	if (is力劈)
	{
		// 力劈华山
		dam += userAtk * 3 - (SufferDef + TargetData->m_ATK.GetData()) * 3 / 2;
	}
	else
	{
		dam += (userAtk)-(SufferDef);
	}
	if (dam < 1)
	{
		dam = 1;
	}
	//修炼和伤害修正
	int xiuliancha = UserData->m_XiuLian.GetAtk() - TargetData->m_XiuLian.GetDef();
	float damf = (float)dam;
	if (xiuliancha > 0)
	{
		for (int i = 0; i < xiuliancha; ++i)
		{
			damf = damf * 1.02f + 5;
		}
	}
	else
	{
		for (int i = 0; i < (-xiuliancha); ++i)
		{
			damf = damf * 0.98f - 5;
			if (damf < 1)
			{
				damf = 1;
				break;
			}
		}
	}
	dam = (int)damf;
	//	asert(dam < 50000, "修炼后伤害超过五万");
	Damageup += CountSpecial(UserData, TargetData, pTarget->GetSex());//特攻修正

	int atk2345 = UserData->ShiXueAdd; //攻击数修正
	if (atk2345 >= 0xffffff)
	{
		atk2345 -= 0xffffff;
	}
	// 	while (atk2345 >= 0xffff)
	// 	{
	// 		atk2345 -= 0xffff;
	// 	}
	atk2345 *= atknum;
	Damageup += atk2345;

	int& userlv = UserData->m_LV;  //自身等级
	dam += dam * Damageup / 100;
	int damp = UserData->m_DamagePercent.d1 - TargetData->m_DamagePercent.d2;
	if (TargetData->m_DamagePercent.d2 > 9900)
	{
		damp = 9900 - TargetData->m_DamagePercent.d2;
	}
	dam = dam * (100 + damp) / 100;

	//必杀修正
	CountCriDamage(UserData, TargetData, dam);
	if (!is善恶 && rand() % 100 < UserData->m_JinJiaRate.d1 - UserData->m_JinJiaRate.d2)dam /= 2;

	//结果修正
	dam += UserData->m_DamageAdd.d1 - TargetData->m_DamageAdd.d2;
	dam += (UserData->m_DamageAddLv.d1 - TargetData->m_DamageAddLv.d2) * userlv;
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
	else if (dam > 0 && TargetData->m_FightProperty.m_bDefend)
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
		CheckFightStateOnLine(TargetID, dam);
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
	SuckBlood(dam, UserID, TargetData);//吸血
	CheckFanZheng(UserID, TargetID, dam);//反震
	//致伤
//	asert(dam < 50000, "保护后超过五万");
	int rate = UserData->m_AtkDownHPHurt.d1 - TargetData->m_AtkDownHPHurt.d2;
	if (rate > 0)AddHpHurt(TargetID, -(dam*rate) / 100);
	//降蓝
	rate = UserData->m_AtkDownMP.d1 - TargetData->m_AtkDownMP.d2;
	if (rate > 0)AddMp(TargetID, -(dam*rate) / 100);
	//降攻
	if (TargetData->m_AtkDownAtk.d1)
	{
		if (TargetData->m_ATK.GetData() > 1)
		{
			rate = UserData->m_AtkDownAtk.d1 - TargetData->m_AtkDownAtk.d2;
			if (rate > 0)
			{
				if (TargetData->m_ATK.GetData() <= rate)rate = TargetData->m_ATK.GetData() - 1;
				TargetData->m_ATK.AddDataAdd(-rate);
			}
		}
	}
	//降防
	if (TargetData->m_AtkDownDef.d1)
	{
		if (TargetData->m_DEF.GetData() > 1)
		{
			rate = UserData->m_AtkDownDef.d1 - TargetData->m_AtkDownDef.d2;
			if (rate > 0)
			{
				if (TargetData->m_DEF.GetData() <= rate)rate = TargetData->m_DEF.GetData() - 1;
				TargetData->m_DEF.AddDataAdd(-rate);
			}
		}
	}
	//降命中
	if (TargetData->m_AtkDownHit.d1)
	{
		if (TargetData->m_HIT.GetData() > 1)
		{
			rate = UserData->m_AtkDownHit.d1 - TargetData->m_AtkDownHit.d2;
			if (rate > 0)
			{
				if (TargetData->m_HIT.GetData() <= rate)rate = TargetData->m_HIT.GetData() - 1;
				TargetData->m_HIT.AddDataAdd(-rate);
			}
		}
	}
	//降灵
	if (TargetData->m_AtkDownWakan.d1)
	{
		if (TargetData->m_Wakan.GetData() > 1)
		{
			rate = UserData->m_AtkDownWakan.d1 - TargetData->m_AtkDownWakan.d2;
			if (rate > 0)
			{
				if (TargetData->m_Wakan.GetData() <= rate)rate = TargetData->m_Wakan.GetData() - 1;
				TargetData->m_Wakan.AddDataAdd(-rate);
			}
		}
	}
	//降速
	if (TargetData->m_AtkDownSpd.d1)
	{
		if (TargetData->m_SPD.GetData() > 1)
		{
			rate = UserData->m_AtkDownSpd.d1 - TargetData->m_AtkDownSpd.d2;
			if (rate > 0)
			{
				if (TargetData->m_SPD.GetData() <= rate)rate = TargetData->m_SPD.GetData() - 1;
				TargetData->m_SPD.AddDataAdd(-rate);
			}
		}
	}

	//降CP
	if (TargetData->m_AtkDownCP.d1)
	{
		rate = UserData->m_AtkDownCP.d1 - UserData->m_AtkDownCP.d2;
		if (rate > 0)UserData->m_CP -= rate;
		if (UserData->m_CP < 0)UserData->m_CP = 0;
	}

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



void cSkillManager::EffectSkill(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (TargetID == -1)return;
	sFightList* pUserList = m_pFightState->m_pList[UserID];
	cObj* pTarget = m_pFightState->m_pList[TargetID]->m_pData;
	cObj* pUser = m_pFightState->m_pList[UserID]->m_pData;
	cPetData* pTargetData;
	cPetData* pUserData;
	sBuff buf;
	buf.times = -999;

	pTarget->GetDateP(pTargetData);
	pUser->GetDateP(pUserData);
	int& userlv = pUserData->m_LV;
	int& targetlv = pTargetData->m_LV;
	int dam = 0;

	switch (sSkillID)
	{
	case 50:return;
		//	case 2095:return;
	case 1050:
		CountphysicalDamage(dam, UserID, TargetID/*, 30*/);
		if ((rand() % 100) < 80)
		{
			buf.times = 2 + rand() % 4;
			SetDateBuffUp(UserID, TargetID, 50, buf, Skilllv);
			buf.times = -999;
		}
		break;
	case 1095://力劈
	{
		CountphysicalDamage(dam, UserID, TargetID, 10086);
	}
	break;
	case 2101://空间震

	{
		pUserData->m_PierceMagic.d1 += 80;
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX光);
		pUserData->m_PierceMagic.d1 -= 80;
	}
	break;
	case 3040://破碎
		CountphysicalDamage(dam, UserID, TargetID, 0);
		AddMp(TargetID, -dam);
		break;
	case 3035://弱点
		pUserData->m_Pierce.d1 += 40;
		CountphysicalDamage(dam, UserID, TargetID, 0);
		pUserData->m_Pierce.d1 -= 40;
		break;
	case 3043://弱点EX
		pUserData->m_Pierce.d1 += 80;
		CountphysicalDamage(dam, UserID, TargetID, 0);
		pUserData->m_Pierce.d1 -= 80;
		break;
	case 3034://破血
		pUserData->m_Pierce.d1 += 5;
		CountphysicalDamage(dam, UserID, TargetID, 50);
		pUserData->m_Pierce.d1 -= 5;
		break;
	case 3042://破血2
	case 3044://破血EX
		pUserData->m_Pierce.d1 += 5;
		CountphysicalDamage(dam, UserID, TargetID, 0);
		pUserData->m_Pierce.d1 -= 5;
		break;
	case 147://定心
		buf.times = 8;
		break;
	case 1007://乾坤袋

	{
		cObj* target = g_pMainState->m_FightList[TargetID].m_pData;
		string targetname = target->m_TrueName.GetString();
		if (0 == targetname.compare(g_pMainState->m_taskSM.m_Npc.m_name))
		{
			cPetData* pData;
			target->GetDateP(pData);
			if (pData->m_HP < (pData->m_HPMax.GetData()) / 2)
			{
				if (rand() % 3 < 2)
				{
					dam = pData->m_HP;
					AddHp(TargetID, -dam);
					SetDamage(dam, TargetID);
					g_pMainState->m_taskSM.m_bXiangFuSuccess = TRUE;
				}
			}

		}
	}
	break;
	case 0://横扫千军
	{
		int damageup;
		switch (pUserList->m_NowTarget)
		{
		case 0:
			damageup = 0;
			break;
		case 1:// 攻击者攻击-目标防御 120%的伤害
			damageup = 5;
			break;
		case 2:// 攻击者攻击-目标防御  并有10%的波动  150%的伤害
			damageup = 10;
			break;
		default:
			damageup = 15;
			break;
		}
		CountphysicalDamage(dam, UserID, TargetID, damageup);
	}
	break;
	case 1: // 后发
		SetDateBuffUp(TargetID, UserID, sSkillID, buf, Skilllv);
		buf.times = -999;
		break;
	case 7: // 破斧
	{
		CountphysicalDamage(dam, UserID, TargetID, -95);
	}
	break;
	case 1017:// 破斧?????????????????
		CountphysicalDamage(dam, UserID, TargetID, 60);
		break;
	case 8://安神诀
		buf.times = 8;
		break;
	case 1010: // 后发
	{
		CountphysicalDamage(dam, UserID, TargetID, 150);
		pUser->ReMoveStateID(1);
	}
	break;
	case 4://杀气诀
		buf.times = 8;
		break;
	case 11://五雷咒
	case 28://落雷符
	{
		pUserData->ghostSpecial.d1 += 100;
		int dadd = pUserData->m_DEF.GetData() >> 4;
		pUserData->m_Wakan.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 20/*20 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 5,eMWX雷*/);
		pUserData->ghostSpecial.d1 -= 100;
		pUserData->m_Wakan.AddDataOriginal(-dadd);
	}
	break;
	case 13:
	{
		m_pFightState->m_pList[UserID]->isLive = FALSE;
		if (UserID == g_pMainState->m_HeroID)
			m_pFightState->m_bEscape = TRUE;
	}
	break;
	case 6: //反间计
	case 14://催眠符
	case 15://失心符
	case 17://失忆
	case 18://追魂
	case 19://离魂
	case 20://失魂
	case 21://定身
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 16://落魄
		buf.times = 2;
		buf.times += (Skilllv - targetlv) / 10;
	case 22://归元咒
		dam = Skilllv * 2 + 100;
		CorrectCureHP(dam, UserID, UserID);//治疗修正
		SetDamage(-dam, TargetID);
		break;
	case 23://凝神术
		SetDamage(-20, TargetID);
		CorrectCureMP(dam = Skilllv * 2, UserID, UserID);//治疗修正
//		AddMp(TargetID, (Skilllv + 30));
		break;
	case 26://分身术
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 27://碎甲符
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 31://唧唧歪歪

	{
		int dadd = pUserData->m_DEF.GetData() >> 4;
		pUserData->m_Wakan.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 20/*15 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4*/);
		pUserData->m_Wakan.AddDataOriginal(-dadd);
	}
	break;
	case 33:  //金刚护法

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 34:    //韦陀护法  
	case 35:  //金刚护体
	case 36:     //一苇渡江

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	}
	case 37:     //我佛慈悲
		Resurgence(TargetID);
		AddHpHurt(TargetID, (Skilllv * 12));
		dam = (Skilllv * 10);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 38:     //推拿
		dam = Skilllv * 12;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正

		break;
	case 39:    //活血
		dam = Skilllv * 12;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正

		break;
	case 40:    //推气过宫
		dam = Skilllv * 8;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 41:    //妙手回春
		AddHpHurt(TargetID, (Skilllv * 8));
		break;
	case 42:    //救死扶伤
		AddHpHurt(TargetID, dam = Skilllv * 8);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 43://解毒
		pTarget->ReMoveState(eBuffType毒);
		dam = Skilllv * 3;
		//		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 45://舍身
		AddHpHurt(TargetID, 100, (1 << 14));
		dam = -AddHp(TargetID, 100, (1 << 14));
		SetDamage(dam, TargetID);
		break;
	case 46:    //佛法无边

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 49:    //楚楚可怜

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 54:    //似玉生香

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 59:    //一笑倾城

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 63:    //天神护法

	{
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 66:	//宁心
		pUser->ReMoveState(eBuffType负面);
		break;
	case 67:    //镇妖 

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 68:    //错乱
	case 69:    //百万神兵

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 71://天雷斩
	case 98:
	{
		int dadd = pUserData->m_DEF.GetData() >> 3;
		pUserData->m_ATK.AddDataOriginal(dadd);
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->m_ATK.AddDataOriginal(-dadd);
	}
	break;
	case 72://五雷轰顶

	{
		int rate = (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag())/**2*/;
		int offset = Skilllv - pTargetData->m_LV;
		rate = 70 + rate + offset;
		if (rand() % 100 < rate)
			dam = pTargetData->m_HP / 4;
		else dam = pTargetData->m_HP / 20;
		if (dam > (pUserData->m_LV * 50))dam = pUserData->m_LV * 50;
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
	}
	break;
	case 74://雷霆万钧
	{
		int dadd = pUserData->m_DEF.GetData() >> 4;
		pUserData->m_Wakan.AddDataOriginal(dadd);
		CountMagicDamage(dam, UserID, TargetID, 25/*20 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 8,eMWX雷*/);
		pUserData->m_Wakan.AddDataOriginal(-dadd);
	}
	break;
	case 119://寡欲令
	case 77: //解封

	{
		m_pFightState->ReMoveSealState(TargetID);
	}
	break;
	case 79://龙腾
		CountMagicDamage(dam, UserID, TargetID, 25/*40 + Skilllv / 5*/, eMWX水);
		break;
	case 80://龙卷雨击
		CountMagicDamage(dam, UserID, TargetID, 20/*25 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4,eMWX雷水*/);
		break;
	case 81://逆鳞
		buf.times = 8;
		break;
	case 84: //龙呤
		dam = Skilllv + 10;
		CountMagic2Damage(dam, UserID, TargetID/*, eMWX水*/);
		AddMp(TargetID, -dam);
		break;
	case 88://二龙
		CountMagicDamage(dam, UserID, TargetID, 30/*30 + Skilllv / 5 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4,eMWX水*/);
		break;
	case 89://日月乾坤

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
	}
	break;
	case 90: //炼气化神

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		dam = Skilllv;
		CorrectCureMP(dam, UserID, TargetID);
		buf.damage = dam;
		SetDamage(30, UserID);
	}
	break;
	case 91://生命之泉

	{
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		dam = Skilllv * 2 + 120;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		buf.damage = dam;
	}
	break;
	case 94:   //三花聚顶
		dam = (Skilllv * 4 + 50);
		CorrectCureMP(dam, UserID, TargetID);
		//		SetDamage(30, UserID);
		break;
	case 97: //烟雨
	{
		int dadd = pUserData->m_DEF.GetData() >> 3;
		pUserData->m_ATK.AddDataOriginal(dadd);
		CountphysicalDamage(dam, UserID, TargetID);
		pUserData->m_ATK.AddDataOriginal(-dadd);
	}
	break;
	case 102://普渡众生
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		dam = Skilllv * 5;
		buf.damage = dam;
		buf.damage2 = dam;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 103://紧箍咒
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		buf.damage = (Skilllv * 3 + pTargetData->m_HPMax.GetData() / 20) * (100 + pUserData->m_DamageAddPercentMagic.d1) / 100;
		if (buf.damage > pUserData->m_LV * 15)
		{
			buf.damage = pUserData->m_LV * 15;
		}
		break;
	case 104://杨柳甘露
		Resurgence(TargetID);
		dam = Skilllv * Skilllv / 144 + Skilllv * 5;
		dam *= 2;
		AddHpHurt(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case	105:// 日光华
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX光);
		break;
	case	106:// 靛沧海
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX水);
		if (rand() % 20 == 0)
		{
			m_pFightState->m_pList[TargetID]->m_WorkType = -1;
		}
		break;
	case	107:// 巨岩破
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX土);
		if (rand() % 8 == 0)
		{
			AddCp(TargetID, -dam / 30);
		}
		break;
	case	108:// 苍茫树
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID);
		if (rand() % 10 == 0)
		{
			AddMp(UserID, -dam / 10);
		}
		break;
	case	109:// 地裂火
		dam = (Skilllv * 4 + 100) * 13 / 10 * (23 - g_pMainState->m_FightList[UserID].m_MaxTargetNum) / 20;
		CountMagic2Damage(dam, UserID, TargetID, eMWX火);
		if (rand() % 20 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 112://灵动
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 113://五行颠倒
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 115://自在心法
		if (pTarget->m_StateList.size())
		{
			int d = 0;
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
				if (Iterator->ID == 102)
				{
					int mpadd = Iterator->times;
					if (mpadd <= 1)
					{
						mpadd *= Iterator->damage * 2;
					}
					else
					{
						mpadd *= Iterator->damage * 5 / 4;
					}

					if (mpadd > d) d = mpadd;
					g_pMainState->m_SkillManager.SetDateBuffDown(Iterator);// it2->targetID, it2->ID);
					Iterator->data.Free();
					pTarget->m_StateList.erase(Iterator++);
				}
				else
				{
					++Iterator;
				}
			}
			if (d > 0)
			{
				AddHpHurt(TargetID, d);
				AddHp(TargetID, d);
				SetDamage(-d, TargetID);
			}

		}
		break;
	case 116://阎罗令
		dam = (Skilllv * 3 / 2 + 30) * 13 / 10 * 2;
		CountMagic2Damage(dam, UserID, TargetID);
		AddHpHurt(TargetID, -(Skilllv * 3 / 2 + 30));
		break;
	case 117://判官令
		dam = (Skilllv * 3 + 75) * 13 / 10 * 3 / 2;
		CountMagic2Damage(dam, UserID, TargetID);
		AddMp(TargetID, -(Skilllv * 3 + 75));
		break;
	case 120://鬼眼
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 122://尸腐毒
	{
		if (pTarget->CheckHaveState(sSkillID))return;
		if (pTargetData->m_race == 5 || pTargetData->m_race == 6 || pTargetData->m_race >= 1000)return;//机械和鬼不会中毒
// 			int Poision = pUserData->poisonRate.d1 - pUserData->poisonRate .d2 + 80; //中毒率
// 			if (rand() % 100 < Poision)
		{
			sBuff buf;
			buf.damage = pUserData->m_DamageAddPercentPoision.d1 - pTargetData->m_DamageAddPercentPoision.d2;//中毒伤害修正
			buf.times = 3 + (Skilllv - targetlv) / 25;
			SetDateBuffUp(UserID, TargetID, sSkillID, buf);
			buf.times = -999;
			dam = pTargetData->m_HP / 10 + Skilllv;
			if (dam > userlv * 15)
			{
				dam = userlv * 15;
			}
			AddHp(TargetID, -dam);
			SetDamage(dam, TargetID);

			cPetData* pPet;
			int randstart, randend;
			if (UserID < 10)randstart = 0; else randstart = 10;
			randend = randstart + 10;
			for (int i = randstart; i < randend; i++)
			{
				sFightList& list = g_pMainState->m_FightList[i];
				if (!list.isLive)continue;
				list.m_pData->GetDateP(pPet);

				if (pPet->m_HP < 1)continue;
				int d = dam * 4 / 5;
				if (d > Skilllv * 5 + 180)
				{
					d = Skilllv * 5 + 180;
				}
				AddHp(i, d);
				SetDamage(-d, i);
			}
		}
	}
	break;
	case 123:   //修罗隐身
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 125:
		Resurgence(TargetID);
		AddHpHurt(TargetID, Skilllv * 10);
		dam = Skilllv * 9;
		//		AddHp(TargetID, dam);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 126:
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 127:// 魂飞魄散
		pTarget->ReMoveState(eBuffType增益);
		break;
	case 129:
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 25;
		// 锢魂术
		break;
	case 131://飞砂走石
		CountMagicDamage(dam, UserID, TargetID, 30/*25 + Skilllv / 4 - (m_pFightState->m_pList[UserID]->m_MaxTargetNum - 1) * 4, eMWX土*/);
		break;
	case	132:// 三昧真火
		CountMagicDamage(dam, UserID, TargetID, 35/*70 + Skilllv / 4, eMWX火*/);
		break;
	case 133://牛劲
		buf.times = 8;
		break;
	case 141://象形
		CountphysicalDamage(dam, UserID, TargetID, 50);
		pUser->ReMoveStateID(145);//取消变身
		buf.times = 1;
		SetDateBuffUp(UserID, TargetID, sSkillID, buf);
		buf.times = -999;
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
		CountphysicalDamage(dam, UserID, TargetID, 160);
		break;
	case	144:// 威慑
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 25;
		break;
	case 145://变身
		buf.times = 5;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 148:// 连环击
		CountphysicalDamage(dam, UserID, TargetID, 15 - pUserData->m_FightProperty.AttackNum * 5);
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
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 152:
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 154://勾魂
	{
		dam = pTargetData->m_HPMax.GetData() / 20;
		dam += Skilllv * 3;
		dam = dam * (100 - pTargetData->m_DamageAddPercentMagic2.d2) / 100;
		if (dam > userlv * 20)
		{
			dam = userlv * 20;
		}
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
		CorrectCureHP(dam, UserID, UserID);//治疗修正
	}
	break;
	case 155://摄魄
// 		dam = -AddMp(TargetID, -5, userlv * 100);
// 		dam += -AddMp(TargetID, -Skilllv * 2);
		dam = pTargetData->m_MPMax.GetData() / 20;
		dam += Skilllv * 3;
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
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 159://含情脉脉
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 160:// 盘丝阵
		buf.times = 3;
		buf.times += (Skilllv - targetlv) / 5;
		break;
	case 161: //复苏
		m_pFightState->ReMoveSealState(UserID);
		m_pFightState->ReMoveDeBuffState(UserID);
		m_pFightState->ReMovePoisionState(UserID);
		break;
	case 162:  //天罗地网
		dam = Skilllv * 2 + (pUserData->m_ATK.GetData() / 5);
		dam = dam * 5 / 3;
		CountMagic2Damage(dam, UserID, TargetID);
		if (rand() % 100 < 10)
		{
			buf.times = rand() % 3 + 1;
		}
		break;
	case 164://姐妹同心
		dam = AddMp(TargetID, -10, userlv * 100);
		dam += AddMp(TargetID, Skilllv * 5);
		dam = 0;
		break;
	case 166://幻镜术
		buf.times = 3;
		buf.times += (Skilllv - userlv) / 5;
		break;
	case 1001://抓捕

	{
		if (!pTargetData->m_Controler.CheckGrab())
		{
			g_pMainState->m_Channel.AddNewString("该对象无法抓捕");
			return;
		}
		cCharacter* pc1 = (cCharacter*)pUser->m_pIndex;
		if (pc1->m_PCData.m_NumofBB > 7)
		{
			g_pMainState->m_Tags.Add("召唤兽数量达到上限");
			break;
		}
		if ((rand() % 100) > 50)
		{

			m_pFightState->BackFromFight(TargetID);
			cPet* pPet = (cPet*)pTarget->m_pIndex;
			pc1->m_PCData.GetPet(pPet);
			pTarget->m_pIndex = 0;
			pTarget->m_IndexType = 0;
		}
	}
	break;
	case 2084:  //雷击
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX雷);
		break;
	case 2085://奔雷咒
		CountMagicDamage(dam, UserID, TargetID, 20/*35 - pUserList->m_NowTarget * 5*/, eMWX雷);
		break;
	case 2086: //落岩
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX土);
		if (rand() % 5 == 0)
		{
			AddCp(TargetID, -20);
		}
		break;
	case 2087: //泰山压顶
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX土);
		if (rand() % 10 == 0)
		{
			AddCp(TargetID, -20);
		}
		break;
	case 2088: //水攻
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX水);
		if (rand() % 15 == 0)
		{
			m_pFightState->m_pList[TargetID]->m_WorkType = -1;
		}
		break;
	case 2089: //水漫金山
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX水);
		if (rand() % 30 == 0)
		{
			m_pFightState->m_pList[TargetID]->m_WorkType = -1;
		}
		break;
	case 2090: //烈火
		CountMagicDamage(dam, UserID, TargetID, 20, eMWX火);
		if (rand() % 10 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 2091: //地狱烈火
		CountMagicDamage(dam, UserID, TargetID, 20/*30 - pUserList->m_NowTarget * 5*/, eMWX火);
		if (rand() % 20 == 0)
		{
			AddHpHurt(TargetID, -dam / 10);
		}
		break;
	case 2092://惊心一剑
		CountphysicalDamage(dam, UserID, TargetID/*, -10*/);
		AddMp(TargetID, -dam / 4 - userlv / 3);
		buf.times = 1;
		break;
	case 2094://死亡召唤
		CountphysicalDamage(dam, UserID, TargetID);
		if (rand() % 100 < 15)
			buf.times = 10;
		break;
	case 2093://夜舞倾城
		buf.times = 3;
		dam = pUserData->m_ProPertyAtk * 3 / 2 + pUserData->m_SPD.GetData() / 3;
		AddHp(TargetID, -dam);
		SetDamage(dam, TargetID);
		break;
	case 2095://力劈华山
		SetDateBuffUp(UserID, UserID, sSkillID, buf, Skilllv);
		buf.times = -999;
		break;
	case 2096: //剑荡四方
		CountphysicalDamage(dam, UserID, TargetID, -35);
		break;
	case 2097:// 法术防御
		buf.times = 6;
		break;
	case 2098://善恶有报
		CountphysicalDamage(dam, UserID, TargetID, 10088);
		break;
	case 2099://壁垒击破
		CountphysicalDamage(dam, UserID, TargetID, 10087);
		break;
	case 2100://苍鸾怒击
		CountphysicalDamage(dam, UserID, TargetID, 100);
		break;
	case 2105: //月光
		pUserData->m_DamageAddPercentMagic.d1 -= pUserData->m_FightProperty.AttackNum * 20;
		//		pUserData->m_MagicCriRate.d1 -= pUserData->m_FightProperty.AttackNum * 5;
		CountMagicDamage(dam, UserID, TargetID, 35);
		pUserData->m_DamageAddPercentMagic.d1 += pUserData->m_FightProperty.AttackNum * 20;
		//		pUserData->m_MagicCriRate.d1 += pUserData->m_FightProperty.AttackNum * 5;
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
		dam += 240;
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
		dam = CountHPPercent(pTargetData, 50, userlv);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 3005:  //气归
	case 3007: //四海升平
		dam = CountHPPercent(pTargetData, 30, userlv / 2);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		break;
	case 3008://回魂咒
		Resurgence(TargetID);
		dam = CountHPPercent(pTargetData, 20, userlv);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		AddHpHurt(TargetID, dam);
		break;
	case 3009: //起死回生
		Resurgence(TargetID);
		dam = CountHPPercent(pTargetData, 50, userlv);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		AddHpHurt(TargetID, dam);
		break;
	case 3012://玉清
	case 3010://水清
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		break;
	case 3011://冰清
	case 3013://晶清
		dam = CountHPPercent(pTargetData, 20, userlv / 2);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		break;
	case 3016://笑里藏刀
		AddCp(TargetID, -70);
		break;
	case 3017://绝幻魔音
		AddCp(TargetID, -30);
		break;
	case 3018://野兽	
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 2))
			pTargetData->m_ATK.AddDataAddPercent(10);
		break;
	case 3019://魔兽之印
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 1))
			pTargetData->m_ATK.AddDataAddPercent(5);
		break;
	case 3020://光辉
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 2))
			pTargetData->m_DEF.AddDataAddPercent(10);
		break;
	case 3021://圣灵
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 1))
			pTargetData->m_DEF.AddDataAddPercent(5);
		break;
	case 3022://流云
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 2))
			pTargetData->m_SPD.AddDataAddPercent(10);
		break;
	case 3023://啸风
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 1))
			pTargetData->m_SPD.AddDataAddPercent(5);
		break;
	case 3024://太极护法
		buf.times = 4;
		break;
	case 3025://罗汉金钟
		buf.times = 4;
		break;
	case 3026://修罗咒
		buf.times = 4;
		break;
	case 3027://天衣无缝
		buf.times = 4;
		break;
	case 3028://放下屠刀
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 8))
		{
			pTargetData->m_FightProperty.m_AtkIntensify += 8;
			pTargetData->m_ATK.AddDataAddPercent(-10);
		}
		break;
	case 3029://牌山压制
		if (!(pTargetData->m_FightProperty.m_AtkIntensify && 4))
		{
			pTargetData->m_FightProperty.m_AtkIntensify += 4;
			pTargetData->m_ATK.AddDataAddPercent(-5);
		}
		break;
	case 3030://破甲术
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 8))
		{
			pTargetData->m_FightProperty.m_DefIntensify += 8;
			pTargetData->m_DEF.AddDataAddPercent(-10);
		}
		break;
	case 3031://碎甲术
		if (!(pTargetData->m_FightProperty.m_DefIntensify && 4))
		{
			pTargetData->m_FightProperty.m_DefIntensify += 4;
			pTargetData->m_DEF.AddDataAddPercent(-5);
		}
		break;
	case 3032://凝滞术
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 8))
		{
			pTargetData->m_FightProperty.m_SpdIntensify += 8;
			pTargetData->m_SPD.AddDataAddPercent(-10);
		}
		break;
	case 3033://停陷术
		if (!(pTargetData->m_FightProperty.m_SpdIntensify && 4))
			pTargetData->m_SPD.AddDataAddPercent(-5);
		break;
	case 3038://星杯圣域
		pTargetData->m_FightProperty.m_WallNum = 2;
		break;
	case 3039://命疗术EX

	{
		dam = CountHPPercent(pTargetData, 50, userlv);
		dam += 1000;
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
	}
	break;
	case 3046://大地之墙
		pTargetData->m_FightProperty.m_WallNum = 1;
		break;
	case 3047://心如明镜
		buf.times = 5;
		break;
	case 3048://慈航普度
		Resurgence(TargetID);
		dam = CountHPPercent(pTargetData, 100, userlv << 3);
		AddHpHurt(TargetID, 100, 10000);
		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		pTarget->ReMoveState(eBuffType封印);
		pTarget->ReMoveState(eBuffType毒);
		pTarget->ReMoveState(eBuffType负面);
		// 		Resurgence(TargetID);
		// 		dam = CountHPPercent(pTargetData, 50, userlv);
		// 		CorrectCureHP(dam, UserID, TargetID);//治疗修正
		// 		AddHpHurt(TargetID, dam);

		break;
	case 3049://迅疾如风
		buf.times = 5;
		break;
	case 2102:
		CountParry(pUserData, pTargetData);//格挡
		CountCri(pUserData, pTargetData);//必杀
		CountphysicalDamage(dam, UserID, TargetID, 80);
		break;
	default:
		ERRBOX2(sSkillID);
		return;
	}
	if (buf.times != -999)
	{
		if (buf.times < 1)buf.times = 1;
		if (buf.times > 1)
		{
			if (UserID < 10 && TargetID < 10)
				buf.times += pTargetData->buffAdd;
			else
				if (TargetID > 9 && UserID > 10)
					buf.times += pTargetData->buffAdd;
		}
		SetDateBuffUp(UserID, TargetID, sSkillID, buf, Skilllv);
	}
}


BOOL cSkillManager::CheckMagicHit(int Skilllv, int sSkillID, int UserID, int TargetID)
{//法术的命中
	cPetData* pUserData;
	cPetData* pTargetData;
	g_pMainState->m_FightList[UserID].m_pData->GetDateP(pUserData);
	g_pMainState->m_FightList[TargetID].m_pData->GetDateP(pTargetData);
	if (abs(UserID - TargetID) >= 10 && pUserData->PeopleSpecial.d1 - pTargetData->PeopleSpecial.d2 < 0)
	{
		return FALSE;
	}

	int rate = 0;
	auto func = [&]()
	{
		if (pTargetData->m_race >= 1000)
		{
			rate -= 999;
		}
		else
		{
			if (!Skilllv)
			{
				Skilllv = pUserData->m_LV;
			}
			rate += (pUserData->m_XiuLian.GetMag() - pTargetData->m_XiuLian.GetDMag());
			//封印法术命中
			rate += pUserData->m_SealRate.d1 - pTargetData->m_SealRate.d2 + ((Skilllv - pTargetData->m_LV) >> 1);
		}
	};
	switch (sSkillID)
	{
		//召唤兽法术
	case 2084:
	case 2085:
	case 2086:
	case 2087:
	case 2088:
	case 2089:
	case 2090:
	case 2091:
		// 落雷符
	case 28:
		// 唧唧歪歪
	case 31:
		// 雷霆万钧
	case 74:
		//五形法术
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
		// 阎罗判官
	case 116:
	case 117:
		//魔王
	case 131:
	case 132:
		// 天罗地网
	case 162:
		rate += 100;
		//法术命中率
		rate += pUserData->m_MagicHitRate.d1 - pTargetData->m_MagicHitRate.d2;
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
		rate += 50;
		func();
		break;
		//女儿
	case 54:rate += 50; func(); break;//似玉生香
	case 59:rate += 30; func(); break;
		//天宫
	case 67:rate += 50; func(); break;
	case 68:rate += 50; func(); break;
	case 69:rate += 50; func(); break;
		//五庄
	case 89:rate += 50; func(); break;
		//地府
	case 122:rate += 85; func(); break;
	case 127:rate += 75; func(); break;
	case 129:rate += 35; func(); break;
		//ST
	case 144:rate += 50; func(); break;
		//PS
	case 154:rate += 95; func(); break; // 勾魂
	case 155:rate += 95; func(); break; // 摄魄
	case 156:rate += 50; func(); break; // 魔音
	case 159:rate += 50; func(); break; // 含情
	case 164:rate += 50; func(); break; // 姐妹
// 		if (pUserData->m_Popularity - pTargetData->m_Popularity >= 50)
// 		{
// 			rate += (pUserData->m_Popularity - pTargetData->m_Popularity) / 50;
// 		}
		break;
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
	case 201: //叶隐
		rate = 60 + (Skilllv >> 1);
		break;
	default:
		return TRUE;
	}
	return (rand() % 100) < rate;
}



void cMengPaiManager::lvUpMainSkill(cPCData& pcDate, int lv, int ID, bool isHero /* = false */)
{
	if (ID > 7 || ID < 0)return;
	if (pcDate.m_MengPaiID < 0 || pcDate.m_MengPaiID>11)return;
	cZhuJiNeng* pZhuJiNeng = &m_MengPai[pcDate.m_MengPaiID].m_MainSkill[ID];
	int& skilllv = pcDate.m_MengPaiSkillLV[ID];
	int prelv = skilllv;
	int nextlv = prelv + lv;
	if (!ID && !isHero)
	{
		switch (pcDate.m_MengPaiID)
		{
		case 0://大唐
			//		switch (ID)
			//		{
			// 		case 0:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 1:pcDate.AddSpdZZ(lv);break;
			// 		case 2:pcDate.AddHpZZ(7 * lv); break;
			// 		case 3:pcDate.AddAvoidZZ(lv); break;
			// 		case 4:
			// 			pcDate.AddGrowing(-prelv/10);
			// 			pcDate.AddGrowing(nextlv /10); 
			// 			break;
			// 		case 5:pcDate.AddDefZZ(3 * lv); break;
			// 		case 6:pcDate.AddMagZZ(2 * lv); break;
			//		}
// 			pcDate.m_Spurting.d1 -= prelv / 10;
// 			pcDate.m_Spurting.d1 += nextlv / 10;
			pcDate.m_Pierce.d1 -= prelv / 13;
			pcDate.m_Pierce.d1 += nextlv / 13;
			break;
		case 1://化生
			//		switch (ID)
			//		{
			// 		case 0:pcDate.AddSpdZZ( lv); break;
			// 		case 1:pcDate.AddAtkZZ( lv); break;
			// 		case 2:pcDate.AddMagZZ(3 * lv); break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv /10);
			// 			pcDate.AddGrowing(nextlv /10);
			// 			break;
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:pcDate.AddHpZZ(10 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ( lv); break;
			//		}

			pcDate.m_CureCriRate.d1 -= prelv / 10;
			pcDate.m_CureCriRate.d1 += nextlv / 10;
			break;
		case 2://女儿
			//		switch (ID)
			//		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:pcDate.AddAvoidZZ(3 * lv); break;
			// 		case 2:pcDate.AddDefZZ(2 * lv); break;
			// 		case 3:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 4:
			// 			pcDate.AddHpZZ(5 * lv);
			pcDate.m_SPD.AddDataAddPercent(-prelv / 20);
			pcDate.m_SPD.AddDataAddPercent(nextlv / 20);
			// 			break;
			// 		case 5:pcDate.AddMagZZ(2 * lv); break;
			// 		case 6:pcDate.AddSpdZZ(3 * lv); break;
			//		}
			break;
		case 3://方寸
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddDefZZ(lv); break;
			// 		case 1:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.ghostSpecial.d1 -= prelv / 4;
			pcDate.ghostSpecial.d1 += nextlv / 4;
			// 			break;
			// 		case 2:
			// 			pcDate.AddMagZZ(lv); 
			pcDate.MonsterSpecial.d1 -= prelv / 4;
			pcDate.MonsterSpecial.d1 += nextlv / 4;
			// 			break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 4:pcDate.AddHpZZ(7 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}
			break;
		case 4:  //狮驼
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddDefZZ(lv); break;
			// 		case 1:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 2:pcDate.AddHpZZ(10 * lv); break;
			// 		case 3:pcDate.AddMagZZ(3 * lv); break;
			// 		case 4:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 5:pcDate.AddAvoidZZ(lv); break;
			// 		case 6:pcDate.AddSpdZZ(lv); break;
			// 		}
			pcDate.m_SuckBloodRate.d1 -= prelv / 20;
			pcDate.m_SuckBloodRate.d1 += nextlv / 20;
			break;
		case 5://魔王
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			pcDate.m_MagicCriRate.d1 -= prelv / 15;
			pcDate.m_MagicCriRate.d1 += nextlv / 15;
			// 			break;
			// 		case 1:pcDate.AddMagZZ(5 * lv); break;
			// 		case 2:
			// 			pcDate.AddSpdZZ(-prelv / 2);
			// 			pcDate.AddSpdZZ(nextlv/2); 
			pcDate.m_MagicFire.d2 -= prelv / 10;
			pcDate.m_MagicFire.d2 += nextlv / 10;
			// 			break;
			// 		case 3:
			// 			pcDate.AddAtkZZ(2 * lv); 
			pcDate.m_MagicFire.d1 -= prelv / 10;
			pcDate.m_MagicFire.d1 += nextlv / 10;
			// 			break;
			// 		case 4:
			// 			pcDate.AddHpZZ(9 * lv);
			// 			break;
			// 		case 5:
			// 			pcDate.AddDefZZ(lv);
			pcDate.m_CounterRate.d1 -= prelv / 5;
			pcDate.m_CounterRate.d1 += nextlv / 5;
			// 			break;
			// 		case 6:
			// 			pcDate.AddAvoidZZ(-prelv / 2);
			// 			pcDate.AddAvoidZZ(nextlv/2); 
			// 			break;
			// 		}
			break;
		case 6://盘丝
			// 			switch (ID)
			// 			{
			// 			case 0:
			// 				pcDate.AddDefZZ(2* lv); 
			pcDate.m_HiddenWeaponDamagePercent.d2 -= prelv / 4;
			pcDate.m_HiddenWeaponDamagePercent.d2 += nextlv / 4;
			// 				break;
			// 			case 1: pcDate.AddMagZZ(4 * lv); break;
			// 			case 2:pcDate.AddHpZZ(7 * lv); break;
			// 			case 3:
			// 				pcDate.AddGrowing(-prelv / 10);
			// 				pcDate.AddGrowing(nextlv / 10);
			// 				break;
			// 			case 4:
			// 				pcDate.AddAtkZZ(3 * lv); break;	
			// 				break;
			// 			case 5:pcDate.AddAvoidZZ(3 * lv); break;
			// 			case 6:pcDate.AddSpdZZ(2* lv); break;
			// 			}
			break;
		case 7://地府
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			pcDate.m_SealRate.d2 -= prelv / 10;
			pcDate.m_SealRate.d2 += nextlv / 10;
			// 			break;
			// 		case 1:pcDate.AddAtkZZ(3 * lv); break;
			// 		case 2:pcDate.AddSpdZZ(1 * lv); break;
			// 		case 3:
			// 			pcDate.AddHpZZ(10 * lv); 
//			pcDate.nightLv -= prelv / 10;
//			pcDate.nightLv += nextlv / 10;
			// 			break;
			// 		case 4:pcDate.AddMagZZ(3 * lv); break;
			// 		case 5:
			// 			pcDate.AddDefZZ( lv);
//			pcDate.poisonRate.d1 -= prelv / 10;//毒率
//			pcDate.poisonRate.d1 += nextlv / 10;//毒率
			// 			break;
			// 		case 6:pcDate.AddAvoidZZ(lv); break;
			// 		}

			pcDate.m_DamageAddPercentMagic2.d1 -= prelv / 10;
			pcDate.m_DamageAddPercentMagic2.d1 += nextlv / 10;
			break;
		case 8://龙宫
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:
			// 			pcDate.AddMagZZ(5 * lv); 
			pcDate.m_MagicWater.d2 -= prelv / 10;
			pcDate.m_MagicWater.d2 += nextlv / 10;
			// 			break;
			// 		case 2:pcDate.AddHpZZ(5* lv); break;
			// 		case 3:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.m_MagicWater.d1 -= prelv / 10;
			pcDate.m_MagicWater.d1 += nextlv / 10;

			pcDate.m_PierceMagic.d1 -= prelv / 13;
			pcDate.m_PierceMagic.d1 += nextlv / 13;

			pcDate.m_MagicCriRate.d1 -= prelv / 40;
			pcDate.m_MagicCriRate.d1 += nextlv / 40;

			// 			break;		
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:pcDate.AddAvoidZZ(-prelv/2); 
			// 			pcDate.AddAvoidZZ(nextlv / 2); break;
			// 		case 6:pcDate.AddSpdZZ(-prelv/2); 
			// 			pcDate.AddSpdZZ(nextlv/ 2); break;
			// 		}
			break;
		case 9://五庄
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 1:pcDate.AddAtkZZ(2 * lv); break;
			// 		case 2:pcDate.AddHpZZ(6 * lv); break;
			// 		case 3:pcDate.AddMagZZ(2 * lv); break;
			// 		case 4:pcDate.AddDefZZ(2 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}

			pcDate.m_ParryRate.d1 -= prelv / 10;
			pcDate.m_ParryRate.d1 += nextlv / 10;
			break;
		case 10://普陀
			// 		switch (ID)
			// 		{
			// 		case 0:pcDate.AddMagZZ(3 * lv); break;
			// 		case 1:pcDate.AddHpZZ(6 * lv); break;
			// 		case 2:pcDate.AddSpdZZ(lv); break;
			// 		case 3:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 4:pcDate.AddDefZZ(3 * lv); break;
			// 		case 5:
			// 			if (1)
		{
			//				pcDate.AddAtkZZ(lv);
			int data = prelv / 20;
			pcDate.m_MagicFire.d2 -= data; //火
			pcDate.m_MagicSoil.d2 -= data; //土
			pcDate.m_MagicWater.d2 -= data;  //水
			pcDate.m_MagicThunder.d2 -= data;//雷
			data = nextlv / 20;
			pcDate.m_MagicFire.d2 += data; //火
			pcDate.m_MagicSoil.d2 += data; //土
			pcDate.m_MagicWater.d2 += data;  //水
			pcDate.m_MagicThunder.d2 += data;//雷
		}

		pcDate.m_DamageAddPercentCure.d1 -= prelv / 10;
		pcDate.m_DamageAddPercentCure.d1 += nextlv / 10;

		// 			break;
		// 		case 6:pcDate.AddAvoidZZ(lv); break;
		// 		}
		break;
		case 11://天宫
			// 		switch (ID)
			// 		{
			// 		case 0:
			// 			pcDate.AddAtkZZ(lv); 
			pcDate.MonsterSpecial.d1 -= prelv / 4;
			pcDate.MonsterSpecial.d1 += nextlv / 4;

			pcDate.m_HitRate.d2 -= prelv / 8;
			pcDate.m_HitRate.d2 += nextlv / 8;
			// 			break;
			// 		case 1:pcDate.AddHpZZ(6 * lv); break;
			// 		case 2:
			// 			pcDate.AddGrowing(-prelv / 10);
			// 			pcDate.AddGrowing(nextlv / 10);
			// 			break;
			// 		case 3:pcDate.AddDefZZ(2 * lv); break;
			// 		case 4:pcDate.AddMagZZ(2 * lv); break;
			// 		case 5:pcDate.AddSpdZZ(2 * lv); break;
			// 		case 6:pcDate.AddAvoidZZ(2 * lv); break;
			// 		}
			break;
		default:
			ERRBOX;
			return;
		}
	}
	skilllv += lv;
	//	if (lv>0)
	for (int i = 0; i < pZhuJiNeng->m_NumSkillInclude; i++)
	{
		if (isHero || prelv < pZhuJiNeng->m_Limit[i])
			if (skilllv >= pZhuJiNeng->m_Limit[i])
			{
				//存在检测
				for (int j = 0; j < pcDate.m_SkillEnablelist.size(); j++)
				{
					if (pcDate.m_SkillEnablelist[j]->m_Id == pZhuJiNeng->m_SkillIncludeID[i])
						return;
				}
				sSkill* pSkill = &m_SkillList[pZhuJiNeng->m_SkillIncludeID[i]];
				pcDate.m_SkillEnablelist.push_back(pSkill);

			}
	}
}



BOOL cSkillManager::Use粗劣小AI(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightList* pUserList = &g_pMainState->m_FightList[UserID];
	cObj* pUser = pUserList->m_pData;
	cPetData* pUserData;
	cPetData* pTargetData;
	pUser->GetDateP(pUserData);
	cObj* pTarget = g_pMainState->m_FightList[TargetID].m_pData;
	pTarget->GetDateP(pTargetData);
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		int hpout = 0;
		Cost(hpout, Skilllv, sSkillID, UserID, 1, TRUE);
		if (hpout)
		{
			SetDamage(hpout, UserID);
		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
	}
	return TRUE;
	case 1:
		if (WaitForMagicPoint(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->SetStatic(FALSE);
			pUser->SetMagicSound(sSkillID);//声音

			DWORD MagicID;
			int MagicPos;
			BOOL MagicUporDown;
			BOOL  toAll;
			BOOL bAtk;
			int maxnum;
			GetMagicAndNum(Skilllv, sSkillID, UserID, TargetID, MagicID, maxnum, MagicPos, MagicUporDown, toAll);
			int magicspeed = GetSpeed(sSkillID);
			bAtk = GetSkillAtk(sSkillID);
			pUserList->m_MaxTargetNum = 0;
			if (toAll)	m_pFightState->m_FullSkill.SetMagicUp(0, MagicID, 0, 0);

			auto func = [&](bool isCheckDie, cAttackAI::eEnemyType type, int stateid)
			{
				vector<POINT> tList;
				g_pMainState->m_AI.m_AttackAI.FindEnemy(isCheckDie, FALSE, tList, type, TargetID, stateid);
				if (!tList.size())tList.push_back({ TargetID, 0 });
				if (tList.size() < maxnum)maxnum = tList.size();
				int i = 0;
				for (; i < maxnum; ++i)
				{
					if (tList[i].x == TargetID)break;
				}
				if (i == maxnum)tList[maxnum - 1].x = TargetID;
				for (int i = 0; i < maxnum; ++i)
				{
					pUserList->targetlist[i] = tList[i].x;
				}
				pUserList->m_MaxTargetNum = maxnum;
			};

			auto func2 = [&](bool isCheckDie, cAttackAI::eEnemyType type, int stateid)
			{
				vector<POINT> tList;
				g_pMainState->m_AI.m_AttackAI.FindEnemy(isCheckDie, FALSE, tList, type, TargetID, stateid);
				auto list2 = g_pMainState->m_AI.m_AttackAI.check隐身(tList, UserID);
				if (!list2.size())list2.push_back(TargetID);
				if (list2.size() < maxnum)maxnum = list2.size();
				int i = 0;
				for (; i < maxnum; ++i)
				{
					if (list2[i] == TargetID)break;
				}
				if (i == maxnum)list2[maxnum - 1] = TargetID;
				for (int i = 0; i < maxnum; ++i)
				{
					pUserList->targetlist[i] = list2[i];
				}
				pUserList->m_MaxTargetNum = maxnum;
			};


			if (maxnum < 2)
			{
				pUserList->targetlist[0] = TargetID;
				pUserList->m_MaxTargetNum = 1;
			}
			else
				switch (sSkillID)
				{
				case 27: // 碎甲
				{
					func2(true, cAttackAI::eET封印对象, 27);
					break;
				}
				// 金刚护法
				case 33:
					func(true, cAttackAI::eET上金刚33, 33);
					break;
					// 加血 91PT灯呢我自己加 呵呵哒 哦，AI 单体技能不划算，我变成双体好了
					// 我加特技
				case 38:
				case 39:
				case 40:
				case 41:
				case 42:
				case 45:
					//			case 94:
				case 3007:
				case 3013:
					func(true, cAttackAI::eET血最少, -1);
					// 				{
					// 					vector<POINT> tList;
					// 					g_pMainState->m_AI.m_AttackAI.find相关类型的己方(FALSE,FALSE,tList, cAttackAI::eET血最少, UserID);
					// 					if (tList.size() < maxnum)maxnum = tList.size();
					// 					int i = 0;
					// 					for (; i < maxnum; i++)
					// 					{
					// 						if (tList[i].x == TargetID)break;
					// 					}						
					// 					if (i == maxnum)tList[maxnum - 1].x = TargetID;
					// 					for (i = 0; i < maxnum; i++)
					// 					{
					// 						pUserList->targetlist[i] = tList[i].x;
					// 					}
					// 					pUserList->m_MaxTargetNum = maxnum;
					// 				}
					break;
				case 91:
				case 102:
					func(true, cAttackAI::eET血最少, sSkillID);
					// 			{
					// 				vector<POINT> tList;
					// 				g_pMainState->m_AI.m_AttackAI.find相关类型的己方(FALSE, FALSE, tList, cAttackAI::eET血最少, UserID, 102);
					// 				if (!tList.size())tList.push_back({ TargetID, 0 });
					// 				if (tList.size() < maxnum)maxnum = tList.size();
					// 				int i = 0;
					// 				for (; i < maxnum; i++)
					// 				{
					// 					if (tList[i].x == TargetID)break;
					// 				}
					// 				if (i == maxnum)tList[maxnum - 1].x = TargetID;
					// 				for (i = 0; i < maxnum; i++)
					// 				{
					// 					pUserList->targetlist[i] = tList[i].x;
					// 				}
					// 				pUserList->m_MaxTargetNum = maxnum;
					// 			}
					break;
				case 112: // 灵动九天
					func(true, cAttackAI::eET上灵动112, 112);
					// 				{
					// 					vector<POINT> tList;
					// 					g_pMainState->m_AI.m_AttackAI.find相关类型的己方(false, FALSE, tList, cAttackAI::eET上灵动112, UserID, 112);
					// 					if (!tList.size())tList.push_back({ TargetID, 0 });
					// 					if (tList.size() < maxnum)maxnum = tList.size();
					// 					int i = 0;
					// 					for (; i < maxnum; i++)
					// 					{
					// 						if (tList[i].x == TargetID)break;
					// 					}
					// 					for (int i = 0; i < maxnum; i++)
					// 					{
					// 						pUserList->targetlist[i] = tList[i].x;
					// 					}
					// 					pUserList->m_MaxTargetNum = maxnum;
					// 				}
					break;
				case 120: // 鬼眼
					func(true, cAttackAI::eET鬼眼120, -1);
					// 			{
					// 				int num = 1;
					// 				int star = UserID >= 10 ? 10 : 0;
					// 				for (int i = star; i < star + 10; ++i)
					// 				{
					// 					if (i == TargetID)continue;
					// 					if (!g_pMainState->m_FightList[i].isExist)
					// 					{
					// 						continue;
					// 					}
					// 					cPetData *data = nullptr;
					// 					g_pMainState->m_FightList[i].m_pData->GetDateP(data);
					// 					if (!data)
					// 					{
					// 						continue;
					// 					}
					// 					if (data->PeopleSpecial.d1 >= 100)
					// 					{
					// 						continue;
					// 					}
					// 					pUserList->targetlist[num] = i;
					// 					if (++num == maxnum)
					// 					{
					// 						break;
					// 					}
					// 				}
					// 				pUserList->targetlist[0] = TargetID;
					// 				pUserList->m_MaxTargetNum = num;
					// 			}
					break;
				case 126://黄泉
					func2(true, cAttackAI::eET黄泉之息126, 126);
					break;
				case 127://魂飞魄散
					func2(true, cAttackAI::eET魂飞魄散127, -1);
					break;
				case 37: // 救人的
				case 104:
				case 125:
				case 3008:
				case 3009:
					pUserList->m_MaxTargetNum = 0;
					for (int i = 0; i < maxnum; i++)
					{
						pUserList->targetlist[pUserList->m_MaxTargetNum] = g_pMainState->m_AI.GetNear(UserID, TargetID, i, 2);

						if (bAtk)
							if (UserID == pUserList->targetlist[pUserList->m_MaxTargetNum])
							{//防止对象攻击自己
								continue;
							}

						if (-1 == pUserList->targetlist[pUserList->m_MaxTargetNum])
						{
							break;
						}
						pUserList->m_MaxTargetNum += 1;
					}
					break;
				case 3048:
				{
					int num = 0;
					int star = UserID >= 10 ? 10 : 0;
					for (int i = star; i < star + 10; ++i)
					{
						//					if (i == TargetID)continue;
						if (!g_pMainState->m_FightList[i].isLive)
						{
							continue;
						}
						if (g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_CHARACTER)
						{
							continue;
						}
						if (!g_pMainState->m_FightList[i].CheckDie())
						{
							continue;
						}
						cPetData *data = nullptr;
						g_pMainState->m_FightList[i].m_pData->GetDateP(data);
						if (!data)
						{
							continue;
						}
						if (pUserData->PeopleSpecial.d1 < data->PeopleSpecial.d2)
						{
							continue;
						}
						pUserList->targetlist[num] = i;
						if (++num == maxnum)
						{
							//						break;
						}
					}
					//				pUserList->targetlist[0] = TargetID;
					pUserList->m_MaxTargetNum = num;
					int d = pUserData->m_HP - pUserData->m_HPMax.GetData() / 10;
					if (d > 0)
					{
						AddHp(UserID, -d);
						SetDamage(d, UserID);
						pUserData->m_HPHurtMax = pUserData->m_HP;
						pUserData->m_MP = 0;
					}
				}
				break;
				default:
					for (int i = 0; i < maxnum; i++)
					{
						pUserList->targetlist[pUserList->m_MaxTargetNum] = g_pMainState->m_AI.GetNear(UserID, TargetID, i, 1 + 2);
						//GetTargetID(UserID, TargetID, i);

						if (bAtk)
							if (UserID == pUserList->targetlist[pUserList->m_MaxTargetNum])
							{//防止对象攻击自己
								continue;
							}

						if (-1 == pUserList->targetlist[pUserList->m_MaxTargetNum])
						{
							break;
						}
						pUserList->m_MaxTargetNum += 1;
					}
					break;
				}
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)m_pFightState->SetMagicSuffer(pUserList->m_NowTargetID, pUser->GetDirection());

				if (toAll)
				{
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_bSufferFullSkill = TRUE;
					m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_FrameGap = magicspeed;
				}
				else
				{
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_bSufferFullSkill = FALSE;
					m_pFightState->m_pList[pUserList->m_NowTargetID]->SetMagiSufferID(MagicID, MagicPos, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID], MagicUporDown);
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_pData->m_MagicSuffer.m_FrameGap = magicspeed;
				}
			}
			stage += 1;
		}
		return TRUE;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(FALSE);
			stage += 1;
		}
	case 3:  //附加BUFF

	{
		DWORD MagicID;
		BOOL toAll = GetSkillToAll(sSkillID);
		int LateTime; //伤害计算延时
		BOOL bAtk;
		GetDelayAnd(sSkillID, LateTime, MagicID);
		bAtk = GetSkillAtk(sSkillID);
		BOOL bover = FALSE;
		if (toAll)
		{
			if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() == m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame() - LateTime)
			{
				bover = TRUE;
			}
		}
		else
		{
			if (!pTarget->m_MagicSuffer.m_NeedShow)bover = TRUE;
			else
			{
				if (LateTime >= pTarget->m_MagicSuffer.m_pFile->GetMaxFrame())LateTime = pTarget->m_MagicSuffer.m_pFile->GetMaxFrame() - 1;
				if (pTarget->m_MagicSuffer.GetFrame() == pTarget->m_MagicSuffer.m_pFile->GetMaxFrame() - LateTime)
				{
					bover = TRUE;
				}
			}
		}
		if (bover)
		{
			stage = 4;
			pUserList->m_NowTarget = -1;
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)
				{
					m_pFightState->SwitchMagicSuffer(pUserList->m_NowTargetID);
					m_pFightState->m_pList[pUserList->m_NowTargetID]->m_pData->SetSound(POS_SUFFER);//声音

				}

				if (CheckMagicHit(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID/*TargetID*/))
				{
					EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);
				}
			}
			cPetData* pPet;
			pUser->GetDateP(pPet);
			if (1 > pPet->m_HP)
			{
				if (UserID < 10)
					pUserList->m_sufferDirection = 3;
				else pUserList->m_sufferDirection = 7;
				g_pMainState->m_pFightState->SetDie(UserID);
				pTargetData->m_CP /= 2;
				return TRUE;
			}
		}
	}
	return TRUE;
	case 4://等待主角动作完成
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			switch (sSkillID)
			{
			case 7: // 破釜沉舟

			{
				pUserList->m_SkillSelect.SkillID = 1017;
				stage = 0;
			}
			return TRUE;
			case 50: // 漫天花雨

			{
				pUserList->m_SkillSelect.SkillID = 1050;
				stage = 0;
			}
			return TRUE;
			case 2095: // 力劈华山

			{
				pUserList->m_SkillSelect.SkillID = 1095;
				stage = 0;
			}
			return TRUE;
			}
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(FALSE);
			stage = 5;
		}
		return TRUE;
	case 5:StageWaitSleep(10, UserID, 6); break;
	case 6:

	{
		pUser->SetMagicSound(-1);//声音
		pUserList->m_work.pop_back();

		if (g_pMainState->m_FightList[TargetID].isLive && (!g_pMainState->m_FightList[TargetID].CheckDie()))
		{
			CoutComboMagic(sSkillID, pUserData, UserID, pTargetData);
		}

	}
	break;

	}
	return TRUE;
}


#endif