#include "_global.h"


bool cInterfaceTeam::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_xPosList.resize(20);
	m_yPosList.resize(20);
	m_tMengPai.resize(5);
	m_TeamTurn.resize(20);
	m_lineupSelectBP.resize(11);
	m_lineupSelectBPT.resize(11);
	m_Describe.resize(2);
	m_lineupPeoplepp.resize(5);
	m_lineupPeoplep.resize(5);
	m_lineupSelectB.Set(&g_pMainState->m_Button4);
	m_lineupSelectB.m_bStatic = true;
	m_SetFriend.Set(&g_pMainState->m_Button4);
	m_SetFriend.m_bStatic = true;


	m_Fighter.resize(5);
	m_tName.resize(5);
	m_tLv.resize(5);

	for (int i = 0; i < m_TeamTurn.size(); i++)
	{
		m_TeamTurn[i] = i;
	}
	m_lineupB.Load(0x79D01E0E);
	m_lineupB.SetStatic(true);
	m_lineupBT.SetColor(RGB(255, 255, 255));
	m_lineupBT.SetString("阵型");

	//m_ControlB.Set(&g_pMainState->m_Button4);
	//m_ControlB.m_bStatic=true;
	//m_ControlBT.SetColor(RGB(255, 255, 255));
	//m_ControlBT.SetString("控制对友");


	m_tSetFriend.SetColor(RGB(255, 255, 255));
//	m_tSetFriend.SetString("配置队友");
	m_lineupSelectBack.Load(0x8072710D);
	m_lineupSelectBack.SetStatic(true);
	m_lineupPeople.Load(0x0E43E0DF);

	for (int i = 0; i < 11; i++)
	{
		m_lineupSelectBP[i].Set(&g_pMainState->m_Button4);
		m_lineupSelectBP[i].m_bStatic = true;
		m_lineupSelectBPT[i].SetXY(0, 0);
		m_lineupSelectBPT[i].SetColor(RGB(255, 255, 255));
		m_lineupSelectBPT[i].m_hFont = g_pMainState->m_hFont[0];
	}
	m_Describe[0].SetColor(RGB(255, 255, 0));
	m_Describe[1].SetColor(RGB(0, 255, 0));
	m_Describe[1].LockWidth(211);
	m_lineupSelectBT.SetColor(RGB(255, 255, 255));
	m_lineupSelectBT.m_hFont = g_pMainState->m_hFont[0];
	m_lineupSelectBT.SetXY(0, 0);


	m_lineupSelectBPT[0].SetString("普通阵");
	m_lineupSelectBPT[1].SetString("地载阵");
	m_lineupSelectBPT[2].SetString("风扬阵");
	m_lineupSelectBPT[3].SetString("虎翼阵");
	m_lineupSelectBPT[4].SetString("龙飞阵");
	m_lineupSelectBPT[5].SetString("鸟翔阵");
	m_lineupSelectBPT[6].SetString("蛇蟠阵");
	m_lineupSelectBPT[7].SetString("天覆阵");
	m_lineupSelectBPT[8].SetString("云垂阵");
	m_lineupSelectBPT[9].SetString("雷绝阵");
	m_lineupSelectBPT[10].SetString("鹰啸阵");
	m_lineupSelectBT.SetString("选定阵型");

	m_lineupPeoplepT.resize(5);
	for (int i = 0; i < 5; i++)
	{
		m_lineupPeoplep[i].Set(&m_lineupPeople);
		m_lineupPeoplep[i].m_bStatic = true;
		m_lineupPeoplepT[i].SetColor(RGB(255, 255, 255));
		m_lineupPeoplepT[i].m_hFont = g_pMainState->m_hFont[0];
	}

	m_lineupPeoplepT[0].SetString("1");
	m_lineupPeoplepT[1].SetString("2");
	m_lineupPeoplepT[2].SetString("3");
	m_lineupPeoplepT[3].SetString("4");
	m_lineupPeoplepT[4].SetString("5");

	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_lineupCancelB.Set(&g_pMainState->m_Cancel);
	m_lineupCancelB.m_bStatic = true;

	m_Back.Load(0xF5B8E062);
	m_Back.SetStatic(true);
	m_FighterSelectid = -1;
	m_FighterSelect.Load(0xC540D7A7);
	m_FighterSelect.SetStatic(true);
	for (int i = 0; i < 5; i++)
	{
		m_Fighter[i].Init();
		m_FighterBtns[i].Set(&g_pMainState->m_Button2);
		m_FighterBtns[i].m_bStatic = true;
		m_tFighterBtns[i].SetColor(RGB(255, 255, 255));
		m_tFighterBtns[i].SetString("自动");
	}

	m_lineupName.m_hFont = g_pMainState->m_hFont[0];
	m_lineupName.SetString(m_lineupSelectBPT[0].GetString());
	m_lineupSelectBP[0].SetFrame帧(1);

	m_tSmall.SetString("0");
	m_tBig.SetString(cct::MaxRoleLv);
	m_tLangTime.SetColor(RGB(0xFF, 0xFF, 0));
	m_pFightState = g_pMainState->m_pFightState;


	forr(_accs, i)
	{
		_accs[i]._show8 = 1;
		_accs[i]._tag = i;
		_accs[i]._cb = [&](int idx, int skill)
		{
			if (idx >= g_pMainState->m_Friend._friends.size()/*m_LeaveBegin*/)
			{
				return;
			}
			int id = GetTeamTurn(idx);
			auto& list = g_pMainState->m_FightWorkList[id];
			if (!list.isExist)
			{
				return;
			}
			g_pMainState->m_Friend._friends[id].dski = list.m_FriendListid = skill;
			g_pMainState->m_pFightState->m_FightMenu.SetControl(id, false);
			g_pMainState->m_pFightState->m_FightMenu.SetControl(id + 5, false);
			g_pMainState->m_Friend._friends[id].ctrl = false;
			m_tFighterBtns[idx].SetString("默认");
		};
		_accs[i].Init();
	}

	forv(_tLeaveings, k)
	{
		_tLeaveings.at(k).m_hFont = g_pMainState->m_hFont[5];
		_tLeaveings.at(k).SetStyle(2);
		_tLeaveings.at(k).SetString("离队中");
		_tLeaveings.at(k).SetColor(RGB(0xFF, 0, 0));
	}

	_bs.resize(4);
	_ts.resize(4);
	forv(_bs, k)
	{
		_bs.at(k).Set(&g_pMainState->m_Button4);
		_bs.at(k).m_bStatic = TRUE;
		_ts.at(k).SetColor(RGB(0xFF, 0xFF, 0xFF));
	}
	_ts.at(0).SetString("前移");
	_ts.at(1).SetString("升为队长");
	_ts.at(2).SetString("酒肆");
	_ts.at(3).SetString("巫医");

	Move(g_half320 - m_Back.m_Picture.m_Width / 2, g_half240 - m_Back.m_Picture.m_Height / 2);
	MoveLineSelect(g_half320 - m_lineupSelectBack.m_Picture.m_Width / 2, g_half240 - m_lineupSelectBack.m_Picture.m_Height / 2);

	return true;
}

