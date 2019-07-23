#include "_global.h"

static bool is单击连击(int skill)
{
	switch (skill)
	{
	case 0: //横扫千军
	case 1010: // 后发
	case 1050: //满天
	case 97:  //烟雨剑法
	case 141://象形
	case 143:// 狮搏
	case 148://连环击
	case 167://裂石
	case 168:
	case 169:

	case 2092://惊心一剑
	case 2094://死亡召唤
	case 1095: //力劈
	case 2098://善恶有报
	case 2099://壁垒击破

	case 3034://破血
	case 3035://弱点
	case 3040://破碎
		return true;
	}
	return false;
}

static bool is分击(int skill)
{
	switch (skill)
	{
	case 1017:// 破釜第二段
	case 71:  // 天雷斩
	case 98:  // 缥缈式
	case 142: // 鹰击
	case 170: // 浪涌
	case 1171:
	case 1172:

	case 2110:// 剑荡四方
		return true;
	}
	return false;
}

static void cbCounter(int UserID)
{
	auto& ss = g_pMainState->m_FightWorkList[UserID].m_SkillSelectForCounter;
	if (ss.SkillID >= 0)
	{
		g_pMainState->m_FightWorkList[UserID].m_SkillSelect = ss;
		ss.SkillID = -1;
	}
};


