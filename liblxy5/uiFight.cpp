#include "_global.h"
static cInterfacePetSkill s_uiPetSkill;
static void setMiaoshuDesc(string s)
{
	auto& ms = g_pMainState->m_pFightState->m_MiaoShu;
	if (s.empty())
	{
		ms.SetTime(1);
		return;
	}
	if (s == ms.GetString())
	{
		return;
	}
	ms.SetString(s);
	ms.SetTime(0xFFFF);
	ms.UpdateXCenter();
}

bool cInterfaceFight::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Describe.Init();
	m_TitleT.SetColor(RGB(255, 255, 255));
	m_SkillPreSelectT.SetColor(RGB(255, 255, 255));
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;

	//召唤召唤兽
	m_Button.Load(0x79D01E0E);
	ccm::get()->pushWdf("战斗召唤面板按钮", 0x79D01E0E);
	m_Button.SetStatic(true);
	m_PetBack.Load(0xE87F26E1);
	ccm::get()->pushWdf("战斗召唤面板", 0xE87F26E1);
	////////////////////////////////////////////////////////////////////////// 呵呵哒 战斗召唤
	m_PetPage = 0;

	m_UpB.Load(0x08E2D199);
	ccm::get()->pushWdf("战斗召唤面板按钮上", 0x08E2D199);
	m_UpB.SetStatic(true);
	m_DownB.Load(0xC013B53B);
	ccm::get()->pushWdf("战斗召唤面板按钮下", 0xC013B53B);
	m_DownB.SetStatic(true);

	ccm::get()->pushWdf("战斗召唤面板select", 0xF151309F);
	for (int i = 0; i < 2; i++)
	{
		m_PetSelectBack[i].Load(0xF151309F);
		m_PetSelectBack[i].SetStatic(true);
		m_PetSelectBack[i].SetFrame(1);
		m_PetSelectBack[i].SetxOffset(30);
	}
	//道具
	m_ItemSelectFrame.Load(0x6F88F494);
	m_ItemSelectFrame.m_NeedShow = false;
	m_ItemBack.Load(0xE3AEF018);
	ccm::get()->pushWdf("战斗道具面板", 0xE3AEF018);
	ccm::get()->pushWdf("战斗道具面板select", 0x6F88F494);

	m_pFightState = g_pMainState->m_pFightState;
	m_NowFighterID = -1;
	m_Magic.Load(2208066685);
	ccm::get()->pushWdf("战斗指令法术", 2208066685);
	m_Magic.SetStatic(true);
	m_Item.Load(361218670);
	m_Item.SetStatic(true);
	m_Defend.Load(2791494731);
	m_Defend.SetStatic(true);
	m_Guard.Load(73900200);
	m_Guard.SetStatic(true);
	m_Summon.Load(2732776514);
	m_Summon.SetStatic(true);
	//  m_Auto.Load(4021614423);
	//	m_Auto.SetStatic(true);
//	m_Catch.Load(717963597);
	m_Catch.Load(4021614423);
	m_Catch.SetStatic(true);
	m_Escape.Load(320881121);
	m_Escape.SetStatic(true);
	m_Fabao.Load(781132167);
	m_Fabao.SetStatic(true);
	m_Stunt.Load(949865717);
	m_Stunt.SetStatic(true);
	m_Conduct.Load(2324308397);
	m_Conduct.SetStatic(true);

	////////////////////////////////////////////////////////////////////////// 呵呵哒 6/10/14/20/30格 战斗技能选择
	m_BackMagic6.Load(0x2FD95E30);
	m_BackMagic10.Load(0x69823EE5);
	m_BackMagic14.Load(0x0A8B7D87);
	m_BackMagic20.Load(0x32F119A5);
	m_BackMagic30.Load(0x4226BD41);
	m_MagicBack.m_bStatic = true;

	m_MenuMode = FMENU_NORMAL;
	m_TitleT.SetString("选择法术");
	MoveMenu(550 + g_640 - 640, 100 + g_480 - 480);
	s_uiPetSkill.Init();


	_autoBack.Load(0xB0025203);
	_autoBack.SetShowWidth(100);
	_autoBack.SetShowHeight(48);
	_autoBtn.Set(&g_pMainState->m_Button4);
	_autoBtn.m_bStatic = true;
	_tAutoBtn.SetString("取消自动");
	_tAutoBtn.SetColor(RGB(0xFF, 0xFF, 0xFF));

	_tAutoTurn.SetString("自动");
	_tAutoTurn.SetColor(RGB(0xFF, 0xFF, 0xFF));

	moveAuto(700, 105);
//	moveAuto(g_half320 - _autoBack.GetShowHeight() / 2, g_half240);
	return true;
}

bool cInterfaceFight::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&_autoBack, 1);
	pCanvas->Add(&_autoBtn, 1);
	pCanvas->Add(&_tAutoBtn, 1);
	pCanvas->Add(&_tAutoTurn, 1);

	if (!m_NeedShow)return true;
	ShowMenu(pCanvas);

	switch (m_MenuMode)
	{
	case FMENU_NORMAL:
		break;
	case FMENU_MAGIC2:
		break;
	case FMENU_ITEM:
		ShowItem(pCanvas);
		break;
	case FMENU_GRAB:
		break;
	case FMENU_ITEM2:
		break;
	case FMENU_MAGIC:
		ShowMagic(pCanvas);
		break;
	case FMENU_PET:
		ShowPet召唤界面();
		break;
	case FMENU_PROTECT:
		break;
	case FMENU_SPECIAL:
		ShowSpecial(pCanvas);
		break;
	case FMENU_SPECIAL2:
		break;
		/*case FMENU_CONDUCT:
		break;*/
		//case FMENU_FABAO:
		//	ShowItem(pCanvas);
		//	break;
	default:
		ERRBOX;
		break;
	}
	return true;
}



bool cInterfaceFight::ProcessAuto()
{
	if (m_MoveBack)
	{
		if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			m_MoveBack = false;
		}
		m_Sleeptime = 3;
//		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		int xn = m_xAutoPos - m_OldxMouse + g_xMouse;
		int yn = m_yAutoPos - m_OldyMouse + g_yMouse;
		moveAuto(xn, yn);
		m_OldxMouse = g_xMouse;
		m_OldyMouse = g_yMouse;
		return true;
	}

	if (!_autoBack.m_NeedShow || (!isOn(g_xMouse, g_yMouse, _autoBack.m_PreShowRect)))
	{
		return false;
	}
	g_pMainState->SetMouseOnMap(false);

	_autoBtn.SetFrame帧(0);
	if (CheckOn(&_autoBtn, 11))
	{
		return true;
	}

	//鼠标在空白处,准备移动
	m_Select = 16;
	CheckL();
	return true;
}



bool cInterfaceFight::ProcessInput()
{
	if (m_Describe.m_NeedShow)m_Describe.OnOff(false);
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}

	if (m_NowFighterID == -1)
	{
		AddTurn();
		if (m_NowFighterID == -1)
		{
			if (m_pFightState->m_turn == 1)
			{
				m_pFightState->m_turn = 10086;
			}
			return false;
		}
	}

	const auto& ulist = g_pMainState->m_FightWorkList[m_NowFighterID];
	if (ulist.isExist)
	{
		if (ulist.m_pObj->m_IndexType == INDEXTYEP_CHARACTER)
		{
			g_pMainState->m_Accelator.setCharacter((cCharacter*)ulist.m_pObj->m_pIndex);
		}
		else
		{
			g_pMainState->m_Accelator.setCharacter(nullptr);
		}
		g_pMainState->m_Accelator.init2();
	}

	m_Select = -1;
	ResetButton();
	if (CheckA())return true;
//	if (CheckG())return true;
	if (CheckT())return true;
	if (CheckD())return true;
	if (CheckQ())return true;
	if (CheckW())return true;
	if (CheckX())return true;
	if (CheckE())return true;
	if (CheckV())return true;
	if (CheckS())return true;

	if (!g_pMainState->GetLockMouse())return true;

	g_pMainState->m_Accelator.ProcessAccelator();


	if (ProcessAuto())
	{
		return true;
	}

	switch (m_MenuMode)
	{
// 	case FMENU_NORMAL:
// 		if (ProcessNormal())return true;
// 		break;
	case FMENU_MAGIC2:
		if (ProcessMagic2())return true;
		break;
	case FMENU_ITEM:
		if (ProcessItem())return true;
		break;
	case FMENU_GRAB:
 		if (ProcessGrab抓捕())return true;
		break;
	case FMENU_ITEM2:
		if (ProcessItem2())return true;
		break;
	case FMENU_MAGIC:
		if (ProcessMagic())return true;
		break;
	case FMENU_PET:
		if (ProcessPet召唤界面())return true;
		break;
	case FMENU_PROTECT:
		if (ProcessProtect())return true;
		break;
	case FMENU_SPECIAL:
		if (ProcessSpecial())return true;
		break;
		/*case FMENU_CONDUCT:
		break;*/
		/*case FMENU_FABAO:
		if (ProcessItem())return true;
		break;*/
	case FMENU_SPECIAL2:
		if (ProcessSpecial2())return true;
		break;
	default:
		if (m_MenuMode != FMENU_NORMAL)
		{
			ERRBOX;
		}
		break;
	}
	if (ProcessMenu())
	{
		return true;
	}
	if (m_MenuMode == FMENU_NORMAL)
	{
		ProcessNormal();
	}	
	return true;
}

