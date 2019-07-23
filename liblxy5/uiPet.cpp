#include "_global.h"

static const int s_yInv = 22;
static int s_perPoint = 1;
bool cInterfacePet::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	ostringstream oss;
	oss.str("");
	oss << "参战";
	m_TPetProPerty[19].SetString(oss.str());

	m_TPetProPerty[20].SetString(
		toString("*%d", s_perPoint/*ccm::get()->per加点*/));

//	m_TPetProPerty[20].m_NeedShow = false;
	m_TPetProPerty[21].SetString("@");
	
//	m_TPetProPerty[21].m_NeedShow = false;

	oss.str("");
	oss << "放生";
	m_TPetProPerty[22].SetString(oss.str());
	oss.str("");
	oss << "查看资质";
	m_TPetProPerty[23].SetString(oss.str());
	oss.str("");
	oss << "确定";
	m_TPetProPerty[24].SetString(oss.str());
	oss.str("");
	oss << "进阶";
	m_TPetProPerty[25].SetString(oss.str());
	m_PetSkill.Init();
	m_ItemDataTime = 0;

	//m_Shadow.Set(&g_pMainState->m_Shadow);
	//m_Shadow.m_bStatic = true;
	m_TSkillSelectData[0].SetColor(RGB(255, 255, 0));
	m_TSkillSelectData[1].SetColor(RGB(0, 255, 0));

	m_TPetProPerty[1].m_hFont = g_pMainState->m_hFont[0];

	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_UpB.Load(0x08E2D199);
	ccm::get()->pushWdf("宝宝面板按钮上", 0x08E2D199);
	m_UpB.SetStatic(true);
	m_DownB.Load(0xC013B53B);
	ccm::get()->pushWdf("宝宝面板按钮下", 0xC013B53B);
	m_DownB.SetStatic(true);
	m_SkillPage = 0;
	m_PetPage = 0;

	loadBack(1227154258);
	m_back.Load(0x79D01E0E);
	m_back.SetStatic(true);
	ccm::get()->pushWdf("宝宝面板", 1227154258);
	m_PetObj.Init();
	m_PetObj.SetDirection(3);
	m_PetObj.m_IndexType = INDEXTYEP_PET;

	forv (m_TPetName, i)
	{
		m_TPetName[i].m_hFont = g_pMainState->m_hFont[0];
	}
	for (int i = 0; i < 2; i++)
	{
		m_PetSelectBack[i].Load(0xF151309F);
		ccm::get()->pushWdf("宝宝面板select", 0xF151309F);
		m_PetSelectBack[i].SetStatic(true);
		m_PetSelectBack[i].SetFrame(1);
		m_PetSelectBack[i].SetxOffset(30);
	}
	m_SetAttackB.Load(0x79D01E0E);
	ccm::get()->pushWdf("宝宝面板参战", 0x79D01E0E);
	m_SetAttackB.SetStatic(true);
	for (int i = 0; i < 5; i++)
	{
		m_AddPoint[i].Load(0xC47885C6);
		m_SubPoint[i].Load(1577923263);
		ccm::get()->pushWdf("宝宝面板加点", 0xC47885C6);
		ccm::get()->pushWdf("宝宝面板减点", 1577923263);
		m_AddPoint[i].SetStatic(true);
		m_SubPoint[i].SetStatic(true);
		m_AddPoint[i].SetFrame(0);
		m_SubPoint[i].SetFrame(0);
	}
	m_XunYang.Load(0x79D01E0E);
	ccm::get()->pushWdf("宝宝面板驯养", 0x79D01E0E);
	m_XunYang.SetStatic(true);

	_btnJJ.Set(&g_pMainState->m_Button4);
	_btnJJ.m_bStatic = true;

	m_SetAddPoint.Set(&m_XunYang);
	m_SetAddPoint.m_bStatic = true;

	m_ChaKanZiZhi.Load(0xB15C5678);
	ccm::get()->pushWdf("宝宝面板资质", 0xB15C5678);
	m_ChaKanZiZhi.SetStatic(true);
	m_FreePet.Load(0x79D01E0E);
	ccm::get()->pushWdf("宝宝面板放生", 0x79D01E0E);
	m_FreePet.SetStatic(true);
	for (int i = 0; i < 17; i++)
	{
		m_TPetProPerty[i].SetColor(RGB(0, 0, 0));
	}
	for (int i = 17; i < 26; i++)
		m_TPetProPerty[i].SetColor(RGB(250, 250, 250));
	m_TPetProPerty[21].SetColor(RGB(0, 0, 0));
	Move(0, 0 + 35);
	m_PetSkill.m_NeedShow = false;

	// 	for (int i = 0; i < 5; i++)
	// 	{
	// 		m_AddPoint[i].SetFrame(0);
	// 		m_AddPoint[i].m_bMove = true;
	// 		m_SubPoint[i].SetFrame(0);
	// 		m_SubPoint[i].m_bMove = true;
	// 	}

	return true;
}