bool cSkillManager::Use(sFightSkillSelect SkillSelect, int UserID, bool isPut /* = false */)
{
	int& stage = m_pFightState->m_pFightWorkList[UserID]->GetWork()->stage;
	if (stage == 0)
	{
		auto& list = g_pMainState->m_FightWorkList[UserID];
		auto& ski = list.m_SkillSelect;
		int& sid = ski.SkillID;
		int& tid = ski.TargetID;

		bool isfj = false;
		if (g_pMainState->m_FightWorkList[UserID].m_pObj->getPropertyData()->m_FightData.chaos混乱反间)
		{
			isfj = true;
			int autoSelect = g_pMainState->m_AI.find追击反间月光(UserID, 3, true);
			if (autoSelect >= 0)
			{
				list.GetWork()->type = list.m_WorkType = WORKTYPE_ATTACK;
				list.targetID = autoSelect;
				sid = 1000;
				tid = autoSelect;
				SkillSelect = ski;

				list.m_MaxTargetNum = 1;
				list.targetlist[0] = tid;
			}
			else
			{
				g_pMainState->m_AI.defense(UserID);
			}
		}

		int numMax = 1;
		if (!isfj && (sid <= 1000 || sid >= 2000))
		{
			//	int uold = g_pMainState->m_AI.m_UserID;
			g_pMainState->m_AI.SetUser(UserID);
			auto ts = sid == 3048 ?  g_pMainState->m_AI.findOwners(UserID, cAI::eFindType::Relifeable) : g_pMainState->m_AI.findTarget(sid);
			if (ts.empty())
			{
				g_pMainState->m_FightWorkList[UserID].m_work.clear();
				return true;
			}
			if (tid >= 0 && g_pMainState->m_FightWorkList[tid].isExist && g_pMainState->m_AI.See(UserID, tid) && 
				(!g_pMainState->m_FightWorkList[tid].CheckDie() || g_pMainState->m_AI.isSkillResurgence(sid)))
			{
				if (std::find(ts.begin(), ts.end(), tid) == ts.end())
				{
					ts.insert(ts.begin(), tid);
				}
				else
				{
					for (int i = ts.size() - 1; i >= 1; --i)
					{
						if (ts[i] == tid)
						{
							swap(ts[i], ts[0]);
							break;
						}
					}
				}
			}
			auto& list = g_pMainState->m_FightWorkList[UserID];

			if (sid != 1000)
			{
				numMax = g_pMainState->m_SkillManager.GetSkill(sid)->m_TargetNum;
				if (sid == 1017)
				{
					numMax = g_pMainState->m_SkillManager.GetSkill(7)->m_TargetNum;
				}
				else if (sid == 1171)
				{
					numMax = g_pMainState->m_SkillManager.GetSkill(171)->m_TargetNum;
				}
				else if (sid == 1172)
				{
					numMax = g_pMainState->m_SkillManager.GetSkill(172)->m_TargetNum;
				}
			}
			list.m_MaxTargetNum = ts.size();
			if (is单击连击(sid))
			{
				list.m_MaxTargetNum = numMax;
				for (int i = 0; i < list.m_MaxTargetNum; ++i)
				{
					list.targetlist[i] = ts[0];
				}
			}
			else
			{
				list.m_MaxTargetNum = min(list.m_MaxTargetNum, numMax);
				for (int i = 0; i < list.m_MaxTargetNum; ++i)
				{
					list.targetlist[i] = ts[i];
				}
			}

			tid = list.targetlist[0];
			SkillSelect = ski;
		}
	}


	int  Skilllv = SkillSelect.SkillLv;
	int  TargetID = SkillSelect.TargetID;
	int sSkillID = SkillSelect.SkillID;
	

	if (stage == 0x10086 || stage == 0x10087)
	{
		auto& ss = m_pFightState->m_pFightWorkList[UserID]->m_SkillSelect;
		ss.SkillID = 1000;
		return Use1000平砍(Skilllv, 1000, UserID, TargetID);
	}


	if (0 == stage)
	{
		if (m_pFightState->m_pFightWorkList[UserID]->m_pObj->m_NowPos == POS_FIGHT_STAND)
		{
			cPropertyData* petdata;
			cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
			pUser->AutoFightDirection(UserID);
			pUser->GetPropertyData(petdata);
			pUser->SetStatic(false);//有可能刚才在被打,处于静止状态时轮到它了

// 			if (petdata->m_FightData.chaos混乱反间)
// 			{
// 				int autoSelect = g_pMainState->m_AI.find追击反间月光(FightListID, 3, true);
// 				if (-1 != autoSelect)
// 				{
// 					// 狼
// 					m_pFightState->m_pFightWorkList[FightListID]->m_work.clear();
// 					//
// 					m_pFightState->m_pFightWorkList[FightListID]->m_WorkType = WORKTYPE_ATTACK;
// 					m_pFightState->m_pFightWorkList[FightListID]->m_SkillSelect.SkillLv = 0;
// 					m_pFightState->m_pFightWorkList[FightListID]->m_SkillSelect.SkillID = 1000;
// 					m_pFightState->m_pFightWorkList[FightListID]->targetID = autoSelect;
// 					m_pFightState->m_pFightWorkList[FightListID]->m_SkillSelect.TargetID = autoSelect;
// 				}
// 			}

			g_pMainState->m_FightWorkList[UserID].targetID = SkillSelect.TargetID;
			g_pMainState->m_FightWorkList[UserID].m_NowTargetID = SkillSelect.TargetID;
			bool bSeal = false;
			if (petdata->m_FightData.cannotAll)
			{
				bSeal = true;
			}
			else
			{
				if (sSkillID < 3000)//3000以上是特技不属于法术
				{
					if (sSkillID < 2000 && sSkillID>1000)
					{

					}
					else
					{
						if (1000 == sSkillID)
						{
							if (petdata->m_FightData.cannotAttack)
							{
								bSeal = true;
							}
						}
						else if (petdata->m_FightData.cannotMagic || pUser->CheckHaveState(199))
						{
							bSeal = true;
						}
					}
				}
				else if (petdata->m_FightData.cannotSpesialSkill)
				{
						bSeal = true;
				}
			}
			if (!isPut && bSeal)
			{
//				if (UserID == g_pMainState->m_HeroID || UserID == g_pMainState->m_HeroID + 5)
// 				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(UserID))
// 				{
// 					g_pMainState->m_Channel.AddNewString("行动不能");
// 				}
				if (sSkillID >= 3000)
				{
//					m_pFightState->m_MiaoShu.SetString("特技不能");
					pUser->saySkill("特技不能");
					
				}
				else if (sSkillID == 1000)
				{
//					m_pFightState->m_MiaoShu.SetString("攻击不能");
					pUser->saySkill("攻击不能");
				}
				else
				{
//					m_pFightState->m_MiaoShu.SetString("法术不能");
					pUser->saySkill("法术不能");
				}
// 				m_pFightState->m_MiaoShu.SetTime(120);
// 				m_pFightState->m_MiaoShu.UpdateXCenter();
				g_pMainState->m_FightWorkList[UserID].m_work.clear();
				return true;
			}
//			int hpout;
//			if (!isPut && !Cost(hpout, Skilllv, sSkillID, UserID, 1, false))
			if (!Cost(UserID, sSkillID, 1, false))
			{
//				if (UserID==g_pMainState->m_HeroID)
// 				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(UserID))
// 				{
// 					g_pMainState->m_Channel.AddNewString("消耗不足");
// 				}

				if (sSkillID >= 3000)
				{
//					m_pFightState->m_MiaoShu.SetString("特技不足");
					pUser->saySkill("愤怒不足");

				}
				else
				{
//					m_pFightState->m_MiaoShu.SetString("法术不足");
					pUser->saySkill("施法不足");
				}
// 				m_pFightState->m_MiaoShu.SetTime(120);
// 				m_pFightState->m_MiaoShu.UpdateXCenter();
				m_pFightState->m_pFightWorkList[UserID]->m_work.pop_back();
				return true;
			}
			bool m_bmiaoshushow = true;
			string actionname;
			sSkill* pskill = g_pMainState->m_SkillManager.GetSkill(m_pFightState->m_pFightWorkList[UserID]->m_SkillSelect.SkillID);
			if (pskill)
			{
				actionname = pskill->m_Name;
			}
			else
			{
				switch (m_pFightState->m_pFightWorkList[UserID]->m_SkillSelect.SkillID)
				{
				case 1003:
				case 1007:
				{
//					switch (m_pFightState->m_pFightWorkList[UserID]->m_ItemSelectID)
//					{
// 					case eAIUseItemTypeHP:
// 					case eAIUseItemTypeHPALL:
// 						actionname = "药品加血";
// 						break;
// 					case eAIUseItemTypeMP:
// 					case eAIUseItemTypeMPALL:
// 						actionname = "药品加蓝";
// 						break;
// 					case eAIUseItemTypeHPHurt:
// 						actionname = "药品疗伤";
// 						break;
// 					case eAIUseItemTypelive:
// 						actionname = "药品复活";
// 						break;
// 					case eAIUseItemTypeUnseal:
// 						actionname = "药品解封";
// 						break;
// 					case eAIUseItemTypeCP:
// 						actionname = "药品愤怒";
// 						break;
// 					default:
// 						actionname = "药品";
// 						if (GetItem(UserID))
// 						{
// 							actionname = GetItem(UserID)->GetName();
// 						}
// 						break;
// 					}
// 					if (UserID == g_pMainState->m_HeroID || UserID == g_pMainState->m_HeroID + 5)
// 					{
// 						actionname = "药品";
// 					}

					actionname = "药品";
					if (GetItem(UserID))
					{
						actionname = GetItem(UserID)->GetName();
					}
				}
					break;
				case 1004:actionname = "召唤"; break;
				case 1005:actionname = "暗器"; break;
				default:m_bmiaoshushow = false; break;
				}
			}
			if (m_bmiaoshushow)
			{
// 				ostringstream oss;
// 				oss << m_pFightState->m_pFightWorkList[UserID]->m_pObj->m_TrueName.GetString();
// 				oss << ": ";
// 				oss << actionname;
// 				m_pFightState->m_MiaoShu.SetString(oss.str());
// 				m_pFightState->m_MiaoShu.SetTime(120);
// 				m_pFightState->m_MiaoShu.UpdateXCenter();

				pUser->saySkill(actionname);
			}


			//存在检测
			int truetarget = TargetID; // m_pFightState->CheckTarget(UserID, TargetID, sSkillID);
			m_pFightState->m_pFightWorkList[UserID]->m_NowTargetID = truetarget;
			m_pFightState->m_pFightWorkList[UserID]->targetID = truetarget;
			if (truetarget == -1)
			{
				m_pFightState->m_pFightWorkList[UserID]->m_work.pop_back();
				return true;
			}
			if (truetarget == UserID)
			{
				cObj* pUser = m_pFightState->m_pFightWorkList[UserID]->m_pObj;
				cPropertyData* pUserData;
				pUser->GetPropertyData(pUserData);
				if (pUserData->m_FightData.chaos混乱反间)
				{
					if (sSkillID == 1000)
					{
						m_pFightState->m_pFightWorkList[UserID]->m_work.pop_back();
						return true;
					}
				}
			}
// 			if (truetarget != TargetID)
// 			{
// 				m_pFightState->m_pFightWorkList[UserID]->m_SkillSelect.TargetID = truetarget;
// 				TargetID = truetarget;
// 			}
		}

	}

	if (is单击连击(sSkillID) || is分击(sSkillID))
	{
		return Use71法术驱动物理(Skilllv, sSkillID, UserID, TargetID);
	}
	else if ((sSkillID == 107 || sSkillID == 2087) && (m_pFightState->_turn % 2) == 0)
	{
		return Use107巨岩破泰山天罗地网(Skilllv, sSkillID, UserID, TargetID);
	}
	switch (sSkillID)
	{
	case 1:
		return Use1后发(Skilllv, sSkillID, UserID, TargetID);

// 		/*if (Use50(Skilllv, sSkillID, UserID, TargetID))
// 		return true;
// 		return false;*/
// 	case 1050:  //满天花雨
// 	case 1095://力劈
// 	case 0: //横扫千军
// 	case 1010:
// 	case 1017://破釜第二段
// 	case 71:  //天雷斩
// 	case 97://烟雨剑法
// 	case 98:
// 	case 141://象形
// 	case 142:// 鹰击
// 	case 143:// 狮搏
// 	case 148://连环击
// 	case 2092://惊心一剑
// 	case 2094://死亡召唤
// 	case 2096://剑荡四方
// 	case 2098://善恶有报
// 	case 2099://壁垒击破
// 	case 2100://苍鸾怒击
// 		//	case 2102:
// 	case 3034://破血
// 	case 3035://弱点
// 	case 3040://破碎
// 	case 3042://破血2
// 	case 3043://弱点EX
// 	case 3044://破血EX
// 		if (Use71法术驱动物理(Skilllv, sSkillID, UserID, TargetID))
// 			return true;
// 		return false;
// 	case 80://龙卷雨击
// 	case 131:// 飞砂走石
// 		if (Use80龙卷飞沙(Skilllv, sSkillID, UserID, TargetID))
// 			return true;
// 		return false;
//	case 84:	return Use84龙吟(Skilllv, sSkillID, UserID, TargetID);//龙呤


	case 135:
	case 136:
	{
		int tid = -1;
		int start = UserID / 10 * 10;
		int end = start + 5;
		int t;
		for (int i = start; i < end; ++i)
		{
			t = g_pMainState->m_InterfaceTeam.GetTeamTurn(i);
			if (!g_pMainState->m_FightWorkList[t].isExist)
			{
				tid = t;
				break;
			}
		}
		if (tid < 0)
		{
			ccc_msgbox("召唤无敌牛妖/牛虱 出错");
		}
		auto& ski = g_pMainState->m_FightWorkList[UserID].m_SkillSelect;
		TargetID = ski.TargetID = tid;
		return Use1004召唤(Skilllv, sSkillID, UserID, TargetID);
	}
	case 1000:	return  Use1000平砍(Skilllv, sSkillID, UserID, TargetID);
	case 1003: return Use1003物品(Skilllv, sSkillID, UserID, TargetID);
	case 1004:
	{
		TargetID = SkillSelect.TargetID = UserID + 5;
		return Use1004召唤(Skilllv, sSkillID, UserID, SkillSelect.TargetID);
	}
	case 61: return Use61暗器(Skilllv, sSkillID, UserID, TargetID);
	case 1005:	return Use1005暗器(Skilllv, sSkillID, UserID, TargetID);
	case 1006:  return Use1006(Skilllv, sSkillID, UserID, TargetID);
	case 2105:  return  Use2105(Skilllv, sSkillID, UserID, TargetID);
	default:
	{
		if (sSkillID == 1007)
		{
			g_pMainState->m_FightWorkList[UserID].m_MaxTargetNum = 1;
			g_pMainState->m_FightWorkList[UserID].targetlist[0] = TargetID;
		}
		if (Use默认技能(Skilllv, sSkillID, UserID, TargetID))
			return true;
	}
		return false;
	}
}



