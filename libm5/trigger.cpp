#include "global.h"



BOOL cTaskBaotu::Process(int stage)
{
	if (!m_bInit)Init();
	switch (stage)
	{
	case 0:
		
		{	
			g_pMainState->m_Dialog.Reset();
			g_pMainState->m_Dialog.SetObj("店小二");
			 m_Robber.m_name = AutoMakeName();
			m_Robber.m_mapname = m_MapNameList[rand() % m_MapNameList.size()];
			m_Robber.m_modeid = 5;
			g_pMainState->m_Map.AutoGetPos(m_Robber.m_x, m_Robber.m_y, m_Robber.m_mapname);
			ostringstream oss;
			oss.str("");
			oss << "近来传闻大盗#R强盗";
			oss << m_Robber.m_name;
			oss << "#R重现江湖并犯下不少案子,只是从未见他销赃,据说他都把宝贝藏在#R";
			oss << m_Robber.m_mapname;
			oss << "#R#Y";
			oss << m_Robber.m_x;
			oss << " ";
			oss << m_Robber.m_y;
			oss << "#Y 了,不知道是不是真的,要是能找到就发财了";
			string context = oss.str();
			g_pMainState->m_Dialog.SetString(context);
			g_pMainState->m_Dialog.OnOff(TRUE);
			cObj* pObj = g_pMainState->FindObjByName("店小二");
			pObj->m_AutoRun = FALSE;

			//因为要让字体的颜色不同,只能再来一遍
			oss.str("");
			oss << "近来传闻大盗#R强盗";
			oss << m_Robber.m_name;
			oss << "#R重现江湖并犯下不少案子,只是从未见他销赃,据说他都把宝贝藏在#R";
			oss << m_Robber.m_mapname;
			oss << "#R#B";
			oss << m_Robber.m_x;
			oss << " ";
			oss << m_Robber.m_y;
			oss << "#B 了,不知道是不是真的,要是能找到就发财了";
			context = oss.str();
			sJob job;
			job.m_Context = context;
			job.m_Title = "打宝图";
			job.m_Time = 40;
			job.m_pTask = this;
			g_pMainState->m_Job.AddaJob(job);
			g_pMainState->m_TriggerObjMap.AddTask(this, 1,m_Robber);
			return TRUE;
		}
		break;
	case 1:
	
		{
			
			sAddPoint point;
			point.Set(0, 0, 0, 5, 0);
			int id = g_pMainState->AddPetEnemy(m_Robber.m_name, m_Robber.m_modeid, g_pCharacter->m_PCData.m_LV, &point, 80);
			cPetData* pPetdata;
			g_pMainState->m_FightList[id].m_pData->GetDateP(pPetdata);
			pPetdata->m_Controler.Set();
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(3);
			return TRUE;
		}
		break;
	case 3:
		
		{
			if (0==rand()%10)
			{

				string nowname = m_Robber.m_name;
				m_Robber.m_name = AutoMakeName();

				m_Robber.m_mapname = m_MapNameList[rand() % m_MapNameList.size()];
				g_pMainState->m_Map.AutoGetPos(m_Robber.m_x, m_Robber.m_y, m_Robber.m_mapname);
				ostringstream oss;
				oss << "别打了,我只是个小喽啰,我们老大在#R";
				oss << m_Robber.m_mapname;
				oss << "#R " << "#R" << m_Robber.m_x << " " << m_Robber.m_y << "#R";
				g_pMainState->FindObjByName(nowname)->Talk(oss.str());
				g_pMainState->m_Dialog.m_pObj = 0;
				g_pMainState->m_Map.RemoveNpc(nowname);
				m_Robber.m_modeid = 8;
				g_pMainState->m_TriggerObjMap.AddTask(this, 4, m_Robber);

				sJob job;
				job.m_Context = oss.str();
				job.m_Title = "打宝图";
				job.m_Time = 40;
				job.m_pTask = this;
				g_pMainState->m_Job.AddaJob(job);
			}
			else
			{
				g_pMainState->m_Map.RemoveNpc(m_Robber.m_name);
				g_pMainState->m_TriggerObjMap.ReMove(this);
				g_pMainState->m_Job.ReMoveJob(this);
				if (1 || rand() % 100 < 80)
				{

					//得宝图
					sItem2 item;
					item.Set(28, 6);
					item.m_Num = 1;
					g_pMainState->m_ItemManage.AutoItemProperty(&item);
					g_pMainState->SetJiangLiItem(item, 1);
				}
				
				
			}
			sFightList& lis = g_pMainState->m_FightList[g_pMainState->m_HeroID + 5];
			INT64 petexp = 0;
			int money = g_pCharacter->m_PCData.m_LV * 10 + 2000 + rand() % 1000;
			if (lis.isLive&&!lis.CheckDie())
			{
				cPetData* petdata;
				lis.m_pData->GetDateP(petdata);
				petexp = GetNormalFightExp(g_pCharacter->m_PCData.m_LV, g_pCharacter->m_PCData.m_LV);
			}
			SetJiangLi2(0, money, 0, (int)petexp);
				return TRUE;
		}
		break;
	case 4:
	
		{
			cPetData* pPet;
			pPet= AddPCPetEnemyF(g_pCharacter->m_PCData.m_LV * 120, (ePetID)m_Robber.m_modeid, g_pCharacter->m_PCData.m_LV, eMP_随机, m_Robber.m_name);
			pPet->m_Combo.d1 += 50;
			for (int i = 0; i < 5; i++)
			{
				pPet=AddPCPetEnemyF(g_pCharacter->m_PCData.m_LV * 80, e强盗, g_pCharacter->m_PCData.m_LV);
				pPet->m_HitRate.d2 += 20;
			}
			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(5);
			return TRUE;
		}
		break;
	case 5:
		
		{
			g_pMainState->m_Map.RemoveNpc(m_Robber.m_name);
			g_pMainState->m_TriggerObjMap.ReMove(this);
			g_pMainState->m_Job.ReMoveJob(this);
			//得五宝
			SetJiangLiItem(6+rand()%5,27);
			SetJiangLi(3, TRUE, 100, 0, 100, 200);
		}
		break;
	case 6:
	{
			  int lv = g_pCharacter->m_PCData.m_LV;
			  string name="远古";
			  ePetID petid=(ePetID)(rand()%40);
			  name += g_pMainState->m_PetDataManager.GetPetData(petid)->m_Name;
			  int enemynum = g_pMainState->AtutoGetEnemyNum()-1;
			  cPetData* pPet= AddPCPetEnemyF(lv * 80, petid, -1, eMP_随机, name);
			  pPet->AddSkill(ePS_高级反震);
			  for (int i = 0; i < enemynum; i++)
			  {
				  AddPCPetEnemyF(lv * 40, (ePetID)(rand()%40));
			  }
			  AddTriggerFightSuccess(7);
	}
		break;
	case 7:
	{
			  SetJiangLi(2, 1, 50, 0, 100, 200);
			  if (0 == rand() % 10)
			  {
				  SetJiangLiItem(20, 24);
			  }
	}
	default:
		break;
	}
	return FALSE;
}

void cTaskBaotu::Init()
{
	if (m_bInit)return;
	m_bInit = TRUE;
	//读取名字列表
	ifstream File;
	ostringstream oss;
#if ccc_m5
	oss << g_strMediaPath << "任务//打宝图//百家姓.txt";
#else
	oss << g_strMediaPath << "强盗名字.txt";
#endif
	File.open(oss.str());
	int num;
	File >> num;
	string data;
	for (int i = 0; i < num; i++)
	{
		File >> data;
		m_Firstname.push_back(data);
	}
	File >> num;
	for (int i = 0; i < num; i++)
	{
		File >> data;
		m_Secondname.push_back(data);
	}
	File.close();
	oss.str("");
#if ccc_m5
	oss << g_strMediaPath << "任务//打宝图//地点.txt";
#else
	oss << g_strMediaPath << "强盗地点.txt";
#endif
	File.open(oss.str());
	File >> num;
	string str;
	for (int i = 0; i < num; i++)
	{
		File >> str;
		m_MapNameList.push_back(str);
	}
	File.close();
	
	m_type = 30;
}

std::string cTaskBaotu::AutoMakeName()
{
	string str;
	str= m_Firstname[rand() % m_Firstname.size()];
	str+= m_Secondname[rand() % m_Secondname.size()];
	return str;
}



BOOL cTaskNormal::Process(int stage)
{
	cPetData* pUserData;
	cObj* pUser = g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData;
	pUser->GetDateP(pUserData);
	switch (stage)
	{
	case -1:break;
	case 1: //暗雷遇怪
	case 3://明雷遇怪
		g_pMainState->ReadyToFight();
		AddTriggerFightSuccess(4);
		break;
	case 4://奖励
		{
			if (m_pNpc)
			{
				g_pMainState->m_Map.RemoveNpc(m_pNpc,TRUE);
				m_pNpc = 0;
			}
			//计算并显示奖励
			int fightnum = g_pMainState->GetLiveNum(0,5);
			INT64 ExpSuccess = GetNormalFightExp(pUserData->m_LV, g_pMainState->m_Map.m_EnemyLv, fightnum);
			INT64 ExpSuccessBB = GetNormalFightExp(g_pMainState->m_Map.m_EnemyLv, g_pMainState->m_Map.m_EnemyLv, fightnum);
			int money = g_pMainState->m_Map.m_EnemyLv*(fightnum+3)*3;
			if (g_pCharacter->m_PCData.m_FightPetID == -1)ExpSuccessBB = 0;
			g_pMainState->SetJiangLi(ExpSuccess, ExpSuccessBB, money,0,TRUE);
			//m_WeaponRate几率得到装备
			if (rand() % 100 < g_pMainState->m_Map.m_WeaponRate)
			{
				int type = rand() % 22;
				if (type == 13)type = rand() % 13;
				int itemid = g_pMainState->m_ItemManage.GetIDByLv(type, g_pMainState->m_Map.m_Weaponlv*10);
				sItem2 item;
				item.m_Num = 1;
				item.Set(type, itemid);
				g_pMainState->SetJiangLiItem(item);
			}
			return TRUE;
		}
		break;
	case 5://门派传送人
		if (!g_pMainState->m_Dialog.m_retSelect)
		{
			cMyMap& map = g_pMainState->m_Map;
			switch (g_pCharacter->m_PCData.m_MengPaiID)
			{
			case 0:map.LoadMap(151, 10, "大唐官府"); break;
			case 1:map.LoadMap(88, 49, "化生寺"); break;
			case 2:map.LoadMap(20, 98, "女儿村"); break;
			case 3:map.LoadMap(104, 121, "方寸山"); break;
			case 4:map.LoadMap(103, 16, "狮驼岭"); break;
			case 5:map.LoadMap(73, 60, "魔王寨"); break;
			case 6:map.LoadMap(175, 113, "盘丝岭"); break;
			case 7:map.LoadMap(37, 60, "阴曹地府"); break;
			case 8:map.LoadMap(79, 40, "龙宫"); break;
			case 9:map.LoadMap(28, 18, "五庄观"); break;
			case 10:map.LoadMap(16, 55, "普陀山"); break;
			case 11:map.LoadMap(159, 55, "天宫"); break;
			}
		}
		break;
	case 6:
		
		{
			if (g_pMainState->m_Dialog.m_retSelect == 5)
				return TRUE;
			cMyMap& map = g_pMainState->m_Map;
			switch (g_pCharacter->m_PCData.m_race)
			{
			case 4:
			case 5:
			case 6://人				
				switch (g_pMainState->m_Dialog.m_retSelect)
				{
				case 0:map.LoadMap(151, 10, "大唐官府"); break;
				case 1:map.LoadMap(88, 49, "化生寺"); break;
				case 2:map.LoadMap(20, 98, "女儿村"); break;
				case 3:map.LoadMap(104, 121, "方寸山"); break;
				}
				break;
			case 1:
			case 3://妖
				switch (g_pMainState->m_Dialog.m_retSelect)
				{
				case 0:map.LoadMap(103, 16, "狮驼岭"); break;
				case 1:map.LoadMap(73, 60, "魔王寨"); break;
				case 2:map.LoadMap(175, 113, "盘丝岭"); break;
				case 3:map.LoadMap(37, 60, "阴曹地府"); break;
				}
				break;
			case 0:
			case 2://仙	
				switch (g_pMainState->m_Dialog.m_retSelect)
				{
				case 0:map.LoadMap(79, 40, "龙宫"); break;
				case 1:map.LoadMap(28, 18, "五庄观"); break;
				case 2:map.LoadMap(16, 55, "普陀山"); break;
				case 3:map.LoadMap(159, 55, "天宫"); break;
				}
				break;
			}
		}
		break;
	case 7:
		if (g_pMainState->m_Dialog.m_retSelect == 0)
		{
			g_pMainState->m_Map.LoadMap(476, 30, "长安城");
			return TRUE;
		}
		break;
	case 8://管家  // 休息
		g_pCharacter->m_PCData.FillHPMP();
		break;
	case 118:
		{

			g_pMainState->m_FangWu.GetBB();
		}
		break;
	case 119:
		
		{
			g_pMainState->m_FangWu.Move(g_pHeroObj->GetX(), g_pHeroObj->GetY(), g_pMainState->m_Dialog.m_pObj);
		}
		break;
	case 120:
		g_pMainState->m_FangWu.RemovePreJiaJu();
		break;
	case 9://镇宅兽
		
		{
			cObj* pObj = g_pMainState->m_pNowSelect;
			g_pMainState->m_Dialog.Reset();
			g_pMainState->m_Dialog.SetObj(pObj);
			g_pMainState->m_Dialog.SetString("主人,请问有什么吩咐?", "休息", "到这里来", "放生(费用100万)");
			g_pMainState->m_Dialog.SetTrigger(this,10, 8,10,10,10);
			g_pMainState->m_Dialog.OnOff(TRUE);
		}
		break;
	case 10:
		switch (g_pMainState->m_Dialog.m_retSelect)
		{
		case 0:
			g_pCharacter->m_PCData.FillHPMP();
			break;
		case 1:
				g_pMainState->m_FangWu.Move(g_pHeroObj->GetX(), g_pHeroObj->GetY(), g_pMainState->m_Dialog.m_pObj);
			break;
		case 2:
			
			{
				g_pCharacter->m_PCData.m_Money[0] -= 100000;
				g_pMainState->m_FangWu.RemoveBB(g_pMainState->m_Dialog.m_pObj);
				cObj* pObj = g_pMainState->m_Dialog.m_pObj;
				g_pMainState->m_Dialog.m_pObj->Talk("放生了镇宅兽");
				g_pMainState->m_Map.RemoveNpc(pObj->GetX(), pObj->GetY(),"",1);
			}
			break;
		}
		break;
	case 12://南极仙翁
	
		{
			int lv = g_pMainState->m_GlobalButton[3];
			if (lv > 4){ g_pMainState->m_pNowSelect->Talk("我已经没什么可以帮你的了"); return TRUE; }
			ostringstream oss;
			oss << "当前仙灵店铺等级为";
			oss << lv;
			oss << "到下一个级别需要";
			oss << lv+1;
			oss << "百万两,需要吗?";
			g_pMainState->m_TriggerDialog.AddSelect(this, oss.str(), g_pMainState->m_pNowSelect->m_TrueName.GetString(), -1, "是", 13, "否", -1);
		}
		break;
	case 13:
		
		{
			int moneyneed = (g_pMainState->m_GlobalButton[3]+1) * 1000000;
			if (g_pCharacter->m_PCData.AddMoney(0, -moneyneed,0,FALSE))
			{
				g_pMainState->m_GlobalButton[3] += 1;
				ostringstream oss;
				oss << "你的仙灵店铺达到了" << g_pMainState->m_GlobalButton[3]<<"级!#88";

				g_pMainState->m_Dialog.TalkObj(oss.str());
			}
			else
			{
				g_pMainState->m_Dialog.TalkObj("你的钱不够#3");
			}
		}
		break;
	case 14:
		
		{
			if (!g_pMainState->m_ItemManage.m_pNowItem)return FALSE;
			sItem2* pi = g_pMainState->m_ItemManage.m_pNowItem;
			pi->m_Property[0] -= 1;
			if (0 == pi->m_Property[0])pi->m_Num = 0;
			g_pMainState->m_Map.LoadMap(pi->m_Property[1], pi->m_Property[2], pi->m_strProperty.c_str(), 1);
		}
		break;
	case 15:
		
		{
			if (!g_pMainState->m_ItemManage.m_pNowItem)return FALSE;
			sItem2* pi = g_pMainState->m_ItemManage.m_pNowItem;
			pi->m_Property[1]=g_pMainState->m_InterfaceDoor.m_HeroX;
			pi->m_Property[2]=g_pMainState->m_InterfaceDoor.m_HeroY;
			pi->m_strProperty = g_pMainState->m_Map.m_MapName;
			g_pMainState->m_Tags.Add("在当前位置定了旗子");
		}
		break;
	default:
		break;
	}
	return FALSE;
}

BOOL cTrigger::AddTask(cTaskFather* ptask, int stage)
{
	sTaskFather task;
	task.m_pTask = ptask;
	task.m_Stage = stage;
	int num = m_TaskList.size();
	for (int i = 0; i < num; i++)
	{
		if (m_TaskList[i].m_pTask->m_type == ptask->m_type)
		{
			m_TaskList[i].m_Stage = stage;
			return FALSE;
		}
	}
	m_TaskList.push_back(task);
	return TRUE;
}

void cTrigger::ReMove(cTaskFather* pTask)
{
	return ReMove(pTask->m_type);
}

void cTrigger::ReMove(int id)
{
	int num = m_TaskList.size();
	for (int i = 0; i < num; i++)
	{
		if (m_TaskList[i].m_pTask->m_type == id)
		{
			m_TaskList.erase(m_TaskList.begin() + i);
		}
	}
}

BOOL cTrigger::Process()
{
	int num = m_TaskList.size();
	if (!num)return FALSE;
	BOOL b=FALSE;
	for (int i = 0; i < num; i++)
	{
		if (m_TaskList[i].m_pTask->Process(m_TaskList[i].m_Stage))
			b = TRUE;
	}
	return b;
}

BOOL cTrigger::ProcessReMove()
{
	int num = m_TaskList.size();
	if (!num)return FALSE;
	cTaskFather* ptask = m_TaskList[0].m_pTask;
	int stage = m_TaskList[0].m_Stage;
	Clear();

	auto z = &g_pMainState->m_ZhuXian;
	auto& c = g_pMainState->_challengeChapterStorage;
	if (c >= 0 && ptask == z)
	{
		z->SetChapter(c);
		auto ap = z->m_AddPoint;
		z->Init();
		z->m_AddPoint = ap;
		c = -1;
		return FALSE;
	}
	ptask->Process(stage);
	return TRUE;
}

void cTaskZhuaGui::Init()
{
	if (m_bInit)return;
	m_bInit = TRUE;
	//读取名字列表
	ifstream File;
	ostringstream oss;
#if ccc_m5
	oss << g_strMediaPath << "任务//抓鬼//百家姓.txt";
#else
	oss << g_strMediaPath << "抓鬼名字.txt";
#endif
	File.open(oss.str());
	if (!File)ERRBOX;
	int num;
	File >> num;
	string data;
	for (int i = 0; i < num; i++)
	{
		File >> data;
		m_Firstname.push_back(data);
	}
	File >> num;
	for (int i = 0; i < num; i++)
	{
		File >> data;
		m_Secondname.push_back(data);
	}
	File >> num;
	for (int i = 0; i < num; i++)
	{
		File >> data;
		m_Thirdname.push_back(data);
	}
	File.close();
	oss.str("");
#if ccc_m5
	oss << g_strMediaPath << "任务//抓鬼//地点.txt";
#else
	oss << g_strMediaPath << "抓鬼地点.txt";
#endif
	File.open(oss.str());
	if (!File)ERRBOX;
	File >> num;
	string str;
	for (int i = 0; i < num; i++)
	{
		File >> str;
		m_MapNameList.push_back(str);
	}
	
	m_type = 40;
}

BOOL cTaskZhuaGui::Process(int stage)
{
	CheckInit();
	switch (stage)
	{
	case 0:
		
		{
			cObj* pObj = g_pMainState->FindObjByName("钟馗");
			if (g_pMainState->m_Job.CheckHaveJob(m_type))
			{
				pObj->Talk("你已经有任务了");
				return TRUE;
			}
			
			int ournum = g_pMainState->GetPCFightNum();
			if (ournum < 3)
			{
				pObj->Talk("这个任务很危险,你还是再多找点人吧(至少3人组队");
				return TRUE;//最少3个人
			}

			AutoGetGost(m_Ghost, m_MapNameList[rand() % m_MapNameList.size()]);
			//根据名字决定位置
			int  falsex;
			int  falsey;
			GetErrPos(m_Ghost, falsex, falsey);
			ostringstream oss;
			oss.str("");
			oss << "有一只#R";
			oss << m_Ghost.m_name;
			oss << "#R逃出了地府,据我估计,他应该在#R";
			oss << m_Ghost.m_mapname;
			oss << "#R#Y";
			oss << falsex;
			oss << " ";
			oss << falsey;
			oss << "#Y 附近,请少侠去抓它回来";
			string context = oss.str();
			pObj->Talk(oss.str());
			g_pMainState->m_Dialog.m_pObj = 0;
			pObj->m_AutoRun = FALSE;
			UpdateZGJob();
			
		
			m_HuanShu += 1;

			g_pMainState->m_TriggerObjMap.AddTask(this, 1,m_Ghost);
			return TRUE;
		}
		break;
	case 1:
		
		{
			ReadyToFight(m_Ghost);
			AddTriggerFightSuccess(3);
			return TRUE;
		}
		break;
	case 3:
		
		{
			BOOL btrigger=FALSE;
			if (m_HuanShu == m_RetNum)btrigger = TRUE;
			m_Ghost.m_modeid = -1;
			m_Ghost.m_mapname = "";
			g_pMainState->m_Map.RemoveNpc(m_Ghost.m_name);
			g_pMainState->m_TriggerObjMap.ReMove(this);
			g_pMainState->m_Job.ReMoveJob(this);
			SetJiangLi(5, TRUE, 100, 0, 100, 100);
			//得装备
			if (m_HuanShu==10)
			{
				int itemtype = rand() % 22;
				int lv=-1;
				if (g_pCharacter->m_PCData.m_LV > 80)
				{
					switch (rand()%4)
					{
					case 0:
						lv = 80;
						break;
					case 1:
						lv = 70;
						break;
					case 2:
						lv = 60;
						break;
					default:
						break;
					}
				}
				else
				if (g_pCharacter->m_PCData.m_LV >60)
				{
					switch (rand() % 4)
					{
					case 0:
						lv = 60;
						break;
					case 1:
						lv = 50;
						break;
					}
				}
				else
				{
					switch (rand() % 4)
					{
					case 0:
						lv = 50;
						break;
					}
				}
				if (lv > -1)
				{
					int itemid= g_pMainState->m_ItemManage.GetIDByLv(itemtype,lv);
					sItem2 item;
					item.m_Num = 1;
					item.Set(itemtype, itemid);
					g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID,&item);
					ostringstream oss;
					oss << "你得到了";
					oss << item.m_pItemData->m_Name;
					g_pMainState->m_Tags.Add(oss.str());
				}
				m_HuanShu = 0;
			}
			if (btrigger)
			{
				cTaskFather* p = m_pTask;
				m_pTask = 0;
				m_RetNum = 100;
				p->Process(m_RetStage);
			}
			return TRUE;
		}
		break;
	default:
		break;
	}
	return FALSE;
}

