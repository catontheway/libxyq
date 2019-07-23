#include "global.h"

// 随机选择目标
// SelectType 是法术的类型
// 0 平时自己
// 1 平时己方
// 2 战斗自己
// 3 战斗己方
// 4 战斗敌方
// 5 平时战斗自己
// 6 平时战斗己方
// 7 被动
// 8 未
// 9 战斗己方but自己
#if ccc_date
int cAI::AutoFindTarget(int userID, int SelectType, bool isCheckPeopleSpecial)
{
	//查找所有可选的ID
	int k = 10;
	switch (SelectType)
	{
	case 2: //只能对自己使用的法术
	case 5:
		return  userID;
	case 3: //只能对我方使用的法术ww
	case 6:
		if (userID < 10)k = 0;
		break;
	case 4: //对敌人使用
		if (userID > 9)	k = 0;
		break;
	}
	int existNum = 0;
	int idlist[10];
	sFightList* pList;
	int i2;
	cPetData *data = nullptr;
	g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
	int peopleSpecail = data->PeopleSpecial.d1;
	for (int i = 0; i < 10; i++)
	{
		i2 = i + k;
		pList = &g_pMainState->m_FightList[i2];
		if (i2 == userID)
		{
			if (SelectType == 3 || SelectType == 6)
			{
				continue;
			}
		}
		//目标是否存在
		if (userID!=i2)
		if (pList->isLive)
		{
			//目标是否活着
			if (!pList->CheckDie())
			{
				cPetData *data2 = nullptr;
				pList->m_pData->GetDateP(data2);
				if (!isCheckPeopleSpecial || (isCheckPeopleSpecial && peopleSpecail >= data2->PeopleSpecial.d2))
				{
					idlist[existNum] = i2;
					existNum += 1;
				}
			}
		}
	}
	//
	if (SelectType == 3 || SelectType == 6)
	{
		if (0 == existNum)return userID;
	}
	else
	if (0 == existNum)return -1;
	g_pMainState->m_InterfaceDoor.m_TimeShiCheng.UpdateTime();
	int select = idlist[rand() % existNum];

	return select;
}

int cAI::GetNextPos(int ID, int Num, int bLive)
{
	if (Num < 0 || Num >19)
	{
		ERRBOX(Num);
		return -1;
	}
	int start, end;
	if (ID < 10)start = 0;
	else start = 10;
	end = start + 10;
	for (int i = start; i < end; i++)
	{
		sFightList& list = g_pMainState->m_FightList[i];
		switch (bLive)
		{
		case 0://只找空位
			if (!list.isLive)return i;
			break;
		case 1://只找活物
			if ((0 == list.isLive) || list.CheckDie())
			{
			}
			else return i;
			break;
		case 2://只要存在就行
			if (list.isLive)
			{
				return i;
			}
			break;
		}
	}
	return -1;
}

int cAI::GetNear(int usetId, int ID, int Num,int bLive)
{
	if (Num < 0 || Num >19)
	{
		ERRBOX(Num);
		return -1;
	}
	int start, end;
	if (ID < 10)start = 0;
	else start = 10;
	end =start+ 10;

	int xpos = g_pMainState->m_pFightState->m_xPosList[ID];
	int ypos = g_pMainState->m_pFightState->m_yPosList[ID];
	int gaplist[10];
	int idlist[10];
	for (int i = 0; i < 10; i++)
	{
		idlist[i] = start+i;
	}
	int startgap = 0;
	cPetData *data = nullptr;
	g_pMainState->m_FightList[usetId].m_pData->GetDateP(data);
	int peopleSpecail = data->PeopleSpecial.d1;
	for (int i = start; i < end; i++)
	{
		sFightList& list = g_pMainState->m_FightList[i];
		switch (bLive)
		{
		case 0://只找空位
			if (list.isLive)
			{
				gaplist[startgap] = 999999;;
				startgap += 1;	
				continue;
			}
			break;
		case 1://只找活物
			if ((0 == list.isLive) || list.CheckDie())
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			break;
		case 2://只要存在就行
			if (!list.isLive)
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			break;
		case 3: // 看得见的活物
			if ((0 == list.isLive) || list.CheckDie())
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			cPetData *data2 = nullptr;
			g_pMainState->m_FightList[i].m_pData->GetDateP(data2);
			if (peopleSpecail < data2->PeopleSpecial.d2)
			{
				gaplist[startgap] = 999999;;
				startgap += 1;
				continue;
			}
			break;
		}
		
		int xpos2 = g_pMainState->m_pFightState->m_xPosList[i];
		int ypos2 = g_pMainState->m_pFightState->m_yPosList[i];
		gaplist[startgap] = abs(xpos - xpos2) + ((abs(ypos - ypos2))<<1);
		startgap += 1;
	}
	int pa, pb;
	for (int a = 0; a < startgap-1; a++)
	for (int b = a + 1; b<startgap; b++)
	{
		pa = gaplist[a];
		pb = gaplist[b];
		if (pa>pb)//前数大于后数
		{
			swap(gaplist[a], gaplist[b]);
			swap(idlist[a], idlist[b]);
		}
	}//排序结果，当前位置Y小的在前。
	if (999999 == gaplist[Num])return -1;
	return idlist[Num];

}


void cAttackAI::Escape(int userID)
{
// 	if (MyTest::getInstance()->isForceEspace)
// 	{
// 		g_pMainState->m_pFightState->m_bEscape = TRUE;
// 		return;
// 	}

	sFightList& list = g_pMainState->m_FightList[userID];
	list.m_WorkType = WORKTYPE_MAGIC;
	list.m_SkillSelect.Lv = 0;
	list.m_SkillSelect.SkillID = 1006;
	list.targetID = userID;
	list.m_SkillSelect.TargetID = userID;
}

void cAttackAI::Def(int userID)
{
	if (!g_pMainState->m_FightList[userID].isLive)return;
	cPetData* petdata;
	g_pMainState->m_FightList[userID].m_pData->GetDateP(petdata);
	if (petdata->m_FightProperty.cannotAll)return;
//	g_pMainState->m_AI.m_AttackAI.m_FightTarget[userID] = userID;
	sBuff buf;
	buf.times = 1;
	g_pMainState->m_SkillManager.SetDateBuffUp(userID, userID, 1002, buf);
	g_pMainState->m_FightList[userID].m_WorkType = -2;
}

BOOL cAttackAI::UseItem(eAIUseItemType mode)
{
	if (m_TargetID == -1)return FALSE;
	int ItemOwnerID = m_UserID;
	if (g_pMainState->m_FightList[ItemOwnerID].m_pData->m_IndexType == INDEXTYEP_PET)
	{
		if ((m_UserID % 10) >= 5)
			ItemOwnerID = m_UserID - 5;
		if (g_pMainState->m_FightList[ItemOwnerID].m_pData->m_IndexType == INDEXTYEP_PET)
		{
			return FALSE;
		}
	}
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[ItemOwnerID].m_pData->m_pIndex;
	if (!pc)
	{
		return FALSE;
	}
	sFightList& list = g_pMainState->m_FightList[m_UserID];
	if (pc->m_PCData.m_Item[mode].GetNum() < 2)
		return FALSE;
	list.m_ItemSelectID = mode;
	list.m_SkillSelect.SkillID = 1003;
	if (mode == eAIUseItemType暗器)
		list.m_SkillSelect.SkillID = 1005;
	list.m_SkillSelect.Lv = 0;
	list.m_SkillSelect.TargetID = m_TargetID;
	list.m_WorkType = WORKTYPE_MAGIC;


	int start, end;
	if (m_TargetID < 10)start = 0;
	else start = 10;
	end = start + 10;
	switch (mode)
	{
	case eAIUseItemTypeHP:
		m_bNeedAddHp[m_TargetID] -= 50;
		break;
	case eAIUseItemTypeHPALL:
		if (1)
		{
			for (int i = start; i < end;i++)
				m_bNeedAddHp[m_TargetID] -= 30;
		}
		break;
	case eAIUseItemTypeMP:
		m_bNeedAddMp[m_TargetID] = 0;
		break;
	case eAIUseItemTypeMPALL:
		if (1)
		{
			for (int i = start; i < end; i++)
				m_bNeedAddMp[m_TargetID] = 0;
		}
		break;
	case eAIUseItemTypelive:
		m_bNeedlive[m_TargetID] = 0;
		break;
	case eAIUseItemTypeUnseal:
		m_bNeedUnSeal[m_TargetID] = 0;
		break;
	case eAIUseItemType暗器:
		m_bAtk[m_TargetID] += 20;
		break;
	}
	return TRUE;
	
	
}

// 
// 
// int cAI::FindDieFight(int start /*= 0*/, int end /*= 5*/)
// {
// 
// 
// 	for (int i = start; i < end; i++)
// 	{
// 		if (g_pMainState->m_FightList[i].isExist)
// 		if (g_pMainState->m_FightList[i].CheckDie())
// 		{
// 			return i;
// 		}
// 	}
// 	return -1;
// }
// 


int cAttackAI::getVisibleNO(int userID, bool our, bool isCheckPeopleSpecial)
{
	int star;
	if (our && userID < 10 || (!our && userID >= 10))
	{
		star = 0;
	}
	else
	{
		star = 10;
	}
	int num = 0;
	for (int i = star; i < star + 10; ++i)
	{
		if (g_pMainState->m_FightList[i].isLive && !g_pMainState->m_FightList[i].CheckDie())
		{
			cPetData *data = nullptr;
			g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
			cPetData *data2 = nullptr;
			g_pMainState->m_FightList[i].m_pData->GetDateP(data2);
			if (data && data->PeopleSpecial.d1 < data2->PeopleSpecial.d2)
			{
				continue;
			}
			++num;
		}
	}
	return num;
}

bool cAttackAI::runPoxueAtk()
{
	if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 3)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3034))
			{
				if (m_TargetID < 0)
				{
					SetTarget(FindAtkTarget(300, TRUE, m_UserID));
				}
				if (m_TargetID >= 0)
				{
					UseMagic(3034);
					return true;
				}
			}
		}
		if (!m_pUserPetData->m_FightProperty.cannotAttack)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(100, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				NormalAtk();
				return true;
			}
		}
	}
	return false;
}

bool cAttackAI::runSelfunseal()
{
	if (isCanAtk() && isPut() && selectAtk())
	{
		return true;
	}
	if (m_pUserPetData->m_FightProperty.cannotMagic || m_pUserPetData->m_FightProperty.cannotSkill)
	{
		if (!m_pUserPetData->PeopleSpecial.d2)
		{
			if (!m_pUserPetData->m_FightProperty.cannotUseItem)
			{
				if (m_bNeedUnSeal[m_UserID])
				{
//					if (CheckItem(eAIUseItemTypeUnseal))
					{
						SetTarget(m_UserID);
						if (UseItem(eAIUseItemTypeUnseal))
						{
							m_bNeedUnSeal[m_UserID] = FALSE;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool cAttackAI::isPutRate()
{
	if (isAtkMode())
	{
		return (isCanAtk() && isPut() && rand() % 100 < 15) || !isCanMag();
	}
	return isCanAtk() && isPut() && !isCanMag();
}

bool cAttackAI::selectAtk()
{
	if (!isCanAtk())
	{
		return false;
	}
	if (m_TargetID < 0)
	{
		SetTarget(FindAtkTarget(100, TRUE, m_UserID));
	}
	if (m_TargetID >= 0)
	{
		NormalAtk();
		return true;
	}
	return false;
}

bool cAttackAI::RunLH()
{
	int self = m_UserID < 10 ? 10 : 0;
	vector<POINT>out;
	FindEnemy(TRUE, FALSE, out, eET可法系, self);
	if (out.size() > 2 && !m_pUser->CheckHaveState(3025) && CheckCanSkill(3025))
	{
		SetTarget(m_UserID);
		UseMagic(3025);
		return true;
	}
	return false;
}

void cAttackAI::RunDT()
{
	SetTarget(m_FightTarget[m_UserID]);
	bool isTasrget = (m_TargetID >= 0);
	int self = m_UserID < 10 ? 10 : 0;
	auto runPoxue = [&]()
	{
		if (isCanSpec() && CheckCanSkill(3034))
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(300, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(3034);
				return true;
			}
		}
		return false;
	};

	auto isBlood10 = [&]()
	{
		return m_pUserPetData->m_HP > m_pUserPetData->m_HPMax.GetData() / 10;
	};
	
	auto isPofuBlood = [&]()
	{
		return m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData() > m_pTargetPetData->m_HP;
	};

	auto runPofuOfNoTarget = [&]()
	{
		if (isBlood10())
		{
			SetTarget(FindAtkTarget(150, TRUE, m_UserID));
			if (m_TargetID >= 0)
			{
				UseMagic(7);
				return true;
			}
		}
		return false;
	};

	auto runHengsao = [&]()
	{
		if (isBlood10())
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(400, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(0);
				return true;
			}
		}
		return false;
	};


	if (m_TargetID >= 0)
	{
		if (isCanMag())
		{
			if (isPofuBlood() && isBlood10() && getVisibleNO() > 2)
			{
				return UseMagic(7);
			}
			if (!isAtkMode() && runHengsao())
			{
				return;
			}
			if (isBlood10() && getVisibleNO() > 2)
			{
				return UseMagic(7);
			}
		}
		if (isCanAtk() && isPut() && selectAtk())
		{
			return;
		}
		if (runPoxue())
		{
			return;
		}
	}

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (m_TargetID < 0 && isCanMag())
		{
			vector<POINT> out;
			if (g_pMainState->m_pFightState->_turn < 5)
			{
				FindEnemy(TRUE, FALSE, out, eET可封系, m_UserID);
				auto out2 = check隐身(out, m_UserID);
				if (!out2.size() && rand() % 100 < 20)
				{
					out.clear();
					FindEnemy(TRUE, FALSE, out, eET反间6, self);
					out2 = check隐身(out, m_UserID);
					if (out2.size())
					{
						SetTarget(out2.front());
						return UseMagic(6);
					}
				}
			}

			FindEnemy(TRUE, FALSE, out, eET可法系, self);
			if (out.size() > 2 && !m_pUser->CheckHaveState(8) &&
				!m_pUser->CheckHaveState(113) &&
				!m_pUser->CheckHaveState(2097) &&
				!m_pUser->CheckHaveState(3024) && 
				!m_pUser->CheckHaveState(3025))
			{
				if (isUseOtherRate())
				{
					SetTarget(m_UserID);
					return UseMagic(8);
				}
			}
		}
	}
	if (runPoxue())
	{
		return;
	}
	if (isPutRate() && selectAtk())
	{
		return;
	}
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag() && getVisibleNO() > 2)
	{
//		if (m_UserID < 10 || (m_UserID >= 10 && rand() % 100 < 70))
		if ((isAtkMode() && (m_UserID < 10 || (m_UserID >= 10 && rand() % 100 < 70))) || (!isAtkMode() && isPofuBlood()))
		{
			if (runPofuOfNoTarget())
			{
				return;
			}
		}
	}
	if (isCanMag() && runHengsao())
	{
		return;
	}

	if (runSelfunseal())
	{
		return;
	}
	if (!m_pUser->CheckHaveState(0) && !m_pUser->CheckHaveState(7))
	{
		return Def(m_UserID);
	}
}
void cAttackAI::RunNR()
{
	SetTarget(m_FightTarget[m_UserID]);
	int tOld = m_TargetID;
// 	BOOL bConduct = FALSE;
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
// 		SetTarget(m_FightTarget[m_UserID]);
// 		bConduct = TRUE;
// 	}
// 	else SetTarget(-1);

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			//玩家指定目标的情况下并且目标没有被封 尝试封印目标
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && (isM == 0 || isM == 1))
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(54);
			}
		}

// 		if (!m_bSeal[m_TargetID])
// 		{
// 			if (!m_pTargetPetData->m_FightProperty.cannotMagic)
// 			{
// 				m_bSeal[m_TargetID] = TRUE;
//  				if (m_pUserPetData->m_LV > 129)
//  				{
//  					return UseMagic(59);
//  				}
// 				return UseMagic(54);
// 			}
// 		}

	}
// 	if ((MyTest::getInstance()->isAtkMode(m_UserID) || (!MyTest::getInstance()->isAtkMode(m_UserID) && rand() % 100 < 60)) && !m_pUserPetData->m_FightProperty.cannotUseItem)
// 	{//使用暗器
// 		if (m_TargetID < 0)
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
// 		}
// 		if (m_TargetID >= 0 && UseItem(eAIUseItemType暗器))
// 		{
// 			return;
// 		}
// 	}

	int told = m_TargetID;
	m_TargetID = tOld;
	if (isPutRate() && selectAtk())
	{
		return;
	}
	m_TargetID = told;
	
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag() && rand() % 100 < 30)
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0)
		{
			return UseMagic(50);
		}
	}
	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0 && UseItem(eAIUseItemType暗器))
		{
			return;
		}
	}

// 	if (!m_pUserPetData->m_FightProperty.cannotMagic)
// 	{
// 		if (m_TargetID < 0)
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
// 		}
// 		if (m_TargetID >= 0)
// 		{
// 			return UseMagic(50);
// 		}
// 	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	
}
void cAttackAI::RunFC()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
// 	if (m_pUserPetData->m_AiLv > 80)
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
// 	{
// 		if (m_pUserPetData->m_StrongLv > 70)
// 		{//笑里
// 
// 			if (m_FightTarget[m_UserID] == -1)
// 			{
// 				int target = FindCpMaxTarget();
// 				if (target > -1)
// 				{
// 					SetTarget(target);
// 
// 					if (m_pTarget->m_IndexType == INDEXTYEP_CHARACTER)
// 					{
// 						cCharacter* pc = (cCharacter*)m_pTarget->m_pIndex;
// 						if (pc->m_PCData.m_CP > 100)
// 						{
// 
// 							if (CheckCanSkill(3016))return UseMagic(3016);//笑里
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}

	auto runLuoleifu = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
//				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
				SetTarget(FindAtkTarget(100, FALSE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(28);
				return true;
			}
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		int self = m_UserID < 10 ? 10 : 0;
		if (isCanMag())
		{
			if (m_TargetID < 0)
			{
				vector<POINT> out;
				FindEnemy(TRUE, FALSE, out, eET可法系, self);
				if (out.size() > 2 && !m_pUser->CheckHaveState(26) && !m_pUser->CheckHaveState(113))
				{
					if (isUseOtherRate())
					{
						SetTarget(m_UserID);
						return UseMagic(26);
					}
				}
			}
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && isM >= 0)
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(isM == 1 ? 15 : (isM == 0 ? 21 : 17));
			}
			vector<POINT> out;
			FindEnemy(TRUE, FALSE, out, eET封印对象, self, 27);
			auto out2 = check隐身(out, m_UserID);
			if (out2.size() > 2)
			{
				SetTarget(out2.front());
				return UseMagic(27);
			}
		}
	}
// 		if (m_pUserPetData->m_LV >= 120 && !m_pUser->CheckHaveState(26))
// 		{
// 			SetTarget(m_UserID);
// 			return UseMagic(26);
// 		}

	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runLuoleifu())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	