bool cInterfaceFight::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	if (m_NowFighterID>-1)
		UpdateMenu();
	return true;
}

bool cInterfaceFight::UpdateMenu()
{
	m_Magic.m_NeedShow = true;
	m_Stunt.m_NeedShow = true;
	m_Fabao.m_NeedShow = true;
	m_Conduct.m_NeedShow = true;
	m_Item.m_NeedShow = true;
	m_Defend.m_NeedShow = true;
	m_Guard.m_NeedShow = true;
	m_Summon.m_NeedShow = true;
	//	m_Auto.m_NeedShow = true;
	m_Catch.m_NeedShow = true;
	m_Escape.m_NeedShow = true;
	cObj*  pTarget = g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj;
	cPropertyData* pTargetData;
	pTarget->GetPropertyData(pTargetData);
	if (pTarget->GetDataType() == INDEXTYEP_PET)
	{
		m_Stunt.m_NeedShow = false;
		m_Fabao.m_NeedShow = false;
		m_Conduct.m_NeedShow = false;
		m_Summon.m_NeedShow = false;
		//	m_Auto.m_NeedShow = false;
		m_Catch.m_NeedShow = false;
	}
	//法术
	if (false && pTargetData->m_FightData.cannotMagic)
	{
		m_Magic.m_NeedShow = false;
	}
	//特技
	if (false && pTargetData->m_FightData.cannotSpesialSkill)
	{
		m_Stunt.m_NeedShow = false;
	}
	m_Fabao.m_NeedShow = false;	

	MoveMenu(550 + g_640 - 640, 100 + g_480 - 480);

	return true;
}

bool cInterfaceFight::InitMagic()
{
	m_TitleT.SetString("选择法术");
	cPropertyData *data = nullptr;
	g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->GetPropertyData(data);
	int &id = g_pMainState->m_FightWorkList[m_NowFighterID].m_SkillPreSelect.SkillID;
	if (id >= 2000 && !data->isHadPetSkill(id))
	{
		id = -1;
	}
	int skillid = id;
	if (skillid != -1)
	{
		sSkill* pSkill = pSkill = g_pMainState->m_SkillManager.GetSkill(skillid);
		string str2;
		str2 += pSkill->m_Name;
		m_SkillPreSelectT.SetString(str2);
	}
	else m_SkillPreSelectT.SetString("未保存法术");
	m_NumofSkill = 0;
	switch (g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->GetDataType())
	{
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			cCharacter* p = (cCharacter*)g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->m_pIndex;
			m_NumofSkill = 0;
			for (int i = 0; i < p->m_PcData.m_SkillEnablelist.size(); i++)
			{
				if (p->m_PcData.m_SkillEnablelist[i]->m_SkillType>1 && p->m_PcData.m_SkillEnablelist[i]->m_SkillType<7)//是否战斗可用
				{
					m_pSkillShow[m_NumofSkill] = p->m_PcData.m_SkillEnablelist[i];
					m_NumofSkill += 1;
				}
				if (m_NumofSkill == 30)
					break;
			}
			for (int i = 0; i < p->m_PcData.m_NumofBBSkill; i++)
			{
				if (p->m_PcData.m_petSkills[i]->m_SkillType != 7)
				{
					m_pSkillShow[m_NumofSkill] = p->m_PcData.m_petSkills[i];
					m_NumofSkill += 1;
				}
				if (m_NumofSkill == 30)
					break;
			}
		}
		break;
	case INDEXTYEP_PET:
		if (1)
		{
			cPet* p = (cPet*)g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->m_pIndex;
			for (int i = 0; i < p->m_PetData.m_NumofBBSkill; i++)
			{
				if (p->m_PetData.m_petSkills[i]->m_SkillType != 7)
				{
					m_pSkillShow[m_NumofSkill] = p->m_PetData.m_petSkills[i];
					m_NumofSkill += 1;
				}
			}
		}
		break;
	default:
		break;
	}
	if (m_NumofSkill < 11)m_MagicBack.Set(&m_BackMagic10);
	else
		if (m_NumofSkill < 15)m_MagicBack.Set(&m_BackMagic14);
		else
			if (m_NumofSkill < 21)m_MagicBack.Set(&m_BackMagic20);
			else
			{
				m_MagicBack.Set(&m_BackMagic30);
				if (30 == m_NumofSkill)
					m_NumofSkill = 30;
			}
	//加载技能头像,并设置好位置
	for (int i = 0; i < m_NumofSkill; i++)
	{
		m_SkillHead[i].Load(m_pSkillShow[i]->m_BigHead);
	}
	MoveMagicBack(g_half320 - m_MagicBack.m_pFile->GetWidth() / 2, g_half240 - m_MagicBack.m_pFile->GetHeight() / 2);
	return true;
}


bool cInterfaceFight::AddTurn(bool do10086 /* = true */)
{
	if (m_NowFighterID >= 0)
	{
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->m_TrueName.SetColor(RGB(0, 255, 0));
	}
	while (1)
	{
		if (m_NowFighterID >= 0)
		{
			m_NowFighterID = g_pMainState->m_InterfaceTeam.GetReTramTrun(m_NowFighterID);
		}
		switch (m_NowFighterID)
		{
		case -1:
			m_NowFighterID = 0;
			break;
		case 0:
			m_NowFighterID = 5;
			break;
		case 1:
			m_NowFighterID = 6;
			break;
		case 2:
			m_NowFighterID = 7;
			break;
		case 3:
			m_NowFighterID = 8;
			break;
		case 4:
			m_NowFighterID = 9;
			break;
		case 5:
			m_NowFighterID = 1;
			break;
		case 6:
			m_NowFighterID = 2;
			break;
		case 7:
			m_NowFighterID = 3;
			break;
		case 8:
			m_NowFighterID = 4;
			break;
		case 9:
			if (1)
			{
				if (do10086)
				{
					m_pFightState->m_turn = 1;
				}
// 				else
// 				{
// 					if (_isAutoBattle && ++_timeWaiting > 300)
// 					{
// 						m_pFightState->m_turn = 1;
// 					}
// 				}
				m_NowFighterID = -1;
				if (m_pObjSelect)
				{
					m_pObjSelect->m_TrueName.SetColor(RGB(0, 255, 0));
					m_pObjSelect->SetShine(false);

				}
				return true;
			}
			break;
		}

		m_NowFighterID = g_pMainState->m_InterfaceTeam.GetTeamTurn(m_NowFighterID);
		if (CheckTurn(m_NowFighterID))
		{
			if (g_StateType == STATE_FIGHT)
			{
				UpdateMenu();
				//	FillSkillHead(m_pNowFighterID);
				////////////////////////////////////////////////////////////////////////// 呵呵哒 不要紫色
				m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->m_TrueName.SetColor(RGB(0xFF, 0, 0));
			}
			return true;
		}

	}
	return true;
}

bool cInterfaceFight::CheckTurn(int ID)
{
	if (!m_pFightState->m_pFightWorkList[ID]->isExist)//存在
	{
		return false;
	}
	if (!CheckControl(ID))return false;

	//	if (!m_pFightState->m_pList[ID]->m_bDie)//活着 //死了一样可以选择命令
	if (m_pFightState->m_pFightWorkList[ID]->m_FriendListid >= 0)
	{
		return false;
	}
	cPropertyData* pTargetData;
	m_pFightState->m_pFightWorkList[ID]->m_pObj->GetPropertyData(pTargetData);
	//if (!pTargetData->m_Controler.CheckHero())return false;
	if (m_pFightState->m_pFightWorkList[ID]->m_WorkType >= 0)
	{
		return false;
	}

	return true;
	//	m_pFightState->m_pList[ID]->m_pData->GetDateP(pTargetData);
	if (pTargetData->m_FightData.chaos混乱反间)
	{
		return false;
	}
	return !pTargetData->m_FightData.cannotAll;
}

