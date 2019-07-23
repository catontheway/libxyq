#include "_global.h"
#include "_txt.h"

//#define ccc_checkwas

static int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}



// cocos2dx
static int gettimeofday(struct timeval * val, struct timezone *)
{
	if (val)
	{
		LARGE_INTEGER liTime, liFreq;
		QueryPerformanceFrequency(&liFreq);
		QueryPerformanceCounter(&liTime);
		val->tv_sec = (long)(liTime.QuadPart / liFreq.QuadPart);
		val->tv_usec = (long)(liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0);
	}
	return 0;
}



static bool /*Application::*/openURL(const std::string &url)
{
	WCHAR *temp = new WCHAR[url.size() + 1];
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), url.size() + 1, temp, url.size() + 1);
	HINSTANCE r = ShellExecuteW(NULL, L"open", temp, NULL, NULL, SW_SHOWNORMAL);
	delete[] temp;
	return (size_t)r > 32;
}



#if 0
Application::Application()
	: _instance(nullptr)
	, _accelTable(nullptr)
{
	_instance = GetModuleHandle(nullptr);
	_animationInterval.QuadPart = 0;
	CC_ASSERT(!sm_pSharedApplication);
	sm_pSharedApplication = this;

}

Application::~Application()
{
	CC_ASSERT(this == sm_pSharedApplication);
	sm_pSharedApplication = nullptr;
}

int Application::run()
{
	//     PVRFrameEnableControlWindow(false);
	// 
	//     ///////////////////////////////////////////////////////////////////////////
	//     /////////////// changing timer resolution
	//     ///////////////////////////////////////////////////////////////////////////
	//     UINT TARGET_RESOLUTION = 1; // 1 millisecond target resolution
	//     TIMECAPS tc;
	//     UINT wTimerRes = 0;
	//     if (TIMERR_NOERROR == timeGetDevCaps(&tc, sizeof(TIMECAPS)))
	//     {
	//         wTimerRes = std::min(std::max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	//         timeBeginPeriod(wTimerRes);
	//     }

	// Main message loop:
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceCounter(&nLast);

	initGLContextAttrs();

	// Initialize instance and cocos2d.
	if (!applicationDidFinishLaunching())
	{
		return 0;
	}
	auto director = Director::getInstance();
	//    auto glview = director->getOpenGLView();

	// Retain glview to avoid glview being released in the while loop
	//    glview->retain();

	LONGLONG interval = 0LL;
	LONG waitMS = 0L;

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	while (true/*!glview->windowShouldClose()*/)
	{
		QueryPerformanceCounter(&nNow);
		interval = nNow.QuadPart - nLast.QuadPart;
		if (interval >= _animationInterval.QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart;
			director->mainLoop();
			//          glview->pollEvents();
		}
		else
		{
			// The precision of timer on Windows is set to highest (1ms) by 'timeBeginPeriod' from above code,
			// but it's still not precise enough. For example, if the precision of timer is 1ms,
			// Sleep(3) may make a sleep of 2ms or 4ms. Therefore, we subtract 1ms here to make Sleep time shorter.
			// If 'waitMS' is equal or less than 1ms, don't sleep and run into next loop to
			// boost CPU to next frame accurately.
			waitMS = (_animationInterval.QuadPart - interval) * 1000LL / freq.QuadPart - 1L;
			if (waitMS > 1L)
				Sleep(waitMS);
		}
	}

	// Director should still do a cleanup if the window was closed manually.
	//    if (glview->isOpenGLReady())


	{
		director->end();
		director->mainLoop();
		director = nullptr;
	}
	//    glview->release();

	///////////////////////////////////////////////////////////////////////////
	/////////////// restoring timer resolution
	///////////////////////////////////////////////////////////////////////////
	//     if (wTimerRes != 0)
	//     {
	//         timeEndPeriod(wTimerRes);
	//     }
	return 0;
}



void Application::setAnimationInterval(float interval)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	_animationInterval.QuadPart = (LONGLONG)(interval * freq.QuadPart);
}
#endif