// 			if (target2 == -1)
// 			{//敌方全部被封了.........
// 				if (m_bPKMode)
// 				{
// 					if (m_pUserPetData->m_LV>129)
// 					{
// 						if (!m_pUser->CheckHaveState(26))
// 							return UseMagic(26);
// 						if (!m_pTarget->CheckHaveState(27))
// 							return UseMagic(27);
// 						return defense(m_UserID);
// 					}
// 				}
// 				else
// 					return UseMagic(28);
// 			}
// 			SetTarget(target2);
// 		}
// 	
// 		if (m_FightTarget[m_UserID] == -1)
// 		{
// 			if (!m_pTarget->CheckHaveState(15))
// 				return UseMagic(15);
// 		}
// 		else
// 		{
// 			//检测我方是物理型的多还是法术型的多
// 			int ouratknum = 0;
// 			int start, end;
// 			if (m_UserID < 10)start = 0;
// 			else start = 10;
// 			end = start + 10;
// 			cPetData* pPetdata;
// 			for (int i = start; i < end; i++)
// 			{
// 				g_pMainState->m_FightList[i].m_pData->GetDateP(pPetdata);
// 				if (pPetdata->m_AddPoint.atk> 2)
// 				{
// 					ouratknum += 1;
// 					continue;
// 				}
// 				if (pPetdata->m_AddPoint.mp > 2)
// 				{
// 					ouratknum -= 1;
// 					continue;
// 				}
// 			}
// 			if (ouratknum > 1)
// 			{
// 				return UseMagic(20);
// 			}
// 			else return UseMagic(14);
// 		}
// 		if (!m_pUserPetData->m_FightProperty.cannotUseItem)
// 		{
// 			if (CheckItem(eAIUseItemTypeMP)) { UseItem(eAIUseItemTypeMP); return; }
// 			if (CheckItem(eAIUseItemTypeMPALL)) { UseItem(eAIUseItemTypeMPALL); return; }
// 		}
// 	}else
// 	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
// 	{
// 		if (CheckItem(eAIUseItemTypeUnseal)){ UseItem(eAIUseItemTypeUnseal); return; }
// 	}
}
void cAttackAI::RunHS()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 		SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
	//烧双专用

		auto runjjyy = [&]()
		{
			if (!m_pUserPetData->m_FightProperty.cannotMagic)
			{
				if (m_TargetID < 0)
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
				}
				if (m_TargetID >= 0)
				{
					UseMagic(31);
					return true;
				}
			}
			return false;
		};

	if (!isAtkMode())
	{
		//使用法术
		vector<POINT> tList;

		auto hf = [&](int i)
		{
			//金刚护法
			int rr = FindEnemy(TRUE, FALSE, tList, eET上金刚33, m_UserID, 33);
			if (rr > i && tList.size())
			{
				SetTarget(tList[0].x);
				UseMagic(33);
				return true;
			}
			return false;
		};

		int self = m_UserID < 10 ? 10 : 0;
		auto ht = [&](int i)
		{
			//检测对方物理
			FindEnemy(TRUE, FALSE, tList, eET可物理系, self);
			if (tList.size() >= 2)
			{
				tList.clear();
				//金刚护体
				FindEnemy(TRUE, FALSE, tList, eET防最低, m_UserID, 35);
				if (tList.size() > i)
				{
					SetTarget(tList[0].x);
					UseMagic(35);
					return true;
				}
			}
			return false;
		};
		if (isCanMag())
		{
			if (hf(2))
			{
				return;
			}
		}

		if (isCanSpec() && RunLH())
		{
			return;
		}

		if (isCanMag())
		{
			if (ht(2))
			{
				return;
			}

			// 佛法无边
			FindEnemy(TRUE, FALSE, tList, eET佛法无边46, m_UserID, 46);
			if (tList.size())
			{
				SetTarget(tList[0].x);
				return UseMagic(46);
			}

			//韦陀护法
			FindEnemy(TRUE, FALSE, tList, eET可物理系, m_UserID, 34);
			if (tList.size() > 2)
			{
				SetTarget(tList[0].x);
				return UseMagic(34);
			}

			if (hf(0))
			{
				return;
			}

			if (ht(0))
			{
				return;
			}
		}
	}
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runjjyy())
		{
			return;
		}
	}

	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
}
void cAttackAI::RunLG()
{
	if (!isAtkMode() && isCanSpec() && RunLH())
	{
		return;
	}
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (m_FightTarget[m_UserID] >= 0)
	{
		SetTarget(m_FightTarget[m_UserID]);
	}
	else
	{
		SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
	}
	if (m_TargetID >= 0 && !m_pUserPetData->m_FightProperty.cannotMagic)
	{
		int n = getVisibleNO();
		if (n > 2)
		{
			if (m_UserID >= 10 && rand() % 100 < 20)
			{
				return UseMagic(88);
			}
			return UseMagic(80);
		}
		return UseMagic(88);
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	
// 	int start, end;
// 	if (m_UserID<10)start = 10;
// 	else start = 0;
// 	end = start + 10;
// 	switch (g_pMainState->GetLiveNum(start, end))
// 	{
// 	case 1://龙腾
// 		if (m_pUserPetData->m_AiLv > 90)
// 		if (m_pUserPetData->CheckHavePetSkill(2101))
// 		{
// 			return UseMagic(2101);
// 		}
// 		return UseMagic(79);
// 		break;
// 	case 2://二龙
// 		if (m_pUserPetData->m_LV > 109)
// 			return UseMagic(88);
// 	default://龙卷
// 		return UseMagic(80);
// 		break;
// 	}
}
void cAttackAI::RunTG()
{
	// 	if (m_FightTarget[m_UserID] > -1)
	// 	{
	SetTarget(m_FightTarget[m_UserID]);
	// 	}
	// 	else SetTarget(-1);
	// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
	// 	{
	// 	}

	auto runLeitingwanjun = [&]()
	{
		if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_ProPertyAtk)
		{
			if (m_TargetID < 0)
			{
//				SetTarget(FindDefminTarget(eProPerty灵力, false));
				SetTarget(FindAtkTarget(100, FALSE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(74);
				return true;
			}
		}
		else
		{
			if (m_TargetID < 0)
			{
//				SetTarget(FindDefminTarget(eProPerty防御, false));
				SetTarget(FindAtkTarget(100, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(71);
				return true;
			}
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			if (rand() % 100 < 20)
			{
				if (m_TargetID < 0)
				{
					SetTarget(FindDefminTarget(eProPerty气血, TRUE));
				}
				if (m_TargetID >= 0 && m_pTargetPetData->m_HP > m_pUserPetData->m_LV * 50 && m_pTargetPetData->m_HP > 6000)
				{
					return UseMagic(72);
				}
			}
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && isM >= 0)
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(isM == 1 ? 68 : (isM == 0 ? 69 : 67));
			}
		}
	}
	int t = m_TargetID;
	int p = RunPet();
	if ((p == 3 || p == 4) && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runLeitingwanjun())
		{
			return;
		}
	}

	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotMagic)
// 	{
// 		if (g_pMainState->m_FightList[10].isExist)
// 		{
// 			cPetData* ppetdata;
// 			g_pMainState->m_FightList[10].m_pData->GetDateP(ppetdata);
// 			if (ppetdata->m_HP > m_pUserPetData->m_LV * 200)
// 			{
// 				SetTarget(10);
// 				if (!CheckCanSkill(72))
// 				{
// 					SetTarget(m_UserID);
// 					if (CheckItem(eAIUseItemTypeMP)) { UseItem(eAIUseItemTypeMP); return; }
// 					if (CheckItem(eAIUseItemTypeMPALL)){ UseItem(eAIUseItemTypeMPALL); return; }
// 
// 					if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_LV * 2)//魔天宫
// 						return UseMagic(74);
// 					return defense(m_UserID);
// 				}
// 				return UseMagic(72);
// 			}
// 		}
// 		if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_LV * 2)//力天宫
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(FindAtkTarget(130));
// 			return  UseMagic(74);
// 		}
// 		else
// 		{
// //			if (m_pUserPetData->m_LV > 129)
// 			{
// 				if (m_FightTarget[m_UserID] == -1)
// 					SetTarget(FindAtkTarget(110,FALSE));
// 				return UseMagic(74);
// 			}
// //			else
// 			{
// 				if (m_FightTarget[m_UserID] == -1)
// 				{
// 					int start, end;
// 					if (m_UserID < 10)start = 10;
// 					else start = 0;
// 					end = start + 10;
// 					SetTarget(FindDefminTarget(start,end,eProPerty气血,TRUE));
// 				}
// 				if (m_pTargetPetData->m_HP > m_pUserPetData->m_LV * 200)
// 					return UseMagic(71);
// 				else
// 				{
// 					m_bSeal[m_TargetID] = TRUE;
// 					return UseMagic(68);
// 				}
// 			}
// 		}
// 	}
// 	if (!m_pUserPetData->m_FightProperty.cannotMagic)
// 	{
// // 		if (m_pUserPetData->m_AddPoint.atk > 2)//力天宫
// // 		{
// // 			if (m_FightTarget[m_UserID] == -1)
// // 				SetTarget(FindAtkTarget(100));
// // 			return NormalAtk();
// // 
// // 		}
// 
// 		if (m_pUserPetData->m_ProPertyMag >= m_pUserPetData->m_LV * 2)//力天宫
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(FindAtkTarget(130));
// 			return  UseMagic(74);
// 		}
// 	}
// 	defense(m_UserID);
}
void cAttackAI::RunWZ()
{	
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
	auto runYanyujianfa = [&]()
	{
		if (m_pUserPetData->m_HP > m_pUserPetData->m_HPMax.GetData() / 10)
		{
			if (m_TargetID < 0)
			{
//				SetTarget(FindDefminTarget(eProPerty防御, false));
				SetTarget(FindAtkTarget(200, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(97);
				return true;
			}
		}
		return false;
	};

	auto runPiaomiaoshi = [&]()
	{
		if (m_TargetID < 0)
		{
//			SetTarget(FindDefminTarget(eProPerty防御, false));
			SetTarget(FindAtkTarget(100, TRUE, m_UserID));
		}
		if (m_TargetID >= 0)
		{
			UseMagic(98);
			return true;
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			else
			{
				isM = 0;
			}
			if (m_TargetID >= 0 && isM >= 0)
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(89);
			}
		}
	}
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		int n = getVisibleNO();
		if (m_TargetID >= 0 || n < 3 || (m_UserID >= 10 && rand() % 100 < 30))
		{
			if (runYanyujianfa())
			{
				return;
			}
			
		}
		if (runPiaomiaoshi())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
	
// 		m_bSeal[m_TargetID] = TRUE;
// 		if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 2)//是不是剑五庄
// 		{
// 			int n = g_pMainState->GetLiveNum(m_UserID < 10 ? 10 : 0, m_UserID < 10 ? 20 : 10);
// 			if (n > 2 || (n <= 2 && (rand() & n) > 0))
// 			{
// 				SetTarget(FindDefminTarget(m_UserID < 10 ? 10 : 0, m_UserID < 10 ? 20 : 10, eProPerty气血, TRUE));
// 				return UseMagic(98);
// 			}
// 			else if (m_pUserPetData->m_HP > m_pUserPetData->m_HPMax.GetData() * 50 / 100)
// 			{//烟雨
// 				if (m_TargetID == -1)SetTarget(FindAtkTarget(200));
// 				if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 				if (m_pTargetPetData->m_HP < m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData())
// 					return NormalAtk();
// 				return UseMagic(97);
// 			}
// 			else
// 			{
// 				//生命之泉
// 				if (m_pUser->CheckHaveState(91))
// 				{
// 					SetTarget(m_UserID);
// 					return UseMagic(91);
// 				}
// 				else return NormalAtk();
// 			}
// 		}
// 		if (m_TargetID == -1)
// 		{
// 			int start, end;
// 			if (m_UserID < 10)start = 11;
// 			else start = 1;
// 			end = start + 9;
// 			if (m_bPKMode)//日光乾坤在非PK时无法封主怪
// 			{
// 				start -= 1;
// 				end -= 5;
// 			}
// 			int target2= FindUnSeal(start, end);
// 			if (target2 == -1)
// 			{
// 				SetTarget(m_UserID);
// 				if (m_pUser->CheckHaveState(91))return UseMagic(91);
// 				SetTarget(FindAtkTarget(200));
// 				if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 				if (m_pTargetPetData->m_HP < m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData())
// 					return NormalAtk();
// 				return UseMagic(97);
// 			}
// 			SetTarget(target2);
// 		}
// 		m_bSeal[m_TargetID] = TRUE;
// 		return UseMagic(89);//日月
// 	}
// 	
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 		if (m_pUserPetData->m_AddPoint.atk > 2)
// 		{
// 			if (m_TargetID == -1)SetTarget(FindAtkTarget(100));
// 			return NormalAtk();
// 		}
// 	}
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
// 	{
// 		if (CheckItem(eAIUseItemTypeHP)){ UseItem(eAIUseItemTypeHP); return; }
// 	}
// 	return defense(m_UserID);

}
void cAttackAI::RunPT()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
// 	}
// 	else SetTarget(-1);
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 	}
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
// 	{
// 	}

	auto runWuxing = [&]()
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0)
		{
			UseMagic(105 + rand() % 5);
			return true;
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
	}
	int self = m_UserID < 10 ? 10 : 0;
	if (!isAtkMode() && isCanMag())
	{
		vector<POINT> outMself;
		FindEnemy(TRUE, FALSE, outMself, eET可法系, self);

		vector<POINT> outMuser;
		FindEnemy(TRUE, FALSE, outMuser, eET可法系, m_UserID);

		vector<POINT> outLd;
		int rr = FindEnemy(TRUE, FALSE, outLd, eET上灵动112, m_UserID, 112);
		auto out2 = check隐身(outLd, m_UserID);
// 		if (out2.size() < rr)
// 		{
// 			rr = out2.size();
// 		}

		if (outMself.size() > 2 || outMuser.size()/* || rr > 2*/)
		{
			if (out2.size())
			{
				SetTarget(out2.front());
				return UseMagic(112);
			}
		}

		vector<POINT> out;
		FindEnemy(TRUE, FALSE, out, eET颠倒五行113, m_UserID, 113);
		auto out3 = check隐身(out, m_UserID);
		if (out3.size() && outMself.size())
		{
			SetTarget(out3.front());
			return UseMagic(113);
		}

		if (out2.size())
		{
			SetTarget(out2.front());
			return UseMagic(112);
		}
		if (runWuxing())
		{
			return;
		}
	}	
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runWuxing())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}
}
void cAttackAI::RunDF()
{
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
	int tOld = m_TargetID;
// 	}
// 	else SetTarget(-1);
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill)
// 	{
// 		if ((!m_pUserPetData->m_FightProperty.cannotSkill) && m_pUserPetData->m_AiLv > 90)
// 		{
// 			if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 2)//力地府
// 			{
// 				if (CheckCanSkill(3034))
// 				{
// 					if (m_FightTarget[m_UserID] == -1)
// 						SetTarget(FindAtkTarget(200));
// 					return UseMagic(3034);
// 				}
// 			}
// 		}
// 	}
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 		if (m_pUserPetData->m_AddPoint.atk > 2)//力地府
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(FindAtkTarget(150));
// 			return NormalAtk();
// 		}
// 	}

	auto runYanluoling = [&]()
	{
		if (m_TargetID < 0)
		{
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		}
		if (m_TargetID >= 0)
		{
			UseMagic(getVisibleNO() > 1 ? 116 : 117);
			return true;
		}
		return false;
	};

	int self = m_UserID < 10 ? 10 : 0;

	auto runGuiyan = [&](int n)
	{
		vector<POINT> outMself;
		FindEnemy(TRUE, FALSE, outMself, eET速度最快2, self);
		auto out2 = check隐身(outMself, m_UserID);
		if (outMself.size() != out2.size())
		{
			FindEnemy(TRUE, FALSE, outMself, eET鬼眼120, m_UserID);
			if (outMself.size() > n)
			{
				SetTarget(outMself.front().x);
				UseMagic(120);
				return true;
			}
		}
		return false;
	};

	auto runGuiyanSeal = [&](int n)
	{
		vector<POINT> outMself;
		FindEnemy(TRUE, FALSE, outMself, eET可封系, self);
		auto out2 = check隐身(outMself, m_UserID);
		if (out2.size() > 1)
		{
			FindEnemy(TRUE, FALSE, outMself, eET鬼眼120, m_UserID);
			if (outMself.size() > n)
			{
				SetTarget(outMself.front().x);
				UseMagic(120);
				return true;
			}
		}
		return false;
	};

	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			if (runGuiyanSeal(5))
			{
				return;
			}

			if (runGuiyan(5))
			{
				return;
			}

			// 		int yinshen = 0;
			// 		//		int guiyan = 0;
			// 		int star = m_UserID < 10 ? 10 : 0;
			// 		for (int i = star; i < star + 10; ++i)
			// 		{
			// 			if (!g_pMainState->m_FightList[i].isExist || g_pMainState->m_FightList[i].CheckDie())
			// 			{
			// 				continue;
			// 			}
			// 			cPetData *data = nullptr;
			// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
			// 			if (!data)
			// 			{
			// 				continue;
			// 			}
			// 			if (data->PeopleSpecial.d2 > 0)
			// 			{
			// 				++yinshen;
			// 			}
			// 		}
			// 		int star = m_UserID < 10 ? 0 : 10;
			// 		for (int i = star; i < star + 10; ++i)
			// 		{
			// 			if (!g_pMainState->m_FightList[i].isExist || g_pMainState->m_FightList[i].CheckDie())
			// 			{
			// 				continue;
			// 			}
			// 			cPetData *data = nullptr;
			// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
			// 			if (!data)
			// 			{
			// 				continue;
			// 			}
			// 			if (data->PeopleSpecial.d1 > 0)
			// 			{
			// 				++guiyan;
			// 			}
			// 		}
			// 		if (yinshen > 0 && !m_pUserPetData->PeopleSpecial.d1)
			// 		{
			// 			SetTarget(m_UserID);
			// 			return UseMagic(120);
			// 		}

			if (m_TargetID < 0)
			{
				vector<POINT> out;
				int rr = FindEnemy(TRUE, FALSE, out, eET魂飞魄散127, self);
				auto out2 = check隐身(out, m_UserID);
				if (rr > 0 && out2.size())
				{
					SetTarget(out2.front());
					return UseMagic(127);
				}

				FindEnemy(TRUE, FALSE, out, eET锢魂术129, self);
				out2 = check隐身(out, m_UserID);
				if (out2.size())
				{
					SetTarget(out2.front());
					return UseMagic(129);
				}

				if (runGuiyanSeal(1))
				{
					return;
				}
				if (runGuiyan(1))
				{
					return;
				}

				FindEnemy(TRUE, FALSE, out, eET黄泉之息126, self, 126);
				out2 = check隐身(out, m_UserID);
				if (out2.size() > 3)
				{
					SetTarget(out2.front());
					return UseMagic(126);
				}
			}
		}
	}
	int told = m_TargetID;
	m_TargetID = tOld;
	if (isPutRate() && selectAtk())
	{
		return;
	}
	m_TargetID = told;
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (isCanMag())
	{
		if (runYanluoling())
		{
			return;
		}
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}

