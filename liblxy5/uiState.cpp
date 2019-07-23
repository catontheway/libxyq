#include "_global.h"


static int s_perPoint = 1;
bool cState::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Addp.resize(5);
	m_Subp.resize(5);
//	m_TPcFnt.resize(35);
	m_PetSkill.Init();
	m_TSkillHeadSelectDate[0].SetColor(RGB(255, 255, 0));
	m_TSkillHeadSelectDate[1].SetColor(RGB(0, 255, 0));
	for (int i = 0; i < 24; i++)
		m_TPcFnt[i].SetColor(RGB(0, 0, 0));
	for (int i = 24; i < m_TPcFnt.size(); i++)
		m_TPcFnt[i].SetColor(RGB(230, 230, 230));
	m_TPcFnt[27].SetColor(RGB(0, 0, 0));
	m_TPcFnt[28].SetColor(RGB(0, 0, 0));
	m_TPcFnt[29].SetColor(RGB(0, 0, 0));


	m_TSkillHeadSelectDate[0].SetColor(RGB(255, 255, 0));
	m_TSkillHeadSelectDate[1].SetColor(RGB(0, 255, 0));

	for (int i = 0; i < 9; i++) 
		m_TPetDate[i].SetColor(RGB(0, 0, 0));
	m_frampre = 0;
	m_SkillPage = 0;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_LeveUp.Load(0x9B3AF4E5);
	ccm::get()->pushWdf("升级", 0x9B3AF4E5);
	m_Sub.Load(1577923263);
	ccm::get()->pushWdf("按钮加", 1577923263);
	m_Add.Load(3296232902);
	ccm::get()->pushWdf("按钮减", 3296232902);
	m_State.Load(0xA16FD45C);
	ccm::get()->pushWdf("属性面板", 0xA16FD45C);
	m_ButtonLvUp.Set(&g_pMainState->m_Button2);
	m_ButtonLvDown.Set(&g_pMainState->m_Button2);
	m_PointSpeed.Set(&g_pMainState->m_Button2);
	m_ButtonSkill.Set(&g_pMainState->m_Button2);
	m_SeeZZ.Set(&g_pMainState->m_Button2);
	m_Sub.SetStatic(true);
	m_Add.SetStatic(true);
	m_ButtonLvUp.m_bStatic = true;
	m_ButtonLvDown.m_bStatic = true;
	m_PointSpeed.m_bStatic = true;
	m_ButtonSkill.m_bStatic = true;
	m_State.SetStatic(true);
	m_SeeZZ.m_bStatic = true;
	for (int i = 0; i < 5; i++)
	{
		m_Addp[i].Set(&m_Add);
		m_Subp[i].Set(&m_Sub);
		m_Addp[i].m_bStatic = true;
		m_Subp[i].m_bStatic = true;
	}

	forr(_btns, i)
	{
		_btns[i].Set(&g_pMainState->m_Button2);
		_btns[i].m_bStatic = true;
		_tBtns[i].SetColor(RGB(230, 230, 230));
		_tBtns[i].SetString("空");
	}
	_tBtns[0].SetString("酒肆");
	_tBtns[1].SetString("巫医");
	//	m_TPcFnt[24].SetString( _cC == g_pCharacter ? "升级" : "退队");
	m_TPcFnt[25].SetString("技能");
	m_TPcFnt[26].SetString("确定");
	m_TPcFnt[30].SetString("降级");
	m_TPcFnt[31].SetString(toString("*%d", s_perPoint/*ccm::get()->per加点*/));

	for (int i = 0; i < 12; i++)
		m_SkillHead[i].SetStatic(true);

	Move(384 + g_640 - 640, 0 + 50);
//	m_PetSkill.m_NeedShow = false;
	return true;
}

bool cState::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	if (!m_pPCData)return false;
	pCanvas->Add(&m_State, 1, true);
	pCanvas->Add(&m_Cancel, 1);

	for (int i = 0; i < 5; i++)
	{
		pCanvas->Add(&m_Addp[i], 1);
		pCanvas->Add(&m_Subp[i], 1);
	}
	pCanvas->Add(&m_ButtonLvUp, 1);
	pCanvas->Add(&m_ButtonLvDown, 1);
	pCanvas->Add(&m_PointSpeed, 1);
	pCanvas->Add(&m_ButtonSkill, 1);
	pCanvas->Add(&m_SeeZZ, 1);

	forr(m_TPcFnt, i)
	{
		pCanvas->Add(&m_TPcFnt[i]);
	}

	forr(_btns, i)
	{
		break;
		pCanvas->Add(&_btns[i], 1);
		pCanvas->Add(&_tBtns[i], 1);
	}
	//资质界面滑动效果
	if (m_PetSkill.m_NeedShow)
		m_PetSkill.Show(pCanvas);
	return true;
}

bool cState::SetCharacter(cCharacter* pc)
{
	_cC = pc;
	if (!m_bInit)Init();
	m_pPCData = &pc->m_PcData;
	_pointTemps =
	{
		m_pPCData->PointBody,
		m_pPCData->PointMag,
		m_pPCData->PointStr,
		m_pPCData->PointDex,
		m_pPCData->PointAgi,
		m_pPCData->PointRemain
	};
	UpDatePcDate();
	return true;
}

