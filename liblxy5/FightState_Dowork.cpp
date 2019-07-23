#include "_global.h"


bool cFightState::DoWork()
{
	m_FightMenu.ProcessAuto();
	cObj* pUser;
	cPropertyData* pUserData;
	// 狼：加注释
	switch (m_turn)
	{
	case 0: // 0 等待指令完成
	{
		// 等待附加状态 套装 动作完成
		bool isOk = true;
		for (int i = 0; i < 20; ++i)
		{
			if (!m_pFightWorkList[i]->isExist)
			{
				continue;
			}
			if (m_pFightWorkList[i]->m_work.size())
			{
				isOk = false;
				break;
			}
		}
		if (!isOk)
		{
			break;
		}
	}
	m_FightMenu.m_NeedShow = true;
	m_FightMenu.ProcessInput();

	if (m_FightMenu._isAutoBattle)
	{
		m_FightMenu._timeWaiting = 0;
		m_turn = 10086;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_FullSkill.m_FullSkilUP[i].m_NeedShow)
		{
			m_FullSkill.m_FullSkilUP[i].m_NeedShow = false;
		}
	}
	break;
	case 10086:
	{
		if (m_FightMenu._isAutoBattle)
		{
			if (++m_FightMenu._timeWaiting > 300)
			{
				while (m_turn != 1)
				{
					if (m_FightMenu.m_NowFighterID >= 0)
					{
						if (m_FightMenu.CheckControl(m_FightMenu.m_NowFighterID))
						{
							m_FightMenu.RunQ();
						}
					}
					m_FightMenu.AddTurn();
				}
			}
		}
		else
		{
			m_turn = 1;
		}
	}
	break;
	case 1: // 1 出手速度排序，AI初始化
	if (_turn == 0)
	{
		m_FightMenu._tAutoTurn.SetString("第1回合");
		g_pMainState->m_AI.checkHero();
	}
	SortBySpeed();
	g_pMainState->m_TriggerFightTurn.Process();
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
	}

	if (g_StateType != STATE_FIGHT)return true;
	m_MiaoShu.SetTime(30);