// 		int start, end;
// 		if (m_TargetID<10)start = 0;
// 		else start = 10;
// 		end = start + 10;
// 		if (g_pMainState->GetLiveNum(start, end) > 1)
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			return UseMagic(116);
// 		}
// 		else
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			UseMagic(117);
// 		}
// 	}
// 
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotSkill && m_pUserPetData->m_ProPertyAtk > m_pUserPetData->m_LV * 2)
// 	{
// 		if (CheckCanSkill(3034))
// 		{
// 			if (m_TargetID < 0)
// 			{
// 				SetTarget(FindAtkTarget(300, TRUE, m_UserID));
// 				if (m_TargetID >= 0)
// 				{
// 					return UseMagic(3034);
// 				}
// 			}
// 		}
// 	}
// 
// 	if (!m_pUserPetData->m_FightProperty.cannotAttack)
// 	{
// 		if (m_TargetID < 0)
// 		{
// 			SetTarget(FindAtkTarget(100, TRUE, m_UserID));
// 			if (m_TargetID >= 0)
// 			{
// 				return NormalAtk();
// 			}
// 		}
// 	}
// 
// 	if (m_pUserPetData->m_FightProperty.cannotMagic &&
// 	return defense(m_UserID);
}
void cAttackAI::RunPS()
{
// 	BOOL bConduct = FALSE;
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
 	SetTarget(m_FightTarget[m_UserID]);
	int tOld = m_TargetID;
// 		bConduct = TRUE;
// 	}
// 	else SetTarget(-1);

	auto runTianluodiwang = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(162);
				return true;
			}
		}
		return false;
	};

	auto runGouhun = [&]()
	{
		if (m_pUserPetData->m_HP * 100 / m_pUserPetData->m_HPHurtMax < 60)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindDefminTarget(eProPerty气血, true));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(154);
				return true;
			}
		}
		return false;
	};

	int self = m_UserID < 10 ? 10 : 0;
	if (!isAtkMode())
	{
		if (isCanSpec() && RunLH())
		{
			return;
		}
		if (isCanMag())
		{
			if (m_TargetID < 0)
			{
				vector<POINT> outMself;
				FindEnemy(TRUE, FALSE, outMself, eET可法系, self);
				if (outMself.size() > 2 && isUseOtherRate() &&
					!m_pUser->CheckHaveState(166) &&
					!m_pUser->CheckHaveState(2097) &&
					!m_pUser->CheckHaveState(3024) &&
					!m_pUser->CheckHaveState(3025))
				{
					SetTarget(m_UserID);
					return UseMagic(166);
				}
			}

			char isM = -1;
			if (m_TargetID < 0 || (m_TargetID >= 0 && !FindUnSeal(m_TargetID, isM)))
			{
				SetTarget(FindUnSeal(isM));
			}
			if (m_TargetID >= 0 && (isM == 0 || isM == 1))
			{
				m_bSeal[m_TargetID] = TRUE;
				return UseMagic(159);
			}

			//		if (m_pUser->CheckHaveState(166))
			// 		{
			// 
			// 		}
			// 		if (m_pUserPetData->m_LV >= 120)
			// 		{
			// 			SetTarget(m_UserID);
			// 			return UseMagic(166);
			// 		}

			vector<POINT> outMself;
			FindEnemy(TRUE, FALSE, outMself, eET锢魂术129, self);
			auto out2 = check隐身(outMself, m_UserID);
			if (out2.size())
			{
				SetTarget(out2.front());
				return UseMagic(156);
			}

			if (runGouhun())
			{
				return;
			}

			if (m_TargetID < 0)
			{
				vector<POINT> outMself;
				FindEnemy(TRUE, FALSE, outMself, eET可物理系, self);
				if (outMself.size() > 2 && !m_pUser->CheckHaveState(160))
				{
					SetTarget(m_UserID);
					return UseMagic(160);
				}
			}
		}

		// 		if ((m_pUserPetData->m_MP * 100 / m_pUserPetData->m_MPMax.GetData() < 5) || (m_pUserPetData->m_MP < 80))
		// 		{
		// 			if (m_TargetID < 0)
		// 			{
		// 				SetTarget(FindDefminTarget(eProPerty魔法, true));
		// 			}
		// 			if (m_TargetID >= 0)
		// 			{
		// 				return UseMagic(155);
		// 			}
		// 		}


	}

	int told = m_TargetID;
	m_TargetID = tOld;
	if (isPutRate() && selectAtk())
	{
		return;
	}
	m_TargetID = told;
	int t = m_TargetID;
	if (RunPet() == 3 && isPetRate())
	{
		return;
	}
	m_TargetID = t;

	if (isCanMag() && runGouhun())
	{
		return;
	}

	if (runTianluodiwang())
	{
		return;
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}

// 	BOOL bCanMagic, bCanAtk,bCanSkill;
// 	bCanMagic = !m_pUserPetData->m_FightProperty.cannotMagic;
// 	bCanAtk = !m_pUserPetData->m_FightProperty.cannotAttack;
// 	bCanSkill = !m_pUserPetData->m_FightProperty.cannotSkill;
// 	if (m_pUserPetData->m_ProPertyAtk >= m_pUserPetData->m_LV * 2)//力盘丝
// 	{
// 		if (m_FightTarget[m_UserID] == -1)
// 			SetTarget(FindAtkTarget(150));
// 		if (bCanAtk)
// 		{
// 			if(!bCanMagic)return NormalAtk();
// 			if (m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData() > m_pUserPetData->m_LV * 5)
// 				return NormalAtk();
// 			else
// 				return UseMagic(162); //天罗地网
// 		}
// 		else
// 		{
// 			if (bCanMagic)UseMagic(162); //天罗地网
// 		}
// 		
// 	}
// 
// 	if (bCanMagic)
// 	{//可以使用魔法的情况下
// 		if (bConduct)
// 		{//玩家指定目标的情况下并且目标没有被封 尝试封印目标
// 			if (!m_bSeal[m_TargetID])
// 			{
// 				if (!m_pTargetPetData->m_FightProperty.cannotMagic)
// 				{
// 					m_bSeal[m_TargetID] = TRUE;
// 					return UseMagic(159);
// 				}
// 
// 			}
// 			else
// 			{
// 				if (!m_bPKMode)
// 					return UseMagic(162); //天罗地网
// 				else
// 					return UseMagic(155);//打蓝
// 			}
// 		}
// 		if (!m_bPKMode)
// 		{
// 			if (m_FightTarget[m_UserID] == -1)
// 				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			return UseMagic(162); //天罗地网
// 		}
// 		//PK
// 		if (m_FightTarget[m_UserID] == -1)
// 		{
// 			int unsealtarget = FindUnSeal(5);
// 			if (unsealtarget == -1)
// 			{//所有的敌人都被封了?
// 				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4));
// 			}
// 			else
// 			{
// 				SetTarget(unsealtarget);
// 				return UseMagic(159);
// 			}
// 		}
//	}
//	return defense(m_UserID);
}
void cAttackAI::RunMW()
{
	if (!isAtkMode() && isCanSpec() && RunLH())
	{
		return;
	}
	int t = m_TargetID;
	if (RunPet() == 4 && isPetRate())
	{
		return;
	}
	m_TargetID = t;
	if (m_FightTarget[m_UserID] > -1)
	{
		SetTarget(m_FightTarget[m_UserID]);
	}
	else SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));

	int self = m_UserID < 10 ? 10 : 0;
	if (!m_pUserPetData->m_FightProperty.cannotMagic)
	{
		if (!m_pUserPetData->PeopleSpecial.d1)
		{
			vector<POINT> outMself;
			FindEnemy(TRUE, FALSE, outMself, eET速度最快2, self);
			auto out2 = check隐身(outMself, m_UserID);
			if (outMself.size() != out2.size())
			{
				if (out2.size() < 3)
				{
					SetTarget(m_UserID);
					return UseMagic(133);
				}
			}
		}
		return UseMagic((getVisibleNO() <= 1 || (m_UserID >= 10 && rand() % 100 < 20)) ? 132 : 131);
	}
	if (!runSelfunseal())
	{
		Def(m_UserID);
	}


// 	int start, end;
// 	if (m_UserID<10)start = 10;
// 	else start = 0;
// 	end = start + 10;
// 	if (g_pMainState->GetLiveNum(start, end) > 1)
// 	{//飞砂走石	
// 		return UseMagic(131);
// 	}
// 	else
// 	{//三味真火
// 		return UseMagic(132);
// 	}
}
void cAttackAI::RunST()
{
	if (!isAtkMode() && isCanSpec() && RunLH())
	{
		return;
	}
	SetTarget(m_FightTarget[m_UserID]);

	auto get145Times = [&]()
	{
		for (list<sBuff>::iterator it = m_pUser->m_StateList.begin(); it != m_pUser->m_StateList.end(); it++)
		{
			if (it->ID == 145)
				return it->times;
		}
		return -1;
	};

	auto isYingji = [&]()
	{
		int n = getVisibleNO();
		return n > 3 || (n == 3 && rand() % 100 < 35);
	};
		

	auto runYingji = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(100, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(142);
				return true;
			}
		}
		return false;
	};

	auto runShibo = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(250, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(143);
				return true;
			}
		}
		return false;
	};

	auto runLianhuanji = [&]()
	{
		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(500, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(148);
				return true;
			}
		}
		return false;
	};

	int t = get145Times();
	if (m_TargetID >= 0 && t >= 0 && runLianhuanji())
	{
		return;
	}
	if (MyTest::getInstance()->isAtkMode(m_UserID))
	{
		if (t >= 0 && m_UserID >= 10 && rand() % 100 < 30 && runLianhuanji())
		{
			return;
		}
	}

	if (t >= 0 && isYingji() && runYingji())
	{
		return;
	}
	if (t >= 0)
	{
		if (t > 0 && runShibo())
		{
			return;
		}
		else if (t == 0 && runLianhuanji())
		{
			return;
		}
	}
	if (!m_pUserPetData->m_FightProperty.cannotSkill)
	{
		if (CheckCanSkill(3034))
		{
			if (m_TargetID < 0)
			{
				SetTarget(FindAtkTarget(300, TRUE, m_UserID));
			}
			if (m_TargetID >= 0)
			{
				return UseMagic(3034);
			}
		}
	}
	if(!m_pUserPetData->m_FightProperty.cannotMagic)
	{
		SetTarget(m_UserID);
		return UseMagic(145);
	}

	if (!m_pUserPetData->m_FightProperty.cannotAttack)
	{
		if (m_TargetID < 0)
		{
			SetTarget(FindAtkTarget(100, TRUE, m_UserID));
		}
		if (m_TargetID >= 0)
		{
			return NormalAtk();
		}
	}

	if (!m_pUser->CheckHaveState(142)/* && !m_pUser->CheckHaveState(148)*/)
	{
		return Def(m_UserID);
	}
}


void cAttackAI::UseMagic(int id)
{
	if (m_TargetID == -1)return;
	sFightList& list = g_pMainState->m_FightList[m_UserID];
	list.m_WorkType = WORKTYPE_MAGIC;
// 	list.m_SkillSelect.Lv = m_pUserPetData->m_LV + m_pUserPetData->m_StrongLv/5-10;
// 	if (list.m_SkillSelect.Lv < 0)list.m_SkillSelect.Lv = 0;
// 	if (list.m_SkillSelect.Lv>180)list.m_SkillSelect.Lv = 180;
	list.m_SkillSelect.Lv = list.m_pData->GetSkillLv(0);
	list.m_SkillSelect.SkillID = id;
	list.m_SkillSelect.TargetID = m_TargetID;
}

void cAttackAI::NormalAtk()
{
	sFightList& list = g_pMainState->m_FightList[m_UserID];
	list.m_WorkType = WORKTYPE_ATTACK;
	list.m_SkillSelect.Lv = 0;
	list.m_SkillSelect.SkillID = 1000;
	list.m_SkillSelect.TargetID = m_TargetID;
}

void cAttackAI::ResetNeed()
{
	for (int i = 0; i < 20; i++)
	{
		m_bNeedUnSeal[i] = 0;
		m_bNeedAddHp[i] = 0;
		m_bNeedAddMp[i] = 0;
		m_bNeedlive[i] = 0;
		m_bNeedAddHpHurt[i] = 0;
	}
}

// 无视+2
BOOL cAttackAI::SaveOneself(int start,int end)
{
	for (int i = start; i < end; i++)
	{
		if (i == g_pMainState->m_HeroID)continue;
		SaveOneself2(i);
	}
	return FALSE;
}
void cAttackAI::SaveOneself2(int i)
{
	if (!g_pMainState->m_FightList[i].isLive)return;
	if (g_pMainState->m_FightList[i].CheckDie())return;
	if (g_pMainState->m_FightList[i].m_WorkType != -1)return;
	SetUser(i);
	SetTarget(i);
	if (m_pUserPc)
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
		//		if (m_pUserPetData->m_StrongLv > 90 - 50)
			{
				if (m_bNeedAddHp[i] > 0 || m_bNeedAddHpHurt[i] > 0)
				{
					if (CheckCanSkill(3006))
					{
						m_bNeedAddHp[i] = FALSE;
						m_bNeedAddHpHurt[i] = FALSE;
						return UseMagic(3006);//命归
					}
				}
				if (m_bNeedAddMp[i])
				{
					if (CheckCanSkill(3004))
					{
						m_bNeedAddMp[i] = FALSE;
						return UseMagic(3004);//凝神诀  
					}
				}
			}
		//		else
		//		if (m_pUserPetData->m_StrongLv > 50)
		{
			if (m_bNeedAddHp[i] || m_bNeedAddHpHurt[i])
			{
				if (CheckCanSkill(3005))
				{
					m_bNeedAddHp[i] = FALSE;
					m_bNeedAddHpHurt[i] = FALSE;
					return UseMagic(3005);//气归

				}
			}
			if (m_bNeedAddMp[i])
			{
				if (CheckCanSkill(3003))
				{
					m_bNeedAddMp[i] = FALSE;
					return UseMagic(3003);//凝气诀
				}
			}
		}
		}
	if (m_pUserPetData->m_FightProperty.cannotUseItem)return;
	if (m_bNeedAddHpHurt[i])
	{
		if (CheckItem(eAIUseItemTypeHPHurt))
		{
			UseItem(eAIUseItemTypeHPHurt);
		}
		return;
	}
	if (m_bNeedAddHp[i])
	{
		if (CheckItem(eAIUseItemTypeHP))
		{
			UseItem(eAIUseItemTypeHP);
		}
		return;
	}
	if (m_bNeedUnSeal[i])
	{
		if (CheckItem(eAIUseItemTypeUnseal))
			UseItem(eAIUseItemTypeUnseal);//解封
		return;
	}
	if (m_bNeedAddMp[i])
	{
		if (CheckItem(eAIUseItemTypeMP))
			UseItem(eAIUseItemTypeMP);
		return;
	}
}


void cAttackAI::GetNeed(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (!g_pMainState->m_FightList[i].isLive)continue;
		SetUser(i);
		//死亡
		if (m_pUserPetData->m_HP == 0)
		{
			if (!m_pUserPetData->m_FightProperty.cannotLive)
			{
				m_bNeedlive[i] = TRUE;
			}
		}
		int limit = m_pUserPc ? m_HPLimit : m_HPLimit / 2 + 50;
		//血不够
		if (m_pUserPetData->m_HP < (m_pUserPetData->m_HPMax.GetData() * limit) / 100)
		{
			//血低,越需要加血
			int k = (m_pUserPetData->m_HP * 100) / m_pUserPetData->m_HPMax.GetData() + 1;
			k = k * limit / m_HPLimit;
			k = 100 - k;
			if (m_pUserPetData->m_HPHurtMax < m_pUserPetData->m_HPMax.GetData())

				m_bNeedAddHpHurt[i] = TRUE;

			m_bNeedAddHp[i] = k;
	
			if (m_pUserPc && m_pUserPetData->m_FightProperty.cannotAddHP)//禁疗也算封
			{
				m_bNeedUnSeal[i] = TRUE;
			}
		}

		m_bNeedAddMp[i] = TRUE;
		vector<int> ms, m2s, ps, bs;
		isHadPetSkill(m_pUserPetData, bs, ps, ms, m2s);
		if (m_pUserPetData->m_LiveMpLv || (!m_pUserPc && !bs.size() && !ps.size() && !ms.size() && !m2s.size()))
		{
			m_bNeedAddMp[i] = FALSE;
		}
		else if (m_pUserPetData->m_MP >= m_pUserPetData->m_LV + 10 ||
			m_pUserPetData->m_MP >= m_pUserPetData->m_MPMax.GetData() - 30)
		{
			m_bNeedAddMp[i] = FALSE;
		}
		else if (m_pUserPc && !m_pUserPc->m_PCData.m_MengPaiID)
		{
// 			m_bNeedAddMp[i] = (m_pUserPetData->m_MP * 100) / m_pUserPetData->m_MPMax.GetData();
// 			m_bNeedAddMp[i] = 100 - m_bNeedAddMp[i];
			m_bNeedAddMp[i] = FALSE;
		}
		if (m_pUser->CheckHaveState(6))	
		{
			//中了反间
			m_bNeedUnSeal[i] = TRUE;
		}
		if (m_pUserPetData->m_FightProperty.cannotMagic)//不能使用魔法
		{
			if (!m_pUser->m_StateList.size())
			{
				continue;
			}
			if (m_pUser->m_StateList.back().times < 3)
			{
				continue;//3回合以下的BUFF不用管
			}
			if (i % 10 > 4)
			{
				if (m_pUserPetData->m_ProPertyHP >= m_pUserPetData->m_LV * 3)
				{
					continue;//血宠不用救
				}
				if (m_pUserPetData->m_ProPertyAtk > m_pUserPetData->m_LV)
				{
					continue;//攻宠封法不要紧
				}
			}
			m_bNeedUnSeal[i] = TRUE;
		}
		
		if (m_pUserPetData->m_FightProperty.cannotAttack)//不能攻击
		{
			if (!m_pUser->m_StateList.size())
			{
				continue;
			}
			if (m_pUser->m_StateList.back().times < 3)
			{
				continue;//3回合以下的BUFF不用管
			}
			if (!m_pUserPc)
			{
				if (m_pUserPetData->m_ProPertyAtk > m_pUserPetData->m_LV)
				{
					if (!ps.size())
					{
						m_bNeedUnSeal[i] = TRUE;
					}					
				}
			}
		}
		if (m_pUserPetData->m_FightProperty.cannotSkill)//不能
		{
			if (m_pUserPc && m_pUserPetData->m_CP > 80)
			{
				m_bNeedUnSeal[i] = TRUE;
			}
		}

		if (m_pUserPetData->PeopleSpecial.d2 || 
			m_pUserPetData->restoreRate ||
			m_pUser->CheckHaveState(0) ||
			m_pUser->CheckHaveState(7) ||
			m_pUser->CheckHaveState(142))
		{
			m_bNeedUnSeal[i] = FALSE;
		}

// 		if (m_bNeedlive[i])
// 		{
// 			m_bNeedUnSeal[i] = FALSE;
// 			m_bNeedAddHp[i] = FALSE;
// 			m_bNeedAddHpHurt[i] = FALSE;
// 			m_bNeedAddMp[i] = FALSE;
// 		}
	}
}