bool cInterfaceTeam::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.m_Picture.SetXY(x, y);
	m_lineupName.SetXY(x + 100, y + 42);
	m_lineupB.SetX(x + 20);
	m_lineupB.SetY(y + 38);
	m_lineupBT.SetXY(x + 24, y + 40);

	//m_ControlB.SetX(x + 380);
	//m_ControlB.SetY(y + 40);
	//m_ControlBT.SetXY(x + 384, y + 42);

	// 300
	m_SetFriend.SetXY(x + 208, y + 38);
	m_tSetFriend.SetXCenter(m_SetFriend.GetCenter());
	m_tSetFriend.UpdateXCenter();
	m_tSetFriend.SetY(m_SetFriend.GetY() + 2);
	m_tSmall.SetXY(x + 214, y + 42);
	m_tBig.SetXY(x + 259, y + 42);
	m_tLangTime.SetXY(x + 25, y + 12);
	for (int i = 0; i < 5; i++)
	{
		m_Fighter[i].SetXY(x + 65 + i * 120, y + 190);
		m_Fighter[i].MoveShadow();
		m_tName[i].SetXCenter(x + 65 + i * 120);
		m_tName[i].SetY(y + 220);
		m_tName[i].UpdateXCenter();
		m_tMengPai[i].SetXCenter(x + 65 + i * 120);
		m_tMengPai[i].SetY(y + 243);
		m_tMengPai[i].UpdateXCenter();
		m_tLv[i].SetXY(x + 16 + i * 119, y + 266);

		m_FighterBtns[i].SetXY(x + 50 + i * 119, y + 263);
		m_tFighterBtns[i].SetXCenter(m_FighterBtns[i].GetCenter());
		m_tFighterBtns[i].UpdateXCenter();
		m_tFighterBtns[i].SetY(m_FighterBtns[i].m_y + 2);

		_accs[i].m_Accelatorbackp[0].SetXY(m_FighterBtns[i].m_x + 46, m_FighterBtns[i].m_y);
		_accs[i].m_AccelatorSkill[0].SetXY(m_FighterBtns[i].m_x + 46 + 4, m_FighterBtns[i].m_y + 3);
//		_accs[i].MoveMagicBack(x + 94 + i * 119, y + 263);
	}

	forv(_bs, k)
	{
		_bs.at(k).SetXY(x + 208 + (k + 1) * 80, m_SetFriend.GetY());
		_ts.at(k).SetXCenter(_bs.at(k).GetCenter());
		_ts.at(k).SetY(_bs.at(k).GetY() + 2);
		_ts.at(k).UpdateXCenter();
	}
	forv(_tLeaveings, k)
	{
		_tLeaveings.at(k).SetXY(x + 20 + k * 119, y + 77);
	}

	m_Cancel.SetXY(x + 593, y + 4);

	m_FightRect.left = m_xPos + 10;
	m_FightRect.right = m_xPos + 600;
	m_FightRect.top = m_yPos + 72;
	m_FightRect.bottom = m_yPos + 211;
	m_FighterSelect.m_Picture.m_y = m_FightRect.top;
	m_FighterSelect.m_Picture.m_x = m_FightRect.left + 120 * m_FighterSelectid;
	return true;
}

bool cInterfaceTeam::ProcessInput()
{
	ResetButton();
	m_Select = -1;

	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}
	if (m_bLiineupSelect)
		return ProcessSelectLineup(g_xMouse, g_yMouse);
	if (isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);
		g_pMainState->m_Cursor.m_FollowMode = false;
		//阵型选择
		if (CheckOn(&m_lineupB, 21))return true;
		//	if (CheckOn(&m_ControlB, 24))return true;
		if (CheckOn(&m_Cancel, 20))return true;

		int m_LeaveBegin = getLeaveBegin();
		for (int i = 0; i < m_LeaveBegin; ++i)
		{
			_accs[i].ProcessInput();
		}

		if (isOn(g_xMouse, g_yMouse, m_FightRect))
		{
			m_Select = (g_xMouse - m_FightRect.left) / 120;

			if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
			{
				g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
				
				doSwap(m_LeaveBegin, m_FighterSelectid, m_Select);
				return true;
				if (m_FighterSelectid < 0 || m_FighterSelectid >= m_LeaveBegin || m_Select == m_FighterSelectid || m_Select < 0 || m_Select >= m_LeaveBegin)
				{
					return true;
				}
				auto& list = g_pMainState->m_FightWorkList;
				auto& os = g_pMainState->m_Friend._friends;
				int i1 = m_TeamTurn[m_FighterSelectid];
				int i2 = m_TeamTurn[m_Select];
				if (!(list[i1].isExist && list[i2].isExist))
				{
					return true;
				}

				swap(os[i1], os[i2]);
				update(m_TeamTurn[m_FighterSelectid] == 0 || m_TeamTurn[m_Select] == 0, m_LeaveBegin);
// 				list[i1].Swap(list[i2]);
// 				list[i1].m_pObj->m_IDInFightlist = list[i1].m_pObj->getPropertyData()->m_IDinFightWorkList = i1;
// 				list[i2].m_pObj->m_IDInFightlist = list[i2].m_pObj->getPropertyData()->m_IDinFightWorkList = i2;
// 
// 				if (m_TeamTurn[m_FighterSelectid] == 0 || m_TeamTurn[m_Select] == 0)
// 				{
// 					int x = g_pHeroObj->GetX();
// 					int y = g_pHeroObj->GetY();
// 					g_pMainState->SetCharacter(0/*m_TeamTurn[0]*/);
// 					g_pHeroObj->SetXY(x, y);
// 					g_pHeroObj->Stand();
// 				}
				UpDate();
				g_pMainState->m_PCHead.UpDateHead();
				return true;
			}


			return CheckL();
		}
		if (CheckOn(&m_SetFriend, 8))return true;
		for (int i = 0; i < 5; ++i)
		{
			if (CheckOn(&m_FighterBtns[i], 10000 + i))return true;
		}
		forv(_bs, k)
		{
			if (CheckOn(&_bs.at(k), 1000 + k))return true;
		}

		m_Select = 0;
		if (CheckRB())return true;
		m_Select = 7;
		if (CheckL())return true;
	}
	return true;
}


bool cInterfaceTeam::doSwap(int leaveBegin, int select, int target)
{
	if (target < 0 || target >= leaveBegin || select == target || select < 0 || select >= leaveBegin)
	{
		return false;
	}
	auto& list = g_pMainState->m_FightWorkList;
	auto& os = g_pMainState->m_Friend._friends;
	int i1 = m_TeamTurn[select];
	int i2 = m_TeamTurn[target];
	if (!(list[i1].isExist && list[i2].isExist))
	{
		return false;
	}
	swap(os[i1], os[i2]);
	update(m_TeamTurn[select] == 0 || m_TeamTurn[target] == 0, leaveBegin);
// 	list[i1].Swap(list[i2]);
// 	list[i1].m_pObj->m_IDInFightlist = list[i1].m_pObj->getPropertyData()->m_IDinFightWorkList = i1;
// 	list[i2].m_pObj->m_IDInFightlist = list[i2].m_pObj->getPropertyData()->m_IDinFightWorkList = i2;
// 
// 	if (m_TeamTurn[m_FighterSelectid] == 0 || m_TeamTurn[m_Select] == 0)
// 	{
// 		int x = g_pHeroObj->GetX();
// 		int y = g_pHeroObj->GetY();
// 		g_pMainState->SetCharacter(0/*m_TeamTurn[0]*/);
// 		g_pHeroObj->SetXY(x, y);
// 		g_pHeroObj->Stand();
// 	}
	UpDate();
	g_pMainState->m_PCHead.UpDateHead();
	return true;
}



bool cInterfaceTeam::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	if (m_bLiineupSelect)
		return ShowSelectLineup(pCanvas);
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_lineupName);
	pCanvas->Add(&m_lineupB, 1);
	pCanvas->Add(&m_lineupBT);

	/*pCanvas->Add(&m_ControlB, 1);
	pCanvas->Add(&m_ControlBT);*/

	pCanvas->Add(&m_SetFriend, 1);
	pCanvas->Add(&m_tSetFriend);

