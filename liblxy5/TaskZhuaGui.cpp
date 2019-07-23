#include "_global.h"

void cTaskZhuaGui::Init()
{
	if (m_bInit)return;
	m_bInit = true;
	m_Firstname = { "子时", "丑时", "寅时", "卯时", "辰时", "已时", "午时", "未时", "申时", "酉时", "戌时", "亥时" };
	m_Secondname = { "一刻", "二刻", "三刻", "四刻" };
	m_Thirdname =
	{
		"诌鬼",
		"假鬼",
		"奸鬼",
		"捣大鬼",
		"冒失鬼",
		"挖渣鬼",
		"仔细鬼",
		"讨吃鬼",
		"地哩鬼",
		"叫街鬼",
		"偷尸鬼",
		"含碜鬼",
		"倒塌鬼",
		"涎脸鬼",
		"滴料鬼",
		"发贱鬼",
		"急急鬼",
		"耍碗鬼",
		"低达鬼",
		"遭瘟鬼",
		"轻薄鬼",
		"浇虚鬼",
		"绵缠鬼",
		"黑眼鬼",
		"龌龊鬼",
		"温斯鬼",
		"不通鬼",
		"诓骗鬼",
		"急赖鬼",
		"心病鬼",
		"醉死鬼",
		"抠掏鬼",
		"伶俐鬼",
		"急突鬼",
		"丢谎鬼",
		"乜斜鬼",
		"撩桥鬼",
		"色中饿鬼"
	};

	m_MapNameList =
	{
		"普陀山",
		"女儿村",
		"建邺城",
		"傲来国",
		"大唐境外",
		"长寿村",
		"江南野外",
		"宝象国",
		"朱紫国",
		"西梁女国",
	};


	m_MapNameList = cct::getFields();

// 	//读取名字列表
// 	ifstream File;
// 	ostringstream oss;
// 	oss << g_pathData << "抓鬼名字.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 	int num;
// 	File >> num;
// 	string data;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> data;
// 		m_Firstname.push_back(data);
// 	}
// 	File >> num;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> data;
// 		m_Secondname.push_back(data);
// 	}
// 	File >> num;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> data;
// 		m_Thirdname.push_back(data);
// 		Q_LOG("\"%s\",", data.c_str());
// 	}
// 	File.close();
// 	oss.str("");
// 	oss << g_pathData << "抓鬼地点.txt";
// 	File.open(oss.str());
// 	if (!File)ERRBOX;
// 	File >> num;
// 	string str;
// 	for (int i = 0; i < num; i++)
// 	{
// 		File >> str;
// 		m_MapNameList.push_back(str);
// 	}

	m_type = 40;
	m_HuanShu = g_GlobalValues[3];
}