//	g_pMainState->m_AI.Run();
//	g_pMainState->m_AI.resetNeed();
// 	g_pMainState->m_AI.GetNeed(0, 20);
// 	g_pMainState->m_AI.ZhiHui(false);
// 	g_pMainState->m_AI.ZhiHui(true);
// 	for (int i = 0; i < 20; i++)
// 	{
// 		g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 		if (g_pMainState->m_FightList[i].isExist)
// 		if (g_pMainState->m_FightList[i].m_WorkType == -1)
// 		{
// 			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
// 			if (g_pMainState->m_FightList[i].m_pData->CheckHaveState(148) || g_pMainState->m_FightList[i].m_pData->CheckHaveState(142))
// 			{
// 				g_pMainState->m_AI.defense(i);
// 			}
// 			cPetData *data = nullptr;
// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
// 			if (!data)
// 			{
// 				continue;
// 			}
// 			if (((cPCData*)data)->m_MengPaiID == eMP_狮驼岭)
// 			{
// 				g_pMainState->m_AI.AutoRunAi(i);
// 			}
// 		}
// 	}
	m_FightMenu.m_NeedShow = false;
	m_CurrIDPerTurn = 0;
	m_turn += 1;
	case 2: // 2 检测战斗结束或继续
		if (!g_pMainState->GetLiveNum(10, 20))
		{
			//战胜了
			SuccessFight();
			return true;
		}
		if (!g_pMainState->GetLiveNum(0, 10))
		{
			//战败了
			FailFight();
			return true;
		}
		while (true)
		{
			if (m_CurrIDPerTurn > 19)
			{
				// 行动完毕 准备下一回合
				m_turn = 4;
				break;
			}
			int nowid = m_SpeedListPos[m_CurrIDPerTurn];
			// 否则 到下一个行动ID
			sFightWork*& list = m_pFightWorkList[nowid];
			if (list->m_work.size())
				break;
// 			if (list->m_WorkType == -2)
// 				break;
			g_pMainState->m_InterfaceDoor.m_TimeShiCheng.stepMiliSec();
			// 如果ID还未收到指令
			if (list->isExist)
			{
				if (list->_myTurn == 0)
				{
					bool is0 = true;
					int start = nowid / 10 * 10;
					int end = start + 10;
					for (int i = start; i < end; ++i)
					{
						if (!m_pFightWorkList[i]->isExist)
						{
							continue;
						}
						if (m_pFightWorkList[i]->_myTurn > 0)
						{
							is0 = false;
							break;
						}
					}
					if (!is0)
					{
						// 刚刚被召唤出场 
						// 第一回合就召唤牛妖怎么办,送你了...
						m_CurrIDPerTurn += 1;
						if (m_CurrIDPerTurn == 20)
						{
							m_turn = 4;
							break;
						}
					}
					else if(list->m_WorkType == -1)
					{
						// AI判断指令
						g_pMainState->m_AI.AutoRunAi(nowid);
					}
				}
				else if (list->m_WorkType == -1)
				{
					// AI判断指令
					g_pMainState->m_AI.AutoRunAi(nowid);
				}
			}
			// 收到指令，再次判断战斗是否继续
			if (list->m_WorkType >= 0)
			{
				if (!g_pMainState->GetLiveNum(10, 20))
				{
					//战胜了
					SuccessFight();
					return true;
				}
				if (!g_pMainState->GetLiveNum(0, 10))
				{
					//战败了
					FailFight();
					return true;
				}
				// 收到指令但是死了,没办法,下一个吧
				if (list->CheckDie())
				{
					m_CurrIDPerTurn += 1;
					continue;
				}

				// 指令加入行为组
				SetWork(nowid, list->m_WorkType);

				// 清空指令
				list->m_WorkType = -1;


				m_turn += 1;
				break;
			}
			else
			{
				// 还是没收到指令，呆着吧，下一个出手
				m_CurrIDPerTurn += 1;
				if (m_CurrIDPerTurn == 20)
				{
					m_turn = 4;
					break;
				}
			}
		}
		break;
	case 3://等待1个角色行动完成
	{
		int i3 = 0;
		for (; i3 < 20; i3++)
		{
			if (m_pFightWorkList[i3]->isExist)
			{
				if (m_pFightWorkList[i3]->m_work.size())
					break;
			}
		}
		if (i3 == 20)
		{
			// 每个ID行动完毕，包括引发的各种其他ID行动
			m_CurrIDPerTurn += 1;
			m_turn = 2;
			if (m_CurrIDPerTurn == 20) //一回合结束
			{
				// 等所有ID都行动完毕，准信下一回合
				m_turn = 4;
			}
		}
	}
		break;
	case 4:// 准备下一回合

	{//战斗结束检测

		if (!g_pMainState->GetLiveNum(10, 20))
		{
			//战胜了
			SuccessFight();
			return true;
		}
		if (!g_pMainState->GetLiveNum(0, 10))
		{
			//战败了
			FailFight();
			return true;
		}

		for (int i = 0; i < 20; i++)
		{
			//m_pList[i]->targetID = -1;
			if (m_pFightWorkList[i]->isExist)
			{
				m_pFightWorkList[i]->m_pObj->GetPropertyData(pUserData);
				pUserData->m_FightData.AttackNum = 0;
				pUserData->m_FightData.SufferNum = 0;
				m_pFightWorkList[i]->RestTarget();
				m_pFightWorkList[i]->m_work.clear();
				m_pFightWorkList[i]->m_WorkType = -1;
			}
		}

		for (int i = 0; i < 20; i++)
		{
			if (!m_pFightWorkList[i]->isExist)
				continue;
			//更新角色BUFF
			g_pMainState->m_SkillManager.CheckFightState(i);
			pUser = g_pMainState->m_FightWorkList[i].m_pObj;
			pUser->GetPropertyData(pUserData);

			//状态恢愎率
			if (pUserData->LiveRestoreRate > 0)
			{
				if (rand() % 100 < pUserData->LiveRestoreRate)
				{
					pUser->ReMoveState(eBuffType封印);
					pUser->ReMoveState(eBuffType毒);
					pUser->ReMoveState(eBuffType负面);
				}
			}

			
			if (pUserData->m_FightData.m_TurnHPHurtAdd)
				g_pMainState->m_SkillManager.AddHpHurt(i, pUserData->m_FightData.m_TurnHPHurtAdd);
			if (pUserData->m_FightData.m_TurnHPAdd)
				g_pMainState->m_SkillManager.AddHp(i, pUserData->m_FightData.m_TurnHPAdd);
			if (pUserData->m_FightData.m_TurnMPAdd)
				g_pMainState->m_SkillManager.AddMp(i, pUserData->m_FightData.m_TurnMPAdd);
			if (pUserData->LiveCp)
				g_pMainState->m_SkillManager.AddCp(i, pUserData->LiveCp);

			// 救命毫毛
			if (g_pMainState->m_FightWorkList[i].CheckDie())
			{
				if (rand() % 100 < pUserData->LiveRelifeRate)
				{
					if (g_pMainState->m_SkillManager.Resurgence(i))
					{
						g_pMainState->m_SkillManager.AddHpHurt(i, 499 + pUserData->m_Lv * 3);
						g_pMainState->m_SkillManager.AddHp(i, 499 + pUserData->m_Lv * 3);
						g_pMainState->m_SkillManager.SetDamage(-499 - pUserData->m_Lv * 3, i);
					}
				}
				else if (pUserData->Ghost.d1 > 0)
				{
					// 鬼魂术
					if (++g_pMainState->m_FightWorkList[i]._ghostTurn == pUserData->Ghost.d1)
					{
						if (g_pMainState->m_SkillManager.Resurgence(i))
						{
							g_pMainState->m_SkillManager.AddHpHurt(i, pUserData->HPMax.GetData());
							g_pMainState->m_SkillManager.AddHp(i, pUserData->HPMax.GetData());
							g_pMainState->m_SkillManager.SetDamage(-pUserData->HPMax.GetData(), i);
							g_pMainState->m_FightWorkList[i]._ghostTurn = 0;
						}
						else
						{
							--g_pMainState->m_FightWorkList[i]._ghostTurn;
						}
					}
				}
			}

			// 嗜血追击
			if (pUserData->isHadPetSkill(2076))
			{
				m_pFightWorkList[i]->_zhuiji = 1;
			}
			// 苍穹弩机
			if (pUserData->isHadPetSkill(2100))
			{
				m_pFightWorkList[i]->_nuji = 1;
// 				m_pFightWorkList[i]->_nujiFromCom = 0;
// 				m_pFightWorkList[i]->_nujiFromCri = 0;
			}

			pUserData->m_FightData.m_bDefend = false;
		}
	}
		m_turn = 0;
		m_FightMenu._timeWaiting = 0;
