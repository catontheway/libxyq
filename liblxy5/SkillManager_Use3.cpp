#include "_global.h"
static void cbCounter(int UserID)
{
	auto& ss = g_pMainState->m_FightWorkList[UserID].m_SkillSelectForCounter;
	if (ss.SkillID >= 0)
	{
		g_pMainState->m_FightWorkList[UserID].m_SkillSelect = ss;
		ss.SkillID = -1;
	}
};

//道具
bool cSkillManager::Use1003物品(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		pUserList->m_pObj->Set(POS_MAGIC);
		pUserList->m_pObj->SetSound(POS_MAGIC);
		stage += 1;
	}
		return true;
	case 1:
		if (WaitForMagicPoint(UserID))
		{
			stage += 1;
			if (g_pMainState->m_ItemManage.UseItem(GetItem(UserID), TargetID))
			{
				if (g_pMainState->m_ItemManage.m_bToAll)
				{
					int startid;
					if (TargetID < 10)startid = 0;
					else startid = 10;
					for (int i = startid; i < startid + 10; i++)
						SetDamage(-g_pMainState->m_ItemManage.m_hp, TargetID);
				}
				else
					SetDamage(-g_pMainState->m_ItemManage.m_hp, TargetID);
			}
		}
		return true;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || (pUserList->m_pObj->m_NowPos == POS_FIGHT_STAND))
		{
			pUserList->m_pObj->Set(POS_FIGHT_STAND);
			pUserList->m_work.pop_back();
		}
		return true;
	}
	return true;
}



