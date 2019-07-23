#include "_global.h"

bool CMainState::AutoPet(cPet*& pPet, int ID, int StrongLv, int LV, sAddPoint addpoint)
{
	if (!pPet)pPet = new cPet;
	pPet->SetData(g_pMainState->m_PetDataManager.GetPetData(cct::getModel(ID)));
	auto& p = pPet->m_PetData;
	p.m_Name = pPet->GetData()->m_Name;
	p.Reset();
	p.Load(ID, true, true);
	p.m_Lv = LV;
	p.setPointAfterLv(addpoint, false);
	p.apply();
	p.FillHpMp();
// 	pPet->AutoPetData(ID, StrongLv, &addpoint);
// 	pPet->m_PetData.LeveUp(LV, true, true);
//	p.SetJinJie(1);
	return true;
}


bool CMainState::AutoPet(cPet*& pPet, int ID, int StrongLv, int LV)
{
	AutoPet(pPet, ID, StrongLv, LV, sAddPoint());
	pPet->m_PetData.setPointAfterLv(getAddpointFromPet(&pPet->m_PetData, true), false);
	pPet->m_PetData.apply();
	pPet->m_PetData.FillHpMp();
// 	if (!pPet)pPet = new cPet;
// 	pPet->m_PetData.Reset();
// 	pPet->m_PetData.m_Lv = 0;
// 	sAddPoint addpoint;
// 	pPet->AutoPetData(ID, StrongLv, &addpoint);
// 	pPet->m_PetData.m_AddPoint = ;
// 	pPet->m_PetData.LeveUp(LV, true, true);
	return true;
}


bool CMainState::AutoPet(cPet* &pet0, int modeid, int lv, bool addBlood /* = false */)
{
	pet0->SetData(g_pMainState->m_PetDataManager.GetPetData(modeid));
	cPetData& pet = pet0->m_PetData;
	pet.Load(modeid, true, true);
	pet.m_Lv = lv;
	bool isGad = (pet0->GetData()->m_LvTake == 0);
	if (!isGad)
	{
		pet.AddSkill(108);
		pet.AddSkill(105);
	}
	pet.PointRemain = cct::PointRemian;
	pet.setPointAfterLv(g_pMainState->getAddpointFromPet(&pet, addBlood), true);
	if (!isGad)
	{
		pet.m_NumofBBSkill -= 2;
	}

	bool isFs = !pet.autoData(addBlood, pet0->GetData()->m_LvTake != 0 || pet.m_NumofBBSkill == 0);
	pet.autoEquip(true, !g_pMainState->m_AI.isMagFromPoint(&pet));

// 	vector<int> stones = { (g_pMainState->m_AI.isAtkFromPoint(&pet)) ? 15 : 12, 11, (rand() % 100 < 50) ? 13 : 16 };
// 	modeid = (pet.m_Lv - 5) / 10;
// 	modeid = max(modeid, 0);
// 	modeid = min(modeid, 16);
// 	forr(stones, kk)
// 	{
// 		auto& prs = pet.m_Equips[kk].m_Property;
// 		prs[0] = modeid;
// 		prs[1] = stones[kk];
// 		g_pMainState->m_ItemManage.SetUpBaoShi(prs, prs[1], prs[0], true);
// 	}
// 	if (isFs)
// 	{
// 		static vector<int> s1s;
// 		if (s1s.empty())
// 		{
// 			s1s.push_back(14);
// 			s1s.push_back(50);
// 			s1s.push_back(135);
// 			s1s.push_back(182);
// 
// 			s1s.push_back(2085);
// 			s1s.push_back(2087);
// 			s1s.push_back(2089);
// 			s1s.push_back(2091);
// 			s1s.push_back(2092);
// 			s1s.push_back(2093);
// 			s1s.push_back(2094);
// 			s1s.push_back(2095);
// 			s1s.push_back(2098);
// 			s1s.push_back(2099);
// 		}
// 		modeid = s1s[rand() % s1s.size()];
// 		forr(stones, kk)
// 		{
// 			pet.m_Equips[kk].m_Property[15] = modeid;
// 		}
// 	}

	pet.apply();
	pet.FillHpMp();
	return true;
}


