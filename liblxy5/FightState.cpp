#include "_global.h"


unsigned int WINAPI cFightState::ThreadProc(_In_ LPVOID lpParameter)
{
	cFightState*  pFightState = (cFightState*)lpParameter;
	for (;;)
	{
		pFightState->m_ThreadSleep = false;
		for (int i = 0; i < 5; i++)
		{
			if (pFightState->m_IDtoLoad[i])
			{
				pFightState->m_pFileToLoad[i]->Load(pFightState->m_IDtoLoad[i]);
				pFightState->m_IDtoLoad[i] = 0;
			}
		}
		pFightState->m_ThreadSleep = true;
		ccc_log("动态加载完成");
		//加载完就睡觉
		SuspendThread(pFightState->m_hThread);
	}
}


bool cFightState::Init(void* pData)
{
	if (isInit)
	{
		return true;
	}

	//创建线程
	if (!m_hThread)
	{
		m_MiaoShu.SetXCenter(g_half320);
		m_MiaoShu.SetY(g_480 - 80);
		m_MiaoShu.SetColor(RGB(255, 255, 255));
		for (int i = 0; i < 10; i++)
		{
			m_HiddenWeaponsp[i].Set(&m_HiddenWeapons);
			m_HiddenWeaponsp[i].m_NeedShow = false;
		}
		m_FightBack1.Load(0xE3B87E0F);
		//我用的图片是800*600的,但显示的是640*480的
		m_FightBack1.SetxOffset2((800 - g_640) / 2);
		m_FightBack1.SetyOffset2((600 - g_480) / 2);
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, CREATE_SUSPENDED, NULL);
		//CreateThread(0, 0, ThreadProc, this, CREATE_SUSPENDED, 0);

		m_FightMenu.Init();
		m_pFightBack = new uchar[800 * 600 * 2];

		for (int i = 0; i < 20; i++)
		{
			m_pFightWorkList[i] = &g_pMainState->m_FightWorkList[i];
//			m_pList[i]->_myTurn = 0;
		}
	}
	_magicCri.Load(0xDAD8AC20);
	isInit = true;
	m_bEscape = false;
	m_CurrIDPerTurn = 0;
	g_pMainState->m_Cursor.m_FollowMode = false;
	g_pMainState->m_PCHead.MoveTeamHead(1);
	if (g_pMainState->m_pNowSelect)
	{
		g_pMainState->m_pNowSelect->SetShine(false);
		g_pMainState->m_pNowSelect = 0;
	}

	_leaveBegin = 0;
	int leaveBegin = 0;
	for (int i = 0; i < 5; ++i)
	{
		const auto& list = g_pMainState->m_FightWorkList[i];
		if (!list.isExist)
		{
			continue;
		}
		++leaveBegin;
		if (list.m_pObj->getPropertyData()->_isOurTeamTemp)
		{
			continue;
		}
		++_leaveBegin;
	}

	if (leaveBegin == _leaveBegin)
	{
		if (_leaveBegin < 3)
		{
			g_pMainState->m_InterfaceTeam.SetFormation(normal, 0, true);
		}
	}
// 	else
// 	{
// 		//检测是否有5人
// 		for (int i = 0; i < 5; i++)
// 		{
// 			if (!g_pMainState->m_FightWorkList[i].isExist)
// 			{
// 				g_pMainState->m_InterfaceTeam.SetFormation(normal, 0, true);
// 				break;
// 			}
// 		}
// 	}


// 	for (int i = 0; i < 5; i++)
// 	{
// 		if (m_pFightWorkList[i]->isExist)
// 		{
// 			int tid = g_pMainState->m_InterfaceTeam.GetReTramTrun(i);
// 			if (tid >= g_pMainState->m_InterfaceTeam.m_LeaveBegin)
// 			{
// 				m_pFightWorkList[i]->isExist = false;
// 				m_pFightWorkList[i + 5]->isExist = false;
// 			}
// 		}
// 	}

	// 	if (g_pMainState->m_GlobalButton[0] == 100)
	// 	{
	// 		g_pMainState->m_AI.m_bPKMode = true;
	// 	}
	// 	else g_pMainState->m_AI.m_bPKMode = false;
	for (int i = 0; i < 20; i++)
	{
		// 		if (i == 0 || i == 10)
		// 		{
		// 			cPetData *data = nullptr;
		// 			g_pMainState->m_FightList[i].m_pData->GetDateP(data);
		// 			
		// 			if (data)
		// 			{
		// 				auto pc = (cPCData*)data;
		//  				auto w2 = pc->m_pWeaponData2;
		// 				if (w2)
		// 				{
		// 					int k = 0;
		// 				}
		// 			}
		// 		}

		m_SpeedListPos[i] = i;
		PrePareToFight(i);
	}
	SortBySpeed();

	for (int i = 0; i < 5; i++)
	{
		m_IDtoLoad[i] = 0;
	}

	//更新背景

	if (1)
	{
		const cMap* m = g_pMainState->m_Map.m_pMap;
		int cx = m->m_xCenter - g_half320;
		int cy = m->m_yCenter - g_half240;
		int bx, by, idx, ix, iy;
		uchar* pf, *pb;
		for (int k = 0; k < 600; ++k)
		{
			by = (cy + k) / 240;
			iy = (cy + k) % 240;
			for (int i = 0; i < 800; ++i)
			{
				bx = (cx + i) / 320;
				ix = (cx + i) % 320;
				idx = by * m->m_WidthNum + bx;
				if (idx < 0 || idx >= m->m_NumBlock)
				{
					continue;
				}
				pf = &m_pFightBack[(k * 800 + i) * 2];
				pb = &g_pMainState->m_Map.m_pMap->m_pBitmap[idx][(iy * 320 + ix) * 2];
				memcpy(pf, pb, 2);
			}
		}
	}

// 	int xOf1 = g_pMainState->m_Map.m_pMap->m_xCenterOffset;
// 	int yOf1 = g_pMainState->m_Map.m_pMap->m_yCenterOffset;
// 	int i1 = xOf1 <= 80 ? 2 : 1;
// 	int j1 = yOf1 <= 48 ? 2 : 1;
// 	for (int i = 0; i < 4; i++)
// 	{
// 		for (int j = 0; j < 4; j++)
// 		{
// 			////////////////////////////////////////////////////////////////////////// 呵呵哒 战斗图块
// 			int xstart;
// 			int ystart;
// 			int xOf;
// 			int yOf;
// 			int W;
// 			int H;
// 			switch (i)
// 			{
// 			case 0:
// 				xOf = 0;
// 				xstart = (i1 == 2) ? (240 + xOf1) : (xOf1 - 80);
// 				W = 320 - xstart;
// 				break;
// 			case 1:
// 				xOf = (i1 == 2) ? (80 - xOf1) : (400 - xOf1);
// 				xstart = 0;
// 				W = 320;
// 				break;
// 			case 2:
// 				xOf = (i1 == 2) ? (80 - xOf1) : (400 - xOf1);
// 				xOf += 320;
// 				xstart = 0;
// 				W = (i1 == 2) ? (320) : (80 + xOf1);
// 				break;
// 			default:
// 				if (i == 3 && i1 == 1)
// 				{
// 					continue;
// 				}
// 				xOf = 720 - xOf1;
// 				xstart = 0;
// 				W = 80 - xOf1;
// 				break;
// 			}
// 			switch (j)
// 			{
// 			case 0:
// 				yOf = 0;
// 				ystart = (j1 == 2) ? (192 + yOf1) : (yOf1 - 48);
// 				H = 240 - ystart;
// 				break;
// 			case 1:
// 				yOf = (j1 == 2) ? (48 - yOf1) : (288 - yOf1);
// 				ystart = 0;
// 				H = 240;
// 				break;
// 			case 2:
// 				yOf = (j1 == 2) ? (48 - yOf1) : (288 - yOf1);
// 				yOf += 240;
// 				ystart = 0;
// 				H = (j1 == 2) ? (240) : (48 + yOf1);
// 				break;
// 			default:
// 				if (j == 3 && j1 == 1)
// 				{
// 					continue;
// 				}
// 				yOf = 528 - yOf1;
// 				ystart = 0;
// 				H = 48 - yOf1;
// 				break;
// 			}
// 
// 			int k = g_pMainState->m_Map.m_pMap->m_NowMapNum + (i - i1) + (j - j1) *g_pMainState->m_Map.m_pMap->m_WidthNum;
// 			if (k < 0)continue;
// 			if (k >= g_pMainState->m_Map.m_pMap->m_NumBlock)continue;
// 			////////////////////////////////////////////////////////////////////////// 呵呵哒 战斗底图
// 			uchar* P1 = &m_pFightBack[(xOf + yOf * 800) << 1];
// 			uchar* P2 = &g_pMainState->m_Map.m_pMap->m_pBitmap[k][((xstart)+(ystart)* 320) << 1];
// 			int w2 = W << 1;
// 			for (int y = 0; y < H; y++)
// 			{
// 				memcpy_s(P1, w2, P2, w2);
// 				P1 += 800 * 2;
// 				P2 += 320 * 2;
// 			}
// 		}
// 	}


	int index, index1, index2;
	WPixel pix1, pix2;
	uchar* lpSrc = m_FightBack1.m_Picture.Spr.lpDate[0];

	int index11 = (m_FightBack1.m_Picture.m_yOffset2) * 800 + m_FightBack1.m_Picture.m_xOffset2;
	index1 = index11;
	index = index1 << 1;
	index2 = 0;
	for (int i = 0; i < g_480; i++)
	{
		for (int j = 0; j < g_640; j++)
		{
			pix1.l = lpSrc[index];
			pix1.h = lpSrc[index + 1];
			pix2.l = m_pFightBack[index2];
			pix2.h = m_pFightBack[index2 + 1];

			pix2.red = (pix1.red + pix2.red) >> 1;
			pix2.green = (pix1.green + pix2.green) >> 1;
			pix2.blue = (pix1.blue + pix2.blue) >> 1;
			m_pFightBack[index2] = pix2.l;
			m_pFightBack[index2 + 1] = pix2.h;


			index1 += 1;
			index += 2;
			index2 += 2;
		}
		index11 += 800;
		index1 = index11;
		index = index11 << 1;
	}


	for (int i = 0; i < g_pMainState->m_Canvas.m_CanvasCube.size(); i++)
	{
		if (!g_pMainState->m_Canvas.m_CanvasCube[i].m_bCover已覆盖数据)
			g_pMainState->m_Canvas.m_CanvasCube[i].PicNumOfPreFrame = -1;
	}
	m_ThreadSleep = true;

	m_Frame.SetXY(200, 200);
	m_Frame.SetColor(RGB(200, 0, 0));
	g_pMainState->m_Map.m_pMap->m_bMove = false;

	m_turn = 0;


	bool isAuto = m_FightMenu._isAutoBattle = !m_FightMenu.CheckControl(); //m_FightMenu._isAutoBattle = false;