bool cSkillManager::Use1005暗器(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (!Skilllv)
	{
		Skilllv = g_pMainState->m_FightWorkList[UserID].m_pObj->GetSkillLv(0);
	}
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	cPropertyData* pPet;
	pUser->GetPropertyData(pPet);
	int lv = pPet->m_Lv;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		if (pUser->m_IndexType == INDEXTYEP_PET)
		{
			pUserList->m_work.pop_back();
			stage = -1;
//			g_pMainState->m_Channel.AddNewString("宠物无法使用暗器");
			pUser->saySkill("暗器不能");
			return true;
		}
		sItem2* pItem = GetItem(UserID);
		if (pItem->GetNum() < 1)
		{
			pUserList->m_work.pop_back();
			stage = -1;
//			g_pMainState->m_Channel.AddNewString("没有道具");
			pUser->saySkill("道具不足");
			return true;
		}
		if (lv / 15 < pItem->GetID())
		{
			pUserList->m_work.pop_back();
			stage = -1;
//			g_pMainState->m_Channel.AddNewString("角色等级太低,无法使用");
			pUser->saySkill("等级不足");
			return true;
		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage += 1;
	}
		return true;
	case 1:

	{

		if (WaitForMagicPoint(UserID))
		{
			stage += 1;
			sItem2* pItem = GetItem(UserID);

			ulong dateid = 0;
			int num = 0;
			switch (pItem->GetID())
			{
			case 0://飞刀
				dateid = 0x44BE65A3;
				num = 1;
				break;
			case 1://飞蝗石
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 2://铁蒺藜
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 3://无影神针
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 4://孔雀翎
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 5://含沙射影
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 6://回龙摄魂标
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 7://寸阴若梦
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 8://魔睛子
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 9://顺逆神针
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			default:
				return false;
			}
			num = 1;
			if (((cCharacter*)pPet)->m_PcData.m_MengPaiID == (int)eMP_女儿村)
			{
// 				num = Skilllv / 25 + 1;
// 				if (num > 7)
// 				{
// 					num = 7;
// 				}
				num = 7;
			}
			m_pFightState->m_HiddenWeapons.Load(dateid);
			int i = 0;
			for (; i < num; i++)
			{
				m_pFightState->m_HiddenWeaponsTargetID[i] = g_pMainState->m_AI.find溅射暗器(UserID, TargetID, i, true + 2);
				if (-1 == m_pFightState->m_HiddenWeaponsTargetID[i])
					break;
				m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = true;
				m_pFightState->m_HiddenWeaponsp[i].m_x = pUser->GetX();
				m_pFightState->m_HiddenWeaponsp[i].m_y = pUser->GetY() - 30;
			}
			m_pFightState->m_HiddenWeaponsUseNum = i;
		}
	}
		return true;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			stage += 1;
		}
	case 3:

	{
		int targetid;
		sItem2* pItem = GetItem(UserID);
		for (int i = 0; i < 10; i++)
		{
			if (true == m_pFightState->m_HiddenWeaponsp[i].m_NeedShow)
			{
				if (m_pFightState->HiddenWeaponsMove(i))
				{
					targetid = m_pFightState->m_HiddenWeaponsTargetID[i];
					m_pFightState->m_HiddenWeaponsUseNum -= 1;
					m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = false;
					if (!g_pMainState->m_FightWorkList[targetid].isExist)continue;
					cPropertyData* pTargetData;
					g_pMainState->m_FightWorkList[targetid].m_pObj->GetPropertyData(pTargetData);
					int damageup = pPet->DmgPercentOfArm.d1 - pTargetData->DmgPercentOfArm.d2;
					if (false && rand() % 100 >= 100 + pPet->HitRate.d1 - pTargetData->HitRate.d2)
					{
						m_pFightState->SetAvoid_state15(targetid, pUser->GetDirection());
					}
					else
					{
						int dam, damh;
						switch (pItem->GetID())
						{
						case 0://飞刀
							dam = 100;
							damh = 10;
							break;
						case 1://飞蝗石
							dam = 120;
							damh = 20;
							break;
						case 2://铁蒺藜
							dam = 200;
							damh = 50;
							break;
						case 3://无影神针
							dam = 300;
							damh = 80;
							break;
						case 4://孔雀翎
							dam = 400;
							damh = 100;
							break;
						case 5://含沙射影
							dam = 500;
							damh = 150;
							break;
						case 6://回龙摄魂标
							dam = 800;
							damh = 200;
							break;
						case 7://寸阴若梦
							dam = 1000;
							damh = 250;
							break;
						case 8://魔睛子
							dam = 1500;
							damh = 300;
							break;
						default://顺逆神针
							dam = 2000;
							damh = 400;
							break;
						}


						damh = dam = (pItem->GetID() + 1) * 25;
//						dam = (Skilllv * 2 + dam + 50);
						dam = dam * (100 + damageup) / 100;

						if (dam > 0)
						{
							CheckPoision(UserID, targetid);//中毒修正
//							if ((TargetID < 10) || g_pMainState->m_AI.m_bPKMode)
							{//普通任务时伤害其实是2倍化的
								// 									dam = dam >> 1;
								// 									damh = damh >> 1;
							}
							m_pFightState->SetSuffer_state30(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction, UserID);
							AddHp(targetid, -dam);
							AddHpHurt(targetid, -damh);
							SetDamage(dam, targetid);
						}
						else
							m_pFightState->SetAvoid_state15(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction);
					}
				}
			}
		}
		if (0 == m_pFightState->m_HiddenWeaponsUseNum)
		{
			if (3 == stage)
			{
				pUserList->m_work.pop_back();
				stage = -1;
			}
		}
	}
		break;
	}
	return true;
}