std::string cTaskZhuaGui::AutoMakeName()
{
	Init();
	string str;
	str = m_Firstname[rand() % m_Firstname.size()];
	str += m_Secondname[rand() % m_Secondname.size()];
	str += m_Thirdname[rand() % m_Secondname.size()];
	return str;
}

BOOL cTaskZhuaGui::ReadyToFight(sNpc& npc)
{
	int ournum = g_pMainState->GetPCFightNum();
	if (ournum < 3)
	{
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetObj(npc.m_name);
		g_pMainState->m_Dialog.SetString("这么几个人就别来送死了(至少3人组队)");
		g_pMainState->m_Dialog.OnOff(TRUE);
		return FALSE;//最少3个人
	}
	int enemynum =  rand() % (m_HuanShu/2+1) + ournum;//计算敌人的数量
	if (enemynum > 10)enemynum = 10;
	int Averagelevel = g_pMainState->GetAverageLv();
	//设置主怪  18野鬼  26僵尸  27 牛头  28 马面 10 骷髅怪
	
	sZiZhi zizhi;
	zizhi = g_pMainState->m_PetDataManager.GetPetData(npc.m_modeid)->m_ZiZhi;
	cObj* pTarget = g_pMainState->m_FightList[10].m_pData;
	g_pMainState->m_FightList[10].isLive = TRUE;
	pTarget->ResetIndex();
#if ccc_m5
	sAddPoint addpoint;
	pTarget->AutoPCData(npc.m_name, 0, 0, 0, (eMengPai)(rand() % 12), 0, npc.m_modeid, 50 + m_HuanShu * 5);
	g_pMainState->FollowLv(10, Averagelevel);
	cPetData* pPetdata;
	pTarget->GetDateP(pPetdata);
	switch (npc.m_modeid)
	{
	case 26://血鬼
		pPetdata->m_HPMax.AddDataAddPercent(2000);
		break;
	case 28://马面
		pPetdata->m_DamageAddPercentMagic.d1 += 70;
		pPetdata->m_HPMax.AddDataAddPercent(1400);
		break;
	case 10://敏鬼
		pPetdata->m_HitRate.d2 += 50;
		pPetdata->m_HPMax.AddDataAddPercent(800);
		break;
	case 27://牛头
		pPetdata->m_DamagePercent.d2 += 70;
		pPetdata->m_HPMax.AddDataAddPercent(800);
		break;
	default: //野鬼
		pPetdata->m_DamagePercent.d2 += 70;
		pPetdata->m_DamageAddPercentMagic.d1 += 70;
		pPetdata->m_HPMax.AddDataAddPercent(600);
		break;
	}
	pPetdata->FillHPMP();
	enemynum -= 1;

	sPetData* pPetdata2;
	string enemyname;
	int modeid;
	addpoint.Set(5, 0, 0, 0, 0);
	for (int i = 0; i < enemynum; i++)
	{
		modeid = rand() % 34;
		pPetdata2 = g_pMainState->m_PetDataManager.GetPetData(modeid);
		enemyname = pPetdata2->m_Name;
		enemyname += "恶鬼";
		int id = g_pMainState->AddPCPetEnemy((ePetID)modeid, g_pCharacter->m_PCData.m_LV - 15, &addpoint, (eMengPai)(rand() % 12), enemyname);
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPetdata);
		pPetdata->FillHPMP();
	}
#else
	eMengPai e = (eMengPai)(rand() % 12);
	pTarget->AutoPCData(npc.m_name, 0, 0, 0, e, 0, npc.m_modeid, 50 + m_HuanShu * 5);
	cPetData* pPetdata;
	pTarget->GetDateP(pPetdata);
	pPetdata->m_AddPoint = g_pMainState->m_ZhuXian.getAddPointFromMenpai(e);
	((cCharacter*)pTarget->m_pIndex)->m_PCData.FollowlvAddPoint(Averagelevel + 5, true, true, false);
	switch (npc.m_modeid)
	{
	case 26://血鬼
		pPetdata->m_Pierce.d2 -= 90;
		pPetdata->m_PierceMagic.d2 -= 90;
		pPetdata->m_HPMax.AddDataAddPercent(5000);
		break;
	case 28://马面
		pPetdata->m_Pierce.d2 -= 80;
		pPetdata->m_DamageAddPercentMagic.d2 += 70;
		pPetdata->m_HPMax.AddDataAddPercent(3500);
		break;
	case 10://敏鬼
		pPetdata->m_Pierce.d2 -= 60;
		pPetdata->m_PierceMagic.d2 -= 60;
		pPetdata->m_HitRate.d2 += 80;
		pPetdata->m_HPMax.AddDataAddPercent(2000);
		break;
	case 27://牛头
		pPetdata->m_PierceMagic.d2 -= 80;
		pPetdata->m_DamagePercent.d2 += 70;
		pPetdata->m_HPMax.AddDataAddPercent(2000);
		break;
	default: //野鬼
		pPetdata->m_DamagePercent.d2 += 80;
		pPetdata->m_DamageAddPercentMagic.d2 += 80;
		pPetdata->m_HPMax.AddDataAddPercent(500);
		break;
	}
	pPetdata->FillHPMP();
	((cPCData*)pPetdata)->m_XiuLian.Set(Averagelevel / 5, 0, Averagelevel / 5, 0);
	enemynum -= 1;

	sPetData* pPetdata2;
	string enemyname;
	int modeid;
	sAddPoint addpoint;
	for (int i = 0; i < enemynum; i++)
	{
		modeid = rand() % 34;
		pPetdata2 = g_pMainState->m_PetDataManager.GetPetData(modeid);
		enemyname = pPetdata2->m_Name;
		enemyname += "恶鬼";
		e = (eMengPai)(rand() % 12);
		int id = g_pMainState->AddPCPetEnemy((ePetID)modeid, 0, &addpoint,e, enemyname);
		g_pMainState->m_FightList[id].m_pData->GetDateP(pPetdata);
		pPetdata->m_AddPoint = g_pMainState->m_ZhuXian.getAddPointFromMenpai(e);
		((cCharacter*)g_pMainState->m_FightList[id].m_pData->m_pIndex)->m_PCData.FollowlvAddPoint(Averagelevel, true, true, false);
		pPetdata->FillHPMP();
	}
#endif
	g_StateType = STATE_FIGHT;
	SetMusic();
	return TRUE;
}

void cTaskZhuaGui::AutoGetGost(sNpc& npc, string mapname)
{
	int modeid;
	switch (rand() % 5)
	{
	case 0:modeid = 26; break;//血鬼
	case 1:modeid = 28; break;//马面
	case 2:modeid = 10; break;//敏鬼
	case 3:modeid = 27; break;//牛头
	default: modeid = 18; break;//野鬼
	}
	int x, y;
	g_pMainState->m_Map.AutoGetPos(x, y, mapname);
	npc.Set(AutoMakeName(), mapname, modeid, x, y,npc.m_JinJieID.GetBJinJie());
}

void cTaskZhuaGui::GetErrPos(sNpc npc, int& xout, int& yout)
{
	int direction = rand() % 9;
	if (direction == 5)direction +=rand()%4;
	//根据名字决定位置
	xout = npc.m_x;
	yout = npc.m_y;
	int offset2 =  40;
	int offset =  40;
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
	if ((xout - npc.m_x)>40)xout = npc.m_x+40;
	if ((npc.m_x - xout)>40)xout = npc.m_x - 40;
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
		File << m_pTask->m_type<<" ";
		File << m_RetNum<<" ";
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
		File >> k ;
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

void cTaskZhuaGui::UpdateZGJob(BOOL bTrue)
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
	oss << "有一只#R";
	oss << m_Ghost.m_name;
	oss << "#R逃出了地府,据我估计,他应该在#R";
	oss << m_Ghost.m_mapname;
	oss << "#R#B";
	oss << falsex;
	oss << " ";
	oss << falsey;
	oss << "#B 附近,请少侠去抓它回来";


	sJob job;
	job.m_Context = oss.str();
	job.m_Title = "抓鬼";
	job.m_Time = 40;
	job.m_pTask = this;
	g_pMainState->m_Job.AddaJob(job, m_HuanShu);
}


BOOL cTaskBangPai::Process(int stage)
{
	return TRUE;
}