// 	int c = 0;
// 	for (int i = 0; i < g_pMainState->m_InterfaceTeam.getLeaveBegin()/*m_LeaveBegin*/; ++i)
// 	{
// 		if (!m_FightMenu.CheckTurn(g_pMainState->m_InterfaceTeam.GetTeamTurn(i)))
// 		{
// 			++c;
// 		}
// 	}
// 	if (c == g_pMainState->m_InterfaceTeam.getLeaveBegin()/*m_LeaveBegin*/)
// 	{
// 		isAuto = true;
// 	}


	m_FightMenu._autoBack.m_NeedShow = isAuto;
	m_FightMenu._autoBtn.m_NeedShow = isAuto;
	m_FightMenu._tAutoBtn.m_NeedShow = isAuto;
	m_FightMenu._tAutoTurn.m_NeedShow = isAuto;

// 	if (m_FightMenu._isAutoBattle)
// 	{
// 		m_FightMenu._timeWaiting = 0;
// 	}


	g_pMainState->m_TriggerFightStart.Process();
	g_pMainState->m_Accelator.init2();
	return true;
}


bool cFightState::Frame(void* pData/*=0*/)
{
	if (!isInit)Init();
	g_pMainState->SetMouseOnMap(true);
	g_pMainState->UpDateInput();
	g_pMainState->ProcessInterface();
	if (g_StateType != STATE_FIGHT)return true;
	ccm::get()->initControl();
	DoWork();
	if (g_StateType != STATE_FIGHT)return true;

	//逃跑
	if (m_bEscape)
	{
		EscapeFight();
		return true;
	}
	//显示角色
	SortShow();

	for (int i = 0; i < m_ShowTurnUseNum; i++)
	{
		switch (m_ShowTurnType[i])
		{
		case 1:

		{
			sFightWork* pShowList = (sFightWork*)m_pShowTurn[i];
			cObj* pObj = pShowList->m_pObj;
			g_pMainState->m_Canvas.Add(pShowList->m_pObj->GetShadow(), 1);
			pShowList->ShowOnScreen(&g_pMainState->m_Canvas);
			if (pObj->m_IDInFightlist < 10 ||
				(pObj->m_IDInFightlist >= 10 && g_GlobalValues[8]/*cct::get()->isShowBloodBar*/))
			{
				//显示血条
//				if ((0 == pShowList->m_work.size()) && (pShowList->m_pData->m_NowPos == POS_FIGHT_STAND))
				if (!pShowList->CheckDie())
				{
					g_pMainState->m_Canvas.Add(&pObj->m_HpEmptyLinep, 1);
					g_pMainState->m_Canvas.Add(&pObj->m_HpLinep, 1);
				}
			}
		}
			break;
		case 2:

		{
			cObjWas* pWfilep = (cObjWas*)m_pShowTurn[i];
			g_pMainState->m_Canvas.Add(pWfilep, 1);
		}
			break;
		}

	}
	for (int i = 0; i < 3; i++)
	{
		if (m_FullSkill.m_FullSkilUP[i].m_NeedShow)
		{
			g_pMainState->m_Canvas.Add(&m_FullSkill.m_FullSkilUP[i], 1);
			if (m_FullSkill.m_FullSkilUP[i].GetMaxFrame()>1)
				if (m_FullSkill.m_FullSkilUP[i].GetNowFrame() == m_FullSkill.m_FullSkilUP[i].GetMaxFrame() - 1)
				{
				m_FullSkill.m_FullSkilUP[i].SetFrame(0);
				m_FullSkill.m_FullSkilUP[i].m_NeedShow = false;
				}
		}
	}
	//显示伤害
	for (int i = 0; i < 20; i++)
	{
		if (m_pFightWorkList[i]->isExist)
		{
			m_pFightWorkList[i]->m_pObj->showMagicCri(&g_pMainState->m_Canvas);
			if (m_pFightWorkList[i]->m_DamageTime[0] < 71)
				m_pFightWorkList[i]->ShowDamage(g_pMainState);
		}
	}
	if (m_MiaoShu.m_NeedShow)
		m_MiaoShu.Show(&g_pMainState->m_Canvas);
	g_pMainState->ShowInterface();
//	if (m_FightMenu.m_NeedShow)
	m_FightMenu.Show(&g_pMainState->m_Canvas);
	g_pMainState->ShowInterface2();


	g_pMainState->m_Canvas.Show();
	g_pMainState->m_Mp3.CheckEnd();
	return true;
}



bool cFightState::Free()
{
	SAFE_DELETE_ARRAY(m_pFightBack);
	return true;
}

bool cFightState::ProcessInput()
{
	g_pMainState->ProcessInterface();

	return true;
}



int cFightState::GetSelect(long x, long y)
{
	for (int i = 0; i < 20; i++)
	{
		if (m_pFightWorkList[i]->isExist)
		{
			if (m_pFightWorkList[i]->m_pObj->m_pShowData[0]->isSelectOn(x, y))
				return i;
			if (m_pFightWorkList[i]->m_pObj->m_pShowData[1]->m_NowID)
				if (m_pFightWorkList[i]->m_pObj->m_pShowData[1]->isSelectOn(x, y))
					return i;
			if (m_pFightWorkList[i]->m_pObj->m_pShowData[2]->m_NowID)
				if (m_pFightWorkList[i]->m_pObj->m_pShowData[2]->isSelectOn(x, y))
					return i;
		}
	}

	return -1;
}



bool cFightState::Guard(int ID, int xTarget, int yTarget)
{
	//	sFightList* pFigh = m_pList[ID];
	float Speed = 30.0f;
	int x = m_pFightWorkList[ID]->m_pObj->GetX();
	int y = m_pFightWorkList[ID]->m_pObj->GetY();
	if (x == xTarget&&y == yTarget)return true;
	//得到正确的目标位置
	//int direction1 = GetDirection4(x, y, xTarget, yTarget);
	if (x != xTarget&&y != yTarget)
	{
		m_pFightWorkList[ID]->m_pObj->SetDirection(GetDirection4(x, y, (int)xTarget, (int)yTarget));
	}
	if (abs(x - xTarget) < 20 && abs(y - yTarget) < 20)
	{
		m_pFightWorkList[ID]->m_pObj->SetPos(xTarget, yTarget);
		m_pFightWorkList[ID]->m_pObj->MoveHpLine();
		m_pFightWorkList[ID]->m_pObj->MoveDialog();
		return true;
	}
	float radian = atan2(
		(float)(yTarget - y),
		(float)(xTarget - x)
		);
	float yOffset = Speed * sin(radian);
	float xOffset = Speed * cos(radian);
	m_pFightWorkList[ID]->m_pObj->SetPos(x + xOffset, y + yOffset);
	m_pFightWorkList[ID]->m_pObj->MoveHpLine();
	m_pFightWorkList[ID]->m_pObj->MoveDialog();
	return false;
}


