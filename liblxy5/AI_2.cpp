#include "_global.h"
#include "_txt.h"


void cAI::UseSkill(int id, const vector<int>& targets)
{
	//	if (m_TargetID == -1)return;
	sFightWork& list = g_pMainState->m_FightWorkList[m_UserID];
	list.m_WorkType = WORKTYPE_MAGIC;
	// 	list.m_SkillSelect.SkillLv = m_pUserPetData->m_Lv + m_pUserPetData->m_StrongLv/5-10;
	// 	if (list.m_SkillSelect.SkillLv < 0)list.m_SkillSelect.SkillLv = 0;
	// 	if (list.m_SkillSelect.SkillLv>180)list.m_SkillSelect.SkillLv = 180;
	list.m_SkillSelect.SkillLv = list.m_pObj->GetSkillLv(0);
	list.m_SkillSelect.SkillID = id;
	list.m_SkillSelect.TargetID = targets.front();
	// 	list.m_MaxTargetNum = g_pMainState->m_SkillManager.GetSkill(id)->m_TargetNum;
	// 	if (list.m_MaxTargetNum > targets.size())
	{
		list.m_MaxTargetNum = targets.size();
	}
	for (int i = 0; i < list.m_MaxTargetNum; ++i)
	{
		list.targetlist[i] = targets[i];
	}
}

void cAI::NormalAtk(const vector<int>& targets)
{
	sFightWork& list = g_pMainState->m_FightWorkList[m_UserID];
	list.m_WorkType = WORKTYPE_ATTACK;
	list.m_SkillSelect.SkillLv = 0;
	list.m_SkillSelect.SkillID = 1000;
	list.m_SkillSelect.TargetID = targets.front();

	list.m_MaxTargetNum = targets.size();
	for (int i = 0; i < list.m_MaxTargetNum; ++i)
	{
		list.targetlist[i] = targets[i];
	}
}


void cAI::checkHero()
{
	//	Reset();
	//	GetNeed(0, 20);
	_controlMap.clear();
	_controlMap.insert(make_pair(eFindType::Dying, set<int>()));
	_controlMap.insert(make_pair(eFindType::UnSeal, set<int>()));
	auto isItemResurgence = [](int k)
	{
		sItem2* item = g_pMainState->m_SkillManager.GetItem(k);
		if (!item)
		{
			return false;
		}
		if (item->GetType() != 22)
		{
			return false;
		}
		return item->GetID() == 44 || item->GetID() == 45;
	};

	auto isItemUnSeal = [](int k)
	{
		sItem2* item = g_pMainState->m_SkillManager.GetItem(k);
		if (!item)
		{
			return false;
		}
		if (item->GetType() != 22)
		{
			return false;
		}
		return item->GetID() == 49;
	};

	for (int i = 0; i < 10; ++i)
	{
		if (!g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))
		{
			continue;
		}
		if (g_pMainState->m_FightWorkList[i].m_FriendListid >= 0)
		{
			continue;
		}
		const auto& ss = g_pMainState->m_FightWorkList[i].m_SkillSelect;
		if (ss.TargetID < 0)
		{
			continue;
		}

		if (isSkillResurgence(ss.SkillID) || (ss.SkillID == 1003 && isItemResurgence(i)))
		{
			_controlMap.at(eFindType::Dying).insert(ss.TargetID);
		}
		else if ((ss.SkillID >= 3010 && ss.SkillID <= 3013) ||
			(ss.SkillID == 1003 && isItemUnSeal(i)))
		{
			_controlMap.at(eFindType::UnSeal).insert(ss.TargetID);
		}

	}
}