//	pCanvas->Add(&m_tSmall);
//	pCanvas->Add(&m_tBig);
	pCanvas->Add(&m_tLangTime);
	if (m_FighterSelectid > -1)
	{
		pCanvas->Add(&m_FighterSelect, 1);
	}

	int fightnum = g_pMainState->m_Friend._friends.size(); //g_pMainState->GetLiveNum(0, 5);
	for (int k = 0; k < fightnum; k++)
	{
		if (m_Fighter[k].m_pIndex)
		{
			pCanvas->Add(&m_tName[k]);
			pCanvas->Add(&m_tMengPai[k]);
			pCanvas->Add(&m_tLv[k]);
			pCanvas->Add(m_Fighter[k].GetShadow(), 1);
			cWasFile* foot = &m_Fighter[k].m_Foot;
			if (foot->m_NowID)
			{
// 				int x = foot->GetX();
// 				int y = foot->GetY();
//				foot->SetX(m_Fighter[k].GetShadow()->GetX());
//				foot->SetY(m_Fighter[k].GetShadow()->GetY());
				pCanvas->Add(foot, 1);
//				foot->SetX(x);
//				foot->SetY(y);
			}
//			bool isShow = m_Fighter[k].GetShow();
//			m_Fighter[k].SetShow(true);
			m_Fighter[k].ShowOnScreen(pCanvas);
//			m_Fighter[k].SetShow(isShow);
			pCanvas->Add(&m_FighterBtns[k], 1);
			pCanvas->Add(&m_tFighterBtns[k], 1);
		}
	}
	forr(_accs, k)
	{
		_accs[k].Show(pCanvas);
		pCanvas->Add(&_accs[k].m_Accelatorbackp[0], 1);
		pCanvas->Add(&_accs[k].m_AccelatorSkill[0], 1);
	}

	forv(_bs, k)
	{
		pCanvas->Add(&_bs.at(k), 1);
		pCanvas->Add(&_ts.at(k));
	}
	for(int k = getLeaveBegin(); k < 5; ++k)
	{
		pCanvas->Add(&_tLeaveings.at(k));
	}

	pCanvas->Add(&m_Cancel, 1);
	return true;
}

bool cInterfaceTeam::UpDate()
{
	int fightnum = g_pMainState->m_Friend._friends.size();//g_pMainState->GetLiveNum(0, 5);

	cObj* pPet;
	ostringstream oss;
	for (int i = 0; i < 5; i++)
	{
		FreeFighter(i);
	}

	bool bErr = false;
	for (int i = 0; i < fightnum; i++)
	{
// 		if (!g_pMainState->m_FightWorkList[m_TeamTurn[i]].isExist)
// 		{
// 			bErr = true;
// 			if (!AutoSwap(i))
// 				return false;
// 		}
//		pPet = g_pMainState->m_FightWorkList[m_TeamTurn[i]].m_pObj;
		pPet = g_pMainState->m_Friend._friends[i].obj;
		m_Fighter[i].m_pIndex = pPet->m_pIndex;
		m_Fighter[i].m_IndexType = INDEXTYEP_CHARACTER; // pPet->m_IndexType;
		m_Fighter[i].m_Foot = pPet->m_Foot;
		m_Fighter[i].Set(POS_STAND);
//		pPet->GetPropertyData(pPetData);
		cPcData* pPetData = &((cCharacter*)pPet->m_pIndex)->m_PcData;
		m_tName[i].SetString(pPetData->m_Name);
		if (m_Fighter[i].m_IndexType == INDEXTYEP_CHARACTER)
		{
			cMengPai* pMengPai = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai((cCharacter*)pPet->m_pIndex);
			if (pMengPai)
				m_tMengPai[i].SetString(pMengPai->m_Name);
			else m_tMengPai[i].SetString("");
		}
 		else  	
 			m_tMengPai[i].SetString("");
		oss.str("");
		oss << pPetData->m_Lv/* << "级"*/;
		m_tLv[i].SetString(oss.str());
		m_tName[i].UpdateXCenter();
		m_tMengPai[i].UpdateXCenter();
	}

	forv(_accs, i)
	{
		int ski = g_pMainState->m_FightWorkList[m_TeamTurn[i]].m_FriendListid;
		if (i < getLeaveBegin())
		{
			if (ski < 0)
			{
				m_tFighterBtns[i].SetString(g_pMainState->m_pFightState->m_FightMenu.CheckControl(m_TeamTurn[i]) ? "手动" : "自动");
			}
			else
			{
				m_tFighterBtns[i].SetString("默认");
			}
		}
		else
		{
			m_tFighterBtns[i].SetString("休息");
		}

		if (ski < 0)
		{
			_accs[i].m_AccelatorSkill[0].Load(0);
		}
		else
		{
			_accs[i].m_AccelatorSkillid[0] = ski;
			_accs[i].m_AccelatorSkill[0].Load(g_pMainState->m_SkillManager.GetMengPaiSkill(ski)->m_SmallHead);
		}
	}
	if (bErr)
		g_pMainState->m_PCHead.UpDateHead();

	return true;
}

