#include "_global.h"


bool TaskZhuXian::Process3(int stage)
{
	//小白龙
	setJobTitle("玄奘的身世(下篇)");
	switch (stage)
	{
	case 0:
		AddTriggerDialog("大胆! 衙...", "行了，何必为虎作伥呢，一看就知道你是假冒伪劣的，消息挺灵通的嘛，那么快就跑掉了", 
			"我是不会告诉你刘大人跑去大唐境外了的！", 
			"不用告诉我洽洽手指也算得出来，长安城有大唐官府 化生寺 两大门派坐镇，酆都那边的阴曹地府 我量他也不敢去，更不敢叫土地神或者传送使者带去凌波城、女魃墓、普陀山了，随便碰到个厉害一点的门派弟子也够他喝一壶的", 
			"分析......很到位啊，可是，不了我这关你的剧情照样没法推进#18", 
			"言之有理竟无言以对,#4这就很好办了");
		break;
	case 1:
	{
		AddEnemy(20000, e护卫, 50, eMP_辅助, "伪-刘洪");
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(10000, e护卫, 45, eMP_随机);
		}

		for (int i = 0; i < 5; ++i)
		{
			AddEnemy(10000, e护卫, 45, eMP_输出);
		}

		if (g_pMainState->m_InterfaceTeam.getLeaveBegin() == 5)
		{
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
		}
		auto pc = AddEnemy(0, e镖头, 29, eMP_大唐官府, "郑将军", nullptr, -1, -1, true);
		if (pc)
		{
			pc->PointRemain = cct::PointRemian;
			pc->setPointAfterLv(g_pMainState->getAddpointFromMp(eMP_大唐官府, true), true);
			pc->autoEquip(false);
			pc->autoData(false, true, true);
			pc->apply();
			pc->m_Controler.Set(0);
			g_pMainState->m_pFightState->m_FightMenu.SetControl(pc->m_IDinFightWorkList, false);

			g_pMainState->setNowSelect(pc->getObj());
		}
		readyFightAndSucces();
	}
		break;
	case 2:
		g_pMainState->FindObjByName("刘洪")->say("为了刘头,拖住他们!");
		g_pMainState->awardEquip(50);
		AddTriggerObj("刘洪");
		break;
	case 3:
		g_pMainState->awardk(100, 30);
		g_pMainState->m_pNowSelect = nullptr;
		AddTriggerDialog("", "比之前的看门守卫厉害多了#24这不科学啊", 
			"少侠先去追刘洪吧，不然他们再往西边跑那就不好找了，少侠若是需要，可以去长安我老弟的镖局，讨几本阵书#83",
			"这都什么时候了还惦记着自家生意...");
		AddJob("真-#R刘洪#R\n大唐境外 590 20" + g_strNeedBattle);
		break;
	case 4:
		AddTriggerObj("刘洪", "大唐境外");
		break;
	case 5:
		AddTriggerDialog("就你们几个追过来，看来我的手下们还真能拖住你们的兵力#28", 
			"得了吧，你要不害怕那你跑什么，过不了多久我们的将军就通关赶过来了", 
			"无所谓，看得出来你们不是官府军队的人，身手也颇为不凡，不过争取这点时间把你们几个打残也是绰绰有余了", 
			"对不起，待会你会被打脸的#90");
		break;
	case 6:
	{
		auto pc = AddEnemy(200000, e强盗, 40, eMP_大唐官府, "刘洪");
		pc->LiveHp = 100000;
		pc = AddEnemy(200000, e山贼, 40, eMP_阴曹地府, "李彪");
		pc->LiveHp = 100000;
		pc->Speed.AddDataAdd(8000);
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(15000, e护卫, 45, eMP_随机);
		}

		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(15000, e护卫, 45, eMP_输出);
		}

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
	}
	break;
	case 7:
	{		
		int lnum = g_pMainState->GetLiveNum(10, 20);
		if (lnum == 1)
		{
			g_pMainState->m_pFightState->SuccessFight();
			break;
		}
		if (lnum != 2)
		{
			break;
		}

		cPcData* lb = g_pMainState->m_FightWorkList[11].m_pObj->getPcData();
		cPcData* lh = g_pMainState->m_FightWorkList[10].m_pObj->getPcData();
		lh->DmgAdd.d2 -= 1000000;
		lb->Hit.AddDataAdd(1000000);
		
		auto& list = g_pMainState->m_FightWorkList[11];
		list.m_pObj->ReMoveState(eBuffType封印);
		auto& ski = list.m_SkillSelect;

// 		if (list.m_work.empty())
// 		{
// 			list.SetWork(WORKTYPE_ATTACK);
// 		}
// 		list.GetWork()->type = 
		list.m_WorkType = WORKTYPE_ATTACK;
		list.targetID = ski.TargetID = 10;
		ski.SkillID = 1000;

// 		list.m_MaxTargetNum = 1;
// 		list.targetlist[0] = 10;

		lb->getObj()->say("哼,没用的废物!");
		lh->getObj()->say("别这样!");
	}
	break;
	case 8:
		g_pMainState->awardEquip(50);
		AddTriggerObj("刘洪");
		g_pMainState->FindObjByName("刘洪")->say("求...求你...帮我照...顾#R江州#R的#R老母亲#R...呃~");
		AddJob("看一下#R刘洪#R吧");
		break;
	case 9:
		g_pMainState->awardk(150, 40);
		AddTriggerDialog("求...求你...帮我照...顾#R江州#R的#R老母亲#R...呃~", "......");
		AddJob("想不到副官#R李彪#R才是幕后BOSS" + g_strNeedBattle);
		break;
	case 10:
		g_pMainState->FindObjByName("刘洪")->m_ShowTime = 0;
		g_pMainState->m_Map.RemoveNpc("刘洪", true);
		AddTriggerObj("李彪");
		break;
	case 11:
		AddTriggerDialog("凡人终究靠不住...", "听你这么说我就明白了，我说你的手下怎么那么厉害， 是你冲了话费送了什么法宝？现出原形瞅瞅？#90");
		break;
	case 12:
		
		g_pMainState->setNowSelect("李彪.", g_pMainState->m_PetDataManager.m_PetList[e骷髅怪].m_dialoghead[0]);
		AddTriggerDialog("瞅啥瞅！", "骷髅怪？呸#60，在人间野了这么久，做多少害人的勾当，洗白了也是侮辱了我的金柳露#4");
		break;
	case 13:
	{
		auto pc = AddEnemy(30000, e骷髅怪, 50, eMP_阴曹地府, "李彪");
		pc->LiveHp += 1000;
		pc->LiveRestoreRate += 50;
		pc->StartMagic = ePS_法术防御 + 2000;
		pc->DmgPercentOfFix.d2 += 30;
		pc->DmgPercentOfMagic.d2 += 20;
		pc->HitRateOfSeal.d1 += 10000;
		pc->DmgAddOfCure.d1 += 800;

		for (int i = 0; i < 4; ++i)
		{
			pc = AddEnemy(20000, e火星人, 50, eMP_随机, "傀儡");
		}

		for (int i = 0; i < 5; ++i)
		{
			pc = AddEnemy(20000, e火星人, 50, eMP_输出, "傀儡");
		}

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
		break;
	}
	case 14:
	{

		auto& list0 = g_pMainState->m_FightWorkList[10];
		if (!list0.isExist)
		{
			break;
		}
		cPropertyData* data = list0.m_pObj->getPropertyData();
		if (!data->m_FightData.cannotMagic)
		{
			list0.m_WorkType = WORKTYPE_MAGIC;
			auto& ski = list0.m_SkillSelect;
			list0.targetID = ski.TargetID = -1;
			ski.SkillID = 122;
			ski.SkillLv = cct::MaxSkillLv;
		}
		auto& gs = data->m_FightData.m_guardID;
		for (int i = 11; i < 20; ++i)
		{
			auto& list = g_pMainState->m_FightWorkList[i];
			if (!list.isExist)
			{
				continue;
			}

// 			g_pMainState->m_FightWorkList[Objselect].m_pObj->GetPropertyData(pTargetData);
// 			pTargetData->m_FightData.m_guardID.push_back(m_NowFighterID);
// 			m_pSkillSelect = 0;
// 			g_pMainState->m_FightWorkList[m_NowFighterID].m_WorkType = -2;
			if (std::find(gs.begin(), gs.end(), i) == gs.end())
			{
				gs.push_back(i);
			}
		}
	}
		break;
	case 15:
		g_pMainState->awardEquip(60);
		g_pMainState->FindObjByName("李彪")->say("悔不该省话费啊!");
		RemoveTriggerObj();
		g_pMainState->m_pNowSelect = nullptr;
		AddJob("#R刘将军#R也赶过来了");
		{
			sNpc npc;
			npc.Set("郑将军", "大唐境外", e镖头, 580, 20, DIRECTION_RIGHT);
			AddTriggerObjMap(&npc, _next, false);
		}
		break;
	case 16:
		g_pMainState->awardk(200, 50);
		lostTag("兵符");
		AddTriggerDialog("李彪都奄奄一息了，真是英雄出少年啊", "哪里，还请将军把它带回大雁锁妖塔", "末将这就去办");
		break;
	case 17:
		RemoveTriggerObjMap(580, 20);
		g_pMainState->m_Map.RemoveNpc("郑将军", true);
		g_pMainState->m_Map.RemoveNpc("李彪", true);
		AddJob("还是去看一下刘洪的母亲#R刘母#R吧\n大唐国境 250 300");
		AddTriggerObj("刘母", "大唐国境");
		break;
	case 18:
		AddTriggerDialog("我儿哎，报应啊...", "也罢，留些银两您过日子吧...");
		break;
	case 19:
		AddJob("和#R殷温娇#R交谈\n大唐国境\n江州 衙门");
		AddTriggerObj("殷温娇");
		break;
	case 20:
		AddTriggerDialog("少侠的平冤之恩难以回报#15", "已经回报了很多经验和装备了#24，其实做这件事本身就是最大的回报了#1", "#120还请少侠告知江流儿安心修法渡化世人");
		break;
	case 21:
		AddJob("和#R玄奘#R交谈\n大唐国境\n#R金山寺#R内");
		AddTriggerObj("玄奘", "金山寺");
		break;
	case 22:
		AddTriggerDialog("家仇得报，复知父母平安，从今以后发愿立意安禅：愿以此功德，庄严佛净土。上报四重恩，下济三途苦。若有见闻者，悉发菩提心。同生极乐国，尽报此一身");
		break;
	case 23:
		AddTag("完成<玄奘的身世>剧情");
		g_pMainState->m_Job.ReMoveJob(this);
		g_pMainState->awardEquip(50);
		break;

