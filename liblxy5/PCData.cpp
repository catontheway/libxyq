#include "_global.h"

cPcData::~cPcData()
{
	for (int i = m_NumofBB - 1; i >= 0; i--)
	{
		RemovePet(i);
	}

// 	if (m_pCardPetData)
// 		SAFE_DELETE(m_pCardPetData);
}

cPcData::cPcData()
{
//	_isBabyModeForLvup = false;
	Reset();
//	m_pCardPetData = new cPet;
//	m_pPets.resize(8);
//	PointRemain = cct::get()->point额外;
}

void cPcData::Reset()
{
	cPropertyData::Reset();
	// 	m_traderLV = 0;
	// 	m_traderExp = 0;
	//辅助技能
	forr (m_FuZhuSkillLvList, i)
	{
		m_FuZhuSkillLvList[i] = 0;
	}
	forr(m_Accelarate, i)
		m_Accelarate[i] = -1;

	// 	cPropertyData* pPetdata = this;
	// 	pPetdata->Reset(); 

	//脸
	m_faceMood = 0;
	//变身
//	m_bUseCard = false;
	m_CardPetID = -1;
	//m_CardRanSe.Reset();//有一定几率变成变异召唤兽
	//	m_pCardPetData = 0;
	//坐骑
	m_bOnZuoQi = false; //是否坐上坐骑
	m_ZQ = -1;  //坐骑ID
	m_ZuoQiRanSe.partnum = 0;//坐骑染色
	m_ZhuangShiRanSe.partnum = 0;//装饰染色
	m_ZuoQi.m_pZuoQi = 0;
	//持有的召唤兽数
	//	int  m_NumofBB = 0;
	m_FightPetID = -1;
	//经验钱加成
	m_SkillEnablelist.clear();
	//	m_MengPaiPoint = 0;
	m_NumofSpecial = 0;
	forr(m_SpecialSkillList, i)
	{
		m_SpecialSkillList[i] = -1;  //装备特技
	}
	//门派
	m_MengPaiID = -1;
	forr(m_MengPaiSkillLvs, i)
		m_MengPaiSkillLvs[i] = 0;
	// 	m_Popularity = 0;  //人气
	// 	//帮派
	// 	m_BangPaiID = -1;
	// 	m_BangPaiPoint = 0;
	//修炼
	m_XiuLian.Reset();
	forr(m_Money, i)
		m_Money[i] = 0;       //钱  存银 储备金

}


bool cPcData::AddMoney(int xianjin, int chubei /*= 0*/, int cunyin /*= 0*/, bool bCost)
{
	INT64 old[3];
	INT64 data = 0;
	for (int i = 0; i < 3; i++)
	{
		old[i] = m_Money[i];
	}
	bool ret = true;
	if (xianjin)
		if (AddUpZero(m_Money[0], xianjin))ret = false;
	if (cunyin)
		if (AddUpZero(m_Money[1], cunyin))ret = false;
	if (chubei)
		data = AddUpZero(m_Money[2], chubei);
	if (data)if (AddUpZero(m_Money[0], data))ret = false;
	if (!ret)
	{
		if (!bCost)
		{
			for (int i = 0; i < 3; i++)
			{
				m_Money[i] = old[i];
			}
		}
	}
	for (int i = 1; i < 3; i++)
	{
		m_Money[0] += m_Money[i];
		m_Money[i] = 0;
	}
	return ret;
}


bool cPcData::AddExp(int exp, int expbb/*=0*/, bool bCost)
{
	bool bRet = true;
	if (exp)
	{
		m_EXP += exp;
		if (m_EXP < 0)
		{
			if (bCost)
				m_EXP = 0;
			else
				m_EXP -= exp;
			bRet = false;
		}
	}
	if (expbb)
	{
		if (-1 < m_FightPetID)
		{
			INT64 & petexp = m_pPets[m_FightPetID]->m_PetData.m_EXP;
			petexp += expbb;
			if (petexp < 0)
			{
				if (bCost)
					petexp = 0;
				else petexp -= exp;;
				bRet = false;
			}
			else
			{
				g_pMainState->m_pFightState->CheckPetExp();
			}
		}
	}
	return bRet;
}


int cPcData::FindItem(int type, int id)
{
	forr(m_Items, i)
	{
		if (m_Items[i].GetNum())
		{
			if (m_Items[i].GetType() == type)
				if (m_Items[i].GetID() == id)
				{
				return i;
				}
		}
	}
	return -1;
}


void cPcData::SetCard(int id)
{
	if (id < 0)return;
	m_CardPetID = id;

// 	if (!m_pCardPetData)m_pCardPetData = new cPet;
// 	m_pCardPetData->SetData(g_pMainState->m_PetDataManager.GetPetData(m_CardPetID));
}


sItem2* cPcData::GetItem(int ID)
{
	if (ID >= 12000)//召唤兽装备
	{
		if (-1 == m_FightPetID)
			return 0;
		return &m_pPets[m_FightPetID]->m_PetData.m_Equips[ID - 12000];
	}
	if (ID < 10000)//各种物品
		return ID >= m_Items.size() ? &m_Fabaos[ID - m_Items.size()] : &m_Items[ID];
	if (ID == 11000)//坐骑装饰
		return &m_ZuoQi.m_ZhuangShi;
	return &m_Equips[ID - 10000];//角色装备
}


bool cPcData::Equip(sItem2& item, int m_bEquip)
{
	if (item.GetNum() < 1)
		return false;
	if (m_bEquip == 1)
	{
		if (!CanEquip(item))
			return false;
		if (!item.m_Property.size())
		{
//			g_pMainState->m_Tags.Add("未鉴定");
			return false;
		}
	}
	// 	int nowpos = 5;
	// 	EquipExtra(item.m_Property, nowpos, m_bEquip);
	int pos;
	switch (item.GetType())
	{
	case 15:
	case 16:
		pos = 0;
		break;
	case 17:
	case 18:
		pos = 3;
		break;
	case 19:
		pos = 1;
		break;
	case 20:
		pos = 4;
		break;
	case 21:
		pos = 5;
		break;
	default:
		pos = 2;
		break;
	}
	// 	if (m_bEquip)m_SpecialSkillList[pos] = item.m_Property[1];
	// 	else m_SpecialSkillList[pos] = -1;
	// 	for (int i = 2; i < 5; i++)
	// 		g_pMainState->m_SkillManager.SetSpecialSkill2(this, item.m_Property[i], m_bEquip);

	if (2 == pos)
	{
		m_pWeaponData2 = 0;
		m_pCharacterData2 = 0;
	}

	return true;
}