bool CMainState::Init(void* pData)
{
	if (isInit)return true;
	isInit = true;

	Init2();

	Init3();

	isInit = true;

	ResetAll();
	g_pMainState->m_InterfaceTeam.SetFormation(normal);
	g_pMainState->m_InterfaceTeam.SetFormation(normal, true);
	g_pMainState->m_InterfaceDoor.m_TimeShiCheng.Init(g_FPS, 0, 0, 0, 0, 0, 0);



//	m_ZhuXian.Process0(0);
	ifstream ifile(g_pathSave + "存档.sav");
	if (!ifile.is_open())
	{
		initGame();
		_langtimeLast = 0;
	}
	else
	{
		ifile.close();
		ifile.open(g_pathSave + "存档.txt");
		if (!ifile.is_open())
		{
			ifile.close();
			m_InterfaceSystem.Load(0);
		}
		else
		{
			ifile.close();
			m_InterfaceSystem.Load(1);
// 			time_t tt = time(nullptr);
// 			tm* t = localtime(&tt);
// 			int _yearDay = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;
// 			if (_yearDay != g_GlobalValues[18])
// 			{
// 				_uiSign.OnOff(true);
// 			}	
		}
		g_pMainState->_langtimeLast = g_GlobalValues[20];
	//	g_pHeroObj->say("你肯定没看公告,没看小白说明图#118", 0xFFF);
	}

	// 当前版本
	g_GlobalValues[127] = 20180320;

	if (getMinLv() <= 30)
	{
		m_ZhuXian.SetChapter(0);
		m_ZhuXian.Process(0);
	}

	m_Tags.Add("按 F 召唤说明书");
	m_Tags.Add("更多游戏信息, 请查看资料片");
	return true;
}


bool CMainState::Frame(void* pData)
{

	Init();
	UpDateInput();
	ProcessInput();
	if (g_StateType != STATE_MAIN)
	{
		return true;
	}
	if (g_pMainState->m_InterfaceDoor.m_TimeShiCheng.ss % 3 == 1)
	{
		TeamFollow();
	}
	MoveObj();

	ShowObj();
//	if (g_GlobalValues[9] < 2)
	ShowInterface();
	ShowInterface2();
	m_Accelator.ProcessAccelator();


	if (g_pHeroObj->m_AstartPathIndex > -2)
	{
		m_Map.CheckChuanSong();
	}
	m_Canvas.Show();
	m_Map.m_pMap->Follow(m_FightWorkList[m_HeroID].m_pObj);

	m_Mp3.CheckEnd();

	if (_autoGhost > 0)
	{
		m_TaskZhuaGui.Process(10086);
	}

	return true;
}


void CMainState::resetLangTime()
{
	_langtimeOnce = g_iFPS / 60;
	_langtimeLast = g_GlobalValues[20] = 0;
}




bool CMainState::Free()
{
	g_StateType = STATE_GAMEOVER;
	m_ScriptTemplate.Free();
	//先召还
	for (int i = 0; i < 20; i++)
	{
		if (m_FightWorkList[i].isExist)
			if (m_FightWorkList[i].m_pObj->GetDataType() == INDEXTYEP_CHARACTER)
			{
			cCharacter* pc = (cCharacter*)m_FightWorkList[i].m_pObj->m_pIndex;
			if (pc->m_PcData.m_FightPetID > -1)
			{
				SetFightPet(i, -1);
			}
			}
	}
	//把存在的东西删掉
	for (int i = 0; i < 20; i++)
	{
		g_pMainState->FreeFightList(i);
	}
	for (int i = 0; i < 20; i++)
	{
		SAFE_DELETE(m_FightWorkList[i].m_pObj);
	}


	m_Dialog.Free();
	m_Map.Free();

	SelectObject(g_DC, m_hOldFont);
	SelectObject(g_DC2, m_hOldFont2);
	for (int i = 0; i < 6; i++)
		DeleteObject(m_hFont[i]);

	m_InterfacePet.Free();

	//删除我们所创建的对象
	//g_pDirectSound->Release();
	return true;
}


CMainState::~CMainState()
{
	Free();
	DeleteObject(m_blackbrush);
	SAFE_DELETE_ARRAY(m_MaskList);
}


