#include "_global.h"
static bool  s_isEnemyAutoAtkMode;

void ccm::init()
{
	saveWdf();
	saveMyWdf();
	g_GlobalValues[0] = 99;

	g_GlobalValues[6] = 0;
	g_GlobalValues[5] = 0;
	g_GlobalValues[4] = 0;

//	g_pMainState->LoadCharacterData2(g_pMainState->m_HeroID, "队长");
	g_pMainState->LoadCharacterData(eJuSe羽灵神);
	g_pMainState->LoadCharacterData(eJuSe逍遥生);
	g_pMainState->LoadCharacterData(eJuSe杀破狼);
	g_pMainState->LoadCharacterData(eJuSe剑侠客);
	g_pMainState->LoadCharacterData(eJuSe虎头怪);
// 	auto& obj = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
// 	obj->SetDataType(INDEXTYEP_CHARACTER);
// 	cCharacter* pc = (cCharacter*)obj->m_pIndex;
// 	cPcData& pcd = pc->m_PcData;
// 	pc->LoadButData(eJueSe::eJuSe剑侠客);
// 	obj->m_TrueName.SetColor(RGB(0, 255, 0));
// 	obj->SetTrueName(pc->GetData()->m_Name);
// 	pcd.m_Name = pc->GetData()->m_Name;
	g_pMainState->m_PCHead.UpDateHead();
	for (int i = 0; i < 5; ++i)
	{
		g_pMainState->m_Channel.AddNewString("ChannelTest", "表弟", i);
	}
	g_pHeroObj->m_ContextList.SetFaceText("贱人!,搞得人家都不想更了!#108", g_pMainState->m_hFont[0], 114);
//	g_pHeroObj->m_ShowTime = 0xFFFF;

// 	for (int i = 0; i < 109; ++i)
// 	{
// 		g_pCharacter->m_PcData.m_EXP += GetCharacterExp(g_pCharacter->m_PcData.m_Lv + 1);
// 		g_pCharacter->m_PcData.lvup();
// 	}

	int mps[] = { eMP_凌波城, eMP_普陀山, eMP_狮驼岭, eMP_神木林, eMP_阴曹地府 };
	auto cbCreate = [&mps](cPcData& pc)
	{
		pc.m_Lv = 69;
		int idx = pc.m_IDinFightWorkList;

		pc.setPointAfterLv(g_pMainState->getAddpointFromMp(mps[idx]), true);

		pc.autoData(true, true, true);
		pc.autoEquip(false);
		pc.apply();
		pc.FillHpMp();

		g_pCharacter->m_PcData.m_EXP += GetCharacterExp(0);
		pc.m_Money[0] += 1 << 30;

		for (int k = 0; k < 5; ++k)
		{
			cPet* pPet = new cPet;
			int model;
			{
				do
				{
					model = pc.m_Lv / 2 + rand() % (c_PetNumber - 2 - pc.m_Lv / 2 - 1);
					pPet->SetData(g_pMainState->m_PetDataManager.GetPetData(model));
				} while (pPet->GetData()->m_LvTake > pc.m_Lv);
			}
			cPetData& pp = pPet->m_PetData;
			pp.m_Name = pPet->GetData()->m_Name;
			pp.Load(model, true, true);
			pp.m_Lv = min((g_pCharacter->m_PcData.m_Lv + cct::LvGapFromRoleAndBaby), cct::MaxBabyLv);
			pp.PointRemain = cct::PointRemian;
			pp.setPointAfterLv(g_pMainState->getAddpointFromPet(&pp, true), true);

			pp.autoEquip(true, g_pMainState->m_AI.isAtkFromPoint(&pp));
			pp.apply();
			pp.FillHpMp();
			pc.AddPet(pPet);
			g_pMainState->SetFightPet(pc.m_IDinFightWorkList, rand() % pc.m_NumofBB);
		}
	};

	for (int i = 0; i < 5; ++i)
	{
		cbCreate(((cCharacter*)g_pMainState->m_FightWorkList[i].m_pObj->m_pIndex)->m_PcData);
	}

	g_pMainState->m_ZuoQi.GetZuoQi(g_pCharacter->m_PcData, 79 + rand() % 10);
// 	g_pMainState->m_InterfaceTeam.m_LeaveBegin = 5;
// 	for (int i = 1; i < g_pMainState->m_InterfaceTeam.m_LeaveBegin; ++i)
// 	{
// 		g_pMainState->m_FightWorkList[i].m_pObj->SetShow(true);
// 	}
//	g_pMainState->m_InterfaceTeam.UpDate();
	g_pMainState->m_PCHead.UpDateHead();
	
// 	for (int i = 1; i < 5; ++i)
// 	{
// 		cPcData* data = (cPcData*)g_pMainState->m_FightWorkList[i].m_pObj->getPropertyData();
// 		data->m_Lv = pc.m_Lv;
// 		data->setPointAfterLv(p, true);
// 		data->m_MengPaiID = mps[i];
// 
// 		forr(data->m_MengPaiSkillLvs, i)
// 		{
// 			data->m_MengPaiSkillLvs[i] = pc.m_Lv + cct::lvGapFromRoleAndSkill;
// 		}
// 		const auto& mpManeger = g_pMainState->m_SkillManager.m_MengPaiManager;
// 		const auto& mainSkills = mpManeger.m_MengPai[data->m_MengPaiID].m_MainSkill;
// 		forv(mainSkills, k)
// 		{
// 			const auto& pZhuJiNeng = &mainSkills[k];
// 			for (int i = 0; i < pZhuJiNeng->m_NumSkillInclude; i++)
// 			{
// 				sSkill* pSkill = (sSkill*)&mpManeger.m_SkillList[pZhuJiNeng->m_SkillIncludeID[i]];
// 				data->m_SkillEnablelist.push_back(pSkill);
// 			}
// 		}
// 		data->apply();
// 		data->FillHpMp();
// 
// 		g_pCharacter->m_PcData.m_EXP += GetCharacterExp(0);
// 		pc.m_Money[0] += 1 << 18;
// 	}





	////////////////////////////////////////////////////////////////////////// 宝宝
//	for (auto i : { e地狱战神, e如意仙子, e净瓶女娲, e炎魔神, e鼠先锋 })
//	for (auto i : { e阴阳伞, e锦毛貂精, e犀牛将军, e小魔头, e牛魔王 })
//	for (auto i : { e镇元大仙, e李靖, e观音姐姐, e空度禅师, e超级泡泡 })
//	for (auto i : { e镜妖, e泪妖, e琴仙, e金铙僧, e灵灯侍者})
//  for (auto i : { e增长巡守, e雪人, e小白泽, e小象, e般若天女 })
// 	for (auto i : { e剑灵, e龙马, e神猴, e神鸡, e土地 })
// 	{
// 		//	p.Set(0, 2, 0, 3, 0);
// 		cPet* pPet = new cPet;
// 		pPet->SetData(g_pMainState->m_PetDataManager.GetPetData(i));
// 		cPetData& pp = pPet->m_PetData;
// 		pp.m_Name = pPet->GetData()->m_Name;
// 		pp.Load(i, true, true);
// 		pp.m_Lv = g_pCharacter->m_PcData.m_Lv + cct::lvGapFromRoleAndBaby;
// 		pp.setPointAfterLv(p, true);
// 		pp.AddSkill(ePS_高级驱鬼);
// 		pp.apply();
// 		pp.FillHpMp();
// 		pc.AddPet(pPet);
// 		pp.LiveRelifeRate = 100;
// 	}
//	g_pMainState->SetFightPet(pc.m_IDinFightWorkList, 1);


// 	for (auto name : mapNames)
// 	{
// 		g_pMainState->m_Map.RemoveAllNpc();
// 		g_pMainState->m_Map.LoadMap(0, 0, name.c_str());
// 	}

//	g_pMainState->m_Map.LoadMap(19, 74, "蓬莱仙岛");
	g_pMainState->m_Map.LoadMap(520, 124, "长安城");
//	g_pMainState->LockLv(cct::maxRoleLv);

//	g_pMainState->m_ZuoQi.GetZuoQi(g_pCharacter->m_PcData, 79 + rand() % 10);
//	g_pMainState->m_ZuoQi.GetZuoQi(g_pCharacter->m_PcData, 8 + rand() % 137);
//	pc.m_bOnZuoQi = true;

// 	g_pMainState->_uiHeadTop.OnOff(true);
// 	g_pMainState->_uiXiangRui.OnOff(true);
// 	g_pMainState->_uiFoot.OnOff(true);
// 	g_pMainState->_uiFoot2.OnOff(true);
// 	g_pMainState->_uiAnimalSign.OnOff(true);
// 	g_pMainState->m_FangWu.SetGuiMo(3);

	for (int i = 42; i <= 51; ++i)
	{
		if (0 == (g_GlobalValues[1] & (1 << (i - 42))))
		{
			g_GlobalValues[1] |= (1 << (i - 42));
		}
	}

	return;

	auto addAndPaopao = [&](const string &name)
	{
		g_pMainState->m_Friend.AddFriend(name);
		g_pMainState->m_ZhuXian.AutoGetPet(name/*, 0*/);
	};

	auto addAndPaopaos = [&](const vector<string> &names)
	{
		for (const auto &name : names)
		{
			addAndPaopao(name);
		}
	};


	int locklv = 5;
	int pro = 0;
//	addAndPaopaos({ "篮子", "神天兵", "虎子" });

	auto expOnce = [&]()
	{
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
	};

	if (juQing > 0) // 玄奘前
	{
		expOnce();
		addAndPaopaos({ "燕子", "怀念", "敖白", "紫菜" });
		locklv = 25;
		pro = 1;
	}
	if (juQing > 1) // 琉璃前
	{
		addAndPaopao("清风");
		g_pMainState->m_Friend.AddFriend("傻妞");
		sShangPinPet sppet;
		sppet.Set(e超级大熊猫, 0, 100, true);
		g_pMainState->m_ZhuXian.GetPet("傻妞", &sppet, 100);
		expOnce();
		locklv = 55;
		pro = 2;
	}
	if (juQing > 2)// 西凉前
	{
		addAndPaopao("小蛮");
		locklv = 65;
		pro = 8;
	}
	if (juQing > 3) // 小白龙前
	{
		locklv = 75;
		pro = 3;
	}
	if (juQing > 4) // 天蓬前
	{
		expOnce();
		sShangPinPet sppet;
		sAddPoint addpoint;
		addpoint.Set(4, 0, 0, 1, 0);
		sppet.Set(e超级神兔, &addpoint, 100, true);
		g_pMainState->m_ZhuXian.GetPet("小蛮", &sppet, 100);

		g_pMainState->m_Friend.AddFriend("四季");

		addpoint.Set(0, 0, 4, 1, 0);
		sppet.Set(e超级海豚, &addpoint, 100, true);
		g_pMainState->m_ZhuXian.GetPet("四季", &sppet, 100);
		locklv = 105;
		pro = 4;
	}
	if (juQing > 5) // 猴哥前
	{
		g_pMainState->m_Friend.AddFriend("冷涯傲雪");
		g_pMainState->m_ZhuXian.AutoGetPet("冷涯傲雪"/*, 2*/);

		g_pMainState->m_Friend.AddFriend("小胖牛");
		g_pMainState->m_ZhuXian.AutoGetPet("小胖牛"/*, 3*/);

		//		g_pMainState->m_ZhuXian.AutoGetPet("紫菜", 4, 5);
		locklv = 125;
		pro = 5;
	}
	if (juQing > 6) // 白骨精前
	{
		expOnce();
		locklv = 135;
		pro = 6;
	}
	if (juQing > 7) // 芭蕉扇前
	{
		expOnce();
		pro = 7;
	}
	if (juQing > 8) // 门派蚩尤前
	{
		expOnce();
		locklv = 145;
	}
	if (juQing > 9) // 终章前
	{
		expOnce();
		locklv = 155;
		g_pMainState->m_Friend.AddFriend("羽灵神");
		pro = 9;
	}
	if (juQing > 10) // boss前
	{
		expOnce();
		g_pMainState->m_Friend.AddFriend("杀破狼");
		for (const auto &flist : g_pMainState->m_Friend.m_FriendList)
		{
			const string &name = flist.m_Name;
			g_pMainState->m_ZhuXian.AutoGetPet(name, rand() % 20 + 20);
			g_pMainState->m_ZhuXian.AutoGetPet(name, rand() % 20 + 20);
			for (int i = 0; i < 5; ++i)
			{
				g_pMainState->m_ZhuXian.AutoGetPet(name, rand() % 20);
			}
		}
		locklv = 175;
	}
 	int exp = 0;
// 	for (int i = cct::get()->minRoleLv;
// 		i < locklv - cct::get()->perLvup * 2;
// 		i += ((i % 10 == 5) ? 4 : 6))
// 	{
// 		exp += GetCharacterExp(i);
// 	}


//	g_pCharacter->m_PcData.m_BangPaiID = 0;
//	g_pCharacter->m_PcData.m_MengPaiID = -1;
//	g_pCharacter->m_PcData.LeveUp(cct::get()->minRoleLv, false, true);
//	g_pCharacter->m_PCData.FollowSkill();
//	g_pCharacter->m_PcData.FollowEuip();
//	g_pCharacter->m_PCData.FollowItem(true);
	g_pCharacter->m_PcData.FillHpMp();
// 	g_pHeroObj->Reset();
// 	g_pHeroObj->Set(POS_STAND);
	g_pCharacter->m_PcData.m_Money[0] = 0xffff;
	g_pCharacter->m_PcData.m_Money[1] = (1 << 24);
	g_pCharacter->m_PcData.m_EXP = exp;
	g_pMainState->m_Map.LoadMap(19, 74, "桃源村");
	g_GlobalValues[2] = (locklv);
//	g_pMainState->m_Friend.Invite("篮子");

//  	g_pMainState->m_Friend.AddFriend("敖白");
//  	g_pMainState->m_ZhuXian.AutoGetPet("敖白");
// 	g_pCharacter->m_PCData.LeveUp(cct::get()->maxRoleLv, false, true);
//  	g_pMainState->m_ZhuXian.SetChapter(4);
//  	g_pMainState->m_ZhuXian.Process4(10);
//    	return;

	if (pro == 0)
	{
		g_pMainState->m_ZhuXian.SetChapter(0);
		g_pMainState->m_ZhuXian.Process0(10086);
	}
	else if (pro == 1)
	{
		g_pMainState->m_ZhuXian.SetChapter(1);
		g_pMainState->m_ZhuXian.Process1(0);
	}
	else if (pro == 2)
	{
		g_pMainState->m_ZhuXian.Process2(0);
	}
	else if (pro == 3)
	{
		g_pMainState->m_ZhuXian.Process3(0);
	}
	else if (pro == 4)
	{
		g_pMainState->m_ZhuXian.Process4(0);
	}
	else if (pro == 5)
	{
		g_pMainState->m_ZhuXian.Process5(0);
	}
	else if (pro == 6)
	{
		g_pMainState->m_ZhuXian.Process6(0);
	}
	else if (pro == 7)
	{
		if (juQing > 8)
		{
			g_pMainState->m_ZhuXian.SetChapter(7);
			g_pMainState->m_ZhuXian.Process7(26);
		}
		else
		{
			g_pMainState->m_ZhuXian.Process7(0);
		}

	}
	else if (pro == 8)
	{
		g_pMainState->m_ZhuXian.Process8(0);
	}
// 	else if (pro == 9)
// 	{
// 		if (juQing > 10)
// 		{
// 			g_pMainState->m_ZhuXian.SetChapter(9);
// 			g_pMainState->m_ZhuXian.Process9(6);
// 		}
// 		else
// 		{
// 			g_pMainState->m_ZhuXian.Process9(0);
// 		}
// 	}


	g_pMainState->m_Tags.Add("更多彩蛋(说明书.txt)", INT_MAX);
	g_pMainState->m_Tags.Add("更多操作(png说明图)", INT_MAX);

	if (0)
	{
		ofstream fileOut;
		set<unsigned long> maps;
		set<unsigned long> map2s;
		set<int> mapIDs;
		for (auto name : mapNames)
		{
			g_pMainState->m_Map.RemoveAllNpc();
			g_pMainState->m_Map.LoadMap(0, 0, name.c_str());

			maps.insert(g_pMainState->m_Map.m_SmallMap.m_NowID);
			mapIDs.insert(g_pMainState->m_Map.m_MapNumber);
			for (const auto &jz : g_pMainState->m_Map.m_JianZhuID)
			{
				map2s.insert(jz);
			}
		}

		cWasFile m_File;
		ifstream *fileWdf = nullptr;

		int i = -1;
		for (const auto &e : maps)
		{
			bool b = m_File.GetFileP(e, fileWdf, [&](const uchar *data)
			{
				int size = 18;
				fileOut.open(toString("C:/Users/wolf/Desktop/mapwas/%04d-%x-0.was", ++i, e), ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入地图was失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入地图was遗漏");
		}
		//		return;
		i = -1;
		for (const auto &e : map2s)
		{
			bool b = m_File.GetFileP(e, fileWdf, [&](const uchar *data)
			{
				int size = 18;
				fileOut.open(toString("C:/Users/wolf/Desktop/map2was/%04d-%x-0.was", ++i, e), ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入建筑was失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入建筑was遗漏");
		}

		fileOut.open("C:/Users/wolf/Desktop/mapIDs.txt");
		if (!fileOut)
		{
			fileOut.close();
			asert(false, "写入建筑was失败");
			return;
		}
		fileOut << mapIDs.size() << "\n";
		for (const auto &e : mapIDs)
		{
			fileOut << e << "\n";
		}
		fileOut.close();
	}
}



void ccm::useCard(int id2 /* = -1 */)
{
	//	g_pCharacter->m_PCData.m_JinJieNum.m_PositionID = 1;
	cPcData& pc = g_pCharacter->m_PcData;
	if (id2 < 0)
	{
		id2 = pc.modeid;
		if (++id2 >= g_pMainState->m_pCharacterDataList.size())
		{
			id2 = 0;
		}
	}
	g_pCharacter->changeModel(id2);

	const auto& clist = g_pMainState->m_pCharacterDataList;

	string name = clist[id2].m_Name;
	forr(clist, i)
	{
		if (i == id2)
		{
			continue;
		}
		const auto& name2 = clist[i].m_Name;
		if (pc.m_Name == name2)
		{
			pc.m_Name = name;
		}
		if (g_pHeroObj->m_TrueName.GetString() == name2)
		{
			g_pHeroObj->m_TrueName.SetString(name);
		}
		if (g_pHeroObj->m_Name称谓.GetString() == name2)
		{
			g_pHeroObj->m_Name称谓.SetString(name);
		}
	}
}

void ccm::PKinit()
{
//	s_isEnemyAutoAtkMode = isBattle打野;
//	isBattle打野 = true;
	return;
	g_pMainState->m_ZhiXian3.Init2();
}



static vector<cCharacter*> s_cs;
void ccm::PK()
{
	int id = g_pMainState->m_InterfaceTeam.getLeaveBegin();
	s_cs.resize(id);
	for (int i = id - 1; i >= 0; --i)
	{
		cObj *objMe = g_pMainState->m_FightWorkList[i].m_pObj;
		cPcData &pcMe = *objMe->getPcData();

		id = i + 10;
		auto& list = g_pMainState->m_FightWorkList[id];
		list.isExist = true;
		cObj* obj = list.m_pObj;
		obj->AutoData(pcMe.modeid, nullptr, -1, pcMe.m_Name + "影子");
		cPcData& pc = *obj->getPcData();
		pc.m_IDinFightWorkList = id;
		pc.m_Name = obj->m_TrueName.GetString();
		pc.Load(pcMe.modeid, pcMe.m_MengPaiID);
		pc.m_Lv = pcMe.m_Lv;
		pc.PointBody = pcMe.PointBody;
		pc.PointMag = pcMe.PointMag;
		pc.PointStr = pcMe.PointStr;
		pc.PointDex = pcMe.PointDex;
		pc.PointAgi = pcMe.PointAgi;

		pc.m_XiuLian = pcMe.m_XiuLian;
		pc.m_XiuLianBB = pcMe.m_XiuLianBB;
		pc.m_FuZhuSkillLvList = pcMe.m_FuZhuSkillLvList;
		pc.m_MengPaiSkillLvs = pcMe.m_MengPaiSkillLvs;

		pc.m_Fabaos = pcMe.m_Fabaos;
		pc.m_Equips = pcMe.m_Equips;

		pc.m_NumofBBSkill = pcMe.m_NumofBBSkill;
		pc.m_petSkills = pcMe.m_petSkills;

		pc.m_pCharacterData2 = nullptr;
		pc.m_pWeaponData2 = nullptr;
		
		pc.apply();
		pc.Speed.AddDataAdd(1);
		pc.FillHpMp();
		
		for (int k = 0; k < pcMe.m_NumofBB; ++k)
		{
			cPetData& petMe = pcMe.m_pPets[k]->m_PetData;
			if (k == pcMe.m_FightPetID)
			{
				auto p = g_pMainState->AddEnemy(petMe.modeid, petMe.m_Lv, petMe.m_Name + "影子", nullptr, id + 5);

// 				cPet* pet0 = new cPet();
// 				pet0->SetData(g_pMainState->m_PetDataManager.GetPetData(petMe.modeid));
// 				cPetData& pet = pet0->m_PetData;
// 				pet.m_Name = petMe.m_Name + "影子";
// 				pet.Load(petMe.modeid, false, false);
				p->m_NumofBBSkill = petMe.m_NumofBBSkill;
				p->m_petSkills = petMe.m_petSkills;
				p->m_ZiZhi = petMe.m_ZiZhi;
				p->m_JinJieNum = petMe.m_JinJieNum;
				p->m_Lv = petMe.m_Lv;
				p->PointBody = petMe.PointBody;
				p->PointMag = petMe.PointMag;
				p->PointStr = petMe.PointStr;
				p->PointDex = petMe.PointDex;
				p->PointAgi = petMe.PointAgi;
				p->m_Equips = petMe.m_Equips;
				p->m_XiuLian = pcMe.m_XiuLianBB;
				p->apply();
				p->FillHpMp();
				continue;
			}
//			cPetData& petMe = pcMe.m_pPets[k]->m_PetData;
			cPet* pet0 = new cPet();
			pet0->SetData(g_pMainState->m_PetDataManager.GetPetData(petMe.modeid));
			cPetData& pet = pet0->m_PetData;
			pet.m_Name = petMe.m_Name + "影子";
			pet.Load(petMe.modeid, false, false);
			pet.m_NumofBBSkill = petMe.m_NumofBBSkill;
			pet.m_petSkills = petMe.m_petSkills;
			pet.m_ZiZhi = petMe.m_ZiZhi;
			pet.m_JinJieNum = petMe.m_JinJieNum;

			pet.m_Lv = petMe.m_Lv;
			pet.PointBody = petMe.PointBody;
			pet.PointMag = petMe.PointMag;
			pet.PointStr = petMe.PointStr;
			pet.PointDex = petMe.PointDex;
			pet.PointAgi = petMe.PointAgi;
			pet.m_XiuLian = pcMe.m_XiuLianBB;

			pet.m_Equips = petMe.m_Equips;
			pet.m_Controler.Set(true, false, true);
			pet.apply();
			pet.FillHpMp();
			pc.AddPet(pet0);
		}

// 		g_pMainState->SetFightPet(id, -1);
// 		auto& list5 = g_pMainState->m_FightWorkList[id + 5];
// 		if (pcMe.m_FightPetID >= 0)
// 		{
// 			g_pMainState->SetFightPet(id, pcMe.m_FightPetID);
// 			list5.m_pObj->ClearState();
// 			list5.m_pObj->Reset();
// 			list5.m_pObj->Set(POS_FIGHT_STAND);
// 			list5.m_pObj->SetStatic(false);
// 		}
// 		list5.m_bPrePareFight = false;
		pc.m_Controler.Set(false, false, false, true, false);
		s_cs[i] = (cCharacter*)obj->m_pIndex;
	}
	g_pMainState->FindObj();
}


struct sModeName{ int mode; string name; };
sModeName getModeFormMp(int mp)
{
	auto getName2 = [](const string &name1, const string &name2)
	{
		if (rand() % 100 < 50)
		{
			return name1;
		}
		return name2;
	};
	auto getMode2 = [](int mode1, int mode2)
	{
		if (rand() % 100 < 50)
		{
			return mode1;
		}
		return mode2;
	};

	auto getRand2 = [](int mode1, const string &name1, int mode2, const string &name2)
	{
		sModeName mn = { mode1, name1 };
		if (rand() % 100 < 50)
		{
			mn = { mode2, name2 };
		}
		return mn;
	};
	eMengPai e = (eMengPai)mp;
	sModeName mn = { 0, "猪队友" };
	switch (e)
	{
	case eMP_大唐官府:
		if (rand() % 100 < 50)
		{
			mn = { 1, "中国好少年" };
			break;
		}
		mn = { 0, getName2("桂小太郎", "酒伴何以久伴") };
		break;
	case eMP_化生寺:
		mn = { 1, getName2("情圣战天", "笑傲江湖757") };
		break;
	case eMP_女儿村:
		mn = { getMode2(2, 3), "微风筑城" };
		break;
	case eMP_方寸山:
		mn = getRand2(0, "待墨成碑", 12, "微风筑城");
		break;
	case eMP_狮驼岭:
		mn = getRand2(5, "是你的牛哥", 14, "狮驼大明王");
		break;
	case eMP_魔王寨:
		mn = { 4, "大笨猫" };
		break;
	case eMP_盘丝岭:
		mn = { getMode2(6, 7), "丫头" };
		break;
	case eMP_阴曹地府:
		mn = getRand2(4, "大笨猫", 14, "竟无言以对");
		break;
	case eMP_东海龙宫:
		mn = { 8, getName2("无聊的风车", "醉翁李") };
		break;
	case eMP_五庄观:
		mn = getRand2(8, "嘉喜", 9, "附魔帝君");
		break;
	case eMP_普陀山:
		mn = { getMode2(10, 11), "淡漠" };
		break;
	case eMP_天宫:
		mn = { 13, "小林子" };
		break;
	}
	return mn;
}

std::array<sAddPoint, 12> getPkAddpoint()
{
	ifstream File;
	File.open(/*g_pathPK + */"加点.txt");
	asert(bool(File), "无法读取擂台(加点.txt)");
	std::array<sAddPoint, 12> aps;
	string temp;
	forv(aps, i)
	{
		File >> aps[i].str;
		File >> aps[i].dex;
		File >> aps[i].body;
		File >> aps[i].mag;
		File >> aps[i].agi;
		getline(File, temp);
	}
	File.close();
	return aps;
}

void ccm::PK(int lv)
{
	int mid = g_pMainState->m_pNowSelect->GetModeID() - 2000;
	vector<int> lvs = { 69, 89, 89, 109, 109, 109, 129, 129, 129, 159, 159, cct::MaxRoleLv };
	bool isRand = std::find(lvs.begin(), lvs.end(), lv) == lvs.end();
	int mp = eMP_随机;
	int r = rand() % 100;
	if (r > 85)
	{
		mp = eMP_物理;
	}
	else if (r > 70)
	{
		mp = eMP_法系;
	}
	else if (r > 55)
	{
		mp = eMP_输出;
	}
	else if (r > 40)
	{
		mp = eMP_辅助;
	}

	eMengPai e;
	int modeid;
	int lv2;
	int num = (isRand ? (2 + rand() % 4) : 5);
	s_cs.resize(num);
	num += 10;
	for (int id = 10; id < num; ++id)
	{
		do
		{
			e = (eMengPai)cct::getMenpai((id == 10) ? eMP_随机 : mp);
			modeid = g_pMainState->getModelFromMp(e);
			if (id != 10 || mid == modeid)
			{
				break;
			}
		} while (true);
		auto& flist = g_pMainState->m_FightWorkList[id];
		flist.isExist = true;
		flist.m_pObj->AutoData(modeid + 2000, nullptr);
		cPcData& pc = *flist.m_pObj->getPcData();
		pc.Load(modeid, e);
		pc.m_Lv = isRand ? (lvs[rand() % lvs.size()]) : lv;
		pc.PointRemain = cct::PointRemian;
		pc.setPointAfterLv(g_pMainState->getAddpointFromMp(e, true), true);
		pc.autoData(true, true, true);
		pc.autoEquip(false);
		pc.m_Equips[4].m_Property[14] = 0;
		vector<int> spels = { 7, 9, 10, 13, 25, 48 };
		forr(spels, kk)
		{
			pc.m_Equips[kk].m_Property[12] = spels[kk];
		}
		pc.apply();
		pc.FillHpMp();
		pc.m_IDinFightWorkList = id;


		for (int k = pc.m_pPets.size() - 2; k >= 0; --k)
		{
			modeid = cct::getPetModel(pc.m_Lv - 34, pc.m_Lv, true);
			lv2 = pc.m_Lv + cct::LvGapFromRoleAndBaby;
			lv2 = min(lv2, cct::MaxBabyLv);
			cPet* pet0 = new cPet;
			g_pMainState->AutoPet(pet0, modeid, lv2, true);
			cPetData& pet = pet0->m_PetData;
			pet.SetJinJie(1 + rand() % 3);
			pet.m_IDinFightWorkList = id + 5;
		//	pet.m_Controler.Set(true, true, true);
			pc.AddPet(pet0);
		}

		{
			modeid = cct::getPetModel(pc.m_Lv - 34, pc.m_Lv, true);
			lv2 = pc.m_Lv + cct::LvGapFromRoleAndBaby;
			lv2 = min(lv2, cct::MaxBabyLv);
			auto p = g_pMainState->AddEnemy(modeid, lv2, "", nullptr, id + 5);

			bool isGad = (g_pMainState->m_PetDataManager.m_PetList[modeid].m_LvTake == 0);
			if (!isGad)
			{
				p->AddSkill(108);
				p->AddSkill(105);
			}
			p->PointRemain = cct::PointRemian;
			p->setPointAfterLv(g_pMainState->getAddpointFromPet(p, true), true);
			if (!isGad)
			{
				p->m_NumofBBSkill -= 2;
			}

			bool isFs = !p->autoData(true, !isGad || p->m_NumofBBSkill == 0);
			p->autoEquip(true, !g_pMainState->m_AI.isMagFromPoint(p));
			p->SetJinJie(1 + rand() % 3);
		}

//		auto& list5 = g_pMainState->m_FightWorkList[id + 5];
//		g_pMainState->SetFightPet(id, rand() % pc.m_NumofBB);
// 		list5.m_pObj->ClearState();
// 		list5.m_pObj->Reset();
// 		list5.m_pObj->Set(POS_FIGHT_STAND);
// 		list5.m_pObj->SetStatic(false);
//		list5.m_bPrePareFight = false;

		pc.m_Controler.Set(false, false, false, true);
		s_cs[id - 10] = (cCharacter*)flist.m_pObj->m_pIndex;
	}
	g_pMainState->FindObj();
	return;

	int flag = 0;
	int format = (flag >> 24) - 1;

	flag %= (1 << 24);
	vector<int>mps;
//	int num = flag % 16;
	mps.resize(flag % 16);
	forr(mps, i)
	{
		mps[i] = (flag >> ((i + 1) * 4));
		flag %= (1 << ((i + 1) * 4));
	}
	auto aps = getPkAddpoint();
	for (int i = 0; i < num; ++i)
	{
		int id = i + 10;
		int mp = mps[i];
		int bbNum = 8;
		sAddPoint ap;
		if (mp >= 0 && mp < 12)
		{
			ap = aps[mp];
		}
		auto mn = getModeFormMp(mp);
		sZiZhi zz;
		int grow = 3;
		if (mp == eMP_东海龙宫)
		{
			grow = 2;
		}
		else if (mp == eMP_魔王寨 || mp == eMP_方寸山 || mp == eMP_化生寺 || mp == eMP_普陀山)
		{
			grow = 4;
		}
		zz.Set(100, 100, 100, 100, 100, 100, grow);
		g_pMainState->m_FightWorkList[id].isExist = true;
//		g_pMainState->m_FightWorkList[id].m_pObj->AutoPCData(mn.name, mn.mode, &ap, &zz, (eMengPai)mp);
		cObj *obj = g_pMainState->m_FightWorkList[id].m_pObj;
		cPcData &pc = ((cCharacter*)obj->m_pIndex)->m_PcData;
// 		pc.FollowlvAddPoint(g_pCharacter->m_PcData.m_Lv, false, true, true);
// 		learnPetSkill(pc);
// 		pc.m_AiLv = true;
//		pc.FollowShoe();
//		for (int i = 0; i < 4; i++)
		if (isClassical)
		{
			int i = 0;
			sChangeColorData &rs = pc.m_RanSe.m_ranse[i];
			//			rs.Read(File, mn.mode, sChangeColorData::ePc, i);
			rs.partnum = 4;
			ulong color = g_pMainState->m_pCharacterDataList[mn.mode].m_ColorID;
			if (color == 0)
			{
				color = 0x1657;
			}
			g_pMainState->m_ColorManage.Set(color);
			for (int k = 0; k < rs.partnum; ++k)
			{
				rs.SetColorChange(k, (k <= 2) ? (rand() % 8) : 0);
				g_pMainState->m_ColorManage.GetColorMatrix(
					k,
					rs.GetColorChange(k),
					rs.m_colormatrix[k]);
			}
		}
		for (int k = 0; k < bbNum; ++k)
		{
			bool isAtk = rand() % 100 < 35;
			sShangPinPet spet;
			spet.LoadEasy(isAtk ? 0 : 20);
			int pmode;
			while (true)
			{
				pmode = rand() % 162;
				if (pmode >= 114 && pmode <= 148)
				{
					continue;
				}
				int lv = g_pMainState->m_PetDataManager.m_PetList[pmode].m_LvTake;
				if (lv > pc.m_Lv)
				{
					continue;
				}
				if (lv > 0 && lv < pc.m_Lv - 80)
				{
					continue;
				}
				if (pc.m_Lv < 45 && lv == 0)
				{
					continue;
				}
				if (pc.m_Lv >= 45 && lv >= 5 && lv < 45)
				{
					continue;
				}
				if (pc.m_Lv >= 45 && lv == 0 && rand() % 100 < 80)
				{
					continue;
				}
				break;
			}

			cPet* pet = new cPet();
			pet->m_PetData.m_ZiZhi.Set(1600, 1600, 3000, 8000, 1600, 1600, 144);
//			pet->m_PetData.m_ZiZhi.Set(pet->m_PetData.m_ZiZhi, 0, 0);
			pet->m_PetData.m_ZiZhi = pet->m_PetData.m_ZiZhi;
			for (auto skill : spet.m_skillid)
			{
				pet->m_PetData.AddSkill(ePetSkill(skill));
			}
			if (isAtk)
			{
				if (rand() % 100 < 35)
				{
					pet->m_PetData.AddSkill((rand() % 100 < 62) ? ePetSkill::ePS_力劈华山 : ePetSkill::ePS_善恶有报);
				}
			}
			else
			{
				pet->m_PetData.AddSkill(ePetSkill(85 + (rand() % 4) * 2));
			}
			pet->SetData(g_pMainState->m_PetDataManager.GetPetData(pmode));
// 			if (isAtk)
// 			{
// 				if (rand() % 100 < 50)
// 				{
// 					pet->m_PetData.m_AddPoint.Set(4, 0, 0, 1, 0);
// 				}
// 				else
// 				{
// 					pet->m_PetData.m_AddPoint.Set(3, 1, 0, 1, 0);
// 				}
// 			}
// 			else
// 			{
// 				if (rand() % 100 < 50)
// 				{
// 					pet->m_PetData.m_AddPoint.Set(0, 0, 4, 1, 0);
// 				}
// 				else
// 				{
// 					pet->m_PetData.m_AddPoint.Set(0, 1, 3, 1, 0);
// 				}
// 			}
// 			int lv = pc.m_Lv + ccm::get()->lvGapFromRoleAndBaby;
// 			if (lv > ccm::get()->maxBabyLv)
// 			{
// 				lv = ccm::get()->maxBabyLv;
// 			}
//			pet->m_PetData.Followlv(lv, true, true, true);
			pet->m_PetData.m_Name = g_pMainState->m_PetDataManager.GetPetData(pmode)->m_Name;
			pet->m_PetData.SetJinJie(rand() % 3 + 1);
			pc.AddPet(pet);

			if (0)
			{
				int i = 0;
				sChangeColorData &rs = pet->m_PetData.m_RanSe.m_ranse[i];
				//			rs.Read(File, mn.mode, sChangeColorData::ePc, i);
				rs.partnum = 4;
				ulong color = g_pMainState->m_PetDataManager.GetPetData(pet->m_PetData.modeid)->m_ModelActs[i].m_ColorID;
				if (color == 0)
				{
					color = 0x1657;
				}
				g_pMainState->m_ColorManage.Set(color);
				for (int k = 0; k < rs.partnum; ++k)
				{
					rs.SetColorChange(k, rand() % 4);
					g_pMainState->m_ColorManage.GetColorMatrix(
						k,
						rs.GetColorChange(k),
						rs.m_colormatrix[k]);
				}
			}

		}
		if (pc.m_NumofBB > 0)
		{
			g_pMainState->SetFightPet(id, 0);
			g_pMainState->m_FightWorkList[id + 5].m_pObj->Set(POS_FIGHT_STAND);
		}

		pc.m_Controler.Set(false, false, false, true, false);
	}

	auto& team = g_pMainState->m_InterfaceTeam;
	eFormation eOld = team.m_eEnemyFormation;
	team.m_eEnemyFormation = team.m_eOurFormation;
	team.SetFighterPos(true);
	team.m_bLiineupSelect = false;
	team.m_eEnemyFormation = eOld;
}



void ccm::PKover()
{
	forr(s_cs, i)
	{
		s_cs[i]->Free();
		g_pMainState->m_FightWorkList[i + 15].m_pObj->m_pIndex = 0;
		g_pMainState->m_FightWorkList[i + 15].m_pObj->m_IndexType = 0;
		SAFE_DELETE(s_cs[i]);
		g_pMainState->m_FightWorkList[i + 10].m_pObj->m_pIndex = 0;
		g_pMainState->m_FightWorkList[i + 10].m_pObj->m_IndexType = 0;
	}

	return;
//	isBattle打野 = s_isEnemyAutoAtkMode;
	for (int i = 10; i < 15; i++)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			g_pMainState->SetFightPet(i, -1);
		}
	}
}


struct sPkTeam { string name; vector<int>mps; int format = 0; };

void ccm::PKNpc(int flag)
{
	cMyMap *mymap = &g_pMainState->m_Map;
	sNpc npc;
	vector<int> lvs = { 69, 89, 89, 109, 109, 109, 129, 129, 129, 159, 159, cct::MaxRoleLv };
	vector<string> names = { "精锐", "勇武", "勇武", "神威", "神威", "神威", "天科", "天科", "天科", "天元", "天元", "天元" };
	int r, mid, typelist[2], weapontype, weaponid;
	string name;
	while (true)
	{
		if (mymap->m_numberOfNpc >= MAX_NPC_NUM / 2)
		{
			return;
		}
		r = rand() % lvs.size();
		cObj* obj = mymap->m_pNpc[mymap->m_numberOfNpc];
		mid = rand() % g_pMainState->m_pCharacterDataList.size();

		obj->m_ScriptOneType = 1010;
		if (flag == 0)
		{
			obj->m_ScriptOneId = 0;
			name = g_pMainState->m_pCharacterDataList[mid].m_Name;
		}
		else
		{
			obj->m_ScriptOneId = lvs[r];
			name = names[r];

		}
		GetWeaponType(mid, typelist[0], typelist[1]);
		weapontype = typelist[rand() % 2];
		if (weapontype < 0)
		{
			weapontype = typelist[0];
		}

		weaponid = g_pMainState->m_ItemManage.GetIDByLv(weapontype, lvs[r]);
		npc.Set(name, mymap->m_MapName, mid + 2000, 0, 0);
		mymap->AutoGetPos(npc.m_x, npc.m_y, mymap->m_MapName);
		npc.weaponid = weaponid;
		npc.weapontype = weapontype;
		mymap->AddNpc(&npc, nullptr, "单");
	}
	return;

	ifstream file;
	vector<sPkTeam> teams;
	auto readTeam = [&](int n)
	{
		file.open(/*g_pathPK + */toString("%d人队.txt", n));
		asert(bool(file), "无法读取擂台(%d人队.txt)", n);
		sPkTeam team;
		team.mps.resize(n);
		int num;
		file >> num;
		string strTemp;
		getline(file, strTemp);
		for (int i = 0; i < num; ++i)
		{
			file >> team.name;
			asert(team.name.size(), "擂台(%d人队.txt)队名错误");
			for (int k = 0; k < n; ++k)
			{
				file >> team.mps[k];
				asert(team.mps[k] >= 0 && team.mps[k] <= 11, "擂台(%d人队.txt)门派编号错误");
			}
			if (n == 5)
			{
				file >> team.format;
				asert(team.format >= 0 && team.format <= 10, "擂台(%d人队.txt)阵型编号错误");
			}
			teams.push_back(team);
			getline(file, strTemp);
		}
		file.close();
	};

	auto readTeamRand = [&]()
	{
		sPkTeam team;
		int n = 2 + rand() % 4;
		team.mps.resize(n);
		team.name = "酱油";
		if (n == 3)
		{
			team.name = "杂牌";
		}
		else if (n == 4)
		{
			team.name = "混搭";
		}
		else if (n == 5)
		{
			team.name = "随机";
		}

		team.name += "队";
		for (int k = 0; k < n; ++k)
		{
			team.mps[k] = rand() % 12;
		}
		if (n == 5)
		{
			team.format = 1 + rand() % 10;
		}
		teams.push_back(team);
	};

	auto getStageFormMp = [&](const sPkTeam &t)
	{
		unsigned int n = t.mps.size();
		forv(t.mps, i)
		{
			n += (t.mps[i] << (4 * (i + 1)));
		}
		return n += ((t.format + 1) << 24);
	};

	for (int i = 1; i <= 5; ++i)
	{
		readTeam(i);
	}
	for (int i = 0; i < 50; ++i)
	{
		readTeamRand();
	}
	while (teams.size() >= 60)
	{
		teams.pop_back();
	}

// 	cMyMap *mymap = &g_pMainState->m_Map;
// 	sNpc npc;
	for (const auto &t : teams)
	{
		if (mymap->m_numberOfNpc >= 59)
		{
			return;
		}

		mymap->m_pNpc[mymap->m_numberOfNpc]->m_ScriptOneType = 1010;
		mymap->m_pNpc[mymap->m_numberOfNpc]->m_ScriptOneId = getStageFormMp(t);
		int typelist[2];
		GetWeaponType(t.mps.front(), typelist[0], typelist[1]);
		int weapontype = typelist[rand() % 2];
		int	weaponid = g_pMainState->m_ItemManage.GetIDByLv(weapontype, g_pCharacter->m_PcData.m_Lv);
		npc.Set(t.name, mymap->m_MapName, t.mps.front() + 2000, 0, 0);
		mymap->AutoGetPos(npc.m_x, npc.m_y, mymap->m_MapName);
		npc.weaponid = weaponid;
		npc.weapontype = weapontype;
		mymap->AddNpc(&npc, nullptr, "单");
	}
}




bool ccm::isAtkMode(int id)
{
	if (id >= 0 && id < 10)
	{
		return true;
//		return isAutoAtkMode;
	}

	cPropertyData *data = nullptr;
	g_pMainState->m_FightWorkList[id].m_pObj->GetPropertyData(data);
	if (!data)
	{
		asert(false, "AI战斗编号错误");
	}

	int k = data->m_XiuLian.GetAtk();
	if (0/*isBattle打野*/)
	{
		k = 100;
	}
	else
	{
		int i = data->m_XiuLian.GetMag();
		if (i > k)
		{
			k = i;
		}
		k = 20 + k * 3;
	}
	if (k > 95)
	{
		k = 95;
	}
	return  rand() % 100 > k;


}









#include "_global.h"

static ccm *s_myTestInstance = nullptr;
struct sWid{ string desc; unsigned long id; };
vector<sWid> *s_wids = nullptr;
set<unsigned long> s_wdfSet;
static unsigned long *s_wdfs = nullptr;
static int s_indexOfWdf = -1;
map<unsigned long, unsigned long> s_tables;
map<unsigned long, int> s_ignores;
static int per加点front = 1;

ccm* ccm::get()
{
	if (!s_myTestInstance)
	{
		s_myTestInstance = new ccm();
		// 		s_myTestInstance->putMenpaiSkills = { 0, 50, 80, 98, 131 };
		// 		s_myTestInstance->putPetSkills = { 1, 3, 7, 15, 24, 26, 48, 52, 56, 58, 75, 82, 103 };
		s_wids = new vector<sWid>();
		s_wdfs = new unsigned long[32768];
	}
	return s_myTestInstance;
}




// void ccm::switch加点方案()
// {
// 	if (per加点 == 10)
// 	{
// 		per加点 = (per加点front == 1) ? 100 : 1;
// 		per加点front = 10;
// 	}
// 	else if (per加点 == 100)
// 	{
// 		per加点 = 10;
// 		per加点front = 100;
// 	}
// 	else
// 	{
// 		per加点 = 10;
// 		per加点front = 1;
// 	}
// 
// 	if (per加点 == 1)
// 	{
// 		g_pMainState->m_Tags.Add("普通加点");
// 	}
// 	else if (per加点 == 10)
// 	{
// 		g_pMainState->m_Tags.Add("快速加点");
// 	}
// 	else
// 	{
// 		g_pMainState->m_Tags.Add("超速加点");
// 	}
// }


void ccm::playerNormalize(int lv /*= 0*/)
{
	g_pMainState->m_pFightState->EscapeFight();
	return;
	// 	g_pCharacter->m_PcData.LeveUp(-10, false, false);
	// 	g_pCharacter->m_PcData.Followlv(lv, false, true, true);
}


void ccm::addMoney(int money)
{
	g_pCharacter->m_PcData.m_Money[0] += 1000000;
}




void learnPetSkill(cPcData &pc)
{
	int mp = pc.m_MengPaiID;
	for (auto eskill : { 0, 2, 7, 9, 17, 25, 29, 76, 81 })
	{
		pc.AddSkill(ePetSkill(eskill));
	}
	if (mp == eMP_东海龙宫 || mp == eMP_魔王寨)
	{
		pc.AddSkill(ePetSkill(47));
		pc.AddSkill(ePetSkill(59));
	}
	else if (mp == eMP_大唐官府 || mp == eMP_狮驼岭)
	{
		for (auto eskill : { 10, 23, 39, 75 })
		{
			pc.AddSkill(ePetSkill(eskill));
		}
	}
}





void ccm::暗雷场景马上战斗()
{
	g_pMainState->m_TaskNormal.Process(1);
}

bool ccm::isInBattle()
{
	return g_StateType == STATE_FIGHT;
}

void ccm::set仙店(int lv)
{
	g_GlobalValues[3] = lv;
}


bool ccm::isSpecialOrZZ(int zz)
{
	return zz < 50;
}

// int ccm::getBabyLv()
// {
// 	return g_pCharacter->m_PcData.m_Lv + lvGapFromRoleAndBaby;
// }

int ccm::getDesbinOf头盔(int e, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10;
	if (e == eMP_大唐官府 || e == eMP_狮驼岭)
	{
		++dusbin;
	}
	return dusbin;
}

int ccm::getDesbinOf项链(int e, int teji /* = 0 */)
{
	return (teji + 1) * 10;
}

int ccm::getDesbinOf武器(int e, int teji /* = 0 */)
{
	return (teji + 1) * 10;
}

int ccm::getDesbinOf铠甲(int e, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10;
	if (e == eMP_东海龙宫 || e == eMP_魔王寨)
	{
		++dusbin;
	}
	else if (e == eMP_无 || e == eMP_普陀山 || e == eMP_阴曹地府 || e == eMP_盘丝岭 || e == eMP_狮驼岭)
	{
		dusbin += 2;
	}
	return dusbin;
}

int ccm::getDesbinOf腰带(int e, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10 + 1;
	if (e == eMP_东海龙宫 || e == eMP_魔王寨 || e == eMP_无)
	{
		--dusbin;
	}
	return dusbin;
}

int ccm::getDesbinOf鞋子(int e, bool isAtk /* = false */, int teji /* = 0 */)
{
	int dusbin = (teji + 1) * 10;
	if (e == eMP_大唐官府 || e == eMP_狮驼岭 || (isAtk && (e == eMP_五庄观 || e == eMP_女儿村 || e == eMP_阴曹地府 || e == eMP_盘丝岭)))
	{
		dusbin += 1;
	}
	else if (e == eMP_东海龙宫 || e == eMP_魔王寨 || (isAtk && (e == eMP_化生寺 || e == eMP_方寸山 || eMP_天宫)))
	{
		dusbin += 2;
	}
	// 	else if (e == eMP_化生寺 || e == eMP_普陀山 || e == eMP_阴曹地府 || e == eMP_无)
	// 	{
	// 		// 气血
	// 		dusbin += 3;
	// 	}
	return dusbin;
}

void ccm::initControl()
{
	//	g_pMainState->m_GlobalButton[0] = 99;
	//	g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(isControl);
}


void ccm::pushWdf(const string &desc, unsigned long id)
{
	if (juQing != 10086 && juQing != 10087)
	{
		return;
	}
	s_wdfs[++s_indexOfWdf] = id;
	asert(s_indexOfWdf < 32768, "wdf索引溢出");
	return;
	s_wids->push_back({ desc, id });
}

void ccm::pushWdf2(const string &desc, unsigned long id)
{
	pushWdf(desc, id);
}

void ccm::saveWdf()
{
	if (juQing != 10086 && juQing != 10087)
	{
		return;
	}
	s_wdfSet.clear();
	if (juQing == 10086)
	{
		pushWdf3();
	}
	for (int i = 0; i <= s_indexOfWdf; ++i)
	{
		if (s_wdfs[i] > 552)
		{
			s_wdfSet.insert(s_wdfs[i]);
		}
	}
	string path/* = gpathExpand*/;
	if (juQing == 10086)
	{
		path += "全部wdf.txt";
	}
	else if (juQing == 10087)
	{
		path += "差异wdf.txt";
	}
	ofstream file(path);
	asert((bool)file, "写入%s失败", path.c_str());
	file << s_wdfSet.size() << "\n";
	for (const auto &wdf : s_wdfSet)
	{
		file << toString("%lu", wdf) << "\n";
	}
	file.close();
	ccc_msgbox("写入%s完毕", path.c_str());
	return;

	file << s_wids->size() << "\n";
	for (const auto &wdf : *s_wids)
	{
		file << wdf.id << "      " << wdf.desc << "\n";
	}

	file << (s_indexOfWdf + 1) << "\n";
	for (int i = 0; i <= s_indexOfWdf; ++i)
	{
		file << s_wdfs[i] << "\n";
	}
	delete[] s_wdfs;

	file.close();
	ccc_msgbox("写入wdf列表成功");
}


void ccm::pushWdf3()
{
	s_wdfSet.insert(0xCF1D211E);
	s_wdfSet.insert(0x535C1994);
	s_wdfSet.insert(0x1733E33B);
	s_wdfSet.insert(0x1FBC5273);
	s_wdfSet.insert(0xB48A9B3D);
	s_wdfSet.insert(0x5A055B13);
	s_wdfSet.insert(0xB87E0F0C);
	s_wdfSet.insert(0xB352AE45);
	s_wdfSet.insert(0xC5750B15);
	s_wdfSet.insert(0xFC03AFF1);
	s_wdfSet.insert(0x0D98AC0A);
	s_wdfSet.insert(0x9B3AF4E5);
	s_wdfSet.insert(0xA16FD45C);
	s_wdfSet.insert(0x02EF9247);
	s_wdfSet.insert(0xCAB0B8B4);//0x9874B9B8
	s_wdfSet.insert(0xA15292B2);//0x8F499AA3
	s_wdfSet.insert(2119033822);//0x216FE0F8
	s_wdfSet.insert(0x3D1FA249);
	s_wdfSet.insert(250440769);//0xD5D51AD0  410697672
	s_wdfSet.insert(240383749);// 240383749 //0x78DDA320
	s_wdfSet.insert(2088395993);//0xD5DF5927
	s_wdfSet.insert(0x5116F7DF);//0x414977BD
	s_wdfSet.insert(222208523);//0x3B9F2278
	s_wdfSet.insert(0x1DF7B97D);//  574791040);
	s_wdfSet.insert(0xF151309F);// 788193189);
	s_wdfSet.insert(0x436592D8);
	s_wdfSet.insert(0x08E2D199);
	s_wdfSet.insert(0xC013B53B);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xC47885C6);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xB15C5678);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x1A2DEAB9);//1259967470);
	s_wdfSet.insert(0x8F43CE91);//0x51E340B6);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xDE3F48B7);
	s_wdfSet.insert(0xAC307575);//走
	s_wdfSet.insert(0x9DF6DEBC); //白天	
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x2EFADFA5);
	s_wdfSet.insert(0x73D983B7);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xE87F26E1);
	s_wdfSet.insert(0x08E2D199);
	s_wdfSet.insert(0xC013B53B);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xE3AEF018);
	s_wdfSet.insert(0x2FD95E30);
	s_wdfSet.insert(0x69823EE5);
	s_wdfSet.insert(0x0A8B7D87);
	s_wdfSet.insert(0x32F119A5);
	s_wdfSet.insert(0x4226BD41);
	s_wdfSet.insert(0x1D0C0B23);
	s_wdfSet.insert(0xFBEC073F);//0xCC7BC6C6);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xB05126E8);
	s_wdfSet.insert(0x26066130);
	s_wdfSet.insert(0x354CD2EB);
	s_wdfSet.insert(0xF792E03C);
	s_wdfSet.insert(0x146BB550);
	s_wdfSet.insert(0xA393A808);
	s_wdfSet.insert(0x907E024C);
	s_wdfSet.insert(0xCB50AB1D);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0x9ED74AA6);
	s_wdfSet.insert(0xF151309F);
	s_wdfSet.insert(0xDD1E6B63);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x2BD1DEF7);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xD6A27FFA);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x86785735);
	s_wdfSet.insert(0x541FA615);
	s_wdfSet.insert(0x420FF401);
	s_wdfSet.insert(0xE3AEF018);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0x536A7E15);
	s_wdfSet.insert(0x694F39D1);
	s_wdfSet.insert(0x694F39D1);
	s_wdfSet.insert(0xB05126E8);
	s_wdfSet.insert(0x26066130);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0xE3AEF018);
	s_wdfSet.insert(0xABB7D0DB);
	s_wdfSet.insert(0x361FA820);
	s_wdfSet.insert(0xC0A66903);
	s_wdfSet.insert(0xD1D11294);
	s_wdfSet.insert(0xAA7DEB05);
	s_wdfSet.insert(0x21274A87);
	s_wdfSet.insert(0x9C4978D);
	s_wdfSet.insert(0xC9E2F072);
	s_wdfSet.insert(0x2ACB36B2);
	s_wdfSet.insert(0xC26BF189);
	s_wdfSet.insert(0x1AA170AE);
	s_wdfSet.insert(0x7921D3A3);
	s_wdfSet.insert(0xEA7CAB84);
	s_wdfSet.insert(0x203CE1F7);
	s_wdfSet.insert(0x2178F38B);
	s_wdfSet.insert(0x008C2611);
	s_wdfSet.insert(0xAAD44583);
	s_wdfSet.insert(0xCE4D3C2D);
	s_wdfSet.insert(0x7B3C08E4);
	s_wdfSet.insert(0xBAF8009F);
	s_wdfSet.insert(0x2E8758EE);
	s_wdfSet.insert(0x354CD2EB);
	s_wdfSet.insert(0x146BB550);
	s_wdfSet.insert(0x516749F4);
	s_wdfSet.insert(0xC5C5FE46);//长寿
	s_wdfSet.insert(0x3D561594);//建邺
	s_wdfSet.insert(0xDB61AD29);//长安
	s_wdfSet.insert(0x6BD8F1C8);//AL
	s_wdfSet.insert(0x29622DDB);//西凉女国
	s_wdfSet.insert(0x491E6B4C);//宝象
	s_wdfSet.insert(0x549B2B83);//朱紫国
	s_wdfSet.insert(0xA393A808);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x9B1DB10D);
	s_wdfSet.insert(0x9B1DB10D);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x63CC8A23);
	s_wdfSet.insert(0x00D13BBF);
	s_wdfSet.insert(0x00D13BBF);//0x18C30C41);
	s_wdfSet.insert(0x323E2BCD);
	s_wdfSet.insert(0xA7CE2F61);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x6F88F494);
	s_wdfSet.insert(0x65C5B7EE);
	s_wdfSet.insert(0xF9858C95);
	s_wdfSet.insert(0x1B1DCE56);
	s_wdfSet.insert(0x43700E25);
	s_wdfSet.insert(0xF9ADC3DA);
	s_wdfSet.insert(0xA0120D38);
	s_wdfSet.insert(0x32BE710D);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0x8072710D);
	s_wdfSet.insert(0x0E43E0DF);
	s_wdfSet.insert(0xF5B8E062);
	s_wdfSet.insert(0xC540D7A7);
	s_wdfSet.insert(0x4B82870A);// 0x4B82870A; // 0x014FF746);// 0xEDCED445);// 0x436592D8);// 0xAB7B8559);
	s_wdfSet.insert(0x93E77F54);
	s_wdfSet.insert(0x0B19A5DC);
	s_wdfSet.insert(0x26E89B1F);
	s_wdfSet.insert(0xE9EC7A25);
	s_wdfSet.insert(0x11A18FBF);
	s_wdfSet.insert(0x13659C02);
	s_wdfSet.insert(0xA0B51368);
	s_wdfSet.insert(0xEDEEF9AF);
	s_wdfSet.insert(0xCCB7A7C3);
	s_wdfSet.insert(0x6B27F57F);
	s_wdfSet.insert(0x6BF13E64);
	s_wdfSet.insert(0xA9BC7D93);
	s_wdfSet.insert(0x71DF41E1);
	s_wdfSet.insert(0xE0C66A6F);
	s_wdfSet.insert(0x9C992236);
	s_wdfSet.insert(0xFF1D4A14);
	s_wdfSet.insert(0x6EA52AE1);
	s_wdfSet.insert(0x47FE6497);
	s_wdfSet.insert(0x6AB41A9A);
	s_wdfSet.insert(0x991B588D);
	s_wdfSet.insert(0xAD1DC28A);
	s_wdfSet.insert(0x150B5122);
	s_wdfSet.insert(0x301A4FE7);
	s_wdfSet.insert(0xEC9EBCA8);
	s_wdfSet.insert(0xBF78C1EF);
	s_wdfSet.insert(0x5B96A2DD);
	s_wdfSet.insert(0xCA26DE5D);
	s_wdfSet.insert(0xEA60ABA4);
	s_wdfSet.insert(0x0D906C8D);
	s_wdfSet.insert(0x63566DA9);
	s_wdfSet.insert(0x637B3C48);
	s_wdfSet.insert(0x6A154DDE);
	s_wdfSet.insert(0x689EB676);
	s_wdfSet.insert(0xE329AD6A);
	s_wdfSet.insert(0x048DA00D);
	s_wdfSet.insert(0xEA1F50E2);
	s_wdfSet.insert(0xCE11152D);
	s_wdfSet.insert(0xCC1742A6);
	s_wdfSet.insert(0x7FFAB47A);
	s_wdfSet.insert(0x0AF24A29);
	s_wdfSet.insert(0x5ABFF907);
	s_wdfSet.insert(0xF63C410E);
	s_wdfSet.insert(0xF8A67A7A);
	s_wdfSet.insert(0xF617F5A9);
	s_wdfSet.insert(0xCB50AB1D);
	s_wdfSet.insert(0x1A2DEAB9);
	s_wdfSet.insert(0x79D01E0E);
	s_wdfSet.insert(0xF9494E3A);
	s_wdfSet.insert(0x254E7029);
	s_wdfSet.insert(0x35A981D3);
	s_wdfSet.insert(0x2BD1DEF7);
	s_wdfSet.insert(0x10921CA7);
	s_wdfSet.insert(0x77D2082D);
	s_wdfSet.insert(0x3E912705);
	s_wdfSet.insert(0x808CEB72);
	s_wdfSet.insert(0xAFE0E635);
	s_wdfSet.insert(0xAFE0E635);
	s_wdfSet.insert(0x535C1994);
	s_wdfSet.insert(0x7F4CBC8C);
	s_wdfSet.insert(0x4ADFB0ED);
	s_wdfSet.insert(0xE2BC8127);
	s_wdfSet.insert(0x1EE9406C);
	s_wdfSet.insert(0x1D3FF13C);
	s_wdfSet.insert(0x4ADFB0ED);
	s_wdfSet.insert(0xE2BC8127);
	s_wdfSet.insert(0xA19EAB31);  //龙
	s_wdfSet.insert(0xF1F26922);  //电
	s_wdfSet.insert(0xD61E2519);  //背景
	s_wdfSet.insert(0x4DB67680);
	s_wdfSet.insert(0x49CBD108);
	s_wdfSet.insert(0xA19EAB31);  //龙 
	s_wdfSet.insert(0xD61E2519);  //背景
	s_wdfSet.insert(0xD61E2519);  //背景
	s_wdfSet.insert(0xF1F26922);  //电
	s_wdfSet.insert(0x4DB67680);
	s_wdfSet.insert(0x49CBD108);
	s_wdfSet.insert(0x5EC2D5BB);
	s_wdfSet.insert(0x9FE48849);
	s_wdfSet.insert(0x63605C8D);
	s_wdfSet.insert(0x5EC2D5BB);
	s_wdfSet.insert(0x63605C8D);
	s_wdfSet.insert(0x9FE48849);
	s_wdfSet.insert(0x63605C8D);
	s_wdfSet.insert(0x9FE48849);
	s_wdfSet.insert(0xD9463A0C);
	s_wdfSet.insert(0x2A2A0663);
	s_wdfSet.insert(0x62EDD1CB);
	s_wdfSet.insert(0x8B43833D);
	s_wdfSet.insert(0x5525C5FB);
	s_wdfSet.insert(0xF184BD59);
	s_wdfSet.insert(0x72AD6DBA);
	s_wdfSet.insert(0xDBCEE32C);
	s_wdfSet.insert(0x59D77EF9);
	s_wdfSet.insert(3635978625);// 0x1E1AF8D9;
	s_wdfSet.insert(0x98753F94);
	s_wdfSet.insert(0x2F78C46E);
	s_wdfSet.insert(0xC48ABA7B);
	s_wdfSet.insert(0x313BCC79);
	s_wdfSet.insert(0x719D767F);
	s_wdfSet.insert(0xF8EE853A);
	s_wdfSet.insert(0xD8857128);
	s_wdfSet.insert(0xEFE73EB9);
	s_wdfSet.insert(0x95FF4460);
	s_wdfSet.insert(0x4DDF5690);
	s_wdfSet.insert(0x21435203);
	s_wdfSet.insert(0x839CC29A);
	s_wdfSet.insert(0x5ECEBEDD);
	s_wdfSet.insert(0x5C0073EE);
	s_wdfSet.insert(0x62EDD1CB);
	s_wdfSet.insert(0x3646A4D9);
	s_wdfSet.insert(0x58628406);
	s_wdfSet.insert(0x20FCCE94);
	s_wdfSet.insert(0x85C9AF08);
	s_wdfSet.insert(0xBBEA83F4);
	s_wdfSet.insert(0x3D3FA597);
	s_wdfSet.insert(0xAF07277F);
	s_wdfSet.insert(0x8103AFD2);//0xC4AA8E18;
	s_wdfSet.insert(0x369C6A29);
	s_wdfSet.insert(0x8F3E73D5);
	s_wdfSet.insert(0x0B788E5A);
	s_wdfSet.insert(0x19182964);
	s_wdfSet.insert(0xDEDEE983);
	s_wdfSet.insert(0xAF07277F);// 0x5CC81980;
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x44BE65A3);
	s_wdfSet.insert(0x8F3E73D5);
	s_wdfSet.insert(0x78246FE4);
	s_wdfSet.insert(0xBE7DDF16);
	s_wdfSet.insert(0xDF4C3BE3);
	s_wdfSet.insert(0xACA4A54A);
	s_wdfSet.insert(0x6AD55205);
	s_wdfSet.insert(0x4C117B7C);
	s_wdfSet.insert(0xA3FD9577);
	s_wdfSet.insert(0x66BEBCBA);
	s_wdfSet.insert(0x718754A2);
	s_wdfSet.insert(0x6AD55205);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x3BA4B993);
	s_wdfSet.insert(0xDBFCCCBA);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x6B59951D);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x171544B2);
	s_wdfSet.insert(0xB1822745);
	s_wdfSet.insert(0x21FAE73F);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0x1D3FF13C);
	s_wdfSet.insert(0xB0B36693);
	s_wdfSet.insert(0xECD0E003);//必杀
	s_wdfSet.insert(0x3622636F);
	s_wdfSet.insert(0x86D66B9A);
	s_wdfSet.insert(0xF11233BB);
	s_wdfSet.insert(0x4FD9FFF3);
	s_wdfSet.insert(0x4D0A334C);
	s_wdfSet.insert(0xA4120EA9);
	s_wdfSet.insert(0xE3B87E0F);
	s_wdfSet.insert(0x1D3FF13C);
	s_wdfSet.insert(0xECD0E003);
	s_wdfSet.insert(0xB0212A04);
	s_wdfSet.insert(0xB0212A04);


	s_wdfSet.insert(406701913);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3296232902);
	s_wdfSet.insert(3277532867);  //4069888541
	s_wdfSet.insert(3144573054);//3443219224
	s_wdfSet.insert(2119033822);//0x216FE0F8
	s_wdfSet.insert(1807500026);//886189649    
	s_wdfSet.insert(250440769);//0xD5D51AD0  410697672
	s_wdfSet.insert(240383749);// 240383749 //0x78DDA320
	s_wdfSet.insert(2088395993);//0xD5DF5927
	s_wdfSet.insert(222208523);//0x3B9F2278
	s_wdfSet.insert(700775208);
	s_wdfSet.insert(149082521);
	s_wdfSet.insert(153189907);
	s_wdfSet.insert(993909921);
	s_wdfSet.insert(1044547630);
	s_wdfSet.insert(1560928702);
	s_wdfSet.insert(1227154258);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3351166789); //站
	s_wdfSet.insert(2574487372);  //黑天
	s_wdfSet.insert(3482058907);
	s_wdfSet.insert(2208066685);
	s_wdfSet.insert(361218670);
	s_wdfSet.insert(2791494731);
	s_wdfSet.insert(73900200);
	s_wdfSet.insert(2732776514);
	s_wdfSet.insert(4021614423);
	s_wdfSet.insert(717963597);
	s_wdfSet.insert(320881121);
	s_wdfSet.insert(781132167);
	s_wdfSet.insert(949865717);
	s_wdfSet.insert(2324308397);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(1338020705);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(42282575);
	s_wdfSet.insert(1762476724);
	s_wdfSet.insert(780622062);
	s_wdfSet.insert(2198359531);
	s_wdfSet.insert(1261107812);
	s_wdfSet.insert(76806695);
	s_wdfSet.insert(406701913);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3296232902);
	s_wdfSet.insert(3277532867);  //4069888541
	s_wdfSet.insert(3144573054);//3443219224
	s_wdfSet.insert(2119033822);//0x216FE0F8
	s_wdfSet.insert(1807500026);//886189649    
	s_wdfSet.insert(250440769);//0xD5D51AD0  410697672
	s_wdfSet.insert(240383749);// 240383749 //0x78DDA320
	s_wdfSet.insert(2088395993);//0xD5DF5927
	s_wdfSet.insert(222208523);//0x3B9F2278
	s_wdfSet.insert(700775208);
	s_wdfSet.insert(149082521);
	s_wdfSet.insert(153189907);
	s_wdfSet.insert(993909921);
	s_wdfSet.insert(1044547630);
	s_wdfSet.insert(1560928702);
	s_wdfSet.insert(1227154258);
	s_wdfSet.insert(1577923263);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3136727389);
	s_wdfSet.insert(3351166789); //站
	s_wdfSet.insert(2574487372);  //黑天
	s_wdfSet.insert(3482058907);
	s_wdfSet.insert(2208066685);
	s_wdfSet.insert(361218670);
	s_wdfSet.insert(2791494731);
	s_wdfSet.insert(73900200);
	s_wdfSet.insert(2732776514);
	s_wdfSet.insert(4021614423);
	s_wdfSet.insert(717963597);
	s_wdfSet.insert(320881121);
	s_wdfSet.insert(781132167);
	s_wdfSet.insert(949865717);
	s_wdfSet.insert(2324308397);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(1338020705);
	s_wdfSet.insert(3929029437);
	s_wdfSet.insert(42282575);
	s_wdfSet.insert(1762476724);
	s_wdfSet.insert(780622062);
	s_wdfSet.insert(2198359531);
	s_wdfSet.insert(1261107812);
	s_wdfSet.insert(76806695);
	s_wdfSet.insert(1084205009);
	s_wdfSet.insert(1030021222);
	s_wdfSet.insert(968268166);
	s_wdfSet.insert(3860707508);
	s_wdfSet.insert(3398426285);
	s_wdfSet.insert(3635978625);
	s_wdfSet.insert(3946646209);
	s_wdfSet.insert(3655438388);
	s_wdfSet.insert(1214058823);
	s_wdfSet.insert(2336457533);
	s_wdfSet.insert(2461182746);
	s_wdfSet.insert(916220457);
	s_wdfSet.insert(382287583);
	s_wdfSet.insert(3930943562);
	s_wdfSet.insert(3635978625);// 0x1E1AF8D9;
	s_wdfSet.insert(755485932);
	s_wdfSet.insert(35379719);
	s_wdfSet.insert(2673692967);
	s_wdfSet.insert(2194212682);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3705976162);
	s_wdfSet.insert(1382520422);
	s_wdfSet.insert(968268166);
	s_wdfSet.insert(3860707508);
	s_wdfSet.insert(3398426285);
	s_wdfSet.insert(3635978625);
	s_wdfSet.insert(3946646209);
	s_wdfSet.insert(3655438388);
	s_wdfSet.insert(1214058823);
	s_wdfSet.insert(2336457533);
	s_wdfSet.insert(2461182746);
	s_wdfSet.insert(916220457);
	s_wdfSet.insert(382287583);
	s_wdfSet.insert(3930943562);
	s_wdfSet.insert(3635978625);// 0x1E1AF8D9;
	s_wdfSet.insert(755485932);
	s_wdfSet.insert(35379719);
	s_wdfSet.insert(2673692967);
	s_wdfSet.insert(2194212682);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3416022732);
	s_wdfSet.insert(3705976162);
	s_wdfSet.insert(1382520422);
}

