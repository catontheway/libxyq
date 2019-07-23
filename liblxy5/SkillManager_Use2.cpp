#include "_global.h"
#include "_txt.h"

static void cbCounter(int UserID)
{
	auto& ss = g_pMainState->m_FightWorkList[UserID].m_SkillSelectForCounter;
	if (ss.SkillID >= 0)
	{
		g_pMainState->m_FightWorkList[UserID].m_SkillSelect = ss;
		ss.SkillID = -1;
	}
};

//后发制人
bool cSkillManager::Use1后发(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
		return true;
	case 1:
		if (WaitForMagicPoint(UserID))
		{
			// 斩龙诀动画
			pUser->SetMagicSound(sSkillID);

			int MagicID = g_pMainState->m_SkillManager.GetSkill(sSkillID)->m_MagicID;
			vector<ulong> ids;
			if (MagicID)
			{
				ids.push_back(MagicID);
			}
			const auto& s = ctt::getSkillActs();
			forr(s, i)
			{
				if ((int)s[i].e == sSkillID)
				{
					const auto& u = s[i];
					if (u.u1)
					{
						ids.push_back(u.u1);
					}
					if (u.u2)
					{
						ids.push_back(u.u2);
					}
					if (u.u3)
					{
						ids.push_back(u.u3);
					}
					break;
				}
			}
			if (ids.empty())
			{
			}
			else
			{
				MagicID = ids[max(0, g_pMainState->m_pFightState->_turn) % ids.size()];
			}

			pUserList->SetMagiSufferID(/*968268166*/ MagicID,
				-10, &m_pFightState->m_FullSkill.m_SufferMagic[UserID]);
			stage += 1;
		}
		return true;
	case 2:
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		if (!pUser->m_MagicSuffer.m_NeedShow)
		{
			stage += 1;
			EffectSkill(Skilllv, sSkillID, UserID, TargetID);
			pUser->Set(POS_FIGHT_STAND);
		}
		return true;
	case 3:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUserList->m_work.pop_back();
		}
		return true;
	}
	return true;
}



