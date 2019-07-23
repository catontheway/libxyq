#include "_global.h"


std::string cInterfaceFriendQiangHua2::getString(int i)
{
	switch (i)
	{
	case 0:
		return "退出";
	case 1:
		return cct::getINT(16) ? "静音" : "音乐";
	case 2:
		return cct::getINT(17) ? "无声" : "声效";
	case 3:
		return toString("走速%d", cct::getINT(7));
	case 4:
		return cct::getINT(8) ? "显示血条" : "隐藏血条";
	case 5:
		return "信息栏";
	case 6:
	{
		int ui = cct::getINT(5);
		if (ui == 1)
		{
			return "国韵ui";
		}
		if (ui == 2)
		{
			return "水晶ui";
		}
		if (ui == 3)
		{
			return "雅致ui";
		}
		return "经典ui";
	}
	case 7:
		return cct::getINT(6) ? "迭代模型" : "经典模型";
	case 8:
		return cct::getINT(22) ? "迭代法术" : "经典法术";
	case 9:
		return g_pMainState->_guaji ? "挂机中" : "不挂机";
	case 10:
		return g_pMainState->_autoGhost ? "抓鬼中" : "自动抓鬼";
	case 11:
		return "";
	case 12:
		return "";
	case 13:
		return "";
	case 14:
		return "签到";
	default:
		break;
	}
	return "";
}


bool cInterfaceFriendQiangHua2::initShow()
{
	forr(_ts, i)
	{
		_ts[i]->SetString(getString(i));
	}
	return true;
}



void cInterfaceFriendQiangHua2::onClick(int i)
{
	switch (i)
	{
	case 0:
		g_pMainState->m_InterfaceSystem2.OnOff(!g_pMainState->m_InterfaceSystem2.m_NeedShow);
		break;
	case 1:
		cct::switchINT(16);
		if (cct::getINT(16))
			g_pMainState->m_Mp3.Stop();
		else
			g_pMainState->m_Mp3.Play();
		break;
	case 2:
		cct::switchINT(17);
		break;
	case 3:
		if (1)
		{
			if (++g_GlobalValues[7] > 5)
			{
				cct::setINT(7, 1);
			}
		}
		break;
	case 4:
		cct::switchINT(8);
		break;
	case 5: 
		cct::switchINT(9);
		break;
	case 6:
		if (++g_GlobalValues[5] > 3)
		{
			cct::setINT(5, 0);
		}
		cct::autoSave();
		g_pMainState->m_Tags.Add("下次登录生效");
		break;
	case 7:
		cct::switchINT(6);
		cct::autoSave();
		g_pMainState->m_Tags.Add("下次登录生效");
		break;
	case 8:
		cct::switchINT(22);
		cct::autoSave();
		break;
	case 9:
		g_pMainState->_guaji = !g_pMainState->_guaji;
		if (g_pMainState->_guaji)
		{
			g_pMainState->m_Tags.Add("野外站着也会遇怪");
			g_pMainState->m_Tags.Add("建议烧双先设置队伍自动/默认法术");
		}
		break;
	case 10:
		if (!g_pMainState->_autoGhost)
		{
			if (g_StateType == STATE_FIGHT)
			{
				g_pMainState->m_Tags.Add("战斗中不可以");
				break;
			}
			bool isAuto = true;
			bool isDski = true;
			int num = g_pMainState->m_InterfaceTeam.getLeaveBegin();
			for (int i = 0; i < num; ++i)
			{
				if (isDski && g_pMainState->m_FightWorkList[i].m_FriendListid < 0)
				{
					isDski = false;
				}
				if (isAuto && g_pMainState->m_pFightState->m_FightMenu.CheckControl(i))
				{
					isAuto = false;
				}
			}
			if (!isAuto && !isDski)
			{
				g_pMainState->m_Tags.Add("请先设置队伍自动/默认法术");
				break;
			}

			for (int i = c_InterfaceShowNum - 1; i >= 0; i--)
			{
				if (g_pMainState->m_Interface[i])
				{
					g_pMainState->m_Interface[i]->OnOff(false);
				}
			}

			g_pMainState->_autoGhost = 1;
			g_pMainState->m_Tags.Add("进入自动抓鬼模式");
		}
		else
		{
			g_pMainState->_autoGhost = 0;
		}
		break;
	case 14:
		g_pMainState->_uiSign.OnOff();
		break;
		SetFullScreen2(g_bFillScreen = !g_bFillScreen);
		break;
	}
}




bool cInterfaceFriendQiangHua2::Init()
{
	if (!cInterfaceFather::Init())
	{
		return false;
	}
	loadBack(0x694F39D1);

	sChild tTitle("系统设置", 100, 3);
	addChild(tTitle);

	forv(_ts, i)
	{
		sChild btn(&g_pMainState->m_Button4, 22 + (i % 3) * 80, 52 + (i / 3) * 30);
		_ts[i] = (cText*)btn.ptr2;
		btn.tag = i;
		btn.onClick = [&](const sChild* c)
		{
			onClick(c->tag);
			initShow();
		};
		addChild(btn);
	}

// 	if (m_bInit)return true;
// 	m_bInit = true;
// 	m_Back.Load(0x694F39D1);
// 	m_Back.SetStatic(true);
// 	m_Cancel.Set(&g_pMainState->m_Cancel);
// 	m_Cancel.m_bStatic = true;
// 	m_title.SetColor(RGB(255, 255, 255));
// 	m_title.SetString("系统设置");
// 
// 	for (int i = 0; i < m_Buttonp.size(); i++)
// 	{
// 		m_Buttonp[i].Set(&g_pMainState->m_Button4);
// 		m_Buttonp[i].m_bStatic = true;
// 		m_Text[i].SetColor(RGB(255, 255, 255));
// 	}
// 

	initShow();
 	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);

	return true;
}





void cInterfaceFriendQiangHua2::SavePos(ofstream& File)
{
	//保存地点
	File << g_strSpace; // "\n\r";
	File << g_pMainState->m_Map.m_MapName << g_strSpace;
	File << g_pHeroObj->GetX() / 20 << g_strSpace;
	File << (g_pMainState->m_Map.m_pMap->m_Height - g_pHeroObj->GetY()) / 20 << g_strSpace;

}

void cInterfaceFriendQiangHua2::LoadPos(ifstream& File)
{
	g_pMainState->m_Map.m_MapName = "";//
	/*for (int i = 0; i < g_pMainState->m_Map.m_numberOfNpc; i++)
	{
	g_pMainState->m_Map.m_pNpc[i]->Free();
	}
	g_pMainState->m_Map.m_numberOfNpc = 0;
	g_pMainState->m_Map.m_MapNumber = -1;*/
	//读取地点
	int xpos, ypos;
	string mapname;
	File >> mapname;
	File >> xpos;
	File >> ypos;
	if (g_pMainState->m_FangWu.GetMapName() == mapname)
		g_pMainState->m_FangWu.GoIn();
	else
	{
		g_pMainState->m_Map.LoadMap(xpos, ypos, (char*)mapname.c_str(), false);
	}
}

void cInterfaceFriendQiangHua2::SaveFightList(ofstream& File)
{
	File << g_pMainState->m_HeroID << " ";
	g_pMainState->m_InterfaceTeam.Save(File);
	File << "\n";
	for (int i = 0; i < 5; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
		File << list.isExist << " ";
		File << list.CheckDie() << " ";
		if (!list.isExist)continue;
		File << list.m_pObj->m_IndexType << " ";
		if (list.isExist)
		{
			switch (list.m_pObj->m_IndexType)
			{
			case INDEXTYEP_CHARACTER:
				if (1)
				{
					cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
// 					if (i != g_pMainState->m_HeroID)
// 					{
// 						//检测召唤兽进阶
// 						int jinjienum = (g_pCharacter->m_PcData.m_Lv + 10) / cct::per进阶;
// 						for (int i2 = 0; i2 < pc->m_PcData.m_NumofBB; i2++)
// 						{
// 							cPropertyData& Pet = pc->m_PcData.m_pPets[i2]->m_PetData;
// 							if (Pet.m_JinJieNum.m_index < jinjienum)
// 							{
// 								Pet.SetJinJie(jinjienum - Pet.m_JinJieNum.m_index);
// 								Pet.m_RanSe.Reset();
// 								sFriendList* plist = g_pMainState->m_Friend.FindFriend2(pc->m_PcData.m_dataFileName);
// 								for (uint i3 = 0; i3 < plist->m_BBList.size(); i3++)
// 								{
// 									if (plist->m_BBList[i3].m_name == Pet.m_Name)
// 									{
// 										plist->m_Ranse.Reset();
// 									}
// 								}
// 							}
// 						}
// 					}
					pc->m_PcData.Save(File);
				}
				break;
			case INDEXTYEP_PET:
				if (1)
				{
					cPet* pc = (cPet*)list.m_pObj->m_pIndex;
					pc->m_PetData.Save(File);
				}
				break;
			default:
				ERRBOX(0);
				break;
			}
		}

	}
}