// 		m_FightMenu.SetControl(g_pMainState->m_HeroID, true);
// 		m_FightMenu.SetControl(g_pMainState->m_HeroID + 5, true);
		g_pMainState->m_AI.checkHero();
		m_FightMenu._tAutoTurn.SetString(toString("第%d回合", (++_turn) + 1));
		if (!m_FightMenu._autoBack.m_NeedShow)
		{
			g_pMainState->m_Tags.Add(m_FightMenu._tAutoTurn.GetString());
		}

		for (int i = 0; i < 20; i++)
		{
			++m_pFightWorkList[i]->_myTurn;
		}
		return true;
	} // swicth m_turn end



	for (int i = 0; i < 20; i++)
	{
		if (m_pFightWorkList[i]->isExist)
		{
			if (m_pFightWorkList[i]->m_work.empty())
				continue;
			for (int j = 0; j < m_pFightWorkList[i]->m_work.size(); j++)
			{
				pUser = g_pMainState->m_FightWorkList[i].m_pObj;
				pUser->GetPropertyData(pUserData);
				switch (m_pFightWorkList[i]->GetWork()->type)
				{
				case WORKTYPE_MAGICSUFFER:
					MagicSuffer(i);
					break;
				case WORKTYPE_SUFFER:  //被打,什么时候结束由攻击者决定
					Suffer(i);
					break;
				case WORKTYPE_ATTACK:
					//是否被封
				{
//					if (pUserData->m_FightData.cannotAttack)
//					{
//						m_pFightWorkList[i]->m_work.clear();
// 						if (i == g_pMainState->m_HeroID)
// 							g_pMainState->m_Channel.AddNewString("攻击不能");
// 						m_MiaoShu.SetString("攻击不能");
// 						m_MiaoShu.SetTime(120);
// 						m_MiaoShu.UpdateXCenter();
//						break;
//					}
					if (g_pMainState->m_SkillManager.Use(m_pFightWorkList[i]->m_SkillSelect, i))
					{
					}
				}
					break;
				case WORKTYPE_MAGIC2:
					g_pMainState->m_SkillManager.Use(m_pFightWorkList[i]->m_SkillSelect, i);
					break;
				case WORKTYPE_MAGIC:
					//是否被封
					g_pMainState->m_SkillManager.Use(m_pFightWorkList[i]->m_SkillSelect, i);
					break;
				case WORKTYPE_ITEM:
					//使用道具
					if (pUserData->m_FightData.cannotAll)
					{
						pUser->saySkill("道具不能");
						m_pFightWorkList[i]->m_work.clear();
// 						if (i == g_pMainState->m_HeroID)
// 							g_pMainState->m_Channel.AddNewString("道具不能");
// 						m_MiaoShu.SetString("道具不能");
// 						m_MiaoShu.SetTime(120);
// 						m_MiaoShu.UpdateXCenter();
						break;
					}
					g_pMainState->m_SkillManager.Use(m_pFightWorkList[i]->m_SkillSelect, i);



					break;
				case WORKTYPE_SUMMON:
					if (pUserData->m_FightData.cannotAll)
					{
						pUser->saySkill("召唤不能");
						m_pFightWorkList[i]->m_work.clear();
// 						if (i == g_pMainState->m_HeroID)
// 							g_pMainState->m_Channel.AddNewString("召唤不能");
// 						m_MiaoShu.SetString("召唤不能");
// 						m_MiaoShu.SetTime(120);
// 						m_MiaoShu.UpdateXCenter();
						break;
					}
					if (m_pFightWorkList[i + 5]->isExist && m_pFightWorkList[i + 5]->m_pObj->getPcData())
					{
						pUser->saySkill("召唤不能");
						m_pFightWorkList[i]->m_work.clear();
						break;
					}
					if (g_pMainState->m_SkillManager.Use(m_pFightWorkList[i]->m_SkillSelect, i))
					{

					}
					break;
				case WORKTYPE_DEFEND:
					Defend(i);
					break;
				case WORKTYPE_FLY:
					if (!m_pFightWorkList[i]->DieFly())
					{
						BackFromFight(i);
					}
					break;
				case WORKTYPE_FALLDOWN:
					FallDown(i);
					break;
				case  WORKTYPE_CATCH:
					if (g_pMainState->m_SkillManager.Use(m_pFightWorkList[i]->m_SkillSelect, i))
					{
					}
					break;
				case WORKTYPE_AVOID:
					Avoid(i);
					break;
				case WORKTYPE_RETURN:
					if (ReturnApproach(i))
					{
						m_pFightWorkList[i]->m_work.pop_back();
						return true;
					}
					break;
				case WORKTYPE_COUNTER:
					if (Counter(i))
					{

					}
					break;
				default:
					ERRBOX;
					break;
				}
			}
		}
	}
	return false;
}