//逃跑
bool cSkillManager::Use1006(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	cObj* pTarget = pUserList->m_pObj;
	cPropertyData* pUserData;
	cPropertyData* pTargetData;
	pUser->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);

	////ERR 逃跑必成功
	//pUserList->work.clear();
	//pUserList->m_stage = 0;
	//m_pFightState->m_bEscape = true;
	//return true;
	////ERR
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		int direct;
		if (UserID < 10)direct = 3;
		else  direct = 7;
		pUser->SetDirection(direct);
		pUser->Set(POS_WALK);
		stage = 1;
		m_time = 30;
	}
		break;
	case 1:
		StageWaitSleep(20, UserID, 2);
		break;
	case 2:
		if (true || rand() % 100 < 95 + g_GlobalValues[13]/* + pUserData->m_FuZhuSkillLvList[9] - pTargetData->m_FuZhuSkillLvList[10]*/)
		{
			stage = 3;
			pUser->m_Wav.Free();
			pUser->m_Wav.LoadWav(35379719);
		}
		else
		{
			stage = 4;
			pUser->m_Wav.Free();
			pUser->m_Wav.LoadWav(2673692967);
		}
		break;
	case 3:

	{
		int k;
		if (UserID < 10)k = 3;
		else  k = -3;
		int x2 = pUser->GetX() + 2 * k;
		int y2 = pUser->GetY() + 1 * k;
		pUser->SetPos(x2, y2);
		pUser->MoveHpLine();


		//移动对话
		if (pUser->m_ShowTime > 0)
		{
			pUser->MoveDialog();
		}
		//移动名字
		if (pUser->m_bNeedShowName)
		{
			pUser->MoveName();
		}
		if (UserID % 10 < 5)
			if (pUserData->m_Controler.CheckHaveBB())
			{//召唤兽一起跑
			if (m_pFightState->m_pFightWorkList[UserID + 5]->isExist && (!m_pFightState->m_pFightWorkList[UserID + 5]->CheckDie()))
			{
				cObj* pPet = m_pFightState->m_pFightWorkList[UserID + 5]->m_pObj;
				int x3 = pPet->GetX() + 2 * k;
				int y3 = pPet->GetY() + 1 * k;
				if (pPet->m_NowPos != POS_WALK)
				{
					pPet->Set(POS_WALK);
					pPet->SetDirection(pUser->GetDirection());
				}
				pPet->SetPos(x3, y3);
				pPet->MoveHpLine();
				//移动对话
				if (pPet->m_ShowTime > 0)
				{
					pPet->MoveDialog();
				}
				//移动名字
				if (pPet->m_bNeedShowName)
				{
					pPet->MoveName();
				}
			}
			}
		if (y2 > g_480 || y2 < 0)
		{
			g_pMainState->m_pFightState->BackFromFight(UserID);

			if (pUserData->m_Controler.CheckHaveBB())
			{
				g_pMainState->m_pFightState->BackFromFight(UserID);
			}

			if (pUser->getPcData() && UserID < 5)
			{
				m_pFightState->m_bEscape = true;
			}
			else if (UserID >= 5 && UserID < 10 && 
				g_pMainState->m_FightWorkList[UserID - 5].CheckDie() && 
				g_pMainState->m_pFightState->m_FightMenu.CheckControl(UserID))
			{
				m_pFightState->m_bEscape = true;
			}
		}
	}
		break;
	case 4:
	{
		m_time -= 1;
		pUserList->Rotate(1);
		if (m_time < 0)
		{
			int direct;
			if (UserID < 10)direct = 7;
			else  direct = 3;
			pUser->SetDirection(direct);
			pUser->Set(POS_FIGHT_STAND);
			pUserList->m_work.clear();
		}
	}
		break;
	}
	return true;
}