void CMainState::LoadList()
{
	if (m_LoadList)return;
	m_LoadList = true;


// 	ifstream File;
// 	ifstream File2;
// 	string strdustbin;
// 	int intdustbin;
// 	string path = g_pathData;
// 	path += "角色//角色.txt";
// 	File.open(path.c_str());
// 	path = g_pathData;
// 	path += "角色//角色声音.txt";
// 	File2.open(path.c_str());
// 	getline(File2, strdustbin);
// 	int charnum2;
// 	File >> charnum2;
// 	m_pCharacterDataList.resize(charnum2);
// 
// 	for (int i = 0; i < charnum2; i++)
// 	{
// 		cct::get()->strDescTemp = toString("角色%d", i);
// 		m_pCharacterDataList[i].Read(File);
// 		//读取声音
// 		File2 >> intdustbin;
// 		getline(File2, strdustbin);
// 		for (int j = 0; j < m_pCharacterDataList[i].m_Pos.size(); j++)
// 		{
// 			m_pCharacterDataList[i].m_Pos[j].m_Sound.Read(File2);
// 			if (i == 15 && !cct::get()->isPushRole15)
// 			{
// 				continue;
// 			}
// 			cct::get()->pushRoleHead(cct::get()->strDescTemp + "(声音)攻", m_pCharacterDataList[i].m_Pos[j].m_Sound.m_soundattack);
// 			cct::get()->pushRoleHead(cct::get()->strDescTemp + "(声音)死", m_pCharacterDataList[i].m_Pos[j].m_Sound.m_sounddead);
// 			cct::get()->pushRoleHead(cct::get()->strDescTemp + "(声音)法", m_pCharacterDataList[i].m_Pos[j].m_Sound.m_soundmajic);
// 			cct::get()->pushRoleHead(cct::get()->strDescTemp + "(声音)受", m_pCharacterDataList[i].m_Pos[j].m_Sound.m_soundsuffer);
// 			cct::get()->pushRoleHead(cct::get()->strDescTemp + "(声音)防", m_pCharacterDataList[i].m_Pos[j].m_Sound.m_sounddefend);
// 		}
// 	}
// 
// 	File.close();
// 	File2.close();
	cWasFile was;
	const auto& roles = ctt::getRoles();
	vector<ulong> colors;
	for (int i = 0; i < 10; ++i)
	{
		colors.push_back(8192 + i);
	}
	for (int i = 0; i < 5; ++i)
	{
		colors.push_back(8208 + i);
	}
	for (int i = 0; i < 3; ++i)
	{
		colors.push_back(0);
	}

	const auto& cTable = ctt::getColors();
	forv(roles, k)
	{
		const auto& r = roles[k];
		auto& c = m_pCharacterDataList[k];
		c.m_ID = (int)r.e;
		c.m_Pos.resize(r.actions.size());
		c.m_ColorID = colors[c.m_ID];
		const auto& it = cTable.find(c.m_ColorID);
		if (it != cTable.end())
		{
			c.m_ColorID = it->second;
		}
		c.m_Name = r.name;
//		c.m_Autorace = r.race;
//		c.m_bSex;
		c.m_posbow = r.body.bow;
		c.m_poscry = r.body.cry;
		c.m_posdance = r.body.dance;
		c.m_posgreet = r.body.greet;
		c.m_possit = r.body.sit;
		c.m_posangry = r.body.angry;

		forv(c.m_Pos, i)
		{
			
			const auto& ac = r.actions[i];
			const auto& a = ac.action;

			auto& p = c.m_Pos[i];
			p.m_attack = a.atk;
			p.m_attack2 = a.atk;
			p.m_defend = a.def;
			p.m_dead = a.dead;
			p.m_fstand = a.await;
			p.m_magic = a.maigc;
			p.m_return = a.back;
			p.m_run = a.go;
			p.m_stand = a.stand;
			p.m_walk = a.walk;
			p.m_suffer = a.atkd;


#ifdef ccc_checkwas
			was.Load(p.m_attack);
			was.Load(p.m_attack2);
			was.Load(p.m_defend);
			was.Load(p.m_dead);
			was.Load(p.m_fstand);
			was.Load(p.m_magic);
			was.Load(p.m_return);
			was.Load(p.m_run);
			was.Load(p.m_stand);
			was.Load(p.m_walk);
			was.Load(p.m_suffer);
#endif

			auto& s = p.m_Sound;
			s.m_sounddead = ac.sound.dead;
			s.m_soundsuffer = ac.sound.atkd;
			s.m_soundmajic = ac.sound.magic;
			s.m_soundattack = ac.sound.atk;
			s.m_soundattack2 = ac.sound.atk2;
			s.m_sounddefend = ac.sound.def;

#ifdef ccc_checkwas
			was.Load(s.m_sounddead);
			was.Load(s.m_soundsuffer);
			was.Load(s.m_soundattack);
			was.Load(s.m_soundattack2);
			was.Load(s.m_soundmajic);
			was.Load(s.m_sounddefend);
#endif

			auto& o = p.m_Offset;
			o.m_xOff = ac.offx;
			o.m_yOff = o.m_xOff >> 1;
			o.m_Point[0] = ac.atk;
			o.m_Point[1] = o.m_Point[0];
// 			if (c.m_ID == eJueSe::eJuSe飞燕女 && i == 1)
// 			{
// 				o.m_Point[1] = 7;
// 			}
// 			else if (c.m_ID == eJueSe::eJuSe虎头怪 && i == 0)
// 			{
// 				o.m_Point[1] = 8;
// 			}
// 			else if(c.m_ID == eJueSe::eJuSe龙太子 && i == 0)
// 			{
// 				o.m_Point[1] = 5;
// 			}
			//角色只有一种攻击
			o.m_Point2[0] = o.m_Point[0];
			o.m_Point2[1] = o.m_Point[1];
			o.m_MagicPoint = r.actions[i].magic;
		}

		c.m_Head[0].m_dialog = r.head.small;
		c.m_Head[0].m_HeadFriend = r.head.amigo;
		auto& hs = c.m_Head[0].m_HeadMoods;
		//右上角的头像
		hs[0].m_smallhead = r.head.big;
		//道具栏中的头像
		hs[0].m_bighead = r.head.dialog;
		hs[1].m_smallhead = r.head.smallHappy;
		hs[1].m_bighead = r.head.bigHappy;
		hs[2].m_smallhead = r.head.smallSad;
		hs[2].m_bighead = r.head.bigSad;
		hs[3].m_smallhead = r.head.smallProud;
		hs[3].m_bighead = r.head.bigProud;

		c.m_Head[1].m_dialog = r.head2.dialog;
		c.m_Head[1].m_HeadFriend = r.head2.amigo;
		auto& h2s = c.m_Head[1].m_HeadMoods;
		//右上角的头像
		h2s[0].m_smallhead = r.head2.small;
		//道具栏中的头像
		h2s[0].m_bighead = r.head2.big;
		h2s[1].m_smallhead = r.head2.smallHappy;
		h2s[1].m_bighead = r.head2.bigHappy;
		h2s[2].m_smallhead = r.head2.smallSad;
		h2s[2].m_bighead = r.head2.bigSad;
		h2s[3].m_smallhead = r.head2.smallProud;
		h2s[3].m_bighead = r.head2.bigProud;

		c.m_Head[2].m_dialog = r.head3.small;
		c.m_Head[2].m_HeadFriend = r.head3.amigo;
		auto& h3s = c.m_Head[2].m_HeadMoods;
		//右上角的头像
		h3s[0].m_smallhead = r.head3.big;
		//道具栏中的头像
		h3s[0].m_bighead = r.head3.dialog;
		h3s[1].m_smallhead = r.head3.smallHappy;
		h3s[1].m_bighead = r.head3.bigHappy;
		h3s[2].m_smallhead = r.head3.smallSad;
		h3s[2].m_bighead = r.head3.bigSad;
		h3s[3].m_smallhead = r.head3.smallProud;
		h3s[3].m_bighead = r.head3.bigProud;

#ifdef ccc_checkwas
		for (int kk = 0; kk <= 2; ++kk)
		{
			was.Load(c.m_Head[kk].m_dialog);
			was.Load(c.m_Head[kk].m_HeadFriend);
			for (int ii = 0; ii <= 3; ++ii)
			{
				was.Load(c.m_Head[kk].m_HeadMoods[ii].m_bighead);
				was.Load(c.m_Head[kk].m_HeadMoods[ii].m_smallhead);
			}

		}
#endif
	}

	if (!cct::getINT(6))
	{
		m_pCharacterDataList[eJuSe逍遥生].m_Pos[1].m_stand = m_pCharacterDataList[eJuSe逍遥生].m_Pos[0].m_stand;
	}

	m_pCharacterDataList[15].m_Pos[0].m_Sound = m_pCharacterDataList[0].m_Pos[0].m_Sound;
	m_pCharacterDataList[16].m_Pos[0].m_Sound = m_pCharacterDataList[eJueSe::eJuSe巫蛮儿].m_Pos[0].m_Sound;
	m_pCharacterDataList[17].m_Pos[0].m_Sound = m_pCharacterDataList[eJueSe::eJuSe飞燕女].m_Pos[0].m_Sound;
// 	ifstream File6;
// 	path = g_pathData;
// 	path += "NPC.txt";
// 	File6.open(path.c_str());
// 	int npcnum;
// 	File6 >> npcnum;
// 	m_pNpcList.resize(npcnum);
// 
// 	for (int i = 0; i < npcnum; i++)
// 	{
// 		File6 >> m_pNpcList[i].m_ModeId;
// 		File6 >> m_pNpcList[i].m_name;
// 		File6 >> m_pNpcList[i].m_dialog;
// 		File6 >> m_pNpcList[i].m_stand;
// 		File6 >> m_pNpcList[i].m_walk;
// 		cct::get()->pushNpcHead(string("NPC") + m_pNpcList[i].m_name + "对话", m_pNpcList[i].m_dialog);
// 		cct::get()->pushNpc(string("NPC") + m_pNpcList[i].m_name + "站", m_pNpcList[i].m_stand);
// 		cct::get()->pushNpc(string("NPC") + m_pNpcList[i].m_name + "走", m_pNpcList[i].m_walk);
// 	}
// 	File6.close();


	const auto& npcs = ctt::getNpcs();
	m_pNpcList.resize(npcs.size());
	forv(npcs, k)
	{
		const auto& n = npcs[k];
		auto& npc = m_pNpcList[k];
		npc.m_ModeId = (int)n.e + 1000;
		npc.m_name = n.name;
		npc.m_dialog = n.dialog;
		npc.m_stand = n.stand;
		npc.m_walk = n.walk;

//		ccc_log("%d %s", npc.m_ModeId, npc.m_name.c_str());
#ifdef ccc_checkwas
		was.Load(npc.m_dialog);
		was.Load(npc.m_stand);
		was.Load(npc.m_walk);
#endif
	}

// 	path = g_pathData;
// 	path += "坐骑列表.txt";
// 	m_ZuoQi.Init(path.c_str());


// 	set<int> sts = { 16, 76, 77, 78, 94, 140 };
// 	for (int i = 42; i <= 49; ++i)
// 	{
// 		sts.insert(i);
// 	}
	const auto& zqs = ctt::getZqs();
	forv(m_ZuoQi.m_ZuoQi, k)
	{
		auto& zq = m_ZuoQi.m_ZuoQi[k];
		const auto& z = zqs[k];
		zq.ID = (int)z.e;
		zq.Name = z.name;
		zq.nodeStand = z.stand;
		zq.nodeWalk = z.walk;

#ifdef ccc_checkwas
		was.Load(zq.nodeStand);
		was.Load(zq.nodeWalk);
#endif
		if (k < 8)
		{
			zq.m_ColorID = z.color;
			const auto& it = cTable.find(zq.m_ColorID);
			if (it != cTable.end())
			{
				zq.m_ColorID = it->second;
			}
#ifdef ccc_checkwas
			was.Load(zq.m_ColorID);
#endif
			forv(zq.CharStand, i)
			{
				zq.CharStand[i] = 0;
				zq.CharWalk[i] = 0;
			}
			forv(z.masters, i)
			{
				const auto& m = z.masters[i];
				zq.CharStand[(int)m.master] = m.stand;
				zq.CharWalk[(int)m.master] = m.walk;
#ifdef ccc_checkwas
				was.Load(m.stand);
				was.Load(m.walk);
#endif
			}
			continue;
		}

//		站 16 42-49 76-78 94 140
// 		{ eModel::偃无师yw, 0xC8FDA195, 0xC8FDA428 },
// 		{ eModel::桃夭夭ty, 0x0C8FDA28, 0x0C8FDA70 },
// 		{ eModel::鬼潇潇gx, 0x094C5BFB, 0xFE2D2B18 },
		zq.m_ColorID = 0;
// 		if (sts.find(k) != sts.end())
// 		{
// 			forv(zq.CharStand, i)
// 			{
// 				zq.CharStand[i] = zq.CharWalk[i] = m_pCharacterDataList[i].m_Pos[0].m_stand;
// 			}
// 		}
// 		else
		{
			forv(zq.CharStand, i)
			{
				switch (eModel(i))
				{
				case eModel::剑侠客jx:
				case eModel::逍遥生xy:
				case eModel::飞燕女fy:
				case eModel::英女侠yn:
				case eModel::巫蛮儿wm:
					zq.CharStand[i] = m_ZuoQi.m_ZuoQi[3].CharStand[i];
					zq.CharWalk[i] = m_ZuoQi.m_ZuoQi[3].CharStand[i];
					break;
				case eModel::虎头怪ht:
				case eModel::巨魔王jm:
				case eModel::骨精灵gj:
				case eModel::狐美人hm:
				case eModel::杀破狼sp:
					zq.CharStand[i] = m_ZuoQi.m_ZuoQi[4].CharStand[i];
					zq.CharWalk[i] = m_ZuoQi.m_ZuoQi[4].CharStand[i];
					break;
				case eModel::龙太子lt:
				case eModel::神天兵st:
				case eModel::玄彩蛾xc:
				case eModel::舞天姬wt:
				case eModel::羽灵神yl:
					zq.CharStand[i] = m_ZuoQi.m_ZuoQi[7].CharStand[i];
					zq.CharWalk[i] = m_ZuoQi.m_ZuoQi[7].CharStand[i];
					break;
				case eModel::偃无师yw:
					zq.CharStand[i] = 0xC8FDA195;
					zq.CharWalk[i] = 0xC8FDA428;
					break;
				case eModel::桃夭夭ty:
					zq.CharStand[i] = 0x0C8FDA28;
					zq.CharWalk[i] = 0x0C8FDA70;
					break;
				case eModel::鬼潇潇gx:
					zq.CharStand[i] = 0x094C5BFB;
					zq.CharWalk[i] = 0xFE2D2B18;
					break;
				default:
					break;
				}
#ifdef ccc_checkwas
				was.Load(zq.CharStand[i]);
				was.Load(zq.CharWalk[i]);
#endif
			}
		}
	}



	m_ItemManage.Init();
	m_SkillManager.Init();
	m_ItemManage.m_ItemList[40].resize(m_SkillManager.m_PetSkillList.size());
	const auto& itsj = ctt::getItem(ctt::eItem::兽决s, 0);
	forv (m_ItemManage.m_ItemList[40], i)
	{
		auto& it = m_ItemManage.m_ItemList[40][i];
		it.m_ID = i;
		it.m_Type = (int)ctt::eItem::兽决s;
		it.m_SmallHead = itsj.small;
		it.m_BigHead = itsj.big;
		const auto& uid = m_SkillManager.m_PetSkillList[i].m_BigHead;
		if (uid)
		{
			it.m_SmallHead = uid;
		}
		it.m_Name = itsj.name;
		it.m_Text = m_SkillManager.m_PetSkillList[i].m_Name;
	}
	m_PetDataManager.Init();
// 	for (int i = 0; i < m_ItemManage.m_ItemList[26].size(); ++i)
// 	{
// 		auto& it = m_ItemManage.m_ItemList[26][i];
// 		it.m_SmallHead = m_PetDataManager.m_PetList[i].m_bighead[0];
// 		it.SetLv(0);
// 	}

	auto& cards = m_ItemManage.m_ItemList[(int)ctt::eItem::卡片k];
	forv(cards, i)
	{
		const auto& p = m_PetDataManager.m_PetList[i];
		if (i < 162)
		{
			if (p.m_bighead[1] && p.m_bighead[1] != 0x42475124)
			{
				cards[i].m_SmallHead = p.m_bighead[1];
			}
		}
		else if ((!cards[i].m_SmallHead) && p.m_bighead[1] && p.m_bighead[1] != 0x42475124)
		{
			cards[i].m_SmallHead = p.m_bighead[1];
		}

		if (!cards[i].m_SmallHead)
		{
			cards[i].m_SmallHead = 0x2E030271;
		}
		
		if (!cards[i].m_BigHead)
		{
			cards[i].m_BigHead = 0x8A3FAE92;
		}
		cards[i].m_Name = "变身卡";
		cards[i].m_Text = p.m_Name;

#ifdef ccc_checkwas
 		was.Load(0x8A3FAE92);
#endif
	}

	// 逆鳞 81
	// 炼气 90
	// 普度 102
	// 隐身 123
	// 回首 137
	// 定心 147
	// 盘丝阵 160
	// 碎星决 176
	vector<int> s1s = ctt::getSkillStarts();
	// 催眠 14
	// 漫天 50
	// 牛虱 135
	// 夺魄令 182
	s1s.push_back(14);
	s1s.push_back(50);
	s1s.push_back(135);
	s1s.push_back(182);

	s1s.push_back(2085);
	s1s.push_back(2087);
	s1s.push_back(2089);
	s1s.push_back(2091);
	s1s.push_back(2092);
	s1s.push_back(2093);
	s1s.push_back(2094);
	s1s.push_back(2095);
	s1s.push_back(2098);
	s1s.push_back(2099);
	auto& stones = m_ItemManage.m_ItemList[(int)ctt::eItem::符石f];
	stones.resize(s1s.size());
	forv(stones, i)
	{
		auto& s = stones[i];
		s.m_ID = i;
		if (i > 0)
		{
			s.m_Type = stones[0].m_Type;
			s.m_SmallHead = stones[0].m_SmallHead;
			s.m_BigHead = stones[0].m_BigHead;
		}
	
		const auto& sk = m_SkillManager.GetSkill(s1s[i]);
		if (sk->m_SkillType == ctt::eSkillUse::BattleOther)
		{
			s.m_Name = "追加符石";
		}
		else
		{
			s.m_Name = "状态符石";
		}
		s.m_Text = sk->m_Name;
		s.SetLv(s1s[i]);
	}
}