void cInterfaceFriendQiangHua2::LoadFightList(ifstream& File)
{
	int heroid;
	File >> heroid;
	g_pMainState->m_InterfaceTeam.Load(File);
	int indextype;
	for (int i = 0; i < 5; i++)
	{
		g_pMainState->FreeFightList(i);
	}
	for (int i = 0; i < 5; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
		list.m_pObj->m_TrueName.SetColor(RGB(0, 255, 0));
		File >> list.isExist;
		bool bdie;
		File >> bdie;
		list.SetDie(bdie);
		if (!list.isExist)continue;
		File >> indextype;
		list.m_pObj->SetDataType(indextype);
		if (list.isExist)
		{
			switch (list.m_pObj->m_IndexType)
			{
			case INDEXTYEP_CHARACTER:
				if (1)
				{
					cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
					pc->m_PcData.Load(File);
					pc->SetData(&g_pMainState->m_pCharacterDataList[pc->m_PcData.modeid]);
					list.m_pObj->m_TrueName.SetString(pc->m_PcData.m_Name);
					if (i == heroid)g_pMainState->SetCharacter(heroid);
					if (pc->m_PcData.m_FightPetID > -1)
					{
						int petid = pc->m_PcData.m_FightPetID;
						pc->m_PcData.m_FightPetID = -1;
						g_pMainState->SetFightPet(i, petid);
					}
// 					if (i != g_pMainState->m_HeroID)
// 					{
// 						pc->m_PcData.FollowShoe();
// 					}

				}
				break;
			case INDEXTYEP_PET:
				if (1)
				{
					cPet* pc = (cPet*)list.m_pObj->m_pIndex;
					pc->m_PetData.Load(File);
					pc->SetData(g_pMainState->m_PetDataManager.GetPetData(pc->m_PetData.modeid));
					list.m_pObj->m_TrueName.SetString(pc->m_PetData.m_Name);
				}
				break;
			default:
				ERRBOX(0);
				return;
			}
			list.m_pObj->Reset();
			list.m_pObj->Set(POS_STAND);
		}

	}
	//	g_pMainState->SetCharacter(g_pMainState->m_HeroID);
	/*g_pHeroObj->Reset();
	g_pHeroObj->Set(POS_STAND);*/

	//g_pMainState->m_InterfaceTeam.SetFormation(normal);
	//g_pMainState->m_InterfaceTeam.SetFormation(normal, true);
}

void cInterfaceFriendQiangHua2::SaveTrigger(ofstream& File)
{
	SaveATrigger(&g_pMainState->m_TriggerFightTurn, File);
	SaveATrigger(&g_pMainState->m_TriggerFightStart, File);
	g_pMainState->m_TriggerGive.Save(File);
	SaveATrigger(&g_pMainState->m_TriggerFightSuccess, File);
	g_pMainState->m_TriggerObj.Save(File);
	g_pMainState->m_TriggerObjMap.Save(File);
	g_pMainState->m_Triggerlv.Save(File);
	g_pMainState->m_TriggerGive.Save(File);
	g_pMainState->m_TriggerDialog.Save(File);
	//g_pMainState->m_TriggerTime.Save(File);
	g_pMainState->m_Job.Save(File);
	File << "////////////////保存剧情";
//	g_pMainState->m_ZhuXian.Save(File);
	g_pMainState->m_ZhiXian.Save(File);
	g_pMainState->m_ZhiXian2.Save(File);
	g_pMainState->m_ZhiXian3.Save(File);

}
void cInterfaceFriendQiangHua2::LoadTrigger(ifstream& File)
{
	LoadATrigger(&g_pMainState->m_TriggerFightTurn, File);
	LoadATrigger(&g_pMainState->m_TriggerFightStart, File);
	g_pMainState->m_TriggerGive.Load(File);
	LoadATrigger(&g_pMainState->m_TriggerFightSuccess, File);
	g_pMainState->m_TriggerObj.Load(File);
	g_pMainState->m_TriggerObjMap.Load(File);
	g_pMainState->m_Triggerlv.Load(File);
	g_pMainState->m_TriggerGive.Load(File);
	g_pMainState->m_TriggerDialog.Load(File);
	//g_pMainState->m_TriggerTime.Load(File);
	g_pMainState->m_Job.Load(File);
	string dustbin;
	File >> dustbin;
//	g_pMainState->m_ZhuXian.Load(File);
	g_pMainState->m_ZhiXian.Load(File);
	g_pMainState->m_ZhiXian2.Load(File);
	g_pMainState->m_ZhiXian3.Load(File);
}
void cInterfaceFriendQiangHua2::SaveATrigger(cTrigger* trigger, ofstream& File)
{
	File << "\n";
	File << trigger->m_TaskList.size() << " ";
	for (int i = 0; i < trigger->m_TaskList.size(); i++)
	{
		File << trigger->m_TaskList[i].m_pTask->m_type << " ";
		File << trigger->m_TaskList[i].m_pTask->m_HuanShu << " ";
		File << trigger->m_TaskList[i].m_Stage << " ";
	}
	File << "\n";
}
void cInterfaceFriendQiangHua2::LoadATrigger(cTrigger* trigger, ifstream& File)
{
	int num;
	File >> num;
	int stage;
	int type;
	int huanshu;
	trigger->Clear();
	for (int i = 0; i < num; i++)
	{
		File >> type;
		File >> huanshu;
		File >> stage;
		cTaskFather* ptask = g_pMainState->FindTaskByID(type);
		ptask->m_HuanShu = huanshu;
		trigger->AddTask(ptask, stage);
	}

}
void cInterfaceFriendQiangHua2::SaveFriend(ofstream& File)
{
	g_pMainState->m_Friend.Save(File);
}
void cInterfaceFriendQiangHua2::LoadFriend(ifstream& File)
{
	g_pMainState->m_Friend.Load(File);
}

void cInterfaceFriendQiangHua2::GetSaveTitle(vector<string>& strselect)
{
	strselect.resize(4);
	int nowid = -1;
	for (int i = 0; i < 4; i++)
	{
		ifstream File3;
		ostringstream oss;
		//		oss << g_pathSave;
		oss << i;
		oss << ".txt";
		File3.open(oss.str());
		if (!File3)
		{
			strselect[i] = "无";
			continue;
		}
		oss.str("");
		//读取地点

		int xpos, lv;
		//保存时间
		File3 >> xpos;
		File3 >> lv;
		if (nowid < xpos)
		{
			nowid = xpos;
		}
		oss << "第" << xpos << "次存档,等级:" << lv;
		strselect[i] = oss.str();
}
	ifstream File;
	ostringstream oss;
	//	oss << g_pathSave << "5.txt";
	File.open(oss.str());
	if (!File)return;
	int newid;
	File >> newid;
	File.close();
	strselect[newid] += "    最新";
}



bool cInterfaceFriendQiangHua2::ProcessInputMore()
{
	return false;
	switch (m_bMode)
	{
	case 1://保存
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4)
			{

				Save(g_pMainState->m_Dialog.m_retSelect);
				g_pMainState->m_Tags.Add("游戏已保存");
			}
			m_bMode = 0;
		}
		return true;
	case 2://读取
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4 && g_pMainState->m_Dialog.m_retSelect > -1)
			{
				Load(g_pMainState->m_Dialog.m_retSelect);
				OnOff(false);
			}
			m_bMode = 0;
		}
		return true;
	}
	return false;
}

#if 0
void cInterfaceFriendQiangHua2::OnOff(bool NeedShow)
{
	if (g_pMainState->m_Dialog.m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);
	if (NeedShow)
	{
		Init();
//		m_Cancel.SetFrame帧(0);
// 		m_Text[8].SetString("");
// 		m_Text[9].SetString("");
// 		int &grow = g_pCharacter->m_PcData.m_ZiZhi.grow;
// 		const vector<int> &puts = cct::get()->putMenpaiSkills;
// 		if (grow < puts.size())
// 		{
// 			m_Text[8].SetString(g_pMainState->m_SkillManager.GetMengPaiSkill(puts[grow])->m_Name);
// 		}
//
// 		if (g_pCharacter->m_PcData.m_NumofBBSkill > 0)
// 		{
// 			string name = g_pCharacter->m_PcData.m_petSkills[0]->m_Name;
// 			if (name.size() > 8 && name.substr(0, 4) == "高级")
// 			{
// 				name = name.substr(4, name.length() - 4);
// 			}
// 			m_Text[9].SetString(name);
// 		}
		m_Text[0].SetString("退出");
		m_Text[13].SetString("保存");
		m_Text[14].SetString("读取");
		m_Text[1].SetString(!g_pMainState->m_GlobalButton[16] ? "音乐" : "静音");
		m_Text[2].SetString(!g_pMainState->m_GlobalButton[17] ? "声效" : "无声");
		m_Text[3].SetString(toString("走速%d", g_pMainState->m_GlobalButton[7] /*cct::get()->moveSpeedInMap*/));
		m_Text[4].SetString(/*cct::get()->isShowBloodBar*/g_pMainState->m_GlobalButton[8] ? "显示血条" : "隐藏血条");
		m_Text[5].SetString("界面");

	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}




bool cInterfaceFriendQiangHua2::Move(int xPos, int yPos)
{
	m_xPos = xPos;
	m_yPos = yPos;
	m_Back.SetXY(xPos, yPos);
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	m_title.SetXCenter(m_xPos + 130);
	m_title.SetY(m_yPos + 3);
	m_title.UpdateXCenter();
	int xstart, ystart;
	xstart = m_xPos + 22;
	ystart = m_yPos + 52;
	for (int i = 0; i < m_Buttonp.size(); i++)
	{
		m_Buttonp[i].SetXY(xstart + (i % 3) * 80, ystart + (i / 3) * 30);
		m_Text[i].SetXCenter(m_Buttonp[i].GetX() + m_Buttonp[i].GetShowWidth() / 2);
		m_Text[i].SetY(m_Buttonp[i].GetY() + 3);
		m_Text[i].UpdateXCenter();
	}
	return true;
}



bool cInterfaceFriendQiangHua2::ProcessInputMore()
{
	switch (m_bMode)
	{
	case 1://保存
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4)
			{

				Save(g_pMainState->m_Dialog.m_retSelect);
				g_pMainState->m_Tags.Add("游戏已保存");
			}
			m_bMode = 0;
		}
		return true;
	case 2://读取
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4 && g_pMainState->m_Dialog.m_retSelect > -1)
			{
				Load(g_pMainState->m_Dialog.m_retSelect);
				OnOff(false);
			}
			m_bMode = 0;
		}
		return true;
	}
	return false;
}