bool cFightState::Approach(int ID, int TargetID, bool gap /* = false */, float Speed /* = 15.0f */)
{
	int xTarget = m_pFightWorkList[TargetID]->m_pObj->GetX();
	int yTarget = m_pFightWorkList[TargetID]->m_pObj->GetY();
	m_pFightWorkList[ID]->m_pObj->Set(POS_RUN);
	m_pFightWorkList[ID]->m_pObj->SetStatic(false);
//	sFightList* pFigh = m_pList[ID];
	const sFightPoint* pOffse = m_pFightWorkList[ID]->GetFightPoint();
	int xDistance = pOffse->m_xOff;
	int yDistace = pOffse->m_yOff;
	if (gap)
	{
		xDistance = 0;
		yDistace = 0;
	}
//	float Speed = 15.0f;
	int x = m_pFightWorkList[ID]->m_pObj->GetX();
	int y = m_pFightWorkList[ID]->m_pObj->GetY();
	if (x == xTarget&&y == yTarget)
	{
		return true;
	}
	int xTargetold = (int)xTarget;
	int yTargetold = (int)yTarget;

	//得到正确的目标位置
	int direction1 = GetDirection4(x, y, xTargetold, yTargetold);

	if (xDistance || yDistace)
	{
		switch (direction1)
		{
		case 9:
			xTarget -= xDistance;
			yTarget += yDistace;
			break;
		case 7:
			xTarget += xDistance;
			yTarget += yDistace;
			break;
		case 3:
			xTarget -= xDistance;
			yTarget -= yDistace;
			break;
		case 1:
			xTarget += xDistance;
			yTarget -= yDistace;
			break;
		}
	}
	//确定方向
	int  direction2;
	if (x != xTarget&&y != yTarget)
		direction2 = GetDirection4(x, y, (int)xTarget, (int)yTarget);
	else   direction2 = m_pFightWorkList[ID]->m_pObj->GetDirection();
	if (direction2 != m_pFightWorkList[ID]->m_pObj->GetDirection())
	{
		m_pFightWorkList[ID]->m_pObj->SetDirection(direction2);
	}
	int k = (x - xTarget)*(x - xTarget) + (y - yTarget)*(y - yTarget);
	if (k <= Speed*Speed)  //如果离目标只差一点点
	{
		m_pFightWorkList[ID]->m_pObj->Set(POS_RUN);
		m_pFightWorkList[ID]->m_pObj->SetPos(xTarget, yTarget);
		m_pFightWorkList[ID]->m_pObj->SetDirection(GetDirection4(x, y, xTargetold, yTargetold));
		m_pFightWorkList[ID]->m_pObj->Move2();
		return  true;
	}
	float radian = atan2(
		(float)(yTarget - y),
		(float)(xTarget - x)
		);
	float yOffset = Speed * sin(radian);
	float xOffset = Speed * cos(radian);

	m_pFightWorkList[ID]->m_pObj->Set(POS_RUN);
	m_pFightWorkList[ID]->m_pObj->SetPos(x + xOffset, y + yOffset);
	m_pFightWorkList[ID]->m_pObj->Move2();
	return false;
}


void cFightState::SortShow()
{
	m_ShowTurnUseNum = 0;
	int yList[30];
	int xoffsetList[30];
	int dustbin;
	void* pdustbin;

	for (int i = 0; i < 20; i++)
	{
		if (m_pFightWorkList[i]->isExist == true)
		{
			m_pShowTurn[m_ShowTurnUseNum] = m_pFightWorkList[i];
			m_ShowTurnType[m_ShowTurnUseNum] = 1;
			yList[m_ShowTurnUseNum] = m_pFightWorkList[i]->m_pObj->GetShadow()->m_y;// -m_pList[i]->m_pData->GetShadow()->m_x / 3;
			xoffsetList[m_ShowTurnUseNum] = m_pFightWorkList[i]->m_pObj->GetShadow()->m_x;
			m_ShowTurnUseNum += 1;

		}
	}
	//暗器
	for (int i = 0; i < m_HiddenWeaponsUseNum; i++)
	{
		m_pShowTurn[m_ShowTurnUseNum] = &m_HiddenWeaponsp[i];
		yList[m_ShowTurnUseNum] = m_HiddenWeaponsp[i].m_y;// -m_HiddenWeaponsp[i].m_x / 3;
		xoffsetList[m_ShowTurnUseNum] = m_HiddenWeaponsp[i].m_x;
		m_ShowTurnType[m_ShowTurnUseNum] = 2;
		m_ShowTurnUseNum += 1;
	}

	for (int i = 0; i < m_ShowTurnUseNum; i++)
		for (int j = i + 1; j < m_ShowTurnUseNum; j++)
		{
		if (yList[i] >= yList[j])
		{
			if (yList[i] == yList[j])
			{
				if (xoffsetList[i] < xoffsetList[j])continue;
			}
			dustbin = yList[i];
			yList[i] = yList[j];
			yList[j] = dustbin;

			dustbin = m_ShowTurnType[i];
			m_ShowTurnType[i] = m_ShowTurnType[j];
			m_ShowTurnType[j] = dustbin;

			pdustbin = m_pShowTurn[i];
			m_pShowTurn[i] = m_pShowTurn[j];
			m_pShowTurn[j] = pdustbin;
		}
		}

}


void cFightState::SetTarget(int ID, int Target)
{
	m_pFightWorkList[ID]->targetID = Target;
}


bool cFightState::ReturnApproach(int ID, float Speed /*= 20.0f*/)
{
	int xTarget = m_战斗坐标xs[ID];
	int yTarget = m_战斗坐标ys[ID];
	int x = (int)m_pFightWorkList[ID]->m_pObj->GetX();
	int y = (int)m_pFightWorkList[ID]->m_pObj->GetY();
	cObj* pObj = m_pFightWorkList[ID]->m_pObj;
	//是否已经到目的地
	if (abs(xTarget - x) < 2 && abs(yTarget - y) < 2)
	{
		if (ID < 10)
		{
			pObj->SetDirection(7);
		}
		else
		{
			pObj->SetDirection(3);
		}
		pObj->SetPos(xTarget, yTarget);
		pObj->Set(POS_FIGHT_STAND);
		pObj->Move2();
		return true;
	}
	int direction = GetDirection4(x, y, xTarget, yTarget);
	m_pFightWorkList[ID]->m_pObj->Set(POS_RETURN);
	cWasFile* pdata = pObj->m_pShowData[0];
	if (direction != pObj->GetDirection())  //如果要移动的方向和原来的方向不同,则转向
	{
		int nowframe1 = pdata->GetNowFrame();
		if (nowframe1 != pdata->GetMaxFrame() - 1 && pdata->GetWillNextFrame())
		{
			pdata->SetFrame(0);
			pObj->Move2();
			pObj->SetDirection(direction);
			return false;
		}
	}
	int k = (int)((x - xTarget)*(x - xTarget) + (y - yTarget)*(y - yTarget));
	if (k > 0 && k <= Speed*Speed)  //如果离目标只差一点点
	{
		pdata->SetFrame(pdata->GetMaxFrame() - 1);
		pObj->SetPos(xTarget, yTarget);
		pObj->Move2();
		return false;
	}
	float radian = atan2(
		(float)(yTarget - y),
		(float)(xTarget - x)
		);
	float yOffset = Speed * sin(radian);
	float xOffset = Speed * cos(radian);
	pObj->SetPos((int)(x + xOffset), (int)(y + yOffset));
	//防止出现最后一帧
	if (pdata->GetNowFrame() == pdata->GetMaxFrame() - 2)
		pdata->SetFrame(0);
	pObj->SetDirection(direction);
	pObj->Move2();
	return false;
}