bool cSkillManager::Use1000平砍(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = &g_pMainState->m_FightWorkList[UserID];
	sFightWork* pTargetList = nullptr;
	if (TargetID >= 0)
	{
		pTargetList = &g_pMainState->m_FightWorkList[TargetID];
	}
	
	cObj* pUser = pUserList->m_pObj;
	cPropertyData* pUserData;
	pUser->GetPropertyData(pUserData);
	pUserList->targetID = TargetID;
	cObj* pTarget = pTargetList->m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	
	auto setSkillSelect = [&](int t)
	{
		sFightSkillSelect select;
		select.SkillLv = pUserData->m_Lv;  //pUserList->m_pObj->GetSkillLv(pUserData->EndMagic) + pUserData->m_XiuLian.GetMag();
		select.SkillID = pUserData->EndMagic;
		if (g_pMainState->m_AI.isSkillSeal(pUserData->EndMagic))
		{
			select.SkillLv = pUserData->m_Lv - 25;
			if (select.SkillLv < 5)
			{
				select.SkillLv = 5;
			}
		}
		select.TargetID = t;
		return select;
	};

	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:
		if (1)
		{
			const sFightPoint* pOffse = pUserList->GetFightPoint();
			if (pOffse->m_xOff > 0)
				stage = 22;
// 			else if (pUser->m_IndexType == INDEXTYEP_PET && pUserData->modeid == ePetID::蜈蚣)
// 			{
// 				stage = 120;
// 			}
			else
			{
				stage = 21;
			}
		}
		return true;
	case 22:
		if (m_pFightState->Approach(UserID, TargetID))
			stage = 21;
		return true;
	case 21:
		if (1)
		{
			if (pUserList->_combo)
			{
				pTargetData->m_FightData.m_bHit = true;
			}
			else
			{
				//检测命中
				CheckHit(pUserData, pTargetData);
				// 从天而降
				if (pTargetData->m_FightData.m_bHit &&
					pUserData->isHadPetSkill(2104) &&
					rand() % 100 < 5)
				{
					pTargetData->m_FightData.m_bHit = false;
				}
			}

//			if (pUserData->m_FightData.AttackNum > 0)
//			{
// 				pUserData->NightLv = pTargetData->m_FightData.m_bHit;
// 				pUserData->AbnormalResist = false;
// 				if (pTargetData->ShiXueAdd >= 0xffffff)
// 				{
// 					pTargetData->ShiXueAdd -= 0xffffff;
// 				}
// 			}
// 			else if (pUserData->NightLv)
// 			{
// 				pUserData->NightLv = pTargetData->m_FightData.m_bHit;
// 			}
			pUser->Set(POS_FIGHT_STAND);
			if (pTargetData->m_FightData.m_bHit)
			{
				bool is大块 = pUserData->isHadPetSkill(2109);
				if (is大块)
				{
					pUserData->CriRate.d1 += 10;
				}

				CountParry(pUserData, pTargetData);//防御
				CountCri(pUserData, pTargetData);//必杀

				if (is大块)
				{
					pUserData->CriRate.d1 -= 10;
				}

				auto& gs = pTargetData->m_FightData.m_guardID;
				forr(gs, i)
				{
					auto& list = g_pMainState->m_FightWorkList[gs[i]];
					if (!list.isExist || list.CheckDie())
					{
						gs.erase(gs.begin() + i);
					}
				}
				//如果有人保护,等待保护者就位
				if (gs.size())
				{
					pTarget->m_MagicWav.LoadWav(0x4ADFB0ED);
					stage = 101;
					return true;
				}
			}
			stage = 20;
		}
		return true;
	case 20:
		StageWaitSleep(4, UserID, 120);
		return true;
	case 120:
	{
		int pos;
		if (rand() % 100 < 50)
			pos = POS_ATTACK2;
		else
			pos = POS_ATTACK;
		pUser->Set(pos);
		pUser->SetSound(pos);
		stage = 1;
	}
	case 1:
	{
		int atkp = m_pFightState->WorkAttack(UserID);
		switch (atkp)
		{
		case 0:
			return true;
		default:
		{
			//是不是弓箭
			const sFightPoint* pOffse = pUserList->GetFightPoint();
			if (pOffse->m_xOff == 0 && !(
				(pUser->m_IndexType == INDEXTYEP_PET && pUserData->modeid == ePetID::蜈蚣) |
				(pUser->m_IndexType == INDEXTYEP_CHARACTER && ((cPcData*)pUserData)->m_CardPetID == ePetID::蜈蚣)
				))
			{
				m_pFightState->m_HiddenWeapons.Load(0xE2BC8127);
				m_pFightState->m_HiddenWeaponsUseNum = 1;
				m_pFightState->m_HiddenWeaponsp[0].m_NeedShow = true;
				m_pFightState->m_HiddenWeaponsp[0].m_x = pUser->GetX();
				m_pFightState->m_HiddenWeaponsp[0].m_y = pUser->GetY() + 20;
				m_pFightState->m_HiddenWeaponsTargetID[0] = TargetID;
				stage = 23;
				return true;
			}
			if (!PhysicalAtkHitStage(UserID, TargetID, sSkillID))
			{

				stage = 3;
				return true;
			}
			if (atkp != 1)
			{
				stage += 1;
				return true;
			}
		}
			break;
		}
	}
		return true;
	case 23://弓箭

	{
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		if (m_pFightState->HiddenWeaponsMove(0, 50))
		{
			if (!PhysicalAtkHitStage(UserID, TargetID, sSkillID))
			{
				stage = 3;
				return true;
			}
			stage = 2;
		}
	}
		return true;
	case 2:  //攻击判定
	{
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		stage = 3;
		int dam = 0;
		int dup = 0;
		// 从天而降
		if (pUserData->isHadPetSkill(2104))
		{
//			if (pUserData->ShiXueAdd >= 0xffffff)
			if (pUserList->_zhuiji == 5)
			{
				dup -= 45;
			}
			else
			{
				dup += 10;
			}
		}
		else
		{
//			if (pUserData->ShiXueAdd >= 0xffffff)
			if (pUserList->_zhuiji == 5)
			{
				dup -= 50;
			}
		}

		CountphysicalDamage(dam, UserID, TargetID, dup);
		// 千钧一怒
		if (pUserData->isHadPetSkill(2107))
		{
			if (dam > pTargetData->HPMax.GetData() / 10)
			{
				if (UserID % 10 >= 5)
				{
					sFightWork* u = &g_pMainState->m_FightWorkList[UserID - 5];
					if (u->isExist && u->m_pObj)
					{
						AddCp(UserID - 5, 10);
					}
				}
			}
		}
		if (pUserData->Spurting.d1)
		{
			int jianshetarget;
			for (int i = 0; i < 2; i++)
			{
				if (g_pMainState->m_FightWorkList[TargetID].CheckDie())
					jianshetarget = g_pMainState->m_AI.find溅射暗器(UserID, TargetID, i, true/* + 2*/);
				else
					jianshetarget = g_pMainState->m_AI.find溅射暗器(UserID, TargetID, i + 1, true/* + 2*/);
				if (jianshetarget>-1 && dam > 0)
				{
					cPropertyData* jianshepet;
					g_pMainState->m_FightWorkList[jianshetarget].m_pObj->GetPropertyData(jianshepet);
					int rate = pUserData->Spurting.d1 - jianshepet->Spurting.d2;
					if (rate > 0)
					{
						int   dam2 = (dam*rate) / 100;
						AddHp(jianshetarget, -dam2);
						SetDamage(dam2, jianshetarget);
						if (1 > jianshepet->m_HP)//被溅射死
						{
							if (UserID < 10)
								g_pMainState->m_FightWorkList[jianshetarget].m_sufferDirection = 7;
							else g_pMainState->m_FightWorkList[jianshetarget].m_sufferDirection = 3;
							g_pMainState->m_pFightState->SetDie(jianshetarget);
							pTargetData->m_CP /= 2;
					//		 return true;
						}
					}
				}
			}
		}	
	}
		return true;
	case 3:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			//pUser->SetStatic(false);
			g_pMainState->m_FightWorkList[TargetID].SetMagiSufferID(0, 1, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID]);
			bool die = g_pMainState->m_FightWorkList[TargetID].CheckDie();

			pUserList->_endmagic = -1;
			if (!die && pUserData->EndMagic >= 0 && !pUserData->m_FightData.chaos混乱反间 && rand() % 100 < 20)
			{
				pUserList->_endmagic = pUserData->EndMagic;
			}

			bool isCombo = false;
			if (pUserList->_combo)
			{
				isCombo = true;
				pUserList->_combo = 0;
			}
			else if (!die && pUserList->_zhuiji != 5 && pUserList->_nuji != 5)
			{
				bool is大块 = pUserData->isHadPetSkill(2109);
				if (is大块)
				{
					pUserData->ComboRate.d1 += 10;
				}
				pUserList->_combo = CoutCombo连击(pUserData, pTargetData);
				if (is大块)
				{
					pUserData->ComboRate.d1 -= 10;
				}
				
			}

			if (pUserList->_nuji == 5)
			{
				if (!isCombo)
				{
					pUserList->_nuji = 0;
				}
			}
			if ((pUserData->m_FightData.m_bCri/* || pUserList->_combo*/) && pUserList->_nuji > 0 && pUserList->_nuji < 5)
			{
				++pUserList->_nuji;
			}

			if (pUserList->_zhuiji == 5)
			{
				pUserList->_zhuiji = 0;
			}

			if (die)
			{
				if (pUserList->_nuji > 1)
				{
					int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
					if (tid >= 0)
					{
						pUserList->_nuji = 5;
						pUserList->m_SkillSelect.TargetID = tid;
						stage = 22;
						ccc_log("死亡触发怒击");
						return true;
					}
				}
				else if (pUserList->_zhuiji == 1)
				{
					int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
					if (tid >= 0)
					{
						pUserList->_zhuiji = 5;
						pUserList->m_SkillSelect.TargetID = tid;
						stage = 22;
						ccc_log("触发追击");
						return true;
					}
				}
				stage = 5;
				return true;
			}
			stage = 4;
		}
		return true;
	case 4:
		if (pTargetData)
		{
			//是否反击
			int rat = pTargetData->CounterRate.d1 - pUserData->CounterRate.d2;
			if ((rand() % 100) < rat)
			{
				pUserList->_combo = 0;
				pUser->Set(POS_FIGHT_STAND);
				stage = 14;
			}
			else
			{
				stage = 7;
			}
		}
		else 
			stage = 7;
		return true;
	case 14:
	{
		//先等待硬直结束
		if (g_pMainState->m_FightWorkList[TargetID].m_work.size())
			return true;
		stage = 6;
		//反击
		pUser->Set(POS_FIGHT_STAND);
		pTarget->SetStatic(false);
		m_pFightState->SetCounter(TargetID, UserID);
	}
		return true;
	case 5:
	{
		bool isReturn = m_pFightState->ReturnApproach(UserID);
		// 如果角色已经返回原味
		if (isReturn)
		{
			// work完成，清掉
			pUserList->m_work.pop_back();
			// 追加法术
			if (0) // 触发条件 比如TargetID没死/几率什么的
			{
				// 添加work
				pUserList->SetWork(WORKTYPE_MAGIC);
			//	pUserList->m_WorkType = -1;
				pUserList->m_SkillSelect = setSkillSelect(TargetID); // 设置好技能选择的 目标, 编号, 等级
				// 使用技能
				return Use(pUserList->m_SkillSelect, UserID, true);
			}
		} 
		return true;
	}
	case 6://等待对手反击完
	{
//		return StageWaitFightBack(UserID, TargetID, 7);
		if (pTargetList->m_work.empty())
		{
			pUserList->GetWork()->stage = 7;
		}
		return true;
	}

	case 7://是否连击
	{
		// 5 返回
		// 21 原地
		// 22 靠近
		if (!pTargetData->m_FightData.m_bHit)
		{
			stage = 5;
			pUserList->_endmagic = -1;
			return true;
		}
		bool combo = pUserList->_combo == 1;
		if (combo && pUserList->_nuji > 0 && pUserList->_nuji < 5)
		{
			++pUserList->_nuji;
// 			if (pUserList->_nuji > 1)
// 			{
// 				pUserList->_nuji = 5;
// 			}
		}

		bool isNj = pUserList->_nuji == 5;
		bool isZj = pUserList->_zhuiji == 5;
		int mag = pUserList->_endmagic;

		if (mag >= 0)
		{
			if (!combo)
			{
				stage = 10086;
			}
			else
			{
				stage = 10010;
			}
		}
		else
		{
			if (combo)
			{
				stage = 21;
			}
			else if (pUserList->_nuji > 1)
			{
				int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
				if (tid >= 0)
				{
					pUserList->_nuji = 5;
					pUserList->m_SkillSelect.TargetID = tid;
// 					pTargetList = &g_pMainState->m_FightWorkList[TargetID];
// 					pTarget = pTargetList->m_pObj;
// 					pTarget->GetPropertyData(pTargetData);
					ccc_log("触发怒击");
					stage = 22;
				}
				else
				{
					stage = 5;
				}
			}
			else
			{
				stage = 5;
			}
		}
	}
		return true;
	case 10010: // 触发的法术后继续攻击
	{
		if (m_pFightState->ReturnApproach(UserID))
		{
			ccc_log("触发法术,有后续");
//			pUserList->m_work.pop_back();
			pUserList->GetWork()->stage = 0x10086;
			pUserList->SetWork(WORKTYPE_MAGIC);
		//	pUserList->m_WorkType = -1;
			pUserList->_endmagic = -1;
			pUserList->m_SkillSelect = setSkillSelect(TargetID);
			return Use(pUserList->m_SkillSelect, UserID, true);
		}
	}
		return true;
	case 0x10086: // 继续攻击
	{
		if (!pTargetList || !pTargetList->isExist)
		{
			pUserList->m_work.pop_back();
			return true;
		}

		if (pUserList->_combo && !pTargetList->CheckDie())
		{
			stage = 22;
			return true;
		}
		int nid = -1;
		if (pUserList->_nuji > 1)
		{
			int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
			if (tid >= 0)
			{
				nid = tid;
			}
		}
		int zid = -1;
		if (pTargetList->CheckDie())
		{
			if (pUserList->_zhuiji == 1)
			{
				int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
				if (tid >= 0)
				{
					zid = tid;
				}
			}
		}
		if (zid < 0 && nid < 0)
		{
			pUserList->m_work.pop_back();
			return true;
		}

		if (nid >= 0)
		{
			pUserList->_nuji = 5;
			pUserList->m_SkillSelect.TargetID = nid;
			ccc_log("触发法术后, 优先怒击");
		}
		else if (zid >= 0)
		{
			pUserList->_zhuiji = 5;
			pUserList->m_SkillSelect.TargetID = zid;
			ccc_log("触发法术后, 死亡追击");
		}

//		Q_LOG("触发法术后继续攻击");
		// 靠近
		stage = 22;
	}
		return true;
	case 0x10087:
	{
		if (!pTargetList || !pTargetList->isExist)
		{
			pUserList->m_work.pop_back();
			return true;
		}
		int nid = -1;
		if (pUserList->_nuji > 1)
		{
			int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
			if (tid >= 0)
			{
				nid = tid;
			}
		}
		int zid = -1;
		if (pTargetList->CheckDie())
		{
			if (pUserList->_zhuiji == 1)
			{
				int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
				if (tid >= 0)
				{
					zid = tid;
				}
			}
		}

		if (nid >= 0)
		{
			pUserList->_nuji = 5;
			pUserList->m_SkillSelect.TargetID = nid;
			stage = 22;
			ccc_log("触发法术后, 死亡优先怒击");
		}
		else if (zid >= 0)
		{
			pUserList->_zhuiji = 5;
			pUserList->m_SkillSelect.TargetID = zid;
			stage = 22;
			ccc_log("触发法术后, 死亡追击");
		}
		else
		{
			pUserList->m_work.pop_back();
		}
		return true;

		//////////////////////////////////////////////////////////////////////////
		bool iszj = false;
		if (pTargetList && pTargetList->isExist && pTargetList->CheckDie())
		{
			if (pUserList->_zhuiji == 1)
			{
				int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
				if (tid >= 0)
				{
					pUserList->_zhuiji = 5;
					pUserList->m_SkillSelect.TargetID = tid;
				}
			}
		}
		if (!iszj)
		{
			pUserList->m_work.pop_back();
			return true;
		}

		ccc_log("触发法术后追击");
		stage = 22;
	}
		return true;
	case 10086: // 最后一次攻击触发的法术 
	{
		if (m_pFightState->ReturnApproach(UserID))
		{
			ccc_log("最后一次攻击触发法术");
			pUserList->GetWork()->stage = 0x10087;
			pUserList->m_SkillSelect = setSkillSelect(TargetID);
			pUserList->SetWork(WORKTYPE_MAGIC);
		//	pUserList->m_WorkType = -1;
			pUserList->_endmagic = -1;
			return Use(pUserList->m_SkillSelect, UserID, true);
		}
	}
		return true;
	case 101: //等待保护者就位
		return StageWaitProtect(UserID, TargetID, 120);
	}
	return false;
}