BOOL cTaskSM::Process(int stage)
{
	switch (stage)
	{
	//case 21://示威
	//	
	//	{
	//		if (g_pMainState->m_Map.m_MapName == m_Npc.m_mapname)
	//		{
	//			g_pMainState->m_Map.RemoveNpc(m_Npc.m_x, m_Npc.m_y, m_Npc.m_name, 1);
	//		}
	//		Process(20);
	//	}
	//	break;
	//case 1000://任务消失
	//	/*g_pMainState->m_TriggerObjMap.ReMove(this);
	//	g_pMainState->m_Job.ReMoveJob(this);
	//	g_pMainState->m_TriggerObj.ReMove(this);
	//	g_pMainState->m_Job.ReMoveJob(this);*/
	//	break;
	//case 11:
	//		/*GetJiangLi();
	//		GetShiFu()->Talk("做的不错,继续努力");*/
	//		return TRUE;
	//case 20://任务失败
	//	
	//	{
	//		//Process(1000);
	//		//int money = m_HuanShu * 50;
	//		//g_pCharacter->m_PCData.AddMoney(-money, 0,0);
	//		//g_pMainState->m_Tags.GetMoneyAndExp(-money);//损失
	//	}
	//	break;
	//case 4://取消任务
	//	
	//	{
	//		/*Process(11);
	//		return TRUE;*/
	//		//
	//	/*	if (g_pMainState->m_Dialog.m_retSelect)
	//			return TRUE;
	//		m_pNowObj->Talk("你的任务已经取消了");
	//		Process(20);	*/
	//	}
	//	break;
	//case 19:
	//	
	//	//{
	//	//	sZiZhi zizhi;
	//	//	zizhi.Set(1000, 1000, 1500, 4000, 1000, 1000, 100);
	//	//	g_pMainState->AddPCEnemy(m_Npc.m_name, m_Npc.m_modeid, g_pCharacter->m_PCData.m_LV,
	//	//		0, &zizhi, (eMengPai)m_EnemyMengPai, &m_ShiWeiWeapon);

	//	//	g_pMainState->m_FightList[10].isLive = TRUE;
	//	////	cObj* pObj = g_pMainState->m_FightList[10].m_pData;
	//	//	zizhi.Set(1000, 1000, 1500, 4000, 1000, 1000, 100);
	//	//	g_pMainState->AddPC(m_YuanJiu.m_name, m_YuanJiu.m_modeid, g_pCharacter->m_PCData.m_LV,
	//	//		0, &zizhi, (eMengPai)g_pCharacter->m_PCData.m_MengPaiID);
	//	//

	//	//	g_StateType = STATE_FIGHT;
	//	//	AddTriggerFightSuccess(17);
	//	//}
	//	break;

	//case 17:
	//	
	//	/*{
	//		cObj* pObj = g_pMainState->FindObjByName(m_Npc.m_name);
	//		pObj->Talk("我错了,回去告诉你师父吧,我再也不敢了");
	//		g_pMainState->m_Map.RemoveNpc(m_Npc.m_name);
	//		GetJiangLi();
	//	
	//	}*/
	//	break;
	//case 16://巡逻怪
	//	
	//	/*{
	//		g_pMainState->m_FightList[10].isLive = TRUE;
	//		cObj* pObj = g_pMainState->m_FightList[10].m_pData;
	//		sZiZhi zizhi;
	//		zizhi.Set(1000, 1000, 1500, 4000, 1000, 1000, 100);
	//		pObj->AutoPCData(m_Npc.m_name, m_Npc.m_modeid, 0, &zizhi, (eMengPai)m_EnemyMengPai, &m_ShiWeiWeapon);
	//		g_pMainState->FollowLv(10, g_pCharacter->m_PCData.m_LV);
	//		g_pMainState->m_FightList[11].isLive = TRUE;
	//		pObj = g_pMainState->m_FightList[11].m_pData;
	//		pObj->AutoPetData("帮凶", rand() % 70, 10, 0, g_pCharacter->m_PCData.m_LV);
	//	
	//		
	//		g_StateType = STATE_FIGHT;
	//		AddTriggerFightSuccess(17);
	//	}*/
	//	break;
	//case 15:
	//	/*if (0 == g_pMainState->m_Map.m_MapName.compare(m_Npc.m_mapname))
	//	{
	//		g_pMainState->m_Map.AddNpc(&m_Npc, this, "无", 16);
	//		cObj* target = g_pMainState->m_Map.m_pNpc[g_pMainState->m_Map.m_numberOfNpc - 1];
	//		cCharacter* pc= (cCharacter*)target->m_pIndex;
	//		pc->m_PCData.m_Equip[2] = m_ShiWeiWeapon;
	//		target->m_NowPos = -1;
	//		target->Set(POS_STAND);
	//	}*/
	//	break;
	case 0:
		if (!g_pMainState->m_pNowSelect)return TRUE;
		m_pNowObj = g_pMainState->m_pNowSelect;
#if ccc_m5
		if (-1 == g_pCharacter->m_PCData.m_MengPaiID)
#else
		if (-1 == g_pCharacter->m_PCData.m_MengPaiID || g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_ShiFuName != g_pMainState->m_pNowSelect->m_TrueName.GetString())
#endif
		{
			m_pNowObj->Talk("是否要拜师?", this, 1, "是", "否");
		}
		else
		{
			if (g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_ShiFuName== g_pMainState->m_pNowSelect->m_TrueName.GetString())
			{
				CheckInit(g_pCharacter->m_PCData.m_MengPaiID);
			/*	ostringstream oss;
				oss << "师门任务(还剩";
				oss << g_pCharacter->m_PCData.m_LV - m_HuanShu;
				oss << "个)";*/
				m_pNowObj->Talk("请选择要做的事",this,3, "学习技能");
			}
			else
			{
				m_pNowObj->Talk("非本门弟子,不要在此处逗留");
			}
		}
		break;
	case 1://拜师成功
		
		{
			if (0==g_pMainState->m_Dialog.m_retSelect)
			{
				int mengpaiid=-1;
				for (int i = 0; i < 12; i++)
				{
					if (g_pMainState->m_Dialog.m_ContextList.m_Name.GetString() == g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[i].m_ShiFuName)
					{
						mengpaiid = i;
						break;
					}
				}
				if (-1 == mengpaiid)ERRBOX;
#if ccc_m5
				g_pCharacter->m_PCData.m_MengPaiID = mengpaiid;
				g_pMainState->m_Tags.Add("恭喜你成功拜师");
				string text="门派特色:";
				switch (mengpaiid)
				{
				case eMP_大唐官府:
					g_pCharacter->m_PCData.m_Spurting.d1 += 20;
					text += "溅射伤害+20%";
					break;
				case eMP_化生寺:
					g_pCharacter->m_PCData.m_CureCriRate.d1+=20;
					text += "治疗有20%几率加倍";
					break;
				case eMP_方寸山:
					g_pCharacter->m_PCData.ghostSpecial.d1 += 30;
					text += "对鬼伤害+30%";
					break;
				case eMP_女儿村:
				case eMP_五庄观:
					g_pCharacter->m_PCData.m_SPD.AddDataAddPercent(10);
					text += "速度+10%";
					break;
				case eMP_狮驼岭:
					g_pCharacter->m_PCData.m_HPMax.AddDataAddPercent(20);
					text += "气血+20%";
					break;
				case eMP_魔王寨:
					g_pCharacter->m_PCData.m_MagicCriRate.d1 += 20;
					text += "20%几率法暴";
					break;
				case eMP_盘丝岭:
					g_pCharacter->m_PCData.m_HiddenWeaponDamagePercent.d2+= 50;
					text += "暗器防御+50%";
					break;
				case eMP_阴曹地府:
					g_pCharacter->m_PCData.m_DamageAddPercentMagic2.d1 += 20;
					text += "固定伤害+20%";
					break;
				case eMP_东海龙宫:
					g_pCharacter->m_PCData.m_PierceMagic.d1 += 15;
					text += "法术无视对方15%的灵力";
					break;
				case eMP_普陀山:
					g_pCharacter->m_PCData.m_DamageAddPercentCure.d1 += 20;
					text += "治疗率+20%";
					break;
				case eMP_天宫:
					g_pCharacter->m_PCData.m_HitRate.d2 += 15;
					text += "躲避率+15%";
					break;
				}
				g_pMainState->m_Channel.AddNewString(text);
#else
				auto func = [](cPCData &data, int _1)
				{
					string text;
					switch (data.m_MengPaiID)
					{
					case eMP_大唐官府:
						data.m_Pierce.d1 += _1 * 15;
						text += "无视防御+15%";
						break;
					case eMP_化生寺:
						data.m_CureCriRate.d1 += _1 * 20;
						text += "爆慈悲+20%";
						break;
					case eMP_方寸山:
						data.ghostSpecial.d1 += _1 * 50;
						data.MonsterSpecial.d1 += _1 * 50;
						text += "驱鬼效果+50%";
						break;
					case eMP_女儿村:
						data.m_SPD.AddDataAddPercent(_1 * 10);
						text += "速度+10%";
						break;
					case eMP_五庄观:
						data.m_ParryRate.d1 += _1 * 20;
						text += "格挡率+20%";
						break;
					case eMP_狮驼岭:
						data.m_SuckBloodRate.d1 += _1 * 10;
						text += "吸血+10%";
						break;
					case eMP_魔王寨:
						data.m_MagicCriRate.d1 += _1 * 15;
						data.m_MagicFire.d1 += _1 * 20;
						data.m_MagicFire.d2 += _1 * 20;
						data.m_CounterRate.d1 += _1 * 40;
						text += "法术暴击率+15%";
						break;
					case eMP_盘丝岭:
						data.m_HiddenWeaponDamagePercent.d2 += _1 * 50;
						text += "暗器防御+50%";
						break;
					case eMP_阴曹地府:
						data.m_DamageAddPercentMagic2.d1 += _1 * 20;
						data.m_SealRate.d2 += _1 * 20;
//						data.poisonRate.d1 += _1 * 20;
						text += "固定伤害+20%";
						break;
					case eMP_东海龙宫:
						data.m_MagicCriRate.d1 += _1 * 5;
						data.m_PierceMagic.d1 += _1 * 15;
						data.m_MagicWater.d1 += _1 * 20;
						data.m_MagicWater.d2 += _1 * 20;
						text += "无视灵力+15%";
						break;
					case eMP_普陀山:
					{
						data.m_DamageAddPercentCure.d1 += _1 * 20;
						int v = _1 * 20;
						data.m_MagicFire.d2 += v;
						data.m_MagicSoil.d2 += v;
						data.m_MagicWater.d2 += v;
						data.m_MagicThunder.d2 += v;
						text += "治疗效果+20%";
					}
						break;
					case eMP_天宫:
						data.m_HitRate.d2 += _1 * 25;
						data.MonsterSpecial.d1 += _1 * 50;
						text += "躲避率+25%";
						break;
					}
					return text;
				};

				func(g_pCharacter->m_PCData, -1);
				int mpOld = g_pCharacter->m_PCData.m_MengPaiID;
				g_pCharacter->m_PCData.m_MengPaiID = mengpaiid;
				g_pMainState->m_Tags.Add("恭喜你成功拜师");
				string text = "附加小光环:";
				text += func(g_pCharacter->m_PCData, 1);
				g_pMainState->m_Channel.AddNewString(text);
				if (mpOld < 0)
				{
					g_pCharacter->m_PCData.FollowSkill();
				}
				else
				{
					g_pCharacter->m_PCData.m_SkillEnablelist.clear();
					for (int i = 0; i < 7; ++i)
					{
						g_pMainState->m_SkillManager.lvUpMainSkill(g_pCharacter->m_PCData, 0, i, true);
					}
				}
#endif
			}
		}
		break;
	case 2:
		
		//{
		//	
		//	if (g_pMainState->m_Job.CheckHaveJob(m_type))
		//	{
		//		m_pNowObj->Talk("你已经有任务了,需要取消吗?取消任务会损失等级*50的钱",this,4, "我不做了");
		//		return TRUE;
		//	}
		//	m_bHaveTask = TRUE;
		//	int renqi = g_pCharacter->m_PCData.m_Popularity / 200;
		//	int  tasktype;
		//	if (m_HuanShu< 40)
		//	{
		//		if (rand() % 100 < 30 - renqi)
		//			tasktype =5;//巡逻
		//		else  
		//		if (rand() % 100 < 20 + renqi)
		//			tasktype = 0;//送信
		//		else  if (rand() % 100 < 15 + renqi)tasktype = 1;//要0级装备
		//		else  if (rand() % 100 < 15 + renqi)tasktype = 3;//要包子
		//		else  if (rand() % 100 < 15 + renqi)tasktype= 18;//要黄纸等
		//		else  tasktype = 2; //要垃圾药品
		//	}else
		//	if (m_HuanShu < 70)
		//	{	
		//		if (rand() % 100 < 30 - renqi)tasktype = 5;//巡逻
		//		else  if (rand() % 100 < 30 + renqi)tasktype = 4;//要10-30级装备
		//		else  if (rand() % 100 < 20 + renqi)tasktype = 8;//要召唤兽
		//		else  if (rand() % 100 < 20 + renqi)tasktype = 18;//要黄纸等
		//		else  tasktype = 2; //要垃圾药品
		//	}
		//	else
		//	if (m_HuanShu <100)
		//	{
		//		if (rand() % 100 < 20 - renqi)tasktype = 10;//
		//		else  if (rand() % 100 < 20 - renqi)tasktype = 19;//要40-50环
		//		else  if (rand() % 100 < 20 + renqi)tasktype = 8;//要召唤兽
		//		else  if (rand() % 100 < 20 - renqi)tasktype = 17;//要花 ,乐
		//		else  if (rand() % 100 < 20 + renqi)tasktype=11;//援救
		//		else  tasktype = 14;//要三级药
		//
		//	}
		//	else
		//	if (m_HuanShu < 130)
		//	{
		//		if (rand() % 100 < 20 - renqi)tasktype = 10;//
		//		else  if (rand() % 100 < 2 - renqi)tasktype = 16;//要60-70环
		//		else  if (rand() % 100 < 20 + renqi)tasktype = 8;//要召唤兽
		//		else  if (rand() % 100 < 20 - renqi)tasktype = 17;//要花 ,乐
		//		else  if (rand() % 100 < 20 + renqi)tasktype = 11;//援救
		//	//	else  if (rand() % 100 < 15 - renqi)tasktype = 7;//降伏
		//		else  tasktype = 14;//要三级药
		//	}
		//	else
		//	{
		//		if (rand() % 100 < 10 - renqi)tasktype = 10;//
		//		else  if (rand() % 100 < 5 - renqi)tasktype = 16;//要60-70环
		//		else  if (rand() % 100 < 15 + renqi)tasktype = 8;//要召唤兽
		//		else  if (rand() % 100 < 10 - renqi)tasktype = 17;//要花 ,乐
		//		else  if (rand() % 100 < 30 + renqi)tasktype = 11;//援救
		//		else  if (rand() % 100 < 10 - renqi)tasktype = 13;//要2级家具
		////		else  if (rand() % 100 < 15 - renqi)tasktype = 7;//降伏
		//		else  if (rand() % 100 < 10 - renqi)tasktype = 9;//要东西
		//		else  tasktype = 14;//要三级药
		//	}
		//	AddTask(tasktype);
		//}
		break;
	case 3:
		
		{
			switch (g_pMainState->m_Dialog.m_retSelect)
			{
			case 0:
				
				/*if (g_pCharacter->m_PCData.m_LV > 19)
				{
					if (m_HuanShu < g_pCharacter->m_PCData.m_LV)
					{
						return Process(2); 
					}
					else
					{
						
						g_pMainState->m_Dialog.m_pObj->Talk("你已经够努力了,过段时间再来做师门吧");
						return TRUE;
					}
				}
				else
				{
					g_pMainState->m_Dialog.m_pObj->Talk("你的等级太低,到20级再来");
					return TRUE;
				}*/
			//	break;
			//case 1://学习技能
				g_pMainState->m_LearnSkill.OnOff(TRUE);
				break;
			//case 2://领奖
			//	if (g_pCharacter->m_PCData.m_MengPaiPoint < 120)
			//	{
			//		m_pNowObj->Talk("你的门派贡献度太低,到20级再来");
			//	}
			//	else
			//	{
			//		g_pCharacter->m_PCData.m_MengPaiPoint -=120;
			//		SetJiangLiItem(31, 24);
			//	}
			//	break;
			default://关闭
				break;
			}
		}
		break;
	
	//case 5: //师门巡逻
	//
	//	{
	//			g_pMainState->m_InterfaceDoor.SetTrigger(this, 6, 600);
	//			g_pMainState->m_Map.m_MapType = 1;
	//			m_SuccessNum = 0;
	//	}
	//	return TRUE;
	//case 6:
	//	
	//	{
	//		cPetData* pPet;
	//		int petid = rand() % 50;
	//		m_enemyname = "捣乱的";
	//		sPetData* psPet = g_pMainState->m_PetDataManager.GetPetData(petid);
	//		m_enemyname += psPet->m_Name;
	//		pPet = AddPCPetEnemyF(g_pCharacter->m_PCData.m_LV * 40, (ePetID)petid, g_pCharacter->m_PCData.m_LV-20, eMP_随机, m_enemyname);
	//		m_enemyface = psPet->m_dialoghead[0];
	//		AddPetEnemyF(g_pCharacter->m_PCData.m_LV * 35, (ePetID)(rand() % 50), g_pCharacter->m_PCData.m_LV - 20, "帮凶");
	//		SetMusic();
	//		g_StateType = STATE_FIGHT;
	//		AddTriggerFightSuccess(7);
	//	}
	//	break;
	//case 7:
	//
	//	{
	//		string text;
	//		m_SuccessNum += 1;
	//		if (m_SuccessNum == 2)
	//		{
	//			GetJiangLi();
	//			text = "回去告诉你师父吧,我再也不敢了";
	//			g_pMainState->m_InterfaceDoor.SetTrigger(0, 0);
	//		}
	//		else
	//		{
	//			text = "我跑.继续捣乱去";	

	//		}
	//		g_pMainState->m_Dialog.Reset();
	//		g_pMainState->m_Dialog.m_ContextList.m_Name.SetString(m_enemyname);
	//		g_pMainState->m_Dialog.SetHead(m_enemyface);
	//		g_pMainState->m_Dialog.SetString(text);
	//		g_pMainState->m_Dialog.OnOff(TRUE);
	//	}
	//	break;
	//case 8:	
	//	if (0 == g_pMainState->m_Map.m_MapName.compare(m_Npc.m_mapname))
	//	{
	//		g_pMainState->m_Map.AddNpc(&m_Npc, this, "无", 9);
	//	}
	//	break;
	//case 9:
	//
	//	{
	//		g_pMainState->AddPCEnemy(m_Npc.m_name, 0, g_pCharacter->m_PCData.m_LV, 0, 0, (eMengPai)(rand() % 12),0, m_Npc.m_modeid);
	//		
	//		g_StateType = STATE_FIGHT;
	//		m_bXiangFuSuccess = FALSE;
	//		AddTriggerFightSuccess(10);
	//	}
	//	break;
	//case 10:
	//
	//	{
	//		g_pMainState->m_Map.RemoveNpc(m_Npc.m_name);
	//		if (m_bXiangFuSuccess)
	//		{
	//			g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->Talk("抓到了,回去报告师父吧");
	//			
	//			sJob job;
	//			job.m_Context = "回去把乾坤袋给师父";
	//			job.m_Title = "降伏";
	//			job.m_Time = 40;
	//			job.m_pTask = this;
	//			g_pMainState->m_Job.ReMoveJob(this);
	//			g_pMainState->m_Job.AddaJob(job);
	//			g_pMainState->m_TriggerObjMap.ReMove(this);
	//			string sfname = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PCData.m_MengPaiID)->m_Name;
	//			g_pMainState->m_TriggerGive.AddTask(sfname, 11, 28, this, 11);
	//		}
	//		else
	//		{
	//			g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
	//			m_Npc.m_name += g_pMainState->m_TaskBaoTu.AutoMakeName();
	//			ostringstream oss;
	//			oss << "有个#R";
	//			oss << m_Npc.m_name;
	//			oss << "#R在江湖上为非做歹,现被为师打伤,听说他在#R";
	//			oss << m_Npc.m_mapname;
	//			oss << "#R#Y";
	//			oss << m_Npc.m_x / 20;
	//			oss << " ";
	//			oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
	//			oss << "#Y养伤,你去用乾坤袋将他降伏带回来";
	//
	//			sJob job;
	//			job.m_Title = "降伏";
	//			job.m_Time = 40;
	//			job.m_Context = oss.str();
	//			job.m_pTask = this;
	//			g_pMainState->m_Job.ReMoveJob(this);
	//			g_pMainState->m_Job.AddaJob(job);
	//			g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->Talk("让他跑了,再去找他吧");
	//		}
	//	}
	//	break;

	//case 12:
	//
	//	{
	//		string shifuname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_ShiFuName;
	//		if (0==g_pMainState->m_pNowSelect->m_TrueName.GetString().compare(shifuname))
	//		{
	//			for (int i = g_pCharacter->m_PCData.m_NumofBB - 1; i >= 0; i--)
	//			{
	//				if (g_pCharacter->m_PCData.m_pPetDataList[i]->GetData()->m_ID == m_TargetBBid)
	//				{
	//					g_pCharacter->m_PCData.DeletePet(i);
	//					GetJiangLi();
	//					string targetname = g_pMainState->m_pNowSelect->m_TrueName.GetString();
	//					g_pMainState->FindObjByName(targetname)->Talk("做的不错,继续努力");
	//					return TRUE;
	//				}
	//				
	//			}
	//		}
	//	}
	//	return FALSE;
	case 13:
		
		{
			sPetData* pPetdata= g_pMainState->m_PetDataManager.GetPetData(m_TargetBBid);
			int moneyneed = pPetdata->m_LVLimit * 200+5500;
			cObj* pre = g_pMainState->m_Dialog.m_pObj;
			g_pMainState->m_Dialog.Reset();
			g_pMainState->m_Dialog.SetObj(pre);
			g_pMainState->m_Dialog.SetTrigger(this, 14,14,14,14,14);
			ostringstream oss;
			oss << "购买#R";
			oss << pPetdata->m_Name;
			oss << "#R需要#Y";
			oss << moneyneed;
			oss << "#Y两,确定要买吗?";
			g_pMainState->m_Dialog.SetString(oss.str(), "购买");
			g_pMainState->m_Dialog.OnOff(TRUE);
		}
		break;
	case 14:
		
		{
			if (g_pMainState->m_Dialog.m_retSelect == 0)
			{
			
				sPetData* pPetdata = g_pMainState->m_PetDataManager.GetPetData(m_TargetBBid);
				int moneyneed = pPetdata->m_LVLimit * 200 + 5500;
				if (g_pCharacter->m_PCData.m_Money[0] >= moneyneed)
				{
					cPet* pet = new cPet;
					pet->AutoPetData(m_TargetBBid, 1, 0);
#if ccc_m5
					pet->m_PetDataZZ.LeveUp(15, FALSE);
#else
					pet->m_PetDataZZ.LeveUp(g_pCharacter->m_PCData.m_LV, true, true);
#endif
					g_pCharacter->m_PCData.GetPet(pet);

					ostringstream oss;
					oss << "购买";
					oss << pPetdata->m_Name;
					oss << "花费";
					oss << moneyneed;
					oss << "两";
					g_pMainState->m_Tags.Add(oss.str());
					g_pCharacter->m_PCData.m_Money[0] -= moneyneed;
				}
				else
				{
					g_pMainState->m_Tags.Add("钱不够");
				}
			}
		}
		break;
	//case 100://送到信
	//	
	//	{
	//		string name = g_pMainState->m_InterfaceGive.GetTarget()->m_TrueName.GetString();
	//		if (0 == name.compare(m_npcname))
	//		{
	//			if (g_pMainState->m_InterfaceGive.m_NumItem[0].m_num)
	//			{
	//				sItem2& item = g_pMainState->m_InterfaceGive.m_ItemGive[0];
	//				if (item.GetType()==28)
	//				if (item.GetID() == 18)
	//				{
	//				//	g_pCharacter->m_PCData.m_Item[g_pMainState->m_InterfaceGive.m_ItemGiveOwner[0]].m_Num = 0;
	//					g_pMainState->m_InterfaceGive.GetTarget()->Talk("信已经收到了,回去告诉你师父吧");
	//					Process(1000);
	//					AddTriggerObj(GetShiFuName(),GetShiFuMap(),11);
	//					return TRUE;
	//				}
	//			}
	//			
	//		}
	//	}
	//	return FALSE;
	//case 101:
	//	
	//	{
	//		string name = g_pMainState->m_InterfaceGive.GetTarget()->m_TrueName.GetString();
	//		if (0 == name.compare(g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_ShiFuName))
	//		{
	//			if (g_pMainState->m_InterfaceGive.m_NumItem[0].m_num)
	//			{
	//				sItem2& item = g_pMainState->m_InterfaceGive.m_ItemGive[0];
	//				if (item.GetType() == m_ItemNeed.GetType())
	//				if (item.GetID() == m_ItemNeed.GetID())
	//				{
	//				//	g_pCharacter->m_PCData.m_Item[g_pMainState->m_InterfaceGive.m_ItemGiveOwner[0]].m_Num -= 1;
	//					GetJiangLi();
	//					
	//					g_pMainState->m_InterfaceGive.GetTarget()->Talk("表现的不错,这是奖励");
	//					return TRUE;
	//				}
	//			}

	//		}
	//	}
	//	return FALSE;
	default:
		break;
	}
	return TRUE;
}

//void cTaskSM::AddTask(int type)
//{
//	switch (type)
//	{
//		//
//	case 0://送信
//		
//		{
//			//..........
//			string  npcname;
//			cObj pShiFu;
//			if (g_pCharacter->m_PCData.m_MengPaiID<0 || g_pCharacter->m_PCData.m_MengPaiID>11)
//				return;
//			npcname = m_NameList[g_pCharacter->m_PCData.m_MengPaiID][rand() % m_NameList[g_pCharacter->m_PCData.m_MengPaiID].size()];
//			if (npcname == "")
//				return;
//			m_npcname = npcname;
//			ostringstream oss;
//			oss << "这里有一封给#R";
//			oss << npcname;
//			oss << "#R的信,麻烦你送过去";
//			DialogTalkNObj(oss.str());
//
//			UpdateJob(oss.str());
//			AddTriggerGive(npcname, 28, 18, 100);
//			SetJiangLiItem(18,28);
//		}
//		break;
//		case	1://要0级装备
//		case	2://要垃圾药品
//		case	3://要包子
//		case	4://要10-30装备
//		case	6://要垃圾药
//		case	9://要东西
//		case	12://要1级家具
//		case	13://要2级家具
//		case	14://要三级药
//		case	15://要烹饪
//		case	16://要60-70环
//		case	17://要花 ,乐
//		case	18://要黄纸等
//		case	19://要40-50环
//		
//			{
//					   int	itemtype = -1;
//					   int	itemid = -1;
//
//				switch (type)
//				{
//				case 1:
//					itemtype = rand() % 23;
//					if (itemtype == 13)itemtype = rand() % 13;
//					itemid = 0;
//					break;
//				case 2:
//					itemtype = 22;
//					switch (rand() % 6)
//					{
//					case 0:itemid = 1; break;
//					case 1:itemid = 2; break;
//					case 2:itemid = 19; break;
//					case 3:itemid = 20; break;
//					case 4:itemid = 26; break;
//					default:itemid = 34; break;
//					}
//					break;
//				case 3:
//					itemtype = 23;
//					itemid = 0;
//					break;
//				case 4:
//					itemtype = rand() % 23;
//					if (itemtype == 13)itemtype = rand() % 13;
//					itemid = g_pMainState->m_ItemManage.GetIDByLv(itemtype, (rand() % 3 + 1) *10);
//					break;
//				case	6://要垃圾药
//					itemtype = 22;
//					switch (rand() % 6)
//					{
//					case 0:itemid = 3; break;
//					case 1:itemid = 4; break;
//					case 2:itemid = 21; break;
//					case 3:itemid = 22; break;
//					case 4:itemid = 26; break;
//					default:itemid = 35; break;
//					}
//					break;
//				case	9://要宝石
//					itemtype = 29;
//					switch (rand() % 6)
//					{
//					case 0:itemid = 0; break;
//					case 1:itemid = 8; break;
//					case 2:itemid = 14; break;
//					case 3:itemid = 6; break;
//					case 4:itemid = 5; break;
//					default:itemid = 4; break;
//					}
//					break;
//				case	12://要1级家具
//					itemtype = 35;
//					itemid = rand() % 15;
//					break;
//				case	13://要2级家具
//					itemtype = 36;
//					itemid = rand() % 15;
//					break;
//				case	14://要高级药
//					itemtype = 22;
//					switch (rand() % 6)
//					{
//					case 0:itemid = 7; break;
//					case 1:itemid = 8; break;
//					case 2:itemid = 23; break;
//					case 3:itemid = 24; break;
//					case 4:itemid = 31; break;
//					default:itemid = 36; break;
//					}
//					break;
//				case	15://要烹饪
//					itemtype = 23;
//					switch (rand() % 6)
//					{
//					case 0:itemid = 1; break;
//					case 1:itemid = 2; break;
//					case 2:itemid = 3; break;
//					case 3:itemid = 5; break;
//					case 4:itemid = 6; break;
//					default:itemid = 7; break;
//					}
//					break;
//				case	16://要60-70环
//					itemtype = rand() % 23;
//					if (itemtype == 13)itemtype = rand() % 13;
//					itemid = g_pMainState->m_ItemManage.GetIDByLv(itemtype, (rand() % 2 + 6) * 10);
//					break;
//				case	17://要花 ,乐
//					if (rand() % 2)
//					{
//						itemtype = 30;
//						itemid = rand() % 2;
//					}
//					else
//					{
//						itemtype = 39;
//						itemid = rand() % 6;
//					}
//					break;
//				case	18://要黄纸等
//					itemtype = 27;
//					switch (rand() % 3)
//					{
//					case 0:itemid = 52; break;
//					case 1:itemid = 53; break;
//					case 2:itemid = 54; break;
//					}
//					break;
//				case	19://要40-50环
//					itemtype = rand() % 23;
//					if (itemtype == 13)itemtype = rand() % 13;
//					itemid = g_pMainState->m_ItemManage.GetIDByLv(itemtype, (rand() % 2 + 4) * 10);
//					break;
//				default:
//					return ;
//				}	
//				m_ItemNeed.Set(itemtype, itemid);
//
//				ostringstream oss;
//				oss<< "去帮为师买个#R";
//				oss<< m_ItemNeed.GetName();
//				oss << "#R回来";
//				UpdateJob(oss.str());
//				AddTriggerGive(g_pMainState->m_Dialog.m_pObj->m_TrueName.GetString(), itemtype, itemid, 101, 1);
//				DialogTalkNObj(oss.str()); 
//			}
//			break;
//		case	5://巡逻
//			
//			{
//				DialogTalkNObj("近来有些不法之徒在门派捣乱,现在派你去将他们就地斩杀");
//				UpdateJob("在门派巡逻");
//				m_mapname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_XunLuoMapName;
//				AddTriggerObjMap(m_mapname,5 );
//			}
//			break;
//		case	7://降伏
//			
//			{
//				if (!m_bInitXiangFu)InitXiangFu();
//
//				cObj* pPreObj = g_pMainState->m_Dialog.m_pObj;
//				g_pMainState->m_Dialog.Reset();
//				g_pMainState->m_Dialog.SetObj(pPreObj);
//				g_pMainState->m_Dialog.m_pObj = 0;
//
//				m_Npc.m_name = m_XiangFuNameList[rand() % m_XiangFuNameList.size()];
//				m_Npc.m_mapname = m_XiangFuDiDianList[rand() % m_XiangFuDiDianList.size()];
//				g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
//
//				ostringstream oss;
//				oss << "有个#R";
//				oss << m_Npc.m_name;
//				oss << "#R在江湖上为非做歹,现被为师打伤,听说他在#R";
//				oss << m_Npc.m_mapname;
//				oss << "#R#Y";
//				oss << m_Npc.m_x / 20;
//				oss << " ";
//				oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
//				oss << "#Y养伤,你去用乾坤袋将他降伏带回来";
//				DialogTalkNObj(oss.str());
//				UpdateJob(oss.str());
//				m_Npc.m_modeid = rand() % 40 + g_pCharacter->m_PCData.m_LV / 5;
//				AddTriggerObjMap(&m_Npc,8);
//			}
//			break;
//		case	8://要召唤兽
//			
//			{
//				m_TargetBBid = rand() % 20 + g_pCharacter->m_PCData.m_LV / 5;
//				string bbname= g_pMainState->m_PetDataManager.GetPetData(m_TargetBBid)->m_Name;
//				ostringstream oss;
//					oss<< "替为师抓只#R";
//				oss<< bbname;
//				oss<<"#R回来";
//				DialogTalkNObj(oss.str());
//				cMengPai& mp = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID];
//				m_Npc.m_name = mp.m_ShiFuName;
//				m_Npc.m_mapname = mp.m_ShiFuMap;
//				AddTriggerObj(m_Npc.m_name, m_Npc.m_mapname,12);
//				UpdateJob(oss.str());
//			}
//			break;
//		case	10://示威
//			
//			{
//				if (!m_bInitShiWei)InitShiWei();
//				m_EnemyMengPai = rand() % 12;
//				m_Npc.m_mapname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[m_EnemyMengPai].m_XunLuoMapName;
//				m_Npc.m_name = m_ShiWeiNameList[m_EnemyMengPai][rand() % m_ShiWeiNameList[m_EnemyMengPai].size()];
//				m_Npc.m_modeid = m_ShiWeiIdList[m_EnemyMengPai][rand() % m_ShiWeiIdList[m_EnemyMengPai].size()];
//				g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
//				ostringstream oss;
//				oss << m_Npc.m_mapname;
//				oss << "的#R";
//				oss << m_Npc.m_name;
//				oss << "#R多次袭击本门弟子,现躲在#R";
//				oss << m_Npc.m_mapname;
//				oss << m_Npc.m_x/20;
//				oss << "  ";
//				oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
//				oss << "#R,你去给ta点厉害瞧瞧";
//				string text = oss.str();
//				DialogTalkNObj(oss.str());
//				g_pMainState->m_TriggerObjMap.AddTask(this, 15,m_Npc);
//
//				int weapontype[2];
//				GetWeaponType(m_Npc.m_modeid, weapontype[0], weapontype[1]);
//				int typenum=2;
//				if (weapontype[1] == -1)typenum = 1;
//				int weaponid1,weapontype1;
//				weapontype1 =  weapontype[rand() % typenum];
//				weaponid1 =  g_pMainState->m_ItemManage.GetIDByLv(weapontype1, (rand() % 6 + 9) * 10);
//				m_ShiWeiWeapon.Set(weapontype1,weaponid1);
//				m_ShiWeiWeapon.m_Num = 1;
//				UpdateJob(oss.str());
//			}
//			break;
//		case	11://援救
//			
//			{
//				if (!m_bInitShiWei)InitShiWei();
//				if (!m_bInitXiangFu)InitXiangFu();
//				m_EnemyMengPai = rand() % 12;
//				m_Npc.m_mapname = m_XiangFuDiDianList[rand()%m_XiangFuDiDianList.size()];
//				m_Npc.m_name = m_ShiWeiNameList[m_EnemyMengPai][rand() % m_ShiWeiNameList[m_EnemyMengPai].size()];
//				m_Npc.m_modeid = m_ShiWeiIdList[m_EnemyMengPai][rand() % m_ShiWeiIdList[m_EnemyMengPai].size()];
//				g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
//				ostringstream oss;
//				oss << "#R";
//				oss << m_Npc.m_name;
//				oss << "#R正在#R";
//				oss << m_Npc.m_mapname;
//				oss << m_Npc.m_x / 20;
//				oss << "  ";
//				oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
//				oss << "#R,袭击本门弟子,你快去援救";
//				string text = oss.str();
//				DialogTalkNObj(text);
//				m_YuanJiu.m_name = "苦战中的同门";
//				m_YuanJiu.m_x = m_Npc.m_x;
//				m_YuanJiu.m_y = m_Npc.m_y;
//				m_YuanJiu.m_direction = m_Npc.m_direction;
//				m_YuanJiu.m_modeid = rand() % 14;;
//	
//				g_pMainState->m_TriggerObjMap.AddTask(this, 19, m_YuanJiu);
//				int weapontype[2];
//				GetWeaponType(m_Npc.m_modeid, weapontype[0], weapontype[1]);
//				int typenum = 2;
//				if (weapontype[1] == -1)typenum = 1;
//				int weaponid1, weapontype1;
//				weapontype1 = weapontype[rand() % typenum];
//				weaponid1 = g_pMainState->m_ItemManage.GetIDByLv(weapontype1, (rand() % 6 + 9) * 10);
//				m_ShiWeiWeapon.Set(weapontype1, weaponid1);
//				m_ShiWeiWeapon.m_Num = 1;
//				UpdateJob(text);
//			}
//			return;
//	}
//}