#if 0
	case 0:
		g_GlobalValues[5] = 4;
		SetChapter(3);
		AddTriggerObj2(7, 8, 1);
		UpdateJob2(9);
		AddTriggerDialog2(1, -1);
		break;
	case 1://小白龙
		AddTriggerDialog2(2, 2);
		break;
	case 2://超级海豚
	{
		cPropertyData* petdata = AddPetEnemy2(20000, e超级海豚, 89/*, eMP_东海龙宫*/);
		petdata->MagicWater.d1 += 20;
		ePetID petid;
		for (int i = 0; i < 6; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e龟丞相; break;
			case 1:petid = e鲛人; break;
			case 2:petid = e蟹将; break;
			default:petid = e小龙女; break;
			}
			Add变身Enemy2(10000, petid, 69);
		}
		SetMusic("Paranoia");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(5);
	}
		return true;
	case 5:
	{
		SetJiangLi2(800000, 100000, 50000, 800000);
		AddChannel2(27);
		AddChannel2(38);
		AddTriggerObj2(7, 8, 6);

		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		// 			g_pCharacter->m_PCData.AddAvoidZZ(100);
		// 			g_pCharacter->m_PCData.AddHpZZ(100);
		//			g_pMainState->LockLv(67);

		// 			sShangPinPet sppet;
		// 			sAddPoint addpoint;
		// 			addpoint.Set(0, 0, 4, 1, 0);
		// 			sppet.Set(e超级海豚,&addpoint,100,true);
		// 			GetPet(m_Textlist[35], &sppet, 100);
	}
		break;
	case 6://小白龙
		TalkList(0, 10, 11, 12, 7);
		break;
	case 7://塔塔之神
		AddTriggerDialog2(6, -1);
		AddTriggerObj2(13, 14, 8);
		UpdateJob2(15);
		break;
	case 8://奔波儿霸
		AddTriggerDialog2(7, -1);
		AddTriggerObj2(16, 17, 9);
		UpdateJob2(18);
		break;
	case 9://蟹将
		AddTriggerDialog2(8, 10);
		break;
	case 10://蟹将
	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(20000, e蟹将, 89, eMP_东海龙宫);
		pPet->MagicWater.d2 += 20;
		ePetID petid;
		for (int i = 0; i < 6; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e蚌精; break;
			case 1:petid = e鲛人; break;
			case 2:petid = e蟹将; break;
			default:petid = e虾兵; break;
			}
			Add变身Enemy2(10000, petid, 69);
		}
		SetMusic("魔方少女纹");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(11);
	}
		return true;
	case 11:
	{
		SetJiangLi2(810000, 100000, 50000, 810000);
		AddTriggerDialog2(9, -1);
		AddTriggerObj2(19, 17, 12);
		UpdateJob2(20);
		// 			g_pCharacter->m_PCData.AddMagZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(70);
	}
		return true;
	case 12://万胜公主
	{
		AddTriggerDialog2(10, -1);
		AddTriggerObj2(21, 22, 13);
		UpdateJob2(23);

	}
		break;
	case 13://九头精怪
		g_pMainState->SetDialogListNpc(m_Textlist[19], 1001);
		AddTriggerDialog2(11, 14);
		break;
	case 14://
	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(20000, e九头精怪, 90, eMP_狮驼岭, 21);
