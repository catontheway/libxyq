
#include "global.h"

#if ccc_date
BOOL cPetData::LeveUp(int lv, bool isBaby, bool isAdd)
{
	if (!lv)return FALSE;
	m_ATK.AddDataOriginal(-CountATK());//伤害
	m_DEF.AddDataOriginal(-CountDEF());//防
	m_HPMax.AddDataOriginal(-CountHP());//HP
	m_MPMax.AddDataOriginal(-CountMP());//MP
	m_Wakan.AddDataOriginal(-CountWakan());//灵力
	m_SPD.AddDataOriginal(-CountSpd());//速度
	m_Evade.AddDataOriginal(-CountEvade());//躲闪
	m_HIT.AddDataOriginal(-CountHit());//命中

	m_LV += lv;

	////////////////////////////////////////////////////////////////////////// 呵呵哒 自动加点在这里
	if (isAdd)
	{
		m_ProPertyAtk += (m_AddPoint.atk + 1)*lv;
		m_ProPertyDef += (m_AddPoint.def + 1)*lv;
		m_ProPertyHP += (m_AddPoint.hp + 1)*lv;
		m_ProPertyMag += (m_AddPoint.mp + 1)*lv;
		m_ProPertySpd += (m_AddPoint.spd + 1)*lv;
	}
	else
	{
		m_ProPertyAtk += lv;
		m_ProPertyDef += lv;
		m_ProPertyHP += lv;
		m_ProPertyMag += lv;
		m_ProPertySpd += lv;
		m_ProPerty未分配点 += 5 * lv;
	}

	_isBabyModeForLvup = isBaby;
	//计算新属性
	m_ATK.AddDataOriginal(CountATK());//伤害
	m_DEF.AddDataOriginal(CountDEF());//防
	m_HPMax.AddDataOriginal(CountHP());//HP
	m_MPMax.AddDataOriginal(CountMP());//MP
	m_Wakan.AddDataOriginal(CountWakan());//灵力
	m_SPD.AddDataOriginal(CountSpd());//速度
	m_Evade.AddDataOriginal(CountEvade());//躲闪
	m_HIT.AddDataOriginal(CountHit());//命中


	m_PhysicalMax += 5 * lv; //体力上限;     
	m_EnergyMax += 5 * lv;  //活力上限
	ExpMax = GetCharacterExp(m_LV);
	FillHPMP();
	return TRUE;

}


void cPetData::AddHpZZ(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	m_HPMax.AddDataOriginal(-CountHP());
	m_ZiZhi.m_HPZZ += num;
	m_HPMax.AddDataOriginal(CountHP());
	m_HPHurtMax = m_HPMax.GetData();
	m_HP = m_HPHurtMax;
	_isBabyModeForLvup = isBabyOld;
}
void cPetData::AddGrowing(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	int atk, def, mag, spd, hp;
	atk = m_ProPertyAtk;
	def = m_ProPertyDef;
	spd = m_ProPertySpd;
	hp = m_ProPertyHP;
	mag = m_ProPertyMag;
	bool isBB = true;
	AddProPertyAtk(-atk);
	AddProPertyDef(-def);
	AddProPertyMag(-mag);
	AddProPertyHp(-hp);
	AddProPertySpd(-spd);
	m_ZiZhi.m_Growing += num;
	AddProPertyAtk(atk);
	AddProPertyDef(def);
	AddProPertyMag(mag);
	AddProPertyHp(hp);
	AddProPertySpd(spd);
	_isBabyModeForLvup = isBabyOld;
}

void cPetData::AddMagZZ(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	m_MPMax.AddDataOriginal(-CountMP());
	m_Wakan.AddDataOriginal(-CountWakan());
	m_ZiZhi.m_MAGZZ += num;
	m_MPMax.AddDataOriginal(CountMP());
	m_Wakan.AddDataOriginal(CountWakan());
	m_MP = m_MPMax.GetData();
	_isBabyModeForLvup = isBabyOld;
}