bool cAI::AutoRunAi(int user)
{
	SetUser(user);

	if (!m_pUserPc)
	{
		int skill = RunPet();
		if (skill >= 0)
		{
			auto ts = findTarget(skill);
			if (ts.size())
			{
				UseSkill(skill, ts);
				return true;
			}
			if (!m_pUserData->m_FightData.cannotAll)
			{
				defense(user);
				return true;
			}
		}
		if (!m_pUserData->m_FightData.cannotAll)
		{
			defense(user);
			return true;
		}
		return false;
	}

	eMengPai mp = (eMengPai)m_pUserPc->m_PcData.m_MengPaiID;
	int skill = g_pMainState->m_FightWorkList[user].m_FriendListid;
	if (skill >= 0)
	{
		auto ts = findTarget(skill);
		if (ts.size() && Cost(skill))
		{
			UseSkill(skill, ts);
			return true;
		}
		if ((isMpPhy((cPcData*)m_pUserData) || m_pUserData->m_MP == 0 || mp < 0) && isCanAtk())
		{
			auto ts = findTarget(1000);
			if (ts.size())
			{
				NormalAtk(ts);
				return true;
			}
		}
		if (!m_pUserData->m_FightData.cannotAll)
		{
			defense(user);
			return true;
		}
		return false;
	}

	if (isMpCure((cPcData*)m_pUserData) && isCanMag() && resurgence(user))
	{
		return true;
	}

	if (isMpSeal((cPcData*)m_pUserData))
	{
		if (runResurgence3000())
		{
			return true;
		}
	}

	if (isMpCure((cPcData*)m_pUserData) || isMpSeal((cPcData*)m_pUserData))
	{
		if (runUnSeal3000(false))
		{
			return true;
		}

		if (isMpCure((cPcData*)m_pUserData) && isCanMag() && Cure(user))
		{
			return true;
		}

		if (RunLH())
		{
			return true;
		}
	}
	else
	{
		auto seals = getSeals(user);
		auto cures = getCures(user);

		if (seals.empty() && cures.empty())
		{
			if (runResurgence3000())
			{
				return true;
			}

			if (runUnSeal3000(true))
			{
				return true;
			}
			if (RunLH())
			{
				return true;
			}
		}
	}

	if (CureSelf())
	{
		return true;
	}

	switch (mp)
	{
	case eMP_大唐官府:if (RunDT()) return true; break;
	case eMP_方寸山:if (RunFC()) return true; break;
	case eMP_化生寺:if (RunHS()) return true; break;
	case eMP_女儿村:if (RunNR()) return true; break;
	case eMP_天宫:if (RunTG()) return true; break;
	case eMP_东海龙宫:if (RunLG()) return true; break;
	case eMP_五庄观:if (RunWZ()) return true; break;
	case eMP_普陀山:if (RunPT()) return true; break;
	case eMP_阴曹地府:  if (RunDF()) return true; break;
	case eMP_魔王寨:if (RunMW()) return true; break;
	case eMP_狮驼岭:if (RunST()) return true; break;
	case eMP_盘丝岭:if (RunPS()) return true; break;
	case eMP_凌波城:if (RunLB()) return true; break;
	case eMP_无底洞:if (RunWD()) return true; break;
	case eMP_神木林:if (RunSM()) return true; break;
	}

	if (runPoxueRuodianPosui3000())
	{
		return true;
	}

	if ((isMpPhy((cPcData*)m_pUserData) || m_pUserData->m_MP == 0 || mp < 0) && isCanAtk())
	{
		auto ts = findTarget(1000);
		if (ts.size())
		{
			NormalAtk(ts);
			return true;
		}
	}

	if (!m_pUserData->m_FightData.cannotAll)
	{
		defense(user);
		return true;
	}
	return false;
}


static vector<int> s_petAtkSkills = { (int)eSkill::死亡召唤, (int)eSkill::善恶有报, (int)eSkill::力劈华山 };
static vector<int> s_petAtkSkill2s = { (int)eSkill::壁垒击破, (int)eSkill::惊心一剑, (int)eSkill::剑荡四方 };
static vector<int> s_petMagSkills = { (int)eSkill::天降灵葫, (int)eSkill::月光, (int)eSkill::吸星大法xx };

