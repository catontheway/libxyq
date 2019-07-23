#include "_global.h"



bool TaskZhuXian::Process5(int stage)
{
	int next = stage + 1;
	setJobTitle("含冤的小白龙");
	int i = 10;
	int r = rand() % 20;
	switch (stage)
	{
	case 0:
		AddTriggerDialog("#G哎，最近的日子可真难过#G#103"
			, "大力兄什么事情这么烦心啊", "最近跟几个猪朋狗友在喝酒的时候，不知道把打神鞭落在哪处了，没那鞭子我可要职位不保啊！#4", "今天刚好有空，我帮你找找吧",
			"那太谢谢你！你真是我的好兄弟。");
		AddJob("#R任务提示#R：\n#B长寿村#B\n#R相关人物：#R\n#B毛驴张 #B\n#R任务介绍#R\n长寿村（81，129）的毛驴张捡到了一根从天而降的鞭子，正是大力神灵遗失的玄天铁鞭。 ");
		break;
	case 1:
		AddTriggerObj("毛驴张", "长寿村");
		break;
	case 2:
		AddTriggerDialog(""
			, "毛张驴，听说你最近得了件宝物，能否让我见识见识",
			"#2你谁啊！我咋不认识你啊，还有我叫毛驴张，不叫毛张驴。",
			"我是你隔壁王老狗啊！我们还一起喝过酒的咧，你这鞭子挺漂亮的，能送给我不。",
			"那可不行！除非你能找瓶神仙饮来换。",
			"没问题，包我身上。");
		AddJob("#R任务提示#R：\n#B长寿村#B\n#R相关人物：#R\n#B毛驴张 #B\n#R任务介绍#R\n找神仙饮换毛驴张的打神鞭 ");
		break;

	case 3:
		AddTriggerGive("毛驴张", 22, 52, _next);
		break;

	case 4:
		g_pMainState->awardk(0, 50);
		g_pMainState->m_pNowSelect = g_pMainState->FindObjByName("毛驴张");
		AddTriggerDialog("谢谢你，今晚有酒喝了");
		break;
	case 5:
		getTag("得到打神鞭");
		AddJob("#R任务提示#R：\n#B天宫#B\n#R相关人物：\n#B#大力神灵 #B\n#R任务介绍#R\n把打神鞭交还给大力神灵");
		AddTriggerObj("大力神灵", "天宫", _next);
		break;
	case 6:
		getTag("失去打神鞭");
		AddTriggerDialog("我真是太崇拜你了,办事速度真不是一般的快，我终于不用被玉帝体罚了#1",
			"#3，那是当然，现在办事没点速度，还怎么在这个地球上生存。（貌似我跟谁也说过这话。。。。）",
			"", "话说你准备给谁行刑啊！", "你不知道么？是西海龙王的三太子打破了玉帝亲赐的夜明珠，犯了诛九族的大罪，他父亲为了保存宗室血脉！无奈上告天庭，玉帝大怒，令我重打300大板，然后送他去见佛祖，这会估计在天牢喊冤呢！"
			,"有这等事，我去看看小白龙现在什么情况，没它唐三藏去不了西天取经啊！");
		AddJob("#R任务提示#R：#B天宫#B\n#R相关人物：#R#B天牢守卫 #B\n#R任务介绍#R\n去天牢看望小白龙");
		break;
	case 7:
		AddTriggerObj("天牢守卫");
		break;
	case 8:
		AddTriggerDialog(""
			, "守卫大哥，我想打听打听关在这里小白龙的事情，顺便看望一下他",
			"这恐怕办不到！小白龙在昨晚打伤天牢守卫，越狱了，具体去哪里我也不知道，可能返回海底了吧",
			"哦，原来是这样子，不怕我发动广大人民群众的人肉搜索功能就能找到他，谢谢了。",
			"不用客气，我也觉得他是冤枉的！");
		AddJob("#R任务提示#R：\n#B海底迷宫五层#B\n#R相关人物：#R\n#B小白龙 #B\n#R任务介绍#R\n去海底迷宫五层（54，38）找到越狱的小白龙 ");
		break;
	case 9:
		AddTriggerObj("小白龙", "海底迷宫五层");
		break;
	case 10:
		AddTriggerDialog(""
			, "可找到你了,你师父糖曾已经离开怜香阁了,你现在去找你师父，准备驮他去取经吧.",
			"来者何人？该不会是天庭派下来捉我的狗腿子吧！肯定是，我是不会乖乖地就范的，吃我一嘴",
			"just wait a minute!#8，妈的，生活在水下的东西都尼玛听不懂人话是么？",
			"受死吧！玉帝的走狗！");
		break;
	case 11:
	{
		auto pc = AddEnemy(30000, e蛟龙, 65, eMP_东海龙宫, "小白龙");
		pc->getObj()->say("#17玉帝的走狗#17，我是不会屈服在你的淫威之下的#2");
		AddEnemy(10000, e小龙女, 60, eMP_随机);
		AddEnemy(10000, e鲛人, 60, eMP_随机);
		AddEnemy(10000, e蚌精, 60, eMP_随机);
		AddEnemy(10000, e龟丞相, 60, eMP_随机);
		AddEnemy(10000, e虾兵, 60, eMP_输出);
		g_pMainState->m_FightWorkList[13 + rand() % 5].m_pObj->say("#G保护小白龙，吾等所向披靡！#G#118");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next);
		break;
	}

	case 12:
		AddTriggerDialog("可恶，居然这样就输了..我不甘心。。",
			"小白龙我不是来捉你的，我是来了解事情的真相的，你们龙宫的人怎么老喜欢见面就开打",
			"不好意思误会了，我这几天都是提心吊胆的，前几天我被万胜公主污告说我打碎了玉帝送的珠子，天庭派人把我抓了过去,判了我死刑,我好不容易逃出来.躲在这里，我是冤枉的#15玉帝送的珠子,我一直寄放在我朋友镇塔之神那里.打碎的那个只是180万一个便宜货,但万胜公主就一口咬定是我打碎了玉帝送的珠子",
			"(180W的便宜货.........真想烧死你这个富二代#71)", "你拿着我的信物龙鳞去找镇塔之神帮忙。", "好吧,我去找镇塔之神问问#3");
		g_pMainState->awardEquip(60);
		g_pMainState->awardk(350, 80);
		getTag("得到龙鳞");
		AddTriggerObj("小白龙");
		g_pMainState->FindObjByName("小白龙")->say("玉帝想捉我，没那么容易");
		AddJob("#R任务提示#R：\n#B大雁塔七层#B\n#R相关人物：#R\n#B镇塔之神 #B\n#R任务介绍#R\n去大雁塔七层找到镇塔之神问珠子的事情");
		break;

	case 13:
		AddTriggerObj("镇塔之神", "大雁塔七层");
		break;
	case 14:
		getTag("失去龙鳞");
		AddTriggerDialog("这样啊,虽然我很想帮小白龙,但那个珠子被人偷走了.所以我也无法证明不是小白龙打碎了珠子.现在妖魔横行，要是给他们逃出大雁塔就麻烦了",
			"那我该怎么办才好？",
			"我用法力封住了一个小偷,做为镇塔之神,我不能擅离职守,他现在在塔里出不去了,他应该在四层,你去找到他,问他同伙的下落吧.",
			"好的。谢谢！");
		AddJob("#R任务提示#R：\n#B大雁塔四层#B\n#R相关人物：#R\n#B奔波儿灞 #B\n#R任务介绍#R\n去大雁塔四层找姓奔的");
	case 15:
		AddTriggerObj("奔波儿灞", "大雁塔四层");
		break;
	case 16:
		AddTriggerDialog("我叫奔波儿灞。是乱石山波波谈万圣龙王手下的蛤蟆精，我家万圣公主招了哥名为九头精怪的驸马，法力无边，最近在塔里偷了一个珠子，怕被人发现，叫我在这里看守",
			"你真是个诚实的孩纸？",
			"我也没办法，本来我不想战斗的，但是作者说，在这里一定的战斗，不然剧情太短，所以没办法，你懂的，不过在这之前你得先和我3个手下过过招，我毕竟是BOSS，得最后登场",
			"作者也真是闲的蛋疼啊！没办法只有跑剧情维持维持生活这样子。");
		AddJob("#R任务提示#R：\n#B大雁塔四层#B\n#R相关人物：#R\n#B血之魅 #B\n#R任务介绍#R\n去大雁塔四层收复血之魅（需战斗）");
		break;

	case 17:
		AddTriggerObj("血之魅");
		break;
	case 18:
	{
		AddEnemy(20000, e野鬼, 60, eMP_阴曹地府, "血之魅");
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(10000, e野鬼, 60, eMP_随机);
		}
		AddJob("#R任务提示#R：\n#B大雁塔五层#B\n#R相关人物：#R\n#B森之魅 #B\n#R任务介绍#R\n去大雁塔五层收复森之魅（需战斗）");
		readyFightAndSucces();
	}
		break;

	case 19:
		
		AddTriggerObj("森之魅", "大雁塔五层");
		break;

	case 20:
	{
		AddEnemy(20000, e吸血鬼, 60, eMP_狮驼岭, "森之魅");
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(10000, e僵尸, 60, eMP_随机);
		}
		AddJob("#R任务提示#R：\n#B大雁塔二层#B\n#R相关人物：#R\n#B奔波儿灞 #B\n#R任务介绍#R\n去大雁塔二层收复梦之魅（需战斗）");
		readyFightAndSucces();
	}
		break;

	case 21:

		AddTriggerObj("梦之魅", "大雁塔二层");
		break;
	case 22:
	{
		AddEnemy(20000, e僵尸, 60, eMP_大唐官府, "梦之魅");
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(10000, e野鬼, 60, eMP_随机);
		}
		AddJob("#R任务提示#R：\n#B大雁塔四层#B\n#R相关人物：#R\n#B奔波儿灞 #B\n#R任务介绍#R\n去大雁塔四层打败奔波儿灞（需战斗）");
		readyFightAndSucces();
	}
		break;

	case 23:

		AddTriggerObj("奔波儿灞", "大雁塔四层");
		break;
	case 24:
		AddTriggerDialog("少侠功夫了得，看来我也得尽全力应战才行",
			"呵呵，没有办法我就是这么强大，让你一血我都不怕",
			"忍法-创造再生之术、忍法-通灵之术",
			"#17好像很厉害的样子");
		AddJob("#R任务提示#R：\n#B大雁塔四层#B\n#R相关人物：#R\n#B血之魅 #B\n#R任务介绍#R\n去大雁塔四层收复血之魅（需战斗）");
		break;
	case 25:
	{
		auto pc = AddEnemy(30000, e蛤蟆精, 40, eMP_大唐官府, "奔波儿灞");
		pc->LiveHp += 1000;
		pc->LiveRestoreRate += 50;
		pc->StartMagic = ePS_高级必杀 + 2000;
		pc->DmgPercentOfFix.d2 += 30;
		pc->DmgPercentOfMagic.d2 += 20;
		pc->HitRateOfSeal.d1 += 10000;
		pc->DmgAddOfCure.d1 += 800;
		pc = AddEnemy(20000, e吸血鬼, 40, eMP_东海龙宫, "梦之魅");
		pc->LiveHp = 10000;
		pc->Speed.AddDataAdd(8000);
		pc = AddEnemy(20000, e僵尸, 40, eMP_阴曹地府, "血之魅");
		pc->LiveHp = 10000;
		pc->Speed.AddDataAdd(8000);
		pc = AddEnemy(20000, e野鬼, 40, eMP_狮驼岭, "森之魅");
		pc->LiveHp = 10000;
		pc->Speed.AddDataAdd(8000);
		for (int i = 0; i < 2; ++i)
		{
			AddEnemy(15000, e牛头, 45, eMP_随机);
		}

		for (int i = 0; i < 2; ++i)
		{
			AddEnemy(15000, e马面, 45, eMP_输出);
		}

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next );}
		break;
	case 26:
		AddTriggerObj("奔波儿灞");
		break;
	case 27:
		AddTriggerDialog("不打了，不打了，你都是开挂的，我全都招了",
			"早交代不就没那么多事情了",
			"珠子是九头精怪偷的,他和万胜公主有奸情.他们合伙让小白龙做替罪羊,这样日后他们拿关珠子招摇过市也没问题了.",
			"#17原来如此,你已经没有利用价值了#18");
		g_pMainState->awardk(400, 100);
		g_pMainState->awardItem(26, 108 + rand() % 80, 1, true);
		AddJob("#R任务提示#R：\n#B龙宫#B\n#R相关人物：#R\n#B蟹将 #B\n#R任务介绍#R\n去龙宫找万圣公主");
		break;
	case 28:

		AddTriggerObj("蟹将军", "龙宫");
		break;
	case 29:

		AddTriggerObj("蟹将军", "龙宫");
		break;
	case 30:
		g_pMainState->setNowSelect();
		AddTriggerDialog("来者何人何神何仙何魔!居然敢擅闯龙宫，吃我一钳子。",
			"这话我好像在哪里听过.......想起来了就上次来的时候，尼玛，不会这么健忘吧", "#G废话少说受死吧。", "#G我决定了今晚来个清蒸螃蟹。");
		break;

	case 31:
	{
		auto pc = AddEnemy(30000, e蟹将, 60, eMP_大唐官府, "蟹将军");
		pc->LiveHp = 1000;
		pc = AddEnemy(25000, e虾兵, 60, eMP_凌波城, "虾将军");
		pc->LiveHp = 1000;
		pc->Speed.AddDataAdd(8000);
		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(15000, e虾兵, 45, eMP_随机);
		}

		for (int i = 0; i < 4; ++i)
		{
			AddEnemy(15000, e蟹将, 45, eMP_输出);
		}

		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(_next + 1);
		AddTriggerFightTurn(_next);
	}
		break;
	case 32:
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
		lh->DmgAdd.d2 -= 5000;
		lb->Hit.AddDataAdd(5000);

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

		lb->getObj()->say("草泥马，给点力行不!");
		lh->getObj()->say("好的，大哥我一定努力!");
	}
		break;

	case 33:
		g_pMainState->awardEquip(80);
		g_pMainState->awardItem(27, 42 + rand() % 9, 1, true);
		g_pMainState->awardk(200, 250);//60W经验，100W钱
		AddJob("#R任务提示#R：\n#B龙宫#B\n#R相关人物：#R\n#B蟹将 #B\n#R任务介绍#R\n向蟹将军打探万圣公主位置");
		AddTriggerObj("蟹将军","龙宫");
		break;
	case 34:
		
		g_pMainState->FindObjByName("蟹将军")->say("#R万圣公主#R在20 64");
		g_pHeroObj->say("早说不就不用挨打了嘛#24");	
		AddTriggerObj("万圣公主", "龙宫", _next + 1);
		break;
	case 35:
		AddTriggerObj("万圣公主", "龙宫");
		break;
	case 36:
		
		AddTriggerDialog("你是什么人?是不是看见我美，想来强奸非礼我？",
			"你就想#4，你和九头精怪联手陷害小白龙的事我都已经知道了,坦白从宽,抗拒从严#4",
			"珠子是九头精怪偷的,少侠,我是被迫的,九头精怪偷了龙宫的龙须草,我如果不按他说的做,他就把龙须草带走#15.",
			"#17原来如此,然后呢#3#18",
			"我都照做了,他还是把龙须草拿走了#8九头精怪现在在牛魔王那里赴宴,我陪你去找他吧.");
		AddJob("#R任务提示#R：\n#B魔王居#B\n#R相关人物：#R\n#B九头精怪 #B\n#R任务介绍#R\n去牛魔王住处找九头精怪");
		break;

	case 37:

		AddTriggerObj("九头精怪", "魔王居");
		break;
	case 38:
		AddTriggerDialog("","九头精怪,今天就是你的死期#4",
			"口出狂言,今天要死的人是你#18#4");
		AddJob("#R任务提示#R：\n#B魔王居#B\n#R相关人物：#R\n#B九头精怪 #B\n#R任务介绍#R\n打败九头精怪");
		break;

	case 39:
	{
		auto pc = AddEnemy(40000, e九头精怪, 65, eMP_随机, "九头精怪");
		pc->getObj()->say("#G没错珠子是我偷的，有本事你来抢回去啊#G#17");
		pc = AddEnemy(35000, e狐狸精, 60, eMP_东海龙宫, "万圣公主");
		pc->getObj()->say("#G刚才没把握才把你引到这儿的,受死吧#18#G");
		pc->LiveHp = 100000;
		pc->Speed.AddDataAdd(8000);
		pc = AddEnemy(35000, e牛魔王, 60, eMP_魔王寨, "牛魔王");
		pc->getObj()->say("#G哪里来的妖怪,竟敢欺负俺老牛的朋友,来人拿下#4#G");
		pc->LiveHp = 100000;
		pc->Speed.AddDataAdd(8000);
		AddEnemy(18000, e花妖, 60, eMP_输出);
		AddEnemy(18000, e黑山老妖, 60, eMP_随机);
		AddEnemy(18000, e黑山老妖, 60, eMP_随机);
		AddEnemy(18000, e花妖, 60, eMP_随机);
		AddEnemy(18000, e牛妖, 60, eMP_随机);
		AddEnemy(18000, e牛妖, 60, eMP_随机);
		g_pMainState->SetRanse(i, 1);//给召唤兽加颜色代码
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#G出来搞事情了#18#");
		g_pMainState->m_FightWorkList[10 + rand() % 5].m_pObj->say("#18");
		readyFightAndSucces();
	}
		break;

	case 40:
		g_pMainState->awardEquip(70);
	
		if (r >6)//奖励代码段
		{

			if (r >= 0 && r <1)//10%
			{
				g_pMainState->awardBook(100 + (rand() % 4 * 10));//书
				g_pMainState->award5bao();//五宝

			}
			else if (r >= 1 && r<2)//10%
			{
				g_pMainState->awardIron(100 + (rand() % 4 * 10));//铁
				g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石

			}
			else if (r >= 2 && r<4)
			{
				g_pMainState->awardItem(23, rand() % 9, 1, true);
				g_pMainState->awardItem(27, 38 + rand() % 3, 1, true);//强化石
			}
			else if (r >= 4 && r <= 7)
			{
				g_pMainState->awardItem(23, rand() % 9, 1, true);
			}
		}

		else if (r>7)
		{
			g_pMainState->awardk(100, 100);//10W经验，10W钱
			g_pHeroObj->say("#15我不要当非洲人");;
		}
		///
		AddTriggerObj("九头精怪");
		g_pMainState->FindObjByName("九头精怪")->say("啊...可恶...我居然...会败在你葵花宝典的招式下~");
		AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B玉帝 #B\n#R任务介绍#R\n向玉帝说明情况");
		break;
	case 41:
		g_pMainState->awardk(1500, 400);
		AddTriggerDialog("啊...可恶...我居然...会败在你葵花宝典的招式下~", ".....居然打赢了,真是不可思议#3。。。.");
		AddJob("#R任务提示#R：\n#B凌宵宝殿#B\n#R相关人物：#R\n#B玉帝 #B\n#R任务介绍#R\n向玉帝说明情况，先看看九头精有啥遗言吧");
		break;

	case 42:
		AddTriggerObj("玉皇大帝", "凌宵宝殿");
		break;
	case 43:

		AddTriggerDialog("这不是我送小白龙的宝珠吗....",
			"小白龙是被九头精怪陷害的.他没有打碎珠子",
			"好吧,你去告诉小白龙吧,他无罪了#17");
		AddJob("#R任务提示#R：\n#B海底迷宫五层#B\n#R相关人物：#R\n#B小白龙 #B\n#R任务介绍#R\n去海底迷宫五层（54，38）找小白龙 ");
		break;
	case 44:
		AddTriggerObj("小白龙", "海底迷宫五层");
		break;

	case 45:

		AddTriggerDialog("请受小白龙一拜,我这就去找师父去.",
			"接下来去找猪八戒吧.");
		AddJob("#R任务提示#R：\n#B大唐境外#B\n#R相关人物：#R\n#B猪八戒 #B\n#R任务介绍#R\n去大唐境外找天蓬元帅猪八戒 ");
		break;
	case 46:
		RemoveTriggerObj();
		g_pMainState->m_Job.ReMoveJob(this);

		g_pHeroObj->say("#24下个剧情找大唐境外天蓬元帅启动");
		break;