bool cPcData::CanEquip(int type)
{
	if (modeid < 0)
	{
		return false;
	}
	return	g_pMainState->m_pCharacterDataList[modeid].CanEquip(type);
}



bool cPcData::CanEquip(sItem2& item)
{
	if (modeid < 0)
	{
		return false;
	}

// 	if (!CanEquip(item.GetType()))
// 	{
// 		return false;
// 	}
// 	if (m_Lv < g_pMainState->m_ItemManage.GetlvByID(item.GetType(), item.GetID()))
// 	{
// 		return false;
// 	}
// 无级别
	return m_Lv >= item.m_pItemData->GetLv() || cct::isWJB(&item);
}


int cPcData::getEquipAtk()
{
	int atk = 0;
	forr(m_Equips, i)
	{
		if (m_Equips[i].m_Num != 1)
		{
			continue;
		}
		const auto& props = m_Equips[i].m_Property;
		for (int i = 0; i < props.size(); i += 2)
		{
			switch (props[i])
			{
			case eProPerty伤害: 
				atk += (props[i + 1]); 
				break;
			}
		}
	}
	return atk;
}




void cPcData::autoEquip(bool isNormal, bool isWJB /* = false */, int mp /* = -1 */)
{
	int lv = m_Lv;
	sItem2 item;
	item.m_Num = 1;
	sItem* pit = new sItem;
	item.m_pItemData = pit;
	pit->SetLv(lv);

// 	{ eItem::宝石b, 0x00, 0x0ADECF25, 0x41656FA0, "光芒石", "镶嵌到腰带上气血+40" },
// 	{ eItem::宝石b, 0x01, 0xFADEE7FC, 0x750B0C1A, "黑宝石", "镶嵌到腰带或鞋子上速度+8" },
// 	{ eItem::宝石b, 0x02, 0xA5E276AE, 0xD9DCF799, "红玛瑙", "镶嵌到武器或头盔上命中+25" },
// 	{ eItem::宝石b, 0x03, 0x651D319C, 0xD7E9FDB3, "红宝石", "镶嵌到项链或鞋子上火抗+2" },
// 	{ eItem::宝石b, 0x04, 0x88253E8D, 0x4A96C39E, "黄宝石", "镶嵌到项链或鞋子上雷抗+2" },
// 	{ eItem::宝石b, 0x05, 0x791427E4, 0x67107BB6, "蓝宝石", "镶嵌到项链或鞋子上水抗+2" },
// 	{ eItem::宝石b, 0x06, 0xE59EFA68, 0x0DCD4F81, "绿宝石", "镶嵌到项链或鞋子上土抗+2" },
// 	{ eItem::宝石b, 0x07, 0x84D01F40, 0xCB7F4075, "舍利子", "镶嵌到项链或衣服上灵力+6" },
// 	{ eItem::宝石b, 0x08, 0x2CB3CC8D, 0xC365BC0A, "神秘石", "镶嵌到武器或鞋子上躲避+40" },
// 	{ eItem::宝石b, 0x09, 0x52B2BFF6, 0x8FE88E79, "太阳石", "镶嵌到头盔或武器上伤害+8" },
// 	{ eItem::宝石b, 0x0A, 0xCFF52FDF, 0xB6D2F539, "月亮石", "镶嵌到头盔或衣服上防御+12" },

	//项链,腰带,鞋子	
	vector<int> es = { 1, 4, 5 };
	vector<int> stones = { 7, 1, 1 };
	int slv = 0;// = lv / 10;
// 	slv = min(16, slv);
	if (mp == -1)
	{
		mp = m_MengPaiID;
	}
	bool isMag = mp == eMP_神木林 || mp == eMP_东海龙宫 || mp == eMP_魔王寨;

	if (isMag && !isNormal)
	{
		stones[1] = 0;
		stones[2] = 8;
	}

	auto iswjb = [&]()
	{
// 		if (cct::isWJB(&item))
// 		{
// 			slv = cct::MaxStoneWJB;
// 		}
//		else 
		if (lv >= 10)
		{
			slv = lv / 10;
			slv = min(cct::MaxStoneLv, slv);
		}
		return slv > 0;
	};

	//项链,腰带,鞋子	
	for (int i = 0; i < 3; i++)
	{
		item.Set(19 + i, g_pMainState->m_ItemManage.GetIDByLv(19 + i, lv));
		bool nor = isNormal;
		if (nor && i == 0 && isMag)
		{
			nor = false;
		}
		item.m_Property = g_pMainState->m_ItemManage.AutoItemPropertyEquipButWeapon(&item, nor);
		if (isWJB && item.m_Property.size() > 13)
		{
			item.m_Property[13] = 0;
			if (i == 1 && item.m_Property.size() > 14)
			{
				item.m_Property[14] = 0;
			}
		}
		if (/*!isNormal || */isMag || i > 0)
		{
			if (iswjb())
			{
				item.m_Property[0] = /*(i == 0 && isNormal) ? cct::MaxStoneWJB : */slv;
				item.m_Property[1] = stones[i];
				g_pMainState->m_ItemManage.SetUpBaoShi(item.m_Property, item.m_Property[1], item.m_Property[0], false);
			}
		}
		m_Equips[es[i]] = item;
	}

	//头盔 分男女
	if (CanEquip(15))
	{
		item.Set(15, g_pMainState->m_ItemManage.GetIDByLv(15, lv));
	}
	else
	{
		item.Set(16, g_pMainState->m_ItemManage.GetIDByLv(16, lv));
	}
	item.m_Property = g_pMainState->m_ItemManage.AutoItemPropertyEquipButWeapon(&item, isNormal);
	if (isWJB && item.m_Property.size() > 13)
	{
		item.m_Property[13] = 0;
	}
	bool isphy = (mp == eMP_大唐官府 || mp == eMP_狮驼岭 || mp == eMP_凌波城);
	if (!isNormal || isphy)
	{
		if (iswjb())
		{
			item.m_Property[0] = /*(isphy && isNormal) ? cct::MaxStoneWJB : */slv;
			item.m_Property[1] = isphy ? 2 : 10;
			g_pMainState->m_ItemManage.SetUpBaoShi(item.m_Property, item.m_Property[1], item.m_Property[0], false);
		}
	}
	m_Equips[0] = item;


	// 衣服 也分
	if (CanEquip(17))
	{
		item.Set(17, g_pMainState->m_ItemManage.GetIDByLv(17, lv));
	}
	else
	{
		item.Set(18, g_pMainState->m_ItemManage.GetIDByLv(18, lv));
	}
	item.m_Property = g_pMainState->m_ItemManage.AutoItemPropertyEquipButWeapon(&item, isNormal);
	if (isWJB && item.m_Property.size() > 13)
	{
		item.m_Property[13] = 0;
	}
	if (!isNormal || isMag)
	{
		if (iswjb())
		{
			item.m_Property[0] = /*(isMag && isNormal) ? cct::MaxStoneWJB : */slv;
			item.m_Property[1] = (isMag) ? 7 : 10;
			g_pMainState->m_ItemManage.SetUpBaoShi(item.m_Property, item.m_Property[1], item.m_Property[0], false);
		}
	}
	m_Equips[3] = item;

	////////////////////////////////////////////////////////////////////////// 武器
	int typelist[2];
	GetWeaponType(modeid, typelist[0], typelist[1]);
	int k = typelist[rand() % 2];
	if (typelist[1] == -1)
	{
		k = typelist[0];
	}
	item.Set(k, g_pMainState->m_ItemManage.GetIDByLv(k, lv));
	item.m_Property = g_pMainState->m_ItemManage.AutoItemPropertyWeapon(&item, isNormal);
	if (isWJB && item.m_Property.size() > 13)
	{
		item.m_Property[13] = 0;
	}
	if (!isNormal && iswjb())
	{
		item.m_Property[0] = /*(isphy && isNormal) ? cct::MaxStoneWJB : */slv;
		item.m_Property[1] = isphy ? 2 : 9;
		g_pMainState->m_ItemManage.SetUpBaoShi(item.m_Property, item.m_Property[1], item.m_Property[0], false);
	}
	m_Equips[2] = item;
//  g_pMainState->m_InterfaceItem.Add(0, *this, &item);
//  g_pMainState->m_InterfaceItem.UseItem(0, *this);
// 	Equip(item);
 	m_pWeaponData2 = nullptr;
	m_pCharacterData2 = nullptr;
	getObj()->Reset();
	getObj()->Set(POS_STAND);

	if (item.m_pItemData != pit)
	{
		delete pit;
	}
}