void cPetData::AddAtkZZ(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	m_ATK.AddDataOriginal(-CountATK());
	m_HIT.AddDataOriginal(-CountHit());
	m_ZiZhi.m_ATKZZ += num;
	m_ATK.AddDataOriginal(CountATK());
	m_HIT.AddDataOriginal(CountHit());
	_isBabyModeForLvup = isBabyOld;
}
void cPetData::AddAvoidZZ(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	m_Evade.AddDataOriginal(-CountEvade());
	m_ZiZhi.m_AVOIDZZ += num;
	m_Evade.AddDataOriginal(CountEvade());
	_isBabyModeForLvup = isBabyOld;
}
void cPetData::AddSpdZZ(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	m_SPD.AddDataOriginal(-CountSpd());
	m_ZiZhi.m_SPDZZ += num;
	m_SPD.AddDataOriginal(CountSpd());
	_isBabyModeForLvup = isBabyOld;
}

void cPetData::AddDefZZ(int num)
{
	if (!num || !_isBabyModeForLvup)return;
	bool isBabyOld = _isBabyModeForLvup;
	_isBabyModeForLvup = true;
	m_DEF.AddDataOriginal(-CountDEF());
	m_ZiZhi.m_DEFZZ += num;
	m_DEF.AddDataOriginal(CountDEF());
	_isBabyModeForLvup = isBabyOld;
}




int cPetData::CountATK()
{
	bool isBB = _isBabyModeForLvup;
	int atk = m_LV * m_ZiZhi.m_ATKZZ * (1400 + 10 * m_ZiZhi.m_Growing) / 750000 +
		m_ProPertyAtk * m_ZiZhi.m_Growing / 100;
	if (isBB)
	{
		return atk;
	}
	float v = 0;
	for (int i = m_LV + MyTest::getInstance()->maxSkillLv - MyTest::getInstance()->maxRoleLv; i >= 0; --i)
	{
		v += 2.51f + .02f * i;
	}
	v += m_ProPertyAtk * .77f;
	return (int)v;

}

int cPetData::CountDEF()
{
	bool isBB = _isBabyModeForLvup;
	// (9.4f + 19 * m_ZiZhi.m_Growing / 3.0f)
	int def = (m_LV*m_ZiZhi.m_DEFZZ) * 19 / 7500 +
		(m_ProPertyDef*m_ZiZhi.m_Growing * 4) / 300;
	if (isBB)
	{
		return def;
	}
	float v = 0;
	for (int i = m_LV + MyTest::getInstance()->maxSkillLv - MyTest::getInstance()->maxRoleLv; i >= 0; --i)
	{
		v += 1 + .02f * i;
	}
	v += m_ProPertyDef * 1.6f;
	return (int)v;
}

int cPetData::CountHP()
{
	bool isBB = _isBabyModeForLvup;
	int hp = (m_LV*m_ZiZhi.m_HPZZ) / 1000 +
		m_ProPertyHP * m_ZiZhi.m_Growing * 6 / 100;
	if (isBB)
	{
		return hp * 2;
	}
	return 100 + m_ProPertyHP * 6;
}

int cPetData::CountWakan()
{
	bool isBB = _isBabyModeForLvup;
	//灵力=等级*(法力资质+1640)*(成长+1)/7500+体质*0.3+法力*0.7+力量*0.4+耐力*0.2
	int	wakan = (m_LV* (m_ZiZhi.m_MAGZZ + 1640)*(m_ZiZhi.m_Growing + 100) / 75000 +
		m_ProPertyHP * 3 +
		m_ProPertyMag * 7 +
		m_ProPertyAtk * 4 +
		m_ProPertyDef * 2
		) / 10;
	if (isBB)
	{
		return wakan;
	}
	float v = 0;
	for (int i = m_LV + MyTest::getInstance()->maxSkillLv - MyTest::getInstance()->maxRoleLv; i >= 0; --i)
	{
		v += .5f + .01f * i;
	}
	v += m_ProPertyMag * .7f + m_ProPertyHP * .3f + m_ProPertyAtk * .4f + m_ProPertyDef * .2f;
	return (int)v;
}

int cPetData::CountMP()
{
	bool isBB = _isBabyModeForLvup;
	int mp = m_LV * m_ZiZhi.m_MAGZZ / 500 + m_ZiZhi.m_Growing*m_ProPertyMag * 3 / 100;
	if (isBB)
	{
		return mp;
	}
	return 80 + m_ProPertyMag * 4;
}

