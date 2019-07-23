#include "_global.h"
#include "_txt.h"

// 0-1000, 2000+
static bool runSkill(eSkill skill, int size)
{
	if (!g_pMainState->m_AI.isCanMag())
	{
		return false;
	}
	int k;
	auto ts = g_pMainState->m_AI.findTarget((int)skill, k);
	if (k >= 0 && k < size)
	{
		return false;
	}
	if (k < 0 && ts.size() < size)
	{
		return false;
	}
	if (!g_pMainState->m_AI.Cost((int)skill))
	{
		return false;
	}

	if (g_pMainState->m_AI.isSkillSeal((int)skill))
	{
		g_pMainState->m_AI.setData(g_pMainState->m_AI.m_UserID, ts.front());
		if (g_pMainState->m_SkillManager.CheckMagicHit(g_pMainState->m_AI.m_pUser->GetSkillLv(0), (int)skill, g_pMainState->m_AI.m_UserID, ts.front()) <= 20)
		{
			return false;
		}
	}

	g_pMainState->m_AI.UseSkill((int)skill, ts);
	return true;
}

// 0-1000, 2000+
static bool runSkill(const vector<eSkill>& skills)
{
	forv(skills, i)
	{
		if (runSkill(skills[i], 1))
		{
			return true;
		}
	}
	return false;
}

// 0-1000, 2000+
static bool runSkill(eSkill s){ vector<eSkill> es = { s }; return runSkill(es); }



bool cAI::CureSelf()
{
	if (!isHpLessThan(m_pUserData, 35))
	{
		return false;
	}

	if (getCures(m_UserID).size())
	{
		return false;
	}

	if (!isCanMag())
	{
		return runCure3000();
	}

	eMengPai mp = (eMengPai)m_pUserPc->m_PcData.m_MengPaiID;
	switch (mp)
	{
	case eMP_大唐官府:
		if (!isStateDMag(m_pUser))
		{
			auto ts = findOthers(m_UserID, eFindType::MpMag,
				[&](int i)
			{
				int uOld = m_UserID;
				SetUser(i);
				bool b = isCanMag();
				SetUser(uOld);
				return b;
			});
			if (ts.size() > 0)
			{
				if (runSkill(eSkill::安神诀))
				{
					return true;
				}
			}
		}
		break;
	case eMP_化生寺:
		break;
	case eMP_女儿村:
		break;
	case eMP_方寸山:
		if (!isStateDMag(m_pUser))
		{
			auto ts = findOthers(m_UserID, eFindType::MpMag,
				[&](int i)
			{
				int uOld = m_UserID;
				SetUser(i);
				bool b = isCanMag();
				SetUser(uOld);
				return b;
			});
			if (ts.size() > 0)
			{
				if (runSkill(eSkill::分身术))
				{
					return true;
				}
			}
		}

		if (runSkill(eSkill::归元咒))
		{
			return true;
		}

		break;
	case eMP_狮驼岭:
		if (!isStateDMag(m_pUser))
		{
			auto ts = findOthers(m_UserID, eFindType::MpMag,
				[&](int i)
			{
				int uOld = m_UserID;
				SetUser(i);
				bool b = isCanMag();
				SetUser(uOld);
				return b;
			});
			if (ts.size() > 0)
			{
				if (runSkill(eSkill::定心术))
				{
					return true;
				}
			}
		}
		break;
	case eMP_魔王寨:
		break;
	case eMP_盘丝岭:
		if (runSkill(eSkill::勾魂))
		{
			return true;
		}
		{
			auto ts = findOthers(m_UserID, eFindType::MpMag,
				[&](int i)
			{
				int uOld = m_UserID;
				SetUser(i);
				bool b = isCanMag();
				SetUser(uOld);
				return b;
			});
			if (ts.size() > 0)
			{
				if (runSkill(eSkill::幻镜术))
				{
					return true;
				}
			}
		}
		break;
	case eMP_阴曹地府:
		break;
	case eMP_东海龙宫:
		if (!isStateDMag(m_pUser))
		{
			if (runSkill(eSkill::神龙摆尾))
			{
				return true;
			}
		}
		break;
	case eMP_五庄观:
		break;
	case eMP_普陀山:
		break;
	case eMP_天宫:
		if (!isStateDMag(m_pUser))
		{
			auto ts = findOthers(m_UserID, eFindType::MpMag,
				[&](int i)
			{
				int uOld = m_UserID;
				SetUser(i);
				bool b = isCanMag();
				SetUser(uOld);
				return b;
			});
			if (ts.size() > 0)
			{
				if (runSkill(eSkill::天神护体))
				{
					return true;
				}
			}
		}
		break;
	case eMP_凌波城:
		if (runSkill(eSkill::不动如山))
		{
			return true;
		}
		break;
	case eMP_无底洞:
		break;
	case eMP_神木林:
		if (runSkill(eSkill::炎护))
		{
			return true;
		}
		if (runSkill(eSkill::星月之惠))
		{
			return true;
		}
		break;
	case eMP_随机:
		break;
	default:
		break;
	}

	return runCure3000();
}



