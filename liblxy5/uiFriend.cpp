#include "_global.h"




void cFriend::sMessageList::Save(ofstream& File)
{
	File << "\n";
	File << messagePath << "\n";
	File << id << " ";
	File << p->m_type << " ";
	File << p->m_HuanShu << " ";
	File << taskid << " ";
}



void cFriend::sMessageList::Load(ifstream& File)
{
	getline(File, messagePath);
	getline(File, messagePath);
	File >> id;
	int type;
	File >> type;
	p = g_pMainState->FindTaskByID(type);
	File >> p->m_HuanShu;
	File >> taskid;
}



void sFriendList::Save(ofstream& File)
{
	File << "\n";
	m_JinJieNum.Save(File);
	File << m_bDuJie << " ";
	File << m_traderLV << " ";
	File << m_Feeling << " ";
	File << m_Name << " ";
	File << m_dataFileName << " ";
	File << 0 << " ";// m_bOnLine << " ";
	File << m_stronglv << " ";
	File << m_modeid << " ";
	File << m_weapontype << " ";
	File << m_weaponid << " ";
	m_Ranse.Save(File);
	File << m_money << " ";
	File << m_bOnZuoQi << " ";
	File << m_ZuoQiID << " ";
	//坐骑
	m_ZuoQiRanse.Save(File);
	File << m_bZhuangShi << " ";
	File << m_ZhuangShiID << " ";
	m_ZhuangShiRanse.Save(File);
	File << m_BBList.size() << " ";
	for (int i = 0; i < m_BBList.size(); i++)
	{
		m_BBList[i].Save(File);
	}
	File << m_FightBB << "\n";
	//File << 0 << " ";
	/*File << m_PetSkillList.size() << " ";
	for (int i = 0; i < m_PetSkillList.size(); i++)
	{
	File << m_PetSkillList[i] << " ";
	}*/
	//File << "\n";
}



void sFriendList::Load(ifstream& File)
{
	m_JinJieNum.Load(File);
	File >> m_bDuJie;
	File >> m_traderLV;
	File >> m_Feeling;
	File >> m_Name;
	File >> m_dataFileName;
	int dustbin;
	File >> dustbin;// m_bOnLine;
	File >> m_stronglv;
	File >> m_modeid;
	File >> m_weapontype;
	File >> m_weaponid;
	m_Ranse.Read(m_modeid + 2000, File, m_JinJieNum.m_index);
	File >> m_money;
	File >> m_bOnZuoQi;
	File >> m_ZuoQiID;
	//坐骑
	m_ZuoQiRanse.Read(File, m_ZuoQiID, sChangeColorData::eZuoQi, 0);
	File >> m_bZhuangShi;
	File >> m_ZhuangShiID;
	m_ZhuangShiRanse.Read(File, m_ZhuangShiID, sChangeColorData::eZhuangShi, 0);
	int bbnum;
	File >> bbnum;
	m_BBList.resize(bbnum);
	/*for (int i = 0; i < 5; i++)
	{
	if (g_pMainState->m_FightList[i].m_pData->m_TrueName.GetString() == m_Name)
	{

	}
	}*/


	for (int i = 0; i < m_BBList.size(); i++)
	{
		m_BBList[i].Load(File, (g_pCharacter->m_PcData.m_Lv + 10) / 60);
	}
	File >> m_FightBB;
	/*int petskillnum;
	File >> petskillnum;*/
	/*m_PetSkillList.resize(petskillnum);
	for (int i = 0; i < m_PetSkillList.size(); i++)
	{
	File >> m_PetSkillList[i];
	}*/

}


ulong sFriendList::GetFriendHead()
{
	return g_pMainState->m_pCharacterDataList[m_modeid].m_Head[m_bDuJie].m_HeadFriend;
}

ulong sFriendList::GetDialogHead()
{
	return g_pMainState->m_pCharacterDataList[m_modeid].m_Head[m_bDuJie].m_dialog;
}

bool sFriendList::CheckInTeam()
{
	if (getIDinTeam() > -1)return true;
	return false;
}