bool cInterfaceTeam::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	int m_LeaveBegin = getLeaveBegin();
	switch (m_Select)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		m_FighterSelectid = m_Select;
		m_FighterSelect.m_Picture.m_x = m_FightRect.left + 120 * m_FighterSelectid;
		m_FighterSelect.m_bMove = true;
		m_tSetFriend.SetString(m_FighterSelectid < m_LeaveBegin ? "离队" : "入队");
		break;
	case 6:
		if (1)
		{
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
				Move(m_xPos + xDel, m_yPos + yDel);
			}
		}
		return true;
	case 7://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	case 8:
		if (m_FighterSelectid >= 0 && m_FighterSelectid < g_pMainState->m_Friend._friends.size())
		{
			if (m_FighterSelectid < m_LeaveBegin)
			{
				if (m_LeaveBegin < 2)
				{
					g_pMainState->m_Tags.Add("再离就没人了");
					return true;
				}
				int trueid = g_pMainState->m_InterfaceTeam.GetTeamTurn(m_FighterSelectid);

				auto& os = g_pMainState->m_Friend._friends;
				auto& list = g_pMainState->m_FightWorkList;

				if (!list[trueid].isExist)
					return true;
				
//				g_pMainState->m_FightWorkList[trueid].isExist = false;
//				auto obj = list[trueid].m_pObj;
//				obj->SetShow(false);

				for (int i = m_FighterSelectid; i < 4; ++i)
				{
					swap(os[m_TeamTurn[i]], os[m_TeamTurn[i + 1]]);
//					list[m_TeamTurn[i]].Swap(list[m_TeamTurn[i + 1]]);
// 					int nexttrueid = g_pMainState->m_InterfaceTeam.GetTeamTurn(i + 1);
// 					if (g_pMainState->m_FightWorkList[nexttrueid].isExist)
// 					{
// 						g_pMainState->m_InterfaceTeam.SwapTeamTurn(i, i + 1);
// 						if (m_TeamTurn[i] == trueid)
// 						{
// 							trueid = m_TeamTurn[i + 1];
// 						}
// 						else if (m_TeamTurn[i + 1] == trueid)
// 						{
// 							trueid = m_TeamTurn[i];
// 						}
// 					}
// 					else
// 					{
// 						break;
// 					}
				}

				update(m_FighterSelectid == 0, --m_LeaveBegin);
				UpDate();
				g_pMainState->m_PCHead.UpDateHead();

// 				for (int i = 0; i < 5; ++i)
// 				{
// 					if (obj == g_pMainState->m_FightWorkList[i].m_pObj)
// 					{
// 						g_pMainState->m_FightWorkList[i].isExist = true;
// 						cPcData* pTargetData;
// 						obj->GetPropertyData(pTargetData);
// 						if (pTargetData->m_FightPetID >= 0)
// 						{
// 							g_pMainState->m_FightWorkList[i + 5].isExist = true;
// 						}
// 						break;
// 					}
// 				}
// 				UpDate();
//				m_PcData.m_IDinFightWorkList;
//				//g_pMainState->FreeFightList(g_pMainState->m_InterfaceTeam.GetTeamTurn(i));
// 				if (m_TeamTurn[0] != g_pMainState->m_HeroID)
// 				{
// 					int x = g_pHeroObj->GetX();
// 					int y = g_pHeroObj->GetY();
// 					g_pMainState->SetCharacter(m_TeamTurn[0]);
// 					g_pHeroObj->SetXY(x, y);
// 					g_pHeroObj->Stand();
// 
// 				}
				
			}
			else if (m_LeaveBegin < 5)
			{
				int trueid = g_pMainState->m_InterfaceTeam.GetTeamTurn(m_FighterSelectid);
//				if (!list[trueid].isExist)return true;
//				list[trueid].m_pObj->SetShow(true);

// 				if (m_LeaveBegin != m_FighterSelectid)
// 				{
// 					SwapTeamTurn(m_LeaveBegin, m_FighterSelectid);
// 				}
// 				++m_LeaveBegin;


				auto& os = g_pMainState->m_Friend._friends;
				auto& list = g_pMainState->m_FightWorkList;
				for (int i = m_FighterSelectid - 1; i >= m_LeaveBegin; --i)
				{
					swap(os[m_TeamTurn[i]], os[m_TeamTurn[i + 1]]);
//					list[m_TeamTurn[i]].Swap(list[m_TeamTurn[i + 1]]);
// 					int preid = g_pMainState->m_InterfaceTeam.GetTeamTurn(i + 1);
// 					if (true || !g_pMainState->m_FightWorkList[preid].isExist)
// 					{
// 						g_pMainState->m_InterfaceTeam.SwapTeamTurn(i, i + 1);
// 						if (m_TeamTurn[i] == trueid)
// 						{
// 							trueid = m_TeamTurn[i + 1];
// 						}
// 						else if (m_TeamTurn[i + 1] == trueid)
// 						{
// 							trueid = m_TeamTurn[i];
// 						}
// 					}
// 					else
// 					{
// 						break;
// 					}
					
				}

				update(false, ++m_LeaveBegin);

				UpDate();
				g_pMainState->m_PCHead.UpDateHead();
			}
			return true;
			if (m_FighterSelectid < 0)return true;
			int id = m_TeamTurn[m_FighterSelectid];
			if (id == g_pMainState->m_HeroID)return true;
			cPropertyData* ppetdata;
			g_pMainState->m_FightWorkList[id].m_pObj->GetPropertyData(ppetdata);
		//	id = g_pMainState->m_Friend.FindFriend(ppetdata->m_dataFileName);
			g_pMainState->m_Friend.m_friendqianghua.Set(g_pMainState->m_Friend.m_FriendList[id]);
			g_pMainState->m_Friend.m_friendqianghua.OnOff(true);
		}
		break;
	case 20:
		OnOff(false);
		m_Cancel.SetFrame帧(1);
		break;
	case 21:
		if (1)
		{
			m_bLiineupSelect = true;
			g_pMainState->m_Canvas.SetRedraw(m_lineupSelectBack.m_PreShowRect);
			m_Back.m_bMove = true;
			SetlineupPeople(m_eOurFormation);
			int havet = g_GlobalValues[1];
			m_lineupSelectBP[0].SetFrame帧(0);
			for (int i = 1; i < 11; i++)
			{
				if (havet & (1 << (i - 1)))
				{
					m_lineupSelectBP[i].SetFrame帧(0);
				}
				else m_lineupSelectBP[i].SetFrame帧(3);
			}
			m_plineupButton = 0;
			m_plineupButton = &m_lineupSelectBP[m_eOurFormation];
			m_plineupButton->SetFrame帧(1);
			m_plineupButton->m_bMove = true;
			m_lineupName.SetString(m_lineupSelectBPT[m_eOurFormation].GetString());
		}
		break;
	case 22:
		m_bLiineupSelect = false;
		break;
	case 23://设置阵法
		SetFormation(m_eLineupSelect, 0, true);
		break;
		/*case 24:
		m_ControlB.SetFrame(1);
		g_pMainState->m_pFightState->m_FightMenu.SetTeamControl();
		break;*/
		//阵法
	case 100:
	case 101:
	case 102:
	case 103:
	case 104:
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
	case 110:
		if (1)
		{
			if (m_plineupButton)
			{
				m_plineupButton->SetFrame帧(0);
				m_plineupButton->m_bMove = true;
				m_plineupButton = 0;
			}
			m_plineupButton = m_framprep;
			m_framprep->SetFrame帧(1);
			m_framprep = 0;
			m_eLineupSelect = (eFormation)(m_Select - 100);
			SetlineupPeople(m_eLineupSelect);
		}
		break;
	case 10000:
	case 10001:
	case 10002:
	case 10003:
	case 10004:
	{
		if (m_Select - 10000 >= m_LeaveBegin)
		{
			g_pMainState->m_Tags.Add("请先入队");
			break;
		}
		int id = g_pMainState->m_InterfaceTeam.GetTeamTurn(m_Select - 10000);
		bool f = g_pMainState->m_pFightState->m_FightMenu.CheckControl(id);
		int& skill = g_pMainState->m_FightWorkList[id].m_FriendListid;
		g_pMainState->m_pFightState->m_FightMenu.SetControl(id, !f);
		g_pMainState->m_pFightState->m_FightMenu.SetControl(id + 5, !f);
		g_pMainState->m_InterfaceTeam.m_tFighterBtns[m_Select - 10000].SetString(f ? "自动" : "手动");
		g_pMainState->m_Friend._friends[id].dski = skill = -1;
		g_pMainState->m_Friend._friends[id].ctrl = !f;
		g_pMainState->m_InterfaceTeam._accs[m_Select - 10000].m_AccelatorSkill[0].Load(0);
		UpDate();
	}
		break;
	case 1000:
	case 1001:
	{
		if (m_FighterSelectid < 0)
		{
			g_pMainState->m_Tags.Add("请先选择队员");
			break;
		}
		if (m_FighterSelectid >= m_LeaveBegin)
		{
			g_pMainState->m_Tags.Add("请先入队");
			break;
		}
		if (m_FighterSelectid == 0)
		{
			g_pMainState->m_Tags.Add("已经是队长了");
			break;
		}
		doSwap(m_LeaveBegin, m_FighterSelectid,  (m_Select == 1000) ? m_FighterSelectid - 1 : 0);
	}
		break;
	case 1002:
		if (g_StateType == STATE_MAIN)
		{
			for (int k = 0; k < 5; ++k)
			{
				auto& li = g_pMainState->m_FightWorkList.at(k);
				if (li.isExist)
				{
					li.m_pObj->getPcData()->FillHpMp();
				}
			}
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
			g_pMainState->m_PCHead.UpDateHead();
		}
		break;
	case 1003:
		if (g_StateType == STATE_MAIN)
		{
			for (int k = 0; k < 5; ++k)
			{
				auto& li = g_pMainState->m_FightWorkList.at(k);
				if (li.isExist)
				{
					auto pc = li.m_pObj->getPcData();
					for (int i = pc->m_NumofBB - 1; i >= 0; --i)
					{
						pc->m_pPets[i]->m_PetData.FillHpMp();
					}
				}
			}
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
			g_pMainState->m_PCHead.UpDateHead();
		}
	break;
	}
	return true;
}