bool cSkillManager::Use80龙卷飞沙(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	sFightWork* pTargetList = m_pFightState->m_pFightWorkList[TargetID];
	cObj* pUser = pUserList->m_pObj;
	cPropertyData* pUserData;
	pUser->GetPropertyData(pUserData);
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		while (!m_pFightState->m_ThreadSleep)
		{
			Sleep(1);  //等待线程
		}
		switch (sSkillID)
		{
		case 80:
			m_pFightState->m_IDtoLoad[0] = 0xA19EAB31;  //龙
			m_pFightState->m_IDtoLoad[1] = 0xF1F26922;  //电
			m_pFightState->m_IDtoLoad[2] = 0xD61E2519;  //背景
			break;
		case 131://飞沙走石
			m_pFightState->m_IDtoLoad[0] = 0x4DB67680;
			//			m_pFightState->m_IDtoLoad[1] = 0x49CBD108;
			break;
		default:
			ERRBOX;
			break;
		}
		m_pFightState->m_pFileToLoad[0] = &m_pFightState->m_FullSkill.m_FullSkilUP[0];
		m_pFightState->m_pFileToLoad[1] = &m_pFightState->m_FullSkill.m_FullSkilUP[1];
		m_pFightState->m_pFileToLoad[2] = &m_pFightState->m_FullSkill.m_FullSkilUP[2];
		ResumeThread(m_pFightState->m_hThread);
		stage = 1;
		return true;
	case 1:
		if (WaitForMagicPoint(UserID))
		{
			pUser->SetMagicSound(sSkillID);

			while (!m_pFightState->m_ThreadSleep)
			{
				Sleep(1);  //等待线程
			}
			int speed =  GetSpeed(sSkillID);
			for (int i = 0; i < 3; i++)
				m_pFightState->m_FullSkill.m_FullSkilUP[i].m_Picture.m_FrameGap = speed;

			//ulong FullMagicID = 0;
			//ulong FullMagicID2 = 0;
			//int Position = 1;
			int pos;
			int maxtarget;
			ulong magicid;
			bool upordown;
			bool toall;
			GetMagicAndNum秒几(Skilllv, sSkillID, UserID, TargetID, magicid, maxtarget, pos, upordown, toall);

			for (int i = 0; i < 2; i++)
				m_pFightState->m_FullSkill.m_FullSkilUP[i].m_Picture.m_FrameGap = GetSpeed(sSkillID);
			pUserList->m_MaxTargetNum = 0;
			int id;
			for (int i = 0; i < maxtarget; i++)
			{
				pUserList->targetlist[pUserList->m_MaxTargetNum] = GetTargetID(UserID, TargetID, i);
				id = pUserList->targetlist[pUserList->m_MaxTargetNum];
				if (id == UserID)continue;
				if (id != -1)
				{
					pUserList->m_NowTargetID = pUserList->targetlist[pUserList->m_MaxTargetNum];
					m_pFightState->SetMagicSuffer(id, pUser->GetDirection());
					m_pFightState->m_pFightWorkList[id]->m_bSufferFullSkill = true;
					pUserList->m_MaxTargetNum += 1;
				}
				else break;
			}
			stage += 1;
		}
		return true;
	case 2:

	{
		ulong id[3];
		int x1, y1;
		x1 = m_pFightState->m_pFightWorkList[TargetID]->m_pObj->GetX();
		y1 = m_pFightState->m_pFightWorkList[TargetID]->m_pObj->GetY();
		x1 = 280;
		y1 = 150;
		if (UserID >= 10)
		{
			x1 = g_640 - x1 + ((sSkillID == 131) ? 150 : 100);
			y1 = g_480 - y1 - 80;
		}
		if (m_pFightState->m_IDtoLoad[1] != 0)Sleep(0);//等待线程
		switch (sSkillID)
		{
		case 80:
			id[0] = 0xA19EAB31;  //龙 
			// 				id[1] = 0xD61E2519;  //背景
			// 				id[2] = 0xF1F26922;  //电
			id[2] = 0xD61E2519;  //背景
			id[1] = 0xF1F26922;  //电
			m_pFightState->m_FullSkill.SetMagicUp(0, id[0], x1, y1);
			m_pFightState->m_FullSkill.SetMagicUp(1, id[1], x1, y1);
			if (m_pFightState->m_IDtoLoad[2] != 0)Sleep(0);//等待线程
			m_pFightState->m_FullSkill.SetMagicUp(2, id[2], x1, y1);
			break;
		case 131://飞沙走石
			id[0] = 0x4DB67680;
			//				id[1] = 0x49CBD108;
			//				m_pFightState->m_FullSkill.SetMagicUp(1, id[1], x1,y1);
			m_pFightState->m_FullSkill.SetMagicUp(0, id[0], x1 - 170, y1 - 100);
			break;
		default: ERRBOX;
		}
		stage += 1;
	}
		return true;
	case 3:

	{
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		ulong MagicID = 0;
		//	bool toAll = 0;
		int LateTime;
		GetDelayAnd(sSkillID, LateTime, MagicID);

		//	int nowframe = m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame();
		//			int maxframe = m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame();
		if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() == m_pFightState->m_FullSkill.m_FullSkilUP[0].GetMaxFrame() - LateTime)
		{
			//伤害判定
			for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
			{
				int id = pUserList->targetlist[i];
				if (id == -1)
				{
					stage += 1;
					return true;
				}
				if ((rand() % 100) < CheckMagicHit(Skilllv, sSkillID, UserID, id))
				{
					EffectSkill(Skilllv, sSkillID, UserID, id);
					if (g_pMainState->m_FightWorkList[id]._magicCri)
					{
						g_pMainState->m_FightWorkList[id]._magicCri = 0;
						g_pMainState->m_FightWorkList[id].m_pObj->SetMagicCri(&m_pFightState->_magicCri);
					}

				}
				m_pFightState->SwitchMagicSuffer(id);
			}
//			int dustbin;
//			Cost(dustbin, Skilllv, sSkillID, UserID, pUserList->m_MaxTargetNum, true);
			Cost(UserID, sSkillID, pUserList->m_MaxTargetNum, true);
			stage += 1;
		}

	}
		return true;
	case 4:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			pUserList->m_work.pop_back();
			for (int i = 0; i < 3; i++)
				m_pFightState->m_FullSkill.m_FullSkilUP[i].m_NeedShow = false;

			cPropertyData* pTargetdata;
			m_pFightState->m_pFightWorkList[TargetID]->m_pObj->GetPropertyData(pTargetdata);
			if (1 > pUserData->m_HP)
			{
				if (UserID < 10)
					pUserList->m_sufferDirection = 3;
				else pUserList->m_sufferDirection = 7;
				g_pMainState->m_pFightState->SetDie(UserID);
				pTargetdata->m_CP /= 2;
				return true;
			}


			CoutComboMagic(sSkillID, pUserData, UserID, pTargetdata);
		}
		return true;
	}
	return true;

}