#if 0
	case 0:
		g_GlobalValues[6] = 8;
		g_GlobalValues[5] = 7;
		SetChapter(5);
		AddTriggerObj2(8, 9, 1);
		UpdateJob2(10);
		break;
	case 1:
		AddTriggerDialog2(3, 3); //美猴王
		break;
	case 3:
	{
		Add变身Enemy2(30000, e雨师, 109, eMP_化生寺, 26);
		Add变身Enemy2(30000, e沙和尚, 109, eMP_东海龙宫, 28);
		Add变身Enemy2(30000, e猪八戒, 109, eMP_狮驼岭, 27);
		ePetID petid;
		for (int i = 0; i < 3; i++)
		{
			switch (rand() % 3)
			{
			case 0:petid = e巨力神猿; break;
			case 1:petid = e长眉灵猴; break;
			default:petid = e超级金猴; break;
			}
			Add变身Enemy2(10000, petid, 99);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(11);
	}
		return true;
	case 11:

	{
		SetJiangLi2(1250000, 250000, 250000, 1250000);

		AddTriggerDialog2(4, -11); //美猴王
		//			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(95);
	}
		return true;
	case -11:

	{
		auto pet = Add变身Enemy2(990000, e孙悟空, 69, eMP_大唐官府);
		pet->DmgAdd.d1 += 0x1fff;
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e巨力神猿; break;
			case 1:petid = e长眉灵猴; break;
			default:petid = e超级金猴; break;
			}
			Add变身Enemy2(8000, petid, 59);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(-13);
		AddTriggerFightFalse(-13);
		AddTriggerFightEscape(-13);
	}
		return true;
	case -13:

	{
		TalkList(5, 11, 12, 13, 12);
	}
		return true;


	case 12:TalkList(6, 14, 15, 16, next); break;//观音姐姐
	case 13:TalkList(7, 8, 9, 10, next); break;//李靖
	case 14:TalkList(8, 8, 17, 10, next); break;//美猴王
	case 15:AddTriggerDialog2(9, next); break;//美猴王
	case 16:

	{
		cPropertyData* pPet;
		pPet = Add变身Enemy2(30000, e孙悟空, 138, eMP_大唐官府);
		pPet->MagicFire.d2 += 20;
		pPet->HitRate.d2 += 30;
//		pPet->PeopleSpecial.d1 += 1000;
		ePetID petid;
		for (int i = 0; i < 4; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e巨力神猿; break;
			case 1:petid = e长眉灵猴; break;
			default:petid = e超级金猴; break;
			}
			Add变身Enemy2(10000, petid, 99);
		}
		SetMusic("打不倒的空气人");
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(17);
	}
		return true;
	case 17:

	{
		SetJiangLi2(1300000, 250000, 250000, 1300000);

		TalkList(10, 14, 15, 16, next);
		//			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(105);
		AddChannel2(37);
		int xp, yp;
		for (int i = 0; i < 55; i++)
		{
			g_pMainState->m_Map.AutoGetPos(xp, yp, m_Textlist[36]);
			switch (rand() % 3)
			{
			case 0:
				AddTriggerObjMap2(35, 36, e鬼将, xp, yp, -1, -17);
				break;
			case 1:
				AddTriggerObjMap2(35, 36, e净瓶女娲, xp, yp, -1, -18);
				break;
			case 2:
				AddTriggerObjMap2(35, 36, e炎魔神, xp, yp, -1, -19);
				break;
			}
		}
	}
		return true;
	case -17:

	{
		m_pObj = g_pMainState->m_pNowSelect;
		int lv = g_pCharacter->m_PcData.m_Lv;
		Add变身Enemy2(lv * 250, e鬼将, lv + 5, eMP_随机, 35);
		for (int i = 0; i < 7; i++)
			Add变身Enemy2(lv * 200, (ePetID)(35 + rand() % 20), lv);

		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(-117);
	}
		return true;
	case -18:

	{
		m_pObj = g_pMainState->m_pNowSelect;
		int lv = g_pCharacter->m_PcData.m_Lv;
		Add变身Enemy2(lv * 250, e净瓶女娲, lv + 5, eMP_随机, 35);
		for (int i = 0; i < 7; i++)
			Add变身Enemy2(lv * 200, (ePetID)(35 + rand() % 20), lv);

		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(-117);
	}
		return true;//
	case -19://炎魔神

	{
		m_pObj = g_pMainState->m_pNowSelect;
		int lv = g_pCharacter->m_PcData.m_Lv;
		cPropertyData* pPet;
		pPet = Add变身Enemy2(lv * 250, e炎魔神, lv + 5, eMP_魔王寨, 35);
		pPet->AddSkill(ePS_高级反震);
		for (int i = 0; i < 7; i++)
			Add变身Enemy2(lv * 200, (ePetID)(35 + rand() % 20), lv);

		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(-117);
	}
		return true;
	case -117:
		SetJiangLi2(100000, 50000, 50000, 100000);
		RemoveTriggerObjMap2(m_pObj);
		g_pMainState->m_Map.RemoveNpc(m_pObj, true);
		return true;
	case 18:TalkList(11, 18, 19, 20, next); break;//李靖
	case 19:TalkList(12, 11, 12, 13, next); break;//地藏王
	case 20:TalkList(13, 21, 22, 23, -20); break;//观音姐姐
	case -20:TalkList(14, 24, 22, 25, 21); break;//黑熊精
	case 21:AddTriggerDialog2(15, next); break;//小龙女
	case 22:

	{
		Add变身Enemy2(20000, e小龙女, 109, eMP_普陀山);
		ePetID petid;
		for (int i = 0; i < 7; i++)
		{
			switch (rand() % 2)
			{
			case 0:petid = e黑熊精; break;
			default:petid = e黑熊; break;
			}
			Add变身Enemy2(10000, petid, 89);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(23);
	}
		return true;
	case 23:

	{

		SetJiangLi2(1320000, 250000, 250000, 1320000);

		TalkList(16, 8, 9, 10, next);
		//			g_pCharacter->m_PCData.AddGrowing(1);
		//			g_pMainState->LockLv(99);
	}
		return true;
	case 24:AddTriggerDialog2(17, next); break;//美猴王
	case 25:

	{
		Add变身Enemy2(30000, e六耳猕猴, 159, eMP_大唐官府);
		ePetID petid;
		for (int i = 0; i < 9; i++)
		{
			switch (rand() % 4)
			{
			case 0:petid = e巨力神猿; break;
			case 1:petid = e长眉灵猴; break;
			default:petid = e超级金猴; break;
			}
			Add变身Enemy2(8000, petid, 109);
		}
		SetMusic();
		g_StateType = STATE_FIGHT;
		AddTriggerFightSuccess(26);

	}
		return true;
	case 26:

	{
		//			RemoveTriggerObjMap();//妖王没了
		SetJiangLi2(1400000, 250000, 300000, 1400000);
		RemoveTriggerObj();
		TalkList(18, -1, -1, -1, -1, -26);
		g_GlobalValues[14] += 200;
		g_GlobalValues[15] += 200;
//		g_pCharacter->m_PcData.m_BangPaiID = 0;
		// 			g_pCharacter->m_PCData.AddDefZZ(50);
		// 			g_pCharacter->m_PCData.AddGrowing(1);
		g_pMainState->LockLv(115);
	}
		return true;
	case -26:
		Un邀请("清风");
		AddFriend(32);
		g_pMainState->SetDialogListNpc(m_Textlist[31], 1081);
		TalkList(19, -1, -1, -1, -1, 28); break;//
		break;
	case 28:

	{
		g_pMainState->ClearDialogList();
		Un邀请("燕子");
		AddFriend(33);
		TalkList(20, -1, -1, -1, -1, -1);

		AutoGetPet(m_Textlist[33]/*, 3*/);
		Invite(m_Textlist[33]);

		AutoGetPet(m_Textlist[32]/*, 2*/);
		Invite(m_Textlist[32]);
		Un邀请("小蛮");
		AddFriend(34);
		//			AutoGetPet(m_Textlist[34], 4,5);
		Invite(m_Textlist[34]);

		////////////////////////////////////////////////////////////////////////// 呵呵哒 不要副本
		//			Process6(0);

		g_pMainState->m_TaskFB.Start(0);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.SetTask(this, 29);

	}
		break;
	case 29:
		g_pMainState->m_TaskFB.Start(1);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.SetTask(this, 30);
		break;
	case 30:
		g_pMainState->m_TaskFB.Start(2);
		g_pMainState->m_TaskFB.Process(0);
		g_pMainState->m_TaskFB.SetTask(this, 31);
		break;
	case 31:
		Process6(0);
		g_pMainState->LockLv(125);
		break;
#endif
	default:
		ERRBOX2(stage);
		break;
	}


	return true;
}