bool cSkillManager::Use61暗器(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (!Skilllv)
	{
		Skilllv = g_pMainState->m_FightWorkList[UserID].m_pObj->GetSkillLv(0);
	}
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	cPropertyData* pPet;
	pUser->GetPropertyData(pPet);
	int lv = pPet->m_Lv;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
		if (pUser->m_IndexType == INDEXTYEP_PET)
		{
			pUserList->m_work.pop_back();
			stage = -1;
//			g_pMainState->m_Channel.AddNewString("宠物无法使用暗器");
			pUser->saySkill("暗器不能");
			return true;
		}
		// 		sItem2* pItem = GetItem(UserID);
		// 		if (pItem->GetNum() < 1)
		// 		{
		// 			pUserList->m_work.pop_back();
		// 			stage = -1;
		// 			g_pMainState->m_Channel.AddNewString("没有道具");
		// 			return true;
		// 		}
		// 		if (lv / 15 < pItem->GetID())
		// 		{
		// 			pUserList->m_work.pop_back();
		// 			stage = -1;
		// 			g_pMainState->m_Channel.AddNewString("角色等级太低,无法使用");
		// 			return true;
		// 		}
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage += 1;
	}
		return true;
	case 1:

	{

		if (WaitForMagicPoint(UserID))
		{
			stage += 1;
//			sItem2* pItem = GetItem(UserID);

			ulong dateid = 0;
			int num = 0;
			switch (Skilllv / 20)
			{
			case 0://飞刀
				dateid = 0x44BE65A3;
				num = 1;
				break;
			case 1://飞蝗石
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 2://铁蒺藜
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 3://无影神针
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 4://孔雀翎
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 5://含沙射影
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 6://回龙摄魂标
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 7://寸阴若梦
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 8://魔睛子
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			case 9://顺逆神针
				dateid = 0x44BE65A3;
				num = 1 + lv / 30;
				break;
			default:
				dateid = 0x44BE65A3;
				break;
				//				return false;
			}
			num = 7;// Skilllv / 25 + 1;
// 			if (num > 7)
// 			{
// 				num = 7;
// 			}

			m_pFightState->m_HiddenWeapons.Load(dateid);
			int i = 0;
			for (; i < num; i++)
			{
				m_pFightState->m_HiddenWeaponsTargetID[i] = g_pMainState->m_AI.find溅射暗器(UserID, TargetID, i, true + 2);
				if (-1 == m_pFightState->m_HiddenWeaponsTargetID[i])
					break;
				m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = true;
				m_pFightState->m_HiddenWeaponsp[i].m_x = pUser->GetX();
				m_pFightState->m_HiddenWeaponsp[i].m_y = pUser->GetY() - 30;
			}
			m_pFightState->m_HiddenWeaponsUseNum = i;
		}
	}
		return true;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			stage += 1;
		}
	case 3:

	{
		int targetid;
//		sItem2* pItem = GetItem(UserID);
		for (int i = 0; i < 10; i++)
		{
			if (true == m_pFightState->m_HiddenWeaponsp[i].m_NeedShow)
			{
				if (m_pFightState->HiddenWeaponsMove(i))
				{
					targetid = m_pFightState->m_HiddenWeaponsTargetID[i];
					m_pFightState->m_HiddenWeaponsUseNum -= 1;
					m_pFightState->m_HiddenWeaponsp[i].m_NeedShow = false;
					if (!g_pMainState->m_FightWorkList[targetid].isExist)continue;
					cPropertyData* pTargetData;
					g_pMainState->m_FightWorkList[targetid].m_pObj->GetPropertyData(pTargetData);
					int damageup = pPet->DmgPercentOfArm.d1 - pTargetData->DmgPercentOfArm.d2;
					if (false && rand() % 100 >= 100 + pPet->HitRate.d1 - pTargetData->HitRate.d2)
					{
						m_pFightState->SetAvoid_state15(targetid, pUser->GetDirection());
					}
					else
					{
						int dam, damh;
						switch (Skilllv / 20)
						{
						case 0://飞刀
							dam = 100;
							damh = 10;
							break;
						case 1://飞蝗石
							dam = 120;
							damh = 20;
							break;
						case 2://铁蒺藜
							dam = 200;
							damh = 50;
							break;
						case 3://无影神针
							dam = 300;
							damh = 80;
							break;
						case 4://孔雀翎
							dam = 400;
							damh = 100;
							break;
						case 5://含沙射影
							dam = 500;
							damh = 150;
							break;
						case 6://回龙摄魂标
							dam = 800;
							damh = 200;
							break;
						case 7://寸阴若梦
							dam = 1000;
							damh = 250;
							break;
						case 8://魔睛子
							dam = 1500;
							damh = 300;
							break;
						default://顺逆神针
							dam = 2000;
							damh = 400;
							break;
						}


// 						damh = dam = (Skilllv / 20 + 1) * 30;
// 						dam = (Skilllv * 2 + dam + 50);
// 						dam = dam *(100 + damageup) / 100;
						dam = Skilllv * 28 / 5;
//						dam += dam * damageup / 100;
						if (dam > 0)
						{
							CheckPoision(UserID, targetid);//中毒修正
//							if ((TargetID < 10) || g_pMainState->m_AI.m_bPKMode)
							{//普通任务时伤害其实是2倍化的
								// 									dam = dam >> 1;
								// 									damh = damh >> 1;
							}
							m_pFightState->SetSuffer_state30(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction, UserID);
							AddHp(targetid, -dam);
							AddHpHurt(targetid, -damh);
							SetDamage(dam, targetid);
						}
						else
							m_pFightState->SetAvoid_state15(targetid, m_pFightState->m_HiddenWeaponsp[i].m_direction);
					}
				}
			}
		}
		if (0 == m_pFightState->m_HiddenWeaponsUseNum)
		{
			if (3 == stage)
			{
				pUserList->m_work.pop_back();
				stage = -1;
			}
		}
	}
		break;
	}
	return true;
}