bool cState::ProcessInput()
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
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	ResetButton();
	if (isOn(g_xMouse, g_yMouse, m_State.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);
		if (CheckOn(&m_Cancel, 0))return true;
		if (CheckOn(&m_ButtonLvUp, 1))return true;
		if (CheckOn(&m_ButtonLvDown, 2))return true;
		if (CheckOn(&m_ButtonSkill, 3))return true;
		if (CheckOn(&m_SeeZZ, 4))return true;
		if (CheckOn(&m_PointSpeed, 5))return true;
		for (int i = 0; i < 5; i++)
		{
			if (3 == m_Addp[i].GetFrame())continue;//灰色的按钮不处理
			if (CheckOn(&m_Addp[i], 10 + i))return true;
		}
		for (int i = 0; i < 5; i++)
		{
			if (3 == m_Subp[i].GetFrame())continue;//灰色的按钮不处理
			if (CheckOn(&m_Subp[i], 20 + i))return true;
		}
		forr(_btns, i)
		{
			if (CheckOn(&_btns[i], 30 + i))return true;
		}
		if (CheckRB())return true;
		m_Select = 7;
		CheckL();
	}
	//鼠标是否在资质介面上

	m_PetSkill.ProcessInput();

	return true;
}

bool cState::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	ostringstream oss;
	switch (m_Select)
	{
	case 0://关闭
		OnOff(false);
		m_Cancel.SetFrame帧(1);
		return true;
	case 1:  //升级
		if (1)
		{
			if (g_StateType != STATE_MAIN)return true;
// 			if (_cC != g_pCharacter)
// 			{
// 				g_pMainState->m_Friend.UnInvite(_cC->GetName());
// 				OnOff(false);
// 				return true;
// 			}

			if (m_pPCData->m_Lv >= cct::MaxRoleLv)
			{
				g_pMainState->m_Tags.Add("等级已满");
				return false;
			}

			int limitlv = g_pMainState->GetLockLv上限();
			int perlvup = 1; // cct::get()->perLvup = (g_pCharacter->m_PcData.m_Lv % 10 == 9) ? 6 : 4;
			// 			if (m_pPCData->m_Lv + perlvup > cct::get()->maxRoleLv)
			// 			{
			// 				perlvup = cct::get()->maxRoleLv - m_pPCData->m_Lv;
			// 			}

			if (limitlv < m_pPCData->m_Lv + perlvup)
			{
				if (limitlv == cct::LvFor飞升)
				{
					g_pMainState->m_Tags.Add("未飞升");
				}
				else if (limitlv == cct::LvFor渡劫)
				{
					g_pMainState->m_Tags.Add("未渡劫");
				}
				else
				{
					g_pMainState->m_Tags.Add("已达当前等级上限");
				}
				
				g_pMainState->m_Triggerlv.Process();
				return false;
			}



			auto expMax = GetCharacterExp(m_pPCData->m_Lv + perlvup); //m_pPCData->m_ExpMax;
			if (m_pPCData->m_EXP < expMax)
			{
				g_pMainState->m_Tags.Add("经验不足");
				return false;
			}
			// 			if (m_AddPoint.idle未分配点数)
			// 			{
			// 				g_pMainState->m_Tags.Add("加点方式未设置");
			// 				return false;
			// 			}


			// 			if (g_pCharacter->m_PCData.m_MengPaiID < 0 && m_pPCData->m_Lv >= limitlv - cct::get()->perLvup)
			// 			{
			// 				g_pMainState->m_Tags.Add("未拜入门派,暂时无法升级");
			// 				return false;
			// 			}

			for (int i = 0; i < perlvup; ++i)
			{
				if (m_pPCData->lvup())
				{
					g_pMainState->m_Triggerlv.Process();
				}
				else
				{
					return true;
				}
			}
// 			if (!m_pPCData->LeveUp(perlvup, false, false))
// 			{
// 				g_pMainState->m_Triggerlv.Process();
// 				return true;
// 			}
// 			m_pPCData->FullFuzhuBut暗器();
// 			m_pPCData->FollowEuip();
// 			m_pPCData->FollowXiulian();
// 			m_pPCData->FollowItem();
// 			m_pPCData->FollowSkill();
// 			m_pPCData->FollowBaby();
// 
// 			if (_cC == g_pCharacter)
// 			{
// 				m_pPCData->m_EXP -= expMax;
// 				if (m_pPCData->m_EXP < 0)
// 				{
// 					m_pPCData->m_EXP = 0;
// 				}
// 				// 				g_pMainState->m_Tags.Add("装备几乎铺满了某个包裹");
// 				// 				m_pPCData->FollowEquipAll();
// 				m_pPCData->FollowSkill();
// 			}

			_pointTemps =
			{ m_pPCData->PointBody,
			m_pPCData->PointMag,
			m_pPCData->PointStr,
			m_pPCData->PointDex,
			m_pPCData->PointAgi,
			m_pPCData->PointRemain
			};

//			g_pCharacter->m_PcData.Add人气(5 * cct::get()->perLvup);//升1级加5点人气
			g_pMainState->m_Triggerlv.Process();
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0x02EF9247);
			ccm::get()->pushWdf("声音升级", 0x02EF9247);
			UpDatePcDate();
//			pObj->SetMagicEffectFromItem(&m_LeveUp, -10, 2);
			m_ButtonLvUp.SetFrame帧(1);
			m_ButtonLvUp.m_bMove = true;
//			m_pPCData->FillHPMP();
			m_pPCData->apply();
			
			g_pMainState->m_PCHead.UpDateHead();
			g_pMainState->m_PCHead.UpdatePcHp();
			g_pMainState->m_PCHead.UpdatePcMp();
			g_pMainState->m_PCHead.UpdatePcExp();
			m_isNeedLvupOfFriend = true;

			for (int i = 0; i < 5; i++)
			{
				m_Addp[i].SetFrame帧(0);
				m_Addp[i].m_bMove = true;
			}
		}
		return true;
	case 2: // 降级
		if (g_StateType == STATE_MAIN)
		{
			forr(m_pPCData->m_Equips, i)
			{
				if (m_pPCData->m_Equips[i].GetNum() > 0)
				{
					g_pMainState->m_Tags.Add("请裸身");
					return true;
				}
			}
			if (!m_pPCData->lvdown())
			{
				return true;
			}

			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0x02EF9247);
			m_pPCData->m_XiuLian.lvdown(cct::getCurrMaxXiulianLv(m_pPCData->m_Lv));
			m_pPCData->m_XiuLianBB.lvdown(cct::getCurrMaxXiulianLv(m_pPCData->m_Lv));

			if (1)
			{
				int& lv = m_pPCData->m_MengPaiSkillLvs[0];
				while (lv > m_pPCData->m_Lv + cct::LvGapFromRoleAndSkill)
				{
					m_pPCData->m_EXP += GetMainSkillExp(lv);
					m_pPCData->m_Money[0] += GetMainSkillMoney(lv);
					forr(m_pPCData->m_MengPaiSkillLvs, i)
					{
						--m_pPCData->m_MengPaiSkillLvs[i];
					}
				}
			}
			if (m_pPCData->m_FightPetID >= 0)
			{
				auto p = m_pPCData->m_pPets[m_pPCData->m_FightPetID];
				if (p->m_PetData.m_Lv > m_pPCData->m_Lv + cct::LvGapFromRoleAndBaby || p->GetData()->m_LvTake > m_pPCData->m_Lv)
				{
					g_pMainState->SetFightPet(m_pPCData->m_IDinFightWorkList, -1);
				}
			}
			m_pPCData->apply();
			m_pPCData->FillHpMp();
			_pointTemps =
			{ m_pPCData->PointBody,
			m_pPCData->PointMag,
			m_pPCData->PointStr,
			m_pPCData->PointDex,
			m_pPCData->PointAgi,
			m_pPCData->PointRemain
			};

			g_pMainState->m_PCHead.UpDateHead();
			UpDatePcDate();
			UpdateProPerty();
		}
		return true;
	case 3: // 查看技能
		if (1)
		{
			OnOff(false);
			g_pMainState->m_InterfaceJiNeng.setCharator(_cC);
			g_pMainState->m_InterfaceJiNeng.OnOff(true);

		}
		return true;
	case 4://查看资质 呵呵哒/确认加点
		if (g_StateType != STATE_MAIN)return true;
		if (_pointTemps[0] == m_pPCData->PointBody &&
			_pointTemps[1] == m_pPCData->PointMag &&
			_pointTemps[2] == m_pPCData->PointStr &&
			_pointTemps[3] == m_pPCData->PointDex &&
			_pointTemps[4] == m_pPCData->PointAgi)
		{
			return true;
		}

		if (_pointTemps[0] + _pointTemps[1] + _pointTemps[2] + _pointTemps[3] + _pointTemps[4] + _pointTemps[5] !=
			m_pPCData->PointBody + m_pPCData->PointMag + m_pPCData->PointStr + m_pPCData->PointDex + m_pPCData->PointAgi + m_pPCData->PointRemain)
		{
			return true;
		}

		if (m_PetSkill.m_NeedShow)
		{
			m_SeeZZ.SetFrame帧(0);
		}
		else
		{
			m_SeeZZ.SetFrame帧(1);
//			m_PetSkill.UpdateData(m_pPCData, false);
		}
