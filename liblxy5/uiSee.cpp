#include "_global.h"



bool cInterfaceChaKan::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
		OnOff(false);
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
	}
	return true;
}

void cInterfaceChaKan::OnOff(bool NeedShow)
{
	if (m_NeedShow == NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (!m_NeedShow)
	{
//		m_data = 0;
// 		if (_obj)
// 		{
// 			_obj->Free();
// 			SAFE_DELETE(_obj);
// 		}

		uiPetSkill.OnOff(false);
	}
	else
	{
		Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.GetPicRange());
}

bool cInterfaceChaKan::Move(int xPos, int yPos)
{
	m_xPos = xPos;
	m_yPos = yPos;
	m_Back.SetXY(xPos, yPos);
	m_Cancel.SetXY(xPos + m_Back.GetWidth() - 20, yPos + 3);
	uiPetSkill.m_back.m_PreShowRect.right = m_xPos + m_Back.GetWidth();
	uiPetSkill.m_back.m_PreShowRect.top = m_yPos;
	uiPetSkill.m_back.m_PreShowRect.bottom = m_yPos + m_Back.GetHeight();
	uiPetSkill.m_back.m_PreShowRect.left = uiPetSkill.m_back.m_PreShowRect.right - uiPetSkill.m_back.GetWidth() / 2;


	m_Property[14].SetXCenter(m_xPos + 115);
	m_Property[14].SetY(m_yPos + 180);
	m_Property[14].UpdateXCenter();

	m_Property[13].SetXY(m_xPos + 93, m_yPos + 208);
	m_Property[12].SetXY(m_xPos + 218, m_yPos + 208);

	int xstart = m_xPos + 60;
	int xstart2 = xstart + 149;
	int ystart = m_yPos + 231;
	for (int i = 0; i < 6; i++)
	{
		m_Property[i].SetXY(xstart, ystart);
		m_Property[i + 6].SetXY(xstart2, ystart);
		ystart += 24;
	}

	for (int i = 0; i < 4; i++)
	{
		m_Pic[i].SetXY(114 + m_xPos, 154 + m_yPos);
	}
	m_Shadow.SetXY(114 + m_xPos, 154 + m_yPos);
	uiPetSkill.Move(m_xPos + m_Back.GetWidth() - uiPetSkill.m_back.GetWidth(), yPos - 69);
	xstart = uiPetSkill.m_xPos + 128;
	for (int i = 0; i < 9; ++i)
	{
		int y = uiPetSkill.m_yPos + 101 + i * 22;
		if (i >= 6)
		{
			y += 4;
		}
		uiPetSkill.m_TPetProPerty[i].SetXY(xstart, y);
	}
	uiPetSkill.MoveSkillHead(uiPetSkill.m_xPos + 20, uiPetSkill.m_yPos + 311);
	uiPetSkill.m_back.m_PreShowRect.left = uiPetSkill.m_xPos + 20;
	uiPetSkill.m_back.m_PreShowRect.right = m_Back.GetWidth() + m_xPos;
	m_MengPai.SetXCenter(m_Shadow.GetX());
	m_MengPai.SetY(m_yPos + 35);
	m_MengPai.UpdateXCenter();
	MovePetEquip();
	return true;
}

bool cInterfaceChaKan::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	m_Select = -1;
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 6;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}

	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	if (CheckOn(&m_Cancel, 0))return true;

	if (!uiPetSkill.m_bDaShuMode)
		if (CheckRB())return true;
	uiPetSkill.ProcessInput();

	g_pMainState->SetMouseOnMap(false);

	m_Select = 7;
	if (CheckL())return true;
	return true;
}

bool cInterfaceChaKan::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	OnOff(false);
	return true;
}