void cPcData::autoData(bool skill, bool xl, bool fz)
{
	if (skill)
	{
		int lv = m_Lv + cct::LvGapFromRoleAndSkill;
		lv = min(lv, cct::MaxSkillLv);
		forr(m_MengPaiSkillLvs, i)
		{
			m_MengPaiSkillLvs[i] = lv;
		}
		autoSkillEnable();
	}

	if (fz)
	{
		forr(m_FuZhuSkillLvList, i)
		{
			m_FuZhuSkillLvList[i] = cBangPaiJiNengXueXi::m_BangpaiSkilllv;
		}
	}

	if (xl)
	{
		int lv = cct::getCurrMaxXiulianLv(m_Lv);
		for (int i = 0; i < 4; ++i)
		{
			m_XiuLian.AddXiuLianLv(lv, (eXiuLian)i);
			m_XiuLianBB.AddXiuLianLv(lv, (eXiuLian)i);
		}

	}
}




void cPcData::autoSkillEnable()
{
	m_SkillEnablelist.clear();
	if (m_MengPaiID < 0)
	{
		return;
	}

	const auto& mpManeger = g_pMainState->m_SkillManager.m_MengPaiManager;
	const auto& mainSkills = mpManeger.m_MengPai[m_MengPaiID].m_MainSkill;
	forv(mainSkills, k)
	{
		const auto& pZhuJiNeng = &mainSkills[k];
		for (int i = 0; i < pZhuJiNeng->m_NumSkillInclude; i++)
		{
			sSkill* pSkill = (sSkill*)&mpManeger.m_SkillList[pZhuJiNeng->m_SkillIncludeID[i]];
			m_SkillEnablelist.push_back(pSkill);
		}
	}
}



bool cPcData::RemovePet(int ID, bool deleteNow /* = false */)
{
	if (ID < 0)return false;
	if (m_NumofBB <= ID)return false;
	if (m_pPets[ID])
	{
		if (m_FightPetID == ID)
		{
			m_FightPetID = -1;
		}
	//	if (g_pMainState->m_InterFaceBuyPet.m_Item.size() < g_pMainState->m_InterFaceBuyPet.m_ItemHead.size())
		if (!deleteNow && m_IDinFightWorkList >= 0 && m_IDinFightWorkList < 5)
		{
			g_pMainState->m_InterFaceBuyPet.addPet(m_pPets[ID]);
		}
		else
		{
			SAFE_DELETE(m_pPets[ID]);
		}
		for (int i = ID; i < m_NumofBB - 1; ++i)
		{
			m_pPets[i] = m_pPets[i + 1];
		}
		m_pPets[--m_NumofBB] = nullptr;
	}
	return true;
}


bool cPcData::AddPet(cPet* pPet)
{
	//得到一个召唤兽
	if (!pPet)return false;
	if (m_NumofBB == m_pPets.size())return false;
	pPet->m_PetData.m_IDinFightWorkList = m_IDinFightWorkList + 5;
	m_pPets[m_NumofBB] = pPet;
	++m_NumofBB;
	return true;
}