//		m_PetSkill.OnOff(!m_PetSkill.m_NeedShow);
		m_frampre = 0;
		{
// 			m_pPCData->Atk.AddDataOriginal(-m_pPCData->CountATK());//伤害
// 			m_pPCData->Def.AddDataOriginal(-m_pPCData->CountDEF());//防
// 			m_pPCData->HPMax.AddDataOriginal(-m_pPCData->CountHP());//HP
// 			m_pPCData->MPMax.AddDataOriginal(-m_pPCData->CountMP());//MP
// 			m_pPCData->Mana.AddDataOriginal(-m_pPCData->CountWakan());//灵力
// 			m_pPCData->Speed.AddDataOriginal(-m_pPCData->CountSpd());//速度
// 			m_pPCData->Evade.AddDataOriginal(-m_pPCData->CountEvade());//躲闪
// 			m_pPCData->Hit.AddDataOriginal(-m_pPCData->CountHit());//命中

			m_pPCData->PointBody = _pointTemps[0];
			m_pPCData->PointMag = _pointTemps[1];
			m_pPCData->PointStr = _pointTemps[2];
			m_pPCData->PointDex = _pointTemps[3];
			m_pPCData->PointAgi = _pointTemps[4];
			m_pPCData->PointRemain = _pointTemps[5];



			//计算新属性
// 			m_pPCData->Atk.AddDataOriginal(m_pPCData->CountATK());//伤害
// 			m_pPCData->Def.AddDataOriginal(m_pPCData->CountDEF());//防
// 			m_pPCData->HPMax.AddDataOriginal(m_pPCData->CountHP());//HP
// 			m_pPCData->MPMax.AddDataOriginal(m_pPCData->CountMP());//MP
// 			m_pPCData->Mana.AddDataOriginal(m_pPCData->CountWakan());//灵力
// 			m_pPCData->Speed.AddDataOriginal(m_pPCData->CountSpd());//速度
// 			m_pPCData->Evade.AddDataOriginal(m_pPCData->CountEvade());//躲闪
// 			m_pPCData->Hit.AddDataOriginal(m_pPCData->CountHit());//命中

			m_pPCData->apply();
			m_pPCData->FillHpMp();
			UpDatePcDate();
		}
		return true;
	case 5: // 加点速度
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
		m_TPcFnt[31].SetString(toString("*%d", per));
	}
		return true;
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
		//加点
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		if (1)
		{
			//			if (0 == m_pPCData->m_AddPoint.idle未分配点数)return true;
			int per加点 = s_perPoint; // ccm::get()->per加点;
			if (_pointTemps[5] < per加点)return true;
			switch (m_Select)
			{
			case 10:
				m_Addp[0].SetFrame帧(1);
				//				m_pPCData->m_AddPoint.hp += 1;
				_pointTemps[0] += per加点;
				if (m_Addp[0].GetFrame() == 1)
				{
					m_Subp[0].SetFrame帧(0);
					m_Subp[0].m_bMove = true;
				}
				break;
			case 11:
				m_Addp[1].SetFrame帧(1);
				//				m_pPCData->m_AddPoint.mp += 1;
				_pointTemps[1] += per加点;
				if (m_Addp[1].GetFrame() == 1)
				{
					m_Subp[1].SetFrame帧(0);
					m_Subp[1].m_bMove = true;
				}
				break;
			case 12:
				m_Addp[2].SetFrame帧(1);
				//				m_pPCData->m_AddPoint.atk += 1;		
				_pointTemps[2] += per加点;
				if (m_Addp[2].GetFrame() == 1)
				{
					m_Subp[2].SetFrame帧(0);
					m_Subp[2].m_bMove = true;
				}
				break;
			case 13:
				m_Addp[3].SetFrame帧(1);
				//				m_pPCData->m_AddPoint.def += 1;
				_pointTemps[3] += per加点;
				if (m_Addp[3].GetFrame() == 1)
				{
					m_Subp[3].SetFrame帧(0);
					m_Subp[3].m_bMove = true;
				}
				break;
			case 14:
				m_Addp[4].SetFrame帧(1);
				//				m_pPCData->m_AddPoint.spd += 1;
				_pointTemps[4] += per加点;
				if (m_Addp[4].GetFrame() == 1)
				{
					m_Subp[4].SetFrame帧(0);
					m_Subp[4].m_bMove = true;
				}
				break;
			}
			//			m_pPCData->m_AddPoint.idle未分配点数  -= 1;
			//			if (0 == m_pPCData->m_AddPoint.idle未分配点数 )
			if ((_pointTemps[5] -= per加点) < per加点)
			{
				for (int i = 0; i < 5; i++)
				{
					m_Addp[i].SetFrame帧(3);
					m_Addp[i].m_bMove = true;
				}
			}
			UpdateProPerty();
		}
		return true;
		//减点
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
		if (1)
		{
			int per加点 = s_perPoint; // ccm::get()->per加点;
			switch (m_Select)
			{
			case 20:
				// 呵呵哒 不得少于基本+装备(敏捷/临时)
				//				if (0 == m_pPCData->m_AddPoint.hp )return true;
				//				m_pPCData->m_AddPoint.hp -= 1;
				if (_pointTemps[0] - per加点 < m_pPCData->m_Lv/* + m_pPCData->PointBody2*/ + cct::MinPoint)return true;
				_pointTemps[0] -= per加点;
				m_Subp[0].SetFrame帧(1);
				//				if (0 == m_pPCData->m_AddPoint.hp)
				if (_pointTemps[0] <= m_pPCData->m_Lv)
				{
					m_Subp[0].SetFrame帧(3);
					m_Subp[0].m_bMove = true;
				}
				break;
			case 21:
				//				if (0 == m_pPCData->m_AddPoint.mp)return true;
				//				m_pPCData->m_AddPoint.mp -= 1;
				if (_pointTemps[1] - per加点 < m_pPCData->m_Lv/* + m_pPCData->PointMag2*/ + cct::MinPoint)return true;
				_pointTemps[1] -= per加点;
				m_Subp[1].SetFrame帧(1);
				//				if (0 == m_pPCData->m_AddPoint.mp)
				if (_pointTemps[1] <= m_pPCData->m_Lv)
				{
					m_Subp[1].SetFrame帧(3);
					m_Subp[1].m_bMove = true;
				}
				break;
			case 22:
				//				if (0 == m_pPCData->m_AddPoint.atk)return true;
				//				m_pPCData->m_AddPoint.atk -= 1;
				if (_pointTemps[2] - per加点 < m_pPCData->m_Lv/* + m_pPCData->PointStr2*/ + cct::MinPoint)return true;
				_pointTemps[2] -= per加点;
				m_Subp[2].SetFrame帧(1);
				//				if (0 == m_pPCData->m_AddPoint.atk)
				if (_pointTemps[2] <= m_pPCData->m_Lv)
				{
					m_Subp[2].SetFrame帧(3);
					m_Subp[2].m_bMove = true;
				}
				break;
			case 23:
				//				if (0 == m_pPCData->m_AddPoint.def)return true;
				//				m_pPCData->m_AddPoint.def -= 1;
				if (_pointTemps[3] - per加点 < m_pPCData->m_Lv/* + m_pPCData->PointDex2*/ + cct::MinPoint)return true;
				_pointTemps[3] -= per加点;
				m_Subp[3].SetFrame帧(1);
				//				if (0 == m_pPCData->m_AddPoint.def)
				if (_pointTemps[3] <= m_pPCData->m_Lv)
				{
					m_Subp[3].SetFrame帧(3);
					m_Subp[3].m_bMove = true;
				}
				break;
			case 24:
				//				if (0 == m_pPCData->m_AddPoint.spd)return true;
				//				m_pPCData->m_AddPoint.spd -= 1;
				if (_pointTemps[4] - per加点 < m_pPCData->m_Lv/* + m_pPCData->PointAgi2*/ + cct::MinPoint)return true;
				_pointTemps[4] -= per加点;
				m_Subp[4].SetFrame帧(1);
				//				if (0 == m_pPCData->m_AddPoint.spd)
				if (_pointTemps[4] <= m_pPCData->m_Lv)
				{
					m_Subp[4].SetFrame帧(3);
					m_Subp[4].m_bMove = true;
				}
				break;
			}
			// 			m_pPCData->m_AddPoint.idle未分配点数 += 1;
			// 			if (m_pPCData->m_AddPoint.idle未分配点数 == 1)
			_pointTemps[5] += per加点;
			{
				for (int i = 0; i < 5; i++)
				{
					m_Addp[i].SetFrame帧(0);
					m_Addp[i].m_bMove = true;
				}
			}
			UpdateProPerty();
		}
		return true;
	case 30: // 酒肆
		if (g_StateType == STATE_MAIN)
		{
			m_pPCData->FillHpMp();
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
			UpDatePcDate();
		}
		return true;
	case 31: // 巫医
		if (g_StateType == STATE_MAIN)
		{
			for (int i = m_pPCData->m_NumofBB - 1; i >= 0; --i)
			{
				m_pPCData->m_pPets[i]->m_PetData.FillHpMp();
			}
			g_pHeroObj->m_Wav.Free();
			g_pHeroObj->m_Wav.LoadWav(0xAFE0E635);
			UpDatePcDate();
		}
		return true;
	}
	return true;
}