int cPetData::CountSpd()
{
	bool isBB = _isBabyModeForLvup;
	int spd = (m_ZiZhi.m_SPDZZ*m_ProPertySpd) / 1000;
	if (isBB)
	{
		return spd;
	}
	return int(m_ProPertySpd * .7f + m_ProPertyHP * .1f + m_ProPertyAtk * .1f + m_ProPertyDef * .1f);
}

int cPetData::CountEvade()
{
	bool isBB = _isBabyModeForLvup;
	int evade = m_ProPertySpd * m_ZiZhi.m_AVOIDZZ / 500;
	if (isBB)
	{
		return evade;
	}
	float v = 0;
	for (int i = m_LV + MyTest::getInstance()->maxSkillLv - MyTest::getInstance()->maxRoleLv; i >= 0; --i)
	{
		v += 2 + .02f * i;
	}
	v += m_ProPertySpd;
	return (int)v;
}

int cPetData::CountHit()
{
	bool isBB = _isBabyModeForLvup;
	int hit = m_ProPertyAtk * 3;
	if (isBB)
	{
		return hit;
	}
	float v = 0;
	v += m_ProPertyAtk * 2.31f;
	return (int)v;
}






void cPCData::Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip)
{
	if (lv == m_LV)return;
	LeveUp(lv - m_LV, isBabyMode, isAdd);
	FollowSkill();
	FollowItem(true);
	if (!isEquip)
	{
		return;
	}
	FollowEuip();
	FullFuzhuBut暗器();
	FollowXiulian();
	FollowBaby();
	FillHPMP();
}



int cPCData::getEquipAtk()
{
	int atk = 0;
	for (int i = 0; i < 6; ++i)
	{
		const vector<int>& prop = m_Equip[i].m_Property;
		for (int k = 0; k < prop.size(); k += 2)
		{
			if (prop[k] != eProPerty伤害)
			{
				continue;
			}
			atk += prop[k + 1];
		}
	}
	if (m_Equip[2].m_Num && !m_Equip[2].m_Property.size())
	{
		asert(false, "武器空属性(战斗)");
		atk += 37 + (m_LV / 10) * 40 + 200;
	}
	return atk;
}





void cPetData::Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip)
{
	if (lv == m_LV)return;
	LeveUp(lv - m_LV, isBabyMode, isAdd);
	if (isEquip)
	{
		sItem2 item;
		item.m_Num = 1;
		int itemid = (m_LV/* - MyTest::getInstance()->lvGapFromRoleAndBaby*/) / 10;

		if (itemid > 16)itemid = 16;
		//		if (0 == m_PetEquip[0].GetNum() || m_PetEquip[0].GetID() < itemid)
		{
			// 			int baoshinum = itemid;
			// 			if (baoshinum > g_pMainState->m_GlobalButton[5])
			// 				baoshinum = g_pMainState->m_GlobalButton[5];
			for (int j = 0; j < 3; j++)
			{
				if (m_PetEquip[j].GetNum() && !m_PetEquip[j].m_Property.size())
				{
					asert(false, "宝宝装备空属性");
				}
				//				sItem2 baoshi;
				//				int baoshiid = -1;
				item.Set(32 + j, itemid);
				int dusbin = (m_AddPoint.atk > 0) ? 0 : 1;
				g_pMainState->m_ItemManage.AutoItemProperty(&item, m_Popularity, dusbin);
				g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, eMP_无);
				// 				switch (j)
				// 				{
				// 				case 0:
				// 					if (m_AddPoint.atk > 2)
				// 						baoshiid = 15;
				// 					else
				// 						baoshiid = 12;
				// 					break;
				// 				case 1:
				// 					baoshiid = 11;
				// 					break;
				// 				case 2:
				// 					baoshiid = 16;
				// 					break;
				// 				}
				// 				baoshi.Set(29, baoshiid);
				// 				for (int i = 0; i < baoshinum; i++)
				// 					g_pMainState->m_ItemManage.XiangQian(item, baoshi);
				PetEquip(j, -1);
				m_PetEquip[j] = item;
				PetEquip(j, 1);
			}
		}
		FillHPMP();
	}
}