int sFriendList::getIDinTeam()
{
	for (int i = 0; i < 5; i++)
	{
		if (!g_pMainState->m_FightWorkList[i].isExist)continue;
		if (g_pMainState->m_FightWorkList[i].m_pObj->m_TrueName.GetString() == m_Name)return i;
	}
	return -1;
}



bool cFriend::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	for (int i = 0; i < 4; i++)
	{
		m_Buttonp[i].m_bStatic = true;
		m_Buttonp[i].Set(&g_pMainState->m_Button4);
		m_ButtonText[i].SetColor(RGB(255, 255, 255));
		m_ButtonText[i].m_hFont = g_pMainState->m_hFont[0];
	}
	m_ButtonText[0].SetString("邀请入队");
	m_ButtonText[1].SetString("好友强化");

	m_ButtonText[2].SetString("上一页"/*"给TA钱"*/);
	m_ButtonText[3].SetString("下一页"/*"要钱"*/);
	for (int i = 0; i < 2; i++)
	{
		m_PetSelectBack[i].Load(0xF151309F);
		m_PetSelectBack[i].SetStatic(true);
		m_PetSelectBack[i].SetFrame(1);
		m_PetSelectBack[i].SetxOffset(38);
	}
	ccm::get()->pushWdf("好友面板select", 0xF151309F);
	m_nowPage = 0;
	m_Back.Load(3482058907);

	Move(g_640 - m_Back.m_Picture.m_Width, 50);
	return true;
}

bool cFriend::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);
	pCanvas->Add(&m_Cancel, 1);
	if (m_TrueFriendSelect > -1)
	{
		pCanvas->Add(&m_PetSelectBack[0], 1);
		pCanvas->Add(&m_PetSelectBack[1], 1);
	}
	for (int i = 0; i < m_NameNum; i++)
	{

		pCanvas->Add(&m_NameList[i]);
		pCanvas->Add(&m_NameListHead[i], 1);
	}
	for (int i = 0; i < 4; i++)
	{
		pCanvas->Add(&m_Buttonp[i], 1);
		pCanvas->Add(&m_ButtonText[i]);
	}
	return true;
}

bool cFriend::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	ResetButton();
	if (m_bMoveMode)//移动
	{
		m_Select = 26;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())
			m_bMoveMode = false;
		return true;
	}
	m_Select = -1;


	for (int i = 0; i < 2; i++)
	{
		m_PetSelectBack[i].m_NeedShow = false;
	}

	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return false;
	g_pMainState->SetMouseOnMap(false);
	g_pMainState->m_Cursor.m_FollowMode = false;
	if (CheckOn(&m_Cancel, 20))return true;
	for (int i = 0; i < 4; i++)
		if (CheckOn(&m_Buttonp[i], 10 + i))return true;

	int yStart = m_yPos + _yStart;
	if (m_NameNum > 0)
		if (g_yMouse >m_Rect.top && g_yMouse<m_Rect.bottom)
		{
		m_Select = (g_yMouse - yStart) / _hInv;
		if (m_Select >= m_NameNum)m_Select = m_NameNum - 1;
		for (int i = 0; i < 2; i++)
		{
			m_PetSelectBack[i].SetY(yStart + m_Select * +_hInv + 2);
			m_PetSelectBack[i].m_NeedShow = true;
		}

		if (CheckL())return true;
		if (CheckRB())return true;
		}

	//准备移动
	m_Select = 27;
	if (CheckL())return true;
	m_Select = 20;
	if (CheckRB())return true;
	return true;
}