sAddPoint CMainState::getAddpointFromPet(cPetData *data, bool is1Or0Blood /* = false */)
{
	sAddPoint add, add2;
	if (is1Or0Blood)
	{
		add.Set(4, 0, 0, 1, 0);
		add2.Set(0, 0, 4, 1, 0);
	}
	else
	{
		add.Set(5, 0, 0, 0, 0);
		add2.Set(0, 0, 5, 0, 0);
	}
	if (!data || data->modeid < 0)
	{
		return add;
	}

	int type = g_pMainState->m_PetDataManager.GetPetData(data->modeid)->m_addPointType;
	if (type == 1)
	{
		return add;
	}
	else if (type == 2)
	{
		return add2;
	}
	else if (type == 3)
	{
		return (rand() % 100 < 50) ? add : add2;
	}



	vector<int> ms, m2s, ps, bs;

	vector<sSkill*> skills;
	for (int j = 0; j < data->m_NumofBBSkill; j++)
	{
		skills.push_back(data->m_petSkills[j]);
	}
	bool phySkill = g_pMainState->m_AI.isHadPetSkill(skills, bs, ps, ms, m2s);
	if (ms.size() || m2s.size())
	{
		return add2;
	}
	return add;


	const auto& z = data->m_ZiZhi;
	if (z.atk >= 1600)
	{
		if (z.mag < 2800 || bs.empty())
		{
			return add;
		}
	}


	if (ms.size() || m2s.size())
	{
		if (ps.empty())
		{
			return add2;
		}
	}

	else if (z.mag >= 3000)
	{

	}

	if ((ms.size() || m2s.size()))



	if (((z.atk * 2) < z.mag || (z.atk < 1600 && z.mag > 3000) || (ps.empty() && bs.size() && (z.atk * 3 / 2) < z.mag)) && (ms.size() || m2s.size()))
	{
		return add2;
	}
	return add;
}



sAddPoint CMainState::getAddpointFromMp(int mp, bool isAddBlood /*= false*/)
{
	sAddPoint ap;
	vector<sAddPoint> as;
	ap.Set(0, 0, 5, 0, 0);
	as.push_back(ap);
	ap.Set(0, 0, 4, 1, 0);
	as.push_back(ap);
	ap.Set(0, 1, 4, 0, 0);
	as.push_back(ap);
	ap.Set(0, 1, 3, 1, 0);
	as.push_back(ap);

	auto func = [&]()
	{
		ap = as[rand() % as.size()];
		if (!isAddBlood)
		{
			ap.mag += ap.body;
			ap.body = 0;
		}
		return ap;
	};
	
	if (mp == eMP_神木林)
	{
		if (rand() % 100 < 50)
		{
			swap(ap.mag, ap.body);
		}
		return func();
	}

	switch (mp)
	{
	case eMP_魔王寨:
	case eMP_东海龙宫:
		return func();
	}

	as.clear();
	ap.Set(5, 0, 0, 0, 0);
	as.push_back(ap);
	ap.Set(4, 1, 0, 0, 0);
	as.push_back(ap);
	ap.Set(4, 0, 0, 1, 0);
	as.push_back(ap);
	ap.Set(4, 0, 0, 0, 1);
	as.push_back(ap);
	ap.Set(3, 1, 0, 1, 0);
	as.push_back(ap);
	ap.Set(3, 1, 0, 0, 1);
	as.push_back(ap);
	ap.Set(3, 0, 0, 1, 1);
	as.push_back(ap);

	switch (mp)
	{
	case eMP_大唐官府:
	case eMP_狮驼岭:
	case eMP_凌波城:
		ap = as[rand() % as.size()];
		if (!isAddBlood)
		{
			ap.str += ap.body;
			ap.body = 0;
		}
		return ap;
	}


	as.clear();
	bool isSeal = true;
	switch (mp)
	{
	case eMP_化生寺:
	case eMP_普陀山:
	case eMP_阴曹地府:
	case eMP_无底洞:
		isSeal = false;
		ap.Set(0, 2, 0, 2, 1);
		as.push_back(ap);
		ap.Set(0, 3, 0, 1, 1);
		as.push_back(ap);
// 		ap.Set(0, 4, 0, 0, 1);
// 		as.push_back(ap);
		break;
	}
	ap.Set(0, 1, 0, 2, 2);
	as.push_back(ap);
	ap.Set(0, 2, 0, 1, 2);
	as.push_back(ap);
	ap.Set(0, 3, 0, 0, 2);
	as.push_back(ap);

	ap.Set(0, 0, 0, 2, 3);
	as.push_back(ap);
	ap.Set(0, 1, 0, 1, 3);
	as.push_back(ap);
	ap.Set(0, 2, 0, 0, 3);
	as.push_back(ap);
	
	if (isSeal)
	{
		ap.Set(0, 0, 0, 1, 4);
		as.push_back(ap);
		ap.Set(0, 1, 0, 0, 4);
		as.push_back(ap);
// 		ap.Set(0, 0, 0, 0, 5);
// 		as.push_back(ap);
	}

	ap = as[rand() % as.size()];
	if (!isAddBlood)
	{
		ap.dex += ap.body;
		ap.body = 0;
	}
	return ap;
}



