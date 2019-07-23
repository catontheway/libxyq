#include "_global.h"

static void setXiangFu(sNpc& m_Npc, string& strTalk, string& strJob)
{
	ostringstream oss;
// 	oss << "有个#R";
// 	oss << m_Npc.m_name;
// 	oss << "#R在江湖上为非做歹,现被为师打伤,听说他在#R";
// 	oss << m_Npc.m_mapname;
// 	oss << "#R#Y";
// 	oss << m_Npc.m_x/* / 20*/;
// 	oss << " ";
// 	oss << /*(g_pMainState->m_Map.m_BmpTest.GetHeight() - */m_Npc.m_y/*) / 20*/;
// 	oss << "#Y养伤,将他降伏带回来";

	oss << "前往 #R";
	oss << m_Npc.m_mapname;
	oss << "#R#Y";
	oss << m_Npc.m_x/* / 20*/;
	oss << " ";
	oss << /*(g_pMainState->m_Map.m_BmpTest.GetHeight() - */m_Npc.m_y/*) / 20*/;
	oss << " #Y降伏#R";
	oss << m_Npc.m_name;
	oss << "#R,记得带上#R乾坤袋#R";
	strTalk = oss.str();

	oss.str("");
	oss << "#R";
	oss << m_Npc.m_mapname;
	oss << "#R #B";
	oss << m_Npc.m_x/* / 20*/;
	oss << " ";
	oss << m_Npc.m_y;
	oss << "#B\n降伏#R";
	oss << m_Npc.m_name;
	oss << "#R\n记得带上#R乾坤袋#R";
	strJob = oss.str();
	return;

	oss.str("");
	oss << "#R";
	oss << m_Npc.m_name;
	oss << "#R在#R";
	oss << m_Npc.m_mapname;
	oss << "#R#Y";
	oss << m_Npc.m_x/* / 20*/;
	oss << " ";
	oss << /*(g_pMainState->m_Map.m_BmpTest.GetHeight() - */m_Npc.m_y/*) / 20*/;
	oss << "#Y养伤,用#R乾坤袋#R将其降伏,并交给师傅";
	strJob = oss.str();
}

void getTongMen(const sNpc& m_Npc, string& strTalk, string& strJob)
{
	ostringstream oss;
	oss << "本门弟子在 #R";
	oss << m_Npc.m_mapname;
	oss << "#R#Y";
	oss << m_Npc.m_x/* / 20*/;
	oss << " ";
	oss << m_Npc.m_y;
	oss << "#Y 被袭击,速速前往援救";
	strTalk = oss.str();

	oss.str("");
	oss << "苦战中的同门\n#R";
	oss << m_Npc.m_mapname;
	oss << "#R #B";
	oss << m_Npc.m_x/* / 20*/;
	oss << " ";
	oss << m_Npc.m_y;
	oss << "#B\n速速支援";
	strJob = oss.str();
}