bool cState::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_State.SetX(x);
	m_State.SetY(y);
	m_Cancel.SetX(x + 233);
	m_Cancel.SetY(y + 5);
	for (int i = 0; i < 5; i++)
	{
		m_Addp[i].m_x = m_xPos + 205;
		m_Addp[i].m_y = m_yPos + 255 + i * 23;
		m_Subp[i].m_x = m_xPos + 225;
		m_Subp[i].m_y = m_yPos + 255 + i * 23;
	}


	m_ButtonLvUp.SetXY(m_xPos + 151, m_yPos + 175);
	m_ButtonLvDown.SetXY(m_xPos + 151 + 50, m_yPos + 175);
	m_TPcFnt[30].SetXY(m_ButtonLvDown.m_x + 3, m_ButtonLvDown.m_y + 2);



	for (int i = 0; i < 3; ++i)
	{
		_btns[i].SetXY(m_xPos + 204, m_yPos + 53 + i * 22);
	}

	for (int i = 0; i < 4; ++i)
	{
		_btns[i + 3].SetXY(m_xPos + 51 + i * 50, m_yPos + 199);
		_btns[i + 7].SetXY(m_xPos + 51 + i * 50, m_yPos + 222);
	}

	forr(_btns, i)
	{
		_tBtns[i].SetXCenter(_btns[i].GetCenter());
		_tBtns[i].UpdateXCenter();
		_tBtns[i].SetY(_btns[i].m_y + 2);
	}



	m_SeeZZ.SetX(m_xPos + 174 + 28);
	m_SeeZZ.SetY(m_yPos + 370);

	m_PointSpeed.SetX(m_xPos + 174 + 28);
	m_PointSpeed.SetY(m_yPos + 394);
	m_TPcFnt[31].SetXCenter(m_PointSpeed.GetCenter());
	m_TPcFnt[31].UpdateXCenter();
	m_TPcFnt[31].SetY(m_PointSpeed.m_y + 2);

	m_ButtonSkill.SetX(m_xPos + 174 + 28);
	m_ButtonSkill.SetY(m_yPos + 423);


	m_TPcFnt[0].SetXY(m_xPos + 140, m_yPos + 32);
	m_TPcFnt[29].SetXY(m_xPos + 56, m_yPos + 56);
	m_TPcFnt[1].SetXY(m_xPos + 56, m_yPos + 33);
	m_TPcFnt[2].SetXY(m_xPos + 210, m_yPos + 57);
	m_TPcFnt[3].SetXY(m_xPos + 210, m_yPos + 80);
	m_TPcFnt[4].SetXY(m_xPos + 210, m_yPos + 103);

	m_TPcFnt[28].SetXY(m_xPos + 56, m_yPos + 78);  //帮派
	m_TPcFnt[27].SetXY(m_xPos + 56, m_yPos + 101);  //门派


	m_TPcFnt[5].SetXY(m_xPos + 56, m_yPos + 133);//HP
	m_TPcFnt[6].SetXY(m_xPos + 56, m_yPos + 156);//MP
	m_TPcFnt[7].SetXY(m_xPos + 56, m_yPos + 180 - 1);//CP
	m_TPcFnt[8].SetXY(m_xPos + 56, m_yPos + 203);//活力
	m_TPcFnt[9].SetXY(m_xPos + 56, m_yPos + 226); //体力
	m_TPcFnt[10].SetXY(m_xPos + 56, m_yPos + 256 - 1);
	m_TPcFnt[11].SetXY(m_xPos + 151, m_yPos + 256 - 1);
	m_TPcFnt[12].SetXY(m_xPos + 56, m_yPos + 280 - 1);
	m_TPcFnt[13].SetXY(m_xPos + 151, m_yPos + 280 - 1);
	m_TPcFnt[14].SetXY(m_xPos + 56, m_yPos + 302 - 1);
	m_TPcFnt[15].SetXY(m_xPos + 151, m_yPos + 302 - 1);
	m_TPcFnt[16].SetXY(m_xPos + 56, m_yPos + 325 - 1);
	m_TPcFnt[17].SetXY(m_xPos + 151, m_yPos + 325 - 1);
	m_TPcFnt[18].SetXY(m_xPos + 56, m_yPos + 348 - 1);
	m_TPcFnt[19].SetXY(m_xPos + 151, m_yPos + 348 - 1);
	m_TPcFnt[20].SetXY(m_xPos + 56, m_yPos + 372 - 1);
	m_TPcFnt[21].SetXY(m_xPos + 141, m_yPos + 372 - 1); //
	m_TPcFnt[22].SetXY(m_xPos + 86, m_yPos + 402 - 1);  //升级经验
	m_TPcFnt[23].SetXY(m_xPos + 86, m_yPos + 426 - 1); //获得经验
	m_TPcFnt[24].SetXY(m_ButtonLvUp.m_x + 3, m_ButtonLvUp.m_y + 2);//升级
	m_TPcFnt[25].SetXY(m_ButtonSkill.m_x + 3, m_ButtonSkill.m_y + 2);//技能
	m_TPcFnt[26].SetXY(m_SeeZZ.m_x + 3, m_SeeZZ.m_y + 2);	//加点



	m_bMove = true;
	m_PetSkill.Move(x - m_PetSkill.m_back.GetWidth(), -90);
	return true;
}