void cPCData::FollowlvAddPoint(int lv, bool isBabyMode, bool isEquip, bool isXiulian)
{
	if (lv == m_LV)return;
	LeveUp(lv - m_LV, isBabyMode, true);
	FollowSkill();
	FollowItem(isXiulian);
	if (isEquip)
	{
		FollowEuip(isXiulian);
	}
	if (isXiulian)
	{
		FullFuzhuBut暗器();
		FollowXiulian();
	}
	FollowBaby();
	FillHPMP();
}


void cPCData::FollowSkill()
{
	if (m_MengPaiID < 0)
		return;
	int lvadd = MyTest::getInstance()->maxSkillLv - MyTest::getInstance()->maxRoleLv + m_LV - m_MengPaiSkillLV[0];

	if (!lvadd)return;

	for (int i = 0; i < 7; i++)
	{
		g_pMainState->m_SkillManager.lvUpMainSkill(*this, lvadd, i);
	}
}

void cPCData::FollowXiulian()
{
	int maxlv = (m_LV - 20) / 5;
	if (maxlv < 0)
	{
		maxlv = 0;
	}
	else if (maxlv > MyTest::getInstance()->maxXiuLian)
	{
		maxlv = MyTest::getInstance()->maxXiuLian;
	}
	m_XiuLian.Set(maxlv, maxlv, maxlv, maxlv);
	m_BBXiuLian.Set(maxlv, maxlv, maxlv, maxlv);
	if (maxlv > g_pMainState->m_GlobalButton[6])
	{
		maxlv = g_pMainState->m_GlobalButton[6];
	}
}

void cPCData::FollowEuip(bool is穿盔甲 /* = true */)
{
	int idx = g_pMainState->m_InterfaceItem.FindIdle(0, 60, *this);
	if (idx < 0)
	{
		return;
	}
	sItem2 item;
	item.m_Num = 1;
	int lv = m_LV;
	int maxlv = m_LV;

	//	if ((!m_Equip[2].m_Num) || g_pMainState->m_ItemManage.GetlvByID(m_Equip[2].GetType(), m_Equip[2].GetID()) < lv - 9)
	{
		int baoshinum = maxlv / 10;
		if (baoshinum > g_pMainState->m_GlobalButton[5])
			baoshinum = g_pMainState->m_GlobalButton[5];
		//项链,腰带,鞋子	
		for (int i = 0; i < 3; i++)
		{
			item.Set(19 + i, g_pMainState->m_ItemManage.GetIDByLv(19 + i, lv));
			int desbin;
			if (i == 0)
			{
				desbin = MyTest::getInstance()->getDesbinOf项链(m_MengPaiID, _spesialSkills[1]);
			}
			else if (i == 1)
			{
				desbin = MyTest::getInstance()->getDesbinOf腰带(m_MengPaiID, _spesialSkills[4]);
			}
			else if (i == 2)
			{
				desbin = MyTest::getInstance()->getDesbinOf鞋子(m_MengPaiID, false, _spesialSkills[5]);
			}
			g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin);
			g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, (eMengPai)m_MengPaiID);
			asert(item.m_Property.size(), "装备创建空属性");
			g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
			g_pMainState->m_InterfaceItem.UseItem(idx, *this);
		}



		//头盔 分男女
		if (CanEquip(15))
			item.Set(15, g_pMainState->m_ItemManage.GetIDByLv(15, lv));
		else
			item.Set(16, g_pMainState->m_ItemManage.GetIDByLv(16, lv));
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, MyTest::getInstance()->getDesbinOf头盔(m_MengPaiID, _spesialSkills[0]));
		g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, (eMengPai)m_MengPaiID);
		// 				sItem2 baoshi;
		// 				int id;
		// 				if (m_AddPoint.atk > 1)id = 2;
		// 				else id = 10;
		// 				baoshi.Set(29, id);
		// 				for (int i2 = 0; i2 < baoshinum; i2++)g_pMainState->m_ItemManage.XiangQian(item, baoshi);
		asert(item.m_Property.size(), "头盔创建空属性");
		g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
		g_pMainState->m_InterfaceItem.UseItem(idx, *this);
		if (is穿盔甲)
		{
			// 衣服 也分
			if (CanEquip(17))
				item.Set(17, g_pMainState->m_ItemManage.GetIDByLv(17, lv));
			else
				item.Set(18, g_pMainState->m_ItemManage.GetIDByLv(18, lv));

			g_pMainState->m_ItemManage.AutoItemProperty(&item, this, MyTest::getInstance()->getDesbinOf铠甲(m_MengPaiID, _spesialSkills[3]));
			g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, eMengPai(m_MengPaiID));
			// 				baoshi.Set(29, 10);
			// 				for (int i2 = 0; i2 < baoshinum; i2++)g_pMainState->m_ItemManage.XiangQian(item, baoshi);

			asert(item.m_Property.size(), "衣服创建空属性");
			g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
			g_pMainState->m_InterfaceItem.UseItem(idx, *this);
		}

		//武器
		FollowWeapon();

		FillHPMP();
	}
}