bool cTaskSM::Process(int stage)
{
	switch (stage)
	{
// 	case 21://示威
// 		{
// 			if (g_pMainState->m_Map.m_MapName == m_Npc.m_mapname)
// 			{
// 				g_pMainState->m_Map.RemoveNpc(m_Npc.m_x, m_Npc.m_y, m_Npc.m_name, 1);
// 			}
// 			Process(20);
// 		}
// 		break;

	case 998:
		GetShiFu()->Talk("做的不错,继续努力");
		Process(1001);
		break;
	case 999:
	{
		auto& d = g_pMainState->m_Dialog;
		d.Reset();
		d.m_ContextList.m_Name.SetString(m_Npc.m_name);
		d.m_ContextList.m_Name.UpdateXCenter();
		d.SetHead(g_pMainState->m_PetDataManager.GetPetData(m_Npc.m_modeid)->GetID(0, POS_DIALOG));
		d.SetString("我错了, 再也不敢了");
		d.OnOff(true);
		g_pMainState->m_InterfaceDoor.SetTrigger(0, 0);
	}
		Process(1001);
	case 1000://任务消失 // 任务完成
		g_pMainState->m_TriggerObjMap.ReMove(this);
		g_pMainState->m_Job.ReMoveJob(this);
		g_pMainState->m_TriggerObj.ReMove(this);
		break;
	case 1001:
		Process(1000);
	//	GetJiangLi();
// 		INT64 exp = g_pCharacter->m_PcData.m_EXP;
// 		INT64 mon = g_pCharacter->m_PcData.m_Money[0];
// 		g_pMainState->award1000(188 + m_HuanShu * 12, 48 + m_HuanShu * 6, true);
// 		exp = g_pCharacter->m_PcData.m_EXP - exp;
// 		mon = g_pCharacter->m_PcData.m_Money[0] - mon;
// 		for (int i = g_pMainState->m_Friend._friends.size() - 1; i >= 1; --i)
// 		{
// 			cPcData* pc = &((cCharacter*)g_pMainState->m_Friend._friends[i].obj->m_pIndex)->m_PcData;
// 			pc->AddExp(exp * 2 / 3, exp);
// 		}
		g_pMainState->awardklv(188 + m_HuanShu * 12, 48 + m_HuanShu * 6);
		g_pMainState->award125(20 + m_HuanShu, 150);
		if ((g_GlobalValues[4] = ++m_HuanShu) >= 10)
		{
			g_GlobalValues[4] = m_HuanShu = 1;
		}
		m_pNowObj = nullptr;
		break;
// 	case 11:
// 			GetJiangLi();
// 			GetShiFu()->Talk("做的不错,继续努力");
// 			return true;
// 	case 20://任务失败
// 		{
// 			Process(1000);
// 			int money = m_HuanShu * 50;
// 			g_pCharacter->m_PcData.AddMoney(-money, 0,0);
// 			g_pMainState->m_Tags.GetMoneyAndExp(-money);//损失
// 		}
// 		break;
// 	case 4://取消任务
// 		{
// 			Process(11);
// 			return true;
// 			
// 			if (g_pMainState->m_Dialog.m_retSelect)
// 				return true;
// 			m_pNowObj->Talk("你的任务已经取消了");
// 			Process(20);
// 		}
// 		break;
//	case 19:	
//		{
// 			sZiZhi zizhi;
// 			zizhi.Set(1000, 1000, 1500, 4000, 1000, 1000, 100);
// 			g_pMainState->AddPCEnemy(m_Npc.m_name, m_Npc.m_modeid, g_pCharacter->m_PcData.m_Lv,
// 				0, &zizhi, (eMengPai)m_EnemyMengPai, &m_ShiWeiWeapon);
// 
// 			g_pMainState->m_FightList[10].isLive = true;
// 		//	cObj* pObj = g_pMainState->m_FightList[10].m_pData;
// 			zizhi.Set(1000, 1000, 1500, 4000, 1000, 1000, 100);
// 			g_pMainState->AddPC(m_YuanJiu.m_name, m_YuanJiu.m_modeid, g_pCharacter->m_PcData.m_Lv,
// 				0, &zizhi, (eMengPai)g_pCharacter->m_PCData.m_MengPaiID);
// 		
// 
// 			g_StateType = STATE_FIGHT;
// 			AddTriggerFightSuccess(17);
// 		}
// 		break;
// 
// 	case 17:
// 		{
// 			cObj* pObj = g_pMainState->FindObjByName(m_Npc.m_name);
// 			pObj->Talk("我错了,回去告诉你师父吧,我再也不敢了");
// 			g_pMainState->m_Map.RemoveNpc(m_Npc.m_name);
// 			GetJiangLi();
// 		}
// 		break;
// 	case 16://巡逻怪
// 		{
// 			g_pMainState->m_FightList[10].isLive = true;
// 			cObj* pObj = g_pMainState->m_FightList[10].m_pData;
// 			sZiZhi zizhi;
// 			zizhi.Set(1000, 1000, 1500, 4000, 1000, 1000, 100);
// 			pObj->AutoPCData(m_Npc.m_name, m_Npc.m_modeid, 0, &zizhi, (eMengPai)m_EnemyMengPai, &m_ShiWeiWeapon);
// 			g_pMainState->FollowLv(10, g_pCharacter->m_PcData.m_Lv);
// 			g_pMainState->m_FightList[11].isLive = true;
// 			pObj = g_pMainState->m_FightList[11].m_pData;
// 			pObj->AutoPetData("帮凶", rand() % 70, 10, 0, g_pCharacter->m_PcData.m_Lv);
// 			
// 				
// 			g_StateType = STATE_FIGHT;
// 			AddTriggerFightSuccess(17);
// 		}
// 		break;
// 	case 15:
// 		if (0 == g_pMainState->m_Map.m_MapName.compare(m_Npc.m_mapname))
// 		{
// 			g_pMainState->m_Map.AddNpc(&m_Npc, this, "无", 16);
// 			cObj* target = g_pMainState->m_Map.m_pNpc[g_pMainState->m_Map.m_numberOfNpc - 1];
// 			cCharacter* pc= (cCharacter*)target->m_pIndex;
// 			pc->m_PCData.m_Equip[2] = m_ShiWeiWeapon;
// 			target->m_NowPos = -1;
// 			target->Set(POS_STAND);
// 		}
// 		break;
	case 0:
		if (!g_pMainState->m_pNowSelect)return true;
		m_pNowObj = g_pMainState->m_pNowSelect;
		if (-1 == g_pCharacter->m_PcData.m_MengPaiID || g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PcData.m_MengPaiID].m_ShiFuName != g_pMainState->m_pNowSelect->m_TrueName.GetString())
		{
			m_pNowObj->Talk("是否要拜师?", this, 1, "确定", "取消");
		}
		else
		{
			if (g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PcData.m_MengPaiID].m_ShiFuName == g_pMainState->m_pNowSelect->m_TrueName.GetString())
			{
				CheckInit(g_pCharacter->m_PcData.m_MengPaiID);
					ostringstream oss;
// 				oss << "师门任务(还剩";
// 				oss << g_pCharacter->m_PcData.m_Lv - m_HuanShu;
// 				oss << "个)";
				m_pNowObj->Talk("请选择要做的事", this, 2, "师门任务", "学习技能");
			}
			else
			{
				m_pNowObj->Talk("非本门弟子,不要在此处逗留");
			}
		}
		break;
	case 1://拜师成功
	{
		if (0 == g_pMainState->m_Dialog.m_retSelect)
		{
			int mengpaiid = -1;
			for (int i = 0; i < c_MenPaiNumber; i++)
			{
				if (g_pMainState->m_Dialog.m_ContextList.m_Name.GetString() == g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[i].m_ShiFuName)
				{
					mengpaiid = i;
					break;
				}
			}
			if (-1 == mengpaiid)ERRBOX;

			auto func = [](cPcData &data, int _1)
			{
				string text;
				switch (data.m_MengPaiID)
				{
				case eMP_大唐官府:
					text += "+物理穿刺";
					break;
				case eMP_化生寺:
					text += "+治疗暴击";
					break;
				case eMP_方寸山:
					text += "+驱鬼";
					break;
				case eMP_女儿村:
					text += "+速度";
					break;
				case eMP_五庄观:
					text += "+法术格挡";
					break;
				case eMP_狮驼岭:
					text += "+吸血";
					break;
				case eMP_魔王寨:
					text += "+法术波动+火系吸收";
					break;
				case eMP_盘丝岭:
					text += "+暗器防御";
					break;
				case eMP_阴曹地府:
					text += "+封印抵抗";
					break;
				case eMP_东海龙宫:
					text += "+法术暴击+水系吸收";
					break;
				case eMP_普陀山:
					text += "+治疗效果";
					break;
				case eMP_天宫:
					text += "+神迹率";
					break;
				case eMP_凌波城:
					text += "+必杀率";
					break;
				case eMP_无底洞:
					text += "+再生";
					break;
				case eMP_神木林:
					text += "+法术连击";
					break;
				}
				return text;
			};

			func(g_pCharacter->m_PcData, -1);
			int mpOld = g_pCharacter->m_PcData.m_MengPaiID;
			g_pCharacter->m_PcData.m_MengPaiID = mengpaiid;
			g_pMainState->m_Tags.Add("恭喜你成功拜师");
			string text = "附加小光环: ";
			text += func(g_pCharacter->m_PcData, 1);

			g_pMainState->m_Channel.AddNewString(text);
// 			if (mpOld < 0)
// 			{
// //				g_pCharacter->m_PcData.FollowSkill();
// 			}
// 			else
			{
				forr(g_pCharacter->m_PcData.m_Accelarate, i)
					g_pCharacter->m_PcData.m_Accelarate[i] = -1;
				
				//　技能解锁
				g_pCharacter->m_PcData.autoSkillEnable();

				forr(g_pCharacter->m_PcData.m_MengPaiSkillLvs, i)
				{
					g_pCharacter->m_PcData.m_MengPaiSkillLvs[i] = max(g_pCharacter->m_PcData.m_MengPaiSkillLvs[i], cct::LvGapFromRoleAndSkill);
				}

				g_pMainState->m_FightWorkList[g_pCharacter->m_PcData.m_IDinFightWorkList].m_FriendListid = -1;

// 				for (int i = 0; i < 7; ++i)
// 				{
// 					g_pMainState->m_SkillManager.lvUpMainSkill(g_pCharacter->m_PcData, 0, i, true);
// 				}
			}
			//				g_pCharacter->m_PCData.FollowEquipAll();
			// 				if (g_pMainState->GetLockLv上限() < 25)
			// 				{
			// 					g_pMainState->LockLv(25);
			// 				}
		}
	}
		break;
	case 2:
		{
		switch (g_pMainState->m_Dialog.m_retSelect)
		{
		case 0:

			if (g_pMainState->m_Job.CheckHaveJob("师门任务"/*m_type*/))
			{
				m_pNowObj->Talk("已有任务,要取消?", this, 4, "是的不做了", "我还要继续");
				return true;
			}
			else
			{
				Process(3);
			}
			break;
		case 1:
			g_pMainState->m_LearnSkill.OnOff(true);
			break;
		}
// 			m_bHaveTask = true;
// 			int renqi = g_pCharacter->m_PCData.m_Popularity / 200;
// 			int  tasktype;
// 			if (m_HuanShu< 40)
// 			{
// 				if (rand() % 100 < 30 - renqi)
// 					tasktype =5;//巡逻
// 				else  
// 				if (rand() % 100 < 20 + renqi)
// 					tasktype = 0;//送信
// 				else  if (rand() % 100 < 15 + renqi)tasktype = 1;//要0级装备
// 				else  if (rand() % 100 < 15 + renqi)tasktype = 3;//要包子
// 				else  if (rand() % 100 < 15 + renqi)tasktype= 18;//要黄纸等
// 				else  tasktype = 2; //要垃圾药品
// 			}else
// 			if (m_HuanShu < 70)
// 			{	
// 				if (rand() % 100 < 30 - renqi)tasktype = 5;//巡逻
// 				else  if (rand() % 100 < 30 + renqi)tasktype = 4;//要10-30级装备
// 				else  if (rand() % 100 < 20 + renqi)tasktype = 8;//要召唤兽
// 				else  if (rand() % 100 < 20 + renqi)tasktype = 18;//要黄纸等
// 				else  tasktype = 2; //要垃圾药品
// 			}
// 			else
// 			if (m_HuanShu <100)
// 			{
// 				if (rand() % 100 < 20 - renqi)tasktype = 10;//
// 				else  if (rand() % 100 < 20 - renqi)tasktype = 19;//要40-50环
// 				else  if (rand() % 100 < 20 + renqi)tasktype = 8;//要召唤兽
// 				else  if (rand() % 100 < 20 - renqi)tasktype = 17;//要花 ,乐
// 				else  if (rand() % 100 < 20 + renqi)tasktype=11;//援救
// 				else  tasktype = 14;//要三级药
// 		
// 			}
// 			else
// 			if (m_HuanShu < 130)
// 			{
// 				if (rand() % 100 < 20 - renqi)tasktype = 10;//
// 				else  if (rand() % 100 < 2 - renqi)tasktype = 16;//要60-70环
// 				else  if (rand() % 100 < 20 + renqi)tasktype = 8;//要召唤兽
// 				else  if (rand() % 100 < 20 - renqi)tasktype = 17;//要花 ,乐
// 				else  if (rand() % 100 < 20 + renqi)tasktype = 11;//援救
// 			//	else  if (rand() % 100 < 15 - renqi)tasktype = 7;//降伏
// 				else  tasktype = 14;//要三级药
// 			}
// 			else
// 			{
// 				if (rand() % 100 < 10 - renqi)tasktype = 10;//
// 				else  if (rand() % 100 < 5 - renqi)tasktype = 16;//要60-70环
// 				else  if (rand() % 100 < 15 + renqi)tasktype = 8;//要召唤兽
// 				else  if (rand() % 100 < 10 - renqi)tasktype = 17;//要花 ,乐
// 				else  if (rand() % 100 < 30 + renqi)tasktype = 11;//援救
// 				else  if (rand() % 100 < 10 - renqi)tasktype = 13;//要2级家具
// 		//		else  if (rand() % 100 < 15 - renqi)tasktype = 7;//降伏
// 				else  if (rand() % 100 < 10 - renqi)tasktype = 9;//要东西
// 				else  tasktype = 14;//要三级药
// 			}
// 			AddTask(tasktype);
		}
		break;
	case 3:
	{
		m_pNowObj = nullptr;
		int r = rand() % 100;
		string strTalk, strJob;
		if (r < 25)
		{
			strTalk = "最近门派里有点动静,出去看看吧";
			string mapname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PcData.m_MengPaiID].m_XunLuoMapName;
			strJob = "在#R" + mapname + "#R巡逻";
			AddTriggerObjMap(mapname, 200);
		}
		else if (r < 55)
		{
			int mp = m_SuccessNum = rand() % c_MenPaiNumber;
			string mapname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[mp].m_XunLuoMapName;
			strJob = "#R" + mapname + "#R\n首席弟子切磋";
			strTalk = "你去和#R" + mapname + "#R首席弟子切磋,点到即止";
			AddTriggerObj("首席弟子", mapname, 100);
		}
		else if (r < 85)
		{
			if (!m_bInitXiangFu)InitXiangFu();

			m_YuanJiu.m_name = "苦战中的同门";
			m_YuanJiu.m_mapname = m_XiangFuDiDianList[rand() % m_XiangFuDiDianList.size()];
			g_pMainState->m_Map.AutoGetPos(m_YuanJiu.m_x, m_YuanJiu.m_y, m_YuanJiu.m_mapname);
			//	m_YuanJiu.m_direction = m_Npc.m_direction;
			m_YuanJiu.m_modeid = g_pMainState->getModelFromMp(g_pCharacter->m_PcData.m_MengPaiID) + 2000; //rand() % 14;

			//	ostringstream oss("敌人在");
			//	oss << "#R";
			//	oss << m_Npc.m_mapname;
			//	oss << "#R#Y";
			//	oss << m_Npc.m_x / 20;
			//	oss << " ";
			//	oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
			//	oss << "#Y袭击本门弟子,速速前往援救";
			getTongMen(m_YuanJiu, strTalk, strJob);
			AddTriggerObjMap(&m_YuanJiu, 400);
		}
		else
		{
			if (!m_bInitXiangFu)InitXiangFu();
// 			cObj* pPreObj = g_pMainState->m_Dialog.m_pObj;
// 			g_pMainState->m_Dialog.Reset();
// 			g_pMainState->m_Dialog.SetObj(pPreObj);
// 			g_pMainState->m_Dialog.m_pObj = 0;

			m_Npc.m_modeid = cct::getPetModel(45, 125);
			m_Npc.m_name = g_pMainState->m_PetDataManager.GetPetData(m_Npc.m_modeid)->m_Name;// m_XiangFuNameList[rand() % m_XiangFuNameList.size()];
			m_Npc.m_mapname = m_XiangFuDiDianList[rand() % m_XiangFuDiDianList.size()];

			g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
			setXiangFu(m_Npc, strTalk, strJob);
			m_Npc.m_name = "待降服的" + m_Npc.m_name;
			AddTriggerObjMap(&m_Npc, 300);
		}

		GetShiFu()->Talk(strTalk);
		UpdateJob(strJob);
	}
		break;
		case 4:
			switch (g_pMainState->m_Dialog.m_retSelect)
			{
			case 0:
				g_pMainState->m_TriggerObjMap.ReMove(this);
				g_pMainState->m_TriggerObj.ReMove(this);
				g_pMainState->m_Job.ReMoveJob(this);
				g_GlobalValues[4] = m_HuanShu = 0;
				GetShiFu()->Talk("任务已经取消");
				break;
			default:
				break;
			}
			break;
		case 100: // 首席
		{
			g_pMainState->AddEnemy(g_pMainState->m_pNowSelect->GetModeID(), g_pCharacter->m_PcData.m_Lv, (eMengPai)m_SuccessNum, "首席弟子"/*g_pMainState->m_pNowSelect->GetName()*/);
			for (int i = 0; i < 2; ++i)
			{
				int mp = cct::getMenpai(eMP_随机);
				g_pMainState->AddEnemy(g_pMainState->getModelFromMp(mp) + 2000, g_pMainState->getAvgLv(), (eMengPai)mp, "彪悍粉丝");
			}
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(1001);
		}
			break;
		case 200:   //师门巡逻
			g_pMainState->m_InterfaceDoor.SetTrigger(this, 201);
			g_pMainState->m_Map.m_MapType = 1;
			m_SuccessNum = 0;
			break;
		case 201:  //师门巡逻
		{
			int lv = g_pCharacter->m_PcData.m_Lv;
			int lv1 = lv - 25;
			int lv2 = lv + 25;
			lv1 = max(5, lv1);
			lv2 = min(175, lv2);

			int petid = cct::getPetModel(lv1, lv2);
			auto pet = g_pMainState->AddEnemy(petid, lv);
			pet->m_Name = "捣乱的" + pet->m_Name;
			pet->getObj()->SetTrueName(pet->m_Name);
			m_Npc.m_modeid = petid;
			m_Npc.m_name = pet->m_Name;
			
			lv = g_pMainState->getAvgLv();
			for (int i = 0; i < 7; ++i)
			{
				petid = cct::getPetModel(lv1, lv2);
				auto pet = g_pMainState->AddEnemy(petid, lv);
				pet->m_Name = "捣乱的" + pet->m_Name;
				pet->getObj()->SetTrueName(pet->m_Name);
			}
			
// 			m_enemyname = "捣乱的";
// 			sPetData* psPet = g_pMainState->m_PetDataManager.GetPetData(petid);
// 			m_enemyname += psPet->m_Name;
// 			pPet = AddPCPetEnemyF(g_pCharacter->m_PcData.m_Lv * 40, (ePetID)petid, g_pCharacter->m_PcData.m_Lv - 20, eMP_随机, m_enemyname);
// 			m_enemyface = psPet->m_dialoghead[0];
// 			AddPetEnemyF(g_pCharacter->m_PcData.m_Lv * 35, (ePetID)(rand() % 50), g_pCharacter->m_PcData.m_Lv - 20, "帮凶");
// 			SetMusic();
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(999);
		}
			break;
		case 300: // 降服
		{
			auto pet = g_pMainState->AddEnemy(m_Npc.m_modeid, g_pCharacter->m_PcData.m_Lv, (eMengPai)cct::getMenpai(eMP_随机), g_pMainState->m_pNowSelect->GetName());
			m_pNowObj = pet->getObj(); // g_pMainState->m_FightWorkList[pet->m_IDinFightWorkList].m_pObj;
// 			cPetData* pPet;
// 			int petid = rand() % 50;
// 			m_enemyname = "捣乱的";
// 			sPetData* psPet = g_pMainState->m_PetDataManager.GetPetData(petid);
// 			m_enemyname += psPet->m_Name;
// 			pPet = AddPCPetEnemyF(g_pCharacter->m_PcData.m_Lv * 40, (ePetID)petid, g_pCharacter->m_PcData.m_Lv - 20, eMP_随机, m_enemyname);
// 			m_enemyface = psPet->m_dialoghead[0];
// 			AddPetEnemyF(g_pCharacter->m_PcData.m_Lv * 35, (ePetID)(rand() % 50), g_pCharacter->m_PcData.m_Lv - 20, "帮凶");
// 			SetMusic();
 			g_StateType = STATE_FIGHT;
			m_bXiangFuSuccess = false;
 			AddTriggerFightSuccess(301);
		}
			break;
		case 301:
			g_pMainState->m_Map.RemoveNpc(m_Npc.m_name);
			if (m_bXiangFuSuccess)
			{
				g_pHeroObj->Talk("抓到了,回去报告师父吧");
				g_pMainState->m_TriggerGive.AddTask(GetShiFuName(), 11, 28, this, 998);
			}
			else
			{
				Process(1000);
				g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
				string strTalk, strJob;
				setXiangFu(m_Npc, strTalk, strJob);
				UpdateJob(strJob);
				g_pHeroObj->Talk("跑掉了,继续");
				AddTriggerObjMap(&m_Npc, 300);
			}
			break;
		case 400:
		{
			int lv = g_pCharacter->m_PcData.m_Lv;
			int lv1 = lv - 25;
			int lv2 = lv + 25;
			lv1 = max(5, lv1);
			lv2 = max(175, lv2);

			if (g_pMainState->m_InterfaceTeam.getLeaveBegin() == 5)
			{
				g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
			}
			int mp = g_pCharacter->m_PcData.m_MengPaiID;
			cPcData* pet = g_pMainState->AddEnemy(m_YuanJiu.m_modeid, g_pCharacter->m_PcData.m_Lv / 2 + 5, (eMengPai)mp, "同门", nullptr, -1, -1, true);
			pet->PointRemain = cct::PointRemian;
			pet->setPointAfterLv(g_pMainState->getAddpointFromMp(mp, true), true);
			pet->autoEquip(false);
			pet->autoData(false, true, true);
			pet->apply();
			g_pMainState->m_pFightState->m_FightMenu.SetControl(pet->m_IDinFightWorkList, false);
			m_SuccessNum = pet->m_IDinFightWorkList;

			int petid  = cct::getPetModel(lv1, lv2);
			/*int */mp = cct::getMenpai(eMP_随机);
			g_pMainState->AddEnemy(petid, lv, (eMengPai)mp, "坏人");

			lv = g_pMainState->getAvgLv();
			for (int i = 0; i < 2; ++i)
			{
				petid = cct::getPetModel(lv1, lv2);
				int mp = cct::getMenpai(eMP_随机);
				g_pMainState->AddEnemy(petid, lv, (eMengPai)mp, "坏人");
			}
			g_StateType = STATE_FIGHT;
			AddTriggerFightSuccess(401);
			AddTriggerFightEscape(403);
			AddTriggerFightFalse(402);
		}
			break;
		case 401:
			g_pMainState->m_Map.RemoveNpc(m_YuanJiu.m_name);
			if (m_SuccessNum >= 0)
			{
				auto& d = g_pMainState->m_Dialog;
				d.Reset();
				d.m_ContextList.m_Name.SetString("同门");
				d.m_ContextList.m_Name.UpdateXCenter();
				d.SetHead(g_pMainState->m_pCharacterDataList[m_YuanJiu.m_modeid - 2000].m_Head[2].m_dialog);
				d.SetString("谢谢你及时赶到,我回去复命了");
				d.OnOff(true);
				Process(1001);
			}
			else
			{
				Process(403);
			}
			break;
		case 402:
			g_pMainState->m_pFightState->DieEffect(1);
		case 403:
			if (m_SuccessNum < 0)
			{
				g_pMainState->m_Map.RemoveNpc("苦战中的同门");
				g_pMainState->m_Map.AutoGetPos(m_YuanJiu.m_x, m_YuanJiu.m_y, m_YuanJiu.m_mapname);
				string strJob, strTalk;
				getTongMen(m_YuanJiu, strTalk, strJob);
				UpdateJob(strJob);
				AddTriggerObjMap(&m_YuanJiu, 400);
				g_pHeroObj->Talk("未完成,继续");
			}
			break;
