#include "_global.h"
#include "_txt.h"


bool cAI::isSkillSeal(int skill)
{
	eSkill e = (eSkill)skill;
	switch (e)
	{
	case eSkill::反间之计:
	case eSkill::催眠符:
	case eSkill::失心符:
	case eSkill::落魄符:
	case eSkill::失忆符:
	case eSkill::追魂符:
	case eSkill::离魂符:
	case eSkill::失魂符:
	case eSkill::定身符:

	case eSkill::碎甲符:

	case eSkill::莲步轻舞:
	case eSkill::如花解语:
	case eSkill::似玉生香:
	case eSkill::一笑倾城:
	case eSkill::镇妖:
	case eSkill::错乱:
	case eSkill::百万神兵:
	case eSkill::日月乾坤:

		// 	case eSkill::魂飞魄散:
		// 	case eSkill::锢魂术:

	case eSkill::威慑:

		// 	case eSkill::勾魂:
		// 	case eSkill::摄魄:
		// 	case eSkill::魔音摄魂:

	case eSkill::含情脉脉:

	case eSkill::夺魄令:
		// 	case eSkill::煞气诀:
		// 	case eSkill::惊魂掌:
		// 	case eSkill::摧心术:

		return true;
	}
	return false;
}

bool cAI::isSkillResurgence(int skill)
{
	eSkill e = (eSkill)skill;
	return (e == eSkill::回魂咒 ||
		e == eSkill::起死回生 ||
		e == eSkill::我佛慈悲 ||
		e == eSkill::还阳术 ||
		e == eSkill::由己渡人 ||

		e == eSkill::杨柳甘露 ||
		e == eSkill::慈航普渡);
}

void cAI::setData(int i1, int i2)
{
	s_list1 = &g_pMainState->m_FightWorkList[i1];
	s_list2 = &g_pMainState->m_FightWorkList[i2];
	s_obj1 = s_list1->m_pObj;
	s_obj2 = s_list2->m_pObj;
	s_data1 = s_obj1->getPropertyData();
	s_data2 = s_obj2->getPropertyData();
}


int cAI::getMagicDamage(int user, int target, int Damageup)
{
	int UserID = user;
	setData(user, target);
	cObj* pUser = s_obj1;
	cPropertyData* pUserData = s_data1;
	cPropertyData* pTargetData = s_data2;
	int wakanUser = pUserData->Mana.GetData();    //自身灵力
	int  wakanTarget = pTargetData->Mana.GetData(); //目标灵力
	//	wakanTarget -= pUserData->m_Lv<<1;
	// 盾气
	// 	int turn = m_pFightState->m_pFightWorkList[TargetID]->_myTurn;
	// 	if (pTargetData->isHadPetSkill(75) && turn < 5) // 灵能激发
	// 	{
	// 		wakanTarget += (5 - turn) * pTargetData->m_Lv / 5;
	// 	}

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

	int dam = (skillLv * Damageup + wakanUser * 10 - wakanTarget * 10 + 装备伤害分量 * 10) * (21 - targetNum) / 200;

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
	//	Damageup += CountSpecial(pUserData, pTargetData/*, pTarget->GetSex()*/);//特攻修正

	dam = dam * (100 + xiuliancha * 2 + pUserData->DmgPercentOfMagic.d1 - pTargetData->DmgPercentOfMagic.d2 + Damageup) / 100;
	dam += pUserData->DmgAddOfMagic.d1 - pTargetData->DmgAddOfMagic.d2 + xiuliancha * 5;


	return max(dam, 0);
}


