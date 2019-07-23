#include "_global.h"


bool cSkillManager::SetDateBuffUp(int userID, int targetID, int stateid, sBuff& buf, int skilllv)
{
	if (g_StateType != STATE_FIGHT)return true;
	if (buf.remainingTimes < 1)buf.remainingTimes = 1;
	int MagicPos = 0;
	ulong MagicID = 0; //BUFF 的ID 已经没用了
	bool MagicUpOrDown = false; //设置BUFF 在人物显示后显示
	//	int  magicType = 1; //默认法术类型 封印
	cObj* pTarget = m_pFightState->m_pFightWorkList[targetID]->m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	sFightData& TargetFightP = pTargetData->m_FightData;
	//eBuffType EffectType = eBuffType封印;


	cObj* pUser = m_pFightState->m_pFightWorkList[userID]->m_pObj;
	cPropertyData* pUsetData;
	pUser->GetPropertyData(pUsetData);

	for (list<sBuff>::iterator it = pTarget->m_StateList.begin(); it != pTarget->m_StateList.end(); it++)
	{
		if (it->ID == stateid)
		{
			it->remainingTimes = buf.remainingTimes;
			if (it->damage < buf.damage)
			{
				it->damage = buf.damage;
			}
			if (it->damage2 < buf.damage2)
			{
				it->damage2 = buf.damage2;
			}
			return true;
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
		TargetFightP.cannotSpesialSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicPos = -10;
		MagicUpOrDown = true;
		break;
	case 1://后发制人 ...down...
		MagicID = 0x2A2A0663;
		pTargetData->Speed.AddDataAdd(0xFFFF);
//		pTargetData->m_Pierce.d1 += 30;
		pTargetData->CriRate.d1 += 20;
//		pTargetData->m_DamagePercent.d1 += 50;
		pTargetData->Def.AddDataAdd(buf.damage = skilllv * 3);
		pTargetData->Mana.AddDataAdd(buf.damage2 = skilllv * 2);
		MagicPos = -10;
		break;
	case 4://杀气诀
//		MagicUpOrDown = true;
		MagicID = 0x62EDD1CB;
		pTargetData->Hit.AddDataAdd(buf.damage2 = skilllv * 5);
		pTargetData->Atk.AddDataAdd(buf.damage = skilllv);
		MagicPos = -10;
		break;
	case 6://反间计
		pTarget->SetShakeFor抖动(true);
		TargetFightP.chaos混乱反间 += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		TargetFightP.cannotUseItem += 1;
		break;
	case 8://安神诀
		MagicPos = 10;
		MagicUpOrDown = true;
//		MagicID = 3860707508;
//		pTargetData->DmgPercentOfMagic.d2 += 30;
		pTargetData->Mana.AddDataAdd(buf.damage = skilllv);
		break;
	case 14://催眠
		MagicPos = -10;
		TargetFightP.cannotAll += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 3398426285;
		break;
	case 15://失心 ...down...
		MagicPos = -10;
		TargetFightP.cannotMagic += 1;
		pTargetData->Def.AddDataAddPercent(-(buf.damage = 15));
		pTargetData->Mana.AddDataAddPercent(-(buf.damage2 = 15));
		pTargetData->Evade.AddDataAddPercent(-25);
		MagicID = 3635978625;
		break;
// 	case 16://落魄
// 		MagicPos = -10;
// 		TargetFightP.cannotMagic += 1;
// 		TargetFightP.cannotAttack += 1;
// //		pTargetData->m_Wakan.AddDataAddPercent(-20);
// 		pTarget->SetShakeFor抖动(true);
// //		MagicID = 0x8B43833D;
// 		break;
	case 17://失忆
		MagicPos = -10;
// 		TargetFightP.cannotAttack += 1;
// 		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		MagicID = 3946646209;
		break;
// 	case 18://追魂
// 		MagicPos = -10;
// 		TargetFightP.cannotAttack += 1;
// 		pTargetData->Def.AddDataAddPercent(-20);
// 		MagicID = 3655438388;
// 		break;
// 	case 19://离魂
// 		MagicPos = -10;
// 		TargetFightP.cannotMagic += 1;
// 		MagicID = 1214058823;
// 		break;
// 	case 20://失魂   
// 		MagicPos = -10;
// 		TargetFightP.cannotMagic += 1;
// 		MagicID = 2336457533;
// 		break;
	case 21://定身
		MagicPos = -10;
//		TargetFightP.cannotAll += 1;
		pTargetData->Def.AddDataAddPercent(-(buf.damage = 15));
		pTargetData->Mana.AddDataAddPercent(-(buf.damage2 = 15));
		TargetFightP.cannotAttack += 1;
// 		TargetFightP.cannotMagic += 1;
// 		TargetFightP.cannotSkill += 1;
		MagicID = 2461182746;
		break;
	case 26: // 分身术
		pTarget->SetShadow(30);
		pTargetData->HitRateOfMagic.d2 += buf.damage = skilllv / 5;
		break;
	case 27: //碎甲符
		pTargetData->Def.AddDataAddPercent(-(buf.damage = 15));
		pTargetData->Mana.AddDataAddPercent(-(buf.damage2 = 15));
		MagicID = 0x5525C5FB;
		MagicUpOrDown = true;
		MagicPos = 10;
		break;
	case 33://金刚护法
		pTarget->SetTwinkle(true);
		pTargetData->Atk.AddDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 34: //韦陀护法  
		pTargetData->Hit.AddDataAdd(buf.damage = skilllv * 3);
		pTargetData->Atk.AddDataAdd(buf.damage2 = skilllv);
		MagicID = 0xF184BD59;
		MagicPos = -10;
//		MagicUpOrDown = true;
		break;
	case 35:  //金刚护体
		pTargetData->Def.AddDataAdd(buf.damage = skilllv * 3 / 2);
		MagicID = 916220457;
		MagicUpOrDown = true;
		break;
	case 36://一苇渡江
		MagicID = 382287583;
//		MagicPos = -10;
		MagicUpOrDown = true;
		pTargetData->Speed.AddDataAddPercent(buf.damage = skilllv / 3);
		break;
	case 46:    //佛法无边
		pTargetData->ComboRateOfMagic.d1 += (buf.damage = 15 + skilllv / 10);
		MagicID = 3930943562;
		MagicPos = -10;
		MagicUpOrDown = true;
		break;
	case 49:    //楚楚可怜
		MagicID = 0x72AD6DBA;
		MagicPos = -10;
		MagicUpOrDown = true;
// 		pTargetData->m_HitRate.d2 += 100;
// 		pTargetData->m_MagicHitRate.d2 += 100;
// 		pTargetData->m_SealRate.d2 += 100;
// 		pTargetData->poisonRate.d2 += 100;
		TargetFightP.cannotMagic += 1;
		pTargetData->Hide.d1 += 1;
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
// 	case 59://一笑倾城
// 		TargetFightP.cannotMagic += 1;
// 		MagicID = 3635978625;// 0x1E1AF8D9;
// 		MagicPos = -10;
// 		break;
	case 62://天神护体
		pTargetData->Mana.AddDataAdd(buf.damage = skilllv);
		pTargetData->HitRateOfMagic.d2 += (buf.damage2 = 15);
//		MagicID = 0;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;
	case 67:	//镇妖
//		pTargetData->m_ATK.AddDataAddPercent(-30);
		TargetFightP.cannotSpesialSkill += 1;
		MagicID = 0x98753F94;
		MagicPos = -10;
		break;
	case 68:	//错乱
		pTargetData->Hit.AddDataAddPercent(-(buf.damage = 20));
		TargetFightP.cannotMagic += 1;
		MagicID = 0x2F78C46E;
		MagicUpOrDown = true;
		MagicPos = -10;
		break;
	case 69:	//百万神兵
		TargetFightP.cannotAttack += 1;
		MagicID = 0xC48ABA7B;
		MagicPos = -10;
		break;
	case 81:// 逆鳞
		pTarget->SetTwinkle(true);
		pTargetData->Atk.SetDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 87:// 神龙摆尾
		pTargetData->DmgPercent.d2 += buf.damage = 20;
// 		MagicID = 0xC48ABA7B;
 		MagicPos = -10;
		MagicUpOrDown = true;
		break;
	case 89:  //日月乾坤
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		MagicID = 0x313BCC79;
		MagicUpOrDown = 1;
		MagicPos = -10;
		break;
	case 90:   //炼气化神
		MagicID = 0x719D767F;
		MagicUpOrDown = 1;
		MagicPos = 10;
		//		buf.damage = skilllv;
		pTargetData->m_FightData.m_TurnMPAdd += buf.damage;
//		AddMp(targetID, buf.damage);
		break;
	case 91: //生命之泉
		MagicID = 0xF8EE853A;
		MagicUpOrDown = 1;
		MagicPos = 10;
//		buf.damage = skilllv * 2 + 120;
		pTargetData->m_FightData.m_TurnHPAdd += buf.damage;
//		AddHp(targetID, buf.damage);
		buf.damage2 = buf.damage;
		break;
	case 104:
	case 102: //普渡众生
		MagicID = 0xD8857128;
		MagicUpOrDown = 1;
		MagicPos = 10;
		buf.damage = skilllv * 4 + 50;
		buf.damage2 = buf.damage;
		pTargetData->m_FightData.m_TurnHPAdd += buf.damage;
		pTargetData->m_FightData.m_TurnHPHurtAdd += buf.damage2;
		break;
	case 103:// 紧箍咒
		MagicID = 0xEFE73EB9;
		MagicUpOrDown = 1;
		MagicPos = 10;
		pTargetData->m_FightData.m_TurnHPHurtAdd -= buf.damage = skilllv * 2;
		pTargetData->m_FightData.m_TurnHPAdd -= buf.damage;
		break;
	case 112:// 灵动九天
		MagicID = 0x95FF4460;
		MagicUpOrDown = 1;
		MagicPos = 0;
		pTargetData->Mana.AddDataAdd(buf.damage = skilllv);
		break;
	case 113:// 颠倒五行
// 		MagicID = 0x4DDF5690;
// 		MagicUpOrDown = true;
 		MagicPos = -10;
// 		pTargetData->m_Wakan.AddDataAdd(buf.damage = skilllv);
// 		pTargetData->m_ATK.AddDataAdd(buf.damage);
// 		pTargetData->m_DEF.AddDataAdd(buf.damage);
// 		pTargetData->m_SPD.AddDataAdd(buf.damage);
// 		pTargetData->m_HIT.AddDataAdd(buf.damage);
		buf.damage = skilllv / 6 + 5;
		pTargetData->MagicThunder.d2 += buf.damage;
		pTargetData->MagicSoil.d2 += buf.damage; //土
		pTargetData->MagicFire.d2 += buf.damage; //火
		pTargetData->MagicWater.d2 += buf.damage; //水
		pTargetData->HitRateOfMagic.d2 += buf.damage / 2;
		break;
	case 120://幽冥鬼眼
		MagicID = 0x21435203;
// 		pTargetData->m_HitRate.d1 += 100;
		pTargetData->HitRateOfSeal.d2 += (buf.damage = 20);
// 		pTargetData->poisonRate.d1 += 30;
		pTargetData->Hide.d2 += (buf.damage2 = 0xFF);
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
		pTargetData->Hide.d1 += 1;
//		pTargetData->m_HitRate.d1 += 10;
// 		pTargetData->m_HitRate.d2 += 100;
// 		pTargetData->m_MagicHitRate.d2 += 100;
// 		pTargetData->m_SealRate.d2 += 100;
// 		pTargetData->poisonRate.d2 += 100;
		TargetFightP.cannotMagic += 1;
	}
		break;
	case 125: //还阳术
		pTargetData->Atk.AddDataAdd(buf.damage = skilllv * 3 / 2);
		break;
	case 126:// 黄泉之息
		MagicID = 0x5ECEBEDD;
		pTargetData->Speed.AddDataAddPercent(-(buf.damage = skilllv / 10));
		MagicUpOrDown = 1;
		MagicPos = -10;
		break;
	case 129:// 锢魂术
		MagicID = 0x5C0073EE;
		MagicUpOrDown = 1;
//		MagicPos = 1;
		pTargetData->m_FightData.cannotLive += 1;
		break;
	case 133://牛劲
		MagicID = 0x62EDD1CB;
		MagicUpOrDown = 1;
		pTargetData->Mana.AddDataAdd(buf.damage = skilllv);
//		pTargetData->m_MagicHitRate.d1 += 100;
		pTargetData->Hide.d2 += (buf.damage2 = 0xFF);
		break;
	case 137: //魔王回首
		pTargetData->CounterRate.d1 += (buf.damage = 100);
		MagicUpOrDown = 1;
		break;
	case 141://象形
		TargetFightP.cannotAll += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 0x3646A4D9;
		MagicPos = -10;
		break;
	case 142://鹰击
	case 148://连环击
//		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		TargetFightP.cannotUseItem += 1;
		MagicID = 0x58628406;
		MagicPos = -10;
		MagicUpOrDown = true;
		break;
	case 144:// 威慑
		MagicID = 0x20FCCE94;
		MagicPos = -10;
		TargetFightP.cannotAttack += 1;
		TargetFightP.cannotMagic += 1;
		TargetFightP.cannotSpesialSkill += 1;
		TargetFightP.cannotUseItem += 1;
// 		pTargetData->Atk.AddDataAddPercent(-20);
// 		pTargetData->Def.AddDataAddPercent(-10);
// 		pTargetData->Mana.AddDataAddPercent(-10);
		MagicUpOrDown = true;
		break;
	case 145:// 变身
		MagicID = 0x85C9AF08;
		pTargetData->Atk.AddDataAdd(buf.damage = skilllv);
		MagicUpOrDown = 1;
		break;
	case 147://定心术
		MagicID = 755485932;
		pTargetData->Mana.AddDataAdd(buf.damage = skilllv);
		MagicUpOrDown = 1;
		break;
	case 150://极度疯狂
		MagicID = 0xBBEA83F4;
		pTargetData->CounterRate.d1 += (buf.damage = 100);
		MagicUpOrDown = 1;
		break;
// 	case 152://天魔解体
// 		MagicID = 0x3D3FA597;
// 		pTargetData->HPMax.AddDataAddPercent(30);
// 		{
// 			int dam = AddHp(targetID, 5, 10000);
// 			SetDamage(-dam, targetID);
// 		}
// 		MagicUpOrDown = 1;
// 		break;
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
		buf.damage = skilllv * 3 / 2;
		pTargetData->Def.AddDataAdd(buf.damage);
		MagicID = 0x369C6A29;
		MagicUpOrDown = true;
		break;
	case 162:  //天罗地网
		MagicPos = -10;
		MagicID = 0x8F3E73D5;
		TargetFightP.cannotAttack += 1;
		break;
	case 166://幻镜术
		MagicID = 0x0B788E5A;
		MagicUpOrDown = true;
		MagicPos = 0;
		pTargetData->StabRateOfMagic.d1 += (buf.damage = 50);    //法术反弹伤害
		pTargetData->StabPercentOfMagic.d1 += (buf.damage2 = 50); //法术反弹率
		break;
	case 175: // 不动如山
		pTargetData->DmgAdd.d2 += buf.damage = skilllv * 3 / 2;
		pTargetData->DmgAddOfMagic.d2 += buf.damage2 = skilllv;
		break;
	case 176: // 碎星决
		pTargetData->DmgAdd.d1 += buf.damage = skilllv * 3 / 2;
		pTargetData->m_FightData.zhanyi += 1;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;
	case 177: // 镇魂诀
		pTargetData->CriRate.d1 += buf.damage = skilllv / 20;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;
	case 181: // 化骨
		pTargetData->SuckBloodPercent.d1 += buf.damage = skilllv / 10;
		pTargetData->SuckBloodRate.d1 += buf.damage2 = 100;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;
	case 182: // 夺魄令
		TargetFightP.cannotMagic += 1;
		MagicPos = -10;
		break;
	case 185: // 催心术
		pTargetData->Speed.AddDataAdd(-(buf.damage = skilllv / 2));
		MagicPos = -10;
		MagicUpOrDown = true;
		break;
	case 187: // 明光宝烛
		pTargetData->DmgAdd.d2 += buf.damage = skilllv * 3 / 2;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;
	case 188: // 金身舍利
		pTargetData->DmgAddOfMagic.d2 += buf.damage2 = skilllv;
//		MagicPos = -10;
		MagicUpOrDown = true;
		break;
	case 198: // 雾杀
		MagicPos = 10;
		MagicUpOrDown = true;
//		buf.damage = 100;
		break;
	case 199: // 血雨休息(夺魄令)
//		TargetFightP.cannotMagic += 1;
		MagicPos = -10;
		break;
	case 201: // 炎护 
		TargetFightP.yanhu += 1;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;
	case 204: // 蜜润
		pTargetData->DmgAddOfMagic.d2 += buf.damage2 = skilllv;
		MagicPos = 10;
		MagicUpOrDown = true;
		break;

	case 1002: //1回合的格挡 BUFF
		pTargetData->ParryRate.d1 += buf.damage = 0xFFFF;
		break;
// 	case 1004://保护
// 		break;
// 	case 2092://惊心一剑
// 		//		pTargetData->m_ATK.AddDataAddPercent(-20);
// 		break;
	case 2093://夜舞倾城
		buf.damage = 5;
		pTargetData->Atk.AddDataAddPercent(-buf.damage);   //伤害
		pTargetData->Hit.AddDataAddPercent(-buf.damage);   //命中
		pTargetData->Def.AddDataAddPercent(-buf.damage);   //防御
		pTargetData->Mana.AddDataAddPercent(-buf.damage); //灵力
		pTargetData->Speed.AddDataAddPercent(-buf.damage);   //速度
		pTargetData->Evade.AddDataAddPercent(-buf.damage); //躲闪
		break;
	case 2094://死亡召唤
		MagicID = 0x19182964;
		MagicPos = -10;
		pTargetData->m_FightData.cannotLive += 1;
		break;
	case 2095: // 力劈
		pTargetData->Hit.AddDataAddPercent(buf.damage = 200);   //命中
		break;
	case 2096: // 浮云神马
		pTargetData->Speed.AddDataAddPercent(buf.damage = 10);
		break;
	case 2097:// 法术防御
		MagicID = 0xDEDEE983;
		MagicUpOrDown = true;
		pTargetData->DmgPercentOfMagic.d2 += buf.damage = 60;
		break;
	case 2101:// 无畏布施
//		MagicID = 0xDEDEE983;
		MagicUpOrDown = true;
		pTargetData->DmgAdd.d2 += buf.damage = pUsetData->Def / 5;
		pTargetData->DmgAddOfMagic.d2 += buf.damage2 = pUsetData->Mana / 4;
		break;
	case 1998:// 无畏布施2
		MagicPos = 10;
		MagicUpOrDown = true;
		pTargetData->Def.AddDataAddPercent(-(buf.damage = 20));
		pTargetData->Mana.AddDataAddPercent(-(buf.damage2 = 25));
		break;
// 	case 3018://野兽之力
// 		pTargetData->DmgPercent.d1 += 10;
// 		break;
// 	case 3019:
// 		pTargetData->DmgPercent.d1 += 5;
// 		break;
// 	case 3020://光辉之甲
// 		pTargetData->Def.AddDataAddPercent(10);
// 		break;
// 	case 3021:
// 		pTargetData->Def.AddDataAddPercent(5);
// 		break;
// 	case 3022: // 流云诀
// 		pTargetData->Speed.AddDataAddPercent(10);
// 		break;
// 	case 3023:
// 		pTargetData->Speed.AddDataAddPercent(5);
// 		break;
	case 3024://太极护法 
	case 3025://罗汉
		MagicPos = -10;
		MagicID = 0xAF07277F;// 0x5CC81980;
		pTargetData->DmgPercentOfMagic.d2 += buf.damage = 50;
		break;
	case 3026://修罗咒
		MagicPos = 10;
		MagicUpOrDown = true;
		pTargetData->StabRateOfMagic.d1 += buf.damage = 100;
		pTargetData->StabPercentOfMagic.d1 += buf.damage2 = 50;
		pTargetData->StabRate.d1 += buf.damage;
		pTargetData->StabPercent.d1 += buf.damage2;
		break;
	case 3027://天衣无缝
		MagicPos = 10;
		MagicUpOrDown = true;
		pTargetData->HitRateOfMagic.d2 += buf.damage = 50;
		break;
// 	case 3028:// 放下屠刀
// 		pTargetData->DmgPercent.d1 -= 10;
// 		break;
// 	case 3029:
// 		pTargetData->DmgPercent.d1 -= 5;
// 		break;
// 	case 3030://破甲术
// 		pTargetData->Def.AddDataAddPercent(-10);
// 		break;
// 	case 3031:
// 		pTargetData->Def.AddDataAddPercent(-5);
// 		break;
// 	case 3032: // 凝滞术
// 		pTargetData->Speed.AddDataAddPercent(-10);
// 		break;
// 	case 3033:
// 		pTargetData->Speed.AddDataAddPercent(-5);
// 		break;

	case 3047://心如明镜
		MagicPos = 10;
		MagicUpOrDown = true;
		pTargetData->DmgPercentOfMagic.d2 += buf.damage = 50;//法术防御加成
		pTargetData->DmgPercent.d2 += buf.damage;//物理防御加成
		pTargetData->HitRateOfPoison.d2 += buf.damage2 = 0xFF;
		pTargetData->HitRateOfSeal.d2 += buf.damage2;
//		pTarget->ReMoveState(eBuffType其它);
		break;
	default:
		ERRBOX2(stateid);
		return true;
	}
	sSkill* pskill = g_pMainState->m_SkillManager.GetSkill(stateid);
	if (pskill)
	{
		buf.EffectType = (eBuffType)pskill->m_EffectType;
		buf.MagicID = pskill->m_State;
		if (stateid == 35)
		{
			if (targetID < 10)
			{
				buf.MagicID = 0x592EBD89;
				MagicUpOrDown = false;
			}
			else
			{
				buf.MagicID = 0x2F45B9F0;
				MagicUpOrDown = true;
			}
			MagicPos = -10;
		}
	}
	else
	{
		buf.EffectType = eBuffType其它;
		if (stateid == 1998)
		{
			buf.MagicID = 0x5525C5FB;
		}
		else
		{
			buf.MagicID = 0;
		}
	}
	buf.skilllv = skilllv;
	buf.userID = userID;
	buf.targetID = targetID;
//	buf.MagicID = MagicID;
	buf.bufPos = MagicPos;
	buf.bBuffup = MagicUpOrDown;
	buf.ID = stateid; //设置BUFF  ID
	m_pFightState->AddState(targetID, buf);
	return true;
}