void cTaskSM::GetJiangLi()
{
	int lv = m_HuanShu+20;
	int exp,money;
	if (lv < 40)
	{
		exp = (1500 - lv * 12);
		money = (700 - lv * 9);
	}
	if (lv < 70)
	{
		exp = (2100 - lv * 12);
		money = (1400 - lv * 13);
	}
	if (lv < 100)
	{
		exp = (2700 - lv * 11);
		money = (1700 - lv * 10);
	}
	if (lv < 130)
	{
		exp = (3300 - lv * 11);
		money = (2000 - lv * 11);
	}
	else
	{
		exp = (3900 - lv * 8);
		money = (2300 - lv * 8);
	}
	exp = (exp*15*lv) / 100;
	money = (money *15*lv) / 100;
	SetJiangLi2(exp,money);
	m_HuanShu += 1;
	g_pCharacter->m_PCData.m_MengPaiPoint += 1;
	m_bHaveTask = FALSE;
	Process(1000);
}

void cTaskSM::CheckInit(int mengpaiid)
{
	if (!m_bInit2) Init();
	if (m_bInit[mengpaiid])return;
	//cMengPai& mengpai= g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[mengpaiid];
	//string path;
	//path = g_strMediaPath;
	//path+="任务\\师门\\";
	//if (mengpaiid == 4)//BUG
	//{
	//	path += "狮陀岭";
	//}
	//else
	//	path += mengpai.m_Name;
	//path += ".txt";
	//ifstream File;
	//File.open(path);
	//if (!File.is_open())ERRBOX;
	//int num;
	//File >> num;
	//string name;
	//for (int i = 0; i < num; i++)
	//{
	//	File >> name;
	//	m_NameList[mengpaiid].push_back(name);
	//}
	//File.close();
}

void cTaskSM::InitXiangFu()
{
	/*ifstream File;
	ostringstream oss;
	oss << g_strMediaPath << "任务//师门//师门降伏.txt";
	File.open(oss.str());
	if (!File.is_open()){ ERRBOX; return; }
	int num;
	File >> num;
	string didian;
	for (int i = 0; i < num; i++)
	{
		File >> didian;
		m_XiangFuDiDianList.push_back(didian);
	}
	File >> num;
	string name;
	for (int i = 0; i < num; i++)
	{
		File >> name;
		m_XiangFuNameList.push_back(name);
	}
	File.close();*/
}

cObj* cTaskSM::GetShiFu()
{
	return g_pMainState->FindObjByName(GetShiFuName());
}

std::string cTaskSM::GetShiFuName()
{
	if (-1 == g_pCharacter->m_PCData.m_MengPaiID)return "";
	return g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PCData.m_MengPaiID)->m_ShiFuName;
}
std::string cTaskSM::GetShiFuMap()
{
	if (-1 == g_pCharacter->m_PCData.m_MengPaiID)return "";
	return g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PCData.m_MengPaiID)->m_ShiFuMap;
}
void cTaskSM::InitShiWei()
{
	m_bInitShiWei = TRUE;
	ifstream File;
	ostringstream oss;
#if ccc_m5
	oss << g_strMediaPath << "任务\\师门\\师门示威.txt";
#else
	oss << g_strMediaPath << "师门\\师门示威.txt";
#endif
	File.open(oss.str());
	if (!File)ERRBOX;
	string name;
	int num;
	int id;
	for (int i = 0; i < 12; i++)
	{
		File >> name;
		File >> num;
		for (int j = 0; j < num; j++)
		{
			File >> name;
			File >> id;
			m_ShiWeiIdList[i].push_back(id);
			m_ShiWeiNameList[i].push_back(name);
		}
	}
}

void cTaskSM::UpdateJob(string context)
{
	sJob job;
	job.Set("师门", context,30,this,20);
	g_pMainState->m_Job.AddaJob(job,m_HuanShu);
}

void cTaskSM::Save(ofstream& File)
{
	File<< m_HuanShu<<" ";
	File << m_bHaveTask<<" ";
	if (!m_bHaveTask)return;
	File << m_bXiangFuSuccess;
	m_Npc.Save(File);
	File << m_EnemyMengPai;
	m_ShiWeiWeapon.Save(File);//示威时NPC的武器
	m_YuanJiu.Save(File);
	File << m_TargetBBid;
	m_ItemNeed.Save(File);//记录当前师门要的东西
	File << m_npcname<<" "; //记录当前师门要找的人
	File << m_mapname<<" ";
	File << m_SuccessNum<<" ";
	File << m_enemyname<<" ";
	File << m_enemyface<<" ";
}

void cTaskSM::Load(ifstream& File)
{
	m_bInitShiWei = FALSE;
	for (int i = 0; i < 12; i++)
		m_bInit[i] = 0;
	File >> m_HuanShu;
	File >> m_bHaveTask;
	if (!m_bHaveTask)return;
	File >> m_bXiangFuSuccess;
	m_Npc.Load(File);
	File >> m_EnemyMengPai;
	m_ShiWeiWeapon.Load(File);//示威时NPC的武器
	m_YuanJiu.Load(File);
	File >> m_TargetBBid;
	m_ItemNeed.Load(File);//记录当前师门要的东西
	File >> m_npcname ; //记录当前师门要找的人
	File >> m_mapname ;
	File >> m_SuccessNum ;
	File >> m_enemyname ;
	File >> m_enemyface ;
}


BOOL cTaskFB::Process(int stage)
{
	
	switch (m_FBID)
	{
	case 0:ProcessWj(stage);break;
	case 1:ProcessSL(stage);break;
	case 2:ProcessCC(stage); break;
	case 3:ProcessSM(stage); break;
	case 4:ProcessSJ(stage); break;
	}
	return TRUE;
}

BOOL cTaskFB::Start(int id)
{
	m_FBID = id;
	m_TextList.clear();
	ifstream File;
	ostringstream oss;
#if ccc_m5
	oss <<g_strMediaPath<<"任务//副本//" << id << ".txt";
#else
	oss << g_strMediaPath << "副本//" << id << ".txt";
#endif
	File.open(oss.str());
	if (!File)ERRBOX;
	int num;
	File >> num;
	if (num)
	{
		m_TextList.resize(num);
		getline(File, m_TextList[0]);
		for (int i = 0; i < num; i++)
		{
			getline(File, m_TextList[i]);
		}
	}
	File.close();
	m_List.clear();
	m_List2.clear();
	return TRUE;
}