bool cState::UpDatePcDate()
{
	if (!m_pPCData)return false;
	ostringstream oss;
	//名字
	oss << m_pPCData->m_Name;
	m_TPcFnt[0].SetString(oss.str());
	oss.str("");
	//等级
	oss << m_pPCData->m_Lv;
	m_TPcFnt[1].SetString(oss.str());


	m_TPcFnt[29].SetString(/*g_pMainState->m_FightWorkList[m_pPCData->m_IDinFightWorkList].m_pObj*/m_pPCData->getObj()->m_Name称谓.GetString());

	//人气
	oss.str("");
//	oss << m_pPCData->m_Popularity;
	m_TPcFnt[2].SetString(oss.str());



	//门派
	if (-1 < m_pPCData->m_MengPaiID)
	{
		string mengpainame = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[m_pPCData->m_MengPaiID].m_Name;
		m_TPcFnt[27].SetString(mengpainame);
		m_TPcFnt[27].m_NeedShow = true;
	}
	else m_TPcFnt[27].m_NeedShow = false;
	//帮派
	//	if (-1 < m_pPCData->m_BangPaiID)
	{
		m_TPcFnt[28].SetString("浪西游");
	}
	//	else m_TPcFnt[28].SetString("无");
	m_TPcFnt[28].m_NeedShow = true;
	//帮贡
	oss.str("");
//	oss << m_pPCData->m_BangPaiPoint;
	m_TPcFnt[3].SetString(oss.str());

	oss.str("");
	//帮贡
//	oss << m_pPCData->m_MengPaiPoint;
	m_TPcFnt[4].SetString(oss.str());
	oss.str("");
	//气血
	UpDateHp();
	//魔法
	UpDateMp();
	//愤怒
	UpDateCp();
	//活力
//	oss << m_pPCData->m_Energy << '/' << m_pPCData->m_EnergyMax;
	m_TPcFnt[8].SetString(oss.str());
	oss.str("");
	//体力
//	oss << m_pPCData->m_Physical << '/' << m_pPCData->m_PhysicalMax;
	m_TPcFnt[9].SetString(oss.str());
	oss.str("");
	//命中
	oss << m_pPCData->Hit.GetData();
	m_TPcFnt[10].SetString(oss.str());
	oss.str("");
	//伤害
	oss << m_pPCData->Atk.GetData();
	m_TPcFnt[12].SetString(oss.str());
	oss.str("");

	//防御
	oss << m_pPCData->Def.GetData();
	m_TPcFnt[14].SetString(oss.str());
	oss.str("");


	//速度
	oss << m_pPCData->Speed.GetData();
	m_TPcFnt[16].SetString(oss.str());
	oss.str("");


	//躲避
	oss << m_pPCData->Evade.GetData();
	m_TPcFnt[18].SetString(oss.str());
	oss.str("");


	//灵力
	oss << m_pPCData->Mana.GetData();
	m_TPcFnt[20].SetString(oss.str());
	oss.str("");
	UpdateProPerty();



	//升级经验
	oss << GetCharacterExp(m_pPCData->m_Lv + 1);//m_pPCData->m_ExpMax;
	m_TPcFnt[22].SetString(oss.str());
	oss.str("");
	//获得经验
	oss << m_pPCData->m_EXP;
	m_TPcFnt[23].SetString(oss.str());

	//角色资质
	oss.str("");
// 	oss << m_pPCData->m_ZiZhi.atk;
// 	m_TPetDate[0].SetString(oss.str());
// 	//防御资质
// 	oss.str("");
// 	oss << m_pPCData->m_ZiZhi.def;
// 	m_TPetDate[1].SetString(oss.str());
// 	//体力资质
// 	oss.str("");
// 	oss << m_pPCData->m_ZiZhi.hp;
// 	m_TPetDate[2].SetString(oss.str());
// 	//法力资质
// 	oss.str("");
// 	oss << m_pPCData->m_ZiZhi.mag;
// 	m_TPetDate[3].SetString(oss.str());
// 	//速度资质
// 	oss.str("");
// 	oss << m_pPCData->m_ZiZhi.speed;
// 	m_TPetDate[4].SetString(oss.str());
// 	//躲闪资质
// 	oss.str("");
// 	oss << m_pPCData->m_ZiZhi.avoid;
// 	m_TPetDate[5].SetString(oss.str());
// 	//寿命
// 	oss.str("");
// 	//	oss << "*MAX*";
// 	m_TPetDate[6].SetString(oss.str());
// 	float groving = (float)m_pPCData->m_ZiZhi.grow;
// 	groving /= 100;
// 	//成长率
// 	oss.str("");
// 	oss << groving;
// 	m_TPetDate[7].SetString(oss.str());
// 	oss.str("");
// 	oss << "*";
// 	m_TPetDate[8].SetString(oss.str());



	return true;
}