bool cSkillManager::Use84龙吟(int Skilllv, int sSkillID, int UserID, int TargetID)
{//龙吟
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	cObj* pUser = pUserList->m_pObj;
	cObj* pTarget = m_pFightState->m_pFightWorkList[TargetID]->m_pObj;
	int& stage = pUserList->GetWork()->stage;
	switch (stage)
	{
	case 0:

	{
// 		int hpout = 0;
// 		Cost(hpout, Skilllv, sSkillID, UserID, 1, true);
// 		if (hpout)
// 		{
// 			SetDamage(hpout, UserID);
// 		}
		Cost(UserID, sSkillID, 1, true);

		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		while (!m_pFightState->m_ThreadSleep)
		{
			Sleep(1);  //等待线程
		}

		m_pFightState->m_pFileToLoad[0] = &m_pFightState->m_FullSkill.m_SufferMagic[TargetID];
		m_pFightState->m_IDtoLoad[0] = 0x5EC2D5BB;
		m_pFightState->m_pFileToLoad[1] = &m_pFightState->m_FullSkill.m_FullSkilUP[0];
		m_pFightState->m_IDtoLoad[1] = 0x9FE48849;
		m_pFightState->m_pFileToLoad[2] = &m_pFightState->m_FullSkill.m_FullSkilUP[1];
		m_pFightState->m_IDtoLoad[2] = 0x63605C8D;
		for (int i = 0; i < 3; i++)
			m_pFightState->m_pFileToLoad[i]->m_Picture.m_FrameGap = 2;
		ResumeThread(m_pFightState->m_hThread);
		stage = 1;
	}
		return true;
	case 1:
		if (WaitForMagicPoint(UserID))
		{
			pUser->SetMagicSound(sSkillID);
			if (m_pFightState->m_IDtoLoad[0] != 0)Sleep(1);//等待线程
			int speed = GetSpeed(sSkillID);
			for (int i = 0; i < 3; i++)
				m_pFightState->m_FullSkill.m_FullSkilUP[i].m_Picture.m_FrameGap = speed;

			pUserList->m_MaxTargetNum = 0;
			int id;
			for (int i = 0; i < 10; i++)
			{
				id = GetTargetID(UserID, TargetID, i);
				if (UserID == id)continue;
				if (-1 == id)break;
				pUserList->targetlist[pUserList->m_MaxTargetNum] = id;
				m_pFightState->SetMagicSuffer(id, pUser->GetDirection());
				m_pFightState->m_pFightWorkList[id]->SetMagiSufferID(0x5EC2D5BB, 2, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID]);
				m_pFightState->m_pFightWorkList[id]->m_bSufferFullSkill = true;
				pUserList->m_MaxTargetNum += 1;
			}
			pUserList->m_NowTargetIdx = -1;
			for (int i = 0; i < 3; i++)
				m_pFightState->m_FullSkill.m_FullSkilUP[i].m_NeedShow = false;
			stage += 1;
		}
		return true;
	case 2:
		if (pTarget->m_MagicSuffer.GetFrame() >= 4)
		{
			if (TargetID > 9)
			{
				m_pFightState->m_FullSkill.SetMagicUp(0, 0x63605C8D, 300, 150);
				m_pFightState->m_FullSkill.SetMagicUp(1, 0x9FE48849, 230, 200);
			}
			else
			{
				m_pFightState->m_FullSkill.SetMagicUp(0, 0x63605C8D, 400, 250);
				m_pFightState->m_FullSkill.SetMagicUp(1, 0x9FE48849, 430, 300);
			}
			stage += 1;
		}
		return true;
	case 3:
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUser->Set(POS_FIGHT_STAND);
		}
		if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetNowFrame() == 3)
		{
			cPropertyData* data;
			pUser->GetPropertyData(data);
			//	int dam=Skilllv+data->m_Lv/2;
			//伤害判定
			while (pUserList->NextTarget(m_pFightState, sSkillID))
			{
				EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);
				m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.m_NeedShow = false;
				m_pFightState->SwitchMagicSuffer(pUserList->m_NowTargetID);
			}
			stage += 1;
		}
		return true;
	case 4:
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUser->Set(POS_FIGHT_STAND);
			pUserList->m_work.pop_back();
			cPropertyData* pPet;
			pUserList->m_pObj->GetPropertyData(pPet);
			if (1 > pPet->m_HP)
			{
				if (UserID < 10)
					pUserList->m_sufferDirection = 3;
				else pUserList->m_sufferDirection = 7;
				g_pMainState->m_pFightState->SetDie(UserID);
				cPropertyData *pTargetData;
				pTarget->GetPropertyData(pTargetData);
				pTargetData->m_CP /= 2;
				return true;
			}
		}
		return true;
	}
	return true;
}