bool cFightState::Suffer(int ID)
{
	int& time = m_pFightWorkList[ID]->GetWork()->stage;
	cObj* pTarget = m_pFightWorkList[ID]->m_pObj;

	for (int i = 0; i < 3; i++)
	{
		pTarget->m_pShowData[i]->m_bMove = true;
	}
	if (time == 30)
	{
		pTarget->SetDirection(GetReverseDirection(m_pFightWorkList[ID]->m_sufferDirection));
		pTarget->Set(POS_SUFFER);
		pTarget->SetStatic(true);

		pTarget->SetFrame(1);

		m_Sufferspd = 2;
		time -= 4;
		cPropertyData* pet;
		pTarget->GetPropertyData(pet);
		if (pet->m_HP < 1)
		{
			if (m_pFightWorkList[ID]->m_NowBeAtkowner > -1)
			{
				m_pFightWorkList[m_pFightWorkList[ID]->m_NowBeAtkowner]->m_pObj->SetSpeed(8);
			}
		}
	}
	else
	{
		if (time > 10)
		{
	   //	int maxf = pTarget->m_pShowData[0]->GetNowFrame();
			time -= 1;
			pTarget->SufferBack(m_Sufferspd, m_pFightWorkList[ID]->m_sufferDirection);
			//////////////////////////////////////////////////////////////////////////
			pTarget->Move2();
			//////////////////////////////////////////////////////////////////////////
		}
		else
		{
			if (time > 0)
			{
				cPropertyData* pTargetData;
				pTarget->GetPropertyData(pTargetData);
				if (1 > pTargetData->m_HP)
				{
					time -= 1;
					return true;
				}
				else
				{
					time = 0;
					return true;
				}
			}
			else
			{
				if (time == 0)
				{
					cPropertyData* pTargetData;
					pTarget->GetPropertyData(pTargetData);
					if (pTargetData->m_Controler.GetFly())
					{

						if (1 > pTargetData->m_HP)
						{
							time = -100;
							return true;
						}
					}
					time -= 1;
					//pTarget->m_pShowData[0]->SetFrame(1);
				}
				else
				{
					if (time > -100)
					{
						if (abs(pTarget->m_xPos - pTarget->m_oldx) < 6.0f)
						{
							if (abs(pTarget->m_yPos - pTarget->m_oldy) < 6.0f)
							{
								pTarget->SetX(pTarget->m_oldx);
								pTarget->SetY(pTarget->m_oldy);
								time = -100;
								return true;
							}
						}
						time -= 1;
						int direction = GetReverseDirection(m_pFightWorkList[ID]->m_sufferDirection);
						pTarget->SetDirection(direction);
						pTarget->SufferBack(m_Sufferspd, direction);
						pTarget->Set(POS_SUFFER);
						//////////////////////////////////////////////////////////////////////////
						pTarget->Move2();
						//////////////////////////////////////////////////////////////////////////
					}
					else  if (-100 == time)
					{
						cPropertyData* pTargetData;
						pTarget->GetPropertyData(pTargetData);
						if (1 > pTargetData->m_HP)
						{
							SetDie(ID);
							return true;
						}
						time -= 1;
					}
					else
					{
						pTarget->Set(POS_FIGHT_STAND);
						pTarget->SetFrame(pTarget->m_pShowData[0]->GetMaxFrame() - 2);//减少等待时间
						pTarget->Move2();
						m_pFightWorkList[ID]->m_work.pop_back();
						pTarget->SetStatic(false);
						return true;
					}
				}
			}
		}
	}
	return false;
}


bool cFightState::MagicSuffer(int ID)
{
	cObj* pobj = m_pFightWorkList[ID]->m_pObj;
	for (int i = 0; i < 4; i++)
	{
		pobj->m_pShowData[i]->m_bMove = true;
	}
	return true;
}


int cFightState::AutoSelectRand(bool Enemy)
{
	int startNum = rand() % 10;
	int offset = 0;
	if (!Enemy)
	{
		offset = 10;
	}
	int i = 0;
	for (; i < 10; i++)
	{
		if (m_pFightWorkList[startNum + offset]->isExist)
			break;
		else
			startNum = (startNum + 1) % 10;
	}
	if (i == 10)return -1;
	return startNum + offset;
}


int cFightState::WorkAttack(int i)
{
	cWasFile* ShowData = m_pFightWorkList[i]->m_pObj->m_pShowData[0];
	int point0;
	int point1;

	if (m_pFightWorkList[i]->m_pObj->m_NowPos == POS_ATTACK)
	{
		point0 = m_pFightWorkList[i]->GetFightPoint()->m_Point[0];
		point1 = m_pFightWorkList[i]->GetFightPoint()->m_Point[1];
	}
	else
	{
		point0 = m_pFightWorkList[i]->GetFightPoint()->m_Point2[0];
		point1 = m_pFightWorkList[i]->GetFightPoint()->m_Point2[1];
	}
	////是否到攻击点
	int nowfrme = ShowData->GetNowFrame();
	if (ShowData->GetMaxFrame() <= point0)point0 = ShowData->GetMaxFrame() - 1;

	if (nowfrme == point0 && ShowData->GetWillNextFrame())
	{
		if (point0 == point1)
			return 3; //第一点+第二点
		return 1;//第一点
	}
	//是否到伤害点 第二点
	if (ShowData->GetMaxFrame() <= point1)point1 = ShowData->GetMaxFrame() - 1;
	if (ShowData->GetNowFrame() == point1)
	{
		//		Q::msgbox("", "%d", ShowData->m_Picture.m_NextFrame);
		if (ShowData->GetWillNextFrame())
		{
			return 2;
		}
	}
	return 0;
}


bool cFightState::WaitPosEnd(int i)
{
	cWasFile* data = m_pFightWorkList[i]->m_pObj->m_pShowData[0];
	if (data->GetMaxFrame() - data->GetNowFrame() == 1)
	{
		if (data->GetWillNextFrame())
			return true;
	}
	return false;
}


bool cFightState::SetSuffer_state30(int ID, int direction, int userid)
{
// 	cPropertyData* petdata;
// 	m_pList[ID]->m_pObj->GetPropertyData(petdata);

	m_pFightWorkList[ID]->m_NowBeAtkowner = userid;


	m_pFightWorkList[ID]->m_pObj->SetSound(POS_SUFFER, true);

	m_pFightWorkList[ID]->m_sufferDirection = direction;

	if (m_pFightWorkList[ID]->m_work.size())
	{
		if (WORKTYPE_SUFFER == m_pFightWorkList[ID]->GetWork()->type)
		{
			m_pFightWorkList[ID]->GetWork()->stage = 30;
			return true;
		}
	}
	m_pFightWorkList[ID]->SetWork(WORKTYPE_SUFFER);
	m_pFightWorkList[ID]->GetWork()->stage = 30;
	m_pFightWorkList[ID]->m_pObj->m_oldx = m_pFightWorkList[ID]->m_pObj->m_xPos;
	m_pFightWorkList[ID]->m_pObj->m_oldy = m_pFightWorkList[ID]->m_pObj->m_yPos;
	return true;
}


bool cFightState::SetWork(int ID, int Type)
{
	m_pFightWorkList[ID]->SetWork(Type);
	return true;
}


bool cFightState::SetMagicSuffer(int ID, int direction)
{
	//m_pList[ID]->m_work.clear();
	m_pFightWorkList[ID]->SetWork(WORKTYPE_MAGICSUFFER);
	cObj* pObj = m_pFightWorkList[ID]->m_pObj;
	pObj->SetShake(true);
	pObj->Set(POS_SUFFER);
	pObj->SetStatic(true);
	m_pFightWorkList[ID]->m_sufferDirection = direction;
	pObj->SetDirection(GetReverseDirection(direction));
	for (int i = 0; i < 3; i++)
	{
		if (pObj->m_pShowData[i]->m_NeedShow)
		{
			pObj->m_pShowData[i]->SetFrame(1);
			pObj->m_pShowData[i]->m_bMove = true;
		}
	}

	return true;
}


bool cFightState::SwitchMagicSuffer(int ID)
{
	sFightWork* p = m_pFightWorkList[ID];
	if (p->m_work.size())
	{
		p->m_work.pop_back();
	}
	p->m_pObj->SetShake(false);
	p->m_pObj->SetStatic(false);
	SetSuffer_state30(ID, p->m_sufferDirection, -1);
	return true;
}



bool cFightState::SwitchMagicSufferAvoid(int ID)
{
	sFightWork* p = m_pFightWorkList[ID];
	if (p->m_work.size())
	{
		p->m_work.pop_back();
	}
	p->m_pObj->SetShake(false);
	p->m_pObj->SetStatic(false);
	SetAvoid_state15(ID, p->m_sufferDirection);
	return true;
}



bool cFightState::SortBySpeed()
{
	cObj* pObj[2];
	cPropertyData* pPetData[2];
	int* spd1, *spd2;
	int posid;
	for (int i = 0; i < 20; i++)
		for (int j = i + 1; j < 20; j++)
		{
		if (m_pFightWorkList[m_SpeedListPos[i]]->isExist && m_pFightWorkList[m_SpeedListPos[j]]->isExist)
		{
			pObj[0] = m_pFightWorkList[m_SpeedListPos[i]]->m_pObj;
			pObj[1] = m_pFightWorkList[m_SpeedListPos[j]]->m_pObj;
			pObj[0]->GetPropertyData(pPetData[0]);
			pObj[1]->GetPropertyData(pPetData[1]);


			spd1 = pPetData[0]->Speed.GetDatap();
			spd2 = pPetData[1]->Speed.GetDatap();
			if (*spd1 < *spd2)
			{
				posid = m_SpeedListPos[i];
				m_SpeedListPos[i] = m_SpeedListPos[j];
				m_SpeedListPos[j] = posid;
			}
		}
		}
	for (int i = 0; i < 20; ++i)
	{
		m_pFightWorkList[m_SpeedListPos[i]]->_turnOfSpeed = i;
	}
	return true;
}