void ccm::saveWdf3()
{
	ofstream file("C:/Users/wolf/Desktop/wdfSet.txt");
	asert((bool)file, "写入wdf列表失败");
	file << s_wdfSet.size() << "\n";
	for (const auto &wdf : s_wdfSet)
	{
		file << wdf << "\n";
	}
	file.close();
	ccc_msgbox("写入wdfSet列表成功");
}


unsigned long ccm::getUid(unsigned long id)
{
	if (isClassical)
	{
		return id;
	}
	const auto &it = s_tables.find(id);
	if (it == s_tables.end())
	{
		return id;
	}
	return it->second;
}

void ccm::pushTable(unsigned long id, unsigned long idNew)
{
	s_tables.insert(make_pair(id, idNew));
}

int ccm::isIgnore(unsigned long id)
{
	if (isClassical)
	{
		return 0;
	}
	if (id == 647087968)
	{
		return 2;
	}
	const auto &it = s_ignores.find(id);
	return it != s_ignores.end();
}

void ccm::pushIgnore(unsigned long id)
{
	s_ignores.insert(make_pair(id, 1));
}

int ccm::getJinjie(int lv)
{
	int per进阶 = 45;
	if (lv < per进阶)
	{
		return 1;
	}
	if (lv < per进阶 * 2)
	{
		return 1 + (rand() % 100 < 20) + (rand() % 100 < 5);
	}
	return 1 + (rand() % 100 < 50) + (rand() % 100 < 20);
}