// 		case 7:
// 		{
// 			string text;
// 			m_SuccessNum += 1;
// 			if (m_SuccessNum == 2)
// 			{
// 				GetJiangLi();
// 				text = "回去告诉你师父吧,我再也不敢了";
// 				g_pMainState->m_InterfaceDoor.SetTrigger(0, 0);
// 			}
// 			else
// 			{
// 				text = "我跑.继续捣乱去";	
// 
// 			}
// 			g_pMainState->m_Dialog.Reset();
// 			g_pMainState->m_Dialog.m_ContextList.m_Name.SetString(m_enemyname);
// 			g_pMainState->m_Dialog.SetHead(m_enemyface);
// 			g_pMainState->m_Dialog.SetString(text);
// 			g_pMainState->m_Dialog.OnOff(true);
// 		}
// 		break;
// 		case 8:	
// 			if (0 == g_pMainState->m_Map.m_MapName.compare(m_Npc.m_mapname))
// 			{
// 				g_pMainState->m_Map.AddNpc(&m_Npc, this, "无", 9);
// 			}
// 			break;
// 		case 9:
// 		{
// 			g_pMainState->AddPCEnemy(m_Npc.m_name, 0, g_pCharacter->m_PcData.m_Lv, 0, 0, (eMengPai)(rand() % 12), 0, m_Npc.m_modeid);
// 
// 			g_StateType = STATE_FIGHT;
// 			m_bXiangFuSuccess = false;
// 			AddTriggerFightSuccess(10);
// 		}
// 			break;
// 		case 10:
// 		{
// 			g_pMainState->m_Map.RemoveNpc(m_Npc.m_name);
// 			if (m_bXiangFuSuccess)
// 			{
// 				g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->Talk("抓到了,回去报告师父吧");
// 					
// 				sJob job;
// 				job.m_Context = "回去把乾坤袋给师父";
// 				job.m_Title = "降伏";
// 				job.m_Time = 40;
// 				job.m_pTask = this;
// 				g_pMainState->m_Job.ReMoveJob(this);
// 				g_pMainState->m_Job.AddaJob(job);
// 				g_pMainState->m_TriggerObjMap.ReMove(this);
// 				string sfname = g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PCData.m_MengPaiID)->m_Name;
// 				g_pMainState->m_TriggerGive.AddTask(sfname, 11, 28, this, 11);
// 			}
// 			else
// 			{
// 				g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
// 				m_Npc.m_name += g_pMainState->m_TaskBaoTu.AutoMakeName();
// 				ostringstream oss;
// 				oss << "有个#R";
// 				oss << m_Npc.m_name;
// 				oss << "#R在江湖上为非做歹,现被为师打伤,听说他在#R";
// 				oss << m_Npc.m_mapname;
// 				oss << "#R#Y";
// 				oss << m_Npc.m_x / 20;
// 				oss << " ";
// 				oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
// 				oss << "#Y养伤,你去用乾坤袋将他降伏带回来";
// 		
// 				sJob job;
// 				job.m_Title = "降伏";
// 				job.m_Time = 40;
// 				job.m_Context = oss.str();
// 				job.m_pTask = this;
// 				g_pMainState->m_Job.ReMoveJob(this);
// 				g_pMainState->m_Job.AddaJob(job);
// 				g_pMainState->m_FightList[g_pMainState->m_HeroID].m_pData->Talk("让他跑了,再去找他吧");
// 			}
// 		}
// 		break;
// 
// 		case 12:	
// 		{
// 			string shifuname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_ShiFuName;
// 			if (0 == g_pMainState->m_pNowSelect->m_TrueName.GetString().compare(shifuname))
// 			{
// 				for (int i = g_pCharacter->m_PCData.m_NumofBB - 1; i >= 0; i--)
// 				{
// 					if (g_pCharacter->m_PCData.m_pPetDataList[i]->GetData()->m_ID == m_TargetBBid)
// 					{
// 						g_pCharacter->m_PCData.DeletePet(i);
// 						GetJiangLi();
// 						string targetname = g_pMainState->m_pNowSelect->m_TrueName.GetString();
// 						g_pMainState->FindObjByName(targetname)->Talk("做的不错,继续努力");
// 						return true;
// 					}
// 
// 				}
// 			}
// 		}
// 		return false;
// 	case 13:
// 	{
// 		sPetData* pPetdata = g_pMainState->m_PetDataManager.GetPetData(m_TargetBBid);
// 		int moneyneed = pPetdata->m_LvTake * 200 + 5500;
// 		cObj* pre = g_pMainState->m_Dialog.m_pObj;
// 		g_pMainState->m_Dialog.Reset();
// 		g_pMainState->m_Dialog.SetObj(pre);
// 		g_pMainState->m_Dialog.SetTrigger(this, 14, 14, 14, 14, 14);
// 		ostringstream oss;
// 		oss << "购买#R";
// 		oss << pPetdata->m_Name;
// 		oss << "#R需要#Y";
// 		oss << moneyneed;
// 		oss << "#Y两,确定要买吗?";
// 		g_pMainState->m_Dialog.SetString(oss.str(), "购买");
// 		g_pMainState->m_Dialog.OnOff(true);
// 	}
// 		break;
// 	case 14:
// 	// 做师门的
// 	{
// 		if (g_pMainState->m_Dialog.m_retSelect == 0)
// 		{
// 
// 			sPetData* pPetdata = g_pMainState->m_PetDataManager.GetPetData(m_TargetBBid);
// 			int moneyneed = pPetdata->m_LvTake * 200 + 5500;
// 			if (g_pCharacter->m_PcData.m_Money[0] >= moneyneed)
// 			{
//  			cPet* pet = new cPet;
//  			pet->AutoPetData(m_TargetBBid, 1, 0);
//  			pet->m_PetData.LeveUp(g_pCharacter->m_PcData.m_Lv, true, true);
//  			g_pCharacter->m_PcData.AddPet(pet);
// 
// 				ostringstream oss;
// 				oss << "购买";
// 				oss << pPetdata->m_Name;
// 				oss << "花费";
// 				oss << moneyneed;
// 				oss << "两";
// 				g_pMainState->m_Tags.Add(oss.str());
// 				g_pCharacter->m_PcData.m_Money[0] -= moneyneed;
// 			}
// 			else
// 			{
// 				g_pMainState->m_Tags.Add("盘缠不足");
// 			}
// 		}
// 	}
// 		break;
// 	case 100://送到信
// 	{
// 		string name = g_pMainState->m_InterfaceGive.GetTarget()->m_TrueName.GetString();
// 		if (0 == name.compare(m_npcname))
// 		{
// 			if (g_pMainState->m_InterfaceGive.m_NumItem[0].m_num)
// 			{
// 				sItem2& item = g_pMainState->m_InterfaceGive.m_ItemGive[0];
// 				if (item.GetType() == 28)
// 					if (item.GetID() == 18)
// 					{
// 					//	g_pCharacter->m_PCData.m_Item[g_pMainState->m_InterfaceGive.m_ItemGiveOwner[0]].m_Num = 0;
// 					g_pMainState->m_InterfaceGive.GetTarget()->Talk("信已经收到了,回去告诉你师父吧");
// 					Process(1000);
// 					AddTriggerObj(GetShiFuName(), GetShiFuMap(), 11);
// 					return true;
// 					}
// 			}
// 
// 		}
// 	}
// 		return false;
// 	case 101:
// 	{
// 		string name = g_pMainState->m_InterfaceGive.GetTarget()->m_TrueName.GetString();
// 		if (0 == name.compare(g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_ShiFuName))
// 		{
// 			if (g_pMainState->m_InterfaceGive.m_NumItem[0].m_num)
// 			{
// 				sItem2& item = g_pMainState->m_InterfaceGive.m_ItemGive[0];
// 				if (item.GetType() == m_ItemNeed.GetType())
// 					if (item.GetID() == m_ItemNeed.GetID())
// 					{
// 					//	g_pCharacter->m_PCData.m_Item[g_pMainState->m_InterfaceGive.m_ItemGiveOwner[0]].m_Num -= 1;
// 					GetJiangLi();
// 
// 					g_pMainState->m_InterfaceGive.GetTarget()->Talk("表现的不错,这是奖励");
// 					return true;
// 					}
// 			}
// 
// 		}
// 	}
// 		return false;
//	default:
//		break;
	}
	return true;
}