bool cTaskZhuaGui::Process(int stage)
{
	CheckInit();
	int r = rand() % 10;
	switch (stage)
	{
	case 0:
	{
		cObj* pObj = g_pMainState->FindObjByName("钟馗");
		if (g_pMainState->m_Job.CheckHaveJob(m_type))
		{
			if (!g_pMainState->_autoGhost)
			{
				pObj->Talk("你已经有任务了");
			}
			return true;
		}

// 		int ournum = g_pMainState->GetPCFightNum();
// 		if (ournum < 2)
// 		{
// 			pObj->Talk("这个任务很危险,你还是再多找点人吧(至少2人组队");
// 			return true;//最少3个人
// 		}

		AutoGetGost(m_Ghost, m_MapNameList[rand() % m_MapNameList.size()]);
		//根据名字决定位置
		int  falsex;
		int  falsey;
		GetErrPos(m_Ghost, falsex, falsey);
//		falsex = m_Ghost.m_x;
//		falsey = m_Ghost.m_y;
		ostringstream oss;
		oss.str("");
		oss << "#R";
		oss << m_Ghost.m_name;
		oss << "#R出逃, 现于#R";
		oss << m_Ghost.m_mapname;
		oss << "#R #Y";
		oss << falsex;
		oss << " ";
		oss << falsey;
		oss << "#Y 附近,请少侠速速缉拿";
		string context = oss.str();
		pObj->Talk(oss.str());
		g_pMainState->m_Dialog.m_pObj = 0;
		pObj->m_AutoRun = false;
		UpdateZGJob();


	//	g_GlobalValues[3] = ++m_HuanShu;

		g_pMainState->m_TriggerObjMap.AddTask(this, 1, m_Ghost);
		return true;
	}
		break;
	case 1:
	{
		ReadyToFight(m_Ghost);
		AddTriggerFightSuccess(3);
		if (g_pMainState->_autoGhost)
		{
			AddTriggerFightFalse(4);
		}
		return true;
	}
		break;
	case 3:

	{
		bool btrigger = false;
		if (m_HuanShu == m_RetNum)btrigger = true;
		m_Ghost.m_modeid = -1;
		m_Ghost.m_mapname = "";
		g_pMainState->m_Map.RemoveNpc(m_Ghost.m_name);
		g_pMainState->m_TriggerObjMap.ReMove(this);
		g_pMainState->m_Job.ReMoveJob(this);
	//	SetJiangLi(22, true, 40, 0, 100, 100);

		g_pMainState->awardklv(152 + m_HuanShu * 5, 32 + m_HuanShu * 3);
		g_pMainState->award125(10 + m_HuanShu * 3, /*110*/150);

		if (0)
		{
			// 草儿特供???

			if (r >= 0 && r < 1)//10%
			{
				g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
				g_pMainState->award5bao();//五宝
				g_pMainState->awardk(600, 800);//10W经验，10W钱
			}
			else if (r >= 1 && r < 2)//10%
			{
				g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
			//	g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石
				g_pMainState->awardk(100, 100);//10W经验，10W钱
				g_pMainState->awardk(600, 800);//10W经验，10W钱
			}
			else if (r >= 2 && r < 4)
			{
				g_pMainState->awardItem(23, rand() % 9, 1, true);
				//	g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石
				g_pMainState->awardk(500, 600);//10W经验，10W钱
			}
			else if (r >= 4 && r <= 7)
			{
				g_pMainState->awardItem(23, rand() % 9, 1, true);
				g_pMainState->awardk(200, 400);//10W经验，10W钱
			}

			else if (r > 7)
			{
				g_pMainState->awardk(100, 100);//10W经验，10W钱
				g_pHeroObj->say("#15我不要当非洲人");;
			}
		}
		if (g_pMainState->_autoGhost)
		{
			g_pMainState->_autoGhost = 2;
			cct::autoSave();
//			return true;
		}

		//得装备
		if ((g_GlobalValues[3] = ++m_HuanShu) >= 10)
		{
			g_GlobalValues[3] = m_HuanShu = 0;
		}
		return true;

		if (btrigger)
		{
			cTaskFather* p = m_pTask;
			m_pTask = 0;
			m_RetNum = 100;
			p->Process(m_RetStage);
		}
		return true;
	}
		break;
	case 4:
		if (g_pMainState->_autoGhost)
		{
			g_pMainState->m_pFightState->DieEffect(1);
			g_pMainState->_autoGhost = 250;
		}
		break;
	case 10086:
	{
		int& k = g_pMainState->_autoGhost;
		if (k == 1)
		{
			if (g_pMainState->m_Job.CheckHaveJob(m_type))
			{
				k = 180;
				return true;
			}
			++k;
			return true;
		}
		if (k >= 2 && k < 240)
		{
			if (++k == 90)
			{
				g_pMainState->m_Map.LoadMap(44, 54, "阴曹地府");
			}
			return true;
		}
		if (k >= 240 && k < 480)
		{
			if (++k == 244)
			{
				Process(0);
			}
			return true;
		}
		if (k == 480)
		{
			if (m_Ghost.m_mapname != g_pMainState->m_Map.m_MapName)
			{
				int x, y;
				g_pMainState->m_Map.AutoGetPos(x, y, m_Ghost.m_mapname);
				g_pMainState->m_Map.LoadMap(x, y, m_Ghost.m_mapname.c_str());
			}
			++k;
			return true;
		}
		if (k >= 481 && k < 600)
		{
			++k;
			return true;
		}
		if (k == 600)
		{
			g_pMainState->m_FindPt.findAstart(g_pHeroObj, m_Ghost.m_x * 20, g_pMainState->m_Map.m_pBmp->GetHeight() - m_Ghost.m_y * 20);
			++k;
			return true;
		}
		if (k == 601)
		{
			if (abs(g_pHeroObj->GetX() - m_Ghost.m_x * 20) < 81 && abs(g_pHeroObj->GetY() - (g_pMainState->m_Map.m_pBmp->GetHeight() - m_Ghost.m_y * 20)) < 81)
			{
				++k;
			}
			else if (g_pHeroObj->m_AstartPathIndex == -2)
			{
				k = 600;
			}
			return true;
		}
		if (k >= 602 && k < 900)
		{
			++k;
			return true;
		}
		if (k == 900)
		{
			Process(1);
			++k;
			return true;
		}
	}
		break;
	default:
		break;
	}
	return false;
}