void cTaskFB::ProcessWj(int stage)
{
	int lv = g_pCharacter->m_PCData.m_LV;
	switch (stage)
	{
	case 0:
		
		{
			m_Stage = 0;
			g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[0], this, 1);
			g_pMainState->m_TriggerObjMap.AddTask(this, 2, m_TextList[3]);
			StageSetSameNpc(3, m_TextList[3], 3, 10, m_TextList[4]);
			UpdateJob(m_TextList[20]);
		}
		break;
	case 1:
	
		{
			g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, -100, "是", "否");
		}
		break;
	case -100:
		if (g_pMainState->m_Dialog.m_retSelect)
		return ;
	case -1:
		
		{
			if (m_Stage < 10)
			{
				g_pMainState->m_Map.LoadMap(118, 90, m_TextList[3].c_str());
			}
			else
			{
				g_pMainState->m_Map.LoadMap(30, 16, m_TextList[12].c_str());
			}
		}
		break;
	case -2:
		break;
	case 2:
		
		{
			if (0 == m_Stage)
			{
				g_pMainState->m_TriggerDialog.AddTaskFB("0", 0, this, -2);
				m_Stage = 1;
			}
			AddNpc();
			ostringstream oss;
			oss << "还剩#R" << m_List.size() << "#R个树妖";
			UpdateJob(oss.str(), 40);
		}
		break;
	case 3://树妖战斗
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
		 	AddPCPetEnemyF(lv * 90, e树怪, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			int enemynum =  g_pMainState->AtutoGetEnemyNum()-1;
			for (int i = 0; i < enemynum; i++)
			{
				AddPCPetEnemyF(lv * 80, e树怪, -1, eMP_随机, "伙伴木妖");
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(4);
		}
		break;
	case 4://树妖战斗胜利
		
		{
			SetJiangLi(2);
			
			if (true || !m_List.size())
			{
				if (1 == m_Stage)
				{
					g_pMainState->m_Map.RemoveAllNpc();
					g_pMainState->m_InterfaceSmallMap.clear();
					m_List.clear();
					g_pMainState->m_TriggerDialog.AddTaskFB("0", 1, this, -5);
					m_Stage += 1;
				}
				return ;
			}
			RemoveNpc(m_NowNpc);
			ostringstream oss;
			oss << "还剩#R" << m_List.size() << "#R个树妖";
			UpdateJob(oss.str());
		}
		break;
	case -5:
		
		{
			RemoveNpc(m_NowNpc);
			StageSetSameNpc(1111, m_TextList[3], 6, 15, m_TextList[6]);
			g_pMainState->m_TriggerObjMap.AddTask(this, 5, m_TextList[3]);	
			ostringstream oss;
			oss << "还剩#R" << m_List.size() << "#R个仙人";
			UpdateJob(oss.str(), 40);
		}
		break;
	case 5:
		
		{
			AddNpc();
			ostringstream oss;
			oss << "还剩#R" << m_List.size() << "#R个仙人";
			UpdateJob(oss.str(), 40);
		}
		break;
	case 6:
		
		{ //点中一个仙人
			m_NowNpc = g_pMainState->m_pNowSelect;
			RemoveNpc(m_NowNpc);
			m_NowNpc = 0;
			SetJiangLi(2,300,50);
			if (5 >= m_List.size())
			{ //仙人数为0
				cObj obj;
				obj.SetXY(116 * 20, g_pMainState->m_Map.m_pMap->m_Height - 23 * 20);
				g_pMainState->m_FindPt.FindPath(&obj, 26 * 20, g_pMainState->m_Map.m_pMap->m_Height - 42 * 20);
				m_List.resize(15);//荆棘妖
				int timenum = obj.m_time / m_List.size();
				for (int i = 0; i < m_List.size(); i++)
				{
					SetNpc( m_List[i],8,m_TextList[9], m_TextList[3], 15, obj.m_Path[obj.m_time].sx / 20,
						(g_pMainState->m_Map.m_pMap->m_Height - obj.m_Path[obj.m_time].sy) / 20);
					obj.m_time -= timenum;	
				}
				UpdateJob(m_TextList[10]);
				g_pMainState->m_Tags.Add(m_TextList[10]);
				//国王
				m_List2.resize(1);
				SetNpc(m_List2[0],-7,m_TextList[8], m_TextList[3], 1003,18,35);
				g_pMainState->m_InterfaceSmallMap.clear();
				g_pMainState->m_InterfaceSmallMap.addNpc(&m_List2[0].m_Npc);
				AddTriggerObjMap(m_TextList[3],-6);
				m_Stage = 2;
				Process(-6);
				AddTriggerDialog(3,-2);
				return;
			}
			ostringstream oss;
			oss << "还剩#R" << m_List.size() << "#R个仙人";
			UpdateJob(oss.str());
		}
		break;
	case -6: //国王出现
		
		{
			if (m_Stage == 3)
			{
				AddNpc();
			}
			else
				AddNpcOne(&m_List2[0],TRUE);
		}
		break;
	case -7://与国王对话
		
		{ 
			if (2 == m_Stage)AddTriggerDialog(2, 7);
		}
		break;
	case 7://荆棘妖出现
		
		{	
			m_Stage = 3;
			sJob job;
			job.Set(m_TextList[5], m_TextList[7], 40, this, 1002);
			g_pMainState->m_Job.AddaJob(job);
			Process(-6);
		}
		break;
	case 8://荆棘战斗
	
		{ 
			m_NowNpc = g_pMainState->m_pNowSelect;
			cPetData* pet;
			pet= AddPCPetEnemyF(lv * 140, e花妖, lv+5, eMP_化生寺, m_NowNpc->m_TrueName.GetString());
			pet->AddSkill(ePS_反震);
			pet=AddPCPetEnemyF(lv * 140, e牛妖, lv + 5, eMP_魔王寨, "大法荆棘");
			pet->m_DamageAddPercentMagic.d2 += 50;
			AddPCPetEnemyF(lv * 140, e羊头怪, lv + 5, eMP_大唐官府, "大力荆棘");
			pet->m_DamagePercent.d2 += 50;
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(9);
		}
		break;
	case 9://荆棘奖励
		
		{
			SetJiangLi(3);
			RemoveNpc(m_NowNpc);
			m_NowNpc = 0;
			if (true || !m_List.size())
			{
				m_List2.clear();
				m_List.clear();
				StageSetSameNpc(36, m_TextList[12], 11, 3, m_TextList[13]);
				g_pMainState->m_Channel.AddNewString(m_TextList[11]);
				m_Stage = 10;
				g_pMainState->m_TriggerObjMap.AddTask(this, 10, m_TextList[12]);
				Process(-1);
				return;
			}
			ostringstream oss;
			oss << "还剩#R" << m_List.size() << "#R个荆棘";
			UpdateJob(oss.str());
		}
		break;
	case 10://守阵妖怪出现

		{
			UpdateJob(m_TextList[11],40);
			AddNpc();
		}
		break;
	case 11://守阵妖怪 战斗
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;

			m_NowNpc = g_pMainState->m_pNowSelect;
			AddPCPetEnemyF(lv * 150, e地狱战神, lv+5, eMP_随机, m_NowNpc->m_TrueName.GetString());
			for (int i = 0; i < 2;i++)
			AddPCPetEnemyF(lv * 90, e兔子怪, lv+3, eMP_随机, "妖怪守卫");
			for (int i = 0; i < 5; i++)
			{
				AddPCPetEnemyF(lv * 100, e牛头, -1, eMP_随机, "妖怪士兵");
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(12);
		}
		break;
	case 12:
	
		{
			SetJiangLi(5);
			RemoveNpc(m_NowNpc);
			m_NowNpc = 0;
			if (true || !m_List.size())
			{ //阵破 ;
				vector<int>  modeid;
				modeid.resize(30);
				for (int i = 0; i < 30; i++)
					modeid[i] = i;
				StageSetSameNpc(modeid, m_TextList[12], 15, 15, m_TextList[16]);

				g_pMainState->m_TriggerObjMap.AddTask(this, 13, m_TextList[12]);
				UpdateJob(m_TextList[14], 40);
				g_pMainState->m_Channel.AddNewString(m_TextList[14]);
				return;
			}
			if (m_List.size() == 2)
			{
				UpdateJob(m_TextList[11], 5);
			}
		}
		break;
	case 13:
	
		{
			UpdateJob(m_TextList[14], 40);
			g_pMainState->m_Channel.AddNewString(m_TextList[14]);
			AddNpc();
		}
		break;
	case 15://小妖战斗
	
		{
			
			m_NowNpc = g_pMainState->m_pNowSelect;

			AddPCPetEnemyF(lv * 70, (ePetID)m_NowNpc->GetModeID(), -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			for (int i = 0; i < 4; i++)
			{
				AddPCPetEnemyF(lv * 60,(ePetID)(rand()%40), -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(16);
		}
		break;
	case 16://小妖奖励
	
		{
			SetJiangLi(2);
			RemoveNpc(m_NowNpc);
			if (true || !m_List.size())
			{ //
				m_List.resize(1);
				SetNpc(m_List[0],18,m_TextList[19], m_TextList[12], 51, 64, 32, 1);
				g_pMainState->m_TriggerObjMap.AddTask(this, 17, m_TextList[12]);
				UpdateJob(m_TextList[15]);
				Process(17);
				return;
			}
			
		}
		break;
	case 17://BOSS出现
	
		{
			g_pMainState->m_Tags.Add(m_TextList[15]);
			AddNpc();
		}
		break;
	case 18:
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			cPetData* pPet;
			AddPCPetEnemyF(lv * 160, e大力金刚, lv+10, eMP_狮驼岭, m_NowNpc->m_TrueName.GetString());
			for (int i = 0; i < 4; i++)
			{
				pPet=AddPCPetEnemyF(lv * 150, e蛤蟆精, lv + 5, eMP_随机, "随从");
				pPet->m_Combo.d1 = 60;
				pPet->comboNumUp = 6;
			}
			for (int i = 0; i < 5; i++)
			{
				pPet = AddPCPetEnemyF(lv * 140, e狐狸精, lv + 5, eMP_随机, "使女");
				pPet->m_Combo.d1 = 60;
				pPet->comboNumUp = 6;
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(19);
		}
		break;
	case 19:

		{
			SetJiangLi(10);
			RemoveNpc(m_NowNpc);

			g_pMainState->m_Channel.AddNewString(m_TextList[17]);
			g_pMainState->m_Tags.Add(m_TextList[17]);
		}
	case 1002:

		{
			EndFB();
		}
		break;
	default:
		ERRBOX;
		break;
	}
}

void cTaskFB::Load(ifstream& File)
{//放在地图读取后
	m_List.clear();
	m_List2.clear();
	File >> m_FBID;
	if (-1 == m_FBID)return;
	File >> m_Stage;
	File >> m_Stage2;
	File >> m_HuanShu;
	Start(m_FBID);
	int npc2num;
	File >> npc2num;
	m_List.resize(npc2num);
	for (int i = 0; i < npc2num; i++)
		m_List[i].Load(File);

	File >> npc2num;
	m_List2.resize(npc2num);
	for (int i = 0; i < npc2num; i++)
	{
		m_List2[i].Load(File);
	}
	BOOL havetrigger;
	File >> havetrigger;
	if (havetrigger)
	{
		int type;
		File >> type;
		m_pEnd = g_pMainState->FindTaskByID(type);
		File >> m_Ret;
	}
}

void cTaskFB::Save(ofstream& File)
{
	File << "\n";
	File << m_FBID << " ";
	if (-1 == m_FBID)return;
	File << m_Stage<<" ";
	File << m_Stage2 << " ";
	File << m_HuanShu << " ";
	File << m_List.size() << " ";
	for (int i = 0; i < m_List.size(); i++)
	{
		m_List[i].Save(File);
	}
	File << m_List2.size()<<" ";
	for (int i = 0; i < m_List2.size(); i++)
	{
		m_List2[i].Save(File);
	}
	if (m_pEnd)
	{
		File << 1 << " ";
		File << m_pEnd->m_type<<" ";
		File << m_Ret<<" ";
	}
	else
	{
		File << 0 << " ";
	}
}
void cTaskFB::RemoveNpc(sNpc* p, BOOL bRemoveList )
{
	cObj* po = g_pMainState->FindObjByNpc(p);
	RemoveNpc(po,bRemoveList);
}
void cTaskFB::RemoveNpc(cObj*& p, BOOL bRemoveList )
{
	if (!p)return;
	if (bRemoveList)
	{
		UINT i;
		for (i = 0; i < m_List.size(); i++)
		{
			if (m_List[i].m_Npc.m_x == p->GetX() / 20)
			if (m_List[i].m_Npc.m_y == (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20)
			if (m_List[i].m_Npc.m_name == p->m_TrueName.GetString())
			{
				m_List.erase(m_List.begin() + i);
				break;
			}
		}
		if (i==m_List.size())
		for (i = 0; i < m_List2.size(); i++)
		{
			if (m_List2[i].m_Npc.m_x == p->GetX() / 20)
			if (m_List2[i].m_Npc.m_y == (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20)
			if (m_List2[i].m_Npc.m_name == p->m_TrueName.GetString())
			{
				m_List2.erase(m_List2.begin() + i);
				break;
			}
		}
	}
	g_pMainState->m_Map.RemoveNpc(p, TRUE);
	p = 0;
}

void cTaskFB::AddTriggerDialog(string path, int id, int ret)
{
	g_pMainState->m_TriggerDialog.AddTaskFB(path, id, this, ret);
}

void cTaskFB::AddNpc()
{
	for (int i = 0; i < m_List.size(); i++)
	{
		g_pMainState->m_Map.AddNpc(&m_List[i]);
	}
	for (int i = 0; i < m_List2.size(); i++)
	{
		g_pMainState->m_Map.AddNpc(&m_List2[i]);
	}
	g_pMainState->FindObj();
}

void cTaskFB::UpdateJob(string context, int time/*=-1*/, int falret /*= 1002*/, string title /*= ""*/)
{ //
	sJob job;
	if (title == "")
		title = "副本";
	job.Set(title, context, time, this, falret);
	g_pMainState->m_Job.AddaJob(job);
}



void cTaskFB::ProcessSL(int stage)
{
	switch (stage)
	{
	case 0:
		
		{
			m_Stage = 0;
			g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[0], this, 1);
			g_pMainState->m_TriggerObjMap.AddTask(this, 2, m_TextList[2]);
			m_List.resize(2);
			SetNpc(m_List[0],3,m_TextList[3], m_TextList[2],1117,35,37,3);
			SetNpc(m_List[1],6, m_TextList[4], m_TextList[2], 1118, 93, 80, 1);
			UpdateJob(m_TextList[26]);
		}
		break;
	case 1:g_pMainState->m_pNowSelect->Talk(m_TextList[5], this, -1, "是", "否");
		break;
	case -1:
		if (!g_pMainState->m_Dialog.m_retSelect)
		{
			UpdateJob(m_TextList[8], 120);
			g_pMainState->m_Map.LoadMap(16, 14, m_TextList[2].c_str());
		}
		break;
	case 2:
		
		{
			if (!m_List.size())return ;
			if (m_Stage==3)
				AddNpcOne(&m_List[1]);
			AddNpcOne(&m_List[0], TRUE);
		}
		break;
	case 3:
		m_NowNpc = g_pMainState->m_pNowSelect;
		g_pMainState->m_pNowSelect->Talk(m_TextList[13], this, -3, "是", "否");
		break;
	case -3:
			switch (m_Stage)
			{
			case 0://送信
				
				{
					m_NowNpc->Talk(m_TextList[7]);
					g_pMainState->m_TriggerObjMap.AddTask(this, 4, m_TextList[9]);
					UpdateJob(m_TextList[7]);
					m_Stage = 2;
					
				}
				break;
			case 1: //收集木材
				
				{
					m_NowNpc->Talk(m_TextList[6]);
					g_pMainState->m_TriggerObj.AddTask(m_TextList[4], m_TextList[2], this, 6);
					UpdateJob(m_TextList[6]);
					m_Stage = 3;
					AddNpcOne(&m_List[1]);

				}
				break;
			default:
				break;
			}
		break;
	case 4://设置NPC
		
		{
			cMyMap* p = &g_pMainState->m_Map;
			int num = p->m_numberOfNpc;
			for (int i = 0; i < num; i++)
			{
				p->m_pNpc[i]->m_TaskTrigger.m_pTask = this;
				p->m_pNpc[i]->m_TaskTrigger.m_Stage = 5;
			}
		}
		break;
	case 5://回收NPC
		
		{
			g_pMainState->m_pNowSelect->Talk(m_TextList[10]);
			g_pMainState->m_Dialog.m_pObj = 0;
			g_pMainState->m_Map.RemoveNpc(g_pMainState->m_pNowSelect,TRUE);
			if (g_pMainState->m_Map.m_numberOfNpc< /*3*/20) // 21个NPC
			{
				g_pMainState->m_Map.RemoveAllNpc();
				UpdateJob(m_TextList[8]);
				SetJiangLi(10,TRUE);
				g_pMainState->m_TriggerObjMap.ReMove(this,m_TextList[9]);
				g_pHeroObj->Talk(m_TextList[14]);
				m_Stage = 1;

				g_pMainState->m_TriggerObjMap.AddTask(this, 2, m_TextList[2]);
			
				m_HuanShu = 0;
				g_pMainState->m_Map.LoadMap(16, 14, m_TextList[2].c_str());
			}
		}
		break;
	case 6:
		{
			if (3 != m_Stage)return;
			int lv = g_pCharacter->m_PCData.m_LV;
			m_NowNpc = g_pMainState->m_pNowSelect;
			int select = rand() % 10;
			if (false && select == 0)
			{
				Process(7);
			}
			else
			{
				g_pMainState->m_Tags.Add(m_TextList[11]);
				for (int i = 0; i < 8; i++)
				{
					AddPCPetEnemyF(lv*60, (ePetID)(rand() % 10), -1, eMP_随机, m_TextList[12]);
				}
				SetMusicFB();
				g_StateType = STATE_FIGHT;
				AddTriggerFightSuccess(7);
			}
		}
		break;
	case 7://桃树奖励
		{
			SetJiangLi(2);
			m_HuanShu += 1;
			if (true || m_HuanShu == 5)
			{
				RemoveNpc(m_NowNpc);
				m_NowNpc = g_pMainState->FindObjByName(m_TextList[3]);
				RemoveNpc(m_NowNpc);
				g_pMainState->m_TriggerObj.ReMove(this);
				AddTriggerDialog(0, 8);

				return;
			}
			UpdateJob(m_TextList[8], 120);
			m_Stage = 1;
		}
		break;
	case 8:
		{
			sMapObjTrigger npc;
			SetNpc(npc,9,m_TextList[15], m_TextList[2], 139, 49, 28,1);
		
			UpdateJob(m_TextList[20]);
			g_pMainState->m_TriggerObjMap.AddTask(npc);
			AddNpcOne(&npc,FALSE);
		}
		break;
	case 9:
		m_NowNpc = g_pMainState->m_pNowSelect;
		AddTriggerDialog(1, 10); break;
	case 10:
		{

			m_List.resize(2);
			SetNpc(m_List[0],12,m_TextList[17], m_TextList[2], 56, 116, 83, 1);//虎翼
			SetNpc(m_List[1],13,m_TextList[18], m_TextList[2], 49, 122, 80, 1);//蛇
			AddTriggerObjMap(m_TextList[2], 11);
			g_pMainState->m_Map.RemoveNpc(m_NowNpc,TRUE);
			g_pMainState->m_Map.RemoveNpc("程咬金", TRUE);
			UpdateJob(m_TextList[16]);
			Process(11);
		}
		break;
	case 11:AddNpc(); break;
	case 12:
	case 13:
		{
			int lv = g_pCharacter->m_PCData.m_LV;
			m_NowNpc = g_pMainState->m_pNowSelect;
		//	sNpc* pNpc = (sNpc*)m_NowNpc->m_pIndex;
			if (stage == 12)
			{	
				AddPCPetEnemyF(lv * 120, (ePetID)m_List[0].m_Npc.m_modeid, lv + 5, eMP_随机, m_TextList[17]);
			}
			else
			{
				AddPCPetEnemyF(lv * 120, (ePetID)m_List[m_List.size()-1].m_Npc.m_modeid, lv + 5, eMP_随机, m_TextList[18]);
			}
			for (int i = 0; i < 7; i++)
			{
				AddPCPetEnemyF(lv * 80, (ePetID)(rand() % 40), -1, eMP_随机, m_TextList[19]);
			}
			AddTriggerFightSuccess(14);
			SetMusicFB();
			g_StateType = STATE_FIGHT;
		}
		break;
	case 14:
		{
			SetJiangLi(4, 1);
			RemoveNpc(m_NowNpc);
			if (!m_List.size())
			{
				m_List.resize(1);
				SetNpc( m_List[0],15,m_TextList[21], m_TextList[2], 1066, 120, 81, 1);
				AddTriggerObjMap(&m_List[0]);
				AddNpc();
			}
		}
		break;
	case 15:
			g_pMainState->m_pNowSelect->Talk(m_TextList[22], this, 16, "是", "否");
		break;
	case 16:
	{
			g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[22], this, 18);
			g_pMainState->m_Map.LoadMap(54, 4, m_TextList[23].c_str());
			AddTriggerObjMap(m_TextList[23], 11);
			m_List.resize(20);
			cObj obj;
			obj.SetXY(28 * 20, g_pMainState->m_Map.m_pMap->m_Height - 14 * 20);
			g_pMainState->m_FindPt.FindPath(&obj, 20 * 20, g_pMainState->m_Map.m_pMap->m_Height - 81 * 20);
			int timenum = obj.m_time / m_List.size();
			for (int i = 0; i < m_List.size(); i++)
			{
				SetNpc(m_List[i],22,m_TextList[19], m_TextList[23], rand() % 40, obj.m_Path[obj.m_time].sx / 20, (g_pMainState->m_Map.m_pMap->m_Height - obj.m_Path[obj.m_time].sy) / 20);
				obj.m_time -= timenum;
			}
			m_List2.resize(1);
			for (int i = 0; i < m_List2.size(); i++)
			{
				SetNpc(m_List2[i],21,m_TextList[24], m_TextList[23], 121, 43, 78, 1);
			}
			Process(11);
		}
		break;
	case 18:g_pMainState->m_pNowSelect->Talk(m_TextList[5], this, 19, "是", "否");
		break;
	case 19:
		g_pMainState->m_Map.LoadMap(16, 14, m_TextList[2].c_str());
		break;
	case 22: //小妖战斗
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			int lv = g_pCharacter->m_PCData.m_LV;
			AddPCPetEnemyF(lv * 80, (ePetID)(m_NowNpc->GetModeID()));
			for (int i = 0; i < 7; i++)
			{
				AddPCPetEnemyF(lv * 70, (ePetID)(m_NowNpc->GetModeID()));
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(20);
		}
		break;
	case 20://小妖奖励
		
		{
			SetJiangLi(2);
			RemoveNpc(m_NowNpc);
		}
		break;
	case 21://大王战斗
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			int lv = g_pCharacter->m_PCData.m_LV;
			AddPCPetEnemyF(lv * 150, (ePetID)m_NowNpc->GetModeID(), lv + 10, eMP_随机, m_NowNpc->m_TrueName.GetString());
			for (int i = 0; i < 9; i++)
			{
				AddPCPetEnemyF(lv * 100,(ePetID)(rand()%50));
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;

			AddTriggerFightSuccess(23);
		}
		break;
	case 23://BOSS奖励 
		
		{
			SetJiangLi(10,TRUE);
			RemoveNpc(m_NowNpc);
			g_pMainState->m_Channel.AddNewString(m_TextList[25]);
			g_pMainState->m_Tags.Add(m_TextList[25]);
		}
	case 1002:
		EndFB();
		break;
	default:
		break;
	}
}




void cTaskFB::ProcessCC(int stage)
{
	int lv = g_pCharacter->m_PCData.m_LV;
	switch (stage)
	{
	case 0:
		
		{
			m_Stage =0;
			AddTriggerObj(m_TextList[1], m_TextList[0], 1);
			AddTriggerObjMap(m_TextList[3], 3);
			m_List.resize(1);
			SetNpc(m_List[0],4,m_TextList[5], m_TextList[3], 1075,53,32,1);
			UpdateJob(m_TextList[22]);	
		}
		break;
	case 1:
		g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, -1, "是", "否");
		break;
	case -1:
		if (g_pMainState->m_Dialog.m_retSelect)return;
	case 2:
		
		{
			if (!m_Stage)
			{
				g_pMainState->m_Map.LoadMap(8, 11, m_TextList[3].c_str());
			}
			else
			{
				g_pMainState->m_Map.LoadMap(37, 20, m_TextList[14].c_str());
			}
		}
		break;
	case 3:AddNpc();
		break;
	case 4:
		m_NowNpc = g_pMainState->m_pNowSelect;
		AddTriggerDialog(0, 6); 
		UpdateJob("回答道士的问题,把收集到的木头交给道观", -1, -1, "副本");
		break;
	case 6://车迟收集木头
		
		{
			m_Stage2 = 20;
			RemoveNpc(m_NowNpc);
			m_List2.resize(1);
			SetNpc(m_List2[0],8,m_TextList[4], m_TextList[3], 1119, 87, 116, 1);
			StageSetSameNpc(1077, m_TextList[3], 9, 40, m_TextList[6]);
			
		}
		break;
	case 8:
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			int num=0;
			for (int i = 0; i < 60; i++)
			{
				sItem2& item= g_pCharacter->m_PCData.m_Item[i];
				if (!item.m_Num)continue;
				if (item.GetID() == 56)
				if (item.GetType() == 27)
				{
					num += item.GetNum();
					item.m_Num = 0;
				}
			}
			if (num)
			{
				if (num > m_Stage2)
					num = m_Stage2;
				m_Stage2 -= num;
				for (int i = 0; i < num; i++)
				{
					SetJiangLi(1);
					if (!(rand() % 20))GetItem(27, rand() % 4 + 38, TRUE);
				}
				if (m_Stage2 >= 20)
				{
					ostringstream oss;
					oss << "还需要";
					oss << m_Stage2;
					oss << "个木头";
					m_NowNpc->Talk(oss.str());
				}
				else
				{
					g_pHeroObj->Talk(m_TextList[7]);
					UpdateJob(m_TextList[7]);
					ClearNpc();
					StageSetSameNpc(120,m_TextList[3],12,40,m_TextList[8]);
				}
			}
		}
		break;
	case 9://道士
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			m_NowNpc->Answer(this, 10);
		}
		break;
	case 10:
		
		{
			if (g_pMainState->m_Dialog.m_retSelect == g_pMainState->m_Dialog.m_Question.answer )
			{
				GetItem(27, 56);
			}
			else
			{
				m_NowNpc->Talk(g_pMainState->m_Dialog.GetTrueSelect());
			}
			//道士换地方
			int x, y;
			sMapObjTrigger* pNpc= FindNpcByObj(m_NowNpc);
			g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[3]);
			m_NowNpc->SetXY(x * 20, g_pMainState->m_Map.m_pMap->m_Height - y * 20);
			if (!m_NowNpc)return;
			pNpc->m_Npc.m_x = x;
			pNpc->m_Npc.m_y = y;
			g_pMainState->FindObj();
		}
		break;
	case 12:
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			int enemynum =g_pMainState->AtutoGetEnemyNum();
			sAddPoint addpoint;
			for (int i = 0; i < enemynum; i++)
			{
				AddPetEnemyF(lv * 80, e泡泡, lv, m_TextList[8]);
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(13);
		}
		break;
	case 13:
		
		{
			SetJiangLi(2,0,200,100);
			if (!(rand() % 10))GetItem(27, rand() % 4 + 38, TRUE);
			RemoveNpc(m_NowNpc);
			if (true || !m_List.size())
			{
				ClearNpc();
				AddTriggerDialog(1, 14);
			}
		}
		break;
	case 14:
		
		{
			UpdateJob(m_TextList[12]);
			m_List.resize(3);
			SetNpc(m_List[0],16,m_TextList[9],m_TextList[3],51,62,99,3);
			SetNpc(m_List[1],16,m_TextList[10], m_TextList[3], 51, 72, 103, 3);
			SetNpc(m_List[2],16,m_TextList[11], m_TextList[3], 51, 84, 109, 3);
			Process(3);
		}
		break;
	case 16:
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			AddPCPetEnemyF(lv * 150, e大力金刚, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			for (int i = 0; i < 7; i++)
			{
				AddPCPetEnemyF(lv * 100, (ePetID)(rand() % 30));
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(17);
		}
		break;
	case 17:
		
		{
			SetJiangLi(5);
			if (!(rand() % 20))
			{
				GetItem(27, 5,TRUE);
			}
			RemoveNpc(m_NowNpc);
			int x, y;
			g_pMainState->m_Map.AutoGetPos(x,y,m_TextList[14]);
			if (!m_List.size())
			{
				m_Stage = 1;
				AddTriggerObjMap(m_TextList[14], 3);
				//偷懒 只设计了雷打不动
				m_List.resize(2);
				g_pMainState->m_Map.AutoGetPos(x, y);
				SetNpc(m_List[0], 18, m_TextList[15], m_TextList[14],56,x,y);
				g_pMainState->m_Map.AutoGetPos(x, y);
				SetNpc(m_List[1], 19, m_TextList[16], m_TextList[14], 48, x, y);
				Process(2);
				UpdateJob(m_TextList[13]);
			}
		}
		break;
	case 18://你不动
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
	
			AddPCPetEnemyF(lv * 120, e律法女娲, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			sAddPoint addpoint;
			for (int i = 0; i < 7; i++)
			{
				AddPCPetEnemyF(lv * 90, (ePetID)(rand() % 50));
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(20);
		}
		break;
	case 19://我不动
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			AddPCPetEnemyF(lv * 160, e净瓶女娲, lv+9, eMP_魔王寨, m_NowNpc->m_TrueName.GetString());
			for (int i = 0; i < 4;i++)
			AddPCPetEnemyF(lv * 160, e净瓶女娲, -1, eMP_魔王寨);
			for (int i = 0; i < 5; i++)
				AddPCPetEnemyF(lv * 160, e大力金刚);
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(20);
		}
		break;
	case 20:
		
		{
			RemoveNpc(m_NowNpc);
			SetJiangLi(5);
			if (!m_List.size())
			{
				m_NowNpc->Talk(m_TextList[17]);
				m_List.resize(1);
				int x, y;
				g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[14]);
				SetNpc(m_List[0], 21, m_TextList[18],m_TextList[14],56,20,128,3);
				Process(3);
				UpdateJob(m_TextList[17]);
			}
		}
		break;
	case 21://最终BOSS
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			AddPCPetEnemyF(lv * 180, e超级神虎, lv + 10, eMP_狮驼岭, "虎力大仙");
			AddPCPetEnemyF(lv * 180, e超级神羊, lv + 9, eMP_魔王寨, "羊力大仙");
			AddPCPetEnemyF(lv * 180, e超级灵鹿, lv + 9, eMP_化生寺, "鹿力大仙");
			sAddPoint addpoint;
			ePetID petid;
			for (int i = 0; i < 5; i++)
			{
				switch (rand()%3)
				{
				case 0:petid = e炎魔神; break;
				case 1:petid = e灵鹤; break;
				default:petid = e鬼将;
					break;
				}
				AddPCPetEnemyF(lv * 120, petid);
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(22);
		}
		break;
	case 22:
		
		{
			RemoveNpc(m_NowNpc);
			SetJiangLi(10);
			//宝箱出现
			StageSetSameNpc(1125, m_TextList[14], 23, 20);
			UpdateJob(m_TextList[21], 2);
			g_pHeroObj->Talk("直接完成副本, 不捡宝箱了", this, 1003, "完成", "不,我要捡");
		}
		break;
	case 23:
		
		{
			vector<int> rate;
			rate.resize(5);
			rate[0] = 5;
			rate[1] = 30;
			rate[2] = 25;
			rate[3] = 20;
			rate[4] = 20;
			int rat = rand() % 100;		
			for (int i = 0; i < rate.size(); i++)
			{
				if (rat < rate[i])
				{
					switch (i)
					{
					case 0: 
						switch (rand() % 3)
						{
						case 0:
							SetJiangLiItem(g_pMainState->m_ItemManage.m_LShouJueList[rand() % g_pMainState->m_ItemManage.m_LShouJueList.size()], 40); //兽决
							break;
						case 1:SetJiangLiItem(33, 27);
							break;
						case 2:
							SetJiangLiItem(rand()%6+5, 27);
							break;
						}
						break;
					case 1:SetJiangLiItem(rand() % 17, 29); //宝石
						break;
					case 2:SetJiangLi(5, TRUE, 100, 0, 0);//钱
						break;
					case 3:SetJiangLi(5, TRUE, 0, 0, 100);//经验
						break;
					case 4:SetJiangLiItem(rand()%89,41);//符石
						break;
					}
					break;
				}
				rat -= rate[i];
			}
			RemoveNpc(g_pMainState->m_pNowSelect);
			if (!m_List.size())
			{
				ProcessCC(1002);
			}
		}
		break;
	case 1002:
		EndFB();
		break;
	case 1003:
		if (g_pMainState->m_Dialog.m_retSelect == 0)
		{
			ProcessCC(1002);
		}
		break;
 	}
}

void cTaskFB::GetItem(int type,int id, BOOL needtag,int num)
{
	sItem2 item;
	item.m_Num = num;
	item.Set(type, id);
	g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
	if (needtag)
	{
		ostringstream oss;
		oss << "你得到了";
		oss << item.m_pItemData->m_Name;
		g_pMainState->m_Tags.Add(oss.str());
	}
}