int cAI::getPhyDamage(int UserID, int TargetID, int Damageup)
{
	setData(UserID, TargetID);
	cObj* pUser = s_obj1;
	cPropertyData* UserData = s_data1;
	cPropertyData* TargetData = s_data2;
	//	pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
	// 	pUser->GetPropertyData(UserData);
	// 	pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	// 	pTarget->GetPropertyData(TargetData);
	//sFightData& userFightData = UserData->m_FightProperty;
	sFightData& targetFightData = TargetData->m_FightData;
	// 	if (TargetData->m_FightData.m_WallNum > 0)
	// 	{
	// 		TargetData->m_FightData.m_WallNum -= 1;
	// 		dam = 0;
	// 		return;
	// 	}
	int userAtk = UserData->Atk.GetData();    //自身攻击
	int SufferDef = TargetData->Def.GetData(); //目标防御
	// 盾气
	// 	int turn = m_pFightState->m_pFightWorkList[TargetID]->_myTurn;
	// 	if (TargetData->isHadPetSkill(78) && turn < 5)
	// 	{
	// 		SufferDef += (5 - turn) * TargetData->m_Lv * 2 / 5;
	// 	}
	// 	else if (TargetData->isHadPetSkill(77) && turn < 5)
	// 	{
	// 		SufferDef += (5 - turn) * TargetData->m_Lv / 5;
	// 	}

	int& atknum = targetFightData.SufferNum;

	////////////////////////////////////////////////////////////////////////// 呵呵哒 越被打格挡越没用
	int picrcerate = UserData->Pierce刺穿.d1 - TargetData->Pierce刺穿.d2 + atknum/**3*/;
	// 	bool is壁垒 = false;
	// 	bool is善恶 = false;
	// 	bool is力劈 = false;
	// 	if (Damageup == 10086)
	// 	{
	// 		is力劈 = true;
	// 		Damageup = 0;
	// 		//		picrcerate += 5;
	// 	}
	// 	if (Damageup == 10087)
	// 	{
	// 		Damageup = 0;
	// 		picrcerate += 5;
	// 		if (TargetData->m_FightData.m_bDefend)
	// 		{
	// 			is壁垒 = true;
	// 		}
	// 	}
	// 	if (Damageup == 10088)
	// 	{
	// 		is善恶 = true;
	// 		Damageup = 0;
	// 		//		picrcerate += 5;
	// 	}
	if (picrcerate > 0)
	{
		SufferDef -= (SufferDef * picrcerate) / 100;//无视防御
	}

	// 	if (is力劈)
	// 	{
	// 		// 力劈华山
	// 		dam += userAtk * 3 - (SufferDef + TargetData->Atk.GetData() * 2);
	// 	}
	// 	else
	// 	{
	// 		dam += (userAtk)-(SufferDef);
	// 	}
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

	int dam = (userAtk)-(SufferDef);
	if (Damageup == 10086)
	{
		Damageup = 0;
		dam = userAtk * 3 - (SufferDef + TargetData->Atk.GetData() * 2);
	}
	//	Damageup += CountSpecial(UserData, TargetData/*, pTarget->GetSex()*/);//特攻修正
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

	if (dam > 1 && TargetData->m_FightData.m_bDefend)
	{
		dam /= 2;
	}

	return max(dam, 0);
};