bool cSkillManager::Use默认技能(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = &g_pMainState->m_FightWorkList[UserID];
	sFightWork* pTargetList = &g_pMainState->m_FightWorkList[TargetID];
	cObj* pUser = pUserList->m_pObj;
	cPropertyData* pUserData;
	cPropertyData* pTargetData;
	pUser->GetPropertyData(pUserData);
	cObj* pTarget = pTargetList->m_pObj;
	pTarget->GetPropertyData(pTargetData);
	int& stage = pUserList->GetWork()->stage;
	static ulong s_magic2102;

	switch (stage)
	{
	case 0:
	{
//		int hpout = 0;
//		Cost(hpout, Skilllv, sSkillID, UserID, 1, true);
// 		if (hpout)
// 		{
// 			SetDamage(hpout, UserID);
// 		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
	}
		return true;
	case 1:
		if (WaitForMagicPoint(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->SetStatic(false);
			pUser->SetMagicSound(sSkillID);//声音

			ulong MagicID;
			int MagicPos;
			bool MagicUporDown;
			bool  toAll;
			bool bAtk = GetSkill需要目标被打动画(sSkillID);
			int maxnum;
			GetMagicAndNum秒几(Skilllv, sSkillID, UserID, TargetID, MagicID, maxnum, MagicPos, MagicUporDown, toAll);
 			int magicspeed = GetSpeed(MagicID/*sSkillID*/);

			if (sSkillID == 2102)
			{
				// 灵葫
				int r = rand() % 100;
				if (r < 13)
				{
					maxnum = 1;
				}
				else if (r < 33)
				{
					maxnum = 2;
				}
				else if (r < 67)
				{
					maxnum = 3;
				}
				else if (r < 87)
				{
					maxnum = 4;
				}
				else
				{
					maxnum = 5;
				}
				if (maxnum == 2 || maxnum == 3)
				{
					MagicID = 0x75331968;
					toAll = true;
				}
				else if (maxnum == 4 || maxnum == 5)
				{
					MagicID = 0xF99822CE;
					toAll = true;
				}
				s_magic2102 = MagicID;
				if (maxnum < pUserList->m_MaxTargetNum)
				{
					pUserList->m_MaxTargetNum = maxnum;
				}
			}

//			pUserList->m_MaxTargetNum = 0;
			if (toAll)
			{
				// QQ截图
				int x = 0, y = 0;
				if (TargetID < 10)
				{
					x = 553;
					y = 412;
				}
				else
				{
					x = 290;
					y = 230;
				}
				if (MagicID == 0x4DB67680)
				{
					// 飞沙
					x -= 120;
					y -= 140;
				}
				else if (MagicID == 0xDED2253F)
				{
					// 地狱烈火
					x += 120;
					y -= 135;
				}

				while (!m_pFightState->m_ThreadSleep)
				{
					Sleep(1);  //等待线程
				}

				m_pFightState->m_FullSkill.SetMagicUp(0, MagicID, x, y);
				m_pFightState->m_FullSkill.m_FullSkilUP[0].SetFrame(0);
				m_pFightState->m_FullSkill.m_FullSkilUP[0].m_NeedShow = true;
				m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_x = x;
				m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_y = y;

				m_pFightState->m_IDtoLoad[0] = MagicID;
				m_pFightState->m_pFileToLoad[0] = &m_pFightState->m_FullSkill.m_FullSkilUP[0];
				ResumeThread(m_pFightState->m_hThread);
			}

// 			auto func = [&](bool isCheckDie, cAI::eEnemyType type, int stateid)
// 			{
// 				vector<POINT> tList;
// 				g_pMainState->m_AI.finds(isCheckDie, false, tList, type, TargetID, stateid);
// 				if (tList.empty())tList.push_back({ TargetID, 0 });
// 				if (tList.size() < maxnum)maxnum = tList.size();
// 				int i = 0;
// 				for (; i < maxnum; ++i)
// 				{
// 					if (tList[i].x == TargetID)break;
// 				}
// 				if (i == maxnum)tList[maxnum - 1].x = TargetID;
// 				for (int i = 0; i < maxnum; ++i)
// 				{
// 					pUserList->targetlist[i] = tList[i].x;
// 				}
// 				pUserList->m_MaxTargetNum = maxnum;
// 			};
// 
// 			// 检测隐身
// 			auto func2 = [&](bool isCheckDie, cAI::eEnemyType type, int stateid)
// 			{
// 				vector<POINT> tList;
// 				g_pMainState->m_AI.finds(isCheckDie, false, tList, type, TargetID, stateid);
// 				auto list2 = g_pMainState->m_AI.check隐身(tList, UserID);
// 				if (!list2.size())list2.push_back(TargetID);
// 				if (list2.size() < maxnum)maxnum = list2.size();
// 				int i = 0;
// 				for (; i < maxnum; ++i)
// 				{
// 					if (list2[i] == TargetID)break;
// 				}
// 				if (i == maxnum)list2[maxnum - 1] = TargetID;
// 				for (int i = 0; i < maxnum; ++i)
// 				{
// 					pUserList->targetlist[i] = list2[i];
// 				}
// 				pUserList->m_MaxTargetNum = maxnum;
// 			};
// 
// 
// 			if (maxnum < 2)
// 			{
// 				pUserList->targetlist[0] = TargetID;
// 				pUserList->m_MaxTargetNum = 1;
// 			}
// 			else
// 			{
// 				switch (sSkillID)
// 				{
// 				case 27: // 碎甲
// 				{
// 					func2(true, cAI::eET封印对象, 27);
// 					break;
// 				}
// 				case 33: // 金刚护法
// 				case 176:// 碎星
// 				case 177:// 镇魂
// 					func(true, cAI::eET上金刚33, 33);
// 					break;
// // 				case 38:
// // 				case 39:
// 				case 40: // 推
// 				case 41: // 妙手
// 				case 42: // 救死扶伤
// //				case 45:
// //			    case 94:
// 				case 189: // 金莲
// // 				case 3007: // 四海
// // 				case 3013: // 晶清
// 				{
// 					func(true, cAI::eET血最少, -1);
// 					int i = 1;
// 					for (; i < pUserList->m_MaxTargetNum; ++i)
// 					{
// 						if (pUserList->targetlist[i] == TargetID)
// 						{
// 							break;
// 						}
// 					}
// 					if (i != pUserList->m_MaxTargetNum)
// 					{
// 						swap(pUserList->targetlist[i], pUserList->targetlist[0]);
// 					}
// 				}
// // 				{
// // 					vector<POINT> tList;
// // 					g_pMainState->m_AI.find相关类型的己方(false,false,tList, cAttackAI::eET血最少, UserID);
// // 					if (tList.size() < maxnum)maxnum = tList.size();
// // 					int i = 0;
// // 					for (; i < maxnum; i++)
// // 					{
// // 						if (tList[i].x == TargetID)break;
// // 					}						
// // 					if (i == maxnum)tList[maxnum - 1].x = TargetID;
// // 					for (i = 0; i < maxnum; i++)
// // 					{
// // 						pUserList->targetlist[i] = tList[i].x;
// // 					}
// // 					pUserList->m_MaxTargetNum = maxnum;
// // 				}
// 
// 					break;
// 				case 91: // 灯
// 				case 102:
// 					func(true, cAI::eET血最少, sSkillID);
// 					// 			{
// 					// 				vector<POINT> tList;
// 					// 				g_pMainState->m_AI.find相关类型的己方(false, false, tList, cAttackAI::eET血最少, UserID, 102);
// 					// 				if (!tList.size())tList.push_back({ TargetID, 0 });
// 					// 				if (tList.size() < maxnum)maxnum = tList.size();
// 					// 				int i = 0;
// 					// 				for (; i < maxnum; i++)
// 					// 				{
// 					// 					if (tList[i].x == TargetID)break;
// 					// 				}
// 					// 				if (i == maxnum)tList[maxnum - 1].x = TargetID;
// 					// 				for (i = 0; i < maxnum; i++)
// 					// 				{
// 					// 					pUserList->targetlist[i] = tList[i].x;
// 					// 				}
// 					// 				pUserList->m_MaxTargetNum = maxnum;
// 					// 			}
// 					break;
// 				case 112: // 灵动九天
// 				case 204: // 蜜润
// 					func(true, cAI::eET上灵动112, 112);
// 					// 				{
// 					// 					vector<POINT> tList;
// 					// 					g_pMainState->m_AI.find相关类型的己方(false, false, tList, cAttackAI::eET上灵动112, UserID, 112);
// 					// 					if (!tList.size())tList.push_back({ TargetID, 0 });
// 					// 					if (tList.size() < maxnum)maxnum = tList.size();
// 					// 					int i = 0;
// 					// 					for (; i < maxnum; i++)
// 					// 					{
// 					// 						if (tList[i].x == TargetID)break;
// 					// 					}
// 					// 					for (int i = 0; i < maxnum; i++)
// 					// 					{
// 					// 						pUserList->targetlist[i] = tList[i].x;
// 					// 					}
// 					// 					pUserList->m_MaxTargetNum = maxnum;
// 					// 				}
// 					break;
// 				case 120: // 鬼眼
// 					func(true, cAI::eET鬼眼120, -1);
// 					// 			{
// 					// 				int num = 1;
// 					// 				int star = UserID >= 10 ? 10 : 0;
// 					// 				for (int i = star; i < star + 10; ++i)
// 					// 				{
// 					// 					if (i == TargetID)continue;
// 					// 					if (!g_pMainState->m_FightList[i].isExist)
// 					// 					{
// 					// 						continue;
// 					// 					}
// 					// 					cPetData *data = nullptr;
// 					// 					g_pMainState->m_FightList[i].m_pData->GetDateP(data);
// 					// 					if (!data)
// 					// 					{
// 					// 						continue;
// 					// 					}
// 					// 					if (data->PeopleSpecial.d1 >= 100)
// 					// 					{
// 					// 						continue;
// 					// 					}
// 					// 					pUserList->targetlist[num] = i;
// 					// 					if (++num == maxnum)
// 					// 					{
// 					// 						break;
// 					// 					}
// 					// 				}
// 					// 				pUserList->targetlist[0] = TargetID;
// 					// 				pUserList->m_MaxTargetNum = num;
// 					// 			}
// 					break;
// // 				case 126://黄泉
// // 					func2(true, cAttackAI::eET黄泉之息126, 126);
// // 					break;
// // 				case 127://魂飞魄散
// // 					func2(true, cAttackAI::eET魂飞魄散127, -1);
// // 					break;
// // 				case 37: // 我佛慈悲
// // 				case 104: // 杨柳
// // 				case 125: // 还阳
// // 				case 3008: // 回魂咒
// // 				case 3009: // 起死回生
// // 					pUserList->m_MaxTargetNum = 0;
// // 					for (int i = 0; i < maxnum; i++)
// // 					{
// // 						pUserList->targetlist[pUserList->m_MaxTargetNum] = g_pMainState->m_AI.Get战斗Id附近的Id(UserID, TargetID, i, 2);
// // 
// // 						if (bAtk)
// // 						{
// // 							if (UserID == pUserList->targetlist[pUserList->m_MaxTargetNum])
// // 							{//防止对象攻击自己
// // 								continue;
// // 							}
// // 						}
// // 						if (-1 == pUserList->targetlist[pUserList->m_MaxTargetNum])
// // 						{
// // 							break;
// // 						}
// // 						pUserList->m_MaxTargetNum += 1;
// // 					}
// // 					break;
// 				case 3048: // 慈航
// 				{
// 					int num = 0;
// 					int star = UserID >= 10 ? 10 : 0;
// 					for (int i = star; i < star + 10; ++i)
// 					{
// //					    if (i == TargetID)continue;
// 						if (!g_pMainState->m_FightWorkList[i].isExist)
// 						{
// 							continue;
// 						}
// 						if (g_pMainState->m_FightWorkList[i].m_pObj->m_IndexType != INDEXTYEP_CHARACTER)
// 						{
// 							continue;
// 						}
// 						if (!g_pMainState->m_FightWorkList[i].CheckDie())
// 						{
// 							continue;
// 						}
// 						cPropertyData *data = nullptr;
// 						g_pMainState->m_FightWorkList[i].m_pObj->GetPropertyData(data);
// 						if (!data)
// 						{
// 							continue;
// 						}
// 						if (!pUserData->Hide.d2 && data->Hide.d1)
// 						{
// 							continue;
// 						}
// 						pUserList->targetlist[num] = i;
// 						if (++num == maxnum)
// 						{
// 							// break;
// 						}
// 					}
// //				    pUserList->targetlist[0] = TargetID;
// 					pUserList->m_MaxTargetNum = num;
// 					int d = pUserData->m_HP - pUserData->HPMax.GetData() / 10;
// 					if (d > 0)
// 					{
// 						AddHp(UserID, -d);
// 						SetDamage(d, UserID);
// 					}
// 					d = pUserData->m_HP2 - pUserData->HPMax.GetData() / 10;
// 					if (d > 0)
// 					{
// 						AddHpHurt(UserID, -d);
// 					}
// 					pUserData->m_MP = 0;
// 				}
// 					break;
// 				default:
// 					for (int i = 0; i < maxnum; i++)
// 					{
// 						pUserList->targetlist[pUserList->m_MaxTargetNum] = g_pMainState->m_AI.find溅射暗器(UserID, TargetID, i, 3);
// 						// GetTargetID(UserID, TargetID, i);
// 
// 						if (bAtk)
// 						{
// 							if (UserID == pUserList->targetlist[pUserList->m_MaxTargetNum])
// 							{
// 								//防止对象攻击自己
// 								continue;
// 							}
// 						}
// 
// 						if (-1 == pUserList->targetlist[pUserList->m_MaxTargetNum])
// 						{
// 							break;
// 						}
// 						pUserList->m_MaxTargetNum += 1;
// 					}
// 					break;
// 				}
// 			}
			if (sSkillID != 7)
			{
				Cost(UserID, sSkillID, pUserList->m_MaxTargetNum, true);
			}
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)
				{
//					m_pFightState->SetMagicSuffer(pUserList->m_NowTargetID, pUser->GetDirection());
					g_pMainState->m_FightWorkList[pUserList->m_NowTargetID].m_sufferDirection = pUser->GetDirection();
				}

				if (toAll)
				{
					while (!m_pFightState->m_ThreadSleep)
					{
						Sleep(1);  //等待线程
					}
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_bSufferFullSkill = true;
					m_pFightState->m_FullSkill.m_FullSkilUP[0].SetDirection((sSkillID == 2102 && TargetID < 10));
					m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_FrameGap = magicspeed;
				}
				else
				{
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_bSufferFullSkill = false;
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->SetMagiSufferID(MagicID, MagicPos, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID], MagicUporDown);
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.m_FrameGap = magicspeed;
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.m_direction = (sSkillID == 2102 && TargetID < 10);
				}
			}
			stage += 1;
		}
		return true;
	case 2:
	{
		bool isOk = m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic;// || (pUser->m_NowPos == POS_FIGHT_STAND);
		if (isOk)
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
//			stage += 1;
		}



		ulong MagicID;
		bool toAll = isAni画面型(sSkillID);
		int LateTime; //伤害计算延时