bool cInterfaceTeam::ProcessSelectLineup(int xMouse, int yMouse)
{
	if (!isOn(xMouse, yMouse, m_lineupSelectBack.m_PreShowRect))return false;
	g_pMainState->SetMouseOnMap(false);
	for (int i = 0; i < 11; i++)
	{
		if (3 == m_lineupSelectBP[i].GetFrame())continue;
		if (1 == m_lineupSelectBP[i].GetFrame())continue;
		if (CheckOn(&m_lineupSelectBP[i], 100 + i))return true;
	}
	//取消
	if (CheckOn(&m_lineupCancelB, 22))return true;
	//选择阵法
	if (CheckOn(&m_lineupSelectB, 23))return true;
	m_Select = 1;
	if (CheckRB())return true;
	return true;
}

void cInterfaceTeam::MoveLineSelect(int x, int y)
{
	m_lineupSelectBack.SetX(x);
	m_lineupSelectBack.SetY(y);
	m_lineupCancelB.m_x = x + m_lineupSelectBack.GetWidth() - 22;
	m_lineupCancelB.m_y = y + 4;
	m_Describe[0].SetXY(x + 270, y + 24);
	m_Describe[1].SetXY(x + 270, y + 44);
	for (int i = 0; i < 11; i++)
	{
		int xo = i % 3;
		int yo = i / 3;
		m_lineupSelectBP[i].SetXY(x + 23 + xo * 80, y + 38 + yo * 30);
		m_lineupSelectBPT[i].SetXCenter(m_lineupSelectBP[i].GetX() + m_lineupSelectBP[i].GetShowWidth() / 2);
		m_lineupSelectBPT[i].SetY(m_lineupSelectBP[i].GetY() + 3);
		m_lineupSelectBPT[i].UpdateXCenter();
	}
	m_lineupSelectB.SetXY(x + 25, y + 280);
	m_lineupSelectBT.SetXCenter(m_lineupSelectB.GetCenter());
	m_lineupSelectBT.SetY(y + 283);
	m_lineupSelectBT.UpdateXCenter();
}

bool cInterfaceTeam::ShowSelectLineup(cCanvas* pCanvas)
{
	pCanvas->Add(&m_lineupSelectBack, 1, 1);
	pCanvas->Add(&m_lineupCancelB, 1);
	pCanvas->Add(&m_Describe[0]);
	pCanvas->Add(&m_Describe[1]);
	for (int i = 0; i < 5; i++)pCanvas->Add(m_lineupPeoplepp[i], 1);
	for (int i = 0; i < 5; i++)pCanvas->Add(&m_lineupPeoplepT[i]);

	for (int i = 0; i < 11; i++)
	{
		pCanvas->Add(&m_lineupSelectBP[i], 1);
		pCanvas->Add(&m_lineupSelectBPT[i]);
	}
	pCanvas->Add(&m_lineupSelectB, 1);
	pCanvas->Add(&m_lineupSelectBT);
	return true;
}

void cInterfaceTeam::SetlineupPeople(eFormation select)
{
	//图片有 52  54 的偏移
	int xPos = m_xPos + 52;
	int yPos = m_yPos - 54;
	int xOf1 = 38;
	int yOf1 = 19;
	m_Describe[0].SetString(m_lineupSelectBPT[select].GetString());
	string str;
	switch (select)
	{
	case normal:
		if (1)
		{
			str = "没有任何效果";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 4;
			m_lineupPeoplep[4].m_x = xstart;
			m_lineupPeoplep[4].m_y = ystart;
		}
		break;
	case land://地阵
		if (1)
		{
			str = "1,3,4号位物法防御+15%, 2号位物法伤害+15%, 5号位速度+10%,其它位物法伤害+10%,";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 1;

			m_lineupPeoplep[1].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;

			m_lineupPeoplep[4].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[4].m_y = ystart - yOf1 * 1;
		}
		break;
	case wind:
		if (1)
		{
			str = "1号位物法伤害+20%,  4,5号位速度+10%,其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 4;
			m_lineupPeoplep[4].m_x = xstart;
			m_lineupPeoplep[4].m_y = ystart - yOf1 * 2;
		}
		break;
	case tiger:
		if (1)
		{
			str = "1号位物法伤害+25%, 2,3号位物法防御+10%, 其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 5;
			m_lineupPeoplep[4].m_x = xstart - xOf1;
			m_lineupPeoplep[4].m_y = ystart - yOf1;
		}
		break;
	case dragon:
		if (1)
		{
			str = "1号位法术防御+20%, 2号位物理防御+20%, 3号位法术伤害+30%,速度-30% 4号位速度+15%,5号位物法伤害+20%,其它位物法伤害+10%,";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 5;
			m_lineupPeoplep[3].m_x = xstart;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[4].m_x = xstart + xOf1;
			m_lineupPeoplep[4].m_y = ystart - yOf1 * 3;
		}
		break;
	case bird:
		if (1)
		{
			str = "1-5位速度+20%其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 2;

			m_lineupPeoplep[1].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[2].m_y = ystart;

			m_lineupPeoplep[3].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 4;
			m_lineupPeoplep[4].m_x = xstart;
			m_lineupPeoplep[4].m_y = ystart;
		}
		break;
	case snake:
		if (1)
		{
			str = "1,2,3号位法术躲避率+15%, 其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 1;

			m_lineupPeoplep[3].m_x = xstart;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[4].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[4].m_y = ystart - yOf1;
		}
		break;
	case sky:
		if (1)
		{
			str = "1-5位物法伤害+20%,速度-10%,其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[0].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 4;
			m_lineupPeoplep[4].m_x = xstart;
			m_lineupPeoplep[4].m_y = ystart;
		}
		break;
	case cloud:
		if (1)
		{
			str = "1号位物法防御+40%速度-30%, 2号位物法防御+10%, 4,5号位速度+15%,其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[0].m_y = ystart;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 1;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 4;
			m_lineupPeoplep[4].m_x = xstart;
			m_lineupPeoplep[4].m_y = ystart;
		}
		break;
	case thunder:
		if (1)
		{
			str = "1,2,3号位固定伤害效果+20%, 4,5号位物法伤害+10%,其它位物法伤害+10%";
			m_Describe[1].SetString(str);
			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[0].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[0].m_y = ystart;
			m_lineupPeoplep[4].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[4].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 1;

			m_lineupPeoplep[1].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 2;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[2].m_y = ystart;
		}
		break;
	case eagle:
		if (1)
		{
			str = "1号位物法防御+10%, 2,3号位速度+15%, 4号位物法伤害+15%, 其它位物法伤害+10%";
			m_Describe[1].SetString(str);

			int xstart = xPos + 145;
			int ystart = yPos + 240;
			m_lineupPeoplep[4].m_x = xstart + xOf1 * 4;
			m_lineupPeoplep[4].m_y = ystart;
			m_lineupPeoplep[1].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[1].m_y = ystart - yOf1 * 3;
			m_lineupPeoplep[2].m_x = xstart + xOf1 * 1;
			m_lineupPeoplep[2].m_y = ystart - yOf1 * 1;


			m_lineupPeoplep[0].m_x = xstart + xOf1 * 3;
			m_lineupPeoplep[0].m_y = ystart - yOf1;
			m_lineupPeoplep[3].m_x = xstart + xOf1 * 2;
			m_lineupPeoplep[3].m_y = ystart - yOf1 * 2;
		}
		break;
	default:
		ERRBOX;
		break;
	}
	for (int i = 0; i < 5; i++)
	{
		m_lineupPeoplep[i].m_bMove = true;
		m_lineupPeoplepT[i].SetXY(m_lineupPeoplep[i].m_x + 3, m_lineupPeoplep[i].m_y + 20);
	}
	for (int i = 0; i < 2; i++)
		m_Describe[i].m_bMove = true;
	SortLineupPeople();
}