int CMainState::getModelFromMp(int mp)
{
	mp = cct::getMenpai(mp);
	vector<int> cs;
	switch (mp)
	{
	case eMP_大唐官府:
	case eMP_方寸山:
	case eMP_神木林:
		cs.push_back(eJuSe剑侠客);
		cs.push_back(eJuSe逍遥生);
		cs.push_back(eJuSe飞燕女);
		cs.push_back(eJuSe英女侠);
		cs.push_back(eJuSe巫蛮儿);
		cs.push_back(eJuSe偃无师);
		break;
	case eMP_化生寺:
		cs.push_back(eJuSe剑侠客);
		cs.push_back(eJuSe逍遥生);
		cs.push_back(eJuSe偃无师);
		break;
	case eMP_女儿村:
		cs.push_back(eJuSe飞燕女);
		cs.push_back(eJuSe英女侠);
		cs.push_back(eJuSe巫蛮儿);
		break;
	case eMP_狮驼岭:
		cs.push_back(eJuSe虎头怪);
		cs.push_back(eJuSe巨魔王);
		cs.push_back(eJuSe杀破狼);
		break;
	case eMP_魔王寨:
	case eMP_阴曹地府:
	case eMP_无底洞:
		cs.push_back(eJuSe虎头怪);
		cs.push_back(eJuSe巨魔王);
		cs.push_back(eJuSe骨精灵);
		cs.push_back(eJuSe狐美人);
		cs.push_back(eJuSe杀破狼);
		cs.push_back(eJuSe鬼潇潇);
		break;
	case eMP_盘丝岭:
		cs.push_back(eJuSe骨精灵);
		cs.push_back(eJuSe狐美人);
		cs.push_back(eJuSe鬼潇潇);
		break;
	case eMP_东海龙宫:
	case eMP_天宫:
	case eMP_凌波城:
		cs.push_back(eJuSe龙太子);
		cs.push_back(eJuSe神天兵);
		cs.push_back(eJuSe玄彩蛾);
		cs.push_back(eJuSe舞天姬);
		cs.push_back(eJuSe羽灵神);
		cs.push_back(eJuSe桃夭夭);
		break;
	case eMP_五庄观:
		cs.push_back(eJuSe龙太子);
		cs.push_back(eJuSe神天兵);
		cs.push_back(eJuSe羽灵神);
		break;
	case eMP_普陀山:
		cs.push_back(eJuSe玄彩蛾);
		cs.push_back(eJuSe舞天姬);
		cs.push_back(eJuSe桃夭夭);
		break;
	}
	return cs[rand() % cs.size()];
}


cObj* CMainState::AddEnemy(int pos /* = -1 */, bool our /* = false */)
{
	sFightWork* plist = 0;
	int start;
	if (-1 == pos)
	{
		if (our)
			start = 0;
		else
			start = 10;
	}
	else start = pos;
	int id = -1;
	for (int i = start; i < start + 10; i++)
	{
		if (!m_FightWorkList[i].isExist)
		{
			id = i;
			break;
		}
	}

	if (id == -1)return nullptr; // id;
	m_FightWorkList[id].isExist = true;
	plist = &m_FightWorkList[id];
	if (our)
	{
		plist->m_pObj = new cObj;
		plist->m_pObj->Init();
		plist->m_pObj->m_IDInFightlist = id;
	}
	return plist->m_pObj;
}


cPetData* CMainState::AddEnemy(int modeid, int lv, string name /* = "" */, sAddPoint* ap /* = nullptr */, int pos /* = -1 */, bool our /* = false */)
{
	cObj* obj = AddEnemy(pos, our);
	if (!obj)
	{
		return nullptr;
	}
	obj->AutoData(modeid, name);

	cPetData *data = obj->getPetData();
//	data->Reset();
//	data->m_IDinFightWorkList = obj->m_IDInFightlist;
	if (name.size())
	{
		data->m_Name = name;
	}
	data->Load(modeid, true, true);
	data->m_Lv = lv;
	data->setPointAfterLv((ap ? (*ap) : getAddpointFromPet(data, true)), false);
	data->autoEquip(true, false);
	data->apply();
	data->FillHpMp();
	data->SetJinJie(1);
	if (our)
	{
		data->_isOurTeamTemp = true;
	}
	return data;
}