bool cFightState::PrePareToFight(int i)
{
	if (!m_pFightWorkList[i]->isExist)return true;

	if (m_pFightWorkList[i]->m_bPrePareFight)return true;
	m_pFightWorkList[i]->m_bPrePareFight = true;
	cObj* pTarget = m_pFightWorkList[i]->m_pObj;
	pTarget->SetSound(POS_SOUNDSUFFER, false);
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	if (1 > pTargetData->m_HP)pTargetData->m_HP = 1;

	if (i < 10 && !pTargetData->_isOurTeamTemp)
	{
		if (pTarget->getPcData())
		{
			pTarget->getPcData()->apply();
		}
		else if (pTarget->getPetData())
		{
			pTarget->getPetData()->apply();
		}
	}
//	pTargetData->SetXLEffect(true);
	//初始化角色状态
	pTargetData->m_FightData.Init();
	pTarget->m_ConductFire.m_NeedShow = false;
	pTarget->m_ConductSeal.m_NeedShow = false;
	pTarget->m_TrueName.SetColor(RGB(0, 255, 0));
	m_pFightWorkList[i]->SetDie(false);
	pTarget->m_TrueName.m_bShowOnScreen = true;
	m_pFightWorkList[i]->m_work.clear();
	m_pFightWorkList[i]->m_WorkType = -1;

	m_pFightWorkList[i]->reset();
	if (!pTargetData->m_Controler.GetDel())
	{
		//记录角色的的位置,方向和基本属性
		m_pFightWorkList[i]->xOldPos = pTarget->GetX();
		m_pFightWorkList[i]->yOldPos = pTarget->GetY();
		m_pFightWorkList[i]->m_oldDirection = m_pFightWorkList[i]->m_pObj->GetDirection();

// 		pTargetData->m_FightProperty.m_oldATK = pTargetData->Atk;      //伤害
// 		pTargetData->m_FightProperty.m_oldHIT = pTargetData->Hit;   //命中
// 		pTargetData->m_FightProperty.m_oldDEF = pTargetData->Def;   //防御
// 		pTargetData->m_FightProperty.m_oldWakan = pTargetData->Mana; //灵力
// 		pTargetData->m_FightProperty.m_oldSPD = pTargetData->Speed;   //速度
// 		pTargetData->m_FightProperty.m_oldEvade = pTargetData->Evade; //躲闪
// 		pTargetData->m_FightProperty.m_oldGoldLive = pTargetData->RelifeRate;
//		pTargetData->m_FightData._isFlyOld = pTargetData->m_Controler.GetFly();
		pTargetData->m_FightData.m_TurnHPAdd = pTargetData->LiveHp/**pTargetData->m_Lv / 10*/;
		pTargetData->m_FightData.m_TurnHPHurtAdd = 0;
		pTargetData->m_FightData.m_TurnMPAdd = pTargetData->LiveMp/**pTargetData->m_Lv / 10*/;
	}

	if (pTargetData->_isOurTeamTemp || i >= 10)
	{
		pTargetData->m_FightData.m_TurnHPAdd = pTargetData->LiveHp;
		pTargetData->m_FightData.m_TurnMPAdd = pTargetData->LiveMp;
	}

	//附加阵法效果
	g_pMainState->m_InterfaceTeam.SetupOneFormationEffect(g_pMainState->m_InterfaceTeam.GetReTramTrun(i), pTargetData, 1);

	//设置角色的初始动作, 方向,位置
	pTarget->Set(POS_FIGHT_STAND);
	if (i < 10)
		pTarget->SetDirection(DIRECTION_LEFT_UP);
	else
		pTarget->SetDirection(DIRECTION_RIGHT_DOWN);

	pTarget->SetXY(m_战斗坐标xs[i], m_战斗坐标ys[i]);
	pTarget->MoveShadow();
	pTarget->MoveDialog();
	pTarget->MoveHpLine();
	pTarget->UpdateHpLine();
	pTarget->MoveName();
	pTarget->SetShadow(false);

	int skilllv = pTarget->GetSkillLv(0);
	if (pTarget->m_IndexType == INDEXTYEP_CHARACTER)
	{
		cPcData* pc = (cPcData*)pTargetData;
		if (pc->m_MengPaiID == eMP_凌波城)
		{
			pTargetData->m_FightData.zhanyi = 3;
			sBuff buf;
			buf.ID = 1997;
			buf.remainingTimes = 0xFFF;
			buf.EffectType = eBuffType其它;
			buf.bBuffup = true;
			buf.bufPos = 10;
			buf.damage = 2;
			buf.MagicID = 0x3D3C8D10;
			buf.targetID = i;
			buf.userID = i;
			buf.skilllv = 0;
			buf.data.m_Picture.m_FrameGap = 1;
			AddState(i, buf);
		}
		else if (pc->m_MengPaiID == eMP_狮驼岭)
		{
			sBuff buf;
			buf.remainingTimes = 8;
			g_pMainState->m_SkillManager.SetDateBuffUp(i, i, 145, buf, pTargetData->m_Lv);
		}

		for (int k = 0; k < pc->m_NumofBB; ++k)
		{
			pc->m_pPets[k]->m_PetData._owerIdx = k;
		}
		if (pc->m_FightPetID >= 0)
		{
			pc->m_pPets[pc->m_FightPetID]->m_PetData._owerIdx = -1;
		}
	}

	if (pTargetData->Cp1)
	{
		g_pMainState->m_SkillManager.AddCp(i, pTargetData->Cp1);
	}


	auto cbSkill = [&](int sid)
	{
		auto& s = m_pFightWorkList[i]->m_SkillSelect;
		s.SkillID = sid;
		s.SkillLv = pTargetData->m_Lv;
		s.TargetID = i;
		m_pFightWorkList[i]->SetWork(WORKTYPE_MAGIC);
//		m_pFightWorkList[i]->m_WorkType = -1;
		g_pMainState->m_SkillManager.Use(s, i);
	};

	// 开场
	if (pTargetData->Hide.d1 >= 2)
	{
		// 隐身
		cbSkill(123);
	}
	else if (pTargetData->StartMagic >= 0)
	{
		cbSkill(pTargetData->StartMagic);
	}

	// 神马浮云
	if (pTargetData->isHadPetSkill(2096))
	{
		sBuff buf;
		buf.remainingTimes = 5;
		g_pMainState->m_SkillManager.SetDateBuffUp(i, i, 2096, buf, skilllv);
		if (i % 10 >= 5)
		{
			g_pMainState->m_SkillManager.SetDateBuffUp(i - 5, i - 5, 2096, buf, skilllv);
		}
	}

	int hpmax = pTargetData->HPMax.GetData();
	int& hp2 = pTargetData->m_HP2;
	int& hp = pTargetData->m_HP;
	if (hp2 > hpmax)
	{
		hp2 = hpmax;
	}
	if (hp > hp2)
	{
		hp = hp2;
	}

	return true;
}