#if 0
void cTaskSM::AddTask(int type)
{
	switch (type)
	{
		//
	case 0://送信

	{
		//..........
		string  npcname;
		cObj pShiFu;
		if (g_pCharacter->m_PCData.m_MengPaiID < 0 || g_pCharacter->m_PCData.m_MengPaiID>11)
			return;
		npcname = m_NameList[g_pCharacter->m_PCData.m_MengPaiID][rand() % m_NameList[g_pCharacter->m_PCData.m_MengPaiID].size()];
		if (npcname == "")
			return;
		m_npcname = npcname;
		ostringstream oss;
		oss << "这里有一封给#R";
		oss << npcname;
		oss << "#R的信,麻烦你送过去";
		DialogTalkNObj(oss.str());

		UpdateJob(oss.str());
		AddTriggerGive(npcname, 28, 18, 100);
		SetJiangLiItem(18, 28);
	}
		break;
	case	1://要0级装备
	case	2://要垃圾药品
	case	3://要包子
	case	4://要10-30装备
	case	6://要垃圾药
	case	9://要东西
	case	12://要1级家具
	case	13://要2级家具
	case	14://要三级药
	case	15://要烹饪
	case	16://要60-70环
	case	17://要花 ,乐
	case	18://要黄纸等
	case	19://要40-50环

	{
		int	itemtype = -1;
		int	itemid = -1;

		switch (type)
		{
		case 1:
			itemtype = rand() % 23;
			if (itemtype == 13)itemtype = rand() % 13;
			itemid = 0;
			break;
		case 2:
			itemtype = 22;
			switch (rand() % 6)
			{
			case 0:itemid = 1; break;
			case 1:itemid = 2; break;
			case 2:itemid = 19; break;
			case 3:itemid = 20; break;
			case 4:itemid = 26; break;
			default:itemid = 34; break;
			}
			break;
		case 3:
			itemtype = 23;
			itemid = 0;
			break;
		case 4:
			itemtype = rand() % 23;
			if (itemtype == 13)itemtype = rand() % 13;
			itemid = g_pMainState->m_ItemManage.GetIDByLv(itemtype, (rand() % 3 + 1) * 10);
			break;
		case	6://要垃圾药
			itemtype = 22;
			switch (rand() % 6)
			{
			case 0:itemid = 3; break;
			case 1:itemid = 4; break;
			case 2:itemid = 21; break;
			case 3:itemid = 22; break;
			case 4:itemid = 26; break;
			default:itemid = 35; break;
			}
			break;
		case	9://要宝石
			itemtype = 29;
			switch (rand() % 6)
			{
			case 0:itemid = 0; break;
			case 1:itemid = 8; break;
			case 2:itemid = 14; break;
			case 3:itemid = 6; break;
			case 4:itemid = 5; break;
			default:itemid = 4; break;
			}
			break;
		case	12://要1级家具
			itemtype = 35;
			itemid = rand() % 15;
			break;
		case	13://要2级家具
			itemtype = 36;
			itemid = rand() % 15;
			break;
		case	14://要高级药
			itemtype = 22;
			switch (rand() % 6)
			{
			case 0:itemid = 7; break;
			case 1:itemid = 8; break;
			case 2:itemid = 23; break;
			case 3:itemid = 24; break;
			case 4:itemid = 31; break;
			default:itemid = 36; break;
			}
			break;
		case	15://要烹饪
			itemtype = 23;
			switch (rand() % 6)
			{
			case 0:itemid = 1; break;
			case 1:itemid = 2; break;
			case 2:itemid = 3; break;
			case 3:itemid = 5; break;
			case 4:itemid = 6; break;
			default:itemid = 7; break;
			}
			break;
		case	16://要60-70环
			itemtype = rand() % 23;
			if (itemtype == 13)itemtype = rand() % 13;
			itemid = g_pMainState->m_ItemManage.GetIDByLv(itemtype, (rand() % 2 + 6) * 10);
			break;
		case	17://要花 ,乐
			if (rand() % 2)
			{
				itemtype = 30;
				itemid = rand() % 2;
			}
			else
			{
				itemtype = 39;
				itemid = rand() % 6;
			}
			break;
		case	18://要黄纸等
			itemtype = 27;
			switch (rand() % 3)
			{
			case 0:itemid = 52; break;
			case 1:itemid = 53; break;
			case 2:itemid = 54; break;
			}
			break;
		case	19://要40-50环
			itemtype = rand() % 23;
			if (itemtype == 13)itemtype = rand() % 13;
			itemid = g_pMainState->m_ItemManage.GetIDByLv(itemtype, (rand() % 2 + 4) * 10);
			break;
		default:
			return;
		}
		m_ItemNeed.Set(itemtype, itemid);

		ostringstream oss;
		oss << "去帮为师买个#R";
		oss << m_ItemNeed.GetName();
		oss << "#R回来";
		UpdateJob(oss.str());
		AddTriggerGive(g_pMainState->m_Dialog.m_pObj->m_TrueName.GetString(), itemtype, itemid, 101, 1);
		DialogTalkNObj(oss.str());
	}
		break;
	case	5://巡逻

	{
		DialogTalkNObj("近来有些不法之徒在门派捣乱,现在派你去将他们就地斩杀");
		UpdateJob("在门派巡逻");
		m_mapname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID].m_XunLuoMapName;
		AddTriggerObjMap(m_mapname, 5);
	}
		break;
	case	7://降伏
	{
		if (!m_bInitXiangFu)InitXiangFu();

		cObj* pPreObj = g_pMainState->m_Dialog.m_pObj;
		g_pMainState->m_Dialog.Reset();
		g_pMainState->m_Dialog.SetObj(pPreObj);
		g_pMainState->m_Dialog.m_pObj = 0;

		m_Npc.m_name = m_XiangFuNameList[rand() % m_XiangFuNameList.size()];
		m_Npc.m_mapname = m_XiangFuDiDianList[rand() % m_XiangFuDiDianList.size()];
		g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);

		ostringstream oss;
		oss << "有个#R";
		oss << m_Npc.m_name;
		oss << "#R在江湖上为非做歹,现被为师打伤,听说他在#R";
		oss << m_Npc.m_mapname;
		oss << "#R#Y";
		oss << m_Npc.m_x / 20;
		oss << " ";
		oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
		oss << "#Y养伤,你去用乾坤袋将他降伏带回来";
		DialogTalkNObj(oss.str());
		UpdateJob(oss.str());
		m_Npc.m_modeid = rand() % 40 + g_pCharacter->m_PcData.m_Lv / 5;
		AddTriggerObjMap(&m_Npc, 8);
	}
		break;
	case	8://要召唤兽

	{
		m_TargetBBid = rand() % 20 + g_pCharacter->m_PcData.m_Lv / 5;
		string bbname = g_pMainState->m_PetDataManager.GetPetData(m_TargetBBid)->m_Name;
		ostringstream oss;
		oss << "替为师抓只#R";
		oss << bbname;
		oss << "#R回来";
		DialogTalkNObj(oss.str());
		cMengPai& mp = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[g_pCharacter->m_PCData.m_MengPaiID];
		m_Npc.m_name = mp.m_ShiFuName;
		m_Npc.m_mapname = mp.m_ShiFuMap;
		AddTriggerObj(m_Npc.m_name, m_Npc.m_mapname, 12);
		UpdateJob(oss.str());
	}
		break;
	case	10://示威

	{
		if (!m_bInitShiWei)InitShiWei();
		m_EnemyMengPai = rand() % 12;
		m_Npc.m_mapname = g_pMainState->m_SkillManager.m_MengPaiManager.m_MengPai[m_EnemyMengPai].m_XunLuoMapName;
		m_Npc.m_name = m_ShiWeiNameList[m_EnemyMengPai][rand() % m_ShiWeiNameList[m_EnemyMengPai].size()];
		m_Npc.m_modeid = m_ShiWeiIdList[m_EnemyMengPai][rand() % m_ShiWeiIdList[m_EnemyMengPai].size()];
		g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
		ostringstream oss;
		oss << m_Npc.m_mapname;
		oss << "的#R";
		oss << m_Npc.m_name;
		oss << "#R多次袭击本门弟子,现躲在#R";
		oss << m_Npc.m_mapname;
		oss << m_Npc.m_x / 20;
		oss << "  ";
		oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
		oss << "#R,你去给ta点厉害瞧瞧";
		string text = oss.str();
		DialogTalkNObj(oss.str());
		g_pMainState->m_TriggerObjMap.AddTask(this, 15, m_Npc);

		int weapontype[2];
		GetWeaponType(m_Npc.m_modeid, weapontype[0], weapontype[1]);
		int typenum = 2;
		if (weapontype[1] == -1)typenum = 1;
		int weaponid1, weapontype1;
		weapontype1 = weapontype[rand() % typenum];
		weaponid1 = g_pMainState->m_ItemManage.GetIDByLv(weapontype1, (rand() % 6 + 9) * 10);
		m_ShiWeiWeapon.Set(weapontype1, weaponid1);
		m_ShiWeiWeapon.m_Num = 1;
		UpdateJob(oss.str());
	}
		break;
	case	11://援救

	{
		if (!m_bInitShiWei)InitShiWei();
		if (!m_bInitXiangFu)InitXiangFu();
		m_EnemyMengPai = rand() % 12;
		m_Npc.m_mapname = m_XiangFuDiDianList[rand() % m_XiangFuDiDianList.size()];
		m_Npc.m_name = m_ShiWeiNameList[m_EnemyMengPai][rand() % m_ShiWeiNameList[m_EnemyMengPai].size()];
		m_Npc.m_modeid = m_ShiWeiIdList[m_EnemyMengPai][rand() % m_ShiWeiIdList[m_EnemyMengPai].size()];
		g_pMainState->m_Map.AutoGetPos(m_Npc.m_x, m_Npc.m_y, m_Npc.m_mapname);
		ostringstream oss;
		oss << "#R";
		oss << m_Npc.m_name;
		oss << "#R正在#R";
		oss << m_Npc.m_mapname;
		oss << m_Npc.m_x / 20;
		oss << "  ";
		oss << (g_pMainState->m_Map.m_BmpTest.GetHeight() - m_Npc.m_y) / 20;
		oss << "#R,袭击本门弟子,你快去援救";
		string text = oss.str();
		DialogTalkNObj(text);
		m_YuanJiu.m_name = "苦战中的同门";
		m_YuanJiu.m_x = m_Npc.m_x;
		m_YuanJiu.m_y = m_Npc.m_y;
		m_YuanJiu.m_direction = m_Npc.m_direction;
		m_YuanJiu.m_modeid = rand() % 14;;

		g_pMainState->m_TriggerObjMap.AddTask(this, 19, m_YuanJiu);
		int weapontype[2];
		GetWeaponType(m_Npc.m_modeid, weapontype[0], weapontype[1]);
		int typenum = 2;
		if (weapontype[1] == -1)typenum = 1;
		int weaponid1, weapontype1;
		weapontype1 = weapontype[rand() % typenum];
		weaponid1 = g_pMainState->m_ItemManage.GetIDByLv(weapontype1, (rand() % 6 + 9) * 10);
		m_ShiWeiWeapon.Set(weapontype1, weaponid1);
		m_ShiWeiWeapon.m_Num = 1;
		UpdateJob(text);
	}
		return;
	}
}
#endif