bool cInterfaceFriendQiangHua2::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}

	m_Select = -1;
	ResetButton();

	switch (m_bMode)
	{
	case 1://保存
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4)
			{
				Save(g_pMainState->m_Dialog.m_retSelect);
				g_pMainState->m_Tags.Add("保存成功");
			}
			m_bMode = 0;
		}
		return true;
	case 2://读取
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4 && g_pMainState->m_Dialog.m_retSelect > -1)
			{
				Load(g_pMainState->m_Dialog.m_retSelect);
				OnOff(false);
			}
			m_bMode = 0;
		}
		return true;
	}

	if (m_bMoveMode)//移动
	{
		m_Select = 106;
		g_pMainState->SetMouseOnMap(false);
		if (!CheckL())m_bMoveMode = false;
		return true;
	}
	if (!isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))return true;
	g_pMainState->SetMouseOnMap(false);
	if (CheckOn(&m_Cancel, 100))return true;
	for (int i = 0; i < m_Buttonp.size(); i++)
		if (CheckOn(&m_Buttonp[i], i))return true;
	m_Select = 0;
	if (CheckRB())return true;
	m_Select = 107;
	if (CheckL())return true;
	return true;
}


if (1)
{
	g_pMainState->m_Tags.Add("未完成");
	break;
	vector<string> strselect;
	GetSaveTitle(strselect);
	g_pMainState->m_Dialog.SetObj(0);
	g_pMainState->m_Dialog.OnOff(false);
	g_pMainState->m_Dialog.Reset();
	g_pMainState->m_Dialog.m_bRetSelect = true;
	if (i/*m_Select*/ == 13)
	{
		m_bMode = 1;
		//				m_Buttonp[1].SetFrame帧(1);
		g_pMainState->m_Dialog.SetString("选择存档位置", strselect[0], strselect[1], strselect[2]);//, strselect[3]);
	}
	else
	{
		m_bMode = 2;
		//				m_Buttonp[2].SetFrame帧(1);
		g_pMainState->m_Dialog.SetString("选择读取位置", strselect[0], strselect[1], strselect[2], strselect[3]);
	}
	g_pMainState->m_Dialog.OnOff(true);
}

bool cInterfaceFriendQiangHua2::CheckL()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	m_Sleeptime = 3;
	if (m_frampre)
		m_frampre->SetFrame(1);

	switch (m_Select)
	{
	case 0:
		g_pMainState->m_InterfaceSystem2.OnOff(!g_pMainState->m_InterfaceSystem2.m_NeedShow);
		break;
	case 13:
	case 14:
		if (1)
		{
			vector<string> strselect;
			GetSaveTitle(strselect);
			g_pMainState->m_Dialog.SetObj(0);
			g_pMainState->m_Dialog.OnOff(false);
			g_pMainState->m_Dialog.Reset();
			g_pMainState->m_Dialog.m_bRetSelect = true;
			if (m_Select == 13)
			{
				m_bMode = 1;
				m_Buttonp[1].SetFrame帧(1);
				g_pMainState->m_Dialog.SetString("选择存档位置", strselect[0], strselect[1], strselect[2]);//, strselect[3]);
			}
			else
			{
				m_bMode = 2;
				m_Buttonp[2].SetFrame帧(1);
				g_pMainState->m_Dialog.SetString("选择读取位置", strselect[0], strselect[1], strselect[2], strselect[3]);
			}
			g_pMainState->m_Dialog.OnOff(true);
		}
		break;
	case 1:
		g_pMainState->m_GlobalButton[16] = !g_pMainState->m_GlobalButton[16];
		m_Text[1].SetString(!g_pMainState->m_GlobalButton[16] ? "音乐" : "静音");
		if (g_pMainState->m_GlobalButton[16])
			g_pMainState->m_Mp3.Stop();
		else
			g_pMainState->m_Mp3.Play();


// 		cct::get()->isAutoAtkMode = !cct::get()->isAutoAtkMode;
// 		m_Text[3].SetString(cct::get()->isAutoAtkMode ? "输出模式" : "辅助模式");
		for (int i = 0; i < 5; i++)
		{
			if (i == g_pMainState->m_HeroID)continue;
			if (!g_pMainState->m_FightWorkList[i].isExist)continue;
//			((cCharacter*)g_pMainState->m_FightWorkList[i].m_pObj->m_pIndex)->m_PcData.FollowShoe();
		}
		break;
	case 2:		
		g_pMainState->m_GlobalButton[17] = !g_pMainState->m_GlobalButton[17];
		m_Text[2].SetString(!g_pMainState->m_GlobalButton[17] ? "声效" : "无声");
// 		cct::get()->isControl = !cct::get()->isControl;
// 		m_Text[4].SetString(cct::get()->isControl ? "控制全队" : "控制队长");
		break;
	case 3://染色
		if (1)
		{
			if (++g_pMainState->m_GlobalButton[7]/*cct::get()->moveSpeedInMap*/ > 8)
			{
				g_pMainState->m_GlobalButton[7]/*cct::get()->moveSpeedInMap*/ = 1;
			}
			m_Text[3].SetString(toString("走速%d", g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_moveSpeed = g_pMainState->m_GlobalButton[7]/*cct::get()->moveSpeedInMap*/));
		}
		break;
	case 4://坐骑染色
		if (1)
		{
//			cct::get()->isShowBloodBar = !cct::get()->isShowBloodBar;
			g_pMainState->m_GlobalButton[8] = !g_pMainState->m_GlobalButton[8];
			m_Text[4].SetString(/*cct::get()->isShowBloodBar*/g_pMainState->m_GlobalButton[8] ? "显示血条" : "隐藏血条");
		}
		break;
	case 5://装饰染色
		if (1)
		{
			if (++g_pMainState->m_GlobalButton[9] > 2)
			{
				g_pMainState->m_GlobalButton[9] = 0;
			}

// 			cPcData pcd;
// 			pcd.Read("队长", g_pathFriend);
// 			pcd.m_ZiZhi.grow = g_pCharacter->m_PcData.m_ZiZhi.grow;
// 			g_pCharacter->m_PcData.m_ZiZhi = pcd.m_ZiZhi;
// 			g_pCharacter->m_PcData._spesialSkills = pcd._spesialSkills;
// 			g_pCharacter->m_PcData.FollowEquipAll();
// 			g_pMainState->m_Tags.Add("装备几乎铺满了某个包裹");
// 			for (int i = 0; i < g_pCharacter->m_PcData.m_NumofBBSkill; ++i)
// 			{
// 				g_pMainState->m_SkillManager.SetPetSkill1(&g_pCharacter->m_PcData, g_pCharacter->m_PcData.m_petSkills[i]->m_Id, -1);
// 			}
// 			g_pCharacter->m_PcData.m_NumofBBSkill = 0;
// 			for (int i = 0; i < pcd.m_NumofBBSkill; ++i)
// 			{
// 				g_pCharacter->m_PcData.AddSkill(ePetSkill(pcd.m_petSkills[i]->m_Id));
// 				g_pMainState->m_Tags.Add(toString("学会技能:%s", pcd.m_pPetSkill[i]->m_Name.c_str()));
// 			}
// 
// 			g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj->m_TrueName.SetString(g_pCharacter->m_PcData.m_Name = pcd.m_Name);
		}
		break;
	case 8://召唤兽染色
		if (1)
		{
// 			int &grow = g_pCharacter->m_PcData.m_ZiZhi.grow;
// 			const vector<int> &puts = cct::get()->putMenpaiSkills;
// 			if (++grow >= puts.size())
// 			{
// 				grow = 0;
// 			}
// 			g_pCharacter->m_PcData.m_AiLv = true;
// 			m_Text[8].SetString(g_pMainState->m_SkillManager.GetMengPaiSkill(puts[grow])->m_Name);
// 			int id = puts[grow];
// 			g_pMainState->m_Tags.Add(toString("追加法术:%s", g_pMainState->m_SkillManager.GetMengPaiSkill(id)->m_Name.c_str()));
// 			g_pCharacter->m_PCData.m_AiLv = g_pCharacter->m_PCData.m_ZiZhi.m_Growing < cct::get()->putMenpaiSkills.size();
		}
		break;
	case 9://出战
		if (1)
		{
// 			const vector<int> &puts = cct::get()->putPetSkills;
// 			int skillIndex = 0;
// 			if (g_pCharacter->m_PcData.m_NumofBBSkill > 0)
// 			{
// 				for (int i = g_pCharacter->m_PcData.m_NumofBBSkill - 1; i > 0; --i)
// 				{
// 					g_pMainState->m_SkillManager.SetPetSkill1(&g_pCharacter->m_PcData, g_pCharacter->m_PcData.m_petSkills[i]->m_Id, -1);
// 				}
// 				g_pCharacter->m_PcData.m_NumofBBSkill = 1;
// 
// 				sSkill *skill = g_pCharacter->m_PcData.m_petSkills[0];
// 				int index = -1;
// 				forv(puts, i)
// 				{
// 					if (puts[i] == skill->m_Id)
// 					{
// 						index = i;
// 						break;
// 					}
// 				}
// 				if (index >= 0)
// 				{
// 					if (index == puts.size() - 1)
// 					{
// 						index = 0;
// 					}
// 					else
// 					{
// 						++index;
// 					}
// 					skillIndex = index;
// 				}
// 			}
// 			g_pMainState->m_SkillManager.SetPetSkill(&g_pCharacter->m_PcData, puts[skillIndex], 0);
// 			string name = g_pMainState->m_SkillManager.GetPetSkill(puts[skillIndex])->m_Name;
// 			if (name.size() > 8 && name.substr(0, 4) == "高级")
// 			{
// 				name = name.substr(4, name.length() - 4);
// 			}
// 			m_Text[9].SetString(name);
		}
		break;
	case 10://BB强化
		if (1)
		{
			g_pMainState->SetJiangLi(0xfffff, 0, 0, 0, 1);
		}
		break;
	case 11://放生
		if (1)
		{
			g_pMainState->SetJiangLi(0, 0, 0xfffff, 0, 1);
		}
		break;
	case 106://移动
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
	case 107://准备移动
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		m_bMoveMode = true;
		return true;
	case 100:
		m_framprep->SetFrame帧(1);
		OnOff(false);
		break;
	}
	return true;
}