void cAttackAI::SetTarget(int target)
{
	if (m_TargetID == target)return;
	m_TargetID = target;
	if (target < 0)
	{
		m_pTarget = nullptr;
		m_pTargetPetData = nullptr;
		return;
	}
	if (!g_pMainState->m_FightList[target].isLive)
	{
		m_TargetID = -1;
		m_pTarget = nullptr;
		m_pTargetPetData = nullptr;
		return;
	}
	m_pTargetList = &g_pMainState->m_FightList[m_TargetID];
	m_pTarget= g_pMainState->m_FightList[m_TargetID].m_pData;
	m_pTarget->GetDateP(m_pTargetPetData);
	if (0 == m_pTargetPetData)
	{
		ERRBOX(target);
	}
}

void cAttackAI::SetUser(int userid)
{
	if (m_UserID == userid)return;
	m_UserID = userid;
	pUserList = &g_pMainState->m_FightList[userid];
	m_pUser = g_pMainState->m_FightList[userid].m_pData;
	if (m_pUser->m_IndexType==INDEXTYEP_CHARACTER)
		m_pUserPc=(cCharacter*)m_pUser->m_pIndex;
	else m_pUserPc = 0;
	m_pUser->GetDateP(m_pUserPetData);
} 

void cAttackAI::Run()
{
//	Reset();
//	GetNeed(0, 20);
	for (int i = 0; i < 10; i++)
	{
		break;
		if ((i%5)==g_pMainState->m_HeroID)
		{
			if (g_pMainState->m_FightList[i].isLive)
			{
				SetUser(i);
				if (m_pUserPc)
				{
					if (pUserList->m_WorkType == WORKTYPE_MAGIC)
					{
						//检测主角 封印
						if (pUserList->m_SkillSelect.TargetID > 9)
						{
							m_bNeedUnSeal[pUserList->m_SkillSelect.TargetID] = TRUE;
						}
						else
						{
							m_bNeedAddHp[pUserList->m_SkillSelect.TargetID] -= 50;
						}
					}
				}
				if (pUserList->m_WorkType == WORKTYPE_ITEM)
				{	//检测主角加血
					if (pUserList->m_SkillSelect.TargetID < 10)
					{
					//	sItem2* pItem = &m_pUserPc->m_PCData.m_Item[pUserList->m_ItemSelectID];
						m_bNeedAddHp[pUserList->m_SkillSelect.TargetID] -= 20;
					}
				}
			}
		}
	}
//	ZhiHui(FALSE);
//	ZhiHui(TRUE);
// 	PreRun(0,10);
// 	if (m_bPKMode)
// 	{
// 		ZhiHui(FALSE);
// 	}
// 
// 
// 	for (int i = 0; i < 10; i++)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		if (g_pMainState->m_FightList[i].isExist)
// 		if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			AutoRunAi(i);
// 		}
// 	}
//	if (m_bPKMode)
// 	{
// 		for (int i = 10; i < 20; i++)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			if (g_pMainState->m_FightList[i].isExist)
// 			if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 			{
// 				g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 				AutoRunAi(i);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		for (int i = 10; i < 20; i++)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			if (g_pMainState->m_FightList[i].isExist)
// 			if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 			{
// 				g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 				AutoRunEnemyAi(i);
// 			}
// 		}
// 	}



// 	vector<POINT>out;
// 	FindEnemy(FALSE, TRUE, out, eET速度最快, 10);
// 	forv(out, i)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		AutoRunAi(out[i].x);
// 	}
// 	out.clear();
// 	FindEnemy(FALSE, TRUE, out, eET速度最快, 0);
// 	forv(out, i)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		AutoRunAi(out[i].x);
// 	}


	for (int i = 0; i < 20; i++)
	{
//		m_FightTarget[i] = -1;
		m_bSeal[i] = FALSE;
		m_bAtk[i] = 0;
	}
}


// 无视
void cAttackAI::PreRun(int start, int end)
{
	//CoutIdleList(start,end);
	GetNeed(start, end);
	ContentLive(start,end);
	ContentHP(start, end);
	ContentUnSeal(start, end);
	SaveOneself(start, end);
}

void cAttackAI::AutoRunAi(int i)
{
	SetUser(i);	
	if (getVisibleNO() < 1)
	{
		return Def(m_UserID);
	}
	if (!m_pUserPc)//召唤兽
	{
		if (g_pMainState->m_FightList[m_UserID].isLive)
		{
			if (!RunPet())
			{
				Def(i);
			}
		}
		return;
	}
// 	if (m_pUserPetData->m_LV < 25)
// 	{
// 		if (m_FightTarget[m_UserID] > -1)
// 		{
// 			SetTarget(m_FightTarget[m_UserID]);
// 		}
// 		else
// 		{
// 			SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true));
// 			if (m_TargetID < 0)
// 			{
// 				SetTarget(g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, false));
// 			}
// 		}
// 		return	NormalAtk();
// 	}
	

	eMengPai emngpaiid = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
	switch (emngpaiid)
	{
	case eMP_大唐官府:return RunDT();
	case eMP_方寸山:return RunFC();
	case eMP_化生寺:return RunHS();	
	case eMP_女儿村:return RunNR();	
	case eMP_天宫:return RunTG();
	case eMP_东海龙宫:return RunLG();
	case eMP_五庄观:return RunWZ();
	case eMP_普陀山:return RunPT();
	case eMP_阴曹地府:return RunDF();
	case eMP_魔王寨:return RunMW();
	case eMP_狮驼岭:return RunST();
	case eMP_盘丝岭:return RunPS();
	default:
		break;
	}
}

void cAttackAI::AutoRunEnemyAi(int i)
{
	vector<POINT> tlist;
	SetUser(i);
	if (m_pUserPetData->m_FightProperty.cannotAll)return;
	if (m_FightTarget[i] > -1)
	{
		SetTarget(m_FightTarget[i]);
	}
	else
		SetTarget(g_pMainState->m_AI.AutoFindTarget(i, 4, true));
	
//	int ailv = m_pUserPetData->m_AiLv;
	if (m_pUserPetData->m_FightProperty.cannotMagic)//被封法术时用物理
	{
		return NormalAtk();
	}
	if (!m_pUserPc)//召唤兽
	{
		vector<int> skilllist;
		//寻找召唤兽的主动技能
		for (int j = 0; j < m_pUserPetData->m_NumofBBSkill; j++)
		{
			if (m_pUserPetData->m_pPetSkill[j]->m_SkillType == 4)
			{
				skilllist.push_back(m_pUserPetData->m_pPetSkill[j]->m_Id);
			}
		}
		if (skilllist.size())
		{//随便用
			int skilluse = 2000 + skilllist[rand() % skilllist.size()];
			if (CheckCanSkill(skilluse))
				return UseMagic(skilluse);
		}
		return	NormalAtk();
	}
	eMengPai emngpaiid = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
	if (m_pUserPetData->m_FightProperty.cannotMagic)
	{
		switch (emngpaiid)
		{
		case eMP_女儿村:
			if (!m_pUserPetData->m_FightProperty.cannotUseItem)
			 UseItem(eAIUseItemType暗器);
			else NormalAtk();
			return;
		default:
			NormalAtk();
			return;
		}
	}
	switch (emngpaiid)
	{
	case eMP_大唐官府:
			switch (rand() % 7)
			{
			case 0:return NormalAtk();
			case 1:
				if (m_pUserPetData->m_HP<5000)
				{
					if (m_pUserPetData->m_LV > 129)
					{
						return NpcTryMagic(7);
					}
				}
				if (m_pUserPetData->m_FightProperty.cannotAttack)return NpcTryMagic(0);
				return NormalAtk();
				break;
			case 2:return NpcTryMagic(1);
			case 3:
				if (!CheckHaveState(i, 4))
				{
					if (CheckCanSkill(4))
					{
						SetTarget(i);
						return UseMagic(4);
					}
					else
						return NormalAtk();
				}
				else
				{
					if (m_pUserPetData->m_FightProperty.cannotAttack)return NpcTryMagic(0);
					return NormalAtk();
				}
			case 4:return NpcTryMagic(6);
			default:return NpcTryMagic(0);
			}
			break;
	case eMP_方寸山:
		switch (rand() % 4)
		{
		case 0:
			if (m_pUserPetData->m_FightProperty.cannotAttack)
			{
				return NpcTryMagic(11);
			}
			else
			return NormalAtk();
		case 1:
			if (1)
			{
				int start, end;
				if (m_UserID < 10)start = 10;
				else start = 0;
				end = start + 10;
				int target2 = FindUnSeal(start, end);
				if (target2 == -1)return NormalAtk();
				SetTarget(target2);
				m_bSeal[m_TargetID] = TRUE;
				switch (rand() % 5)
				{
				case 1:return NpcTryMagic(14);
				case 2:return NpcTryMagic(15);
				case 3:return NpcTryMagic(19);
				case 4:return NpcTryMagic(20);
				default:return NpcTryMagic(21);
				}
			}
		default:return NpcTryMagic(11);
		}
		break;
	case eMP_化生寺:
			switch (rand() % 7)
			{
			case 0:
				return UseMagic(31);
			case 1:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(40);
				}
				else
				return NormalAtk();
			case 2:
				if (1)
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					switch (rand() % 5)
					{
					case 0: return NpcTryMagic(42);
					case 1:return NpcTryMagic(33);
					case 2: return NpcTryMagic(35);
					case 3: return NpcTryMagic(39);
					case 4: return NpcTryMagic(40);
					}
				}
				break;
			default:
				SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
				if (rand() % 2)return NpcTryMagic(40);
				else  return NpcTryMagic(42);
			}
			break;
	case eMP_女儿村:
			switch (rand() % 4)
			{
			case 0:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					 UseItem(eAIUseItemType暗器);
					 return;
				}
				else
				return NormalAtk();
			case 1:
				if (1)
				{
					int start, end;
					if (m_UserID < 10)start = 10;
					else start = 0;
					end = start + 10;
					int target2 = FindUnSeal(start, end);
					if (target2 == -1)return NormalAtk();
					SetTarget(target2);
					m_bSeal[m_TargetID] = TRUE;
					if (m_pUserPetData->m_LV > 129)return NpcTryMagic(54);
					return NpcTryMagic(54);
				}
			default:
				UseItem(eAIUseItemType暗器);
				return;
			
			}
		break;
	case eMP_天宫:
			switch (rand() % 10)
			{
			case 1:
			case 2:
				if (1)
				{
					int start, end;
					if (m_UserID < 10)start = 10;
					else start = 0;
					end = start + 10;
					int target2 = FindUnSeal(start, end);
					if (target2 == -1)return NormalAtk();
					SetTarget(target2);
					m_bSeal[m_TargetID] = TRUE;
					if (rand() % 2)
					{
						return NpcTryMagic(68);
					}
					else return NpcTryMagic(69);
				}
				return;
			case 3:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(71);
				}
				else
				return NormalAtk();
			case 4:return NpcTryMagic(72); 
			case 5: 
				if (m_pUserPetData->m_LV > 129)return NpcTryMagic(74);
			default:return NpcTryMagic(71);
			}
		break;
	case eMP_东海龙宫:
			switch (rand()%7)
			{
			case 0:return NpcTryMagic(84);
			case 1:return NpcTryMagic(79);
			case 2:
				if (m_pUserPetData->m_LV > 129)return NpcTryMagic(88);
				else 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(80);
				}
				else
					return NormalAtk();
			case 3:
				if (!CheckHaveState(m_UserID,147))
				{
					if (CheckCanSkill(147))
					{
						SetTarget(m_UserID);
						return UseMagic(147);
					}
				}
				return NpcTryMagic(80);
			default:return NpcTryMagic(80);
			}
		break;
	case eMP_五庄观:
			switch (rand() % 7)
			{
			case 0: 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(97);
				}
				else
				return NormalAtk();
			case 2: 
				if (1)
				{
					int start, end;
					if (m_UserID < 10)start = 11;
					else start = 1;
					end = start + 9;
					if (m_bPKMode)//日光乾坤在非PK时无法封主怪
					{
						start -= 1;
						end -= 5;
					}
					int target2 = FindUnSeal(start, end);
					if (target2 == -1)return NormalAtk();
					SetTarget(target2);
					m_bSeal[m_TargetID] = TRUE;
					return NpcTryMagic(89);
				}
			case 3: 
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					return NpcTryMagic(91);
			default: 
				return NpcTryMagic(97);
			}
		break;
	case eMP_普陀山:
		if (rand() % 3)
		{
			return NpcTryMagic(105 + rand() % 5);
		}
		else
		{
			int targetid = g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true);
			switch (rand() % 5)
			{
			case 0: 
				if (CheckCanSkill(113))
				{//颠倒五行
					SetTarget(targetid);
					if (m_pTarget->CheckHaveState(113))
					{
						SetTarget(g_pMainState->m_AI.AutoFindTarget(i, 4, true));
						return NpcTryMagic(105 + rand() % 5);
					}
					return  NpcTryMagic(113);
				}
				return NpcTryMagic(105 + rand() % 5);
			case 1:
				if (CheckCanSkill(102))//普渡
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					if (tlist.size())
					{
						SetTarget(tlist[0].x);
						return NpcTryMagic(102);
					}
				}
				SetTarget(g_pMainState->m_AI.AutoFindTarget(i, 4, true));
				return NpcTryMagic(105 + rand() % 5);
			case 2: 
				if (CheckCanSkill(103))
				return UseMagic(103);
				return NormalAtk();
			case 3: 
				if (CheckCanSkill(112))
				{
					SetTarget(targetid);
					return UseMagic(112);
				}
				return NpcTryMagic(105 + rand() % 5);
			case 4:
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(105 + rand() % 5);
				}
				else
				return NormalAtk();
			}
		}
		break;
	case eMP_阴曹地府:
		if (1)
		{
			
			switch (rand() % 6)
			{
			case 0: 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(117);
				}
				else
				return NormalAtk();
			case 1:return NpcTryMagic(117);
			case 3: return NpcTryMagic(122);
			case 4: 
				if (CheckCanSkill(123))
				{
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 3, true));
					return NpcTryMagic(123);
				}
				else return NpcTryMagic(116);
			default: return NpcTryMagic(116);
			}
		}
		break;
	case eMP_魔王寨:
		if (1)
		{
			switch (rand() % 6)
			{
			case 0: 
				if (m_pUserPetData->m_FightProperty.cannotAttack)
				{
					return NpcTryMagic(131);
				}
				else
				return NormalAtk();
			case 1:return NpcTryMagic(132);
			case 2:
				if (!m_pUser->CheckHaveState(133))
				{
					if (CheckCanSkill(133))
					{
						SetTarget(m_UserID);
						return NpcTryMagic(133);
					}
				}
				return NpcTryMagic(131);
			default:  return NpcTryMagic(131);
			}
		}
		break;
	case eMP_狮驼岭:
		if (1)
		{
			if (m_pUser->CheckHaveState(145))
			{
				switch (rand() % 5)
				{
				case 0:return NpcTryMagic(143);
				case 1:return NpcTryMagic(148);
				case 2:return NpcTryMagic(141);
				default: return NpcTryMagic(142);
				}
			}
			else
			{
				switch (rand() % 3)
				{
				case 0:
					if (m_pUserPetData->m_FightProperty.cannotAttack)
					{
						SetTarget(m_UserID);
						return NpcTryMagic(145);
					}
					else
					return NormalAtk();
				default:
					SetTarget(m_UserID);
					return NpcTryMagic(145);
				}
			}
		}
		break;
	case eMP_盘丝岭:
		switch (rand() % 6)
		{
		case 0:
			if(rand()%2)
			return NpcTryMagic(154);
			return NpcTryMagic(155);
		case 1:return NpcTryMagic(156);
		case 2:
			if (1)
			{
				int start, end;
				if (m_UserID < 10)start = 10;
				else start = 0;
				end = start + 10;
				int target2 = FindUnSeal(start, end);
				if (target2 == -1)return NormalAtk();
				SetTarget(target2);
				m_bSeal[m_TargetID] = TRUE;
				return NpcTryMagic(159);
			}
		case 3:
			if (!CheckHaveState(m_UserID, 160))
			{
				if (CheckCanSkill(160))
				{
					SetTarget(m_UserID);
					return UseMagic(160);
				}
				
			}
			if (m_pUserPetData->m_FightProperty.cannotAttack)
			{
				return NpcTryMagic(162);
			}
			else
			return NormalAtk();
		case 4:return NpcTryMagic(164);
		default:return NpcTryMagic(162);
		}
		break;
	 default:
		 ERRBOX;
		break;
	}
}