int cFightState::CheckTarget(int ID, int target, int skillid)
{
	if (target < 0)
	{
		return target;
	}
	if (m_pFightWorkList[target]->isExist)
	{
		if (g_pMainState->m_FightWorkList[target].CheckDie())
		{
			switch (skillid)
			{// 复活法术和特技
			case 37:
			case 104:
			case 125:
			case 193: // 由己渡人
			case 3008:
			case 3009:
			case 3048:
				return target;
				break;
			case 1003:
				if (1)
				{
					sItem2* item = g_pMainState->m_SkillManager.GetItem(ID);
					if (item->GetType() == 22)
					{
						switch (item->GetID())
						{// 复活药
						case 44:
						case 45:
// 						case 51:
// 						case 52:
// 						case 60:
							return target;
							break;
						}
					}
				}
				break;
			default:
				break;
			}
		}
		else return target;
	}

	int t = 4;
	if ((ID / 10) == (target / 10))
	{
		t = 3;
	}
	return g_pMainState->m_AI.find追击反间月光(ID, t, true);

	if (ID < 10 && target < 10)
	{
		return g_pMainState->m_AI.find追击反间月光(ID, 3, true);
	}
	else
	{
		if (ID > 9 && target > 9)
		{
			return g_pMainState->m_AI.find追击反间月光(ID, 3, true);
		}
		else
		{
			return g_pMainState->m_AI.find追击反间月光(ID, 4, true);
		}
	}
}



void cFightState::SetDie(int ID, bool dynamicFly /* = false */)
{
	m_pFightWorkList[ID]->m_work.clear();
	m_pFightWorkList[ID]->m_WorkType = -1;
	m_pFightWorkList[ID]->m_pObj->m_MagicSuffer.m_NeedShow = false;
	cPropertyData* petdata;
	m_pFightWorkList[ID]->m_pObj->GetPropertyData(petdata);
	m_pFightWorkList[ID]->m_DiePoint = 2;


	bool isg1 = false;
	if (petdata->Ghost.d1 > 0)
	{
		bool isg2 = false;
		int user = g_pMainState->m_FightWorkList[ID].m_NowBeAtkowner;
		if (user >= 0)
		{
			sFightWork& w = g_pMainState->m_FightWorkList[user];
			if (w.isExist && w.m_pObj)
			{
				cPropertyData* d = w.m_pObj->getPropertyData();
				if (d && d->Ghost.d2 > 0)
				{
					isg2 = true;
				}
			}
		}
		if (!isg2)
		{
			isg1 = true;
		}
	}

	if (isg1 || (!petdata->m_Controler.GetFly() && !dynamicFly))
	{
//		m_pList[ID]->m_pData->SetSound(POS_DEAD);
		SetWork(ID, WORKTYPE_FALLDOWN);
	}
	else
	{
		m_pFightWorkList[ID]->m_pObj->m_Wav.LoadWav(1382520422);
//		m_pFightWorkList[ID]->m_pObj->getPropertyData()->FillHpMp();
		SetWork(ID, WORKTYPE_FLY);


		if (g_pMainState->m_taskSM.m_SuccessNum >= 0 && 
			m_pFightWorkList[ID]->m_pObj->getPropertyData()->_isOurTeamTemp && 
			m_pFightWorkList[ID]->m_pObj->m_TrueName.GetString() == "同门")
		{
			g_pMainState->m_taskSM.m_SuccessNum = -1;
		}
	}
}




bool cFightState::ApproachProtect(int ID, int TargetID)
{
	int xTarget = m_pFightWorkList[TargetID]->m_pObj->GetX();
	int yTarget = m_pFightWorkList[TargetID]->m_pObj->GetY();
	//m_pList[ID]->m_pData->Set(POS_RUN);
	m_pFightWorkList[ID]->m_pObj->SetStatic(false);

	int xDistance = 0;
	int yDistace = 0;

	float Speed = 30.0f;
	int x = m_pFightWorkList[ID]->m_pObj->GetX();
	int y = m_pFightWorkList[ID]->m_pObj->GetY();
	if (x == xTarget&&y == yTarget)
	{
		return true;
	}
	int xTargetold = (int)xTarget;
	int yTargetold = (int)yTarget;

	//得到正确的目标位置
	int direction1 = GetDirection4(x, y, xTargetold, yTargetold);

	if (xDistance || yDistace)
	{
		switch (direction1)
		{
		case 9:
			xTarget -= xDistance;
			yTarget += yDistace;
			break;
		case 7:
			xTarget += xDistance;
			yTarget += yDistace;
			break;
		case 3:
			xTarget -= xDistance;
			yTarget -= yDistace;
			break;
		case 1:
			xTarget += xDistance;
			yTarget -= yDistace;
			break;
		}
	}
	//确定方向
	int  direction2;
	if (x != xTarget&&y != yTarget)
		direction2 = GetDirection4(x, y, (int)xTarget, (int)yTarget);
	else   direction2 = m_pFightWorkList[ID]->m_pObj->GetDirection();
	if (direction2 != m_pFightWorkList[ID]->m_pObj->GetDirection())
	{
		m_pFightWorkList[ID]->m_pObj->SetDirection(direction2);
	}
	int k = (x - xTarget)*(x - xTarget) + (y - yTarget)*(y - yTarget);
	if (k <= Speed*Speed)  //如果离目标只差一点点
	{
		m_pFightWorkList[ID]->m_pObj->Set(POS_FIGHT_STAND);
		m_pFightWorkList[ID]->m_pObj->SetPos(xTarget, yTarget);
		//m_pList[ID]->m_pData->SetDirection(GetDirection4(x, y, xTargetold, yTargetold));
		m_pFightWorkList[ID]->m_pObj->Move2();
		return  true;
	}
	float radian = atan2(
		(float)(yTarget - y),
		(float)(xTarget - x)
		);
	float yOffset = Speed * sin(radian);
	float xOffset = Speed * cos(radian);

	m_pFightWorkList[ID]->m_pObj->Set(POS_FIGHT_STAND);
	m_pFightWorkList[ID]->m_pObj->SetPos(x + xOffset, y + yOffset);
	m_pFightWorkList[ID]->m_pObj->Move2();
	return false;
}


//给角色加一个BUF
bool cFightState::AddState(int userID, sBuff buf)
{
	return m_pFightWorkList[userID]->m_pObj->AddState(buf);
}




bool cFightState::FallDown(int ID)
{
	int& stage = m_pFightWorkList[ID]->GetWork()->stage;
	switch (stage)
	{
	case 0:
		m_pFightWorkList[ID]->m_pObj->Set(POS_DEAD);
		m_pFightWorkList[ID]->m_pObj->SetSound(POS_DEAD);
		m_pFightWorkList[ID]->m_pObj->SetStatic(false);
		stage = 1;
		break;
	case 1:
		if (WaitPosEnd(ID))
		{
			m_pFightWorkList[ID]->m_pObj->SetStatic(true);
			m_pFightWorkList[ID]->m_work.clear();
		}
		break;
	}

	return true;
}


bool cFightState::Avoid(int ID)
{
	sFightWork* p = m_pFightWorkList[ID];
	cObj* pObj = p->m_pObj;
	int& time = p->GetWork()->stage;
	time -= 1;
	if (time % 2 != 0)return true;
	for (int i = 0; i < 3; i++)
	{
		pObj->m_pShowData[i]->m_bMove = true;
	}
	if (14 == time)
	{
		pObj->m_oldx = (float)m_战斗坐标xs[ID];// pObj->m_xPos;
		pObj->m_oldy = (float)m_战斗坐标ys[ID];// pObj->m_yPos;
	}
	else
		if (time > 0)
		{
		pObj->SetDirection(GetReverseDirection(m_pFightWorkList[ID]->m_sufferDirection));
		pObj->SufferBack(8.0f, p->m_sufferDirection);
		}
		else
			if (time > -3)
			{
			}
			else
			{
				//	int xp1 = m_pList[ID]->m_pData->GetX();
				//	int xp2 = (int)m_xPosList[ID];
				//	int yp1 = m_pList[ID]->m_pData->GetY();
				//int yp2 = (int)m_yPosList[ID];
				if (abs(p->m_pObj->GetX() - m_战斗坐标xs[ID]) < 9 && abs(p->m_pObj->GetY() - m_战斗坐标ys[ID]) < 9)
				{
					pObj->SetXY(pObj->m_oldx, pObj->m_oldy);
					p->m_work.pop_back();
					//	pObj->SetGhost(false);
					return false;
				}
				int direction = GetReverseDirection(p->m_sufferDirection);
				pObj->SetDirection(direction);
				pObj->SufferBack(8.0f, direction);
			}
	return false;
}