CMainState::CMainState()
{
//	g_GlobalValues.resize(c_GlobalButtonNum);
	m_MaskList = new char[1024];
	m_FightWorkList.resize(20);
	for (int i = 0; i < c_InterfaceShowNum; i++)
	{
		m_Interface[i] = 0;
	}
	for (int i = 0; i < MAX_OBJ_NUM; i++)
	{
		m_pObj[i] = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		m_FightWorkList[i].m_pObj = 0;
		m_FightWorkList[i].isExist = false;
	}
	m_ObjNumber = 0;
}




void CMainState::Init2()
{
	if (m_bInit2)return;
	m_bInit2 = true;
	// 创建IDirectSound8接口
	DirectSoundCreate8(NULL, &g_pDirectSound, NULL);
	g_pDirectSound->SetCooperativeLevel(g_hWnd, DSSCL_NORMAL);
	g_redbrush = CreateSolidBrush(RGB(255, 0, 0));
	g_blackbrush = CreateSolidBrush(RGB(0, 0, 0));
	g_whitebrush = CreateSolidBrush(RGB(255, 255, 255));
	g_bluebrush = CreateSolidBrush(RGB(0, 0, 255));


	m_hFont.resize(6);
	//中字
	m_hFont[0] = EasyCreateFont(g_fntSize, "Arial");
	//	m_Tags.m_Text.m_hFont = m_hFont[0];
	//	m_hFont[1] = EasyCreateFont(15,  L"华康少女文字W5");
	//	m_hFont[2] = EasyCreateFont(28,  L"汉仪中黑简",700);
	m_hFont[2] = EasyCreateFont(24, "Arial");
	//	m_hFont[3] = EasyCreateFont(24,  L"汉仪柏青体简");
	//	m_hFont[4] = EasyCreateFont(24,  L"方正胖头鱼简体",700);
	//	m_hFont[5] = EasyCreateFont(12,  L"汉仪魏碑简");
	m_hFont[5] = EasyCreateFont(12, "Arial");
	m_hOldFont2 = (HFONT)SelectObject(g_DC2, m_hFont[0]);

	m_Button4.Load(0x86D66B9A);
	m_Button2.Load(0x79D01E0E);
	m_Cancel.Load(0xF11233BB);
	m_HpLine.Load(0x4FD9FFF3);
	m_HpEmptyLine.Load(0x4D0A334C);
	m_Shadow.Load(3705976162);
	m_FNumRed.Load(551);
	m_FNumGreen.Load(552);
	m_FaceTextBack.Load(0xA4120EA9);
	Input.Init();
	Keyboard.Create(&Input, KEYBOARD);
	Mouse.Create(&Input, MOUSE);

	m_Canvas.Init();
	m_Cursor.Init();
	m_InterfaceTeam.Init();

}