bool cInterfaceFight::ProcessItem()
{
	if (m_MoveBack)
	{
		m_Select = 17;
		if (!CheckL())m_MoveBack = false;
		return true;
	}
	if (CheckRButton())return true;
	if (CheckOn(&m_Cancel, 100))return true;
	m_ItemSelect = g_pMainState->m_ItemSelect.Process(g_xMouse, g_yMouse);
	if (m_ItemSelect > -1)
	{
		m_Select = 12;
		if (CheckL())
		{
			g_pMainState->m_ItemSelect.m_Describe.OnOff(false);
			g_pMainState->m_InterfaceItem.m_SelectPre = -1;
			return true;
		}
	}
	m_Select = 16;
	CheckL();
	return true;
	//
	//m_ItemSelect = -1;

	//if (!isOn(g_xMouse, g_yMouse, m_ItemBack.m_PreShowRect))return false;
	//g_pMainState->SetMouseOnMap(false);
	//
	//if (isOn(g_xMouse, g_yMouse, m_ItemRect))
	//{
	//	m_ItemSelect = (g_xMouse - m_ItemRect.left) / 51 + ((g_yMouse - m_ItemRect.top) / 51) * 5;
	//}
	//if (m_ItemSelect > -1 && m_ItemCanUse[m_ItemSelect])
	//{
	//	m_ItemSelect;
	//	int xpos, ypos;

	//	cObj* pObj = g_pMainState->m_pFightState->m_pList[m_NowFighterID]->m_pData;

	//	if (INDEXTYEP_PET == pObj->m_IndexType)
	//	{
	//		cPetData* pPet;
	//		pObj->GetDateP(pPet);
	//		if (pPet->m_Controler.CheckBB())
	//			pObj = g_pMainState->m_FightList[m_NowFighterID - 5].m_pData;
	//		else return false;
	//	}
	//	cCharacter* pc = (cCharacter*)pObj->m_pIndex;
	//	sItem2* pItem = pc->m_PCData.GetItem(m_ItemSelect);
	//	xpos = m_ItemHead[m_ItemSelect].GetX();
	//	ypos = m_ItemHead[m_ItemSelect].GetY();
	//	if (!pItem->GetNum())return true;
	//		g_pMainState->m_ItemManage.SetItemDescribe(
	//			xpos, ypos, m_Describe, pItem
	//			);

	//	


	//		if (m_Describe.m_NeedShow)
	//		{
	//			CWFile* itemfirst = &m_ItemHead[m_ItemSelect];

	//			m_ItemSelectFrame.m_NeedShow = true;
	//			m_ItemSelectFrame.m_Picture.m_x = itemfirst->GetX();
	//			m_ItemSelectFrame.m_Picture.m_y = itemfirst->GetY();
	//		}

	//	m_Select = 12;
	//	if (CheckL())
	//	{
	//		m_Describe.OnOff(false);
	//		g_pMainState->m_InterfaceItem.m_SelectPre = -1;
	//		return true;
	//	}
	//}
	//else
	//{
	//	m_ItemSelect = -1;
	//	m_ItemSelectFrame.m_NeedShow = false;
	//	g_pMainState->m_InterfaceItem.m_MouseOnMark.m_NeedShow = false;
	//	g_pMainState->m_InterfaceItem.m_SelectPre = -1;
	//	if (m_Describe.m_NeedShow)
	//		m_Describe.OnOff(false);
	//	
	//	
	//	
	//}
	//if(CheckRButton())return true;
	//return false;
	//鼠标在空白处,准备移动

}
//2
void cInterfaceFight::InitItem(int offset)
{
	cObj* pObj = g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj;
	if (INDEXTYEP_PET == pObj->m_IndexType)
	{
		cPropertyData* pPet;
		pObj->GetPropertyData(pPet);
		if (pPet->m_Controler.CheckBB())
			pObj = g_pMainState->m_FightWorkList[m_NowFighterID - 5].m_pObj;
		else return;
	}
	cCharacter* pc = (cCharacter*)pObj->m_pIndex;

	g_pMainState->m_ItemSelect.Update(&pc->m_PcData.m_Items[0]);
	MoveItem(g_half320 - m_ItemBack.GetWidth() / 2, g_half240 - m_ItemBack.GetHeight() / 2);
	//g_pMainState->m_ItemSelect.Move(m_ItemBack.GetX()+19, m_ItemBack.GetY()+34);
	//int itemoffset;
	m_TitleT.SetString("选择物品");
	m_ItemBack.m_bMove = true;
	//cObj* pObj = g_pMainState->m_FightList[m_NowFighterID].m_pData;
	//if (INDEXTYEP_PET == pObj->m_IndexType)
	//{
	//	cPetData* pPet;
	//	pObj->GetDateP(pPet);
	//	if (pPet->m_Controler.CheckBB())
	//		pObj = g_pMainState->m_FightList[m_NowFighterID - 5].m_pData;
	//	else return;
	//}
	//cCharacter* pc = (cCharacter*)pObj->m_pIndex;
	//for (int i = 0; i < 20; i++)
	//{
	//	itemoffset = i + offset;
	//	m_ItemCanUse[i] = false;
	//	sItem2& Item = pc->m_PCData.m_Item[itemoffset];
	//	if (Item.GetNum())
	//	{
	//		switch (Item.GetType())
	//		{
	//		case 28:
	//			if (Item.GetID() == 11)
	//			{
	//				m_ItemCanUse[i] = true;

	//				m_ItemHead[i].Load(Item.m_pItemData->m_SmallHead);
	//			}
	//			break;
	//		case 22://药品
	//		case 25://暗器
	//			if (1)
	//			{
	//				m_ItemCanUse[i] = true;
	//				m_ItemHead[i].Load(Item.m_pItemData->m_SmallHead);
	//			}
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		m_ItemHead[i].Free();
	//	}
	//}
	//m_Item.SetFrame(1);
	//MoveItem(g_half320 - m_ItemBack.m_Picture.m_Width / 2, g_half240 - m_ItemBack.m_Picture.m_Height / 2);
}

bool cInterfaceFight::SetNowFight(int fight)
{
	m_NowFighterID = fight;
	UpdateMenu();

	return true;
}


void cInterfaceFight::MoveMagicBack(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_MagicBack.m_x = x;
	m_MagicBack.m_y = y;
	if (m_NumofSkill < 11)
	{
		//设置技能位置
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 30 + 88 * (i % 2), m_MagicBack.m_y + 33 + 42 * (i / 2));
		}
	}
	else if (m_NumofSkill < 15)
	{
		//设置技能位置
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 30 + 88 * (i % 2), m_MagicBack.m_y + 33 + 42 * (i / 2));
		}
	}
	else if (m_NumofSkill < 21)
	{
		//设置技能位置
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 30 + 88 * (i % 2), m_MagicBack.m_y + 30 + 42 * (i / 2));
		}
	}
	else //30
	{
		for (int i = 0; i < m_NumofSkill; i++)
		{
			m_SkillHead[i].SetXY(m_MagicBack.m_x + 25 + 50 * (i % 3), m_MagicBack.m_y + 27 + 42 * (i / 3));
		}
	}
	m_Cancel.m_x = m_MagicBack.m_x + m_MagicBack.m_pFile->GetWidth() - 20;
	m_Cancel.m_y = m_MagicBack.m_y + 5;
	int xc = x + m_MagicBack.m_Width / 2;
	m_TitleT.SetY(y + 3);
	m_TitleT.SetXCenter(xc);
	m_TitleT.UpdateXCenter();
	m_SkillPreSelectT.SetY(y + m_MagicBack.m_pFile->GetHeight() - 20);
	m_SkillPreSelectT.SetXCenter(xc);
	m_SkillPreSelectT.UpdateXCenter();
}

void cInterfaceFight::MoveMenu(int x, int y)
{
	m_xMenuPos = x;
	m_yMenuPos = y;
	int yOff = 24;
	int i = 0;
	if (m_Magic.m_NeedShow)
	{
		m_Magic.SetXY(x, y + yOff*i);
		i += 1;
	}
	if (m_Stunt.m_NeedShow)
	{
		m_Stunt.SetXY(x, y + yOff*i);  //特技
		i += 1;
	}
	if (m_Fabao.m_NeedShow)
	{
		m_Fabao.SetXY(x, y + yOff*i);
		i += 1;
	}
	if (m_Conduct.m_NeedShow)
	{
		m_Conduct.SetXY(x, y + yOff*i);
		i += 1;
	}
	if (m_Item.m_NeedShow)
	{
		m_Item.SetXY(x, y + yOff*i);  //道具
		i += 1;
	}
	if (m_Defend.m_NeedShow)  //防
	{
		m_Defend.SetXY(x, y + yOff*i);
		i += 1;
	}
	if (m_Guard.m_NeedShow)  //保护
	{
		m_Guard.SetXY(x, y + yOff*i);
		i += 1;
	}
	if (m_Summon.m_NeedShow)  //召唤
	{
		m_Summon.SetXY(x, y + yOff*i); //召唤
		i += 1;
	}
	//if (m_Auto.m_NeedShow)  //自动
	//{
	//	m_Auto.SetXY(x, y + yOff*i);
	//	i += 1;
	//}
	if (m_Catch.m_NeedShow)  //抓捕
	{
		m_Catch.SetXY(x, y + yOff*i);
		i += 1;
	}
	if (m_Escape.m_NeedShow)  //逃跑
	{
		m_Escape.SetXY(x, y + yOff*i);
		i += 1;
	}
	m_NumofButtonShow = i;
}


void cInterfaceFight::moveAuto(int x, int y)
{
	_autoBack.SetXY(x, y);
	_tAutoTurn.SetXY(x + 18, y + 5);
	_autoBtn.SetXY(x + 13, y + 26);
	_tAutoBtn.SetXY(x + 18, y + 28);
	m_xAutoPos = x;
	m_yAutoPos = y;
}