int cAI::getDamage(int user, int target, int skill)
{
	eSkill e = (eSkill)skill;
	if ((e >= eSkill::雷击 && e <= eSkill::地狱烈火) ||
		e == eSkill::月光 ||
		e == eSkill::天降灵葫 ||
		e == eSkill::落雷符 ||
		e == eSkill::唧唧歪歪 ||
		e == eSkill::雷霆万钧 ||
		e == eSkill::龙卷雨击 ||
		e == eSkill::龙腾 ||
		e == eSkill::二龙戏珠 ||
		e == eSkill::飞砂走石 ||
		e == eSkill::三昧真火 ||
		(e >= eSkill::落叶萧萧 && e < eSkill::雾杀))
	{
		return getMagicDamage(user, target, 20);
	}
	else if (skill == 1000 ||
		e == eSkill::惊心一剑 ||
		e == eSkill::死亡召唤 ||
		e == eSkill::善恶有报 ||
		e == eSkill::壁垒击破 ||
		e == eSkill::破碎无双 ||
		e == eSkill::满天花雨 ||
		e == eSkill::天雷斩 ||
		e == eSkill::飘渺式 ||
		e == eSkill::鹰击 ||
		e == eSkill::裂石 ||
		e == eSkill::浪涌 ||
		e == eSkill::惊涛怒 ||
		e == eSkill::翻江搅海)
	{
		return getPhyDamage(user, target, 0);
	}
	else if (e == eSkill::破釜沉舟)
	{
		return getPhyDamage(user, target, 45);
	}
	else if (e == eSkill::夜舞倾城)
	{
		cPropertyData *pd = g_pMainState->m_FightWorkList[user].m_pObj->getPropertyData();
		return pd->PointStr * 3 / 2 + pd->Speed.GetData() / 3;
	}
	else if ((e >= eSkill::日光华 && e <= eSkill::地裂火) ||
		e == eSkill::阎罗令 ||
		e == eSkill::天罗地网 ||
		e == eSkill::夺命咒)
	{
		return g_pMainState->m_FightWorkList[user].m_pObj->GetSkillLv(0) * 5 + 1;
	}
	else if (e == eSkill::判官令)
	{
		return g_pMainState->m_FightWorkList[user].m_pObj->GetSkillLv(0) * 7 + 1;
	}
	else if (e == eSkill::力劈华山)
	{
		return getPhyDamage(user, target, 10086);
	}
	else if (e == eSkill::剑荡四方)
	{
		return getPhyDamage(user, target, -40);
	}
	else if (e == eSkill::破血狂攻)
	{
		return getPhyDamage(user, target, 180);
	}
	else if (e == eSkill::弱点击破)
	{
		cPropertyData *pd = g_pMainState->m_FightWorkList[user].m_pObj->getPropertyData();
		pd->Pierce刺穿.d1 += 45;
		int d = getPhyDamage(user, target, 0);
		pd->Pierce刺穿.d1 -= 45;
		return d;
	}
	else if (e == eSkill::横扫千军)
	{
		return getPhyDamage(user, target, 300);
	}
	else if (e == eSkill::后发制人)
	{
		return getPhyDamage(user, target, 100);
	}
	else if (e == eSkill::烟雨剑法 ||
		e == eSkill::断岳势)
	{
		return getPhyDamage(user, target, 100);
	}
	else if (e == eSkill::黄泉之息)
	{
		cPropertyData *u = g_pMainState->m_FightWorkList[user].m_pObj->getPropertyData();
		cPropertyData *t = g_pMainState->m_FightWorkList[target].m_pObj->getPropertyData();
		int d = g_pMainState->m_FightWorkList[user].m_pObj->GetSkillLv(0);
		d = d * 3 + u->Mana.GetData() - t->Mana.GetData() + u->Atk.GetData() - t->Atk.GetData();
		return max(0, d);
	}
	else if (e == eSkill::狮搏)
	{
		return getPhyDamage(user, target, 120);
	}
	else if (e == eSkill::连环击)
	{
		return getPhyDamage(user, target, 500);
	}
	else if (e == eSkill::天崩地裂)
	{
		return getPhyDamage(user, target, 200);
	}
	else if (e == eSkill::血雨)
	{
		cPropertyData *u = g_pMainState->m_FightWorkList[user].m_pObj->getPropertyData();
		return getMagicDamage(user, target, 20) + u->HPMax.GetData() / 5;
	}
	return -1;
}


bool cAI::See(int user, int target, bool check /* = true */)
{
	if (!check || user == target)
	{
		return true;
	}
	setData(user, target);
	if (s_data1->Hide.d2 > 0)
	{
		return true;
	}
	if (s_data2->Hide.d1 == 0)
	{
		return true;
	}
	return false;
}

bool cAI::isAtkFromPoint(cPropertyData* data)
{
	return data->PointStr > (data->m_Lv + cct::MinPoint);
}

bool cAI::isMagFromPoint(cPropertyData* data)
{
	return data->PointMag > (data->m_Lv + cct::MinPoint);
}

bool cAI::isState(cObj* obj, const vector<int>& ss)
{
	forr(ss, i)
	{
		if (obj->CheckHaveState(ss[i]))
		{
			return true;
		}
	}
	return false;
}

bool cAI::isStateDMag(cObj* obj)
{
	vector<int> states =
	{ (int)eSkill::安神诀,
	(int)eSkill::分身术,
	(int)eSkill::神龙摆尾,
	(int)eSkill::定心术,
	(int)eSkill::天神护体,
	(int)eSkill::灵动九天,
	(int)eSkill::颠倒五行,
	(int)eSkill::金身舍利,
	(int)eSkill::太极护法,
	(int)eSkill::罗汉金钟,
	(int)eSkill::无畏布施,
	(int)eSkill::法术防御,
	(int)eSkill::心如明镜 };
	return isState(obj, states);
}