void cTaskSM::GetJiangLi()
{
	int lv = m_HuanShu + 20;
	int exp, money;
// 	if (lv < 40)
// 	{
// 		exp = (1500 - lv * 12);
// 		money = (700 - lv * 9);
// 	}
// 	if (lv < 70)
// 	{
// 		exp = (2100 - lv * 12);
// 		money = (1400 - lv * 13);
// 	}
// 	if (lv < 100)
// 	{
// 		exp = (2700 - lv * 11);
// 		money = (1700 - lv * 10);
// 	}
// 	if (lv < 130)
// 	{
// 		exp = (3300 - lv * 11);
// 		money = (2000 - lv * 11);
// 	}
// 	else
	{
		exp = (3900 - lv * 8);
		money = (2300 - lv * 8);
	}
	exp = (exp * 15 * lv) / 3;
	money = (money * 15 * lv) / 20;
	lv = g_pCharacter->m_PcData.m_Lv;
	exp = exp * lv / cct::MaxRoleLv;
	money = money * lv / cct::MaxBabyLv;
	SetJiangLi2(exp, money, 0, exp);
//	m_HuanShu += 1;
//	g_pCharacter->m_PcData.m_MengPaiPoint += 1;
	m_bHaveTask = false;
//	Process(1000);
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
	if (m_XiangFuDiDianList.empty())
	{
		m_XiangFuDiDianList = cct::getFields();
	}
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
	if (-1 == g_pCharacter->m_PcData.m_MengPaiID)return "";
	return g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PcData.m_MengPaiID)->m_ShiFuName;
}
std::string cTaskSM::GetShiFuMap()
{
	if (-1 == g_pCharacter->m_PcData.m_MengPaiID)return "";
	return g_pMainState->m_SkillManager.m_MengPaiManager.GetMengPai(g_pCharacter->m_PcData.m_MengPaiID)->m_ShiFuMap;
}
void cTaskSM::InitShiWei()
{
	return;
	m_bInitShiWei = true;
	ifstream File;
	ostringstream oss;
//	oss << g_pathData << "师门\\师门示威.txt";
	File.open(oss.str());
	if (!File)ERRBOX;
	string name;
	int num;
	int id;
	for (int i = 0; i < c_MenPaiNumber; i++)
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
	job.Set("师门任务", context, 30, this, 20);
	g_pMainState->m_Job.AddaJob(job, m_HuanShu);
}