bool cFriend::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_PetSelectBack[0].m_Picture.m_x = m_xPos + 5 + 2;
	m_PetSelectBack[1].m_Picture.m_x = m_PetSelectBack[0].m_Picture.m_x + m_PetSelectBack[0].m_Picture.m_ShowWidth;
	for (int i = 0; i < 2; i++)
	{
		m_PetSelectBack[i].m_Picture.m_y = m_yPos + (_yStart + 2) + m_TrueFriendSelect * _hInv;
		m_PetSelectBack[i].m_bMove = true;
	}

	m_Back.SetXY(x, y);
	for (int i = 0; i < m_MaxNameNum; i++)
	{
		m_NameListHead[i].m_Picture.SetXY(x + 10, y + _yStart + i * _hInv);
		m_NameList[i].SetXY(x + 50, y + (_yStart + 5) + i * _hInv);
	}
	for (int i = 0; i < 4; i++)
	{
		m_Buttonp[i].m_x = m_xPos + 25;

	}
	m_Cancel.SetXY(x + 107, y + 4);
	m_Buttonp[0].m_y = m_yPos + 30;
	m_Buttonp[1].m_y = m_yPos + 65;
	m_Buttonp[2].m_y = m_yPos + 335;
	m_Buttonp[3].m_y = m_yPos + 370;
	for (int i = 0; i < 4; i++)
	{
		m_ButtonText[i].SetXCenter(m_Buttonp[i].m_x + m_Buttonp[i].GetShowWidth() / 2);
		m_ButtonText[i].SetY(m_Buttonp[i].m_y + 3);
		m_ButtonText[i].UpdateXCenter();
	}
	UpdateList(m_nowPage);

	m_Rect.left = m_xPos + 3;
	m_Rect.right = m_Rect.left + 120;
	m_Rect.top = m_yPos + _yStart;
	m_Rect.bottom = m_Rect.top + 230;
	return true;
}

bool cFriend::AddFriend(string filepath)
{
	cObj* Obj = new cObj;
//	g_pMainState->LoadCharacterData2(Obj, filepath);
	cCharacter* pc = (cCharacter*)Obj->m_pIndex;
	cPcData * pcdata = &pc->m_PcData;
	sFriendList lis;
	//lis.m_bOnLine = false;
	lis.m_Name = pcdata->m_Name;
//	lis.m_dataFileName = pcdata->m_dataFileName;
	lis.m_Feeling = 0;
//	lis.m_traderLV = pc->m_PcData.m_traderLV;
	//记录类型
	lis.m_modeid = pcdata->modeid;
//	lis.m_stronglv = pcdata->m_StrongLv;//属性加成
	lis.m_money = 0;
	//武器造型
	if (pcdata->m_Equips[2].GetNum())
	{
		lis.m_weaponid = pcdata->m_Equips[2].GetID();
		lis.m_weapontype = pcdata->m_Equips[2].GetType();
	}
	else
	{
		lis.m_weapontype = -1;
		lis.m_weaponid = -1;
	}
	//染色
	lis.m_Ranse = pcdata->m_RanSe;

	lis.m_ZuoQiRanse = pcdata->m_ZuoQiRanSe;

	//坐骑
	lis.m_bOnZuoQi = pcdata->m_bOnZuoQi; //是否坐上坐骑
	lis.m_ZuoQiID = pcdata->m_ZQ;
	lis.m_bZhuangShi = pcdata->m_ZuoQi.m_ZhuangShi.GetNum();
	if (lis.m_bZhuangShi)
	{
		lis.m_ZhuangShiID = pcdata->m_ZuoQi.m_ZhuangShi.GetID();
	}
	lis.m_ZhuangShiRanse = pcdata->m_ZhuangShiRanSe;

	lis.m_money = 29999999;//BUG
	for (int i = 0; i < m_FriendList.size(); i++)
	{
		if (0 == m_FriendList[i].m_Name.compare(lis.m_Name))
		{
			m_FriendList.erase(m_FriendList.begin() + i);
			break;
		}
	}
	m_FriendList.push_back(lis);
	Obj->Free();
	SAFE_DELETE(Obj);
	return true;
}

bool cFriend::UpdateList(int page/*=-1*/)
{
	if (page == -1)
		page = m_nowPage;
	else m_nowPage = page;
	m_NameNum = m_FriendList.size() - page * m_MaxNameNum;
	if (m_NameNum<0)return false;
	if (m_NameNum > m_MaxNameNum)m_NameNum = m_MaxNameNum;

	int k;
	for (int i = m_nowPage * m_MaxNameNum; i < (m_nowPage + 1) * m_MaxNameNum && i < m_FriendList.size(); ++i)
	{
		k = i % m_MaxNameNum;
		if (m_FriendList[i].CheckInTeam())
		{
			m_NameList[k].SetColor(RGB(0, 0, 0));
		}
		else
		{
			m_NameList[k].SetColor(RGB(0, 126, 0));
		}
		cPcData pcd;
//		pcd.Read(m_FriendList[i].m_dataFileName, g_pathFriend);
		m_NameList[k].SetString(pcd.m_Name);
		m_NameList[k].m_NeedShow = true;
		m_NameListHead[k].Load(m_FriendList[i].GetFriendHead());
	}
	m_NameNum = k + 1;
	m_Back.m_bMove = true;
	return true;
}