void cPcData::apply()
{
	cPropertyData::apply(nullptr);
	forr(m_FuZhuSkillLvList, i)
	{
		applyFZ(m_FuZhuSkillLvList[i], i);
	}
	applyMP(m_MengPaiSkillLvs[0]);
	m_bDuJie = 0;
	m_faceMood = 0;
	forr(m_Fabaos, i)
	{
		if (m_Fabaos[i].m_Num != 1)
		{
			continue;
		}
		switch (m_Fabaos[i].GetID())
		{
		case eFaBao19通灵宝玉:
			m_bDuJie += 5;
			break;
		case eFaBao20聚宝盆:
			m_faceMood += 5;
			break;
		default:
			applyFabao(m_Fabaos[i].GetID());
			break;
		}
	}
	map<int, int> taozhuangMap;
	m_NumofSpecial = 0;
	forr(m_Equips, i)
	{
		if (m_Equips[i].m_Num != 1)
		{
			continue;
		}
		const auto& props = m_Equips[i].m_Property;
		int psize = props.size();
		// 特技 12
		if (psize > 12 && props[12] >= 0)
		{
			m_SpecialSkillList[m_NumofSpecial] = props[12];
			++m_NumofSpecial;
		}
		// 是否无级别 13
		// 是否神佑/愤怒 14
		if (psize > 14)
		{
			if (props[14] == 0 && i == 2)
			{
				RelifeRate.d1 += 20;
			}
			else if (props[14] == 0 && i == 4)
			{
				CpSavePercent = 20;
			}
		}

		// 符石 15

		if (i != 2 && psize > 15 && props[15] >= 0)
		{
			const auto& it = taozhuangMap.find(props[15]);
			if (it == taozhuangMap.end())
			{
				taozhuangMap.insert(make_pair(props[15], 1));
			}
			else
			{
				++it->second;
			}
		}
		if (taozhuangMap.size() == 1 && taozhuangMap.begin()->second == 5)
		{
			StartMagic = taozhuangMap.begin()->first;
		}
	}

	auto data = this;
	int _1 = 1;
	switch (m_MengPaiID)
	{
	case eMP_大唐官府:
		data->Pierce刺穿.d1 += _1 * 10;
		break;
	case eMP_化生寺:
		data->DmgAddOfCure.d1 += _1 * m_Lv;
		data->DmgAddOfCure.d2 += _1 * m_Lv;
		data->CriRateOfCure.d1 += _1 * 20;
		break;
	case eMP_方寸山:
		data->Ghost.d2 += _1 * 50;
		break;
	case eMP_女儿村:
		data->Speed.AddDataOriginal(_1 * m_Lv);
		break;
	case eMP_五庄观:
		data->ParryRateOfMaigc.d1 += _1 * 10;
		break;
	case eMP_狮驼岭:
		data->SuckBloodRate.d1 += _1 * 20;
		data->SuckBloodPercent.d1 += _1 * 10;
		break;
	case eMP_魔王寨:
		data->CriRateOfMagic.d1 += _1 * 5;
		data->Pierce刺穿OfMagic.d1 += _1 * 5;
		data->MagicWater.d1 += 10;
		data->ParryRate.d1 += _1 * 15;
		data->MagicFire.d1 += _1 * 15;
		data->MagicFire.d2 += _1 * 15;
		break;
	case eMP_盘丝岭:
		data->DmgPercentOfArm.d2 += _1 * 99;
		break;
	case eMP_阴曹地府:
		data->HitRateOfSeal.d2 += _1 * 20;
		break;
	case eMP_东海龙宫:
		data->CriRateOfMagic.d1 += _1 * 15;
		data->Pierce刺穿OfMagic.d1 += _1 * 5;
		data->MagicWater.d1 += _1 * 15;
		data->MagicWater.d2 += _1 * 15;
		break;
	case eMP_普陀山:
	{
		data->DmgPercentOfCure.d1 += _1 * 10;
// 		int v = _1 * 15;
// 		data->MagicFire.d2 += v;
// 		data->MagicSoil.d2 += v;
// 		data->MagicWater.d2 += v;
// 		data->MagicThunder.d2 += v;
	}
		break;
	case eMP_天宫:
		data->LiveRestoreRate += _1 * 10;
		break;
	case eMP_凌波城:
		data->CriRate.d1 += _1 * 5;
		break;
	case eMP_无底洞:
		data->LiveHp += _1 * m_Lv;
		break;	
	case eMP_神木林:
		data->ComboRateOfMagic.d1 += 5;
		data->CriRateOfMagic.d1 += _1 * 5;
		data->Pierce刺穿OfMagic.d1 += _1 * 5;
		break;
	}


	if (m_HP2 > HPMax.GetData())
	{
		m_HP2 = HPMax.GetData();
	}
	if (m_HP > m_HP2)
	{
		m_HP = m_HP2;
	}
}



void cPcData::SaveCode(sOstream& File)
{
// 	cPropertyData* pPetdata = this;
// 	pPetdata->Save(File, false);
	cPropertyData::SaveCode(File);
	File << m_bDuJie << g_strSpace;
	File << m_faceMood << g_strSpace;
	// 	//商人等级
	// 	File << m_traderLV << " ";
	// 	File << m_traderExp << " ";
	// 	//帮派
	// 	File << m_BangPaiID << " ";
	// 	File << m_BangPaiPoint << "\n";


	//门派
	File << m_MengPaiID << g_strSpace;
	forr(m_MengPaiSkillLvs, i)
	{
		File << m_MengPaiSkillLvs[i] << g_strSpace;
	}
	// 	File << "\n";
	// 	File << m_MengPaiPoint << " ";
	// 	File << "\n";
	// 	//人气
	// 	File << m_Popularity << " ";
	//钱  存银 储备金
	forr(m_Money, i)
	{
		File << m_Money[i] << g_strSpace;
	}
	// 	File << m_Physical << " ";	//体力
	// 	File << m_PhysicalMax << " ";	//体力上限
	// 	File << m_Energy << " ";		//活力
	// 	File << m_EnergyMax << " ";	//活力上限
	// 	File << m_CP << "\n";      //愤怒
	// 
	// 	//修炼
	m_XiuLian.Save(File);
	m_XiuLianBB.Save(File);
// 	//装备特技
// 	forr(m_MengPaiSkillLvs, i)
// 	{
// 		File << m_MengPaiSkillLvs[i] << g_strSpace;
// 	}
	//	File << "\n";
	//师门技能
// 	File << m_SkillEnablelist.size() << g_strSpace;
// 	for (int i = 0; i < m_SkillEnablelist.size(); i++)
// 	{
// 		File << m_SkillEnablelist[i]->m_Id << g_strSpace;
// 	}
	//	File << "\n";
	//物品
	forr(m_Items, i)
	{
		m_Items[i].SaveCode(File);
	}
	forr(m_Fabaos, i)
	{
		m_Fabaos[i].SaveCode(File);
	}
	//装备
	forr(m_Equips, i)
	{
		m_Equips[i].SaveCode(File);
	}

	File << m_FightPetID << g_strSpace;
	//召唤兽
	File << m_NumofBB << g_strSpace;
	for (int i = 0; i < m_NumofBB; ++i)
	{
		//		File << 101 << "\n";
// 		if (i == m_FightPetID)
// 		{//出战召唤兽的修炼去掉
// 			m_pPets[i]->m_PetData.m_XiuLian.Reset();
// 			m_pPets[i]->m_PetData.Save(File);
// 			m_pPets[i]->m_PetData.m_XiuLian = m_XiuLianBB;
// 		}
// 		else
			m_pPets[i]->m_PetData.SaveCode(File);
	}
	//变身
	// 	File << m_bUseCard << " ";
	// 	if (m_bUseCard)
	// 	{
	// 		m_JinJieNum.Save(File);
	// 		File << GetCard() << " ";
	// 		m_pCardPetData->propertyData.m_RanSe.Save(File);
	// 	}

	forr(m_Accelarate, i)
	{
		File << m_Accelarate[i] << g_strSpace;
	}
	//	File << "\n\n";
	forr(m_FuZhuSkillLvList, i)
	{
		File << m_FuZhuSkillLvList[i] << g_strSpace;
	}
}