void cTaskSM::Save(ofstream& File)
{
	File << m_HuanShu << " ";
	File << m_bHaveTask << " ";
	if (!m_bHaveTask)return;
	File << m_bXiangFuSuccess;
	m_Npc.Save(File);
	File << m_EnemyMengPai;
	m_ShiWeiWeapon.Save(File);//示威时NPC的武器
	m_YuanJiu.Save(File);
	File << m_TargetBBid;
	m_ItemNeed.Save(File);//记录当前师门要的东西
	File << m_npcname << " "; //记录当前师门要找的人
	File << m_mapname << " ";
	File << m_SuccessNum << " ";
	File << m_enemyname << " ";
	File << m_enemyface << " ";
}

void cTaskSM::Load(ifstream& File)
{
	m_bInitShiWei = false;
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
	File >> m_npcname; //记录当前师门要找的人
	File >> m_mapname;
	File >> m_SuccessNum;
	File >> m_enemyname;
	File >> m_enemyface;
}

void cTaskSM::Init()
{
	m_type = 1003; 
	m_bInit2 = true; 
	m_HuanShu = g_GlobalValues[4];
	return;
	if (g_GlobalValues[4])
	{
		m_HuanShu = g_GlobalValues[4];
		if (m_HuanShu >= 10)
		{
			m_HuanShu = 1;
		}
	}
	else 
	{
		m_HuanShu = 1;
	}
}
