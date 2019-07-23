#include "_global.h"



bool cInterfaceRanSe::Init()
{
	m_NextPage.Load(0xCB50AB1D);
	m_NextPage.SetStatic(true);
	m_Back.Load(0x61E6DAFE/*0x1A2DEAB9*/);
	m_Back.SetStatic(true);
	m_btBuy.Load(0x79D01E0E);
	m_btBuy.SetStatic(true);
	m_tBuy.SetColor(RGB(255, 255, 255));
	m_tBuy.SetString("确定");
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Title.SetColor(RGB(255, 255, 255));
	m_Title.SetString("染色");
	for (int i = 0; i < 4; i++)
	{
		m_btSelect[i].Load(0xF9494E3A);
		m_btSelect[i].SetStatic(true);
		m_tSelect[i].SetColor(RGB(255, 255, 255));
		m_tSelect[i].SetString(" ");
	}

	_wasMode.Load(g_pMainState->m_Button4.m_NowID);
	_wasMode.SetStatic(true);

	_wasLeft.Load(0xF9494E3A);
	_wasLeft.SetStatic(true);

	_wasRight.Load(0xF9494E3A);
	_wasRight.SetStatic(true);

	m_tSelect[0].SetString("<-");
	m_tSelect[1].SetString("->");


	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	m_bInit = true;
	return true;
}

bool cInterfaceRanSe::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetXY(m_xPos, m_yPos);

	_wasMode.SetX(m_Back.GetCenter() - _wasMode.GetWidth() / 2);
	_wasMode.SetY(m_yPos + 3);

	m_Title.SetXCenter(_wasMode.GetCenter());
	m_Title.SetY(_wasMode.GetY() + 3);
	m_Title.UpdateXCenter();

	m_btBuy.SetXY(m_xPos + m_Back.GetWidth() / 2 - m_btBuy.GetWidth() / 2, m_yPos + 300/*238*/);

	m_tBuy.SetXCenter(m_btBuy.GetX() + m_btBuy.GetWidth() / 2);
	m_tBuy.SetY(m_btBuy.GetY() + 2);
	m_tBuy.UpdateXCenter();

	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	int cube = m_btSelect->GetWidth();
	int xstart = m_Back.GetCenter() - cube * 2 - 15;
	cube += 10;
	for (int i = 0; i < 4; i++)
	{
		m_btSelect[i].SetXY(xstart + cube * i, m_yPos + 265/*195*/);

		m_tSelect[i].SetY(m_btSelect[i].GetY() + 3);
		m_tSelect[i].SetXCenter(m_btSelect[i].GetX() + m_btSelect[i].GetWidth() / 2);
		m_tSelect[i].UpdateXCenter();
	}
	m_Target.SetXY(m_xPos + m_Back.GetWidth() / 2, m_yPos + 230/*m_Back.GetHeight() - 95*/);
	m_NextPage.SetXY(m_xPos + m_Back.GetWidth() - 45 , m_yPos + 40);

	_wasLeft.SetXY(m_btBuy.GetX() - 16 - _wasLeft.GetWidth(), m_btBuy.GetY());
	_wasRight.SetXY(m_btBuy.GetX() + m_btBuy.GetWidth() + 16, m_btBuy.GetY());

	m_tSelect[0].SetY(_wasLeft.GetY() + 3);
	m_tSelect[0].SetXCenter(_wasLeft.GetCenter());
	m_tSelect[0].UpdateXCenter();

	m_tSelect[1].SetY(_wasRight.GetY() + 3);
	m_tSelect[1].SetXCenter(_wasRight.GetCenter());
	m_tSelect[1].UpdateXCenter();
	return true;
}

bool cInterfaceRanSe::ProcessInput()
{
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}

	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	g_pMainState->SetMouseOnMap(false);
	if (CheckOn(&m_Cancel, 5))return true;
	if (CheckOn(&m_btBuy, 4))return true;
	if (CheckOn(&m_NextPage, 8))return true;
	if (CheckOn(&_wasMode, 9))return true;
	if (CheckOn(&_wasLeft, 10))return true;
	if (CheckOn(&_wasRight, 11))return true;
	for (int i = 0; i < 4; i++)
	{
		if (CheckOn(&m_btSelect[i], i))return true;
	}
	m_Select = 0;
	if (CheckRB())return true;

	//准备移动
	m_Select = 7;
	if (CheckL())return true;
	return true;
}

void cInterfaceRanSe::OnOff(bool NeedShow)
{
	g_pMainState->InterfaceSetShow(this, NeedShow);
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
	if (m_NeedShow)
	{
		if (!m_bInit)Init();
		m_Title.SetString(_isRandMode ? "随机模式" : "染色模式");
	}
	else m_plist = 0;
}

