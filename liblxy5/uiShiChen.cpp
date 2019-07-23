#include "_global.h"

static time_t s_tt;
static tm* s_t;
static int s_sec;
void cShiCheng::stepMiliSec()
{
	s_tt = time(nullptr);
	s_t = localtime(&s_tt);
	minute = s_t->tm_min;
	second = s_t->tm_sec;
	s_sec = (minute % 30) * 60 + second;
	if ((s_sec % 150) == 0)
	{
		s_sec /= 150;
		UpdateShiCheng(s_sec * 2);
		if (onSwicths[s_sec])
		{
			onSwicths[s_sec]();
		}
	}
	ss += 1;
	return;
	if (ss%m_fps == 0)  //前进一秒
	{
		second += 1;
		if (60 == second) //前进一分
		{
			second = 0;
			stepMinuteAndAutoSave(1);
		}
	}
	//	srand(ss);
};

void cShiCheng::CountDayOfWeek()
{
	m_week = (day + 2 * month + 3 * (month + 1) / 5 + year / 4 + year / 100 + year / 400) % 7 + 1;
}

void cShiCheng::UpdateShiCheng(int h)
{
	switch (h)
	{
	case 23:
	case 24:
	case 0:
		m_Data.Load(m_23_1);
	case 1:
	case 2:
		m_Data.Load(m_1_3);
		break;
	case 3:
	case 4:
		m_Data.Load(m_3_5);
		break;
	case 5:
	case 6:
		m_Data.Load(m_5_7);
		break;
	case 7:
	case 8:
		m_Data.Load(m_7_9);
		break;
	case 9:
	case 10:
		m_Data.Load(m_9_11);
		break;
	case 11:
	case 12:
		m_Data.Load(m_11_13);
		break;
	case 13:
	case 14:
		m_Data.Load(m_13_15);
		break;
	case 15:
	case 16:
		m_Data.Load(m_15_17);
		break;
	case 17:
	case 18:
		m_Data.Load(m_17_19);
		break;
	case 19:
	case 20:
		m_Data.Load(m_19_21);
		break;
	case 21:
	case 22:
		m_Data.Load(m_21_23);
		break;
	}
	if (hour > 11 && hour < 24)
	{
	m_bWhite = true;

	}
	else
	{
	m_bWhite = false;
	}
	g_pMainState->m_InterfaceDoor.SetWhite(m_bWhite);
}

void cShiCheng::Save(ofstream& File)
{
	//保存时间
	File << m_fps << " ";
	File << year << " ";
	File << month << " ";
	File << day << " ";
	File << minute << " ";
	File << second << " ";
	File << ss << " ";
	File << "\n";
}

void cShiCheng::Load(ifstream& File)
{
	File >> m_fps;
	File >> year;
	File >> month;
	File >> day;
	File >> minute;
	File >> second;
	File >> ss;
	g_pMainState->m_InterfaceDoor.m_TimeShiCheng.Init(
		m_fps,
		year,
		month,
		day,
		hour,
		minute,
		second
		);
}

void cShiCheng::stepMinuteAndAutoSave(int time)
{
	minute += time;
	if (minute % 5 == 0)
	{
		if (g_StateType == STATE_MAIN)
		{
			if (g_pMainState->m_Dialog.m_NeedShow == false)
			{
				g_pMainState->m_InterfaceSystem.Save(3);
				//	g_pMainState->m_Channel.AddNewString("自动在第四个位置存档");
			}
		}
	}
	if (minute >= 60)
	{
		AddHour();
		minute -= 60;
	}
}
void cShiCheng::AddHour(int num)
{
	hour += num;
	if (hour == 24)
	{
		hour = 0;
		AddDay();
	}
	//g_pMainState->m_TriggerTime.Process();
	//UpdateShiCheng(hour);
}
void cShiCheng::AddDay()
{
	day += 1;
	int days = 31;
	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		days = 30;
		break;
	case 2:
		if (0 == year % 4)
		{
			days = 28;
		}
		else
		{
			days = 29;
		}
		break;
	}
	if (day == days)   //前进一月
	{
		day = 1;
		AddMonth();
	}
	//用蔡勒公式计算星期
	CountDayOfWeek();

	//更新好友
	g_pMainState->m_Friend.AddDay();
}

void cShiCheng::AddMonth()
{
	month += 1;
	if (12 == month)   //前进一年
	{
		month = 1;
		AddYear();
	}
}