bool cFriend::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		if (m_TrueFriendSelect >= 0)
		{//把之前的变回来	
			if (m_FriendList[m_TrueFriendSelect/* + m_nowPage * m_MaxNameNum*/].CheckInTeam()) //可以被邀请的角色名字是绿色
			{
				m_NameList[m_TrueFriendSelect % m_MaxNameNum].SetColor(RGB(0, 0, 0));
			}
			else  //不可以被邀请的角色名字是黑色
			{
				m_NameList[m_TrueFriendSelect % m_MaxNameNum].SetColor(RGB(0, 128, 0));
			}
		}
		m_TrueFriendSelect = m_Select + m_MaxNameNum * m_nowPage;
		m_NameList[m_Select/*m_TrueFriendSelect*/].SetColor(RGB(255, 0, 0));
		// 		if (m_friendqianghua.m_NeedShow)
		// 		{
		// 			m_friendqianghua.Set(m_FriendList[m_TrueFriendSelect]);
		// 		}
		if (m_FriendList[m_TrueFriendSelect].CheckInTeam()) //可以被邀请的角色名字是绿色
		{
			m_Buttonp[0].SetFrame帧(3);
		}
		else m_Buttonp[0].SetFrame帧(0);
		break;
	case 10://邀请入队
		m_Buttonp[0].SetFrame帧(1);
		if (m_TrueFriendSelect < 0)return true;
		if (m_FriendList.size() <= m_TrueFriendSelect)return true;
		//		if (-1 == g_pMainState->CheckInTeam(m_FriendList[m_TrueFriendSelect].m_Name))break;
		if (m_FriendList[m_TrueFriendSelect].CheckInTeam())return true;
		if (Invite(m_TrueFriendSelect))
		{
			m_NameList[m_TrueFriendSelect].SetColor(0);
		}
		// 		{
		// 			int index = -1;
		// 			forr(m_FriendList, i)
		// 			{
		// 				if (m_FriendList[i].m_Name == m_NameList[m_TrueFriendSelect].GetString())
		// 				{
		// 					index = i;
		// 					break;
		// 				}
		// 			}
		// 			if (index >= 0)
		// 			{
		// 				if (m_FriendList[index].CheckInTeam())return true;
		// 				if (Invite(index))
		// 				{
		// 					if (m_TrueFriendSelect + m_nowPage * m_MaxNameNum >= 0)
		// 						m_NameList[m_TrueFriendSelect + m_nowPage * m_MaxNameNum].SetColor(0);
		// 				}
		// 			}
		// 		}
		break;
	case 11:
		m_Buttonp[1].SetFrame帧(1);
		if (m_TrueFriendSelect < 0)return true;

		{
			m_friendqianghua.Set(m_FriendList[m_TrueFriendSelect]);
			m_friendqianghua.OnOff(true);
			// 			int index = -1;
			// 			forr(m_FriendList, i)
			// 			{
			// 				if (m_FriendList[i].m_Name == m_NameList[m_TrueFriendSelect + m_nowPage*m_MaxNameNum].GetString())
			// 				{
			// 					index = i;
			// 					break;
			// 				}
			// 			}
			// 			if (index >= 0)
			// 			{
			// 				m_friendqianghua.Set(m_FriendList[index]);
			// 				m_friendqianghua.OnOff(true);
			// 			}
		}

		// 		m_friendqianghua.Set(m_FriendList[m_TrueFriendSelect+m_nowPage*m_MaxNameNum]);
		// 		m_friendqianghua.OnOff(true);
		break;
	case 12://给钱
		if (m_nowPage <= 0)
		{
			break;
		}
		m_nowPage = 0;
		OnOff(false);
		OnOff(true);
		//		{
		// 			m_Buttonp[2].SetFrame帧(1);
		// 			if (m_TrueFriendSelect < 0)return true;
		// 			g_pMainState->m_YingHang.SetMode(0, &m_FriendList[m_TrueFriendSelect]);
		// 			g_pMainState->m_YingHang.OnOff(true);
		// 			g_pMainState->m_YingHang.m_ShuRu.SetMaxNum(g_pCharacter->m_PCData.m_Money[0]);
		// 			ostringstream oss;
		// 			oss << m_FriendList[m_TrueFriendSelect + m_nowPage * m_MaxNameNum].m_money;
		// 			g_pMainState->m_YingHang.m_CunYing.SetString(oss.str());
		//				
		//		}
		break;
	case 13: //要钱
		if (m_nowPage == 1 || m_nowPage < 0 || m_FriendList.size() <= m_MaxNameNum)
		{
			break;
		}
		m_nowPage = 1;
		OnOff(false);
		OnOff(true);
		//		{
		// 			m_Buttonp[3].SetFrame帧(1);
		// 			if (m_TrueFriendSelect < 0)return true;
		// 			g_pMainState->m_YingHang.SetMode(1, &m_FriendList[m_TrueFriendSelect]);
		// 			g_pMainState->m_YingHang.OnOff(true);
		//		}
		break;
	case 20://关闭
		OnOff(false);
		m_Cancel.SetFrame帧(1);
		break;

	case 26://移动

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
	case 27://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	}
	return true;
}