//		pPet->m_AtkDownHPHurt.d1 = 5;
		pPet = Add变身Enemy2(20000, e蚌精, 90, eMP_东海龙宫, 19);
		pPet->MagicWater.d2 += 20;
		pPet->SetJinJie(3);
		ePetID petid;
		for (int i = 0; i < 8; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e牛妖; break;
			case 1:petid = e犀牛将军; break;
			case 2:petid = e犀牛将军人; break;
			default:petid = e野猪精; break;
			}
			Add变身Enemy2(8000, petid, 69);
		}
		SetMusic("redmoon");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(15);
	}
		return true;
	case 15:
	{
		g_pMainState->ClearDialogList();
		SetJiangLi2(850000, 100000, 50000, 850000);

		AddTriggerDialog2(12, -1);
		AddTriggerObj2(24, 25, 16);
		UpdateJob2(26);
		g_pMainState->ClearDialogList();
		// 			g_pCharacter->m_PCData.AddHpZZ(600);
		// 			g_pCharacter->m_PCData.AddGrowing(2);
		g_pMainState->LockLv(85);
	}
		return true;
	case 16://玉皇大帝
		AddTriggerDialog2(13, -1);
		AddTriggerObj2(7, 8, 17);
		UpdateJob2(9);
		break;
	case 17://小白龙
		TalkList(14, -1, -1, -1, -1, 18);
		break;
	case 18:
		Process4(0);
		break;
#endif
	default:
		ERRBOX2(stage);
		break;

	}

	
	return true;
}