void cPcData::LoadCode(sIstream& File)
{
	// 	cPropertyData* pPetdata = (cPropertyData*)this;
	// 	pPetdata->Load(File, false);
	cPropertyData::LoadCode(File);

	File >> m_bDuJie;
	File >> m_faceMood;
	//商人等级
	// 	File >> m_traderLV;
	// 	File >> m_traderExp;
	// 	m_traderExpMax = GetCharacterExp(m_traderLV);
	// 
	// 	//帮派
	// 	File >> m_BangPaiID;
	// 	File >> m_BangPaiPoint;

	//门派
	File >> m_MengPaiID;
	forr(m_MengPaiSkillLvs, i)
	{
		File >> m_MengPaiSkillLvs[i];
		if (m_MengPaiSkillLvs[i] > m_Lv + cct::LvGapFromRoleAndSkill)
		{
			ERRBOX2(m_MengPaiSkillLvs[i]);
		}
	}
	// 	File >> m_MengPaiPoint;
	// 	//人气
	// 	File >> m_Popularity;
	//钱  存银 储备金
	forr(m_Money, i)
	{
		File >> m_Money[i];
	}
	// 	File >> m_Physical;	//体力
	// 	File >> m_PhysicalMax;	//体力上限
	// 	File >> m_Energy;		//活力
	// 	File >> m_EnergyMax;	//活力上限
	// 	File >> m_CP;      //愤怒
	// 
	// 	//修炼
	m_XiuLian.Load(File);
	m_XiuLianBB.Load(File);

	int numofbb2 = cct::getCurrMaxXiulianLv(m_Lv);
	auto xlMin = [&](int& xl)
	{
		xl = min(numofbb2, xl);
	};

	xlMin(m_XiuLian.GetAtk());
	xlMin(m_XiuLian.GetMag());
	xlMin(m_XiuLian.GetDef());
	xlMin(m_XiuLian.GetDMag());

	xlMin(m_XiuLianBB.GetAtk());
	xlMin(m_XiuLianBB.GetMag());
	xlMin(m_XiuLianBB.GetDef());
	xlMin(m_XiuLianBB.GetDMag());

	//装备特技
// 	forr(m_SpecialSkillList, i)
// 	{
// 		File >> m_SpecialSkillList[i];
// 	}
	//师门技能
// 	int numsmskill, smskillid;
// 	File >> numsmskill;
// 	for (int i = 0; i < numsmskill; i++)
// 	{
// 		File >> smskillid;
// 		sSkill* pSkill = g_pMainState->m_SkillManager.GetSkill(smskillid);
// 		m_SkillEnablelist.push_back(pSkill);
// 	}
	//物品
	forr(m_Items, i)
	{
		m_Items[i].LoadCode(File);
	}
	forr(m_Fabaos, i)
	{
		m_Fabaos[i].LoadCode(File);
	}
	forr(m_Equips, i)
	{
		m_Equips[i].LoadCode(File);
	}
	File >> m_FightPetID;
	//召唤兽
//	int mark;
	File >> m_NumofBB;
	numofbb2 = m_NumofBB;
	for (int i = 0; i < numofbb2; i++)
	{
//		File >> mark;
		if (!m_pPets[i])m_pPets[i] = new cPet;
		m_pPets[i]->m_PetData.LoadCode(File);
		if (m_pPets[i]->m_PetData.modeid >= 0)
		{
			m_pPets[i]->SetData(g_pMainState->m_PetDataManager.GetPetData(m_pPets[i]->m_PetData.modeid));
		}
		else
		{
			ccc_msgbox("召唤兽读档错误");
		}
	}

	//变身
	// 	File >> m_bUseCard;
	// 	if (m_bUseCard)
	// 	{
	// 		m_JinJieNum.Load(File);
	// 		int cardid;
	// 		File >> cardid;
	// 		SetCard(cardid);
	// 		m_pCardPetData->propertyData.m_RanSe.Read(cardid, File);
	// 	}

	forr(m_Accelarate, i)
	{
		File >> m_Accelarate[i];
	}
	forr(m_FuZhuSkillLvList, i)
	{
		File >> m_FuZhuSkillLvList[i];
		m_FuZhuSkillLvList[i] = min(m_FuZhuSkillLvList[i], cBangPaiJiNengXueXi::m_BangpaiSkilllv);
	}
}

void cPcData::Save(ofstream& File)
{
	cPropertyData::Save(File);
	for (int i = 0; i < m_NumofBB; i++)
	{
		m_pPets[i]->m_PetData.Save(File);
	}

	//坐骑
	File << m_bOnZuoQi << g_strSpace; //是否坐上坐骑
	File << m_ZQ << g_strSpace;
	m_ZuoQiRanSe.Save(File);
	m_ZuoQi.m_ZhuangShi.Save(File);//
	File << m_ZhuangShiRanSe.partnum << g_strSpace;
	for (int i = 0; i < m_ZhuangShiRanSe.partnum; i++)//装饰染色
	{
		File << m_ZhuangShiRanSe.GetColorChange(i) << g_strSpace;
	}


}

void cPcData::Load(ifstream& File)
{
	cPropertyData::Load(File);

	for (int i = 0; i < m_NumofBB; i++)
	{
		m_pPets[i]->m_PetData.Load(File);
	}

	//坐骑
	File >> m_bOnZuoQi; //是否坐上坐骑
	File >> m_ZQ;
	g_pMainState->m_ZuoQi.GetZuoQi(*this, m_ZQ);

	m_ZuoQiRanSe.Read(File, m_ZQ, sChangeColorData::eZuoQi, 0);
	m_ZuoQi.m_ZhuangShi.Load(File);//读取坐骑装饰
	if (m_ZuoQi.m_ZhuangShi.GetNum() > 0)
	{
		m_ZhuangShiRanSe.Read(File, m_ZuoQi.m_ZhuangShi.GetID(), sChangeColorData::eZhuangShi, 0);
	}
	else
	{
		m_ZhuangShiRanSe.Read(File, 0, sChangeColorData::eZhuangShi, 0);
	}
}


void cPcData::Load(int model, int mp /* = -1 */)
{
	modeid = cct::getModel(model);
	if (m_Name.empty())
	{
		m_Name = g_pMainState->m_pCharacterDataList[modeid].m_Name;
	}
	m_MengPaiID = cct::getMenpai(mp);
}







#if 0