void cState::UpDateHp()
{
	if (!m_pPCData)
	{
		return;
	}
	g_pMainState->m_Canvas.SetRedraw(m_TPcFnt[5].m_PreShowRect);
	ostringstream oss;
	oss << m_pPCData->m_HP << '/' << m_pPCData->m_HP2 << '/' << m_pPCData->HPMax.GetData();
	m_TPcFnt[5].SetString(oss.str());
}
void cState::UpDateMp()
{
	if (!m_pPCData)
	{
		return;
	}
	g_pMainState->m_Canvas.SetRedraw(m_TPcFnt[6].m_PreShowRect);
	ostringstream oss;
	oss << m_pPCData->m_MP << '/' << m_pPCData->MPMax.GetData();
	m_TPcFnt[6].SetString(oss.str());
}
void cState::UpDateCp()
{
	if (!m_pPCData)
	{
		return;
	}
	g_pMainState->m_Canvas.SetRedraw(m_TPcFnt[7].m_PreShowRect);
	ostringstream oss;
	oss << m_pPCData->m_CP << "/150";
	m_TPcFnt[7].SetString(oss.str());
}

void cState::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_State.m_PreShowRect);
	if (m_NeedShow)
	{

		Init();
		m_Sleeptime = 0;
		m_Cancel.SetFrame帧(0);
		_cC->m_PcData.apply();
		UpDatePcDate();
		UpdateProPerty();
		UpdateAddPointB();

		for (int i = 0; i < 5; i++)
		{
			m_Addp[i].SetFrame帧(0);
			m_Addp[i].m_bMove = true;
			m_Subp[i].SetFrame帧(0);
			m_Subp[i].m_bMove = true;
		}
		m_TPcFnt[24].SetString("升级"/*_cC == g_pCharacter ? "升级" : "离队"*/);
		// 		m_ButtonLvUp.m_NeedShow = (g_StateType != STATE_FIGHT);
		// 		m_SeeZZ.m_NeedShow = (g_StateType != STATE_FIGHT);
	}
	else
	{
		cct::autoSave();
	}