//召唤
bool cSkillManager::Use1004召唤(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = &g_pMainState->m_FightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	cPropertyData* pUserData;
	pUser->GetPropertyData(pUserData);

// 	if (g_pMainState->m_FightWorkList[UserID + 5].isExist)
// 	{
// 		g_pMainState->m_pFightState->SetFightBufDown(UserID + 5);
// 	}
// 	g_pMainState->SetFightPet(UserID, pUserList->m_SkillSelect.SkillLv);
// 	m_pFightState->PrePareToFight(UserID + 5);
// 	m_pFightState->m_CurrIDPerTurn += 1;
// 	g_pMainState->FindObj();
// 	pUserList->m_work.pop_back();
// 	return true;


	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:
	{
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
	}
		return true;
	case 1:
		if (WaitForMagicPoint(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->SetStatic(false);
			stage += 1;
			m_pFightState->m_FullSkill.SetMagicUp(0, 0xF90D5594, 
			g_pMainState->m_pFightState->m_战斗坐标xs[TargetID],
			g_pMainState->m_pFightState->m_战斗坐标ys[TargetID]);
			m_pFightState->m_pFightWorkList[UserID]->m_bSufferFullSkill = true;
			m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_FrameGap = GetSpeed(0);
		}
		return true;
	case 2:
	{
		bool f = m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() >= m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame() - 1;
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
			stage = 3;
		}
		else if (f)
		{
			stage = 4;
		}
	}
	case 3:  //附加BUFF
	{
		stage = 5;
// 		if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() >= m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame() - 1)
// 		{
// 			stage = 5;
// 		}
	}
		return true;
	case 4:
	{
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
			stage = 5;
		}
	}
		return true;
	case 5://等待主角动作完成
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);

			auto& list = g_pMainState->m_FightWorkList[TargetID];

			if (sSkillID == 1004)
			{
				if (list.isExist)
				{
					g_pMainState->m_pFightState->SetFightBufDown(TargetID);
				}
				g_pMainState->SetFightPet(UserID, pUserList->m_SkillSelect.SkillLv);

				// 不重新排序速度了
			}
			else if (sSkillID == 135 || sSkillID == 136)
			{
//				auto& listTemp = g_pMainState->m_FightWorkTemps[(UserID >= 10)];
// 				listTemp.m_pObj = list.m_pObj;
// 				listTemp.m_FriendListid = list.m_FriendListid;
// 				listTemp.m_SkillPreSelect = list.m_SkillPreSelect;
// 				listTemp = list;
// 				listTemp._moon = TargetID;
// 				listTemp._myTurn = g_pMainState->m_pFightState->m_FightMenu.CheckControl(TargetID) ? 0 : (-1);
				g_pMainState->m_pFightState->m_FightMenu.SetControl(TargetID, false);

				list.isExist = true;
				int modeid = sSkillID == 135 ? e踏云兽 : e牛妖;
				list.m_pObj = new cObj;
				list.m_pObj->Init();
				list.m_pObj->m_TrueName.m_bShowOnScreen = false;
				list.m_pObj->m_TrueName.SetColor(RGB(0, 0, 0));
				list.m_pObj->m_IDInFightlist = TargetID;

				list.m_pObj->AutoData(modeid, GetSkill(sSkillID)->m_Name);
				cPetData *data = list.m_pObj->getPetData();
//				list.m_pObj->GetPropertyData(data);
				data->Reset();
				data->Load(modeid, true, true);
				data->m_Lv = pUserData->m_Lv;
				sAddPoint ap;
				if (sSkillID == 135)
				{
					ap.Set(4, 0, 0, 1, 0);
					data->m_ZiZhi.Set(1600, 1600, 1200, 6000, 1600, 1200, 130);
				}
				else
				{
					ap.Set(0, 0, 4, 1, 0);
					data->m_ZiZhi.Set(1200, 1600, 3200, 6000, 1600, 1200, 130);
				}
				data->setPointAfterLv(ap, false);
				
				data->m_XiuLian = ((cPcData*)pUserData)->m_XiuLianBB;
				data->m_NumofBBSkill = 2;
				int sid = (sSkillID == 135) ? 2024 : 2057;
				int sid2 = (sSkillID == 135) ? 2004 : 2090;
				data->m_petSkills[0] = GetSkill(sid);
				data->m_petSkills[1] = GetSkill(sid2);
				data->m_XiuLian = pUserData->m_XiuLian;
				data->apply();
				data->FillHpMp();
				data->_isOurTeamTemp = true;
			}

			m_pFightState->PrePareToFight(TargetID);