bool cFightState::BackFromFight(int i)
{
	auto plist = m_pFightWorkList[i];
	if (!plist->m_bPrePareFight)return true;
	plist->m_bPrePareFight = false;


	plist->m_work.clear();
	plist->m_WorkType = -1;
	plist->m_pObj->m_MagicSuffer.m_NeedShow = false;
	plist->m_DamageTime[0] = 100;
	plist->m_pObj->SetStatic(false);
	plist->m_pObj->m_TrueName.m_bShowOnScreen = false;

	cObj* pTarget = m_pFightWorkList[i]->m_pObj;
	pTarget->Reset();
	pTarget->SetShake(false);
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);

	SetFightBufDown(i);
	if (!pTargetData->m_Controler.GetDel())
	{
//		pTargetData->SetXLEffect(false);
		//还原角色的位置,方向,并使之站立
		pTarget->SetXY(plist->xOldPos, plist->yOldPos);
		pTarget->SetDirection(m_pFightWorkList[i]->m_oldDirection);
		pTarget->m_TrueName.SetColor(RGB(0, 255, 0));
		pTarget->Stand();
		pTarget->MoveShadow();
		pTarget->MoveDialog();
		//去除效果
// 		pTargetData->Atk = pTargetData->m_FightProperty.m_oldATK;      //伤害
// 		pTargetData->Hit = pTargetData->m_FightProperty.m_oldHIT;   //命中
// 		pTargetData->Def = pTargetData->m_FightProperty.m_oldDEF;   //防御
// 		pTargetData->Mana = pTargetData->m_FightProperty.m_oldWakan; //灵力
// 		pTargetData->Speed = pTargetData->m_FightProperty.m_oldSPD;   //速度
// 		pTargetData->Evade = pTargetData->m_FightProperty.m_oldEvade; //躲闪
// 		pTargetData->RelifeRate = pTargetData->m_FightProperty.m_oldGoldLive;
//		pTargetData->m_FightData.Clear();
//		pTargetData->m_Controler.setFly(pTargetData->m_FightData._isFlyOld);

// 		if (i >= 15)
// 		{
// 			g_pMainState->FreeFightList(i);
// 		}
	}
	else
	{
		g_pMainState->FreeFightList(i);
	}
	plist->isExist = false;

//	auto& listTemp = g_pMainState->m_FightWorkTemps[(i >= 10)];
//	if (i == listTemp._moon)
//	{
//		plist->Free();
//		*plist = listTemp;
//		m_FightMenu.SetControl(i, (listTemp._myTurn != -1));
//		listTemp._moon = -1;
// 		listTemp._moon = -1;
// 		plist->m_pObj = listTemp.m_pObj;
// 		plist->m_FriendListid = listTemp.m_FriendListid;
// 		plist->m_SkillPreSelect = listTemp.m_SkillPreSelect;
// 		if (g_StateType != STATE_GAMEOVER)
// 		{
// 			g_pMainState->FindObj();
// 		}
//	}

	return true;
}