cPcData* CMainState::AddEnemy(int modeid, int lv, eMengPai mengpaid, string name /* = "" */, sAddPoint* addpoint /* = nullptr */, int weaponLv /* = -1 */, int pos /* = -1 */, bool our /* = false */)
{
	cObj* obj = AddEnemy(pos, our);
	if (!obj)
	{
		return nullptr;
	}

	int mp = cct::getMenpai(mengpaid);
	int petid = -1;
	if (modeid < 2000)
	{
		petid = modeid;
		modeid = getModelFromMp(mp) + 2000;
		if (name.empty())
		{
			name = g_pMainState->m_PetDataManager.m_PetList[petid].m_Name;
		}
	}
	obj->AutoData(modeid, nullptr, petid, name);
	cCharacter* c = (cCharacter*)obj->m_pIndex;
	cPcData &pc = c->m_PcData;
//	pc.m_IDinFightWorkList = obj->m_IDInFightlist;
	if (name.size())
	{
		pc.m_Name = name;
	}
	pc.Load(modeid, mp);

	pc.m_Lv = lv;
	auto ap = addpoint ? (*addpoint) : getAddpointFromMp(mp, false);
	pc.setPointAfterLv(ap, false);
	pc.autoData(true, false, false);
	pc.autoEquip(true);
	
	if (weaponLv >= 0)
	{
	// 草儿特供??
		////////////////////////////////////////////////////////////////////////// 武器
		int typelist[2];
		GetWeaponType(modeid - 2000, typelist[0], typelist[1]);
		int k = typelist[rand() % 2];
		if (typelist[1] == -1)
		{
			k = typelist[0];
		}
		pc.m_Equips[2].Set(k, g_pMainState->m_ItemManage.GetIDByLv(k, weaponLv), false);
		pc.m_pWeaponData2 = nullptr;
		pc.m_pCharacterData2 = nullptr;
		obj->Reset();
		obj->Set(POS_STAND);
	}
	if (petid < 0)
	{
		pc.m_pCharacterData2 = nullptr;
		pc.m_pWeaponData2 = nullptr;
	}

	pc.apply();
	if (pc.m_Lv > 0)
	{
		pc.DmgPercent.d2 -= (5 - ap.dex) * 5;
		pc.Def.AddDataAddPercent((ap.dex - 5) * 5);
		pc.DmgPercentOfMagic.d2 -= (5 - ap.mag) * 10;
	//	pc.Mana.AddDataAddPercent((ap.mag - 4) * 5);
	//	pc.DmgPercent.d2 -= 10 + (5 - (pc.PointDex - pc.m_Lv - cct::MinPoint) / pc.m_Lv) * 3;
	}

//	ap = getAddpointFromMp(mp, true);
//	pc.HPMax.SetDataAddPercent((cBangPaiJiNengXueXi::m_BangpaiSkilllv << 3) + (ap.body << 8));
// 	int hp1 = pc.HPMax.GetData();
// 	hp1 = (pc.m_Lv * cBangPaiJiNengXueXi::m_BangpaiSkilllv) * (pc.m_Lv / 4) / hp1;
// 	hp1 += cBangPaiJiNengXueXi::m_BangpaiSkilllv;
	pc.HPMax.SetDataAddPercent(pc.m_Lv * 8);
	pc.MPMax.SetData(pc.MPMax.GetData() * (cBangPaiJiNengXueXi::m_BangpaiSkilllv * 2 + 100) / 100 + 0);
	pc.FillHpMp();
// 	if (pc.m_Lv > 20)
// 	{
// 		pc.Speed.AddDataAddPercent(20 + (pc.PointAgi - pc.m_Lv - cct::MinPoint) * 10 / pc.m_Lv);
// 	}
//	pc.SetCard(petid);
// 	if (pWeapon)
// 	{
// 		m_FightWorkList[id].m_pObj->SetWeapon强制换模型_不动数据_可能未鉴定(pWeapon->GetType(), pWeapon->GetID());
// 	}
//	return id;
	pc.SetJinJie(1);

	if (our)
	{
		pc._isOurTeamTemp = true;
	}
	else
	{
		pc._isWeakSeal = true;
	}
	return &pc;
}