void cShiCheng::AddYear()
{
	year += 1;
}

cShiCheng::cShiCheng()
{
	m_23_1 = 0x361FA820;
	m_1_3 = 0xC0A66903;
	m_3_5 = 0xD1D11294;
	m_5_7 = 0xAA7DEB05;
	m_7_9 = 0x21274A87;
	m_9_11 = 0x9C4978D;
	m_11_13 = 0xC9E2F072;
	m_13_15 = 0x2ACB36B2;
	m_15_17 = 0xC26BF189;
	m_17_19 = 0x1AA170AE;
	m_19_21 = 0x7921D3A3;
	m_21_23 = 0xEA7CAB84;
	m_Data.SetX(0);
	m_Data.SetY(25);
	m_Data.SetStatic(true);
	forr(onSwicths, i)
	{
		onSwicths[i] = nullptr;
	}
}















bool cInterfaceDoor::Init()
{
	if (m_bInit)return true;
	m_bInit = true;

	m_CharacterPos.SetColor(RGB(255, 255, 255));
	m_CharacterPos.SetXCenter(56);
	m_CharacterPos.SetY(63);
	m_MapName.SetXCenter(60);
	m_MapName.SetY(12);
	m_MapName.SetColor(RGB(255, 255, 255));
	m_MapNameNeedShow = true;
	m_GlimSelect = 0;


	m_WorldmapGlim.Load(3136727389);
	ccm::get()->pushWdf("时辰面板灯笼", 3136727389);
	m_WorldmapGlim.m_isStatic = true;
	m_Glim.Load(3136727389);
	m_Glim.m_isStatic = true;
	m_MapGlim.Load(3136727389);
	m_MapGlim.m_isStatic = true;
	m_Door.Load(0xDE3F48B7);
	ccm::get()->pushWdf("时辰面板", 0xDE3F48B7);
	m_Door.m_isStatic = true;
	m_SmallPeople[0].Load(0xAC307575);//走
	m_SmallPeople[1].Load(3351166789); //站
	ccm::get()->pushWdf("时辰面板人走", 0xAC307575);
	ccm::get()->pushWdf("时辰面板人站", 3351166789);
	m_Door.SetX(0);
	m_Door.SetY(0);
	m_WorldmapGlim.SetX(96);
	m_WorldmapGlim.SetY(25);

	m_Glim.SetX(96);
	m_Glim.SetY(40);

	m_MapGlim.SetX(96);
	m_MapGlim.SetY(55);
	for (int i = 0; i < 2; i++)
	{
		m_SmallPeople[1].SetX(60);
		m_SmallPeople[1].SetY(60);
	}
	m_MapName.m_hFont = g_pMainState->m_hFont[0];
	return true;
}

bool cInterfaceDoor::Show(cCanvas* pCanvas)
{
// 	if (g_GlobalValues[9] > 0)
// 	{
// 		return true;
// 	}
	pCanvas->Add(&m_Back, 1);
	pCanvas->Add(&m_Door, 1);
	pCanvas->Add(&m_WorldmapGlim, 1);
	pCanvas->Add(&m_Glim, 1);
	pCanvas->Add(&m_MapGlim, 1);
	pCanvas->Add(&m_SmallPeople[1], 1);
	pCanvas->Add(&m_TimeShiCheng.m_Data, 1, false);//显示时辰

	pCanvas->Add(&m_CharacterPos);

	if (m_MapNameNeedShow)
	{
		pCanvas->Add(&m_MapName);
	}
	return true;
}