bool cInterfacePet::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);
	pCanvas->Add(&m_back, 1, true);
	pCanvas->Add(&m_Cancel, 1);
	if (m_TrueSelect > -1)
	{
		pCanvas->Add(&m_PetSelectBack[0], 1);
		pCanvas->Add(&m_PetSelectBack[1], 1);
	}
	pCanvas->Add(&m_UpB, 1);
	pCanvas->Add(&m_DownB, 1);


	pCanvas->Add(&m_SetAttackB, 1);
	pCanvas->Add(&m_FreePet, 1);
	pCanvas->Add(&m_XunYang, 1);
	pCanvas->Add(&m_ChaKanZiZhi, 1);
	pCanvas->Add(&_btnJJ, 1);

	for (int i = 0; i < 5; i++)
	{
		pCanvas->Add(&m_AddPoint[i], 1);
		pCanvas->Add(&m_SubPoint[i], 1);
	}
	if (_charactor->m_PcData.m_NumofBB)
	{
		//pCanvas->Add(&m_Shadow, 1);
		if (m_PetObj.m_pIndex)
		{
			pCanvas->Add(m_PetObj.GetShadow(), 1);
			m_PetObj.ShowOnScreen(pCanvas);
		}
		/*for (int i = 0; i < 4; i++)
		{
		if (m_PetPic[i].m_NowID)
		pCanvas->Add(&m_PetPic[i], 1);
		}*/
		for (int i = 0; i < 19; i++)
		{
			pCanvas->Add(&m_TPetProPerty[i]);
		}
	}
	pCanvas->Add(&m_SetAddPoint, 1);
	for (int i = 19; i < 26; i++)
	{
		pCanvas->Add(&m_TPetProPerty[i]);
	}
	if (m_PetSkill.m_NeedShow)
	{
		m_PetSkill.Show(pCanvas);
	}
	int petnum = (_charactor->m_PcData.m_NumofBB - m_PetPage * m_TPetName.size());
	if (petnum > m_TPetName.size())petnum = m_TPetName.size();
	for (int i = 0; i < petnum; i++)
	{
		pCanvas->Add(&m_TPetName[i]);
	}

	int id = _charactor->m_PcData.m_FightPetID;
	if (id >= 0)
	{
		m_TPetProPerty[21].m_NeedShow = ((id / m_TPetName.size()) == m_PetPage);
		const auto& t = m_TPetName[id % m_TPetName.size()];
		m_TPetProPerty[21].SetXY(t.m_x + 95, t.m_y);
	}
	else
	{
		m_TPetProPerty[21].m_NeedShow = false;
	}

	return true;
}

bool cInterfacePet::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}
	ResetButton();
	if (m_FreePetMode)
	{
		return ProcessFreePet();
	}
	//如果鼠标不在界面上,直接退出
	if (isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);
		if (CheckOn(&m_Cancel, 60))return true;
		if (CheckOn(&m_SetAttackB, 13))return true;
		//		if(m_bAddPoint)
		for (int i = 0; i < 5; i++)  //
		{
			if (m_AddPoint[i].GetNowFrame() != 3)
				if (CheckOn(&m_AddPoint[i], 20 + i))return true;
			if (m_SubPoint[i].GetNowFrame() != 3)
				if (CheckOn(&m_SubPoint[i], 30 + i))return true;
		}
		if (CheckOn(&m_XunYang, 14))return true;
		if (CheckOn(&m_ChaKanZiZhi, 15))return true;
		if (CheckOn(&m_FreePet, 17))return true;
		if (CheckOn(&m_SetAddPoint, 61))return true;
		if (CheckOn(&_btnJJ, 10086))return true;
		if (CheckOn(&m_back, 10010))return true;

		if (m_UpB.GetNowFrame() != 3)
			if (CheckOn(&m_UpB, 50))return true;
		if (m_DownB.GetNowFrame() != 3)
			if (CheckOn(&m_DownB, 51))return true;

		//召唤兽选择
		if (g_yMouse > m_yPos + 45 && g_yMouse<m_yPos + 160 && g_xMouse>m_xPos + 15 && g_xMouse < m_xPos + 120)
		{
			m_PetSelectBack[0].m_NeedShow = true;
			m_PetSelectBack[1].m_NeedShow = true;
			m_Select = (g_yMouse - (m_yPos + 45)) / s_yInv;
			if (m_Select >= m_TPetName.size())m_Select = m_TPetName.size() - 1;
			if (_charactor->m_PcData.m_NumofBB - m_PetPage * m_TPetName.size() <= m_Select)
			{
				m_Select = _charactor->m_PcData.m_NumofBB - m_PetPage * m_TPetName.size() - 1;
			}
			m_PetSelectBack[0].SetY(m_yPos + 45 + m_Select * s_yInv);
			m_PetSelectBack[1].SetY(m_PetSelectBack[0].GetY());
			return CheckL();
		}
		else
		{
			m_PetSelectBack[0].m_NeedShow = false;
			m_PetSelectBack[1].m_NeedShow = false;
		}
		//关闭界面
		if (g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))
		{
			OnOff(false);
		}
		m_Select = 7;
		CheckL();
	}

	if (m_PetSkill.m_NeedShow)
	{
		m_PetSkill.ProcessInput();
		if (!m_PetSkill.m_NeedShow)
		{
			m_ChaKanZiZhi.SetFrame(0);
			m_ChaKanZiZhi.m_bMove = true;
		}
	}
	return true;
}