bool cInterfaceFriendQiangHua2::Show(cCanvas* pCanvas)
{
	pCanvas->Add(&m_Back, 1, 1);
	pCanvas->Add(&m_Cancel, 1);
	pCanvas->Add(&m_title);
	//pCanvas->Add(&m_Money);
	for (int i = 0; i < m_Buttonp.size(); i++)
	{
		if (i >= 15)
		{
			continue;
		}
		pCanvas->Add(&m_Buttonp[i], 1);
		pCanvas->Add(&m_Text[i]);
	}
	return true;
}

bool cInterfaceFriendQiangHua2::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	case 1:
		break;
	default:
		break;
	}

	return true;
}
void cInterfaceFriendQiangHua2::Update()
{
	Move(m_xPos, m_yPos);
}

#endif

void encrypt(unsigned long *v, unsigned long *k)
{
	unsigned long y = v[0], z = v[1], sum = 0x72663124, i;         /* set up */
	unsigned long delta = 0x31415926;                 /* a key schedule constant */
	unsigned long a = k[0], b = k[1], c = k[2], d = k[3];   /* cache key */
	for (i = 0; i < 64; i++)
	{                        /* basic cycle start */
		sum += delta;
		y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);/* end cycle */
	}
	v[0] = y;
	v[1] = z;

}

void decrypt(unsigned long *v, unsigned long *k)
{
	unsigned long y = v[0], z = v[1], sum = 0x72663124, i; /* set up */
	unsigned long delta = 0x31415926;                  /* a key schedule constant */
	unsigned long a = k[0], b = k[1], c = k[2], d = k[3];    /* cache key */
	for (i = 0; i < 64; i++)
	{                            /* basic cycle start */
		z -= ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
		y -= ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		sum -= delta;                                /* end cycle */
	}
	v[0] = y;
	v[1] = z;
}

char* enciphering(char *ch, int size, int key)
{
	char *str = new char[size];
	int i = 0, x;
	bool decide = true;
	while (i < size)
	{
		if (ch[i] >= 'a'&&ch[i] <= 'z')
		{
			x = ch[i] + i + key + 1;
			while (decide)
			{
				if (x > 'z')
					x -= 26;
				else
					decide = false;
			}
			decide = true;
			str[i] = x;
		}
		else
			str[i] = ch[i];
		i++;
	}
	return str;
}
char* deciphering(char *ch, int size, int key)
{
	char *str = new char[size];
	int i = 0, x;
	bool decide = true;
	while (i < size)
	{
		if (ch[i] >= 'a'&& ch[i] <= 'z')
		{
			x = ch[i] - i - 1 - key;
			while (decide)
			{
				if (x < 'a')
					x += 26;
				else
					decide = false;
			}
			decide = true;
			str[i] = x;
		}
		else
			str[i] = ch[i];
		i++;
	}
	return str;
}