// 无视+4
void cAttackAI::ContentHP(int start, int end)
{
	
	for (int i = start; i < end; i++)
	{
		if (!m_bNeedlive[i])//确保应该活着
		if (m_bNeedAddHp[i]>0 || m_bNeedAddHpHurt[i]>0)
		{
			SetTarget(i);
			ContentHP2(start, end);
			if (m_bNeedAddHp[i]<0)
			m_bNeedAddHp[i] = 0;
			if (m_bNeedAddHpHurt[i]<0)
			m_bNeedAddHpHurt[i] = 0;
		}
	}
}
void cAttackAI::ContentHP2(int start, int end)
{
	vector<int> list;
	int id2 = -1;
	int id;
	int firstpos = -1;
	for (int i = 19; i >-1; i--)
	{
		id = g_pMainState->m_pFightState->m_SpeedListPos[i];
		if (id < start || id >= end)continue;
		if (!g_pMainState->m_FightList[id].isLive)continue;
		if (g_pMainState->m_FightList[id].CheckDie())continue;
		if (g_pMainState->m_FightList[id].m_WorkType != -1)continue;

		if (-1 == id2)
		if (g_pMainState->m_FightList[id].m_pData->m_IndexType == INDEXTYEP_CHARACTER)
		{//
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[id].m_pData->m_pIndex;
			if (!pc->m_PCData.m_FightProperty.cannotMagic)
			{
				switch (pc->m_PCData.m_MengPaiID)
				{
				case eMP_普陀山:
				case eMP_化生寺:
				case eMP_五庄观:
					id2 = id;
					firstpos = list.size();
					break;
				}
			}
		}
		cPetData* pPet;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPet);
		if (!pPet->m_FightProperty.cannotUseItem)
			list.push_back(id);
	}
	if (!list.size())return;
	if (-1 == id2)
	{
		id2 = list[0];
		firstpos = 0;
	}
	SetUser(id2);
	//BOOL bUse = FALSE;

		int num = 0;//需要治疗的对象数
		for (int i2 = start; i2 < end; i2++)
		if (m_bNeedAddHp[i2]>0 || m_bNeedAddHpHurt[i2]>0)
			num += 1;
		if (m_pUserPc)
		{
			eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
			switch (mengpai)
			{
			case eMP_化生寺:
				if (1)
				{
					if (num == 1)
					{
// 						switch (m_pUserPetData->m_StrongLv >> 5)
 						{
// 						case 3:
							if (CheckCanSkill(39))
							{
								m_bNeedAddHpHurt[m_TargetID] = -20;
								m_bNeedAddHp[m_TargetID] = -20;
								return UseMagic(39);
							}
							else 
//						case 2:
							if (CheckCanSkill(3002))
							{
								m_bNeedAddHpHurt[m_TargetID] = -15;
								m_bNeedAddHp[m_TargetID] = -15;
								return UseMagic(3002);
							}
//						case 1:
							else 
							if (CheckCanSkill(3001))
							{
								m_bNeedAddHpHurt[m_TargetID] = -10;
								m_bNeedAddHp[m_TargetID] = -10;
								return UseMagic(3001);
							}
// 							break;
 						}
					}
					//法术
					if (!m_pUserPetData->m_FightProperty.cannotMagic)
					{
						int skillid;
						if (num > 1)
						{
							if (m_bNeedAddHpHurt>0)skillid = 42;
							else skillid = 40;
						}
						else
						{
							
							if (m_bNeedAddHpHurt>0)skillid = 38;
							else
							{
								if (m_pUserPetData->m_LV > 129)
									skillid = 45;
								else
									skillid = 39;
							}

						}
						if (CheckCanSkill(skillid))
						{
							m_bNeedAddHpHurt[m_TargetID] = -10;
							m_bNeedAddHp[m_TargetID] = -10;
							return UseMagic(skillid);
						}
					}
				}
				break;
			case eMP_阴曹地府:
				if (num > 1) //四海
				{
//					if (m_pUserPetData->m_StrongLv > 90)
					{
						if (CheckCanSkill(7))
						{
							m_bNeedAddHpHurt[m_TargetID] = -20;
							m_bNeedAddHp[m_TargetID] = -20;
							return UseMagic(39);
						}
					}
				}
				break;
			case eMP_普陀山:
				if (1)
				{
					if (num > 1) //四海
					{
//						if (m_pUserPetData->m_StrongLv >90)
						{
							if (CheckCanSkill(7))
							{
								m_bNeedAddHpHurt[m_TargetID] = -20;
								m_bNeedAddHp[m_TargetID] = -20;
								return UseMagic(39);
							}
						}
					}
					//法术
					if (!m_pUserPetData->m_FightProperty.cannotMagic)
					{
						if (CheckCanSkill(102))
						{
							m_bNeedAddHpHurt[m_TargetID] = -30;
							m_bNeedAddHp[m_TargetID] = -30;
							return UseMagic(102);
						}
					}
				}
				break;
			}
		}
		//道具

		if (m_bNeedAddHp[m_TargetID]>0)
		{
			if (num > 3)
			{
				if (CheckItem(eAIUseItemTypeHPALL))
				{
					for (int i2 = start; i2 < end;i2++)
						m_bNeedAddHp[i2] =0;
					  UseItem(eAIUseItemTypeHPALL);
					  return;
				}
			}
			if (CheckItem(eAIUseItemTypeHP))
			{
				m_bNeedAddHp[m_TargetID] = 0;
				  UseItem(eAIUseItemTypeHP);
				  return;
			}
		}
		if (CheckItem(eAIUseItemTypeHPHurt))
		{
			m_bNeedAddHpHurt[m_TargetID] = 0;
			  UseItem(eAIUseItemTypeHPHurt);
			  return;
		}
	
}
void cAttackAI::ContentLive(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (m_bNeedlive[i])
		{
			SetTarget(i);
			ContentLive2(start, end);
		}
	}
}
void cAttackAI::ContentLive2(int start, int end)
{
	vector<int> list;
	int id2=-1;
	int id;
	int firstpos=-1;
	for (int i = 0; i < 20; i++)
	{
		id= g_pMainState->m_pFightState->m_SpeedListPos[i];
		if (id < start || id >= end)continue;
		if (!g_pMainState->m_FightList[id].isLive)continue;
		if (g_pMainState->m_FightList[id].CheckDie())continue;
		if (g_pMainState->m_FightList[id].m_WorkType != -1)continue;

		if (-1==id2)
		if (g_pMainState->m_FightList[id].m_pData->m_IndexType == INDEXTYEP_CHARACTER)
		{//
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[id].m_pData->m_pIndex;
			if (!pc->m_PCData.m_FightProperty.cannotMagic)
			{
				switch (pc->m_PCData.m_MengPaiID)
				{
				case eMP_普陀山:
				case eMP_化生寺:
					id2 = id;
					firstpos = list.size();
					break;
				case eMP_阴曹地府:
					if (pc->m_PCData.m_LV > 128)
					{
						id2 = id;
						firstpos = list.size();
					}
				}
			}
		}
		cPetData* pPet;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPet);
		if (!pPet->m_FightProperty.cannotUseItem)
			list.push_back(id);
	}
	if (!list.size())return;
	if (-1 == id2)
	{
		id2 = list[0];
		firstpos =0;
	}
	SetUser(id2);
	BOOL bUse = FALSE;
	if (m_pUserPc)
	{
		eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
		switch (mengpai)
		{
		case eMP_普陀山:
			if (1)
			{
				//特技   普陀有慈航
//				if (m_pUserPetData->m_StrongLv > 95)
				{
					int num = 0;
					for (int i2 = start; i2<end; i2++)
					if (m_bNeedlive[i2])num += 1;
					if (num > 2)
					{
						if (CheckCanSkill(3048))
						{
							for (int i2 = start; i2 < end; i2++)
								m_bNeedlive[i2] = FALSE;
							UseMagic(3048);
							bUse = TRUE;
						}
					}
				}
				if (!bUse)
				//法术
				if (!m_pUserPetData->m_FightProperty.cannotMagic)
				{
					if (CheckCanSkill(102))
					{
						m_bNeedlive[id2] = FALSE;
						 UseMagic(102);
						 bUse = TRUE;
					}
				}
			}
			break;
		case eMP_化生寺:
			//法术
			if (!m_pUserPetData->m_FightProperty.cannotMagic)
			{
				if (CheckCanSkill(37))
				{
					m_bNeedlive[id2] = FALSE;
					UseMagic(37);
					bUse = TRUE;
				}
			}
			break;
		case eMP_阴曹地府:
			//法术
			if (m_pUserPetData->m_LV > 129)
			if (!m_pUserPetData->m_FightProperty.cannotMagic)
			{
				if (CheckCanSkill(37))
				{
					m_bNeedlive[id2] = FALSE;
					UseMagic(37);
					bUse = TRUE;
				}
			}
			break;
		}
	}
	if (!bUse)
	//道具
	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
	if (CheckItem(eAIUseItemTypelive))
	{
		m_bNeedlive[m_TargetID] = FALSE;
		 UseItem(eAIUseItemTypelive);
		 bUse = TRUE;
	}
	if (!bUse)return;
	for (int i = firstpos + 1; i < list.size(); i++)
	{
		SetUser(list[firstpos + 1]);
		//道具
		if (!m_pUserPetData->m_FightProperty.cannotUseItem)
		if (CheckItem(eAIUseItemTypelive))
		{
			m_bNeedlive[m_TargetID] = FALSE;
			m_bNeedAddHp[m_TargetID] = FALSE;
			m_bNeedAddHpHurt[m_TargetID] = FALSE;
			 UseItem(eAIUseItemTypeHPHurt);
			 return;
		}

	}
}

BOOL cAttackAI::CheckCanSkill(int skillid)
{//检察一个技能是否可用,比如法术,MP不够,则返回0
	int dubstbin;
	int skilllv = 0;
	if (skillid < 1000)
	{
		sSkill *skill = g_pMainState->m_SkillManager.GetMengPaiSkill(skillid);
		skilllv = m_pUserPc->m_PCData.m_MengPaiSkillLV[skill->m_Owner];
	}
	return g_pMainState->m_SkillManager.Cost(dubstbin, skilllv, skillid, m_UserID, 5, FALSE);
}

//void cAttackAI::CoutIdleList(int start, int end)
//{
//	int needlist[10];
//	for (int i = start; i < end; i++)
//	{
//		m_IdleList[i] = i;
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		SetUser(i);
//		if (!m_pUserPc)
//		{
//			if (m_pUserPetData->m_AddPoint.hp>1 || m_pUserPetData->m_AddPoint.spd>1)
//			{
//				needlist[i] = 80;
//			}
//			else
//				needlist[i] = 10;
//		}
//		else
//		{
//			eMengPai mp = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
//			switch (mp)
//			{
//			case eMP_大唐官府:
//				needlist[i] = 1;
//				break;
//			case eMP_化生寺:
//				needlist[i] = 99;
//				break;
//			case eMP_女儿村:
//				needlist[i] = 10;
//				break;
//			case eMP_方寸山:
//				needlist[i] = 10;
//				break;
//			case eMP_狮驼岭:
//				needlist[i] = 1;
//				break;
//			case eMP_魔王寨:
//				needlist[i] = 1;
//				break;
//			case eMP_盘丝岭:
//				needlist[i] = 10;
//				break;
//			case eMP_阴曹地府:
//				if (m_pUserPetData->m_AddPoint.atk > 2)
//				{
//					needlist[i] = 10;
//				}
//				else
//				{
//					needlist[i] = 98;
//				}
//				break;
//			case eMP_东海龙宫:
//				needlist[i] = 1;
//				break;
//			case eMP_五庄观:
//				needlist[i] = 90;
//				break;
//			case eMP_普陀山:
//				needlist[i] = 95;
//				break;
//			case eMP_天宫:
//				needlist[i] = 80;
//				break;
//			default:
//				needlist[i] = 0;
//				break;
//			}
//		}
//		if (m_pUserPetData->m_FightProperty.cannotMagic)
//		{
//			needlist[i] += 10;
//		}
//		if (m_pUserPetData->m_FightProperty.chaos)
//		{
//			needlist[i] -= 100;
//			continue;
//		}
//		if (g_pMainState->m_FightList[i].m_bDie)
//		{
//			needlist[i] -= 100;
//			continue;
//		}
//	}
//	for (int a = 0; a < 9; a++)
//	for (int b = a + 1; b<10; b++)
//	{
//		if (needlist[a]<needlist[b])//前数大于后数
//		{
//			swap(needlist[a], needlist[b]);
//			swap(m_IdleList[a+start], m_IdleList[b+start]);
//		}
//	}//排序	
//}

void cAttackAI::Reset()
{
	cPetData* pPetdata;
	for (int i = 0; i < 20; i++)
	{

		m_bNeedAddHp[i] = 0;//当回合该对象是否需要加血
		m_bNeedAddHpHurt[i] = 0;
		m_bNeedUnSeal[i] = 0;//当回合该对象是否需要解封
		m_bNeedlive[i] = 0;
		m_bNeedAddMp[i] = 0;
		//检查角色是否被封
		m_bBeSeal[i] = FALSE;
		_isShiFudu[i] = FALSE;
		if (g_pMainState->m_FightList[i].isLive)
		{
			g_pMainState->m_FightList[i].m_pData->GetDateP(pPetdata);
			if (pPetdata->m_FightProperty.cannotMagic && !pPetdata->PeopleSpecial.d2)
				m_bBeSeal[i] = TRUE;
			if (g_pMainState->m_FightList[i].m_pData->CheckHaveState(122))
			{
				_isShiFudu[i] = TRUE;
			}
		}
		
	}
}

BOOL cAttackAI::CheckItem(eAIUseItemType mode)
{
	if (m_UserID % 10 < 5)
	{
		if (m_pUserPc)
		if (m_pUserPc->m_PCData.m_Item[mode].GetNum())
			return TRUE;
	}
	else
	{
		if (INDEXTYEP_CHARACTER == g_pMainState->m_FightList[m_UserID - 5].m_pData->m_IndexType)
		{
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[m_UserID - 5].m_pData->m_pIndex;
			if (pc)
			{
				if (pc->m_PCData.m_Item[mode].GetNum())
					return TRUE;
			}

		}
	}
	return FALSE;
}
// 无视+2
void cAttackAI::ContentUnSeal(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (m_bNeedUnSeal[i])
		{
			SetTarget(i);
			ContentUnSeal2(start, end);
			m_bNeedUnSeal[i] = FALSE;
		}
	}
}
void cAttackAI::ContentUnSeal2(int start, int end)
{
	vector<int> list;
	int id2 = -1;
	int id;
	int firstpos = -1;
	for (int i = 19; i > -1; i--)
	{
		id = g_pMainState->m_pFightState->m_SpeedListPos[i];
		if (id < start || id >= end)continue;
		if (!g_pMainState->m_FightList[id].isLive)continue;
		if (g_pMainState->m_FightList[id].CheckDie())continue;
		if (g_pMainState->m_FightList[id].m_WorkType != -1)continue;
		cPetData* pPet;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPet);
		if (!pPet->m_FightProperty.cannotUseItem)
			list.push_back(id);
	}
	if (!list.size())return;
	if (-1 == id2)
	{
		id2 = list[0];
		firstpos = 0;
	}
	SetUser(id2);
//	BOOL bUse = FALSE;
	
	int num = 0;
	for (int i2 = start; i2 < end; i2++)
	if (m_bNeedUnSeal[i2])num += 1;
		
		if (m_pUserPc)
		{
			eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
			switch (mengpai)
			{
			case eMP_方寸山:
			case eMP_盘丝岭:
			case eMP_阴曹地府:
			case eMP_五庄观:
			case eMP_天宫:
			case eMP_女儿村:
				if (1)
				{
					if (num > 2)
					{
//						switch (m_pUserPetData->m_StrongLv >> 6)
						{
//						case 1:
							if (CheckCanSkill(3013))
							{
								for (int i2 = start; i2 < end; i2++)
								{
									m_bNeedUnSeal[i2] = FALSE;
									if (m_bNeedAddHp[i2]>0)
									{
										m_bNeedAddHp[i2] -= 20;
									}
								}
								return UseMagic(3013);
							}
//						case 0: 
							else 
							if (CheckCanSkill(3012))
							{
								for (int i2 = start; i2 < end; i2++)
									m_bNeedUnSeal[i2] = FALSE;
								return UseMagic(3012);
							}
//							break;
						}
					}
					else
					//特技   
//					switch (m_pUserPetData->m_StrongLv >> 6)
					{
//					case 1:
						if (CheckCanSkill(3011))
						{
							m_bNeedUnSeal[m_TargetID] = FALSE;
							if (m_bNeedAddHp[m_TargetID]>0)
							m_bNeedAddHp[m_TargetID] -= 20;
							return UseMagic(3013);
						}
						else 
//					case 0:
						if (CheckCanSkill(3010))
						{
								m_bNeedUnSeal[m_TargetID] = FALSE;
							return UseMagic(3012);
						}
//						break;
					}
				}
				break;
			
			}
		}
		//道具
		if (!m_pUserPetData->m_FightProperty.cannotUseItem)
		if (CheckItem(eAIUseItemTypeUnseal))
		{
			m_bNeedUnSeal[m_TargetID] = FALSE;
			  UseItem(eAIUseItemTypeUnseal);
			  return;
		}
}

cAttackAI::cAttackAI()
{
	for (int i = 0; i < 20; i++)
	{
		m_FightTarget[i] = -1;
		m_bSeal[i] = FALSE;
		m_bNeedAddHp[i] = 0;//当回合该对象是否需要加血
		m_bNeedAddHpHurt[i] = 0;
		m_bNeedUnSeal[i] = 0;//当回合该对象是否需要解封
		m_bNeedlive[i] = 0;
		m_bNeedAddMp[i] = 0;
		m_bBeSeal[i] = 0;//是否被封
		m_bAtk[i] = 0;//
		_isShiFudu[i] = 0;
	}
}

//int cAttackAI::FintTarget(int id)
//{
//	int targetid;
//	int start, end;
//	if (id < 10)start = 10;
//	else start = 0;
//	end = start + 10;
//
//	if (-1 == m_FightTarget[id])
//	{
//		SetUser(id);
//		if (m_pUserPc)
//		{
//
//			eMengPai mengpai = (eMengPai)m_pUserPc->m_PCData.m_MengPaiID;
//			switch (mengpai)
//			{
//			case eMP_五庄观:
//				if (m_pUserPetData->m_AddPoint.atk < 3)
//				{
//					return FindUnSeal(start, end);
//				}
//			case eMP_大唐官府:
//			case eMP_狮驼岭:
//			case eMP_天宫:
//				switch (rand() % 3)
//				{
//				case 0:
//					return FindDefminTarget(start, end, eProPerty防御);
//				case 1:
//					return FindDefminTarget(start, end, eProPerty伤害, 1);
//				case 2:
//					return FindDefminTarget(start, end, eProPerty灵力, 1);
//				}
//				break;
//			case eMP_化生寺:
//				if (id < 10)start = 0;
//				else start = 10;
//				end = start + 10;
//				return FindDefminTarget(start, end, eProPerty防御);
//				break;
//			case eMP_方寸山:
//					return FindUnSeal(start, end);
//				break;
//			case eMP_魔王寨:
//			case eMP_东海龙宫:
//					return FindDefminTarget(start, end, eProPerty灵力);
//				break;
//			case eMP_盘丝岭:
//				if (m_pUserPetData->m_AddPoint.atk > 2)
//					return FindDefminTarget(start, end, eProPerty防御);
//				else
//					return FindUnSeal(start, end);
//			case eMP_阴曹地府:
//				if (m_pUserPetData->m_AddPoint.atk>2)
//					return FindDefminTarget(start, end, eProPerty防御);
//			case eMP_普陀山:
//				switch (rand() % 3)
//				{
//				case 0:
//					return FindDefminTarget(start, end, eProPerty防御, 1);
//				case 1:
//					return FindDefminTarget(start, end, eProPerty伤害, 1);
//				case 2:
//					return FindDefminTarget(start, end, eProPerty灵力, 1);
//				}
//				break;
//			case eMP_女儿村:
//					return FindUnSeal(start, end);
//			}
//		}
//		else
//		{
//			if (m_pUserPetData->m_AddPoint.atk>2)
//				return FindDefminTarget(start, end, eProPerty防御);
//			else
//				return FindDefminTarget(start, end, eProPerty灵力);
//		}
//	}
//	else
//	{
//		if (!g_pMainState->m_FightList[m_FightTarget[id]].isLive)
//		{
//			return FintTarget(id);
//		}
//		else targetid = m_FightTarget[id];
//	}
//	if (targetid == -1)return -1;
//	SetTarget(targetid);
//	return targetid;
//}