std::string cTaskZhuaGui::AutoMakeName()
{
	Init();
	string str;
	str = m_Firstname[rand() % m_Firstname.size()];
	str += m_Secondname[rand() % m_Secondname.size()];
	str += m_Thirdname[rand() % m_Secondname.size()];
	str += "王";
	return str;
}

bool cTaskZhuaGui::ReadyToFight(sNpc& npc)
{
// 	int ournum = g_pMainState->GetPCFightNum();
// 	if (ournum < 2)
// 	{
// 		g_pMainState->m_Dialog.Reset();
// 		g_pMainState->m_Dialog.SetObj(npc.m_name);
// 		g_pMainState->m_Dialog.SetString("一个人就别来送死了");
// 		g_pMainState->m_Dialog.OnOff(true);
// 		return false;//最少3个人
// 	}
	int enemynum = g_pMainState->AtutoGetEnemyNum(5, 8); // rand() % (m_HuanShu / 2 + 1) + ournum;//计算敌人的数量
	int Averagelevel = g_pMainState->getAvgLv();
	//设置主怪  18野鬼  26僵尸  27 牛头  28 马面 10 骷髅怪

	int mp;
	switch (npc.m_modeid)
	{
	case e幽灵: // 攻击不高且双不抗，血量中等，但是物理躲避超高
		mp = cct::getMenpai(eMP_封系);
		break;
	case e夜罗刹:// 灵力高法伤高，物理攻击低
		mp = cct::getMenpai(eMP_法系);
		break;
	case e炎魔神:// 双抗，但是怕固定伤害，伤害不高血量极少，辅助门派居多
		mp = cct::getMenpai(eMP_辅助);
		break;
	case e吸血鬼:// 双不抗，有高鬼魂，血厚攻击不高，地府门派居多，会阎罗令和尸腐毒
		mp = cct::getMenpai(eMP_阴曹地府);
		break;
	case e鬼将: // 双不抗，血量不多但是物理输出超高
		mp = cct::getMenpai(eMP_物理);
		break;
	}
	sAddPoint ap = g_pMainState->getAddpointFromMp(mp);
	if (npc.m_modeid == e炎魔神)
	{
		ap.agi += ap.dex;
		ap.dex = 0;
	}
	auto pPetdata = g_pMainState->AddEnemy(npc.m_modeid, g_pMainState->getMaxLv(), (eMengPai)mp, npc.m_name, &ap);
	int per = pPetdata->HPMax.GetPercent();
	pPetdata->HPMax.SetDataAddPercent(per * 3 / 2);
//	cPropertyData* pPetdata = g_pMainState->m_FightWorkList[id0].m_pObj->getPropertyData();

// 	sZiZhi zizhi;
// 	zizhi = g_pMainState->m_PetDataManager.GetPetData(npc.m_modeid)->m_ZiZhi;
// 	cObj* pTarget = g_pMainState->m_FightWorkList[10].m_pObj;
// 	g_pMainState->m_FightWorkList[10].isExist = true;
// //	pTarget->ResetIndex();
// 
// 	//	sAddPoint addpoint;
// 	eMengPai e = (eMengPai)(rand() % 12);
// // 	pTarget->AutoPCData(npc.m_name, 0, 0, 0, e, 0, npc.m_modeid, 50 + m_HuanShu * 5);
// // 	//	g_pMainState->FollowLv(10, Averagelevel);
// 	pTarget->AutoData(0, 0, npc.m_modeid, npc.m_name);
//  	cPropertyData* pPetdata;
//  	pTarget->GetPropertyData(pPetdata);
// 	pPetdata->m_AddPoint = g_pMainState->m_ZhuXian.getAddPointFromMenpai(e);
// 	((cCharacter*)pTarget->m_pIndex)->m_PcData.FollowlvAddPoint(Averagelevel + 5, true, true, false);
	switch (npc.m_modeid)
	{
	case e幽灵: // 攻击不高且双不抗，血量中等，但是物理躲避超高
		pPetdata->_isWeakSeal = false;
// 		pPetdata->Pierce刺穿.d2 -= 60;
// 		pPetdata->Pierce刺穿OfMagic.d2 -= 60;
//		pPetdata->HitRate.d2 += 50;
		pPetdata->Evade.AddDataAddPercent(800);
//		pPetdata->HPMax.AddDataAddPercent(2000);
		pPetdata->m_XiuLian.GetMag() = cct::getCurrMaxXiulianLv(pPetdata->m_Lv);
		pPetdata->applyXL();
		break;
	case e夜罗刹:// 灵力高法伤高，物理攻击低
// 		pPetdata->Pierce刺穿.d2 -= 99;
// 		pPetdata->DmgPercentOfMagic.d2 += 99;
 		pPetdata->DmgPercentOfMagic.d1 += 128;
		pPetdata->DmgPercentOfMagic.d2 += 64;
		pPetdata->Pierce刺穿OfMagic.d1 += 20;
		pPetdata->Pierce刺穿OfMagic.d2 += 64;
// 		pPetdata->HPMax.AddDataAddPercent(2000);
		break;
	case e炎魔神:// 双抗，但是怕固定伤害，伤害不高血量极少，辅助门派居多
		pPetdata->DmgPercent.d2 += 99;
		pPetdata->Pierce刺穿.d2 += 99;
		pPetdata->DmgPercentOfMagic.d2 += 99;
		pPetdata->Pierce刺穿OfMagic.d2 += 99;
		pPetdata->DmgPercentOfFix.d2 -= 32;
		pPetdata->HPMax.SetDataAddPercent(per * 2 / 3);
		break;
	case e吸血鬼:// 双不抗，有高鬼魂，血厚攻击不高，地府门派居多，会阎罗令和尸腐毒
//		pPetdata->Pierce刺穿.d2 -= 80;
//		pPetdata->Pierce刺穿OfMagic.d2 -= 99;
//		pPetdata->HPMax.AddDataAddPercent();
		pPetdata->Ghost.d1 += 5;
		break;
	case e鬼将: // 双不抗，血量不多但是物理输出超高
		pPetdata->DmgPercent.d1 += 128;
		pPetdata->Pierce刺穿.d1 += 20;
		break;
	}
// 	switch (npc.m_modeid)
// 	{
// 	case 26://血鬼
// 		pPetdata->Pierce刺穿.d2 -= 99;
// 		pPetdata->Pierce刺穿OfMagic.d2 -= 99;
// 		pPetdata->HPMax.AddDataAddPercent(5000);
// 		break;
// 	case 28://马面
// 		pPetdata->Pierce刺穿.d2 -= 99;
// 		pPetdata->DmgPercentOfMagic.d2 += 99;
// 		pPetdata->HPMax.AddDataAddPercent(3500);
// 		break;
// 	case 10://敏鬼
// 		pPetdata->Pierce刺穿.d2 -= 60;
// 		pPetdata->Pierce刺穿OfMagic.d2 -= 60;
// 		pPetdata->HitRate.d2 += 80;
// 		pPetdata->HPMax.AddDataAddPercent(2000);
// 		break;
// 	case 27://牛头
// 		pPetdata->Pierce刺穿OfMagic.d2 -= 99;
// 		pPetdata->DmgPercent.d2 += 119;
// 		pPetdata->HPMax.AddDataAddPercent(2000);
// 		break;
// 	default: //野鬼
// 		pPetdata->DmgPercent.d2 += 119;
// 		pPetdata->DmgPercentOfMagic.d2 += 99;
// 		pPetdata->HPMax.AddDataAddPercent(500);
// 		break;
// 	}
//	pPetdata->MPMax.AddDataAddPercent(5);
	pPetdata->FillHpMp();
// 	int xl = cct::getCurrMaxXiulianLv(pPetdata->m_Lv);
// 	pPetdata->m_XiuLian.Set(xl, 0, xl, 0);
// 	pPetdata->applyXL();
//	((cPcData*)pPetdata)->m_XiuLian.Set(Averagelevel / 5, 0, Averagelevel / 5, 0);
//	enemynum -= 1;

	
	string enemyname;
	int modeid;
//	sAddPoint addpoint;
	//	addpoint.Set(5, 0, 0, 0, 0);

	for (int i = 1; i < enemynum; i++)
	{
		modeid = cct::getPetModel(55, 135);
		enemyname = g_pMainState->m_PetDataManager.GetPetData(modeid)->m_Name;
		enemyname += "恶鬼";
//		int id = g_pMainState->AddPCPetEnemy((ePetID)modeid, Averagelevel, &addpoint, eMP_随机, enemyname);
		/*int id*/auto pPetdata2 = i < 5 ? (cPetData*)g_pMainState->AddEnemy(modeid, Averagelevel, eMP_随机, enemyname) : g_pMainState->AddEnemy(modeid, Averagelevel, enemyname);
//		cPropertyData* pPetdata2 = g_pMainState->m_FightWorkList[id].m_pObj->getPropertyData();
// 		pPetdata->m_AddPoint = g_pMainState->m_ZhuXian.getAddPointFromMenpai(e);
// 		((cCharacter*)g_pMainState->m_FightWorkList[id].m_pObj->m_pIndex)->m_PcData.FollowlvAddPoint(Averagelevel, true, true, false);
//		pPetdata2->HPMax.AddDataAddPercent(2000);
//		pPetdata2->FillHpMp();
		int xl = cct::getCurrMaxXiulianLv(pPetdata2->m_Lv) / 3;
 		pPetdata2->m_XiuLian.Set(xl, 0, xl, 0);
 		pPetdata2->applyXL();
	}
	g_StateType = STATE_FIGHT;
	SetMusic();
	return true;
}