//		bool bAtk = GetSkill需要目标被打动画(sSkillID);
		GetDelayAnd(sSkillID, LateTime, MagicID);
		cct::setDelta(MagicID, LateTime);
		if (sSkillID == 2102)
		{
			MagicID = s_magic2102;
			toAll = (MagicID != GetSkill(sSkillID)->m_MagicID);
		}
		bool bover = false;
		if (toAll)
		{
// 			if (!pTarget->m_MagicSuffer.m_NeedShow)
// 			{
// 				bover = true;
// 			}
// 			else
			{
				while (!m_pFightState->m_ThreadSleep)
				{
					Sleep(1);  //等待线程
				}
				int maxf = m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame();
				LateTime += max((maxf - LateTime) / 2, 3);
				if (LateTime >/*=*/ maxf)
				{
					LateTime = maxf/* - 1*/;
				}
				if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() == maxf - max(1, LateTime))
				{
					bover = true;
				}
			}
		}
		else
		{
			if (!pTarget->m_MagicSuffer.m_NeedShow)
			{
				bover = true;
			}
			else
			{
				int maxf = pTarget->m_MagicSuffer.m_pFile->GetMaxFrame();
				LateTime += max((maxf - LateTime) / 2, 3);

				if (LateTime >/*=*/ maxf)
				{
					LateTime = maxf/* - 1*/;
				}
				if (pTarget->m_MagicSuffer.GetFrame() == maxf - LateTime)
				{
					bover = true;
				}
			}
		}

		if (bover)
		{
			bool bAtk = GetSkill需要目标被打动画(sSkillID);
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)
				{
					m_pFightState->SetMagicSuffer(pUserList->m_NowTargetID, g_pMainState->m_FightWorkList[pUserList->m_NowTargetID].m_sufferDirection);
				}
			}
			stage = 3;
		}
	}