void cInterfaceTeam::SortLineupPeople()
{
	for (int i = 0; i < 5; i++)
	{
		m_lineupPeoplepp[i] = &m_lineupPeoplep[i];
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_lineupPeoplepp[i]->m_y>m_lineupPeoplepp[i + 1]->m_y)
		{
			cObjWas* p = m_lineupPeoplepp[i];
			m_lineupPeoplepp[i] = m_lineupPeoplepp[i + 1];
			m_lineupPeoplepp[i + 1] = p;
		}
	}
}


void cInterfaceTeam::SetFighterPos2(int** px, int** py, int xOf1, int yOf1, bool enemy)
{
	eFormation Formation;
	if (enemy)
		Formation = m_eEnemyFormation;
	else
		Formation = m_eOurFormation;
	xOf1 = 65;
	yOf1 = 40;
	int xstart = 340 + (g_640 - 640) - 80;
	int ystart = 390 + (g_480 - 480) + 20;
	switch (Formation)
	{
	case normal:
		if (1)
		{
			*px[0] = xstart + xOf1 * 2;
			*py[0] = ystart - yOf1 * 2;
			*px[1] = xstart + xOf1 * 3;
			*py[1] = ystart - yOf1 * 3;
			*px[2] = xstart + xOf1 * 1;
			*py[2] = ystart - yOf1 * 1;
			*px[3] = xstart + xOf1 * 4;
			*py[3] = ystart - yOf1 * 4;
			*px[4] = xstart;
			*py[4] = ystart;
		}
		break;
	case land://地阵
		if (1)
		{
			*px[0] = xstart + xOf1 * 3;
			*py[0] = ystart - yOf1;
			*px[1] = xstart + xOf1 * 2;
			*py[1] = ystart - yOf1 * 2;
			*px[2] = xstart + xOf1 * 4;
			*py[2] = ystart - yOf1 * 2;
			*px[3] = xstart + xOf1 * 2;
			*py[3] = ystart;
			*px[4] = xstart + xOf1 * 4;
			*py[4] = ystart;
		}
		break;
	case wind:
		if (1)
		{
			*px[0] = xstart + xOf1 * 3;
			*py[0] = ystart - yOf1;
			*px[1] = (*px[0]) + xOf1;
			*py[1] = (*py[0]) - yOf1;

			*px[2] = (*px[0]) - xOf1;
			*py[2] = (*py[0]) + yOf1;
			*px[3] = (*px[1]) - xOf1;
			*py[3] = (*py[1]) - yOf1;
			*px[4] = (*px[2]) - xOf1;
			*py[4] = (*py[2]) - yOf1;
		}
		break;
	case tiger:
		if (1)
		{
			*px[0] = xstart + xOf1 * 4;
			*py[0] = ystart;
			*px[1] = xstart + xOf1 * 4;
			*py[1] = ystart - yOf1 * 2;
			*px[2] = xstart + xOf1 * 2;
			*py[2] = ystart;
			*px[3] = xstart + xOf1 * 4;
			*py[3] = ystart - yOf1 * 4;
			*px[4] = xstart;
			*py[4] = ystart;
		}
		break;
	case dragon:
		if (1)
		{
			*px[0] = xstart + xOf1 * 3;
			*py[0] = ystart - yOf1;
			*px[1] = xstart + xOf1 * 4;
			*py[1] = ystart;
			*px[2] = xstart + xOf1 * 4;
			*py[2] = ystart - yOf1 * 4;
			*px[3] = xstart + xOf1;
			*py[3] = ystart - yOf1;
			*px[4] = xstart + xOf1 * 2;
			*py[4] = ystart - yOf1 * 2;
		}
		break;
	case bird:
		if (1)
		{
			*px[0] = xstart + xOf1 * 2;
			*py[0] = ystart - yOf1 * 2;
			*px[1] = xstart + xOf1 * 4;
			*py[1] = ystart - yOf1 * 2;
			*px[2] = xstart + xOf1 * 2;
			*py[2] = ystart;
			*px[3] = xstart + xOf1 * 4;
			*py[3] = ystart - yOf1 * 4;
			*px[4] = xstart;
			*py[4] = ystart;
		}
		break;
	case snake:
		if (1)
		{
			*px[0] = xstart + xOf1 * 3;
			*py[0] = ystart - yOf1;
			*px[2] = xstart + xOf1 * 4;
			*py[2] = ystart - yOf1 * 2;
			*px[1] = xstart + xOf1 * 2;
			*py[1] = ystart;
			*px[3] = xstart + xOf1;
			*py[3] = ystart - yOf1;
			*px[4] = xstart + xOf1 * 4;
			*py[4] = ystart;
		}
		break;
	case sky:
		if (1)
		{
			*px[0] = xstart + xOf1 * 3;
			*py[0] = ystart - yOf1 * 1;
			*px[1] = xstart + xOf1 * 3;
			*py[1] = ystart - yOf1 * 3;
			*px[2] = xstart + xOf1 * 1;
			*py[2] = ystart - yOf1 * 1;
			*px[3] = xstart + xOf1 * 4;
			*py[3] = ystart - yOf1 * 4;
			*px[4] = xstart;
			*py[4] = ystart;
		}
		break;
	case cloud:
		if (1)
		{
			*px[0] = xstart + xOf1 * 4;
			*py[0] = ystart;
			*px[1] = xstart + xOf1 * 3;
			*py[1] = ystart - yOf1 * 3;
			*px[2] = xstart + xOf1 * 1;
			*py[2] = ystart - yOf1 * 1;
			*px[3] = xstart + xOf1 * 4;
			*py[3] = ystart - yOf1 * 4;
			*px[4] = xstart;
			*py[4] = ystart;
		}
		break;
	case thunder:
		if (1)
		{
			*px[0] = xstart + xOf1 * 4;
			*py[0] = ystart;
			*px[4] = xstart + xOf1 * 3;
			*py[4] = ystart - yOf1 * 3;
			*px[3] = xstart + xOf1 * 1;
			*py[3] = ystart - yOf1 * 1;
			*px[1] = xstart + xOf1 * 4;
			*py[1] = ystart - yOf1 * 2;
			*px[2] = xstart + xOf1 * 2;
			*py[2] = ystart;
		}
		break;
	case eagle:
		if (1)
		{
			*px[4] = xstart + xOf1 * 4;
			*py[4] = ystart;
			*px[1] = xstart + xOf1 * 3;
			*py[1] = ystart - yOf1 * 3;
			*px[2] = xstart + xOf1 * 1;
			*py[2] = ystart - yOf1 * 1;
			*px[0] = xstart + xOf1 * 3;
			*py[0] = ystart - yOf1;
			*px[3] = xstart + xOf1 * 2;
			*py[3] = ystart - yOf1 * 2;
		}
		break;
	default:
		ERRBOX;
		break;
	}

	*px[5] = xstart + xOf1;
	*py[5] = ystart - yOf1 * 3;
	*px[6] = xstart + xOf1 * 2;
	*py[6] = ystart - yOf1 * 4;
	*px[7] = xstart;
	*py[7] = ystart - yOf1 * 2;
	*px[8] = xstart + xOf1 * 3;
	*py[8] = ystart - yOf1 * 5;
	*px[9] = xstart - xOf1;
	*py[9] = ystart - yOf1;
// 	if (enemy)
// 	{
// 		for (int i = 5; i < 10; i++)
// 		{
// 			*px[i] -= 10;
// 		}
// 	}
// 	else
// 	{
// 		for (int i = 5; i < 10; i++)
// 		{
// 			*py[i] -= 10;
// 		}
// 	}
	if (enemy)
	{
		for (int i = 0; i < 10; i++)
		{
			*px[i] = g_640 - *px[i];
			*py[i] = g_480 - *py[i] + 90;
		}

	}
	UpdatePos();
}