bool cInterfacePet::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	ostringstream oss;
	switch (m_Select)
	{
	case -1:
		return true;
	case 0:  //召唤兽选择
	case 1:
	case 2:
	case 3:
	case 4:
		SelectPet(m_Select + m_PetPage * m_TPetName.size());
		break;
	case 6://移动
		if (1)
		{
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
			m_Sleeptime = 0;
		}
		return true;
	case 7://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	case 13:
		//设置参战
		if (g_StateType != STATE_MAIN)return true;
		if (m_TrueSelect < 0)return true;
//		if (2 == m_SetAttackB.GetNowFrame())
		if (m_TrueSelect != _charactor->m_PcData.m_FightPetID)
		{
//			m_back.m_bMove = true;
//			if (g_pMainState->SetFightPet(g_pMainState->m_HeroID, m_TrueSelect))
			if (g_pMainState->SetFightPet(_heroID, m_TrueSelect))
			{
//				m_SetAttackB.SetFrame(1);
				m_frampre = 0;
				m_TPetProPerty[19].SetString("休息");
			}
			else
				g_pMainState->m_Tags.Add("角色等级条件不足");
		}
		else
		{
			m_TPetProPerty[21].m_NeedShow = false;
//			m_SetAttackB.SetFrame(0);
			m_SetAttackB.m_bMove = true;
			g_pMainState->SetFightPet(_heroID, -1);
			m_TPetProPerty[19].SetString("参战");

		}
		return true;
	case 14:
		if (1)
		{	
			auto& per = s_perPoint; // ccm::get()->per加点;
			if (per == 1)
			{
				per = 10;
			}
			else if (per == 10)
			{
				per = 100;
			}
			else if (per == 100)
			{
				per = 1;
			}
			m_TPetProPerty[20].SetString(toString("*%d", per));
			//训养
// 			m_XunYang.SetFrame(1);
// 			if (m_TrueSelect < 0)return true;
// 			cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
// 			cPropertyData* pTargetData = &pPetSelect->m_PetData;
// 			int& lv = pTargetData->m_Lv;
// 			AddExp(pTargetData, (pTargetData->m_Lv / 3 + 1)*GetNormalFightExp(lv, lv, 5));
		}
		return true;
	case 15: // 查看资质
		if (m_ChaKanZiZhi.GetNowFrame() == 1)
		{
			m_PetSkill.m_NeedShow = false;
			m_ChaKanZiZhi.SetFrame(0);
		}
		else
		{
			m_PetSkill.m_NeedShow = true;
			m_ChaKanZiZhi.SetFrame(1);
			m_frampre = 0;
		}
		g_pMainState->m_Canvas.SetRedraw(m_PetSkill.m_Back.m_PreShowRect);
		return true;
	case 17:
	{
		if (g_StateType != STATE_MAIN)return true;
		m_FreePet.SetFrame(1);
		if (m_TrueSelect < 0)return true;
		if (g_pMainState->m_InterFaceBuyPet.m_Item.size() >= 20)
		{
			g_pMainState->m_Tags.Add("仓库已满");
			return true;
		}
		cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
		//cPetData* pTargetData = &pPetSelect->m_PetDataZZ;
		//放生
		m_FreePetMode = true;
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetPet(pPetSelect);
		g_pMainState->m_Dialog.SetString("回收到仓库还是放生?(#Y仓库满了也会直接放生#Y)", "回收", "放生", "点错了");
		g_pMainState->m_Dialog.OnOff(true);
		g_pMainState->m_Dialog.m_bRetSelect = true;
	}
		return true;
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:

	{
		if (m_TrueSelect < 0)return true;
		int per加点 = s_perPoint; // ccm::get()->per加点;
		if (_pointTemps[5] < per加点)
		{
			return true;
		}
		cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
		cPropertyData& petdata = pPetSelect->m_PetData;
		switch (m_Select)
		{
		case 20:  //加点
		{
			oss << (_pointTemps[0] += per加点) + petdata.PointBody2;
			m_TPetProPerty[8].SetString(oss.str());
		}
			break;
		case 21:
		{
			oss << (_pointTemps[1] += per加点) + petdata.PointMag2;
			m_TPetProPerty[9].SetString(oss.str());
		}
			break;
		case 22:
		{
			oss << (_pointTemps[2] += per加点) + petdata.PointStr2;
			m_TPetProPerty[10].SetString(oss.str());
		}
			break;
		case 23:
		{
			oss << (_pointTemps[3] += per加点) + petdata.PointDex2;
			m_TPetProPerty[11].SetString(oss.str());
		}
			break;
		case 24:
		{
			oss << (_pointTemps[4] += per加点) + petdata.PointAgi2;
			m_TPetProPerty[12].SetString(oss.str());
		}
			break;
		}
		UpdatePointButton();
		if (m_frampre->GetNowFrame() != 3)
			m_frampre->SetFrame(1);
		oss.str("");
		oss << (_pointTemps[5] -= per加点);
		m_TPetProPerty[13].SetString(oss.str());
	}
		return true;
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
		if (1)
		{
			if (m_TrueSelect < 0)return true;
			if (m_TrueSelect >= _charactor->m_PcData.m_NumofBB)
			{
				return true;
			}
			int per加点 = s_perPoint; // ccm::get()->per加点;
			cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
			cPetData& petdata = pPetSelect->m_PetData;
			oss.str("");
			switch (m_Select)
			{
			case 30:  //减点
				if (_pointTemps[0] - per加点 >= pPetSelect->m_PetData.m_Lv + cct::MinPoint)
				{
					oss << (_pointTemps[0] -= per加点) + petdata.PointBody2;
					m_TPetProPerty[8].SetString(oss.str());

					oss.str("");
					oss << (_pointTemps[5] += per加点);
					m_TPetProPerty[13].SetString(oss.str());
				}
				break;
			case 31:
				if (_pointTemps[1] - per加点 >= pPetSelect->m_PetData.m_Lv + cct::MinPoint)
				{
					oss << (_pointTemps[1] -= per加点) + petdata.PointMag2;
					m_TPetProPerty[9].SetString(oss.str());
					oss.str("");
					oss << (_pointTemps[5] += per加点);
					m_TPetProPerty[13].SetString(oss.str());
				}
				break;
			case 32:
				if (_pointTemps[2] - per加点 >= pPetSelect->m_PetData.m_Lv + cct::MinPoint)
				{
					oss << (_pointTemps[2] -= per加点) + petdata.PointStr2;
					m_TPetProPerty[10].SetString(oss.str());
					oss.str("");
					oss << (_pointTemps[5] += per加点);
					m_TPetProPerty[13].SetString(oss.str());
				}
				break;
			case 33:
				if (_pointTemps[3] - per加点 >= pPetSelect->m_PetData.m_Lv + cct::MinPoint)
				{
					oss << (_pointTemps[3] -= per加点) + petdata.PointDex2;
					m_TPetProPerty[11].SetString(oss.str());
					oss.str("");
					oss << (_pointTemps[5] += per加点);
					m_TPetProPerty[13].SetString(oss.str());
				}
				break;
			case 34:
				if (_pointTemps[4] - per加点 >= pPetSelect->m_PetData.m_Lv + cct::MinPoint)
				{
					oss << (_pointTemps[4] -= per加点) + petdata.PointAgi2;
					m_TPetProPerty[12].SetString(oss.str());
					oss.str("");
					oss << (_pointTemps[5] += per加点);
					m_TPetProPerty[13].SetString(oss.str());
				}
				break;
			}

			UpdatePointButton();
			if (m_frampre->GetNowFrame() != 3)
				m_frampre->SetFrame(1);
			oss.str("");
		}
		return true;
	case 50://上翻
		if (m_PetPage > 0)
		{
			SetPage(m_PetPage - 1);
		}
		return true;
	case 51://下翻
		if (_charactor->m_PcData.m_NumofBB > m_TPetName.size())
		{
			SetPage(m_PetPage + 1);
		}
		return true;
	case 60: //取消
		OnOff(false);
		return true;
	case 61://设置加点
		if (1)
		{
			if (g_StateType != STATE_MAIN)return true;
			cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
			cPetData* pPCData = &pPetSelect->m_PetData;
			if (_pointTemps[0] == pPCData->PointBody &&
				_pointTemps[1] == pPCData->PointMag &&
				_pointTemps[2] == pPCData->PointStr &&
				_pointTemps[3] == pPCData->PointDex &&
				_pointTemps[4] == pPCData->PointAgi)
			{
				return true;
			}

			if (_pointTemps[0] + _pointTemps[1] + _pointTemps[2] + _pointTemps[3] + _pointTemps[4] + _pointTemps[5] !=
				pPCData->PointBody + pPCData->PointMag + pPCData->PointStr + pPCData->PointDex + pPCData->PointAgi + pPCData->PointRemain)
			{
				return true;
			}
			m_framprep->SetFrame帧(1);
// 			if (m_TrueSelect > -1)
// 				m_bAddPoint = !m_bAddPoint;
// 			if (m_bAddPoint)
// 			{
// 				UpdatePointButton();
// 			}
// 			UpdateProPerty();
//
// 			pPCData->Atk.AddDataOriginal(-pPCData->CountATK());//伤害
// 			pPCData->Def.AddDataOriginal(-pPCData->CountDEF());//防
// 			pPCData->HPMax.AddDataOriginal(-pPCData->CountHP());//HP
// 			pPCData->MPMax.AddDataOriginal(-pPCData->CountMP());//MP
// 			pPCData->Mana.AddDataOriginal(-pPCData->CountWakan());//灵力
// 			pPCData->Speed.AddDataOriginal(-pPCData->CountSpd());//速度
// 			pPCData->Evade.AddDataOriginal(-pPCData->CountEvade());//躲闪
// 			pPCData->Hit.AddDataOriginal(-pPCData->CountHit());//命中
			pPCData->PointBody = _pointTemps[0];
			pPCData->PointStr = _pointTemps[2];
			pPCData->PointDex = _pointTemps[3];
			pPCData->PointMag = _pointTemps[1];
			pPCData->PointAgi = _pointTemps[4];
			pPCData->PointRemain = _pointTemps[5];
// 			pPCData->Atk.AddDataOriginal(pPCData->CountATK());//伤害
// 			pPCData->Def.AddDataOriginal(pPCData->CountDEF());//防
// 			pPCData->HPMax.AddDataOriginal(pPCData->CountHP());//HP
// 			pPCData->MPMax.AddDataOriginal(pPCData->CountMP());//MP
// 			pPCData->Mana.AddDataOriginal(pPCData->CountWakan());//灵力
// 			pPCData->Speed.AddDataOriginal(pPCData->CountSpd());//速度
// 			pPCData->Evade.AddDataOriginal(pPCData->CountEvade());//躲闪
// 			pPCData->Hit.AddDataOriginal(pPCData->CountHit());//命中
			pPCData->apply();
			pPCData->FillHpMp();
			UpDateByLvUp();
		}
		return true;
	case 10086:
		if (g_StateType != STATE_MAIN)return true;
		if (1)
		{
			m_framprep->SetFrame帧(1);
			cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
			cPropertyData* pPCData = &pPetSelect->m_PetData;
			int jj = pPCData->m_JinJieNum.m_JinJieNum;
			if (jj >= 3)
			{
				pPCData->m_JinJieNum.Reset();
			}
			else
			{
				pPCData->SetJinJie(1);
			}
			m_PetObj.Reset();
			m_PetObj.Set(POS_STAND);
			m_TPetProPerty[25].SetString(toString("进阶%d", pPetSelect->m_PetData.m_JinJieNum.m_JinJieNum));
		}
		return true;
	case 10010: // 染色
		if (g_StateType == STATE_MAIN)
		{
			g_pMainState->m_InterfaceRanSe.SetMode(4, _heroID);
			g_pMainState->m_InterfaceRanSe.OnOff(true);
		}
		return true;
	default:
		ERRBOX;
		break;
	}
	return true;
}