//		return true;
	case 3:  //附加BUFF
	{
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic/* || (pUser->m_NowPos == POS_FIGHT_STAND)*/)
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
		}
		ulong MagicID;
		bool toAll = isAni画面型(sSkillID);
		int LateTime; //伤害计算延时
		bool bAtk = GetSkill需要目标被打动画(sSkillID);
		GetDelayAnd(sSkillID, LateTime, MagicID);
		cct::setDelta(MagicID, LateTime);

		if (sSkillID == 2102)
		{
			MagicID = s_magic2102;
			toAll = (MagicID != GetSkill(sSkillID)->m_MagicID);
		}

		bool bover = false;
		if (toAll)
		{
// 			if (!pTarget->m_MagicSuffer.m_NeedShow)
// 			{
// 				bover = true;
// 			}
// 			else
			{
				while (!m_pFightState->m_ThreadSleep)
				{
					Sleep(1);  //等待线程
				}
				int maxf = m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame();
				if (LateTime >/*=*/ maxf)
				{
					LateTime = maxf/* - 1*/;
				}
				if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() == maxf - LateTime)
				{
					bover = true;
				}
			}
		}
		else
		{
			if (!pTarget->m_MagicSuffer.m_NeedShow)
			{
				bover = true;
			}
			else
			{
				if (LateTime >= pTarget->m_MagicSuffer.m_pFile->GetMaxFrame())
				{
					LateTime = pTarget->m_MagicSuffer.m_pFile->GetMaxFrame() - 1;
				}
				if (pTarget->m_MagicSuffer.GetFrame() == pTarget->m_MagicSuffer.m_pFile->GetMaxFrame() - LateTime)
				{
					bover = true;
				}
			}
		}
		if (bover)
		{
			stage = 4;
			pUserList->m_NowTargetIdx = -1;
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->m_NowTargetID = pUserList->targetlist[i];
				if (bAtk)
				{
					m_pFightState->SwitchMagicSuffer(pUserList->m_NowTargetID);
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->SetSound(POS_SUFFER);//声音
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_NowBeAtkowner = UserID;

				}

				if ((rand() % 100) < CheckMagicHit(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID/*TargetID*/))
				{
					EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);
					if (g_pMainState->m_FightWorkList[pUserList->m_NowTargetID]._magicCri)
					{
						g_pMainState->m_FightWorkList[pUserList->m_NowTargetID]._magicCri = 0;
						g_pMainState->m_FightWorkList[pUserList->m_NowTargetID].m_pObj->SetMagicCri(&m_pFightState->_magicCri);
					}
				}
			}
			cPropertyData* pPet;
			pUser->GetPropertyData(pPet);
			if (1 > pPet->m_HP)
			{
				if (UserID < 10)
					pUserList->m_sufferDirection = 3;
				else pUserList->m_sufferDirection = 7;
				g_pMainState->m_pFightState->SetDie(UserID);
				pTargetData->m_CP /= 2;
				return true;
			}
		}
	}
		return true;
	case 4://等待主角动作完成
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			// 龙魂
			if (pUserData->isHadPetSkill(2108))
			{
				int& lh = m_pFightState->m_pFightWorkList[UserID]->_longhun;
				if (++lh == 3)
				{
					lh = 0;
					pUserData->DmgPercentOfMagic.d1 += 1;
				}
			}
			switch (sSkillID)
			{
			case 7: // 破釜沉舟
				pUserList->m_SkillSelect.SkillID = 1017;
				stage = 0;
				return true;

			case 50: // 漫天花雨
				pUserList->m_SkillSelect.SkillID = 1050;
				stage = 0;
				return true;
			case 171: // 惊涛怒
				pUserList->m_SkillSelect.SkillID = 1171;
				stage = 0;
				return true;
			case 172: // 翻江搅海
				pUserList->m_SkillSelect.SkillID = 1172;
				stage = 0;
				return true;
			case 2095: // 力劈华山
				pUserList->m_SkillSelect.SkillID = 1095;
				stage = 0;
				return true;
			}
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
			stage = 5;
		}
		return true;
	case 5:StageWaitSleep(10, UserID, 6); break;
	case 6:
	{
		pUser->SetMagicSound(-1);//声音
		pUserList->m_work.pop_back();

		if (g_pMainState->m_FightWorkList[TargetID].isExist && (!g_pMainState->m_FightWorkList[TargetID].CheckDie()))
		{
			CoutComboMagic(sSkillID, pUserData, UserID, pTargetData);
		}
		else
		{
			cbCounter(UserID);
		}
	}
		break;
	}
	return true;
}