void cPCData::FollowWeapon()
{
	int idx = g_pMainState->m_InterfaceItem.FindIdle(0, 60, *this);
	if (idx < 0)
	{
		return;
	}
	sItem2 item;
	item.m_Num = 1;
	int lv = m_LV;
	int i = 2;
	int typelist[2];
	GetWeaponType(modeid, typelist[0], typelist[1]);
	int k = typelist[rand() % 2];
	if (typelist[1] == -1)
		k = typelist[0];
	item.Set(k, g_pMainState->m_ItemManage.GetIDByLv(k, lv));
	g_pMainState->m_ItemManage.AutoItemProperty(&item, this, MyTest::getInstance()->getDesbinOf武器(m_MengPaiID, _spesialSkills[2]));
	g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, eMengPai(m_MengPaiID));
	// 	if (m_AddPoint.atk > 1)id = 2;
	// 	else id = 8;
	// 
	// 	baoshi.Set(29, id);
	// 	for (int i2 = 0; i2 < baoshinum; i2++)g_pMainState->m_ItemManage.XiangQian(item, baoshi);
	asert(item.m_Property.size(), "武器创建空属性");
	g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
	g_pMainState->m_InterfaceItem.UseItem(idx, *this);
}

void cPCData::FollowShoe()
{
	int idx = g_pMainState->m_InterfaceItem.FindIdle(0, 60, *this);
	if (idx < 0)
	{
		return;
	}
	sItem2 item;
	item.m_Num = 1;
	int lv = m_LV;
	int i = 2;
	item.Set(19 + i, g_pMainState->m_ItemManage.GetIDByLv(19 + i, lv));
	////////////////////////////////////////////////////////////////////////// 呵呵哒 带装备
	int desbin;
	eMengPai e = (eMengPai)m_MengPaiID;
	// 	if (!is穿盔甲 && e != eMP_大唐官府 && e != eMP_狮驼岭)
	// 	{
	// 		e = eMP_东海龙宫;
	// 	}
	desbin = MyTest::getInstance()->getDesbinOf鞋子(e, MyTest::getInstance()->isAutoAtkMode, _spesialSkills[5]);
	g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin);
	g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, (eMengPai)m_MengPaiID);
	// 	sItem2 baoshi;
	// 	int id;
	// 	switch (item.GetType())
	// 	{
	// 	case 19://项链
	// 		id = 7;	
	// 		break;
	// 	case 20:
	// 		id = 0;
	// 		break;
	// 	default:
	// 		if (m_AddPoint.mp > 2)id = 8;
	// 		else id = 1;
	// 		break;
	// 	}
	// 	baoshi.Set(29,id);		
	// 	for (int i2 = 0; i2<baoshinum; i2++)
	// 		g_pMainState->m_ItemManage.XiangQian(item, baoshi);
	asert(item.m_Property.size(), "鞋子创建空属性");
	g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
	//	int def = m_DEF.GetData();////////
	g_pMainState->m_InterfaceItem.UseItem(idx, *this);
	//	def = m_DEF.GetData();////////
	//	int k = 0;
}