bool cFriend::Invite(int id, int idlepos)
{
	//有没有空位
	if (idlepos == -1)
	{
		int i = 0;
		for (; i < 5; i++)
		{
			if (!g_pMainState->m_FightWorkList[g_pMainState->m_InterfaceTeam.GetTeamTurn(i)].isExist)
			{
				idlepos = g_pMainState->m_InterfaceTeam.GetTeamTurn(i);
				break;
			}
		}
		if (5 == i)return false;
	}

	//检测是否已经存在于敌我双方中
	for (int i = 0; i < 20; i++)
	{
		if (g_pMainState->m_FightWorkList[i].isExist)
		{
			cPropertyData* pPetdata;
			g_pMainState->m_FightWorkList[i].m_pObj->GetPropertyData(pPetdata);
			if (0 == pPetdata->m_Name.compare(m_FriendList[id].m_Name))
			{
				return false;
			}
		}
	}
//	g_pMainState->LoadCharacterData2(idlepos, m_FriendList[id].m_dataFileName);
	sFightWork& list = g_pMainState->m_FightWorkList[idlepos];

	cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
// 	pc->m_PcData.FollowlvAddPoint(g_pCharacter->m_PcData.m_Lv, false, true, true);
// 	pc->m_PcData.FollowShoe();
//	pc->m_PCData.m_AiLv = pc->m_PCData.m_ZiZhi.m_Growing < cct::get()->putMenpaiSkills.size();
	if (idlepos < 10)
	{
		pc->m_PcData.m_Controler.Set(0, 0);
//		if (g_pCharacter->m_PcData.m_Lv >= cct::LvFor飞升)pc->m_PcData.m_bDuJie = true;
	}
	else pc->m_PcData.m_Controler.Set(0, 1);
	pc->m_PcData.m_IDinFightWorkList = idlepos;
//	pc->m_PcData.m_Popularity = g_pCharacter->m_PcData.m_Popularity;
	list.isExist = true;
	list.SetDie(false);
	list.m_pObj->SetDirection(g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->GetDirection());

	list.m_pObj->SetX(g_pHeroObj->GetX());
	list.m_pObj->SetY(g_pHeroObj->GetY());
	list.m_pObj->Stand();


	list.m_FriendListid = id;//记录

	/*pc->m_PCData.m_RanSe = m_FriendList[id].m_Ranse;


	if (m_FriendList[id].m_bOnZuoQi)
	{
	pc->m_PCData.m_bOnZuoQi = m_FriendList[id].m_bOnZuoQi;
	g_pMainState->m_ZuoQi.GetZuoQi(pc->m_PCData, m_FriendList[id].m_ZuoQiID);
	pc->m_PCData.m_ZuoQiRanSe = m_FriendList[id].m_ZuoQiRanse;

	}*/


	sFriendList& list2 = m_FriendList[id];
	//	int jinjienum = (g_pCharacter->m_PcData.m_Lv + 10) / 60;
	for (int i = 0; i < list2.m_BBList.size(); i++)
	{
		cPet* ppet = new cPet;
		ppet->Set(&list2.m_BBList[i], list2.m_stronglv);
//		if (*pc->m_PcData.m_Lv >= cct::get()->lv进阶)
//			ppet->m_PetData.SetJinJie((pc->m_PcData.m_Lv + 10) / cct::get()->per进阶);
//		g_pMainState->GivePcAPet(idlepos, ppet);
	}
	g_pMainState->SetFightPet(idlepos, list2.m_FightBB, false);

	//
	// 	sZiZhi& zz = list2.m_zizhi;
	// 	pc->m_PCData.AddAtkZZ(zz.m_ATKZZ);
	// 	pc->m_PCData.AddDefZZ(zz.m_DEFZZ);
	// 	pc->m_PCData.AddMagZZ(zz.m_MAGZZ);
	// 	pc->m_PCData.AddHpZZ(zz.m_HPZZ);
	// 	pc->m_PCData.AddAvoidZZ(zz.m_AVOIDZZ);
	// 	pc->m_PCData.AddSpdZZ(zz.m_SPDZZ);
	// 	pc->m_PCData.AddGrowing(zz.m_Growing);


	//	g_pMainState->FollowLv(idlepos);
	//玩家设置修正
	pc->m_PcData.m_JinJieNum = list2.m_JinJieNum;
	if (list2.m_weapontype > -1)
	{
		int id = pc->m_PcData.m_Equips[2].GetID();
		pc->m_PcData.m_Equips[2].Set(list2.m_weapontype, id);
		cPcData *data = &pc->m_PcData;
		sItem2 *item = &data->m_Equips[2];
//		Q_ASSERT(item->m_Property.size(), "武器空属性(定制)");
//		item->Set(m_pdata->m_weapontype, m_pdata->m_weaponid);
//		g_pMainState->m_ItemManage.AutoItemProperty(item, data, cct::get()->getDesbinOf武器(data->m_MengPaiID));
//		g_pMainState->m_ItemManage.AutoFuShi(item, data->m_Lv, eMengPai(data->m_MengPaiID));
//		g_pMainState->m_InterfaceItem.Add(59, *data, item);
//		g_pMainState->m_InterfaceItem.UseItem(59, *data);
	}
	pc->m_PcData.m_RanSe = list2.m_Ranse;


	pc->m_PcData.m_bOnZuoQi = list2.m_bOnZuoQi;
	if (list2.m_ZuoQiID > -1)
	{
		pc->m_PcData.m_ZuoQiRanSe = list2.m_ZuoQiRanse;
		g_pMainState->m_ZuoQi.GetZuoQi(pc->m_PcData, list2.m_ZuoQiID);
		if (list2.m_ZhuangShiID > -1)
		{
			pc->m_PcData.m_ZuoQi.m_ZhuangShi.Set(24, list2.m_ZhuangShiID);
			pc->m_PcData.m_ZhuangShiRanSe = list2.m_ZhuangShiRanse;
		}
	}

	list.m_pObj->Reset();
	list.m_pObj->Set(POS_STAND);
	list.m_pObj->MoveShadow();
	g_pMainState->m_PCHead.UpDateHead();

	return true;
}