bool cInterfacePet::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_UpB.m_Picture.m_x = x + 122;
	m_UpB.m_Picture.m_y = y + 25;
	m_DownB.m_Picture.m_x = x + 122;
	m_DownB.m_Picture.m_y = y + 140;
	m_SetAttackB.m_Picture.m_x = m_xPos + 223;
	m_SetAttackB.m_Picture.m_y = m_yPos + 144;
	for (int i = 0; i < 5; i++)
	{
		m_AddPoint[i].m_Picture.m_x = m_xPos + 230;
		m_AddPoint[i].m_Picture.m_y = m_yPos + 215 + 25 * i;
		m_SubPoint[i].m_Picture.m_x = m_xPos + 250;
		m_SubPoint[i].m_Picture.m_y = m_yPos + 215 + 25 * i;
	}
	m_XunYang.m_Picture.m_x = m_xPos + 228/*175*/;
	m_XunYang.m_Picture.m_y = m_yPos + 362/*358*/;

	m_SetAddPoint.m_x = m_xPos + 228;
	m_SetAddPoint.m_y = m_yPos + 335;

	m_FreePet.m_Picture.m_x = m_xPos + 16;
	m_FreePet.m_Picture.m_y = m_yPos + 430;

	_btnJJ.m_x = m_xPos + 72;
	_btnJJ.m_y = m_yPos + 430;
	_btnJJ.m_x = m_xPos + 202;
	_btnJJ.m_y = m_yPos + 398;

	m_ChaKanZiZhi.m_Picture.m_x = m_xPos + 202;
	m_ChaKanZiZhi.m_Picture.m_y = m_yPos + 425;

	m_Back.SetXY(x, y);
	m_back.SetXY(m_xPos + 75, m_yPos + 430);