bool cFightState::SetAvoid_state15(int ID, int direction)
{
	m_pFightWorkList[ID]->SetWork(WORKTYPE_AVOID);
	m_pFightWorkList[ID]->GetWork()->stage = 15;
	m_pFightWorkList[ID]->m_sufferDirection = direction;
	//	m_pList[ID]->m_pData->SetGhost(true);
	return true;
}


bool cFightState::Defend(int ID)
{
	int& time = m_pFightWorkList[ID]->GetWork()->stage;
	cObj* pTarget = m_pFightWorkList[ID]->m_pObj;

	for (int i = 0; i < 3; i++)
	{
		pTarget->m_pShowData[i]->m_bMove = true;
	}
	if (time == 30)
	{
		pTarget->Set(POS_DEF);

		pTarget->SetStatic(true);
		m_Sufferspd = 2;
		time -= 4;
		cPropertyData* pet;
		pTarget->GetPropertyData(pet);
		if (pet->m_HP < 1)
		{
			if (m_pFightWorkList[ID]->m_NowBeAtkowner > -1)
			{
				m_pFightWorkList[m_pFightWorkList[ID]->m_NowBeAtkowner]->m_pObj->SetSpeed(8);
			}
		}
	}
	else
		if (time > 10)
		{
		time -= 1;
		pTarget->SufferBack(3, m_pFightWorkList[ID]->m_sufferDirection);
		}
		else
			if (time > 0)
			{
		cPropertyData* pTargetData;
		pTarget->GetPropertyData(pTargetData);
		if (1 > pTargetData->m_HP)
		{
			time -= 1;
			return true;
		}
		else
		{
			time = 0;
			return true;
		}
			}
			else
				if (time == 0)
				{
		cPropertyData* pTargetData;
		pTarget->GetPropertyData(pTargetData);
		if (pTargetData->m_Controler.GetFly())
		{
			if (1 > pTargetData->m_HP)
			{
				time = -100;
				return true;
			}
		}
		time -= 1;
				}
				else
					if (time > -100)
					{
		if (abs(pTarget->m_xPos - pTarget->m_oldx) < 6.0f)
		{
			if (abs(pTarget->m_yPos - pTarget->m_oldy) < 6.0f)
			{
				pTarget->SetX(pTarget->m_oldx);
				pTarget->SetY(pTarget->m_oldy);
				time = -100;
				return true;
			}
		}
		time -= 1;
		pTarget->SufferBack(m_Sufferspd, GetReverseDirection(m_pFightWorkList[ID]->m_sufferDirection));



					}
					else  if (-100 == time)
					{
						cPropertyData* pTargetData;
						pTarget->GetPropertyData(pTargetData);
						if (1 > pTargetData->m_HP)
						{
							SetDie(ID);
							return true;
						}
						time -= 1;
					}
					else
					{
						pTarget->Set(POS_FIGHT_STAND);
						pTarget->SetFrame(pTarget->m_pShowData[0]->GetMaxFrame() - 1);

						pTarget->Move2();
						m_pFightWorkList[ID]->m_work.pop_back();
						pTarget->SetStatic(false);
						for (int i = 0; i < 3; i++)
						{
							pTarget->m_pShowData[i]->m_bMove = true;
						}
						return true;
					}

					return false;
}


bool cFightState::SetDefend_stage30(int ID, int direction, int userid)
{
	cPropertyData* pet;
	m_pFightWorkList[ID]->m_pObj->GetPropertyData(pet);
	if (pet->m_HP < 1)
	{
		SetSuffer_state30(ID, direction, userid);
		return true;
	}
	m_pFightWorkList[ID]->m_pObj->Set(POS_DEF);
	m_pFightWorkList[ID]->m_pObj->SetSound(POS_DEF);
	m_pFightWorkList[ID]->m_sufferDirection = direction;

	if (m_pFightWorkList[ID]->m_work.size())
	{
		if (WORKTYPE_DEFEND == m_pFightWorkList[ID]->GetWork()->type)
		{
			m_pFightWorkList[ID]->GetWork()->stage = 30;
			return true;
		}
	}
	m_pFightWorkList[ID]->SetWork(WORKTYPE_DEFEND);
	m_pFightWorkList[ID]->GetWork()->stage = 30;
	m_pFightWorkList[ID]->m_pObj->m_oldx = m_pFightWorkList[ID]->m_pObj->m_xPos;
	m_pFightWorkList[ID]->m_pObj->m_oldy = m_pFightWorkList[ID]->m_pObj->m_yPos;

	return true;
}



void cFightState::SetCounter(int ID, int TargetID)
{
	m_pFightWorkList[ID]->SetWork(WORKTYPE_COUNTER);
	m_pFightWorkList[ID]->targetID = TargetID;
}




bool cFightState::Counter(int ID)
{
	int TargetID = m_pFightWorkList[ID]->targetID;
	int& stage = m_pFightWorkList[ID]->GetWork()->stage;

	

	cObj* pUser = m_pFightWorkList[ID]->m_pObj;
	cObj* pTarget = m_pFightWorkList[TargetID]->m_pObj;



	cPropertyData* pUserData;
	cPropertyData* pTargetData;
	pUser->GetPropertyData(pUserData);
	pTarget->GetPropertyData(pTargetData);
	switch (stage)
	{
	case 0:
		if (1)
		{
			int pos;
			if (rand() % 2)
				pos = POS_ATTACK2;
			else
				pos = POS_ATTACK;
			pUser->Set(pos);
			pUser->SetSound(pos);

			stage = 120;
		}
	case 120:
		if (1)
		{
			int atkp = WorkAttack(ID);
			switch (atkp)
			{
			case 0:
				return true;
			default:
				if (1)
				{
					if (atkp != 2)
						stage = 1;
					ulong magic2 = 0x1D3FF13C;
					int MagicPos = 1;
					//必杀
					if (g_pMainState->m_SkillManager.CountCri(pUserData, pTargetData))
					{
						magic2 = 0xECD0E003;
					}
					m_pFightWorkList[TargetID]->SetMagiSufferID(magic2, MagicPos, &m_FullSkill.m_SufferMagic[TargetID]);
					SetSuffer_state30(TargetID, pUser->GetDirection(), ID);

				}
				break;
			}
		}
		return true;
	case 1:
		if (1)
		{
			stage += 1;
			int dam = 0;
			g_pMainState->m_SkillManager.CountphysicalDamage(dam, ID, TargetID);

		}
		return  true;
	case 2:
		if (WaitPosEnd(ID))
		{
			pUser->Set(POS_FIGHT_STAND);
			m_pFightWorkList[TargetID]->SetMagiSufferID(0, 1, &m_FullSkill.m_SufferMagic[TargetID]);
			m_pFightWorkList[ID]->m_work.pop_back();

			m_pFightWorkList[ID]->m_SkillSelectForCounter.SkillID = -1;


			sFightWork* pUserList = m_pFightWorkList[ID];
			sFightWork* pTargetList = m_pFightWorkList[TargetID];
			if (pTargetList->CheckDie())
			{
				return true;
			}
			if (rand() % 100 < 30 && pUserData->EndMagic >= 0 && !pUserData->m_FightData.chaos混乱反间)
			{
				auto& ss = pUserList->m_SkillSelect;
				m_pFightWorkList[ID]->m_SkillSelectForCounter = ss;

				ss.SkillLv = pUserData->m_Lv;
				ss.SkillID = pUserData->EndMagic;
				ss.TargetID = TargetID;
				pUserList->SetWork(WORKTYPE_MAGIC);
//				pUserList->m_WorkType = -1;

				return g_pMainState->m_SkillManager.Use(pUserList->m_SkillSelect, ID, true);
			}
		}
		return true;
// 	case 0x10086:
// 		m_pFightWorkList[ID]->m_work.pop_back();
// 		break;
	}
	return true;
}