bool cFriend::Invite(string name, int fighterid)
{
	for (int i = 0; i < m_FriendList.size(); i++)
	{
		if (name == m_FriendList[i].m_dataFileName)
		{
			Invite(i, fighterid);
			g_pMainState->m_PCHead.UpDateHead();
			return true;
		}
	}
	if (AddFriend(name))
	{
		return Invite(name);
	}
	return false;
}

void cFriend::OnOff(bool NeedShow)
{
	//	return ;
	if (m_MessageList.size())
	{
		g_pMainState->m_TriggerDialog.AddTask(m_MessageList[0].messagePath, m_MessageList[0].id, m_MessageList[0].p, m_MessageList[0].taskid);
		m_MessageList.erase(m_MessageList.begin());
		if (!m_MessageList.size())
		{
			g_pMainState->m_Menu.m_Info.SetStatic(true);
			g_pMainState->m_Menu.m_Info.SetFrame(0);
		}
		return;
	}
	if (NeedShow == m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (m_NeedShow)
	{
		Init();
		if (m_TrueFriendSelect >= m_FriendList.size())
		{
			m_TrueFriendSelect = m_FriendList.size() - 1;
		};
		UpdateList(m_nowPage);
		if ((!m_nowPage && m_TrueFriendSelect >= 0 && m_TrueFriendSelect < m_MaxNameNum) || (m_nowPage && m_TrueFriendSelect >= m_MaxNameNum))
		{
			m_NameList[m_TrueFriendSelect % m_MaxNameNum].SetColor(RGB(255, 0, 0));
		}

		// 		if (m_TrueFriendSelect >= m_NameNum)
		// 		{
		// 			if (m_TrueFriendSelect > -1)
		// 			{
		// 				if (m_FriendList[m_TrueFriendSelect + m_nowPage * m_MaxNameNum].CheckInTeam()) //可以被邀请的角色名字是绿色
		// 				{
		// 					m_NameList[m_TrueFriendSelect].SetColor(RGB(0, 0, 0));
		// 				}
		// 				else  //不可以被邀请的角色名字是黑色
		// 				{
		// 					m_NameList[m_TrueFriendSelect].SetColor(RGB(0, 128, 0));
		// 				}
		// 			}
		// 			m_TrueFriendSelect = m_NameNum - 1;
		// 			if (m_TrueFriendSelect>-1)
		// 			m_NameList[m_TrueFriendSelect].SetColor(RGB(255, 0, 0));
		// 		}
		m_Sleeptime = 0;
	}
	//	else
	//	{
	// 		if (m_nowPage == 1)
	// 		{
	// 			m_nowPage = 0;
	// 		}
	// 		else
	// 		{
	// 			int k = 0;
	// 			k = m_FriendList.size();
	// 			forr(m_FriendList, i)
	// 			{
	// 				if (m_FriendList[i + m_nowPage * m_MaxNameNum].CheckInTeam())
	// 				{
	// 					continue;
	// 				}
	// 				++k;
	// 			}
	// 			if (k > m_MaxNameNum)
	// 			{
	// 				m_nowPage = 1;
	// 			}
	// 		}
	//	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}

bool cFriend::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		if (1)
		{
			g_pMainState->m_ChaKan.Set(m_FriendList[m_Select + m_nowPage * m_MaxNameNum]);
			g_pMainState->m_ChaKan.OnOff(true);

			// 			int index = -1;
			// 			forr(m_FriendList, i)
			// 			{
			// 				if (m_FriendList[i].m_Name == m_NameList[m_Select + m_nowPage * m_MaxNameNum].GetString())
			// 				{
			// 					index = i;
			// 					break;
			// 				}
			// 			}
			// 			if (index >= 0)
			// 			{
			// 				g_pMainState->m_ChaKan.Set(m_FriendList[index]);
			// 				g_pMainState->m_ChaKan.OnOff(true);
			// 				cObj* Obj = new cObj;
			// 				g_pMainState->LoadCharacterData2(Obj, m_FriendList[index].m_dataFileName);
			// 				cCharacter* pc1 = (cCharacter*)Obj->m_pIndex;
			// 				g_pMainState->m_State.SetFight(pc1);
			// 				g_pMainState->m_State.OnOff(true);
			//			}
		}
		break;
	case 20:
		OnOff(false);
		break;
	default:
		break;
	}

	return true;
}