static set<unsigned long> s_Zuoqi;
static set<unsigned long> s_ZuoqiHead;
static set<unsigned long> s_Home;
static set<unsigned long> s_HomeHead;
static set<unsigned long> s_Item;
static set<unsigned long> s_ItemHead;
static set<unsigned long> s_Chat;
static set<unsigned long> s_Other;
static set<unsigned long> s_Npc;
static set<unsigned long> s_NpcHead;
static set<unsigned long> s_MpSkill;
static set<unsigned long> s_MpSkillHead;
static set<unsigned long> s_MpHead;
static set<unsigned long> s_BabySkill;
static set<unsigned long> s_BabySkillHead;
static set<unsigned long> s_SpecialSkill;
static set<unsigned long> s_SpecialSkillHead;
static set<unsigned long> s_FuzhuSkillHead;
static set<unsigned long> s_BabyHead;
static set<unsigned long> s_Baby;
static set<unsigned long> s_RoleHead;
static set<unsigned long> s_Role;
static set<unsigned long> s_RoleZuoqi;
static set<unsigned long> s_Weapon;
static set<unsigned long> s_WeaponHead;
void ccm::pushZuoqi(const string &desc, unsigned long id)
{
	s_Zuoqi.insert(id);
}

void ccm::pushZuoqiHead(const string &desc, unsigned long id)
{
	s_ZuoqiHead.insert(id);
}