void cInterfaceFight::SelectMode(eFightMenu eFightMenu)
{

	//先把之前的图像擦除
	if (eFightMenu == m_MenuMode)return;

	cCanvas&  canvas = g_pMainState->m_Canvas;
	switch (m_MenuMode)
	{
	case FMENU_NORMAL:

		break;
	case FMENU_MAGIC2:
	case FMENU_GRAB:
	case FMENU_ITEM2:
	case FMENU_SPECIAL2:
	case FMENU_PROTECT:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Normal);
		break;
		//	case FMENU_FABAO:
	case FMENU_ITEM:
		canvas.SetRedraw(m_ItemBack.m_PreShowRect);
		break;
	case FMENU_MAGIC:
	case FMENU_SPECIAL:
		canvas.SetRedraw(m_MagicBack.m_PreShowRect);
		break;
	case FMENU_PET:
		canvas.SetRedraw(m_PetBack.m_PreShowRect);
		break;
	default:
		ERRBOX;
		break;
	}

	m_MenuMode = eFightMenu;
	switch (eFightMenu)
	{
	case FMENU_NORMAL:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Normal);
		break;
	case FMENU_MAGIC2:
		InitMagic2();
		break;
	case FMENU_ITEM:
		InitItem(0);
		break;
	case FMENU_GRAB:
//		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Grab);
		break;
	case FMENU_ITEM2:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Magic);
		break;
	case FMENU_MAGIC:
		InitMagic();
		break;
	case FMENU_PET:
		InitPet();

		break;
	case FMENU_PROTECT:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Guard);
		break;
	case FMENU_SPECIAL:
		InitSpecial();
		break;
	case FMENU_SPECIAL2:
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Magic);
		break;
		//case FMENU_CONDUCT:

		break;
	default:
		ERRBOX;
		break;
	}
}

void cInterfaceFight::SwitchMode(eFightMenu eFightMenu)
{
	if (m_MenuMode == eFightMenu)
	{
		SelectMode(FMENU_NORMAL);
	}
	else
	{
		m_Cancel.SetFrame帧(0);
		SelectMode(eFightMenu);
	}
	if (m_Describe.m_NeedShow)
	{
		m_Describe.OnOff(false);
	}
}

bool cInterfaceFight::RunA()
{
	int autoSelect = -1;// g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_NowFighterID, 4, true);
//	if (-1 != autoSelect)
	{
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_WorkType = WORKTYPE_ATTACK;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillLv = 0;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillID = 1000;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->targetID = autoSelect;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.TargetID = autoSelect;
	}
	AddTurn();
	SelectMode(FMENU_NORMAL);
	return true;
}

bool cInterfaceFight::RunQ()
{
	sFightWork* figher = m_pFightState->m_pFightWorkList[m_NowFighterID];
	int id = figher->m_SkillPreSelect.SkillID;

	if (id >= 2000)
	{
		cPropertyData *data = nullptr;
		g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->GetPropertyData(data);
		if (!data->isHadPetSkill(id))
		{
			id = -1;
		}
	}
	if (-1 == id)
	{
		RunA();
		return true;
	}

// 	int autoSelect = g_pMainState->m_AI.m_FightTarget[m_NowFighterID];
// 	if (autoSelect >= 0 && g_pMainState->m_FightWorkList[autoSelect].isExist)
// 	{
// 		//		autoSelect = g_pMainState->m_AI.m_FightTarget[m_NowFighterID];
// 	}
// 	else
// 	{
// 		sSkill* skill = g_pMainState->m_SkillManager.GetSkill(id);
// 		autoSelect = g_pMainState->m_AI.findBattleTargetAndStepMiliSec(m_NowFighterID, skill->m_SkillType, true);
// 	}
// 	if (-1 == autoSelect)
// 	{
// 		RunA();
// 		return true;
// 	}

	figher->m_SkillSelect.SkillLv = figher->m_SkillPreSelect.SkillLv;
	figher->m_SkillSelect.SkillID = figher->m_SkillPreSelect.SkillID;
	figher->m_SkillSelect.TargetID = -1; // autoSelect;
	if (id == 141 || id == 142 || id == 143 || id == 148)
	{
		if (!g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->CheckHaveState(145))
		{
			figher->m_SkillSelect.SkillID = 145;
			figher->m_SkillSelect.TargetID = m_NowFighterID; // figher->m_pObj->m_IDInFightlist;
		}
	}
	figher->m_WorkType = WORKTYPE_MAGIC;
	SelectMode(FMENU_NORMAL);
	AddTurn();
	return true;
}


bool cInterfaceFight::CheckQ()
{
	//自动法术
	if (g_pMainState->Keyboard.GetKeyState(DIK_Q))
	{
		g_pMainState->Keyboard.SetLock(DIK_Q);
		RunQ();
		return true;
	}
	return false;
}


bool cInterfaceFight::CheckD()
{
	if (g_pMainState->Keyboard.GetKeyState(DIK_D))//防
	{
		g_pMainState->Keyboard.SetLock(DIK_D);
		Def();
		return true;
	}
	return false;
}
void cInterfaceFight::Def()
{
	g_pMainState->m_AI.defense(m_NowFighterID);
	SelectMode(FMENU_NORMAL);
	AddTurn();
}
bool cInterfaceFight::CheckT()
{
	if (g_pMainState->Keyboard.GetKeyState(DIK_T))//保护
	{
		g_pMainState->Keyboard.SetLock(DIK_T);
		SwitchMode(FMENU_PROTECT);
		return true;
	}
	return false;
}


bool cInterfaceFight::CheckA()
{
	if (g_pMainState->Keyboard.GetKeyState(DIK_A))
	{
		g_pMainState->Keyboard.SetLock(DIK_A);
		RunA();
		return true;
	}
	return false;
}

bool cInterfaceFight::CheckG()
{
	if (g_pMainState->Keyboard.GetKeyState(DIK_G))//抓捕
	{
		g_pMainState->Keyboard.SetLock(DIK_G);
//		SwitchMode(FMENU_GRAB);
		return true;
	}
	return false;
}

bool cInterfaceFight::CheckW()
{
	//是否显示法术界面
	if (g_pMainState->Keyboard.GetKeyState(DIK_W))
	{
		g_pMainState->Keyboard.SetLock(DIK_W);
		SwitchMode(FMENU_MAGIC);
		return true;
	}
	return false;
}
bool cInterfaceFight::CheckX()
{
	//是否显示法术界面
	if (g_pMainState->Keyboard.GetKeyState(DIK_X))
	{
		g_pMainState->Keyboard.SetLock(DIK_X);
		if (m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->getPetData())
		{
			return true;
		}
		SwitchMode(FMENU_SPECIAL);
		return true;
	}
	return false;
}
bool cInterfaceFight::CheckE()
{
	//道具模式
	if (g_pMainState->Keyboard.GetKeyState(DIK_E))
	{
		g_pMainState->Keyboard.SetLock(DIK_E);
		SwitchMode(FMENU_ITEM);
		return true;
	}
	return false;
}
bool cInterfaceFight::CheckV()
{
	//指挥
	if (g_pMainState->Keyboard.GetKeyState(DIK_V))
	{
		g_pMainState->Keyboard.SetLock(DIK_V);
		m_InterfaceConduct.OnOff(!m_InterfaceConduct.m_NeedShow);
		//	SwitchMode(FMENU_CONDUCT);
		return true;
	}
	return false;
}
bool cInterfaceFight::CheckRButton()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	if (m_Describe.m_NeedShow)
	{
		m_Describe.OnOff(false);
		g_pMainState->m_InterfaceItem.m_SelectPre = -1;
	}
	switch (m_MenuMode)
	{
	case FMENU_NORMAL:
		break;
	case FMENU_MAGIC2:
	case FMENU_ITEM2:
	case FMENU_PROTECT:
	case FMENU_GRAB:
		SelectMode(FMENU_NORMAL);
		break;
	case FMENU_ITEM:
		if (-1 == m_ItemSelect)
		{
			SelectMode(FMENU_NORMAL);
		}
		else
		{
			g_pMainState->m_FightWorkList[m_NowFighterID].m_ItemSelectID = m_ItemSelect;
			g_pMainState->m_FightWorkList[m_NowFighterID].m_autoItemSelectID = m_ItemSelect;
			SelectMode(FMENU_ITEM2);
		}
		break;
		/*case FMENU_FABAO:
		if (-1 == m_ItemSelect)
		{
		SelectMode(FMENU_NORMAL);
		}
		else
		{
		g_pMainState->m_FightList[m_NowFighterID].m_ItemSelectID = m_ItemSelect + 49;
		g_pMainState->m_FightList[m_NowFighterID].m_autoItemSelectID = m_ItemSelect + 49;
		SelectMode(FMENU_ITEM2);
		}
		break;*/
	case FMENU_MAGIC:
		switch (m_Select)
		{
		case 14:
			if (1)
			{
				if (m_pSkillSelect->m_Owner == -1)
				{
					auto& pre5 = m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillPreSelect;
					pre5.SkillID = m_pSkillSelect->m_Id + 2000;
					pre5.SkillLv = m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->getPropertyData()->m_Lv;
				//	g_pMainState->m_Friend._friends[m_NowFighterID - 5].pre5 = pre5;
					g_pMainState->m_Friend._friends[m_NowFighterID - 5].prebb = pre5.SkillID;
				}
				else
				{
					auto& list = m_pFightState->m_pFightWorkList[m_NowFighterID];
					auto& pre = list->m_SkillPreSelect;
					pre.SkillID = m_pSkillSelect->m_Id;
					pre.SkillLv = list->m_pObj->getPcData()->m_MengPaiSkillLvs[m_pSkillSelect->m_Owner];
					g_pMainState->m_Friend._friends[m_NowFighterID].pre = pre.SkillID;
				}
				InitMagic2();
			}
			break;
		case 15:
			SelectMode(FMENU_NORMAL);
			break;
		}
		break;
	case FMENU_PET:
		SelectMode(FMENU_NORMAL);
		break;
	case FMENU_SPECIAL:
		if (-1 == m_Select)
		{
			SelectMode(FMENU_NORMAL);
		}
		else
		{
			m_SpecialSelect = 2000 + m_Select - 101;
			SelectMode(FMENU_SPECIAL2);
		}
		break;
	case  FMENU_SPECIAL2:
		SelectMode(FMENU_SPECIAL);
		break;
	default:
		ERRBOX;
		break;
	}
	return true;
}