bool cSkillManager::Use107巨岩破泰山天罗地网(int Skilllv, int sSkillID, int UserID, int TargetID)
{
	sFightWork* pUserList = m_pFightState->m_pFightWorkList[UserID];
	sFightWork* pTargetList = &g_pMainState->m_FightWorkList[TargetID];
	cObj* pUser = pUserList->m_pObj;
	cObj* pTarget =pTargetList->m_pObj;
	int& stage = pUserList->GetWork()->stage;

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
	switch (stage)
	{
	case 0:
		if (1)
		{
// 			int hpout = 0;
// 			Cost(hpout, Skilllv, sSkillID, UserID, 1, true);
// 			if (hpout)
// 			{
// 				SetDamage(hpout, UserID);
// 			}
			Cost(UserID, sSkillID, 1, true);
			pUser->Set(POS_MAGIC);
			pUser->SetSound(POS_MAGIC);
			stage = 1;
		}
		return true;
	case 1:
		if (WaitForMagicPoint(UserID))
		{

			if (sSkillID != 107)
				pUser->SetMagicSound(sSkillID);//声音
			else
				pUser->SetMagicSound(sSkillID, 18);//巨岩破的前半段声音不要了
			ulong MagicID;
			int MagicPos;
			bool MagicUporDown;
			bool  toAll;
			bool bAtk;
			int maxnum;
			GetMagicAndNum秒几(Skilllv, sSkillID, UserID, TargetID, MagicID, maxnum, MagicPos, MagicUporDown, toAll);

			int magicspeed = GetSpeed(MagicID/*sSkillID*/);
			bAtk = GetSkill需要目标被打动画(sSkillID);
			pUserList->m_MaxTargetNum = 0;

			for (int i = 0; i < maxnum; i++)
			{
//				pUserList->targetlist[pUserList->m_MaxTargetNum] = GetTargetID(UserID, TargetID, i);
				int id = pUserList->targetlist[pUserList->m_MaxTargetNum];
				if (-1 == id)break;
				if (UserID == id)continue;
				pUserList->m_MaxTargetNum += 1;
			}
			if (toAll)
			{
				for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
				{
					pUserList->m_NowTargetID = pUserList->targetlist[i];

					m_pFightState->SetMagicSuffer(pUserList->m_NowTargetID, pUser->GetDirection());
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_bSufferFullSkill = toAll;

				}

				m_pFightState->m_FullSkill.SetMagicUp(0, MagicID, x/*pTarget->GetX()*/, y/*pTarget->GetY()*/ - 200);
				m_pFightState->m_FullSkill.m_FullSkilUP[0].m_Picture.m_FrameGap = magicspeed;
			}
			else
			{
				for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
				{
					pUserList->m_NowTargetID = pUserList->targetlist[i];
					m_pFightState->SetMagicSuffer(pUserList->m_NowTargetID, pUser->GetDirection());

					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_bSufferFullSkill = toAll;
					//0x565A6FE1
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->SetMagiSufferID(MagicID, -10, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID], MagicUporDown);
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.m_y -= 140;
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.m_FrameGap = magicspeed;


				}
			}
			pUserList->m_NowTargetIdx = -1;
			stage = 19;
		}
		return true;
	case 19:
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUserList->m_pObj->Set(POS_FIGHT_STAND);
		}
		StageWaitSleep(15, UserID, 20);
		break;
	case 20:
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUserList->m_pObj->Set(POS_FIGHT_STAND);
		}
		switch (sSkillID)
		{
		case 162:
		case 107:
			pUserList->m_NowTargetIdx = -1;
			if (m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.m_y == m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->GetY())
			{
				if (sSkillID == 107)
				{
					for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
					{
						pUserList->m_NowTargetID = pUserList->targetlist[i];
						int umid = GetSkill(sSkillID)->m_MagicID; // 0xDF4C3BE3
						m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->SetMagiSufferID(umid, -10, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID], true);
					}
				}
				pUserList->m_NowTargetIdx = -1;
				stage = 3;
			}
			else
			{
				for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
				{
					pUserList->m_NowTargetID = pUserList->targetlist[i];
					m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.SetY(m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->m_MagicSuffer.GetY() + 20);
				}
				pUserList->m_NowTargetIdx = -1;
			}
			break;

		case 2087:
			m_pFightState->m_FullSkill.m_FullSkilUP[0].SetY(m_pFightState->m_FullSkill.m_FullSkilUP[0].GetY() + 40);
			if (m_pFightState->m_FullSkill.m_FullSkilUP[0].GetY() == y)
			{
				pUserList->m_NowTargetIdx = -1;
				stage = 3;
			}
			break;
		default:
			return false;
		}
		break;
	case 3:  //附加BUFF
	{
		if (m_pFightState->WaitPosEnd(UserID))
		{
			pUserList->m_pObj->Set(POS_FIGHT_STAND);
		}

		ulong MagicID;
		//bool toAll=GetSkillToAll(sSkillID);
		int LateTime; //伤害计算延时

		GetDelayAnd(sSkillID, LateTime, MagicID);

		for (int i = 0; i < pUserList->m_MaxTargetNum; i++)
		{
			pUserList->m_NowTargetID = pUserList->targetlist[i];

			m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_pObj->SetSound(POS_SUFFER);//声音
			m_pFightState->SwitchMagicSuffer(pUserList->m_NowTargetID);
			m_pFightState->m_pFightWorkList[pUserList->m_NowTargetID]->m_NowBeAtkowner = UserID;
			EffectSkill(Skilllv, sSkillID, UserID, pUserList->m_NowTargetID);
			if (g_pMainState->m_FightWorkList[pUserList->m_NowTargetID]._magicCri)
			{
				g_pMainState->m_FightWorkList[pUserList->m_NowTargetID]._magicCri = 0;
				g_pMainState->m_FightWorkList[pUserList->m_NowTargetID].m_pObj->SetMagicCri(&m_pFightState->_magicCri);
			}

		}
		if (sSkillID == 107) //泰山压顶延时下吧
			stage = 4;
		else
			stage = 5;
	}
		return true;
	case 4://等待主角动作完成
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			if (sSkillID == 162)
			{
				pUser->SetMagicSound(-1);//声音
			}
			pUserList->m_pObj->Set(POS_FIGHT_STAND);
			pUserList->m_work.pop_back();
			m_pFightState->m_FullSkill.m_FullSkilUP[0].m_NeedShow = false;

			cbCounter(UserID);

			cPropertyData* targetdata;
			pTarget->GetPropertyData(targetdata);
			cPropertyData* pPet;
			pUser->GetPropertyData(pPet);
			if (1 > pPet->m_HP)
			{
				if (UserID < 10)
					pUserList->m_sufferDirection = 3;
				else pUserList->m_sufferDirection = 7;
				g_pMainState->m_pFightState->SetDie(UserID);
				targetdata->m_CP /= 2;
				return true;
			}



			CoutComboMagic(sSkillID, pPet, UserID, targetdata);
		}
		return true;
	case 5://等待主角动作完成
		if (m_pFightState->WaitPosEnd(UserID) || (pUser->m_NowPos == POS_FIGHT_STAND))
		{
			pUserList->m_pObj->Set(POS_FIGHT_STAND);
		}
		StageWaitSleep(10, UserID, 4);
		return true;
	}
	return true;
}