//			int id = g_pMainState->m_InterfaceTeam.GetTeamTurn(TargetID);
			list.m_pObj->SetXY(g_pMainState->m_pFightState->m_战斗坐标xs[TargetID], g_pMainState->m_pFightState->m_战斗坐标ys[TargetID]);
			list.m_pObj->MoveShadow();
			list.m_pObj->MoveDialog();
			list.m_pObj->MoveHpLine();
			list.m_pObj->UpdateHpLine();
			list.m_pObj->MoveName();

//			m_pFightState->SortBySpeed();
//			m_pFightState->m_CurrIDPerTurn += 1;
			g_pMainState->FindObj();
			pUserList->m_work.pop_back();
			cbCounter(UserID);

			cPetData* pTargetData = list.m_pObj->getPetData();
			if (pTargetData->StartMagic < 0 && pTargetData->Hide.d1 == 0)
			{
				if (pTargetData->PointMag > pTargetData->m_Lv * 2) // 瞬法
				{
					vector<int> bs, ps, ms, m2s;
					g_pMainState->m_AI.isHadPetSkill(pTargetData, bs, ps, ms, m2s);
					int sid = -1;
					if (m2s.size())
					{
						sid = m2s[rand() % m2s.size()];
					}
					else if (ms.size())
					{
						sid = ms[rand() % ms.size()];
					}
					if (sid >= 0)
					{
// 						int tid = g_pMainState->m_AI.findBattleTargetAndStepMiliSec(TargetID, 4, true);
// 						if (tid >= 0)
						{
							auto& s = list.m_SkillSelect;
							s.SkillID = sid;
							s.SkillLv = pTargetData->m_Lv;
							s.TargetID = -1; // tid;
							list.SetWork(WORKTYPE_MAGIC);
						//	list.m_WorkType = -1;
							g_pMainState->m_SkillManager.Use(s, TargetID);
						}
					}
				}
				else if (pTargetData->PointStr > pTargetData->m_Lv * 2) // 瞬法
				{
// 					int tid = g_pMainState->m_AI.findBattleTargetAndStepMiliSec(TargetID, 4, true);
// 					if (tid >= 0)
					{
						auto& s = list.m_SkillSelect;
						s.SkillID = 1000;
						s.SkillLv = 0;
						s.TargetID = -1; // tid;
						list.SetWork(WORKTYPE_ATTACK);
					//	list.m_WorkType = -1;
						g_pMainState->m_SkillManager.Use(s, TargetID);
					}
				}
			}

		}
		return true;
	}
	
	return true;



//	sFightWorkList*& pUserList = m_pFightState->m_pFightWorkList[UserID];

	//int& stage = pUserList->GetWork()->stage;
	//switch (stage)
	//{
	//case 0:
	/*	pUserList->m_pData->Set(POS_MAGIC);
	pUserList->m_pData->SetSound(POS_MAGIC);
	stage += 1;
	return true;
	case 1:
	if (WaitForMagicPoint(UserID))
	{*/
	//先把之前的召唤兽去除战斗效果
	if (g_pMainState->m_FightWorkList[UserID + 5].isExist)
	{
		g_pMainState->m_pFightState->SetFightBufDown(UserID + 5);
	}
	g_pMainState->SetFightPet(UserID, pUserList->m_SkillSelect.SkillLv);
	m_pFightState->PrePareToFight(UserID + 5);