void cTaskFB::ProcessSJ(int stage)
{
	int lv = g_pCharacter->m_PCData.m_LV;
	switch (stage)
	{
	case 0:
		{
			Init();
			m_HuanShu = 0;
			m_Stage = 0;
			g_pMainState->m_TriggerObj.AddTask(m_TextList[1], m_TextList[0], this, 1);
			AddTriggerObjMap(m_TextList[3], 3);
			m_List.resize(1);
			SetNpc(m_List[0],4,m_TextList[5], m_TextList[3], 1050, 59, 47, 1);
			UpdateJob(m_TextList[23]);

		}
		break;
	case 1:
		{
			g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, -2, "是", "否");
		}
		break;
	case -2:
		if (g_pMainState->m_Dialog.m_retSelect)return;
	case 2:
		switch (m_Stage)
		{
		case 0:g_pMainState->m_Map.LoadMap(16, 30, m_TextList[3].c_str()); break;
		case 1:g_pMainState->m_Map.LoadMap(120, 57, m_TextList[7].c_str()); break;
		case 2:g_pMainState->m_Map.LoadMap(69, 51, m_TextList[9].c_str()); break;
		case 3:g_pMainState->m_Map.LoadMap(69, 51, m_TextList[19].c_str()); break;
		}
		break;
	case 3:AddNpc();
		break;
	case 4:
		m_NowNpc = g_pMainState->m_pNowSelect;
		g_pMainState->m_pNowSelect->Talk(m_TextList[6], this, 5, "是", "否");
		break;
	case 5://得到抓鬼任务
		if (!g_pMainState->m_Dialog.m_retSelect)
		{
			//..
			m_List2.resize(1);
			g_pMainState->m_TaskZhuaGui.AutoGetGost(m_List2[0].m_Npc, m_TextList[3]);
			m_List2[0].m_pTask = this;
			m_List2[0].m_Stage = 8;
			int xerr, yerr;
			g_pMainState->m_TaskZhuaGui.GetErrPos(m_List2[0].m_Npc, xerr, yerr);
			ostringstream oss;
			oss << "去#R" << xerr << " " << yerr << "#R附近把#R" << m_List2[0].m_Npc.m_name << "#R抓回来";
			m_NowNpc->Talk(oss.str());
			UpdateJob(oss.str());
			AddTriggerObjMap(m_TextList[3], 6);
			AddNpcOne(&m_List2[0], TRUE);
			g_pMainState->m_InterfaceSmallMap.addNpc(&m_List2[0].m_Npc);
		}
		break;
	case 6:
		AddNpc();
		break;
	case 8:
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			g_pMainState->m_TaskZhuaGui.ReadyToFight(m_List2[0].m_Npc);
		
			AddTriggerFightSuccess(9);
		}
		break;
	case 9:
		RemoveNpc(m_NowNpc);
		SetJiangLi(3);
		m_HuanShu += 1;
		if (true || m_HuanShu == 6)
		{
			m_Stage = 1;

			ProcessSJ(2);
			g_pMainState->m_TaskHuoDong.Initmp();
			std::vector<ePetID> modes =
			{ e程咬金, e空度禅师, e孙婆婆, e菩提祖师, e大大王, e牛魔王,
			e白晶晶, e地藏王, e东海龙王, e镇元大仙, e观音姐姐, e李靖 };

			m_List.resize(12);
			for (int i = 0; i < m_List.size(); i++)
			{
				// m_List[i] = g_pMainState->m_TaskHuoDong.m_List[i];
				m_List[i].m_Npc.Set(g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[i].m_ShiFuName,
					m_TextList[7], modes[i], 0, 0);
				m_List[i].m_pTask = this;
				m_List[i].m_Stage = 10;
				g_pMainState->m_Map.AutoGetPos(m_List[i].m_Npc.m_x, m_List[i].m_Npc.m_y, m_TextList[7]);
			}
			AddTriggerObjMap(m_TextList[7], 6);
			ProcessSJ(6);
			g_pMainState->m_Tags.Add(m_TextList[15]);
			UpdateJob(m_TextList[15]);
			return ;
		}
		UpdateJob(m_TextList[16]);
		break;
	case 10:
		{
			m_NowNpc = g_pMainState->m_pNowSelect;

			if (0)
			{
				int id = m_NowNpc->GetModeID() - 2000;
				sMapObjTrigger* plist = FindNpcByObj(m_NowNpc);
				g_pMainState->m_TaskHuoDong.ReadytoFightmp(*plist, (eMengPai)id);
			}
			else
			{
				g_pMainState->m_TaskHuoDong.ReadytoFightmp(lv, m_NowNpc);
			}
			AddTriggerFightSuccess(11);
		}
		break;
	case 11:
		{
			SetJiangLi(8,TRUE,100,30,150);
			RemoveNpc(m_NowNpc);
			if (true || !m_List.size())
			{
				
				ProcessSJ(-11);
			}
		}
		break;
	case -11:
	{
				m_Stage = 2;
				ProcessSJ(2);
				g_pMainState->m_Tags.Add(m_TextList[8]);
				UpdateJob(m_TextList[8]);
				m_List.resize(1);
				string name;
				int modeid;
				if (-1 == g_pCharacter->m_PCData.m_MengPaiID)g_pCharacter->m_PCData.m_MengPaiID = 0;
				name = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PCData.m_MengPaiID)->m_ShiFuName;
				switch (g_pCharacter->m_PCData.m_MengPaiID)
				{
				case eMP_大唐官府:modeid = 139; break;
				case eMP_化生寺:modeid = 142; break;
				case eMP_女儿村:modeid = 132; break;
				case eMP_方寸山:modeid = 135; break;
				case eMP_狮驼岭:modeid = 143; break;
				case eMP_魔王寨:modeid = 133; break;
				case eMP_盘丝岭:modeid = 136; break;
				case eMP_阴曹地府:modeid = 140; break;
				case eMP_东海龙宫:modeid = 131; break;
				case eMP_五庄观:modeid = 134; break;
				case eMP_普陀山:modeid = 141; break;
				default:  modeid = 138; break;
				}
				m_HuanShu = 0;
				//int x, y;
				
				SetNpc(m_List[0], 12, name, m_TextList[9], modeid, 102, 62, 3);
				AddTriggerObjMap(m_TextList[9], 3);//&m_List[0]);
				AddNpcOne(&m_List[0]);
				m_Stage2 = 0;
	}
		break;
	case 12:
		{
			if (m_Stage2)return;
			m_NowNpc = g_pMainState->m_pNowSelect;
			m_NowNpc->Talk(m_TextList[10], this, 13, "是", "否");
			
		}
		break;
	case 13:
		{
			if (0 != g_pMainState->m_Dialog.m_retSelect)return;
			m_Stage2 = 1;
			int rate = rand() % 100;
			if (false && rate < 30)
			{//要包子
				m_NowNpc->Talk(m_TextList[11]);
				g_pMainState->m_TriggerGive.AddTask(m_NowNpc->m_TrueName.GetString(),0,23,this, 14);
				return;
			}
			else
			{//战斗
				int x, y;
				g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[9]);
				ostringstream oss;
				oss << m_TextList[12];
				oss << x << " " << y;
				oss << m_TextList[13];
				m_NowNpc->Talk(oss.str());
				UpdateJob(oss.str());
				m_List2.resize(1);
				SetNpc(m_List2[0], 15, m_TextList[14], m_TextList[9], rand() % 12 + 2000, x, y);
				AddNpcOne(&m_List2[0],TRUE);
				g_pMainState->m_InterfaceSmallMap.addNpc(&m_List2[0].m_Npc);
			}
		}
		break;
	case 14:
		{
			SetJiangLi(2, TRUE, 50);
			m_Stage2 = 0;
		}
		break;
	case 15:
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			cPetData* pPet;
			pPet=AddPCEnemyF(lv *120, m_NowNpc->GetModeID(), 0, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			pPet->m_DamagePercent.d2 = 50;
			int enemynum =  g_pMainState->AtutoGetEnemyNum()-1;
			for (int i = 0; i < enemynum; i++)
			{
				switch (rand() % 4)
				{
				case 0:
					pPet = AddPCPetEnemyF(-lv * 10, e蛤蟆精);
					pPet->m_DamagePercent.d2 = 90;
					pPet->m_DamageAddPercentMagic.d2 = 90;
					break;
				case 1:
					pPet = AddPCPetEnemyF(-lv*10, e蛤蟆精);
					pPet->m_DamagePercent.d2 = 90;
					pPet->m_DamageAddPercentMagic.d2 = 90;
					break;
				case 2:
					pPet = AddPCPetEnemyF(lv*100, e花妖);
					pPet->m_DamagePercent.d2 = 80;
					break;
				case 3:
					pPet = AddPCPetEnemyF(lv*100, e蝴蝶仙子);
					pPet->m_DamagePercent.d2 = 80;
					break;
				}
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(16);
		}
		break;
	case 16:
		{
			   UpdateJob(m_TextList[8]);
			RemoveNpc(m_NowNpc);
			SetJiangLi(3, TRUE);
			m_Stage2 = 0;
			m_HuanShu += 1;
			if (true || 8 == m_HuanShu)
			{
				m_Stage = 3;
				m_HuanShu = 0;
				AddTriggerObjMap(m_TextList[19], 3);
				
				g_pMainState->m_Tags.Add(m_TextList[17]);
				UpdateJob(m_TextList[18]);

				m_List2.resize(1);
				SetNpc(m_List2[0], 18, m_TextList[20], m_TextList[19], 1120, 63, 113);

				vector<int> modelist;
				modelist.resize(4);
				for (int i = 0; i < 4; i++)
					modelist[i] = i + 63;
				StageSetSameNpc(modelist, m_TextList[19], 17, 20);


			
				AddTriggerGive(m_TextList[20], 27, 57, 20,FALSE);
				AddTriggerGive(m_TextList[20], 27, 58, 21,FALSE);
				ProcessSJ(2);
				m_Stage2 = 50;
			}
		}
		break;
	case 17://冬 战斗
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			AddPCPetEnemyF(lv * 140,(ePetID)m_NowNpc->GetModeID(),-1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			int enemynum =  g_pMainState->AtutoGetEnemyNum()-1;
			ePetID ptid;
			for (int i = 0; i < enemynum; i++)
			{
				switch (rand()%4)
				{
				case 0:ptid = e机关兽;
				case 1:ptid = e机关鸟;
				case 2:ptid = e阴阳伞;
					default:ptid = e蛤蟆精;
				}
				AddPCPetEnemyF(lv * 100, ptid);
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(19);
		}
		break;
	case 18:
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			ostringstream oss;
			oss << "当前进度#R";
			oss << m_HuanShu <<"/"<< m_Stage2;
			oss << "#R";
			g_pMainState->m_pNowSelect->Talk(oss.str());
		}
		break;
	case 19:
		{
			GetItem(27, 57 + rand() % 2, TRUE); 
			RemoveNpc(m_NowNpc);
		}
		break;
	case 20:
	case 21:
		{
			if (20==stage)
			m_HuanShu += 20;
			else m_HuanShu += 30;
			SetJiangLi(3, TRUE);


			int mode2;
			switch (m_HuanShu / 10)
			{
			case 0:mode2 = 1120; break;
			case 1:mode2 = 1121; break;
			case 2:mode2 = 1122; break;
			case 3:mode2 = 1123; break;
			default: mode2 = 1124; break;
			}
			if (mode2 != m_List2[0].m_Npc.m_modeid)
			{
				m_List2[0].m_Npc.m_modeid = mode2;
				RemoveNpc(&m_List2[0].m_Npc, FALSE);
				g_pMainState->m_Map.AddNpc(&m_List2[0],TRUE);
			}
			if (m_HuanShu < 50)
			{
				AddTriggerGive(m_TextList[20], 27, 57, 20, FALSE);
				AddTriggerGive(m_TextList[20], 27, 58, 21, FALSE);
			}
			else
			{				
				m_NowNpc = 0;
				// m_NowNpc->Talk(m_TextList[21]);
				g_pHeroObj->Talk(m_TextList[21] + "\n(所以你要直接退出副本吗)?", this, 1003, "是", "否");
				ClearNpc();

				g_pMainState->m_InterfaceSmallMap.clear();
				StageSetSameNpc(1125, m_TextList[19],22,25);

				UpdateJob(m_TextList[22]);

			}
		}
		break;
	case 22:
		{
			int rat = rand() % 100;
			if (rat < 5)
			{
				SetJiangLiItem(33, 27);
			}
			else
			if (rat < 15)
			{
				SetJiangLiItem(38 + rand() % 4, 27);
			}
			if (rat < 25)
			{
				SetJiangLiItem(rand()%17,29);
			}
			else
			{
				if(rand()%2)
				SetJiangLi(5, TRUE,100,0,0);
				else SetJiangLi(5, TRUE, 0, 0);
			}
			RemoveNpc(g_pMainState->m_pNowSelect);
			if (!m_List.size())
			{
				ProcessSJ(1002);
			}
			break;
		}
	case 1002:
		EndFB();
		break;
	case 1003:
		if (g_pMainState->m_Dialog.m_retSelect == 0)
		{
			ProcessSJ(1002);
		}
		break;
	}
}


void cTaskFB::ProcessSM(int stage)
{
	int lv = g_pCharacter->m_PCData.m_LV;
	switch (stage)
	{
	case 0:
		{
			m_Stage = 0;
			AddTriggerObj(m_TextList[1], m_TextList[0], 1);
			AddTriggerObjMap(m_TextList[3], 4);
			StageSetSameNpc(2001, m_TextList[3], 5, 15,m_TextList[8]);
			StageSetSameNpc2(1125, m_TextList[3], -5, 23 + 10, m_TextList[14]);
		}
		break;
	case 1:
		{
			g_pMainState->m_pNowSelect->Talk(m_TextList[2], this, 2, "是", "否");
		}
		break;
	case 2:
		if (g_pMainState->m_Dialog.m_retSelect)return;
	case 3:
		switch (m_Stage)
		{
		case 0:
			g_pMainState->m_Map.LoadMap(24, 31, m_TextList[3].c_str());
			UpdateJob(m_TextList[9]);
			break;
		case 1:
			g_pMainState->m_Map.LoadMap(45, 25, m_TextList[4].c_str());
			UpdateJob(m_TextList[12]);
			break;
		case 2:
			g_pMainState->m_Map.LoadMap(8, 11, m_TextList[5].c_str());
			break;
		case 3:
			g_pMainState->m_Map.LoadMap(65, 56, m_TextList[6].c_str());
			break;
		case 4:
			g_pMainState->m_Map.LoadMap(8, 11, m_TextList[7].c_str());
			break;
		}
		break;
	case 4:AddNpc(); break;
	case -5:
		RemoveNpc(g_pMainState->m_pNowSelect);
		if (m_List2.size() > 30)
		{
			switch (rand() % 3)
			{
			case 0:SetJiangLi(1, TRUE, 50, 0, 0); break;
			case 1:SetJiangLi(1, TRUE, 0, 0, 50); break;
			default:
				g_pCharacter->m_PCData.m_HP /= 2;
				g_pCharacter->m_PCData.m_MP /= 2;
				g_pMainState->m_PCHead.UpdatePcHp();
				g_pMainState->m_PCHead.UpdatePcMp();
				AddTag(m_TextList[15]);
				break;
			}
		}
		else
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			int enemynum = g_pMainState->AtutoGetEnemyNum();
			for (int i = 0; i < enemynum; i++)
			{
				AddPCPetEnemyF(lv * 65, (ePetID)(rand() % 40));
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(-6);
		}
		if (!(m_List.size()) && (!m_List2.size()))
		{
			m_Stage = 1;
			AddTriggerObjMap(m_TextList[4], 4);
			m_List2.resize(0);
			m_List.resize(1);
			SetNpc(m_List[0], 7, m_TextList[10], m_TextList[4], 1084, 48, 31);
			m_HuanShu = 1;
			ProcessSM(3);
		}
		break;
	case -6://宝箱战斗胜
		{
			RemoveNpc(m_NowNpc);
			SetJiangLi(1);
			if (true || !(m_List.size()) && (!m_List2.size()))
			{
				m_Stage = 1;
				//////////////////////////////////////////////////////////////////////////
				m_Stage2 = 0;
				//////////////////////////////////////////////////////////////////////////
				AddTriggerObjMap(m_TextList[4], 4);
				m_List2.resize(0);
				m_List.resize(1);
				SetNpc(m_List[0], 7, m_TextList[10], m_TextList[4], 1084, 48, 31);
				m_HuanShu = 1;
				ProcessSM(3);
			}
		}
		break;
	case 5://玄武仙人
		m_NowNpc = g_pMainState->m_pNowSelect;
		m_NowNpc->Answer(this, 6);
		break;
	case 6:

		{
			if (g_pMainState->m_Dialog.m_retSelect == g_pMainState->m_Dialog.m_Question.answer)
			{
				RemoveNpc(m_NowNpc);
				SetJiangLi(2,TRUE,0);
			}
			else
			{
				m_NowNpc->Talk(g_pMainState->m_Dialog.GetTrueSelect());
			}
			if (!(m_List.size())&& (!m_List2.size()))
			{
				m_Stage = 1;
				m_Stage2 = 0;
				AddTriggerObjMap(m_TextList[4], 4);
				m_List2.resize(0);
				m_List.resize(1);
				SetNpc(m_List[0], 7, m_TextList[10], m_TextList[4], 1084,48,31);
				m_HuanShu = 1;
				ProcessSM(3);
			}
		}
		break;
	case 7:
	
		{
			if (m_Stage2>0)
			{
				g_pMainState->m_pNowSelect->Talk(m_TextList[24]); 
				return;
			}
			g_pMainState->m_pNowSelect->Talk(m_TextList[11]);
			m_Stage2 = 1;
			sItem2 item;
			item.m_Num = 1;
			item.Set(28, 21);
			int x, y;
			g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[4]);
			item.m_Property.resize(2);
			item.m_Property[0]=x;
			item.m_Property[1]=y;
			g_pMainState->m_InterfaceItem.GetItem(g_pMainState->m_HeroID, &item);
		}
		break;
	case 8://挖宝
	
		{
			if (g_pMainState->m_Map.m_MapName != m_TextList[4])
			{

				return;
			}
			sItem2* pItem = g_pCharacter->m_PCData.GetItem(g_pMainState->m_InterfaceItem.m_NowSelect);
			if (abs(g_pMainState->m_InterfaceDoor.m_HeroX -pItem->m_Property[0])<7)
			if (abs(g_pMainState->m_InterfaceDoor.m_HeroY - pItem->m_Property[1])<7)
			{
				m_Stage2 = 0;
				int rat = rand() % 100;
				if (m_HuanShu < 2/*rat < 20*/)
				{
					SetJiangLi(2,TRUE);
					m_HuanShu += 1;
					if (m_HuanShu > 7)
					{
						m_HuanShu = 0;
						AddTriggerObjMap(m_TextList[5], 4);
						m_Stage = 2;
						m_List.resize(8);
						int x, y;
						g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[5]);
						for (int i = 0; i < 8; i++)
						{
							g_pMainState->m_Map.AutoGetPos(x, y);
							SetNpc(m_List[i], 12, m_TextList[16 + i], m_TextList[5], 41, x, y);
						}
						UpdateJob(m_TextList[25]);
						Process(3);
						AddTag(m_TextList[25]);
					}
				}
				else
				{
					Process(9);	
					UpdateJob(m_TextList[12]);
				}
				pItem->m_Num = 0;
				return;
			}
			ostringstream oss;
			oss << "地点:" << pItem->m_Property[0] << " " << pItem->m_Property[1];
			AddTag(oss.str());
		}
		break;
	case 9: //挖宝战斗
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;

			AddPCPetEnemyF(lv * 10000, e雨师, -1, eMP_随机, m_TextList[13]);
			for (int i = 0; i < 5; i++)
			{
				AddPCPetEnemyF(lv * 65, (ePetID)(rand() % 40));
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightTurn(10);
			AddTriggerFightSuccess(11);
		}
		break;
	case 10:
	
		{
			if (!g_pMainState->m_FightList[10].isLive)g_pMainState->m_pFightState->EscapeFight();
			int num=  g_pMainState->GetLiveNum(10, 20);
			cAttackAI& ai= g_pMainState->m_AI.m_AttackAI;
			if (1==num)
			{
				g_pMainState->m_pFightState->SuccessFight();
			}
			else
			{
				ai.Def(10);
			}
		}
		break;
	case 11:
	
		{
			SetJiangLi(3,TRUE);
			m_HuanShu += 1;
			if (true || m_HuanShu >7)
			{
				m_HuanShu = 0;
				AddTriggerObjMap(m_TextList[5], 4);
				m_Stage = 2;
				
				int x, y;
				g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[5]);
				m_List.resize(4);
				for (int i = 0; i < 4; i++)
				{
					g_pMainState->m_Map.AutoGetPos(x, y);
					SetNpc(m_List[i], 12, m_TextList[16 + i], m_TextList[5], 41, x, y);
				}
				m_List2.resize(4);
				for (int i = 0; i < 4; i++)
				{
					g_pMainState->m_Map.AutoGetPos(x, y);
					SetNpc(m_List2[i], 12, m_TextList[20 + i], m_TextList[5], 41, x, y);
				}
				UpdateJob(m_TextList[25]);
				Process(3);
				AddTag(m_TextList[25]);
			}
		}
		break;
	case 12:
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;

			AddPCPetEnemyF(lv * 100, (ePetID)(m_NowNpc->GetModeID()), -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
			cPetData* Pet;
			for (int i = 0; i < 2; i++)
			{
				Pet = AddPCPetEnemyF(0, e星灵仙子, -1, eMP_随机, m_NowNpc->m_TrueName.GetString());
				Pet->m_DamageAdd.d2 = 80;
				Pet->m_DamageAddMagic.d2 = 80;
			}
			for (int i = 0; i < 5; i++)
			{
				AddPCPetEnemyF(lv * 60, e如意仙子);
			}
			SetMusicFB();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(13);
		}
		break;
	case 13:

	{
			   BOOL find = FALSE;
			   string name = m_NowNpc->m_TrueName.GetString();
			   for (int i = 0; i < m_List.size(); i++)
			   {
				   if (name == m_List[i].m_Npc.m_name)
				   {
					   if (i == 0)
					   {
						   RemoveNpc(m_NowNpc);
						   find = TRUE;
						   break;
					   }
				   }
			   }
			   if (!find)
			   for (int i = 0; i < m_List2.size(); i++)
			   {
				   if (name == m_List2[i].m_Npc.m_name)
				   {
					   if (i == 0)
					   {
						   RemoveNpc(m_NowNpc);
						   find = TRUE;
						   break;
					   }
				   }
			   }
			   if (!find)
			   if ((!m_List.size()) && (!m_List2.size()))
			   {

			   }
			   // else return;
	}
	case -13:
			
			{//白虎门结束
				m_Stage = 3;
				AddTriggerObjMap(m_TextList[6], 4);
				m_List.resize(23);
				m_List2.resize(4);
				int x, y;
				g_pMainState->m_Map.AutoGetPos(x, y, m_TextList[6]);
				for (int i = 0; i < 4; i++)
				{
					g_pMainState->m_Map.AutoGetPos(x, y);
					SetNpc(m_List2[i],14,m_TextList[3+i] ,m_TextList[6],49,x,y);
				}
				for (int i = 0; i < 23; i++)
				{
					g_pMainState->m_Map.AutoGetPos(x, y);
					if (i==14)//BUG 两个玄武门
						SetNpc(m_List[i], 14, m_TextList[26 + 15], m_TextList[6], 49, x, y);
					else
						SetNpc(m_List[i], 14, m_TextList[26 + i], m_TextList[6], 49, x, y);
				}
				UpdateJob(m_TextList[53]);
				g_pMainState->m_Tags.Add(m_TextList[53]);
				Process(3);
			}
		break;
	case 14:
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			AddPCPetEnemyF(lv * 100, (ePetID)(m_NowNpc->GetModeID()), lv+5, eMP_随机, m_NowNpc->m_TrueName.GetString());
			cPetData* Pet;
			for (int i = 0; i < 2; i++)
			{
				Pet = AddPCPetEnemyF(lv*60, e星灵仙子);
				Pet->m_DamageAdd.d2 = 30;
				Pet->m_DamageAddMagic.d2 = 30;
			}
			sAddPoint addpoint;
			for (int i = 0; i < 5; i++)
			{
				AddPCPetEnemyF(lv*70, e天兵);
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(15);
		}
		break;
	case 15:
		
		{
			RemoveNpc(m_NowNpc);
			SetJiangLi(3);
			if (true || !m_List2.size())
			{
				ClearNpc();
				m_List.resize(1);
				SetNpc(m_List[0],16,m_TextList[50],m_TextList[6],2000,65,57,1);
				m_List[0].m_Npc.SetRanse(0,4,3);
				m_List[0].m_Npc.weapontype = 0;
				m_List[0].m_Npc.weaponid = 24;
				AddNpc();
				UpdateJob(m_TextList[51]);
				AddTag(m_TextList[51]);
			}
		}
		break;
	case 16://神密剑客  0 4 3 0
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			
			cPetData* Pet;
			Pet= AddPCEnemyF(lv * 200, 0, 0, lv + 10, eMP_大唐官府, m_NowNpc->m_TrueName.GetString(), m_List[0].m_Npc.weapontype, m_List[0].m_Npc.weaponid);
			Pet->m_RanSe.m_ranse[0].Set(2, 3, 3, 0);
			g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
			
			for (int i = 0; i < 7; i++)
			{
				Pet = AddPCEnemyF(lv * 120, 0, 0, lv + 10, eMP_大唐官府, "剑客影子", m_List[0].m_Npc.weapontype, m_List[0].m_Npc.weaponid);
				Pet->m_RanSe.m_ranse[0].Set(2, 3, 3, 0);
				g_pMainState->m_ColorManage.Give2(&Pet->m_RanSe.m_ranse[0], 2000);
			}
			g_StateType = STATE_FIGHT;
			SetMusicFB();
			AddTriggerFightSuccess(17);
		}
		break;
	case 17://
		
		{
			m_Stage = 4;
			m_List[0].m_Npc.weaponid = -1;
			m_List[0].m_Npc.weapontype = -1;
			m_List.resize(50);
			StageSetSameNpc(1125, m_TextList[7], 18, 40, m_TextList[14]);
			AddTriggerObjMap(m_TextList[7],4);
			Process(3);
			SetJiangLi(10);
			AddTag(m_TextList[52]);
			UpdateJob(m_TextList[52]);
			g_pHeroObj->Talk("直接完成副本, 不捡宝箱了", this, 1003, "完成", "不,我要捡");
		}
		break;
	case 18:
		
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			cJiangLi jiangli;
			jiangli.SetBaoShi(20);//宝石
			jiangli.Add(3,27,5,3); //66
			jiangli.Add(33, 27, 4);//彩果
			jiangli.AddLShouJue(2);//低兽决
			jiangli.Add(38, 27,10, 4);//强化石
			jiangli.SetExp(30,8);
			jiangli.SetMoeny(25,8);
			jiangli.AutoGetJiangLi();
			RemoveNpc(m_NowNpc);
			if (m_List.size()<2)
				Process(1002);
		}
		break;
	case 1002:
		EndFB();
		break;
	case 1003:
		if (g_pMainState->m_Dialog.m_retSelect == 0)
		{
			ProcessSM(1002);
		}
		break;
	}
}