void ccm::pushHome(const string &desc, unsigned long id)
{
	s_Home.insert(id);
}

void ccm::pushHomeHead(const string &desc, unsigned long id)
{
	s_HomeHead.insert(id);
}

void ccm::pushItem(const string &desc, unsigned long id)
{
	s_Item.insert(id);
}

void ccm::pushItemHead(const string &desc, unsigned long id)
{
	s_ItemHead.insert(id);
}

void ccm::pushChat(const string &desc, unsigned long id)
{
	s_Chat.insert(id);
}

void ccm::pushOther(const string &desc, unsigned long id)
{
	s_Other.insert(id);
}

void ccm::pushNpc(const string &desc, unsigned long id)
{
	s_Npc.insert(id);
}

void ccm::pushNpcHead(const string &desc, unsigned long id)
{
	s_NpcHead.insert(id);
}

void ccm::pushMpSkill(const string &desc, unsigned long id)
{
	s_MpSkill.insert(id);
}

void ccm::pushMpSkillHead(const string &desc, unsigned long id)
{
	s_MpSkillHead.insert(id);
}

void ccm::pushMpHead(const string &desc, unsigned long id)
{
	s_MpHead.insert(id);
}

void ccm::pushBabySkill(const string &desc, unsigned long id)
{
	s_BabySkill.insert(id);
}