int cAI::RunPet()
{
	if (isCanMag() && 
		m_pUserData->isHadPetSkill((int)eSkill::法术防御) &&
		!m_pUser->CheckHaveState((int)eSkill::法术防御) && 
		Cost((int)eSkill::法术防御))
	{
		if (findOthers(m_UserID, eFindType::MpMag,
			[&](int i)
		{
			int uOld = m_UserID;
			m_UserID = i;
			bool b = isCanMag();
			m_UserID = uOld;
			return b;
		}).size())
		{
			return (int)eSkill::法术防御;
		}
	}

	auto runSs = [&](vector<int>& ss)
	{
		while (ss.size())
		{
			int r = rand() % ss.size();
			if (Cost(ss[r]))
			{
				auto ts = findTarget(ss[r]);
				if (ts.size())
				{
					return ss[r];
				}
			}
			ss.erase(ss.begin() + r);
		};
		return -1;
	};

	auto runs = [&](const vector<int>& ss)
	{
		vector<int> s2;
		int skill;
		forv(ss, i)
		{
			skill = ss[i];
			if (m_pUserData->isHadPetSkill(skill) && Cost(skill))
			{
				auto ts = findTarget(skill);
				if (skill == (int)eSkill::剑荡四方)
				{
					if (ts.size() >= 3)
					{
						s2.push_back(skill);
					}
				}
				else
				{
					if (ts.size())
					{
						s2.push_back(skill);
					}
				}

			}
		}
		return s2;
	};

	if (isCanMag())
	{
		vector<int> ms, m2s, ps, bs;
		isHadPetSkill(m_pUserData, bs, ps, ms, m2s);

		if (!isMagFromPoint(m_pUserData))
		{
			vector<int> ss = runs(s_petAtkSkills);
			if (ss.size() && rand() % 100 < 90)
			{
				return ss[rand() % ss.size()];
			}

			ss = runs(s_petAtkSkill2s);
			if (ss.size() && rand() % 100 < 90)
			{
				return ss[rand() % ss.size()];
			}

			if (rand() % 100 < 90 && isCanAtk())
			{
				return 1000;
			}
		}

		vector<int> ss = runs(s_petMagSkills);
		if (ss.size() && rand() % 100 < 80)
		{
			return ss[rand() % ss.size()];
		}

		int skill = runSs(m2s);
		if (skill >= 0)
		{
			return skill;
		}
		skill = runSs(ms);
		if (skill >= 0)
		{
			return skill;
		}
	}

	if (isCanAtk())
	{
		if (m_pUserData->m_MP == 0 || !isMagFromPoint(m_pUserData))
		{
			return 1000;
		}
	}

	return -1;
}



bool cAI::resurgence(int user/*, int target*/)
{

	int k;
	auto ts = findTarget((int)eSkill::我佛慈悲, k);
	if (k == 0)
	{
		return false;
	}
	eMengPai mp = (eMengPai)m_pUserPc->m_PcData.m_MengPaiID;
	int skill = -1;
	switch (mp)
	{
	case eMP_化生寺:
		skill = (int)eSkill::我佛慈悲;
		break;
	case eMP_普陀山:
		skill = (int)eSkill::杨柳甘露;
		break;
	case eMP_阴曹地府:
		skill = (int)eSkill::还阳术;
		break;
	case eMP_无底洞:
		skill = (int)eSkill::由己渡人;
		break;
	}
	if (skill >= 0)
	{
		if (Cost(skill))
		{
			UseSkill(skill, ts);
			return true;
		}
	}
	return false;
}



bool cAI::Cure(int user/*, int target,bool toall*/)
{
	auto ts = findOwners(user, eFindType::Hp70);
	if (ts.empty())
	{
		return false;
	}
	eMengPai mp = (eMengPai)m_pUserPc->m_PcData.m_MengPaiID;
	if (mp == eMP_普陀山)
	{
		if (ts.size() == 1)
		{
			setData(m_UserID, ts.front());
			if (isState(s_obj2, { (int)eSkill::普渡众生, (int)eSkill::杨柳甘露 }))
			{
				int k;
				auto t2s = findTarget((int)eSkill::自在心法, k);
				if (k > 0 && std::find(t2s.begin(), t2s.end(), ts.front()) != t2s.end())
				{
					if (Cost((int)eSkill::自在心法))
					{
						UseSkill((int)eSkill::自在心法, ts);
						return true;
					}
				}
			}
		}
		int k;
		ts = findTarget((int)eSkill::普渡众生, k);
		if (k > 0 && Cost((int)eSkill::普渡众生))
		{
			UseSkill((int)eSkill::普渡众生, ts);
			return true;
		}
		return false;
	}

	if (mp == eMP_五庄观)
	{
		int k;
		ts = findTarget((int)eSkill::生命之泉, k);
		if (k > 0 && Cost((int)eSkill::生命之泉))
		{
			UseSkill((int)eSkill::生命之泉, ts);
			return true;
		}
		return false;
	}

	int skill = -1;
	switch (mp)
	{
	case eMP_化生寺:
		if (findOwners(user, eFindType::HpNotFull).size() == 1)
		{
			skill = (int)eSkill::活血;
		}
		else
		{
			skill = (int)eSkill::救死扶伤;
		}
		break;
//	case eMP_五庄观:
//	case eMP_普陀山:
	case eMP_阴曹地府:
		skill = (int)eSkill::尸腐毒;
		break;
	case eMP_无底洞:
		skill = (int)eSkill::地涌金莲;
		break;
	}
	if (skill >= 0)
	{
		int k;
		auto ts = findTarget(skill, k);
		if ((k > 0 || (k < 0 && ts.size())) && Cost(skill))
		{
			UseSkill(skill, ts);
			return true;
		}
	}
	return false;


}