//	if (m_PetSkill.m_NeedShow)
	{
		m_PetSkill.Move(x + m_Back.GetWidth(), y);
	}
	m_Cancel.SetXY(m_Back.GetX() + 260, m_Back.GetY() + 5);
	m_PetObj.SetXY(m_xPos + 210, m_yPos + 120);
	m_PetObj.MoveShadow();
	/*for (int i = 0; i < 4; i++)
	{
	m_PetPic[i].m_Picture.m_x = m_xPos + 210;
	m_PetPic[i].m_Picture.m_y = m_yPos + 120;
	}
	m_Shadow.m_x = m_PetPic[0].m_Picture.m_x;
	m_Shadow.m_y = m_PetPic[0].m_Picture.m_y;*/
	forv(m_TPetName, i)
	{
		m_TPetName[i].SetXY(m_xPos + 15, m_yPos + 50 + i * s_yInv);
	}
	m_PetSelectBack[0].SetX(m_xPos + 10);
	m_PetSelectBack[1].SetX(m_xPos + 55);
	m_PetSelectBack[0].m_NeedShow = false;
	m_PetSelectBack[1].m_NeedShow = false;

	MovePetProPerty();
	return true;
}


bool cInterfacePet::SetPage(int page)
{
	if (page<0)page = 0;
	if ((page * m_TPetName.size()) >= _charactor->m_PcData.m_NumofBB)page -= 1;
	if (m_TrueSelect > -1)
		m_TPetName[m_TrueSelect - m_PetPage * m_TPetName.size()].SetColor(RGB(0, 0, 0));
	//m_TrueSelect = -1;
	m_PetPage = page;
	UpdateList(m_PetPage);
	if (m_PetPage < 0)
	{
		m_TrueSelect = -1;
		return true;
	}
//	m_TrueSelect = m_PetPage * m_TPetName.size();
	SelectPet(m_TrueSelect);
	if (m_PetPage <1)
		m_UpB.SetFrame(3);
	else
		m_UpB.SetFrame(0);

	if (m_PetPage>-1 && m_PetPage < (_charactor->m_PcData.m_NumofBB - 1) / m_TPetName.size())
		m_DownB.SetFrame(0);
	else
		m_DownB.SetFrame(3);

	RECT rect;
	rect.left = m_xPos + 15;
	rect.right = m_xPos + 120;
	rect.top = m_yPos + 45;
	rect.bottom = m_yPos + 160;
	g_pMainState->m_Canvas.SetRedraw(rect);

	m_Select = 0;
// 	if (m_TrueSelect == _charactor->m_PcData.m_FightPetID)
// 		m_SetAttackB.SetFrame(1);
// 	else  m_SetAttackB.SetFrame(0);
	return true;
}