// 月光
bool cSkillManager::Use2105(int Skilllv, int sSkillID, int UserID, int TargetID)
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


	ulong MagicID;
	int MagicPos;
	bool MagicUporDown;
	int maxnum;
	bool toAll;
	GetMagicAndNum秒几(Skilllv, sSkillID, UserID, TargetID, MagicID, maxnum, MagicPos, MagicUporDown, toAll);
	int magicspeed = GetSpeed(/*sSkillID*/MagicID);
	bool bAtk = true;// GetSkill需要目标被打动画(sSkillID);

	auto moon = [&]()
	{
//		pUserList->m_NowTargetID = TargetID; // pUserList->targetlist[i];
		if (bAtk)
		{
			m_pFightState->SetMagicSuffer(TargetID, pUser->GetDirection());
		}
		pTargetList->m_bSufferFullSkill = false;
		pTargetList->SetMagiSufferID(MagicID, MagicPos, &m_pFightState->m_FullSkill.m_SufferMagic[TargetID], MagicUporDown);
		pTargetList->m_pObj->m_MagicSuffer.m_FrameGap = magicspeed;
	};

	auto isOver = [&](cObj *ptar)
	{
		ulong MagicID2;
		int LateTime;
		GetDelayAnd(sSkillID, LateTime, MagicID2);
		if (pUserList->_moon == 0)
		{
			LateTime -= 6;
		}
		else
		{
			LateTime += 12;
		}
		bool bover = false;
	
		if (!ptar->m_MagicSuffer.m_NeedShow)
		{
			bover = true;
		}
		else
		{
			if (LateTime >= ptar->m_MagicSuffer.m_pFile->GetMaxFrame())
			{
				LateTime = ptar->m_MagicSuffer.m_pFile->GetMaxFrame() - 1;
			}
			if (ptar->m_MagicSuffer.GetFrame() == ptar->m_MagicSuffer.m_pFile->GetMaxFrame() - LateTime)
			{
				bover = true;
			}
		}
		return bover;
	};

	auto over = [&, pTargetList, pTarget]()
	{
//		pUserList->m_NowTargetID = TargetID; // pUserList->targetlist[i];
		if (bAtk)
		{
			m_pFightState->SwitchMagicSuffer(TargetID);
			m_pFightState->m_pFightWorkList[TargetID]->m_pObj->SetSound(POS_SUFFER);//声音
			m_pFightState->m_pFightWorkList[TargetID]->m_NowBeAtkowner = UserID;
		}

		if ((rand() % 100) < CheckMagicHit(Skilllv, sSkillID, UserID, TargetID))
		{
			EffectSkill(Skilllv, sSkillID, UserID, TargetID);
			if (pTargetList->_magicCri)
			{
				pTargetList->_magicCri = 0;
				pTarget->SetMagicCri(&m_pFightState->_magicCri);
			}
		}

// 		cPropertyData* pPet;
// 		pUser->GetPropertyData(pPet);
		if (1 > pUserData->m_HP)
		{
			if (UserID < 10)
				pUserList->m_sufferDirection = 3;
			else pUserList->m_sufferDirection = 7;
			g_pMainState->m_pFightState->SetDie(UserID);
			pUserData->m_CP /= 2;
//			return true;
		}
	};

	switch (stage)
	{
	case 0:
	{
// 		int hpout = 0;
// 		if (Cost(hpout, Skilllv, sSkillID, UserID, 1, true))
// 		{
// 			SetDamage(hpout, UserID);
// 		}
		Cost(UserID, sSkillID, 1, true);
		pUser->Set(POS_MAGIC);
		pUser->SetSound(POS_MAGIC);
		stage = 1;
		pUserList->_moon = 0;
	}
		return true;
	case 1:
		if (WaitForMagicPoint(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->SetStatic(false);
			pUser->SetMagicSound(sSkillID);//声音

//			pUserList->m_MaxTargetNum = 1;// maxnum;
//			pUserList->targetlist[0] = TargetID;
			moon();
			stage += 1;
		}
		return true;
	case 2:
	{
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
			stage += 1;
		}
	}
	case 3:
	{
		bool bover = isOver(g_pMainState->m_FightWorkList[TargetID/*pUserList->m_NowTargetID*/].m_pObj);
		if (bover)
		{
			over();
			stage = 4;
// 			if (pUserList->_moon == 0)
// 			{
// 				stage = 4;
// 			}
// 			else
// 			{
// 				stage = 5;
// 			}
		}
	}
		return true;
	case 4://等待主角动作完成
		if (m_pFightState->WaitPosEnd(UserID) || pUser->m_pShowData[0]->m_isStatic)
		{
			pUser->Set(POS_FIGHT_STAND);
			pUser->SetStatic(false);
			stage = 5;
		}
		return true;
	case 6:
		StageWaitSleep(60, UserID, 4);
		return true;
	case 5:
	{
		if (++pUserList->_moon < maxnum)
		{
			if (pUserList->_moon == 1)
			{
				pUserList->m_NowTargetID = TargetID;
			}
			int tid = g_pMainState->m_AI.find追击反间月光(UserID, 4, true);
			if (tid < 0)
			{
				pUser->SetMagicSound(-1);//声音
				pUserList->m_work.pop_back();
				pUserList->m_SkillSelect.TargetID = pUserList->m_NowTargetID;
				return true;
			}
			else
			{
//				pUserList->targetlist[0] = tid;
				pUserList->m_SkillSelect.TargetID = tid;
//				pUserList->m_NowTargetID = TargetID;
// 				moon();
// 				stage = 3;
				stage = 1;
				return true;
			}
		}
		else
		{
			pUser->SetMagicSound(-1);//声音
			pUserList->m_work.pop_back();
			pUserList->m_SkillSelect.TargetID = pUserList->m_NowTargetID;
		}

	}
		return true;

	}
	return true;
}