bool cFightState::HiddenWeaponsMove(int id, int yoffset)
{
	float xTarget = (float)m_pFightWorkList[m_HiddenWeaponsTargetID[id]]->m_pObj->GetX();
	float yTarget = (float)(m_pFightWorkList[m_HiddenWeaponsTargetID[id]]->m_pObj->GetY() + yoffset);
	int x = m_HiddenWeaponsp[id].m_x;
	int y = m_HiddenWeaponsp[id].m_y;
	int xDistance = 30;
	int yDistace = 0;
	float Speed = 18.0f;


	if (x == xTarget&&y == yTarget)
	{
		m_HiddenWeaponsp[id].m_NeedShow = false;
		return true;
	}
	int xTargetold = (int)xTarget;
	int yTargetold = (int)yTarget;

	//得到正确的目标位置
	int direction1 = GetDirection4(x, y, xTargetold, yTargetold);

	if (xDistance || yDistace)
	{
		switch (direction1)
		{
		case 9:
			xTarget -= xDistance;
			yTarget += yDistace;
			break;
		case 7:
			xTarget += xDistance;
			yTarget += yDistace;
			break;
		case 3:
			xTarget -= xDistance;
			yTarget -= yDistace;
			break;
		case 1:
			xTarget += xDistance;
			yTarget -= yDistace;
			break;
		}
	}
	//确定方向
	int  direction2;
	if (x != xTarget&&y != yTarget)
		direction2 = GetDirection4(x, y, (int)xTarget, (int)yTarget);
	else   direction2 = m_HiddenWeaponsp[id].m_direction;

	m_HiddenWeaponsp[id].m_direction = direction2;

	int targetx2 = (int)xTarget;
	int targety2 = (int)yTarget;
	int k = (x - targetx2)*(x - targetx2) + (y - targety2)*(y - targety2);
	if (k <= Speed*Speed)  //如果离目标只差一点点
	{
		m_HiddenWeaponsp[id].m_NeedShow = false;
		return  true;
	}
	float radian = atan2(
		yTarget - y,
		xTarget - x
		);
	int yOffset2 = (int)(Speed * sin(radian));
	int xOffset = (int)(Speed * cos(radian));
	m_HiddenWeaponsp[id].m_x = x + xOffset;
	m_HiddenWeaponsp[id].m_y = y + yOffset2;
	m_HiddenWeaponsp[id].m_bMove = true;
	return false;
}


bool cFightState::ReMoveSealState(int userID)
{
	return ReMoveState(eBuffType封印, userID);
}


bool cFightState::ReMoveBuffState(int userID)
{
	return ReMoveState(eBuffType增益, userID);
}

bool cFightState::ReMoveDeBuffState(int userID)
{
	return ReMoveState(eBuffType负面, userID);
}

bool cFightState::ReMovePoisionState(int userID)
{
	return ReMoveState(eBuffType毒, userID);
}

bool cFightState::ReMoveStateID(int id, int userID)
{
	return m_pFightWorkList[userID]->m_pObj->ReMoveStateID(id);
}


bool cFightState::ReMoveState(eBuffType Type, int userID)
{
	return m_pFightWorkList[userID]->m_pObj->ReMoveState(Type);
}


void cFightState::ClearState(int id)
{
	return m_pFightWorkList[id]->m_pObj->ClearState();
}


void cFightState::SuccessFight()
{
//	sFightList* pObjList = &g_pMainState->m_FightList[g_pMainState->m_HeroID];
	EndFight();
	g_pMainState->m_TriggerFightFail.Clear();
	g_pMainState->m_TriggerFightEscape.Clear();
	g_pMainState->m_TriggerFightTurn.Clear();
	g_pMainState->m_TriggerFightStart.Clear();
	g_pMainState->m_TriggerFightSuccess.ProcessReMove();//计算奖励
	g_pMainState->m_PCHead.UpdateDate();
// 	if (g_StateType != STATE_FIGHT)
// 	{
// 		FillHpMpMedicine();
// 	}
}



void cFightState::EndFight(bool bFriendCure)
{
	////////////////////////////////////////////////////////////////////////// 呵呵哒 
// 	for (int i = 0; i < 20; ++i)
// 	{
// 		g_pMainState->m_AI.m_FightTarget[i] = -1;
// 	}
	if (g_StateType != STATE_FIGHT)return;
	m_turn = 0;
	_turn = 0;
	isInit = false;
	g_StateType = STATE_MAIN;
	g_pMainState->m_PCHead.MoveTeamHead(0);
	g_pMainState->m_Mp3.Load(g_pMainState->m_MusicName);

	g_pMainState->m_Accelator.setCharacter(g_pCharacter);
	g_pMainState->m_Accelator.init2();


	for (int i = 0; i < 20; i++)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			BackFromFight(i);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		m_FullSkill.m_FullSkilUP[i].m_NeedShow = false;
	}
	m_FightMenu.m_NowFighterID = -1;


	for (int i = 0; i < 10; i++)
	{
		if (m_pFightWorkList[i]->m_pObj->m_IndexType)
		{
			m_pFightWorkList[i]->isExist = true;
			m_pFightWorkList[i]->SetDie(false);
		}
	}

	g_pMainState->m_InterfaceTeam.update(false, _leaveBegin);
	g_pMainState->m_PCHead.UpDateHead();

// 	for (int i = 0; i < 10; i++)
// 	{
// 		if (i >= 5)
// 		{
// 			int tid = g_pMainState->m_InterfaceTeam.GetReTramTrun(i - 5);
// //			if (tid < g_pMainState->m_InterfaceTeam.getLeaveBegin())
// 			{
// 				if (m_pFightWorkList[i]->m_pObj->m_IndexType)
// 				{
// 					m_pFightWorkList[i]->isExist = true;
// 					m_pFightWorkList[i]->SetDie(false);
// 				}
// 			}
// 		}
// 		else
// 		{
// 			int tid = g_pMainState->m_InterfaceTeam.GetReTramTrun(i);
// //			if (tid < g_pMainState->m_InterfaceTeam.getLeaveBegin())
// 			{
// 				if (m_pFightWorkList[i]->m_pObj->m_IndexType)
// 				{
// 					m_pFightWorkList[i]->isExist = true;
// 					m_pFightWorkList[i]->SetDie(false);
// 				}
// 			}
// 		}
// 	}


//	if (g_pCharacter->m_PcData.m_FightPetID>-1)
	{//检测召唤兽升级
		CheckPetExp();
		FillHpMpMedicine();
	}


// 	for (int i = 0; i < 5; ++i)
// 	{
// 		if (!m_pFightWorkList[i]->isExist &&
// 			m_pFightWorkList[i]->m_pObj &&
// 			m_pFightWorkList[i]->m_pObj->m_pIndex &&
// 			m_pFightWorkList[i]->m_pObj->m_IndexType)
// 		{
// 			int tid = g_pMainState->m_InterfaceTeam.GetReTramTrun(i);
// 			if (tid >= g_pMainState->m_InterfaceTeam.m_LeaveBegin)
// 			{
// 				m_pFightWorkList[i]->isExist = true;
// 				cObj* pTarget = m_pFightWorkList[i]->m_pObj;
// 				cPcData* pTargetData = pTarget->getPcData();
// //				pTarget->GetPropertyData(pTargetData);
// 				if (pTargetData->m_FightPetID >= 0)
// 				{
// 					m_pFightWorkList[i + 5]->isExist = true;
// 				}
// 			}
// 		}
// 	}

	if (g_pMainState->m_InterfaceTeam.m_eEnemyFormation != normal)
		g_pMainState->m_InterfaceTeam.SetFormation(normal, true);

//	cct::get()->isBattle打野 = false;


	g_pMainState->FindObj();
	//重画
	g_pMainState->m_Canvas.SetRedrawAll();


}



void cFightState::SetFightBufDown(int i)
{
	cPropertyData* pTargetData;
	m_pFightWorkList[i]->m_pObj->GetPropertyData(pTargetData);
	//去除角色的状态,还原角色数据 
	m_pFightWorkList[i]->m_pObj->m_MagicSuffer.m_NeedShow = false;
	// 伤害显示时间
	m_pFightWorkList[i]->m_DamageTime[0] = 100;
	//去除阵法效果
	g_pMainState->m_InterfaceTeam.SetupOneFormationEffect(g_pMainState->m_InterfaceTeam.GetReTramTrun(i), pTargetData, 0);
	ClearState(i);
}




void cFightState::FailFight()
{
	EndFight();
	//
	g_pMainState->m_TriggerFightSuccess.Clear();
	g_pMainState->m_TriggerFightEscape.Clear();
	g_pMainState->m_TriggerFightTurn.Clear();
	g_pMainState->m_TriggerFightStart.Clear();
	if (!g_pMainState->m_TriggerFightFail.ProcessReMove())
	{
		DieEffect(1);
		return;
		g_pMainState->m_pEndState->Set("GAME OVER", "队伍全灭了..请尝试点技能,点修,更新装备宝宝");
		g_StateType = STATE_GAMEOVER;
	}

}


void cFightState::EscapeFight()
{//从战斗中逃跑

	EndFight();
	//
	g_pMainState->m_TriggerFightSuccess.Clear();
	g_pMainState->m_TriggerFightFail.Clear();
	g_pMainState->m_TriggerFightTurn.Clear();
	g_pMainState->m_TriggerFightStart.Clear();
	g_pMainState->m_TriggerFightEscape.ProcessReMove();

//	FillHpMpMedicine();

}