bool cInterfacePet::MovePetProPerty()
{
	m_TPetProPerty[25].SetXY(m_xPos + 202 + 12, m_yPos + 401);

	m_TPetProPerty[24].SetXCenter(m_SetAddPoint.GetCenter());
	m_TPetProPerty[24].UpdateXCenter();
	m_TPetProPerty[24].SetY(m_SetAddPoint.GetY() + 3);

	m_TPetProPerty[20].SetXCenter(m_XunYang.GetCenter());
	m_TPetProPerty[20].UpdateXCenter();
	m_TPetProPerty[20].SetY(m_XunYang.GetY() + 3);

	m_TPetProPerty[23].SetXY(m_xPos + 185 + 22, m_yPos + 432);
	m_TPetProPerty[22].SetXY(m_xPos + 20, m_yPos + 432);
//	m_TPetProPerty[21].SetXY(m_xPos + 70, m_yPos + 432);
	const auto& t = m_TPetName[abs(_charactor->m_PcData.m_FightPetID) % _charactor->m_PcData.m_pPets.size()];
	m_TPetProPerty[21].SetXY(t.m_x + 95, t.m_y);
//	m_TPetProPerty[20].SetXY(m_xPos + 180, m_yPos + 362);
	int yinv = -1;
	m_TPetProPerty[19].SetXY(m_xPos + 228, m_yPos + 147);
	m_TPetProPerty[18].SetXY(m_xPos + 85, m_yPos + 170);
	m_TPetProPerty[17].SetXY(m_xPos + 215, m_yPos + 170);
	m_TPetProPerty[16].SetXY(m_xPos + 50, m_yPos + 410 - 2);
	m_TPetProPerty[15].SetXY(m_xPos + 90, m_yPos + 386 - 2);
	m_TPetProPerty[14].SetXY(m_xPos + 90, m_yPos + 362 - 2);
	m_TPetProPerty[13].SetXY(m_xPos + 180, m_yPos + 338 + yinv);
	m_TPetProPerty[12].SetXY(m_xPos + 180, m_yPos + 314 + yinv);
	m_TPetProPerty[11].SetXY(m_xPos + 180, m_yPos + 290 + yinv);
	m_TPetProPerty[10].SetXY(m_xPos + 180, m_yPos + 266 + yinv);
	m_TPetProPerty[9].SetXY(m_xPos + 180, m_yPos + 242 + yinv);
	m_TPetProPerty[8].SetXY(m_xPos + 180, m_yPos + 218 + yinv);
	m_TPetProPerty[7].SetXY(m_xPos + 50, m_yPos + 338 + yinv);
	m_TPetProPerty[6].SetXY(m_xPos + 50, m_yPos + 314 + yinv);
	m_TPetProPerty[5].SetXY(m_xPos + 50, m_yPos + 290 + yinv);
	m_TPetProPerty[4].SetXY(m_xPos + 50, m_yPos + 266 + yinv);
	m_TPetProPerty[3].SetXY(m_xPos + 50, m_yPos + 242 + yinv);
	m_TPetProPerty[0].SetXY(m_xPos + 180, m_yPos + 147 + yinv);
	m_TPetProPerty[1].SetXY(m_xPos + 50, m_yPos + 194 + yinv);
	m_TPetProPerty[2].SetXY(m_xPos + 50, m_yPos + 218 + yinv);
	return true;
}



cInterfacePet::~cInterfacePet()
{
	Free();
}

bool cInterfacePet::Free()
{
	m_PetObj.m_IndexType = 0;
	m_PetObj.m_pIndex = 0;
	/*for (int i = 0; i < 4; i++)
	m_PetPic[i].Free();*/
	return true;
}



void cInterfacePet::OnOff(bool NeedShow)
{
	if (NeedShow == m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);

	if (NeedShow)
	{
		m_Sleeptime = 0;
		Init();
		SetPage(m_PetPage);
		SelectPet(m_TrueSelect);
		// 		m_SetAddPoint.m_NeedShow = (g_StateType != STATE_FIGHT);
		// 		m_FreePet.m_NeedShow = (g_StateType != STATE_FIGHT);
		// 		m_SetAttackB.m_NeedShow = (g_StateType != STATE_FIGHT);
	}
	else
	{
		m_PetObj.m_pIndex = 0;
		cct::autoSave();
	}
	g_pMainState->m_Canvas.SetRedraw(m_PetSkill.m_Back.m_PreShowRect);
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}