void ccm::pushBabySkillHead(const string &desc, unsigned long id)
{
	s_BabySkillHead.insert(id);
}

void ccm::pushSpecialSkill(const string &desc, unsigned long id)
{
	s_SpecialSkill.insert(id);
}

void ccm::pushSpecialSkillHead(const string &desc, unsigned long id)
{
	s_SpecialSkillHead.insert(id);
}

void ccm::pushFuzhuSkillHead(const string &desc, unsigned long id)
{
	s_FuzhuSkillHead.insert(id);
}

void ccm::pushBabyHead(const string &desc, unsigned long id)
{
	s_BabyHead.insert(id);
}

void ccm::pushBaby(const string &desc, unsigned long id)
{
	s_Baby.insert(id);
}

void ccm::pushRoleHead(const string &desc, unsigned long id)
{
	s_RoleHead.insert(id);
}

void ccm::pushRole(const string &desc, unsigned long id)
{
	s_Role.insert(id);
}


void ccm::pushRoleZuoqi(const string &desc, unsigned long id)
{
	s_RoleZuoqi.insert(id);
}


void ccm::pushWeapon(const string &desc, unsigned long id)
{
	s_Weapon.insert(id);
}

void ccm::pushWeaponHead(const string &desc, unsigned long id)
{
	s_WeaponHead.insert(id);
}