bool cAI::RunDT()
{
	if (isCanMag())
	{
		int skill = (int)eSkill::破釜沉舟;
		auto ts = findTarget(skill);
		if (ts.size() >= 3)
		{
			setData(m_UserID, ts.front());
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
		else if (ts.size() > 0)
		{

			skill = 1000;
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}

			skill = (int)eSkill::横扫千军;
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
	}

	if (Summon())
	{
		return true;
	}


	if (getCureSeals(m_UserID).empty() && ((g_pMainState->m_FightWorkList[m_UserID]._myTurn % 3) == 0))
	{
		if (runSkill(eSkill::反间之计))
		{
			return true;
		}
	}

	if (isCanMag())
	{
		int skill = 1000;
		auto ts = findTarget(skill);
		if (ts.size() && getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
		{
			if (Cost(skill))
			{
				UseSkill(skill, ts);
				return true;
			}
		}
	}

	if (runSkill(eSkill::横扫千军))
	{
		return true;
	}

	return false;

}

bool cAI::RunNR()
{
	if (runSkill(eSkill::似玉生香))
	{
		return true;
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::雨落寒沙, 3))
	{
		return true;
	}

	if (runSkill({ eSkill::满天花雨, eSkill::雨落寒沙 }))
	{
		return true;
	}

	return false;


}

bool cAI::RunFC()
{
	if (m_pUserData->m_MP == 0)
	{
		if (runSkill(eSkill::凝神术))
		{
			return true;
		}
	}

	if (runSkill(eSkill::失心符))
	{
		return true;
	}

	if (Summon())
	{
		return true;
	}

	auto ts = findOthers(m_UserID, eFindType::MpMag,
	[&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	});

	if (ts.size() && runSkill(eSkill::分身术))
	{
		return true;
	}

	if (runSkill({ eSkill::定身符, eSkill::碎甲符, eSkill::落雷符 }))
	{
		return true;
	}


	return false;


}

bool cAI::RunHS()
{
	int phy = findOthers(m_UserID, eFindType::MpPhy, [&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	}).size();
	int size = findOwners(m_UserID).size();

	if (size >= 5 && runSkill(eSkill::金刚护法, 3))
	{
		return true;
	}

	if (phy > 0 && size >= 5 && runSkill(eSkill::金刚护体, 3))
	{
		return true;
	}


	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::佛法无边))
	{
		return true;
	}

	if (size >= 5 && runSkill(eSkill::韦陀护法, 3))
	{
		return true;
	}

	if (size <= 3 && runSkill(eSkill::金刚护法))
	{
		return true;
	}

	if (phy > 0 && size <= 3 && runSkill(eSkill::金刚护体))
	{
		return true;
	}


	if (runSkill(eSkill::唧唧歪歪))
	{
		return true;
	}

	return false;


}

bool cAI::RunLG()
{
	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::龙卷雨击, 3))
	{
		return true;
	}


	if (runSkill(eSkill::二龙戏珠))
	{
		return true;
	}

	return false;


}

bool cAI::RunTG()
{
	if (runSkill(eSkill::错乱))
	{
		return true;
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::百万神兵))
	{
		return true;
	}

	if (isCanMag())
	{
		auto ts = findOthers(m_UserID, eFindType::MpMag,
			[&](int i)
		{
			int uOld = m_UserID;
			SetUser(i);
			bool b = isCanMag();
			SetUser(uOld);
			return b;
		});

		if (ts.size() && runSkill(eSkill::天神护体))
		{
			return true;
		}

		int skill = (int)eSkill::五雷轰顶;
		ts = findTarget(skill);
		if (ts.size() && Cost(skill))
		{
			setData(m_UserID, ts.front());
			if (s_data2->m_HP > s_data1->m_Lv * 120)
			{
				UseSkill(skill, ts);
				return true;
			}
		}
	}

	if (runSkill(eSkill::雷霆万钧))
	{
		return true;
	}
	return false;



}

