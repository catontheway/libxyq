#include "_global.h"


bool CMainState::ProcessInput()
{
	static int time;
	m_isMouseOnMap = true;
	if (m_pNowSelect) //把之前高亮的对象取消高亮
	{
		m_pNowSelect->SetShine(false);
		m_pNowSelect = 0;
	}
//	if (g_GlobalValues[9] < 3)
	ProcessInterface();
	if (g_StateType == STATE_MAIN)
	{
		m_Menu.ProcessInput();
	}
	

// 	if (Keyboard.GetKeyState(DIK_X))
// 	{
// 		Keyboard.SetLock(DIK_X);//仙灵店铺
// 	
// 		int xianling = g_pMainState->m_GlobalButton[3];
// 		if (xianling > 0)
// 		{
// 			if (xianling > 5)
// 			{
// 				g_pMainState->m_GlobalButton[3] = 5;
// 				xianling = 5;
// 			}
// 			g_pMainState->m_InterFaceBuy.Open(xianling + 87);
// 		}
// 	}
	
#if _DEBUG
	if (Keyboard.GetKeyState(DIK_Z))
	{
		Keyboard.SetLock(DIK_Z);
		m_WorldMap.OnOff(!m_WorldMap.m_NeedShow);
	}
#endif
	//S键按下
	if (Keyboard.GetKeyState(DIK_S))
	{
		Keyboard.SetLock(DIK_S);
		m_InterfaceSystem.OnOff(!m_InterfaceSystem.m_NeedShow);
	}

	if (Keyboard.GetKeyState(DIK_T))
	{
		Keyboard.SetLock(DIK_T);
		m_InterfaceTeam.OnOff(!m_InterfaceTeam.m_NeedShow);
	}
// 	if (g_StateType != STATE_FIGHT)
// 	{
// 		if (Keyboard.GetKeyState(DIK_LSHIFT))
// 		{
// 			Keyboard.SetLock(DIK_LSHIFT);
// 			cct::get()->switch加点方案();
// 		}
// 		else if(Keyboard.GetKeyState(DIK_RSHIFT))
// 		{
// 			Keyboard.SetLock(DIK_RSHIFT);
// 			cct::get()->switch加点方案();
// 		}
// 	}

	//TAB  小地图
	if (Keyboard.GetKeyState(DIK_TAB))
	{
		Keyboard.SetLock(DIK_TAB);
		m_InterfaceSmallMap.OnOff(!m_InterfaceSmallMap.m_NeedShow);
		return true;
	}
	if (m_isMouseOnMap && !g_pMainState->_autoGhost)
	{
		int xMove = 0;
		int yMove = 0;
		bool bMove = false;
		if (Keyboard.GetKeyState(DIK_LEFT))
		{
			xMove = -20;
			bMove = true;
			m_Cursor.m_FollowMode = false;
		}
		if (Keyboard.GetKeyState(DIK_RIGHT))
		{
			xMove = 20;
			bMove = true;
			m_Cursor.m_FollowMode = false;
		}
		if (Keyboard.GetKeyState(DIK_UP))
		{
			yMove = -20;
			bMove = true;
			m_Cursor.m_FollowMode = false;
		}
		if (Keyboard.GetKeyState(DIK_DOWN))
		{
			yMove = 20;
			bMove = true;
			m_Cursor.m_FollowMode = false;
		}
		if (bMove)
		{
			cObj* pUser = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
			pUser->m_AstartPathIndex = -1;
			pUser->setNextTargetOnAstart((float)(pUser->GetX() +xMove), (float)(pUser->GetY()+yMove));
		}
	}
	
    m_Cursor.Process();
	return true;
}



bool CMainState::Give(int CharID, sItem2* pItem)
{
	m_InterfaceItem.GetItem(CharID, pItem);
	return true;
}




void CMainState::SetMouseOnMap(bool lock)
{
	m_isMouseOnMap = lock;
	m_Cursor.m_FollowMode = false;
}


cTaskFather* CMainState::FindTaskByID(int ID)
{
	switch (ID)
	{
	case 0:return &m_TaskNormal;
	case 2:return &m_TaskBangPai;
	case 30:return &m_TaskBaoTu;
	case 35:return &m_TaskHuoDong;
	case 40:return &m_TaskZhuaGui;
	case TASK_TYPE_FUBEN: return &m_TaskFB;
	case 1003:return &m_taskSM;
	case TASK_TYPE_ZHUXIAN: return &m_ZhuXian;
	case 2008:return &m_ZhiXian;
	case 2009:return &m_ZhiXian2;
	case 2010:return &m_ZhiXian3;
	default:
		ERRBOX;
		break;
	}
	return 0;
}




void CMainState::SetDialogList(string name, ulong id)
{
	for (int i = 0; i < m_DialogList.size(); i++)
	{
		if (0 == m_DialogList[i].name.compare(name))
		{
			return;
		}
	}
	sDialogList list;
	list.name = name;
	list.idlist = id;
	m_DialogList.push_back(list);
}



void CMainState::SetDialogList(cObj* pObj)
{
	sDialogList list;
	list.name = pObj->m_TrueName.GetString();
	for (int i = 0; i < m_DialogList.size(); i++)
	{
		if (0 == m_DialogList[i].name.compare(list.name))
		{
			return;
		}
	}
	list.idlist = pObj->GetID(POS_DIALOG);
	m_DialogList.push_back(list);
}




void CMainState::SetDialogListPet(string name, ePetID petid, bool bJinJie)
{
	ulong id = m_PetDataManager.GetPetData(petid)->m_dialoghead[bJinJie];
	SetDialogList(name, id);
}





void CMainState::SetDialogListNpc(string name, int npcid)
{
	if (npcid > 999)npcid -= 1000;
	sDialogList list;
	list.name = name;
	list.idlist = m_pNpcList[npcid].m_dialog;
	m_DialogList.push_back(list);  
}

void CMainState::SetDialogListPC(string name, int pcid)
{
	if (pcid > 1999)pcid -= 2000;
	sDialogList list;
	list.name = name;
	list.idlist = m_pCharacterDataList[pcid].m_Head[0].m_dialog;
	m_DialogList.push_back(list);
}