void cPcData::AutoPCData(string name, int modeidd, sAddPoint* addpoint/* =0 */, sZiZhi* zizhi/* =0 */, eMengPai mengpaid /* = eMP_无 */, int cardid /* = -1 */)
{
	m_Name = name;
	m_dataFileName = name;
	if (addpoint)
		m_AddPoint = *addpoint;
	else
	{
		sAddPoint addpoint2;
		m_AddPoint = addpoint2;
	}
	if (-1 != cardid)
	{
		m_bUseCard = true;
		m_CardPetID = cardid;
		if (!m_pCardPetData)m_pCardPetData = new cPet;
		m_pCardPetData->SetData(g_pMainState->m_PetDataManager.GetPetData(m_CardPetID));
	}
	//资质成长
	if (zizhi)
		m_ZiZhi = *zizhi;
	else
	{
		if (-1 != cardid)
		{
			m_ZiZhi.Set(m_pCardPetData->GetData()->m_ZiZhi, m_StrongLv, m_pCardPetData->GetData()->m_LvLimit);
		}
		else
		{
			m_ZiZhi.Set(2000, 2000, 6000, 9000, 2000, 2000, 100 + g_pCharacter->m_PcData.m_Lv / 2);
		}
	}
	m_Popularity = g_pMainState->m_GlobalButton[0] * 10;
	if (mengpaid == eMP_随机)
		mengpaid = (eMengPai)(rand() % 12);
	m_MengPaiID = mengpaid;
	modeid = modeidd;
	if (modeid == 15)
	{
		modeid = 3;
	}
	m_NumofBB = 0;

	// 	bool isBB = false;
	// 	AddProPertyAtk(isBB, 0);
	// 	AddProPertyDef(isBB, 0);
	// 	AddProPertyHp(isBB, 0);
	// 	AddProPertyMag(isBB, 0);
	// 	AddProPertySpd(isBB, 0);
}


bool cPcData::CostBangGong(int num)
{
	if (m_BangPaiPoint < num)return false;
	m_BangPaiPoint -= num;
	return true;
}

bool cPcData::AddTraderExp(int num)
{
	m_traderExp += num;
	if (m_traderExp >= m_traderExpMax)
	{
		m_traderExp -= m_traderExpMax;
		m_traderLV -= 1;
		m_traderExpMax = GetCharacterExp(m_traderLV);
		return true;
	}
	return false;
}



void cPcData::Followlv(int lv, bool isBabyMode, bool isAdd, bool isEquip)
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
	FillHpMp();
}


void cPcData::FollowlvAddPoint(int lv, bool isBabyMode, bool isEquip, bool isXiulian)
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
	FillHpMp();
}


void cPcData::FollowSkill()
{
	if (m_MengPaiID < 0)
		return;
	int lvadd = cct::get()->maxSkillLv - cct::get()->maxRoleLv + m_LV - m_MengPaiSkillLvs[0];

	if (!lvadd)return;

	for (int i = 0; i < 7; i++)
	{
		g_pMainState->m_SkillManager.lvUpMainSkill(*this, lvadd, i);
	}
}

void cPcData::FollowXiulian()
{
	int maxlv = (m_LV - 20) / 5;
	if (maxlv < 0)
	{
		maxlv = 0;
	}
	else if (maxlv > cct::get()->maxXiuLian)
	{
		maxlv = cct::get()->maxXiuLian;
	}
	m_XiuLian.Set(maxlv, maxlv, maxlv, maxlv);
	m_XiuLianBB.Set(maxlv, maxlv, maxlv, maxlv);
// 	if (maxlv>g_pMainState->m_GlobalButton[6])
// 	{
// 		maxlv = g_pMainState->m_GlobalButton[6];
// 	}
}

void cPcData::FollowEuip(bool is穿盔甲 /* = true */)
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
				desbin = cct::get()->getDesbinOf项链(m_MengPaiID, _spesialSkills[1]);
			}
			else if (i == 1)
			{
				desbin = cct::get()->getDesbinOf腰带(m_MengPaiID, _spesialSkills[4]);
			}
			else if (i == 2)
			{
				desbin = cct::get()->getDesbinOf鞋子(m_MengPaiID, false, _spesialSkills[5]);
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
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, cct::get()->getDesbinOf头盔(m_MengPaiID, _spesialSkills[0]));
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

			g_pMainState->m_ItemManage.AutoItemProperty(&item, this, cct::get()->getDesbinOf铠甲(m_MengPaiID, _spesialSkills[3]));
			g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, eMengPai(m_MengPaiID));
			// 				baoshi.Set(29, 10);
			// 				for (int i2 = 0; i2 < baoshinum; i2++)g_pMainState->m_ItemManage.XiangQian(item, baoshi);

			asert(item.m_Property.size(), "衣服创建空属性");
			g_pMainState->m_InterfaceItem.Add(idx, *this, &item);
			g_pMainState->m_InterfaceItem.UseItem(idx, *this);
		}

		//武器
		FollowWeapon();

		FillHpMp();
	}
}

void cPcData::FollowWeapon()
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
	g_pMainState->m_ItemManage.AutoItemProperty(&item, this, cct::get()->getDesbinOf武器(m_MengPaiID, _spesialSkills[2]));
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

void cPcData::FollowShoe()
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
	desbin = cct::get()->getDesbinOf鞋子(e, cct::get()->isAutoAtkMode, _spesialSkills[5]);
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

void cPcData::FollowEquipAll()
{
	sItem2 item;
	item.m_Num = 1;
	int lv = m_LV;

	vector<int> ems;
	for (int i = 0; i < 60; ++i)
	{

		if (m_Items[i].GetNum() > 0 && (m_Items[i].GetType() == 24 || m_Items[i].GetType() == 27 || m_Items[i].GetType() == 28))
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
	int desbin = cct::get()->getDesbinOf鞋子(m_MengPaiID, false, _spesialSkills[5]);
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
	desbin = cct::get()->getDesbinOf腰带(m_MengPaiID, _spesialSkills[4]);
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
	desbin = cct::get()->getDesbinOf铠甲(m_MengPaiID, _spesialSkills[3]);
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
		g_pMainState->m_ItemManage.AutoItemProperty(&item, this, cct::get()->getDesbinOf武器(m_MengPaiID, _spesialSkills[2]));
		g_pMainState->m_ItemManage.AutoFuShi(&item, m_LV, eMengPai(m_MengPaiID));
		g_pMainState->m_InterfaceItem.Add(idx/*50 + i*/, *this, &item);
	}

	idx = findEmpty(49);
	if (idx < 0)
	{
		return;
	}
	item.Set(19, g_pMainState->m_ItemManage.GetIDByLv(19, lv));
	desbin = cct::get()->getDesbinOf项链(m_MengPaiID, _spesialSkills[1]);
	g_pMainState->m_ItemManage.AutoItemProperty(&item, this, desbin);
	g_pMainState->m_ItemManage.AutoFuShi(&item, lv, (eMengPai)m_MengPaiID);
	g_pMainState->m_InterfaceItem.Add(idx/*49*/, *this, &item);



	//头盔分男女
	hel = CanEquip(15) ? 15 : 16;
	item.Set(hel, g_pMainState->m_ItemManage.GetIDByLv(hel, lv));
	desbin = cct::get()->getDesbinOf头盔(m_MengPaiID, _spesialSkills[0]);
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



void cPcData::FollowItem(bool isUnseal)
{
	////////////////////////////////////////////////////////////////////////// 物品 呵呵哒
	//加HP  0
	// 				int itemid = 2 + g_pCharacter->m_PcData.m_Lv / 17;
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
			m_Items[i].Set(22, 药品s[i]);
			m_Items[i].m_Num = 5;
		}
	}
	else
	{
		for (auto i : { 2, 3, 5 })
		{
			m_Items[i].Set(22, 药品s[i]);
			m_Items[i].m_Num = cct::get()->药品数量;
		}
	}

	int anqi = m_LV / 15;
	if (anqi > 9) anqi = 9;
	m_Items[8].Set(25, anqi);
	m_Items[8].m_Num = cct::get()->药品数量;
}