int cAttackAI::FindDefminTarget(int start, int end, eProPerty prop,BOOL maxormin, int userID)
{
	int id=-1;
	for (int i = start; i < end; i++)
	{
		if (g_pMainState->m_FightList[i].isLive)
		{
			id = i;
			break;
		}
	}
	if (-1 == id)return id;
	cPetData *pP1;
	cPetData* pP2;
	for (int i = id + 1; i < end; i++)
	{

		g_pMainState->m_FightList[id].m_pData->GetDateP(pP1);
		if (!g_pMainState->m_FightList[i].isLive)continue;
		g_pMainState->m_FightList[i].m_pData->GetDateP(pP2);
		if (userID != -1)
		{
			cPetData *data = nullptr;
			g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
			if (data && data->PeopleSpecial.d1 < pP2->PeopleSpecial.d2)
			{
				continue;
			}
		}
		if (maxormin)
		{
			switch (prop)
			{
			case eProPerty伤害:if (pP1->m_ATK.GetData() < pP2->m_ATK.GetData())id = i; break;
			case eProPerty防御:if (pP1->m_DEF.GetData() < pP2->m_DEF.GetData())id = i; break;
			case eProPerty灵力:if (pP1->m_Wakan.GetData() < pP2->m_Wakan.GetData())id = i; break;
			case eProPerty速度:if (pP1->m_SPD.GetData() < pP2->m_SPD.GetData())id = i; break;
			case eProPerty气血:	if (pP1->m_HP < pP2->m_HP)id = i;	break;
			}
		}
		else
		{
			switch (prop)
			{
			case eProPerty伤害:if (pP1->m_ATK.GetData() > pP2->m_ATK.GetData())id = i; break;
			case eProPerty防御:if (pP1->m_DEF.GetData() > pP2->m_DEF.GetData())id = i; break;
			case eProPerty灵力:if (pP1->m_Wakan.GetData() > pP2->m_Wakan.GetData())id = i; break;
			case eProPerty速度:if (pP1->m_SPD.GetData() > pP2->m_SPD.GetData())id = i; break;
			case eProPerty气血:	if (pP1->m_HP > pP2->m_HP)id = i;	break;
			}
		}
	}
	return id;
}

int cAttackAI::find尸腐毒对象()
{
	int id = -1;
	int start = m_UserID < 10 ? 10 : 0;
	int end = start + 10;
	cPetData *data = nullptr;
	g_pMainState->m_FightList[m_UserID].m_pData->GetDateP(data);
	for (int i = start; i < end; i++)
	{
		if (_isShiFudu[i])continue;
		if (!g_pMainState->m_FightList[i].isLive)continue;
		if (g_pMainState->m_FightList[i].m_pData->CheckHaveState(122))continue;
		cPetData *data2 = nullptr;
		g_pMainState->m_FightList[i].m_pData->GetDateP(data2);
		if (data2->m_race >= 1000 || data->PeopleSpecial.d1 < data2->PeopleSpecial.d2)continue;
		id = i;
		break;
	}
	if (-1 == id)
		return -1;
	cPetData *pP1;
	cPetData* pP2;
	for (int i = id + 1; i < end; i++)
	{
		if (_isShiFudu[i])continue;
		g_pMainState->m_FightList[id].m_pData->GetDateP(pP1);
		if (!g_pMainState->m_FightList[i].isLive)continue;
		if(g_pMainState->m_FightList[i].m_pData->CheckHaveState(122))continue;
		g_pMainState->m_FightList[i].m_pData->GetDateP(pP2);
		if (data->PeopleSpecial.d1 < pP2->PeopleSpecial.d2 || pP2->m_race >= 1000)
		{
			continue;
		}
		if (pP1->m_HP < pP2->m_HP)id = i;
	}
	return id;
}

int cAttackAI::FindUnSeal(int start, int end)
{
	int num = end - start;
	int id = rand()%num+start;
	for (int i = 0; i < num+1; i++)
	{
		if (g_pMainState->m_FightList[id].isLive)
		{
			if ((!m_bBeSeal[id]) && (!m_bSeal[id]))
			{
//				m_bSeal[id] = TRUE;
				return id;
			}
		}
		id += 1;
		if (id == end)
			id = start;
	}

	return -1;
}

int cAttackAI::FindUnSeal(int num)
{
	int start, end;
	if (m_UserID < 10)
		start = 10;
	else start = 0;
	end = start + num;
	return FindUnSeal(start, end);
}

int cAttackAI::FindUnSeal(char &isMorA)
{
	vector<POINT> out;
	FindEnemy(TRUE, FALSE, out, eET封印对象, m_UserID < 10 ? 10 : 0);
// 	int star = m_UserID < 10 ? 10 : 0;
// 	for (int i = star; i < star + 10; ++i)
	forv(out, i)
	{
		if (FindUnSeal(out[i].x, isMorA))
		{
			return out[i].x;
		}
	}
	return -1;

// 	auto func = [&](const std::function<bool(int, bool, const cPetData*)> &f)
// 	{
// 		int star = m_UserID < 10 ? 10 : 0;
// 		for (int i = star; i < star + 10; ++i)
// 		{
// 			if (!g_pMainState->m_FightList[i].isExist)
// 			{
// 				continue;
// 			}
// 			if (m_bBeSeal[i] || m_bSeal[i])
// 			{
// 				continue;
// 			}
// 			cPetData *data = nullptr;
// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
// 			if (!data)
// 			{
// 				continue;
// 			}
// 			if (data->PeopleSpecial.d2 > 0 || data->m_race >= 1000 ||
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(0)|| 
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(7) ||
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(142)||
// 				g_pMainState->m_FightList[i].m_pData->CheckHaveState(148))
// 			{
// 				continue;
// 			}	
// 			if (f(i, g_pMainState->m_FightList[i].m_pData->m_IndexType == INDEXTYEP_CHARACTER, data))
// 			{
// 				return i;
// 			}
// 		}
// 		return -1;
// 	};
// 
// 	int id = func([&](int i, bool isPc, const cPetData *data)
// 	{
// 		isMorA = 1;
// 		return isPc && !data->m_FightProperty.cannotMagic;
// 	});
// 	if (id < 0)
// 	{
// 		id = func([&](int i, bool isPc, const cPetData *data)
// 		{
// 			if (!isPc && data->m_ProPertyAtk >= data->m_LV * 3)
// 			{
// 				vector<int> ms, m2s, ps, bs;
// 				if (isHadPetSkill((cPetData*)data, bs, ps, ms, m2s))
// 				{
// 					if (ps.size() && !data->m_FightProperty.cannotMagic)
// 					{
// 						isMorA = 1;
// 						return true;
// 					}
// 					
// 					if (!ps.size() && !data->m_FightProperty.cannotAttack)
// 					{
// 						isMorA = 0;
// 						return true;
// 					}
// 				}
// 			}
// 			return false;
// 		});
// 	}
// 	if (id < 0)
// 	{
// 		id = func([&](int i, bool isPc, const cPetData *data)
// 		{
// 			if (isPc && !data->m_FightProperty.cannotSkill && data->m_CP >= 80)
// 			{
// 				isMorA = 2;
// 				return true;
// 			}
// 			return false;
// 		});
// 	}
// 
// 	return id;
}

bool cAttackAI::FindUnSeal(int i, char &isMorA)
{
	if (i < 0)
	{
		return false;
	}
	if (!g_pMainState->m_FightList[i].isLive)
	{
		return false;
	}
	if (m_bBeSeal[i] || m_bSeal[i])
	{
		return false;
	}
	cPetData *data = nullptr;
	g_pMainState->m_FightList[i].m_pData->GetDateP(data);
	if (!data)
	{
		return false;
	}
	if (data->PeopleSpecial.d2 > 0 || data->m_race >= 1000 ||
		g_pMainState->m_FightList[i].m_pData->CheckHaveState(0) ||
		g_pMainState->m_FightList[i].m_pData->CheckHaveState(7) ||
		g_pMainState->m_FightList[i].m_pData->CheckHaveState(142))// ||
// 		g_pMainState->m_FightList[i].m_pData->CheckHaveState(148))
	{
		return false;
	}
	if (rand() % 100 < data->restoreRate)
	{
		return false;
	}

	bool isPc = g_pMainState->m_FightList[i].m_pData->m_IndexType == INDEXTYEP_CHARACTER;

	if (isPc && !data->m_FightProperty.cannotMagic)
	{
		isMorA = 1;
		return true;
	}


	if (!isPc && data->m_ProPertyAtk >= data->m_LV * 3)
	{
		vector<int> ms, m2s, ps, bs;
		if (isHadPetSkill((cPetData*)data, bs, ps, ms, m2s))
		{
			if (ps.size() && !data->m_FightProperty.cannotMagic)
			{
				isMorA = 1;
				return true;
			}

			if (!ps.size() && !data->m_FightProperty.cannotAttack)
			{
				isMorA = 0;
				return true;
			}
		}
	}

	if (isPc && !data->m_FightProperty.cannotSkill && data->m_CP >= 80)
	{
		isMorA = 2;
		return true;
	}

	return false;
}

int cAttackAI::FindAtkTarget(int rate, BOOL ATKOrMagic, int userID /* = -1 */)
{ 
	//寻找物理或法术攻击最有价值的对象
	int start, end;
	if (m_UserID < 10)start = 10;
	else start = 0;
	end = start + 10;
	int num = end - start;
	int id = rand() % num+start;
	int idret = -1;
	int damage = 0;
	int damage2;
	int DamageAddPercent;
	int DamageDefAddPercent;
	for (int i = 0; i < num+1; i++)
	{
		if (g_pMainState->m_FightList[id].isLive)
		if (!g_pMainState->m_FightList[id].CheckDie())
		{
			if (userID != -1)
			{
				cPetData *data = nullptr;
				g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
				cPetData *data2 = nullptr;
				g_pMainState->m_FightList[id].m_pData->GetDateP(data2);
				if (data && data->PeopleSpecial.d1 < data2->PeopleSpecial.d2)
				{
					if (++id >= end)
					{
						id = start;
					}
					continue;
				}
			}
			SetTarget(id);
			int targethp = m_pTargetPetData->m_HP - m_bAtk[id];
			if (ATKOrMagic)
			{
				DamageAddPercent = m_pUserPetData->m_DamagePercent.d1; //自身攻击修炼
				DamageDefAddPercent = m_pTargetPetData->m_DamagePercent.d2;   //目标防御修炼
				damage2 = (m_pUserPetData->m_ATK.GetData() - m_pTargetPetData->m_DEF.GetData()) * rate / 100;
// 				int prr =  m_pTargetPetData->m_ParryRate.d1 - m_pUserPetData->m_ParryRate.d2;
// 				if (prr > 100)
// 				{
// 					prr = 100;
// 				}
// 				damage2 = damage2 * prr / 200;
			}
			else
			{
				DamageAddPercent = m_pUserPetData->m_DamageAddPercentMagic.d1; //自身法术攻击修炼
				DamageDefAddPercent = m_pTargetPetData->m_DamageAddPercentMagic.d2;   //目标法术防御修炼
				damage2 = (m_pUserPetData->m_LV * 3 + m_pUserPetData->m_ATK.GetData() / 6 + m_pUserPetData->m_Wakan.GetData() - m_pTargetPetData->m_Wakan.GetData()) * rate / 100;
			}
			damage2 = damage2 * (100 + DamageAddPercent - DamageDefAddPercent) / 100;//修炼修正
			if (damage2 > targethp)
			{
				//对手的HP越高越好    我方的伤害越低越好
				damage2 = (targethp << 2) - damage2;
			}
			
			if (-1 == idret)
			{
				idret = id;
				damage = damage2;
			}
			else
			{
				if (m_pTargetPetData->m_HP - m_bAtk[id] < 1)
				{
					continue;
				}
				if (damage2 > damage)
				{
					idret = id;
					damage = damage2;
				}
			}
		}
		id += 1;
		if (id >= end)
		{
			id = start;
		}
	}
	if (idret > -1)
	{
		m_bAtk[idret] += damage; //记录对象单回合受到的伤害的预测值
	}
	return idret;
}

int cAttackAI::FindCpMaxTarget(int num/*=100*/)
{
	int start, end;
	if (m_UserID < 10)start = 10;
	else start = 5;
	end = start + 5;
	cPetData* petdata;
	int id = rand() % 5 + start;
	for (int i = 0; i < 5; i++)
	{
		if (!g_pMainState->m_FightList[id].isLive)continue;
		g_pMainState->m_FightList[id].m_pData->GetDateP(petdata);
		if (petdata->m_CP>num)
		{
			return id;
		}
		id += 1;
		if (id >= end)id = start;
	}
	return -1;
}

BOOL cAttackAI::CheckHaveState(int userid, int skillid)
{
	return g_pMainState->m_FightList[userid].m_pData->CheckHaveState(skillid);
}

void cAttackAI::NpcTryMagic(int id)
{
	if (CheckCanSkill(id))
	{
		return UseMagic(id);
	}
	else
	{
		if (m_UserID<10 && m_TargetID<10)
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		else
		if (m_UserID > 9 && m_TargetID > 9)
			SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, true));
		if(m_TargetID < 0)
		{
			if (m_UserID < 10 && m_TargetID < 10)
				SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, false));
			else
				if (m_UserID > 9 && m_TargetID > 9)
					SetTarget(g_pMainState->m_AI.AutoFindTarget(m_UserID, 4, false));
		}
		return NormalAtk();
	}
}

bool cAttackAI::isHadPetSkill(cPetData *data, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills)
{
// 	if (!g_pMainState->m_FightList[userID].isExist)return false;
// 	cPetData *data = nullptr;
// 	g_pMainState->m_FightList[userID].m_pData->GetDateP(data);
	if (!data)return false;
	vector<sSkill*> skills;
	for (int j = 0; j < data->m_NumofBBSkill; j++)
	{
		skills.push_back(data->m_pPetSkill[j]);
		continue;
		sSkill *skill = data->m_pPetSkill[j];
		int id = skill->m_Id;
		switch (skill->m_SkillType)
		{
		case 4:
			if (id == 92 || id == 93 || id == 94 || id == 95 || id == 96 || id == 98 || id == 99 || id == 100 || id == 102)
			{
				pSkills.push_back(id + 2000);
			}
			else if (g_pMainState->m_SkillManager.GetPetSkill(id)->m_TargetNum > 1)
			{
				m2Skills.push_back(id + 2000);
			}
			else
			{
				mSkills.push_back(id + 2000);
			}
			break;
		case 7:continue;
		default:
			buffSkills.push_back(id + 2000);
			break;
		}
	}
	return isHadPetSkill(skills, buffSkills, pSkills, mSkills, m2Skills);
}

bool cAttackAI::isHadPetSkill(const vector<sSkill*> &skills, vector<int> &buffSkills, vector<int> &pSkills, vector<int> &mSkills, vector<int> &m2Skills)
{
	for (const auto &skill : skills)
	{
//		sSkill *skill = data->m_pPetSkill[j];
		int id = skill->m_Id;
		switch (skill->m_SkillType)
		{
		case 4:
			if (id == 92 || id == 93 || id == 94 || id == 95 || id == 96 || id == 98 || id == 99 || id == 100 || id == 102)
			{
				pSkills.push_back(id + 2000);
			}
			else if (g_pMainState->m_SkillManager.GetPetSkill(id)->m_TargetNum > 1)
			{
				m2Skills.push_back(id + 2000);
			}
			else
			{
				mSkills.push_back(id + 2000);
			}
			break;
		case 7:continue;
		default:
			buffSkills.push_back(id + 2000);
			break;
		}
	}
	return true;
}