bool cAI::RunWZ()
{
	if (runSkill(eSkill::日月乾坤))
	{
		return true;
	}


	if (Summon())
	{
		return true;
	}

	auto ts = findOwners(m_UserID, eFindType::Mp0);
	if (ts.size())
	{
		if (runSkill(eSkill::炼气化神))
		{
			return true;
		}
	}

	if (isCanMag())
	{
		int skill = (int)eSkill::飘渺式;
		ts = findTarget(skill);
		if (ts.size() >= 3)
		{
			setData(m_UserID, ts.front());
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
		else if (ts.size() > 0)
		{
			skill = (int)eSkill::烟雨剑法;
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
	}

	if (getFires(m_UserID).size() && runSkill(eSkill::烟雨剑法))
	{
		return true;
	}

	if (runSkill(eSkill::飘渺式, 3))
	{
		return true;
	}

	if (runSkill(eSkill::烟雨剑法))
	{
		return true;
	}

	return false;


}

bool cAI::RunPT()
{
	int mag = findOthers(m_UserID, eFindType::MpMag,
		[&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	}).size();
	int mag2 = findOwners(m_UserID, eFindType::MpMag, nullptr, (int)eSkill::灵动九天).size();
	int size = findOwners(m_UserID).size();
	if (mag || mag2)
	{
		if (size >= 5 && runSkill(eSkill::灵动九天, 3))
		{
			return true;
		}
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::颠倒五行))
	{
		return true;
	}


	if (mag2)
	{
		if (runSkill(eSkill::灵动九天))
		{
			return true;
		}
	}

	int skill = rand() % 5 + 105;
	if (runSkill((eSkill)skill))
	{
		return true;
	}
	return false;


}

bool cAI::RunDF()
{
	if (findOthers(m_UserID, eFindType::Hide).size() || findOthers(m_UserID, eFindType::MpSeal, [&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	}).size())
	{
		if (runSkill(eSkill::幽冥鬼眼))
		{
			return true;
		}
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill({ eSkill::锢魂术, eSkill::魂飞魄散 }))
	{
		return true;
	}

	if (runSkill(eSkill::阎罗令, 3))
	{
		return true;
	}

	if (rand() % 100 < 50 && runSkill(eSkill::判官令))
	{
		return true;
	}

	if (runSkill(eSkill::黄泉之息))
	{
		return true;
	}

	return false;

}

bool cAI::RunPS()
{
	if (m_pUserData->m_MP == 0)
	{
		if (runSkill(eSkill::摄魄))
		{
			return true;
		}
	}

	if (runSkill(eSkill::含情脉脉))
	{
		return true;
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::天罗地网))
	{
		return true;
	}

	return false;


}

bool cAI::RunMW()
{
	eSkill e = eSkill::无敌牛虱;
	if (rand() % 100 < 50)
	{
		e = eSkill::无敌牛妖;
	}

	if (((g_pMainState->m_FightWorkList[m_UserID]._myTurn % 3) == 1) && runSkill(e))
	{
		return true;
	}

	auto ts = findOthers(m_UserID, eFindType::Hide);
	if (ts.size())
	{
		if (runSkill(eSkill::牛劲))
		{
			return true;
		}
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::飞砂走石, 2))
	{
		return true;
	}

	if (runSkill(eSkill::三昧真火))
	{
		return true;
	}

	return false;

}