void cTaskFB::AddTriggerDialog(int id, int ret)
{
	ostringstream oss;
	oss << m_FBID;
	g_pMainState->m_TriggerDialog.AddTaskFB(oss.str(), id, this, ret);
}

void cTaskFather::SetNpc(sMapObjTrigger& data, int ret, string name, string map, int modeid, int x, int y, int direction/*=-1*/)
{
	data.m_Npc.Reset();
	data.m_Npc.Set(name, map, modeid, x, y, direction);
	data.m_Stage = ret;
	data.m_pTask = this;
}

sMapObjTrigger* cTaskFB::FindNpcByObj(cObj* p)
{
	int x = p->GetX()/20;
	int y = (g_pMainState->m_Map.m_pMap->m_Height - p->GetY()) / 20;
	int modeid = p->GetModeID();

	for (int i = 0; i < m_List.size(); i++)
	{
		if (m_List[i].m_Npc.m_x==x)
		if (m_List[i].m_Npc.m_y == y)
		if (m_List[i].m_Npc.m_modeid == modeid)
		{
			return &m_List[i];
		}
	}
	for (int i = 0; i < m_List2.size(); i++)
	{
		if (m_List2[i].m_Npc.m_x == x)
		if (m_List2[i].m_Npc.m_y == y)
		if (m_List2[i].m_Npc.m_modeid == modeid)
		{
			return &m_List2[i];
		}
	}
	return 0;
}

void cTaskFB::ClearNpc()
{
	g_pMainState->m_TaskNormal.m_pNpc = 0;
	if (g_pMainState->m_pNowSelect)
	{
		g_pMainState->m_pNowSelect->SetShine(FALSE);
		g_pMainState->m_pNowSelect = 0;
	}
	g_pMainState->m_Map.RemoveAllNpc();
	m_List2.clear();
	m_List.clear();
	g_pMainState->FindObj();
}
void cTaskFB::StageSetSameNpc(vector<int> modid, string mapname, int ret, int num, string name)
{
	m_List.resize(num);
	int x, y;
	g_pMainState->m_Map.AutoGetPos(x, y, mapname);
	for (int i = 0; i < m_List.size(); i++)
	{
		g_pMainState->m_Map.AutoGetPos(x, y);
		SetNpc(m_List[i], ret, name, mapname, modid[rand() % modid.size()], x, y);
	}
	if (g_pMainState->m_Map.m_MapName == mapname)
	{
		AddNpc();
	}
}
void cTaskFB::StageSetSameNpc(int modid, string mapname, int ret, int num, string name)
{
	vector<int>  mod2;
	mod2.push_back(modid);
	StageSetSameNpc(mod2,mapname,ret,num,name);
}
void cTaskFB::StageSetSameNpc2(vector<int> modid, string mapname, int ret, int num, string name)
{
	m_List2.resize(num);
	int x, y;
	g_pMainState->m_Map.AutoGetPos(x, y, mapname);
	for (int i = 0; i < m_List2.size(); i++)
	{
		g_pMainState->m_Map.AutoGetPos(x, y);
		SetNpc(m_List2[i], ret, name, mapname, modid[rand() % modid.size()], x, y);
	}
	if (g_pMainState->m_Map.m_MapName == mapname)
	{
		AddNpc();
	}
}
void cTaskFB::StageSetSameNpc2(int modid, string mapname, int ret, int num, string name)
{
	vector<int>  mod2;
	mod2.push_back(modid);
	StageSetSameNpc2(mod2, mapname, ret, num, name);
}

void cTaskFB::EndFB()
{
	g_pMainState->m_Tags.Add("副本结束了");
	g_pMainState->m_Map.LoadMap(485, 144, "长安城");
	g_pMainState->m_Job.ReMoveJob(this);
	RemoveTriggerObjMap();
	RemoveTriggerObj();
	m_List.clear();
	m_List2.clear();
	m_FBID = -1;
	if (m_pEnd)
	{
		cTaskFather* p = m_pEnd;
		m_pEnd = 0;
		p->Process(m_Ret);
	}

}

void cTaskFB::SetTask(cTaskFather* p, int ret)
{
	m_pEnd = p; 
	m_Ret = ret; 
}

void cTaskFB::SetMusicFB()
{
	string name;
	switch (rand()%2)
	{
	case 0:
		name="战斗_任务";
		break;
	default:
		name = "战斗_任务2";
		break;
	}
	SetMusic(name);
}



BOOL cTaskFriend::Process(int stage)
{
	switch (stage)
	{
	case 0:
	
		{
			g_pMainState->m_Friend.JuanZeng(g_pMainState->m_YingHang.m_ShuRu.m_num);
		}
		break;
	case 1:
		
		{
			g_pMainState->m_Friend.UnJuanZeng(g_pMainState->m_YingHang.m_ShuRu.m_num);
		}
	default:
		break;
	}
	return TRUE;
}