void cTaskZhuaGui::AutoGetGost(sNpc& npc, string mapname)
{
	static vector<int> ms = { e幽灵, e夜罗刹, e炎魔神, e吸血鬼, e鬼将 };
	int modeid = ms[rand() % ms.size()];
// 	switch (rand() % 5)
// 	{
// 	case 0:modeid = 26; break;//血鬼
// 	case 1:modeid = 28; break;//马面
// 	case 2:modeid = 10; break;//敏鬼
// 	case 3:modeid = 27; break;//牛头
// 	default: modeid = 18; break;//野鬼
// 	}
	int x, y;
	g_pMainState->m_Map.AutoGetPos(x, y, mapname);
	npc.Set(AutoMakeName(), mapname, modeid, x, y, npc.m_JinJieID.GetBJinJie());
}

void cTaskZhuaGui::GetErrPos(sNpc npc, int& xout, int& yout)
{
	int direction = rand() % 9;
	if (direction == 5)direction += rand() % 4;
	//根据名字决定位置
	xout = npc.m_x;
	yout = npc.m_y;
	xout = (xout + 5) / 10 * 10;
	yout = (yout + 5) / 10 * 10;
	return;
	int offset2 = 40;
	int offset = 40;
	switch (direction)
	{
	case 0:
		yout = npc.m_y - rand() % offset2;
		break;
	case 1:
		xout = npc.m_x + rand() % (offset);
		yout = npc.m_y - rand() % offset2;
		break;
	case 2:
		xout = npc.m_x + rand() % offset2;
		yout = npc.m_y - rand() % (offset);
		break;
	case 3:
		xout = npc.m_x + rand() % offset2;
		break;
	case 4:
		xout = npc.m_x + rand() % offset2;
		yout = npc.m_y + rand() % (offset);
		break;
	case 5:
		xout = npc.m_x + rand() % (offset);
		yout = npc.m_y + rand() % offset2;
		break;
	case 6:
		yout = npc.m_y + rand() % offset2;
		break;
	case 7:
		xout = npc.m_x - rand() % (offset);
		yout = npc.m_y + rand() % offset2;
		break;
	case 8:
		xout = npc.m_x - rand() % offset2;
		yout = npc.m_y + rand() % (offset);
		break;
	case 9:
		xout = npc.m_x - rand() % offset2;
		break;
	case 10:
		xout = npc.m_x - rand() % offset2;
		yout = npc.m_y - rand() % (offset);
		break;
	case 11:
		xout = npc.m_x - rand() % (offset);
		yout = npc.m_y - rand() % offset2;
		break;
	default:
		ERRBOX;
		break;
	}
	if (xout < 0)xout = 0;
	if (yout < 0)yout = 0;
	if ((xout - npc.m_x) > 40)xout = npc.m_x + 40;
	if ((npc.m_x - xout) > 40)xout = npc.m_x - 40;
	if ((xout - npc.m_y) > 40)yout = npc.m_y + 40;
	if ((npc.m_y - xout) > 40)yout = npc.m_y - 40;
}