bool cInterfaceDoor::ProcessInput()
{
	m_TimeShiCheng.stepMiliSec();

// 	if (g_GlobalValues[9] > 0)
// 	{
// 		return true;
// 	}
	if (m_Sleeptime > 0)
	{
		g_pMainState->SetMouseOnMap(false);
		m_Sleeptime -= 1;
		return true;
	}

	if (m_bRunMode <2)
	{
		if (m_TimeShiCheng.ss % 3 == 1)
		{
			if (m_bRunMode)
			{
				m_MapName.m_x -= 1;
				m_MapName.SetShowWidth(m_MapName.m_ShowWidth + 1);
				if (m_MapName.m_x < 23)
				{
					m_bRunMode = 0;
				}
			}
			else
			{
				m_MapName.SetxOffset2(m_MapName.m_xOffset2 + 1);

				if (m_MapName.GetShowWidth() < 2)
				{
					m_MapName.SetX(21 + wid);
					m_MapName.SetxOffset2(0);
					m_MapName.SetShowWidth(1);
					m_bRunMode = 1;
				}
			}
			m_MapName.m_bMove = true;
		}
	}
	if (g_StateType != STATE_MAIN)return false;
	CheckFight();
	cObj* pPc1 = g_pMainState->m_FightWorkList[g_pMainState->m_HeroID].m_pObj;
	if ((pPc1->GetX() != m_xoldHeroPos)
		|| (pPc1->GetY() != m_yoldHeroPos))
	{
		m_xoldHeroPos = pPc1->GetX();
		m_yoldHeroPos = pPc1->GetY();
		UpdatePos(pPc1);
	}

	if (!g_pMainState->GetLockMouse())return true;
	ResetButton();
	if (g_yMouse > m_Door.m_PreShowRect.bottom)return true;
	if (g_xMouse > m_Door.m_PreShowRect.right)return true;
	g_pMainState->SetMouseOnMap(false);


	if (CheckOn(&m_MapGlim, 3))return true;
	if (CheckOn(&m_Glim, 2))return true;
	if (CheckOn(&m_WorldmapGlim, 1))return true;
	return false;
}

bool cInterfaceDoor::CheckL()
{
	if (g_pMainState->Mouse.GetButtonState(MOUSE_LBUTTON))
	{
		g_pMainState->Mouse.SetLock(MOUSE_LBUTTON);
	}
	else return false;
	m_Sleeptime = 3;
	switch (m_Select)
	{
	case 1:
		g_pMainState->m_InterfaceSmallMap.OnOff(!g_pMainState->m_InterfaceSmallMap.m_NeedShow);
		return true;
		break;
	case 2:
		if (g_pMainState->m_Map._isTeleporting = !g_pMainState->m_Map._isTeleporting)
		{
			g_pMainState->m_Tags.Add("开启小地图瞬移");
		}
		else
		{
			g_pMainState->m_Tags.Add("关闭小地图瞬移");
		}
		break;
	case 3:
		g_pMainState->ClearInterfaceSetShow();
		g_pMainState->m_WorldMap.OnOff(!g_pMainState->m_WorldMap.m_NeedShow);
		return true;
		break;
	default:
		break;
	}
	return false;
}

void cInterfaceDoor::UpdatePos(cObj* pObj)
{
	if (!g_pMainState)return;
	ostringstream oss;
	m_HeroX = pObj->GetX() / 20;
	m_HeroY = (g_pMainState->m_Map.m_pMap->m_Height - pObj->GetY()) / 20;
	oss << "X:" << m_HeroX << " Y:" << m_HeroY;  //显示角色坐标	
	m_CharacterPos.SetString(oss.str());
	m_CharacterPos.UpdateXCenter();
	m_CharacterPos.m_bMove = true;
}

void cInterfaceDoor::SetName(string name)
{
	g_pMainState->m_Canvas.SetRedraw(m_MapName.m_PreShowRect);
	m_MapName.SetString(name);
	if (m_MapName.GetWidth() > wid)
	{
		m_MapName.SetX(22);
		m_MapName.SetShowWidth(wid);
		m_bRunMode = 0;
	}
	else
	{
		m_MapName.UpdateXCenter();
		m_bRunMode = 2;
	}
}