void cFightState::DieEffect(int type)
{
	switch (type)
	{
	case 0://
		if (0)
		{
			g_pMainState->m_pEndState->Set("GAME OVER", "胜败乃兵家常事,大侠请重新来过");
			g_StateType = STATE_GAMEOVER;
		}
		break;
	case 1:
		if (1)
		{
			if (g_pMainState->getMaxLv() <= 30)
			{
				break;
			}
			g_pMainState->m_Map.LoadMap(20, 15, "轮回司", false);
			g_pMainState->resetLangTime();
			static bool isTagOnce = true;
			if (isTagOnce)
			{
				g_pMainState->m_Channel.AddNewString("浪时间清零");
				isTagOnce = false;
			}
			INT64 exp, exphero = 0;
			bool lostSkill = false;
			for (int i = 0; i < 5; ++i)
			{
				if (!g_pMainState->m_FightWorkList[i].isExist)
				{
					continue;
				}
				cPcData* pc = g_pMainState->m_FightWorkList[i].m_pObj->getPcData();
				// 总经验
				exp = pc->m_EXP;
				for (int k = pc->m_Lv; k >= 0; --k)
				{
					exp += GetCharacterExp(k);
				}
				for (int k = pc->m_MengPaiSkillLvs[0]; k >= 0; --k)
				{
					exp += GetMainSkillExp(k);
				}

				for (int k = pc->m_FuZhuSkillLvList.size() - 1; k >= 0; --k)
				{
					for (int j = pc->m_FuZhuSkillLvList[k]; j >= 0; --j)
					{
						exp += GetMainSkillExp(j);
					}
				}
				exp /= 1000;
				if (exp <= pc->m_EXP)
				{
					pc->m_EXP -= exp;
				}
				else
				{
					lostSkill = true;
					exp = pc->m_EXP;
					pc->m_EXP = 0;
					auto& lvs = pc->m_MengPaiSkillLvs;
					if (lvs[0] > 0)
					{
						--lvs[0];
					}
					forr(lvs, k)
					{
						lvs[k] = lvs[0];
					}
				}
				if (i == g_pMainState->m_HeroID)
				{
					exphero = exp;
				}
			}
			if (lostSkill)
			{
				g_pMainState->m_Channel.AddNewString("损失#R技能#R"); // #R经验#R和
			}
// 			else
// 			{
// 				ostringstream oss;
// 				oss << "损失#R";
// 				oss << exphero << "#R经验";
// 				g_pMainState->m_Channel.AddNewString(oss.str());
// 			}
			cct::autoSave();
			break;
			INT64 moneysub = g_pCharacter->m_PcData.m_Money[0] / 10;
			INT64 expsub = g_pCharacter->m_PcData.m_EXP / 10;
			g_pCharacter->m_PcData.m_Money[0] -= moneysub;
			g_pCharacter->m_PcData.m_EXP -= expsub;
			ostringstream oss;
			oss << "战斗失败了,损失了#R";
			oss << moneysub << "#R钱 #R" << expsub << "#R经验";
			g_pMainState->m_Channel.AddNewString(oss.str());
//			if (g_StateType != STATE_FIGHT)
// 			{
// 				FillHpMpMedicine();
// 			}
		}
		break;
	}
}


void cFightState::FillHpMpMedicine()
{
	//队友自动满血满蓝
	for (int i = 0; i < 5; i++)
	{
		if (!g_pMainState->m_FightWorkList[i].isExist)continue;
//		if (i == g_pMainState->m_HeroID)continue;
		cPropertyData* pdata;
		g_pMainState->m_FightWorkList[i].m_pObj->GetPropertyData(pdata);
		if (pdata->m_HP <= 1 || g_pMainState->_guaji || g_pMainState->_autoGhost)
		{
			pdata->FillHpMp();
		}
		if (INDEXTYEP_CHARACTER == g_pMainState->m_FightWorkList[i].m_pObj->m_IndexType)
		{
			cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[i].m_pObj->m_pIndex;
			for (int j = 0; j < pc->m_PcData.m_NumofBB; j++)
			{
				cPetData& p = pc->m_PcData.m_pPets[j]->m_PetData;
				if (p.m_HP <= 1 || (g_pMainState->_guaji && g_pMainState->m_Map.m_MapType) || g_pMainState->_autoGhost)
				{
					p.FillHpMp();
				}
			}
// 			pc->m_PCData.m_Item[0].m_Num = 15;
// 			pc->m_PCData.m_Item[1].m_Num = 15;
// 			pc->m_PCData.m_Item[2].m_Num = 15;
// 			pc->m_PCData.m_Item[3].m_Num = 15;
// 			pc->m_PCData.m_Item[4].m_Num = 15;
// 			pc->m_PCData.m_Item[5].m_Num = 15;
// 			pc->m_PCData.m_Item[6].m_Num = 10;
// 			pc->m_PCData.m_Item[7].m_Num = 10;
// 			pc->m_PCData.m_Item[8].m_Num = 10;

// 			for (int i = 0; i < 6; ++i)
// 			{
// 				pc->m_PCData.m_Item[i].m_Num = 1;
// 			}
// 			for (int i = 6; i <= 8; ++i)
// 			{
// 				pc->m_PCData.m_Item[i].m_Num = (9 - i) * 5;
// 			}
//
// 			for (int i = 0; i <= 8; ++i)
// 			{
// 				pc->m_PcData.m_Items[i].m_Num = cct::get()->药品数量;
// 			}
		}
	}
}


cFightState::cFightState()
{
	m_pFightWorkList.resize(20);
	for (int i = 0; i < 20; i++)
	{
		m_pFightWorkList[i] = 0;
	}
	for (int i = 0; i < 5; i++)
	{
		m_pFileToLoad[i] = 0;
		m_IDtoLoad[i] = 0;
	}
	for (int i = 0; i < 30; i++)
	{
		m_pShowTurn[i] = 0;
	}
}


void cFightState::CheckPetExp()
{
	for (int i = 0; i < 5; ++i)
	{
		if (!m_pFightWorkList[i])
		{
			continue;
		}
		if (!m_pFightWorkList[i]->isExist || !m_pFightWorkList[i + 5]->isExist)
		{
			continue;
		}
		cPcData* pc = m_pFightWorkList[i]->m_pObj->getPcData();
		if (pc->m_FightPetID < 0)
		{
			continue;
		}
		cPetData* data = &pc->m_pPets[pc->m_FightPetID]->m_PetData;
		int lv = g_pCharacter->m_PcData.m_Lv + cct::LvGapFromRoleAndBaby;
		lv = min(lv, cct::MaxBabyLv);
		while (true)
		{
			if (data->m_Lv >= lv)
			{
				break;
			}
			if (!data->lvup())
			{
				break;
			}
			else
			{
				data->apply();
			}
		}
	}

// 	int lv = g_pCharacter->m_PcData.m_Lv + cct::get()->lvGapFromRoleAndBaby;
// 	if (lv > cct::get()->maxBabyLv)
// 	{
// 		lv = cct::get()->maxBabyLv;
// 	}
// 	for (int i = 0; i < g_pCharacter->m_PcData.m_NumofBB; ++i)
// 	{
// 		cPropertyData* pPetdata = &g_pCharacter->m_PcData.m_pPets[i]->m_PetData;
// 		if (lv == pPetdata->m_Lv)
// 		{
// 			continue;
// 		}
// 		pPetdata->Followlv(lv, true, false, true);
// 	if (false && pPetdata->EXP >= pPetdata->ExpMax)
// 	{
// 		if (pPetdata->m_Lv < g_pCharacter->m_PcData.m_Lv + cct::get()->lvGapFromRoleAndBaby)
// 		{
// 			while (pPetdata->EXP >= pPetdata->ExpMax || 1)
// 			{
// 				if (!pPetdata->LeveUp(1, true, false))break;
// 				if (pPetdata->m_Lv >= g_pCharacter->m_PcData.m_Lv + cct::get()->lvGapFromRoleAndBaby)
// 					break;
// 			}
// 			ostringstream oss;
// 			oss.str("");
// 			oss << "你的";
// 			oss << pPetdata->m_Name;
// 			oss << "升到了";
// 			oss << pPetdata->m_Lv;
// 			oss << "级";
// 			g_pMainState->m_Channel.AddNewString(oss.str(),"",3);
// 			int lvadd = pPetdata->m_Lv - pPetdata->m_FuZhuSkillLvList[0];
// 			for (int i = 0; i < 3; i++)
// 			pPetdata->lvUpFuZhuSkill(lvadd, i);
// 
// 
// 
// 			g_pMainState->m_PCHead.UpdatePetHp();
// 			g_pMainState->m_PCHead.UpdatePetMp();
// 			g_pMainState->m_PCHead.UpdatePetExp();
// 
// 
//
//	}
// 	}
}