void CMainState::Init3()
{
	if (m_bInit3)return;

	////初始化全局变量
// 	for (int i = 0; i < c_GlobalButtonNum; i++)
// 	{
// 		g_GlobalValues[i] = 0;
// 	}
//	m_GlobalButton[0] = 100; //难度
//	m_GlobalButton[1] = 1000;//改成阵型了
//	g_GlobalValues[7] = 2; // 走速

	for (int i = 0; i < 20; i++)
	{
		m_FightWorkList[i].m_pObj = new cObj();
		m_FightWorkList[i].m_pObj->m_IDInFightlist = i;
	}
//	m_FightWorkTemps[0]._moon = m_FightWorkTemps[1]._moon = -1;

	//加载行为模板
	string path;
//	path = g_pathData;
	path += "行为模板.txt";
	m_ScriptTemplate.LoadActionTemplate(path.c_str());
	m_ColorManage.Init();
	m_Tags.Init();
	m_Tag1.Init();
	m_FaceTextBack.SetStatic(true);
	m_FaceTextBack.m_Picture.m_bShadow = 50;
	m_FaceTextBackp.resize(2);
	m_FaceTextBackp[0].Set(&m_FaceTextBack);
	m_FaceTextBackp[1].Set(&m_FaceTextBack);
	m_Channel.Init();
	m_Map.Init();


	LoadList();



	m_Job.Init();
	m_InterfaceDoor.Init();
	for (int i = 0; i < 20; i++)
	{
		m_FightWorkList[i].m_pObj->Init();
		m_FightWorkList[i].m_pObj->m_TrueName.m_bShowOnScreen = false;
//		m_FightWorkList[i].m_pObj->m_TrueName.SetBackColor(RGB(255, 0, 0));
	}

	m_Menu.Init();
	//角色头像
	m_PCHead.Init();

	m_Dialog.Init();
	//设置时辰
	m_InterfaceDoor.m_TimeShiCheng.SetFPS(g_FPS);

	m_bInit3 = true;

	//ifstream File;
	//File.open("2.txt");
	//int dustbin;
	//File >> dustbin;
	//ulong data[2];
	//for (int i = 0; i < 2; i++)
	//	File >> data[i];
	//m_pTestpic.Load(data[0]);
	//m_pTestpic2.Load(data[1]);
	//for (int i = 0; i < 4; i++)
	//{
	//	m_pTestpicp[i].Set(&m_pTestpic);
	//	m_pTestpicp2[i].Set(&m_pTestpic2);
	//
	//}
	//m_pTestpicp[2].m_direction = 1;
	//m_pTestpicp2[2].m_direction=1;
	//m_pTestpicp[3].m_direction = 3;
	//m_pTestpicp2[3].m_direction = 3;
	//m_pTestpicp[0].m_direction = 7;
	//m_pTestpicp2[0].m_direction = 7;
	//m_pTestpicp[1].m_direction = 9;
	//m_pTestpicp2[1].m_direction = 9;

	//m_pTestpicp[0].SetXY(220, 200);
	//m_pTestpicp2[0].SetXY(220, 200);
	//m_pTestpicp[1].SetXY(420, 200);
	//m_pTestpicp2[1].SetXY(420, 200);
	//m_pTestpicp[2].SetXY(220, 300);
	//m_pTestpicp2[2].SetXY(220, 300);
	//m_pTestpicp[3].SetXY(420, 300);
	//m_pTestpicp2[3].SetXY(420, 300);
}