// 	else if (m_isNeedLvupOfFriend)
// 	{
// 		g_pMainState->m_pFightState->CheckPetExp();
// 		m_isNeedLvupOfFriend = false;
// 		//队友升级
// 		for (int i = 0; i < 5; i++)
// 		{
// 			if (i == g_pMainState->m_HeroID)continue;
// 			if (!g_pMainState->m_FightWorkList[i].isExist)continue;
// 			cPcData *data = &((cCharacter*)g_pMainState->m_FightWorkList[i].m_pObj->m_pIndex)->m_PCData;
// 			for (int i = 0; i < 6; ++i)
// 			{
// 				asert(data->m_Equip[i].m_Property.size(), "%s原装备空属性(%d)", data->m_Name.c_str(), i);
// 			}
// 			data->Followlv(g_pCharacter->m_PcData.m_Lv, false, true, true);
// 			data->FollowShoe();
// 		}
// 		if (g_pCharacter->m_PcData.m_Lv >= cct::get()->lvFor渡劫头像)
// 		{
// 			if (!g_pCharacter->m_PcData.m_bDuJie)
// 			{
// 				cCharacter* pPc;
// 				for (int i = 0; i < 5; i++)
// 				{
// 					if (!g_pMainState->m_FightWorkList[i].isExist)continue;
// 					pPc = (cCharacter*)g_pMainState->m_FightWorkList[i].m_pObj->m_pIndex;
// 					pPc->m_PcData.m_bDuJie = true;
// 				}
// 				g_pMainState->m_PCHead.UpDateHead();
// 			}
// 		}
// 	}
	if (m_PetSkill.m_NeedShow)
		g_pMainState->m_Canvas.SetRedraw(m_PetSkill.m_back.m_PreShowRect);
}