bool cInterfaceFight::ProcessMenu()
{
	if (m_MoveBack)
	{
		m_Select = 17;
		if (!CheckL())m_MoveBack = false;
		return true;
	}

	cPcData* data = (cPcData*)g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->getPropertyData();
	cPcData* dataItem = data;
	if (m_NowFighterID % 10 >= 5)
	{
		dataItem = (cPcData*)g_pMainState->m_FightWorkList[m_NowFighterID - 5].m_pObj->getPropertyData();
	}
	switch (m_MenuMode)
	{
	case FMENU_MAGIC2:
		setMiaoshuDesc(m_pSkillSelect ? m_pSkillSelect->m_Name : "");
		break;
	case FMENU_ITEM2:
		setMiaoshuDesc(m_ItemSelect >= 0 ? dataItem->m_Items[m_ItemSelect].GetName() : "");
		break;
	case FMENU_SPECIAL2:
		setMiaoshuDesc(m_SpecialSelect >= 0 ? g_pMainState->m_SkillManager.GetSkill(data->m_SpecialSkillList[m_SpecialSelect])->m_Name : 0);
		break;
	default:
	{
		sFightWork* figher = m_pFightState->m_pFightWorkList[m_NowFighterID];
		int id = figher->m_SkillPreSelect.SkillID;

		if (id >= 2000)
		{
			cPropertyData *data = nullptr;
			g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->GetPropertyData(data);
			if (!data->isHadPetSkill(id))
			{
				id = -1;
			}
		}
		auto ss = g_pMainState->m_SkillManager.GetSkill(id);
		setMiaoshuDesc(ss ? ss->m_Name : "");
	}
		break;
	}

	//鼠标在菜单上
	if (!(g_xMouse > m_xMenuPos - 7 && g_xMouse < m_xMenuPos + 65 && g_yMouse>m_yMenuPos&&g_yMouse < m_yMenuPos + 231))
		return false;
	g_pMainState->SetMouseOnMap(false);

	if (CheckOn(&m_Magic, 0))return true;
	if (CheckOn(&m_Item, 1))return true;
	if (CheckOn(&m_Defend, 2))return true;
	if (CheckOn(&m_Escape, 3))return true;
	if (CheckOn(&m_Guard, 4))return true;
	if (m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->GetDataType() == INDEXTYEP_CHARACTER)
	{
		if (CheckOn(&m_Fabao, 5))return true;
		if (CheckOn(&m_Stunt, 6))return true;
		if (CheckOn(&m_Conduct, 7))return true;
		if (CheckOn(&m_Summon, 8))return true;
		//	if (CheckOn(&m_Auto, 9))return true;
		if (CheckOn(&m_Catch, 10))return true;
	}

	//鼠标在空白处,准备移动
	m_Select = 16;
	CheckL();
	return true;
}

bool cInterfaceFight::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		return false;
	m_Sleeptime = 3;
	if (m_Describe.m_NeedShow)
		m_Describe.OnOff(false);
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	switch (m_Select)
	{
	case 0://法术
		SwitchMode(FMENU_MAGIC);
		m_Magic.SetFrame(1);
		break;
	case 1://道具
		SwitchMode(FMENU_ITEM);
		m_Item.SetFrame(1);
		break;
	case 2://防
		Def();
		m_Defend.SetFrame(1);
		break;
	case 3://逃
	{
		g_pMainState->m_AI.Escape(m_NowFighterID);
		g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->getPropertyData()->Speed.AddDataOriginal(0xFFFFFF);

		m_Escape.SetFrame(1);
//		AddTurn();
		if (m_NowFighterID < 5 || g_pMainState->m_FightWorkList[m_NowFighterID - 5].CheckDie())
		{
			do { AddTurn(); } while (m_pFightState->m_turn < 1);
		}
	}

		break;
	case 4://保护
		Guard();
		m_Guard.SetFrame(1);
		setMiaoshuDesc("保护");
		break;
		//case 5://法宝
		//	SwitchMode(FMENU_FABAO);
		//	m_Fabao.SetFrame(1);
		//	break;
	case 6://特技
		SwitchMode(FMENU_SPECIAL);
		m_Stunt.SetFrame(1);
		break;
	case 7://指挥
		SwitchMode(FMENU_NORMAL);
		m_InterfaceConduct.OnOff(!m_InterfaceConduct.m_NeedShow);
		m_Conduct.SetFrame(1);
//		setMiaoshuDesc("指挥");
		break;
	case 8://召唤
		SwitchMode(FMENU_PET);
		m_Summon.SetFrame(1);
		break;
	case 10://抓捕
//		SwitchMode(FMENU_GRAB);
		m_Catch.SetFrame(1);
		_isAutoBattle = true;
		_timeWaiting = 240;
		m_pFightState->m_turn = 10086;
		_autoBack.m_NeedShow = true;
		_autoBtn.m_NeedShow = true;
		_tAutoBtn.m_NeedShow = true;
		_tAutoTurn.m_NeedShow = true;
// 		do 
// 		{ 
// 			if (m_NowFighterID >= 0 && CheckControl(m_NowFighterID))
// 			{
// 				RunQ();
// 			}
// 			AddTurn(); 
// 		} while (m_pFightState->m_turn < 1);
		break;
	case 11:
		if (g_pMainState->_autoGhost)
		{
			g_pMainState->m_Tags.Add("请先取消自动抓鬼模式");
			break;
		}
		_isAutoBattle = false;
		_timeWaiting = 0;
		_autoBack.m_NeedShow = false;
		_autoBtn.m_NeedShow = false;
		_tAutoBtn.m_NeedShow = false;
		_tAutoTurn.m_NeedShow = false;
		if (m_pFightState->m_turn == 10086)
		{
			m_pFightState->m_turn = 0;
		}
		if (!CheckControl())
		{
			int& f = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_FriendListid;
			if (f >= 0)
			{
				f = -1;
			}
			SetControl(g_pMainState->m_HeroID, true);
			SetControl(g_pMainState->m_HeroID + 5, true);
			g_pMainState->m_Friend._friends[g_pMainState->m_HeroID].ctrl = true;
		}
		break;
	case 12:
		g_pMainState->m_FightWorkList[m_NowFighterID].m_ItemSelectID = m_ItemSelect;
		SelectMode(FMENU_ITEM2);
		break;
	case 14:
		InitMagic2();
		break;
	case 16://准备移动
		m_OldxMouse = g_xMouse;
		m_OldyMouse = g_yMouse;
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_MoveBack = true;
		break;
	case 17://移动
		if (1)
		{
			m_MagicBack.m_bMove = true;
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xn;
			int yn;
			if (m_MenuMode == FMENU_NORMAL)
			{
				xn = m_xMenuPos - m_OldxMouse + g_xMouse;
				yn = m_yMenuPos - m_OldyMouse + g_yMouse;
			}
			else
			{
				xn = m_xPos - m_OldxMouse + g_xMouse;
				yn = m_yPos - m_OldyMouse + g_yMouse;
			}
			switch (m_MenuMode)
			{
			case FMENU_NORMAL:
				MoveMenu(xn, yn);
				break;
			case FMENU_MAGIC2:
				break;
			case FMENU_ITEM:
				MoveItem(xn, yn);
				break;
			case FMENU_MAGIC:
				MoveMagicBack(xn, yn);
				break;
			case FMENU_PET:
				MovePet(xn, yn);
				break;
			case FMENU_PROTECT:
				break;
			case FMENU_SPECIAL:
				MoveSpecial(xn, yn);
				break;
				/*case FMENU_CONDUCT:
				break;*/
				/*	case FMENU_FABAO:
				break;*/
			default:
				ERRBOX;
				break;
			}
			m_OldxMouse = g_xMouse;
			m_OldyMouse = g_yMouse;
		}
		break;
	case 100: //关闭窗口
		SelectMode(FMENU_NORMAL);
		break;
	case 101://特技选择
	case 102:
	case 103:
	case 104:
	case 105:
	case 106:
		m_SpecialSelect = m_Select - 101;
		SelectMode(FMENU_SPECIAL2);
		break;
	default:
		ERRBOX;
		break;
	}
	return true;
}

void cInterfaceFight::Guard()
{
	SwitchMode(FMENU_PROTECT);
}

