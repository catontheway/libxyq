#include "_global.h"


bool CMainState::FindObj()
{
	m_ObjNumber = 0;

	//从NPC中找
	int xmap, ymap;
	xmap = m_Map.m_pMap->GetXCenter();
	ymap = m_Map.m_pMap->GetYCenter();
	for (int i = 0; i < m_Map.m_numberOfNpc; i++)
	{
		if (abs(m_Map.m_pNpc[i]->GetX() - xmap) < g_640 &&
			abs(m_Map.m_pNpc[i]->GetY() - ymap) < g_480)
		{
			if (m_Map.m_pNpc[i]->GetShow())
			{
				m_pObj[m_ObjNumber] = m_Map.m_pNpc[i];
				m_ObjNumber++;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (m_FightWorkList[i].isExist)
		{
			m_pObj[m_ObjNumber] = m_FightWorkList[i].m_pObj;
			m_ObjNumber += 1;
		}
	}
	m_pObj[m_ObjNumber] = 0;

	m_NumShow = 0;
	for (int i = 0; i < m_ObjNumber; i++)
	{
		m_pShowTurn[m_NumShow] = m_pObj[i];
		m_ShowTurnType[m_NumShow] = 0;
		m_NumShow += 1;
		if (m_pObj[i] == g_pHeroObj && _wasHeadTop.m_NowID)
		{
			m_pShowTurn[m_NumShow] = (cObj*)&_wasHeadTop;
			m_ShowTurnType[m_NumShow] = 1;
			m_NumShow += 1;
		}
	}
	int xgap, ygap;
	for (int i = 0; i < m_Map.m_numofJianZhu; i++)
	{
		cWasFile* m_pFile = m_Map.m_pJianZhu[i];
		xgap = abs(m_pFile->GetX() - m_Map.m_pMap->GetXCenter());
		if (xgap > g_640)continue;
		ygap = abs(m_pFile->GetY() - m_Map.m_pMap->GetYCenter());
		if (ygap > g_480)continue;

		m_pFile->Load(m_Map.m_JianZhuID[i]);
		m_pShowTurn[m_NumShow] = m_pFile;
		m_ShowTurnType[m_NumShow] = 1;
		m_NumShow += 1;
		if (xgap > g_half320 + 32 || ygap > g_half240 + 32)
			m_pFile->m_NeedShow = true;
	}


	for (int i = 0; i < m_ObjNumber; i++)
	{
		if (-1 == m_pObj[i]->m_NowPos)
			m_pObj[i]->Set(POS_STAND);
	}

	return true;
}





cObj* CMainState::GetObjPointAt(long x, long y)
{
	for (int i = 0; i < MAX_OBJ_NUM; i++)
	{
		if (m_pObj[i])
		{
			if (m_pObj[i]->isPointOn(x, y))
			{
				if (m_pObj[i] == g_pHeroObj)
					continue;//忽略主角
				if (m_pObj[i]->m_ScriptPath.find("transmit") != string::npos)
				{
					if (y < m_pObj[i]->GetY() - 5)
					{
						continue;
					}
				}
				return m_pObj[i];
			}
		}
	}
	return 0;
}



bool CMainState::MoveObj()
{
	for (int i = 0; i < m_ObjNumber; i++)
	{
		if (m_pObj[i] == 0)continue;
		cObj* p = m_pObj[i];
		if (p->m_AstartPathIndex == -2)continue;
		//寻路
		if (-1 < p->m_AstartPathIndex)
		{
			if (!p->Move())
			{
				p->m_AstartPathIndex -= 2;
				if (-1 >= p->m_AstartPathIndex)
				{
					p->m_AstartPathIndex = -2;
					p->Set(POS_STAND);
					continue;
				}

				int heroXPos = p->m_AstartPathVecs[p->m_AstartPathIndex].x;
				int heroYPos = p->m_AstartPathVecs[p->m_AstartPathIndex].y;
				p->setNextTargetOnAstart(heroXPos, heroYPos);
				if (-1 != p->m_AstartPathIndex)
				{
					p->Move();
				}
			}
		}
		else
			p->Move();//直走
	}
	return true;
}




bool CMainState::FindCharacter(cObj*& data, int CharacterID)
{
	data->SetDataType(INDEXTYEP_CHARACTER);
	cCharacter* p = (cCharacter*)data->m_pIndex;
	if (!p)
	{
		p = new cCharacter;
		data->m_pIndex = p;
	}
	p->SetData(&m_pCharacterDataList[CharacterID]);
	return true;
}



bool CMainState::FindPetData(cPet* pPet, int PetID)
{
	if (PetID < c_PetNumber)
	{
		pPet->SetData(m_PetDataManager.GetPetData(PetID));
		pPet->m_PetData.m_Name = pPet->GetData()->m_Name;
		pPet->m_PetData.modeid = PetID;
		return true;
	}
	return false;
}

bool CMainState::FindData(cObj* data, int Id)
{
	if (!data)
	{
		ERRBOX;
		return false;
	}
	if (Id < 1000)
	{
		data->SetDataType(INDEXTYEP_PET);
		return FindPetData((cPet*)data->m_pIndex, Id);
	}
	if (Id < 2000)
	{
		Id -= 1000;
		data->SetDataType(INDEXTYEP_NPC);
		return FindNPCData((cNpc*&)data->m_pIndex, Id);
	}
	else
	{
		Id -= 2000;
		data->SetDataType(INDEXTYEP_CHARACTER);
		return FindCharacter(data, Id);
	}
}

bool CMainState::FindNPCData(cNpc*& data, int NpcID)
{
	if (!data)
	{
		data = new cNpc;
	}
	data->m_pNpcData = &m_pNpcList[NpcID];
	return true;
}





cObj* CMainState::FindObjByNpc(sNpc* pNpc)
{
	for (int i = 0; i < m_Map.m_numberOfNpc; i++)
	{
		cObj* p = m_Map.m_pNpc[i];
		if (!p->m_TrueName.GetString().compare(pNpc->m_name))
			if (p->GetX() == pNpc->m_x * 20)
				if (p->GetY() == g_pMainState->m_Map.m_pMap->m_Height - pNpc->m_y * 20)
				{
			return m_Map.m_pNpc[i];
				}

	}
	return 0;
}



cObj* CMainState::FindObjByName(string Name)
{
	for (int i = 0; i < m_FightWorkList.size(); i++)
	{
		if (m_FightWorkList[i].isExist == false)continue;
		if (!m_FightWorkList[i].m_pObj->m_TrueName.GetString().compare(Name))
		{
			return m_FightWorkList[i].m_pObj;
		}
	}
	for (int i = 0; i < m_Map.m_numberOfNpc; i++)
	{

		if (!m_Map.m_pNpc[i]->m_TrueName.GetString().compare(Name))
		{
			return m_Map.m_pNpc[i];
		}

	}
	return 0;
}






void CMainState::ShowObj()
{
	SortShow();
	for (int i = 0; i < m_NumShow; i++)
	{
		switch (m_ShowTurnType[i])
		{
		case 0:
		{
			cObj* p = (cObj*)m_pShowTurn[i];
			if (p->GetShow())
			{
				m_Canvas.Add(p->GetShadow(), 0);
				if (p->m_Foot.m_NowID)
				{
					m_Canvas.Add(&p->m_Foot, 0);
				}
				p->Show(&m_Canvas);
			}

		}
			break;
		case 1:

		{
			cWasFile* p = (cWasFile*)m_pShowTurn[i];
			m_Canvas.Add(p, 0);
		}
			break;
		}
	}
}






bool CMainState::TeamFollow()
{
	int preid = 0;
	for (int i = 1; i < 5; i++)
	{
		//	fightid = m_InterfaceTeam.GetTeamTurn(i);
		if (!m_FightWorkList[i].isExist)
		{
			if (m_FightWorkList[i].m_pObj)
			{
				m_FightWorkList[i].m_pObj->SetXY(g_pHeroObj->GetX(), g_pHeroObj->GetY());
			}
			continue;
		}
		cObj* obj = m_FightWorkList[i].m_pObj;

		if (abs(obj->m_xPos - obj->m_xTarget) + abs(obj->m_yPos - obj->m_yTarget) < 25 || obj->m_AstartPathIndex < -1)
		{
			preid = i - 1;
			while (!m_FightWorkList[preid].isExist)
			{
				preid -= 1;
				if (preid < 0)return false;
			}
			cObj* obj2 = m_FightWorkList[preid].m_pObj;//1preid

			float dis = abs(obj->m_xPos - obj2->m_xPos) + abs(obj->m_yPos - obj2->m_yPos);
			if (dis > 100)
			{
				CoutPoint(50, obj->m_xPos, obj->m_yPos, obj2->m_xPos, obj2->m_yPos, obj->m_xTarget, obj->m_yTarget);
				obj->m_AstartPathIndex = -3;
			}
		}
	}
	return true;

// 	// i1队伍 不是list
// 	int preid = 0;
// 	for (int i1 = 0; i1 < 5; i1++)
// 	{
// // 		if (i1 >= m_InterfaceTeam.m_LeaveBegin)
// // 		{
// // 			continue;
// // 		}
// 		int i = m_InterfaceTeam.GetTeamTurn(i1);
// 		if (i == m_HeroID)
// 		{
// 			continue;
// 		}
// 		if (!m_FightWorkList[i].isExist)
// 			continue;
// 
// 		cObj* obj = m_FightWorkList[i].m_pObj;
// 
// 		if (abs(obj->m_xPos - obj->m_xTarget) + abs(obj->m_yPos - obj->m_yTarget) < 15)
// 		{
// 			preid = i1 - 1;
// 			if (i1 == 0)
// 			{
// 				preid = 4;
// 			}
// 			int preid2 = m_InterfaceTeam.GetTeamTurn(preid);
// 			while (!m_FightWorkList[preid2].isExist)
// 			{
// 				if (--preid < 0)
// 				{
// 					return false;
// 				}
// 				preid2 = m_InterfaceTeam.GetTeamTurn(preid);
// 			}
// 			cObj* obj2 = m_FightWorkList[preid2].m_pObj;//1preid
// 
// 			float dis = abs(obj->m_xPos - obj2->m_xPos) + abs(obj->m_yPos - obj2->m_yPos);
// 			if (dis > 100)
// 			{
// 				CoutPoint(50, obj->m_xPos, obj->m_yPos, obj2->m_xPos, obj2->m_yPos, obj->m_xTarget, obj->m_yTarget);
// 				obj->m_AstartPathIndex = -3;
// 			}
// 		}
// 	}
// 	return true;
}