bool cInterfaceRanSe::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		m_frampre->SetFrame(1);
		if (_isRandMode)
		{
			ulong id = m_Target.m_NowID;
			if (!id) return true;
			int fram = m_Target.GetNowFrame();
			m_Target.Free();
			g_pMainState->m_ColorManage.Set(m_ColorID);
			if (!m_ChangeColorData.SetColorChange(m_Select, 0))
			{
				return true;
			}
			auto& m = m_ChangeColorData.m_colormatrix[m_Select];
			m.x1 = rand() % 0x200;
			m.x2 = rand() % 1;
			m.x3 = rand() % 1;
			m.y1 = rand() % 1;
			m.y2 = rand() % 0x200;
			m.y3 = rand() % 1;
			m.z1 = rand() % 1;
			m.z2 = rand() % 1;
			m.z2 = rand() % 0x200;

			m_Target.Load(id, &m_ChangeColorData);
			m_Target.SetFrame(fram);
			return true;
		}
		else
		{
			m_ChangeColorData.AddColorChange(m_Select);
			UpdateColor();
		}

		break;
	case 5://关
		OnOff(false);
		break;
	case 4://确定
		if (1)
		{
			cObj* pobj = g_pMainState->m_FightWorkList[_characterid].m_pObj;
			cCharacter* pc = (cCharacter*)pobj->m_pIndex;
// 			if (true || !m_plist)
// 			{
// 				pobj = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
// 				pc = g_pCharacter;
// 			}
// 			else
// 			{
// 				pobj = g_pMainState->m_FightWorkList[m_plist->getIDinTeam()].m_pObj;
// 				pc = (cCharacter*)pobj->m_pIndex;
// 			}
// 			if (pc->m_PcData.m_FightPetID < 0)
// 			{
// 				break;
// 			}
// 			if (m_plist)
// 			{//更新好友数据
// 				switch (m_Mode)
// 				{
// 				case 0:
// 					m_plist->m_Ranse.m_ranse[0] = m_ChangeColorData;
// 					break;
// 				case 1:
// 					m_plist->m_ZuoQiRanse = m_ChangeColorData;
// 					break;
// 				case 2:
// 					m_plist->m_ZhuangShiRanse = m_ChangeColorData;
// 					break;
// 				case 3:
// 					if (-1 == m_plist->m_FightBB)return false;
// 					m_plist->m_BBList[m_plist->m_FightBB].m_ranse.m_ranse[m_NowPart] = m_ChangeColorData;
// 					pobj = g_pMainState->m_FightWorkList[m_plist->getIDinTeam() + 5].m_pObj;
// 					break;
// 				default:
// 					ERRBOX;
// 					break;
// 				}
// 			}
			//更新好友当前
			switch (m_Mode)
			{
			case 0:
				pc->m_PcData.m_RanSe.m_ranse[m_NowPart] = m_ChangeColorData;
				break;
			case 1:
				pc->m_PcData.m_ZuoQiRanSe = m_ChangeColorData;
				break;
			case 2:
				pc->m_PcData.m_ZhuangShiRanSe = m_ChangeColorData;
				break;
			case 3:
			case 4:
				pc->m_PcData.m_pPets[_fightPetid/*pc->m_PcData.m_FightPetID*/]->m_PetData.m_RanSe.m_ranse[m_NowPart] = m_ChangeColorData;
// 				if (!m_plist)
// 				{
// 					pobj = g_pHeroObj;
// 				}
				if (g_pMainState->m_InterfacePet.m_NeedShow)
				{
					g_pMainState->m_InterfacePet.m_PetObj.Reset();
					g_pMainState->m_InterfacePet.m_PetObj.Set(POS_STAND);
				}
				break;
			default:
				ERRBOX;
				break;
			}
			if (pobj)
			{

				pobj->Reset();
				pobj->Set(POS_STAND);
			}
			OnOff(false);
		}
		break;
	case 6://移动
		if (1)
		{
			m_Sleeptime = 0;
			g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
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
		if (m_Mode != 3)return true;
// 		if (m_plist)
// 		{
// 			cCharacter* pc;
// 			pc = (cCharacter*)g_pMainState->m_FightWorkList[m_plist->getIDinTeam()].m_pObj->m_pIndex;
// 			SetPet(m_NowPart + 1, pc);
// 		}
// 		else
		SetPet(m_NowPart + 1, /*g_pCharacter*/_fightPetid);
		return true;
	case 9:
		m_Title.SetString((_isRandMode = !_isRandMode) ? "随机模式" : "染色模式");
		return true;

	case 10:
	{
		int d = m_Target.m_Picture.m_direction;
		if (--d < 1)
		{
			d = m_Target.GetDirectionNum();
		}
		m_Target.SetDirection(d);
	}
		return true;
	case 11:
	{
		int d = m_Target.m_Picture.m_direction;
		if (++d > m_Target.GetDirectionNum())
		{
			d = 1;
		}
		m_Target.SetDirection(d);
	}
		return true;
	}
	return true;
}