void CMainState::ResetAll()
{
	Init2();
	Init3();
	m_TriggerFightStart.Clear();
	m_TriggerGive.Clear();
	m_TriggerFightSuccess.Clear();
	m_TriggerObj.m_datalist.clear();
	m_TriggerObjMap.m_datalist.clear();
	m_Triggerlv.Clear();
	m_TriggerGive.Clear();
	m_Job.Reset();

	for (int i = 0; i < 20; i++)
	{
		m_FightWorkList[i].Free();
	}
	ClearInterfaceSetShow();
	m_Canvas.m_NeedShowMap = true;
}





HFONT CMainState::EasyCreateFont(int h, string name, int weight)
{
	return CreateFont(
		h, 0,       //字体的高  宽
		0, 0,       //字体显示的角度   字体的角度
		weight,    //字体的磅数   700粗体   
		false,     //斜体
		false,     //下划线
		false,     //删除线
		GB2312_CHARSET,  //字符集
		OUT_CHARACTER_PRECIS,  //输出精度
		CLIP_STROKE_PRECIS,  //裁剪精度
		DEFAULT_QUALITY,  //逻辑字体与输出设备的实际字体之间的精度
		FF_MODERN,      //字体间距
		name.c_str());//L"汉仪魏碑简");//L"方正粗活意简体");//L"方正彩云简体");         //字体名
}