void cInterfaceChaKan::Set(cObj* obj)
{
	Init();
	cCharacter* pc;
	cPet* ppet;
	m_MengPai.m_NeedShow = false;

	vector<ulong> picid;
	array<sChangeColorData*, 4> pranse;
	obj->GetID(POS_STAND, picid);
	switch (obj->m_IndexType)
	{
	case INDEXTYEP_CHARACTER:
		if (1)
		{
			pc = (cCharacter*)obj->m_pIndex;
			m_data = (cPropertyData*)&pc->m_PcData;
			m_Property[13].SetString("---");
			int mengpaiid = pc->m_PcData.m_MengPaiID;
			if (mengpaiid > -1 && mengpaiid<15)
			{
				m_MengPai.SetString(g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(mengpaiid)->m_Name);
				m_MengPai.m_NeedShow = true;
				m_MengPai.UpdateXCenter();
			}
			pc->GetRanse(POS_STAND, pranse);

		}
		break;
	case INDEXTYEP_PET:
		if (1)
		{
			ppet = (cPet*)obj->m_pIndex;
			m_data = &ppet->m_PetData;
			m_Property[13].SetString(ppet->GetData()->m_LvTake);
			ppet->GetRanse(pranse);
		}
		break;
	default:
		return;
	}

//	uiPetSkill.UpdateData(m_data, false);
	MovePetEquip();
	ostringstream oss;
	m_Property[14].SetString(obj->m_TrueName.GetString());

	m_Property[12].SetString(m_data->m_Lv);

	oss.str("");
	oss << m_data->m_HP << "/" << (m_data->HPMax.GetData());
	m_Property[0].SetString(oss.str());
	oss.str("");
	oss << m_data->m_MP << "/" << (m_data->MPMax.GetData());
	m_Property[1].SetString(oss.str());
	m_Property[2].SetString(m_data->Atk.GetData());
	m_Property[3].SetString(m_data->Def.GetData());
	m_Property[4].SetString(m_data->Speed.GetData());
	m_Property[5].SetString(m_data->Mana.GetData());

	m_Property[6].SetString(m_data->PointBody + m_data->PointBody2);
	m_Property[7].SetString(m_data->PointMag + m_data->PointMag2);
	m_Property[8].SetString(m_data->PointStr + m_data->PointStr2);
	m_Property[9].SetString(m_data->PointDex + m_data->PointDex2);
	m_Property[10].SetString(m_data->PointAgi + m_data->PointAgi2);
	m_Property[11].SetString(0);


	for (int i = 0; i < 4; i++)m_Pic[i].Free();

	for (int i = 0; i < picid.size(); i++)
		m_Pic[i].Load(picid[i], pranse[i]);
}


void cInterfaceChaKan::Set(sFriendList& list)
{
	cObj* Obj = new cObj;
//	g_pMainState->LoadCharacterData2(Obj, list.m_dataFileName);
	cCharacter* pc1 = (cCharacter*)Obj->m_pIndex;
	cPcData* pc = &pc1->m_PcData;
//	pc->m_StrongLv = list.m_stronglv;
	/*for (int i = 0; i < list.m_PetSkillList.size(); i++)
	g_pMainState->m_SkillManager.SetPetSkill(pc, list.m_PetSkillList[i], i);*/
//	pc->FollowlvAddPoint(g_pCharacter->m_PcData.m_Lv, false, true, false);
	//染色
	for (int i = 1; i < 4; i++)
		pc->m_RanSe.m_ranse[i].partnum = 0;
	pc->m_RanSe.m_ranse[0] = list.m_Ranse.m_ranse[0];
	if (pc->m_RanSe.m_ranse[0].partnum&&pc1->GetData()->m_ColorID)
	{
		g_pMainState->m_ColorManage.Set(pc1->GetData()->m_ColorID);
		for (int i = 0; i < list.m_Ranse.m_ranse[0].partnum; i++)
		{
			g_pMainState->m_ColorManage.GetColorMatrix(
				i,
				pc->m_RanSe.m_ranse[0].GetColorChange(i),
				pc->m_RanSe.m_ranse[0].m_colormatrix[i]);
		}
	}


	//坐骑
	pc->m_bOnZuoQi = list.m_bOnZuoQi; //是否坐上坐骑
	pc->m_ZQ = list.m_ZuoQiID;
	pc->m_ZuoQiRanSe = list.m_ZuoQiRanse;
	g_pMainState->m_ZuoQi.GetZuoQi(*pc, pc->m_ZQ);

	//装饰染色
	if (list.m_bZhuangShi)
	{
		pc->m_ZuoQi.m_ZhuangShi.m_Num = 1;
		pc->m_ZuoQi.m_ZhuangShi.Set(31, list.m_ZhuangShiID);
		pc->m_ZhuangShiRanSe = list.m_ZhuangShiRanse;
	}
	if (list.m_weaponid>-1)
		pc->m_Equips[2].Set(list.m_weapontype, list.m_weaponid);

	Set(Obj);
}