void cFriend::JuanZeng(int num)
{

	g_pCharacter->m_PcData.m_Money[0] -= num;
	if (g_pCharacter->m_PcData.m_Money[0] < 0)
	{
		g_pCharacter->Talk("钱不够.....");
		g_pCharacter->m_PcData.m_Money[0] += num;
		return;
	}
	m_FriendList[m_TrueFriendSelect/* + m_nowPage * m_MaxNameNum*/].m_money += num;
}
void cFriend::UnJuanZeng(int num)
{
	m_FriendList[m_TrueFriendSelect + m_nowPage * m_MaxNameNum].m_money -= num;
	if (m_FriendList[m_TrueFriendSelect + m_nowPage * m_MaxNameNum].m_money  < 0)
	{
		g_pCharacter->Talk("被TA拒绝了呢....");
		m_FriendList[m_TrueFriendSelect/* + m_nowPage * m_MaxNameNum*/].m_money += num;
	}
	g_pCharacter->m_PcData.m_Money[0] += num;
}

void cFriend::Save(ofstream& File)
{//保存到文件
	File << "\n";
	File << m_MessageList.size() << " ";
	for (int i = 0; i < m_MessageList.size(); i++)
	{
		m_MessageList[i].Save(File);
	}
	File << "\n";
	File << "保存好友列表" << "\n";
	File << m_FriendList.size() << "\n";
	for (int i = 0; i < m_FriendList.size(); i++)
	{
		m_FriendList[i].Save(File);
	}
}