void cInterfaceFight::MoveItem(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_ItemBack.SetXY(x, y);
	m_Cancel.SetXY(x + 272, y + 5);
	m_TitleT.SetXY(x + 110, y + 5);
	g_pMainState->m_ItemSelect.Move(x + 19, y + 34);
	/*for (int i = 0; i < 20; i++)
	{
	int xNum = (i) % 5;
	int yNum = (i) / 5;
	m_ItemHead[i].SetXY(xNum * 51 + 20 + x, yNum * 51 + 35 + y);
	}*/
	m_ItemRect.left = 20 + x;
	m_ItemRect.top = 35 + y;
	m_ItemRect.right = m_ItemRect.left + 255;
	m_ItemRect.bottom = m_ItemRect.top + 204;


}

bool cInterfaceFight::InitSpecial()
{
	m_TitleT.SetString("选择特技");
	m_MagicBack.Set(&m_BackMagic6);
	m_MagicBack.m_bMove = true;
	cCharacter* pC = (cCharacter*)m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->m_pIndex;
	m_SpecialNum = 0;
	for (int i = 0; i<6; i++)
	{
		if (pC->m_PcData.m_SpecialSkillList[i]>-1)
		{
			m_SpecialID[m_SpecialNum] = pC->m_PcData.m_SpecialSkillList[i];
			sSkill*  pSkill = g_pMainState->m_SkillManager.GetSpecialSkill(m_SpecialID[m_SpecialNum]);
			m_SpecialHead[m_SpecialNum].Load(pSkill->m_BigHead);
			m_SpecialNum += 1;
		}
	}
	MoveSpecial(g_half320 - m_MagicBack.m_pFile->GetWidth() / 2, g_half240 - m_MagicBack.m_pFile->GetHeight() / 2);
	return true;
}

void cInterfaceFight::InitPet()
{

	MovePet(g_half320 - m_PetBack.m_Picture.m_Width / 2, g_half240 - m_PetBack.m_Picture.m_Height / 2);
}
void cInterfaceFight::MovePet(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_PetBack.m_Picture.m_x = x;
	m_PetBack.m_Picture.m_y = y;
	m_Button.m_Picture.m_x = x + 60;
	m_Button.m_Picture.m_y = y + 305;
	m_UpB.m_Picture.m_x = x + 130;
	m_UpB.m_Picture.m_y = y + 35;
	m_DownB.m_Picture.m_x = x + 130;
	m_DownB.m_Picture.m_y = y + 145;

	m_Cancel.m_x = x + 145;
	m_Cancel.m_y = y + 5;
	s_uiPetSkill.Move(x + m_PetBack.GetWidth(), y);
	g_pMainState->m_Canvas.SetRedraw(m_PetBack.m_PreShowRect);

}
void cInterfaceFight::ShowPet召唤界面()
{
	cCanvas* pCanvas = &g_pMainState->m_Canvas;
	if (m_PetBack.m_NeedShow)
	{
		s_uiPetSkill.Show(pCanvas);
	}


	pCanvas->Add(&m_PetBack, 1);
	pCanvas->Add(&m_Cancel, 1);

	cCharacter* pC = (cCharacter*)g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->m_pIndex;
	int kk = pC->m_PcData.m_NumofBB;
	if (!kk)return;

	int yInv = 112 / kk;
	if (yInv > 28) yInv = 28;
	else if (yInv < 16) yInv = 16;
	if (-1 == m_PetIDSelect)
	{
		if (m_TruePetIDSelect > -1)
		{
			if (m_TruePetIDSelect >= kk)
			{
				m_TruePetIDSelect = kk - 1;
			}
			m_PetSelectBack[0].m_Picture.m_x = m_PetBack.m_Picture.m_x + 22;
			m_PetSelectBack[0].m_Picture.m_y = m_PetBack.m_Picture.m_y + 55 + (m_TruePetIDSelect - m_PetPage * 4) * yInv;
			m_PetSelectBack[1].m_Picture.m_x = m_PetBack.m_Picture.m_x + 68;
			m_PetSelectBack[1].m_Picture.m_y = m_PetBack.m_Picture.m_y + 55 + (m_TruePetIDSelect - m_PetPage * 4) * yInv;
			m_PetSelectBack[0].m_bMove = true;
			m_PetSelectBack[1].m_bMove = true;
			pCanvas->Add(&m_PetSelectBack[0], 1);
			pCanvas->Add(&m_PetSelectBack[1], 1);
		}
	}
	else
	{
		m_PetSelectBack[0].m_Picture.m_x = m_PetBack.m_Picture.m_x + 22;
		m_PetSelectBack[0].m_Picture.m_y = m_PetBack.m_Picture.m_y + 55 + (m_PetIDSelect - m_PetPage * 4) * yInv;
		m_PetSelectBack[1].m_Picture.m_x = m_PetBack.m_Picture.m_x + 68;
		m_PetSelectBack[1].m_Picture.m_y = m_PetBack.m_Picture.m_y + 55 + (m_PetIDSelect - m_PetPage * 4) * yInv;
		m_PetSelectBack[0].m_bMove = true;
		m_PetSelectBack[1].m_bMove = true;
		pCanvas->Add(&m_PetSelectBack[0], 1);
		pCanvas->Add(&m_PetSelectBack[1], 1);
	}
	pCanvas->Add(&m_UpB, 1);
	pCanvas->Add(&m_DownB, 1);

	if (kk > 4)
	{
		//			kk = 4;
	}

	for (int i = 0; i < kk; i++)
	{
		if (m_TruePetIDSelect == (i))
			m_PetName[i].SetColor(RGB(255, 255, 0));
		else
			m_PetName[i].SetColor(RGB(0, 0, 0));

		m_PetName[i].SetXY(m_PetBack.m_Picture.m_x + 25, m_PetBack.m_Picture.m_y + 60 + (i)* yInv);
		string name = pC->m_PcData.m_pPets[i/* + m_PetPage * 4*/]->m_PetData.m_Name;
		bool isFight = pC->m_PcData.m_FightPetID == i;
		cPetData& pet = pC->m_PcData.m_pPets[i]->m_PetData;
		if (isFight || pet._owerIdx < 0)
		{
			while (name.size() < 11)
			{
				name.push_back(' ');
			}
			name += "×";
		}
		m_PetName[i].SetString(name);
//		if ((m_PetPage && i >= 4) || (!m_PetPage && i < 4))
		{
			pCanvas->Add(&m_PetName[i]);
		}
	}
	if (m_TruePetIDSelect>-1)
	{
		if (m_TruePetIDSelect >= kk)
		{
			m_TruePetIDSelect = kk - 1;
		}
		m_PetProPerty[0].SetColor(RGB(0, 0, 0));
		m_PetProPerty[0].SetXY(m_PetBack.m_Picture.m_x + 60, m_PetBack.m_Picture.m_y + 180);
		m_PetProPerty[0].SetString(pC->m_PcData.m_pPets[m_TruePetIDSelect]->m_PetData.m_Name);
		pCanvas->Add(&m_PetProPerty[0]);
		ostringstream oss;
		oss << pC->m_PcData.m_pPets[m_TruePetIDSelect]->m_PetData.m_Lv;
		m_PetProPerty[1].SetXY(m_PetBack.m_Picture.m_x + 60, m_PetBack.m_Picture.m_y + 205);
		m_PetProPerty[1].SetString(oss.str());
		pCanvas->Add(&m_PetProPerty[1]);

		oss.str("");
		oss << pC->m_PcData.m_pPets[m_TruePetIDSelect]->GetData()->m_LvTake;
		m_PetProPerty[2].SetXY(m_PetBack.m_Picture.m_x + 60, m_PetBack.m_Picture.m_y + 230);
		m_PetProPerty[2].SetString(oss.str());
		pCanvas->Add(&m_PetProPerty[2]);

		oss.str("");
		oss << pC->m_PcData.m_pPets[m_TruePetIDSelect]->m_PetData.m_HP;
		m_PetProPerty[3].SetXY(m_PetBack.m_Picture.m_x + 60, m_PetBack.m_Picture.m_y + 255);
		m_PetProPerty[3].SetString(oss.str());
		pCanvas->Add(&m_PetProPerty[3]);

		oss.str("");
		oss << pC->m_PcData.m_pPets[m_TruePetIDSelect]->m_PetData.m_MP;
		m_PetProPerty[4].SetXY(m_PetBack.m_Picture.m_x + 60, m_PetBack.m_Picture.m_y + 280);
		m_PetProPerty[4].SetString(oss.str());
		pCanvas->Add(&m_PetProPerty[4]);
	}
	pCanvas->Add(&m_Button, 1);
	m_PetProPerty[5].SetColor(RGB(255, 255, 255));
	m_PetProPerty[5].SetXY(m_Button.m_Picture.m_x + 5, m_Button.m_Picture.m_y + 3);
	m_PetProPerty[5].SetString("出战");
	pCanvas->Add(&m_PetProPerty[5]);

}