void cInterfaceChaKan::Set(cPropertyData* data, vector<ulong> picid, array<sChangeColorData*, 4> pranse, sZiZhi* zz)
{
	Init();
	MovePetEquip();
	uiPetSkill.UpdateData(data, zz ? (*zz) : sZiZhi(), false);
	ostringstream oss;
	m_Property[14].SetString(data->m_Name);

	m_Property[12].SetString(data->m_Lv);

	oss.str("");
	oss << data->m_HP << "/" << (data->HPMax.GetData());
	m_Property[0].SetString(oss.str());
	oss.str("");
	oss << data->m_MP << "/" << (data->MPMax.GetData());
	m_Property[1].SetString(oss.str());
	m_Property[2].SetString(data->Atk.GetData());
	m_Property[3].SetString(data->Def.GetData());
	m_Property[4].SetString(data->Speed.GetData());
	m_Property[5].SetString(data->Mana.GetData());

	m_Property[6].SetString(data->PointBody + data->PointBody2);
	m_Property[7].SetString(data->PointMag + data->PointMag2);
	m_Property[8].SetString(data->PointStr + data->PointStr2);
	m_Property[9].SetString(data->PointDex + data->PointDex2);
	m_Property[10].SetString(data->PointAgi + data->PointAgi2);

	m_Property[11].SetString(0);


	for (int i = 0; i < 4; i++)
		m_Pic[i].Free();

	for (int i = 0; i < picid.size(); i++)
		m_Pic[i].Load(picid[i], pranse[i]);
}


void cInterfaceChaKan::Set(cPet* pet)
{
	m_Property[13].SetString(pet->GetData()->m_LvTake);
	m_MengPai.m_NeedShow = false;

	vector<ulong> picid;
	array<sChangeColorData*, 4> pranse;
	pet->GetID(POS_STAND, picid);
	pet->GetRanse(pranse);
	m_data = (cPropertyData*)INDEXTYEP_PET;
	Set(&pet->m_PetData, picid, pranse, &pet->m_PetData.m_ZiZhi);
}


void cInterfaceChaKan::Set(cCharacter* character)
{
	m_Property[13].SetString("---");
	m_MengPai.m_NeedShow = false;

	vector<ulong> picid;
	array<sChangeColorData*, 4> pranse;
	character->GetID(POS_STAND, picid);

	int mengpaiid = character->m_PcData.m_MengPaiID;
	if (mengpaiid > -1 && mengpaiid < c_MenPaiNumber)
	{
		m_MengPai.SetString(g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(mengpaiid)->m_Name);
		m_MengPai.m_NeedShow = true;
		m_MengPai.UpdateXCenter();
	}
	character->GetRanse(POS_STAND, pranse);
	m_data = (cPropertyData*)INDEXTYEP_CHARACTER;
	Set(&character->m_PcData, picid, pranse, nullptr);
}





bool cInterfaceChaKan::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	uiPetSkill.Init();
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Back.Load(0x536A7E15);
	uiPetSkill.m_back.m_NeedShow = false;
	uiPetSkill.m_Cancel.m_NeedShow = false;
	for (int i = 0; i < 4; i++)
		m_Pic[i].SetDirection(3);
	m_Shadow.Set(&g_pMainState->m_Shadow);
	m_MengPai.SetColor(RGB(255, 255, 255));
	return true;
}


bool cInterfaceChaKan::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	for (int i = 0; i < 15; i++)
	{
		pCanvas->Add(&m_Property[i]);
	}
	pCanvas->Add(&m_Shadow, 1);
	for (int i = 0; i < 4; i++)
	{
		pCanvas->Add(&m_Pic[i], 1);
	}
	uiPetSkill.Show(pCanvas);
	if (m_MengPai.m_NeedShow)
		pCanvas->Add(&m_MengPai);
	return true;
}

void cInterfaceChaKan::MovePetEquip()
{
	for (int i = 0; i < 3; i++)
	{
		uiPetSkill.m_EquipBackp[i].SetXY(m_xPos + 200, m_yPos + 30 + i * 60);
		uiPetSkill.m_EquipHead[i].SetXY(uiPetSkill.m_EquipBackp[i].GetX(), uiPetSkill.m_EquipBackp[i].GetY());
	}
	if (m_data == (cPropertyData*)INDEXTYEP_PET)
	{
		return;
	}

	int x0 = uiPetSkill.m_EquipBackp[0].GetX();
	for (int i = 0; i < 6; i++)
	{
		int x = x0;
		if ((i % 2) == 0)
		{
			x = m_xPos - 7;
		}

		int y = uiPetSkill.m_EquipBackp[0].GetY();
		if ((i / 2) > 0)
		{
			y += 60;
		}
		if ((i / 2) > 1)
		{
			y += 60;
		}

		uiPetSkill.m_EquipBackp[i].SetXY(x, y);
		uiPetSkill.m_EquipHead[i].SetXY(x, y);
	}
}