bool cAI::RunST()
{
	auto get145Times = [&]()
	{
		for (list<sBuff>::iterator it = m_pUser->m_StateList.begin(); it != m_pUser->m_StateList.end(); it++)
		{
			if (it->ID == 145)
				return it->remainingTimes;
		}
		return -1;
	};

	if (get145Times() < 0)
	{
		if (runSkill(eSkill::变身))
		{
			return true;
		}
	}

	if (isCanMag())
	{
		int skill = (int)eSkill::鹰击;
		auto ts = findTarget(skill);
		if (ts.size() >= 3)
		{
			setData(m_UserID, ts.front());
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
		else if (ts.size() > 0)
		{
			skill = (get145Times() == 0) ? (int)eSkill::连环击 : (int)eSkill::狮搏;
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
	}

	if (getFires(m_UserID).size() && runSkill((get145Times() == 0) ? eSkill::连环击 : eSkill::狮搏))
	{
		return true;
	}

	if (getCureSeals(m_UserID).empty())
	{
		if (runSkill(eSkill::威慑))
		{
			return true;
		}
	}

// 	auto ts = findOthers(m_UserID, eFindType::MpMag,
// 		[&](int i)
// 	{
// 		int uOld = m_UserID;
// 		SetUser(i);
// 		bool b = isCanMag();
// 		SetUser(uOld);
// 		return b;
// 	});
// 
// 	if (ts.size() && runSkill(eSkill::定心术))
// 	{
// 		return true;
// 	}

	if ((get145Times() > 1 && !m_pUserData->m_FightData.cannotAll || get145Times() < 0) && Summon())
	{
		return true;
	}

	if (runSkill(eSkill::鹰击, 3))
	{
		return true;
	}

	if (get145Times() == 0)
	{
		if (runSkill(eSkill::连环击))
		{
			return true;
		}
	}

	if (runSkill(eSkill::狮搏))
	{
		return true;
	}

	return false;

}

bool cAI::RunLB()
{
	if (runSkill(eSkill::翻江搅海, 5))
	{
		return true;
	}

	// 	if (runSkill(eSkill::惊涛怒, 3))
	// 	{
	// 		return true;
	// 	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::浪涌, 2))
	{
		return true;
	}

	if (isCanMag())
	{
		int skill = (int)eSkill::裂石;
		auto ts = findTarget(skill);
		if (ts.size())
		{
			setData(m_UserID, ts.front());
			if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
			{
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
		skill = (int)eSkill::断岳势;
		if (Cost(skill))
		{
			ts = findTarget(skill);
			if (ts.size())
			{
				setData(m_UserID, ts.front());
				if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
		skill = (int)eSkill::天崩地裂;
		if (Cost(skill))
		{
			ts = findTarget(skill);
			if (ts.size())
			{
				setData(m_UserID, ts.front());
				if (getDamage(m_UserID, ts.front(), skill) > s_data2->m_HP)
				{
					UseSkill(skill, ts);
					return true;
				}
			}
		}
	}

	if (runSkill(eSkill::裂石))
	{
		return true;
	}
	return false;
}

bool cAI::RunWD()
{
	int phy = findOthers(m_UserID, eFindType::MpPhy,
		[&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	}).size();
	int mag = findOthers(m_UserID, eFindType::MpMag,
		[&](int i)
	{
		int uOld = m_UserID;
		SetUser(i);
		bool b = isCanMag();
		SetUser(uOld);
		return b;
	}).size();
	int size = findOwners(m_UserID).size();

	if (mag > 0 && size >= 5 && runSkill(eSkill::金身舍利, 3))
	{
		return true;
	}

	if (phy > 0 && size >= 5 && runSkill(eSkill::明光宝烛, 3))
	{
		return true;
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::夺魄令))
	{
		return true;
	}


	if (mag > 0 && size <= 3 && runSkill(eSkill::金身舍利))
	{
		return true;
	}

	if (phy > 0 && size <= 3 && runSkill(eSkill::明光宝烛))
	{
		return true;
	}

	if (runSkill({ eSkill::移魂化骨, eSkill::夺命咒 }))
	{
		return true;
	}

	return false;

}

bool cAI::RunSM()
{

	int size = findOwners(m_UserID).size();

	if (size >= 5 && runSkill(eSkill::密润, 3))
	{
		return true;
	}

	if (Summon())
	{
		return true;
	}

	if (runSkill(eSkill::落叶萧萧, 2))
	{
		return true;
	}

	if (size <= 3 && runSkill(eSkill::密润))
	{
		return true;
	}

	if (isCanMag())
	{
		int skill = rand() % 3 + 195;
		auto ts = findTarget(skill);
		if (ts.size())
		{
			setData(m_UserID, ts.front());
			int d = getDamage(m_UserID, ts.front(), skill);
			if (d * 2 < getDamage(m_UserID, ts.front(), (int)eSkill::血雨))
			{
				skill = (int)eSkill::血雨;
				if (Cost(skill))
				{
					UseSkill(skill, ts);
					return true;
				}
			}
			if (Cost(skill))
			{
				UseSkill(skill, ts);
				return true;
			}
		}
	}
	return false;
}