void cPcData::FollowBaby()
{
	//更新召唤兽
	int petnum = m_NumofBB;
	int maxlv = m_LV + cct::get()->lvGapFromRoleAndBaby;
	if (maxlv > cct::get()->maxBabyLv)
	{
		maxlv = cct::get()->maxBabyLv;
	}
	for (int i = 0; i < petnum; i++)
	{
		m_pPets[i]->data.m_Popularity = m_Popularity;
		m_pPets[i]->data.Followlv(maxlv, true, true, true);
	}
}

void cPcData::FullFuzhuBut暗器()
{
	lvUpFuZhuSkill(160, 0);
	lvUpFuZhuSkill(160, 1);
	lvUpFuZhuSkill(160, 2);
	lvUpFuZhuSkill(m_LV, 3);
}

int& cPcData::GetCard()
{
	return m_CardPetID;
}

void cPcData::GetShangPinPet(int ShangPinID)
{
	sShangPinPet pet;
	pet.LoadEasy(ShangPinID);
	cPet* pPet = new cPet;
	pPet->Set(&pet, m_StrongLv);
	AddPet(pPet);
}

void cPcData::Read(string name, string path)
{
	path = path + name;
	path += ".txt";
	ifstream File;
	File.open(path);
	if (!File)ERRBOX;
	string dustbin;
	//	int intdustbin;
	File >> modeid;
	getline(File, dustbin);
	if (-1 == modeid)
	{//召唤兽
		ERRBOX;
		/*bPet = true;
		File >> modeid;*/
	}
	//	File >> m_CardPetID;
	if (modeid == 15)
	{
		modeid = 3;
	}
	m_CardPetID = -1;
	if (m_CardPetID > -1)
	{

		if (0 == m_pCardPetData)
			m_pCardPetData = new cPet;
		m_pCardPetData->SetData(g_pMainState->m_PetDataManager.GetPetData(m_CardPetID));
		m_pCardPetData->propertyData.m_JinJieNum = m_JinJieNum;
		m_bUseCard = true;
	}
	else
	{
		m_bUseCard = false;
		SAFE_DELETE(m_pCardPetData);
	}
	//	getline(File, dustbin);
	File >> m_MengPaiID;
	getline(File, dustbin);

	File >> m_Name;
	if (m_Name == "无")ERRBOX;
	getline(File, dustbin);
	//	m_ZiZhi.Load(File);
	File >> m_ZiZhi.atk;
	File >> m_ZiZhi.def;
	File >> m_ZiZhi.hp;
	File >> m_ZiZhi.mag;
	File >> m_ZiZhi.speed;
	File >> m_ZiZhi.avoid;
	getline(File, dustbin);
	// 	File >> m_ZiZhi.m_Growing;
	// 	getline(File, dustbin);
	m_ZiZhi.grow = 100;
	m_AddPoint.Load(File);
	getline(File, dustbin);
	// 	File >> m_MengPaiID;
	// 	getline(File, dustbin);
	int numofbbskill;
	/*	File >> numofbbskill;*/
	numofbbskill = 0;
	vector<int> skill;
	skill.resize(numofbbskill);
	getline(File, dustbin);
	for (int i = 0; i < numofbbskill; i++)
	{
		File >> skill[i];
		//m_pPetSkill[i]=g_pMainState->m_SkillManager.GetPetSkill(intdustbin) ;
	}
	// 	File >> m_LiveHpLv;			getline(File, dustbin);
	// 	File >> m_LiveMpLv;			getline(File, dustbin);
	// 	File >> m_LiveCp;			getline(File, dustbin);
	// 	nightLv = 0;
	// 	File >> mpsavepercent;		getline(File, dustbin);
	// 	File >> restoreRate;		getline(File, dustbin);
	// 	File >> abnormalResist;		getline(File, dustbin);
	// 	File >> magicWavePercent;	getline(File, dustbin);
	// 	File >> comboNumDown;		getline(File, dustbin);
	// 	File >> comboNumUp;			getline(File, dustbin);
	// 	File >> ShiXueAdd;			getline(File, dustbin);
	// 	File >> buffAdd;			getline(File, dustbin);
	// 	File >> m_MagicNumAdd;		getline(File, dustbin);
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_HPMax.SetDataAdd(intdustbin);
	// 
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_MPMax.SetDataAdd(intdustbin);
	// 
	// 
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_ATK.SetDataAdd(intdustbin);
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_HIT.SetDataAdd(intdustbin);
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_DEF.SetDataAdd(intdustbin);
	// 	File >> intdustbin;			getline(File, dustbin);
	// 
	// 	m_Wakan.SetDataAdd(intdustbin);
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_SPD.SetDataAdd(intdustbin);
	// 	File >> intdustbin;			getline(File, dustbin);
	// 	m_Evade.SetDataAdd(intdustbin);
	// 	GoldLivePercent.Load(File);	getline(File, dustbin);
	// 	m_ParryRate.Load(File);		getline(File, dustbin);
	// 	m_CriRate.Load(File);		getline(File, dustbin);
	// 	m_MagicCriRate.Load(File);	getline(File, dustbin);
	// 	m_CureCriRate.Load(File);	getline(File, dustbin);
	// 	m_CriAddPercent.Load(File); getline(File, dustbin);
	// 	m_Combo.Load(File);			getline(File, dustbin);
	// 	m_MagicComboRate.Load(File); getline(File, dustbin);
	// 	m_Pierce.Load(File);		getline(File, dustbin);
	// 	m_PierceMagic.Load(File);	getline(File, dustbin);
	// 
	// 
	// 	m_HitRate.Load(File);					getline(File, dustbin);
	// 	m_MagicHitRate.Load(File);				getline(File, dustbin);
	// 	m_SealRate.Load(File);					getline(File, dustbin);
	// 	poisonRate.Load(File);					getline(File, dustbin);
	// 	m_DamageAddPercentMagic2.Load(File);	getline(File, dustbin);
	// 	m_DamageAddPercentMagic.Load(File);		getline(File, dustbin);
	// 	m_DamagePercent.Load(File);				getline(File, dustbin);
	// 	m_HiddenWeaponDamagePercent.Load(File);	getline(File, dustbin);
	// 	m_DamageAddPercentPoision.Load(File);	getline(File, dustbin);
	// 	m_DamageAddPercentCure.Load(File);		getline(File, dustbin);
	// 	m_PetDamagePercentMagic.Load(File);		getline(File, dustbin);
	// 	m_PetDamagePercent.Load(File);			getline(File, dustbin);
	// 	m_DamageAddMagic.Load(File);			getline(File, dustbin);
	// 	m_DamageAddMagicLv.Load(File);			getline(File, dustbin);
	// 	m_DamageAdd.Load(File);					getline(File, dustbin);
	// 	m_DamageAddLv.Load(File);				getline(File, dustbin);
	// 	m_DamageAddCure.Load(File);				getline(File, dustbin);
	// 	m_CounterRate.Load(File);				getline(File, dustbin);
	// 	m_StabRate.Load(File);					getline(File, dustbin);
	// 	m_StabRateMagic.Load(File);				getline(File, dustbin);
	// 	m_StabDamageRate.Load(File);			getline(File, dustbin);
	// 	m_StabDamageRateMagic.Load(File);		getline(File, dustbin);
	// 	m_SuckBloodRate.Load(File);				getline(File, dustbin);
	// 
	// 	getline(File, dustbin);
	// 	m_AtkDownCP.Load(File);					getline(File, dustbin);
	// 	m_StartMagic.Load(File);				getline(File, dustbin);
	// 	m_MagDownHPHurt.Load(File);				getline(File, dustbin);
	// 	m_AtkDownHPHurt.Load(File);				getline(File, dustbin);
	// 	m_AtkDownMP.Load(File);					getline(File, dustbin);
	// 	m_AtkDownAtk.Load(File);				getline(File, dustbin);
	// 	m_AtkDownHit.Load(File);				getline(File, dustbin);
	// 	m_AtkDownDef.Load(File);				getline(File, dustbin);
	// 	m_AtkDownWakan.Load(File);				getline(File, dustbin);
	// 	m_AtkDownSpd.Load(File);				getline(File, dustbin);
	// 	m_Spurting.Load(File);				getline(File, dustbin);
	// 	m_JinJiaRate.Load(File);				getline(File, dustbin);
	// 	m_XiangMoRate.Load(File);				getline(File, dustbin);
	// 	m_MagicFire.Load(File);				getline(File, dustbin);
	// 	m_MagicSoil.Load(File);				getline(File, dustbin);
	// 	m_MagicWater.Load(File);				getline(File, dustbin);
	// 	m_MagicThunder.Load(File);				getline(File, dustbin);
	// 	BoySpecial.Load(File);					getline(File, dustbin);
	// 	GirlSpecial.Load(File);					getline(File, dustbin);
	// 	GoldSpecial.Load(File);					getline(File, dustbin);
	// 	MagSpecial.Load(File);					getline(File, dustbin);
	// 	ImmortalSpecial.Load(File);				getline(File, dustbin);
	// 	MonsterSpecial.Load(File);				getline(File, dustbin);
	// 	PeopleSpecial.Load(File);				getline(File, dustbin);
	// 	ghostSpecial.Load(File);				getline(File, dustbin);
	// 	machineSpecial.Load(File);				getline(File, dustbin);

	if (cct::get()->isSpecialOrZZ(m_ZiZhi.atk))
	{
		_spesialSkills[0] = m_ZiZhi.atk;
	}

	if (cct::get()->isSpecialOrZZ(m_ZiZhi.hp))
	{
		_spesialSkills[1] = m_ZiZhi.hp;
	}
	if (cct::get()->isSpecialOrZZ(m_ZiZhi.mag))
	{
		_spesialSkills[2] = m_ZiZhi.mag;
	}
	if (cct::get()->isSpecialOrZZ(m_ZiZhi.def))
	{
		_spesialSkills[3] = m_ZiZhi.def;
	}
	if (cct::get()->isSpecialOrZZ(m_ZiZhi.speed))
	{
		_spesialSkills[4] = m_ZiZhi.speed;
	}
	if (cct::get()->isSpecialOrZZ(m_ZiZhi.avoid))
	{
		_spesialSkills[5] = m_ZiZhi.avoid;
	}

	// 	File >> m_dataFileName; 
	// 	getline(File, dustbin);
	// 	if (m_dataFileName == "无")
	m_dataFileName = name;

	// 	File >> m_StrongLv; getline(File, dustbin);
	// 	File >> m_AiLv;  getline(File, dustbin);
	// 	File >> m_Popularity; getline(File, dustbin);
	m_StrongLv = 100;
	m_Popularity = 500;

	m_RanSe.Read(2000 + modeid, File);
	m_NumofBBSkill = 0;
	for (int i = 0; i < skill.size(); i++)
	{
		AddSkill((ePetSkill)skill[i]);
	}

	//	m_AiLv = m_ZiZhi.m_Growing < cct::get()->putMenpaiSkills.size();
	//	bool isBB = false;
	Atk.SetDataOriginal(CountATK());
	Def.SetDataOriginal(CountDEF());
	HPMax.SetDataOriginal(CountHP());
	Hit.SetDataOriginal(CountHit());
	MPMax.SetDataOriginal(CountMP());
	Speed.SetDataOriginal(CountSpd());
	Mana.SetDataOriginal(CountWakan());
	Evade.SetDataOriginal(CountEvade());
	m_ExpTotal = GetCharacterExp(m_LV);


	// 	AddProPertyAtk(30);
	// 	AddProPertyDef(20);
	// 	AddProPertyHp(20);
	// 	AddProPertyMag(20);
	// 	AddProPertySpd(20);
	//	m_ProPerty未分配点 += cct::get()->point额外;
	FillHpMp();
	File.close();
}



#endif