BOOL cObjTrigger::Process(string name)
{
	int num = m_datalist.size();
	if (!num)return FALSE;
	for (int i = 0; i < num; i++)
	{
		if (0 == m_datalist[i].m_mapname.compare(g_pMainState->m_Map.m_MapName))
		{
			if (0==m_datalist[i].m_name.compare(name))
			{
				m_datalist[i].m_pTask->Process(m_datalist[i].m_Stage);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL cObjTrigger::AddTask(string name, string mapname, cTaskFather* ptask, int stage, BOOL bHuChi)
{
	if (bHuChi)
	{
		int num = m_datalist.size();
		for (int i = 0; i < num; i++)
		{
			if (m_datalist[i].m_pTask->m_type == ptask->m_type)
			{
				m_datalist[i].m_Stage = stage;
				m_datalist[i].m_name = name;
				m_datalist[i].m_mapname = mapname;
				return FALSE;
			}
		}
	}
	sObjTrigger task;
	task.m_pTask = ptask;
	task.m_Stage = stage;
	task.m_name = name;
	task.m_mapname = mapname;
	m_datalist.push_back(task);
	return TRUE;
}

void cObjTrigger::ReMove(int i)
{
	m_datalist.erase(m_datalist.begin() + i);
}

void cObjTrigger::ReMove(cTaskFather* pTask)
{
	for (int i = 0; i < m_datalist.size(); i++)
	{
		if (pTask->m_type == m_datalist[i].m_pTask->m_type)
		{
			ReMove(i);
			return ReMove(pTask);
		}
	}
}

void cObjTrigger::Save(ofstream& File)
{
	File << "\n";
	File << m_datalist.size() << " ";
	for (int i = 0; i < m_datalist.size(); i++)
	{
		File << m_datalist[i].m_pTask->m_type << " ";
		File << m_datalist[i].m_pTask->m_HuanShu << " ";
		File << m_datalist[i].m_Stage << "\n";
		File << m_datalist[i].m_name << "\n";
		File << m_datalist[i].m_mapname << "\n";
	}
	File << "\n";
}

void cObjTrigger::Load(ifstream& File)
{
	m_datalist.clear();
	int num;
	File >> num;
	if (!num)return;
	int type;
	int huanshu;
	m_datalist.resize(num);
	
	for (int i = 0; i < num; i++)
	{
		cObjTrigger::sObjTrigger& data=m_datalist[i];
		File >> type;
		File >> huanshu;
		File >> data.m_Stage;
		data.m_pTask = g_pMainState->FindTaskByID(type);
		data.m_pTask->m_HuanShu = huanshu;
		getline(File, data.m_name);
		getline(File, data.m_name);
		getline(File, data.m_mapname);
	}
}

BOOL cMapObjTrigger::AddTask(cTaskFather* ptask, int stage, sNpc Npc ,BOOL bHuChi)
{	
	int num = m_datalist.size();
	if (bHuChi)
	for (int i = 0; i < num; i++)
	{
		if (m_datalist[i].m_pTask)
		if (m_datalist[i].m_pTask->m_type == ptask->m_type)
		{
			if (m_datalist[i].m_Npc.m_mapname == Npc.m_mapname)
			{
				m_datalist[i].m_Npc = Npc;
				m_datalist[i].m_Stage = stage;
				return FALSE;
			}
		}
	}
	sMapObjTrigger data;
	data.m_pTask = ptask;
	data.m_Stage = stage;
	data.m_Npc = Npc;
	m_datalist.push_back(data);
	return TRUE;
}

BOOL cMapObjTrigger::AddTask(cTaskFather* ptask, int stage, string mapname,BOOL bHuChi)
{
	sNpc npc;
	npc.m_mapname = mapname;
	return AddTask(ptask, stage, npc,bHuChi);
}

void cMapObjTrigger::AddTask(sMapObjTrigger& target)
{
	for (int i = 0; i < m_datalist.size(); i++)
	{
		if(m_datalist[i].m_Npc.m_x==target.m_Npc.m_x)
		if (m_datalist[i].m_Npc.m_y == target.m_Npc.m_y)
		if (m_datalist[i].m_Npc.m_name == target.m_Npc.m_name)
		if (m_datalist[i].m_Npc.m_mapname == target.m_Npc.m_mapname)
		{
			return;
		}
	}
	m_datalist.push_back(target);
	if (g_pMainState->m_Map.m_MapName == target.m_Npc.m_mapname)
	{
		g_pMainState->m_Map.AddNpc(&target, TRUE);
	}

}

BOOL cMapObjTrigger::Process()
{
	int num = m_datalist.size();
	if (!num)return FALSE;
	BOOL bTrigger;
	for (int i = 0; i < num; i++)
	{
		if (i < m_datalist.size())
		{
			bTrigger = FALSE;
			if (m_datalist[i].m_Npc.m_mapname == "无")bTrigger = TRUE;
			if (m_datalist[i].m_Npc.m_mapname == g_pMainState->m_Map.m_MapName)bTrigger = TRUE;
			if (bTrigger)
			{
				if (m_datalist[i].m_Npc.m_modeid>-1)
				{
					g_pMainState->m_Map.AddNpc(&m_datalist[i]);
				}
				else
				{
					m_datalist[i].m_pTask->Process(m_datalist[i].m_Stage);
				}
			}
		}
		else return TRUE;
	}
	return TRUE;
}

void cMapObjTrigger::ReMove(int i)
{
	if (m_datalist.size())
	m_datalist.erase(m_datalist.begin() + i);
}
void cMapObjTrigger::ReMove(cTaskFather* pTask,int ret)
{
	for (int i = 0; i < m_datalist.size(); i++)
	if (m_datalist[i].m_pTask == pTask)
	{
		if (ret == -1)
		{
			ReMove(i);
			return ReMove(pTask,ret);
		}
		else
		{
			if (m_datalist[i].m_Stage == ret)
			{
				ReMove(i);
				return;
			}
		}
	}
}

void cMapObjTrigger::ReMove(cTaskFather* pTask, string mapname)
{
	for (int i = 0; i < m_datalist.size(); i++)
	if (m_datalist[i].m_pTask == pTask&&m_datalist[i].m_Npc.m_mapname==mapname)
	{
		ReMove(i);
		return;
	}
}

void cMapObjTrigger::ReMove(cTaskFather* pTask, int x, int y)
{
	for (int i = 0; i < m_datalist.size(); i++)
	if (m_datalist[i].m_pTask == pTask)
	{
		if (m_datalist[i].m_Npc.m_x == x&&m_datalist[i].m_Npc.m_y == y)
		{
			ReMove(i);
			return;
		}
	}
}

void cMapObjTrigger::Save(ofstream& File)
{
	File << "\n";
	File << "地图trigger"<<" ";
	File << m_datalist.size() << " ";;
	for (int i = 0; i < m_datalist.size(); i++)
	{
		sMapObjTrigger& li = m_datalist[i];
		li.Save(File);
	}
	File << "\n";
}

void cMapObjTrigger::Load(ifstream& File)
{
	m_datalist.clear();
	string dustbin;
	int num;
	File >> dustbin ;
	while (dustbin != "地图trigger")
		ERRBOX;
	File >> num;
	if (!num)return;
	m_datalist.resize(num);
	for (int i = 0; i < m_datalist.size(); i++)
	{
		sMapObjTrigger& li = m_datalist[i];
		li.Load(File);
	}
}

sMapObjTrigger* cMapObjTrigger::FindByName(string name)
{
	int num = m_datalist.size();
	for (int i = 0; i < num; i++)
	{
		if (0 == (m_datalist[i].m_Npc.m_name).compare(name))
		{
			return &m_datalist[i];
		}
	}
	return 0;
}



BOOL cLvTrigger::AddTask(cTaskFather* ptask, int stage, int lv)
{
	int num = m_datalist.size();
	for (int i = 0; i < num; i++)
	{
		if (m_datalist[i].m_pTask->m_type == ptask->m_type)
		{
			m_datalist[i].lv = lv;
			m_datalist[i].m_Stage = stage;
			return TRUE;
		}
	}
	sLvTrigger data;
	data.lv = lv;
	data.m_pTask = ptask;
	data.m_Stage = stage;
	m_datalist.push_back(data);
	return TRUE;
}

BOOL cLvTrigger::Process()
{
	int num = m_datalist.size();
	int i = 0;
	for (; i < num; i++)
	{
		if (g_pCharacter->m_PCData.m_LV >= m_datalist[i].lv)
		{
			int stage = m_datalist[i].m_Stage;
			cTaskFather* ptask = m_datalist[i].m_pTask;
			m_datalist.erase(m_datalist.begin()+i);
			ptask->Process(stage);
			break;
		}
	}
	if (i < num)
		return Process();
	return TRUE;
}

void cLvTrigger::ReMove(int i)
{
	if (m_datalist.size())
		m_datalist.erase(m_datalist.begin() + i);
}

void cLvTrigger::ReMove(cTaskFather* pTask)
{
	for (int i = 0; i < m_datalist.size(); i++)
		if (m_datalist[i].m_pTask == pTask)ReMove(i);
}

void cLvTrigger::Save(ofstream& File)
{
	File << "\n";
	File << m_datalist.size() << " ";;
	for (int i = 0; i < m_datalist.size(); i++)
	{
		File <<m_datalist[i].m_pTask->m_type << " ";
		File <<m_datalist[i].m_pTask->m_HuanShu << " ";
		File <<m_datalist[i].m_Stage << " ";
		File <<m_datalist[i].lv << " ";
	}
	File << "\n";
}

void cLvTrigger::Load(ifstream& File)
{
	int num;
	File >> num;
	m_datalist.resize(num);
	int type;
	int huanshu;
	for (int i = 0; i < num; i++)
	{
		File >> type;
		File >> huanshu;
		File >> m_datalist[i].m_Stage;
		m_datalist[i].m_pTask = g_pMainState->FindTaskByID(type);
		m_datalist[i].m_pTask->m_HuanShu = huanshu;
		File >> m_datalist[i].lv;
	}
}

BOOL cDialogTrigger::AddTaskFB(string path, int id, cTaskFather* ptask, int stage)
{
	string path1 = g_strMediaPath;
#if ccc_m5
	path1+="任务//副本//";
#else
	path1 += "副本//";
#endif
	path1 += path;
	path1 += "对话.txt";
	AddTask(path1, id, ptask, stage);
	return TRUE;
}
BOOL cDialogTrigger::sDialogTrigger::AddTaskOriginal(int mode, cTaskFather* ptask, int stage,ifstream& File)
{
	m_Mode = mode;
	int textnum;
	File >> textnum;
	if (0 == textnum)return FALSE;
	m_DialogList.resize(textnum);
	string dustbin;
	getline(File, dustbin);
	for (int i = 0; i < textnum; i++)
	{
		getline(File, m_DialogList[i].name);
#if ccc_m5
		if (m_DialogList[i].name == "主角")
			m_DialogList[i].name = g_pCharacter->m_PCData.m_Name;
#endif
		getline(File, m_DialogList[i].context);
	}
	m_pTask = ptask;
	m_Stage = stage;
	m_Nowtext = 0;
	return TRUE;
}
BOOL cDialogTrigger::AddTask(string path,int id, cTaskFather* ptask, int stage)
{
	ifstream File;
	File.open(path);
	int tag;
	string name;
	string text;
	int textnum;
	File >> tag;
	while (tag != id)
	{
		File >> m_Mode;
		File >> textnum;
		
		getline(File, text);
		for (int i = 0; i < textnum; i++)
		{
			getline(File, name);
			getline(File, text);
		}
		File >> tag;
	}
	File >> m_Mode;
	switch (m_Mode)
	{
	case 1:
		m_datalist[0].AddTaskOriginal(m_Mode, ptask, stage, File);
		return Process(0);
	case 2:
		m_datalist[1].AddTaskOriginal(m_Mode, ptask, stage, File);
		return Process(1);
	default:
		ERRBOX;
		break;
	}
	return FALSE;
}

BOOL cDialogTrigger::sDialogTrigger::Process(BOOL skip /*= FALSE*/)
{
	if (!m_pTask)
		return TRUE;
	if (!skip)
	{
		if (m_Nowtext < m_DialogList.size())
		{
			if (1 == m_Mode) //1代表剧情对话
				g_pMainState->m_Dialog.Talk(&m_DialogList[m_Nowtext]);
			else
			if (2 ==m_Mode)//2代表普通对话
			{
				g_pMainState->m_Channel.AddNewString(m_DialogList[m_Nowtext].context,m_DialogList[m_Nowtext].name, 1);
			}
			m_Nowtext += 1;
			return TRUE;
		}
	}
	m_Nowtext = -1;
	cTaskFather* p = m_pTask;
	m_pTask = 0;
	m_DialogList.clear();
	p->Process(m_Stage);
	return FALSE;
}
BOOL cDialogTrigger::Process(int id,BOOL skip)
{
	return m_datalist[id].Process(skip);
}

void cDialogTrigger::ReMove()
{
	m_datalist[0].m_pTask = 0;
	m_datalist[1].m_pTask = 0;
}

void cDialogTrigger::Save(ofstream& File)
{
	if (m_datalist[0].m_Nowtext>-1)
		g_pMainState->m_Dialog.Close();
	m_datalist[1].Save(File);
}
void cDialogTrigger::Load(ifstream& File)
{
	m_datalist[0].Reset();
	m_datalist[1].Load(File);
}

void cDialogTrigger::AddSelect(cTaskFather* p, string text, string name, int cancelret, string select0, int ret0, string select1, int ret1, string select2, int ret2, string select3, int ret3)
{
	cInterfaceDialog& d=g_pMainState->m_Dialog;
	d.Reset();
	d.SetObj(name);
	d.SetString(text, select0, select1, select2, select3);
	d.SetTrigger(p,cancelret, ret0, ret1, ret2, ret3);
	d.OnOff(TRUE);
}

cDialogTrigger::cDialogTrigger()
{
	m_datalist.resize(2);
}



void cTriggerTime::Process()
{
	cShiCheng& sc = g_pMainState->m_InterfaceDoor.m_TimeShiCheng;
	int y = sc.year;
	int m = sc.month;
	int d = sc.day;
	int h = sc.hour;
	for (int i = 0; i<m_list.size();i++)
	{
		sTimeTrigger& t = m_list[i];
		if (t.m_y > y)continue;;
		if (t.m_y - y > t.m_y2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		if (t.m_m > m)continue;
		if (t.m_m - m > t.m_m2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		if (t.m_d > d)continue;
		if (t.m_d - d > t.m_d2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		if (t.m_h > h)continue;
		if (t.m_h - h > t.m_d2)
		{
			m_list.erase(m_list.begin() + i);
			return Process();
		}
		cTaskFather* task = m_list[i].m_pTask;
		int stage = m_list[i].m_Stage;
		m_list.erase(m_list.begin() + i);
		task->Process(stage);
		return Process();
	}
}

void cTriggerTime::Save(ofstream& File)
{
	File << " ";
	File << m_list.size()<<" ";
	for (int i = 0; i < m_list.size(); i++)
	{
		File << m_list[i].m_h << " ";
		File << m_list[i].m_d << " ";
		File << m_list[i].m_m << " ";
		File << m_list[i].m_y << " ";
		File << m_list[i].m_h2 << " ";
		File << m_list[i].m_d2 << " ";
		File << m_list[i].m_m2 << " ";
		File << m_list[i].m_y2 << " ";
	}
}

void cTriggerTime::Load(ifstream& File)
{
	int num;
	File >> num;
	m_list.resize(num);
	for (int i = 0; i < num; i++)
	{
		File >> m_list[i].m_h ;
		File >> m_list[i].m_d ;
		File >> m_list[i].m_m ;
		File >> m_list[i].m_y ;
		File >> m_list[i].m_h2 ;
		File >> m_list[i].m_d2 ;
		File >> m_list[i].m_m2 ;
		File >> m_list[i].m_y2 ;

	}
}

void cTriggerTime::Add(cTaskFather* task, int stage, int h /*= -1*/, int d /*= -1*/, int m /*= -1*/, int y /*= -1*/, int y2 /*= 0*/, int m2 /*= 0*/, int d2 /*= 0*/, int h2 /*= 0*/)
{
	cShiCheng& t = g_pMainState->m_InterfaceDoor.m_TimeShiCheng;
	if (y == -1)y = t.year;
	if (m == -1)m = t.month;
	if (d == -1)d = t.day;
	for (int i = 0; i < m_list.size(); i++)
	{
		if (m_list[i].m_pTask == task)
		{
			m_list[i].m_y = y;
			m_list[i].m_d = d;
			m_list[i].m_m = m;
			m_list[i].m_h = h;
			m_list[i].m_y2 = y2;
			m_list[i].m_d2 = d2;
			m_list[i].m_m2 = m2;
			m_list[i].m_h2 = h2;
			m_list[i].m_Stage = stage;
		}
	}
	sTimeTrigger lis;
	lis.m_y = y;
	lis.m_d = d;
	lis.m_m = m;
	lis.m_h = h;
	lis.m_y2 = y2;
	lis.m_d2 = d2;
	lis.m_m2 = m2;
	lis.m_h2 = h2;
	lis.m_Stage = stage;
	lis.m_pTask = task;
	m_list.push_back(lis);
}

void cTriggerTime::Remove(cTaskFather* task)
{
	for (int i = 0; i < m_list.size(); i++)
	{
		if (m_list[i].m_pTask == task)
		{
			m_list.erase(m_list.begin() + i);
			return;
		}
	}
}

void cDialogTrigger::sDialogTrigger::Save(ofstream& File)
{
		if (!m_pTask)
		{
			File <<-1<<" ";
			return;
		}
		else
		{
			File << m_pTask->m_type << " ";
			File << m_Mode << " ";
			File << m_DialogList.size() << " ";
			for (int i = 0; i < m_DialogList.size(); i++)
			{
				m_DialogList[i].Save(File);
			}
		}
}

void cDialogTrigger::sDialogTrigger::Load(ifstream& File)
{
	Reset();
	int id;
	File >> id;
	if (-1 == id)return;
	m_pTask = g_pMainState->FindTaskByID(id);
	File >> m_Mode;
	int size;
	File >> size;
	if (!size)return;

	m_DialogList.resize(size);
	for (int i = 0; i < size; i++)
	{
		m_DialogList[i].Load(File);
	}
}





BOOL cTaskHuoDong::Process(int stage)
{
	if (m_HuoDongID == -1)return TRUE;
	switch (m_HuoDongID)
	{
	case 门派闯关:
		Processmp(stage);
		break;
	case 科举:
		break;
	default:
		ERRBOX;
		break;
	}
	return TRUE;
}

BOOL cTaskHuoDong::Processmp(int stage)
{
	
	switch (stage)
	{
	case -1://活动时间到
		break;
	case 0:
		
		{	
			Init();
			for (int i = 0; i < 13; i++)
			{
				AddTriggerObjMap(&m_List[i]);
			}
			m_HuanShu = 0;
			UpdateJob("去长安107,200参加12门派");
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	
		{
			if (stage != m_Stage+1)
			{
				return TRUE;
			}
			m_NowNpc = g_pMainState->m_pNowSelect;
			ReadytoFightmp(m_List[m_Stage], (eMengPai)m_MengPaiId[m_Stage]);
			AddTriggerFightSuccess(15);
		}
		break;
	case 13:
	
		{
			m_NowNpc = g_pMainState->m_pNowSelect;
			m_NowNpc->Talk((m_pTask == &g_pMainState->m_ZhuXian) ? "要挑战12门派师傅吗?(#Y立即#Y进入战斗)" : "要领取任务吗?", this, 14, "是", "否");
		}
		break;
	case 14:
	{
			   if (0 != g_pMainState->m_Dialog.m_retSelect)return TRUE;
			   if (m_Stage > -1)return TRUE;
			   if (m_pTask == &g_pMainState->m_ZhuXian)
			   {
				   m_TriggerHuanShu = m_HuanShu + 1;
				   ReadytoFightmp(g_pCharacter->m_PCData.m_LV);
				   AddTriggerFightSuccess(15);
				   break;
			   }
	}
	case -14:
	
		{//更新任务
			if (!m_Idlist.size())
			{
				m_Idlist.resize(12);
				for (int i = 0; i < 12; i++)
					m_Idlist[i] = i;
			}
			int id = rand() % m_Idlist.size();
			m_Stage = m_Idlist[id];
			m_Idlist.erase(m_Idlist.begin() + id);
			string text = GetText();
			m_NowNpc->Talk(text);
			UpdateJob(text,m_HuanShu);
		}
		break;
	case 15:
		
		{
			SetJiangLi(8, TRUE, 120, 30);
			m_HuanShu += 1;
			if (m_pTask)
			if (m_HuanShu == m_TriggerHuanShu)
			{
				cTaskFather* p = m_pTask;
				m_pTask = 0;
				RemoveTriggerObjMap();
				g_pMainState->m_Job.ReMoveJob(this);
				m_HuoDongID = -1;
				p->Process(m_TaskRet);	
				return TRUE;
			}
			Process(-14);
		}
		break;
	}
	return TRUE;
}



std::string cTaskHuoDong::GetText()
{
	ostringstream oss;
	cMengPai* pmp = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(m_Stage);
	oss << "下一关为#R";
	oss << pmp->m_Name;
	oss << "#R";
	return oss.str();
}

void cTaskHuoDong::Start(eHuoDong id)
{
	m_HuoDongID = id;
	Init();
	Process(0);
}

void cTaskHuoDong::Initmp()
{
	if (m_bInit12)return;
	m_bInit12 = TRUE;
	ifstream File;
	ostringstream oss;
	oss << g_strMediaPath;
#if ccc_m5
	oss << "任务//12门派.txt";
#else
	oss << "十二门派.txt";
#endif
	File.open(oss.str());
	if (!File)ERRBOX;
	for (int i = 0; i < 13; i++)
	{
		File >> m_MengPaiId[i];
		m_List[i].m_Npc.Load(File);
		m_List[i].m_pTask = this;
		m_List[i].m_Stage = i + 1;
	}
	m_Idlist.resize(12);
	for (int i = 0; i < 12; i++)
		m_Idlist[i] = i;
	m_Stage = -1;
	File.close();
}

void cTaskHuoDong::Init()
{
	switch (m_HuoDongID)
	{
	case 门派闯关:
		Initmp();
		break;
	case 科举:
		break;
	default:
		ERRBOX;
		break;
	}
}

void cTaskHuoDong::ReadytoFightmp(sMapObjTrigger& list,eMengPai mp)
{
#if ccc_m5
	int enemynum =  g_pMainState->AtutoGetEnemyNum();
	if (enemynum > 9)enemynum = 9;
	int lv = g_pCharacter->m_PCData.m_LV;
	sZiZhi zizhi;
	zizhi.Set(1200 + m_HuanShu * 3, 800 + m_HuanShu * 3, 2000 + m_HuanShu * 4, 4000 + m_HuanShu * 10, 1000 + m_HuanShu * 2, 1000 + m_HuanShu * 2, 100 + (m_HuanShu >> 2));	
	cPetData* pPet= AddPCEnemyF(lv * 200, list.m_Npc.m_modeid, &zizhi, -1, mp, list.m_Npc.m_name, list.m_Npc.weapontype, list.m_Npc.weaponid);
	pPet->AddSkill(ePS_反震);
	int petrand;
	for (int i = 0; i < enemynum; i++)
	{
		petrand = 10 + m_HuanShu;
	 	petrand= rand() % petrand+(m_HuanShu>>1);
		while (petrand>93)
		{
			petrand -= rand()%20;
		}
		AddPCPetEnemyF(lv*120,(ePetID)petrand);
	}
#else
	int lv = g_pCharacter->m_PCData.m_LV;
	sZiZhi zizhi;
	zizhi.Set(1200 + m_HuanShu * 3, 800 + m_HuanShu * 3, 2000 + m_HuanShu * 4, 4000 + m_HuanShu * 10, 1000 + m_HuanShu * 2, 1000 + m_HuanShu * 2, 100 + (m_HuanShu >> 2));	
	cPetData* pPet= AddPCEnemyF(lv * 300, list.m_Npc.m_modeid, &zizhi, lv, mp, list.m_Npc.m_name, list.m_Npc.weapontype, list.m_Npc.weaponid);
	pPet->AddSkill(ePS_反震);
	((cPCData*)pPet)->FollowXiulian();
	pPet->m_LiveCp = 10 + rand() % 10;
	int petrand;
	for (int i = 0; i < 2; i++)
	{
		petrand = 10 + m_HuanShu;
		petrand = 40 + rand() % petrand + (m_HuanShu >> 1);
		while (petrand > 93)
		{
			petrand -= rand() % 10;
		}
		pPet = AddPCPetEnemyF(lv * 300, (ePetID)petrand, lv - 5, mp);
		if (!pPet->m_JinJieNum.m_JinJieNum)
		{
			pPet->SetJinJie(MyTest::getInstance()->getJinjie(lv));
		}
		((cPCData*)pPet)->m_XiuLian.Set(pPet->m_LV / 10, 0, pPet->m_LV / 10, 0);
	}
	for (int i = 0; i < 2; i++)
	{
		petrand = 10 + m_HuanShu;
		petrand = 40 + rand() % petrand + (m_HuanShu >> 1);
		while (petrand > 93)
		{
			petrand -= rand() % 10;
		}
		pPet = AddPCPetEnemyF(lv * 280, (ePetID)petrand, lv - 5);
		if (!pPet->m_JinJieNum.m_JinJieNum)
		{
			pPet->SetJinJie(MyTest::getInstance()->getJinjie(lv));
		}
		((cPCData*)pPet)->m_XiuLian.Set(pPet->m_LV / 10, 0, pPet->m_LV / 10, 0);
	}
	vector<int> ids = { 81, 51, 83, 77, 88, 89, 90, 91, 92, 93, 54, 52, 86, 50, 49, 46, 85, 78, 56, 94, 95, 98, 100, 106, 107, 123, 149, 152, 154 };
	for (int i = 0; i < 5; i++)
	{
		pPet = AddPetEnemyF(lv * 500, (ePetID)ids[rand() % ids.size()], lv + 5);
		if (!pPet->m_JinJieNum.m_JinJieNum)
		{
			pPet->SetJinJie(MyTest::getInstance()->getJinjie(lv));
		}
	}
#endif
	SetMusic();
	g_StateType = STATE_FIGHT;
}

void cTaskHuoDong::ReadytoFightmp(int lv, cObj* nownpc /* = nullptr */)
{
	if (nownpc == nullptr)
	{
		nownpc = m_NowNpc;
	}
	vector<ePetID> modes =
	{ e程咬金, e空度禅师, e孙婆婆, e菩提祖师, e大大王, e牛魔王,
	e白晶晶, e地藏王, e东海龙王, e镇元大仙, e观音姐姐, e李靖 };

	auto getMPfromMode = [&](int mode)
	{
		forv(modes, i)
		{
			if (modes[i] == mode)
			{
				return eMengPai(i);
			}
		}
		return eMP_随机;
	};

	auto getNamefromMode = [&](int mode)
	{
		forv(modes, i)
		{
			if (modes[i] == mode)
			{
				return g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[i].m_ShiFuName;
			}
		}
		return string("师傅");
	};

	vector<ePetID> mode2;
	forv(modes, i)
	{
		if (modes[i] == nownpc->GetModeID())
		{
			continue;
		}
		mode2.push_back(modes[i]);
	}
	std::random_shuffle(mode2.begin(), mode2.end());
	if (ccc_find(modes, nownpc->GetModeID()))
	{
		mode2.push_back((ePetID)nownpc->GetModeID());
	}

	cPetData* pPet;
	for (int i = 11; i >= 2; --i)
	{
		ePetID e = mode2[i];
		eMengPai mp = getMPfromMode(e);
		pPet = AddPCPetEnemyF(lv * 160, e, -1, mp, getNamefromMode(e));
		int lv = pPet->m_LV;
		if (mp == eMP_女儿村 || mp == eMP_盘丝岭 || mp == eMP_五庄观 || mp == eMP_天宫)
		{
			pPet->m_SealRate.d1 -= 30;
			pPet->m_Controler.Set(1);
		}
		else if (1 || mp == eMP_大唐官府 || mp == eMP_狮驼岭 || mp == eMP_东海龙宫 || mp == eMP_魔王寨)
		{
			pPet->m_Controler.Set(0);
		}
		pPet->m_XiuLian.Set(lv / 5, lv / 5, lv / 5, lv / 5);
	}
	SetMusic();
	g_StateType = STATE_FIGHT;
}

void cTaskHuoDong::UpdateJob(string text,int huanshu)
{
	sJob job;
	string title;
	switch (m_HuoDongID)
	{
	case 门派闯关:title = "门派闯关";
		break;
	case 科举:title = "科举";
		break;
	default:
		break;
	}
	job.Set( title,text, -1, this,0 );
	g_pMainState->m_Job.AddaJob(job, huanshu);
}

void cTaskHuoDong::Load(ifstream& File)
{
	File >> m_HuoDongID;
	if (m_HuoDongID == -1)return;
	m_bInit12 = FALSE;
	Init();
	string str;
	File >> str;
	int num;
	File >> num;
	m_Idlist.resize(num);
	for (UINT i = 0; i < m_Idlist.size(); i++)
		File >> m_Idlist[i];
	File >> m_Stage;
	File >> m_HuanShu; 
	int k;
	File >> k;
	if (k)
	{
		File >> k;
		m_pTask = g_pMainState->FindTaskByID(k);
		File >> m_TaskRet;
		File >> m_TriggerHuanShu;
	}
	
}

void cTaskHuoDong::Save(ofstream& File)
{
	File << "\n";
	File << m_HuoDongID;
	if (m_HuoDongID == -1)return;
	File << " 活动 ";
	File << m_Idlist.size() << " ";
	for (UINT i = 0; i < m_Idlist.size(); i++)
		File << m_Idlist[i] << " ";
	File << m_Stage << " ";
	File << m_HuanShu << " ";
	//是否有剧情
	if (m_pTask)
	{
		File << 1 << " ";
		File << m_pTask->m_type << " ";
		File << m_TaskRet << " ";
		File << m_TriggerHuanShu << " ";
	}
	else File << 0 << " ";
}



void sMapObjTrigger::Save(ofstream& File)
{
	m_Npc.Save(File);
	if (m_pTask)
	{
		File << 1 << " ";
		File << m_Stage << " ";
		File << m_pTask->m_type << " ";
	}
	else File << 0 << " ";
}

void sMapObjTrigger::Load(ifstream& File)
{
	m_Npc.Load(File);
	BOOL havetrigger;
	File >> havetrigger;
	if (havetrigger)
	{
		File >> m_Stage;
		int id;
		File >> id;
		m_pTask = g_pMainState->FindTaskByID(id);
	}
	else
	{
		m_pTask = 0;
	}
}

void sMapObjTrigger::operator=(sFriendList& data)
{
	m_Npc.m_name = data.m_Name;
	if (data.m_modeid<1000)
		m_Npc.m_modeid = 2000+data.m_modeid;
	else
		m_Npc.m_modeid =  data.m_modeid;
	//武器造型
	m_Npc.weapontype = data.m_weapontype;
	m_Npc.weaponid = data.m_weaponid;
	m_Npc.m_JinJieID = data.m_JinJieNum;
	//染色
	m_Npc.m_Ranse = data.m_Ranse;
	//目前就写这点吧,有需要继续
}

void cTriggerGive::ReMove(cTaskFather* ptask)
{
	for (int i = 0; i < m_List.size(); i++)
	{
		if (m_List[i].m_ptask->m_type == ptask->m_type)
		{
			m_List.erase(m_List.begin() + i);
			return ReMove(ptask);
		}
	}
}

void cTriggerGive::ReMove(int id)
{
	m_List.erase(m_List.begin() + id);
}

void cTriggerGive::AddTask(string name, int itemid, int itemtype, cTaskFather* ptask, int ret, BOOL bHuChi)
{
	if (bHuChi)ReMove(ptask);
	sTriggerGive data;
	data.Set(name, itemid, itemtype, ptask, ret);
	m_List.push_back(data);
}

BOOL cTriggerGive::Process(string name, int id, int type)
{
	int num = m_List.size();
	if (!num)return FALSE;
	for (int i = 0; i < num; i++)
	{
		if (m_List[i].m_name == name)
		if (m_List[i].m_itemtype==type)
		if (m_List[i].m_itemid == id)
		{
			cTaskFather* p = m_List[i].m_ptask;
			int stage = m_List[i].m_ret;
			ReMove(i);
			p->Process(stage);
			return TRUE;
		}
	}
	return FALSE;
}

void cTriggerGive::Save(ofstream& File)
{
	File << "\n";
	File << m_List.size()<<" ";
	for (int i = 0; i < m_List.size(); i++)
		m_List[i].Save(File);
	File << "\n";
}
void cTriggerGive::Load(ifstream& File)
{
	int num;
	File >>num ;
	m_List.resize(num);
	for (int i = 0; i < num; i++)
		m_List[i].Load(File);
}
void cTriggerGive::sTriggerGive::Save(ofstream& File)
{
	File << " ";
	if (m_name == "")
	{
		ERRBOX;
	}
	else
		File << m_name << " ";
	File << m_itemid << " ";
	File << m_itemtype << " ";
	File << m_ptask->m_type << " ";
	File << m_ret << " ";
}
void cTriggerGive::sTriggerGive::Load(ifstream& File)
{
	File >> m_name;
	File >> m_itemid;
	File >> m_itemtype;
	int id;
	File >> id;
	m_ptask = g_pMainState->FindTaskByID(id);
	File >> m_ret;
}