bool cInterfacePet::ProcessFreePet()
{
	switch (g_pMainState->m_Dialog.m_retSelect)
	{
	case 0:
		m_FreePetMode = false;
		if (0 == g_pMainState->m_Dialog.m_NowMouseOnSelect)
		{
			int& id = _charactor->m_PcData.m_FightPetID;
			if (m_TrueSelect == id)
			{
				g_pMainState->SetFightPet(_heroID, -1);  //先召还
			}
			_charactor->m_PcData.RemovePet(m_TrueSelect);
			if (id >= 0 && m_TrueSelect < id)
			{
				--id;
			}
			g_pMainState->m_PCHead.m_pPet = 0;
			g_pMainState->m_PCHead.UpdatePet();
			SetPage(m_PetPage);
			SelectPet(0);
// 			if (!_charactor->m_PcData.m_NumofBB)
// 			{
// 				OnOff(false);
// 			}
		}
		g_pMainState->m_Dialog.m_NeedShow = false;
		break;
 	case 1:
		m_FreePetMode = false;
		if (1 == g_pMainState->m_Dialog.m_NowMouseOnSelect)
		{
			int& id = _charactor->m_PcData.m_FightPetID;
			if (m_TrueSelect == id)
			{
				g_pMainState->SetFightPet(_heroID, -1);  //先召还
			}
			_charactor->m_PcData.RemovePet(m_TrueSelect, true);   
			if (id >= 0 && m_TrueSelect < id)
			{
				--id;
			}
			g_pMainState->m_PCHead.m_pPet = 0;
			g_pMainState->m_PCHead.UpdatePet();
			SetPage(m_PetPage);
			SelectPet(0);
		}
		g_pMainState->m_Dialog.m_NeedShow = false;
		break;
// 	case 5:
// 		m_FreePetMode = false;
// 		break;
	default:
		m_FreePetMode = false;
		break;
	}
	return true;
}

void cInterfacePet::UpDateExp()
{
	ostringstream oss;
	oss << _charactor->m_PcData.m_pPets[m_TrueSelect]->m_PetData.m_EXP;
	m_TPetProPerty[14].SetString(oss.str());
}

void cInterfacePet::UpDateByLvUp()
{
	if (m_TrueSelect<0)return;
	cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
	if (!pPetSelect)return;
	ostringstream oss;
	cPetData&  petzz = pPetSelect->m_PetData;
	oss << petzz.m_Lv;
	m_TPetProPerty[0].SetString(oss.str());
	oss.str("");
	oss << petzz.m_Name;
	m_TPetProPerty[1].SetString(oss.str());
	oss.str("");
	oss << petzz.m_HP << "/" << pPetSelect->m_PetData.HPMax.GetData();
	m_TPetProPerty[2].SetString(oss.str());
	oss.str("");
	oss << petzz.m_MP << "/" << pPetSelect->m_PetData.MPMax.GetData();
	m_TPetProPerty[3].SetString(oss.str());
	oss.str("");
	oss << petzz.Atk.GetData();
	m_TPetProPerty[4].SetString(oss.str());
	oss.str("");
	oss << petzz.Def.GetData();
	m_TPetProPerty[5].SetString(oss.str());
	oss.str("");
	oss << petzz.Speed.GetData();
	m_TPetProPerty[6].SetString(oss.str());
	oss.str("");
	oss << petzz.Mana.GetData();
	m_TPetProPerty[7].SetString(oss.str());
	oss.str("");
	UpdateProPerty();
	UpDateExp();

	oss << GetPetExp(petzz.m_Lv + 1);
	m_TPetProPerty[15].SetString(oss.str());
	oss.str("");
	oss << 100;
	m_TPetProPerty[16].SetString(oss.str());
	//参战等级
	oss.str("");
	oss << pPetSelect->GetData()->m_LvTake;
	m_TPetProPerty[17].SetString(oss.str());
	//召唤兽数
	oss.str("");
	oss << _charactor->m_PcData.m_NumofBB << "/" << m_TPetName.size();
	m_TPetProPerty[18].SetString(oss.str());

	if (m_PetSkill.m_NeedShow)
	{
		m_PetSkill.UpdateData(&petzz, true);
	}
}

bool cInterfacePet::SelectPet(int id)
{
	int pre = m_TrueSelect - m_PetPage * m_TPetName.size();
	if (pre > -1 && pre< m_TPetName.size())
		m_TPetName[pre].SetColor(RGB(0, 0, 0));
	m_TrueSelect = id;
	int pageid = id - m_PetPage * m_TPetName.size();
	if (pageid<0 || pageid>=m_TPetName.size())
	{
		m_TrueSelect = m_PetPage * m_TPetName.size();
	}

	if (pageid < 0)return false;
	if (pageid >= m_TPetName.size())
	{
		return false;
	}
	m_TPetName[pageid].SetColor(RGB(255, 255, 0));

	if (m_TrueSelect < 0)
	{
		for (int i = 0; i < 5; i++)
		{
			m_AddPoint[i].SetFrame(3);
			m_SubPoint[i].SetFrame(3);
		}
		UpDateByLvUp();
		Free();
		m_PetSkill.UpdateData(0, true);
	}
	else
	{
		if (_charactor->m_PcData.m_NumofBB <= m_TrueSelect)return false;
		cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
		//vector<ulong> out;
		//pPetSelect->GetID(POS_STAND, out);
		m_PetObj.m_pIndex = pPetSelect;
		m_PetObj.m_IndexType = INDEXTYEP_PET;
		m_PetObj.Reset();
		m_PetObj.Set(POS_STAND);

		pPetSelect->m_PetData.apply();
		/*for (int i = 0; i < 4; i++)
		{
		m_PetPic[i].m_NeedShow = false;
		}
		for (int i = 0; i < out.size(); i++)
		{
		m_PetPic[i].Load(out[i]);
		m_PetPic[i].m_Picture.m_direction = 3;
		m_PetPic[i].m_NeedShow = true;
		}*/
		//更新技能
		//if (m_PetSkill.m_NeedShow)m_PetSkill.UpdateData(&pPetSelect->m_PetDataZZ,true);
		//检测加点是否可用

		setPointTemps();

		UpdatePointButton();
		UpDateByLvUp();
		m_PetSkill.UpdateData(&pPetSelect->m_PetData, true);
		m_TPetProPerty[25].SetString(toString("进阶%d", pPetSelect->m_PetData.m_JinJieNum.m_JinJieNum));
		m_TPetProPerty[19].SetString((m_TrueSelect >= 0 && _charactor->m_PcData.m_FightPetID == m_TrueSelect) ? "休息" : "参战");
	}

// 	if (m_TrueSelect == _charactor->m_PcData.m_FightPetID)
// 		m_SetAttackB.SetFrame(1);
// 	else  m_SetAttackB.SetFrame(0);


	return true;
}