//	int k = m_pFightState->m_SpeedListPos[UserID];
//	m_pFightState->SortBySpeed();
//	if (m_pFightState->m_SpeedListPos[UserID] != k)
		m_pFightState->m_CurrIDPerTurn += 1;
	//	stage += 1;
	g_pMainState->FindObj();
	/*	}
	return true;
	case 2:
	if (m_pFightState->WaitPosEnd(UserID) || (pUserList->m_pData->m_NowPos == POS_FIGHT_STAND))
	{
	pUserList->m_pData->Set(POS_FIGHT_STAND);*/
	pUserList->m_work.pop_back();
	/*	}
	return true;
	}*/
	return true;
}



bool cSkillManager::UseNormal(int skillID)
{
	//平时使用的法术,比如回门派法术
	int targetid = g_pMainState->m_HeroID;
	sSkill* pSkill = g_pMainState->m_SkillManager.GetMengPaiSkill(skillID);
	int skilllv = g_pCharacter->m_PcData.m_MengPaiSkillLvs[pSkill->m_Owner];

// 	int hpout;
// 	if (!Cost(hpout, skilllv, skillID, targetid, 1, false))
// 	{
// 		g_pMainState->m_Channel.AddNewString("技能无法使用");
// 		return true;
// 	}

	if ((rand() % 100) >= CheckMagicHit(skilllv, skillID, targetid, targetid))
	{
// 		Cost(hpout, skilllv, skillID, targetid, 1, true);
		if (g_StateType == STATE_MAIN)
		{
			g_pMainState->m_Tags.Add("技能使用失败");
		}
		return true;
	}
	switch (skillID)
	{
	case 3:   //大唐   各种回门派
	case 25://方寸山
	case 44: //化生寺
	case 58: //女儿村
	case 70: //天宫
	case 83://龙宫
	case 93: //五庄观
	case 110: //普陀
	case 124://地府
	case 138: //魔王寨
	case 149: //狮驼
	case 163: //盘丝岭
	case 180: //凌波城
	case 192://无底洞
	case 202://叶隐
		if (UseSwitchMap(skilllv, skillID, targetid, targetid))
			return true;
		return false;
	}
	return true;
}



bool cSkillManager::UseSwitchMap(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	if (STATE_MAIN == g_StateType)
	{
//		int hpout;
// 		if (!Cost(hpout, Skilllv, sSkillID, UserID, 1, false))
// 		{
// 			g_pMainState->m_Channel.AddNewString("技能无法使用", 0, 3);
// 			return false;
// 		}
//		Cost(hpout, Skilllv, sSkillID, UserID, 1, true);

		cMyMap& map = g_pMainState->m_Map;
		switch (sSkillID)
		{
		case 3:	map.LoadMap(151, 10, "大唐官府"); break;
		case 25:map.LoadMap(104, 121, "方寸山"); break;
		case 44:map.LoadMap(88, 49, "化生寺"); break;
		case 58:map.LoadMap(27, 116, "女儿村"); break;
		case 70:map.LoadMap(159, 55, "天宫"); break;
		case 83:map.LoadMap(79, 40, "龙宫"); break;
		case 93:map.LoadMap(28, 18, "五庄观"); break;
		case 110:map.LoadMap(16, 55, "普陀山"); break;
		case 124:map.LoadMap(37, 60, "阴曹地府"); break;
		case 138:map.LoadMap(73, 60, "魔王寨"); break;
		case 149:map.LoadMap(103, 16, "狮驼岭"); break;
		case 163:map.LoadMap(175, 113, "盘丝岭"); break;
		case 180:map.LoadMap(33, 86, "凌波城"); break; //凌波城		
		case 192:map.LoadMap(61, 44, "无底洞"); break;//无底洞
		case 202:map.LoadMap(68, 63, "神木林"); break;//神木林
		}
	}
	return true;
}