int cAttackAI::RunPet()
{
	bool isAtk = m_pUserPetData->m_ProPertyMag == m_pUserPetData->m_LV;
	SetTarget(m_FightTarget[m_UserID]);
	bool isTar = true;
	if (m_TargetID < 0)
	{
		isTar = false;
		SetTarget(FindAtkTarget(100, isAtk, m_UserID));
	}
	if (m_pUserPetData->m_FightProperty.cannotMagic)
	{
		if (isAtk && m_TargetID >= 0)
		{
			NormalAtk();
			return 1;
		}
		return 0;
		Def(m_UserID);
	}

// 	//寻找目标
// 	if (m_FightTarget[m_UserID] > -1)
// 	{
// 		
// 	}
// 	else
// 	{
// //		int targetid = g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_UserID, 4, true);
// 		int targetid = FindAtkTarget(100, isAtk, m_UserID);
// 		if (targetid == -1)
// 		{
// 			if (runSelfunseal())
// 			{
// 				return;
// 			}
// 			return defense(m_UserID);
// 		}
// 		SetTarget(targetid);
// 	}

	vector<int> ms, m2s, ps, bs;
	if (!isHadPetSkill(m_pUserPetData, bs, ps, ms, m2s))
	{
		return 0;
	}
	if (!MyTest::getInstance()->isAtkMode(m_UserID) && bs.size())
	{
		int s = bs[rand() % bs.size()];
		if (!m_pUser->CheckHaveState(s) && CheckCanSkill(s))
		{
			SetTarget(m_UserID);
			UseMagic(s);
			return 2;
		}
	}

	if (!m2s.size() && !ps.size() && !ms.size())
	{
		if (MyTest::getInstance()->isAtkMode(m_UserID) || isAtk)
		{
			NormalAtk();
			return 1;
		}
		return 0;
		Def(m_UserID);
		
	}

	auto isCan = [&](const vector<int> &ss)
	{
		if (!ss.size())
		{
			return -1;
		}
		bool isCan = false;
		int s;
		for (int i = 0; i < 99; ++i)
		{
			s = ss[rand() % ss.size()];
			if (CheckCanSkill(s))
			{
				isCan = true;
				break;
			}
		}
		if (isCan)
		{
			return s;
		}
		return -1;
	};

	auto runM2s = [&]()
	{
		if (!m2s.size())
		{
			return false;
		}

		int s = -1;
		if (getVisibleNO() < 2)
		{
			forr(m2s, i)
			{
				if (m2s[i] == 2105 && CheckCanSkill(2105))
				{
					s = 2105;
					break;
				}
			}
		}
		if (s == -1)
		{
			s = isCan(m2s);
		}
		if (s >= 0)
		{
			UseMagic(s);
			return true;
		}
		return false;
	};

	auto runPs = [&]()
	{
		int s = isCan(ps);
		if (s >= 0)
		{
			if (isTar)
			{
				UseMagic(s);
				return true;
			}
			int self = m_UserID < 10 ? 10 : 0;
			if (s == 2095)
			{
				vector<POINT> out;
				FindEnemy(TRUE, FALSE, out, eET力劈华山95, self);
				auto out2 = check隐身(out, m_UserID);
				if (out2.size())
				{
					SetTarget(out2.front());
				}
// 				int id = -1;
// 				int start = m_UserID < 10 ? 10 : 0;
// 				for (int i = start; i < start + 10; i++)
// 				{
// 					if (g_pMainState->m_FightList[i].isExist)
// 					{
// 						id = i;
// 						break;
// 					}
// 				}
// 				if (id >= 0)
// 				{
// 					cPetData *pP1;
// 					cPetData* pP2;
// 					for (int i = id + 1; i < start + 10; i++)
// 					{
// 
// 						g_pMainState->m_FightList[id].m_pData->GetDateP(pP1);
// 						if (!g_pMainState->m_FightList[i].isExist)continue;
// 						g_pMainState->m_FightList[i].m_pData->GetDateP(pP2);
// 						if (m_pUserPetData->PeopleSpecial.d1 < pP2->PeopleSpecial.d2)
// 						{
// 							continue;
// 						}
// 						if (pP1->m_ATK.GetData() + pP1->m_DEF.GetData() > pP2->m_ATK.GetData() + pP2->m_DEF.GetData())
// 						{
// 							id = i;
// 						}
// 					}
// 				}
// 				if (id >= 0)
// 				{
// 					SetTarget(id);
// 				}
			}
			else if (s == 2099)
			{
				vector<POINT> out;
				FindEnemy(TRUE, FALSE, out, eET壁垒击破99, self);
				auto out2 = check隐身(out, m_UserID);
				if (out2.size())
				{
					SetTarget(out2.front());
				}
			}
			else if (s == 2094)
			{
				SetTarget(FindDefminTarget(eProPerty气血, false));
			}
			if (m_TargetID >= 0)
			{
				UseMagic(s);
				return true;
			}
		} 
		return false;
	};

	auto runMs = [&]()
	{
		int s = isCan(ms);
		if (s >= 0)
		{
			UseMagic(s);
			return true;
		}
		return false;
	};

	if (isAtk)
	{
		if (runPs())
		{
			return 3;
		}
		NormalAtk();
		return 1;
	}
	if (getVisibleNO() > 1 || !ms.size())
	{
		if (runM2s())
		{
			return 4;
		}
	}
	if (runMs())
	{
		return 4;
	}

	return 0;

// 
// 	//寻找技能
// 	vector<sSkill*> skilllist;
// 	BOOL bHaveBuff=FALSE;//是否会状态法术
// 	BOOL bHaveMagic=FALSE;//是否会单法
// 	BOOL bHaveMagic2=FALSE;//是否会群法
// 	for (int j = 0; j < m_pUserPetData->m_NumofBBSkill; j++)
// 	{
// 		switch (m_pUserPetData->m_pPetSkill[j]->m_SkillType)
// 		{
// 		case 4:
// 			if (1)
// 			{
// 				if (1<g_pMainState->m_SkillManager.GetPetSkill(m_pUserPetData->m_pPetSkill[j]->m_Id)->m_TargetNum)
// 				{
// 					bHaveMagic2 = TRUE;
// 				}
// 				else bHaveMagic = TRUE;
// 			}
// 			break;
// 		case 7:continue;
// 		default:
// 			bHaveBuff = TRUE;
// 			break;
// 		}
// 		skilllist.push_back(m_pUserPetData->m_pPetSkill[j]);
// 	}
// 	//如果有主动技能
// 	if (skilllist.size())
// 	{
// 		if (bHaveBuff)
// 		{
// 			if (rand() % 3 == 1)
// 			{
// 				//状态类法术
// 				for (int i = 0; i < skilllist.size(); i++)
// 				{
// 					if (skilllist[i]->m_SkillType == 2)
// 					{
// 						int skillid = skilllist[i]->m_Id + 2000;
// 						if (!m_pUser->CheckHaveState(skillid))
// 						{
// 							if (CheckCanSkill(skillid))
// 							{
// 								SetTarget(m_UserID);
// 								return UseMagic(skillid);
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 		if (bHaveMagic && (0 == bHaveMagic2))
// 		{
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//单法
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == 0)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 		}
// 		else
// 		if ((0==bHaveMagic) && bHaveMagic2)
// 		{
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//用群法
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == -3)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 		}
// 		else
// 		if (bHaveMagic&& bHaveMagic2)
// 		{
// 			//使用单法或群法
// 			int start, end;
// 			if (m_UserID<10)start = 10;
// 			else start = 0;
// 			end = start + 10;
// 			if (g_pMainState->GetLiveNum(start, end) > 1)
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//用群法
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == -3)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 
// 			for (int i = 0; i < skilllist.size(); i++)
// 			{//单法
// 				if (g_pMainState->m_SkillManager.m_PetSkillList[skilllist[i]->m_Id].m_EffectType == 0)
// 				{
// 					return NpcTryMagic(2000 + skilllist[i]->m_Id);
// 				}
// 			}
// 		}
// 		
// 	}
// 	if (m_pUserPetData->m_ProPertyAtk < m_pUserPetData->m_LV * 2)
// 		return defense(m_UserID);
// 	return	NormalAtk();

}

void cAttackAI::Summon(int id)
{
	g_pMainState->m_FightList[m_UserID].m_SkillSelect.SkillID = 1004;
	g_pMainState->m_FightList[m_UserID].m_SkillSelect.TargetID = g_pMainState->m_FightList[m_UserID].m_FriendListid + 5;
	g_pMainState->m_FightList[m_UserID].m_SkillSelect.Lv = id;
	g_pMainState->m_FightList[m_UserID].m_WorkType = WORKTYPE_SUMMON;
}

int cAttackAI::FindEnemy(BOOL CheckDie,BOOL bCheckWork,vector<POINT>& out, eEnemyType type, int userid, int data, int data2)
{
	out.clear();
	int ret=0;
	vector<POINT> out2;
	cPetData* pPet;
	POINT pt;
	cCharacter* pc;
	int randstart, randend;
	if (userid<10)randstart = 0; else randstart = 10;
	randend = randstart + 10;
	for (int i = randstart; i < randend; i++)
	{
		sFightList& list = g_pMainState->m_FightList[i];

		if (list.m_pData->m_IndexType == INDEXTYEP_CHARACTER)pc = (cCharacter*)list.m_pData->m_pIndex;
		else pc = 0;
		if (!list.isLive)continue;
		list.m_pData->GetDateP(pPet);
		if (bCheckWork)if (list.m_WorkType!=-1)continue;
		if (CheckDie)if (pPet->m_HP < 1)continue;
		
		if (-1 < data)
		if (list.m_pData->CheckHaveState(data))
			continue;
		if (-1 < data2)
		if (list.m_pData->CheckHaveState(data2))
			continue;
			switch (type)
			{
// 			case cAttackAI::eET攻宠:
// 				if (pc)continue;
			case cAttackAI::eET上金刚33:
//				if (pPet->m_AddPoint.atk >= 1)//加了1力以上的定义为物理系
				if( (!pc && pPet->m_ProPertyAtk > pPet->m_LV) || (pc && 
					pc->m_PCData.m_MengPaiID != eMP_方寸山 && 
					pc->m_PCData.m_MengPaiID != eMP_化生寺 &&
					pc->m_PCData.m_MengPaiID != eMP_普陀山 &&
					pc->m_PCData.m_MengPaiID != eMP_东海龙宫 &&
					pc->m_PCData.m_MengPaiID != eMP_魔王寨))
				{

					pt.x = i;
					pt.y = pPet->m_ATK.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
				}
				break;

			case cAttackAI::eET上灵动112:
				if (!pc && pPet->m_ProPertyMag > pPet->m_LV)
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else if (pc && pc->m_PCData.m_MengPaiID != eMP_大唐官府 &&
					pc->m_PCData.m_MengPaiID != eMP_女儿村 &&
					pc->m_PCData.m_MengPaiID != eMP_普陀山 &&
					pc->m_PCData.m_MengPaiID != eMP_五庄观 &&
					pc->m_PCData.m_MengPaiID != eMP_阴曹地府 && 
					pc->m_PCData.m_MengPaiID != eMP_狮驼岭)
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
				}
				break;

			case cAttackAI::eET封印对象:
// 					eMP_大唐官府,
// 					eMP_化生寺,
// 					eMP_女儿村,
// 					eMP_方寸山,
// 					eMP_狮驼岭,
// 					eMP_魔王寨,
// 					eMP_盘丝岭,
// 					eMP_阴曹地府,
// 					eMP_东海龙宫,
// 					eMP_五庄观,
// 					eMP_普陀山,
// 					eMP_天宫,
				if (pc && (pc->m_PCData.m_MengPaiID == eMP_方寸山 ||
					pc->m_PCData.m_MengPaiID == eMP_女儿村 ||
					pc->m_PCData.m_MengPaiID == eMP_盘丝岭 ||
					pc->m_PCData.m_MengPaiID == eMP_五庄观 ||
					pc->m_PCData.m_MengPaiID == eMP_天宫))
				{
					pt.x = i;
					pt.y = 20 - list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
				}
				break;

// 			case cAttackAI::eET法宠:
// 				if (pc)continue;
			case cAttackAI::eET速度最快2:
// 				if (pPet->m_AddPoint.mp >= 1)//加了1魔以上的定义为法系
// 				if ((!pc && pPet->m_ProPertyMag > pPet->m_LV) || 
// 					(pc
// 					pc->m_PCData.m_MengPaiID != eMP_大唐官府 &&
// 					pc->m_PCData.m_MengPaiID != eMP_女儿村 &&
// 					pc->m_PCData.m_MengPaiID != eMP_普陀山 &&
// 					pc->m_PCData.m_MengPaiID != eMP_五庄观 &&
// 					pc->m_PCData.m_MengPaiID != eMP_阴曹地府 && 
// 					pc->m_PCData.m_MengPaiID != eMP_狮驼岭))
// 				if (!pc)
// 				{
// 					continue;
// 				}
				pt.x = i;
				pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
				out.push_back(pt);
				ret += 1;
				break;
			case cAttackAI::eET可封系:
				if (!pc)continue;
				if (pPet->m_FightProperty.cannotMagic)continue;
				switch (pc->m_PCData.m_MengPaiID)
				{
				case eMP_女儿村:
				case eMP_方寸山:
				case eMP_盘丝岭:
				case eMP_五庄观:
				case eMP_天宫:
					pt.x = i;
					pt.y = list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAttackAI::eET可法系:
				if (pPet->m_FightProperty.cannotMagic)continue;
				if ((pc && (pc->m_PCData.m_MengPaiID == eMP_东海龙宫 || pc->m_PCData.m_MengPaiID == eMP_魔王寨)) ||
					(!pc && pPet->m_ProPertyMag > pPet->m_LV * 3))
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAttackAI::eET可物理系:
				if (pPet->m_FightProperty.cannotMagic && pPet->m_FightProperty.cannotSkill)continue;
				if ((pc && (pc->m_PCData.m_MengPaiID == eMP_大唐官府 || pc->m_PCData.m_MengPaiID == eMP_狮驼岭)) ||
					(!pc && pPet->m_ProPertyAtk > pPet->m_LV * 3))
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
					break;
				}
				break;
			case cAttackAI::eET血最少:
				if (pPet->m_HP < 1)
					pt.y = 100;
				else
				{
					pt.y = (100 * pPet->m_HP) / pPet->m_HPMax.GetData();
					if (pt.y < m_HPLimit)ret += 1;
					pt.y = -pt.y;
				}
				pt.x = i;
				out.push_back(pt);
				break;
// 			case cAttackAI::eET需要蓝系:
// 				if (pc)
// 				{
// 					switch (pc->m_PCData.m_MengPaiID)
// 					{
// 					case eMP_大唐官府:continue;
// 					case eMP_东海龙宫:continue;
// 					case eMP_魔王寨:continue;
// 					default:
// 						pt.y = -(100 * pc->m_PCData.m_MP) / pc->m_PCData.m_MPMax.GetData();
// 						pt.x = i;
// 						out.push_back(pt);
// 						break;
// 					}
// 				}
// 				break;
			case cAttackAI::eET医疗系:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
				if (!pc)continue;
				if (pc->m_PCData.m_HP < 1)continue;
				switch (pc->m_PCData.m_MengPaiID)
				{
//				case eMP_五庄观:
				case eMP_化生寺:
				case eMP_普陀山:
				case eMP_阴曹地府:
					pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
					pt.x = i;
					out.push_back(pt);
					ret += 1;
					break;	
				}
				break;
// 			case cAttackAI::eET血宠:
// 				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
// 				if (pc)continue;		
// 				if (pPet->m_ProPertyHP > pPet->m_LV * 2)
// 				{
// 					pt.x = i;
// 					pt.y = list._speedOfBattle; // pPet->m_SPD.GetData();
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET中死亡对象:
// 				if (!pc)continue;
// 				if (list.m_pData->CheckHaveState(2094) || list.m_pData->CheckHaveState(129))
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}	
// 				break;
			case cAttackAI::eET防最低:
				pt.x = i;
				pt.y = -pPet->m_DEF.GetData();
				out.push_back(pt);
				ret += 1;
				break;
			case cAttackAI::eET灵最低:
				pt.x = i;
				pt.y = -pPet->m_Wakan.GetData();
				out.push_back(pt);
				ret += 1;
				break;
// 			case cAttackAI::eET被封物理:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotAttack && !pc->m_PCData.PeopleSpecial.d2)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET被封法术:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotMagic)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
// 			case cAttackAI::eET被禁疗:
// 				if (!pc)continue;
// 				if (pc->m_PCData.m_FightProperty.cannotAddHP)
// 				{
// 					pt.x = i;
// 					pt.y = 1;
// 					out.push_back(pt);
// 					ret += 1;
// 				}
// 				break;
			case cAttackAI::eET无召唤兽:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
				if (i > 14)continue;
				if (!pc)continue;
				if (!g_pMainState->m_FightList[i + 5].isLive)
				{
					for (int i2 = 0; i2 < pc->m_PCData.m_NumofBB; i2++)
					if (pc->m_PCData.m_pPetDataList[i2]->m_PetDataZZ.m_HP > 1)
					{
						pt.x = i;
						pt.y = 1;
						out.push_back(pt);
						ret += 1;
					}
				}
				break;
			case cAttackAI::eET人物死亡:
				if (!pc)continue;
				if (0 == pPet->m_HP)
				{
					if (list.m_pData->CheckHaveState(2094))continue;//死亡
					if (list.m_pData->CheckHaveState(129))continue;//锢魂术
					pt.x = i;
					pt.y = 1;
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET速度最快:
				if (g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
// 				if (pc)
// 				{
// 					switch (pc->m_PCData.m_MengPaiID)
// 					{
// 					case eMP_化生寺:
// 					case eMP_阴曹地府:
// 					case eMP_普陀山:
// 						pt.y = pPet->m_SPD.GetData() * 5 / 4;
// 						break;
// 					case eMP_五庄观:
// 					case eMP_女儿村:
// 					case eMP_方寸山:
// 					case eMP_盘丝岭:
// 					case eMP_天宫:
// 						pt.y = pPet->m_SPD.GetData() * 6 / 4;
// 						break;
// 					default:
// 						pt.y = pPet->m_SPD.GetData() * 4 / 4;
// 						break;
// 
// 					}
// 				}
// 				else
// 				{
// 					pt.y = pPet->m_SPD.GetData() * 7 / 4;
// 				}

				pt.x = i;
				pt.y = list._speedOfBattle;
				out.push_back(pt);
				ret += 1;
				break;
			case eET加血:
				if (list.CheckDie())continue;
				if (pPet->m_FightProperty.cannotAll)continue;
				if (pPet->PeopleSpecial.d2)continue;
				if (pc)
				{
					switch (pc->m_PCData.m_MengPaiID)
					{
					case eMP_化生寺:
					case eMP_阴曹地府:
					case eMP_普陀山:
						pt.y = 10;			
						break;
					case eMP_五庄观:
						pt.y = 9;
						break;
					case eMP_女儿村:
					case eMP_方寸山:
					case eMP_盘丝岭:
					case eMP_天宫:
						pt.y = 5;
						break;
					default:
						pt.y = 4;
						break;

					}
				}
				else
				{
					pt.y = 5 + pPet->m_ProPertyHP / (pPet->m_LV + 1);
// 					if (pPet->m_ProPertyMag / pPet->m_LV > pPet->m_ProPertyAtk / pPet->m_LV)
// 					{
// 						pt.y = 14 - pPet->m_ProPertyMag / pPet->m_LV;
// 					}
// 					else
// 					{
// 						pt.y = 14 - pPet->m_ProPertyAtk / pPet->m_LV;
// 					}
				}
				pt.x = i;
				out.push_back(pt);
				ret += 1;
				break;
// 			case eET解封:
// 				if (list.CheckDie())break;
// 				if (pPet->m_FightProperty.cannotAll)break;
// 				if (pc)
// 				{
// 					pt.y = 1;
// 				}
// 				else
// 				{
// 					pt.y = 2 + pPet->m_ProPertyHP / (pPet->m_LV + 1);
// 
// 					if (pPet->m_AddPoint.mp > 0 || pPet->m_AddPoint.atk > 0)
// 					{
// 						if (pPet->m_AddPoint.mp > 2 || pPet->m_AddPoint.atk > 2)
// 						{
// 							if (pPet->m_AddPoint.mp > 4 || pPet->m_AddPoint.atk > 4)
// 							{
// 								pt.y = 5;
// 							}
// 							else
// 							{
// 								pt.y = 4;
// 							}
// 						}
// 						else
// 						{
// 							pt.y = 3;
// 						}
// 						out.push_back(pt);
// 					}
// 					else
// 					{
// 						pt.y = 2;
// 					}
// 					break;
// 				}
// 				pt.x = i;
// 				out.push_back(pt);
// 				ret += 1;
// 				break;

			case cAttackAI::eET佛法无边46:
				if (pc && (pc->m_PCData.m_MengPaiID == eMP_东海龙宫 || pc->m_PCData.m_MengPaiID == eMP_魔王寨))
				{
					pt.x = i;
					pt.y = pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;

			case cAttackAI::eET颠倒五行113:
				if (pc)
				{
					pt.x = i;
					pt.y = 0xffff - pPet->m_Wakan.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET力劈华山95:
				{
					pt.x = i;
					pt.y = 0xffff - pPet->m_ATK.GetData() - pPet->m_DEF.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET壁垒击破99:
				{
					pt.x = i;
					pt.y = pPet->m_ParryRate.d1;
					if (pt.y > 100)
					{
						pt.y = 100;
					}
					pt.y = pt.y * 10 + 0xffff - pPet->m_DEF.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;
			case cAttackAI::eET锢魂术129:
				if (!pPet->m_Controler.GetFly())
				{
					int r = pPet->m_HP * 100 / pPet->m_HPMax.GetData();
					if (r < 20)
					{
						pt.x = i;
						pt.y = 100 - r;
						out.push_back(pt);
						ret += 1;
					}
				}
				break;

			case cAttackAI::eET魂飞魄散127:
				if (pc)
				{
					int r = pPet->m_HP * 100 / pPet->m_HPMax.GetData();
					bool isok = false;
					for (std::list<sBuff>::iterator Iterator = list.m_pData->m_StateList.begin(); Iterator != list.m_pData->m_StateList.end();)
					{
						if (Iterator->times > 2)
						{
							int id = Iterator->ID;
							if (id == 26 || id == 49 || id == 112 || id == 113 || id == 120 || id == 133)
							{
								isok = true;
							}
							if (id == 102 && r < 80)
							{
								isok = true;
							}
						}
						++Iterator;
					}
					
					if (isok)
					{
						pt.x = i;
						pt.y = 100 - r;
						out.push_back(pt);
						ret += 1;
					}
				}
				else
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out2.push_back(pt);
//					ret += 1;
				}
				break;
			case cAttackAI::eET黄泉之息126:
				if (pc)
				{			
					pt.x = i;
					pt.y = list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
				}
				break;

			case cAttackAI::eET反间6:
				if (!pPet->m_FightProperty.cannotAll && 
					!pPet->m_FightProperty.cannotAttack && 
					!pPet->m_FightProperty.cannotMagic &&
					!pPet->m_FightProperty.chaos)
				{
					pt.x = i;
					pt.y = pPet->m_ATK.GetData();
					out.push_back(pt);
					ret += 1;
				}
				break;


			case cAttackAI::eET鬼眼120:
				if (!pPet->PeopleSpecial.d1)
				{
					pt.x = i;
					pt.y = list._speedOfBattle;
					out.push_back(pt);
					ret += 1;
				}
				break;

			default:ERRBOX(0);
				return -1;
				}
		
	}
	if (out.size()>1)
	{//把最大的数排到最前面
		for (int i = 0; i < out.size()-1;i++)
		for (int j = i+1; j < out.size(); j++)
		{
			if (out[i].y < out[j].y)
			{
				swap(out[i].x, out[j].x);
				swap(out[i].y, out[j].y);
			}
		}
	}
	if (out2.size())
	{
		forv(out2, i)
		{
			out.push_back(out2[i]);
			if (type != eET上金刚33 && type != eET上灵动112 && type != eET魂飞魄散127)
			{
				++ret;
			}
		}
	}
	return ret;
}

void cAttackAI::ZhiHui(BOOL bOur)
{
	int start = 10;
	int end;
	if (bOur)start = 0;
	end = start + 10;
	vector<POINT> tList;
	vector<POINT> tList2;
	//召唤兽死亡,重新招
	int num2;
	int num = FindEnemy(TRUE,TRUE,tList, eET无召唤兽, start);
	for (int i = 0; i < num; i++)
	{	
		if (!g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))continue;
		SetUser(tList[i].x);
		for (int j = 0; j < m_pUserPc->m_PCData.m_NumofBB; j++)
		{
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->m_PetDataZZ.m_HP > 0)
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->GetData()->m_LVLimit <= m_pUserPc->m_PCData.m_LV)
			{
				 Summon(j);
			}
		}
	}
	//人物死亡,复活
	num = FindEnemy(FALSE, FALSE, tList2, eET人物死亡, start);
	if (num)
	{
		// 6 反间不救
		num2 = FindEnemy(TRUE, TRUE, tList, eET医疗系, start, 6);
		if (!num2)
		{
			num2 = FindEnemy(TRUE, TRUE, tList, eET速度最快, start, 6);
		}

		if (num2)
		{
			resurgence2(tList, tList2, 0);
		}
	}

	//解封
	FindEnemy(FALSE, TRUE, tList, eET速度最快, start, 6);
	UnSeal2(tList, start, end);

	//人物加血
	if (FindEnemy(FALSE, TRUE, tList, eET加血, start))
	{
		Cure2(tList, start, end);
	}

	CureMP2(tList,start,end);
}

