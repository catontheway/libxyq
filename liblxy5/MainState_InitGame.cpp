#include "_global.h"
#include "_txt.h"


void CMainState::initGame()
{

	LockLv(159);
	if (0)
	{
		vector<int> skills =
		{
			ePS_高级反击, ePS_高级必杀, ePS_高级连击, ePS_吸血, ePS_高级偷袭, ePS_高级强力, ePS_高级夜战, ePS_嗜血追击,
			/*ePS_高级盾气*/ 78, 82, 100, 107, 109,
			ePS_感知/*, ePS_高级再生*/, ePS_高级冥思/*, ePS_高级幸运*/, ePS_高级神佑复生, ePS_高级法术抵抗/*, ePS_法术防御*/
		};

		LoadCharacterData(eJuSe虎头怪);
		LoadCharacterData(eJuSe逍遥生);
		LoadCharacterData(eJuSe剑侠客);
		LoadCharacterData(eJuSe龙太子);
		LoadCharacterData(eJuSe杀破狼);
		vector<int> mps = { eMP_无底洞, eMP_大唐官府, eMP_神木林, eMP_东海龙宫, eMP_魔王寨 };
		forr(m_Friend._friends, idx)
		{
			cObj* obj = m_FightWorkList[idx].m_pObj;
			cCharacter* cc = (cCharacter*)obj->m_pIndex;
			int mp = cct::getMenpai(eMP_随机);
			mp = mps[idx];
		//	cc->changeModel(getModelFromMp(mp));
			cPcData& pc = cc->m_PcData;
			pc.m_Lv = 159;
			pc.m_MengPaiID = mp;
			obj->SetTrueName(pc.m_Name = cc->GetData()->m_Name);
			obj->m_Name称谓.SetString(pc.m_Name);

			pc.setPointAfterLv(getAddpointFromMp(pc.m_MengPaiID, true), true);
			pc.autoData(true, true, false);
			pc.m_FuZhuSkillLvList[0] = pc.m_FuZhuSkillLvList[1] = pc.m_FuZhuSkillLvList[2] = pc.m_Lv;
			pc.m_Lv = 160;
			pc.autoEquip(false, true);
			pc.m_Lv = 159;
			pc.apply();
			pc.FillHpMp();

			pc.m_Money[0] += 1 << 24;
			//////////////////////////////////////////////////////////////////////////
			vector<int> spels = { 7, 9, 10, 13, 25, 48 };
			forr(spels, kk)
			{
				pc.m_Equips[kk].m_Property[12] = spels[kk];
			}
			//////////////////////////////////////////////////////////////////////////
			int m, k = 0;
			{
				cPet* pPet = new cPet;
				m = cct::getPetModel(pc.m_Lv - 50, pc.m_Lv);
				m = e狂豹人;
				mp = pc.m_Lv + cct::LvGapFromRoleAndBaby;
				mp = min(mp, cct::MaxBabyLv);
				g_pMainState->AutoPet(pPet, m, mp, true);
				pPet->m_PetData.m_ZiZhi.Set(1680, 1600, 2000, 6480, 1800, 1800, 129);
				pPet->m_PetData.SetJinJie(1);
				forv(skills, k)
				{
					pPet->m_PetData.AddSkill(skills[k], k);
				}

				auto& es = pPet->m_PetData.m_Equips;
				forr(es, k)
				{
					if (es[k].m_Property.size() > 15)
					{
						es[k].m_Property[15] = (rand() % 100 < 50) ? 2098/*5*/ : 2098;
					}
				}

				pc.AddPet(pPet);
			}
			SetFightPet(pc.m_IDinFightWorkList, rand() % pc.m_NumofBB);
		//	m_ZuoQi.GetZuoQi(pc, 79 + rand() % 10);
		}
		m_InterfaceTeam.update(false, m_Friend._friends.size());

		for (int i = 42; i <= 51; ++i)
		{
			if (0 == (g_GlobalValues[1] & (1 << (i - 42))))
			{
				g_GlobalValues[1] |= (1 << (i - 42));
			}
		}
//		m_Map.LoadMap(110, 190, "长寿村");
		m_Map.LoadMap(240, 260, "大唐国境");
	}
	//	for (auto i : { e地狱战神, e如意仙子, e净瓶女娲, e炎魔神, e鼠先锋 })
	//	for (auto i : { e阴阳伞, e锦毛貂精, e犀牛将军, e小魔头, e牛魔王 })
	//	for (auto i : { e镇元大仙, e李靖, e观音姐姐, e空度禅师, e超级泡泡 })
	//	for (auto i : { e镜妖, e泪妖, e琴仙, e金铙僧, e灵灯侍者})
	//  for (auto i : { e增长巡守, e雪人, e小白泽, e小象, e般若天女 })
	// 	for (auto i : { e剑灵, e龙马, e神猴, e神鸡, e土地 })
	else
	{
		LoadCharacterData(eJuSe剑侠客);
		LoadCharacterData(1 + rand() % 14);
		LoadCharacterData(eJuSe偃无师);
		LoadCharacterData(eJuSe桃夭夭);
		LoadCharacterData(eJuSe鬼潇潇);
		sAddPoint ap;
		ap.Set(0, 0, 0, 5, 0);
		sItem2 item;
		forr(m_Friend._friends, idx)
		{
			cObj* obj = m_FightWorkList[idx].m_pObj;
			cCharacter* cc = (cCharacter*)obj->m_pIndex;
			cPcData& pc = cc->m_PcData;
			//////////////////////////////////////////////////////////////////////////
			pc.m_Lv = 30;
			pc.autoEquip(false, true);
			item.Set(29, 2);
			g_pMainState->m_ItemManage.XiangQian(pc.m_Equips[0], item);
			item.Set(29, 0);
			g_pMainState->m_ItemManage.XiangQian(pc.m_Equips[4], item);
			//////////////////////////////////////////////////////////////////////////
			pc.m_Lv = 5;
			pc.m_MengPaiID = -1;
			pc.PointRemain = cct::PointRemian;
			pc.setPointAfterLv(ap, false);
			pc.apply();
			pc.FillHpMp();

			cPet* pPet = new cPet;
			int model = cct::getPetModel(0, 5, false);
			pPet->SetData(m_PetDataManager.GetPetData(model));
			cPetData& pp = pPet->m_PetData;

			pp.Load(model, true, true);
			pp.m_Lv = pc.m_Lv + cct::LvGapFromRoleAndBaby;
			pp.m_Lv = max(pp.m_Lv, pPet->GetData()->m_LvTake + cct::LvGapFromRoleAndBaby);
			pp.PointRemain = cct::PointRemian;
			pp.setPointAfterLv(g_pMainState->getAddpointFromPet(&pp, true), true);
			pp.autoEquip(false, false);
			pp.apply();
			pp.SetJinJie(1);
			pp.FillHpMp();
			pc.AddPet(pPet);
			SetFightPet(idx, rand() % pc.m_NumofBB);

			if (idx > 0)
			{
				m_Friend._friends[idx].ctrl = false;
			}
		}

		auto& money = g_pCharacter->m_PcData.m_Money[0];
		auto& exp = g_pCharacter->m_PcData.m_EXP;
		for (int n = 5; n > 0; --n)
		{
			// 50级技能和辅助技能
			for (int k = c_NumFuZhu; k >= 0; --k)
			{
				for (int i = 50; i > 0; --i)
				{
					money += GetMainSkillMoney(i);
					continue;
					exp += GetMainSkillExp(i);
				}
			}

			// 修
			for (int k = 8; k > 0; --k)
			{
				for (int i = 2; i > 0; --i)
				{
					money += GetXiuLIanExp(i) * 2000;
				}
			}

			// 等级
			for (int i = g_pCharacter->m_PcData.m_Lv + 1; i <= 40; ++i)
			{
				break;
				exp += GetCharacterExp(i);
			}
		}

		// 送钱
		money += 0xFFFFF;

		m_InterfaceTeam.update(false, 1);
		m_Map.LoadMap(20, 74, "桃源村");
		g_pHeroObj->say("#R雷黑子#R有困难,去#R建邺城#R看看吧", 0xFFF);
	}

	m_PCHead.UpDateHead();
}