void cInterfaceTeam::SetFighterPos(bool enemy /*= true*/)
{
	int* px[10];
	int* py[10];
	for (int i = 0; i < 10; i++)
	{
		px[i] = &m_xPosList[i + enemy * 10];
		py[i] = &m_yPosList[i + enemy * 10];
	}
	SetFighterPos2(px, py, 0, 0, enemy);
}


void cInterfaceTeam::SetupOneFormationEffect(int Pos, cPropertyData* pPetData, bool UporDown)
{
	if (!pPetData)return;
	//Pos = m_TeamTurn[Pos];//
	int setup;
	if (UporDown)
		setup = 1;
	else  setup = -1;
	eFormation formation;
	if (Pos<10)
	{
		formation = m_eOurFormation;
	}
	else
	{
		formation = m_eEnemyFormation;
	}
	Pos %= 10;
	if (Pos>4)
	{
		pPetData->DmgPercentOfMagic.d1 += 10 * setup;
		pPetData->DmgPercent.d1 += 10 * setup;
		return;
	}
	switch (formation)
	{
	case normal:
		return;
	case land:
		// 1 3 4 位 物法防御提升15%
		switch (Pos)
		{
		case 0:
		case 2:
		case 3:
			pPetData->DmgPercentOfMagic.d2 += 15 * setup;
			pPetData->DmgPercent.d2 += 15 * setup;
			break;
		case 1://2号位物法伤害提升
			pPetData->DmgPercentOfMagic.d1 += 15 * setup;
			pPetData->DmgPercent.d1 += 15 * setup;
			break;
		case 4://5号位加10%速
			pPetData->Speed.AddDataAddPercent(10 * setup);
			break;
		}
		return;
	case wind:
		switch (Pos)
		{
		case 0:
			pPetData->DmgPercentOfMagic.d1 += 20 * setup;
			pPetData->DmgPercent.d1 += 20 * setup;
			break;
		case 1:
		case 2:
			pPetData->DmgPercentOfMagic.d1 += 10 * setup;
			pPetData->DmgPercent.d1 += 10 * setup;
			break;
		case 3://
		case 4://4,5号位加10%速
			pPetData->Speed.AddDataAddPercent(10 * setup);
			break;
		}
		return;
	case tiger:
		switch (Pos)
		{
		case 0:  //1 加25 伤
			pPetData->DmgPercentOfMagic.d1 += 25 * setup;
			pPetData->DmgPercent.d1 += 25 * setup;
			break;
		case 1:   //2 3位加10%防
		case 2:
			pPetData->DmgPercentOfMagic.d2 += 10 * setup;
			pPetData->DmgPercent.d2 += 10 * setup;
			break;
		case 3://
		case 4://4,5号位加10伤
			pPetData->DmgPercentOfMagic.d1 += 10 * setup;
			pPetData->DmgPercent.d1 += 10 * setup;
			break;
		}
		return;
	case dragon:
		switch (Pos)
		{
		case 0:  //1号位 加20法防
			pPetData->DmgPercentOfMagic.d2 += 20 * setup;
			break;
		case 1:   //2号位 加10物防
			pPetData->DmgPercent.d2 += 10 * setup;
			break;
		case 2: //3号位  加30法伤
			pPetData->DmgPercentOfMagic.d1 += 30 * setup;
			break;
		case 3://4号加15 速
			pPetData->Speed.AddDataAddPercent(15 * setup);
			break;
		case 4://5号位加20伤
			pPetData->DmgPercentOfMagic.d1 += 20 * setup;
			pPetData->DmgPercent.d1 += 20 * setup;;
			break;
		}
		return;
	case bird:
		pPetData->Speed.AddDataAddPercent(20 * setup);
		return;
	case snake:
		switch (Pos)
		{
		case 0:  //1-3号位 加15 法术躲避
		case 1:
		case 2:
			pPetData->DmgPercentOfMagic.d2 += 10 * setup;
			pPetData->HitRateOfMagic.d2 += 15 * setup;
			break;
		case 3://
		case 4://4,5号位加10伤
			pPetData->DmgPercentOfMagic.d1 += 10 * setup;
			pPetData->DmgPercent.d1 += 10 * setup;
			break;
		}
		return;
	case sky: // 1-5加 20伤害,减10%速
		pPetData->DmgPercentOfMagic.d1 += 20 * setup;
		pPetData->DmgPercent.d1 += 20 * setup;
		pPetData->Speed.AddDataAddPercent(-10 * setup);
		return;
	case cloud:
		switch (Pos)
		{
		case 0:  //1号位 加40防
			pPetData->DmgPercent.d2 += 40 * setup;
			pPetData->DmgPercentOfMagic.d2 += 40 * setup;
			pPetData->Speed.AddDataAddPercent(-30 * setup);
			break;
		case 1:   //2号位 加10防
			pPetData->DmgPercent.d2 += 10 * setup;
			pPetData->DmgPercentOfMagic.d2 += 10 * setup;
			break;
		case 2: //3号位  加10伤
			pPetData->DmgPercentOfMagic.d1 += 10 * setup;
			pPetData->DmgPercent.d1 += 10 * setup;
			break;
		case 3://4,5号加15 速
		case 4://
			pPetData->Speed.AddDataAddPercent(15 * setup);
			break;
		}
		return;
	case thunder:
		switch (Pos)
		{
		case 0:  //1号位 
		case 1:   //2号位
		case 2: //3号位  加20%固定伤害
			pPetData->DmgPercentOfFix.d1 += 20 * setup;
			break;
		default:
			pPetData->DmgPercentOfMagic.d1 += 10 * setup;
			pPetData->DmgPercent.d1 += 10 * setup;
			break;
		}
		return;
	case eagle:
		switch (Pos)
		{
		case 0:  //1号位 加10物防
			pPetData->DmgPercent.d2 += 10 * setup;
			pPetData->DmgPercentOfMagic.d2 += 10 * setup;
			break;
		case 1:   //2 3号位 加15速
		case 2:
			pPetData->Speed.AddDataAddPercent(15 * setup);
			break;
		case 3://4号加15 伤
			pPetData->DmgPercentOfMagic.d1 += 15 * setup;
			pPetData->DmgPercent.d1 += 15 * setup;
			break;
		case 4://5号加10 伤
			pPetData->DmgPercentOfMagic.d1 += 10 * setup;
			pPetData->DmgPercent.d1 += 10 * setup;
			break;
		}
		return;
	default:
		ERRBOX;
		return;
	}
}