void cPCData::FollowEquipAll()
{
	sItem2 item;
	item.m_Num = 1;
	int lv = m_LV;

	vector<int> ems;
	for (int i = 0; i < 60; ++i)
	{

		if (m_Item[i].GetNum() > 0 && (m_Item[i].GetType() == 24 || m_Item[i].GetType() == 27 || m_Item[i].GetType() == 28))
		{
			continue;
		}
		ems.push_back(i);
	}

	auto findEmpty = [&](int id)
	{
		if (this->m_IDinFightList)
		{
			return id;
		}
		if (ems.empty())
		{
			return -1;
		}
		int i = ems.back();
		ems.pop_back();
		return i;
	};
	int idx = -1;
	item.Set(21, g_pMainState->m_ItemManage.GetIDByLv(21, lv));
	int desbin = MyTest::getInstance()->getDesbinOf鞋子(m_MengPaiID, false, _spesialSkills[5]);
	for (int i = 0; i < 3; ++i)
	{
		idx = findEmpty(57 + i);
		if (idx < 0)
		{
			return;
		}
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin / 10 * 10 + i);
		g_pMainState->m_ItemManage.AutoFuShi(&item, lv, (eMengPai)m_MengPaiID);
		g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
	}

	item.Set(20, g_pMainState->m_ItemManage.GetIDByLv(20, lv));
	desbin = MyTest::getInstance()->getDesbinOf腰带(m_MengPaiID, _spesialSkills[4]);
	for (int i = 0; i < 2; ++i)
	{
		idx = findEmpty(55 + i);
		if (idx < 0)
		{
			return;
		}
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin / 10 * 10 + i);
		g_pMainState->m_ItemManage.AutoFuShi(&item, lv, (eMengPai)m_MengPaiID);
		g_pMainState->m_InterfaceItem.Add(idx/*55 + i*/, *this, &item);
	}


	//铠甲分男女
	int hel = CanEquip(17) ? 17 : 18;
	item.Set(hel, g_pMainState->m_ItemManage.GetIDByLv(hel, lv));
	desbin = MyTest::getInstance()->getDesbinOf铠甲(m_MengPaiID, _spesialSkills[3]);
	for (int i = 0; i < 3; ++i)
	{
		idx = findEmpty(52 + i);
		if (idx < 0)
		{
			return;
		}
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin / 10 * 10 + i);
		g_pMainState->m_ItemManage.AutoFuShi(&item, lv, (eMengPai)m_MengPaiID);
		g_pMainState->m_InterfaceItem.Add(idx/*52 + i*/, *this, &item);
	}

	//武器
	int typelist[2];
	GetWeaponType(modeid, typelist[0], typelist[1]);
	for (int i = 0; i < 2; ++i)
	{
		idx = findEmpty(50 + i);
		if (idx < 0)
		{
			return;
		}
		int k = typelist[i];
		if (typelist[1] == -1) k = typelist[0];
		item.Set(k, g_pMainState->m_ItemManage.GetIDByLv(k, lv));
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, MyTest::getInstance()->getDesbinOf武器(m_MengPaiID, _spesialSkills[2]));
		g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, eMengPai(m_MengPaiID));
		g_pMainState->m_InterfaceItem.Add(idx/*50 + i*/, *this, &item);
	}

	idx = findEmpty(49);
	if (idx < 0)
	{
		return;
	}
	item.Set(19, g_pMainState->m_ItemManage.GetIDByLv(19, lv));
	desbin = MyTest::getInstance()->getDesbinOf项链(m_MengPaiID, _spesialSkills[1]);
	g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin);
	g_pMainState->m_ItemManage.AutoFuShi(&item, lv, (eMengPai)m_MengPaiID);
	g_pMainState->m_InterfaceItem.Add(idx/*49*/, *this, &item);



	//头盔分男女
	hel = CanEquip(15) ? 15 : 16;
	item.Set(hel, g_pMainState->m_ItemManage.GetIDByLv(hel, lv));
	desbin = MyTest::getInstance()->getDesbinOf头盔(m_MengPaiID, _spesialSkills[0]);
	for (int i = 0; i < 2; ++i)
	{
		idx = findEmpty(47 + i);
		if (idx < 0)
		{
			return;
		}
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin / 10 * 10 + i);
		g_pMainState->m_ItemManage.AutoFuShi(&item, lv, (eMengPai)m_MengPaiID);
		g_pMainState->m_InterfaceItem.Add(idx/*47 + i*/, *this, &item);
	}

}