const static char IP_Table[64] =//初始置换
{
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

const static char IPR_Table[64] =    //初始逆置换表
{
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};
static const char Extension_Table[48] =  //扩展置换表
{
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};
const static char P_Table[32] =    //P盒置换表
{
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25
};

const static char PCK_Table[56] =//密钥置换（原64位去掉奇偶校验位后）
{
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};
const static char LOOP_Table[16] =//左移
{
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
const static char PCC_Table[48] =//压缩置换表
{
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};
const static char S_Box[8][4][16] =//8个S盒
{
	{
		// S1 
		{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
		{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
		{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
		{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
	},
	{
		// S2 
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
		{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
		{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
		{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
	},
	{
		// S3 
		{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
		{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
		{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
	},
	{
		// S4 
		{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
		{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
		{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
		{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
	},
	{
		// S5 
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
		{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
		{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
		{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
	},
	{
		// S6 
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
		{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
		{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
		{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
	},
	{
		// S7 
		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
		{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
		{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
		{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
	},
	{
		// S8 
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
		{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
		{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
		{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
	}
};


typedef bool(*PSubKey)[16][48];
enum{ ENCRYPT, DECRYPT };
static bool SubKey[2][16][48];
static bool Is3DES;
static char Tmp[256], deskey[16];

static void SetKey(const char  *Key, int len);
static void SetSubKey(PSubKey pSubKey, const char Key[8]);
static void F_func(bool In[32], const bool Ki[48]);
static void S_func(bool Out[32], const bool In[48]);
static void Transform(bool *Out[32], const bool In[48], int len);
static void Xor(bool *InA, const bool *InB, int len);
static void RotateL(bool *In, int len, int loop);
static void ByteToBit(bool *Out, const char *In, int bits);
static void BitToByte(char *Out, const bool *In, int bits);
static void myDES(char Out[8], char In[8], const PSubKey pSubKey, bool Type);
bool DES_Act(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type);




void cInterfaceFriendQiangHua2::Save(int id)
{
	sOstream ostrCode;
	ofstream ofile(g_pathSave + "存档.txt");
	cct::saveGlobal(ostrCode);
	const auto& fs = g_pMainState->m_Friend._friends;
	string name, name2;
	ofile << fs.size() << g_strSpace << g_pMainState->m_InterfaceTeam.getLeaveBegin() << g_strEnter;
	forr (fs, i)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
//		ofile << list.isExist << g_strSpace << g_pMainState->m_pFightState->m_FightMenu.CheckControl(i) << g_strSpace;
//		if (!list.isExist)continue;
		cObj* obj = fs[i].obj; // list.m_pObj;
		int type = obj->m_IndexType;
		obj->m_IndexType = INDEXTYEP_CHARACTER;
		cPcData* pc = obj->getPcData();
		obj->m_IndexType = type;
		name = obj->m_TrueName.GetString();
		if (name.empty())
		{
			name = pc->m_Name;
		}
		if (name.empty())
		{
			name = name2;
		}
		if (name.empty())
		{
			name = "默认";
		}

		name2 = obj->m_Name称谓.GetString();
		if (name2.empty())
		{
			name2 = name;
		}

		ofile << name << g_strSpace << name2 << g_strSpace  << fs[i].ctrl << g_strSpace << obj->m_Foot.m_NowID << g_strEnter;
		for (int k = 0; k < pc->m_NumofBB; ++k)
		{
			ofile << pc->m_pPets[k]->m_PetData.m_Name << g_strSpace;
		}
		ofile << g_strEnter;
		pc->Save(ofile);
		ofile << g_strEnter;
		ostrCode << fs[i].dski/*list.m_FriendListid*/ << g_strSpace;
		pc->SaveCode(ostrCode);
	}
	const auto& team = g_pMainState->m_InterfaceTeam;
	ofile << g_strSpace << team.m_eOurFormation << g_strSpace;// << team.m_eEnemyFormation << g_strSpace;
	g_pMainState->m_FangWu.Save(ofile);
	SavePos(ofile);
	ofile << g_pMainState->_wasHeadTop.m_NowID << g_strSpace;
	

	auto& ck = g_pMainState->_uiCangKu._items;
	ostrCode << ck.size() << g_strSpace;
	forr(ck, i)
	{
		ck[i].SaveCode(ostrCode);
	}
	const auto& pck = g_pMainState->m_InterFaceBuyPet.m_Item;
	ostrCode << pck.size() << g_strSpace;
	forr(pck, i)
	{
		pck[i]->m_PetData.SaveCode(ostrCode);
		ofile << g_strEnter << pck[i]->m_PetData.m_Name << g_strSpace;
		pck[i]->m_PetData.Save(ofile);
	}

	ofile << g_strEnter << g_strEnter << g_strEnter << "// 可根据喜好调整名字和称谓(重置就写\"默认\")，注意名字不能带<空格>，不能带<换行>，不能带<特殊字符>，反正各种不能带...";
	ofile.close();

	string str = ostrCode.str();
	
	cc::encode(str);

//	int size = str.size();
// 	char *data = new char[size + 8];
// 	DES_Act(data, (char*)str.data(), size, "P", 1, ENCRYPT);
 	ofile.open(g_pathSave + "存档.sav");
// 	ofile.write(data, size + 8);
	ofile.write(str.data(), str.size());
	ofile.close();
//	delete[] data;
	return;

// 	if (id < 0)id = 0;
// 	ofstream File;
// 	ostringstream oss;
// 	//	oss << g_pathSave << "5.txt";
// 	File.open(oss.str());
// 	File << id;
// 	File.close();
// 	oss.str("");
// 	//	oss << g_pathSave;
// 	oss << id;
// 	oss << ".txt";
// 
// 	File.open(oss.str());
// 	g_pMainState->m_InterfaceDoor.Save(File);
// 	File << "\n";
// 	SaveFightList(File);
// 	File << "\n";
// 	File << "下面保存任务" << "\n";
// 	SaveTrigger(File);
// 	SaveFriend(File);
// 	g_pMainState->m_FangWu.Save(File);
// 	g_pMainState->m_TaskZhuaGui.Save(File);
// 	g_pMainState->m_TaskBaoTu.Save(File);
// 	g_pMainState->m_TaskFB.Save(File);
// 	g_pMainState->m_TaskHuoDong.Save(File);
// //	g_pMainState->SaveGlobal(File);
// 	SavePos(File);
// 
// 	g_pMainState->m_Map.Save(File);
// 	g_pMainState->m_taskSM.Save(File);
// 	File.close();
// 
// 	ifstream iFile(oss.str(), ios_base::binary);
// 	iFile.seekg(0, ios_base::end);
//	int size = (int)iFile.tellg();
//	char *data = new char[size];
// 	char *data2 = new char[size + 8];
// 	iFile.seekg(0, ios_base::beg);
//	iFile.read(data, size);
//	DES_Act(data2, data, size, "PAI3.1415926", 12, ENCRYPT);
//	File.open(g_pathSave + toString("%d.sav", id), ios_base::binary);
// 	File.write(data2, size + 8);
// 	File.close();
// 	delete[] data;
// 	delete[] data2;
}



sIstream cInterfaceFriendQiangHua2::Load()
{
	ifstream ifile(g_pathSave + "存档.sav");
	ifile.seekg(0, ios_base::end);
	int size = (int)ifile.tellg();
	char *data = new char[size];
//	char *data2 = new char[size + 8];
	ifile.seekg(0, ios_base::beg);
	ifile.read(data, size);
	ifile.close();

	cc::decode(data, size);

//	int size = str.size();
//	DES_Act(data2, data, size, "P", 1, DECRYPT);
//	sIstream istrCode(data2, size + 8);
	sIstream istrCode(data, size);
	delete[] data;
//	delete[] data2;
	return istrCode;
}



void cInterfaceFriendQiangHua2::Load(int id)
{
	auto checkname = [](const string & name)
	{
		int c = 0;
		forr(name, i)
		{
			const auto& s = name[i];
			if (s >= '0' && s <= '9')
			{
				++c;
			}
		}
		return (c < 7);
	};
	sIstream istrCode = Load();
	cct::loadGlobal(istrCode);

	g_pMainState->ClearInterfaceSetShow();
	string name, name1;
	ulong footid;

	ifstream ifile(g_pathSave + "存档.txt");
	bool isTxt = id;
	auto& fters = g_pMainState->m_Friend._friends;
	int e1 = 5;
	if (isTxt)
	{
		ifile >> e1;
	}
	fters.resize(e1);
	if (isTxt)
	{
		ifile >> e1;
	}
	else
	{
		e1 = 1;
	}
	forr(fters, i)
	{
		auto& fr = fters[i];
		sFightWork& list = g_pMainState->m_FightWorkList[i];
	
//		g_pMainState->m_pFightState->m_FightMenu.SetControl(i, ctrl);
//		if (!list.isExist)continue;


		if (isTxt)
		{
			ifile >> name >> name1 >> fr.ctrl >> footid;
		}
		else
		{
			fr.ctrl = true;
		}
		if (!checkname(name) || !checkname(name1))
		{
			ccc_msgbox("读档出错<name>");
			g_StateType = 0;
		}

		cObj* obj = fr.obj = new cObj; // list.m_pObj;
		obj->Init();
		obj->SetDataType(INDEXTYEP_CHARACTER);
		cPcData* pc = obj->getPcData();
		pc->m_Name = name;

		
		istrCode >> fr.dski;// list.m_FriendListid;
		pc->LoadCode(istrCode);
		pc->apply();
		pc->autoSkillEnable();

		sCharacterData* cdata = &g_pMainState->m_pCharacterDataList[cct::getModel(pc->modeid)];
		((cCharacter*)obj->m_pIndex)->SetData(cdata);
		if (!isTxt || name == "默认")
		{
			pc->m_Name = name = cdata->m_Name;
		}
		if (!isTxt || name1 == "默认")
		{
			name1 = cdata->m_Name;
		}

		obj->m_TrueName.SetColor(RGB(0, 255, 0));
		obj->m_TrueName.SetBackColor(RGB(0, 0, 0));
		obj->m_TrueName.SetString(name);

		obj->m_Name称谓.SetColor(RGB(0, 128, 255));
		obj->m_Name称谓.SetBackColor(RGB(0, 0, 0));
		obj->m_Name称谓.SetString(name1);
		pc->m_Controler.Set(0, 0);

		if (isTxt)
		{
			for (int k = 0; k < pc->m_NumofBB; ++k)
			{
				ifile >> name;
				if (!checkname(name))
				{
					ccc_msgbox("读档出错<name>");
					g_StateType = 0;
				}

				auto& pet = pc->m_pPets[k];
				if (name == "默认")
				{
					name = pet->GetData()->m_Name;
				}
				pet->m_PetData.m_Name = name;
			}
			pc->Load(ifile);

			if (footid >= 0)
			{
				obj->m_Foot.Load(footid);
			}
		}
		else
		{
			for (int k = 0; k < pc->m_NumofBB; ++k)
			{
				auto& pet = pc->m_pPets[k];
				pet->m_PetData.m_Name = pet->GetData()->m_Name;
			}
		}


		if (i == g_pMainState->m_HeroID)
		{
			g_pHeroObj = obj;
			g_pHeroObj->m_bCheckWall = true;//主角走路要进行碰撞检测
			g_pCharacter = (cCharacter*)g_pHeroObj->m_pIndex;
		}

		obj->Reset();
		obj->Set(POS_STAND);
		list.m_FriendListid = fr.dski;

	}
	g_pMainState->m_InterfaceTeam.update(false, e1);

	if (isTxt)
	{
		ifile >> e1;
	}
	else
	{
		e1 = eFormation::normal;
	}
	auto& team = g_pMainState->m_InterfaceTeam;
	team.SetFormation((eFormation)e1, false, true);
// 	ifile >> e1;
 	team.SetFormation(eFormation::normal, true, true);

	if (isTxt)
	{
		g_pMainState->m_FangWu.Load(ifile);
		LoadPos(ifile);
		ifile >> footid;


		g_pMainState->_wasHeadTop.Load(footid);
		g_pMainState->_wasHeadTop.m_PosType = 2;
		g_pMainState->_wasHeadHigh = /*h.isMid ? (g_pMainState->_wasHeadTop.GetHeight() / 2) :*/ 0;
	}
	else
	{
		g_pMainState->m_Map.LoadMap(20, 74, "桃源村");
	}


	auto& ck = g_pMainState->_uiCangKu._items;
	istrCode >> e1;
	forr(ck, i)
	{
		ck[i].LoadCode(istrCode);
	}

	istrCode >> e1;
	auto& pck = g_pMainState->m_InterFaceBuyPet.m_Item;
	pck.resize(e1);
	forr(pck, i)
	{
		if (!pck[i])pck[i] = new cPet;
		pck[i]->m_PetData.LoadCode(istrCode);
		if (pck[i]->m_PetData.modeid >= 0)
		{
			pck[i]->SetData(g_pMainState->m_PetDataManager.GetPetData(pck[i]->m_PetData.modeid));
		}
		else
		{
			ERRBOX2(pck[i]->m_PetData.modeid);
		}

		if (isTxt)
		{
			ifile >> name;
			if (!checkname(name))
			{
				ccc_msgbox("读档出错<name>");
				g_StateType = 0;
			}
			if (name == "默认")
			{
				name = pck[i]->GetData()->m_Name;
			}
			pck[i]->m_PetData.m_Name = name;
			pck[i]->m_PetData.Load(ifile);
		}
		else
		{
			pck[i]->m_PetData.m_Name = pck[i]->GetData()->m_Name;
		}
	}

	ifile.close();
	g_pMainState->m_PCHead.UpDateHead();

	return;


	g_pMainState->ClearInterfaceSetShow();
	g_pMainState->m_Map.SetLock();
	g_pMainState->m_Map.SetLock(false);
	ifstream File;
	//	File.open(g_pathSave + toString("%d.sav", id), ios_base::binary);
	if (!File)
	{
		File.close();
		return;
	}
	File.seekg(0, ios_base::end);
	int size = (int)File.tellg();
	char *data = new char[size];
	char *data2 = new char[size + 8];
	File.seekg(0, ios_base::beg);
	File.read(data, size);
	File.close();
	DES_Act(data2, data, size, "PAI3.1415926", 12, DECRYPT);
	ofstream oFile(/*g_pathSave + */toString("%d.tmp", id), ios_base::binary);
	oFile.write(data2, size + 8);
	oFile.close();
	delete[] data;
	delete[] data2;

	ostringstream oss;
	//	oss << g_pathSave;
	oss << id;
	oss << ".tmp";
	File.open(oss.str());
	g_StateType = STATE_MAIN;
	g_pMainState->m_InterfaceDoor.Load(File);

	LoadFightList(File);
	g_pMainState->m_PCHead.UpDateHead();
	string dustbin;
	File >> dustbin;
	g_pMainState->m_Canvas.m_NeedShowMap = true;
	LoadTrigger(File);
	LoadFriend(File);
	g_pMainState->m_FangWu.Load(File);
	g_pMainState->m_TaskZhuaGui.Load(File);
	g_pMainState->m_TaskBaoTu.Load(File);
	g_pMainState->m_TaskFB.Load(File);
	g_pMainState->m_TaskHuoDong.Load(File);
//	g_pMainState->LoadGlobal(File);
	LoadPos(File);

	g_pMainState->m_Map.LoadMap(File);
	g_pMainState->m_taskSM.Load(File);

	g_pMainState->m_Channel.m_ContextNum = 0;
	g_pMainState->m_Channel.m_ContextShowNum = 0;
	////////////////////////////////////////////////////////////////////////// 呵呵哒
	// 	if (100 == g_pMainState->m_GlobalButton[0] || false)
	// 	{
	// 		g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(true);
	// 	}
	// 	else 
	//		g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(false);
	if (g_GlobalValues[16])
		g_pMainState->m_Mp3.Stop();
	else
		g_pMainState->m_Mp3.Play();
	File.close();
	DeleteFile(oss.str().c_str());
	g_pMainState->m_Canvas.SetRedrawAll();

}






void ByteToBit(bool *Out, const char *In, int bits)
{
	for (int i = 0; i < bits; ++i)
		Out[i] = (In[i >> 3] >> (i & 7)) & 1;
}
void BitToByte(char *Out, const bool *In, int bits)
{
	memset(Out, 0, bits >> 3);
	for (int i = 0; i < bits; ++i)
		Out[i >> 3] |= In[i] << (i & 7);
}

void Transform(bool *Out, bool *In, const char *Table, int len)
{
	for (int i = 0; i < len; ++i)
		Tmp[i] = In[Table[i] - 1];
	memcpy(Out, Tmp, len);
}
void Xor(bool *InA, const bool *InB, int len)
{
	for (int i = 0; i < len; ++i)
		InA[i] ^= InB[i];
}
void RotateL(bool *In, int len, int loop)
{
	memcpy(Tmp, In, loop);
	memcpy(In, In + loop, len - loop);
	memcpy(In + len - loop, Tmp, loop);
}
void S_func(bool Out[32], const bool In[48])
{
	for (char i = 0, j, k; i < 8; ++i, In += 6, Out += 4)
	{
		j = (In[0] << 1) + In[5];
		k = (In[1] << 3) + (In[2] << 2) + (In[3] << 1) + In[4];
		ByteToBit(Out, &S_Box[i][j][k], 4);
	}
}

void F_func(bool In[32], const bool Ki[48])
{
	static bool MR[48];
	Transform(MR, In, Extension_Table, 48);
	Xor(MR, Ki, 48);
	S_func(In, MR);
	Transform(In, In, P_Table, 32);
}

void SetSubKey(PSubKey pSubKey, const char Key[8])
{
	static bool K[64], *KL = &K[0], *KR = &K[28];
	ByteToBit(K, Key, 64);
	Transform(K, K, PCK_Table, 56);
	for (int i = 0; i < 16; i++)
	{
		RotateL(KL, 28, LOOP_Table[i]);
		RotateL(KR, 28, LOOP_Table[i]);
		Transform((*pSubKey)[i], K, PCC_Table, 48);
	}

}

void SetKey(const char  *Key, int len)
{
	memset(deskey, 0, 16);
	memcpy(deskey, Key, len>16 ? 16 : len);
	SetSubKey(&SubKey[0], &deskey[0]);
	Is3DES = len > 8 ? (SetSubKey(&SubKey[1], &deskey[8]), true) : false;
}

void DES(char Out[8], char In[8], const PSubKey pSubKey, bool Type)
{
	static bool M[64], tmp[32], *Li = &M[0], *Ri = &M[32];
	ByteToBit(M, In, 64);
	Transform(M, M, IP_Table, 64);
	if (Type == ENCRYPT)
	{
		for (int i = 0; i < 16; i++)
		{
			memcpy(tmp, Ri, 32);
			F_func(Ri, (*pSubKey)[i]);
			Xor(Ri, Li, 32);
			memcpy(Li, tmp, 32);
		}
	}
	else
	{
		for (int i = 15; i >= 0; i--)
		{
			memcpy(tmp, Li, 32);
			F_func(Li, (*pSubKey)[i]);
			Xor(Li, Ri, 32);
			memcpy(Ri, tmp, 32);
		}
	}
	Transform(M, M, IPR_Table, 64);
	BitToByte(Out, M, 64);
}

bool DES_Act(char *Out, char *In, long datalen, const char *Key, int keylen, bool Type)
{
	if (!(Out&&In&&Key && (datalen = datalen + 7) & 0xfffffff8))
		return false;
	SetKey(Key, keylen);
	if (!Is3DES)
	{
		for (long i = 0, j = datalen >> 3; i < j; ++i, Out += 8, In += 8)
			DES(Out, In, &SubKey[0], Type);
	}
	else
	{
		for (long i = 0, j = datalen >> 3; i < j; ++i, Out += 8, In += 8)
		{
			DES(Out, In, &SubKey[0], Type);
			DES(Out, Out, &SubKey[1], !Type);
			DES(Out, Out, &SubKey[0], Type);
		}
	}
	return true;
}





//////////////////////////////////////////////////////////////////////////





bool cInterfaceSystem::Init()
{
	if (m_bInit)return true;
	m_bInit = true;
	m_ExtGame.Set(&g_pMainState->m_Button4);
	m_SaveGame.Set(&g_pMainState->m_Button4);
	m_LoadGame.Set(&g_pMainState->m_Button4);
	m_ExtGame.m_bStatic = true;
	m_SaveGame.m_bStatic = true;
	m_LoadGame.m_bStatic = true;
	m_tExtGame.SetColor(RGB(255, 255, 255));
	m_tExtGame.SetString("退出?");
	m_tTitle.SetColor(RGB(255, 255, 255));
	//	m_tTitle.SetString("队伍自动/存读档");
	m_tLoadGame.SetColor(RGB(255, 255, 255));
	m_tLoadGame.SetString("否");
	m_tSaveGame.SetColor(RGB(255, 255, 255));
	m_tSaveGame.SetString("是");


	m_Cancel.Set(&g_pMainState->m_Cancel);
	m_Cancel.m_bStatic = true;
	m_Back.Load(0x1DF7B97D);//  574791040);
	ccm::get()->pushWdf("系统面板", 0x1DF7B97D);
	m_Back.SetStatic(true);

	//	m_tTime.SetColor(0);

	Move(g_half320 - m_Back.GetWidth() / 2, g_half240 - m_Back.GetHeight() / 2);
	return true;
}

bool cInterfaceSystem::Show(cCanvas* pCanvas)
{
	if (!m_NeedShow)return true;
	pCanvas->Add(&m_Back, 1, true);
	pCanvas->Add(&m_ExtGame, 1);
	pCanvas->Add(&m_SaveGame, 1);
	pCanvas->Add(&m_LoadGame, 1);
	pCanvas->Add(&m_tExtGame);
	pCanvas->Add(&m_tTitle);
	pCanvas->Add(&m_tSaveGame);
	pCanvas->Add(&m_tLoadGame);
	pCanvas->Add(&m_Cancel, 1);
	//	m_tTime.Show(pCanvas);
	return true;
}

bool cInterfaceSystem::ProcessInput()
{
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}
	if (m_bMoveMode)//移动
	{
		g_pMainState->SetMouseOnMap(false);
		if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
		{
			g_pMainState->SetMouseOnMap(false);
			int xDel = g_xMouse - m_Prex;
			int yDel = g_yMouse - m_Prey;
			m_Prex = g_xMouse;
			m_Prey = g_yMouse;
			if (xDel != 0 || yDel != 0)
			{
				Move(m_xPos + xDel, m_yPos + yDel);
			}
		}
		else	m_bMoveMode = false;
		return true;
	}
	ResetButton();
	m_Select = -1;

	switch (m_bMode)
	{
	case 1://保存
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4)
			{
				Save(g_pMainState->m_Dialog.m_retSelect);
				g_pMainState->m_Tags.Add("保存成功");
			}
			m_bMode = 0;
		}
		return true;
	case 2://读取
		if (1)
		{
			if (g_pMainState->m_Dialog.m_retSelect < 4 && g_pMainState->m_Dialog.m_retSelect > -1)
			{
				Load(g_pMainState->m_Dialog.m_retSelect);
				OnOff(false);
			}
			m_bMode = 0;
		}
		return true;
	}

// 	if (g_pMainState->Keyboard.GetKeyState(DIK_L))
// 	{
// 		g_pMainState->Keyboard.SetLock(DIK_L);
// 		Load(0);
// 		return true;
// 	}

	if (isOn(g_xMouse, g_yMouse, m_Back.m_PreShowRect))
	{
		g_pMainState->SetMouseOnMap(false);

		if (CheckOn(&m_ExtGame, 1))return true;
		if (CheckOn(&m_SaveGame, 2))return true;
		if (CheckOn(&m_LoadGame, 3))return true;
		if (CheckOn(&m_Cancel, 0))return true;
		m_Select = 0;
		if (CheckRB())return true;

		m_Select = 100;
		if (CheckL())return true;;

	}
	return true;
}

bool cInterfaceSystem::Move(int x, int y)
{
	m_xPos = x;
	m_yPos = y;
	m_Back.SetX(x);
	m_Back.SetY(y);
	m_tTitle.SetXCenter(m_Back.GetX() + 80);
	m_tTitle.SetY(m_yPos + 4);
	m_tTitle.UpdateXCenter();
	/*m_ExtGame.SetXY(m_xPos + 15, m_yPos + 40);
	m_SaveGame.SetXY(m_xPos + 15, m_yPos + 65);
	m_LoadGame.SetXY(m_xPos + 15, m_yPos + 90);*/

	m_ExtGame.SetXY(m_Back.GetCenter() - m_ExtGame.GetWidth() / 2, m_yPos + 40);
	m_SaveGame.SetXY(m_ExtGame.GetX(), m_yPos + 65);
	m_LoadGame.SetXY(m_ExtGame.GetX(), m_yPos + 90);


	m_tExtGame.SetXCenter(m_ExtGame.GetX() + m_ExtGame.GetWidth() / 2);
	m_tExtGame.SetY(m_ExtGame.GetY() + 3);
	m_tExtGame.UpdateXCenter();
	m_Cancel.SetXY(m_xPos + m_Back.GetWidth() - 20, m_yPos + 3);
	m_tSaveGame.SetXCenter(m_SaveGame.GetCenter());
	m_tSaveGame.SetY(m_SaveGame.GetY() + 3);
	m_tSaveGame.UpdateXCenter();

	m_tLoadGame.SetXCenter(m_LoadGame.GetCenter());
	m_tLoadGame.SetY(m_LoadGame.GetY() + 3);
	m_tLoadGame.UpdateXCenter();

	//	m_tTime.SetPos(x + 90, y + 40);
	return true;
}

bool cInterfaceSystem::CheckL()
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
		OnOff(false);
		break;
	case 1:
		break;
		//	g_StateType = STATE_EXT;
		// 		for (int i = 0; i < 300; i++)
		// 		{
		// 			g_pMainState->m_Canvas.m_CanvasCube[i].NeedReDraw = true;
		// 		}
		// 		m_ExtGame.SetFrame帧(1);
		// 		OnOff(false);
// 		cct::get()->isAutoAtkMode = !cct::get()->isAutoAtkMode;
// 		m_tExtGame.SetString(cct::get()->isAutoAtkMode ? "输出模式" : "辅助模式");
		for (int i = 0; i < 5; i++)
		{
			if (i == g_pMainState->m_HeroID)continue;
			if (!g_pMainState->m_FightWorkList[i].isExist)continue;
//			((cCharacter*)g_pMainState->m_FightWorkList[i].m_pObj->m_pIndex)->m_PcData.FollowShoe();
		}
		return true;
	case 2:
		g_StateType = STATE_EXT;
		for (int i = 0; i < 300; i++)
		{
			g_pMainState->m_Canvas.m_CanvasCube[i].NeedReDraw = true;
		}
		m_ExtGame.SetFrame帧(1);
		OnOff(false);
	case 3:
		OnOff(false);
		break;
		if (1)
		{
			vector<string> strselect;
			GetSaveTitle(strselect);
			g_pMainState->m_Dialog.SetObj(0);
			g_pMainState->m_Dialog.OnOff(false);
			g_pMainState->m_Dialog.Reset();
			g_pMainState->m_Dialog.m_bRetSelect = true;
			if (m_Select == 2)
			{
				m_bMode = 1;
				m_SaveGame.SetFrame帧(1);
				g_pMainState->m_Dialog.SetString("选择存档位置", strselect[0], strselect[1], strselect[2]);//, strselect[3]);
			}
			else
			{
				m_bMode = 2;
				m_LoadGame.SetFrame帧(1);
				g_pMainState->m_Dialog.SetString("选择读取位置", strselect[0], strselect[1], strselect[2], strselect[3]);
			}
			g_pMainState->m_Dialog.OnOff(true);
			return true;
		}
		break;
	case 100:
		m_bMoveMode = true;
		g_pMainState->Mouse.UnSetLock(MOUSE_LBUTTON);
		m_Prex = g_xMouse;
		m_Prey = g_yMouse;
		break;
	}
	return true;
}

void cInterfaceSystem::OnOff(bool NeedShow)
{
	//	if (g_pMainState->m_Dialog.m_NeedShow)return;
	if (NeedShow == m_NeedShow)return;
	g_pMainState->InterfaceSetShow(this, NeedShow);

	if (m_NeedShow)
	{
		m_Sleeptime = 0;
		Init();
		m_Cancel.SetFrame帧(0);
		cct::autoSave();
	}
	g_pMainState->m_Canvas.SetRedraw(m_Back.m_PreShowRect);
}

bool cInterfaceSystem::CheckRB()
{
	if (!g_pMainState->Mouse.GetButtonState(MOUSE_RBUTTON))return false;
	g_pMainState->Mouse.SetLock(MOUSE_RBUTTON);
	switch (m_Select)
	{
	case 0:
		OnOff(false);
		break;
	default:
		break;
	}
	return true;
}

void cInterfaceSystem::Save(int id)
{
	if (id < 0)id = 0;
	ofstream File;
	ostringstream oss;
	//	oss << g_strDataPath<<"存档//5.txt";
//	oss << g_pathSave << "5.txt";
	File.open(oss.str());
	File << id;
	File.close();
	oss.str("");
	//	oss << g_strDataPath<< "存档//";
//	oss << g_pathSave;
	oss << id;
	oss << ".txt";

	File.open(oss.str());
	g_pMainState->m_InterfaceDoor.Save(File);
	File << "\n";
	SaveFightList(File);
	File << "\n";
	File << "下面保存任务" << "\n";
	SaveTrigger(File);
	SaveFriend(File);
	g_pMainState->m_FangWu.Save(File);
	g_pMainState->m_TaskZhuaGui.Save(File);
	g_pMainState->m_TaskBaoTu.Save(File);
	g_pMainState->m_TaskFB.Save(File);
	g_pMainState->m_TaskHuoDong.Save(File);
//	g_pMainState->SaveGlobal(File);
	SavePos(File);

	g_pMainState->m_Map.Save(File);
	g_pMainState->m_taskSM.Save(File);
	File.close();

}
void cInterfaceSystem::Load(int id)
{
	g_pMainState->ClearInterfaceSetShow();
	g_pMainState->m_Map.SetLock();
	g_pMainState->m_Map.SetLock(false);
	ifstream File;
	ostringstream oss;
	//	oss << g_strDataPath<<"存档//";
//	oss << g_pathSave;
	oss << id;
	oss << ".tmp";
	File.open(oss.str());
	g_StateType = STATE_MAIN;
	g_pMainState->m_InterfaceDoor.Load(File);

	LoadFightList(File);
	g_pMainState->m_PCHead.UpDateHead();
	string dustbin;
	File >> dustbin;
	g_pMainState->m_Canvas.m_NeedShowMap = true;
	LoadTrigger(File);
	LoadFriend(File);
	g_pMainState->m_FangWu.Load(File);
	g_pMainState->m_TaskZhuaGui.Load(File);
	g_pMainState->m_TaskBaoTu.Load(File);
	g_pMainState->m_TaskFB.Load(File);
	g_pMainState->m_TaskHuoDong.Load(File);
//	g_pMainState->LoadGlobal(File);
	LoadPos(File);

	g_pMainState->m_Map.LoadMap(File);
	g_pMainState->m_taskSM.Load(File);

	g_pMainState->m_Channel.m_ContextNum = 0;
	g_pMainState->m_Channel.m_ContextShowNum = 0;
	////////////////////////////////////////////////////////////////////////// 呵呵哒
	// 	if (100 == g_pMainState->m_GlobalButton[0] || false)
	// 	{
	// 		g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(true);
	// 	}
	// 	else 
	//		g_pMainState->m_pFightState->m_FightMenu.SetTeamControl(false);
	if (g_GlobalValues[16])
		g_pMainState->m_Mp3.Stop();
	else
		g_pMainState->m_Mp3.Play();
	File.close();
	g_pMainState->m_Canvas.SetRedrawAll();

}
void cInterfaceSystem::SavePos(ofstream& File)
{
	//保存地点
	File << "\n\r";
	File << g_pMainState->m_Map.m_MapName << " ";
	File << g_pHeroObj->GetX() / 20 << " ";
	File << (g_pMainState->m_Map.m_pMap->m_Height - g_pHeroObj->GetY()) / 20 << " ";

}
void cInterfaceSystem::LoadPos(ifstream& File)
{
	g_pMainState->m_Map.m_MapName = "";//
	/*for (int i = 0; i < g_pMainState->m_Map.m_numberOfNpc; i++)
	{
	g_pMainState->m_Map.m_pNpc[i]->Free();
	}
	g_pMainState->m_Map.m_numberOfNpc = 0;
	g_pMainState->m_Map.m_MapNumber = -1;*/
	//读取地点
	int xpos, ypos;
	string mapname;
	File >> mapname;
	File >> xpos;
	File >> ypos;
	if (g_pMainState->m_FangWu.GetMapName() == mapname)
		g_pMainState->m_FangWu.GoIn();
	else
	{
		g_pMainState->m_Map.LoadMap(xpos, ypos, (char*)mapname.c_str(), false);
	}
}

void cInterfaceSystem::SaveFightList(ofstream& File)
{
	File << g_pMainState->m_HeroID << " ";
	g_pMainState->m_InterfaceTeam.Save(File);
	File << "\n";
	for (int i = 0; i < 5; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
		File << list.isExist << " ";
		File << list.CheckDie() << " ";
		if (!list.isExist)continue;
		File << list.m_pObj->m_IndexType << " ";
		if (list.isExist)
		{
			switch (list.m_pObj->m_IndexType)
			{
			case INDEXTYEP_CHARACTER:
				if (1)
				{
					cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
// 					if (i != g_pMainState->m_HeroID)
// 					{
// 						//检测召唤兽进阶
// 						int jinjienum = (g_pCharacter->m_PcData.m_Lv + 10) / cct::get()->per进阶;
// 						for (uint i2 = 0; i2 < pc->m_PcData.m_NumofBB; i2++)
// 						{
// 							cPropertyData& Pet = pc->m_PcData.m_pPets[i2]->m_PetData;
// 							if (Pet.m_JinJieNum.m_index < jinjienum)
// 							{
// 								Pet.SetJinJie(jinjienum - Pet.m_JinJieNum.m_index);
// 								Pet.m_RanSe.Reset();
// 								sFriendList* plist = g_pMainState->m_Friend.FindFriend2(pc->m_PcData.m_Name);
// 								for (uint i3 = 0; i3 < plist->m_BBList.size(); i3++)
// 								{
// 									if (plist->m_BBList[i3].m_name == Pet.m_Name)
// 									{
// 										plist->m_Ranse.Reset();
// 									}
// 								}
// 							}
// 						}
// 					}
					pc->m_PcData.Save(File);
				}
				break;
			case INDEXTYEP_PET:
				if (1)
				{
					cPet* pc = (cPet*)list.m_pObj->m_pIndex;
					pc->m_PetData.Save(File);
				}
				break;
			default:
				ERRBOX(0);
				break;
			}
		}

	}
}

void cInterfaceSystem::LoadFightList(ifstream& File)
{
	int heroid;
	File >> heroid;
	g_pMainState->m_InterfaceTeam.Load(File);
	int indextype;
	for (int i = 0; i < 5; i++)
	{
		g_pMainState->FreeFightList(i);
	}
	for (int i = 0; i < 5; i++)
	{
		sFightWork& list = g_pMainState->m_FightWorkList[i];
		list.m_pObj->m_TrueName.SetColor(RGB(0, 255, 0));
		File >> list.isExist;
		bool bdie;
		File >> bdie;
		list.SetDie(bdie);
		if (!list.isExist)continue;
		File >> indextype;
		list.m_pObj->SetDataType(indextype);
		if (list.isExist)
		{
			switch (list.m_pObj->m_IndexType)
			{
			case INDEXTYEP_CHARACTER:
				if (1)
				{
					cCharacter* pc = (cCharacter*)list.m_pObj->m_pIndex;
					pc->m_PcData.Load(File);
					pc->SetData(&g_pMainState->m_pCharacterDataList[pc->m_PcData.modeid]);
					list.m_pObj->m_TrueName.SetString(pc->m_PcData.m_Name);
					if (i == heroid)g_pMainState->SetCharacter(heroid);
					if (pc->m_PcData.m_FightPetID > -1)
					{
						int petid = pc->m_PcData.m_FightPetID;
						pc->m_PcData.m_FightPetID = -1;
						g_pMainState->SetFightPet(i, petid);
					}
// 					if (i != g_pMainState->m_HeroID)
// 					{
// 						pc->m_PcData.FollowShoe();
// 					}

				}
				break;
			case INDEXTYEP_PET:
				if (1)
				{
					cPet* pc = (cPet*)list.m_pObj->m_pIndex;
					pc->m_PetData.Load(File);
					pc->SetData(g_pMainState->m_PetDataManager.GetPetData(pc->m_PetData.modeid));
					list.m_pObj->m_TrueName.SetString(pc->m_PetData.m_Name);
				}
				break;
			default:
				ERRBOX(0);
				return;
			}
			list.m_pObj->Reset();
			list.m_pObj->Set(POS_STAND);
		}

	}
	//	g_pMainState->SetCharacter(g_pMainState->m_HeroID);
	/*g_pHeroObj->Reset();
	g_pHeroObj->Set(POS_STAND);*/

	//g_pMainState->m_InterfaceTeam.SetFormation(normal);
	//g_pMainState->m_InterfaceTeam.SetFormation(normal, true);
}

void cInterfaceSystem::SaveTrigger(ofstream& File)
{
	SaveATrigger(&g_pMainState->m_TriggerFightTurn, File);
	SaveATrigger(&g_pMainState->m_TriggerFightStart, File);
	g_pMainState->m_TriggerGive.Save(File);
	SaveATrigger(&g_pMainState->m_TriggerFightSuccess, File);
	g_pMainState->m_TriggerObj.Save(File);
	g_pMainState->m_TriggerObjMap.Save(File);
	g_pMainState->m_Triggerlv.Save(File);
	g_pMainState->m_TriggerGive.Save(File);
	g_pMainState->m_TriggerDialog.Save(File);
	//g_pMainState->m_TriggerTime.Save(File);
	g_pMainState->m_Job.Save(File);
	File << "////////////////保存剧情";
//	g_pMainState->m_ZhuXian.Save(File);
	g_pMainState->m_ZhiXian.Save(File);
	g_pMainState->m_ZhiXian2.Save(File);
	g_pMainState->m_ZhiXian3.Save(File);

}
void cInterfaceSystem::LoadTrigger(ifstream& File)
{
	LoadATrigger(&g_pMainState->m_TriggerFightTurn, File);
	LoadATrigger(&g_pMainState->m_TriggerFightStart, File);
	g_pMainState->m_TriggerGive.Load(File);
	LoadATrigger(&g_pMainState->m_TriggerFightSuccess, File);
	g_pMainState->m_TriggerObj.Load(File);
	g_pMainState->m_TriggerObjMap.Load(File);
	g_pMainState->m_Triggerlv.Load(File);
	g_pMainState->m_TriggerGive.Load(File);
	g_pMainState->m_TriggerDialog.Load(File);
	//g_pMainState->m_TriggerTime.Load(File);
	g_pMainState->m_Job.Load(File);
	string dustbin;
	File >> dustbin;
//	g_pMainState->m_ZhuXian.Load(File);
	g_pMainState->m_ZhiXian.Load(File);
	g_pMainState->m_ZhiXian2.Load(File);
	g_pMainState->m_ZhiXian3.Load(File);
}
void cInterfaceSystem::SaveATrigger(cTrigger* trigger, ofstream& File)
{
	File << "\n";
	File << trigger->m_TaskList.size() << " ";
	for (int i = 0; i < trigger->m_TaskList.size(); i++)
	{
		File << trigger->m_TaskList[i].m_pTask->m_type << " ";
		File << trigger->m_TaskList[i].m_pTask->m_HuanShu << " ";
		File << trigger->m_TaskList[i].m_Stage << " ";
	}
	File << "\n";
}
void cInterfaceSystem::LoadATrigger(cTrigger* trigger, ifstream& File)
{
	int num;
	File >> num;
	int stage;
	int type;
	int huanshu;
	trigger->Clear();
	for (int i = 0; i < num; i++)
	{
		File >> type;
		File >> huanshu;
		File >> stage;
		cTaskFather* ptask = g_pMainState->FindTaskByID(type);
		ptask->m_HuanShu = huanshu;
		trigger->AddTask(ptask, stage);
	}

}

void cInterfaceSystem::SaveFriend(ofstream& File)
{
	g_pMainState->m_Friend.Save(File);
}

void cInterfaceSystem::LoadFriend(ifstream& File)
{
	g_pMainState->m_Friend.Load(File);
}

void cInterfaceSystem::GetSaveTitle(vector<string>& strselect)
{
	strselect.resize(4);
	int nowid = -1;
	for (int i = 0; i < 4; i++)
	{
		ifstream File3;
		ostringstream oss;
		//		oss <<g_strDataPath <<"存档//";
//		oss << g_pathSave;
		oss << i;
		oss << ".txt";
		File3.open(oss.str());
		if (!File3)
		{
			strselect[i] = "无";
			continue;
		}
		oss.str("");
		//读取地点

		int xpos, lv;
		//保存时间
		File3 >> xpos;
		File3 >> lv;
		if (nowid < xpos)
		{
			nowid = xpos;
		}
		oss << "第" << xpos << "次存档,等级:" << lv;
		strselect[i] = oss.str();
	}
	ifstream File;
	ostringstream oss;
	//	oss << g_strDataPath<< "存档//5.txt";
//	oss << g_pathSave << "5.txt";
	File.open(oss.str());
	if (!File)return;
	int newid;
	File >> newid;
	File.close();
	strselect[newid] += "    最新";
}