BOOL cAttackAI::resurgence(int user, int target)
{
	if (!m_bNeedlive[target])
	{
		return TRUE;
	}
	SetUser(user);
	if (pUserList->m_WorkType > -1)return FALSE;
	SetTarget(target);
	if (INDEXTYEP_CHARACTER == m_pUser->m_IndexType)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3048))
			{
				UseMagic(3048);
				vector<int> ts;
				int star = target < 10 ? 0 : 10;
				for (int i = star; i < star + 10; ++i)
				{
					if (!g_pMainState->m_FightList[i].isLive)
					{
						continue;
					}
					if (g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_CHARACTER)
					{
						continue;
					}
					if (!g_pMainState->m_FightList[i].CheckDie())
					{
						continue;
					}
					cPetData *data = nullptr;
					g_pMainState->m_FightList[i].m_pData->GetDateP(data);
					if (!data)
					{
						continue;
					}
					if (m_pUserPetData->PeopleSpecial.d1 < data->PeopleSpecial.d2)
					{
						continue;
					}
					ts.push_back(i);
				}
				if (ts.size() > 2)
				{
					for (int i : ts)
					{
						m_bNeedUnSeal[i] = FALSE;
						m_bNeedlive[i] = FALSE;
						m_bNeedAddHpHurt[i] -= 100;
						m_bNeedAddHp[i] -= 100;
					}
					return TRUE;
				}
			}
		}

		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			switch (m_pUserPc->m_PCData.m_MengPaiID)
			{
			case eMP_普陀山:
				if (CheckCanSkill(104))
				{
					UseMagic(104);
					m_bNeedlive[target] = FALSE;
					m_bNeedAddHpHurt[target] -= 40;
					m_bNeedAddHp[target] -= 40;
					return TRUE;
				}
				break;
			case eMP_化生寺:
				if (CheckCanSkill(37))
				{
					UseMagic(37);
					m_bNeedlive[target] = FALSE;
					m_bNeedAddHpHurt[target] -= 30;
					m_bNeedAddHp[target] -= 30;
					return TRUE;
				}
				break;
			case eMP_阴曹地府:
				if (m_pUserPc->m_PCData.m_LV >= 120)
				{
					if (CheckCanSkill(125))
					{
						UseMagic(125);
						m_bNeedlive[target] = FALSE;
						m_bNeedAddHpHurt[target] -= 25;
						m_bNeedAddHp[target] -= 25;
						return TRUE;
					}
				}
				break;
			}
		}

	}
	if (UseItem(eAIUseItemTypelive))
	{
		m_bNeedlive[target] = FALSE;
		return TRUE;
	}
	if (INDEXTYEP_CHARACTER == m_pUser->m_IndexType)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3009))
			{
				UseMagic(3009);
				m_bNeedlive[target] = FALSE;
				m_bNeedAddHpHurt[target] -= 60;
				m_bNeedAddHp[target] -= 60;
				return TRUE;
			}
			else if (CheckCanSkill(3008))
			{
				UseMagic(3008);
				m_bNeedlive[target] = FALSE;
				m_bNeedAddHpHurt[target] -= 30;
				m_bNeedAddHp[target] -= 30;
				return TRUE;
			}
		}
	}

	return FALSE;

}

void cAttackAI::resurgence2(vector<POINT>& user, vector<POINT>& target, int targetID)
{
	if (target.size() <= targetID)return;
	BOOL blist=TRUE;//是否A拉B B拉C
	int i;
	for (i = 0; i < user.size(); i++)
	{
		if (target[targetID].x == user[i].x)
		{//对象的速度太快
			blist = FALSE;
			continue;
		}
		if (resurgence(user[i].x, target[targetID].x))
			break;
	}
	if (!blist)return resurgence2(user,target,targetID+1);
	//A拉B B拉C C拉D
	if (i == g_pMainState->m_HeroID)return;
	if (i == g_pMainState->m_HeroID+5)return;
	i = targetID;
	for (; i < target.size() - 1; i++)
	{
		if (!resurgence(target[i].x, target[i+1].x))break;
	}
	//D拉BB
	if (target[i].x % 10 < 5 && !g_pMainState->m_FightList[target[i].x + 5].isLive)
	{
		SetUser(target[i].x);
		int j = 0;
		for (; j < m_pUserPc->m_PCData.m_NumofBB; j++)
		{
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->m_PetDataZZ.m_HP>0)
			if (m_pUserPc->m_PCData.m_pPetDataList[j]->GetData()->m_LVLimit <= m_pUserPc->m_PCData.m_LV)
			{
				Summon(j);
			}
		}
		//没有BB,自己吃药
		if (j == m_pUserPc->m_PCData.m_NumofBB)
		{
			SetTarget(target[i].x);
			if (!UseItem(eAIUseItemTypeHPHurt))
			{
				//不做任何处理
			}
		}
	}
}

void cAttackAI::CorrectEnemy(vector<POINT>& out, eEnemyCorrect typ)
{
	BOOL bFind = FALSE;
	int i;
	for (i = 0; i < out.size(); i++)
	{
		SetTarget(out[i].x);
		switch (typ)
		{
		case cAttackAI::eEC道具:
			if (!m_pTargetList->isLive)bFind = TRUE;
			if (m_pTargetList->CheckDie() && (!m_bNeedlive[m_TargetID]))bFind = TRUE;
			if (m_pTargetPetData->m_FightProperty.cannotUseItem)bFind = TRUE;
			break;
		default:
			break;
		}
		if (bFind)
		{
			out.erase(out.begin() + i);
			return CorrectEnemy(out, typ);
		}
	}
	return;
}

BOOL cAttackAI::Cure(int user, int target,BOOL toall)
{
	if (m_bNeedAddHp[target] < 100 - m_HPLimit)
	{
		return TRUE;
	}

	SetUser(user);
	if (pUserList->m_WorkType > -1)return FALSE;
	SetTarget(target);
	BOOL bHurt = FALSE;
	if (m_pTargetPetData->m_HPHurtMax < m_pTargetPetData->m_HPMax.GetData())
		bHurt = TRUE;
	int start = 10;
	int end;
	if (target<10)start = 0;
	end = start + 10;

	if (m_pUserPc)
	{
		if (!m_pUserPetData->m_FightProperty.cannotSkill)
		{
			if (CheckCanSkill(3013))
			{
				UseMagic(3013);
				int star = target < 10 ? 0 : 10;
				for (int i = star; i < star + 10; ++i)
				{
					m_bNeedAddHp[i] -= 20;
					m_bNeedUnSeal[i] = FALSE;
				}
				return TRUE;
			}
			else if (CheckCanSkill(3007))
			{
// 				m_bNeedAddHpHurt[m_TargetID] -= 30;
// 				m_bNeedAddHp[m_TargetID] -= 30;
				UseMagic(3007);
				int star = target < 10 ? 0 : 10;
				for (int i = star; i < star + 10; ++i)
				{
					m_bNeedAddHp[i] -= 30;
				}
				return TRUE;
			}
		}

		if (!m_pUserPetData->m_FightProperty.cannotMagic)
		{
			switch (m_pUserPc->m_PCData.m_MengPaiID)
			{
			case eMP_化生寺:
//			if (bHurt)
			{
				if (toall)
				{
					UseMagic(42);
					for (int i = start; i < end; i++)
						m_bNeedAddHp[i] -= 15;
					return TRUE;
				}
				else
				{
					if (m_pUserPetData->m_LV >= 120)
					{
						UseMagic(45);
						m_bNeedAddHp[target] = 0;
					}
					else
					{
						UseMagic(38);
						m_bNeedAddHp[target] -= 20;
					}
					return TRUE;
				}
			}
// 			else
// 			{
// 				if (toall)
// 				{
// 					UseMagic(40);
// 					for (int i = start; i < end; i++)
// 						m_bNeedAddHp[i] -= 30;
// 					return TRUE;
// 				}
// 				else
// 				{
// 					UseMagic(39);
// 					m_bNeedAddHp[target] -= 60;
// 					return TRUE;
// 				}
// 			}
				break;
			case eMP_阴曹地府:
			{
				SetTarget(find尸腐毒对象());
				if (m_TargetID >= 0)
				{
					_isShiFudu[m_TargetID] = TRUE;
					UseMagic(122);
					for (int i = start; i < end; i++)
						m_bNeedAddHp[i] -= 15;
					return TRUE;
				}
			}
				break;
			case eMP_普陀山:
				if (!m_pTarget->CheckHaveState(102))
				{
					UseMagic(102);
					m_bNeedAddHp[target] -= 15;
					return TRUE;
				}
				else
				{
					UseMagic(115);
					m_bNeedAddHp[target] -= 45;
					return TRUE;
				}
				break;
			case eMP_五庄观:
				if (!m_pTarget->CheckHaveState(91))
				{
					UseMagic(91);
					for (int i = start; i < end; i++)
						m_bNeedAddHp[i] -= 5;
					return TRUE;
				}
				break;
			}
		}
	}

	if (!m_pUserPetData->m_FightProperty.cannotUseItem && !MyTest::getInstance()->isAtkMode(m_UserID))
	{
		BOOL haveall=FALSE;
		if (m_pUserPc)
		{
			if (m_pUserPc->m_PCData.m_Item[1].GetNum())haveall = TRUE;
		}
		else
		{
			if (!m_pUserPetData->m_Controler.CheckBB())return FALSE;
			if (user - 5 < 0){
				ERRBOX(user - 5);
				return FALSE;
			}
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightList[user-5].m_pData->m_pIndex;
			if (pc)
			{
				if (pc->m_PCData.m_Item[1].GetNum())haveall = TRUE;
			}

		}
// 		if (toall&&haveall)
// 		{	
// 			UseItem(eAIUseItemTypeHPALL);
// 			for (int i = start; i < end; i++)
// 				m_bNeedAddHp[i] -= 40;
// 			return TRUE;
// 		}
// 		else
		{
			if (bHurt)
			{
				if (UseItem(eAIUseItemTypeHPHurt) || UseItem(eAIUseItemTypeHP))
				{
					m_bNeedAddHp[target] -= 30;
					return TRUE;
				}
			}
			else
			{
				if (UseItem(eAIUseItemTypeHP) || UseItem(eAIUseItemTypeHPHurt))
				{
					m_bNeedAddHp[target] -= 50;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}


BOOL cAttackAI::CureMP(int user, int target, BOOL toall /*= FALSE*/)
{
// 	if (!m_bNeedAddMp[target])
// 	{
// 		return TRUE;
// 	}
	SetUser(user);
	SetTarget(target);
	if (m_pUserPc)
	{
		if (m_pUserPetData->m_FightProperty.cannotMagic)
			switch (m_pUserPc->m_PCData.m_MengPaiID)
		{
			case eMP_五庄观:
				if (!m_pTarget->CheckHaveState(90))
				{
					UseMagic(90);
					m_bNeedAddMp[target] = FALSE;
					return TRUE;
				}
				else
				{
					if (target == user)
					{
						UseMagic(94);
						m_bNeedAddMp[target] = FALSE;
						return TRUE;
					}
				}
				break;
			case eMP_方寸山:
				if (target == user)
				{
					if (m_pUserPetData->m_HP > 100)
					{
						UseMagic(23);
						m_bNeedAddMp[target] = FALSE;
						return TRUE;
					}
				}
				break;
		}
	}
	if (!m_pUserPetData->m_FightProperty.cannotUseItem)
	{
// 		if (toall)
// 		{
// 			UseItem(eAIUseItemTypeMPALL);
// 			return TRUE;
// 		}
// 		else
		{
			if (UseItem(eAIUseItemTypeMP))
			{
				m_bNeedAddMp[target] = FALSE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

void cAttackAI::UnSeal2(vector<POINT>& tlist, int start, int end)
{
	UINT start1 = 0;
	for (int i = start; i < end; i++)
	{
		if (!m_bNeedUnSeal[i])
		{
			continue;
		}
		if (g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_CHARACTER)
		{
			continue;
		}
		for (int j = start1; j < tlist.size(); j++)
		{
			if (UnSeal(tlist[j].x, i))
			{
				start1 += 1;
				if (start1 == tlist.size())
				{
					return;
				}
				break;
			}
		}
	}

	for (int i = start; i < end; i++)
	{
		if (!m_bNeedUnSeal[i])
		{
			continue;
		}
		for (int j = start1; j < tlist.size(); j++)
		{
			if (UnSeal(tlist[j].x, i))
			{
				start1 += 1;
				if (start1 == tlist.size())
				{
					return;
				}
				break;
			}
		}
	}
}

void cAttackAI::Cure2(vector<POINT>& tlist, int start, int end)
{
	BOOL toall = TRUE;
	int start1 = 0;
	for (int i = start; i < end; i++)
	{
		if (m_bNeedAddHp[i] > (100 - m_HPLimit) && g_pMainState->m_FightList[i].m_pData->m_IndexType != INDEXTYEP_PET)
		{
			for (int j = start1; j < tlist.size(); j++)
			{
				if (toall)
				{
					int num = 0;
					int limit2 = m_HPLimit / 2 + 50;
					for (int k = start; k < end; k++)
					{
						if (m_bNeedAddHp[k] > 100 - limit2)
							num += 1;
					}
					if (num < 2)toall = FALSE;
				}
				if (Cure(tlist[j].x, i, toall))
				{
					start1 += 1;
					if (start1 == tlist.size())return;
					break;
				}
			}

		}
	}
}

BOOL cAttackAI::UnSeal(int user, int target)
{
// 	if (!m_bNeedUnSeal[target])
// 	{
// 		return TRUE;
// 	}
	SetUser(user);
	if (!pUserList->isLive)return FALSE;
	if (pUserList->CheckDie())return FALSE;
	if (pUserList->m_WorkType > -1)return FALSE;
	if (m_pUserPc && !m_pUserPetData->m_FightProperty.cannotSkill)
	{
		if (CheckCanSkill(3013))
		{
// 			m_bNeedAddHpHurt[target] -= 20;
// 			m_bNeedAddHp[target] -= 20;
			SetTarget(target);
			UseMagic(3013);
			int star = target < 10 ? 0 : 10;
			for (int i = star; i < star + 10; ++i)
			{
				m_bNeedUnSeal[i] = FALSE;
				m_bNeedAddHp[i] -= 20;
			
			}
			return TRUE;
		}
	}
	if (m_pUserPetData->m_FightProperty.cannotUseItem)
		return FALSE;
	SetTarget(target);
	if (UseItem(eAIUseItemTypeUnseal))
	{
		m_bNeedUnSeal[target] = FALSE;
		m_bNeedAddHp[target] -= 10;
		return TRUE;
	}
	return FALSE;
}

void cAttackAI::CureMP2(vector<POINT>& tlist, int start, int end)
{
	BOOL toall = TRUE;
	int start1 = 0;
	for (int i = start; i < end; i++)
	{
		if (m_bNeedAddMp[i])
		{
			for (int j = start1; j < tlist.size(); j++)
			{
				if (toall)
				{
					int num = 0;
					for (int k = start; k < end; k++)
					{
						if (m_bNeedAddMp[k])
							num += 1;
					}
					if (num < 3)toall = FALSE;
				}
				if (CureMP(tlist[j].x, i, toall))
				{
					start1 += 1;
					if (start1 == tlist.size())return;
					break;
				}
			}

		}
	}
}

vector<int> cAttackAI::check隐身(vector<POINT>& out, int user)
{
	cPetData *data;
	g_pMainState->m_FightList[user].m_pData->GetDateP(data);
	vector<int> out2;
	forv(out, i)
	{
		cPetData *data2;
		g_pMainState->m_FightList[out[i].x].m_pData->GetDateP(data2);
		if (data->PeopleSpecial.d1 >= data2->PeopleSpecial.d2)
		{
			out2.push_back(out[i].x);
		}
	}
	return out2;
}

#endif