bool cAI::isNotState(cObj* obj, const vector<int>& ss)
{
	forr(ss, i)
	{
		if (obj->CheckHaveState(ss[i]))
		{
			return false;
		}
	}
	return true;
}

bool cAI::isPosion(cObj* obj)
{
	return isState(obj, { 50, 122 });
}

bool cAI::isMpSeal(cPcData* pc)
{
	int mp = pc->m_MengPaiID;
	return (
		mp == eMP_女儿村 ||
		mp == eMP_方寸山 ||
		mp == eMP_盘丝岭 ||
		mp == eMP_五庄观 ||
		mp == eMP_天宫 ||
		mp == eMP_无底洞);
}

bool cAI::isMpCure(cPcData* pc)
{
	int mp = pc->m_MengPaiID;
	return (mp == eMP_化生寺 ||
		mp == eMP_阴曹地府 ||
		mp == eMP_普陀山 ||
//		mp == eMP_五庄观 ||
		mp == eMP_无底洞
		);
}

bool cAI::isMpPhy(cPcData* pc)
{
	int mp = pc->m_MengPaiID;
	return (mp == eMP_大唐官府 ||
		(mp == eMP_五庄观 && isAtkFromPoint(pc)) ||
		(mp == eMP_天宫 && isAtkFromPoint(pc)) ||
		mp == eMP_狮驼岭 ||
		mp == eMP_凌波城);
}

bool cAI::isMpMag(cPcData* pc)
{
	int mp = pc->m_MengPaiID;
	return ((mp == eMP_化生寺 && isMagFromPoint(pc)) ||
		(mp == eMP_方寸山 && isMagFromPoint(pc)) ||
		mp == eMP_神木林 ||
		mp == eMP_东海龙宫 ||
		(mp == eMP_天宫 && isMagFromPoint(pc)) ||
		mp == eMP_魔王寨);
}

vector<int> cAI::getCures(int user)
{
	auto con = [&](int i)
	{
		setData(user, i);
		if (s_obj2->getPetData())
		{
			return false;
		}
		if (s_list2->CheckDie())
		{
			return false;
		}
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag() || isCanSpec();
		SetUser(uOld);
		if (!b)
		{
			return false;
		}
	//	int mp = s_obj2->getPcData()->m_MengPaiID;
		return isMpCure((cPcData*)s_data2);
	};
	return findOwners(user, cAI::eFindType::None, con);
}

vector<int> cAI::getSeals(int user)
{
	auto con = [&](int i)
	{
		setData(user, i);
		if (s_obj2->getPetData())
		{
			return false;
		}
		if (s_list2->CheckDie())
		{
			return false;
		}	
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag() || isCanSpec();
		SetUser(uOld);
		if (!b)
		{
			return false;
		}
	//	int mp = s_obj2->getPcData()->m_MengPaiID;
		return isMpSeal((cPcData*)s_data2);
	};
	return findOwners(user, cAI::eFindType::None, con);
}

vector<int> cAI::getCureSeals(int user)
{
	auto con = [&](int i)
	{
		setData(user, i);
		if (s_obj2->getPetData())
		{
			return false;
		}
		if (s_list2->CheckDie())
		{
			return false;
		}
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag() || isCanSpec();
		SetUser(uOld);
		if (!b)
		{
			return false;
		}
	//	int mp = s_obj2->getPcData()->m_MengPaiID;
		return isMpSeal((cPcData*)s_data2) || isMpCure((cPcData*)s_data2);
	};
	return findOwners(user, cAI::eFindType::None, con);
}

vector<int> cAI::getFires(int user)
{
	vector<int> ts;
	if (user >= 10)
	{
		return ts;
	}
	for (int i = 10; i < 20; ++i)
	{
		if (!g_pMainState->m_FightWorkList[i].isExist)
		{
			continue;
		}
		if (g_pMainState->m_FightWorkList[i].CheckDie())
		{
			continue;
		}
		if (!g_pMainState->m_FightWorkList[i].m_pObj->m_ConductFire.m_NeedShow)
		{
			continue;
		}
		ts.push_back(i);
	}
	return ts;
}

bool cAI::isHpLessThan(cPropertyData* data, int rate)
{
	return data->m_HP < data->HPMax.GetData() * rate / 100;
}