bool cSkillManager::Use71法术驱动物理(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	cPropertyData* pUserData;
	cPropertyData* pTargetData;
	pUserList->m_pObj->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);
	int& stage = pUserList->GetWork()->stage;

	switch (stage)
	{
	case 0: // 目标列表
	{
		if (is单击连击(sSkillID))
		{
			if (TargetID == UserID)
			{
				pUserList->m_work.clear();
				return true;
			}
			pUserList->m_MaxTargetNum += pUserData->TargetNumAdd;
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				pUserList->targetlist[i] = TargetID;
			}
		}
		else if (is分击(sSkillID))
		{
			int maxnum = pUserList->m_MaxTargetNum;
			pUserList->m_MaxTargetNum = 0;
			for (int i = 0; i < maxnum; i++)
			{
//				pUserList->targetlist[pUserList->m_MaxTargetNum] = GetTargetID(UserID, TargetID, i);
				int id = pUserList->targetlist[pUserList->m_MaxTargetNum];
				if (id == UserID)continue;
				if (-1 == id)break;
				pUserList->m_MaxTargetNum += 1;
			}
		}

// 		switch (sSkillID)
// 		{
// 		case 1050:  //满天花雨
// 		case 1095://力劈
// 		case 0://横扫千军
// 		case 97://烟雨剑法
// 		case 141://象形
// 		case 143:// 狮搏
// 		case 148://连环击
// 		case 1010://后发
// 		case 2092://惊心一剑
// 		case 2094://死亡召唤
// 		case 2098://善恶有报
// 		case 2099://壁垒击破
// 		case 2100://苍鸾怒击
// 		case 3034://破血
// 		case 3035://弱点
// 		case 3040://破碎
// 		case 3042://破血2
// 		case 3043://弱点EX
// 		case 3044://破血EX
// 		{
// 			switch (sSkillID)
// 			{
// 			case 0:pUserList->m_MaxTargetNum = 4; break;  //横扫千军
// 			case 97:pUserList->m_MaxTargetNum = 2; break;//烟雨剑法
// 			case 148:
// 
// 			{
// 				if (Skilllv < 30)pUserList->m_MaxTargetNum = 1;
// 				else
// 					if (Skilllv < 50)pUserList->m_MaxTargetNum = 2;
// 					else
// 						if (Skilllv < 70)pUserList->m_MaxTargetNum = 3;
// 						else
// 							if (Skilllv < 105)pUserList->m_MaxTargetNum = 4;
// 							else
// 								if (Skilllv < 140)pUserList->m_MaxTargetNum = 5;
// 								else
// 									pUserList->m_MaxTargetNum = 6;
// 			}
// 				break;
// 			case 3034:pUserList->m_MaxTargetNum = 2; break;//破血
// 			case 1050:  //满天花雨
// 			case 1095://力劈
// 			case 1010://后发
// 			case 2092://惊心一剑
// 			case 2094://死亡召唤
// 			case 2098://善恶有报
// 			case 2099://壁垒击破
// 			case 2100://苍鸾怒击
// 			case 3040://破碎
// 			case 3043://弱点EX
// 			case 3035:
// 				pUserList->m_MaxTargetNum = 1; break;//弱点	
// 			case 3042:pUserList->m_MaxTargetNum = 3; break;//破血2
// 			case 3044:pUserList->m_MaxTargetNum = 4; break;//破血EX
// 			default:pUserList->m_MaxTargetNum = 1;
// 				break;
// 			}
// 			if (TargetID == UserID)
// 			{
// 				pUserList->m_work.clear();
// 				return true;
// 			}
// 			pUserList->m_MaxTargetNum += pUserData->TargetNumAdd;
// 			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
// 			{
// 				pUserList->targetlist[i] = TargetID;
// 			}
// 		}
// 			break;
// 		case 1017://破釜
// 		case 142://鹰击
// 		case 71://天雷斩
// 		case 98: // 缥缈式
// 		case 2096:
// 			//		case 2102:
// 		{
// 			int maxnum = 0;
// 			switch (sSkillID)
// 			{
// 			case 1017:
// 			case 2096:
// 				maxnum = 3;
// 				break;
// 				//			case 2102:
// 				//				maxnum = 2;
// 			case 142://鹰击
// 
// 			{
// 				maxnum = Skilllv / 30 + 1;
// 				if (maxnum > 6)maxnum = 6;
// 			}
// 				break;
// 			case 71://天雷斩
// 			case 98:
// 			{
// 				// 				if (g_pMainState->m_AI.m_bPKMode || TargetID < 10)
// 				// 				{
// 				// 					maxnum = 1;
// 				// 				}
// 				// 				else
// 				{
// 					if (Skilllv > 59)maxnum = 3;
// 					else 	if (Skilllv > 29)maxnum = 2;
// 					else  	maxnum = 1;
// 				}
// 			}
// 				break;
// 			}
// 			maxnum += pUserData->TargetNumAdd;
// 			pUserList->m_MaxTargetNum = 0;
// 			for (int i = 0; i < maxnum; i++)
// 			{
// 				pUserList->targetlist[pUserList->m_MaxTargetNum] = GetTargetID(UserID, TargetID, i);
// 				int id = pUserList->targetlist[pUserList->m_MaxTargetNum];
// 				if (id == UserID)continue;
// 				if (-1 == id)break;
// 				pUserList->m_MaxTargetNum += 1;
// 			}
// 
// 		}
// 			break;
// 		default:
// 			ERRBOX;
// 			break;
// 		}

	}
		pUserList->m_NowTargetIdx = -1;
		if (!pUserList->NextTarget(m_pFightState, sSkillID)) // 找不到目标，弹出
			stage = 7;
		else
			stage = 1;
		return true;
	case 1:
		if (pUserList->m_NowTargetIdx != -1)
		{

			if (pUserList->m_NowTargetIdx == 0)
			{
				// 分体
				// 连击第一次响
				pUserList->targetID = pUserList->targetlist[pUserList->m_NowTargetIdx];
				pUserList->m_pObj->SetMagicSound(sSkillID);
			}
			else
			{
				if (pUserList->targetlist[0] != pUserList->targetlist[1])
				{
					// 分体每次都响
					pUserList->targetID = pUserList->targetlist[pUserList->m_NowTargetIdx];
					pUserList->m_pObj->SetMagicSound(sSkillID);
				}
			}
			stage = 22; // 判断移动
		}
		else stage = 7; // 没有目标了，弹出动作
		return true;
	case 22:

	{
		const sFightPoint* pOffse = g_pMainState->m_FightWorkList[UserID].GetFightPoint();
		if (pOffse->m_xOff > 0)
		{
			if (pUserList->m_NowTargetIdx > 0)
			{
				if (pUserList->m_NowTargetID == pUserList->targetlist[pUserList->m_NowTargetIdx - 1])
				{
					stage = 23;//目标相同不用移动
					return true;
				}
			}
			stage = 2; // 移动
		}
		else
		{
			stage = 23; // 检测命中
		}
	}
		return true;
	case 2:
		// 鹰击
		if (sSkillID == 142) 
		{
			if (m_pFightState->Approach(UserID, pUserList->m_NowTargetID, false, 30))
			{
				stage = 23;
			}
		}
		else
		{
			if (m_pFightState->Approach(UserID, pUserList->m_NowTargetID))
			{
				stage = 23;
			}
		}
		return true;
	case 23:

	{
		m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->GetPropertyData(pTargetData);
		//检测命中
		CheckHit(pUserData, pTargetData, 200);
		pUserList->m_pObj->Set(POS_FIGHT_STAND);
		CountParry(pUserData, pTargetData);//格挡
		CountCri(pUserData, pTargetData);//必杀

		auto& gs = pTargetData->m_FightData.m_guardID;
		forr(gs, i)
		{
			auto& list = g_pMainState->m_FightWorkList[gs[i]];
			if (!list.isExist || list.CheckDie())
			{
				gs.erase(gs.begin() + i);
			}
		}
		//如果有人保护,等待保护者就位
		if (pTargetData->m_FightData.m_guardID.size())
		{
			pTarget->m_MagicWav.LoadWav(0x4ADFB0ED);
			stage = 101;
			return true;
		}
		stage = 20;
	}
		return true;
	case 20: return StageWaitSleep(10, UserID, 3);// 等待
	case 3:

	{
		int pos;
		if (rand() % 100 < 50)
			pos = POS_ATTACK2;
		else
			pos = POS_ATTACK;
		pUserList->m_pObj->Set(pos);
		pUserList->m_pObj->SetSound(pos);
		stage = 120;
	}
	case 120:
	{
		int atkp = m_pFightState->WorkAttack(UserID); // 是否到攻击点
		switch (atkp)
		{
		case 0:return true;
		default:
		{
			//是不是弓箭
			const sFightPoint* pOffse = g_pMainState->m_FightWorkList[UserID].GetFightPoint();
			if (pOffse->m_xOff == 0)
			{
				m_pFightState->m_HiddenWeapons.Load(0xE2BC8127);
				m_pFightState->m_HiddenWeaponsUseNum = 1;
				m_pFightState->m_HiddenWeaponsp[0].m_NeedShow = true;
				m_pFightState->m_HiddenWeaponsp[0].m_x = pUser->GetX();
				m_pFightState->m_HiddenWeaponsp[0].m_y = pUser->GetY() + 20;
				m_pFightState->m_HiddenWeaponsTargetID[0] = pUserList->m_NowTargetID;
				stage = 24;
				return true;
			}
			if (!PhysicalAtkHitStage(UserID, pUserList->m_NowTargetID, sSkillID)) // 攻击点动画
			{
				stage = 4;
				return true;
			}
			if (atkp != 1)
			{
				stage = 4;
			}
		}
			break;
		}
	}
		return true;
	case 24://弓箭

	{
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		if (m_pFightState->HiddenWeaponsMove(0, 50))
		{
			PhysicalAtkHitStage(UserID, pUserList->m_NowTargetID, sSkillID);

			stage = 4;
		}
	}
		return true;
	case 4:  //攻击判定
	{
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		stage = 5;//这个得放在effectskill之前,因为如果被反震了,stage将会失效
		cPropertyData* pPet;
		g_pMainState->m_FightWorkList[pUserList->m_NowTargetID].m_pObj->GetPropertyData(pPet);
		if (pPet->m_FightData.m_bHit)
			EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);

		g_pMainState->m_FightWorkList[pUserList->m_NowTargetID].m_pObj->GetPropertyData(pTargetData);
		if (pTargetData->m_HP < 1)
		{
			pUserList->m_pObj->SetSpeed(15);
		}


		if (!pUserList->NextTarget(m_pFightState, sSkillID))
		{
//			int hpout;
//			Cost(hpout, Skilllv, sSkillID, UserID, pUserList->m_MaxTargetNum, true);
			Cost(UserID, sSkillID, pUserList->m_MaxTargetNum, true);
			switch (sSkillID)
			{
			case 142://鹰击	
			{
				sBuff buf;
				buf.remainingTimes = 1;
				SetDateBuffUp(UserID, UserID, sSkillID, buf);
			}
				break;
			case 148:
				pUser->ReMoveStateID(145);//取消变身
				break;
			case 0: //横扫 
			case 1017:
			{
				sBuff buf;
				buf.remainingTimes = 1;
				SetDateBuffUp(UserID, UserID, 0, buf);
			}
				break;
			case 167:
			case 170:
				++pUserData->m_FightData.zhanyi;
				break;
			}
		}
	}
		return  true;
	case 5:
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_NowPos == POS_FIGHT_STAND)
		{

			if (pUserList->m_NowTargetID == -1)
			{
				pUserList->m_pObj->Set(POS_FIGHT_STAND);
				stage = 7;
				return true;
			}
			if (sSkillID == 142)//鹰击要跑回去
				stage = 8;
			else
				stage = 1;

		}
		return true;
	case 7:
	{
//		return StageWaitReturn(UserID, -1); //弹出动作
		if (m_pFightState->ReturnApproach(UserID))
		{
			m_pFightState->m_pFightWorkList[UserID]->m_work.pop_back();

			cbCounter(UserID);

		}
		return true;
	}
	case 8:
	{
//		return StageWaitReturn(UserID, 1); // 等待返回
		// 鹰击
		if (sSkillID == 142)
		{
			if (m_pFightState->ReturnApproach(UserID, 30))
			{
				m_pFightState->m_pFightWorkList[UserID]->GetWork()->stage = 1;
			}
		}
		else
		{
			if (m_pFightState->ReturnApproach(UserID))
			{
				m_pFightState->m_pFightWorkList[UserID]->GetWork()->stage = 1;
			}
		}
		return true;
	}
	case 101:  return StageWaitProtect(UserID, pUserList->m_NowTargetID, 3);
	}
	return true;
}