void cFriend::Load(ifstream& File)
{//读取文件
	int nummessage;
	File >> nummessage;
	if (nummessage)
	{
		g_pMainState->m_Menu.m_Info.SetStatic(false);
		m_MessageList.resize(nummessage);
		for (int i = 0; i < nummessage; i++)
		{
			m_MessageList[i].Load(File);
		}
	}
	else
	{
		m_MessageList.clear();
		g_pMainState->m_Menu.m_Info.SetStatic(true);
	}
	g_pMainState->m_Menu.m_Info.SetFrame(0);
	int numfriend;
	string dustbin;
	getline(File, dustbin);
	getline(File, dustbin);
	if (dustbin != "保存好友列表")
		ERRBOX;
	File >> numfriend;

	m_FriendList.resize(numfriend);
	for (int i = 0; i < numfriend; i++)
	{
		m_FriendList[i].Load(File);
	}
}

bool cFriend::UnInvite(string name)
{
	if (name == g_pCharacter->GetName())
	{
		return false;
	}
	for (int i = 0; i < 5; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[g_pMainState->m_InterfaceTeam.GetTeamTurn(i)];
		string targetname = list.m_pObj->m_TrueName.GetString();
		if (targetname == name)
		{
			UnInvite(i);
			return true;
		}
	}
	return false;
}

bool cFriend::UnInvite(int id)
{
	int trueid = g_pMainState->m_InterfaceTeam.GetTeamTurn(id);
	if (!g_pMainState->m_FightWorkList[trueid].isExist)return true;
	int i = id;
	for (; i < 4;)
	{
		int nexttrueid = g_pMainState->m_InterfaceTeam.GetTeamTurn(i + 1);
		if (g_pMainState->m_FightWorkList[nexttrueid].isExist)
		{
			g_pMainState->m_InterfaceTeam.SwapTeamTurn(i, i + 1);
		}
		else break;
		++i;
	}
	g_pMainState->FreeFightList(g_pMainState->m_InterfaceTeam.GetTeamTurn(i));
	g_pMainState->m_PCHead.UpDateHead();
	return true;
}

void cFriend::AddMeesage(string path, int id, cTaskFather* ptask, int taskid)
{
	sMessageList list;
	list.messagePath = path;
	list.p = ptask;
	list.taskid = taskid;
	list.id = id;
	m_MessageList.push_back(list);
	g_pMainState->m_Menu.m_Info.SetStatic(false);
}

int cFriend::FindFriend(string name)
{
	for (int i = 0; i < m_FriendList.size(); i++)
	{
		if (!m_FriendList[i].m_dataFileName.compare(name))return i;
	}
	AddFriend(name);
	return FindFriend(name);
}

void cFriend::AddDay()
{
	for (int i = 0; i < m_FriendList.size(); i++)
	{
		sFriendList& l = m_FriendList[i];
		int money = (l.m_stronglv + 100)*g_pCharacter->m_PcData.m_Lv * 300;
		if (l.m_traderLV)
		{
			money += (money*(20 + l.m_traderLV)) / 100;
		}
		if (l.m_stronglv<100)
			l.m_stronglv += 1;
	}
}

void cFriend::ReMove(string name)
{
	for (int i = 0; i < m_FriendList.size(); i++)
	{
		if (m_FriendList[i].m_Name == name)
		{
			m_FriendList.erase(m_FriendList.begin() + i);
			return;
		}
	}
}