bool cInterfaceFight::ProcessPet召唤界面()
{
	m_PetIDSelect = -1;
	if (m_MoveBack)
	{
		m_Select = 17;
		if (!CheckL())
			m_MoveBack = false;
		g_pMainState->SetMouseOnMap(false);
		return true;
	}
	if (isOn(g_xMouse, g_yMouse, m_PetBack.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);

		if (CheckOn(&m_Cancel, 100))return true;
		int xB, yB, hB, wB;
		xB = m_PetBack.m_Picture.m_x;
		yB = m_PetBack.m_Picture.m_y;
		hB = m_PetBack.m_Picture.m_Height;
		wB = m_PetBack.m_Picture.m_Width;

		cPcData& pc = ((cCharacter*)g_pMainState->m_FightWorkList[m_NowFighterID].m_pObj->m_pIndex)->m_PcData;
		int yInv = 22;
		if (pc.m_NumofBB > 0)
		{
			yInv = 112 / pc.m_NumofBB;
		}
		if (yInv > 28) yInv = 28;
		else if (yInv < 16) yInv = 16;

		if (g_yMouse > yB + 22 &&
			g_yMouse< yB + 172 + 28 &&
			g_xMouse> xB + 25 &&
			g_xMouse < xB + 130)
		{


			m_PetIDSelect = (g_yMouse - (yB + 55)) / yInv;
//			if (m_PetIDSelect>3)m_PetIDSelect = 3;
			if (pc.m_NumofBB <= m_PetIDSelect)
				m_PetIDSelect = pc.m_NumofBB - 1;
			if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
			{
				g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
				m_TruePetIDSelect = m_PetIDSelect;

				if (m_TruePetIDSelect >= 0 && m_TruePetIDSelect < pc.m_NumofBB)
				{
					s_uiPetSkill.UpdateData(&pc.m_pPets[m_TruePetIDSelect]->m_PetData, false);
				}
					
			}
		}
		if (m_TruePetIDSelect > -1 )
		{
			if (m_TruePetIDSelect >= pc.m_NumofBB)
			{
				m_TruePetIDSelect = pc.m_NumofBB - 1;
			}
//			s_uiPetSkill.UpdateData(&pd, false);
			if (isOn(g_xMouse, g_yMouse, m_Button.m_PreShowRect))
			{
				if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
				{
					g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
					m_Button.SetFrame(1);

					auto& list = g_pMainState->m_FightWorkList[m_NowFighterID + 5];
					cPet* pet = pc.m_pPets[m_TruePetIDSelect];
					cPetData& pd = pet->m_PetData;
					if (!(list.isExist && list.CheckDie()) &&  pd._owerIdx >= 0 && pd._owerIdx != pc.m_FightPetID && 
						pd.m_Lv <= pc.m_Lv + cct::LvGapFromRoleAndBaby &&
						pet->GetData()->m_LvTake <= pc.m_Lv)
					{
						pd._owerIdx = -1;
						g_pMainState->m_FightWorkList[m_NowFighterID].m_SkillSelect.SkillID = 1004;
						g_pMainState->m_FightWorkList[m_NowFighterID].m_SkillSelect.TargetID = m_NowFighterID + 5;
						g_pMainState->m_FightWorkList[m_NowFighterID].m_SkillSelect.SkillLv = m_TruePetIDSelect;
						g_pMainState->m_FightWorkList[m_NowFighterID].m_WorkType = WORKTYPE_SUMMON;
						SelectMode(FMENU_NORMAL);
						AddTurn();
						return true;
					}
				}
				else m_Button.SetFrame(2);
			}
			else m_Button.SetFrame(0);
		}
		else  m_Button.SetFrame(3);

		//鼠标在空白处,准备移动
		m_Select = 16;
		CheckL();
		if (CheckRButton())return true;
	}
	return true;
}



void cInterfaceFight::ShowMenu(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Magic, 1);
	pCanvas->Add(&m_Item, 1);
	pCanvas->Add(&m_Defend, 1);
	pCanvas->Add(&m_Guard, 1);
	pCanvas->Add(&m_Summon, 1);
	//	pCanvas->Add(&m_Auto, 1);
	pCanvas->Add(&m_Catch, 1);
	pCanvas->Add(&m_Fabao, 1);
	pCanvas->Add(&m_Escape, 1);
	pCanvas->Add(&m_Stunt, 1);
	pCanvas->Add(&m_Conduct, 1);
}

void cInterfaceFight::ShowItem(cCanvas* pCanvas)
{
	pCanvas->Add(&m_ItemBack, 1);
	pCanvas->Add(&m_TitleT);
	pCanvas->Add(&m_Cancel, 1);
	g_pMainState->m_ItemSelect.Show(pCanvas);
	/*
	for (int i = 0; i < 20; i++)
	{
	if (m_ItemCanUse[i])
	{
	pCanvas->Add(&m_ItemHead[i], 1);
	}
	}
	pCanvas->Add(&m_ItemSelectFrame, 1);*/
}

void cInterfaceFight::ShowMagic(cCanvas* pCanvas)
{
	pCanvas->Add(&m_MagicBack, 1);
	pCanvas->Add(&m_TitleT);
	pCanvas->Add(&m_SkillPreSelectT);
	pCanvas->Add(&m_Cancel, 1);
	for (int i = 0; i < m_NumofSkill; i++)
		pCanvas->Add(&m_SkillHead[i], 1);
}

bool cInterfaceFight::ProcessNormal()
{
	if (m_pObjSelect)
	{
		if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
		{
			g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
			if (m_pObjSelect->m_IndexType == INDEXTYEP_CHARACTER)
			{
				g_pMainState->m_ChaKan.Set((cCharacter*)m_pObjSelect->m_pIndex);
			}
			else
			{
				g_pMainState->m_ChaKan.Set((cPet*)m_pObjSelect->m_pIndex);
			}

			g_pMainState->m_ChaKan.OnOff(true);
			return true;
		}
	}
	int Objselect;
//	if (g_pMainState->Keyboard.GetKeyState(DIK_LCONTROL))
	Objselect = m_NowFighterID < 10 ? 10 : 0;
	{
		Objselect = g_pMainState->m_Cursor.SelectObj(Objselect/*m_NowFighterID*/, 4/*9*/, m_pObjSelect);
	}
//	else 
	if (!m_pObjSelect)
	{
		Objselect = g_pMainState->m_Cursor.SelectObj(m_NowFighterID, 4, m_pObjSelect);
	}
	if (-1 == Objselect)return false;

	m_pFightState->m_pFightWorkList[m_NowFighterID]->targetID = Objselect;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_WorkType = WORKTYPE_ATTACK;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillLv = 0;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillID = 1000;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.TargetID = Objselect;
	AddTurn();
	return true;

}

bool cInterfaceFight::ProcessMagic2()
{
	if (CheckRButton())return true;
	int Objselect = g_pMainState->m_Cursor.SelectObj(m_NowFighterID, m_pSkillSelect->m_SkillType, m_pObjSelect);
	if (-1 == Objselect)return false;
	sFightWork* pList = m_pFightState->m_pFightWorkList[m_NowFighterID];
	if (pList->m_pObj->m_IndexType == INDEXTYEP_CHARACTER)
	{
		cCharacter* pc = (cCharacter *)pList->m_pObj->m_pIndex;
		pList->m_SkillSelect.SkillLv = pc->m_PcData.m_MengPaiSkillLvs[m_pSkillSelect->m_Owner];
		pList->m_SkillSelect.SkillID = m_pSkillSelect->m_Id;
	}
	else
	{
		pList->m_SkillSelect.SkillLv = pList->m_pObj->getPropertyData()->m_Lv;
		pList->m_SkillSelect.SkillID = m_pSkillSelect->m_Id + 2000;
	}
	
	int Type = g_pMainState->m_SkillManager.GetSkill(pList->m_SkillSelect.SkillID)->m_SkillType;
	if (Type == 0 || Type == 2 || Type == 5)
	{
		Objselect = m_NowFighterID;
	}
	pList->m_SkillSelect.TargetID = Objselect;
	pList->m_WorkType = WORKTYPE_MAGIC;

	m_pFightState->m_pFightWorkList[Objselect]->m_pObj->SetShine(false);
	SelectMode(FMENU_NORMAL);
	m_pSkillSelect = 0;
	AddTurn();
	return true;
}

bool cInterfaceFight::ProcessMagic()
{
	m_pSkillSelect = 0;

	if (m_MoveBack)
	{
		m_Select = 17;
		if (!CheckL())
			m_MoveBack = false;
		g_pMainState->SetMouseOnMap(false);
		return true;
	}

	if (!isOn(g_xMouse, g_yMouse, m_MagicBack.m_PreShowRect))
	{
		m_MoveBack = false;
		return true;
	}
	g_pMainState->SetMouseOnMap(false);

	if (CheckOn(&m_Cancel, 100))return true;

	int i = 0;
	for (; i < m_NumofSkill; i++)
	{
		if (isOn(g_xMouse, g_yMouse, m_SkillHead[i].m_PreShowRect))
		{
			m_Select = 14;
			string text[3];
			text[0] = m_pSkillShow[i]->m_Name;
			text[1] = m_pSkillShow[i]->m_Text;
			ostringstream oss;
			oss << "消耗:";
			oss << m_pSkillShow[i]->m_tCost;
			text[2] = oss.str();
			m_Describe.Set(g_xMouse, g_yMouse, m_pSkillShow[i]->m_BigHead, 3, text);
			if (0 == m_Describe.m_NeedShow)g_pMainState->InterfaceSetShow(&m_Describe, true);
			m_pSkillSelect = m_pSkillShow[i];
			if (CheckL())return true;
			if (CheckRButton())return true;
			break;
		}
	}
	if (i == m_NumofSkill)
	{
		m_Select = 15;
		if (CheckRButton())return true;

		if (m_Describe.m_NeedShow)
			m_Describe.OnOff(false);
		//鼠标在空白处,准备移动
		m_Select = 16;
		CheckL();
	}
	return false;
}