bool cInterfaceRanSe::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_btBuy, 1);

	pCanvas->Add(&_wasLeft, 1);
	pCanvas->Add(&_wasRight, 1);

	for (int i = 0; i < m_ChangeColorData.partnum; i++)
	{
		pCanvas->Add(&m_btSelect[i], 1);
		pCanvas->Add(&m_tSelect[i], 1);
	}
	pCanvas->Add(&m_tBuy, 1);

	pCanvas->Add(&_wasMode, 1);
	pCanvas->Add(&m_Title, 1);
	pCanvas->Add(&m_Target, 1);
	pCanvas->Add(&m_NextPage, 1);
	

	return true;
}

void cInterfaceRanSe::SetMode(int mode, int Characterid)//sFriendList* plist)
{
	if (Characterid < 0 || Characterid >= 5)
	{
		return;
	}
	if (!g_pMainState->m_FightWorkList[Characterid].isExist)
	{
		return;
	}

	cObj* pobj = g_pMainState->m_FightWorkList[Characterid].m_pObj;
	if (pobj->GetDataType() != INDEXTYEP_CHARACTER)
	{
		return;
	}
	_characterid = Characterid;

	m_Mode = mode;
	m_Target.Free();
	cCharacter* pc;
	cObj* pObj = g_pMainState->m_FightWorkList[Characterid].m_pObj;
	pc = (cCharacter*)pObj->m_pIndex;
// 	if (Characterid != g_pMainState->m_HeroID)
// 	{
// 		m_plist = g_pMainState->m_Friend.FindFriend2(pc->m_PCData.m_Name);
// 		m_plist = g_pMainState->m_Friend.FindFriend2(pc->m_PcData.m_dataFileName);
// 		if (m_Mode == 1 || m_Mode == 2)
// 		{
// 			if (m_plist->m_bOnZuoQi&&m_plist->m_ZuoQiID>-1)
// 			{
// 
// 			}
// 			else
// 			{
// 
// 				OnOff(false);
// 				return;
// 			}
// 		}
// 	}

	//0 角色染色  1坐骑染色  2 坐骑装饰染色 3 召唤兽染色
	ulong data = 0;
	m_ChangeColorData.Reset();
	switch (mode)
	{
	case 0:
		if (1)
		{
//			if (pc->m_PcData.m_bUseCard)
			if (pc->m_PcData.m_CardPetID >= 0)
			{
				g_pMainState->m_Tags.Add("变身卡无法染色");
				OnOff(false);
				return;
			}
			if (pc->m_PcData.m_bOnZuoQi)
				if (pc->m_PcData.m_ZuoQi.m_pZuoQi)
				{
				pc->m_PcData.m_bOnZuoQi = false;
				}

			//data=pc->GetID(POS_STAND);
			m_ColorID = g_pMainState->m_pCharacterDataList[pc->m_PcData.modeid].m_ColorID;
			if (m_ColorID == 0)
			{
				m_ColorID = 0x1657;
			}
			g_pMainState->m_ColorManage.Set(m_ColorID);
			m_ChangeColorData.partnum = g_pMainState->m_ColorManage.GetPartNum();
			if (pc->m_PcData.m_RanSe.m_ranse[0].partnum)
			{
				m_ChangeColorData = pc->m_PcData.m_RanSe.m_ranse[0];
			}
			data = pc->GetID(POS_STAND);
		}
		break;
	case 1:
		if (1)
		{
			if (!pc->m_PcData.m_ZuoQi.m_pZuoQi)
			{
				OnOff(false);
				return;
			}
			data = pc->m_PcData.m_ZuoQi.GetID(POS_STAND);
			m_ColorID = pc->m_PcData.m_ZuoQi.m_pZuoQi->m_ColorID;
			if (m_ColorID == 0)
			{
				m_ColorID = 0x1657;
			}
			g_pMainState->m_ColorManage.Set(m_ColorID);
			m_ChangeColorData.partnum = g_pMainState->m_ColorManage.GetPartNum();

			if (pc->m_PcData.m_ZuoQiRanSe.partnum)
			{
				m_ChangeColorData = pc->m_PcData.m_ZuoQiRanSe;
			}
		}
		break;
	case 2:
		if (1)
		{
			if (!pc->m_PcData.m_ZuoQi.m_ZhuangShi.GetNum())
			{
				break;
			}
			sZuoQiZhuangShi* pZhuangShi = &g_pMainState->m_ItemManage.m_ZuoQiZhuangShiList[pc->m_PcData.m_ZuoQi.m_ZhuangShi.GetID()];
			data = pZhuangShi->NodeStand;
			m_ColorID = pZhuangShi->m_ColorID;
			if (m_ColorID == 0)
			{
				m_ColorID = 0x1657;
			}
			g_pMainState->m_ColorManage.Set(m_ColorID);
			m_ChangeColorData.partnum = g_pMainState->m_ColorManage.GetPartNum();
			if (pc->m_PcData.m_ZhuangShiRanSe.partnum)
			{
				m_ChangeColorData = pc->m_PcData.m_ZhuangShiRanSe;
			}

		}
		break;
	case 3:
		if (pc->m_PcData.m_FightPetID < 0 || pc->m_PcData.m_FightPetID >= pc->m_PcData.m_NumofBB)
		{
			return;
		}
		SetPet(0, pc->m_PcData.m_FightPetID);
		return;
	case 4:
	{
		if (!g_pMainState->m_InterfacePet.m_NeedShow)
		{
			return;
		}
		int select = g_pMainState->m_InterfacePet.m_TrueSelect;
		if (select < 0 || select >= pc->m_PcData.m_NumofBB)
		{
			return;
		}
		SetPet(0, select);
	}
		return;
	default:
		break;
	}

	m_Target.Load(data);
	UpdateColor();
}