void ccm::saveMyWdf()
{
	return;
	cWasFile wdf;
	ifstream *fileWdf = nullptr;
	ofstream fileOut;



	auto func = [&](const set<unsigned long> &sets, string folder)
	{
		if (!sets.size())
		{
			return;
		}
		system(toString("md C:\\Users\\wolf\\Desktop\\wdfpack\\%s\\", folder.c_str()).c_str());
		folder = "C:/Users/wolf/Desktop/wdfpack/" + folder + "/";
		int i = -1;
		for (const auto &e : sets)
		{
			if (e == 0)
			{
				continue;
			}
			bool b = wdf.GetFileP(e, fileWdf, [&](const uchar *data)
			{
				int size = 18;
				fileOut.open(folder + toString("%04d-%x-0.was", ++i, e),
					ios_base::binary);
				if (!fileOut)
				{
					fileOut.close();
					asert(false, "写入was失败");
					return;
				}
				fileOut.write((char*)data, size);
				fileOut.close();
			});
			asert(b, "写入文件遗漏");
		}
	};

	pushWdf3();
	for (const auto s : s_wdfSet)
	{
		s_Other.insert(s);
	}
	s_Other.insert(551);
	s_Other.insert(552);

	func(s_Zuoqi, "坐骑");
	func(s_ZuoqiHead, "坐骑图");
	func(s_Home, "家具");
	func(s_HomeHead, "家具图");
	func(s_Item, "道具");
	func(s_ItemHead, "道具图");
	func(s_Chat, "表情");
	func(s_Other, "其他");
	func(s_Npc, "NPC");
	func(s_NpcHead, "NPC图");
	func(s_MpSkill, "门派技能");
	func(s_MpSkillHead, "门派技能图");
	func(s_MpHead, "门派");
	func(s_BabySkill, "宝宝技能");
	func(s_BabySkillHead, "宝宝技能图");
	func(s_SpecialSkill, "特技");
	func(s_SpecialSkillHead, "特技图");
	func(s_FuzhuSkillHead, "辅助技能");
	func(s_BabyHead, "宝宝图");
	func(s_Baby, "宝宝");
	func(s_RoleHead, "角色图");
	func(s_Role, "角色");
	func(s_RoleZuoqi, "角色坐骑");
	func(s_Weapon, "武器");
	func(s_WeaponHead, "武器图");

	ccc_msgbox("", "写入was完毕");
}