void cInterfacePet::UpdateList(int page)
{
	if (page<0)
	{
		forr (m_TPetName, i)
			m_TPetName[i].SetString("");
		return;
	}
	int num2 = _charactor->m_PcData.m_NumofBB - m_PetPage *  m_TPetName.size();
	if (num2 > m_TPetName.size())num2 = m_TPetName.size();
	for (int i = 0; i < num2; i++)
		m_TPetName[i].SetString(_charactor->m_PcData.m_pPets[i + m_PetPage * m_TPetName.size()]->m_PetData.m_Name);
}

void cInterfacePet::AddExp(cPropertyData* pPetSelect, int num)
{//给召唤兽增加经验
	pPetSelect->m_EXP += num;
	int prelv = pPetSelect->m_Lv;
	g_pMainState->m_pFightState->CheckPetExp();
	if (prelv != pPetSelect->m_Lv)
	{
		UpDateByLvUp();
	}
	else
		UpDateExp();
	g_pMainState->m_PCHead.UpdatePet();

}

void cInterfacePet::UpdatePointButton()
{
	if (m_bAddPoint || 1)
	{
		cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
//		sAddPoint& addpoint = pPetSelect->m_PetData.m_AddPoint;
		int per加点 = s_perPoint; // ccm::get()->per加点;
		for (int i = 0; i < 5; i++)
		{
			if (_pointTemps[5] < per加点)
				m_AddPoint[i].SetFrame(3);
			else
				m_AddPoint[i].SetFrame(0);
			m_SubPoint[i].SetFrame(0);
		}

		if (_pointTemps[0] < per加点)m_SubPoint[0].SetFrame(3);
		if (_pointTemps[1] < per加点)m_SubPoint[1].SetFrame(3);
		if (_pointTemps[2] < per加点)m_SubPoint[2].SetFrame(3);
		if (_pointTemps[3] < per加点)m_SubPoint[3].SetFrame(3);
		if (_pointTemps[4] < per加点)m_SubPoint[4].SetFrame(3);
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			m_SubPoint[i].SetFrame(3);
			m_AddPoint[i].SetFrame(3);
		}
	}
}

void cInterfacePet::UpdateProPerty()
{
	cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
	ostringstream oss;
	cPetData& petzz = pPetSelect->m_PetData;
	if (m_bAddPoint)
	{
// 		oss << petzz.m_AddPoint.body;
// 		m_TPetProPerty[8].SetString(oss.str());
// 		oss.str("");
// 		oss << petzz.m_AddPoint.mag;
// 		m_TPetProPerty[9].SetString(oss.str());
// 		oss.str("");
// 		oss << petzz.m_AddPoint.str;
// 		m_TPetProPerty[10].SetString(oss.str());
// 		oss.str("");
// 		oss << petzz.m_AddPoint.dex;
// 		m_TPetProPerty[11].SetString(oss.str());
// 		oss.str("");
// 		oss << petzz.m_AddPoint.agi;
// 		m_TPetProPerty[12].SetString(oss.str());
// 		oss.str("");
// 		oss << petzz.m_AddPoint.remain;
// 		m_TPetProPerty[13].SetString(oss.str());
// 		oss.str("");
	}
	else
	{
		oss << petzz.PointBody;
		m_TPetProPerty[8].SetString(oss.str());
		oss.str("");
		oss << petzz.PointMag;
		m_TPetProPerty[9].SetString(oss.str());
		oss.str("");
		oss << petzz.PointStr;
		m_TPetProPerty[10].SetString(oss.str());
		oss.str("");
		oss << petzz.PointDex;
		m_TPetProPerty[11].SetString(oss.str());
		oss.str("");
		oss << petzz.PointAgi;
		m_TPetProPerty[12].SetString(oss.str());
		oss.str("");
		oss << petzz.PointRemain;
		m_TPetProPerty[13].SetString(oss.str());
		//		m_TPetProPerty[13].SetString("0");
		oss.str("");
	}
}

cInterfacePet::cInterfacePet(){ _charactor = g_pCharacter; }

void cInterfacePet::setCharactor(int id /* = -1 */)
{
	if (id != -1)
	{
		_heroID = id;
		_charactor = (cCharacter*)g_pMainState->m_FightWorkList[id].m_pObj->m_pIndex;
	}
	else
	{
		_heroID = g_pMainState->m_HeroID;
		_charactor = g_pCharacter;
	}
}

void cInterfacePet::setPointTemps()
{
	cPet* pPetSelect = _charactor->m_PcData.m_pPets[m_TrueSelect];
	cPropertyData* pPCData = &pPetSelect->m_PetData;
	_pointTemps =
	{ pPCData->PointBody,
	pPCData->PointMag,
	pPCData->PointStr,
	pPCData->PointDex,
	pPCData->PointAgi,
	pPCData->PointRemain
	};
}