void cInterfaceTeam::SwapTeamTurn(int id1, int id2)
{
	swap(m_TeamTurn[id1], m_TeamTurn[id2]);
	swap(m_TeamTurn[id1 + 5], m_TeamTurn[id2 + 5]);
	UpdatePos();
}

void cInterfaceTeam::OnOff(bool NeedShow)
{
	if (NeedShow)g_pMainState->ClearInterfaceSetShow();
	g_pMainState->InterfaceSetShow(this, NeedShow);

	if (NeedShow)
	{
		Init();
// 		vector<int> ids = { g_pMainState->m_HeroID };
// 		vector<int> id2s;
// 		for (int i = 0; i < 5; ++i)
// 		{
// 			if (i == g_pMainState->m_HeroID)
// 			{
// 				continue;
// 			}
// 			if (!g_pMainState->m_FightWorkList[i].isExist)
// 			{
// 				id2s.push_back(i);
// 				continue;
// 			}
// 			ids.push_back(i);
// 		}
// 
// 		forv(ids, i)
// 		{
// 			m_TeamTurn[i] = ids[i];
// 			m_TeamTurn[i + 5] = ids[i] + 5;
// 		}
// 		forv(id2s, i)
// 		{
// 			m_TeamTurn[i + ids.size()] = id2s[i];
// 			m_TeamTurn[i + ids.size() + 5] = id2s[i] + 5;
// 		}
		UpDate();
	}
	else
	{
		cct::autoSave();
	}
	forr(_accs, i)
	{
		_accs[i].m_NeedShow = NeedShow;
	}

	g_pMainState->m_Canvas.SetRedraw(m_Back.GetPicRange());
}

bool cInterfaceTeam::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	case 1:
		m_bLiineupSelect = false;
		break;
	default:
		break;
	}
	return true;
}

void cInterfaceTeam::SetFormation(eFormation format, bool enemy /*= false*/, bool bUpdate)
{
	if (enemy)
	{
		m_eEnemyFormation = format;
	}
	else
	{
		m_eOurFormation = format;
	}
	SetFighterPos(enemy);
	m_bLiineupSelect = false;
	if (bUpdate)
	{
		m_lineupName.SetString(m_lineupSelectBPT[m_eOurFormation].GetString());
	}
}

ulong cInterfaceTeam::GetSmallHead(int id)
{
	return g_pMainState->m_FightWorkList[m_TeamTurn[id]].m_pObj->GetID(POS_SMALLHEAD);
}
ulong cInterfaceTeam::GetPetHead(int id)
{
	return g_pMainState->m_FightWorkList[m_TeamTurn[id + 5]].m_pObj->GetID(POS_BIGHEAD);
}

void cInterfaceTeam::UpdatePos()
{
	for (int i = 0; i < 20; i++)
	{
		g_pMainState->m_pFightState->m_战斗坐标xs[i] = g_pMainState->m_InterfaceTeam.GetXPos(i);
		g_pMainState->m_pFightState->m_战斗坐标ys[i] = g_pMainState->m_InterfaceTeam.GetYPos(i);
	}
}

void cInterfaceTeam::Save(ofstream& File)
{
	File << m_eOurFormation << g_strSpace;
	File << m_eEnemyFormation << g_strSpace;
	for (int i = 0; i < 20; i++)
	{
		File << m_TeamTurn[i] << g_strSpace;
	}
//	File << m_LeaveBegin << g_strSpace;
}

void cInterfaceTeam::Load(ifstream& File)
{
	int k;
	File >> k;
	g_pMainState->m_InterfaceTeam.SetFormation((eFormation)k, false, true);
	File >> k;
	g_pMainState->m_InterfaceTeam.SetFormation((eFormation)k, true, true);
	for (int i = 0; i < 20; i++)
	{
		File >> m_TeamTurn[i];
	}
//	File >> m_LeaveBegin;
	UpdatePos();
}

int cInterfaceTeam::GetXPos(int id)
{
	return m_xPosList[GetReTramTrun(id)];
}

int cInterfaceTeam::GetYPos(int id)
{
	return m_yPosList[GetReTramTrun(id)];
}

cInterfaceTeam::~cInterfaceTeam()
{
	for (int i = 0; i < 5; i++)
	{
		FreeFighter(i);

	}
}

void cInterfaceTeam::FreeFighter(int id)
{
	m_Fighter[id].m_pIndex = 0;
	m_Fighter[id].m_IndexType = 0;
	m_Fighter[id].Free();
}

int cInterfaceTeam::GetReTramTrun(int id)
{
	for (int i = 0; i < 20; i++)
	{
		if (m_TeamTurn[i] == id)
		{
			return i;
		}
	}
	return -1;
}

bool cInterfaceTeam::AutoSwap(int k)
{
	int start, end;
	if (k < 10)start = 0;
	else start = 10;
	end = start + 5;
	for (int i = k + 1; i < end; i++)
	{
		if (!g_pMainState->m_FightWorkList[GetTeamTurn(i)].isExist)
			continue;
		SwapTeamTurn(k, i);
		return true;
	}
	return false;
}

int cInterfaceTeam::getLeaveBegin()
{
	int charactID = 0;
	for (; charactID < 5; ++charactID)
	{
		const auto& list = g_pMainState->m_FightWorkList[charactID];
		if (!list.isExist)
		{
			break;
		}
	}
	return charactID;
}

void cInterfaceTeam::update(bool setChar, int m_LeaveBegin)
{
	const auto& os = g_pMainState->m_Friend._friends;
	auto& list = g_pMainState->m_FightWorkList;
	for (int i = 0; i < os.size(); ++i)
	{
		list[i].m_SkillPreSelect.SkillID = os[i].pre;
		list[i + 5].m_SkillPreSelect.SkillID = os[i].prebb;
		list[i].m_FriendListid = os[i].dski;
		g_pMainState->m_pFightState->m_FightMenu.SetControl(i, os[i].ctrl);
		g_pMainState->m_pFightState->m_FightMenu.SetControl(i + 5, os[i].ctrl);
		cObj* obj = list[i].m_pObj = os[i].obj;
		if (i < m_LeaveBegin)
		{
			list[i].isExist = true;
			obj->SetShow(true);
			obj->m_IndexType = INDEXTYEP_CHARACTER;
			auto pc = obj->getPcData();
			obj->m_IDInFightlist = pc->m_IDinFightWorkList = i;
			
			int pid = pc->m_FightPetID;
			if (pid < 0)
			{
				list[i + 5].isExist = false;
				continue;
			}
			g_pMainState->SetFightPet(i, -1);
		//	if (pid >= 0)
			{
				list[i + 5].m_pObj->m_IndexType = INDEXTYEP_PET;
			}
			for (int k = 0; k < pc->m_NumofBB; ++k)
			{
				pc->m_pPets[k]->m_PetData.m_IDinFightWorkList = i + 5;
				if (k != pid)
				{
					g_pMainState->SetFightPet(i, k);
				}
			}
			g_pMainState->SetFightPet(i, pid);
		}
		else
		{
			list[i].isExist = false;
			list[i + 5].isExist = false;
			obj->SetShow(false);

			obj->m_IndexType = 0;
			list[i + 5].m_pObj->m_IndexType = 0;
		}
	}
	if (setChar)
	{
		int x = g_pHeroObj->GetX();
		int y = g_pHeroObj->GetY();
		g_pMainState->SetCharacter(0/*m_TeamTurn[0]*/);
		g_pHeroObj->SetXY(x, y);
		g_pHeroObj->Stand();
	}
	g_pMainState->FindObj();
}