// 染色
// 紫菜 14626 
// 敖白 006
// 虎子 355
// 怀念 024
// 篮子 626
// 冷涯 063
// 清风 004
// 杀破狼 520
// 神天兵 566
// 四季 010
// 小蛮 330
// 小胖牛 334
// 燕子 004
// 羽灵神 030

// This structure is used internally by the XSleep function 
struct XSleep_Structure
{
	int duration;
	HANDLE eventHandle;
};

//////////////////////////////////////////////////////////////////////
// Function  : XSleepThread()
// Purpose   : The thread which will sleep for the given duration
// Returns   : ulong WINAPI
// Parameters:       
//  1. pWaitTime -
//////////////////////////////////////////////////////////////////////
unsigned int WINAPI MySleep::thread(_In_ LPVOID pWaitTime)
{
	XSleep_Structure *sleep = (XSleep_Structure *)pWaitTime;

	Sleep(sleep->duration);
	SetEvent(sleep->eventHandle);

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Function  : XSleep()
// Purpose   : To make the application sleep for the specified time
//             duration.
//             Duration the entire time duration XSleep sleeps, it
//             keeps processing the message pump, to ensure that all
//             messages are posted and that the calling thread does
//             not appear to block all threads!
// Returns   : none
// Parameters:       
//  1. nWaitInMSecs - Duration to sleep specified in miliseconds.
//////////////////////////////////////////////////////////////////////
void MySleep::sleep(int nWaitInMSecs)
{
	XSleep_Structure sleep;

	sleep.duration = nWaitInMSecs;
	sleep.eventHandle = CreateEvent(NULL, true, false, NULL);

	ulong threadId;
	//	CreateThread(NULL, 0, &XSleepThread, &sleep, 0, &threadId);
	threadId = (ulong)_beginthreadex(NULL, 0, MySleep::thread, nullptr, CREATE_SUSPENDED, nullptr);
	MSG msg;

	while (::WaitForSingleObject(sleep.eventHandle, 0) == WAIT_TIMEOUT)
	{
		//get and dispatch messages
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	CloseHandle(sleep.eventHandle);
}