bool cState::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	OnOff(false);
	return true;
}

void cState::switchAddPoint()
{
	m_bAddPoint = !m_bAddPoint;

}

void cState::UpdateProPerty()
{
	ostringstream oss;
// 	if (m_bAddPoint)
// 	{
// 		//体质点数
// 		oss << m_pPCData->m_AddPoint.body;
// 		m_TPcFnt[11].SetString(oss.str());
// 		oss.str("");
// 		//魔力点数
// 		oss << m_pPCData->m_AddPoint.mag;
// 		m_TPcFnt[13].SetString(oss.str());
// 		oss.str("");
// 		//力量点数
// 		oss << m_pPCData->m_AddPoint.str;
// 		m_TPcFnt[15].SetString(oss.str());
// 		oss.str("");
// 		//防点数
// 		oss << m_pPCData->m_AddPoint.dex;
// 		m_TPcFnt[17].SetString(oss.str());
// 		oss.str("");
// 		//速点数
// 		oss << m_pPCData->m_AddPoint.agi;
// 		m_TPcFnt[19].SetString(oss.str());
// 		oss.str("");
// 		//潜力
// 		oss << m_pPCData->m_AddPoint.remain;
// 		m_TPcFnt[21].SetString(oss.str());
// 		oss.str("");
// 	}
// 	else
	{
		//体质点数
		//		oss << m_pPCData->m_ProPertyHP;    
		oss << _pointTemps[0] + m_pPCData->PointBody2;
		m_TPcFnt[11].SetString(oss.str());
		oss.str("");
		//魔力点数
		//		oss << m_pPCData->m_ProPertyMag;   
		oss << _pointTemps[1] + m_pPCData->PointMag2;
		m_TPcFnt[13].SetString(oss.str());
		oss.str("");
		//力量点数
		//		oss << m_pPCData->m_ProPertyAtk;   
		oss << _pointTemps[2] + m_pPCData->PointStr2;
		m_TPcFnt[15].SetString(oss.str());
		oss.str("");
		//防点数
		//		oss << m_pPCData->m_ProPertyDef;   
		oss << _pointTemps[3] + m_pPCData->PointDex2;
		m_TPcFnt[17].SetString(oss.str());
		oss.str("");
		//速点数
		//		oss << m_pPCData->m_ProPertySpd;   
		oss << _pointTemps[4] + m_pPCData->PointAgi2;
		m_TPcFnt[19].SetString(oss.str());
		oss.str("");
		//潜力
		//潜力
		//		oss << m_pPCData->m_ProPerty未分配点;
		oss << _pointTemps[5];
		m_TPcFnt[21].SetString(oss.str());
		oss.str("");
	}
}

void cState::UpdateAddPointB()
{
	for (int i = 0; i < 5; i++)
	{
		m_Addp[i].SetFrame帧(3);
	}
	for (int i = 0; i < 5; i++)
	{
		m_Subp[i].SetFrame帧(3);
	}
// 	if (m_bAddPoint)
// 	{
// 		//检测加点是否可用
// 		//		if (m_pPCData->m_AddPoint.idle)
// 		for (int i = 0; i < 5; i++)
// 		{
// 			m_Addp[i].SetFrame帧(0);
// 		}
// 		if (m_pPCData->m_AddPoint.body)
// 		{
// 			m_Subp[0].SetFrame帧(0);
// 		}
// 		if (m_pPCData->m_AddPoint.mag)
// 		{
// 			m_Subp[1].SetFrame帧(0);
// 		}
// 		if (m_pPCData->m_AddPoint.str)
// 		{
// 			m_Subp[2].SetFrame帧(0);
// 		}
// 
// 		if (m_pPCData->m_AddPoint.dex)
// 		{
// 			m_Subp[3].SetFrame帧(0);
// 		}
// 		if (m_pPCData->m_AddPoint.agi)
// 		{
// 			m_Subp[4].SetFrame帧(0);
// 		}
// 	}
}