void cPCData::FollowItem(bool isUnseal)
{
	////////////////////////////////////////////////////////////////////////// 物品 呵呵哒
	//加HP  0
	// 				int itemid = 2 + g_pCharacter->m_PCData.m_LV / 17;
	// 				if (itemid > 11)itemid = 11;
	// 				m_Item[0].Set(22, itemid);
	// 				m_Item[0].m_Num = 60;
	// 				//全体加HP  1
	// 				itemid = 12 + m_LV / 29;
	// 				if (itemid > 18)itemid = 18;
	// 				m_Item[1].Set(22, itemid);
	// 				m_Item[1].m_Num = 20;
	// 				//加MP  2
	// 				itemid = 19 + m_LV / 29;
	// 				if (itemid > 25)itemid = 25;
	// 				m_Item[2].Set(22, itemid);
	// 				m_Item[2].m_Num = 30;
	// 				//全体加MP  3
	// 				itemid = 26 + m_LV / 25;
	// 				if (itemid > 33)itemid = 33;
	// 				m_Item[3].Set(22, itemid);
	// 				m_Item[3].m_Num = 20;
	// 				//
	// 				//加血加伤  4
	// 				itemid = 40 + m_LV / 50;
	// 				if (itemid > 43)itemid = 43;
	// 				m_Item[4].Set(22, itemid);
	// 				m_Item[4].m_Num = 30;
	// 				//复活  5
	// 				itemid = 44 + m_LV / 100;
	// 				if (itemid > 45)itemid = 45;
	// 				m_Item[5].Set(22, itemid);
	// 				m_Item[5].m_Num = 20;
	// 				//解封  6
	// 				itemid = 49;
	// 				m_Item[6].Set(22, itemid);
	// 				m_Item[6].m_Num = 30;
	// 				//加CP  7
	// 				itemid = 54 + m_LV / 50;
	// 				if (itemid > 57)itemid = 47;
	// 				m_Item[7].Set(22, itemid);
	// 				m_Item[7].m_Num = 30;
	// 				
	// 				//暗器  8
	// 				itemid = m_LV / 17;
	// 				if (itemid > 9)itemid = 9;
	// 				m_Item[8].Set(25, itemid);
	// 				m_Item[8].m_Num = 900;

	vector<int> 药品s = { 18, 18, 43, 43, 17, 45, 49, 54 };
	药品s = { 45, 45, 43, 43, 45, 45, 49, 54 };
	if (isUnseal)
	{
		forv(药品s, i)
		{
			m_Item[i].Set(22, 药品s[i]);
			m_Item[i].m_Num = 5;
		}
	}
	else
	{
		for (auto i : { 2, 3, 5 })
		{
			m_Item[i].Set(22, 药品s[i]);
			m_Item[i].m_Num = MyTest::getInstance()->药品数量;
		}
	}

	int anqi = m_LV / 15;
	if (anqi > 9) anqi = 9;
	m_Item[8].Set(25, anqi);
	m_Item[8].m_Num = MyTest::getInstance()->药品数量;
}

void cPCData::FollowBaby()
{
	//更新召唤兽
	int petnum = m_NumofBB;
	int maxlv = m_LV + MyTest::getInstance()->lvGapFromRoleAndBaby;
	if (maxlv > MyTest::getInstance()->maxBabyLv)
	{
		maxlv = MyTest::getInstance()->maxBabyLv;
	}
	for (int i = 0; i < petnum; i++)
	{
		m_pPetDataList[i]->m_PetDataZZ.m_Popularity = m_Popularity;
		m_pPetDataList[i]->m_PetDataZZ.Followlv(maxlv, true, true, true);
	}
}

void cPCData::FullFuzhuBut暗器()
{
	lvUpFuZhuSkill(160, 0);
	lvUpFuZhuSkill(160, 1);
	lvUpFuZhuSkill(160, 2);
	lvUpFuZhuSkill(m_LV, 3);
}


#endif