void cInterfaceFight::MoveSpecial(int x, int y)
{
	m_MagicBack.m_x = x;
	m_MagicBack.m_y = y;
	m_TitleT.SetXY(x + 50, y + 3);
	m_Cancel.SetXY(x + m_MagicBack.m_pFile->GetWidth() - 20, y + 4);
	int xStart = x + 35;
	int yStart = y + 32;
	for (int i = 0; i < m_SpecialNum; i++)
	{
		int x1 = i % 2;
		int y1 = i / 2;
		m_SpecialHead[i].SetXY(xStart + x1 * 60, yStart + y1 * 60);
	}
}

void cInterfaceFight::ShowSpecial(cCanvas* pCanvas)
{
	pCanvas->Add(&m_MagicBack, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_TitleT);
	for (int i = 0; i < m_SpecialNum; i++)
		pCanvas->Add(&m_SpecialHead[i], 1);
}

bool cInterfaceFight::ProcessSpecial()
{
	if (!isOn(g_xMouse, g_yMouse, m_MagicBack.m_PreShowRect))return false;
	g_pMainState->SetMouseOnMap(false);
	if (CheckOn(&m_Cancel, 100))return true;
	int i = 0;
	for (; i < m_SpecialNum; i++)
		if (isOn(g_xMouse, g_yMouse, m_SpecialHead[i].m_PreShowRect))
		{
		sSkill* pSkill = g_pMainState->m_SkillManager.GetSpecialSkill(m_SpecialID[i]);
		string text[3];
		text[0] = pSkill->m_Name;
		text[1] = pSkill->m_Text;
		ostringstream oss;
		oss << "消耗:";
		oss << pSkill->m_Cost;
		text[2] = oss.str();
		m_Describe.Set(g_xMouse, g_yMouse, pSkill->m_BigHead, 3, text);
		g_pMainState->InterfaceSetShow(&m_Describe, true);
		//cCharacter* pC = (cCharacter*)g_pMainState->m_pFightState->m_pList[m_NowFighterID]->m_pData->m_pIndex;
		m_pSkillSelect = g_pMainState->m_SkillManager.GetSpecialSkill(m_SpecialID[i]);// pC->m_PCData.m_SpecialSkillList[i]);
		m_Select = 101 + i;
		if (CheckL())return true;
		break;
		}
	if (i == m_SpecialNum)
	{
		if (m_Describe.m_NeedShow)m_Describe.OnOff(false);
	}
	CheckRButton();
	return true;
}

bool cInterfaceFight::ProcessSpecial2()
{
	if (CheckRButton())return true;
	int Objselect = g_pMainState->m_Cursor.SelectObj(m_NowFighterID, m_pSkillSelect->m_SkillType, m_pObjSelect);
	if (-1 == Objselect)return false;
	cCharacter* pc = (cCharacter *)m_pFightState->m_pFightWorkList[m_NowFighterID]->m_pObj->m_pIndex;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillLv = 0;

	int skillid = -1;
	int num = m_SpecialSelect;
	for (int i = 0; i < 6; i++)
	{
		if (-1 != pc->m_PcData.m_SpecialSkillList[i])
		{
			num -= 1;
			if (num < 0)
			{
				skillid = pc->m_PcData.m_SpecialSkillList[i] + 3000;
				break;
			}
		}
	}



	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillID = skillid;//pc->m_PCData.m_SpecialSkillList[m_SpecialSelect]+3000;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.TargetID = Objselect;
	m_pFightState->m_pFightWorkList[m_NowFighterID]->m_WorkType = WORKTYPE_MAGIC;
	m_pSkillSelect = 0;
	m_pFightState->m_pFightWorkList[Objselect]->m_pObj->SetShine(false);
	SelectMode(FMENU_NORMAL);
	AddTurn();
	return true;
}

bool cInterfaceFight::ProcessGrab抓捕()
{
	if (CheckRButton())return true;
	int Objselect = g_pMainState->m_Cursor.SelectObj(m_NowFighterID, 4, m_pObjSelect);
	if (-1 != Objselect)
	{
		if (m_pFightState->m_pFightWorkList[Objselect]->m_pObj->GetDataType() != INDEXTYEP_PET)
			return true;

		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_WorkType = WORKTYPE_CATCH;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillLv = 0;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.SkillID = 1001;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect.TargetID = Objselect;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->targetID = Objselect;
		SelectMode(FMENU_NORMAL);
		m_pSkillSelect = 0;
		AddTurn();
		return true;
	}
	else
		if (m_pObjSelect)
		{
		g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Grab);
		}
		else  g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_No);
		return false;
}

bool cInterfaceFight::ProcessItem2()
{
	if (CheckRButton())return true;
	sItem2* pItem = g_pMainState->m_SkillManager.GetItem(m_NowFighterID);
	if (pItem->GetType() != 22 && pItem->GetType() != 25 && !(pItem->GetType() == 28 && pItem->GetID() == 11)) return true;
	int selecttype;
	int  skillid;
	switch (pItem->GetType())
	{
		// 不可叠加
	case 28:
		if (pItem->GetID() == 11)//乾坤袋
		{
			selecttype = 4;
			skillid = 1007;
		}
		else
		{
			selecttype = 3;
			skillid = 1003;
		}
		break;
		// 暗器
	case 25:
		selecttype = 4;
		skillid = 1005;
		break;
	case 24: //法宝
		selecttype = pItem->m_pItemData->m_UseType;
		skillid = 1003;
		break;
	default:
		selecttype = 3;
		skillid = 1003;
		break;
	}
	int Objselect = g_pMainState->m_Cursor.SelectObj(m_NowFighterID, selecttype, m_pObjSelect);
	//int Objselect = SelectObj(m_NowFighterID, selecttype);
	if (-1 != Objselect)
	{
		auto& ski = m_pFightState->m_pFightWorkList[m_NowFighterID]->m_SkillSelect;
		ski.SkillID = skillid;
		ski.SkillLv = 0;
		ski.TargetID = Objselect;
		m_pFightState->m_pFightWorkList[m_NowFighterID]->m_WorkType = WORKTYPE_MAGIC;
		SelectMode(FMENU_NORMAL);
		m_pSkillSelect = 0;
		AddTurn();
		return true;
	}
	return false;
}

bool cInterfaceFight::ProcessProtect()
{
	CheckRButton();
	int Objselect = g_pMainState->m_Cursor.SelectObj(m_NowFighterID, 9, m_pObjSelect);
	if (-1 != Objselect)
	{
		if (Objselect == m_NowFighterID)return false;//不能保护自己

		SelectMode(FMENU_NORMAL);
		cPropertyData* pTargetData;
		g_pMainState->m_FightWorkList[Objselect].m_pObj->GetPropertyData(pTargetData);
		pTargetData->m_FightData.m_guardID.push_back(m_NowFighterID);
		m_pSkillSelect = 0;
		g_pMainState->m_FightWorkList[m_NowFighterID].m_WorkType = -2;
		AddTurn();
		return true;
	}
	return false;
}

bool cInterfaceFight::InitMagic2()
{
	g_pMainState->m_Cursor.Set(g_pMainState->m_Cursor.m_Magic);
	SelectMode(FMENU_MAGIC2);
	return true;
}

void cInterfaceFight::OnOff(bool NeedShow)
{
	if (m_NeedShow == NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_NeedShow)
	{
		Init();
	}
	g_pMainState->m_Canvas.SetRedrawAll();
}

bool cInterfaceFight::CheckS()
{
	if (g_pMainState->Keyboard.GetKeyState(DIK_S))
	{
		g_pMainState->Keyboard.SetLock(DIK_S);
		sFightWork* figher = m_pFightState->m_pFightWorkList[m_NowFighterID];
		int id = figher->m_SkillPreSelect.SkillID;
		if (-1 == id)return true;

		sSkill* skill = g_pMainState->m_SkillManager.GetSkill(id);
		m_pSkillSelect = skill;
		SelectMode(FMENU_MAGIC2);
		return true;
	}
	return false;
}

void cInterfaceFight::SetTeamControl(bool bControl)
{
	for (int i = 0; i < 10; i++)
	{
		m_bCanControl[i] = bControl;
	}
	m_bCanControl[0] = true;
	m_bCanControl[5] = true;
}

cInterfaceFight::cInterfaceFight()
{
	for (int i = 0; i < 20; i++)
		m_bCanControl[i] = false;
}

bool cInterfaceFight::CheckControl(int id)
{
	return m_bCanControl[id];
}

bool cInterfaceFight::CheckControl()
{
	bool isAuto = true;
	for (int i = 0; i < 5; ++i)
	{
		if (!g_pMainState->m_FightWorkList[i].isExist)
		{
			continue;
		}
		if (CheckTurn(i))
		{
			isAuto = false;
			break;
		}
	}
	return !isAuto;
}

