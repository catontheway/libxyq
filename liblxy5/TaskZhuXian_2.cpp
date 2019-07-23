#include "_global.h"


bool TaskZhuXian::Process2(int stage)
{
	setJobTitle("玄奘的身世(中篇)");

	static int s_hadG;
	switch (stage)
	{
	case 0:
		AddTriggerDialog("定颜珠一块钱一斤~大甩卖咯", "这么便宜? 赝品吧?", "货真价值! 这可是我从龙宫宝库带出来的", "我啥都没听见~");
		g_pMainState->m_pNowSelect->say("定颜珠一块钱一斤~大甩卖咯", 0xFFFF);
		break;
	case 1:
	{
		auto pc = AddEnemy(15000, e虾兵, 40, eMP_东海龙宫);
		pc->getObj()->say("我可啥都没说啊#17");

		AddEnemy(8000, e蛤蟆精, 40, eMP_随机);
		AddEnemy(8000, e海星, 40, eMP_随机);
		AddEnemy(8000, e章鱼, 40, eMP_物理);
		AddEnemy(8000, e海毛虫, 40, eMP_输出);
		AddEnemy(8000, e巨蛙, 40, eMP_随机);
		AddEnemy(8000, e大海龟, 40, eMP_随机);
		AddEnemy(8000, e小泡泡, 40, eMP_物理);

		g_pMainState->m_FightWorkList[13 + rand() % 5].m_pObj->say("别怂!咱们水族怕过谁#118");

		readyFightAndSucces();
	}
	break;
	case 2:
		clearSay();
		g_pMainState->awardEquip(40);
		AddTriggerDialog("别打了我认怂#15", 
			"反正我正顺路去龙宫#24, 修为太低了,不借助避水珠下不了水啊,你咋不顺便牵个避水珠出来卖", 
			"#15酆都那边有位山神,他有避水珠", "正好,那边有位樵夫,过去问问");

		AddJob("去酆都那边找樵夫#R大生#R问问山神在哪\n大唐国境90 220");
		getTag("定颜珠s");
		break;
	case 3:
		AddTriggerObj("大生");
		break;
	case 4:
		g_pMainState->awardk(80, 20);
		g_pMainState->FindObjByName("大生")->say("#R山神#R在40 240");
		g_pHeroObj->say("不用谢#24");
	//	AddTriggerDialog("坐标 40 240", "砍柴的人就是爽快#24");
		AddJob("向#R山神#R借避水珠\n大唐国境 40 240" + g_strNeedBattle);
		AddTriggerObj("山神", "大唐国境", _next + 2);
		break;

		break;
	case 7:
		AddTriggerDialog("", "臭豆腐没有! 梅花酒太贵!", 
			"#24我还什么都没说呢", 
			"我不管!把避水珠交出来!", 
			"你哪只耳朵看见我有避水珠?", 
			"我眼睛看见了,豆腐又酒的,少吃零食多吃饭会胖啊? 你看那边江州传遁凌波城的土地,胖的辣么可爱", 
			"你伤我自尊了#14,瘦廋拳捶你");
		break;
	case 8:
	{
		AddEnemy(15000, e雨师, 40, eMP_辅助);
		AddEnemy(8000, e大蝙蝠, 40, eMP_随机);
		AddEnemy(8000, e树怪, 40, eMP_随机);
		AddEnemy(8000, e小浣熊, 40, eMP_输出);
		AddEnemy(8000, e野猪, 40, eMP_随机);
		AddEnemy(8000, e羊头怪, 40, eMP_随机);
		AddEnemy(8000, e老虎, 40, eMP_输出);
		AddEnemy(8000, e黑熊, 40, eMP_输出);

		readyFightAndSucces();
		break;
	}
	case 9:
		g_pMainState->awardEquip(30);
		AddTriggerObj("山神");
		g_pMainState->FindObjByName("山神")->say("#15我还不如回龙窟当野怪,不做仙班基层人员了");
		break;
	case 10:
		g_pMainState->awardk(80, 30);
		AddTriggerDialog("", "避水珠, 谢啦");
		AddJob("出发东海龙宫\n#R蟹将军#R\n龙宫 30 15" + g_strNeedBattle);
		break;
	case 11:
		AddTriggerObj("蟹将军", "龙宫");
		break;
	case 12:
		g_pMainState->setNowSelect();
		AddTriggerDialog("来者何人何神何仙何魔!",
			"just wait a minute!#8");
		break;
	case 13:
	{
		AddEnemy(20000, e蟹将, 45, eMP_东海龙宫, "蟹将军");
		AddEnemy(10000, e碧水夜叉, 45, eMP_随机);
		AddEnemy(10000, e鲛人, 45, eMP_随机);
		AddEnemy(10000, e蚌精, 45, eMP_随机);
		AddEnemy(10000, e龟丞相, 45, eMP_随机);
		AddEnemy(10000, e虾兵, 45, eMP_输出);
		AddEnemy(10000, e虾兵, 45, eMP_输出);
		AddEnemy(10000, e虾兵, 45, eMP_输出);

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
		s_hadG = 0;
		break;
	}
	case 14:
	{
		int idG = -1;
		int num = 0;
		const sFightWork* fw = nullptr;
		for (int i = 10; i < 20; ++i)
		{
			const sFightWork& l = g_pMainState->m_FightWorkList[i];
			if (!l.isExist)
			{
				continue;
			}
			if (num == 0)
			{
				fw = &l;
			}
			if (l.m_pObj->m_TrueName.GetString() == "龙将军")
			{
				idG = i;
				break;
			}
			++num;
		}
		if (idG < 0 && num < 5 && fw && !s_hadG)
		{
			int bbmode = g_pMainState->m_Map.m_EnemyList[rand() % g_pMainState->m_Map.m_NumOfEmemyType];
			sPetData* pm = g_pMainState->m_PetDataManager.GetPetData(bbmode);
			auto ppp = AddEnemy(20000, e蛟龙, 50, eMP_东海龙宫, "龙将军");
			int cid = ppp->m_IDinFightWorkList;
			g_pMainState->m_pFightState->PrePareToFight(cid);
			ppp->FillHpMp();
			cObj* obj = ppp->getObj();
			obj->SetXY(g_pMainState->m_pFightState->m_战斗坐标xs[cid], g_pMainState->m_pFightState->m_战斗坐标ys[cid]);
			obj->MoveShadow();
			obj->MoveDialog();
			obj->MoveHpLine();
			obj->UpdateHpLine();
			obj->MoveName();
			g_pMainState->FindObj();
			fw->m_pObj->say("来者不善,呼叫龙将军");
			s_hadG = 1;
		}
		else if (idG >= 0 && g_pMainState->m_FightWorkList[idG]._myTurn == 1)
		{
			g_pMainState->m_FightWorkList[idG].m_pObj->say("看本将军力挽狂澜#2");
		}
	}
		break;
	case 15:
		clearSay();
		g_pMainState->awardEquip(50);
		AddTriggerDialog("", "停!#90我有盗宝定颜珠的线索", "#17进");
		AddJob("和#R龟千岁#R交谈\n龙宫 100 60");
		break;
	case 16:
		AddTriggerObj("龟千岁");
		break;
	case 17:
		g_pMainState->awardk(100, 30);
		lostTag("定颜珠s");
		AddTriggerDialog("非常感谢少侠帮我们解决了定颜珠事件，至于关于那个凡人，当年我们龙宫水族的确有救过，不过那人伤好了我们就把他送回岸上了，至于去了哪里我们也不知道", "好吧, 回去告诉殷温娇吧");
	//	AddJob("送信\n长安城 殷府\n#R殷丞相#R");
		AddJob("将陈光蕊的事情告诉#R殷温娇#R\n大唐国境\n江州\n衙门");
		break;
	case 18:
		AddTriggerObj("殷温娇", "大唐国境");
		break;
	case 19:
		AddTriggerDialog("感谢少侠，夫君还活着就好，如今我与婆婆走散已久，少侠可否愿意帮忙？", "有奖励当然愿意#24");
		break;
	case 20:
		AddTriggerObj("小二");
		AddJob("打听婆婆的消息\n#R小二#R\n大唐国境 60 70");
		break;
	case 21:
		AddTriggerDialog("老婆婆？刚才那边望见一个人，好像就是一位老人家");
		break;
	case 22:
		AddJob("打听到消息了，好像就是#R婆婆#R\n大唐国境 30 30" + g_strNeedBattle);
		g_pMainState->FindObjByName("婆婆")->say("..我好...饿！#52");
		{
			sNpc npc;
			npc.Set("地痞", "大唐国境", e赌徒, 26, 31, DIRECTION_LEFT);
			AddTriggerObjMap(&npc, _next, false);

			npc.Set("流氓", "大唐国境", e强盗, 21, 29, DIRECTION_RIGHT);
			AddTriggerObjMap(&npc, _next, false);

			npc.Set("恶霸", "大唐国境", e山贼, 24, 25, DIRECTION_UP);
			AddTriggerObjMap(&npc, _next, false);
		}
		g_pMainState->FindObjByName("地痞")->say("..喂喂喂...老太婆，该交保护费了！#52");
		g_pMainState->FindObjByName("流氓")->say(".....饿！...我也挺饿的#52");
		g_pMainState->FindObjByName("恶霸")->say("..少废话...赶紧把钱交出来！#52");
		break;
	case 23:
		AddTriggerDialog("老太婆！有什么值钱的东西赶快交出来！");
		break;
	case 24:
		g_pMainState->setNowSelect("婆婆", g_pMainState->m_pNpcList[57].m_dialog);
		AddTriggerDialog("..我好...饿！#52", "住手！！！我有钱！！！");
		break;
	case 25:
	{
		auto p = AddEnemy(10000, e赌徒, 5, "恶霸");
		p->getObj()->say("大侠我们知道错了#15");
		AddEnemy(10000, e强盗, 5, "地痞");
		AddEnemy(10000, e山贼, 5, "流氓");


		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
		break;
	}
	case 26:
	{
		for (int i = 10; i < 20; ++i)
		{
			auto& list = g_pMainState->m_FightWorkList[i];
			if (!list.isExist)
			{
				continue;
			}
			list.m_SkillSelect.SkillID = 1006;
			list.m_SkillSelect.TargetID = i;
		//	list.SetWork(WORKTYPE_MAGIC);
			list.m_WorkType = WORKTYPE_MAGIC;
			break;
		}
	}
	break;
	case 27:
		clearSay();
		g_pMainState->m_Map.RemoveNpc("地痞", true);
		g_pMainState->m_Map.RemoveNpc("流氓",  true);
		g_pMainState->m_Map.RemoveNpc("恶霸",  true);
		RemoveTriggerObjMap(26, 31);
		RemoveTriggerObjMap(21, 29);
		RemoveTriggerObjMap(24, 25);
		AddTriggerObj("婆婆");
		break;
	case 28:
		g_pMainState->awardk(50, 20);
		AddTriggerDialog("", "来，婆婆，吃点包子，慢点别噎着，水喏~");
		break;
	case 29:
		getTag("婆婆");
		g_pMainState->m_Map.RemoveNpc("婆婆", true);
		AddTriggerObj("殷温娇");
		AddJob("果然是婆婆，带回去见#R殷温娇#R吧\n大唐国境\n江州\n衙门");
		break;
	case 30:
		// ，还有这封书信，也请少侠日后帮我送到长安城内殷府
		// getTag("殷温娇的书信");
		lostTag("婆婆");
		AddTriggerDialog("婆婆...感谢少侠，这封书信，还请少侠帮我送到#R长安城#R内#R殷府#R");
		AddJob("送信\n长安城 殷府\n#R殷丞相#R");
	case 31:
		AddTriggerObj("殷丞相", "丞相府");
		break;
	case 32:
		lostTag("殷温娇的书信");
		AddTriggerDialog("多年不见女儿回娘家这，原来竟是因为那个谁刘洪#14");
		break;
	case 33:
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("殷夫人");
		AddTriggerDialog("我可怜的女儿啊#15", "哎，我出去叹个气...");
		g_pMainState->m_pNowSelect->say("我可怜的女儿啊#15");
		AddJob("殷夫人一病不起, 找#R玉露羹#R给夫人服下\n听说#R#R江湖奸商#R有卖");
		break;
	case 34:
		AddTriggerGive("殷夫人", 22, 58, _next);
		break;
	case 35:
		g_pMainState->awardk(0, 50);
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("殷夫人");
		AddTriggerDialog("谢谢你，我好多了");
		break;
	case 36:
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("殷丞相");
		AddTriggerDialog("这是老夫的奏折，请少侠带去给皇宫#R圣上#R请求出兵讨伐刘洪！", "殷丞相的奏折.get() !");
		getTag("殷丞相的折奏");
		AddJob("皇宫上奏!\n长安城\n金銮殿\n#R李世民#R");
		break;
	case 37:
		AddTriggerObj("李世民", "金銮殿");
		break;
	case 38:
		AddTriggerDialog("朕的大唐居然会有这种事！#R魏爱卿#R，给这几位少侠办理相关事务");
		lostTag("殷丞相的折奏");	
		AddJob("皇宫上奏!\n长安城\n金銮殿\n#R魏征#R");
		break;
	case 39:
		AddTriggerObj("魏征");
		break;
	case 40:
		AddTriggerDialog("请几位少侠带兵前往#R大唐国境#R的#R江州衙门#R讨伐#R刘洪!#R");
		getTag("兵符");
		AddJob("讨伐刘洪!\n大唐国境\n江州 衙门\n先和#R殷温娇#R说一下");
		break;
	case 41:
		AddTriggerObj("殷温娇", "大唐国境");
		break;
	case 42:
		AddTriggerDialog("兵都带来了，看来信已经送到了", "放心，我这就进#R衙门#R去撸#R刘洪#R给你们家平冤#16");
		break;
	case 43:
		AddTriggerDialog("", "进#R衙门#R去撸#R刘洪#R#16");
		break;
	case 44:
		AddTriggerDialog("", "进#R衙门#R去撸#R刘洪#R#16");
		break;
	case 45:
		RemoveTriggerObj();
		g_pMainState->m_Job.ReMoveJob(this);
		break;

#if 0
		//四琉璃
	case 0:
		SetChapter(2);
		g_GlobalValues[5] = 2;
		AddTriggerDialog2(0, -1);
		AddTriggerObj2(1, 2, 1);
		UpdateJob2(16);
		break;
	case 1://卷帘大将
		AddTriggerDialog2(1, -1);
		AddTriggerObj2(3, 4, 2);
		UpdateJob2(15);
		break;
	case 2://粟粟娘
		AddTriggerDialog2(2, -1);
		AddTriggerObj2(5, 6, 3);
		UpdateJob2(17);
		break;
	case 3://女妖
		AddTriggerDialog2(3, 4);
		break;
	case 4:
	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(10000, e芙蓉仙子, 50, eMP_盘丝岭, 5);
		pPet->LiveHp += 10;
		pPet->ComboRate.d1 += 20;
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 3)
			{
			case 0:petid = e赌徒;
				break;
			case 1:petid = e强盗;
				break;
			default:petid = e山贼;
				break;
			}
			Add变身Enemy2(8000, petid, 40);
		}
		SetMusic("镜影命缘");

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(5);
	}
		return true;
	case 5:
	{
		SetJiangLi2(450000, 100000, 50000, 450000);
		AddTriggerDialog2(4, -1);
		AddTriggerObj2(7, 6, 6);
		UpdateJob2(18);
		// 			g_pCharacter->m_PCData.AddDefZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(57);
	}
		return true;
	case 6://金琉璃
		AddTriggerDialog2(5, 7);
		break;
	case 7:
	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(10000, e如意仙子, 59, eMP_盘丝岭, 7);
		pPet->HitRateOfPoison.d1 += 20;
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 3)
			{
			case 0:petid = e蜘蛛精;
				break;
			case 1:petid = e狐狸精;
				break;
			default:petid = e蝴蝶仙子;
				break;
			}
			Add变身Enemy2(8000, petid, 50);
		}
		SetMusic("镜影命缘");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(8);
	}
		return true;
	case 8:
	{
		g_pMainState->m_Friend.AddFriend(m_Textlist[28]);
		AutoGetPet(m_Textlist[28]/*, 0*/);
		SetJiangLi2(480000, 100000, 50000, 480000);
		AddTriggerDialog2(6, 88);
		AddTriggerObj2(8, 4, 9);
		UpdateJob2(15);
		// 			g_pCharacter->m_PCData.AddDefZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(59);
	}
		return true;
	case 88:
		g_pMainState->m_Friend.Invite(m_Textlist[28]);
		AddChannel2(29);
		break;
	case 9://柳飞絮
		AddTriggerDialog2(7, -1);
		AddTriggerObj2(9, 10, 10);
		UpdateJob2(20);
		break;
	case 10://青琉璃
		AddTriggerDialog2(8, -1);
		AddTriggerObj2(26, 10, 11);
		UpdateJob2(21);
		break;
	case 11://翻天怪
		AddTriggerDialog2(9, 12);
		break;
	case 12:
	{
		cPropertyData* p = Add变身Enemy2(10000, e地狱战神, 60, eMP_魔王寨, 26);
		p->StabRate.d1 = 100;
		p->StabPercent.d1 = 40;
		Add变身Enemy2(8000, e白熊, 60);
		Add变身Enemy2(8000, e古代瑞兽, 60);

		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(13);
	}
		return true;
	case 13:
	{
		SetJiangLi2(500000, 100000, 50000, 500000);
		AddTriggerDialog2(10, -1);
		AddTriggerObj2(9, 10, 14);
		UpdateJob2(22);
		//			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(75);
	}
		return true;
	case 14://青琉璃
		AddTriggerDialog2(11, -1);
		AddTriggerObj2(11, 10, 15);
		AddTriggerGive(m_Textlist[9], 22, 30, 17);
		UpdateJob2(23);
		break;
	case 15:AddTriggerDialog2(12, 16); break;
	case 16:
		SetJiangLiItem(30, 22);
		SetJiangLi2(0, 40000);
		RemoveTriggerObj();
		AddTriggerDialog2(23, -1);
		break;
	case 17://青琉璃
		AddTriggerDialog2(13, -1);
		AddTriggerObj2(1, 2, 18);
		UpdateJob2(16);
		break;
	case 18://卷帘大将
		AddTriggerDialog2(14, -1);
		AddTriggerObj2(12, 2, 19);
		UpdateJob2(24);
		break;
	case 19://阿紫
		AddTriggerDialog2(15, -1);
		AddTriggerObj2(1, 2, 20);
		UpdateJob2(16);
		break;
	case 20://卷帘大将
		AddTriggerDialog2(16, -1);
		AddTriggerObj2(12, 2, 21);
		UpdateJob2(24);
		break;
	case 21://姚太尉
		AddTriggerDialog2(17, 22);
		break;
	case 22:
	{
		cPropertyData* ppet = Add变身Enemy2(20000, e天将, 69, eMP_天宫, 27);
		ppet->SetJinJie(2);
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 2)
			{
			case 0:petid = e天兵;
				break;
			default:petid = e天将;
				break;
			}
			Add变身Enemy2(8000, petid, 59);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(23);
	}
		return true;
	case 23:
	{
		SetJiangLi2(550000, 100000, 50000, 550000);
		AddTriggerDialog2(18, 123);
		AddTriggerObj2(1, 2, 24);
		UpdateJob2(16);
		// 			g_pCharacter->m_PCData.AddAtkZZ(100);
		// 			g_pCharacter->m_PCData.AddGrowing(2);
		g_pMainState->LockLv(65);
	}
		return true;
	case 123:AddTriggerDialog2(24, -1); return true;
	case 24://卷帘大将
		AddTriggerDialog2(19, -1);
		AddTriggerObj2(13, 14, 25);
		UpdateJob2(25);
		break;
	case 25://王母娘娘
		AddTriggerDialog2(20, 26);
		break;
	case 26:
	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(20000, e超级孔雀, 69, eMP_天宫);
		pPet->ComboNumDown += 1;
		ePetID petid;
		for (int i = 0; i < 7; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e凤凰;
				break;
			case 1:petid = e雨师;
				break;
			case 2:petid = e蛟龙;
				break;
			default:petid = e风伯;
				break;
			}
			Add变身Enemy2(10000, petid, 59);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(27);
	}
		return true;
	case 27:
	{
		SetJiangLi2(550000, 100000, 50000, 550000);
		AddTriggerDialog2(21, -1);
		AddTriggerObj2(1, 2, 28);
		UpdateJob2(16);
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		// 			g_pCharacter->m_PCData.AddDefZZ(100);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(75);
	}
		return true;
	case 28://卷帘大将
		TalkList(22, -1, -1, 30, -1);
		g_pMainState->m_TaskZhuaGui.SetTrigger(this, 3, 29);
		break;
	case 29://转到西梁女国剧情
		Process8(0);
		return true;
#endif
	default:
		ERRBOX2(stage);
		break;

	}


	return true;
}