void cInterfaceDoor::CheckFight()
{
	if (!m_pTask)return;
	if (m_AvoidFight == 2) return;//不遇怪

	switch (g_pMainState->m_Map.m_MapType)//m_stage == 3)
	{
	case 2://明雷
		if (g_pHeroObj->m_AstartPathIndex != -2) //站立时不遇怪
		{
			int xpos, ypos;
			cObj* p;
			xpos = g_pHeroObj->GetX();
			ypos = g_pHeroObj->GetY();
			for (int i = 0; i < g_pMainState->m_ObjNumber; i++)
			{
				if (g_pMainState->m_pObj[i]->m_IndexType != INDEXTYEP_PET)continue;
				p = g_pMainState->m_pObj[i];
				cPet* pPet = (cPet*)p->m_pIndex;
				string name = p->m_TrueName.GetString();
				if (0 != name.compare(pPet->GetData()->m_Name))
					continue;
				if (abs(p->GetX() - xpos)>25)continue;
				if (abs(p->GetY() - ypos) > 25)continue;
				g_pMainState->m_TaskNormal.m_pNpc = g_pMainState->m_pObj[i];
				m_pTask->Process(m_stage);
				return;
			}
		}
		if (m_TimeShiCheng.second % 8 == 1)
		{
			cObj* p;
			for (int i = rand() % g_pMainState->m_ObjNumber; i < g_pMainState->m_ObjNumber; i++)
			{
				if (g_pMainState->m_pObj[i]->m_IndexType != INDEXTYEP_PET)continue;
				p = g_pMainState->m_pObj[i];
				cPet* pPet = (cPet*)p->m_pIndex;
				string name = p->m_TrueName.GetString();
				if (0 != name.compare(pPet->GetData()->m_Name))
					continue;
				int xmove = 0;
				int ymove = 0;
				int gap = 128;
			//	m_TimeShiCheng.stepMiliSec();
				switch (rand() % 8)
				{
				case 0:xmove = -gap; ymove = -gap; break;
				case 1:xmove = 0; ymove = -gap; break;
				case 2:xmove = -gap; ymove = 0; break;
				case 3:xmove = gap; ymove = -gap; break;
				case 4:xmove = -gap; ymove = gap; break;
				case 5:xmove = gap; ymove = 0; break;
				case 6:xmove = 0; ymove = gap; break;
				case 7:xmove = gap; ymove = gap; break;
				}
				p->m_AstartPathIndex = -1;
				p->setNextTargetOnAstart(g_pMainState->m_pObj[i]->GetX() + xmove, g_pMainState->m_pObj[i]->GetY() + ymove);
				return;
			}
		}
		//}	
		break;
	case 1:
		if (1) //暗雷
		{
			if (g_pMainState->_autoGhost)
			{
				return;
			}
			if (g_pMainState->_guaji == 0 && g_pHeroObj->m_AstartPathIndex == -2)return; //站立时不遇怪
			if (m_AvoidFight == 1) //摄妖香不遇怪
			{
				if (g_pCharacter->m_PcData.m_Lv > g_pMainState->m_Map.m_EnemyLv)return;
			}
			if (m_nowtimeleast > 0)
			{
				m_nowtimeleast -= 1;
			}
			else
			{
				m_pTask->Process(m_stage);
				m_nowtimeleast = m_timeleast + (rand() % 50 * m_timeleast) / 100;
			}
		}
	}
}

void cInterfaceDoor::SetTrigger(cTaskFather* pFather, int stage, int least/*=100*/)
{
	if (pFather)
	{
		m_pTask = pFather;
		m_stage = stage;
		if (m_bHalf)least /= 2;
		m_timeleast = least;
		/*	if (0==m_nowtimeleast)
		m_nowtimeleast = least;*/
		return;
	}
	else
	{
		m_nowtimeleast = 400;
		m_pTask = 0;
	}
}

void cInterfaceDoor::SetWhite(int b)
{
	if (m_bWhite == b)return;
	m_bWhite = b;
	if (b)
	{
		m_Back.Load(0x9DF6DEBC); //白天	
		ccm::get()->pushWdf("时辰面板白天", 0x9DF6DEBC);
	}
	else
	{
		m_Back.Load(2574487372);  //黑天
		ccm::get()->pushWdf("时辰面板晚上", 2574487372);
	}
	m_Back.SetStatic(true);
	m_Back.SetX(20);
	m_Back.SetY(35);
	m_Back.SetShowWidth(80);
}

void cInterfaceDoor::Save(ofstream& File)
{
	File << m_SaveNum << " ";
	File << g_pCharacter->m_PcData.m_Lv << " ";
	File << m_bWhite << " ";
	File << m_nowtimeleast << " ";
	m_SaveNum += 1;
}

void cInterfaceDoor::Load(ifstream& File)
{
	File >> m_SaveNum;
	int dustbin;
	File >> dustbin;
	m_SaveNum += 1;
	int bwhite;
	File >> bwhite;
	SetWhite(bwhite);
	File >> m_nowtimeleast;
}

void cInterfaceDoor::SetHalf(bool bTrue /*= true*/)
{
	if (bTrue)bTrue = !m_bHalf;
	m_bHalf = bTrue;
	if (bTrue)
	{
		m_timeleast /= 2;
		g_pMainState->m_Tags.Add("遇怪率增加了");
	}
	else
	{
		m_timeleast *= 2;
		g_pMainState->m_Tags.Add("遇怪率正常了");
	}
}