void cTaskZhuaGui::Save(ofstream& File)
{
	File << m_HuanShu << " ";
	//是否有抓鬼任务
	m_Ghost.Save(File);
	//是否有剧情
	if (m_pTask)
	{
		File << 1 << " ";
		File << m_pTask->m_type << " ";
		File << m_RetNum << " ";
		File << m_RetStage << " ";
	}
	else File << 0 << " ";
}

void cTaskZhuaGui::Load(ifstream& File)
{
	File >> m_HuanShu;
	m_Ghost.Load(File);
	int k;
	File >> k;
	if (k)
	{
		File >> k;
		m_pTask = g_pMainState->FindTaskByID(k);
		File >> m_RetNum;
		File >> m_RetStage;
	}
}

void cTaskZhuaGui::SetTrigger(cTaskFather* p, int num, int stage)
{
	m_pTask = p;
	m_RetNum = num;
	m_RetStage = stage;
}

void cTaskZhuaGui::UpdateZGJob(bool bTrue)
{
	ostringstream oss;
	//因为要让字体的颜色不同,只能再来一遍
	int falsex, falsey;
	if (bTrue)
	{
		falsex = m_Ghost.m_x;
		falsey = m_Ghost.m_y;
	}
	else
	{
		GetErrPos(m_Ghost, falsex, falsey);
	}
	oss << "#R";
	oss << m_Ghost.m_name;
	oss << "\n";
	oss << m_Ghost.m_mapname;
	oss << "#R #B";
	oss << falsex;
	oss << " ";
	oss << falsey;
	oss << "#B";


	sJob job;
	job.m_Context = oss.str();
	job.m_Title = "钟馗捉鬼";
	job.m_Time = 40;
	job.m_pTask = this;
	g_pMainState->m_Job.AddaJob(job, m_HuanShu);
}

