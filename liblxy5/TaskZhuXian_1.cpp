#include "_global.h"



bool TaskZhuXian::Process1(int stage)
{
	static string s_jobTitle = "玄奘的身世(上篇)";
	static string s_needbattle = "\n(需战斗)";
	int next = stage + 1;
	switch (stage)
	{
	case 0:
		g_pMainState->setNowSelect();
		AddTriggerDialogList({ "我的白鹿去哪了?", "好的知道了#28这就去给大仙您找回来"}, next);
		AddJob(s_jobTitle, "去#R大唐境外#R找#R白鹿精#R" + s_needbattle);
		break;
	case 1:
		AddTriggerObj("白鹿精", "大唐境外", next);
		break;
	case 2:
		g_pMainState->setNowSelect();
		AddTriggerDialogList({ "老头子叫你来的是不,我不回去", "看来刚刚修成人形#24这跟孩子似的叛逆期", 
			"我不管我要跟小狐狸在一起#97"}, next);
		break;
	case 3:
	{
		auto pc = g_pMainState->AddEnemy(e九色鹿, 25, eMP_凌波城, "白鹿精");
		pc->HPMax.SetData(5000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e狐狸精, 25, eMP_盘丝岭, "玉面狐狸");
		pc->HPMax.SetData(5000);
		pc->FillHpMp();
		pc->getObj()->say("敢调戏小白,看老娘不打飞你们#24");


		pc = g_pMainState->AddEnemy(e花妖, 20, eMP_随机);
		pc->HPMax.SetData(3000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e树怪, 20, eMP_随机);
		pc->HPMax.SetData(3000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e小浣熊, 20, eMP_随机);
		pc->HPMax.SetData(3000);
		pc->FillHpMp();

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		break;
	case 4:
		clearSay();
		g_pMainState->awardEquip(30);
		g_pHeroObj->Talk("这么拗, 回去问问仙翁吧");
		AddJob(s_jobTitle, "回#R长寿村#R找#R南极仙翁#R");
		AddTriggerObj("南极仙翁", "长寿村", next);
		break;
	case 5:
		g_pMainState->awardk(20, 10);
		g_pMainState->m_pNowSelect->Talk("罢了罢了,当初点化它时资质就一般,如今动了凡心就随它去吧,事关天下众生,玄奘乃佛系金婵子转世,老仙道家多有不便,少侠可以先去找#R化生寺#R的#R法明长老#R了解一下有关玄奘的身世");
		AddTriggerObj("法明长老", "大雄宝殿", next);
		AddJob(s_jobTitle, "去#R化生寺#R里的#R大雄宝殿#R拜访#R法明长老#R");
		break;
	case 6:
		g_pMainState->m_pNowSelect->Talk("这份血书, 少侠交给玄奘, 他就都清楚了");
		AddTriggerObj("玄奘", "金山寺", next);
		AddJob(s_jobTitle, "把血书交给#R玄奘#R\n#R金山寺#R");
		getTag("玄奘身世的血书");
		break;
	case 7:
		g_pMainState->m_pNowSelect->Talk("敌军还有三十秒到达战场!");
		AddTriggerObj("酒肉和尚", "金山寺", next);
		AddJob(s_jobTitle, "肯定是#R酒肉和尚#R搞鬼,不要问为什么知道" + s_needbattle);
		break;
	case 8:
		g_pMainState->setNowSelect();
		AddTriggerDialogList({"我羡慕嫉妒恨啊!从小师父就宠着他,现在住持讲法都是他,他不过是个没有父母的野孩子!", "这就是你下毒的理由?"}, next);
		break;
	case 9:
	{
		auto pc = g_pMainState->AddEnemy(e慧海, 30, eMP_化生寺, "酒肉和尚");
		pc->HPMax.SetData(6000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e慧海, 30, eMP_物理, "木鱼僧");
		pc->HPMax.SetData(6000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e慧海, 30, eMP_法系, "敲钟僧");
		pc->HPMax.SetData(6000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e慧海, 30, eMP_封系, "扫地僧");
		pc->HPMax.SetData(6000);
		pc->FillHpMp();

		pc = g_pMainState->AddEnemy(e慧海, 30, eMP_辅助, "门僧");
		pc->HPMax.SetData(6000);
		pc->FillHpMp();

		g_pMainState->m_FightWorkList[11 + rand() % 4].m_pObj->say("谁有吃的喝的俺就跟谁");

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		break;
	case 10:
		clearSay();
		g_pMainState->awardEquip(40);
		AddTriggerDialogList({ "", "解药交出来!", "哈哈哈,解药什么的不存在的", "...就知道你这么说,我有别的办法,你等着寺规伺候吧" }, next);
		AddJob(s_jobTitle, "找仙医#R青莲仙女#R看看有什么办法能解玄奘的毒\n普陀山->潮音洞");
		break;
	case 11:
		AddTriggerObj("青莲仙女", "潮音洞", next);
		break;
	case 12:
		g_pMainState->awardk(30, 15);
		g_pMainState->setNowSelect();
		AddTriggerDialogList({ "我这有份丹药,需要配合孟婆汤方能生效", "看来是要跑一趟#R阴曹地府#R了" }, next);
		AddJob(s_jobTitle, "找#R孟婆#R讨要孟婆汤\n#R阴曹地府#R");
		g_pMainState->awardItem(22, 45, 1, true);
		break;
	case 13:
		AddTriggerObj("孟婆", "阴曹地府", next);
		break;
	case 14:
		AddTriggerDialogList({ "原来是青莲仙女的指引, 这样吧, #R地狱迷宫一层#R的#R幽冥鬼#R死活不肯喝我的汤,少侠帮我劝劝他, 事成之后便给你熬一份" }, next);
		AddJob(s_jobTitle, "劝#R幽冥鬼#R喝汤\n#R地狱迷宫一层#R" + s_needbattle);
		break;
	case 15:
		AddTriggerObj("幽冥鬼", "地狱迷宫一层", next);
		break;
	case 16:
		AddTriggerDialogList({ "我不喝我不喝我就不喝!宝宝生气了!", "cho tto ma tte ku da sa! #35"}, next);
		break;
	case 17:
	{
		auto pc = g_pMainState->AddEnemy(e巡游天神, 35, eMP_阴曹地府, "幽冥鬼");
		pc->HPMax.SetData(10000);
		pc->FillHpMp();
		g_pMainState->setNowSelect(pc->getObj());

		for (int i = 0; i < 7; ++i)
		{
			int r = rand() % 100;
			int m = e僵尸;
			if (r < 35)
			{
				m = e野鬼;
			}
			else if (r < 65)
			{
				m = e骷髅怪;
			}
			else
			{
				m = e僵尸;
			}
			pc = g_pMainState->AddEnemy(m, 30, eMP_随机);
			pc->HPMax.SetData(6000);
			pc->FillHpMp();
		}
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
		break;
	case 18:
		g_pMainState->awardEquip(40);
		AddTriggerDialogList({ "", "请给个合理的解释", "我还惦记着我家文秀#17", "信物拿来#68" }, next);
		AddJob(s_jobTitle, "带幽冥鬼的信物给#R文秀#R\n#R大唐国境#R\n江州民居2");
		getTag("幽冥鬼的信物");
		break;
	case 19:
		AddTriggerObj("文秀", "江州民居2", next);
		break;
	case 20:
		g_pMainState->awardk(50, 20);
		AddTriggerDialogList({ "谢谢你, 请把这个带给他, 让他一切放心"}, next);
		AddJob(s_jobTitle, "带文秀的信物给#R幽冥鬼#R\n#R地狱迷宫一层#R");
		lostTag("幽冥鬼的信物");
		getTag("文秀的信物");
		break;
	case 21:
		AddTriggerObj("幽冥鬼", "地狱迷宫一层", next);
		break;
	case 22:
		AddTriggerDialogList({ "好了#1少侠回去告诉#R孟婆#R吧,我接受这份满满的孟婆汤"}, next);
		AddJob(s_jobTitle, "终于可以去找#R孟婆#R了\n#R阴曹地府#R");
		lostTag("文秀的信物");
		break;
	case 23:
		AddTriggerObj("孟婆", "阴曹地府", next);
		break;
	case 24:
		g_pMainState->m_pNowSelect->Talk("谢谢你,这是孟婆汤,快去忙吧");
	//	AddTriggerObj("玄奘", "金山寺", next);
		AddTriggerGive("玄奘", 22, 45, 25);
		AddJob(s_jobTitle, "给#R玄奘#R喂#R九转还魂丹#R\n(给予)\n#R金山寺#R");
		getTag("孟婆汤");
		break;
	case 25:
		lostTag("孟婆汤");
		lostTag("玄奘身世的血书");
		g_pMainState->setNowSelect(g_pMainState->FindObjByName("玄奘"));
		AddTriggerDialogList({ "这血书...原来我身世中藏此深仇大恨!原来母亲尚在#15"}, next);
		RemoveTriggerGive();
		break;
	case 26:
		AddTriggerDialogList({ "", "咱一起打听,多份人手多份力#107" }, next);
		getTag("玄奘身世的血书");
		AddJob(s_jobTitle, "听说衙门有位妇女伸冤无果\n#R大唐国境#R\n江州\n衙门\n#R衙门守卫#R" + s_needbattle);
		break;
	case 27:
		AddTriggerObj("衙门守卫", "大唐国境", next);
		break;
	case 28:
		AddTriggerDialogList({ "站住,什么事?办理相关业务需要先交手续费#90", "话说没有更简单暴力的办法么?"}, next);
		break;
	case 29:
	{
		auto pc = g_pMainState->AddEnemy(e护卫, 35, eMP_无底洞);
		pc->HPMax.SetData(8000);
		pc->FillHpMp();
		g_pMainState->setNowSelect(pc->getObj());

		pc = g_pMainState->AddEnemy(e护卫, 35, eMP_化生寺);
		pc->HPMax.SetData(8000);
		pc->FillHpMp();

		for (int i = 0; i < 6; ++i)
		{
			pc = g_pMainState->AddEnemy(e护卫, 35, eMP_输出);
			pc->HPMax.SetData(8000);
			pc->FillHpMp();
		}

		g_pMainState->m_FightWorkList[10 + rand() % 8].m_pObj->say("咱人多不用怕#28");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(next);
	}
	break;
	case 30:
		clearSay();
		g_pMainState->awardEquip(40);
		AddTriggerDialogList({ "大侠请进请进#17", "有请进费吗?", "有有有,这些,这些,还有这些,呵呵呵"}, next);
		break;
	case 31:
		g_pMainState->awardk(0, 30);
		AddTriggerObj("殷温娇", "大唐国境", next);
		AddJob(s_jobTitle, "进衙门看看#R殷温娇#R\n大唐国境\n江州\n衙门");
		break;
	case 32:
		g_pMainState->awardk(50);
		lostTag("玄奘身世的血书");
		AddTriggerDialogList({ "这就是我当年作的血书#52", "夫人莫激动", "当时夫君陈光蕊考上了状元，恰巧父亲殷丞相替我抛绣球招亲,那绣球恰打着光蕊的乌纱帽, 我二人由此成就了一段姻缘" }, next);
		break;
	case 33:
		AddTriggerDialogList({ "而后光蕊赴任江州, 到了洪江渡口。艄公刘洪、李彪见色起意, 杀了光蕊和家僮,逼我顺从。当时洪江上波涛汹涌,似有水族经过,事后不见夫君尸首，我寻思无计,只得顺了刘洪" }, next);
		break;
	case 34:
		AddTriggerDialogList({ "刘洪穿了光蕊衣冠，带了官凭文书，同我往江州上任去了。刘洪利用职位之便，买通一些官府和衙门上下，我伸冤至今没有回应" }, next);
		break;
	case 35:
		AddTriggerDialogList({ "那时我担心怀着的孩子有危险，三月后孩子生下后，顺水放走，但恐难以识认，即咬破手指，写下血书一纸，将父母姓名、跟脚原由，备细开载。又将此子左脚上一个小指，用口咬下，以为记验" }, next);
		break;
	case 36:
		AddTriggerDialogList({ "", "不见尸首...三月后孩子生下...小指用口咬下...信息量好大啊...\n\n#110" }, next);
		break;
	case 37:
		AddTriggerDialogList({ "我怀疑夫君当时是被水族所救,少侠帮我去江下龙宫水族问问", "行，看我遁水~(刚才路过好像看到有个水族#R虾兵#R, 去问问)" }, next);
		break;
	case 38:
		AddTriggerDialogList({ "", "(刚才路过好像看到有个水族#R虾兵#R, 去问问)" }, next);
		break;
	case 39:
		AddTriggerDialogList({ "", "(刚才路过好像看到有个水族#R虾兵#R, 去问问)" }, next);
		break;
	case 40:
		g_pMainState->FindObjByName("虾兵")->say("定颜珠一块钱一斤~大甩卖咯", 0xFFFF);
		RemoveTriggerObj();
		g_pMainState->m_Job.ReMoveJob(this);
		break;


#if 0
	case 0:AddTriggerDialog2(0, 1); break;
	case 1://找南极仙翁
		Un邀请("怀念");
		Un邀请("敖白");
		Un邀请("紫菜");
		RemoveTriggerObj();
		UpdateJob2(1);
		AddTriggerObj2(2, 3, 2);
//		g_pMainState->LockLv(36);
		g_GlobalValues[4] = 1;
		break;
	case 2:AddTriggerDialog2(1, 3); break;
	case 3://找白鹿
		AddTriggerObj2(5, 4, 4);
		UpdateJob2(6);
		break;
	case 4:
		AddTriggerDialog2(2, 5);
		break;
	case 5: //白鹿战斗

	{
		//			m_AddPoint = g_addPointAtk;
		Add变身Enemy2(3000, e九色鹿, 20, eMP_大唐官府, 5);
		//			m_AddPoint = g_addPointSpd;
		Add变身Enemy2(3000, e狐狸精, 20, eMP_方寸山, 65);
		//			m_AddPoint = g_addPointMag;
		for (int i = 0; i < 3; ++i)
		{
			AddPetEnemy2(2000, e花妖, 30);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(6);
	}
		return true;
	case 6://白鹿奖励

	{
		SetJiangLi2(100000, 20000, 50000, 200000, true);
		AddTriggerDialog2(3, 7);
		// 			g_pCharacter->m_PCData.AddDefZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(37);
	}
		return true;
	case 7:

	{
		UpdateJob2(1);
		AddTriggerObj2(2, 3, 8);
	}
		break;
	case 8:
		AddTriggerDialog2(4, -1);
		AddTriggerObj2(7, 8, 9);
		UpdateJob2(9);
		g_pCharacter->AddMoney(0, -500);
		g_GlobalValues[3] = 1;//学会仙灵
		break;
	case 9:
		AddTriggerDialog2(5, -1);
		AddTriggerObj2(10, 11, 10);
		UpdateJob2(15);
		break;
	case 10:AddTriggerDialog2(6, 11);
		AddTriggerObj2(10, 11, 11);
		break;
	case 11://酒肉1

	{
		//			m_AddPoint = g_addPointSpd;
		Add变身Enemy2(3000, e雨师, 30, eMP_化生寺, 10);
		//			m_AddPoint = g_addPointAtk;
		for (int i = 0; i < 4; i++)
		{
			AddPetEnemy2(2000, e赌徒, 40);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(12);
	}
		break;
	case 12:

	{
		AddTriggerObj2(12, 13, 13);
		AddTriggerDialog2(7, -1);
		SetJiangLi2(150000, 20000, 50000, 200000);
		UpdateJob2(14);
		//			g_pCharacter->m_PCData.AddGrowing(1);
	}
		break;
	case 13:
		g_pMainState->m_Friend.AddFriend("清风");
		AutoGetPet("清风"/*, 0*/);
		AddTriggerDialog2(8, -13);
		AddTriggerObj2(16, 17, 14);
		UpdateJob2(19);
		break;
	case -13:

	{
		g_pMainState->m_Friend.Invite("清风");
		RemoveTriggerObjMap();
	}
		break;
	case 14:AddTriggerDialog2(9, 15); break;//天将
	case 15:

	{
		//			m_AddPoint = g_addPointSpd;
		Add变身Enemy2(3000, e天将, 35, eMP_天宫, 16);
		//			m_AddPoint = g_addPointAtk;
		for (int i = 0; i < 4; i++)
		{
			AddPetEnemy2(2000, e天兵, 45);
		}
		SetMusic("绯雪千夜");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(16);

	}
		break;
	case 16:
		AddTriggerObj2(20, 8, 17);
		AddTriggerDialog2(10, -1);
		SetJiangLi2(180000, 20000, 50000, 120000);
		UpdateJob2(18);
		// 		g_pCharacter->m_PCData.AddDefZZ(50);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		//		g_pMainState->LockLv(39);
		break;
	case 17:
		AddTriggerDialog2(11, 19);
		break;
	case 19://白琉璃

	{
		//			m_AddPoint = g_addPointSpd;
		Add变身Enemy2(3000, e星灵仙子, 39, eMP_阴曹地府, 20);
		//			m_AddPoint = g_addPointMag;
		for (int i = 0; i < 4; i++)
		{
			AddPetEnemy2(2000, e小龙女, 40);
		}
		SetMusic();

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(20);

	}
		break;
	case 20:
		RemoveTriggerObj();
		AddTriggerGive(m_Textlist[12], 22, 44, 21);
		AddTriggerDialog2(12, -1);
		SetJiangLi2(200000, 50000, 50000, 100000);
		UpdateJob2(38);
		// 		g_pCharacter->m_PCData.AddHpZZ(100);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(35);
		break;
	case 21:
		AddTriggerDialog2(13, -21);
		UpdateJob2(21);
		AddTriggerObj2(22, 11, 22);
		g_pMainState->m_Friend.AddFriend(m_Textlist[64]);
		break;
	case -21:g_pMainState->m_Friend.Invite(m_Textlist[64]);
		break;
	case 22:AddTriggerDialog2(14, 23);
		break;
	case 23://酒肉2

	{
		//			m_AddPoint = g_addPointSpd;
		Add变身Enemy2(5000, e雨师, 40, eMP_化生寺, 10);
		ePetID petid;
		for (int i = 0; i < 5; i++)
		{
			//				m_AddPoint = g_addPointAtk;
			switch (rand() % 3)
			{
			case 0:petid = e赌徒;
				break;
			case 1:
				petid = e强盗;
				//					m_AddPoint = g_addPointMag;
				break;
			default:petid = e山贼;
				break;
			}
			AddPetEnemy2(3000, petid, 49);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(24);
	}
		break;
	case 24:
		TalkList(15, 23, 24, 39, 125);
		SetJiangLi2(240000, 20000, 50000, 250000);
		// 		g_pCharacter->m_PCData.AddAtkZZ(50);
		// 		g_pCharacter->m_PCData.AddHpZZ(100);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		//		g_pMainState->LockLv(42);
		break;
	case 125://青莲仙女

	{
		TalkList(49, 75, 76, 77, 126);
		sTaskMapObj obj;
		obj.m_Npc.Set(m_Textlist[75], m_Textlist[76], e超级大熊猫, 84, 59);
		obj.m_Stage = 126;
		obj.m_pTask = this;
		AddTriggerObjMap(&obj);
	}
		break;
	case 126:

	{
		//			m_AddPoint = g_addPointAtk;
		Add变身Enemy2(8000, e超级大熊猫, 35, eMP_狮驼岭);
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 3)
			{
			case 0:petid = e黑熊;
				break;
			case 1:petid = e白熊;
				break;
			default:petid = e黑熊精;
				break;
			}
			AddPetEnemy2(3000, petid, 40);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(127);
	}
		break;
	case 127:

	{
		SetJiangLi2(200000, 20000, 50000, 200000);
		AddTriggerObj2(23, 24, 25);
		UpdateJob2(39);

		RemoveTriggerObjMap();
		RemoveNpc(81, true);
		//		g_pMainState->LockLv(55);
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
		// 		g_pCharacter->m_PCData.AddAtkZZ(50);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		AddChannel2(82);
		AddChannel2(83);
		sShangPinPet sppet;
		sppet.Set(e超级大熊猫, 0, 100, true);
		GetPet(m_Textlist[64], &sppet, 100);
	}
		break;
	case 25://青莲仙女
		AddFriend(84);
		AutoGetPet(m_Textlist[84]/*, 0*/);
		AddTriggerDialog2(16, -1);
		AddTriggerObj2(25, 26, 26);
		UpdateJob2(27);
		break;
	case 26://孟婆
		AddTriggerDialog2(17, -1);
		AddTriggerObj2(28, 29, 27);
		UpdateJob2(30);
		break;
	case 27://幽冥鬼
		AddTriggerDialog2(18, 28);
		break;
	case 28:

	{
		//			m_AddPoint = g_addPointSpd;
		Add变身Enemy2(5000, e巡游天神, 40, eMP_阴曹地府, 28);
		for (int i = 0; i < 4; i++)
		{
			ePetID petid;
			switch (rand() % 4)
			{
			case 0:petid = e骷髅怪;
				break;
			case 1:petid = e马面;
				break;
			case 2:petid = e僵尸;
				break;
			default:petid = e牛头;
				break;
			}
			Add变身Enemy2(3000, petid, 30);
		}
		SetMusic();

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(29);
	}
		break;
	case 29:
		TalkList(19, 31, 32, 33, 30);

		SetJiangLi2(300000, 50000, 50000, 250000);

		// 		g_pCharacter->m_PCData.AddDefZZ(50);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		//		g_pMainState->LockLv(45);
		break;
	case 30://文秀
		AddTriggerObj2(28, 29, 31);
		AddTriggerDialog2(20, -30);
		break;
	case -30:
		SetJiangLiItem(5, 18);
		UpdateJob2(30);
		break;
	case 31://幽冥鬼
		AddTriggerObj2(25, 26, 32);
		AddTriggerDialog2(21, -1);
		UpdateJob2(27);
		break;
	case 32://孟婆
		AddTriggerObj2(22, 11, 33);
		AddTriggerDialog2(22, -1);
		UpdateJob2(40);
		break;
	case 33://玄奘
		AddTriggerObj2(34, 8, 34);
		AddTriggerDialog2(23, -1);
		UpdateJob2(35);
		break;
	case 34://守卫
		AddTriggerDialog2(24, 35); break;
	case 35:
	{
		//		m_AddPoint = g_addPointAtk;
		for (int i = 0; i < 5; i++)
		{
			auto p = Add变身Enemy2(5000, e护卫, 35, eMP_大唐官府, 34);
			p->AddSkill(ePS_高级吸血);

		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(36);
	}
		break;
	case 36:
		AddTriggerObj2(36, 8, 37);
		AddTriggerDialog2(25, -1);
		SetJiangLi2(300000, 20000, 50000, 270000);
		UpdateJob2(37);
		// 		g_pCharacter->m_PCData.AddHpZZ(100);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(45);
		break;
	case 37://殷温娇
		AddTriggerObj2(41, 8, 38);
		AddTriggerDialog2(26, -1);
		UpdateJob2(42);
		break;
	case 38:AddTriggerDialog2(27, 39);
		break;
	case 39://虾兵战斗

	{
		cPropertyData* pPet;
		//			m_AddPoint = g_addPointMag;
		pPet = Add变身Enemy2(8000, e虾兵, 40, eMP_东海龙宫, 41);
		pPet->MagicWater.d2 += 30;
		for (int i = 0; i < 4; i++)
		{
			ePetID petid;
			switch (rand() % 4)
			{
			case 0:petid = e海星;
				break;
			case 1:petid = e章鱼;
				break;
			case 2:petid = e大海龟;
				break;
			default:petid = e海毛虫;
				break;
			}
			pPet = Add变身Enemy2(5000, petid, 40);
			pPet->MagicWater.d2 += 20;
		}
		g_pMainState->m_Mp3.Load("战斗BOSS");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(40);
		AddTriggerDialog2(51);
	}
		break;
	case 40:
		AddTriggerObj2(44, 45, 41);
		SetJiangLi2(300000, 100000, 50000, 300000);
		UpdateJob2(43);
		// 		g_pCharacter->m_PCData.AddMagZZ(100);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		//		g_pMainState->LockLv(47);
		break;
		//蟹将战斗
	case 41:AddTriggerDialog2(28, 42);
		break;
	case 42:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(8000, e蟹将, 49, eMP_东海龙宫, 44);
		pPet->MagicWater.d2 += 50;
		for (int i = 0; i < 4; i++)
		{
			ePetID petid;
			switch (rand() % 4)
			{
			case 0:petid = e海星;
				break;
			case 1:petid = e章鱼;
				break;
			case 2:petid = e虾兵;
				break;
			default:petid = e海毛虫;
				break;
			}
			Add变身Enemy2(5000, petid, 49, eMP_随机);
			pPet->MagicWater.d2 += 30;
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(43);
	}
		break;
	case 43:
		TalkList(29, 46, 45, 47, 44);
		SetJiangLi2(300000, 100000, 50000, 320000);
		// 		g_pCharacter->m_PCData.AddMagZZ(100);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		//		g_pMainState->LockLv(48);
		break;
	case 44://龟千岁
		TalkList(30, 36, 8, 37, 45);
		break;
	case 45://殷温娇
		TalkList(31, 49, 50, 48, 46);
		break;
	case 46://殷丞相
		TalkList(32, 52, 53, 51, 47);
		AddTriggerGive(m_Textlist[49], 22, 30, 49);
		break;
	case 47://江湖奸商
		AddTriggerDialog2(33, 48); break;
	case 48:
		RemoveTriggerObj();
		SetJiangLiItem(30, 22);
		g_pCharacter->m_PcData.m_Money[0] -= 50000;
		break;
	case 49://殷丞相

	{
		AddTriggerDialog2(34, -1);
		UpdateJob2(56);
		sNpc npc;
		npc.Set(m_Textlist[66], m_Textlist[8], 2012, 226, 190, 3);
		AddTriggerObjMap(&npc, 152);
		npc.Set(m_Textlist[67], m_Textlist[8], e山贼, 230, 186, 7);
		AddTriggerObjMap(&npc, 152, 0);
		npc.Set(m_Textlist[67], m_Textlist[8], e山贼, 233, 194, 1);
		AddTriggerObjMap(&npc, 152, 0);
		AddTriggerObjMap(m_Textlist[8], 151, 0);
	}
		break;
	case 151:
		AddTriggerDialog2(44, -1);
		RemoveTriggerObjMap(151);
		UpdateJob2(68);
		break;
	case 152://山贼战斗
		AddTriggerDialog2(45, 153);
		break;
	case 153:
	{
		cPropertyData *pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		if (!pet)
		{
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
			pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		}
		g_pMainState->m_pFightState->m_FightMenu.SetControl(pet->m_IDinFightWorkList, false);
		for (int i = 0; i < 10; i++)
		{
			ePetID petid;
			switch (rand() % 4)
			{
			case 0:petid = e山贼;
				break;
			default:petid = e强盗;
				break;
			}
			Add变身Enemy2(5000, petid, 30);
		}
		SetMusic();

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(154);
	}
		break;
	case 154:
		RemoveNpc(67);
		RemoveNpc(67, 1);
		RemoveTriggerObjMap(-1);
		TalkList(46, 54, 55, 56, 50, 155);
		SetJiangLi2(300000, 100000, 50000, 340000);
		//		g_pCharacter->m_PCData.AddGrowing(5);
		//		g_pMainState->LockLv(49);
		break;
	case 155:
		RemoveNpc(66, 1);
		break;
	case 50://刘洪1
		AddTriggerDialog2(35, 51);
		break;
	case 51:
	{
		cPropertyData *pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		if (!pet)
		{
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
			pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		}
		g_pMainState->m_pFightState->m_FightMenu.SetControl(pet->m_IDinFightWorkList, false);
		auto p = Add变身Enemy2(8000, e护卫, 50, eMP_大唐官府, 54);
		p->AddSkill(ePS_吸血);
		for (int i = 0; i < 7; i++)
		{
			// 			ePetID petid;
			// 			switch (rand() % 4)
			// 			{
			// 			case 0:petid = e山贼;
			// 				break;
			// 			case 1:petid = e护卫;
			// 				break;
			// 			case 2:petid = e赌徒;
			// 				break;
			// 			default:petid = e强盗;
			// 				break;
			// 			}
			Add变身Enemy2(5000, e护卫, 49);
		}
		SetMusic();

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(52);
	}
		break;
	case 52:
	{
		g_pMainState->SetDialogList(m_Textlist[69], g_pMainState->m_PetDataManager.GetPetData(e程咬金)->m_dialoghead[0]);
		TalkList(36, 54, 57, 58, 53);

		SetJiangLi2(400000, 100000, 50000, 350000);
		// 			g_pCharacter->m_PCData.AddAtkZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(55);
	}
		break;
	case 53://刘洪2
		AddTriggerDialog2(37, 54);
		break;
	case 54:
	{
		cPropertyData *pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		if (!pet)
		{
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
			pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		}
		g_pMainState->m_pFightState->m_FightMenu.SetControl(pet->m_IDinFightWorkList, false);
		cPropertyData* pPet;
		pPet = Add变身Enemy2(12000, e护卫, 59, eMP_大唐官府, 54);
//		pPet->m_AtkDownHPHurt.d1 += 5;
		pPet = Add变身Enemy2(8000, e强盗, 59, eMP_阴曹地府, 59);
		pPet->AddSkill(ePS_鬼魂术);
		for (int i = 0; i < 5; i++)
		{
			ePetID petid;
			switch (rand() % 4)
			{
			case 0:petid = e骷髅怪;
				break;
			case 1:petid = e马面;
				break;
			case 2:petid = e僵尸;
				break;
			default:petid = e牛头;
				break;
			}
			Add变身Enemy2(5000, petid, 49);//(eMengPai)(rand() % 12));
		}
		SetMusic("OneLight");

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(55);
	}
		break;
	case 55:
	{
		//			g_pMainState->LockLv(65);
		AddTriggerDialog2(38, -57);
		cPropertyData *pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		if (!pet)
		{
			g_pMainState->SetFightPet(g_pMainState->m_HeroID, -1);
			pet = Add变身Enemy2(50000, e程咬金, 50, eMP_大唐官府, -1, true);
		}
		g_pMainState->m_pFightState->m_FightMenu.SetControl(pet->m_IDinFightWorkList, false);
		cPropertyData* pPet = Add变身Enemy2(20000, e黑山老妖, 59, eMP_阴曹地府, 59);
		pPet->AddSkill(ePS_鬼魂术);
		pPet->SuckBloodPercent.d1 += 30;
		pPet->SetJinJie(2);
		for (int i = 0; i < 9; i++)
		{
			ePetID petid;
			switch (rand() % 4)
			{
			case 0:petid = e黑山老妖;
				break;
			case 1:petid = e马面;
				break;
			case 2:petid = e僵尸;
				break;
			default:petid = e牛头;
				break;
			}
			Add变身Enemy2(5000, petid, 49);
		}
		SetMusic("凶夢伝染");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(57);

	}
		break;
	case -57:
		AddTriggerDialog2(47);
		break;
	case 57:
		AddTriggerDialog2(39, -1);
		AddTriggerObj2(61, 8, 58);
		SetJiangLi2(500000, 100000, 50000, 400000);
		UpdateJob2(62);
		// 		g_pCharacter->m_PCData.AddDefZZ(100);
		// 		g_pCharacter->m_PCData.AddHpZZ(300);
		// 		g_pCharacter->m_PCData.AddGrowing(1);
		//		g_pMainState->LockLv(56);
		break;
	case 58://刘母
		AddTriggerDialog2(40, 59);
		g_pMainState->m_DialogList.clear();
		break;
	case 59:
		AddTriggerObj2(36, 8, 60);
		UpdateJob2(37);
		break;
	case 60://殷温娇
		AddTriggerDialog2(41, -1);
		AddTriggerObj2(22, 11, 61);
		UpdateJob2(63);
		break;
	case 61://玄奘
		TalkList(42, -1, -1, -1, -1, 62);
		break;
	case 62:
		SetJiangLiItem(6, 40);
		AddTriggerDialog2(48);
		Process2(0);
		break;
#endif
	default:
		ERRBOX;
		break;

	}
	return true;
}