void cInterfaceRanSe::UpdateColor()
{
	ulong id = m_Target.m_NowID;
	if (!id)return;
	int fram = m_Target.GetNowFrame();
	m_Target.Free();
	g_pMainState->m_ColorManage.Set(m_ColorID);
// 	if (_isRandMode)
// 	{
// 		if (!m_ChangeColorData.SetColorChange(m_Select, 0))
// 		{
// 			return;
// 		}
// 		auto& m = m_ChangeColorData.m_colormatrix[m_Select];
// 		m.x1 = rand() % 0x200;
// 		m.x2 = rand() % 1;
// 		m.x3 = rand() % 1;
// 		m.y1 = rand() % 1;
// 		m.y2 = rand() % 0x200;
// 		m.y3 = rand() % 1;
// 		m.z1 = rand() % 1;
// 		m.z2 = rand() % 1;
// 		m.z2 = rand() % 0x200;
// 
// 		m_Target.Load(id, &m_ChangeColorData);
// 		m_Target.SetFrame(fram);
// 		return;
// 	}

	for (int i = 0; i < m_ChangeColorData.partnum; i++)
	{
		//防止越界
		if (m_ChangeColorData.GetColorChange(i) >= g_pMainState->m_ColorManage.m_CharacterColor.m_stagesplit[i].m_ColorMatrix.size())
		{
			m_ChangeColorData.SetColorChange(i, 0);
		}
		g_pMainState->m_ColorManage.GetColorMatrix(i, m_ChangeColorData.GetColorChange(i), m_ChangeColorData.m_colormatrix[i]);
	}
	m_Target.Load(id, &m_ChangeColorData);
	m_Target.SetFrame(fram);
}

bool cInterfaceRanSe::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	OnOff(false);
	return true;
}

void cInterfaceRanSe::SetPet(int part, int fightpetid)
{
	cCharacter* pc = (cCharacter*)g_pMainState->m_FightWorkList[_characterid].m_pObj->m_pIndex;
	cPetData* pPetData = &pc->m_PcData.m_pPets[_fightPetid = fightpetid]->m_PetData;
	int modeid = pPetData->modeid;
	sPetData& spetdata = g_pMainState->m_PetDataManager.m_PetList[modeid];
	vector<int>& partid = spetdata.m_ComponentTable[pPetData->m_JinJieNum.m_index];
	if (part >= partid.size())part = 0;
	vector<ulong> data;
	pc->m_PcData.m_pPets[fightpetid]->GetID(POS_STAND, data);
	m_NowPart = part;
	m_ColorID = spetdata.m_ModelActs[partid[m_NowPart]].m_ColorID;
	if (m_ColorID == 0)
	{
		/*g_pMainState->m_Tags.Add("很遗憾,由于本人懒,部分召唤兽无法染色");

		return;*/
		m_ColorID = 0x1657;
	}
	g_pMainState->m_ColorManage.Set(m_ColorID);
	m_ChangeColorData.partnum = g_pMainState->m_ColorManage.GetPartNum();

	/*	if (pc->m_PCData.m_ZuoQi.m_ZhuangShi.m_Property.size())
	{
	m_ChangeColorData = pPetData->m_RanSe.m_ranse[0];
	}*/
	m_Target.Load(data[m_NowPart]);
	UpdateColor();
}